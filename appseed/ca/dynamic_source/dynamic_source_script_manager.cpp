#include "StdAfx.h"
#include <openssl/ssl.h>

#ifdef LINUX
#include <sys/inotify.h>
#endif


namespace dynamic_source
{


   script_manager::script_manager(::ca::application * papp) :
      ca(papp),
      thread(papp),
      ::ca::message_window_simple_callback(papp)
   {

      m_pcache                   = new script_cache(papp);
      m_pcache->m_pmanager       = this;
      m_pcompiler                = new script_compiler(papp);
      m_pcompiler->m_pmanager    = this;
      m_dwBuildTimeWindow        = 84;
      m_dwBuildTimeRandomWindow  = 77 * 5;
      m_iDatabaseWaitTimeOut     = 1000 * 1000 * 60;


      m_mapIncludeMatchesFileExists.InitHashTable(256 * 1024);
      m_mapIncludeMatchesIsDir.InitHashTable(256 * 1024);
      m_mapIncludeHasScript.InitHashTable(256 * 1024);
      m_mapIncludeExpandMd5.InitHashTable(256 * 1024);
      m_mapSession.InitHashTable(256 * 1024);

      calc_rsa_key();

      Begin();

      m_strNamespace             = "netnodelite"; // default namespace is linked to outer project app_core_netnodelite
      m_strNetnodePath           = "C:\\netnodenet\\";
      m_strNetseedPath           = "C:\\netnodenet\\net\\netseed\\";
      m_strNetseedDsCa2Path      = "C:\\netnodenet\\net\\netseed\\ds\\ca2\\";

   }

   script_manager::~script_manager(void)
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



   bool script_manager::initialize_instance()
   {

      initialize_message_window("ca2::fontopus::ccvotagus::netnode::cgclcst");
      m_pcompiler->initialize();

      {
         clear_include_matches_folder_watch * pwatch = new clear_include_matches_folder_watch();
         pwatch->m_strPath = m_strNetseedDsCa2Path;
         pwatch->m_pmanager = this;
         AfxBeginThread(get_app(), clear_include_matches_FolderWatchThread, (LPVOID) pwatch);
      }

      stringa straPath;
      stringa straTitle;

      Application.dir().ls_dir(m_strNetnodePath, &straPath, &straTitle);

      for(int i = 0; i < straPath.get_count(); i++)
      {
         if(gen::str::begins_ci(straTitle[i], "net-"))
         {
            clear_include_matches_folder_watch * pwatch = new clear_include_matches_folder_watch();
            pwatch->m_strPath = straPath[i];
            pwatch->m_pmanager = this;
            AfxBeginThread(get_app(), clear_include_matches_FolderWatchThread, (LPVOID) pwatch);
         }
      }

      return true;
   }


   script_instance * script_manager::get(const char * lpcszName)
   {

      return m_pcache->create_instance(lpcszName);


   }


   void script_manager::handle(::dynamic_source::httpd_socket * pnetnodesocket)
   {
      string strHead;
      script_instance * pinstance = get(get_root_plugin());
      pnetnodesocket->m_pinstanceCurrent = pinstance;
      if(pinstance != NULL)
      {
         pinstance->m_strDebugRequestUri = pnetnodesocket->inattr("request_uri");
         pinstance->m_strDebugThisScript = get_root_plugin();
         pinstance->initialize(pinstance, NULL, pnetnodesocket, this);
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
            TRACE0("Error: ::ca::exception at script_manager::handle run");
            TRACE0(str);
         }
         catch(base_exception * pe)
         {
            string str;
            pe->GetErrorMessage(str);
            pinstance->dprint("str");

            TRACE0("Error: ::ca::exception * at script_manager::handle run");
            TRACE0(str);

            delete pe;
         }
         catch(...)
         {
            TRACE0("Error: Exception at script_manager::handle run");
         }
         try
         {
            pinstance->main_finalize();
         }
         catch(const ::ca::exception &)
         {
            TRACE0("Error: ::ca::exception at script_manager::handle main_finalize");
         }
         catch(...)
         {
            TRACE0("Error: Exception at script_manager::handle main_finalize");
         }
         try
         {
            pinstance->destroy();
         }
         catch(const ::ca::exception &)
         {
            TRACE0("Error: ::ca::exception at script_manager::handle destroy pinstance");
         }
         catch(...)
         {
            TRACE0("Error: Exception at script_manager::handle destroy pinstance");
         }
      }

   }

   script_instance * script_manager::get_output_internal(::dynamic_source::script_instance * pinstanceParent, const char * lpcszName)
   {
      string strName = gen::str::get_word(lpcszName, "?");
      if(strName.is_empty())
      {
         if(pinstanceParent != NULL)
         {
            if(pinstanceParent->main_instance()->m_iDebug > 0)
            {
               if(pinstanceParent->m_pscript->m_memfileError.get_length() > 0)
               {
                  pinstanceParent->main_instance()->netnodesocket()->response().file() << "script_manager::get_output_internal is_empty script parent" << pinstanceParent->m_pscript->m_strName;
               }
            }
         }
         return NULL;
      }
      script_instance * pinstance = get(strName);
      if(pinstance != NULL)
      {
         pinstance->initialize(pinstanceParent->main_instance(), pinstanceParent, pinstanceParent->main_instance()->netnodesocket(), this);
         pinstance->dinit();
         if(pinstance->main_instance()->m_iDebug > 0)
         {
            pinstance->m_strDebugRequestUri = pinstanceParent->main_instance()->netnodesocket()->m_request.m_strRequestUri;
            pinstance->m_strDebugThisScript = strName;
            ::dynamic_source::ds_script * pdsscript = dynamic_cast < ds_script * > (pinstance->m_pscript);
            if(pdsscript != NULL)
            {
               try
               {
                  if(pdsscript->m_memfileError.get_length() > 0)
                  {
                     pinstance->output_file() << pdsscript->m_memfileError;
                  }
               }
               catch(...)
               {
               }
            }

         }
      }
      if(pinstance != NULL)
      {
         pinstance->run();
      }
      return pinstance;
   }

   void script_manager::LoadEnv()
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
      str =System.dir().path(str, "stage\\basis", false);
      str = ";" + str;
      string str2;
      str2 = System.get_module_folder();
      System.file().path().eat_end_level(str2, 2, "\\");
      str2 =System.dir().path(str2, "netnode\\library\\include", false);
      str2 = ";" + str2;
      str = str + str2;

      string strNew;
#ifdef WINDOWS
      DWORD dwSize = GetEnvironmentVariable("PATH", NULL, 0);
      LPTSTR lpsz = new char[dwSize + 1024];
      dwSize = GetEnvironmentVariable("PATH", lpsz, dwSize + 1024);
      strNew = lpsz;
      delete lpsz;
#else
      strNew = getenv("PATH");
#endif
      strNew += str;
#ifdef WINDOWS
      SetEnvironmentVariable("PATH", strNew);
#else
      setenv("PATH", strNew, 1);
#endif


      // just verifying

#ifdef WINDOWS
      dwSize = GetEnvironmentVariable("PATH", NULL, 0);
      lpsz = new char[dwSize + 1024];
      dwSize = GetEnvironmentVariable("PATH", lpsz, dwSize + 1024);
      TRACE(lpsz);
      delete lpsz;
#else
      LPCTSTR lpcsz = getenv("PATH");
#endif

      on_load_env();

   }

   void script_manager::run(const char * lpcszName)
   {
      http::memory_file memfile(get_app());
      script_instance * pinstance = get(lpcszName);
      if(pinstance != NULL)
      {
         pinstance->m_pscript->run(pinstance);
      }
      pinstance->destroy();
   }


   string script_manager::get_library_build_log()
   {
      http::memory_file memfile(get_app());
      POSITION pos = m_pcompiler->m_mapLib.get_start_position();
      while(pos != NULL)
      {
         library_class * plib;
         string strClass;
         m_pcompiler->m_mapLib.get_next_assoc(pos, strClass, (void * &) plib);
         memfile << plib->m_memfileError;
      }
      memfile << m_strPersistentError;
      string strBuildLog;
      memfile.to_string(strBuildLog);
      return strBuildLog;
   }

   void script_manager::message_window_message_handler(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::base, pbase, pobj);
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
      }
   }




   void script_manager::clear_include_matches()
   {

      {
         single_lock sl(&m_mutexIncludeMatches, TRUE);
         m_mapIncludeMatchesFileExists.remove_all();
         m_mapIncludeMatchesIsDir.remove_all();
      }

      {
         single_lock sl(&m_mutexIncludeHasScript, TRUE);
         m_mapIncludeHasScript.remove_all();
      }

      {
         single_lock sl(&m_mutexIncludeExpandMd5, TRUE);
         m_mapIncludeExpandMd5.remove_all();
      }

   }

   bool script_manager::include_matches_file_exists(const string & strPath)
   {
      single_lock sl(&m_mutexIncludeMatches, TRUE);
      ::collection::string_map < bool >::pair * ppair = m_mapIncludeMatchesFileExists.PLookup(strPath);
      if(ppair != NULL)
         return ppair->m_value;
      else
      {
         bool bFileExists = Application.file().exists(strPath);
         m_mapIncludeMatchesFileExists.set_at(strPath, bFileExists);
         return bFileExists;
      }
   }

   void script_manager::set_include_matches_file_exists(const string & strPath, bool bFileExists)
   {
      single_lock sl(&m_mutexIncludeMatches, TRUE);
      m_mapIncludeMatchesFileExists.set_at(strPath, bFileExists);
   }

   bool script_manager::include_matches_is_dir(const string & strPath)
   {
      single_lock sl(&m_mutexIncludeMatches, TRUE);
      ::collection::string_map < bool >::pair * ppair = m_mapIncludeMatchesIsDir.PLookup(strPath);
      if(ppair != NULL)
         return ppair->m_value;
      else
      {
         bool bIsDir = Application.dir().is(strPath);
         m_mapIncludeMatchesIsDir.set_at(strPath, bIsDir);
         return bIsDir;
      }
   }

   bool script_manager::include_has_script(const string & strPath)
   {
      single_lock sl(&m_mutexIncludeHasScript, TRUE);
      ::collection::string_map < bool >::pair * ppair = m_mapIncludeHasScript.PLookup(strPath);
      if(ppair != NULL)
         return ppair->m_value;
      else
      {

         // roughly detect this way: by finding the <?

         bool bHasScript = Application.file().as_string(strPath).find("<?") >= 0;

         m_mapIncludeHasScript.set_at(strPath, bHasScript);

         return bHasScript;

      }
   }

   string script_manager::include_expand_md5(const string & strPath)
   {
      single_lock sl(&m_mutexIncludeExpandMd5, TRUE);
      return m_mapIncludeExpandMd5[strPath];
   }

   void script_manager::set_include_expand_md5(const string & strPath, const string & strMd5)
   {
      single_lock sl(&m_mutexIncludeExpandMd5, TRUE);
      m_mapIncludeExpandMd5[strPath] = strMd5;
   }

   UINT AFX_CDECL script_manager::clear_include_matches_FolderWatchThread(LPVOID lpParam) // thread procedure
   {

#ifdef WINDOWS
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
#else

      clear_include_matches_folder_watch * pwatch = (clear_include_matches_folder_watch *) lpParam;

      int iNotify = inotify_init();

      string strDir = pwatch->m_strPath;
      int_array ia;

      stringa stra;

      stringa straDir;

      App(pwatch->m_pmanager->get_app()).dir().rls(strDir, &straDir);

      inotify_add_watch(iNotify, strDir, IN_CLOSE_WRITE | IN_DELETE | IN_DELETE_SELF | IN_MODIFY | IN_MOVED_TO | IN_CREATE);

      for(int i = 0; i < straDir.get_count(); i++)
         if(stra.add_unique(straDir[i]))
         {
            ia.add(inotify_add_watch(iNotify, straDir[i], IN_CLOSE_WRITE | IN_DELETE | IN_DELETE_SELF | IN_MODIFY | IN_MOVED_TO | IN_CREATE));
            stra.add(straDir[i]);
         }

      straDir.remove_all();
      App(pwatch->m_pmanager->get_app()).dir().rls(strDir, &straDir);
      for(int i = 0; i < straDir.get_count(); i++)
         if(stra.add_unique(straDir[i]))
         {
            ia.add(inotify_add_watch(iNotify, straDir[i], IN_CLOSE_WRITE | IN_DELETE | IN_DELETE_SELF | IN_MODIFY | IN_MOVED_TO | IN_CREATE));
            stra.add(straDir[i]);
         }


      int iLen = 1024;

      inotify_event * pevent = (inotify_event *) malloc(iLen);

      int iRead;
      int iCount;
      while(iRead = read(iNotify, pevent, iLen))
      {
         if(iRead == -1)
         {
            iLen += 1024;
            free(pevent);
            pevent = (inotify_event *) malloc(iLen);
            continue;
         }
         while(iRead > sizeof(inotify_event))
         {

            if(pevent->mask & IN_ISDIR)
            {
               if(pevent->mask & IN_CREATE)
               {
                  straDir.remove_all();
                  App(pwatch->m_pmanager->get_app()).dir().rls(strDir, &straDir);
                  for(int i = 0; i < straDir.get_count(); i++)
                     if(stra.add_unique(straDir[i]))
                     {
                        ia.add(inotify_add_watch(iNotify, straDir[i], IN_CLOSE_WRITE | IN_DELETE | IN_DELETE_SELF | IN_MODIFY | IN_MOVED_TO | IN_CREATE));
                        stra.add(straDir[i]);
                     }

               }
               else if(pevent->mask & IN_DELETE || pevent->mask & IN_DELETE_SELF)
               {
                  straDir.remove_all();
                  App(pwatch->m_pmanager->get_app()).dir().rls(strDir, &straDir);
                  for(int i = 0; i < stra.get_count(); i++)
                     if(!straDir.contains(stra[i]))
                     {
                        inotify_rm_watch(iNotify, ia[i]);
                        stra.remove_at(i);
                        ia.remove_at(i);
                     }
               }
            }
            else
            {
               pwatch->m_pmanager->clear_include_matches();
            }
            iRead -= sizeof(inotify_event) + pevent->len;
         }
      }

      close(iNotify);
      delete pwatch;
      return 0;

#endif


   }

   string script_manager::real_path(const char * pszBase, const char * psz)
   {
      string strRealPath = System.dir().path(pszBase, psz, false);
      if(include_matches_file_exists(strRealPath))
         return strRealPath;
      else if(include_matches_is_dir(strRealPath))
         return strRealPath;
      else
         return "";
   }

#ifdef WINDOWS
#define is_absolute_path(psz) ((isalpha(psz[0]) && psz[1] == ':') \
   || (psz[0] == '\\' && psz[1] == '\\'))
#else
#define is_absolute_path(psz) (psz[0] == '/')
#endif

   string script_manager::real_path(const char * psz)
   {
#ifdef WINDOWS
      if(is_absolute_path(psz))
      {
         if(include_matches_file_exists(psz))
            return psz;
         return "";
      }
      else
      {
         return real_path(m_strNetseedDsCa2Path, psz);
      }
#else
      if(is_absolute_path(psz))
      {
         if(include_matches_file_exists(psz))
            return psz;
         return real_path(m_strNetseedDsCa2Path, psz);
      }
      else
      {
         return real_path(m_strNetseedDsCa2Path, psz);
      }
#endif
   }


   script_manager::session * script_manager::get_session(mutex * & pmutex, const char * pszId)
   {
      single_lock sl(&m_mutexSession, TRUE);
      script_manager::session & session = m_mapSession[pszId];
      pmutex = & session.m_mutex;
      return &session;
   }


   UINT ThreadProcRsa(LPVOID lp)
   {
      script_manager * pmanager = (script_manager *) lp;
      pmanager->calc_rsa_key();
      return 0;
   }

   RSA * script_manager::get_rsa_key()
   {
      if(::GetTickCount() - m_dwLastRsa > (1984 + 1977))
      {
         AfxBeginThread(get_app(), ThreadProcRsa, this);
         m_dwLastRsa = ::GetTickCount();
      }
      single_lock sl(&m_mutexRsa, TRUE);
      return m_rsaptra.last_element();
   }


   void script_manager::calc_rsa_key()
   {
      RSA * prsa = RSA_generate_key(1024, 65537, NULL, NULL);
      single_lock sl(&m_mutexRsa, TRUE);
      m_rsaptra.add(prsa);
      if(m_rsaptra.get_size() > 23)
      {
         RSA_free(m_rsaptra[0]);
         m_rsaptra.remove_at(0);
      }
   }

   void script_manager::on_load_env()
   {
   }

   void script_manager::register_plugin(const char * pszHost, const char * pszScript, const char * pszName, script * pscript)
   {

      plugin_map_item item;
      
      item.m_strHost       = pszHost;
      item.m_strScript     = pszScript;
      item.m_strPlugin     = pszName;

      m_pcache->register_script(pszName, pscript);


   }

   string script_manager::get_root_plugin()
   {
      return "netnode://script_seed_carlos_gustavo_cecyn_lundgren_carlos";
   }

} // namespace dynamic_source


