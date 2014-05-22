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

      m_psystem                                 = this;
      set_app(this);


      if(papp == NULL)
      {

         oprop("parent_system") = (sp(element)) NULL;

      }
      else
      {

         oprop("parent_system") = papp->m_pplaneapp->m_psystem;

      }

      m_ftlibrary = NULL;


      ::application::m_file.set_app(this);
      ::application::m_dir.set_app(this);

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






      m_net.set_app(this);
      m_stra.set_app(this);
//      m_url.set_app(this);
      m_userset.set_app(this);
      m_service.set_app(this);
#ifndef METROWIN
      m_processsection.set_app(this);
#endif
      m_pdatetime = new class ::datetime::departament(this);
//      m_email.set_app(this);

      m_pmachineeventcentral     = NULL;




      m_spfsdata = new ::fs::native(this);



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


//      System.factory().creatable < ::core::log >(System.type_info < ::core::log > (), 1);

/*      if(!::application::process_initialize())
      {
         return false;
      }*/


      if(!set_main_init_data(m_pinitmaindata))
         return false;

      m_spportforward.create(allocer());

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

      if(m_pmachineeventcentral == NULL)
      {

         m_pmachineeventcentral = new ::machine_event_central(this);
         if(!m_pmachineeventcentral->initialize())
            return false;
         if(m_pmachineeventcentral->is_close_application())
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



      enum_display_monitors();

      m_visual.construct(this);

      if(!m_visual.initialize1())
         return false;



      m_spfilehandler = new ::filehandler::handler(this);




      if(!::application::initialize1())
         return false;


      //if(Session.fontopus()->create_system_user("system") == NULL)
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


      return true;

   }


   bool system::find_applications_from_cache()
   {

      m_spfilehandler->m_sptree->remove_all();

      if(directrix()->m_varTopicQuery.has_property("install"))
         return true;

      ::file::binary_buffer_sp file = m_file.get_file(System.dir().appdata("applibcache.bin"), ::file::type_binary | ::file::mode_read);

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

      Application.dir().ls_pattern(System.dir().ca2module(), "*.*", NULL,& straTitle);

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

         file = m_file.get_file(System.dir().appdata("applibcache.bin"), ::file::defer_create_directory | ::file::type_binary | ::file::mode_create  | ::file::mode_write);

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

         appptra = this->appptra();

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
            return false;

         if(appptra.get_size() == 1 && appptra.contains(this))
            return false;

      }

      return true;
   }


   int32_t system::exit_instance()
   {

      __wait_threading_count(::millis((1984 + 1977) * 8));

      try
      {
         if(m_ptwf != NULL)
         {

            m_ptwf->m_bRun = false;
            if(m_ptwf->m_pimpl != NULL)
            {
               m_ptwf->m_pimpl->m_bRun = false;
            }
         }
      }
      catch(...)
      {
      }


      for(int i = 0; i < m_serviceptra.get_size(); i++)
      {
         try
         {
            m_serviceptra(i)->Stop(0);
         }
         catch(...)
         {
         }
      }

      try
      {
         if(m_ptwf != NULL)
         {
            m_ptwf->twf_stop();
            m_ptwf = NULL;
         }
      }
      catch(...)
      {
      }

      for(int i = 0; i < m_serviceptra.get_size(); i++)
      {
         try
         {
            m_serviceptra(i)->Stop((1984 + 1977) * 2);
         }
         catch(...)
         {
         }
      }

      m_serviceptra.remove_all();

      try
      {
         if(m_pfactory != NULL)
         {

            m_pfactory->enable_simple_factory_request(false);

            m_pfactory.release();

         }

      }
      catch(...)
      {
         TRACE("system::exit_instance: Potentially catastrophical error : error disabling simple factory request");
      }



      int32_t iRet = 0;

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


      m_plog.release();

      m_typemap.remove_all();

      m_typemap.release();

      try
      {

         iRet = ::core::system::exit_instance();

      }
      catch (...)
      {

      }


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


   sp(::base_session) system::query_session(index iEdge)
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


   sp(::base::application) system::application_get(index iEdge, const char * pszType, const char * pszId, bool bCreate, bool bSynch, application_bias * pbiasCreate)
   {
      sp(::plane::session) psession = get_session(iEdge, pbiasCreate);
      return psession->application_get(pszType, pszId, bCreate, bSynch, pbiasCreate);
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


   /*   ::core::filehandler::handler & system::filehandler()
   {
   return *m_spfilehandler;
   }*/

   void system::register_bergedge_application(sp(::base::application) papp)
   {

      retry_single_lock rsl(&m_mutex, millis(84), millis(84));

      appptra().add_unique(papp->m_pplaneapp);

      if(System.is_installing() || System.is_uninstalling())
         m_bDoNotExitIfNoApplications = false;
      else if(!papp->m_pplaneapp->is_session()
      && !papp->m_pplaneapp->is_system()
      && !papp->m_pplaneapp->is_serviceable())
      {

            m_bDoNotExitIfNoApplications = false;

      }

   }

   void system::unregister_bergedge_application(sp(::base::application) papp)
   {

      retry_single_lock rsl(&m_mutex, millis(84), millis(84));

      appptra().remove(papp->m_pplaneapp);

   }



   bool system::finalize()
   {

      __wait_threading_count_except(this, ::millis((1984 + 1977) * 8));

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


   string system::matter_as_string(sp(::base::application) papp, const char * pszMatter, const char * pszMatter2)
   {
      var varQuery;
      varQuery["disable_ca2_sessid"] = true;
      return file().as_string(dir_matter(papp, pszMatter, pszMatter2), varQuery, papp);
   }

   string system::dir_matter(sp(::base::application) papp, const char * pszMatter, const char * pszMatter2)
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

   string system::file_as_string(sp(::base::application) papp, const char * pszPath)
   {
      return file().as_string(pszPath, papp);
   }

   string system::dir_path(const char * psz1, const char * psz2, const char * psz3)
   {
      return dir().path(psz1, strlen(psz1), psz2, strlen(psz2), psz3, strlen(psz3));
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

   /*void system::register_delete(sp(element) plistened, sp(element) plistener)
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

   void system::unregister_delete(sp(element) plistened, sp(element) plistener)
   {
      if(plistened == plistener)
         return;
      if(plistened == NULL)
         return;
      if(plistener == NULL)
         return;
      plistener->listenedptra().remove(plistened);
      plistened->listenerptra().remove(plistener);
   }*/

   int32_t system::__ca2_logging_report(
      int32_t iReportType,
      const char * pszFileName,
      int32_t iLineNumber,
      const char * pszModuleName,
      const char * pszFormat, va_list list)
   {
      if(m_plog == NULL || !m_plog->m_bExtendedLog)
      {
         return ::core::SimpleDebugReport(iReportType, pszFileName, iLineNumber, pszModuleName, pszFormat, list);
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

         ::MessageBox(get_splash(), "An error that prevents the application from starting has occurred.\r\n\r\nPlease run app-removal.exe and restart the application, or contact the administrator.", "Startup Error", MB_ICONEXCLAMATION);

#ifdef WINDOWS

         ::ExitProcess(-17);

#endif

         return;

      }

      psession->request_create(pcreatecontext);

   }


   void system::open_by_file_extension(index iEdge, const char * pszFileName)
   {
      sp(::plane::session) psession = get_session(iEdge);
      psession->open_by_file_extension(pszFileName);
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

      str = Application.file().as_string(filename);

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


   sp(::base::application) system::get_new_app(sp(::base::application) pappNewApplicationParent, const char * pszType, const char * pszAppId)
   {

      string strId(pszAppId);

      string strApplicationId;

      if(strId == "app/core/bergedge")
      {

         strApplicationId = "bergedge";

      }
      else if(strId == "app/core/system")
      {

         strApplicationId = "system";

      }
      else
      {

         strApplicationId = strId;

      }


      string strBuildNumber = System.command()->m_varTopicQuery["build_number"];

      if(strBuildNumber.is_empty())
      {

         strBuildNumber = "latest";

      }

#ifdef CUBE

      // Criar novo meio de instalação

#elif !defined(METROWIN)

      if(!System.directrix()->m_varTopicQuery.has_property("install")
         && !System.directrix()->m_varTopicQuery.has_property("uninstall")
         && strId.has_char()
         && !install().is(NULL, strBuildNumber, pszType, strApplicationId, m_strLocale, m_strSchema))
      {

         throw not_installed(get_app(), NULL, strBuildNumber, pszType, strApplicationId, m_strLocale, m_strSchema);

      }

#endif

      ::core::library library(pappNewApplicationParent, NULL);

#ifdef CUBE

      string strLibrary = pszAppId;

      strLibrary.replace("/", "_");
      strLibrary.replace("-", "_");


#else

      string strLibrary = m_mapAppLibrary[pszAppId];

      if (strLibrary.is_empty())
      {

         throw not_installed(get_app(), NULL, strBuildNumber, pszType, strApplicationId, m_strLocale, m_strSchema);

      }

#endif

      sp(::base::application) papp = NULL;

      if(!library.open(strLibrary, false))
         return NULL;

      papp = library.get_new_app(pszAppId);

      if(papp == NULL)
         return NULL;

      sp(::base::application) pgenapp = (papp);

      pgenapp->m_pplaneapp->m_strAppId = pszAppId;

      pgenapp->m_pbasesystem = this;

      pgenapp->m_pplaneapp->m_psystem = this;

#ifdef WINDOWS

      pgenapp->m_hinstance = m_hinstance;

#endif

      pgenapp->::base::application::construct();

      pgenapp->construct();

      return papp;

   }

/*
   bool system::set_main_init_data(::core::main_init_data * pdata)
   {

      if(pdata == NULL)
      {
         if(!::application::set_main_init_data(pdata))
            return false;
         return true;
      }

      property_set set(this);

      var varFile;
      string strApp;

      set._008ParseCommandFork(pdata->m_vssCommandLine, varFile, strApp);

      if((varFile.is_empty() && ((!set.has_property("app") && !set.has_property("show_platform"))
         || (set["app"] == "session" && !set.has_property("session_start")))) &&
         !(set.has_property("install") || set.has_property("uninstall")))
      {
         if(!set.has_property("show_platform") || set["show_platform"] == 1)
         {
            command()->add_line(" : show_platform=1");
            m_bDoNotExitIfNoApplications = true;
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

      if(!::application::set_main_init_data(pdata))
         return false;

      return true;

   }*/






   //////////////////////////////////////////////////////////////////////////////////////////////////
   // System/System
   //
   sp(::user::object) system::place_hold(sp(::user::interaction) pui)
   {


      //if(m_pcubeInterface != NULL)
      //{
        // return m_pcubeInterface->hold(pui);
      //}

      return NULL;

   }

   void system::enum_display_monitors()
   {

#ifdef WINDOWSEX

      m_monitorinfoa.remove_all();

      ::EnumDisplayMonitors(NULL, NULL, &system::monitor_enum_proc, (LPARAM) ( dynamic_cast < ::plane::system * > (this)));

#else

      // todo
//      m_monitorinfoa.remove_all();


#endif

   }

#ifdef WINDOWSEX
   BOOL CALLBACK system::monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
   {
      ::plane::system * psystem = (::plane::system *) dwData;
      psystem->monitor_enum(hmonitor, hdcMonitor, lprcMonitor);
      return TRUE; // to enumerate all
   }

   void system::monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor)
   {

      UNREFERENCED_PARAMETER(hdcMonitor);
      UNREFERENCED_PARAMETER(lprcMonitor);

      m_monitorinfoa.allocate(m_monitorinfoa.get_size() + 1);

      ZERO(m_monitorinfoa.last_element());

      m_monitorinfoa.last_element().cbSize = sizeof(MONITORINFO);

      ::GetMonitorInfo(hmonitor, &m_monitorinfoa.last_element());

      MONITORINFO mi = m_monitorinfoa.last_element();

      TRACE0("application::monitor_enum\n");
      TRACE("upper_bound %d\n", m_monitorinfoa.get_upper_bound());
      TRACE("rcMonitor(left, top, right, bottom) %d, %d, %d, %d\n", mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right, mi.rcMonitor.bottom);
      TRACE("rcWork(left, top, right, bottom) %d, %d, %d, %d\n", mi.rcWork.left, mi.rcWork.top, mi.rcWork.right, mi.rcWork.bottom);

   }


#endif



   ::count system::get_monitor_count()
   {

#ifdef WINDOWSEX

      return m_monitorinfoa.get_count();

#else

      return 1;

#endif

   }

   bool system::get_monitor_rect(index i, LPRECT lprect)
   {


#ifdef WINDOWSEX

      if(i < 0 || i >= get_monitor_count())
         return false;

      *lprect = m_monitorinfoa[i].rcMonitor;

#elif defined(METROWIN)

      return System.GetWindowRect(lprect);

#elif defined(LINUX)

      xdisplay  d;

      if(!d.open(NULL))
         return false;

      lprect->left = 0;
      lprect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdisplay));
      lprect->top = 0;
      lprect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d.m_pdisplay));

#elif defined(APPLEOS)

      if(i < 0 || i >= get_monitor_count())
         return false;

      GetMainScreenRect(lprect);

#else

      throw todo(get_app());

      ::GetWindowRect(::GetDesktopWindow(), lprect);

#endif

      return true;

   }


   index system::get_best_intersection_monitor(LPRECT lprect)
   {

      ::count ca   = get_monitor_count();

      rect        rectIntersect;
      rect        rectMonitor;
      int64_t     iBestArea = 0;
      index       iBestAreaIndex = -1;
      int64_t     iArea;

      for(index i = 0; i < ca; i++)
      {
         get_monitor_rect(i, rectMonitor);
         if(rectIntersect.intersect(rectMonitor, lprect))
         {
            iArea = rectIntersect.area();
            if(iArea > iBestArea)
            {
               iBestAreaIndex = i;
               iBestArea = iArea;
            }
         }
      }

      if(iBestAreaIndex >= 0)
         return iBestAreaIndex;
      else if(get_monitor_count() <= 0)
         return -1;
      else
         return 0;

   }


   ::count system::get_desk_monitor_count()
   {


      return 0;

   }

   bool system::get_desk_monitor_rect(index i, LPRECT lprect)
   {


      return false;

   }

/*
sp(::command_thread) system::command_thread()
   {
      return m_pcommandthread;
   }
*/

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



   void system::get_cursor_pos(LPPOINT lppoint)
   {
#ifdef METROWIN
      Windows::Foundation::Point p;
      p = m_posdata->m_pwindow->get_cursor_pos();
      lppoint->x = (LONG) p.X;
      lppoint->y = (LONG) p.Y;
#else
      ::GetCursorPos(lppoint);
#endif
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
         set_locale(command()->m_varTopicQuery["locale"].stra()[0], ::action::source::user());
      }

      if(command()->m_varTopicQuery["schema"].array_get_count() > 0)
      {
         set_schema(command()->m_varTopicQuery["schema"].stra()[0], ::action::source::user());
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




   sp(::platform::document) system::get_platform(index iEdge, application_bias * pbiasCreation)
   {
      sp(::plane::session) pbergedge = get_session(iEdge, pbiasCreation);
      return pbergedge->get_platform();
   }

   sp(::nature::document) system::get_nature(index iEdge, application_bias * pbiasCreation)
   {
      sp(::plane::session) pbergedge = get_session(iEdge, pbiasCreation);
      return pbergedge->get_nature();
   }


   bool system::is_system()
   {
      return true;
   }

   bool system::set_main_init_data(::core::main_init_data * pdata)
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

      if ((varFile.is_empty() && ((!set.has_property("app") && !directrix()->m_varTopicQuery.has_property("cgcl_app") && !set.has_property("show_platform"))
         || set["app"] == "bergedge" || directrix()->m_varTopicQuery["cgcl_app"] == "bergedge")) &&
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
   sp(::plane::session) system::query_bergedge(index iEdge)
   {
      sp(::plane::session) psession = NULL;
      if(m_pbergedgemap == NULL)
         return NULL;
      if(!m_pbergedgemap->Lookup(iEdge, psession))
      {
         return NULL;
      }
      return psession;
   }


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


   ::exception::engine & system::eengine()
   {

      static ::exception::engine s_eengine(NULL);

      return s_eengine;

   }



   int32_t system::main()
   {

      int iRet = ::core::system::main();

      return iRet;

   }


} // namespace plane





uint32_t _thread_proc_start_core_system(void * p);



uint32_t _thread_proc_start_core_system(void * p)
{

   ::base::system * psystem = (::base::system *)p;

   ::plane::system * pplanesystem = dynamic_cast <::plane::system *> (psystem);

   return pplanesystem->::core::system::main();

}


CLASS_DECL_CORE void __start_core_system(::base::system * psystem)
{

   ::create_thread(NULL,0,&_thread_proc_start_core_system,(LPVOID)psystem,0,0);

}
