#include "StdAfx.h"


namespace icube
{

   CLASS_DECL_ca class system::heap_item_array * g_pheapitema = NULL;


   CLASS_DECL_ca class system::heap_item_array * get_heap_itema()
   {
      return g_pheapitema;
   }

   CLASS_DECL_ca void set_heap_itema(class system::heap_item_array * pitema)
   {
      g_pheapitema = pitema;
   }


   system::system()
   {
      set_app(this);
      m_net.set_app(this);
      m_file.set_app(this);
      m_stra.set_app(this);
      m_url.set_app(this);
      m_html.set_app(this);
      m_xml.set_app(this);
      m_userset.set_app(this);
      m_service.set_app(this);
      m_install.set_app(this);
      m_process.set_app(this);
      m_pdatetime = new class ::ca2::datetime(this);
      m_email.set_app(this);
      m_http.set_app(this);
      m_crypt.set_app(this);
      m_compress.set_app(this);
      m_file.set_app(this);
      m_file4.set_app(this);
      m_file4.path36().set_app(this);

      m_prunstartinstaller       = NULL;
      m_pmachineeventcentral     = NULL;
      m_pfactory                 = NULL;
      m_plog                     = NULL;
      m_ptwf                     = NULL;
      m_pbergedgemap             = NULL;
      m_pcopydesk                = NULL;
      m_plicense                 = NULL;
      m_psystem                  = this;
      m_pfsdata                  = new ::fs::native(this);

      m_bInitApplication         = false;
      m_bInitApplicationResult   = FALSE;
      m_bProcessInitialize       = false;
      m_bProcessInitializeResult = false;

   }

   system::~system()
   {

      try
      {
         if(m_pfactory != NULL)
         {
            gen::del(m_pfactory);
         }
      }
      catch(...)
      {
      }

   }

   BOOL system::InitApplication()
   {

      if(m_bInitApplication)
         return m_bInitApplicationResult;

      m_bInitApplicationResult      = FALSE;
      m_bInitApplication            = true;

      m_bInitApplicationResult = icube::application::InitApplication();

      return m_bInitApplicationResult;
   }


   bool system::process_initialize()
   {
      
      if(m_bProcessInitialize)
         return m_bProcessInitializeResult;

      m_bProcessInitializeResult    = false;
      m_bProcessInitialize          = true;


      if(!gen::system::initialize())
         return false;


      if(m_pfactory == NULL)
      {
         m_pfactory = new class factory;
         m_pfactory->set_app(this);
      }
      ::ca::profiler::initialize();


      System.factory().creatable < ::ca2::log >(typeid(::ca::log), 1);

      if(!system::application::process_initialize())
      {
         return false;
      }

      m_bProcessInitializeResult = true;
      return true;
   }


   bool system::initialize()
   {

      m_pmachineeventcentral = new class machine_event_central(this);
      if(!m_pmachineeventcentral->initialize())
         return false;
      if(m_pmachineeventcentral->is_close_application())
         return false;

      if(!system::application::initialize())
         return false;

      return true;
   }



   bool system::initialize1()
   {
      m_spfilesystem.create(this);
      m_sposi.create(this);
      m_spdir.create(this);

      string strId;
      strId = m_strAppName;
      strId += gen::str::has_char(m_strLicense, ".");
      strId += gen::str::has_char(m_strBaseSupportId, ".");


      // log starts here
      if(!initialize_log(strId))
         return FALSE;

      if(!m_spdir->initialize())
         return false;


      m_puser                 = new ::fontopus::user(this);
      m_puser->m_strLogin     = "system";
      create_user(m_puser);

      System.factory().cloneable_large < ::ca::font_sp >();
      System.factory().cloneable_large < ::ca::brush_sp >();
      System.factory().cloneable_large < ::ca::pen_sp >();
      System.factory().cloneable_large < ::ca::bitmap_sp >();
      System.factory().cloneable_large < ::ca::palette_sp >();
      System.factory().cloneable_large < ::ca::rgn_sp >();
      System.factory().cloneable_large < var >();
      System.factory().creatable < ::ca2::log >(typeid(::ca::log), 1);


      if(!system::application::initialize1())
         return false;

      return true;

   }


   bool system::initialize3()
   {
      
      if(!system::application::initialize3())
         return false;

      if(m_phistory == NULL)
      {
         m_phistory = new os_history(this);
      }

      return true;
   }

   bool system::initialize_instance() 
   {

      set_enum_name(var::type_null      , "null");
      set_enum_name(var::type_empty     , "is_empty");
      set_enum_name(var::type_string    , "string");
      set_enum_name(var::type_integer   , "integer");
      set_enum_name(var::type_ulong     , "ulong");
      set_enum_name(var::type_ca2       , "ca2");
      set_enum_name(var::type_bool      , "bool");
      set_enum_name(var::type_double    , "double");

      if(!system::application::initialize_instance())
        return false;

      m_pbergedgemap = new ::bergedge::bergedge::map;

      return true;
   }


   bool system::bergedge_start()
   {
      return true;
   }

   bool system::os_native_bergedge_start()
   {

      string strId;

      strId = m_pcommandline->m_varQuery.propset()["app"];

      if(strId.is_empty())
         strId = "bergedge";

      ::ca::application_bias bias;
      bias.m_strLicense = strId;

      request_application(0, strId, m_pcommandline->m_varFile, m_pcommandline->m_varQuery, &bias);

      return true;
   }


   int system::exit_instance()
   {
      int iRet = 0;
      try
      {
         iRet = ::fontopus::application::exit_instance();
      }
      catch(...)
      {
      }
      try
      {
         if(m_ptwf != NULL)
         {
            m_ptwf->stop();
            gen::del(m_ptwf);
            m_ptwf = NULL;
         }
      }
      catch(...)
      {
      }
      try
      {
         if(m_sposi.m_p != NULL)
         {
            gen::del(m_sposi.m_p);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(m_spdir.m_p != NULL)
         {
            gen::del(m_spdir.m_p);
         }
      }
      catch(...)
      {
      }


      try
      {
         m_sposi.destroy();
      }
      catch(...)
      {
      }
      try
      {
         m_spdir.destroy();
      }
      catch(...)
      {
      }

      try
      {
         if(m_pmachineeventcentral != NULL)
         {
            m_pmachineeventcentral->set_run(false);
         }
      }
      catch(...)
      {
      }


      try
      {
         gen::del(m_plog);
      }
      catch(...)
      {
      }


      return iRet;
   }

   ::ca::ca * system::on_alloc(::ca::application * papp, const ::ca::type_info & info)
   {
      /*string str;
      str.Format("Could not alloc %s", info.raw_name());
      simple_message_box(str);*/
      ::ca::ca * pobj = System.factory().create(papp, info);
      if(pobj != NULL)
         return pobj;
      on_allocation_error(papp, info);
      return NULL;
   }

   ::ca::ca * system::clone()
   {
      // by the time, it is not possible to clone a system
      return NULL;
   }

   ::ca::ca * system::clone(::ca::ca * pobj)
   {
      return System.factory().base_clone(pobj);
   }


   bergedge::bergedge * system::get_bergedge(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      bergedge::bergedge * pbergedge = NULL;
      if(m_pbergedgemap == NULL)
         return NULL;
      if(!m_pbergedgemap->Lookup(iEdge, pbergedge))
      {
         pbergedge = dynamic_cast < ::bergedge::bergedge * > (create_application("bergedge", true, pbiasCreation));
         pbergedge->m_iEdge = iEdge;
         m_pbergedgemap->set_at(iEdge, pbergedge);
      }
      return pbergedge;
   }


   platform::document * system::get_platform(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      bergedge::bergedge * pbergedge = get_bergedge(iEdge, pbiasCreation);
      return pbergedge->get_platform();
   }

   nature::document * system::get_nature(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      bergedge::bergedge * pbergedge = get_bergedge(iEdge, pbiasCreation);
      return pbergedge->get_nature();
   }

   ::ca::application * system::application_get(index iEdge, const char * pszId, bool bCreate, bool bSynch, ::ca::application_bias * pbiasCreate)
   {
      bergedge::bergedge * pbergedge = get_bergedge(iEdge, pbiasCreate);
      return pbergedge->application_get(pszId, bCreate, bSynch, pbiasCreate);
   }


   ::ca::window_draw * system::get_twf()
   {
      return m_ptwf;
   }

   ::ca::window_draw * system::_001GetTwf()
   {
      return m_ptwf;
   }

   ::ca::history & system::hist()
   {
      return *m_phistory;
   }

   class ::fs::data * system::fs()
   {
      return m_pfsdata;
   }

   bool system::set_history(::ca::history * phistory)
   {
      m_phistory = phistory;
      return true;
   }

   ::ca2::log & system::log()
   {
      return *m_plog;
   }

   factory & system::factory()
   {
      return *m_pfactory;
   }

   ::ca::application_ptra & system::appptra()
   {
      return m_appptra;
   }

   ::ca2::file::system & system::file()
   {
      return m_file;
   }

   ::ca2::net & system::net()
   {
      return m_net;
   }

   ::ca::dir::system & system::dir()
   {
      return m_spdir;
   }

   ::ca2::stra & system::stra()
   {
      return m_stra;
   }

   ::ca2::url & system::url()
   {
      return m_url;
   }

   ::ca2::html & system::html()
   {
      return m_html;
   }

   ::ca2::xml & system::xml()
   {
      return m_xml;
   }

   ::fontopus::user_set & system::userset()
   {
      return m_userset;
   }

   ::ca2::service & system::service()
   {
      return m_service;
   }

   ::ca2::install & system::install()
   {
      return m_install;
   }

   ::ca::osi & system::osi()
   {
      return m_sposi;
   }

   ::ca2::process & system::process()
   {
      return m_process;
   }

   ::ca2::datetime & system::datetime()
   {
      return *m_pdatetime;
   }

   void system::register_bergedge_application(::ca::application * papp)
   {
      appptra().add(papp);
   }

   void system::unregister_bergedge_application(::ca::application * papp)
   {
      appptra().remove(papp);
   }

   void system::appa_load_string_table()
   {
      for(int i = 0; i < appptra().get_size(); i++)
      {
         ca2::application * papp = dynamic_cast < ca2::application * > (appptra()[i]);
         for(int j = 0; j < papp->m_langstrptra.get_size(); j++)
         {
            papp->m_langstrptra[j]->m_str.Empty();
         }
         papp->load_string_table();
      }
   }

   void system::appa_set_locale(const char * pszLocale, bool bUser)
   {
      for(int i = 0; i < appptra().get_size(); i++)
      {
         ca2::application * papp = dynamic_cast < ca2::application * > (appptra()[i]);
         papp->set_locale(pszLocale, bUser);
      }
   }

   void system::appa_set_style(const char * pszStyle, bool bUser)
   {
      for(int i = 0; i < appptra().get_size(); i++)
      {
         ca2::application * papp = dynamic_cast < ca2::application * > (appptra()[i]);
         papp->set_style(pszStyle, bUser);
      }
   }


   machine_event_central & system::machine_event_central()
   {
      return *m_pmachineeventcentral;
   }


   bool system::assert_running_global(const char * pszAppName, const char * pszId)
   {
      if(string(pszId).has_char())
      {
         HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_global_id_mutex_name(pszAppName, pszId));
         if(h == NULL)
         {
            string strApp = pszAppName;
            strApp += "app.exe";
            string strParameters;
            strParameters = ": global_mutex_id=\"" + string(pszId) + "\"";
            ::ShellExecute(NULL, NULL, dir().path(get_module_folder(), strApp), strParameters, NULL, SW_SHOW);
            return false;
         }
         else
         {
            ::CloseHandle(h);
         }
         return true;
      }
      else
      {
         HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_global_mutex_name(pszAppName));
         if(h == NULL)
         {
            string strApp = pszAppName;
            strApp += "app.exe";
            ::ShellExecute(NULL, NULL, dir().path(get_module_folder(), strApp), NULL, NULL, SW_SHOW);
            return false;
         }
         else
         {
            ::CloseHandle(h);
         }
         return true;
      }
   }

   bool system::assert_running_local(const char * pszAppName, const char * pszId)
   {
      string strAppName(pszAppName);
      string strId(pszId);
      if(strId.has_char())
      {
         HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_local_id_mutex_name(pszAppName, strId));
         if(h == NULL)
         {
            string strApp;
            strApp = "cubeapp.exe";
            string strParameters;
            strParameters = ": app=" + strAppName + " local_mutex_id=\"" + strId + "\"";
            ::ShellExecute(NULL, NULL, dir().path(get_ca2_module_folder(), strApp), strParameters, NULL, SW_SHOW);
            return false;
         }
         else
         {
            ::CloseHandle(h);
         }
         return true;
      }
      else
      {
         HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_local_mutex_name(pszAppName));
         if(h == NULL)
         {
            string strApp;
            strApp = "cubeapp.exe";
            string strParameters;
            strParameters = ": app=" + strAppName;
            ::ShellExecute(NULL, NULL, dir().path(get_ca2_module_folder(), strApp), strParameters, NULL, SW_SHOW);
            return false;
         }
         else
         {
            ::CloseHandle(h);
         }
         return true;
      }
   }

   bool system::initialize_log(const char * pszId)
   {
      if(m_plog != NULL)
         return true;
      m_plog = dynamic_cast < class ::ca2::log * > (alloc(this, typeid(class ::ca::log)));
      m_plog->set_extended_log();
      m_plog->set_app(this);
      if(!m_plog->initialize(pszId))
      {
         gen::del(m_plog);
         return false;
      }
//      _template::trace_v = &_template::system_log_trace_v;
      return true;
   }

   bool system::finalize()
   {
      system::application::finalize();
      

      return true;
   }


   string system::matter_as_string(::ca::application * papp, const char * pszMatter, const char * pszMatter2)
   {
      return file().as_string(dir_matter(pszMatter, pszMatter2), papp);
   }

   string system::dir_matter(const char * pszMatter, const char * pszMatter2)
   {
      return dir().matter(pszMatter, pszMatter2);
   }

   bool system::is_inside_time_dir(const char * pszPath)
   {
      return dir().is_inside_time(pszPath);
   }

   bool system::file_is_read_only(const char * pszPath)
   {
      return file().is_read_only(pszPath);
   }

   string system::file_as_string(::ca::application * papp, const char * pszPath)
   {
      return file().as_string(pszPath, papp);
   }

   string system::dir_path(const char * psz1, const char * psz2, const char * psz3)
   {
      return dir().path(psz1, psz2, psz3);
   }

   string system::dir_name(const char * psz)
   {
      return dir().name(psz);
   }

   bool system::dir_mk(const char * psz)
   {
      return dir().mk(psz);
   }

   string system::file_title(const char * psz)
   {
      return file().name_(psz);
   }

   string system::file_name(const char * psz)
   {
      return file().title_(psz);
   }

   void system::register_delete(::ca::ca * plistened, ::ca::ca * plistener)
   {
      if(plistened == plistener)
         return;
      if(plistened == NULL)
         return;
      if(plistener == NULL)
         return;
      CSingleLock sl(&m_mutexDelete, TRUE);
      m_mapmanyDelete[plistened].add(plistener);
      m_mapmanyDeleteReverse[plistener].add(plistened);
   }
      
   void system::unregister_delete(::ca::ca * plistened, ::ca::ca * plistener)
   {
      if(plistened == plistener)
         return;
      if(plistened == NULL)
         return;
      if(plistener == NULL)
         return;
      CSingleLock sl(&m_mutexDelete, TRUE);
      ::ca::map_many::pair * ppair = m_mapmanyDelete.PLookup(plistened);
      if(ppair != NULL)
      {
         ppair->m_value.remove(plistener);
      }
      ::ca::map_many::pair * ppairReverse = m_mapmanyDeleteReverse.PLookup(plistener);
      if(ppairReverse != NULL)
      {
         ppairReverse->m_value.remove(plistened);
      }
   }

   void system::on_delete(::ca::ca * pca)
   {


      CSingleLock sl(&m_mutexDelete, TRUE);


      ::ca::ptra listeneraDelete;


      ::ca::map_many::pair * ppair = m_mapmanyDelete.PLookup(pca);
      if(ppair != NULL)
      {
         ::ca::ptra & listenera = ppair->m_value;
         listeneraDelete = listenera;
         for(int i = 0; i < listenera.get_size(); i++)
         {
            ::ca::ca * plistener = listenera[i];
            m_mapmanyDeleteReverse[plistener].remove(pca);
         }
         m_mapmanyDelete.remove_key(pca);
      }


      ::ca::map_many::pair * ppairReverse = m_mapmanyDeleteReverse.PLookup(pca);
      if(ppairReverse != NULL)
      {
         ::ca::ptra & listeneda = ppairReverse->m_value;
         for(int i = 0; i < listeneda.get_size(); i++)
         {
            ::ca::ca * plistened = listeneda[i];
            m_mapmanyDelete[plistened].remove(pca);
         }
         m_mapmanyDeleteReverse.remove_key(pca);
      }


      sl.Unlock();


      for(int i = 0; i < listeneraDelete.get_size(); i++)
      {
         ::ca::ca * plistener = listeneraDelete[i];
         if(plistener != NULL)
         {
            try
            {
               plistener->on_delete(pca);
            }
            catch(...)
            {
            }
         }
      }


   }

   int system::________ca2_votagus_logging_Report(
      int iReportType, 
      const char * pszFileName, 
      int iLineNumber, 
      const char * pszModuleName, 
      const char * pszFormat, va_list list)
   {
      if(m_plog == NULL || !m_plog->m_bExtendedLog)
      {
         return ::ca::SimpleDebugReport(iReportType, pszFileName, iLineNumber, pszModuleName, pszFormat, list);
      }

      string str;
      if(pszFileName != NULL || pszModuleName != NULL)
      {
         stringa stra;
         if(pszFileName != NULL)
            stra.add(pszFileName);
         if(pszModuleName != NULL)
            stra.add(pszFileName);
         str += stra.implode(", ");
         str += ": ";
      }
      string str2;
      if(pszFormat != NULL)
      {
         if(list != NULL)
         {
            str2.FormatV(pszFormat, list);
         }
         else
         {
            str2 = pszFormat;
         }
      }
      
      str = str + str2;
      string strPrint(str);
      strPrint.replace("%", "%%");
      if(m_plog != NULL)
      {
         m_plog->print(strPrint);
      }
      if(iReportType == _CRT_ASSERT && is_debugger_attached())
      {
#ifdef _DEBUG
         gen::property_set propertyset;
         propertyset["filepath"] = pszFileName;
         propertyset["linenumber"] = iLineNumber;
         message_box("system\\debug\\assert.xhtml", propertyset);
#endif
      }
      if(iReportType == _CRT_ASSERT)
      {
         return 1;
      }
      else
      {
         return 0;
      }
   }

   bool system::assert_failed_line(const char * lpszFileName, int iLine)
   {
      if(!on_assert_failed_line(lpszFileName, iLine))
         return false;
      // may be in another thread than application thread
   #ifdef _DEBUG
   #ifndef _AFX_NO_DEBUG_CRT
      // we remove WM_QUIT because if it is in the queue then the message box
      // won't display
      MSG msg;
      BOOL bQuit = PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE);
      va_list list = NULL;
      bool bResult = ________ca2_votagus_logging_Report(_CRT_ASSERT, lpszFileName, iLine, NULL, NULL, list) != 0;
      if (bQuit)
         PostQuitMessage((int)msg.wParam);
      return bResult;
   #else
      // Not supported.
   #error _AFX_NO_DEBUG_CRT is not supported.
   #endif // _AFX_NO_DEBUG_CRT
   #else
      TRACE("AfxAssertFailedLine %s %d", lpszFileName, iLine);
      return true;
   #endif
   }

   void system::on_allocation_error(::ca::application * papp, const ::ca::type_info & info)
   {
      simple_message_box(NULL, MB_ICONINFORMATION, "Implement \"%s\" allocation\n", info.raw_name());
   }



   bool system::wait_twf(DWORD dwTimeOut)
   {
      if(dwTimeOut > 1984)
         dwTimeOut = 1984;
      if(m_ptwf != NULL && m_ptwf->m_bProDevianMode)
      {
         return m_ptwf->m_eventFree.Lock(dwTimeOut) != FALSE;
      }
      /*else if(m_puiInitialPlaceHolderContainer != NULL)
      {
#define InitialPlaceHolderContainer_TWF_FREE_EVENT 2010
         return App(this).event_lock(m_puiInitialPlaceHolderContainer, InitialPlaceHolderContainer_TWF_FREE_EVENT, dwTimeOut);
      }*/
      else
      {
         return true;
      }
   }

   int system::_001OnDebugReport(int i1, const char * psz1, int i2, const char * psz2, const char * psz3, va_list args)
   {
     return ________ca2_votagus_logging_Report(i1, psz1, i2, psz2, psz3, args);
   }


   void system::request_application(index iEdge, const char * pszId, var varFile, var varQuery, ::ca::application_bias * pbiasCreate)
   {
      get_bergedge(iEdge, pbiasCreate)->request_application(pszId, varFile, varQuery, pbiasCreate);
   }

   void system::request_application(::ca2::application_request * prequest)
   {
      fontopus::application::request_application(prequest);
   }

   void system::open_by_file_extension(index iEdge, const char * pszFileName)
   {
      get_bergedge(iEdge)->open_by_file_extension(pszFileName);
   }

   ::ca::ca * system::alloc(::ca::application * papp, const ::ca::type_info & info)
   {
      return ::gen::system::alloc(papp, info);
   }


   bool system::sync_load_url(string & str, const char * lpszUrl, ::fontopus::user * puser, ::http::cookies * pcookies)
   {
      string filename = System.file().time_square();
      gen::property_set headers;
      gen::property_set post;
      gen::property_set set;
      if(!http().download(lpszUrl, filename, post, headers, set, pcookies, puser))
         return false;
      if(headers["Location"].get_string().has_char())
      {
         post.m_propertya.remove_all();
         headers.m_propertya.remove_all();
         ::DeleteFile(filename);
         return http().download(str, headers["Location"], post, headers, set, pcookies, puser);
      }
      str = Application.file().as_string(filename);
      return true;

   /*   Parse pa(lpszUrl,":/");
      string protocol = pa.getword();
      string host = pa.getword();
      int port;
      {
         Parse pa((const char *) host,":");
         pa.getword();
         port = pa.getvalue();
      }
      string url = "/";
      url += pa.getrest();
      string filename = System.file()time_square();
      
      bool bOk = false;
      bool bRead = false;
      if (protocol == "http" || protocol == "https")
      {
         socket_handler h;
         string strFilename;
         SpaHttpGet s(h, lpszUrl, "");
         if(pcookies != NULL)
         {
            string strCookie;
            for(int i = 0; i < pcookies->get_size(); i++)
            {
               strCookie += (const char *) (pcookies->element_at(i).m_strName + "=" + pcookies->element_at(i).m_strValue);
               strCookie += ";";
            }
            s.AddResponseHeader("Cookie", strCookie);
         }
         s.m_pcookies = pcookies;
         //s.SetLineProtocol(false);
         s.SetFilename((const char *) filename);
         h.add(&s);
         h.Select(1,0);
         while (h.get_count())
         {
            h.Select(1,0);
         }
         bool bOk = s.Complete();
         if(!s.m_strHeaderLocation.is_empty())
         {
            ::DeleteFile(filename);
            sync_load_url(str, s.m_strHeaderLocation, pcookies);
         }
         else
         {
            bRead = true;
         }
      }
      else
      {
         printf("Unknown protocol: '%s'\n", protocol);
      }
      if(bRead)
      {
         int iMaxpath = MAX_PATH;
         int iLen = strlen(filename);
         gzFile gzf = gzopen(filename, "rb");
         int iRead;
         gen::memory_file memfile;
         int iBufSize = (1024 * 256);
         char * buf = (char *) malloc(iBufSize);
         while((iRead = gzread(gzf, buf, iBufSize)) > 0)
         {
            memfile.write(buf, iRead);
         }
         free(buf);
         int iErr;
         const char * pszErr = gzerror(gzf, &iErr);
         char ch = '\0';
         memfile.write(&ch, 1);
         str = (char *) memfile.GetAllocation();
         ::DeleteFile(filename);
      }
      return bOk;*/
   }

   ::ca4::compress & system::compress()
   {
      return m_compress;
   }

   ::ca4::patch & system::patch()
   {
      return m_patch;
   }

   class ::ca4::crypt & system::crypt()
   {
      return m_crypt;
   }

   class ::ca4::email & system::email()
   {
      return m_email;
   }

   class ::ca4::http::system & system::http()
   {
      return m_http;
   }

   ::ca4::file & system::file36()
   {
      return m_file4;
   }

   class copydesk & system::copydesk()
   {
      return *m_pcopydesk;
   }

   class ::fontopus::license & system::license()
   {
      return *m_plicense;
   }


   void system::http_config_proxy(const char * pszUrl, ::sockets::http_tunnel * ptunnel)
   {
      http().config_proxy(pszUrl, ptunnel);
   }

   bool system::is_licensed(const char * pszId, bool bInteractive)
   {
      return license().has(pszId, bInteractive);
   }

   bool system::base_support()
   {
      return true;
   }

   index system::get_new_bergedge()
   {
      int iNewEdge = m_iNewEdge;
      bergedge::bergedge * pbergedge;
      while(m_pbergedgemap->Lookup(iNewEdge, pbergedge))
      {
         iNewEdge++;
      }
      if(get_bergedge(iNewEdge) == NULL)
         return -1;
      m_iNewEdge = iNewEdge + 1;
      return iNewEdge;
   }

        
   bool system::create_twf()
   {
      if(m_ptwf != NULL)
         return true;
      m_ptwf = dynamic_cast < ::ca::window_draw * > (alloc(this, typeid(::ca::window_draw)));
      m_ptwf->start();
      return true;
   }

} // namespace system
