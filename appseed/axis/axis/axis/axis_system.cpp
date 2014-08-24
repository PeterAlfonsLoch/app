#include "framework.h"


void dappy(const char * psz);

#ifdef WINDOWSEX


CLASS_DECL_AXIS HMONITOR GetUiMonitorHandle(HWND hwnd)
{

   return MonitorFromWindow(hwnd,MONITOR_DEFAULTTOPRIMARY);

}


CLASS_DECL_AXIS HMONITOR GetPrimaryMonitorHandle()
{

   const POINT ptZero ={0,0};

   return MonitorFromPoint(ptZero,MONITOR_DEFAULTTOPRIMARY);

}


CLASS_DECL_AXIS bool GetPrimaryMonitorRect(LPRECT lprect)
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


namespace axis
{


   system::system(sp(::aura::application) papp):
      ::aura::system(this),
      m_libraryDraw2d(this)
   {
      
      m_ptwf = NULL;

      m_psimpleui = NULL;

#if defined(METROWIN) || defined(APPLE_IOS)
      m_posdata = new os_data();
#endif

      set_app(this);


      m_paxissystem = this;

      if(papp == NULL)
      {

         oprop("parent_system") = (sp(element)) NULL;

      }
      else
      {

         oprop("parent_system") = papp->m_paxissystem;

      }




      
#ifdef WINDOWS
      m_pmutexDc = NULL;
      m_pdevicecontext = NULL;
#endif

      __node_axis_factory_exchange(this);

      m_bSystemSynchronizedCursor = true;

      m_bSystemSynchronizedScreen = true;

      ::draw2d::dib::static_initialize();

      m_pschemaLayeredFrame = new ::user::schema_layered_frame;

   }


   void system::construct(const char * pszAppId)
   {

      ::axis::application::construct(pszAppId);

   }


   system::~system()
   {

   }



   bool system::process_initialize()
   {




      enum_display_monitors();

      if(!::aura::system::process_initialize())
         return false;


      if(!::axis::application::process_initialize())
         return false;


#ifdef WINDOWSEX

      m_spwindow = canew(interaction_impl(this));

#endif

      m_spos.alloc(allocer());


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

      dappy(string(typeid(*this).name()) + " : Going to ::axis::system::m_spwindow->create_window_ex : " + ::str::from(m_iReturnCode));

      if(!m_spwindow->create_window_ex(0,NULL,NULL,0,null_rect(),NULL,"::axis::system::interaction_impl::no_twf"))
      {

         dappy(string(typeid(*this).name()) + " : ::axis::system::m_spwindow->create_window_ex failure : " + ::str::from(m_iReturnCode));

         return false;

      }

#endif

/*      dappy(string(typeid(*this).name()) + " : Going to ::axis::session " + ::str::from(m_iReturnCode));


      m_paxissession = new ::axis::session(this);

      if(m_paxissession == NULL)
         return false;

      m_paxissession->construct(this,0);


      if(!m_paxissession->begin_synch(&m_iReturnCode))
      {
         return false;
      }

      dappy(string(typeid(*this).name()) + " : ::axis::session OK " + ::str::from(m_iReturnCode));*/

      return true;

   }


   bool system::initialize2()
   {

      if(!::aura::system::initialize2())
         return false;

      if(!::axis::application::initialize2())
         return false;


      return true;

   }


   bool system::initialize_instance()
   {

      if(!::aura::system::initialize_instance())
         return false;

      if(!::axis::application::initialize_instance())
         return false;

      return true;

   }


   bool system::finalize()
   {

      __wait_threading_count_except(this,::millis((5000) * 77));



      bool bOk = false;


      try
      {

         bOk = ::axis::application::finalize();

      }
      catch(...)
      {

         bOk = false;

      }

      try
      {

         bOk = ::aura::system::finalize();

      }
      catch(...)
      {

         bOk = false;

      }


      return bOk;

   }


   int32_t system::exit_instance()
   {

      __wait_threading_count(::millis((5000) * 8));

      int32_t iRet = 0;



      try
      {

         iRet = ::axis::application::exit_instance();

      }
      catch(...)
      {

      }



#ifdef METROWIN
      m_pdevicecontext = nullptr;

      m_pmutexDc.release();
#endif

#ifdef WINDOWSEX



      try
      {

         m_spwindow.release();

      }
      catch(...)
      {

         m_iReturnCode = -2;

      }
#endif

      try
      {

         iRet = ::aura::system::exit_instance();

      }
      catch(...)
      {

      }



      return iRet;

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

         return ::aura::SimpleDebugReport(iReportType,pszFileName,iLineNumber,pszModuleName,pszFormat,list);

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

//         if(list != NULL)
         {

            str2.FormatV(pszFormat,list);

         }
    //     else
         {

  //          str2 = pszFormat;

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


   void system::on_allocation_error(sp(::aura::application) papp,sp(type) info)
   {
      UNREFERENCED_PARAMETER(papp);
      UNREFERENCED_PARAMETER(info);
   }

   ::datetime::departament & system::datetime()
   {

      return *m_pdatetime;

   }



   sp(::user::window_draw) system::get_twf()
   {

      return m_ptwf;

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


   sp(::aura::session) system::query_session(index iEdge)
   {

      return NULL;

   }


   void system::appa_load_string_table()
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

//      for(int32_t i = 0; i < appptra().get_size(); i++)
  //    {
    //     sp(::aura::application) papp = appptra()(i);
      //   papp->load_string_table();
      //}

   }

   void system::appa_set_locale(const char * pszLocale,::action::context actioncontext)
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

//      for(int32_t i = 0; i < appptra().get_size(); i++)
 //     {
  //       sp(::aura::application) papp = appptra()(i);
  //       papp->set_locale(pszLocale,actioncontext);
  //    }

   }

   void system::appa_set_schema(const char * pszStyle,::action::context actioncontext)
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

//      for(int32_t i = 0; i < appptra().get_size(); i++)
  //    {
  //       sp(::aura::application) papp = appptra()(i);
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

      sp(::user::window_draw) pwindow = alloc(System.type_info < ::user::window_draw >());

      m_ptwf = pwindow;

      m_ptwf->add_ref();

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

#elif defined(MACOS)
      
      return GetScreenCount();
      
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


      get_window_rect(m_posdata->m_pwindow,lprect);


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

      GetScreenRect(lprect, iMonitor);

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

      return get_monitor_rect(iWkspace,lprect);

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

      GetWkspaceRect(lprect, iWkspace);
      
//      lprect->top += ::mac::get_system_main_menu_bar_height();
  //    lprect->bottom -= ::mac::get_system_dock_height();

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

#ifdef WINDOWSEX


   system::interaction_impl::interaction_impl(sp(::aura::application) papp):
      element(papp),
      ::user::interaction(papp)
   {

   }

   void system::interaction_impl::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::interaction::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_SETTINGCHANGE,pdispatch,this,&::axis::system::interaction_impl::_001MessageHub);
      IGUI_WIN_MSG_LINK(WM_DISPLAYCHANGE,pdispatch,this,&::axis::system::interaction_impl::_001MessageHub);

   }

   void system::interaction_impl::_001MessageHub(signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);

      if(pbase != NULL)
      {

         if(pbase->m_uiMessage == WM_DISPLAYCHANGE ||
            (pbase->m_uiMessage == WM_SETTINGCHANGE &&
            (pbase->m_wparam == SPI_SETWORKAREA)))
         {

            System.enum_display_monitors();

            for(index i = 0; i < System.frames().get_count(); i++)
            {

               try
               {

                  System.frames()[i]->post_message(WM_APP + 1984 + 21);

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

      return frames()[0];

#endif

   }


   sp(::user::interaction) system::get_focus_guie()
   {

#if defined (METROWIN)

      return GetFocus()->m_pui;

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

         if(Application.file_exists(::dir_path(strCurDir,"core.dylib")))
         {
            m_strCa2ModuleFolder = strCurDir;
            goto finishedCa2Module;
         }


         if(Application.file_exists(::dir_path(m_strModuleFolder,"core.dylib")))
         {
            m_strCa2ModuleFolder = m_strModuleFolder;
            goto finishedCa2Module;
         }

         strModuleFileName = Application.dir().pathfind(getenv("LD_LIBRARY_PATH"),"core.dylib","rfs"); // readable - normal file - non zero sized

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

      return file_title(get_module_file_path());

   }


   string system::get_module_name()
   {

      return file_name(get_module_file_path());

   }

   colorertake5::ParserFactory & system::parser_factory()
   {

      if(m_pparserfactory == NULL)
      {

         m_pparserfactory = new colorertake5::ParserFactory(this);

      }

      return *m_pparserfactory;

   }


   string system::dir_appmatter_locator(sp(::aura::application) papp)
   {

      throw not_implemented(get_app());

   }


} // namespace axis






uint32_t _thread_proc_start_system(void * p)
{

   ::axis::system * psystem = (::axis::system *)p;

   return psystem->main();

}

CLASS_DECL_AXIS void __start_system(::axis::system * psystem)
{

   ::create_thread(NULL,0,&_thread_proc_start_system,(LPVOID)psystem,0,0);

}

#ifdef METROWIN


namespace axis
{


   CLASS_DECL_AXIS bool get_window_rect(::axis::system_window ^ pwindow,RECTD * lprect)
   {

      Windows::Foundation::Rect rect =  pwindow->get_window_rect();

      lprect->left = rect.X;
      lprect->top = rect.Y;
      lprect->right = lprect->left + rect.Width;
      lprect->bottom = lprect->top + rect.Height;

      return true;
   }


   CLASS_DECL_AXIS bool get_window_rect(::axis::system_window ^ pwindow,LPRECT lprect)
   {

      rectd r;

      if(!get_window_rect(pwindow,&r))
         return false;

      if(!::copy(lprect,r))
         return false;

      return true;

   }


} // namespace axis


#endif



