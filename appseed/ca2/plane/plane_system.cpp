#include "framework.h"

#ifdef WINDOWS
#undef new
#include <GdiPlus.h>
#define new DEBUG_NEW
#endif


namespace plane
{


   system::system(sp(::ca::application) papp) :
      m_mutexDelete(this),
      m_http(this),
      m_net(this),
      m_mutex(this),
      m_processsection(this),
      m_visual(this)
   {

#ifdef METROWIN
      m_window                                  = nullptr;
      m_pmutexDc                                = ::null();
      m_pdc                                     = ::null();
#endif
      m_psystem                                 = this;
      set_app(this);


      if(papp == ::null())
      {

         oprop("parent_system") = (sp(::ca::ca)) ::null();

      }
      else
      {

         oprop("parent_system") = papp->m_psystem;

      }


      ::plane::application::m_file.set_app(this);
      ::plane::application::m_dir.set_app(this);

      m_bDoNotExitIfNoApplications              = true;

      string strId;
      //strId = m_strAppName;
      //strId += ::ca::str::has_char(m_strAppId, ".");
      //strId += ::ca::str::has_char(m_strBaseSupportId, ".");


      strId = "ca2log";

      xxdebug_box("Going to start Log", "Just before initialize log", 0);

      // log starts here
      if(!initialize_log(strId))
      {
         xxdebug_box("Could not initialize log", "Failed to initialize log", 0);
         throw "failed to initialize log";
      }


/*
      if(psystemParent == ::null())
      {

         m_peengine                                = new ::exception::engine(this);

      }
      else
      {

         m_peengine                                = psystemParent->m_peengine;

      }
*/


      if(::get_heap_mutex() == ::null())
      {

         ::set_heap_mutex(new mutex(this));

      }

      use_base_ca2_allocator();


      m_pfactory = new class ::ca::factory(this);
      m_pfactory->set_app(this);

      m_pfactory->cloneable_large < ::ca::create_context > ();
      m_pfactory->cloneable_large < ::ca::application_bias > ();
      m_pfactory->cloneable_large < ::ca::command_line > ();
      m_pfactory->cloneable_large < ::manual_reset_event > ();
      m_pfactory->cloneable_large < ::mutex > ();
      m_pfactory->cloneable_large < ::event > ();


      m_net.set_app(this);
      m_file.set_app(this);
      m_stra.set_app(this);
      m_url.set_app(this);
      m_userset.set_app(this);
      m_service.set_app(this);
      m_install.set_app(this);
#ifndef METROWIN
      m_processsection.set_app(this);
#endif
      m_pdatetime = new class ::ca::datetime(this);
      m_email.set_app(this);
      m_http.set_app(this);
      m_compress.set_app(this);
      m_file.set_app(this);

      m_pmachineeventcentral     = ::null();
      //m_pfactory                 = ::null();




      m_spfsdata = new ::fs::native(this);



      m_bInitApplication         = false;
      m_bInitApplicationResult   = FALSE;
      m_bProcessInitialize       = false;
      m_bProcessInitializeResult = false;

      m_bLibCharGuess            = false;
      m_puserstr                 = ::null();

      m_pparserfactory           = ::null();

      m_bLicense                 = false;

      m_prunstartinstaller       = ::null();
      m_bLicense                 = false;
      m_strAppName               = "system";
      m_strInstallToken          = "system";


   }


   system::~system()
   {

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


      if(!::plane::application::process_initialize())
         return false;


      ::ca::profiler::initialize();


//      System.factory().creatable < ::ca::log >(System.type_info < ::ca::log > (), 1);

/*      if(!::plane::application::process_initialize())
      {
         return false;
      }*/

      m_spfile.create(allocer());
      m_spdir.create(allocer());

      m_pxml = canew(::xml::xml(this));

      m_pxml->construct(this);

      if(!m_pxml->initialize1())
         return false;

      if(!m_pxml->initialize())
         return false;

      if(!m_spdir->initialize())
         return false;

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

      if(m_pmachineeventcentral == ::null())
      {

         m_pmachineeventcentral = new ::machine_event_central(this);
         if(!m_pmachineeventcentral->initialize())
            return false;
         if(m_pmachineeventcentral->is_close_application())
            return false;

      }

#ifndef MACOS

      if(m_pparserfactory == ::null())
      {



      }

#endif


      if(!::plane::application::initialize())
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


      //m_spfilesystem.create(allocer());
      m_spos.create(allocer());

      m_spcrypt.create(allocer());

      if(!m_spcrypt.is_set())
         return false;


      if(!::plane::application::initialize1())
         return false;


      if(fontopus()->create_system_user("system") == ::null())
         return false;

/*      System.factory().cloneable_large < ::ca::font >();
      System.factory().cloneable_large < ::ca::brush >();
      System.factory().cloneable_large < ::ca::pen_sp >();
      System.factory().cloneable_large < ::ca::bitmap_sp >();
      System.factory().cloneable_large < ::ca::palette_sp >();
      System.factory().cloneable_large < ::ca::region_sp >();*/
      //      System.factory().cloneable_large < var >();
//      System.factory().creatable < ::ca::log >(System.type_info < ::ca::log > (), 1);

      m_puserstr = new ::user::str(this);
      if(m_puserstr == ::null())
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

      ::ca::filesp file = m_file.get_file(System.dir().appdata("applibcache.bin"), ::ca::file::type_binary | ::ca::file::mode_read);

      if(file.is_null())
         return false;

      ::ca::byte_input_stream is(file);

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

      if(m_pparserfactory == ::null())
      {

         m_pparserfactory = new colorertake5::ParserFactory(this);

      }

      return *m_pparserfactory;

   }


   ::exception::engine & system::eengine()
   {

      static ::exception::engine s_eengine(::null());

      return s_eengine;

   }

   bool system::find_applications_to_cache()
   {

      /*      m_spfilehandler(new ::ca::filehandler::handler(this));*/

      m_mapAppLibrary.remove_all();

      string strLibraryId;
      stringa straTitle;

      Application.dir().ls_pattern(System.dir().ca2module(), "*.*", ::null(),& straTitle);

      for(int32_t i = 0; i < straTitle.get_count(); i++)
      {

         strLibraryId = straTitle[i];

         if(::ca::str::ends_eat_ci(strLibraryId, ".dll")
            || ::ca::str::ends_eat_ci(strLibraryId, ".so")
            || ::ca::str::ends_eat_ci(strLibraryId, ".dylib"))
         {

            map_application_library(strLibraryId);

         }

      }

      ::ca::filesp file;

      try
      {

         file = m_file.get_file(System.dir().appdata("applibcache.bin"), ::ca::file::defer_create_directory | ::ca::file::type_binary | ::ca::file::mode_create  | ::ca::file::mode_write);

      }
      catch(base_exception &)
      {

         return false;

      }

      ::ca::byte_output_stream os(file);

      os << m_mapAppLibrary;

      os << *m_spfilehandler.m_p;

      return true;

   }

   bool system::map_application_library(const char * pszLibrary)
   {

      ::ca::library library(::null());

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

#ifdef LINUX

      if(strLibrary == "libca2")
      {

         strLibrary = "ca2";

      }
      else if(!::ca::str::begins_eat(strLibrary, "libca2"))
      {

         ::ca::str::begins_eat(strLibrary, "lib");

      }

#endif

      string strPrefix = strRoot;

      strPrefix.replace("-", "_");

      strPrefix.replace("/", "_");

      ::ca::str::begins_eat_ci(strLibrary, strPrefix);

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

      if(!::plane::application::initialize3())
         return false;

      if(m_phistory == ::null())
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
      set_enum_name(var::type_int32   , "integer");
      set_enum_name(var::type_uint32     , "ulong");
      set_enum_name(var::type_ca2       , "ca");
      set_enum_name(var::type_bool      , "bool");
      set_enum_name(var::type_double    , "double");*/

      if(!::plane::application::initialize_instance())
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

      ::plane::application::verb();

      if(directrix()->m_varTopicQuery.has_property("install") && (get_tick_count() - dwStart) > (5 * 184 * 1000))
         return false;

      if(directrix()->m_varTopicQuery.has_property("uninstall") && (get_tick_count() - dwStart) > (5 * 184 * 1000))
         return false;

      if(!m_bDoNotExitIfNoApplications)
      {

         ::ca::application_ptra appptra;

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

      try
      {
         if(m_ptwf != ::null())
         {

            m_ptwf->m_bRun = false;
            if(m_ptwf->m_p != ::null())
            {
               m_ptwf->m_p->m_bRun = false;
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
         if(m_ptwf != ::null())
         {
            m_ptwf->twf_stop();
            m_ptwf = ::null();
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
         if(m_pfactory != ::null())
         {

            m_pfactory->enable_simple_factory_request(false);

            m_pfactory.release();

         }

      }
      catch(...)
      {
         TRACE("system::exit_instance: Potentially catastrophical error : error disabling simple factory request");
      }

      m_typemap.release();

      int32_t iRet = 0;
      try
      {
         iRet = ::plane::application::exit_instance();
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


/*      try
      {
         if(m_ptwf != ::null())
         {
            m_ptwf->twf_stop();
            ::ca::del(m_ptwf);
            m_ptwf = ::null();
         }
      }
      catch(...)
      {
      }*/

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
         if(m_pmachineeventcentral != ::null())
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


      return iRet;
   }

   sp(::ca::ca) system::on_alloc(sp(::ca::application) papp, sp(::ca::type_info) info)
   {
      /*string str;
      str.Format("Could not alloc %s", info.name());
      simple_message_box(str);*/
      sp(::ca::ca) pobj = Sys(papp).factory().create(papp, info);
      if(pobj != ::null())
         return pobj;
      on_allocation_error(papp, info);
      return ::null();
   }

   sp(::ca::ca) system::clone()
   {
      // by the time, it is not possible to clone a system
      return ::null();
   }

   sp(::ca::ca) system::clone(sp(::ca::ca) pobj)
   {
      return System.factory().base_clone(pobj);
   }


   sp(::plane::session) system::query_session(index iEdge)
   {
      sp(::plane::session) pbergedge = ::null();
      if(m_pbergedgemap == ::null())
         return ::null();
      if(!m_pbergedgemap->Lookup(iEdge, pbergedge))
      {
         return ::null();
      }
      return pbergedge;
   }


   sp(::plane::session) system::get_session(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      sp(::plane::session) pbergedge = ::null();
      if(m_pbergedgemap == ::null())
         return ::null();
      if(!m_pbergedgemap->Lookup(iEdge, pbergedge))
      {
         pbergedge = create_application("application", "session", true, pbiasCreation);
         if(pbergedge == ::null())
            return ::null();
         pbergedge->m_iEdge = iEdge;
         m_pbergedgemap->set_at(iEdge, pbergedge);
      }
      return pbergedge;
   }


   sp(::ca::application) system::application_get(index iEdge, const char * pszType, const char * pszId, bool bCreate, bool bSynch, ::ca::application_bias * pbiasCreate)
   {
      sp(::plane::session) psession = get_session(iEdge, pbiasCreate);
      return psession->application_get(pszType, pszId, bCreate, bSynch, pbiasCreate);
   }


   sp(::ca::window_draw) system::get_twf()
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

   ::ca::log & system::log()
   {
      return *m_plog;
   }

   ::ca::factory & system::factory()
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

   ::ca::stra & system::stra()
   {
      return m_stra;
   }

   ::xml::xml & system::xml()
   {
      return *m_pxml;
   }

   ::fontopus::user_set & system::userset()
   {
      return m_userset;
   }

   ::ca::service & system::service()
   {
      return m_service;
   }

   ::ca::install & system::install()
   {
      return m_install;
   }

   ::ca::os & system::os()
   {
      return m_spos;
   }

#ifndef METROWIN

   ::ca::process_section & system::process()
   {
      return m_processsection;
   }

#endif

   ::ca::datetime & system::datetime()
   {
      return *m_pdatetime;
   }

   ::user::str & system::str()
   {
      return *m_puserstr;
   }

   /*   ::ca::filehandler::handler & system::filehandler()
   {
   return *m_spfilehandler;
   }*/

   void system::register_bergedge_application(sp(::ca::application) papp)
   {

      retry_single_lock rsl(&m_mutex, millis(84), millis(84));

      appptra().add_unique(papp);

      if(!papp->is_session()
      && !papp->is_system())
      {

         if(System.is_installing() || System.is_uninstalling())
            m_bDoNotExitIfNoApplications = false;
         else
            m_bDoNotExitIfNoApplications = false;

      }

   }

   void system::unregister_bergedge_application(sp(::ca::application) papp)
   {

      retry_single_lock rsl(&m_mutex, millis(84), millis(84));

      appptra().remove(papp);

   }

   void system::appa_load_string_table()
   {

      retry_single_lock rsl(&m_mutex, millis(84), millis(84));

      for(int32_t i = 0; i < appptra().get_size(); i++)
      {
         sp(::ca::application) papp = appptra()(i);
         papp->load_string_table();
      }

   }

   void system::appa_set_locale(const char * pszLocale, bool bUser)
   {

      retry_single_lock rsl(&m_mutex, millis(84), millis(84));

      for(int32_t i = 0; i < appptra().get_size(); i++)
      {
         sp(::ca::application) papp = appptra()(i);
         papp->set_locale(pszLocale, bUser);
      }

   }

   void system::appa_set_schema(const char * pszStyle, bool bUser)
   {

      retry_single_lock rsl(&m_mutex, millis(84), millis(84));

      for(int32_t i = 0; i < appptra().get_size(); i++)
      {
         sp(::ca::application) papp = appptra()(i);
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
         if(pmutex == ::null())
         {

            string strApp = pszAppName;
            strApp += "app.exe";

            string strParameters;
            strParameters = ": global_mutex_id=\"" + string(pszId) + "\"";

#if defined(WINDOWSEX) || defined(LINUX) || defined(MACOS)

            simple_shell_launcher launcher(::ca::null(), ::null(), dir().path(get_module_folder(), strApp), strParameters, ::null(), SW_SHOW);

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
         if(pmutex == ::null())
         {
            string strApp = pszAppName;
            strApp += "app.exe";

#ifdef METROWIN

            throw todo(get_app());

#else

            simple_shell_launcher launcher(::ca::null(), ::null(), dir().path(get_module_folder(), strApp), ::null(), ::null(), SW_SHOW);

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
         if(pmutex == ::null())
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName + " local_mutex_id=\"" + strId + "\"";

#ifdef METROWIN

            throw todo(get_app());

#else

            simple_shell_launcher launcher(::ca::null(), ::null(), dir().path(get_ca2_module_folder(), strApp), strParameters, ::null(), SW_SHOW);

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
         if(pmutex == ::null())
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName;

#ifdef METROWIN

            throw todo(get_app());

#else

            simple_shell_launcher launcher(::ca::null(), ::null(), dir().path(get_ca2_module_folder(), strApp), strParameters, ::null(), SW_SHOW);

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
      if(m_plog != ::null())
         return true;
      m_plog = new ::ca::log(this);
      m_plog->set_extended_log();
      m_plog->set_app(this);
      if(!m_plog->initialize(pszId))
      {
         m_plog.release();
         return false;
      }
      //      ::ca::trace_v = &::ca::system_log_trace_v;
      return true;
   }

   bool system::finalize()
   {

      try
      {
         if(m_spcrypt.is_set())
         {
            m_spcrypt.release();
         }
      }
      catch(...)
      {
      }

      ::plane::application::finalize();

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


   string system::matter_as_string(sp(::ca::application) papp, const char * pszMatter, const char * pszMatter2)
   {
      var varQuery;
      varQuery["disable_ca2_sessid"] = true;
      return file().as_string(dir_matter(papp, pszMatter, pszMatter2), varQuery, papp);
   }

   string system::dir_matter(sp(::ca::application) papp, const char * pszMatter, const char * pszMatter2)
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

   string system::file_as_string(sp(::ca::application) papp, const char * pszPath)
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

   /*void system::register_delete(sp(::ca::ca) plistened, sp(::ca::ca) plistener)
   {
      if(plistened == plistener)
         return;
      if(plistened == ::null())
         return;
      if(plistener == ::null())
         return;
      plistener->listenedptra().add(plistened);
      plistened->listenerptra().add(plistener);
   }

   void system::unregister_delete(sp(::ca::ca) plistened, sp(::ca::ca) plistener)
   {
      if(plistened == plistener)
         return;
      if(plistened == ::null())
         return;
      if(plistener == ::null())
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
      if(m_plog == ::null() || !m_plog->m_bExtendedLog)
      {
         return ::ca::SimpleDebugReport(iReportType, pszFileName, iLineNumber, pszModuleName, pszFormat, list);
      }

      string str;
      if(pszFileName != ::null() || pszModuleName != ::null())
      {
         stringa stra;
         if(pszFileName != ::null())
            stra.add(pszFileName);
         if(pszModuleName != ::null())
            stra.add(pszFileName);
         str += stra.implode(", ");
         str += ": ";
      }
      string str2;
      if(pszFormat != ::null())
      {
         if(list != ::null())
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
      if(m_plog != ::null())
      {
         m_plog->print(strPrint);
      }
      if(iReportType == _CRT_ASSERT && is_debugger_attached())
      {
#ifdef DEBUG
         ::ca::property_set propertyset;
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
      bool bQuit = PeekMessage(&msg, ::null(), WM_QUIT, WM_QUIT, PM_REMOVE) != FALSE;
      va_list list = ::null();
#elif defined(METROWIN)
      va_list list = ::null();
      //throw todo(get_app());
#else
      va_list list = {};
#endif
      bool bResult = __ca2_logging_report(_CRT_ASSERT, lpszFileName, iLine, ::null(), ::null(), list) != 0;
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

   void system::on_allocation_error(sp(::ca::application) papp, sp(::ca::type_info) info)
   {
      UNREFERENCED_PARAMETER(papp);
      simple_message_box(::null(), MB_ICONINFORMATION, "Implement \"%s\" allocation\n", info->friendly_name());
   }



   bool system::wait_twf(uint32_t dwTimeOut)
   {
      if(dwTimeOut > 1984)
         dwTimeOut = 1984;
      if(m_ptwf != ::null() && m_ptwf->m_bProDevianMode)
      {
         return m_ptwf->m_eventFree.wait(millis(dwTimeOut)).signaled();
      }
      /*else if(m_puiInitialPlaceHolderContainer != ::null())
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

   void system::on_request(sp(::ca::create_context) pcreatecontext)
   {
      sp(::plane::session) psession = get_session(pcreatecontext->m_spCommandLine->m_iEdge, pcreatecontext->m_spCommandLine->m_pbiasCreate);
      psession->request_create(pcreatecontext);
   }

   void system::open_by_file_extension(index iEdge, const char * pszFileName)
   {
      sp(::plane::session) psession = get_session(iEdge);
      psession->open_by_file_extension(pszFileName);
   }

   sp(::ca::ca) system::alloc(sp(::ca::application) papp, sp(::ca::type_info) info)
   {
      return ::ca::system::alloc(papp, info);
   }

   sp(::ca::ca) system::alloc(sp(::ca::application) papp, const class id & idType)
   {
      return ::ca::system::alloc(papp, get_type_info(idType));
   }

   bool system::sync_load_url(string & str, const char * lpszUrl, ::fontopus::user * puser, ::http::cookies * pcookies)
   {
      string filename = System.file().time_square(get_app());
      ::ca::property_set headers;
      ::ca::property_set post;
      ::ca::property_set set;
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
      if(pcookies != ::null())
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
      ::primitive::memory_file memfile;
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

   ::ca::compress & system::compress()
   {
      return m_compress;
   }

   ::ca::patch & system::patch()
   {
      return m_patch;
   }

   class ::ca::crypt & system::crypt()
   {
      return m_spcrypt;
   }

   class ::ca::email & system::email()
   {
      return m_email;
   }

   class ::ca::http::system & system::http()
   {
      return m_http;
   }


   ::ca::copydesk & system::copydesk()
   {
      return m_spcopydesk;
   }

   bool system::base_support()
   {
      return true;
   }

   index system::get_new_bergedge(::ca::application_bias * pbiasCreation)
   {
      index iNewEdge = m_iNewEdge;
      sp(::plane::session) pbergedge;
      while(m_pbergedgemap->Lookup(iNewEdge, pbergedge))
      {
         iNewEdge++;
      }
      if(get_session(iNewEdge, pbiasCreation) == ::null())
         return -1;
      m_iNewEdge = iNewEdge + 1;
      return iNewEdge;
   }


   bool system::create_twf()
   {
      if(m_ptwf != ::null())
         return true;
      m_ptwf = alloc(this, System.type_info < ::ca::window_draw > ());
      m_ptwf->twf_start();
      return true;
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

   void system::discard_to_factory(sp(::ca::ca) pca)
   {

      if(m_pfactory == ::null())
         return;

      m_pfactory->discard(pca);

   }


   sp(::ca::application) system::get_new_app(sp(::ca::application) pappNewApplicationParent, const char * pszType, const char * pszAppId)
   {

      string strId(pszAppId);

      string strApplicationId;

      if(strId == "app/ca2/bergedge")
      {

         strApplicationId = "bergedge";

      }
      else if(strId == "app/ca2/system")
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


#ifndef METROWIN

      if(!System.directrix()->m_varTopicQuery.has_property("install")
         && !System.directrix()->m_varTopicQuery.has_property("uninstall")
         && strId.has_char()
         && !install().is(::null(), strBuildNumber, pszType, strApplicationId, m_strLocale, m_strSchema))
      {

         throw not_installed(get_app(), ::null(), strBuildNumber, pszType, strApplicationId, m_strLocale, m_strSchema);

      }

#endif

      ::ca::library library(::null());

      string strLibrary = m_mapAppLibrary[pszAppId];

      if(strLibrary.is_empty())
      {

         throw not_installed(get_app(), ::null(), strBuildNumber, pszType, strApplicationId, m_strLocale, m_strSchema);

      }

      sp(::ca::application) papp = ::null();

      if(!library.open(pappNewApplicationParent, strLibrary, false))
         return ::null();

      papp = library.get_new_app(pszAppId);

      if(papp == ::null())
         return ::null();

      sp(::ca::application) pgenapp = (papp);

      pgenapp->m_strAppId = pszAppId;

      return papp;

   }

/*
   bool system::set_main_init_data(::ca::main_init_data * pdata)
   {

      if(pdata == ::null())
      {
         if(!::plane::application::set_main_init_data(pdata))
            return false;
         return true;
      }

      ::ca::property_set set(this);

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

      if(!::plane::application::set_main_init_data(pdata))
         return false;

      return true;

   }*/

   sp(::ca::type_info) system::get_type_info(const ::std_type_info & info)
   {

#ifdef WINDOWS
      sp(::ca::type_info) & typeinfo = m_typemap[info.raw_name()];
#else
      sp(::ca::type_info) & typeinfo = m_typemap[info.name()];
#endif

      if(typeinfo.is_null())
         typeinfo = canew(::ca::type_info(info));

      return typeinfo;

   }





   //////////////////////////////////////////////////////////////////////////////////////////////////
   // System/System
   //
   sp(::user::document) system::hold(sp(::user::interaction) pui)
   {


      //if(m_pcubeInterface != ::null())
      //{
        // return m_pcubeInterface->hold(pui);
      //}

      return ::null();

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
   BOOL CALLBACK system::monitor_enum_proc(
     HMONITOR hmonitor,
     HDC hdcMonitor,
     LPRECT lprcMonitor,
     LPARAM dwData)
   {
      ::plane::system * papp = (::plane::system *) dwData;
      papp->monitor_enum(hmonitor, hdcMonitor, lprcMonitor);
      return TRUE; // to enumerate all
   }
#endif

#ifdef WINDOWSEX
   void system::monitor_enum(
     HMONITOR hmonitor,
     HDC hdcMonitor,
     LPRECT lprcMonitor)
   {
      UNREFERENCED_PARAMETER(hdcMonitor);
      UNREFERENCED_PARAMETER(lprcMonitor);
      m_monitorinfoa.set_size(m_monitorinfoa.get_size() + 1);
      memset(&m_monitorinfoa.last_element(), 0, sizeof(MONITORINFO));
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

      return System.get_window_rect(lprect);

#elif defined(LINUX)


      xdisplay  d;

      if(!d.open(NULL))
      return false;


      //throw todo(get_app());
      lprect->left = 0;
      lprect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdisplay));
      lprect->top = 0;
      lprect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d.m_pdisplay));



#elif defined(MACOS)


      throw todo(get_app());




#else
      throw todo(get_app());
      ::GetWindowRect(::GetDesktopWindow(), lprect);
#endif
      return true;
      return false;

   }

   index system::get_best_intersection_monitor(LPRECT lprect)
   {

      ::count c   = get_monitor_count();

      rect        rectIntersect;
      rect        rectMonitor;
      int64_t     iBestArea = 0;
      index       iBestAreaIndex = -1;
      int64_t     iArea;

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


   ::count system::get_desk_monitor_count()
   {


      return 0;

   }

   bool system::get_desk_monitor_rect(index i, LPRECT lprect)
   {


      return false;

   }

   sp(::ca::command_thread) system::command_thread()
   {
      return m_pcommandthread;
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


   string system::get_fontopus_server(const char * pszUrl, sp(::ca::application) papp, int32_t iRetry)
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
         ::ca::property_set post;
         ::ca::property_set headers;
         ::ca::property_set set;
         set["disable_ca2_sessid"] = true;
         set["app"] = papp;
         Application.http().get(strGetFontopus, strFontopusServer, post, headers, set, ::null(), ::null(), ::null(), ::null());
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


   bool system::add_library(::ca::library * plibrary)
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


   void system::post_fork_uri(const char * pszUri, ::ca::application_bias * pbiasCreate)
   {

      command()->add_fork_uri(pszUri, pbiasCreate);

      if(command()->m_varTopicQuery["locale"].has_char()
         && command()->m_varTopicQuery["locale"] != "_std")
      {
         set_locale(command()->m_varTopicQuery["locale"], true);
      }

      if(command()->m_varTopicQuery["schema"].has_char())
      {
         set_schema(command()->m_varTopicQuery["schema"], true);
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

         lprect->left      = (LONG) rect.X;
         lprect->top       = (LONG) rect.Y;
         lprect->right     = (LONG) (lprect->left + rect.Width);
         lprect->bottom    = (LONG) (lprect->top + rect.Height);


         return true;

      }
#endif



   /*bool system::InitApplication()
   {

      if(!::plane::application::InitApplication())
         return FALSE;

      return TRUE;

   }


   bool system::process_initialize()
   {

      if(!::plane::application::process_initialize())
         return false;

      return true;

   }


   bool system::initialize()
   {


      if(!::plane::application::initialize())
         return false;

      return true;

   }



   bool system::initialize1()
   {

      if(!::plane::application::initialize1())
         return false;

      return true;

   }



   bool system::initialize3()
   {

      if(!::plane::application::initialize3())
         return false;

      return true;

   }

   bool system::initialize_instance()
   {

      if(!::plane::application::initialize_instance())
         return false;

      return true;

   }


   bool system::bergedge_start()
   {

      if(!::plane::application::bergedge_start())
         return false;

      return true;
   }


   int32_t system::exit_instance()
   {

      int32_t iRet = -1;

      try
      {
         iRet = ::plane::application::exit_instance();
      }
      catch(...)
      {
      }



      return iRet;


   }*/



   /*sp(::plane::session) system::query_session(index iEdge)
   {
      sp(::plane::session) psession = ::null();
      if(m_pbergedgemap == ::null())
         return ::null();
      if(!m_pbergedgemap->Lookup(iEdge, psession))
      {
         return ::null();
      }
      return dynamic_cast < ::sp(::plane::session) > (psession->m_pbergedge);
   }


   sp(::plane::session) system::get_session(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      sp(::plane::session) psession = ::null();
      if(m_pbergedgemap == ::null())
         return ::null();
      if(!m_pbergedgemap->Lookup(iEdge, psession))
      {
         psession =  (create_application("application", "session", true, pbiasCreation));
         if(psession == ::null())
            return ::null();
         psession->m_iEdge = iEdge;
         m_pbergedgemap->set_at(iEdge, psession);
      }
      return dynamic_cast < ::sp(::plane::session) > (psession->m_pbergedge);
   }*/


   sp(::platform::document) system::get_platform(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      sp(::plane::session) pbergedge = get_session(iEdge, pbiasCreation);
      return pbergedge->get_platform();
   }

   sp(::nature::document) system::get_nature(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      sp(::plane::session) pbergedge = get_session(iEdge, pbiasCreation);
      return pbergedge->get_nature();
   }

   /*sp(::ca::application) system::application_get(index iEdge, const char * pszType, const char * pszId, bool bCreate, bool bSynch, ::ca::application_bias * pbiasCreate)
   {
      sp(::plane::session) pbergedge = ge(iEdge, pbiasCreate);
      return pbergedge->application_get(pszType, pszId, bCreate, bSynch, pbiasCreate);
   }*/


   /*bool system::set_history(::ca::history * phistory)
   {

      UNREFERENCED_PARAMETER(phistory);

      return true;

   }*/



   //void system::register_bergedge_application(sp(::ca::application) papp)
   //{


   //   System.register_bergedge_application(papp);


   //}

   //void system::unregister_bergedge_application(sp(::ca::application) papp)
   //{

   //   System.unregister_bergedge_application(papp);


   //}






   //bool system::finalize()
   //{

   //   bool bOk = false;

   //   try
   //   {
   //      bOk = system::application::finalize();
   //   }
   //   catch(...)
   //   {
   //   }


   //   return bOk;
   //}


   //void system::on_request(sp(::ca::create_context) pcreatecontext)
   //{
   //   ::sp(::plane::session) pbergedge = get_bergedge(pcreatecontext->m_spCommandLine->m_iEdge, pcreatecontext->m_spCommandLine->m_pbiasCreate);
   //   pbergedge->request_create(pcreatecontext);
   //}

   //void system::open_by_file_extension(index iEdge, const char * pszFileName)
   //{
   //   System.get_session(iEdge)->open_by_file_extension(pszFileName);
   //}


   //index system::get_new_bergedge(::ca::application_bias * pbiasCreation)
   //{
   //   index iNewEdge = m_iNewEdge;
   //   sp(::plane::session) psession;
   //   while(m_pbergedgemap->Lookup(iNewEdge, psession))
   //   {
   //      iNewEdge++;
   //   }
   //   if(get_bergedge(iNewEdge, pbiasCreation) == ::null())
   //      return -1;
   //   m_iNewEdge = iNewEdge + 1;
   //   return iNewEdge;
   //}


   //bool system::is_system()
   //{
   //   return false;
   //}

   bool system::is_system()
   {
      return true;
   }

   bool system::set_main_init_data(::ca::main_init_data * pdata)
   {

      if(pdata == ::null())
      {
         if(!::plane::application::set_main_init_data(pdata))
            return false;
         return true;
      }

      ::ca::property_set set(this);

      var varFile;
      string strApp;

      set._008ParseCommandFork(pdata->m_vssCommandLine, varFile, strApp);

      if((varFile.is_empty() && ((!set.has_property("app") && !set.has_property("show_platform"))
         || set["app"] == "bergedge")) &&
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

      if(!::plane::application::set_main_init_data(pdata))
         return false;

      return true;

   }


/*   sp(::ca::command_thread) system::command_thread()
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
      sp(::plane::session) psession = ::null();
      if(m_pbergedgemap == ::null())
         return ::null();
      if(!m_pbergedgemap->Lookup(iEdge, psession))
      {
         return ::null();
      }
      return psession;
   }


/*   sp(::plane::session) system::get_session(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      sp(::plane::session) psession = ::null();
      if(m_pbergedgemap == ::null())
         return ::null();
      if(!m_pbergedgemap->Lookup(iEdge, psession))
      {
         psession = (create_application("application", "session", true, pbiasCreation));
         if(psession == ::null())
            return ::null();
         psession->m_iEdge = iEdge;
         m_pbergedgemap->set_at(iEdge, psession);
      }
      return  psession;
   }


   sp(platform::document) system::get_platform(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      sp(::plane::session) pbergedge = get_session(iEdge, pbiasCreation);
      return pbergedge->get_platform();
   }

   sp(nature::document) system::get_nature(index iEdge, ::ca::application_bias * pbiasCreation)
   {
      sp(::plane::session) pbergedge = get_session(iEdge, pbiasCreation);
      return pbergedge->get_nature();
   }

   sp(::ca::application) system::application_get(index iEdge, const char * pszType, const char * pszId, bool bCreate, bool bSynch, ::ca::application_bias * pbiasCreate)
   {
      sp(::plane::session) pbergedge = get_session(iEdge, pbiasCreate);
      return pbergedge->application_get(pszType, pszId, bCreate, bSynch, pbiasCreate);
   }
   */

   void application::assert_valid() const
   {

      ::ca::application::assert_valid();
      //::database::server::assert_valid();

   }


   void application::dump(dump_context & context) const
   {

      ::ca::application::dump(context);
      //::database::server::dump(context);

   }




} // namespace plane



