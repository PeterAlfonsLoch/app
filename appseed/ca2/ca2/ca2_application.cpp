#include "framework.h"


namespace ca2 // namespace cube + namespace cube + cube2 + cube + ca8
{


   CLASS_DECL_ca2 LPFN_instantiate_application g_lpfn_instantiate_application = NULL;


   application::application()
   {

      m_puserex = NULL;

      m_dir.set_app(this);
      m_file.set_app(this);
      m_http.set_app(this);

      m_bIfs            = true;
      m_bLicense     = false;

   }


   application::~application()
   {
   }

   ::ca::application * application::get_system()
   {
      return new application();
   }

   void application::construct()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
   }


   bool application::initialize1()
   {
      m_puserex = new ::userex::userex();

      m_puserex->construct(this);

      if(!m_puserex->initialize1())
         return false;

      m_dwAlive = ::get_tick_count();

      if(!::cubebase::application::initialize1())
         return false;

      m_dwAlive = ::get_tick_count();

      enum_display_monitors();


      rect rect;
      get_monitor_rect(0, &rect);
      for(int32_t i = 1; i < get_monitor_count(); i++)
      {
         class rect rectMonitor;
         get_monitor_rect(i, &rectMonitor);
         rect.unite(rect, &rectMonitor);
      }

#ifdef WINDOWSEX

      m_monitorinfoaDesk = m_monitorinfoa;

#else

      //throw todo(get_app());

#endif

      /*if(m_monitorinfoa.get_size() == 1)
      {
         MONITORINFO mi = m_monitorinfoaDesk.last_element();
         m_monitorinfoaDesk[0].rcMonitor.right = mi.rcMonitor.right /2;
         m_monitorinfoaDesk.add(mi);
         m_monitorinfoaDesk.last_element().rcMonitor.left = mi.rcMonitor.right / 2;

      }*/

      /*if(get_twf() != NULL)
      {
         get_twf()->Update(rect);
      }*/


      return true;


      if(fontopus().m_puser == NULL &&
         (App(this).directrix().m_varTopicQuery.has_property("install")
         || App(this).directrix().m_varTopicQuery.has_property("uninstall")))
      {

         if(!fontopus().create_system_user("system"))
            return false;

      }

      if(!::cubebase::application::initialize1())
         return false;


      return true;


   }





   bool application::initialize2()
   {

      if(!::cubebase::application::initialize2())
         return false;

      if(!m_puserex->initialize2())
         return false;

      return true;

   }





   bool application::initialize()
   {


      m_dwAlive = ::get_tick_count();

      if(is_system())
      {
         System.factory().creatable_small < keyboard_layout > ();
      }

      if(!::cubebase::application::initialize())
         return false;

      m_puinteraction = new ::uinteraction::uinteraction();

      m_puinteraction->construct(this);

      if(!m_puinteraction->initialize())
         return false;

      m_puserbase = new ::userbase::userbase();

      m_puserbase->construct(this);

      if(!m_puserbase->initialize())
         return false;

      m_pfilemanager = new ::filemanager::filemanager();

      ::ca::application::m_pfilemanager = m_pfilemanager;

      m_pfilemanager->construct(this);

      if(!m_pfilemanager->initialize())
         return false;

      m_pmail = new ::mail::mail();

      m_pmail->construct(this);

      if(!m_pmail->initialize())
         return false;

      m_dwAlive = ::get_tick_count();





      m_dwAlive = ::get_tick_count();

      m_splicense = new class ::fontopus::license(this);


      if(!is_system())
      {
         System.register_bergedge_application(this);
      }


      m_dwAlive = ::get_tick_count();

      ensure_app_interest();

      return true;

   }


   bool application::initialize_instance()
   {
      if(!::cubebase::application::initialize_instance())
         return false;

      if(m_psession != NULL && m_psession->m_pbergedge != NULL)
      {

         Session.m_pappCurrent = this;

      }

      return true;
   }

   int32_t application::exit_instance()
   {
      m_iReturnCode = 0;

      try
      {
         m_iReturnCode = ::cubebase::application::exit_instance();
      }
      catch(...)
      {
      }

      try
      {
         System.unregister_bergedge_application(this);
      }
      catch(...)
      {
      }

      return m_iReturnCode;

   }

   void application::_001OnFileNew()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      ::cubebase::application::_001OnFileNew();
   }


   bool application::bergedge_start()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::cubebase::application::bergedge_start();
   }

   bool application::on_install()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::cubebase::application::on_install();
   }

   bool application::on_uninstall()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::cubebase::application::on_uninstall();
   }


   void application::on_request(::ca::create_context * pcreatecontext)
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::cubebase::application::on_request(pcreatecontext);


   }

   bool application::is_serviceable()
   {


      string strId = m_strId;

      char chFirst = '\0';

      if(strId.get_length() > 0)
      {

         chFirst = strId[0];

      }

      return ::cubebase::application::is_serviceable();

   }

   service_base * application::allocate_new_service()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::cubebase::application::allocate_new_service();
   }


   ::user::document_interface * application::_001OpenDocumentFile(var varFile)
   {
      string strId = m_strId;
      char chFirst = '\0';
      if(strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      return ::cubebase::application::_001OpenDocumentFile(varFile);

   }


   int32_t application::run()
   {

      return ::cubebase::application::run();

   }

   string application::message_box(const char * pszMatter, ::ca::property_set & propertyset)
   {
      class message_box box(this);
      box.show(pszMatter, &propertyset);
      return box.m_strResponse;
   }

   int32_t application::simple_message_box(::user::interaction * pwndOwner, const char * pszMessage, UINT fuStyle)
   {
      class message_box box(this);

      ::ca::property_set propertyset;
      propertyset["message"] = pszMessage;

      string strMatter;
      if(fuStyle & MB_YESNOCANCEL)
      {
        strMatter = "system\\user\\simple_message_box\\yesnocancel.xhtml";
      }
      else
      {
         strMatter = "system\\user\\simple_message_box\\ok.xhtml";
      }
      try
      {
         if(!box.show(strMatter, &propertyset))
         {
            string strMessage = pszMessage;
            strMessage.replace("<br>", "\r\n");
            return MessageBox(pwndOwner == NULL ? (oswindow) ::ca::null() : pwndOwner->get_handle(), strMessage, m_strAppName, fuStyle);
         }
      }
      catch(...)
      {
         string strMessage = pszMessage;
         strMessage.replace("<br>", "\r\n");
         return MessageBox(pwndOwner == NULL ? (oswindow) ::ca::null() : pwndOwner->get_handle(), strMessage, m_strAppName, fuStyle);
      }
      if(box.m_strResponse == "ok")
      {
         return IDOK;
      }
      else if(box.m_strResponse == "yes")
      {
         return IDYES;
      }
      else if(box.m_strResponse == "no")
      {
         return IDNO;
      }
      else if(box.m_strResponse == "cancel")
      {
         return IDCANCEL;
      }
      if(fuStyle & MB_YESNOCANCEL)
      {
         return IDCANCEL;
      }
      else
      {
         return 0;
      }
   }

   int32_t application::simple_message_box_timeout(::user::interaction * puiOwner, const char * pszMessage, int32_t iTimeout, UINT fuStyle)
   {
      UNREFERENCED_PARAMETER(puiOwner);

      class message_box box(this);

      ::ca::property_set propertyset;
      propertyset["message"] = pszMessage;
      propertyset["simple_message_box_timeout_ms"] = iTimeout;

      string strMatter;
      if(fuStyle & MB_YESNOCANCEL)
      {
        strMatter = "system\\user\\simple_message_box\\yesnocancel.xhtml";
      }
      else
      {
         strMatter = "system\\user\\simple_message_box\\ok.xhtml";
      }
      box.show(strMatter, &propertyset);
      if(box.m_strResponse == "ok")
      {
         return IDOK;
      }
      else if(box.m_strResponse == "yes")
      {
         return IDYES;
      }
      else if(box.m_strResponse == "no")
      {
         return IDNO;
      }
      else if(box.m_strResponse == "cancel")
      {
         return IDCANCEL;
      }
      if(fuStyle & MB_YESNOCANCEL)
      {
         return IDCANCEL;
      }
      else
      {
         return 0;
      }
   }

   int32_t application::track_popup_menu(const char * pszMatter, point pt, ::user::interaction * puie)
   {
      UNREFERENCED_PARAMETER(pszMatter);
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(puie);
      return 1;
   }

   bool application::set_keyboard_layout(const char * pszPath, bool bUser)
   {
      return user()->keyboard().load_layout(pszPath, bUser);
   }


   bool application::get_fs_size(string & strSize, const char * pszPath, bool & bPending)
   {
      int64_t i64Size;
      if(!get_fs_size(i64Size, pszPath, bPending))
      {
         strSize.Empty();
         return false;
      }
      if(i64Size > 1024 * 1024 * 1024)
      {
         double d = (double) i64Size / (1024.0 * 1024.0 * 1024.0);
         strSize.Format("%0.2f GB", d);
      }
      else if(i64Size > 1024 * 1024)
      {
         double d = (double) i64Size / (1024.0 * 1024.0);
         strSize.Format("%0.1f MB", d);
      }
      else if(i64Size > 1024)
      {
         double d = (double) i64Size / (1024.0);
         strSize.Format("%0.0f KB", d);
      }
      else if(i64Size > 0)
      {
         strSize.Format("1 KB");
      }
      else
      {
         strSize.Format("0 KB");
      }
      if(bPending)
      {
         strSize = "~" + strSize;
      }
      return true;
   }

   bool application::get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending)
   {
      db_server * pcentral = dynamic_cast < db_server * > (&System.m_simpledb.db());
      if(pcentral == NULL)
         return false;
      return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size, pszPath, bPending);
   }

   void application::data_on_after_change(::ca::signal_object * pobj)
   {
      SCAST_PTR(::database::change_event, pchange, pobj);
      if(pchange->m_key.m_idKey == "ca2")
      {
         if(pchange->m_key.m_idIndex  == "savings")
         {
            pchange->data_get(savings().m_eresourceflagsShouldSave);
         }
      }
   }


   bool application::final_handle_exception(::ca::exception & e)
   {
      base_exception * pbe = dynamic_cast < standard_exception * > (&e);
      if(pbe != NULL)
      {
         TRACE(pbe->stack_trace());
      }
      return ::cubebase::application::final_handle_exception(e);
   }

   void application::enum_display_monitors()
   {

#ifdef WINDOWSEX

      m_monitorinfoa.remove_all();

      ::EnumDisplayMonitors(NULL, NULL, &application::monitor_enum_proc, (LPARAM) ( dynamic_cast < ::cube::application * > (this)));

#else

      // todo
//      m_monitorinfoa.remove_all();


#endif

   }

#ifdef WINDOWSEX
   BOOL CALLBACK application::monitor_enum_proc(
     HMONITOR hmonitor,
     HDC hdcMonitor,
     LPRECT lprcMonitor,
     LPARAM dwData)
   {
      cube::application * papp = (cube::application *) dwData;
      papp->monitor_enum(hmonitor, hdcMonitor, lprcMonitor);
      return TRUE; // to enumerate all
   }
#endif

#ifdef WINDOWSEX
   void application::monitor_enum(
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

   ::count application::get_monitor_count()
   {
#ifdef WINDOWSEX
      return m_monitorinfoa.get_size();
#else
      // throw todo(get_app());
      return 1;
#endif
   }

   bool application::get_monitor_rect(index i, LPRECT lprect)
   {
      if(i < 0 || i >= get_monitor_count())
         return false;
#ifdef WINDOWSEX
      *lprect = m_monitorinfoa[i].rcMonitor;
#elif defined(METROWIN)

      return System.get_window_rect(lprect);

#elif defined(LINUX)

      mutex_lock sl(user_mutex(), true);

      Display * d=XOpenDisplay(NULL);


      //throw todo(get_app());
      lprect->left = 0;
      lprect->top = 0;
      lprect->right = WidthOfScreen(DefaultScreenOfDisplay(d));
      lprect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d));


      XCloseDisplay(d);

#elif defined(MACOS)


      throw todo(get_app());




#else
      throw todo(get_app());
      ::GetWindowRect(::GetDesktopWindow(), lprect);
#endif
      return true;
   }


   ::count application::get_desk_monitor_count()
   {
#ifdef WINDOWSEX
      return m_monitorinfoaDesk.get_size();
#else
      throw todo(get_app());
      return 1;
#endif
   }

   bool application::get_desk_monitor_rect(index i, LPRECT lprect)
   {
      if(i < 0 || i >= get_desk_monitor_count())
         return false;
#ifdef WINDOWSEX
      *lprect = m_monitorinfoaDesk[i].rcMonitor;
#elif defined(METROWIN)
      throw todo(get_app());
#elif defined(LINUX)
      throw todo(get_app());
#elif defined(MACOS)
      throw todo(get_app());
#else
      throw todo(get_app());
      ::GetWindowRect(::GetDesktopWindow(), lprect);
#endif
      return true;
   }


   /*bool application::is_licensed(const char * pszId, bool bInteractive)
   {
   return license().has(pszId, bInteractive);
   }

   class ::fontopus::license & application::license()
   {
   return m_splicense;
   }*/

   /*
   ::ca::application * pgenapp = dynamic_cast < ::ca::application * > (papp);
   if(pgenapp != NULL)
   {
   try
   {
   pgenapp->m_dwAlive = ::get_tick_count();
   }
   catch(...)
   {
   }
   }
   */




   /*class ::fs::data * application::fs()
   {
   return m_spfsdata;
   }*/


   void application::set_title(const char * pszTitle)
   {

      Bergedge.set_app_title(m_strInstallType, m_strAppName, pszTitle);

   }


   /*bool application::on_install()
   {
   return ::ca::fontopus::application::on_install();
   }

   bool application::on_uninstall()
   {
   return ::ca::fontopus::application::on_uninstall();
   }

   bool application::is_serviceable()
   {
   return ::ca::fontopus::application::is_serviceable();
   }

   service_base * application::allocate_new_service()
   {
   return ::ca::fontopus::application::allocate_new_service();
   }*/

   bool application::_001CloseApplicationByUser(::user::interaction * pwndExcept)
   {

      // attempt to save all documents
      if(!save_all_modified())
         return false;     // don't close it

      // hide the application's windows before closing all the documents
      HideApplication();

      // close all documents first
      close_all_documents(FALSE);


      userbase()._001CloseAllDocuments(FALSE);


      // there are cases where destroying the documents may destroy the
      //  main ::ca::window of the application.
      //bool b::ca::ContextIsDll = afxContextIsDLL;
      //if (!b::ca::ContextIsDll && papp->GetVisibleFrameCount() <= 0)
      if(user()->GetVisibleTopLevelFrameCountExcept(pwndExcept) <= 0)
      {

         post_thread_message(WM_QUIT, 0, 0);

      }

      return true;

   }


#ifdef WINDOWSEX

   BOOL CALLBACK application::GetAppsEnumWindowsProc(oswindow oswindow, LPARAM lParam)
   {
      application * papp = (application *) lParam;
      uint32_t dwptr;
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 1, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 2)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 2, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 4)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 4, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 5)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 5, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 8)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 8, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 11)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 11, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 23)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 23, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 33)
      {
         return TRUE;
      }
      if(::SendMessageTimeout(oswindow, WM_APP + 2000, 33, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr))
      {
         if(dwptr == 1)
         {
            if(papp->m_straAppInterest.find_first("command") >= 0)
               papp->m_mapAppInterest["command"] = oswindow;
         }
         else if(dwptr == 67)
         {
            if(papp->m_straAppInterest.find_first("winactionarea") >= 0)
               papp->m_mapAppInterest["winactionarea"] = oswindow;
         }
         else if(dwptr == 68)
         {
            if(papp->m_straAppInterest.find_first("winutil") >= 0)
               papp->m_mapAppInterest["winutil"] = oswindow;
         }
         else if(dwptr == 69)
         {
            if(papp->m_straAppInterest.find_first("windesk") >= 0)
               papp->m_mapAppInterest["windesk"] = oswindow;
         }
      }

      return TRUE;

   }

#endif


   void application::update_app_interest()
   {

#ifdef WINDOWSEX

      EnumWindows(GetAppsEnumWindowsProc, (LPARAM) (application *) (this));

#else

      throw todo(get_app());

#endif

   }

   void application::ensure_app_interest()
   {

#ifndef METROWIN

      for(int32_t i = 0; i < m_straAppInterest.get_count(); i++)
      {
         if(m_straAppInterest[i] != m_strAppName && !::IsWindow(m_mapAppInterest[m_straAppInterest[i]]))
         {
            System.assert_running_local(m_straAppInterest[i]);
         }
      }

#else

      //throw todo(get_app());

#endif

   }


   oswindow application::get_ca2_app_wnd(const char * psz)
   {

      return m_mapAppInterest[psz];

   }






   void application::on_exclusive_instance_local_conflict()
   {
      m_straAppInterest.add(m_strAppName);
      update_app_interest();
      oswindow oswindow = get_ca2_app_wnd(m_strAppName);
      if(oswindow != NULL)
      {
#ifndef METROWIN
         ::ShowWindow(oswindow, SW_RESTORE);
#endif
      }
   }

   int32_t application::send_simple_command(const char * psz, void * osdataSender)
   {
      string strApp;
      stringa stra;
      stra.add_tokens(psz, "::", true);
      if(stra.get_size() > 0)
      {
         strApp = stra[0];
         oswindow oswindow = get_ca2_app_wnd(strApp);
         if(oswindow != NULL)
         {
            return send_simple_command((void *) oswindow, psz, osdataSender);
         }
      }
      return -1;
   }

   int32_t application::send_simple_command(void * osdata, const char * psz, void * osdataSender)
   {
#ifdef WINDOWSEX
      ::oswindow oswindow = (::oswindow) osdata;
      if(!::IsWindow(oswindow))
         return -1;
      COPYDATASTRUCT cds;
      memset(&cds, 0, sizeof(cds));
      cds.dwData = 198477;
      cds.cbData = (uint32_t) strlen(psz);
      cds.lpData = (PVOID) psz;
      return (int32_t) SendMessage(oswindow, WM_COPYDATA, (WPARAM) osdataSender, (LPARAM) &cds);
#else
      throw todo(get_app());
#endif
   }

   void application::request(::ca::create_context * pcreatecontext)
   {
      ::cubebase::application::request(pcreatecontext);
   }

   void application::defer_add_document_template(::document_template * ptemplate)
   {
      m_puserbase->defer_add_document_template(ptemplate);
   }


} // namespace ca2 + namespace cube + cube2 + cube + ca8






