//#include "framework.h" // from "axis/net/net_sockets.h"
//#include "axis/net/net_sockets.h"


ftpfs::ftpfs(::aura::application * papp, const char * pszRoot) :
   ::object(papp),
   ::data::data(papp),
   ::fs::data(papp),
   m_sockethandler(papp)
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

   ::file::path & path = listing[listing.add("ftp://")];
   
   UNUSED(path);

   listing.m_straTitle.add("FTP sites");

   return listing;

}


::file::listing & ftpfs::ls(::file::listing & listing)
{

   synch_lock sl(m_pmutex);

   if (listing.m_path == "ftp://")
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

   ::ftp::client_socket * pclient = NULL;

   int iTry = 0;

retry:

   defer_initialize(&pclient, listing.m_path);

   if (pclient->m_estate != ::ftp::client_socket::state_logged)
   {

      if (iTry > 3)
      {

         return listing = failure;

      }

      iTry++;

      goto retry;

   }

   string strPath;

   strPath = System.url().get_object(listing.m_path);

   if (!pclient->List(strPath, ptra))
   {

      if (iTry > 3)
      {

         return listing = failure;

      }

      pclient->m_estate = ::ftp::client_socket::state_initial;

      iTry++;

      goto retry;

   }

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

   if (is_dir(path))
   {

      return NULL;

   }

   if (pfesp != NULL)
   {

      ::release(pfesp->m_p);

   }

   if (nOpenFlags & ::file::mode_read && !(nOpenFlags & ::file::mode_write))
   {

      ::ftp::client_socket * pclient = NULL;

      int iTry = 0;

   retry:

      defer_initialize(&pclient, path);

      if (pclient->m_estate != ::ftp::client_socket::state_logged)
      {

         if (iTry > 3)
         {

            return NULL;

         }

         iTry++;

         goto retry;

      }

      ::file::path pathTemp = Application.file().time(System.dir().time());

      string strRemoteFile = System.url().get_object(path);

      if (!pclient->DownloadFile(strRemoteFile, pathTemp))
      {

         if (iTry > 3)
         {

            return NULL;

         }

         pclient->m_estate = ::ftp::client_socket::state_initial;

         iTry++;

         goto retry;

      }

      return Application.file().get_file(pathTemp, nOpenFlags, pfesp);

   }
   else
   {

      ::ftp::client_socket * pclient = NULL;

      defer_initialize(&pclient, path);

      ::file::buffer_sp spfile;

      spfile = canew(ftpfs_file(this, pclient));

      cres res = spfile->open(path, nOpenFlags);

      if (pfesp != NULL)
      {

         *pfesp = res;

      }

      return spfile;

   }

}


bool ftpfs::file_exists(const ::file::path & pszPath)
{

   return ::fs::data::file_exists(pszPath);

}


var ftpfs::file_length(const ::file::path & pszPath)
{

   return ::fs::data::file_length(pszPath);

}


void ftpfs::defer_initialize(::ftp::client_socket ** ppclient, string strPath)
{

   ::ftp::logon logon;

   logon.Hostname() = System.url().get_server(strPath);
   //logon.Username() = System.url().get_username(listing.m_path);

   string strUrl = "ftp://" + logon.Hostname() + "/";

   string strToken = strUrl;

   strToken.replace(":", "-");
   strToken.replace("/", "_");

   sp(::ftp::client_socket) & client = m_mapClient[strToken];

   int iTry = 0;

   if (client.is_null())
   {

      client = canew(::ftp::client_socket(m_sockethandler));

      sp(::ftp::output) & output = m_mapOutput[strToken];

      output = canew(::ftp::output(get_app()));

      client->AttachObserver(output);

   }

   *ppclient = client.m_p;

   if (client->m_estate == ::ftp::client_socket::state_initial || !client->IsConnected())
   {

   retry:

      Application.get_cred(strUrl, ::null_rect(), logon.Username(), logon.Password(), strToken, strUrl, true);

      if (!client->Login(logon))
      {

         Application.set_cred_ok(strToken, false);

         if (iTry > 3)
         {

            client->m_estate = ::ftp::client_socket::state_initial;

            return;

         }

         iTry++;

         goto retry;

      }

      Application.set_cred(strToken, logon.Username(), logon.Password());

      Application.set_cred_ok(strToken, true);

   }

   client->m_estate = ::ftp::client_socket::state_logged;

   //  \
   //   \
   //    }=====> Elegant code.
   //   /
   //  /

}

bool ftpfs::is_zero_latency(const ::file::path & psz)
{

   return false;

}
