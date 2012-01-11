#include "StdAfx.h"

#ifdef WINDOWS
#undef new
#include <GdiPlus.h>
#define new DEBUG_NEW
#endif

namespace plane
{

/*   CLASS_DECL_ca class heap_item_array * g_pheapitema = NULL;


   CLASS_DECL_ca class heap_item_array * get_heap_itema()
   {
      return g_pheapitema;
   }

   CLASS_DECL_ca void set_heap_itema(class heap_item_array * pitema)
   {
      g_pheapitema = pitema;
   }*/

      

   system::system()
   {

      m_psystem                                 = this;
      m_file.m_psystem                          = this;
      ::plane::application::m_file.m_psystem    = this;
      m_dir.m_psystem                           = this;
      ::plane::application::m_dir.m_psystem     = this;

      m_bDoNotExitIfNoApplications              = false;


      if(::get_heap_mutex() == NULL)
      {
         ::set_heap_mutex(new mutex());
      }

#ifdef WINDOWS
      Gdiplus::GdiplusStartupInput gdiplusStartupInput;
      GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
#endif

/*      if(::plane::get_heap_itema() == NULL)
      {
         ::plane::set_heap_itema(new class ::plane::heap_item_array());
      }*/

      use_base_ca2_allocator();

      set_app(this);

      m_pfactory = new class factory(this);
      m_pfactory->set_app(this);

      m_pfactory->cloneable_large < ::ca::create_context > ();
      m_pfactory->cloneable_large < ::ca::application_bias > ();
      m_pfactory->cloneable_large < ::gen::command_line > ();


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
      //m_pfactory                 = NULL;
      m_plog                     = NULL;
      m_ptwf                     = NULL;
      m_pbergedgemap             = NULL;
      m_pcopydesk                = NULL;

      

      m_spfsdata(new ::fs::native(this));



      m_bInitApplication         = false;
      m_bInitApplicationResult   = FALSE;
      m_bProcessInitialize       = false;
      m_bProcessInitializeResult = false;

      m_bLibCharGuess            = false;
      m_puserstr                 = NULL;

      m_pcube                    = NULL;
      m_pwindowmap               = NULL;

   }

   system::~system()
   {

#ifdef WINDOWS
      Gdiplus::GdiplusShutdown(m_gdiplusToken);
#endif

      m_puiMain      = NULL;
      m_puiActive    = NULL;

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

      m_bInitApplicationResult = plane::application::InitApplication();

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


      ::ca::profiler::initialize();


      System.factory().creatable < ::ca2::log >(System.template type_info < ::ca::log > (), 1);

      if(!::planebase::application::process_initialize())
      {
         return false;
      }

      m_spportforward.create(this);

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

      if(!::plane::application::initialize())
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
      System.factory().cloneable_large < ::ca::region_sp >();
      System.factory().cloneable_large < var >();
      System.factory().creatable < ::ca2::log >(System.template type_info < ::ca::log > (), 1);

      m_puserstr = new ::user::str(this);
      if(m_puserstr == NULL)
         return false;

      if(!str().initialize())
         return false;

      if(!::planebase::application::initialize1())
         return false;

      try
      {
         find_applications();
      }
      catch(...)
      {
      }

      return true;

   }


   bool system::find_applications()
   {

/*      m_spfilehandler(new ::ca2::filehandler::handler(this));*/

      string strLibraryId;
      stringa straTitle;

      Application.dir().ls_pattern(System.dir().ca2module(), "app_*", NULL,& straTitle);

      for(int i = 0; i < straTitle.get_count(); i++)
      {
         strLibraryId = straTitle[i];
         gen::str::ends_eat_ci(strLibraryId, ".dll");
         gen::str::ends_eat_ci(strLibraryId, ".so");
         map_application_library(strLibraryId);
      }

      map_application_library("ca");
      map_application_library("ca2");

      return true;

   }

   bool system::map_application_library(const char * pszLibrary)
   {

      ::ca2::library library;

      if(!library.open(this, pszLibrary))
         return false;




//      m_spfilehandler->defer_add_library(library.m_pca2library);

      stringa stra;
      string strApp;

      library.get_app_list(stra);

      for(int i = 0; i < stra.get_count(); i++)
      {
         strApp = stra[i];
         m_mapAppLibrary.set_at(strApp, pszLibrary);
      }

      if(stra.get_count() <= 0)
         return false;

      return true;

   }



   bool system::initialize3()
   {

      if(!::planebase::application::initialize3())
         return false;

      if(m_phistory == NULL)
      {
         m_phistory = new os_history(this);
      }

      return true;
   }

   bool system::initialize_instance()
   {

      m_pfactory->enable_simple_factory_request();

      set_enum_name(var::type_null      , "null");
      set_enum_name(var::type_empty     , "is_empty");
      set_enum_name(var::type_string    , "string");
      set_enum_name(var::type_integer   , "integer");
      set_enum_name(var::type_ulong     , "ulong");
      set_enum_name(var::type_ca2       , "ca2");
      set_enum_name(var::type_bool      , "bool");
      set_enum_name(var::type_double    , "double");

      if(!planebase::application::initialize_instance())
        return false;

      m_pbergedgemap = new ::plane::session::map;

      return true;
   }


   bool system::bergedge_start()
   {
      return true;
   }

   bool system::verb()
   {

      ::plane::application::verb();

      if(directrix().m_varTopicQuery.has_property("install"))
         return false;

      if(directrix().m_varTopicQuery.has_property("uninstall"))
         return false;

      if(!m_bDoNotExitIfNoApplications)
      {

         if(appptra().get_size() <= 0)
            return false;

         if(appptra().get_size() == 1 && appptra().contains(this))
            return false;

      }

      return true;
   }


   int system::exit_instance()
   {

      try
      {
         m_pfactory->enable_simple_factory_request(false);
      }
      catch(...)
      {
         TRACE("system::exit_instance: Potentially catastrophical error : error disabling simple factory request");
      }

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
         m_spportforward.destroy();
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

      if(m_bLibCharGuess)
      {
         m_bLibCharGuess = false;
         LibCharGuess::Done();
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

   ::ca::ca * system::on_alloc(::ca::application * papp, ::ca::type_info & info)
   {
      /*string str;
      str.Format("Could not alloc %s", info.raw_name());
      simple_message_box(str);*/
      ::ca::ca * pobj = Sys(papp).factory().create(papp, info);
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


   plane::session * system::query_session(index iEdge)
   {
      plane::session * pbergedge = NULL;
      if(m_pbergedgemap == NULL)
         return NULL;
      if(!m_pbergedgemap->Lookup(iEdge, pbergedge))
      {
         return NULL;
      }
      return pbergedge;
   }


   plane::session * system::get_session(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      plane::session * pbergedge = NULL;
      if(m_pbergedgemap == NULL)
         return NULL;
      if(!m_pbergedgemap->Lookup(iEdge, pbergedge))
      {
         pbergedge = dynamic_cast < ::plane::session * > (create_application("session", true, pbiasCreation));
         if(pbergedge == NULL)
            return NULL;
         pbergedge->m_iEdge = iEdge;
         m_pbergedgemap->set_at(iEdge, pbergedge);
      }
      return pbergedge;
   }


   ::ca::application * system::application_get(index iEdge, const char * pszId, bool bCreate, bool bSynch, ::ca::application_bias * pbiasCreate)
   {
      ::plane::session * psession = get_session(iEdge, pbiasCreate);
      return psession->application_get(pszId, bCreate, bSynch, pbiasCreate);
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

   ::ca::file::system & system::file()
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

   ::user::str & system::str()
   {
      return *m_puserstr;
   }

/*   ::ca2::filehandler::handler & system::filehandler()
   {
      return *m_spfilehandler;
   }*/

   void system::register_bergedge_application(::ca::application * papp)
   {
      appptra().add_unique(papp);
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
            strApp = "ca2app.exe";
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
            strApp = "ca2app.exe";
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
      m_plog = dynamic_cast < class ::ca2::log * > (alloc(this, System.template type_info < class ::ca::log > ()));
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
      ::planebase::application::finalize();


      return true;
   }


   string system::matter_as_string(::ca::application * papp, const char * pszMatter, const char * pszMatter2)
   {
      return file().as_string(dir_matter(papp, pszMatter, pszMatter2), papp);
   }

   string system::dir_matter(::ca::application * papp, const char * pszMatter, const char * pszMatter2)
   {
      return dir().matter(papp, pszMatter, pszMatter2);
   }

   bool system::is_inside_time_dir(const char * pszPath)
   {
      return dir().is_inside_time(pszPath, this);
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
      return dir().mk(psz, this);
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
      plistener->listenedptra().add(plistened);
      plistened->listenerptra().add(plistener);
   }

   void system::unregister_delete(::ca::ca * plistened, ::ca::ca * plistener)
   {
      if(plistened == plistener)
         return;
      if(plistened == NULL)
         return;
      if(plistener == NULL)
         return;
      plistener->listenedptra().remove(plistened);
      plistened->listenerptra().remove(plistener);
   }

   void system::on_delete(::ca::ca * pca)
   {
      UNREFERENCED_PARAMETER(pca);
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

   void system::on_allocation_error(::ca::application * papp, ::ca::type_info & info)
   {
      UNREFERENCED_PARAMETER(papp);
      simple_message_box(NULL, MB_ICONINFORMATION, "Implement \"%s\" allocation\n", info.raw_name());
   }



   bool system::wait_twf(DWORD dwTimeOut)
   {
      if(dwTimeOut > 1984)
         dwTimeOut = 1984;
      if(m_ptwf != NULL && m_ptwf->m_bProDevianMode)
      {
         return m_ptwf->m_eventFree.wait(millis(dwTimeOut)).signaled();
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

   void system::on_request(::ca::create_context * pcreatecontext)
   {
      ::plane::session * psession = get_session(pcreatecontext->m_spCommandLine->m_iEdge, pcreatecontext->m_spCommandLine->m_pbiasCreate);
      psession->request(pcreatecontext);
   }

   void system::open_by_file_extension(index iEdge, const char * pszFileName)
   {
      ::plane::session * psession = get_session(iEdge);
      psession->open_by_file_extension(pszFileName);
   }

   ::ca::ca * system::alloc(::ca::application * papp, ::ca::type_info & info)
   {
      return ::gen::system::alloc(papp, info);
   }

   ::ca::ca * system::alloc(::ca::application * papp, const class id & idType)
   {
      return ::gen::system::alloc(papp, get_type_info(idType));
   }

   bool system::sync_load_url(string & str, const char * lpszUrl, ::fontopus::user * puser, ::http::cookies * pcookies)
   {
      string filename = System.file().time_square(get_app());
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
         str = (char *) memfile.get_data();
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

   void system::http_config_proxy(const char * pszUrl, ::sockets::http_tunnel * ptunnel)
   {
      http().config_proxy(pszUrl, ptunnel);
   }

   bool system::base_support()
   {
      return true;
   }

   index system::get_new_bergedge(::ca::application_bias * pbiasCreation)
   {
      int iNewEdge = m_iNewEdge;
      plane::session * pbergedge;
      while(m_pbergedgemap->Lookup(iNewEdge, pbergedge))
      {
         iNewEdge++;
      }
      if(get_session(iNewEdge, pbiasCreation) == NULL)
         return -1;
      m_iNewEdge = iNewEdge + 1;
      return iNewEdge;
   }


   bool system::create_twf()
   {
      if(m_ptwf != NULL)
         return true;
      m_ptwf = dynamic_cast < ::ca::window_draw * > (alloc(this, System.template type_info < ::ca::window_draw > ()));
      m_ptwf->start();
      return true;
   }

   bool system::is_system()
   {
      return true;
   }

   unsigned long system::guess_code_page(const char * pszText)
   {
      if(!m_bLibCharGuess)
      {
         LibCharGuess::Init();
         m_bLibCharGuess = true;
      }
      return LibCharGuess::GuessCodePage(pszText);
   }

   void system::discard_to_factory(::ca::ca * pca)
   {
      m_pfactory->discard(pca);
   }


   ::ca::application * system::get_new_app(::ca::application * pappNewApplicationParent, const char * pszAppId)
   {

      ca2::library library;

      string strLibrary = m_mapAppLibrary[pszAppId];

      ::ca::application * papp = NULL;
      if(!library.open(pappNewApplicationParent, strLibrary, false))
         return NULL;

      papp = library.get_new_app(pszAppId);
      if(papp == NULL)
         return NULL;

      return papp;

   }


   bool system::set_main_init_data(::ca::main_init_data * pdata)
   {

      if(pdata == NULL)
      {
         if(!::plane::application::set_main_init_data(pdata))
            return false;
         return true;
      }
      
      gen::property_set set(this);

      var varFile;
      string strApp;

      set._008ParseCommandFork(pdata->m_vssCommandLine, varFile, strApp);

      if((varFile.is_empty() && ((!set.has_property("app") && !set.has_property("show_platform"))
         || set["app"] == "session")) &&
         !(set.has_property("install") || set.has_property("uninstall")))
      {
         if(!set.has_property("show_platform") || set["show_platform"] == 1)
         {
            command().add_line(" : show_platform=1");
         }
      }
      else
      {
         string strCommandLine = pdata->m_vssCommandLine;
         strCommandLine.trim();
         if(strCommandLine[0] == '\"')
         {
            int iFind = strCommandLine.find("\"", 1);
            strCommandLine = strCommandLine.Mid(iFind + 1);
         }
         else
         {
            int iFind = strCommandLine.find(" ", 1);
            strCommandLine = strCommandLine.Mid(iFind + 1);
         }
         command().add_line(strCommandLine);
      }

      if(!::plane::application::set_main_init_data(pdata))
         return false;
      
      return true;

   }

   ::ca::type_info & system::get_type_info(const ::std_type_info & info)
   {
      
      ::ca::type_info & typeinfo = m_typemap[info.raw_name()];
      
      if(typeinfo.m_id.is_null())
         typeinfo = info;

      return typeinfo;

   }

   


   //////////////////////////////////////////////////////////////////////////////////////////////////
   // System/Cube
   //
   ::document * system::hold(::user::interaction * pui)
   {


      if(m_pcubeInterface != NULL)
      {
         return m_pcubeInterface->hold(pui);
      }

      return NULL;

   }


   count system::get_monitor_count()
   {

      if(m_pcubeInterface != NULL)
      {
         return m_pcubeInterface->get_monitor_count();
      }

      return 0;

   }

   bool system::get_monitor_rect(index i, LPRECT lprect)
   {

      if(m_pcubeInterface != NULL)
      {
         return m_pcubeInterface->get_monitor_rect(i, lprect);
      }


      return false;

   }


   count system::get_desk_monitor_count()
   {

      if(m_pcubeInterface != NULL)
      {
         return m_pcubeInterface->get_desk_monitor_count();
      }

      return 0;

   }

   bool system::get_desk_monitor_rect(index i, LPRECT lprect)
   {

      if(m_pcubeInterface != NULL)
      {
         return m_pcubeInterface->get_desk_monitor_rect(i, lprect);
      }


      return false;

   }

   FileManagerTemplate * system::GetStdFileManagerTemplate()
   {
      
      if(m_pcubeInterface != NULL)
      {
         return m_pcubeInterface->GetStdFileManagerTemplate();
      }

      return NULL;

   }

   ::gen::command_thread & system::command_thread()
   {
	   return *m_pcommandthread;
   }

} // namespace plane

