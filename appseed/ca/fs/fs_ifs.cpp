#include "framework.h"


ifs::ifs(::ca::applicationsp papp, const char * pszRoot) :
   ca(papp),
   ::ca::data(papp),
   ::fs::data(papp)
{
   m_strRoot = pszRoot;
}

bool ifs::has_subdir(const char * pszPath)
{

   defer_initialize();

   xml::document doc(get_app());

   string strUrl;

   strUrl = "http://file.veriwell.net/ifs/ls?path=" + System.url().url_encode(pszPath);

   string strSource;

   strSource = Application.http().get(strUrl);

   if(strSource.is_empty())
      return false;

   if(!doc.load(strSource))
      return false;

   if(doc.get_root()->get_name() != "folder")
      return false;

   xml::node * pnode = doc.get_child("folder");

   if(pnode == ::null())
      return false;

   if(pnode->get_children_count("folder") <= 0)
      return false;

   return true;

}

void ifs::root_ones(stringa & stra)
{
   stra.add("uifs://");
}



bool ifs::ls(const char * pszDir, stringa * pstraPath, stringa * pstraTitle)
{
   
   try
   {
      defer_initialize();
   }
   catch(string & str)
   {
      if(str == "You have not logged in! Exiting!")
      {
         throw string("uifs:// You have not logged in!");
      }
      return false;
   }

   xml::document doc(get_app());

   string strUrl;
   
   strUrl = "http://file.veriwell.net/ifs/ls?path=" + System.url().url_encode(pszDir);

   string strSource;

   strSource = Application.http().get(strUrl);

   if(strSource.is_empty())
      return false;

   if(!doc.load(strSource))
      return false;

   if(doc.get_root()->get_name() != "folder")
      return false;

   xml::node * pnode = doc.get_root()->get_child("folder");

   if(pnode != ::null())
   {
      for(int32_t i = 0; i < pnode->get_children_count(); i++)
      {
         string strName = pnode->child_at(i)->attr("name");
         if(pnode->child_at(i)->get_name() != "folder")
            continue;
         string strPath = dir_path(pszDir, strName);
         m_mapdirTimeout[strPath] = ::get_tick_count() + (4 * 1000);
         m_mapfileTimeout.remove_key(strPath);
         if(pstraPath != ::null())
         {
            pstraPath->add(strPath);
         }
         if(pstraTitle != ::null())
         {
            pstraTitle->add(strName);
         }
      }
   }

   pnode = doc.get_root()->get_child("file");

   if(pnode != ::null())
   {
      for(int32_t i = 0; i < pnode->get_children_count(); i++)
      {
         string strName = pnode->child_at(i)->attr("name");
         string strExtension = pnode->child_at(i)->attr("extension");
         if(pnode->child_at(i)->get_name() != "file")
            continue;
         string strPath = dir_path(pszDir, strName);
         m_mapfileTimeout[strPath] = ::get_tick_count() + (4 * 1000);
         m_mapdirTimeout.remove_key(strPath);
         if(pstraPath != ::null())
         {
            pstraPath->add(strPath);
         }
         if(pstraTitle != ::null())
         {
            pstraTitle->add(strName);
         }
      }
   }

   return true;
}

bool ifs::is_dir(const char * pszPath)
{


   //xml::node node(get_app());

   if(pszPath == ::null() || strlen(pszPath) == 0)
   {
      return true;
   }

   if(stricmp(pszPath, "uifs://") == 0)
   {
      return true;
   }


   defer_initialize();


   uint32_t dwTimeout;

   if(m_mapfileTimeout.Lookup(pszPath, dwTimeout))
   {
      if(::get_tick_count() > dwTimeout)
      {
         stringa straPath;
         stringa straTitle;
         ls(System.dir().name(pszPath), &straPath, &straTitle);
      }
      else
      {
         return false;
      }
   }

   if(m_mapdirTimeout.Lookup(pszPath, dwTimeout))
   {
      if(::get_tick_count() > dwTimeout)
      {
         stringa straPath;
         stringa straTitle;
         ls(System.dir().name(pszPath), &straPath, &straTitle);
         if(m_mapdirTimeout.Lookup(pszPath, dwTimeout))
         {
            return true;
         }
      }
      else
      {
         return true;
      }
   }

   return false;

}

string ifs::file_name(const char * pszPath)
{

   string strPath(pszPath);

   if(!::ca::str::begins_eat_ci(strPath, "ifs://") && !::ca::str::begins_eat_ci(strPath, "uifs://"))
   {
      return "";
   }

   strsize iFind = strPath.reverse_find("/");

   if(iFind < 0)
      iFind = -1;

   return strPath.Mid(iFind + 1);

}

bool ifs::file_move(const char * pszDst, const char * pszSrc)
{
   UNREFERENCED_PARAMETER(pszDst);
   UNREFERENCED_PARAMETER(pszSrc);
   return true;
}


::ca::filesp ifs::get_file(var varFile, UINT nOpenFlags)
{
   
   ::ca::filesp spfile;

   spfile = new ifs_file(get_app(), varFile);

   string strUrl;

   if(varFile.get_type() == var::type_propset)
   {
      if(varFile.has_property("url"))
      {
         strUrl = varFile["url"];
      }
      else
      {
         strUrl = varFile.propset().m_propertya[0].get_value();
      }
   }
   else
   {
      strUrl = varFile;
   }

   if(!spfile->open(strUrl, nOpenFlags))
   {
      throw new ::ca::file_exception(get_app(), ::ca::file_exception::none, 01, varFile.get_string());
   }

   return spfile;

}

bool ifs::file_exists(const char * pszPath)
{
   return ::fs::data::file_exists(pszPath);
}


void ifs::defer_initialize()
{
   
   if(!m_bInitialized)
   {
      //Application.http().get("http://file.veriwell.net/");
      m_bInitialized = true;
   }

}
