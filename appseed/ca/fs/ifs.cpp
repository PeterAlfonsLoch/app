#include "stdafx.h"


ifs::ifs(::ca::application * papp, const char * pszRoot) :
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

   strUrl = "http://file.veriwell.net/ls?path=" + System.url().url_encode(pszPath);

   string strSource;

   strSource = Application.http().get(strUrl);

   if(strSource.is_empty())
      return false;

   if(!doc.load(strSource))
      return false;

   if(doc.get_name() != "folder")
      return false;

   xml::node * pnode = doc.get_child("folder");

   if(pnode == NULL)
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
   
   strUrl = "http://file.veriwell.net/ls?path=" + System.url().url_encode(pszDir);

   string strSource;

   strSource = Application.http().get(strUrl);

   if(strSource.is_empty())
      return false;

   if(!doc.load(strSource))
      return false;

   if(doc.get_name() != "folder")
      return false;

   xml::node * pnode = doc.get_child("folder");

   if(pnode != NULL)
   {
      for(int i = 0; i < pnode->get_children_count(); i++)
      {
         string strName = pnode->child_at(i)->attr("name");
         if(pnode->child_at(i)->get_name() != "folder")
            continue;
         string strPath = dir_path(pszDir, strName);
         m_mapdirTimeout[strPath] = ::GetTickCount() + (4 * 1000);
         m_mapfileTimeout.remove_key(strPath);
         if(pstraPath != NULL)
         {
            pstraPath->add(strPath);
         }
         if(pstraTitle != NULL)
         {
            pstraTitle->add(strName);
         }
      }
   }

   pnode = doc.get_child("file");

   if(pnode != NULL)
   {
      for(int i = 0; i < pnode->get_children_count(); i++)
      {
         string strName = pnode->child_at(i)->attr("name");
         string strExtension = pnode->child_at(i)->attr("extension");
         if(pnode->child_at(i)->get_name() != "file")
            continue;
         string strPath = dir_path(pszDir, strName);
         m_mapfileTimeout[strPath] = ::GetTickCount() + (4 * 1000);
         m_mapdirTimeout.remove_key(strPath);
         if(pstraPath != NULL)
         {
            pstraPath->add(strPath);
         }
         if(pstraTitle != NULL)
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

   if(pszPath == NULL || strlen(pszPath) == 0)
   {
      return true;
   }

   if(stricmp(pszPath, "uifs://") == 0)
   {
      return true;
   }


   defer_initialize();


   DWORD dwTimeout;

   if(m_mapfileTimeout.Lookup(pszPath, dwTimeout))
   {
      if(::GetTickCount() > dwTimeout)
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
      if(::GetTickCount() > dwTimeout)
      {
         stringa straPath;
         stringa straTitle;
         ls(System.dir().name(pszPath), &straPath, &straTitle);
      }
      else
      {
         return true;
      }
   }

   if(m_mapfileTimeout.Lookup(pszPath, dwTimeout))
   {
      if(::GetTickCount() > dwTimeout)
      {
         return false;
      }
      else
      {
         return true;
      }
   }
   else
   {
      return false;
   }

   

   /*string strUrl;

   strUrl = "http://file.veriwell.net/ls?path=" + System.url().url_encode(pszPath);

   string strSource;

   strSource = Application.http().get(strUrl);

   if(strSource.is_empty())
      return false;

   if(!node.load(strSource))
      return false;

   if(node.m_strName != "folder")
      return false;

   return true;*/

}

string ifs::file_name(const char * pszPath)
{

   string strPath(pszPath);

   if(!gen::str::begins_eat_ci(strPath, "ifs://") && !gen::str::begins_eat_ci(strPath, "uifs://"))
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


ex1::filesp ifs::get_file(var varFile, UINT nOpenFlags, ::ex1::file_exception_sp * pexception)
{
   
   ex1::filesp spfile(new ifs_file(get_app()));

   if(!spfile->open(varFile.get_string(), nOpenFlags, pexception))
   {
      throw new ex1::file_exception_sp(get_app());
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
      Application.http().get("http://file.veriwell.net/");
      m_bInitialized = true;
   }

}
