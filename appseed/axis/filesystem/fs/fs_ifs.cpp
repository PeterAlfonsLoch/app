//#include "framework.h" // from "axis/net/net_sockets.h"
//#include "axis/net/net_sockets.h"


ifs::ifs(::aura::application * papp, const char * pszRoot) :
   ::object(papp),
   ::data::data(papp),
   ::fs::data(papp)
{

   m_strRoot = pszRoot;
   m_bInitialized = false;

}


bool ifs::fast_has_subdir(const ::file::path & path)
{

   synch_lock sl(m_pmutex);

//   uint32_t dwTimeout;

   dir_listing & dir = m_map[path];

   if(get_tick_count() < dir.m_uiLsTimeout)
   {

      return dir.get_count() > 0;

   }

   return true;

}

bool ifs::has_subdir(const ::file::path & path)
{

   synch_lock sl(m_pmutex);

//   uint32_t dwTimeout;

   dir_listing & dir = m_map[path];

   if(get_tick_count() < dir.m_uiLsTimeout)
   {

      return dir.get_count() > 0;

   }

   ::file::listing listing(this);

   listing.ls(path);

   if(get_tick_count() < dir.m_uiLsTimeout)
   {

      return dir.get_count() > 0;

   }

   return false;

}


::file::listing & ifs::root_ones(::file::listing & listing)
{

   ::file::path & path = listing[listing.add("uifs://")];

   path.m_iDir = 1;

   listing.m_straTitle.add("User Intelligent File System");



   return listing;

}


::file::listing & ifs::ls(::file::listing & listing)
{

   synch_lock sl(m_pmutex);

//   uint32_t dwTimeout;

   dir_listing & dir = m_map[listing.m_path];

   if(get_tick_count() < dir.m_uiLsTimeout)
   {

      listing = dir;

      return listing;

   }

   dir.clear_results();

   listing.clear_results();


   //::file::patha  straDir;
   //::file::patha  straDirName;
   //::file::patha  straFile;
   //::file::patha  straFileName;
   //int64_array    iaFileSize;
   //int64_array    iaFolderSize;
   //bool_array     baFileDir;
   //bool_array     baFolderDir;

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

      dir.m_uiLsTimeout = get_tick_count() + ((5000) * 4);

      listing = failure;

      return listing;

   }

   xml::document doc(get_app());

   string strUrl;

   strUrl = "http://file.veriwell.net/ifs/ls?path=" + System.url().url_encode(listing.m_path);

   string strSource;

   property_set set(get_app());

   strSource = Application.http().get(strUrl, set);

   if(strSource.is_empty())
   {

      dir.m_uiLsTimeout = get_tick_count() + ((5000) * 4);

      return listing = failure;

   }

   if(!doc.load(strSource))
   {

      dir.m_uiLsTimeout = get_tick_count() + ((5000) * 4);

      return listing = failure;

   }

   if(doc.get_root()->get_name() != "folder")
   {

      dir.m_uiLsTimeout = get_tick_count() + ((5000) * 4);

      return listing = failure;

   }

   sp(::xml::node) pnode = doc.get_root()->get_child("folder");

   if(pnode != NULL)
   {

      for(auto pchild : pnode->children())
      {

         if(pchild->get_name() != "folder")
            continue;

         ::file::path & path = dir.add(::file::path(listing.m_path / pchild->attr("name").get_string(),::file::path_url));

         path.m_iDir = 1;
         
      }

   }

   pnode = doc.get_root()->get_child("file");

   if(pnode != NULL)
   {

      for(auto pchild : pnode->children())
      {

         if(pchild->get_name() != "file")
            continue;

         string strExtension = pchild->attr("extension");
         
         ::file::path & path = dir.add(::file::path(listing.m_path / pchild->attr("name").get_string(),::file::path_url));

         path.m_iSize = pchild->attr("size");

         path.m_iDir = 0;

      }

   }

   dir.m_uiTimeout = get_tick_count() + ((1000) * 4);



   listing = dir;

   //   if(m_mapdirFolder[strDir].is_null())
   //   m_mapdirFolder[strDir] = canew(stringa);
   //if(m_mapdirFolderName[strDir].is_null())
   //   m_mapdirFolderName[strDir] = canew(stringa);
   //if(m_mapdirFile[strDir].is_null())
   //   m_mapdirFile[strDir] = canew(stringa);
   //if(m_mapdirFileName[strDir].is_null())
   //   m_mapdirFileName[strDir] = canew(stringa);
   //if (m_mapdirFileSize[strDir].is_null())
   //   m_mapdirFileSize[strDir] = canew(int64_array);
   //if (m_mapdirFolderSize[strDir].is_null())
   //   m_mapdirFolderSize[strDir] = canew(int64_array);
   //if(m_mapdirFileDir[strDir].is_null())
   //   m_mapdirFileDir[strDir] = canew(bool_array);
   //if(m_mapdirFolderDir[strDir].is_null())
   //   m_mapdirFolderDir[strDir] = canew(bool_array);


   //::file::patha  & straThisDir         = m_mapdirFolder[strDir];
   //::file::patha  & straThisDirName     = m_mapdirFolderName[strDir];
   //::file::patha  & straThisFile        = m_mapdirFile[strDir];
   //::file::patha  & straThisFileName    = m_mapdirFileName[strDir];
   //int64_array    & iaThisFileSize      = *m_mapdirFileSize[strDir];
   //int64_array    & iaThisFolderSize    = *m_mapdirFolderSize[strDir];
   //bool_array     & baThisFileDir       = *m_mapdirFileDir[strDir];
   //bool_array     & baThisFolderDir     = *m_mapdirFolderDir[strDir];


   //straThisDir          = straDir;
   //straThisDirName      = straDirName;
   //straThisFile         = straFile;
   //straThisFileName     = straFileName;
   //iaThisFileSize       = iaFileSize;
   //iaThisFolderSize     = iaFolderSize;
   //baThisFileDir        = baFileDir;
   //baThisFolderDir      = baFolderDir;



   dir.m_uiLsTimeout = get_tick_count() + ((1000) * 4);

   return listing;

}


bool ifs::is_dir(const ::file::path & path)
{
   //xml::node node(get_app());

   if(path.is_empty())
   {
      return true;
   }

   if(stricmp_dup(path, "uifs://") == 0)
   {
      return true;
   }
   if(stricmp_dup(path,"uifs:/") == 0)
   {
      return true;
   }
   if(stricmp_dup(path,"uifs:") == 0)
   {
      return true;
   }


   defer_initialize();


   //uint32_t dwTimeout;

   synch_lock sl(m_pmutex);

   dir_listing & dir = m_map[path.folder()];

   if(::get_tick_count() > dir.m_uiTimeout)
   {

      ::file::listing listing(this);
      listing.ls(path.folder());
   }

   int iFind = dir.name_find_first_ci(path.name());

   if(iFind < 0)
   {
      
      return false;

   }

   return dir[iFind].m_iDir == 1;


}

//string ifs::file_name(const char * pszPath)
//{
//
//   string strPath(pszPath);
//
//   if(!::str::begins_eat_ci(strPath, "ifs://") && !::str::begins_eat_ci(strPath, "uifs://"))
//   {
//      return "";
//   }
//
//   strsize iFind = strPath.reverse_find("/");
//
//   if(iFind < 0)
//      iFind = -1;
//
//   return strPath.Mid(iFind + 1);
//
//}

bool ifs::file_move(const ::file::path & pszDst,const ::file::path & pszSrc)
{
   UNREFERENCED_PARAMETER(pszDst);
   UNREFERENCED_PARAMETER(pszSrc);
   return true;
}


::file::buffer_sp ifs::get_file(const ::file::path & path,UINT nOpenFlags,cres * pfesp)
{

   if(pfesp != NULL)
   {
      ::release(pfesp->m_p);
   }

   ::cres cres;

   ::file::buffer_sp spfile;

   spfile = canew(ifs_file(get_app(), path));

   cres = spfile->open(path,nOpenFlags);

   if(cres.failed())
   {
      
      spfile.release();

      if(pfesp != NULL)
      {

         *pfesp = cres;

      }

   }

   return spfile;

}


bool ifs::file_exists(const ::file::path & pszPath)
{

   return ::fs::data::file_exists(pszPath);

}


var ifs::file_length(const ::file::path & pszPath)
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

bool ifs::is_zero_latency(const ::file::path & psz)
{

   return false;

}
