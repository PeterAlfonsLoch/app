#include "framework.h"

#ifdef WINDOWS
#undef new
#include <GdiPlus.h>
#define new DEBUG_NEW
#endif

namespace plane
{


   system::system(::ca::application * papp) :
      m_mutexDelete(this),
      m_http(this),
      m_net(this)
   {

#ifdef METROWIN
      m_window                                  = nullptr;
      m_pmutexDc                                = NULL;
      m_pdc                                     = NULL;
#endif
      m_psystem                                 = this;
      set_app(this);


      if(papp == NULL)
      {

         oprop("parent_system") = (::ca::ca *) NULL;

      }
      else
      {

         oprop("parent_system") = papp->m_psystem;

      }


//      ::plane::system * psystemParent             = oprop("parent_system").ca2 < ::plane::system > ();


      m_file.m_psystem                          = this;
      ::plane::application::m_file.m_psystem    = this;
      m_dir.m_psystem                           = this;
      ::plane::application::m_dir.m_psystem     = this;

      m_bDoNotExitIfNoApplications              = false;


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


      if(::get_heap_mutex() == NULL)
      {

         ::set_heap_mutex(new mutex(this));

      }

      use_base_ca2_allocator();


      m_pfactory = new class factory(this);
      m_pfactory->set_app(this);

      m_pfactory->cloneable_large < ::ca::create_context > ();
      m_pfactory->cloneable_large < ::ca::application_bias > ();
      m_pfactory->cloneable_large < ::gen::command_line > ();
      m_pfactory->cloneable_large < ::manual_reset_event > ();
      m_pfactory->cloneable_large < ::mutex > ();
      m_pfactory->cloneable_large < ::event > ();


      m_net.set_app(this);
      m_file.set_app(this);
      m_stra.set_app(this);
      m_url.set_app(this);
      m_phtml = new ::html::html(this);
      m_pxml = new ::xml::xml(this);
      m_userset.set_app(this);
      m_service.set_app(this);
      m_install.set_app(this);
#ifndef METROWIN
      m_process.set_app(this);
#endif
      m_pdatetime = new class ::ca2::datetime(this);
      m_email.set_app(this);
      m_http.set_app(this);
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



      m_spfsdata(new ::fs::native(this));



      m_bInitApplication         = false;
      m_bInitApplicationResult   = FALSE;
      m_bProcessInitialize       = false;
      m_bProcessInitializeResult = false;

      m_bLibCharGuess            = false;
      m_puserstr                 = NULL;

      m_pcube                    = NULL;
      m_pwindowmap               = NULL;

      m_pparserfactory           = NULL;

      m_bLicense                 = false;

   }

   system::~system()
   {

#ifdef WINDOWS

      //m_gdiplusStartupOutput.NotificationUnhook(m_gdiplusHookToken);

      //Gdiplus::GdiplusShutdown(m_gdiplusToken);

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

   bool system::InitApplication()
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


      System.factory().creatable < ::ca2::log >(System.type_info < ::ca::log > (), 1);

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

      int error = FT_Init_FreeType( &m_ftlibrary );
      if ( error )
      {
         TRACE("an error occurred during Free Type library initialization");
         return false;
      }

      if(m_pmachineeventcentral == NULL)
      {

         m_pmachineeventcentral = new class machine_event_central(this);
         if(!m_pmachineeventcentral->initialize())
            return false;
         if(m_pmachineeventcentral->is_close_application())
            return false;

      }


      if(m_pparserfactory == NULL)
      {
      
         m_pparserfactory = new colorertake5::ParserFactory(this);

      }



      if(!::plane::application::initialize())
         return false;

      return true;
   }



   bool system::initialize1()
   {


      m_spfilehandler(new ::filehandler::handler(this));


      m_spfilesystem.create(this);
      m_spos.create(this);
      m_spdir.create(this);

      string strId;
      strId = m_strAppName;
      strId += gen::str::has_char(m_strAppId, ".");
      strId += gen::str::has_char(m_strBaseSupportId, ".");

      xxdebug_box("Going to start Log", "Just before initialize log", 0);

      // log starts here
      if(!initialize_log(strId))
      {
         xxdebug_box("Could not initialize log", "Failed to initialize log", 0);
         return FALSE;
      }

      if(!m_spdir->initialize())
         return false;

      m_spcrypt.create(this);

      if(!m_spcrypt.is_set())
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
      //      System.factory().cloneable_large < var >();
      System.factory().creatable < ::ca2::log >(System.type_info < ::ca::log > (), 1);

      m_puserstr = new ::user::str(this);
      if(m_puserstr == NULL)
         return false;

      if(!str().initialize())
         return false;

      if(!::planebase::application::initialize1())
         return false;

      try
      {
         find_applications_from_cache();
      }
      catch(...)
      {
      }

      return true;

   }


   bool system::find_applications_from_cache()
   {

      m_spfilehandler->m_sptree->remove_all();

      if(directrix().m_varTopicQuery.has_property("install"))
         return true;

      ex1::filesp file = get_file(System.dir().appdata("applibcache.bin"), ex1::file::type_binary | ex1::file::mode_read);

      if(file.is_null())
         return false;

      ex1::byte_input_stream is(file);

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

      return *m_pparserfactory;

   }


   ::exception::engine & system::eengine()
   {

      static ::exception::engine s_eengine(NULL);

      return s_eengine;

   }

   bool system::find_applications_to_cache()
   {

      /*      m_spfilehandler(new ::ca2::filehandler::handler(this));*/

      m_mapAppLibrary.remove_all();

      string strLibraryId;
      stringa straTitle;

      Application.dir().ls_pattern(System.dir().ca2module(), "*.*", NULL,& straTitle);

      for(int i = 0; i < straTitle.get_count(); i++)
      {

         strLibraryId = straTitle[i];

         if(gen::str::ends_eat_ci(strLibraryId, ".dll")
            || gen::str::ends_eat_ci(strLibraryId, ".so")
            || gen::str::ends_eat_ci(strLibraryId, ".dylib"))
         {

            map_application_library(strLibraryId);

         }

      }

      ex1::filesp file;

      try
      {

         file = get_file(System.dir().appdata("applibcache.bin"), ex1::file::defer_create_directory | ::ex1::file::type_binary | ex1::file::mode_create  | ::ex1::file::mode_write);

      }
      catch(base_exception &)
      {

         return false;

      }

      ex1::byte_output_stream os(file);

      os << m_mapAppLibrary;

      os << *m_spfilehandler.m_p;

      return true;

   }

   bool system::map_application_library(const char * pszLibrary)
   {

      ::ca2::library library(NULL);

      if(!library.open(this, pszLibrary))
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

      string strPrefix = strRoot;

      strPrefix.replace("-", "_");

      strPrefix.replace("/", "_");

      gen::str::begins_eat_ci(strLibrary, strPrefix);

      strRoot += strLibrary;

      strRoot += "/";

      for(int i = 0; i < stra.get_count(); i++)
      {

         m_mapAppLibrary.set_at(strRoot + stra[i], pszLibrary);

      }

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

      /*set_enum_name(var::type_null      , "null");
      set_enum_name(var::type_empty     , "is_empty");
      set_enum_name(var::type_string    , "string");
      set_enum_name(var::type_integer   , "integer");
      set_enum_name(var::type_ulong     , "ulong");
      set_enum_name(var::type_ca2       , "ca2");
      set_enum_name(var::type_bool      , "bool");
      set_enum_name(var::type_double    , "double");*/

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

      static DWORD dwStart = ::get_tick_count();

      ::plane::application::verb();

      if(directrix().m_varTopicQuery.has_property("install") && (get_tick_count() - dwStart) > (5 * 184 * 1000))
         return false;

      if(directrix().m_varTopicQuery.has_property("uninstall") && (get_tick_count() - dwStart) > (5 * 184 * 1000))
         return false;

      if(!m_bDoNotExitIfNoApplications)
      {

         ::ca::application_ptra appptra;

         appptra = this->appptra();

         for(int i = 0; i < appptra.get_size(); )
         {
            try
            {
               if(appptra[i]->is_bergedge() || appptra[i]->is_session() || appptra[i]->is_system() || appptra[i]->is_cube())
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
         if(m_spos.is_set())
         {
            m_spos.destroy();
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
         m_spos.destroy();
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
      str.Format("Could not alloc %s", info.name());
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
         pbergedge = dynamic_cast < ::plane::session * > (create_application("application", "session", true, pbiasCreation));
         if(pbergedge == NULL)
            return NULL;
         pbergedge->m_iEdge = iEdge;
         m_pbergedgemap->set_at(iEdge, pbergedge);
      }
      return pbergedge;
   }


   ::ca::application * system::application_get(index iEdge, const char * pszType, const char * pszId, bool bCreate, bool bSynch, ::ca::application_bias * pbiasCreate)
   {
      ::plane::session * psession = get_session(iEdge, pbiasCreate);
      return psession->application_get(pszType, pszId, bCreate, bSynch, pbiasCreate);
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

   ::sockets::net & system::net()
   {
      return m_net;
   }

   ::ca2::stra & system::stra()
   {
      return m_stra;
   }

   ::html::html & system::html()
   {
      return *m_phtml;
   }

   ::xml::xml & system::xml()
   {
      return *m_pxml;
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

   ::ca::os & system::os()
   {
      return m_spos;
   }

#ifndef METROWIN

   ::ca2::process & system::process()
   {
      return m_process;
   }

#endif

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

   void system::appa_set_schema(const char * pszStyle, bool bUser)
   {
      for(int i = 0; i < appptra().get_size(); i++)
      {
         ca2::application * papp = dynamic_cast < ca2::application * > (appptra()[i]);
         papp->set_schema(pszStyle, bUser);
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
         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_global_id_mutex_name(pszAppName, pszId));
         ::mutex * pmutex = mutex::open_mutex(this, get_global_id_mutex_name(pszAppName, pszId));
         if(pmutex == NULL)
         {
            
            string strApp = pszAppName;
            strApp += "app.exe";
            
            string strParameters;
            strParameters = ": global_mutex_id=\"" + string(pszId) + "\"";

#if defined(WINDOWSEX) || defined(LINUX) || defined(MACOS)

            simple_shell_launcher launcher(::ca::null(), NULL, dir().path(get_module_folder(), strApp), strParameters, NULL, SW_SHOW);

            launcher.execute();

#else

            throw todo(get_app());

#endif

            return false;
         }
         else
         {
            delete pmutex;
         }
         return true;
      }
      else
      {
         //HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_global_mutex_name(pszAppName));
         ::mutex * pmutex = mutex::open_mutex(this, get_global_mutex_name(pszAppName));
         if(pmutex == NULL)
         {
            string strApp = pszAppName;
            strApp += "app.exe";

#ifdef METROWIN

            throw todo(get_app());

#else

            simple_shell_launcher launcher(::ca::null(), NULL, dir().path(get_module_folder(), strApp), NULL, NULL, SW_SHOW);

            launcher.execute();

#endif

            return false;
         }
         else
         {
            //::CloseHandle(h);
            delete pmutex;
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
         //HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_local_id_mutex_name(pszAppName, strId));
         ::mutex * pmutex = mutex::open_mutex(this, get_local_id_mutex_name(pszAppName, strId));
         if(pmutex == NULL)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName + " local_mutex_id=\"" + strId + "\"";

#ifdef METROWIN

            throw todo(get_app());

#else

            simple_shell_launcher launcher(::ca::null(), NULL, dir().path(get_ca2_module_folder(), strApp), strParameters, NULL, SW_SHOW);

            launcher.execute();

#endif

            return false;
         }
         else
         {
            //::CloseHandle(h);
            delete pmutex;
         }
         return true;
      }
      else
      {
         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_local_mutex_name(pszAppName));
         ::mutex * pmutex = mutex::open_mutex(this, get_local_mutex_name(pszAppName));
         if(pmutex == NULL)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName;

#ifdef METROWIN

            throw todo(get_app());

#else

            simple_shell_launcher launcher(::ca::null(), NULL, dir().path(get_ca2_module_folder(), strApp), strParameters, NULL, SW_SHOW);

            launcher.execute();

#endif

            return false;
         }
         else
         {
            //::CloseHandle(h);
            delete pmutex;
         }
         return true;
      }
   }

   bool system::initialize_log(const char * pszId)
   {
      if(m_plog != NULL)
         return true;
      m_plog = dynamic_cast < class ::ca2::log * > (alloc(this, System.type_info < class ::ca::log > ()));
      m_plog->set_extended_log();
      m_plog->set_app(this);
      if(!m_plog->initialize(pszId))
      {
         gen::del(m_plog);
         return false;
      }
      //      gen::trace_v = &gen::system_log_trace_v;
      return true;
   }

   bool system::finalize()
   {

      try
      {
         if(m_spcrypt.is_set())
         {
            m_spcrypt.destroy();
         }
      }
      catch(...)
      {
      }

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
#ifdef DEBUG
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
#ifdef DEBUG
#ifndef ___NO_DEBUG_CRT
      // we remove WM_QUIT because if it is in the queue then the message box
      // won't display
#ifdef WINDOWSEX
      MSG msg;
      bool bQuit = PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE) != FALSE;
      va_list list = NULL;
#elif defined(METROWIN)
      va_list list = NULL;
      //throw todo(get_app());
#else
      va_list list = {};
#endif
      bool bResult = ________ca2_votagus_logging_Report(_CRT_ASSERT, lpszFileName, iLine, NULL, NULL, list) != 0;
#ifdef WINDOWSEX
      if (bQuit)
         PostQuitMessage((int)msg.wParam);
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

   void system::on_allocation_error(::ca::application * papp, ::ca::type_info & info)
   {
      UNREFERENCED_PARAMETER(papp);
      simple_message_box(NULL, MB_ICONINFORMATION, "Implement \"%s\" allocation\n", info.name());
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
         post.clear();
         headers.clear();
         file().del(filename);
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
      return m_spcrypt;
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

   ::ca4::copydesk & system::copydesk()
   {
      return m_spcopydesk;
   }

   void system::http_config_proxy(const char * pszUrl, ::sockets::http_tunnel * ptunnel)
   {
#ifdef METROWIN
      ptunnel->m_bDirect = true;
#else
      http().config_proxy(pszUrl, ptunnel);
#endif
   }

   bool system::base_support()
   {
      return true;
   }

   index system::get_new_bergedge(::ca::application_bias * pbiasCreation)
   {
      index iNewEdge = m_iNewEdge;
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
      m_ptwf = dynamic_cast < ::ca::window_draw * > (alloc(this, System.type_info < ::ca::window_draw > ()));
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


   ::ca::application * system::get_new_app(::ca::application * pappNewApplicationParent, const char * pszType, const char * pszAppId)
   {

      string strId(pszAppId);

      string strApplicationId;

      if(strId == "app/ca2/bergedge")
      {

         strApplicationId = "bergedge";

      }
      else if(strId == "app/ca2/cube")
      {

         strApplicationId = "cube";

      }
      else
      {

         strApplicationId = strId;

      }


      string strBuildNumber = System.command().m_varTopicQuery["build_number"];

      if(strBuildNumber.is_empty())
      {

         strBuildNumber = "latest";

      }


#ifndef METROWIN

      if(!System.directrix().m_varTopicQuery.has_property("install")
         && !System.directrix().m_varTopicQuery.has_property("uninstall")
         && strId.has_char()
         && !install().is(NULL, strBuildNumber, pszType, strApplicationId, m_strLocale, m_strSchema))
      {

         throw not_installed(get_app(), NULL, strBuildNumber, pszType, strApplicationId, m_strLocale, m_strSchema);

      }

#endif

      ca2::library library(NULL);

      string strLibrary = m_mapAppLibrary[pszAppId];

      ::ca::application * papp = NULL;

      if(!library.open(pappNewApplicationParent, strLibrary, false))
         return NULL;

      papp = library.get_new_app(pszAppId);

      if(papp == NULL)
         return NULL;

      ::radix::application * pradixapp = dynamic_cast < ::radix::application * > (papp);

      pradixapp->m_strAppId = pszAppId;

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
         || (set["app"] == "session" && !set.has_property("session_start")))) &&
         !(set.has_property("install") || set.has_property("uninstall")))
      {
         if(!set.has_property("show_platform") || set["show_platform"] == 1)
         {
            command().add_line(" : show_platform=1");
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
         command().add_line(strCommandLine);
      }

      if(!::plane::application::set_main_init_data(pdata))
         return false;

      return true;

   }

   ::ca::type_info & system::get_type_info(const ::std_type_info & info)
   {

      ::ca::type_info & typeinfo = m_typemap[info.name()];

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

   index system::get_best_intersection_monitor(LPRECT lprect)
   {

      count c = get_monitor_count();

      rect rectIntersect;
      rect rectMonitor;
      int64_t  iBestArea = 0;
      index    iBestAreaIndex = -1;
      int64_t iArea;

      for(index i = 0; i < c; i++)
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


   bool system::on_install()
   {

      try
      {

         if(!plane::application::on_install())
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


   string system::get_fontopus_server(const char * pszUrl, ::ca::application * papp, int iRetry)
   {

      string strFontopusServer;

      if(m_mapFontopusServer.Lookup(pszUrl, strFontopusServer) && strFontopusServer.has_char())
      {
         return strFontopusServer;
      }

retry:

      if(iRetry < 0)
         return ""; // should not retry or lookup is valid and strFontopusServer is really empty

      string strGetFontopus("http://" + System.url().get_server(pszUrl) + "/get_fontopus");
      try
      {
         gen::property_set post;
         gen::property_set headers;
         gen::property_set set;
         set["disable_ca2_sessid"] = true;
         set["app"] = papp;
         Application.http().get(strGetFontopus, strFontopusServer, post, headers, set, NULL, NULL, NULL, NULL);
      }
      catch(...)
      {
      }

      m_mapFontopusServer.set_at(pszUrl, strFontopusServer);

      iRetry--;

      if(strFontopusServer.is_empty())
         goto retry;

      return strFontopusServer;

   }

   void system::get_cursor_pos(LPPOINT lppoint)
   {
#ifdef METROWIN
      Windows::Foundation::Point p;
      p = m_pwindow->get_cursor_pos();
      lppoint->x = p.X;
      lppoint->y = p.Y;
#else
      ::GetCursorPos(lppoint);
#endif
   }


   string system::get_host_location_url()
   {

      return "";

   }


   bool system::add_library(::ca2::library * plibrary)
   {

      m_libraryptra.add(plibrary);

      ::raw_array < ::id > ida;

      plibrary->get_create_view_id_list(ida);

      for(int i = 0; i < ida.get_count(); i++)
      {

         m_idmapCreateViewLibrary.set_at(ida[i], plibrary);

      }

      return true;

   }

   FT_Library & system::ftlibrary()
   {
      return m_ftlibrary;
   }


   void system::post_fork_uri(const char * pszUri, ::ca::application_bias * pbiasCreate)
   {

      command().add_fork_uri(pszUri, pbiasCreate);

      if(command().m_varTopicQuery["locale"].has_char()
         && command().m_varTopicQuery["locale"] != "_std")
      {
         set_locale(command().m_varTopicQuery["locale"], true);
      }

      if(command().m_varTopicQuery["schema"].has_char())
      {
         set_schema(command().m_varTopicQuery["schema"], true);
      }

   }

#ifdef METROWIN

      bool system::get_window_rect(LPRECT lprect)
      {

         Windows::Foundation::Rect rect;
         try
         {
            rect = m_pwindow->get_window_rect();
         }
         catch(...)
         {
            return false;
         }
         
         lprect->left = rect.X;
         lprect->top = rect.Y;
         lprect->right = lprect->left + rect.Width;
         lprect->bottom = lprect->top + rect.Height;


         return true;

      }


#endif

} // namespace plane



