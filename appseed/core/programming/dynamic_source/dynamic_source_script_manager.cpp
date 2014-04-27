#include "framework.h"


#ifdef BSD_STYLE_SOCKETS

//#include <openssl/ssl.h>

#endif


namespace dynamic_source
{

   UINT ThreadProcRsa(LPVOID lp);

   thread_pointer < script_instance > t_pinstanceSeed;

   script_instance * get_seed_instance()
   {
      return t_pinstanceSeed;
   }

   script_manager::plugin_map_item::plugin_map_item()
   {
   }

   script_manager::plugin_map_item::plugin_map_item(const plugin_map_item & item)
   {

      operator = (item);

   }


   script_manager::plugin_map_item & script_manager::plugin_map_item::operator = (const plugin_map_item & item)
   {

      m_strHost         = item.m_strHost;
      m_strScript       = item.m_strScript;
      m_strPlugin       = item.m_strPlugin;

      return *this;

   }


   script_manager::script_manager(sp(base_application) papp) :
      element(papp),
      thread(papp),
      message_queue(papp),
      m_mutexIncludeMatches(papp),
      m_mutexIncludeHasScript(papp),
      m_mutexIncludeExpandMd5(papp),
      m_mutexOutLink(papp),
      m_mutexInLink(papp),
      m_mutexTunnel(papp),
      m_mutexSimage(papp),
      m_mutexSpider(papp),
      m_mutexRsa(papp),
      m_mutexSession(papp),
      m_mutexMusicDbPool(papp),
      m_mutexWayDbPool(papp),
      m_mutexPersistentStr(papp),
      m_mutexUiRedir(papp),
      m_mutexTagId(papp),
      m_mutexTagName(papp),
      m_mutexImageSize(papp)
   {

      m_pcache                   = new script_cache(papp);
      m_pcache->m_pmanager       = this;
      m_pcompiler                = new script_compiler(papp);
      m_pcompiler->m_pmanager    = this;
      m_dwBuildTimeWindow        = 84;
      m_dwBuildTimeRandomWindow  = 77 * 5;
      m_iDatabaseWaitTimeOut     = 15 * 1000 * 1000 * 60;


      m_mapIncludeMatchesFileExists.InitHashTable(256 * 1024);
      m_mapIncludeMatchesIsDir.InitHashTable(256 * 1024);
      m_mapIncludeHasScript.InitHashTable(256 * 1024);
      m_mapIncludeExpandMd5.InitHashTable(256 * 1024);
      m_mapSession.InitHashTable(256 * 1024);

      calc_rsa_key();

      m_strNamespace             = "netnode"; // default namespace is linked to outer project netnode
      #ifdef LINUX
      m_strNetnodePath           = "/netnodenet/";
      m_strNetseedPath           = "/netnodenet/net/netseed/";
      m_strNetseedDsCa2Path      = "/netnodenet/net/netseed/";
      #else
      m_strNetnodePath           = "C:\\netnodenet\\";
      m_strNetseedPath           = "C:\\netnodenet\\net\\netseed\\";
      m_strNetseedDsCa2Path      = "C:\\netnodenet\\net\\netseed\\";
      #endif


      m_iTunnelPluginCount       = 0;


      m_strSeed = "system/seed";

   }

   script_manager::~script_manager()
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

      create_message_queue("::core::netnode::cgclcst");
      m_pcompiler->initialize();
#ifdef WINDOWS
      {
         clear_include_matches_folder_watch * pwatch = new clear_include_matches_folder_watch();
         pwatch->m_pmanager = this;
         pwatch->add_file_watch( m_strNetseedDsCa2Path, true);
         pwatch->begin();
      }

      stringa straPath;
      stringa straTitle;

      Application.dir().ls_dir(m_strNetnodePath, &straPath, &straTitle);

      for(int32_t i = 0; i < straPath.get_count(); i++)
      {
         if(::str::begins_ci(straTitle[i], "net-"))
         {
            clear_include_matches_folder_watch * pwatch = new clear_include_matches_folder_watch();
            pwatch->m_pmanager = this;
            pwatch->add_file_watch(straPath[i], true);
            pwatch->begin();
         }
      }
#endif
      return true;
   }


   script_instance * script_manager::get(const string & strName)
   {

      return m_pcache->create_instance(strName);


   }


   void script_manager::handle(::dynamic_source::httpd_socket * pdssocket)
   {
      string strHead;
      sp(script_instance) pinstance = get(m_strSeed);
      t_pinstanceSeed = pinstance;
      if(pinstance != NULL)
      {
         pinstance->m_strDebugRequestUri = pdssocket->inattr("request_uri");
         pinstance->m_strDebugThisScript = m_strSeed;
         pinstance->initialize(pinstance, NULL, pdssocket, this);
         pinstance->dinit();
         if(pinstance->m_iDebug > 0)
         {
            if(pinstance->get("debug_lib").is_set())
            {
               m_pcompiler->m_memfileLibError.seek_to_begin();
               pdssocket->response().file().transfer_from(m_pcompiler->m_memfileLibError);
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
         catch(::exception::base & e)
         {
            string str;
            e.get_error_message(str);
            pinstance->dprint("str");
            TRACE0("Error: exception at script_manager::handle run");
            TRACE0(str);
         }
         catch(::exception::base * pe)
         {
            string str;
            pe->get_error_message(str);
            pinstance->dprint("str");

            TRACE0("Error: exception * at script_manager::handle run");
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
         catch(const ::exception::exception &)
         {
            TRACE0("Error: exception at script_manager::handle main_finalize");
         }
         catch(...)
         {
            TRACE0("Error: Exception at script_manager::handle main_finalize");
         }
         try
         {
            pinstance->destroy();
         }
         catch(const ::exception::exception &)
         {
            TRACE0("Error: exception at script_manager::handle destroy pinstance");
         }
         catch(...)
         {
            TRACE0("Error: Exception at script_manager::handle destroy pinstance");
         }
         try
         {
            pinstance.release();
         }
         catch(const ::exception::exception &)
         {
            TRACE0("Error: exception at script_manager::handle destroy pinstance");
         }
         catch(...)
         {
            TRACE0("Error: Exception at script_manager::handle destroy pinstance");
         }
      }

   }

   bool script_manager::get_output_internal(::dynamic_source::script_interface * & pinstance, ::dynamic_source::script_interface * pinstanceParent, const string & strNameParam)
   {
      string strName = ::str::get_word(strNameParam, "?");
      if(strName.is_empty())
      {
         if(pinstanceParent != NULL)
         {
            if(pinstanceParent->main_instance()->m_iDebug > 0)
            {
               if(pinstanceParent->m_pscript->m_memfileError.get_length() > 0)
               {
                  pinstanceParent->main_instance()->netnodesocket()->response().ostream() << "script_manager::get_output_internal is_empty script parent" << pinstanceParent->m_pscript->m_strName;
               }
            }
         }
         return false;
      }
      pinstance = get(strName);

      if(pinstance == NULL)
         return false;

      pinstance->initialize(pinstanceParent->main_instance(), pinstanceParent, pinstanceParent->main_instance()->netnodesocket(), this);

      pinstance->dinit();

      if(pinstance->main_instance()->m_iDebug > 0)
      {

         pinstance->m_strDebugRequestUri = pinstanceParent->main_instance()->netnodesocket()->m_request.m_strRequestUri;

         pinstance->m_strDebugThisScript = strName;

         ::dynamic_source::ds_script * pdsscript = dynamic_cast < ds_script * > (pinstance->m_pscript.m_p);

         if(pdsscript != NULL)
         {

            try
            {

               if(pdsscript->m_memfileError.get_length() > 0)
               {
                  pdsscript->m_memfileError.seek_to_begin();
                  pdsscript->m_memfileError.seek_to_begin();

                  pinstance->ostream().transfer_from(pdsscript->m_memfileError);

               }

            }
            catch(...)
            {

            }

         }

      }

      pinstance->run();

      return true;

   }

   void script_manager::LoadEnv()
   {
      /*char * buf;
      uint32_t dwSize = GetDllDirectory(NULL, NULL);
      buf = new char[dwSize + 1024];
      GetDllDirectory(dwSize + 1024, buf);
      TRACE(buf);
      //SetDllDirectory(buf);
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
#ifdef WINDOWSEX
      uint32_t dwSize = GetEnvironmentVariable("PATH", NULL, 0);
      LPTSTR lpsz = new char[dwSize + 1024];
      dwSize = GetEnvironmentVariable("PATH", lpsz, dwSize + 1024);
      strNew = lpsz;
      delete lpsz;
#elif defined(METROWIN)

      throw todo(get_app());

#else
      strNew = getenv("PATH");
#endif
      strNew += str;
#ifdef WINDOWSEX
      SetEnvironmentVariable("PATH", strNew);
#elif defined(METROWIN)

      throw todo(get_app());

#else
      setenv("PATH", strNew, 1);
#endif


      // just verifying

#ifdef WINDOWSEX
      dwSize = GetEnvironmentVariable("PATH", NULL, 0);
      lpsz = new char[dwSize + 1024];
      dwSize = GetEnvironmentVariable("PATH", lpsz, dwSize + 1024);
      TRACE(lpsz);
      delete lpsz;
#elif defined(METROWIN)

      throw todo(get_app());

#else
      //      LPCTSTR lpcsz = getenv("PATH");
#endif

      on_load_env();

   }

   void script_manager::run(const char * lpcszName)
   {
      file::memory_buffer memfile(get_app());
      script_instance * pinstance = get(lpcszName);
      if(pinstance != NULL)
      {
         pinstance->m_pscript->run(pinstance);
      }
      pinstance->destroy();
   }


   string script_manager::get_library_build_log()
   {
      file::plain_text_stream_memory_buffer memfile(get_app());
      POSITION pos = m_pcompiler->m_mapLib.get_start_position();
      while(pos != NULL)
      {
         library_class * plib;
         string strClass;
         m_pcompiler->m_mapLib.get_next_assoc(pos, strClass, (void * &) plib);
         memfile.transfer_from(plib->m_memfileError);
      }

      memfile << m_strPersistentError;
      
      return memfile.to_string();

   }

   void script_manager::message_queue_message_handler(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
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
      string_map < bool >::pair * ppair = m_mapIncludeMatchesFileExists.PLookup(strPath);
      if(ppair != NULL)
         return ppair->m_element2;
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
      string_map < bool >::pair * ppair = m_mapIncludeMatchesIsDir.PLookup(strPath);
      if(ppair != NULL)
         return ppair->m_element2;
      else
      {
         bool bIsDir = Application.dir().is(strPath);
         m_mapIncludeMatchesIsDir.set_at(strPath, bIsDir);
         return bIsDir;
      }
   }

   bool script_manager::include_has_script(const string & strPath)
   {

      if(strPath.is_empty())
         return false;

      single_lock sl(&m_mutexIncludeHasScript, TRUE);
      string_map < bool >::pair * ppair = m_mapIncludeHasScript.PLookup(strPath);
      if(ppair != NULL)
         return ppair->m_element2;
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


   void script_manager::clear_include_matches_folder_watch::handle_file_action(::file_watcher::id watchid, const char * dir, const char * filename, ::file_watcher::e_action eaction)
   {

      UNREFERENCED_PARAMETER(watchid);
      UNREFERENCED_PARAMETER(dir);
      UNREFERENCED_PARAMETER(filename);
      UNREFERENCED_PARAMETER(eaction);

      m_pmanager->clear_include_matches();
      try
      {
         m_pmanager->m_pcompiler->run_persistent();
      }
      catch(...)
      {
      }

   }



   string script_manager::real_path(const string & strBase, const string & str)
   {
      string strRealPath = System.dir().path(strBase, str, false);
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
 
   string script_manager::real_path(const string & str)
   {
#ifdef WINDOWS
      if(is_absolute_path(str))
      {
         if(include_matches_file_exists(str))
            return str;
         return "";
      }
      else
      {
         return real_path(m_strNetseedDsCa2Path, str);
      }
#else
      if(is_absolute_path(str))
      {
         if(include_matches_file_exists(str))
            return str;
         return real_path(m_strNetseedDsCa2Path, str);
      }
      else
      {
         return real_path(m_strNetseedDsCa2Path, str);
      }
#endif
   }

   sp(::dynamic_source::session) script_manager::get_session(const char * pszId)
   {
      
      single_lock sl(&m_mutexSession, TRUE);

      strsp(::dynamic_source::session)::pair * ppair = m_mapSession.PLookup(pszId);

      if (ppair != NULL)
      {

         if (::datetime::time::get_current_time() < ppair->m_element2->m_timeExpiry)
         {

            ppair->m_element2->m_timeExpiry = ::datetime::time::get_current_time() + minutes(9);

            return ppair->m_element2;

         }
            
         ppair->m_element2.m_p->~session();

#undef new
         ::new(ppair->m_element2.m_p) ::dynamic_source::session(pszId, this);
#define new BASE_NEW


         return ppair->m_element2;

      }
         
      sp(::dynamic_source::session) psession = canew(::dynamic_source::session(pszId, this));

      psession->m_timeExpiry = ::datetime::time::get_current_time() + minutes(9);

      m_mapSession.set_at(pszId, psession);

      return psession;

   }


   void script_manager::defer_clean_session()
   {
      single_lock sl(&m_mutexSession, TRUE);
      ::datetime::time time;
      time = ::datetime::time::get_current_time();
      strsp(session)::assoc * passoc = m_mapSession.PGetFirstAssoc();
      strsp(session)::assoc * passocNext;
      while(passoc != NULL)
      {
         passocNext = passoc->m_pnext;
         if(passoc->m_element2.is_null())
         {

            m_mapSession.remove_assoc(passoc);

         }
         else if(passoc->m_element2->get_ref_count() <= 1)
         {
            if(passoc->m_element2->m_timeExpiry < time)
            {
               m_mapSession.remove_assoc(passoc);
            }
         }
         passoc = passocNext;
      }

   }


   UINT ThreadProcRsa(LPVOID lp)
   {
      script_manager * pmanager = (script_manager *) lp;
      pmanager->calc_rsa_key();
      return 0;
   }

   sp(::crypto::rsa) script_manager::get_rsa_key()
   {

      /*if(::get_tick_count() - m_dwLastRsa > (1984 + 1977))
      {

         calc_rsa_key();

         m_dwLastRsa = ::get_tick_count();

      }*/

      single_lock sl(&m_mutexRsa, TRUE);

      return  System.crypto().generate_rsa_key();

   }


   string script_manager::get_rsa_key(script_interface * pscriptinterface)
   {

      pscriptinterface->session_id(); // trigger session creation;

      sp(::crypto::rsa) prsa = get_rsa_key();

      pscriptinterface->set_session_value("rsa", prsa);

      return prsa->n;

   }




   void script_manager::calc_rsa_key()
   {

      sp(::crypto::rsa) prsa = System.crypto().generate_rsa_key();

      single_lock sl(&m_mutexRsa, TRUE);

      m_rsaptra.add(prsa);

      if(m_rsaptra.get_size() > 23)
      {
         
         m_rsaptra.remove_at(0);

      }

   }

   void script_manager::on_load_env()
   {
   }

   void script_manager::register_plugin(const string & strHost, const string & strScript, const string & strName, script * pscript)
   {

      plugin_map_item item;

      item.m_strHost       = strHost;
      item.m_strScript     = strScript;
      item.m_strPlugin     = strName;

      m_pluginmapitema.add(new plugin_map_item(item));

      m_pcache->register_script(strName, pscript);


   }

   string script_manager::get_root_plugin()
   {
      return "netnode://script_seed";
   }


   void script_manager::wait_link_out(const char * pszServer, ::sockets::link_in_socket * pinsocket)
   {

      while(true)
      {

         if(has_link_out_link(pszServer, pinsocket, NULL))
            break;

         Sleep(84);

      }

   }

   bool script_manager::has_link_out_link(const char * pszServer, ::sockets::link_in_socket * pinsocket, ::sockets::httpd_socket * phttpdsocket)
   {

      strsp(::sockets::link_out_socket)::pair * ppair;

      single_lock sl(&m_mutexOutLink, TRUE);

      ppair = m_mapOutLink.PLookup(pszServer);

      ::sockets::link_out_socket * psocket = NULL;

      if(ppair != NULL)
      {

         psocket = ppair->m_element2;

         if(psocket != NULL)
         {

            single_lock sl2(&m_mutexInLink, TRUE);

            if(phttpdsocket != NULL)
            {

               pinsocket->m_in = phttpdsocket;

               pinsocket->m_memfileInput.transfer_from(phttpdsocket->m_memfileInput);

               pinsocket->server_to_link_in(phttpdsocket);

               phttpdsocket->m_bEnd = true;

            }

            m_mapInLink.set_at(psocket, pinsocket);

         }

         m_mapOutLink.remove_key(pszServer);

      }

      if(psocket == NULL)
         return false;

      return true;

   }

   ::sockets::link_in_socket * script_manager::get_link_in(const char * pszServer, ::sockets::link_out_socket * poutsocket)
   {

      single_lock sl2(&m_mutexInLink, TRUE);

      map < ::sockets::link_out_socket *, ::sockets::link_out_socket *, ::sockets::link_in_socket *, ::sockets::link_in_socket * >::pair * ppair =
         m_mapInLink.PLookup(poutsocket);

      {

         single_lock sl3(&m_mutexTunnel, TRUE);

         tunnel_map_item item;

         item.m_strServer    = pszServer;
         item.m_dwLast       = get_tick_count();

         m_mapTunnel.set_at(pszServer, item);

      }

      if(ppair == NULL)
         return NULL;

      ::sockets::link_in_socket * pinsocket = ppair->m_element2;

      m_mapInLink.remove_key(poutsocket);

      return pinsocket;

   }


   bool script_manager::is_online(const char * pszServer)
   {

      single_lock sl(&m_mutexTunnel, TRUE);

      string_map < tunnel_map_item >::pair * ppair = m_mapTunnel.PLookup(pszServer);

      if(ppair == NULL)
         return false;

      if(::get_tick_count() - ppair->m_element2.m_dwLast > (60 * 1000))
         return false;

      return true;

   }


   ::sockets::link_out_socket * script_manager::create_link_out(const char * pszServer, ::sockets::httpd_socket * phttpdsocket)
   {

      ::sockets::link_out_socket * psocket = new sockets::link_out_socket(phttpdsocket->Handler());

      {

         single_lock sl(&m_mutexTunnel, TRUE);

         tunnel_map_item item;

         item.m_strServer    = pszServer;
         item.m_dwLast       = get_tick_count();

         m_mapTunnel.set_at(pszServer, item);

      }

      {

         single_lock sl(&m_mutexOutLink, TRUE);
         m_mapOutLink.set_at(pszServer, psocket);

      }

      return psocket;

   }

   size script_manager::get_image_size(const string & strFile)
   {

      single_lock sl(&m_mutexImageSize, false);

      sl.lock();

      ::size size;

      if(m_mapImageSize.Lookup(strFile, size))
         return size;

      sl.unlock();

      size.cx = 49;

      size.cy = 49;

      if(extract_image_size(strFile, &size))
      {

         sl.lock();

         m_mapImageSize.set_at(strFile, size);

         sl.unlock();

      }

      return size;

   }

   bool script_manager::extract_image_size(const string & strFile, ::size * psize)
   {

      ::file::binary_buffer_sp f;

      try
      {
         f = Application.file().get_file(strFile, ::file::type_binary | ::file::mode_read | ::file::share_deny_write);
      }
      catch(...)
      {
         return false;
      }

      // http://www.cplusplus.com/forum/beginner/45217/

      ::file_size len = f->seek_to_end();

      if(len < 24)
      {
         return false;
      }

      f->seek_to_begin();

      // Strategy:
      // reading GIF dimensions requires the first 10 bytes of the file
      // reading PNG dimensions requires the first 24 bytes of the file
      // reading JPEG dimensions requires scanning through jpeg chunks
      // In all formats, the file is at least 24 bytes big, so we'll read that always
      unsigned char buf[24];

      if(f->read(buf, 24) < 24)
      {
         return false;
      }

      // http://www.64lines.com/jpeg-width-height
      if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF && buf[3]==0xE0 && buf[6]=='J' && buf[7]=='F' && buf[8]=='I' && buf[9]=='F' && buf[10]=='\0')
      {
         unsigned short block_length = buf[4] * 256 + buf[5];
         int i = 4;
         while(i < len)
         {

            i += block_length;               //Increase the file index to get to the next block

            if(i >= len)
               return false;   //Check to protect against segmentation faults

            f->seek(i, ::file::seek_begin);

            if(f->read(buf, 4) < 4)
               return false;

            if(buf[i] != 0xFF)
               return false;   //Check that we are truly at the start of another block

            if(buf[i+1] == 0xC0)
            {
               //0xFFC0 is the "Start of frame" marker which contains the file size
               //The structure of the 0xFFC0 block is quite simple [0xFFC0][ushort length][uchar precision][ushort x][ushort y]

               if(f->read(buf, 5) < 5)
                  return false;

               psize->cy = buf[i+1]*256 + buf[i+2];
               psize->cx = buf[i+3]*256 + buf[i+4];
               return true;
            }
            else
            {
               block_length = buf[2] * 256 + buf[3];   //Go to the next block
            }
         }
         return false;
      }

      // JPEG: (first two bytes of buf are first two bytes of the jpeg file; rest of buf is the DCT frame
      if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF)
      {

         psize->cy = (buf[7]<<8) + buf[8];

         psize->cx = (buf[9]<<8) + buf[10];

         return true;

      }

      // GIF: first three bytes say "GIF", next three give version number. Then dimensions
      if (buf[0]=='G' && buf[1]=='I' && buf[2]=='F')
      {

         psize->cx = buf[6] + (buf[7]<<8);

         psize->cy = buf[8] + (buf[9]<<8);

         return true;

      }

      // PNG: the first frame is by definition an IHDR frame, which gives dimensions
      if(buf[0]==0x89 && buf[1]=='P' && buf[2]=='N' && buf[3]=='G' && buf[4]==0x0D && buf[5]==0x0A && buf[6]==0x1A && buf[7]==0x0A
         && buf[12]=='I' && buf[13]=='H' && buf[14]=='D' && buf[15]=='R')
      {

         psize->cx = (buf[16]<<24) + (buf[17]<<16) + (buf[18]<<8) + (buf[19]<<0);

         psize->cy = (buf[20]<<24) + (buf[21]<<16) + (buf[22]<<8) + (buf[23]<<0);

         return true;

      }

      return false;

   }




} // namespace dynamic_source





