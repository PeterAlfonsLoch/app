#include "framework.h"

void dappy(const char * psz);

#ifdef WINDOWSEX


CLASS_DECL_BASE HMONITOR GetUiMonitorHandle(HWND hwnd)
{

   return MonitorFromWindow(hwnd,MONITOR_DEFAULTTOPRIMARY);

}


CLASS_DECL_BASE HMONITOR GetPrimaryMonitorHandle()
{

   const POINT ptZero ={0,0};

   return MonitorFromPoint(ptZero,MONITOR_DEFAULTTOPRIMARY);

}


CLASS_DECL_BASE bool GetPrimaryMonitorRect(LPRECT lprect)
{

   MONITORINFO mi;

   ZERO(mi);

   mi.cbSize = sizeof(MONITORINFO);

   if(GetMonitorInfo(GetPrimaryMonitorHandle(),&mi))
   {

      *lprect = mi.rcMonitor;

   }
   else
   {

      if(!::GetWindowRect(::GetDesktopWindow(),lprect))
      {

         return false;

      }

   }

   return true;

}


#endif


namespace base
{


   class ::id system::idEmpty;
   class ::id_space * system::s_pidspace = NULL;


   system::system(sp(::base::application) papp):
      m_urldepartament(this),
      //m_mutexDelete(this),
      m_httpsystem(this),
      //m_mutex(this),
#ifndef METROWIN
      //m_processsection(this),
#endif
      //m_visual(this),
      m_libraryDraw2d(this)
   {

#ifdef MATTER_CACHE_FROM_HTTP_SERVER

      m_bMatterFromHttpCache = true;

#else

      m_bMatterFromHttpCache = false;

#endif

      m_psimpleui = NULL;

#if defined(METROWIN) || defined(APPLE_IOS)
      m_posdata = new os_data();
#endif

      set_app(this);
      m_nSafetyPoolSize          = 512;        // default size

      m_pmath                    = canew(math::math(this));
      m_pgeometry                = canew(geometry::geometry(this));
      m_phtml = NULL;


      m_pbasesystem = this;

      if(papp == NULL)
      {

         oprop("parent_system") = (sp(element)) NULL;

      }
      else
      {

         oprop("parent_system") = papp->m_pbasesystem;

      }

      m_peengine = NULL;


      m_pmachineeventcentral = NULL;

      //::ca::application::m_file.set_app(this);
      //::ca::application::m_dir.set_app(this);

      string strId;
      //strId = m_strAppName;
      //strId += ::str::has_char(m_strAppId, ".");
      //strId += ::str::has_char(m_strBaseSupportId, ".");


      strId = "ca2log";


      xxdebug_box("Going to start Log","Just before initialize log",0);

      // log starts here
      if(!initialize_log(strId))
      {
         xxdebug_box("Could not initialize log","Failed to initialize log",0);
         throw "failed to initialize log";
      }


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


      //use_base_ca2_allocator();


      m_pfactory = new class base_factory(this);
      m_pfactory->set_app(this);

      m_pfactory->creatable_large < ::file::simple_binary_buffer >(type_info < ::file::binary_buffer >());
      m_pfactory->creatable_large < ::file::string_buffer >();

      m_spinstall = new ::install::install(this);


#ifdef WINDOWS
      m_pmutexDc = NULL;
      m_pdevicecontext = NULL;
#endif


      factory().cloneable_large < stringa >();
      factory().cloneable_large < ::primitive::memory >();
      factory().cloneable_large < int_array >();

      __node_factory_exchange(this);

      thread::s_bAllocReady = true;

      //Ex1OnFactoryExchange();

      //m_spfilesystem.create(allocer());


      /*   {

            draw2d_gdiplus::factory_exchange factoryexchange(this);

            }*/



      m_pxml = canew(::xml::departament(this));

      m_pxml->construct(this);

      if(!m_pxml->initialize1())
         throw simple_exception(this,"failed to construct system m_pxml->initialize1()");

      if(!m_pxml->initialize())
         throw simple_exception(this,"failed to construct system m_pxml->initialize()");



      

      m_compress.set_app(this);


      m_bSystemSynchronizedCursor = true;

      m_bSystemSynchronizedScreen = true;

      m_spmutexUserAppData = canew(mutex(get_app(),false,"Local\\ca2.UserAppData"));
      //m_spmutexSystemAppData = canew(mutex(get_app(),false,"Global\\ca2.SystemAppData"));
      m_spmutexSystemAppData = canew(mutex(get_app(),false,"Local\\ca2.SystemAppData"));

      m_spmutexFactory = canew(mutex(get_app()));

      m_bGudoNetCache = true;

      ::draw2d::dib::static_initialize();

      m_pschemaLayeredFrame = new ::user::schema_layered_frame;

   }


   void system::construct(const char * pszAppId)
   {

      ::base::application::construct(pszAppId);

   }


   system::~system()
   {

   }


   base_factory & system::factory()
   {

      return *m_pfactory;

   }


   ::exception::engine & system::eengine()
   {

      return *m_peengine;

   }


   bool system::process_initialize()
   {




      enum_display_monitors();

      m_peengine = new ::exception::engine(this);

      m_psslinit = new ::sockets::SSLInitializer(this);

      m_pfactory->cloneable_large < create_context >();
      m_pfactory->cloneable_large < application_bias >();
      m_pfactory->cloneable_large < command_line >();
      m_pfactory->cloneable_large < manual_reset_event >();
      m_pfactory->cloneable_large < mutex >();
      m_pfactory->cloneable_large < event >();

      if(!::base::application::process_initialize())
         return false;

#ifdef WINDOWS

      m_spwindow = canew(interaction_impl(this));

#endif

      m_spos.create(allocer());

      m_spcrypto.create(allocer());

      if(!m_spcrypto.is_set())
         return false;


      if(!set_main_init_data(m_pinitmaindata))
         return false;


      if(m_pmachineeventcentral == NULL)
      {

         m_pmachineeventcentral = new ::machine_event_central(this);
         if(!m_pmachineeventcentral->initialize())
            return false;
         if(m_pmachineeventcentral->is_close_application())
            return false;

      }

#ifdef WINDOWSEX

      dappy(string(typeid(*this).name()) + " : Going to ::base::system::m_spwindow->CreateEx : " + ::str::from(m_iReturnCode));

      if(!m_spwindow->CreateEx(0,NULL,NULL,0,null_rect(),NULL,"::base::system::interaction_impl::no_twf"))
      {

         dappy(string(typeid(*this).name()) + " : ::base::system::m_spwindow->CreateEx failure : " + ::str::from(m_iReturnCode));

         return false;

      }

#endif

      dappy(string(typeid(*this).name()) + " : Going to ::base::session " + ::str::from(m_iReturnCode));
      m_spfile.create(allocer());


      m_spdir.create(allocer());


      m_pbasesession = new ::base::session(this);

      if(m_pbasesession == NULL)
         return false;

      if(!m_spdir->initialize())
         throw simple_exception(this,"failed to construct system m_spdir->initialize");

      m_pbasesession->construct(this,0);


      m_spnet = canew(::sockets::net(this));
      //m_spnet.create(allocer());

      if(m_spnet.is_null())
      {

         m_iReturnCode = -1986;

         return false;

      }


      if(!m_spnet->initialize())
         return false;

      if(!m_pbasesession->begin_synch(&m_iReturnCode))
      {
         return false;
      }

      dappy(string(typeid(*this).name()) + " : ::base::session OK " + ::str::from(m_iReturnCode));

      return true;

   }


   bool system::initialize2()
   {

      if(!::base::application::initialize2())
         return false;

      return true;

   }


   bool system::initialize_instance()
   {

      m_pfactory->enable_simple_factory_request();

      if(!::base::application::initialize_instance())
         return false;

      return true;

   }


   bool system::finalize()
   {

      try
      {

         if(!m_spnet->gudo_set())
         {

            m_iReturnCode = -87;

         }

      }
      catch(...)
      {

         m_iReturnCode = -87;

      }


      __wait_threading_count_except(this,::millis((5000) * 77));

      bool bOk = false;

      try
      {

         bOk = ::base::application::finalize();

      }
      catch(...)
      {

         bOk = false;

      }

      return bOk;

   }


   int32_t system::exit_instance()
   {
      try
      {

         if(m_ptwf != NULL)
         {

            m_ptwf->m_bRun = false;

         }

      }
      catch(...)
      {
      }

      try
      {
         if(m_ptwf != NULL)
         {
            m_ptwf->twf_stop();
            m_ptwf.release();
         }
      }
      catch(...)
      {
      }

      __wait_threading_count(::millis((5000) * 8));

      try
      {


         /*      try
         {
         if(m_plemonarray != NULL)
         {
         delete m_plemonarray;
         }
         }
         catch(...)
         {
         }
         m_plemonarray = NULL;
         */


         m_pmath.release();

         m_pgeometry.release();

      }
      catch(...)
      {
         m_iReturnCode = -86;
      }


      try
      {

         if(!m_spnet->finalize())
         {

            m_iReturnCode = -87;

         }

      }
      catch(...)
      {

         m_iReturnCode = -87;

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


      for(int i = 0; i < m_serviceptra.get_size(); i++)
      {
         try
         {
            m_serviceptra(i)->Stop((5000) * 2);
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

         iRet = ::base::application::exit_instance();

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



      m_plog.release();


      
      {

         synch_lock sl(m_spmutexFactory);

         m_typemap.remove_all();

         m_typemap.release();

      }



      ::base::application::exit_instance();

#ifdef WINDOWS

      m_pdevicecontext = nullptr;

      m_pmutexDc.release();

#endif


      try
      {

         m_spwindow.release();

      }
      catch(...)
      {

         m_iReturnCode = -2;

      }

      try
      {

         m_spnet.release();

      }
      catch(...)
      {

         m_iReturnCode = -86;

      }

      if(m_psslinit != NULL)
      {

         delete m_psslinit;

         m_psslinit = NULL;

      }

      if(m_peengine != NULL)
      {

         delete m_peengine;

         m_peengine = NULL;

      }


      return iRet;

   }


   UINT system::os_post_to_all_threads(UINT uiMessage,WPARAM wparam,lparam lparam)
   {

      post_to_all_threads(uiMessage,wparam,lparam);

      return 0;

   }

   sp(element) system::clone()
   {
      // by the time, it is not possible to clone a system
      return NULL;
   }

   sp(element) system::clone(sp(element) pobj)
   {
      return System.factory().base_clone(pobj);
   }


   void system::discard_to_factory(sp(element) pca)
   {

      if(m_pfactory == NULL)
         return;

      m_pfactory->discard(pca);

   }



   void system::wait_twf()
   {

   }

   bool system::is_system()
   {

      return true;

   }






   int32_t system::_001OnDebugReport(int32_t i1,const char * psz1,int32_t i2,const char * psz2,const char * psz3,va_list args)
   {

      return _debug_logging_report(i1,psz1,i2,psz2,psz3,args);

   }



   int32_t system::_debug_logging_report(int32_t iReportType, const char * pszFileName, int32_t iLineNumber, const char * pszModuleName, const char * pszFormat,va_list list)
   {

      if(m_plog == NULL || !m_plog->m_bExtendedLog)
      {

         return ::base::SimpleDebugReport(iReportType,pszFileName,iLineNumber,pszModuleName,pszFormat,list);

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

            str2.FormatV(pszFormat,list);

         }
         else
         {

            str2 = pszFormat;

         }

      }

      str = str + str2;

      string strPrint(str);

      strPrint.replace("%","%%");

      if(m_plog != NULL)
      {

         m_plog->print(strPrint);

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




   bool system::assert_failed_line(const char * lpszFileName,int32_t iLine)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(iLine);
      return false;
   }


   bool system::on_assert_failed_line(const char * lpszFileName,int32_t iLine)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(iLine);
      return true;
   }




   sp(element) system::on_alloc(sp(::base::application) papp,sp(type) info)
   {
      /*string str;
      str.Format("Could not alloc %s", info.name());
      simple_message_box(str);*/
      sp(element) pobj = m_pfactory->create(papp,info);
      if(pobj != NULL)
         return pobj;
      on_allocation_error(papp,info);
      return NULL;
   }

   sp(element) system::alloc(sp(::base::application) papp,sp(type) info)
   {
      return on_alloc(papp,info);
   }

   sp(element) system::alloc(sp(::base::application) papp,const std_type_info & info)
   {
      return on_alloc(papp,canew(type(info)));
   }

   void system::on_allocation_error(sp(::base::application) papp,sp(type) info)
   {
      UNREFERENCED_PARAMETER(papp);
      UNREFERENCED_PARAMETER(info);
   }

   sp(element) system::alloc(sp(::base::application) papp,const class id & idType)
   {
      return on_alloc(papp,get_type_info(idType));
   }


   sp(type) system::get_type_info(const ::std_type_info & info)
   {

      synch_lock sl(m_spmutexFactory);

#ifdef WINDOWS
      sp(type) & typeinfo = m_typemap[info.raw_name()];
#else
      sp(type) & typeinfo = m_typemap[info.name()];
#endif

      if(typeinfo.is_null())
         typeinfo = canew(type(info));

      return typeinfo;

   }


   ::xml::departament & system::xml()
   {
      return *m_pxml;
   }



   class ::str::base64 & system::base64()
   {

      return m_base64;

   }





   ::sockets::net & system::net()
   {
      return *m_spnet;
   }



   class ::crypto::crypto & system::crypto()
   {
      return *m_spcrypto;
   }



   ::datetime::departament & system::datetime()
   {
      return *m_pdatetime;
   }



   sp(::user::window_draw) system::get_twf()
   {

      return m_ptwf;

   }

   ::base::log & system::log()
   {
      return *m_plog;
   }




   ::fontopus::user_set & system::userset()
   {
      return m_userset;
   }



   ::base::compress & system::compress()
   {
      return m_compress;
   }



   machine_event_central & system::machine_event_central()
   {
      return *m_pmachineeventcentral;
   }


   ::user::str & system::str()
   {

      return *m_puserstr;

   }


   sp(::user::document) system::place_hold(sp(::user::interaction) pui)
   {


      //if(m_pcubeInterface != NULL)
      //{
      // return m_pcubeInterface->hold(pui);
      //}

      return NULL;

   }


   sp(::base::session) system::query_session(index iEdge)
   {

      return NULL;

   }


   ::base::os & system::os()
   {

      return *m_spos;

   }


   spa(::base::session) & system::basesessionptra()
   {

      return m_basesessionptra;

   }

   bool system::initialize_log(const char * pszId)
   {
      if(m_plog != NULL)
         return true;
      m_plog = new ::base::log(this);
      m_plog->set_extended_log();
      m_plog->set_app(this);
      if(!m_plog->initialize(pszId))
      {
         m_plog.release();
         return false;
      }
      //      ::core::trace_v = &::core::system_log_trace_v;
      return true;
   }






   void system::appa_load_string_table()
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

//      for(int32_t i = 0; i < appptra().get_size(); i++)
  //    {
    //     sp(::base::application) papp = appptra()(i);
      //   papp->load_string_table();
      //}

   }

   void system::appa_set_locale(const char * pszLocale,::action::context actioncontext)
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

//      for(int32_t i = 0; i < appptra().get_size(); i++)
 //     {
  //       sp(::base::application) papp = appptra()(i);
  //       papp->set_locale(pszLocale,actioncontext);
  //    }

   }

   void system::appa_set_schema(const char * pszStyle,::action::context actioncontext)
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

//      for(int32_t i = 0; i < appptra().get_size(); i++)
  //    {
  //       sp(::base::application) papp = appptra()(i);
  //       papp->set_schema(pszStyle,actioncontext);
  //    }

   }



   bool system::assert_running_global(const char * pszAppName,const char * pszId)
   {
      if(string(pszId).has_char())
      {
         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_global_id_mutex_name(pszAppName, pszId));
         ::mutex * pmutex = mutex::open_mutex(this,get_global_id_mutex_name(pszAppName,pszId));
         if(pmutex == NULL)
         {

            string strApp = pszAppName;
            strApp += "app.exe";

            string strParameters;
            strParameters = ": global_mutex_id=\"" + string(pszId) + "\"";

#if defined(WINDOWSEX) || defined(LINUX) || defined(APPLEOS)

            simple_shell_launcher launcher(NULL,NULL,dir().path(get_module_folder(),strApp),strParameters,NULL,SW_SHOW);

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
         ::mutex * pmutex = mutex::open_mutex(this,get_global_mutex_name(pszAppName));
         if(pmutex == NULL)
         {
            string strApp = pszAppName;
            strApp += "app.exe";

#if defined(METROWIN)

            throw todo(get_app());

#else

            simple_shell_launcher launcher(NULL,NULL,dir().path(get_module_folder(),strApp),NULL,NULL,SW_SHOW);

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

   bool system::assert_running_local(const char * pszAppName,const char * pszId)
   {
      string strAppName(pszAppName);
      string strId(pszId);
      if(strId.has_char())
      {
         //HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_local_id_mutex_name(pszAppName, strId));
         ::mutex * pmutex = mutex::open_mutex(this,get_local_id_mutex_name(pszAppName,strId));
         if(pmutex == NULL)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName + " local_mutex_id=\"" + strId + "\"";

#ifdef METROWIN

            throw todo(get_app());

#else

            simple_shell_launcher launcher(NULL,NULL,dir().path(get_ca2_module_folder(),strApp),strParameters,NULL,SW_SHOW);

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
         ::mutex * pmutex = mutex::open_mutex(this,get_local_mutex_name(pszAppName));
         if(pmutex == NULL)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName;

#ifdef METROWIN

            throw todo(get_app());

#else

            simple_shell_launcher launcher(NULL,NULL,dir().path(get_ca2_module_folder(),strApp),strParameters,NULL,SW_SHOW);

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







   bool system::initialize_twf()
   {

      if(m_ptwf != NULL)
         return true;

      m_ptwf.create(allocer());

      if(m_ptwf->twf_start())
         return false;

      return true;

   }


   index system::get_main_monitor(LPRECT lprect)
   {

      int iMainMonitor = 0;

#ifdef WINDOWSEX

      HMONITOR hmonitorPrimary = GetPrimaryMonitorHandle();

      for(index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         if(m_hmonitora[iMonitor] == hmonitorPrimary)
         {

            iMainMonitor = iMonitor;

            break;

         }

      }


#endif

      if(lprect != NULL)
      {

         get_monitor_rect(iMainMonitor,lprect);

      }

      return iMainMonitor;

   }


   ::count system::get_monitor_count()
   {

#ifdef WINDOWSEX

      return m_monitorinfoa.get_count();

#else

      return 1;

#endif

   }


   bool system::get_monitor_rect(index iMonitor,LPRECT lprect)
   {

#ifdef WINDOWSEX

      if(iMonitor < 0 || iMonitor >= get_monitor_count())
         return false;

      *lprect = m_monitorinfoa[iMonitor].rcMonitor;

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

      if(iMonitor < 0 || iMonitor >= get_monitor_count())
         return false;

      GetMainScreenRect(lprect);

#else

      throw todo(get_app());

      ::GetWindowRect(::GetDesktopWindow(),lprect);

#endif

      return true;

   }


   ::count system::get_desk_monitor_count()
   {

      return get_monitor_count();

   }


   bool system::get_desk_monitor_rect(index iMonitor,LPRECT lprect)
   {

      return get_monitor_rect(iMonitor,lprect);

   }


   index system::get_ui_wkspace(::user::interaction * pui)
   {

      int iMainWkspace = 0;

#ifdef WINDOWSEX

      HMONITOR hwkspacePrimary = GetUiMonitorHandle(pui->get_handle());

      for(index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
      {

         if(m_hmonitora[iWkspace] == hwkspacePrimary)
         {

            iMainWkspace = iWkspace;

            break;

         }

      }


#endif

      return iMainWkspace;

   }


   index system::get_main_wkspace(LPRECT lprect)
   {

      int iMainWkspace = 0;

#ifdef WINDOWSEX

      HMONITOR hwkspacePrimary = GetPrimaryMonitorHandle();

      for(index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
      {

         if(m_hmonitora[iWkspace] == hwkspacePrimary)
         {

            iMainWkspace = iWkspace;

            break;

         }

      }


#endif

      if(lprect != NULL)
      {

         get_wkspace_rect(iMainWkspace,lprect);

      }

      return iMainWkspace;

   }


   ::count system::get_wkspace_count()
   {

#ifdef WINDOWSEX

      return m_monitorinfoa.get_count();

#else

      return 1;

#endif

   }


   bool system::get_wkspace_rect(index iWkspace,LPRECT lprect)
   {

#ifdef WINDOWSEX

      if(iWkspace < 0 || iWkspace >= get_wkspace_count())
         return false;

      *lprect = m_monitorinfoa[iWkspace].rcWork;

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

      if(iWkspace < 0 || iWkspace >= get_wkspace_count())
         return false;

      GetMainScreenRect(lprect);

#else

      throw todo(get_app());

      ::GetWindowRect(::GetDesktopWindow(),lprect);

#endif

      return true;

   }


   ::count system::get_desk_wkspace_count()
   {

      return get_wkspace_count();

   }


   bool system::get_desk_wkspace_rect(index iWkspace,LPRECT lprect)
   {

      return get_wkspace_rect(iWkspace,lprect);

   }

#ifdef WINDOWS


   system::interaction_impl::interaction_impl(sp(::base::application) papp):
      element(papp),
      ::user::interaction(papp)
   {

   }

   void system::interaction_impl::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::interaction::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_DISPLAYCHANGE,pdispatch,this,&::base::system::interaction_impl::_001MessageHub);

   }

   void system::interaction_impl::_001MessageHub(signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);

      if(pbase != NULL)
      {

         if(pbase->m_uiMessage == WM_DISPLAYCHANGE)
         {

            System.enum_display_monitors();

            for(index i = 0; i < System.frames().get_count(); i++)
            {

               try
               {

                  System.frames()[i]->WfiRestore(true);

               }
               catch(...)
               {
               }

            }


         }

      }

   }


#endif


   sp(::user::interaction) system::get_active_guie()
   {

#if defined(WINDOWSEX) || defined(LINUX) || defined(APPLEOS)

      return window_from_os_data(::GetActiveWindow());

#else

      if(frames().get_size() <= 0)
         return NULL;

      return frames()(0);

#endif

   }


   sp(::user::interaction) system::get_focus_guie()
   {

#if defined (METROWIN)

      return GetFocus()->interaction_impl();

#elif defined(WINDOWSEX) || defined(LINUX)

      ::user::interaction * pwnd = ::window_from_handle(::GetFocus());
      if(pwnd != NULL)
      {
         if(System.get_active_guie()->get_safe_handle() == pwnd->get_safe_handle()
            || ::user::window_util::IsAscendant(System.get_active_guie()->get_safe_handle(),pwnd->get_safe_handle()))
         {
            return pwnd;
         }
         else
         {
            return NULL;
         }
      }
      pwnd = System.window_from_os_data(::GetFocus());
      if(pwnd != NULL)
      {
         if(System.get_active_guie()->get_safe_handle() == pwnd->get_safe_handle()
            || ::user::window_util::IsAscendant(System.get_active_guie()->get_safe_handle(),pwnd->get_safe_handle()))
         {
            return pwnd;
         }
         else
         {
            return NULL;
         }
      }
      return NULL;
#else

      return System.get_active_guie();

#endif

   }


   ::count system::get_application_count()
   {

      ::count c = 0;

      try
      {

         for(index iBaseSession = 0; iBaseSession < m_basesessionptra.get_count(); iBaseSession++)
         {

            try
            {

               c += m_basesessionptra[iBaseSession].appptra().get_count();

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {

      }

      return c;

   }


   application_ptra system::get_appptra()
   {

      application_ptra appptra;

      try
      {

         for(index iBaseSession = 0; iBaseSession < m_basesessionptra.get_count(); iBaseSession++)
         {

            try
            {

               appptra += m_basesessionptra[iBaseSession].appptra();

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {


      }

      return appptra;

   }


   string system::get_ca2_module_folder()
   {

      single_lock sl(m_pmutex,true);

      return m_strCa2ModuleFolder;

   }


   string system::get_ca2_module_file_path()
   {

      string strModuleFileName;

#ifdef WINDOWSEX

      wchar_t lpszModuleFilePath[MAX_PATH + 1];

      if(GetModuleFileNameW(::GetModuleHandleA("core.dll"),lpszModuleFilePath,MAX_PATH + 1))
      {

         strModuleFileName = lpszModuleFilePath;

      }

#elif defined(METROWIN)

      throw todo(this);

#else

#ifdef LINUX

      {

         void * handle = dlopen("core.so",0);

         if(handle == NULL)
            return "";

         link_map * plm;

         dlinfo(handle,RTLD_DI_LINKMAP,&plm);

         strModuleFileName = plm->l_name;

         dlclose(handle);

         //         m_strCa2ModuleFolder = dir::name(strModuleFileName);

      }

#else

      {

         char * pszCurDir = getcwd(NULL,0);

         string strCurDir = pszCurDir;

         free(pszCurDir);

         if(App(this).file().exists(System.dir().path(strCurDir,"core.dylib")))
         {
            m_strCa2ModuleFolder = strCurDir;
            goto finishedCa2Module;
         }


         if(App(this).file().exists(System.dir().path(m_strModuleFolder,"core.dylib")))
         {
            m_strCa2ModuleFolder = m_strModuleFolder;
            goto finishedCa2Module;
         }

         strModuleFileName = App(this).dir().pathfind(getenv("LD_LIBRARY_PATH"),"core.dylib","rfs"); // readable - normal file - non zero sized

      }

   finishedCa2Module:;

#endif

#endif

      return strModuleFileName;


   }


   string system::get_module_folder()
   {

      return m_strModuleFolder;

   }


   string system::get_module_file_path()
   {

#ifdef WINDOWSEX

      wchar_t lpszModuleFilePath[MAX_PATH + 1];

      GetModuleFileNameW(NULL,lpszModuleFilePath,MAX_PATH + 1);

      string strModuleFileName(lpszModuleFilePath);

      return strModuleFileName;

#elif defined(METROWIN)

      return "m_app.exe";

#else

      char * lpszModuleFilePath = br_find_exe_dir("app");

      if(lpszModuleFilePath == NULL)
         return "";

      string strModuleFileName(lpszModuleFilePath);

      free(lpszModuleFilePath);

      return strModuleFileName;

#endif

   }


   string system::get_module_title()
   {

      return file().title_(get_module_file_path());

   }


   string system::get_module_name()
   {

      return file().name_(get_module_file_path());

   }




} // namespace base






uint32_t _thread_proc_start_system(void * p)
{

   ::base::system * psystem = (::base::system *)p;

   return psystem->main();

}

CLASS_DECL_BASE void __start_system(::base::system * psystem)
{

   ::create_thread(NULL,0,&_thread_proc_start_system,(LPVOID)psystem,0,0);

}
