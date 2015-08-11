//#include "framework.h" // from "axis/user/user.h"
//#include "base/user/user.h"

#ifdef METROWIN

CLASS_DECL_IMPORT void draw2d_factory_exchange(::aura::application * papp);

#endif

namespace base
{


   //UINT application::APPM_LANGUAGE = WM_APP + 117;
   //WPARAM application::WPARAM_LANGUAGE_UPDATE = 1;


   application::application()
   {

      m_peventReady = NULL;


#ifdef WINDOWS

      m_hinstance                = NULL;

#endif

      if(m_pauraapp != NULL)
      {

         m_paxisapp              = m_pauraapp->m_paxisapp;

      }

      m_pbaseapp                 = this;

      if(m_pauraapp != NULL)
      {

         m_paxissystem           = m_pauraapp->m_paxissystem;

         if(m_pauraapp->m_pbasesession == NULL && m_paxissystem != NULL)
         {

            m_pbasesession       = m_paxissystem->m_pbasesession;

         }
         else
         {

            m_pbasesession       = m_pauraapp->m_pbasesession;

         }

#ifdef WINDOWS

         m_hinstance             = m_pauraapp->m_hinstance;

#endif

      }
      else
      {

         m_paxissystem           = NULL;

      }

      m_bBaseProcessInitialize         = false;
      m_bBaseProcessInitializeResult   = false;

      m_bBaseInitialize1               = false;
      m_bBaseInitialize1Result         = false;

      m_bBaseInitialize                = false;
      m_bBaseInitializeResult          = false;

      m_bBaseInitializeInstance        = false;
      m_bBaseInitializeInstanceResult  = false;




   }

   application::~application()
   {
   }



   ::user::interaction * application::window_from_os_data(void * pdata)
   {

      if(pdata == NULL)
      {

         return NULL;

      }

      return window_from_handle((oswindow)pdata);

   }


   sp(::user::interaction) application::release_capture_uie()
   {

#if defined(LINUX)

      oswindow oswindowCapture = ::GetCapture();
      if(oswindowCapture == NULL)
         return NULL;
      return oswindowCapture->get_user_interaction()->ReleaseCapture();

#elif defined(METROWIN)

      oswindow oswindowCapture = ::GetCapture();
      if(oswindowCapture == NULL)
         return NULL;
      return oswindowCapture->m_pui->ReleaseCapture();

#elif defined(WINDOWS)

      oswindow oswindowCapture = ::GetCapture();
      if(oswindowCapture == NULL)
         return NULL;
      return System.window_from_os_data(oswindowCapture)->ReleaseCapture();

#elif defined(APPLEOS)

      oswindow oswindowCapture = ::GetCapture();
      if(oswindowCapture == NULL)
         return NULL;
      return oswindowCapture->get_user_interaction()->ReleaseCapture();

#else

      ::exception::throw_not_implemented(get_app());

#endif

   }


   sp(::user::interaction) application::get_capture_uie()
   {

#if defined(METROWIN)

      oswindow oswindowCapture = ::GetCapture();

      if(oswindowCapture == NULL)
         return NULL;

      ::user::interaction * pui = oswindowCapture->window();

      if(pui == NULL)
         return NULL;

      return pui->GetCapture();

#elif defined(WINDOWS) || defined(APPLE_IOS)

      oswindow oswindowCapture = ::GetCapture();

      if(oswindowCapture == NULL)
         return NULL;

      sp(::user::interaction) pui = System.window_from_os_data(oswindowCapture);

      if(pui == NULL)
         return NULL;

      return pui->GetCapture();

#else

      //      ::exception::throw_not_implemented(get_app());

      oswindow oswindowCapture = ::GetCapture();

      if(oswindowCapture == NULL)
         return NULL;

      return window_from_handle(::GetCapture());

#endif

   }


   //   void application::assert_valid() const
   //   {
   //
   //      thread::assert_valid();
   //
   //
   //   }
   //
   //   void application::dump(dump_context & dumpcontext) const
   //   {
   //
   //      thread::dump(dumpcontext);
   //
   //#ifdef WINDOWS
   //
   //      dumpcontext << "m_hinstance = " << (void *)m_hinstance;
   //
   //#endif
   //
   //      //dumpcontext << "\nm_strCmdLine = " << m_strCmdLine;
   //      //dumpcontext << "\nm_nCmdShow = " << m_nCmdShow;
   //      dumpcontext << "\nm_bHelpMode = " << m_strAppName;
   //
   //      dumpcontext << "\n";
   //
   //   }
   //
   //
   //
   //
   //   bool application::is_system()
   //   {
   //
   //      return false;
   //
   //   }
   //
   //   bool application::is_session()
   //   {
   //
   //      return false;
   //
   //   }
   //
   //
   //   bool application::is_serviceable()
   //   {
   //
   //      return false;
   //
   //   }
   //
   //
   //
   //
   //   void application::process_message_filter(int32_t code,signal_details * pobj)
   //   {
   //
   //      if(pobj == NULL)
   //         return;   // not handled
   //
   //      SCAST_PTR(::message::base,pbase,pobj);
   //
   //      sp(::user::frame_window) pTopFrameWnd;
   //      //::user::interaction * pMainWnd;
   //      ::user::interaction * pMsgWnd;
   //      switch(code)
   //      {
   //      //case MSGF_DDEMGR:
   //         // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
   //         //  never call the next hook.
   //         // By returning FALSE, the message will be dispatched
   //         //  instead (the default behavior).
   //         //return;
   //
   //      case MSGF_MENU:
   //         pMsgWnd = dynamic_cast < ::user::interaction * > (pbase->m_pwnd);
   //         if(pMsgWnd != NULL)
   //         {
   //            pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
   //            if(pTopFrameWnd != NULL && pTopFrameWnd->IsTracking() &&
   //               pTopFrameWnd->m_bHelpMode)
   //            {
   //               //pMainWnd = __get_main_window();
   //               //if((m_puiMain != NULL) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
   //               //{
   //               //   //                  pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
   //               //   pbase->m_bRet = true;
   //               //   return;
   //               //}
   //            }
   //         }
   //         // fall through...
   //
   //      case MSGF_DIALOGBOX:    // handles message boxes as well.
   //         //pMainWnd = __get_main_window();
   //         if(code == MSGF_DIALOGBOX && m_puiActive != NULL &&
   //            pbase->m_uiMessage >= WM_KEYFIRST && pbase->m_uiMessage <= WM_KEYLAST)
   //         {
   //            //// need to translate messages for the in-place container
   //            //___THREAD_STATE* pThreadState = __get_thread_state();
   //            //ENSURE(pThreadState);
   //
   //            //if (pThreadState->m_bInMsgFilter)
   //            //   return;
   //            //pThreadState->m_bInMsgFilter = TRUE;    // avoid reentering this code
   //            //if (m_puiActive->is_window_enabled())
   //            //{
   //            //   pre_translate_message(pobj);
   //            //   if(pobj->m_bRet)
   //            //   {
   //            //      pThreadState->m_bInMsgFilter = FALSE;
   //            //      return;
   //            //   }
   //            //}
   //            //pThreadState->m_bInMsgFilter = FALSE;    // ok again
   //         }
   //         break;
   //      }
   //      // default to not handled
   //
   //   }
   //
   //
   //
   //   bool application::verb()
   //   {
   //
   //      axiom()->run();
   //
   //      return true;
   //
   //   }
   //
   //
   //   //ptr_array < ::user::interaction > application::frames()
   //   //{
   //
   //   //   return m_framea.base_ptra();
   //
   //   //}
   //
   //   bool application::get_frame(::user::interaction * & pui)
   //   {
   //
   //      synch_lock sl(&m_mutexFrame);
   //
   //      if(m_uiptraFrame.get_count() <= 0)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      if(pui == NULL)
   //      {
   //
   //         pui = m_uiptraFrame[0];
   //
   //         return true;
   //
   //      }
   //      else
   //      {
   //
   //         for(index i = m_uiptraFrame.get_upper_bound(); i >= 0; i--)
   //         {
   //
   //            if(m_uiptraFrame[i] == pui)
   //            {
   //
   //               i++;
   //
   //               if(i < m_uiptraFrame.get_count())
   //               {
   //
   //                  pui = m_uiptraFrame[i];
   //
   //                  return true;
   //
   //               }
   //               else
   //               {
   //
   //                  return false;
   //
   //               }
   //
   //            }
   //
   //         }
   //
   //      }
   //
   //      return false;
   //
   //   }
   //
   //
   //   void application::add_frame(sp(::user::interaction) pwnd)
   //   {
   //
   //      synch_lock sl(&m_mutexFrame); // recursive lock (on m_framea.add(pwnd)) but m_puiMain is "cared" by m_frame.m_mutex
   //
   //      if(m_uiptraFrame.add_unique(pwnd))
   //      {
   //
   //         System.defer_create_system_frame_window();
   //
   //         Session.on_create_frame_window();
   //
   //         if(m_puiMain == NULL)
   //         {
   //
   //            m_puiMain = pwnd;
   //
   //         }
   //
   //      }
   //
   //   }
   //
   //
   //   void application::remove_frame(sp(::user::interaction) pwnd)
   //   {
   //
   //      synch_lock sl(&m_mutexFrame); // recursive lock (on m_framea.remove(pwnd)) but m_puiMain is "cared" by m_frame.m_mutex
   //
   //      if(m_puiMain == pwnd)
   //      {
   //
   //         m_puiMain = NULL;
   //
   //      }
   //
   //      m_uiptraFrame.remove(pwnd);
   //
   //
   //   }
   //
   //
   //
   //
   //   ::user::interaction * application::window_from_os_data(void * pdata)
   //   {
   //
   //      return window_from_handle((oswindow)pdata);
   //
   //   }
   //
   //
   //   void application::DoWaitCursor(int32_t nCode)
   //   {
   //
   //      if(nCode < 0)
   //      {
   //
   //         m_iWaitCursorCount = 0;
   //         ShowWaitCursor(false);
   //
   //      }
   //      else if(nCode == 0)
   //      {
   //
   //         if(m_iWaitCursorCount > 0)
   //         {
   //            m_iWaitCursorCount--;
   //         }
   //
   //         if(m_iWaitCursorCount > 0)
   //         {
   //
   //            ShowWaitCursor(true);
   //
   //         }
   //
   //         m_iWaitCursorCount = 0;
   //         ShowWaitCursor(false);
   //
   //      }
   //      else
   //      {
   //
   //         if(m_iWaitCursorCount < 0)
   //         {
   //            m_iWaitCursorCount = 0;
   //         }
   //
   //         m_iWaitCursorCount++;
   //
   //         ShowWaitCursor(true);
   //
   //      }
   //
   //
   //
   //   }
   //
   //   void application::ShowWaitCursor(bool bShow)
   //   {
   //
   //      if(m_pimpl == NULL)
   //         return;
   //
   //      m_pimpl->ShowWaitCursor(bShow);
   //
   //   }
   //
   //
   //
   //   void application::construct(const char * pszAppId)
   //   {
   //
   //   }
   //
   //
   //
   //   void application::TermThread(HINSTANCE hInstTerm)
   //   {
   //
   //      ::exception::throw_interface_only(this);
   //
   //   }
   //
   //
   //
   //   sp(::user::interaction) application::FindWindow(const char * lpszClassName,const char * lpszWindowName)
   //   {
   //
   //      ::exception::throw_interface_only(this);
   //
   //      return NULL;
   //
   //   }
   //
   //
   //   sp(::user::interaction) application::FindWindowEx(oswindow oswindowParent,oswindow oswindowChildAfter,const char * lpszClass,const char * lpszWindow)
   //   {
   //
   //      ::exception::throw_interface_only(this);
   //
   //      return NULL;
   //
   //   }
   //
   //
   //   string application::get_version()
   //   {
   //
   //      ::exception::throw_interface_only(this);
   //
   //      return "";
   //
   //   }
   //
   //
   //   void application::SetCurrentHandles()
   //   {
   //
   //      dappy(string(typeid(*this).name()) + " : SetCurrentHandles 1 : " + ::str::from(m_iReturnCode));
   //      m_pimpl->set_os_data((void *) ::get_current_thread());
   //      if(m_pthreadimpl->get_os_data() == NULL)
   //      {
   //         m_pthreadimpl->set_os_data(m_pimpl->get_os_data());
   //      }
   //      dappy(string(typeid(*this).name()) + " : SetCurrentHandles 2 : " + ::str::from(m_iReturnCode));
   //      m_pimpl->set_os_int(::get_current_thread_id());
   //      if(m_pthreadimpl->get_os_int() == 0)
   //      {
   //         m_pthreadimpl->set_os_int(m_pimpl->get_os_int());
   //      }
   //
   //      m_pimpl->SetCurrentHandles();
   //      dappy(string(typeid(*this).name()) + " : SetCurrentHandles impled : " + ::str::from(m_iReturnCode));
   //
   //
   //
   //   }
   //
   //
   //   void application::set_env_var(const string & var,const string & value)
   //   {
   //
   //      ::exception::throw_interface_only(this);
   //
   //   }
   //
   //
   //
   //
   //   //bool application::_001OnDDECommand(const char * lpcsz)
   //   //{
   //
   //   //   ::exception::throw_interface_only(this);
   //
   //   //   return false;
   //
   //   //}
   //
   //
   //   //void application::_001EnableShellOpen()
   //   //{
   //
   //   //   ::exception::throw_interface_only(this);
   //
   //   //}
   //
   //
   //   //::user::document * application::_001OpenDocumentFile(var varFile)
   //   //{
   //
   //   //   ::exception::throw_interface_only(this);
   //
   //   //   return NULL;
   //
   //   //}
   //
   //
   //   //void application::_001OnFileNew(signal_details * pobj)
   //   //{
   //
   //   //   ::exception::throw_interface_only(this);
   //
   //   //}
   //
   //
   //   sp(::aura::printer) application::get_printer(const char * pszDeviceName)
   //   {
   //
   //      ::exception::throw_interface_only(this);
   //
   //      return NULL;
   //
   //   }
   //
   //
   //   bool application::update_module_paths()
   //   {
   //
   //
   //      if(is_system())
   //      {
   //
   //         if(!m_pimpl->update_module_paths())
   //            return false;
   //
   //
   //      }
   //
   //      return true;
   //
   //
   //   }
   //
   //
   //

   //
   //   void application::_001CloseApplication()
   //   {
   //
   //      throw todo(get_app());
   //
   //   }
   //
   //
   //   sp(::user::interaction) application::release_capture_uie()
   //   {
   //
   //#if defined(LINUX)
   //
   //      oswindow oswindowCapture = ::GetCapture();
   //      if (oswindowCapture == NULL)
   //         return NULL;
   //      return oswindowCapture->get_user_interaction()->ReleaseCapture();
   //
   //#elif defined(WINDOWS)
   //
   //      oswindow oswindowCapture = ::GetCapture();
   //      if(oswindowCapture == NULL)
   //         return NULL;
   //      return System.window_from_os_data(oswindowCapture)->ReleaseCapture();
   //
   //#elif defined(APPLEOS)
   //
   //      oswindow oswindowCapture = ::GetCapture();
   //      if (oswindowCapture == NULL)
   //         return NULL;
   //      return oswindowCapture->get_user_interaction()->ReleaseCapture();
   //
   //#else
   //
   //      ::exception::throw_not_implemented(get_app());
   //
   //#endif
   //
   //   }
   //
   //
   //   sp(::user::interaction) application::get_capture_uie()
   //   {
   //
   //#if defined(METROWIN)
   //
   //      oswindow oswindowCapture = ::GetCapture();
   //
   //      if (oswindowCapture == NULL)
   //         return NULL;
   //
   //      ::user::interaction * pui = oswindowCapture->window();
   //
   //      if (pui == NULL)
   //         return NULL;
   //
   //      return pui->GetCapture();
   //
   //#elif defined(WINDOWS) || defined(APPLE_IOS)
   //
   //      oswindow oswindowCapture = ::GetCapture();
   //
   //      if(oswindowCapture == NULL)
   //         return NULL;
   //
   //      sp(::user::interaction) pui = System.window_from_os_data(oswindowCapture);
   //
   //      if(pui == NULL)
   //         return NULL;
   //
   //      return pui->GetCapture();
   //
   //#else
   //
   //      //      ::exception::throw_not_implemented(get_app());
   //
   //      oswindow oswindowCapture = ::GetCapture();
   //
   //      if (oswindowCapture == NULL)
   //         return NULL;
   //
   //      return window_from_handle(::GetCapture());
   //
   //#endif
   //
   //   }
   //
   //
   //
   //
   //
   //
   //
   //   uint32_t application::get_thread_id()
   //   {
   //      return m_pimpl->get_thread_id();
   //   }
   //
   //
   //
   //
   //
   //#ifndef METROWIN
   //
   //   void application::get_time(timeval *p)
   //   {
   //      m_pimpl->get_time(p);
   //   }
   //
   //#endif
   //
   //
   //   bool application::do_prompt_file_name(var & varFile,UINT nIDSTitle,uint32_t lFlags,bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument)
   //   {
   //
   //      UNREFERENCED_PARAMETER(varFile);
   //      UNREFERENCED_PARAMETER(nIDSTitle);
   //
   //      return false;
   //
   //   }
   //
   //
   //   string CLASS_DECL_BASE application::get_cred(const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   //   {
   //
   //      string str = ::fontopus::get_cred(this,strUsername,strPassword,strToken);
   //
   //      if(str == "ok")
   //         return "ok";
   //
   //      if(!bInteractive)
   //         return "failed";
   //
   //      sp(::fontopus::simple_ui) pui;
   //
   //      string strRequestUrl(strRequestUrlParam);
   //
   //      if(strRequestUrl.is_empty())
   //      {
   //
   //         string strIgnitionServer = file_as_string_dup("C:\\ca2\\config\\system\\ignition_server.txt");
   //
   //         if(::str::ends_ci(strIgnitionServer,".ca2.cc"))
   //         {
   //
   //            strRequestUrl = "https://" + strIgnitionServer + "/";
   //
   //         }
   //         else
   //         {
   //
   //            strRequestUrl = "https://account.ca2.cc/";
   //
   //         }
   //
   //      }
   //
   //      pui = canew(::fontopus::simple_ui(this,strRequestUrl));
   //
   //      pui->m_login.m_peditUser->SetWindowText(strUsername);
   //
   //      pui->m_login.m_ppassword->SetWindowText("");
   //
   //      string strResult = pui->get_cred(rect,strUsername,strPassword,strToken,strTitle);
   //
   //      pui->DestroyWindow();
   //
   //      return strResult;
   //
   //   }
   //
   //
   //
   //
   //   bool application::get_temp_file_name_template(string & strRet,const char * pszName,const char * pszExtension,const char * pszTemplate)
   //   {
   //
   //      throw not_implemented(this);
   //
   //      return false;
   //
   //   }
   //
   //
   //   bool application::get_temp_file_name(string & strRet,const char * pszName,const char * pszExtension)
   //   {
   //
   //      return get_temp_file_name_template(strRet,pszName,pszExtension,NULL);
   //
   //   }
   //
   //
   //
   //
   //
   //
   //
   //
   //   ::visual::icon * application::set_icon(object * pobject,::visual::icon * picon,bool bBigIcon)
   //   {
   //
   //      ::visual::icon * piconOld = get_icon(pobject,bBigIcon);
   //
   //      if(bBigIcon)
   //      {
   //
   //         pobject->oprop("big_icon").operator =((sp(object)) picon);
   //
   //      }
   //      else
   //      {
   //
   //         pobject->oprop("small_icon").operator =((sp(object)) picon);
   //
   //      }
   //
   //      return piconOld;
   //
   //   }
   //
   //
   //   ::visual::icon * application::get_icon(object * pobject,bool bBigIcon) const
   //   {
   //
   //      if(bBigIcon)
   //      {
   //
   //         return const_cast <object *> (pobject)->oprop("big_icon").cast < ::visual::icon >();
   //
   //      }
   //      else
   //      {
   //
   //         return const_cast <object *> (pobject)->oprop("small_icon").cast < ::visual::icon >();
   //
   //      }
   //
   //   }
   //
   //
   //
   //   bool application::final_handle_exception(::exception::exception & e)
   //   {
   //      UNREFERENCED_PARAMETER(e);
   //      //linux      exit(-1);
   //
   //      if(!is_system())
   //      {
   //
   //         // get_app() may be it self, it is ok...
   //         if(Sys(get_app()).final_handle_exception((::exception::exception &) e))
   //            return true;
   //
   //
   //      }
   //
   //      return false;
   //   }
   //
   //
   //
   //
   //
   //
   //
   //   bool application::initial_check_directrix()
   //   {
   //
   //      return axis::application::initial_check_directrix();
   //
   //   }
   //
   //
   //   bool application::on_install()
   //   {
   //
   //      if(!axis::application::on_install())
   //         return false;
   //
   //
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool application::on_uninstall()
   //   {
   //
   //      bool bOk = axis::application::on_uninstall();
   //
   //
   //      if(is_serviceable())
   //      {
   //
   //         if(!remove_service())
   //            bOk = false;
   //
   //      }
   //
   //      return bOk;
   //
   //   }
   //
   //
   //   bool application::system_add_app_install(const char * pszId)
   //   {
   //
   //
   //
   //      return axis::application::system_add_app_install(pszId);
   //
   //   }
   //
   //
   //
   //   bool application::os_native_bergedge_start()
   //   {
   //
   //      return axis::application::os_native_bergedge_start();
   //
   //   }
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //   //   void application::construct(const char *pszId)
   //   //   {
   //   //      //if(m_strAppName.has_char())
   //   //      //   return;
   //   //      //m_strAppName.Empty();
   //   //      //m_strId.Empty();
   //   //      if (pszId == NULL)
   //   //      {
   //   //#ifdef WINDOWSEX
   //   //         wstring wstr = ::GetCommandLineW();
   //   //         string str = ::str::international::unicode_to_utf8(wstr);
   //   //         strsize iFind = str.find(" : ");
   //   //         if (iFind >= 0)
   //   //         {
   //   //            iFind = str.find("app=", iFind);
   //   //            if (iFind >= 0)
   //   //            {
   //   //               strsize iEnd = str.find(" ", iFind);
   //   //               if (iEnd < 0)
   //   //               {
   //   //                  m_strId = str.Mid(iFind + 4);
   //   //               }
   //   //               else
   //   //               {
   //   //                  m_strId = str.Mid(iFind + 4, iEnd - iFind - 4);
   //   //               }
   //   //               ::str::begins_eat(m_strId, "\"");
   //   //               ::str::ends_eat(m_strId, "\"");
   //   //            }
   //   //         }
   //   //#endif
   //   //      }
   //   //      else
   //   //      {
   //   //         m_strId = pszId;
   //   //      }
   //   //      if (m_strId.is_empty())
   //   //         m_strId = "mplite";
   //   //      construct();
   //   //      if (m_strAppName.is_empty())
   //   //      {
   //   //         if (m_strAppId.has_char())
   //   //            m_strAppName = m_strAppId;
   //   //         else if (m_strInstallToken.has_char())
   //   //            m_strAppName = m_strInstallToken;
   //   //      }
   //   //   }
   //
   //
   //   //void application::construct()
   //   //{
   //   //   string strId = m_strId;
   //   //   char chFirst = '\0';
   //   //   if (strId.get_length() > 0)
   //   //   {
   //   //      chFirst = strId[0];
   //   //   }
   //
   //   //   ::core::application::construct();
   //
   //   //}
   //
   //
   //
   //
   //   //void application::_001OnFileNew()
   //   //{
   //   //   string strId = m_strId;
   //   //   char chFirst = '\0';
   //   //   if (strId.get_length() > 0)
   //   //   {
   //   //      chFirst = strId[0];
   //   //   }
   //   //   ::core::application::_001OnFileNew(NULL);
   //   //}
   //
   //
   //   //bool application::bergedge_start()
   //   //{
   //   //   string strId = m_strId;
   //   //   char chFirst = '\0';
   //   //   if (strId.get_length() > 0)
   //   //   {
   //   //      chFirst = strId[0];
   //   //   }
   //   //   return ::core::application::bergedge_start();
   //   //}
   //
   //
   //
   //   //bool application::on_install()
   //   //{
   //   //   string strId = m_strId;
   //   //   char chFirst = '\0';
   //   //   if (strId.get_length() > 0)
   //   //   {
   //   //      chFirst = strId[0];
   //   //   }
   //   //   return ::core::application::on_install();
   //   //}
   //
   //   //bool application::on_uninstall()
   //   //{
   //   //   string strId = m_strId;
   //   //   char chFirst = '\0';
   //   //   if (strId.get_length() > 0)
   //   //   {
   //   //      chFirst = strId[0];
   //   //   }
   //   //   return ::core::application::on_uninstall();
   //   //}
   //
   //
   //   void application::on_request(sp(::create) pcreatecontext)
   //   {
   //
   //      ::object::on_request(pcreatecontext);
   //
   //      command()->consolidate(pcreatecontext);
   //
   //   }
   //
   //
   //   //bool application::is_serviceable()
   //   //{
   //
   //
   //   //   string strId = m_strId;
   //   //   char chFirst = '\0';
   //   //   if (strId.get_length() > 0)
   //   //   {
   //   //      chFirst = strId[0];
   //   //   }
   //   //   return ::core::application::is_serviceable();
   //   //}
   //
   //   //service_base * application::allocate_new_service()
   //   //{
   //
   //   //   return NULL;
   //
   //   //}
   //
   //
   //   //sp(::user::document) application::_001OpenDocumentFile(var varFile)
   //   //{
   //   //   string strId = m_strId;
   //   //   char chFirst = '\0';
   //   //   if (strId.get_length() > 0)
   //   //   {
   //   //      chFirst = strId[0];
   //   //   }
   //   //   return ::core::application::_001OpenDocumentFile(varFile);
   //
   //   //}
   //
   //
   //   int32_t application::run()
   //   {
   //
   //      return ::axis::application::run();
   //
   //
   //   }
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //   void application::on_service_request(sp(::create) pcreatecontext)
   //   {
   //
   //      if(!is_serviceable())
   //         return;
   //
   //      if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("create_service"))
   //      {
   //         create_service();
   //      }
   //      else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("start_service"))
   //      {
   //         start_service();
   //      }
   //      else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("stop_service"))
   //      {
   //         stop_service();
   //      }
   //      else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("remove_service"))
   //      {
   //         remove_service();
   //      }
   //
   //
   //   }
   //
   //
   //
   //   bool application::process_initialize()
   //   {
   //
   //      if(m_bBaseProcessInitialize)
   //         return m_bBaseProcessInitializeResult;
   //
   //      m_bBaseProcessInitialize = true;
   //      m_bBaseProcessInitializeResult = false;
   //
   //
   //      if(!::axis::application::process_initialize())
   //         return false;
   //
   //
   //      if(is_system())
   //      {
   //
   //         draw2d_factory_exchange();
   //
   //      }
   //
   //      m_bBaseProcessInitializeResult = true;
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool application::initialize_instance()
   //   {
   //
   //      if(!::axis::application::initialize_instance())
   //         return false;
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool application::initialize1()
   //   {
   //
   //      if(m_bBaseInitialize1)
   //         return m_bBaseInitialize1Result;
   //
   //      m_bBaseInitialize1 = true;
   //
   //      m_bBaseInitialize1Result = false;
   //
   //      if(!::axis::application::initialize1())
   //         return false;
   //
   //      m_dwAlive = ::get_tick_count();
   //
   //      m_bBaseInitialize1Result = true;
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool application::initialize2()
   //   {
   //
   //      if(!::axis::application::initialize2())
   //         return false;
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool application::initialize3()
   //   {
   //
   //      if(!::axis::application::initialize3())
   //         return false;
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool application::initialize()
   //   {
   //
   //      if(!::axis::application::initialize())
   //         return false;
   //
   //
   //
   //      return true;
   //
   //   }
   //
   //
   //   int32_t application::exit_instance()
   //   {
   //
   //
   //      try
   //      {
   //
   //         m_iReturnCode = ::axis::application::exit_instance();
   //
   //      }
   //      catch(...)
   //      {
   //
   //         m_iReturnCode = -1;
   //
   //      }
   //
   //
   //      return m_iReturnCode;
   //
   //   }
   //
   //
   //   bool application::finalize()
   //   {
   //
   //      bool bOk = false;
   //
   //      try
   //      {
   //
   //         bOk = ::axis::application::finalize();
   //
   //      }
   //      catch(...)
   //      {
   //
   //         bOk = false;
   //
   //      }
   //
   //      return bOk;
   //
   //   }
   //
   //
   //   void application::on_exclusive_instance_conflict(EExclusiveInstance eexclusive)
   //   {
   //
   //      if(eexclusive == ExclusiveInstanceLocal)
   //      {
   //
   //         on_exclusive_instance_local_conflict();
   //
   //      }
   //
   //   }
   //
   //
   //   void application::on_exclusive_instance_local_conflict()
   //   {
   //
   //   }
   //
   //
   //   string application::get_mutex_name_gen()
   //   {
   //      return m_strAppName;
   //   }
   //
   //
   //
   //   bool application::Ex2OnAppInstall()
   //   {
   //      return true;
   //   }
   //
   //   bool application::Ex2OnAppUninstall()
   //   {
   //      return true;
   //   }
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //   int32_t application::simple_message_box_timeout(::user::primitive * pwndOwner,const char * pszMessage,::duration durationTimeOut,UINT fuStyle)
   //   {
   //      UNREFERENCED_PARAMETER(durationTimeOut);
   //      return simple_message_box(pwndOwner,pszMessage,fuStyle);
   //   }
   //
   //
   ////   void application::tellme_destroyed(::user::interaction * pui, bool * pDestroyed, bool bTell)
   ////   {
   ////
   ////      if(pui == NULL)
   ////         return;
   ////
   ////      try
   ////      {
   ////
   ////#ifdef LINUX
   ////
   ////         synch_lock sl(get_ui_destroyed_mutex());
   ////
   ////         if(bTell)
   ////         {
   ////
   ////            if(pui->m_bDestroying)
   ////            {
   ////
   ////               *pDestroyed = true;
   ////
   ////            }
   ////            else
   ////            {
   ////
   ////               pui->m_bptraTellMeDestroyed.add(pDestroyed);
   ////
   ////            }
   ////
   ////         }
   ////         else
   ////         {
   ////
   ////            pui->m_bptraTellMeDestroyed.remove(pDestroyed);
   ////
   ////         }
   ////
   ////#endif
   ////
   ////      }
   ////      catch(...)
   ////      {
   ////
   ////      }
   ////
   ////   }
   //
   //
   //   string application::get_license_id()
   //   {
   //
   //      if(m_strLicense.has_char())
   //         return m_strLicense;
   //
   //      if(m_strInstallToken.has_char())
   //         return m_strInstallToken;
   //
   //      return m_strAppId;
   //
   //   }
   //
   //
   //
   //
   //   ::user::user * application::create_user()
   //   {
   //
   //      return canew(::user::user(this));
   //
   //   }
   //
   //
   //   void application::on_create_keyboard()
   //   {
   //
   //      Session.set_keyboard_layout(NULL,::action::source::database());
   //
   //   }
   //
   //
   //   bool application::defer_initialize_twf()
   //   {
   //
   //      if(System.m_ptwf == NULL && (System.m_bShouldInitializeGTwf && m_bShouldInitializeGTwf && m_bInitializeProDevianMode))
   //      {
   //
   //         if(!System.initialize_twf())
   //            return false;
   //
   //      }
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool application::assert_user_logged_in()
   //   {
   //
   //      return axis::application::assert_user_logged_in();
   //
   //   }
   //
   //
   //   ::user::interaction * application::get_active_guie()
   //   {
   //
   //      return Session.get_active_guie();
   //
   //   }
   //
   //
   //   ::user::interaction * application::get_focus_guie()
   //   {
   //
   //      return Session.get_focus_guie();
   //
   //   }
   //
   //
   //
   //
   //   bool application::on_thread_on_idle(::thread_impl * pimpl, LONG lCount)
   //   {
   //
   ////      ASSERT_VALID(this);
   ////
   ////#if defined(WINDOWS) && defined(DEBUG) && !defined(___NO_DEBUG_CRT)
   ////      // check core API's allocator (before idle)
   ////      if(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
   ////         ASSERT(__check_memory());
   ////#endif
   //
   //      single_lock sl(&pimpl->m_mutexUiPtra,TRUE);
   //
   //      ::user::interaction * pui = NULL;
   //
   //
   //      if(lCount <= 0)
   //      {
   //         while(get_frame(pui))
   //         {
   //            //::user::interaction * pui = (::user::interaction *) pimpl->m_spuiptra->element_at(i)->m_pvoidUserInteraction;
   //            bool bOk = false;
   //            try
   //            {
   //
   //               bOk = pui != NULL && pui->IsWindowVisible();
   //            }
   //            catch(...)
   //            {
   //            }
   //            //if(!bOk)
   //            //{
   //            //   try
   //            //   {
   //            //      Application.remove_frame(pui);
   //            //   }
   //            //   catch(...)
   //            //   {
   //            //   }
   //            //   try
   //            //   {
   //            //      Session.remove_frame(pui);
   //            //   }
   //            //   catch(...)
   //            //   {
   //            //   }
   //            //   try
   //            //   {
   //            //      System.remove_frame(pui);
   //            //   }
   //            //   catch(...)
   //            //   {
   //            //   }
   //            //}
   //            //else
   //            //{
   //            //   sl.unlock();
   //            //   try
   //            //   {
   //            //      //pui->send_message(WM_IDLEUPDATECMDUI,(WPARAM)TRUE);
   //            //   }
   //            //   catch(...)
   //            //   {
   //
   //            //   }
   //            //   sl.lock();
   //            //}
   //         }
   //
   //
   //      }
   //      else if(lCount >= 0)
   //      {
   //      }
   //
   ////#if defined(WINDOWS) && defined(DEBUG) && !defined(___NO_DEBUG_CRT)
   ////      // check core API's allocator (after idle)
   ////      if(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
   ////         ASSERT(__check_memory());
   ////#endif
   ////
   //
   //
   //      return lCount < 0;  // nothing more to do if lCount >= 0
   //
   //   }
   //
   //
   //   bool application::post_user_message(::thread_impl * pimpl,::user::primitive * pui,UINT message,WPARAM wparam,lparam lparam)
   //   {
   //
   //      if(pimpl->m_hthread == NULL)
   //         return false;
   //
   //      ::user::message * pmessage    = new ::user::message;
   //      pmessage->m_pui               = (::user::interaction *) pui->m_pvoidUserInteraction;
   //      pmessage->m_uiMessage         = message;
   //      pmessage->m_wparam            = wparam;
   //      pmessage->m_lparam            = lparam;
   //
   //      return pimpl->post_thread_message(WM_APP + 1984,77,(LPARAM)pmessage) != FALSE;
   //
   //   }
   //
   //
   //
   //   bool application::is_window(::user::primitive * pui)
   //   {
   //
   //      return ((::user::interaction *)pui->m_pvoidUserInteraction)->IsWindow();
   //
   //   }
   //
   //   LRESULT application::send_message(::user::primitive * pui,UINT message,WPARAM wparam,lparam lparam)
   //   {
   //
   //      return ((::user::interaction *)pui->m_pvoidUserInteraction)->send_message(message,wparam,lparam);
   //
   //   }
   //
   //   oswindow application::get_safe_handle(::user::primitive * pui)
   //   {
   //
   //      return ((::user::interaction *)pui->m_pvoidUserInteraction)->get_safe_handle();
   //
   //   }
   //
   //   void application::dispatch_user_message(::signal_details * pobj)
   //   {
   //
   //      smart_pointer < ::user::message > spmessage(pobj->m_lparam);
   //      spmessage->send();
   //      pobj->m_uiMessage   = 0;    // ssshhhh.... - self-healing - sh...
   //      pobj->m_wparam      = 0;    // ssshhhh.... - self-healing - sh...
   //      pobj->m_bRet        = true;
   //      return;
   //
   //   }
   //
   //
   //   ::user::interaction * application::get_parent(::user::interaction * pui)
   //   {
   //
   //      return pui->GetParent();
   //
   //   }
   //
   //
   //   bool application::enable_window(::user::primitive * pui, bool bEnable)
   //   {
   //
   //      // if control has the focus, move the focus before disabling
   //      if(!bEnable)
   //      {
   //
   //         if(System.get_focus_guie() == ((::user::interaction *)pui->m_pvoidUserInteraction))
   //         {
   //
   //            Application.send_message(Application.get_parent(((::user::interaction *)pui->m_pvoidUserInteraction)),WM_NEXTDLGCTL,0,(LPARAM)FALSE);
   //
   //         }
   //
   //      }
   //
   //      return ((::user::interaction *)pui->m_pvoidUserInteraction)->enable_window(bEnable);
   //
   //   }
   //
   //
   //   bool application::set_window_text(::user::interaction * pui,const string & strText)
   //   {
   //
   //      pui->SetWindowText(strText);
   //
   //      return true;
   //
   //   }
   //
   //
   //   ptr_array < ::thread > application::get_thread(::user::primitive * pui)
   //   {
   //
   //      return ((::user::interaction *)pui->m_pvoidUserInteraction)->m_threadptra;
   //
   //   }
   //
   //
   //   void application::add_thread(::user::primitive * pui,::thread * pthread)
   //   {
   //
   //      ((::user::interaction *)pui->m_pvoidUserInteraction)->m_threadptra.add_unique(pthread);
   //
   //   }
   //
   //   void application::remove_thread(::user::primitive * pui,::thread * pthread)
   //   {
   //
   //      ((::user::interaction *)pui->m_pvoidUserInteraction)->m_threadptra.remove(pthread);
   //
   //   }
   //
   //   void application::window_graphics_update_window(window_graphics * & pdata,oswindow interaction_impl,COLORREF * pOsBitmapData,const RECT & rect,int cxParam, int cyParam, int iStride)
   //   {
   //
   //      window_graphics::update_window(pdata,interaction_impl,pOsBitmapData,rect,cxParam, cyParam, iStride);
   //
   //   }
   //
   //
   //
   //   sp(::message::base) application::get_message_base(LPMESSAGE lpmsg)
   //   {
   //
   //      ::user::interaction * pwnd = NULL;
   //
   //      if(pwnd == NULL && lpmsg->hwnd != NULL)
   //      {
   //
   //         if(lpmsg->message == 126)
   //         {
   //
   //            TRACE0("WM_DISPLAYCHANGE");
   //
   //         }
   //
   //         ::user::interaction * pwindow = System.window_from_os_data(lpmsg->hwnd);
   //
   //         if(pwindow != NULL)
   //         {
   //            try
   //            {
   //               pwnd = pwindow;
   //            }
   //            catch(...)
   //            {
   //               pwnd = NULL;
   //            }
   //         }
   //
   //         if(pwnd == NULL)
   //            return NULL;
   //
   //      }
   //
   //
   //      if(pwnd != NULL)
   //         return pwnd->get_base(lpmsg->message,lpmsg->wParam,lpmsg->lParam);
   //
   //      ::thread * pthread = ::get_thread();
   //
   //      if(pthread != NULL)
   //         return pthread->get_base(lpmsg->message,lpmsg->wParam,lpmsg->lParam);
   //
   //      return get_base(lpmsg->message,lpmsg->wParam,lpmsg->lParam);
   //
   //   }
   //
   //
   //   void application::process_message(signal_details * pobj)
   //   {
   //
   //      sp(::message::base) pbase = pobj;
   //
   //      if(pbase.is_null() || pbase->m_pwnd == NULL)
   //      {
   //
   //         try
   //         {
   //
   //            message_handler(pobj);
   //
   //         }
   //         catch(const ::exception::exception & e)
   //         {
   //
   //            TRACE("application::process_message : error processing application thread message (const ::exception::exception & )");
   //
   //            if(App(this).on_run_exception((::exception::exception &) e))
   //               goto run;
   //
   //            if(App(this).final_handle_exception((::exception::exception &) e))
   //               goto run;
   //
   //            __post_quit_message(-1);
   //
   //            pbase->set_lresult(-1);
   //
   //            return;
   //
   //         }
   //         catch(::exception::base * pe)
   //         {
   //
   //            process_window_procedure_exception(pe,pbase);
   //
   //            TRACE(::aura::trace::category_AppMsg,0,"Warning: Uncaught exception in message_handler (returning %ld) (application::process_message : error processing application thread message).\n",(int_ptr)pbase->get_lresult());
   //
   //            pe->Delete();
   //
   //         }
   //         catch(...)
   //         {
   //
   //            TRACE("application::process_message : error processing application thread message (...)");
   //
   //         }
   //
   //         return;
   //
   //      }
   //
   //      try
   //      {
   //
   //         ((::user::interaction *)pbase->m_pwnd->m_pvoidUserInteraction)->message_handler(pobj);
   //
   //
   //      }
   //      catch(const ::exception::exception & e)
   //      {
   //
   //         TRACE("application::process_message : error processing window message (const ::exception::exception & )");
   //
   //         if(App(this).on_run_exception((::exception::exception &) e))
   //            goto run;
   //
   //         if(App(this).final_handle_exception((::exception::exception &) e))
   //            goto run;
   //
   //         __post_quit_message(-1);
   //
   //         pbase->set_lresult(-1);
   //
   //         return;
   //
   //      }
   //      catch(::exception::base * pe)
   //      {
   //
   //         process_window_procedure_exception(pe,pbase);
   //
   //         TRACE(::aura::trace::category_AppMsg,0,"Warning: Uncaught exception in message_handler (returning %ld) (application::process_message : error processing window message).\n",(int_ptr)pbase->get_lresult());
   //
   //         pe->Delete();
   //
   //      }
   //      catch(...)
   //      {
   //
   //         TRACE("application::process_message : error processing window message (...)");
   //
   //      }
   //
   //   run:;
   //
   //   }
   //
   //   int32_t application::simple_message_box(::user::primitive * puiOwner,const char * pszMessage,UINT fuStyle)
   //   {
   //
   //#if defined(WINDOWSEX)
   //
   //      return ::simple_message_box(puiOwner->get_safe_handle(),pszMessage,m_strAppName,fuStyle);
   //      //return MessageBoxW(puiOwner->get_safe_handle(),wstring(pszMessage),wstring(m_strAppName),fuStyle);
   //      //return MessageBoxW((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())),
   //      //   wstring(pszMessage), wstring(m_strAppName), fuStyle);
   //
   //#elif  defined(LINUX) || defined(APPLEOS) || defined(ANDROID)
   //
   //      return ::simple_message_box(puiOwner->get_safe_handle(),pszMessage,m_strAppName,fuStyle);
   //      //   return simple_message_box((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())), pszMessage, m_strAppName, fuStyle);
   //
   //#else
   //
   //      return ::simple_message_box(puiOwner->get_safe_handle(),pszMessage,m_strAppName,fuStyle);
   //
   //#endif
   //
   //   }
   //
   //   /*
   //   int32_t application::simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle)
   //   {
   //
   //   #if defined(WINDOWSEX)
   //
   //   return MessageBoxW((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())),
   //   wstring(pszMessage), wstring(m_strAppName), fuStyle);
   //
   //   #elif  defined(LINUX) || defined(APPLEOS) || defined(ANDROID)
   //
   //   return simple_message_box((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())), pszMessage, m_strAppName, fuStyle);
   //
   //   #else
   //
   //   return simple_message_box(m_psystem->m_posdata->m_pui->get_handle(), pszMessage, m_strAppName, fuStyle);
   //
   //   #endif
   //
   //   }
   //   */
   //
   //   int32_t application::simple_message_box(const char * pszMessage,UINT fuStyle)
   //   {
   //
   //#if defined(WINDOWSEX)
   //
   //      return ::simple_message_box(NULL,pszMessage,m_strAppName,fuStyle);
   //      //return MessageBoxW(NULL,wstring(pszMessage),wstring(m_strAppName),fuStyle);
   //      //return MessageBoxW((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())),
   //      //   wstring(pszMessage), wstring(m_strAppName), fuStyle);
   //
   //#elif  defined(LINUX) || defined(APPLEOS) || defined(ANDROID)
   //
   //      return ::simple_message_box(NULL,pszMessage,m_strAppName,fuStyle);
   //      //   return simple_message_box((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())), pszMessage, m_strAppName, fuStyle);
   //
   //#else
   //
   //      return ::simple_message_box(NULL,pszMessage,m_strAppName,fuStyle);
   //
   //#endif
   //
   //   }
   //
   //   string application::message_box(const string & pszMatter,property_set & propertyset)
   //   {
   //
   //      simple_message_box(pszMatter,0);
   //
   //      return "";
   //
   //   }
   //
   //
   //   //int32_t application::simple_message_box_timeout(sp(::user::interaction) pwndOwner,const char * pszMessage,::duration durationTimeOut,UINT fuStyle)
   //   //{
   //   //   UNREFERENCED_PARAMETER(durationTimeOut);
   //   //   return simple_message_box(pwndOwner,pszMessage,fuStyle);
   //   //}
   //
   //
   //   //::user::user * application::create_user()
   //   //{
   //
   //   //   return canew(::user::user(this));
   //
   //   //}
   //
   //   bool application::set_keyboard_layout(const char * pszPath,::action::context actioncontext)
   //   {
   //
   //      return Session.set_keyboard_layout(pszPath,actioncontext);
   //
   //   }
   //
   //
   //   sp(type) application::user_default_controltype_to_typeinfo(::user::e_control_type e_type)
   //   {
   //
   //      return sp(type)();
   //
   //   }
   //
   //
   //   int32_t application::hotplugin_host_starter_start_sync(const char * pszCommandLine,::aura::application * papp,hotplugin::host * phost,hotplugin::plugin * pplugin)
   //   {
   //
   //      return hotplugin::host::host_starter_start_sync(pszCommandLine,get_app(),NULL);
   //
   //   }
   void application::process_message_filter(int32_t code,signal_details * pobj)
   {

      if(pobj == NULL)
         return;   // not handled

      SCAST_PTR(::message::base,pbase,pobj);

      sp(::user::frame_window) pTopFrameWnd;
      //::user::interaction * pMainWnd;
      ::user::interaction * pMsgWnd;
      switch(code)
      {
         //case MSGF_DDEMGR:
         // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
         //  never call the next hook.
         // By returning FALSE, the message will be dispatched
         //  instead (the default behavior).
         //return;

      case MSGF_MENU:
         pMsgWnd = dynamic_cast <::user::interaction *> (pbase->m_pwnd);
         if(pMsgWnd != NULL)
         {
            pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
            if(pTopFrameWnd != NULL && pTopFrameWnd->IsTracking() &&
               pTopFrameWnd->m_bHelpMode)
            {
               //pMainWnd = __get_main_window();
               //if((m_puiMain != NULL) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
               //{
               //   //                  pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
               //   pbase->m_bRet = true;
               //   return;
               //}
            }
         }
         // fall through...

      case MSGF_DIALOGBOX:    // handles message boxes as well.
         //pMainWnd = __get_main_window();
         if(code == MSGF_DIALOGBOX && m_puiActive != NULL &&
            pbase->m_uiMessage >= WM_KEYFIRST && pbase->m_uiMessage <= WM_KEYLAST)
         {
            //// need to translate messages for the in-place container
            //___THREAD_STATE* pThreadState = __get_thread_state();
            //ENSURE(pThreadState);

            //if (pThreadState->m_bInMsgFilter)
            //   return;
            //pThreadState->m_bInMsgFilter = TRUE;    // avoid reentering this code
            //if (m_puiActive->is_window_enabled())
            //{
            //   pre_translate_message(pobj);
            //   if(pobj->m_bRet)
            //   {
            //      pThreadState->m_bInMsgFilter = FALSE;
            //      return;
            //   }
            //}
            //pThreadState->m_bInMsgFilter = FALSE;    // ok again
         }
         break;
      }
      // default to not handled

   }














   bool application::get_frame(::user::interaction * & pui)
   {

#ifdef VSNORD

      if (System.m_posdata != NULL)
      {

         if (System.m_posdata->m_pui != NULL)
         {

            pui = System.m_posdata->m_pui->m_uiptraChild.get_child(pui);

            return pui != NULL;

         }

      }


#endif

      synch_lock sl(&m_mutexFrame);

      if(m_uiptraFrame.get_count() <= 0)
      {

         return false;

      }

      if(pui == NULL)
      {

         pui = m_uiptraFrame[0];

         return true;

      }
      else
      {

         for(index i = m_uiptraFrame.get_upper_bound(); i >= 0; i--)
         {

            if(m_uiptraFrame[i] == pui)
            {

               i++;

               if(i < m_uiptraFrame.get_count())
               {

                  pui = m_uiptraFrame[i];

                  return true;

               }
               else
               {

                  return false;

               }

            }

         }

      }

      return false;

   }










   void application::add_frame(sp(::user::interaction) pwnd)
   {

      synch_lock sl(&m_mutexFrame); // recursive lock (on m_framea.add(pwnd)) but m_puiMain is "cared" by m_frame.m_mutex

      if(m_uiptraFrame.add_unique(pwnd))
      {

         System.defer_create_system_frame_window();

         Session.on_create_frame_window();

         if(m_puiMain == NULL)
         {

            m_puiMain = pwnd;

         }

      }

   }


   void application::remove_frame(sp(::user::interaction) pwnd)
   {

      synch_lock sl(&m_mutexFrame); // recursive lock (on m_framea.remove(pwnd)) but m_puiMain is "cared" by m_frame.m_mutex

      if(m_puiMain == pwnd)
      {

         m_puiMain = NULL;

      }

      m_uiptraFrame.remove(pwnd);


   }




   string application::get_cred(const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   {

      string str = ::fontopus::get_cred(this,strUsername,strPassword,strToken);

      if(str == "ok" && strUsername.has_char() && strPassword.has_char())
         return "ok";

      if(!bInteractive)
         return "failed";

      sp(::fontopus::simple_ui) pui;

      string strRequestUrl(strRequestUrlParam);

      if(strRequestUrl.is_empty())
      {

         string strIgnitionServer = file_as_string_dup("C:\\ca2\\config\\system\\ignition_server.txt");

         if(::str::ends_ci(strIgnitionServer,".ca2.cc"))
         {

            strRequestUrl = "https://" + strIgnitionServer + "/";

         }
         else
         {

            strRequestUrl = "https://account.ca2.cc/";

         }

      }

      pui = canew(::fontopus::simple_ui(this,strRequestUrl));

      pui->m_login.m_peditUser->SetWindowText(strUsername);

      pui->m_login.m_ppassword->SetWindowText("");

      string strResult = pui->get_cred(rect,strUsername,strPassword,strToken,strTitle);

      pui->DestroyWindow();

      return strResult;

   }


   ::user::user * application::create_user()
   {

      return canew(::user::user(this));

   }

   ::user::interaction * application::get_active_guie()
   {

      return Session.get_active_guie();

   }


   ::user::interaction * application::get_focus_guie()
   {

      return Session.get_focus_guie();

   }

   bool application::on_thread_on_idle(::thread_impl * pimpl,LONG lCount)
   {

      //      ASSERT_VALID(this);
      //
      //#if defined(WINDOWS) && defined(DEBUG) && !defined(___NO_DEBUG_CRT)
      //      // check core API's allocator (before idle)
      //      if(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
      //         ASSERT(__check_memory());
      //#endif

      //single_lock sl(&pimpl->m_mutexUiPtra,TRUE);

      ::user::interaction * pui = NULL;


      if(lCount <= 0)
      {
         while(get_frame(pui))
         {
            //::user::interaction * pui = (::user::interaction *) pimpl->m_spuiptra->element_at(i)->m_pvoidUserInteraction;
            bool bOk = false;
            try
            {

               bOk = pui != NULL && pui->IsWindowVisible();
            }
            catch(...)
            {
            }
            if(!bOk)
            {
               //   try
               //   {
               //      Application.remove_frame(pui);
               //   }
               //   catch(...)
               //   {
               //   }
               //   try
               //   {
               //      Session.remove_frame(pui);
               //   }
               //   catch(...)
               //   {
               //   }
               //   try
               //   {
               //      System.remove_frame(pui);
               //   }
               //   catch(...)
               //   {
               //   }
            }
            else
            {
//               sl.unlock();
               try
               {
                  pui->send_message(WM_IDLEUPDATECMDUI,(WPARAM)TRUE);
               }
               catch(...)
               {

               }
  //             sl.lock();
            }
         }


      }
      else if(lCount >= 0)
      {
      }

      //#if defined(WINDOWS) && defined(DEBUG) && !defined(___NO_DEBUG_CRT)
      //      // check core API's allocator (after idle)
      //      if(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
      //         ASSERT(__check_memory());
      //#endif
      //


      return lCount < 0;  // nothing more to do if lCount >= 0

   }


   bool application::post_user_message(::thread_impl * pimpl,::user::primitive * pui,UINT message,WPARAM wparam,lparam lparam)
   {

      if(pimpl->m_hthread == NULL)
         return false;

      ::user::message * pmessage    = new ::user::message;
      pmessage->m_pui               = (::user::interaction *) pui->m_pvoidUserInteraction;
      pmessage->m_uiMessage         = message;
      pmessage->m_wparam            = wparam;
      pmessage->m_lparam            = lparam;

      return pimpl->post_thread_message(WM_APP + 1984,77,(LPARAM)pmessage) != FALSE;

   }



   bool application::is_window(::user::primitive * pui)
   {

      return ((::user::interaction *)pui->m_pvoidUserInteraction)->IsWindow();

   }

   LRESULT application::send_message(::user::primitive * pui,UINT message,WPARAM wparam,lparam lparam)
   {

      return ((::user::interaction *)pui->m_pvoidUserInteraction)->send_message(message,wparam,lparam);

   }

   oswindow application::get_safe_handle(::user::primitive * pui)
   {

      return ((::user::interaction *)pui->m_pvoidUserInteraction)->get_safe_handle();

   }

   void application::dispatch_user_message(::signal_details * pobj)
   {

      smart_pointer < ::user::message > spmessage(pobj->m_lparam);
      spmessage->send();
      pobj->m_uiMessage   = 0;    // ssshhhh.... - self-healing - sh...
      pobj->m_wparam      = 0;    // ssshhhh.... - self-healing - sh...
      pobj->m_bRet        = true;
      return;

   }


   ::user::interaction * application::get_parent(::user::interaction * pui)
   {

      return pui->GetParent();

   }


   bool application::enable_window(::user::primitive * pui,bool bEnable)
   {

      // if control has the focus, move the focus before disabling
      if(!bEnable)
      {

         if(System.get_focus_guie() == ((::user::interaction *)pui->m_pvoidUserInteraction))
         {

            Application.send_message(Application.get_parent(((::user::interaction *)pui->m_pvoidUserInteraction)),WM_NEXTDLGCTL,0,(LPARAM)FALSE);

         }

      }

      return ((::user::interaction *)pui->m_pvoidUserInteraction)->enable_window(bEnable);

   }


   bool application::set_window_text(::user::interaction * pui,const string & strText)
   {

      pui->SetWindowText(strText);

      return true;

   }


   ptr_array < ::thread > application::get_thread(::user::primitive * pui)
   {

      return ((::user::interaction *)pui->m_pvoidUserInteraction)->m_threadptra;

   }


   void application::add_thread(::user::primitive * pui,::thread * pthread)
   {

      ((::user::interaction *)pui->m_pvoidUserInteraction)->m_threadptra.add_unique(pthread);

   }

   void application::remove_thread(::user::primitive * pui,::thread * pthread)
   {

      ((::user::interaction *)pui->m_pvoidUserInteraction)->m_threadptra.remove(pthread);

   }

   void application::window_graphics_update_window(window_graphics ** ppdata,oswindow interaction_impl,COLORREF * pOsBitmapData,const RECT & rect,int cxParam,int cyParam,int iStride,bool bTransferBuffer)
   {

      ::window_graphics::update_window(ppdata,interaction_impl,pOsBitmapData,rect,cxParam,cyParam,iStride,bTransferBuffer);

   }


   sp(::message::base) application::get_message_base(LPMESSAGE lpmsg)
   {

      ::user::interaction * pwnd = NULL;

      if(pwnd == NULL && lpmsg->hwnd != NULL)
      {

         if(lpmsg->message == 126)
         {

            TRACE0("WM_DISPLAYCHANGE");

         }

         ::user::interaction * pwindow = System.window_from_os_data(lpmsg->hwnd);

         if(pwindow != NULL)
         {
            try
            {
               pwnd = pwindow;
            }
            catch(...)
            {
               pwnd = NULL;
            }
         }

         if(pwnd == NULL)
            return NULL;

      }


      if(pwnd != NULL)
         return pwnd->get_base(lpmsg->message,lpmsg->wParam,lpmsg->lParam);

      return ::axis::application::get_message_base(lpmsg);


   }


   void application::process_message(signal_details * pobj)
   {

      sp(::message::base) pbase = pobj;

      if(pbase.is_null() || pbase->m_pwnd == NULL)
      {

         try
         {

            message_handler(pobj);

         }
         catch(const ::exception::exception & e)
         {

            TRACE("application::process_message : error processing application thread message (const ::exception::exception & )");

            if(App(this).on_run_exception((::exception::exception &) e))
               goto run;

            if(App(this).final_handle_exception((::exception::exception &) e))
               goto run;

            __post_quit_message(-1);

            pbase->set_lresult(-1);

            return;

         }
         catch(::exception::base * pe)
         {

            process_window_procedure_exception(pe,pbase);

            TRACE(::aura::trace::category_AppMsg,0,"Warning: Uncaught exception in message_handler (returning %ld) (application::process_message : error processing application thread message).\n",(int_ptr)pbase->get_lresult());

            pe->Delete();

         }
         catch(...)
         {

            TRACE("application::process_message : error processing application thread message (...)");

         }

         return;

      }

      try
      {

         ((::user::interaction *)pbase->m_pwnd->m_pvoidUserInteraction)->message_handler(pobj);


      }
      catch(const ::exception::exception & e)
      {

         TRACE("application::process_message : error processing window message (const ::exception::exception & )");

         if(App(this).on_run_exception((::exception::exception &) e))
            goto run;

         if(App(this).final_handle_exception((::exception::exception &) e))
            goto run;

         __post_quit_message(-1);

         pbase->set_lresult(-1);

         return;

      }
      catch(::exception::base * pe)
      {

         process_window_procedure_exception(pe,pbase);

         TRACE(::aura::trace::category_AppMsg,0,"Warning: Uncaught exception in message_handler (returning %ld) (application::process_message : error processing window message).\n",(int_ptr)pbase->get_lresult());

         pe->Delete();

      }
      catch(...)
      {

         TRACE("application::process_message : error processing window message (...)");

      }

   run:;

   }


   ::user::interaction * application::main_window()
   {

      if(m_puiMain == NULL)
         return NULL;

      return (::user::interaction *) m_puiMain->m_pvoidUserInteraction;

   }


   sp(type) application::user_default_controltype_to_typeinfo(::user::e_control_type e_type)
   {

      return sp(type)();

   }


   int32_t application::hotplugin_host_host_starter_start_sync(const char * pszCommandLine,::aura::application * papp,::hotplugin::host * phost,::hotplugin::plugin * pplugin)
   {

      return hotplugin::host::host_starter_start_sync(pszCommandLine,get_app(),NULL);

   }
   bool application::defer_initialize_twf()
   {

      if(System.m_ptwf == NULL && (System.m_bShouldInitializeGTwf && m_bShouldInitializeGTwf && m_bInitializeProDevianMode))
      {

         if(!System.initialize_twf())
            return false;

      }

      return true;

   }



   ::user::interaction * application::FindWindow(const char * lpszClassName,const char * lpszWindowName)
   {

      ::exception::throw_interface_only(this);

      return NULL;

   }


   ::user::interaction * application::FindWindowEx(oswindow oswindowParent,oswindow oswindowChildAfter,const char * lpszClass,const char * lpszWindow)
   {

      ::exception::throw_interface_only(this);

      return NULL;

   }

   void application::draw2d_factory_exchange()
   {

#if defined(METROWIN)

      ::draw2d_factory_exchange(this);

#else

      ::axis::application::draw2d_factory_exchange();

#endif

   }

} // namespace base







