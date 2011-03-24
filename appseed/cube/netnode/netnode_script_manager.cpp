#include "StdAfx.h"
#include "netnodeScriptManager.h"
#include "netnodeScriptCache.h"
#include "netnodeScriptCompiler.h"
#include "netnodeScriptClass.h"
#include "netnodeScriptInstance.h"

netnodeScriptManager::netnodeScriptManager(::ca::application * papp) :
   ca(papp),
   thread(papp),
   ::ca::message_window_simple_callback(papp),
   m_uiredir(papp)
{
   m_pcache = new netnodeScriptCache(papp);
   m_pcache->m_pmanager = this;
   m_pcompiler = new netnodeScriptCompiler(papp);
   m_pcompiler->m_pmanager = this;
   m_dwBuildTimeWindow = 84;
   m_dwBuildTimeRandomWindow = 77 * 5;
   m_musicdba.set_size(2);

   m_iDatabaseWaitTimeOut = 1000 * 1000 * 60;

   Begin();

}

netnodeScriptManager::~netnodeScriptManager(void)
{
   if(m_pcache != NULL)
   {
      delete m_pcache;
      m_pcache  = NULL;
   }
   if(m_pcompiler != NULL)
   {
      delete m_pcompiler;
      m_pcompiler = NULL;
   }
}

bool netnodeScriptManager::initialize_instance()
{
   initialize_message_window("ca2::fontopus::ccvotagus::netnode::cgclcst");
   m_pcompiler->initialize();

   clear_include_matches_folder_watch * pwatch = new clear_include_matches_folder_watch();
   pwatch->m_strPath = System.dir().netseed("ds\\ca2");
   pwatch->m_pmanager = this;
   AfxBeginThread(get_app(), clear_include_matches_FolderWatchThread, (LPVOID) pwatch);

   return true;
}


netnodeScriptInstance * netnodeScriptManager::get(const char * lpcszName)
{
   return m_pcache->create_instance(lpcszName);
  
}


void netnodeScriptManager::handle(netnodeSocket * pnetnodesocket)
{
   string strHead;
   netnodeScriptInstance * pinstance = get("system/seed_carlosgustavocecynlundgrencarlos");
   pnetnodesocket->m_pinstanceCurrent = pinstance;
   if(pinstance != NULL)
   {
      pinstance->m_strDebugRequestUri = pnetnodesocket->inattr("request_uri");
      pinstance->m_strDebugThisScript = "system/seed_carlosgustavocecynlundgrencarlos";
      pinstance->m_pnetnodesocket = pnetnodesocket;
      pinstance->m_pinstanceMain = pinstance;
      pinstance->m_pinstanceParent = NULL;
      pinstance->m_pmanager = this;
      pinstance->dinit();
      if(pinstance->m_iDebug > 0)
      {
         if(pinstance->get("debug_lib").is_set())
         {
            pnetnodesocket->response().file() << m_pcompiler->m_memfileLibError;
         }
      }
   }
   if(pinstance != NULL)
   {
      pinstance->main_initialize();
      try
      {
         pinstance->m_pscript->run(pinstance);
      }
      catch(const exit_exception &)
      {
      }
      catch(base_exception & e)
      {
         string str;
         e.GetErrorMessage(str);
         pinstance->dprint("str");
         TRACE0("Error: ::ca::exception at netnodeScriptManager::handle run");
         TRACE0(str);
      }
      catch(base_exception * pe)
      {
         string str;
         pe->GetErrorMessage(str);
         pinstance->dprint("str");

         TRACE0("Error: ::ca::exception * at netnodeScriptManager::handle run");
         TRACE0(str);

         delete pe;
      }
      catch(...)
      {
         TRACE0("Error: Exception at netnodeScriptManager::handle run");
      }
      try
      {
         pinstance->main_finalize();
      }
      catch(const ::ca::exception &)
      {
         TRACE0("Error: ::ca::exception at netnodeScriptManager::handle main_finalize");
      }
      catch(...)
      {
         TRACE0("Error: Exception at netnodeScriptManager::handle main_finalize");
      }
      try
      {
         pinstance->destroy();
      }
      catch(const ::ca::exception &)
      {
         TRACE0("Error: ::ca::exception at netnodeScriptManager::handle destroy pinstance");
      }
      catch(...)
      {
         TRACE0("Error: Exception at netnodeScriptManager::handle destroy pinstance");
      }
   }
   
}

netnodeScriptInstance * netnodeScriptManager::get_output_internal(netnodeScriptImpl * pinstanceParent, const char * lpcszName)
{
   string strName = gen::str::get_word(lpcszName, "?");
   if(strName.is_empty())
   {
      if(pinstanceParent != NULL)
      {
         if(pinstanceParent->m_pinstanceMain->m_iDebug > 0)
         {
            if(pinstanceParent->m_pscript->m_memfileError.get_length() > 0)
            {
               pinstanceParent->m_pinstanceMain->m_pnetnodesocket->response().file() << "netnodeScriptManager::get_output_internal is_empty script parent" << pinstanceParent->m_pscript->m_strName;
            }
         }
      }
      return NULL;
   }
   netnodeScriptInstance * pinstance = get(strName);
   if(pinstance != NULL)
   {
      pinstance->m_strDebugRequestUri = pinstanceParent->m_pinstanceMain->m_pnetnodesocket->inattr("request_uri");
      pinstance->m_strDebugThisScript = strName;
      pinstance->m_pnetnodesocket = pinstanceParent->m_pinstanceMain->m_pnetnodesocket;
      pinstance->m_pinstanceParent = pinstanceParent;
      pinstance->m_pinstanceMain = pinstanceParent->m_pinstanceMain;
      pinstance->m_pmanager = this;
      pinstance->dinit();
      if(pinstance->m_pinstanceMain->m_iDebug > 0)
      {
         if(pinstance->m_pscript->m_memfileError.get_length() > 0)
         {
            pinstance->output_file() << pinstance->m_pscript->m_memfileError;
         }
      }
   }
   if(pinstance != NULL)
   {
      pinstance->run();
   }
   return pinstance;
}

void netnodeScriptManager::LoadEnv()
{
   /*char * buf;
   DWORD dwSize = GetDllDirectory(NULL, NULL);
   buf = new char[dwSize + 1024];
   GetDllDirectory(dwSize + 1024, buf);
   TRACE(buf);
   SetDllDirectory(buf);
   GetDllDirectory(dwSize + 1024, buf);
   TRACE(buf);
   delete buf;*/

   string str;
   str = System.get_module_folder();
   System.file().path().eat_end_level(str, 2, "\\");
   str =System.dir().path(str, "stage\\basis");
   str = ";" + str;
   string str2;
   str2 = System.get_module_folder();
   System.file().path().eat_end_level(str2, 2, "\\");
   str2 =System.dir().path(str2, "netnode\\library\\include");
   str2 = ";" + str2;
   str = str + str2;
   DWORD dwSize = GetEnvironmentVariable("PATH", NULL, 0);
   LPTSTR lpsz = new char[dwSize + 1024];
   dwSize = GetEnvironmentVariable("PATH", lpsz, dwSize + 1024);
   strcat(lpsz, str);
   SetEnvironmentVariable("PATH", lpsz);
   delete lpsz;
   dwSize = GetEnvironmentVariable("PATH", NULL, 0);
   lpsz = new char[dwSize + 1024];
   dwSize = GetEnvironmentVariable("PATH", lpsz, dwSize + 1024);
   TRACE(lpsz);
   delete lpsz;

   m_uiredir.load_xml( System.dir().votagus("netseed\\ca2\\fontopus\\net\\ds\\ca2\\include\\11ca2_fontopus_redir.xml"));
}

void netnodeScriptManager::run(const char * lpcszName)
{
   http::memory_file memfile(get_app());
   netnodeScriptInstance * pinstance = get(lpcszName);
   if(pinstance != NULL)
   {
      pinstance->m_pscript->run(pinstance);
   }
   pinstance->destroy();
}


string netnodeScriptManager::get_library_build_log()
{
   http::memory_file memfile(get_app());
   POSITION pos = m_pcompiler->m_mapLib.get_start_position();
   while(pos != NULL)
   {
      netnodeLibraryClass * plib;
      string strClass;
      m_pcompiler->m_mapLib.get_next_assoc(pos, strClass, (void * &) plib);
      memfile << plib->m_memfileError;
   }
   memfile << m_strPersistentError;
   string strBuildLog;
   memfile >> strBuildLog;
   return strBuildLog;
}

fontopus_database * netnodeScriptManager::new_musicdb(int iServer)
{
   return on_new_musicdb(iServer);
}

fontopus_database * netnodeScriptManager::on_new_musicdb(int iServer)
{
   CSingleLock sl(&m_csMusicDbPool, TRUE);
   __int64 iTime = update_musicdb_list(iServer);
   if(m_musicdba[iServer].get_count() > 0)
   {
      return m_musicdba[iServer].pop();
   }
   else
   {
      fontopus_database * pmusicdb = new fontopus_database(get_app());
      pmusicdb->m_iLastUsedTime = iTime;
      pmusicdb->initialize(iServer);
      return pmusicdb;
   }
}

void netnodeScriptManager::free_musicdb(fontopus_database * pmusicdb)
{
  on_free_musicdb(pmusicdb);
}

void netnodeScriptManager::on_free_musicdb(fontopus_database * pmusicdb)
{
   CSingleLock sl(&m_csMusicDbPool, TRUE);
   update_musicdb_list(pmusicdb->m_iLastServer);
   return m_musicdba[pmusicdb->m_iLastServer].push(pmusicdb);
}

__int64 netnodeScriptManager::update_musicdb_list(int iServer)
{
   CSingleLock sl(&m_csMusicDbPool, TRUE);
   __int64 iTime = ::ca::profiler::micros();
   for(int i = 0; i < m_musicdba[iServer].get_count();)
   {
      if(iTime - m_musicdba[iServer][i]->m_iLastUsedTime > m_iDatabaseWaitTimeOut)
      {
         try
         {
            m_musicdba[iServer][i]->m_pinterface = NULL;
         }
         catch(...)
         {
            TRACE("strange fontopus database, could not set its m_pinterface to NULL for deleting");
         }
         try
         {
            delete m_musicdba[iServer][i];
         }
         catch(...)
         {
            TRACE("strange fontopus database, exception when deleting it");
         }
         m_musicdba[iServer].remove_at(i);
      }
      else
      {
         i++;
      }
   }
   return iTime;
}

cynce_database * netnodeScriptManager::new_cyncedb()
{
   return on_new_cyncedb();
}

cynce_database * netnodeScriptManager::on_new_cyncedb()
{
   CSingleLock sl(&m_csCynceDbPool, TRUE);
   __int64 iTime = update_cyncedb_list();
   if(m_cyncedbptra.get_count() > 0)
   {
      return m_cyncedbptra.pop();
   }
   else
   {
      cynce_database * pcyncedb = new cynce_database(get_app());
      pcyncedb->m_iLastUsedTime = iTime;
      pcyncedb->initialize();
      return pcyncedb;
   }
}

void netnodeScriptManager::free_cyncedb(cynce_database * pcyncedb)
{
   on_free_cyncedb(pcyncedb);
}

void netnodeScriptManager::on_free_cyncedb(cynce_database * pcyncedb)
{
   CSingleLock sl(&m_csCynceDbPool, TRUE);
   update_cyncedb_list();
   return m_cyncedbptra.push(pcyncedb);
}

__int64 netnodeScriptManager::update_cyncedb_list()
{
   CSingleLock sl(&m_csCynceDbPool, TRUE);
   __int64 iTime = ::ca::profiler::micros();
   for(int i = 0; i < m_cyncedbptra.get_count();)
   {
      if(iTime - m_cyncedbptra[i]->m_iLastUsedTime > m_iDatabaseWaitTimeOut)
      {
         try
         {
            m_cyncedbptra[i]->m_pinterface = NULL;
         }
         catch(...)
         {
            TRACE("strange cynce database, could not set its m_pinterface to NULL for deleting");
         }
         try
         {
            delete m_cyncedbptra[i];
         }
         catch(...)
         {
            TRACE("strange cynce database, exception when deleting it");
         }
         m_cyncedbptra.remove_at(i);
      }
      else
      {
         i++;
      }
   }
   return iTime;
}

void netnodeScriptManager::message_window_message_handler(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   if(pbase->m_uiMessage == WM_APP + 13)
   {
      //if(wparam == 0)
        // ((netnodeScript *) lparam)->Load(false);
      //else if(wparam == 13)
        // ((netnodeScript *) lparam)->Unload(false);
      pbase->m_bRet = true;
   }
   else if(pbase->m_uiMessage == WM_APP + 14)
   {
/*      if(wparam == 1)
      {
         lresult = (LPARAM) on_new_musicdb();
         return true;
      }
      else */if(pbase->m_wparam == 2)
      {
         on_free_musicdb((fontopus_database *) pbase->m_lparam);
         pbase->m_bRet = true;
      }
      else if(pbase->m_wparam == 101)
      {
         pbase->set_lresult ((LPARAM) on_new_cyncedb());
         pbase->m_bRet = true;
      }
      else if(pbase->m_wparam == 102)
      {
         on_free_cyncedb((cynce_database *)pbase->m_lparam);
         pbase->m_bRet = true;
      }
   }
}




void netnodeScriptManager::clear_include_matches()
{
   CSingleLock sl(&m_mutexIncludeMatches, TRUE);
   m_mapIncludeMatchesFileExists.remove_all();
   m_mapIncludeMatchesIsDir.remove_all();
}

bool netnodeScriptManager::include_matches_file_exists(const char * pszPath)
{
   CSingleLock sl(&m_mutexIncludeMatches, TRUE);
   bool bFileExists;
   if(m_mapIncludeMatchesFileExists.Lookup(pszPath, bFileExists))
      return bFileExists;
   else
   {
      bFileExists = System.file().exists(pszPath);
      m_mapIncludeMatchesFileExists.set_at(pszPath, bFileExists);
      return bFileExists;
   }
}

bool netnodeScriptManager::include_matches_is_dir(const char * pszPath)
{
   CSingleLock sl(&m_mutexIncludeMatches, TRUE);
   bool bIsDir;
   if(m_mapIncludeMatchesIsDir.Lookup(pszPath, bIsDir))
      return bIsDir;
   else
   {
      bIsDir = System.dir().is(pszPath);
      m_mapIncludeMatchesIsDir.set_at(pszPath, bIsDir);
      return bIsDir;
   }
}

UINT AFX_CDECL netnodeScriptManager::clear_include_matches_FolderWatchThread(LPVOID lpParam) // thread procedure
{
   clear_include_matches_folder_watch * pwatch = (clear_include_matches_folder_watch *) lpParam;
   HANDLE hDirectory =
      ::CreateFile((const char *)pwatch->m_strPath,    // folder path 
                   FILE_LIST_DIRECTORY,
                   FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
                   NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
   
   if(INVALID_HANDLE_VALUE == hDirectory)
   {
      DWORD dwError = ::GetLastError();
      // handle error (see this FAQ)
      return dwError;
   }

   DWORD dwBytesReturned = 0;
   const DWORD dwBuffLength = 4096;
   BYTE buffer[dwBuffLength];
   
   while(::ReadDirectoryChangesW(hDirectory, buffer, dwBuffLength, TRUE,
                                 FILE_NOTIFY_CHANGE_FILE_NAME |
                                 FILE_NOTIFY_CHANGE_LAST_WRITE |
                                 FILE_NOTIFY_CHANGE_CREATION, &dwBytesReturned, 
                                 NULL, NULL))
   {
      DWORD dwNextEntryOffset = 0;
      PFILE_NOTIFY_INFORMATION pfni = NULL;
      do
      {
         pfni = (PFILE_NOTIFY_INFORMATION)(buffer + dwNextEntryOffset);
         
         pwatch->m_pmanager->clear_include_matches();
         /*switch(pfni->Action)
         {
         case FILE_ACTION_ADDED: 

            // The file was added to the directory. 
            break;
         case FILE_ACTION_REMOVED: 
            // The file was removed from the directory. 
            break;
         case FILE_ACTION_RENAMED_OLD_NAME: 
            // The file was renamed and this is the old name. 
            break;
         case FILE_ACTION_RENAMED_NEW_NAME: 
            // The file was renamed and this is the new name.
            break;
            // ...
         }*/
         // Enjoy of added, removed, or modified file name...
         dwNextEntryOffset += pfni->NextEntryOffset; // next please!
      }while(pfni->NextEntryOffset != 0);
   } 
   ::CloseHandle(hDirectory);
   delete pwatch;
   return 0;
}

string netnodeScriptManager::real_path(const char * pszBase, const char * psz)
{
   string strRealPath = System.dir().path(pszBase, psz);
   if(include_matches_file_exists(strRealPath))
      return strRealPath;
   else if(include_matches_is_dir(strRealPath))
      return strRealPath;
   else
       return "";
}

string netnodeScriptManager::real_path(const char * psz)
{
   if(System.file().exists(psz))
      return psz;
   return real_path(System.dir().netseed("ds/ca2"), psz);
}

bool netnodeScriptManager::get_session(const char * pszId, ::gen::property_set & set)
{
   CSingleLock sl(&m_mutexSession, TRUE);
   set = m_mapSession[pszId];
   return true;
}

bool netnodeScriptManager::set_session(const char * pszId, ::gen::property_set & set)
{
   CSingleLock sl(&m_mutexSession, TRUE);
   m_mapSession[pszId] = set;
   return true;
}
