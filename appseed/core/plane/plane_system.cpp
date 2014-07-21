#include "framework.h"


#ifdef WINDOWS
#undef new
#include <GdiPlus.h>
#define new BASE_NEW
#endif


namespace plane
{


   system::system(sp(::base::application) papp) :
      m_mutexDelete(this),
      m_mutex(this),
#ifndef METROWIN
      m_processsection(this),
#endif
      m_visual(this),
      ::base::system(papp),
      m_emaildepartament(this)
   {

#ifdef METROWIN
      m_window                                  = nullptr;
#endif

      m_pplanesystem                            = this;
      set_app(this);


      if(papp == NULL)
      {

         oprop("parent_system") = (sp(element)) NULL;

      }
      else
      {

         oprop("parent_system") = papp->m_pplanesystem;

      }

      m_ftlibrary = NULL;


      m_bDoNotExitIfNoApplications              = true;

      string strId;
      //strId = m_strAppName;
      //strId += ::str::has_char(m_strAppId, ".");
      //strId += ::str::has_char(m_strBaseSupportId, ".");




/*
      if(psystemParent == NULL)
      {

         m_peengine                                = new ::exception::engine(this);

      }
      else
      {

         m_peengine                                = psystemParent->m_peengine;

      }
*/






      m_stra.set_app(this);
//      m_url.set_app(this);
      m_userset.set_app(this);
      m_service.set_app(this);
#ifndef METROWIN
      m_processsection.set_app(this);
#endif
      m_pdatetime = new class ::datetime::departament(this);
//      m_email.set_app(this);






      m_bInitApplication         = false;
      m_bInitApplicationResult   = FALSE;
      m_bProcessInitialize       = false;
      m_bProcessInitializeResult = false;

      m_bLibCharGuess            = false;
      m_puserstr                 = NULL;

      m_pparserfactory           = NULL;

      m_bLicense                 = false;

      m_prunstartinstaller       = NULL;
      m_bLicense                 = false;
      m_strAppName               = "system";
      m_strInstallToken          = "system";


   }


   system::~system()
   {

   }


   void system::construct()
   {

      ::application::construct();

      ::core::system::construct();

   }


   bool system::InitApplication()
   {

      if(m_bInitApplication)
         return m_bInitApplicationResult;

      m_bInitApplicationResult      = FALSE;
      m_bInitApplication            = true;

      m_bInitApplicationResult = ::application::InitApplication();

      return m_bInitApplicationResult;
   }


   bool system::process_initialize()
   {



      if(m_bProcessInitialize)
         return m_bProcessInitializeResult;

      m_bProcessInitializeResult    = false;
      m_bProcessInitialize          = true;

      if (!::application::process_initialize())
         return false;

      if(!::core::system::process_initialize())
         return false;




      ::core::profiler::initialize();


//      System.factory().creatable < ::base::log >(System.type_info < ::base::log > (), 1);

/*      if(!::application::process_initialize())
      {
         return false;
      }*/



      m_spportforward.create(allocer());


      m_phtml = create_html();

      m_phtml->add_ref();

      if(m_phtml == NULL)
         return false;

      m_phtml->construct(this);


      m_bProcessInitializeResult = true;
      return true;
   }


   bool system::initialize()
   {

      if(!m_visual.initialize())
         return false;

      int32_t error = FT_Init_FreeType( &m_ftlibrary );
      if ( error )
      {
         TRACE("an error occurred during Free Type library initialization");
         return false;
      }


#ifndef APPLEOS

      if(m_pparserfactory == NULL)
      {



      }

#endif


      if(!::application::initialize())
         return false;

      return true;
   }



   bool system::initialize1()
   {



      m_visual.construct(this);

      if(!m_visual.initialize1())
         return false;



      m_spfilehandler = new ::filehandler::handler(this);




      if(!::application::initialize1())
         return false;


      //if(session().fontopus()->create_system_user("system") == NULL)
        // return false;


      m_puserstr = new ::user::str(this);
      if(m_puserstr == NULL)
         return false;

      if(!str().initialize())
         return false;


#if !defined(DEBUG) || defined(WINDOWS)
      try
      {
#endif
         find_applications_from_cache();
#if !defined(DEBUG) || defined(WINDOWS)
      }
      catch(...)
      {
      }
#endif

      if(!m_phtml->initialize())
         return false;



      return true;

   }


   bool system::find_applications_from_cache()
   {

      m_spfilehandler->m_sptree->remove_all();

      if(directrix()->m_varTopicQuery.has_property("install"))
         return true;

      ::file::binary_buffer_sp file = session().m_file.get_file(System.dir().appdata("applibcache.bin"), ::file::type_binary | ::file::mode_read);

      if(file.is_null())
         return false;

      ::file::byte_input_stream is(file);

      is >> m_mapAppLibrary;

      is >> *m_spfilehandler.m_p;

      return true;

   }


   ::filehandler::handler & system::filehandler()
   {

      return *m_spfilehandler;

   }


   colorertake5::ParserFactory & system::parser_factory()
   {

      if(m_pparserfactory == NULL)
      {

         m_pparserfactory = new colorertake5::ParserFactory(this);

      }

      return *m_pparserfactory;

   }



   bool system::find_applications_to_cache()
   {

      /*      m_spfilehandler(new ::core::filehandler::handler(this));*/

      m_mapAppLibrary.remove_all();

      string strLibraryId;
      stringa straTitle;

      session().dir().ls_pattern(System.dir().ca2module(), "*.*", NULL,& straTitle);

      for(int32_t i = 0; i < straTitle.get_count(); i++)
      {

         strLibraryId = straTitle[i];

         if(::str::ends_eat_ci(strLibraryId, ".dll")
            || ::str::ends_eat_ci(strLibraryId, ".so")
            || ::str::ends_eat_ci(strLibraryId, ".dylib"))
         {

            if(::str::begins_ci(strLibraryId, "libdraw2d_")
            || ::str::begins_ci(strLibraryId, "libbase"))
            {
               continue;
            }

            map_application_library(strLibraryId);

         }

      }

      ::file::binary_buffer_sp file;

      try
      {

         file = session().m_file.get_file(System.dir().appdata("applibcache.bin"), ::file::defer_create_directory | ::file::type_binary | ::file::mode_create  | ::file::mode_write);

      }
      catch(::exception::base &)
      {

         return false;

      }

      ::file::byte_output_stream os(file);

      os << m_mapAppLibrary;

      os << *m_spfilehandler.m_p;

      return true;

   }

   bool system::map_application_library(const char * pszLibrary)
   {

      ::core::library library(this, NULL);

      if (!strcmp(pszLibrary, "app_core_rdpclient.dll"))
      {
         TRACE("reach");
      }

      if(!library.open(pszLibrary, true))
         return false;

      m_spfilehandler->defer_add_library(library.m_pca2library);

      stringa stra;

      string strRoot = library.get_root();

      library.get_app_list(stra);

      if(stra.get_count() <= 0)
         return false;

      strRoot += "/";

      if(stra.get_count() == 1)
      {

         m_mapAppLibrary.set_at(strRoot + stra[0], pszLibrary);

      }

      string strLibrary(pszLibrary);

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

      if(strLibrary == "libbase")
      {

         strLibrary = "base";

      }
      else if(!::str::begins_eat(strLibrary, "libbase"))
      {

         ::str::begins_eat(strLibrary, "lib");

      }

#endif

      string strPrefix = strRoot;

      strPrefix.replace("-", "_");

      strPrefix.replace("/", "_");

      ::str::begins_eat_ci(strLibrary, strPrefix);

      strRoot += strLibrary;

      strRoot += "/";

      for(int32_t i = 0; i < stra.get_count(); i++)
      {

         m_mapAppLibrary.set_at(strRoot + stra[i], pszLibrary);

      }

      return true;

   }



   bool system::initialize3()
   {

      if(!::application::initialize3())
         return false;

      if(m_phistory == NULL)
      {
         m_phistory = new os_history(this);
      }

      return true;
   }

   bool system::initialize_instance()
   {

      if(!::core::system::initialize_instance())
      {
         return false;
      }

      /*set_enum_name(var::type_null      , "NULL");
      set_enum_name(var::type_empty     , "is_empty");
      set_enum_name(var::type_string    , "string");
      set_enum_name(var::type_int32   , "integer");
      set_enum_name(var::type_uint32     , "ulong");
      set_enum_name(var::type_element       , "ca2");
      set_enum_name(var::type_bool      , "bool");
      set_enum_name(var::type_double    , "double");*/



      if(!::application::initialize_instance())
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

      static uint32_t dwStart = ::get_tick_count();

      ::application::verb();

      if(directrix()->m_varTopicQuery.has_property("install") && (get_tick_count() - dwStart) > (5 * 184 * 1000))
         return false;

      if(directrix()->m_varTopicQuery.has_property("uninstall") && (get_tick_count() - dwStart) > (5 * 184 * 1000))
         return false;

      if(!m_bDoNotExitIfNoApplications)
      {

         ::base::application_ptra appptra;

         appptra = get_appptra();

         for(int32_t i = 0; i < appptra.get_size(); )
         {

            try
            {

               if(appptra[i].is_session() || appptra[i].is_system())
               {

                  appptra.remove_at(i);

                  continue;

               }
               else if(appptra[i].is_serviceable() && appptra[i].m_strAppId != directrix()->m_varTopicQuery["app"].get_string())
               {

                  appptra.remove_at(i);

                  continue;

               }

            }
            catch(...)
            {

               appptra.remove_at(i);

               continue;

            }

            i++;

         }

         if(appptra.get_size() <= 0)
         {

            return false;

         }

         if(appptra.get_size() == 1 && appptra.contains(this))
         {

            return false;

         }

      }

      return true;
   }


   int32_t system::exit_instance()
   {

      __wait_threading_count(::millis((5000) * 8));

      if(m_bLibCharGuess)
      {
         m_bLibCharGuess = false;
         LibCharGuess::Done();
      }


      int32_t iRet = 0;


      try
      {

         iRet = ::core::system::exit_instance();

      }
      catch(...)
      {

      }



      try
      {
         m_spportforward.release();
      }
      catch(...)
      {
      }



      try
      {
         if(m_spos.is_set())
         {
            m_spos.release();
         }
      }
      catch(...)
      {
      }
      try
      {
         m_spdir.release();
      }
      catch(...)
      {
      }


      try
      {
         m_spos.release();
      }
      catch(...)
      {
      }
      try
      {
         m_spdir.release();
      }
      catch(...)
      {
      }

      if(m_bLibCharGuess)
      {
         m_bLibCharGuess = false;
         LibCharGuess::Done();
      }


      m_plog.release();

      m_typemap.remove_all();

      m_typemap.release();


      return iRet;
   }

   /*
   sp(element) system::on_alloc(sp(::base::application) papp, sp(type) info)
   {
      /*string str;
      str.Format("Could not alloc %s", info.name());
      simple_message_box(str);*/
      /*sp(element) pobj = Sys(papp).factory().create(papp, info);
      if(pobj != NULL)
         return pobj;
      on_allocation_error(papp, info);
      return NULL;
   }
   */


   sp(::base::session) system::query_session(index iEdge)
   {
      sp(::plane::session) pbergedge = NULL;
      if(m_pbergedgemap == NULL)
         return NULL;
      if(!m_pbergedgemap->Lookup(iEdge, pbergedge))
      {
         return NULL;
      }
      return pbergedge;
   }


   sp(::plane::session) system::get_session(index iEdge, application_bias * pbiasCreation)
   {
      sp(::plane::session) pbergedge = NULL;
      if(m_pbergedgemap == NULL)
         return NULL;
      if(!m_pbergedgemap->Lookup(iEdge, pbergedge))
      {
         pbergedge = create_application("application", "session", true, pbiasCreation);
         if(pbergedge == NULL)
            return NULL;
         pbergedge->m_iEdge = iEdge;
         m_pbergedgemap->set_at(iEdge, pbergedge);
      }
      return pbergedge;
   }


   ::core::history & system::hist()
   {
      return *m_phistory;
   }


   bool system::set_history(::core::history * phistory)
   {
      m_phistory = phistory;
      return true;
   }

   ::core::stra & system::stra()
   {
      return m_stra;
   }

   ::core::service & system::service()
   {
      return m_service;
   }


#ifndef METROWIN

   ::core::process_departament & system::process()
   {
      return m_processsection;
   }

#endif





   bool system::finalize()
   {

      __wait_threading_count_except(this, ::millis((5000) * 77));

      try
      {
         if(m_spcrypto.is_set())
         {
            m_spcrypto.release();
         }
      }
      catch(...)
      {
      }

      ::application::finalize();

      try
      {

         if(m_spportforward.is_set())
         {

            m_spportforward.release();

         }

      }
      catch(...)
      {

      }


      try
      {

         if(m_spfile.is_set())
         {

            m_spfile.release();

         }

      }
      catch(...)
      {

      }




      return true;

   }



   int32_t system::__ca2_logging_report(
      int32_t iReportType,
      const char * pszFileName,
      int32_t iLineNumber,
      const char * pszModuleName,
      const char * pszFormat, va_list list)
   {

      if(m_plog == NULL || !m_plog->m_bExtendedLog)
      {

         return ::base::SimpleDebugReport(iReportType, pszFileName, iLineNumber, pszModuleName, pszFormat, list);

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
#ifdef DEBUG
         property_set propertyset;
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

   bool system::assert_failed_line(const char * lpszFileName, int32_t iLine)
   {
      if(!on_assert_failed_line(lpszFileName, iLine))
         return false;

      // may be in another thread than application thread
#ifdef DEBUG
#ifndef ___NO_DEBUG_CRT
      // we remove WM_QUIT because if it is in the queue then the message box
      // won't display
#ifdef WINDOWSEX
      MESSAGE msg;
      bool bQuit = PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE) != FALSE;
      va_list list = NULL;
#elif defined(METROWIN)
      va_list list = NULL;
      //throw todo(get_app());
#else
      va_list list = {};
#endif
      bool bResult = __ca2_logging_report(_CRT_ASSERT, lpszFileName, iLine, NULL, NULL, list) != 0;
#ifdef WINDOWSEX
      if (bQuit)
         PostQuitMessage((int32_t)msg.wParam);
#endif
      return bResult;
#else
      // Not supported.
#error ___NO_DEBUG_CRT is not supported.
#endif // ___NO_DEBUG_CRT
#else
      TRACE("__assert_failed_line %s %d", lpszFileName, iLine);
      return true;
#endif
   }

   void system::on_allocation_error(sp(::base::application) papp, sp(type) info)
   {

      UNREFERENCED_PARAMETER(papp);

      App(papp).simple_message_box(NULL, MB_ICONINFORMATION, "Implement \"%s\" allocation\n", info->friendly_name());

   }



   bool system::wait_twf(uint32_t dwTimeOut)
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

   int32_t system::_001OnDebugReport(int32_t i1, const char * psz1, int32_t i2, const char * psz2, const char * psz3, va_list args)
   {
      return __ca2_logging_report(i1, psz1, i2, psz2, psz3, args);
   }


   void system::on_request(sp(::create_context) pcreatecontext)
   {

      sp(::plane::session) psession = get_session(pcreatecontext->m_spCommandLine->m_iEdge, pcreatecontext->m_spCommandLine->m_pbiasCreate);

      if (psession == NULL)
      {

         ::simple_message_box(get_splash(), "An error that prevents the application from starting has occurred.\r\n\r\nPlease run app-removal.exe and restart the application, or contact the administrator.", "Startup Error", MB_ICONEXCLAMATION);

#ifdef WINDOWS

         ::ExitProcess(-17);

#endif

         return;

      }

      psession->request_create(pcreatecontext);

   }


   bool system::sync_load_url(string & str, const char * lpszUrl, ::fontopus::user * puser, ::http::cookies * pcookies)
   {
      string filename = System.file().time_square(get_app());
      property_set set;
      set["user"] = puser;
      set["cookies"] = pcookies;
      if(!http().download(lpszUrl, filename, set))
         return false;

      string strLocation = set["get_headers"]["Location"];

      if(strLocation.has_char())
      {

         property_set set;

         set["user"] = puser;

         set["cookies"] = pcookies;

         file().del(filename);

         return http().download(str, strLocation, set);

      }

      str = session().file().as_string(filename);

      return true;

      /*   Parse pa(lpszUrl,":/");
      string protocol = pa.getword();
      string host = pa.getword();
      int32_t port;
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
      for(int32_t i = 0; i < pcookies->get_size(); i++)
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
      int32_t iMaxpath = MAX_PATH;
      int32_t iLen = strlen(filename);
      gzFile gzf = gzopen(filename, "rb");
      int32_t iRead;
      ::file::memory_buffer memfile;
      int32_t iBufSize = (1024 * 256);
      char * buf = (char *) malloc(iBufSize);
      while((iRead = gzread(gzf, buf, iBufSize)) > 0)
      {
      memfile.write(buf, iRead);
      }
      free(buf);
      int32_t iErr;
      const char * pszErr = gzerror(gzf, &iErr);
      char ch = '\0';
      memfile.write(&ch, 1);
      str = (char *) memfile.get_data();
      ::DeleteFile(filename);
      }
      return bOk;*/
   }

   ::core::patch & system::patch()
   {
      return m_patch;
   }


   ::net::email_departament & system::email()
   {
      return m_emaildepartament;
   }

   ::http::system & system::http()
   {
      return m_httpsystem;
   }



   bool system::base_support()
   {
      return true;
   }

   index system::get_new_bergedge(application_bias * pbiasCreation)
   {
      index iNewEdge = m_iNewEdge;
      sp(::plane::session) pbergedge;
      while(m_pbergedgemap->Lookup(iNewEdge, pbergedge))
      {
         iNewEdge++;
      }
      if(get_session(iNewEdge, pbiasCreation) == NULL)
         return -1;
      m_iNewEdge = iNewEdge + 1;
      return iNewEdge;
   }



   uint32_t system::guess_code_page(const char * pszText)
   {
      if(!m_bLibCharGuess)
      {
         LibCharGuess::Init();
         m_bLibCharGuess = true;
      }
      return LibCharGuess::GuessCodePage(pszText);
   }



   sp(::user::object) system::place_hold(sp(::user::interaction) pui)
   {


      //if(m_pcubeInterface != NULL)
      //{
        // return m_pcubeInterface->hold(pui);
      //}

      return NULL;

   }





   bool system::on_install()
   {

      try
      {
         xxdebug_box("system::on_install", "system::on_install", 0);
         if(!::application::on_install())
            return false;

      }
      catch(...)
      {

         return false;

      }


      try
      {

         if(!find_applications_to_cache())
            return false;

      }
      catch(...)
      {

         return false;

      }


      return true;

   }




   string system::get_host_location_url()
   {

      return "";

   }


   bool system::add_library(::core::library * plibrary)
   {

      m_libraryptra.add(plibrary);

      ::array < ::id > ida;

      plibrary->get_create_view_id_list(ida);

      for(int32_t i = 0; i < ida.get_count(); i++)
      {

         m_idmapCreateViewLibrary.set_at(ida[i], plibrary);

      }

      return true;

   }

   FT_Library & system::ftlibrary()
   {
      return m_ftlibrary;
   }


   void system::post_fork_uri(const char * pszUri, application_bias * pbiasCreate)
   {

      command()->add_fork_uri(pszUri, pbiasCreate);

      if(command()->m_varTopicQuery["locale"].array_get_count() > 0 && command()->m_varTopicQuery["locale"].stra().get_count_except_ci("_std") > 0)
      {
         ::root::session().set_locale(command()->m_varTopicQuery["locale"].stra()[0], ::action::source::user());
      }

      if(command()->m_varTopicQuery["schema"].array_get_count() > 0)
      {
         ::root::session().set_schema(command()->m_varTopicQuery["schema"].stra()[0], ::action::source::user());
      }

   }

#ifdef METROWIN

   bool system::GetWindowRect(LPRECT lprect)
      {

         Windows::Foundation::Rect rect;
         try
         {
            rect = m_posdata->m_pwindow->get_window_rect();
         }
         catch(...)
         {
            return false;
         }

         lprect->left      = (LONG) rect.X;
         lprect->top       = (LONG) rect.Y;
         lprect->right     = (LONG) (lprect->left + rect.Width);
         lprect->bottom    = (LONG) (lprect->top + rect.Height);


         return true;

      }
#endif


   bool system::is_system()
   {
      return true;
   }

   bool system::set_main_init_data(::base::main_init_data * pdata)
   {

      if(pdata != NULL)
      {
         if(!::application::set_main_init_data(pdata))
            return false;
      }

      if (pdata == NULL)
         return true;

      property_set set(this);

      var varFile;
      string strApp;

      set._008ParseCommandFork(pdata->m_vssCommandLine, varFile, strApp);

      if ((varFile.is_empty() && ((!set.has_property("app") && !directrix()->m_varTopicQuery.has_property("appid") && !set.has_property("show_platform"))
         || set["app"] == "bergedge" || directrix()->m_varTopicQuery["appid"] == "bergedge")) &&
         !(set.has_property("install") || set.has_property("uninstall")))
      {
         if(!set.has_property("show_platform") || set["show_platform"] == 1)
         {
            command()->add_line(" : show_platform=1");
         }
      }
      else
      {
         string strCommandLine = pdata->m_vssCommandLine;
         strCommandLine.trim();
         if(strCommandLine[0] == '\"')
         {
            strsize iFind = strCommandLine.find("\"", 1);
            strCommandLine = strCommandLine.Mid(iFind + 1);
         }
         else
         {
            strsize iFind = strCommandLine.find(" ", 1);
            strCommandLine = strCommandLine.Mid(iFind + 1);
         }
         command()->add_line(strCommandLine);
      }

      //if(!::application::set_main_init_data(pdata))
        // return false;

      return true;

   }


/*   sp(::command_thread) system::command_thread()
   {
	   return m_pcommandthread;
   }
   */

/*   ::system::system * system::get_cube()
   {

      return this;

   }
   */


/*   sp(::plane::session) system::get_session(index iEdge, application_bias * pbiasCreation)
   {
      sp(::plane::session) psession = NULL;
      if(m_pbergedgemap == NULL)
         return NULL;
      if(!m_pbergedgemap->Lookup(iEdge, psession))
      {
         psession = (create_application("application", "session", true, pbiasCreation));
         if(psession == NULL)
            return NULL;
         psession->m_iEdge = iEdge;
         m_pbergedgemap->set_at(iEdge, psession);
      }
      return  psession;
   }


   sp(platform::document) system::get_platform(index iEdge, application_bias * pbiasCreation)
   {
      sp(::plane::session) pbergedge = get_session(iEdge, pbiasCreation);
      return pbergedge->get_platform();
   }

   sp(nature::document) system::get_nature(index iEdge, application_bias * pbiasCreation)
   {
      sp(::plane::session) pbergedge = get_session(iEdge, pbiasCreation);
      return pbergedge->get_nature();
   }

   sp(::base::application) system::application_get(index iEdge, const char * pszType, const char * pszId, bool bCreate, bool bSynch, application_bias * pbiasCreate)
   {
      sp(::plane::session) pbergedge = get_session(iEdge, pbiasCreate);
      return pbergedge->application_get(pszType, pszId, bCreate, bSynch, pbiasCreate);
   }
   */

   void system::assert_valid() const
   {

      application::assert_valid();
      //::database::server::assert_valid();

   }


   void system::dump(dump_context & context) const
   {

      application::dump(context);
      //::database::server::dump(context);

   }




   int32_t system::main()
   {

      int iRet = ::core::system::main();

      return iRet;

   }


   spa(::plane::session) & system::planesessionptra()
   {

      return m_planesessionptra;

   }


} // namespace plane





uint32_t _thread_proc_start_core_system(void * p);



uint32_t _thread_proc_start_core_system(void * p)
{

   ::base::system * psystem = (::base::system *)p;

   ::plane::system * pplanesystem = dynamic_cast < ::plane::system * > (psystem);

   ::set_thread(pplanesystem);

   try
   {

      if(!pplanesystem->pre_run())
      {

         return pplanesystem->m_iReturnCode;

      }

   }
   catch(...)
   {

      return -1;

   }

   return pplanesystem->::core::system::main();

}


CLASS_DECL_CORE void __start_core_system(::base::system * psystem)
{

   ::create_thread(NULL,0,&_thread_proc_start_core_system,(LPVOID)psystem,0,0);

}
