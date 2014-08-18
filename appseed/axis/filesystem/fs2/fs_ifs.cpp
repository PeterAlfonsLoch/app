#include "framework.h"


ifs::ifs(sp(::axis::application) papp, const char * pszRoot) :
   element(papp),
   ::data::data(papp),
   ::fs::data(papp)
{
   m_strRoot = pszRoot;
   m_bInitialized = false;
}

bool ifs::fast_has_subdir(const char * pszPath)
{

   synch_lock sl(data_mutex());

   uint32_t dwTimeout;

   string strDir(pszPath);

   ::str::ends_eat(strDir, "/");
   ::str::ends_eat(strDir, "\\");

   if(m_maplsTimeout.Lookup(strDir, dwTimeout))
   {

      if(get_tick_count() < dwTimeout)
      {

         return m_mapdirFolder[strDir]->get_count() > 0;

      }

   }

   return true;

}

bool ifs::has_subdir(const char * pszPath)
{
   synch_lock sl(data_mutex());
   uint32_t dwTimeout;

   string strDir(pszPath);

   ::str::ends_eat(strDir, "/");
   ::str::ends_eat(strDir, "\\");

   if(m_maplsTimeout.Lookup(strDir, dwTimeout))
   {

      if(get_tick_count() < dwTimeout)
      {

         return m_mapdirFolder[strDir]->get_count() > 0;

      }

   }

   ls(pszPath, NULL, NULL, NULL, NULL);


   if(m_maplsTimeout.Lookup(strDir, dwTimeout))
   {

      if(get_tick_count() < dwTimeout)
      {

         return m_mapdirFolder[strDir]->get_count() > 0;

      }

   }


   return false;

}

void ifs::root_ones(stringa & straPath, stringa & straTitle)
{
   straPath.add("uifs://");
   straTitle.add("User Intelligent File System");
}



bool ifs::ls(const char * pszDir,stringa * pstraPath,stringa * pstraTitle,int64_array * piaSize,bool_array * pbaDir)
{
   synch_lock sl(data_mutex());
   uint32_t dwTimeout;

   string strDir(pszDir);

   ::str::ends_eat(strDir, "/");
   ::str::ends_eat(strDir, "\\");

   if(m_maplsTimeout.Lookup(strDir, dwTimeout))
   {
      if(get_tick_count() < dwTimeout)
      {
         if(pstraPath  != NULL)
         {
            pstraPath->add(*m_mapdirFolder[strDir]);
            pstraPath->add(*m_mapdirFile[strDir]);
         }
         if(pstraTitle  != NULL)
         {
            pstraTitle->add(*m_mapdirFolderName[strDir]);
            pstraTitle->add(*m_mapdirFileName[strDir]);
         }
         if (piaSize != NULL)
         {
            piaSize->add(*m_mapdirFolderSize[strDir]);
            piaSize->add(*m_mapdirFileSize[strDir]);
         }
         if(pbaDir != NULL)
         {
            pbaDir->add(*m_mapdirFolderDir[strDir]);
            pbaDir->add(*m_mapdirFileDir[strDir]);
         }
         return true;
      }
   }


   //if(!is_dir(strDir))
     // return false;


   if(m_mapdirFolder[strDir].is_null())
      m_mapdirFolder[strDir] = canew(stringa);
   if(m_mapdirFolderName[strDir].is_null())
      m_mapdirFolderName[strDir] = canew(stringa);
   if(m_mapdirFile[strDir].is_null())
      m_mapdirFile[strDir] = canew(stringa);
   if(m_mapdirFileName[strDir].is_null())
      m_mapdirFileName[strDir] = canew(stringa);
   if (m_mapdirFileSize[strDir].is_null())
      m_mapdirFileSize[strDir] = canew(int64_array);
   if (m_mapdirFolderSize[strDir].is_null())
      m_mapdirFolderSize[strDir] = canew(int64_array);
   if(m_mapdirFileDir[strDir].is_null())
      m_mapdirFileDir[strDir] = canew(bool_array);
   if(m_mapdirFolderDir[strDir].is_null())
      m_mapdirFolderDir[strDir] = canew(bool_array);


   stringa        & straDir         = *m_mapdirFolder[strDir];
   stringa        & straDirName     = *m_mapdirFolderName[strDir];
   stringa        & straFile        = *m_mapdirFile[strDir];
   stringa        & straFileName    = *m_mapdirFileName[strDir];
   int64_array    & iaFileSize      = *m_mapdirFileSize[strDir];
   int64_array    & iaFolderSize    = *m_mapdirFolderSize[strDir];
   bool_array     & baFileDir       = *m_mapdirFileDir[strDir];
   bool_array     & baFolderDir     = *m_mapdirFolderDir[strDir];


   straDir.remove_all();
   straDirName.remove_all();
   straFile.remove_all();
   straFileName.remove_all();
   iaFileSize.remove_all();
   iaFolderSize.remove_all();
   baFileDir.remove_all();
   baFolderDir.remove_all();




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
      m_maplsTimeout.set_at(strDir, get_tick_count() + ((5000) * 4));
      return false;
   }

   xml::document doc(get_app());

   string strUrl;

   strUrl = "http://file.veriwell.net/ifs/ls?path=" + url_encode_dup(pszDir);

   string strSource;

   property_set set(get_app());

   strSource = Application.http().get(strUrl, set);

   if(strSource.is_empty())
   {
      
      m_maplsTimeout.set_at(strDir, get_tick_count() + ((5000) * 4));

      return false;

   }

   if(!doc.load(strSource))
   {
      
      m_maplsTimeout.set_at(strDir, get_tick_count() + ((5000) * 4));

      return false;

   }

   if(doc.get_root()->get_name() != "folder")
   {

      m_maplsTimeout.set_at(strDir, get_tick_count() + ((5000) * 4));

      return false;

   }

   sp(::xml::node) pnode = doc.get_root()->get_child("folder");

   if(pnode != NULL)
   {

      for(int32_t i = 0; i < pnode->get_children_count(); i++)
      {

         string strName = pnode->child_at(i)->attr("name");

         if(pnode->child_at(i)->get_name() != "folder")
            continue;

         string strPath = dir_path(pszDir, strName);
         m_mapdirTimeout[strPath] = ::get_tick_count() + (4 * 1000);
         m_mapfileTimeout.remove_key(strPath);
         straDir.add(strPath);
         straDirName.add(strName);
         iaFolderSize.add(0);
         baFolderDir.add(true);
      }
   }

   pnode = doc.get_root()->get_child("file");

   if(pnode != NULL)
   {
      for(int32_t i = 0; i < pnode->get_children_count(); i++)
      {
         string strName = pnode->child_at(i)->attr("name");
         string strExtension = pnode->child_at(i)->attr("extension");
         if(pnode->child_at(i)->get_name() != "file")
            continue;
         string strSize = pnode->child_at(i)->attr("size");
         string strPath = dir_path(pszDir, strName);
         m_mapfileTimeout[strPath] = ::get_tick_count() + (4 * 1000);
         m_mapdirTimeout.remove_key(strPath);
         straFile.add(strPath);
         straFileName.add(strName);
         iaFileSize.add(::str::to_int64(strSize));
         baFileDir.add(false);
      }
   }
   if(pstraPath != NULL)
   {
      pstraPath->add(straDir);
      pstraPath->add(straFile);
   }
   if(pstraTitle != NULL)
   {
      pstraTitle->add(straDirName);
      pstraTitle->add(straFileName);
   }
   if (piaSize != NULL)
   {
      piaSize->add(iaFolderSize);
      piaSize->add(iaFileSize);
   }
   if(pbaDir != NULL)
   {
      pbaDir->add(baFolderDir);
      pbaDir->add(baFileDir);
   }

   m_maplsTimeout.set_at(strDir, get_tick_count() + ((5000) * 4));

   return true;
}

bool ifs::is_dir(const char * pszPath)
{
   synch_lock sl(data_mutex());

   //xml::node node(get_app());

   if(pszPath == NULL || strlen(pszPath) == 0)
   {
      return true;
   }

   if(stricmp_dup(pszPath, "uifs://") == 0)
   {
      return true;
   }


   defer_initialize();


   string strPath(pszPath);

   ::str::ends_eat(strPath, "/");
   ::str::ends_eat(strPath, "\\");


   uint32_t dwTimeout;

   if(m_mapfileTimeout.Lookup(strPath, dwTimeout))
   {
      if(::get_tick_count() > dwTimeout)
      {
         stringa straPath;
         stringa straTitle;
         int64_array iaSize;
         bool_array baDir;
         ls(Application.dir_name(strPath), &straPath, &straTitle, &iaSize, &baDir);
      }
      else
      {
         return false;
      }
   }

   if(m_mapdirTimeout.Lookup(strPath, dwTimeout))
   {
      if(::get_tick_count() > dwTimeout)
      {
         stringa straPath;
         stringa straTitle;
         int64_array iaSize;
         bool_array baDir;
         ls(Application.dir_name(strPath),&straPath,&straTitle,&iaSize, &baDir);
         if(m_mapdirTimeout.Lookup(strPath, dwTimeout))
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

   if(!::str::begins_eat_ci(strPath, "ifs://") && !::str::begins_eat_ci(strPath, "uifs://"))
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


::file::buffer_sp ifs::get_file(var varFile, UINT nOpenFlags)
{

   ::file::buffer_sp spfile;

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
      throw new ::file::exception(get_app(), ::file::exception::none, 01, varFile.get_string());
   }

   return spfile;

}


bool ifs::file_exists(const char * pszPath)
{

   return ::fs::data::file_exists(pszPath);

}


var ifs::file_length(const char * pszPath)
{

   return ::fs::data::file_length(pszPath);

}


void ifs::defer_initialize()
{

   if(!m_bInitialized)
   {
      
      
      m_bInitialized = true;

   }

}

bool ifs::is_zero_latency(const char * psz)
{

   return false;

}
