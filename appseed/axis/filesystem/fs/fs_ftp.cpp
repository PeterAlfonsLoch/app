//#include "framework.h" // from "axis/net/net_sockets.h"
//#include "axis/net/net_sockets.h"


ftpfs::ftpfs(::aura::application * papp, const char * pszRoot) :
   ::object(papp),
   ::data::data(papp),
   ::fs::data(papp)
{

   m_strRoot = pszRoot;
   m_bInitialized = false;

   m_straServer.add("localhost");

}


bool ftpfs::fast_has_subdir(const ::file::path & path)
{

   synch_lock sl(m_pmutex);

   //   uint32_t dwTimeout;

   dir_listing & dir = m_map[path];

   if (get_tick_count() < dir.m_uiLsTimeout)
   {

      return dir.get_count() > 0;

   }

   return true;

}

bool ftpfs::has_subdir(const ::file::path & path)
{

   synch_lock sl(m_pmutex);

   //   uint32_t dwTimeout;

   dir_listing & dir = m_map[path];

   if (get_tick_count() < dir.m_uiLsTimeout)
   {

      return dir.get_count() > 0;

   }

   ::file::listing listing(this);

   listing.ls(path);

   if (get_tick_count() < dir.m_uiLsTimeout)
   {

      return dir.get_count() > 0;

   }

   return false;

}


::file::listing & ftpfs::root_ones(::file::listing & listing)
{

   for (auto strServer : m_straServer)
   {

      string strUrl;

      strUrl = "ftp://" + strServer;

      ::file::path pathUrl;

      pathUrl = strUrl;

      ::file::path & path = listing.add(pathUrl);

      path.m_iDir = 1;

      listing.m_straTitle.add(strUrl);

   }

   return listing;

}


::file::listing & ftpfs::ls(::file::listing & listing)
{

   synch_lock sl(m_pmutex);

   //   uint32_t dwTimeout;

   dir_listing & dir = m_map[listing.m_path];

   if (get_tick_count() < dir.m_uiLsTimeout)
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

   //try
   //{

   //   defer_initialize();

   //}
   //catch (string & str)
   //{

   //   if (str == "You have not logged in! Exiting!")
   //   {

   //      throw string("uftpfs:// You have not logged in!");

   //   }

   //   dir.m_uiLsTimeout = get_tick_count() + ((5000) * 4);

   //   listing = failure;

   //   return listing;

   //}

   ::ftp::file_status_ptra ptra;

   ::ftp::logon logon;

   logon.Hostname() = System.url().get_server(listing.m_path);
   //logon.Username() = System.url().get_username(listing.m_path);

   string strUrl = "ftp://" + logon.Hostname() + "/";

   string strToken = strUrl;

   strToken.replace(":", "-");
   strToken.replace("/", "_");
   
   Application.get_cred(strUrl, ::null_rect(), logon.Username(), logon.Password(), strToken, strUrl, true);

   sp(::ftp::client) & client = m_mapClient[strToken];

   if (client.is_null())
   {

      client = canew(::ftp::client(get_app()));

      if (!client->Login(logon))
      {

         Application.set_cred_ok(strToken, false);

         return listing = failure;

      }

      Application.set_cred(strToken, logon.Username(), logon.Password());
      Application.set_cred_ok(strToken, true);


   }



   string strPath;

   strPath = System.url().get_object(listing.m_path);

   client->List(strPath, ptra);

   for (auto pchild : ptra)
   {

      if (pchild->m_strAttributes.find_ci("d") < 0)
         continue;

      ::file::path & path = dir.add(::file::path(listing.m_path / pchild->m_strName, ::file::path_url));

      path.m_iDir = 1;

   }

   for (auto pchild : ptra)
   {

      if (pchild->m_strAttributes.find_ci("d") >= 0)
         continue;

      ::file::path & path = dir.add(::file::path(listing.m_path / pchild->m_strName, ::file::path_url));

      path.m_iSize = pchild->m_filesize;

      path.m_iDir = 0;

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



   dir.m_uiLsTimeout = get_tick_count() + ((1000) * 30);

   return listing;

}


bool ftpfs::is_dir(const ::file::path & path)
{
   //xml::node node(get_app());

   if (path.is_empty())
   {
      return true;
   }

   if (stricmp_dup(path, "ftp://") == 0)
   {
      return true;
   }
   if (stricmp_dup(path, "ftp:/") == 0)
   {
      return true;
   }
   if (stricmp_dup(path, "ftp:") == 0)
   {
      return true;
   }
   
   string strPath = path;

   if (::str::begins_eat_ci(strPath, "ftp://"))
   {
      ::str::ends_eat(strPath, "/");
      if(m_straServer.contains_ci(strPath))
      {
         return true;
      }
   }


   //defer_initialize();


   //uint32_t dwTimeout;

   synch_lock sl(m_pmutex);

   dir_listing & dir = m_map[path.folder()];

   if (::get_tick_count() > dir.m_uiTimeout)
   {

      ::file::listing listing(this);
      listing.ls(path.folder());
   }

   int iFind = dir.name_find_first_ci(path.name());

   if (iFind < 0)
   {

      return false;

   }

   return dir[iFind].m_iDir == 1;


}


bool ftpfs::file_move(const ::file::path & pszDst, const ::file::path & pszSrc)
{
   UNREFERENCED_PARAMETER(pszDst);
   UNREFERENCED_PARAMETER(pszSrc);
   return true;
}


::file::buffer_sp ftpfs::get_file(const ::file::path & path, UINT nOpenFlags, cres * pfesp)
{

   if (pfesp != NULL)
   {
      ::release(pfesp->m_p);
   }

   ::cres cres;

   ::file::buffer_sp spfile;

   spfile = canew(ftpfs_file(get_app(), path));

   cres = spfile->open(path, nOpenFlags);

   if (cres.failed())
   {

      spfile.release();

      if (pfesp != NULL)
      {

         *pfesp = cres;

      }

   }

   return spfile;

}


bool ftpfs::file_exists(const ::file::path & pszPath)
{

   return ::fs::data::file_exists(pszPath);

}


var ftpfs::file_length(const ::file::path & pszPath)
{

   return ::fs::data::file_length(pszPath);

}


void ftpfs::defer_initialize()
{

   if (!m_bInitialized)
   {


      m_bInitialized = true;

   }

}

bool ftpfs::is_zero_latency(const ::file::path & psz)
{

   return false;

}
