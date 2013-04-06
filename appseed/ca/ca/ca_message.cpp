#include "framework.h"

#if defined(LINUX)
// Ubuntu apt-get install libx11-dev
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#endif

#undef new

struct myfx_CTLCOLOR
{
   ::oswindow oswindow;
   HDC hDC;
   UINT nCtlType;
};


namespace ca
{


   namespace message
   {

      ::ca::signal * CreateSignal()
      {
         return new ::ca::signal();
      }


      /*
      array < Handler *, Handler * > theMessageHandlerArray;

      void HookMessageHandler(Handler * phandler)
      {
         theMessageHandlerArray.add_unique(phandler);
      }

      void UnhookMessageHandler(Handler * phandler)
      {
         while(theMessageHandlerArray.remove_first(phandler));
      }


      void SendGlobalMessage(MPARAM mparam, NPARAM nparam, OPARAM oparam)
      {
         for(int32_t i = 0; i < theMessageHandlerArray.get_size(); i++)
         {
            theMessageHandlerArray[i]->OnMessage(mparam, nparam, oparam);
         }
      }
      */

#ifdef WINDOWS

      bool dispatch::igui_RelayEvent(LPMESSAGE lpmsg)
      {
         switch(lpmsg->message)
         {
         case message_pos_create:
            return OnWndMsgPosCreate();
            break;
         default:
            return false;
         }
         return 0;
      }

#endif

      bool dispatch::OnWndMsgPosCreate()
      {
         return true;
      }

      sp(base) dispatch::peek_message(LPMESSAGE lpmsg, sp(::user::interaction) pwnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
      {
         if(!::PeekMessage(lpmsg, pwnd->get_safe_handle(), wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
            return ::null();
         return get_base(lpmsg, pwnd);
      }

      sp(base) dispatch::get_message(LPMESSAGE lpmsg, sp(::user::interaction) pwnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
      {
         if(!::GetMessage(lpmsg, pwnd->get_safe_handle(), wMsgFilterMin, wMsgFilterMax))
            return ::null();
         return get_base(lpmsg, pwnd);
      }

      sp(base) dispatch::peek_message(sp(::user::interaction) pwnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
      {
         MESSAGE msg;
         return peek_message(&msg, pwnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
      }


      sp(base) dispatch::get_message(sp(::user::interaction) pwnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
      {
         MESSAGE msg;
         return get_message(&msg, pwnd, wMsgFilterMin, wMsgFilterMax);
      }

      sp(base) dispatch::get_base(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam)
      {
         sp(base) pbase;
         e_prototype eprototype = PrototypeNone;
         //if(oswindow != ::null())
         {
            eprototype = dispatch::GetMessagePrototype(uiMessage, 0);
         }
         switch(eprototype)
         {
         case PrototypeNone:
            {
               pbase = canew(base(get_app()));
            }
            break;
         case PrototypeCreate:
            {
               pbase = canew(::ca::message::create(get_app()));
            }
            break;
         case PrototypeNcActivate:
            {
               pbase = canew(nc_activate(get_app()));
            }
            break;
         case PrototypeKey:
            {
               pbase = canew(key(get_app()));
            }
            break;
         case PrototypeTimer:
            {
               pbase = canew(timer(get_app()));
            }
            break;
         case PrototypeShowWindow:
            {
               pbase = canew(show_window(get_app()));
            }
            break;
         case PrototypeSetCursor:
            {
               pbase = canew(set_cursor(get_app()));
            }
            break;
         case PrototypeNcHitTest:
            {
               pbase = canew(nchittest(get_app()));
            }
            break;
         case PrototypeMove:
            {
               pbase = canew(move(get_app()));
            }
            break;
         case PrototypeEraseBkgnd:
            {
               pbase = canew(erase_bkgnd(get_app()));
            }
            break;
         case PrototypeScroll:
            {
               pbase = canew(scroll(get_app()));
            }
            break;
         case PrototypeSetFocus:
            {
               pbase = canew(set_focus(get_app()));
            }
            break;
#if !defined(METROWIN) && !defined(LINUX) && !defined(MACOS)
         case PrototypeWindowPos:
            {
               pbase = canew(window_pos(get_app()));
            }
            break;
         case PrototypeNcCalcSize:
            {
               pbase = canew(nc_calc_size(get_app()));
            }
            break;
#endif
         case PrototypeMouse:
            {
               pbase = canew(mouse(get_app()));
            }
            break;
         case PrototypeMouseWheel:
            {
               pbase = canew(mouse_wheel(get_app()));
            }
            break;
         case PrototypeSize:
            {
               pbase = canew(size(get_app()));
            }
            break;
         case PrototypeActivate:
            {
               pbase = canew(activate(get_app()));
            }
            break;
         default:
            {
               pbase = canew(base(get_app()));
            }
            break;
         }
         if(pbase == ::null())
            return ::null();
         pbase->set(pwnd, uiMessage, wparam, lparam);
         return pbase;
      }

      sp(base) dispatch::get_base(LPMESSAGE lpmsg, sp(::user::interaction) pwnd)
      {
#if defined(METROWIN)
         if(pwnd == ::null() && lpmsg->oswindow != ::null())
         {
            sp(::user::interaction) pwindow = lpmsg->oswindow.window();
#else
         if(pwnd == ::null() && lpmsg->hwnd != ::null())
         {
            if(lpmsg->message == 126)
            {

               TRACE0("WM_DISPLAYCHANGE");
            }
            sp(::user::interaction) pwindow = System.window_from_os_data(lpmsg->hwnd);
#endif
            if(pwindow != ::null())
            {
               try
               {
                  pwnd = pwindow->m_pguie;
               }
               catch(...)
               {
                  pwnd = ::null();
               }
            }

            if(pwnd == ::null())
               return ::null();

         }

         return get_base(pwnd, lpmsg->message, lpmsg->wParam, lpmsg->lParam);

      }


#ifdef LINUX

      sp(base) dispatch::get_base(XEvent * pevent, sp(::user::interaction) pwnd)
      {

         throw todo(get_app());

      }


#endif

      dispatch::dispatch() :
         m_pevOk(::null()),
         m_pmutex(::null())
      {
         m_pfnDispatchWindowProc    = &dispatch::_start_user_message_handler;
      }

      void dispatch::_user_message_handler(::ca::signal_object * pobj)
      {

         dispatch_event_ok()->wait();

         SignalPtrArray signalptra;
         SCAST_PTR(::ca::message::base, pbase, pobj);
         if(pbase->m_uiMessage == (WM_APP + 2014))
         {
            sp(base) pbase2 = pbase->m_lparam;
            _user_message_handler(pbase2);
            if(pbase2->m_wparam != 0)
            {
               delete pbase;
            }
            return;
         }
         m_signala.GetSignalsByMessage(signalptra, pbase->m_uiMessage, 0, 0);
         for(int32_t i = 0; i < signalptra.get_size(); i++)
         {
            Signal & signal = *signalptra[i];
            ::ca::signal * psignal = signal.m_psignal;
            pobj->m_psignal = psignal;
            psignal->emit(pobj);
            if(pobj->m_bRet)
               return;
         }
      }


   /////////////////////////////////////////////////////////////////////////////
   // WM_NOTIFY support

   struct __NOTIFY
   {
      LRESULT* pResult;
      NMHDR* pNMHDR;
   };



      //bool dispatch::_iguimessageDispatchCommandMessage(
         // BaseCommand * pcommand,
         //bool & b)
      //{
         /*int32_t & i = m_iHandling;
         SignalPtrArray signalptra;
         m_signala.GetSignalsByMessage(signalptra, nMsg, nCode, nID);
         for(i = 0; i < signalptra.get_size(); i++)
         {
            Signal & signal = *signalptra[i];
            if(pcommand->m_bHasCommandHandler)
            {
               update_cmd_ui updatecmdui;
               updatecmdui.m_pcmdui = (cmd_ui *)pExtra;
               signal.m_psignal->emit(&updatecmdui);
               b = TRUE;
               if(updatecmdui.m_pcmdui->m_bEnableChanged)
                  return true;
            }
            else
            {
               switch(signal.m_eprototype)
               {
   /*            case PrototypeNotify:
                  {

                     __NOTIFY* pNotify = (__NOTIFY*)pExtra;
                     ASSERT(pNotify != ::null());
                     ASSERT(pNotify->pResult != ::null());
                     ASSERT(pNotify->pNMHDR != ::null());
                     notify notify;
                     notify.m_lparam = (LPARAM) pNotify->pNMHDR;
                     signal.m_psignal->emit(&notify);
                     if(notify.m_bRet)
                        return true;
                  }
                  break;*/
               /*case PrototypeCommand:
                  {
                     if (pHandlerInfo != ::null())
                     {
                        // just fill in the information, don't do it
                        //pHandlerInfo->pTarget = (command_target *) 1;
                        //pHandlerInfo->pmf = (void (__MSG_CALL command_target::*)()) ::null();
                        b = TRUE;
                        return true;
                     }
                     else
                     {
                        BaseCommandSignal command(m_signalOnCommand);
                        command.m_pcommand = pcommand;
                        m_signalOnCommand.m_psignal->emit(&command);
                        if(command.m_bRet)
                           return true;
                     }
                  }
                  break;
               default:
                  // Unknown Prototype
                  ASSERT(FALSE);
                  return false;
               }
            }
         }*/
         //return false;
      //}


      void dispatch::RemoveMessageHandler(::ca::signalizable * psignalizable)
      {
         UNREFERENCED_PARAMETER(psignalizable);
   /* xxx     HandlerItemArray & itema = m_handlerset.m_itema;
         for(int32_t i = 0; i < itema.get_size();)
         {
            if(itema[i]->get_signalizable() == psignalizable)
            {
               itema.remove_at(i);
            }
            else
            {
               i++;
            }
         }
   /*      HandlerMap::pair * ppair = m_handlerset.m_map.PGetFirstAssoc();
         while(ppair != ::null())
         {
            ppair = m_handlerset.m_map.PGetNextAssoc(ppair);
         }*/

      }

      dispatch::SignalArray::~SignalArray()
      {
      }


      sp(::ca::window) dispatch::_GetWnd()
      {
         return dynamic_cast < ::ca::window * > (this);
      }

      Handler::Handler()
      {
   //xxx      HookMessageHandler(this);
      }

      Handler::~Handler()
      {
   //xxx      UnhookMessageHandler(this);
      }

      int32_t Handler::OnMessage(UINT /*message*/, UINT /*uiParam1*/, UINT /*uiParam2*/)
      {
         return 0;
      }


      e_prototype dispatch::GetMessagePrototype(UINT uiMessage, UINT uiCode)
      {
         switch(uiMessage)
         {
         case WM_SIZE:
            return PrototypeSize;
         case WM_HSCROLL:
         case WM_VSCROLL:
            return PrototypeScroll;
         case WM_CREATE:
         case WM_NCCREATE:
            return PrototypeCreate;
         case WM_MOVE:
            return PrototypeMove;
         case WM_ACTIVATE:
            return PrototypeActivate;
         case WM_MEASUREITEM:
            return PrototypeMeasureItem;
#ifdef WINDOWS
         case WM_NOTIFY:
            return PrototypeNotify;
#endif
         case WM_COMMAND:
            {
               switch(uiCode)
               {
               case CN_UPDATE_COMMAND_UI:
                  return PrototypeUpdateCommandUserInterface;
               default:
                  return PrototypeCommand;
               }
            }
         case WM_MOUSEMOVE:
         case WM_LBUTTONDOWN:
         case WM_LBUTTONUP:
         case WM_LBUTTONDBLCLK:
         case WM_RBUTTONDOWN:
         case WM_RBUTTONUP:
         case WM_RBUTTONDBLCLK:
         case WM_MBUTTONDOWN:
         case WM_MBUTTONUP:
         case WM_MBUTTONDBLCLK:
         case WM_NCMOUSEMOVE:
         case WM_NCLBUTTONDOWN:
         case WM_NCLBUTTONUP:
            return PrototypeMouse;
#ifdef WINDOWS
         case WM_MOUSEWHEEL:
            return PrototypeMouseWheel;
#endif
         case WM_NCACTIVATE:
            return PrototypeNcActivate;
         case WM_TIMER:
            return PrototypeTimer;
         case WM_KEYDOWN:
         case WM_KEYUP:
         case WM_CHAR:
         case WM_DEADCHAR:
         case WM_SYSKEYDOWN:
         case WM_SYSKEYUP:
         case WM_SYSCHAR:
         case WM_SYSDEADCHAR:
   #if(_WIN32_WINNT >= 0x0501)
         case WM_UNICHAR:
   #endif
            return PrototypeKey;
         case WM_NCHITTEST:
            return PrototypeNcHitTest;
         case WM_SETCURSOR:
            return PrototypeSetCursor;
         case WM_ERASEBKGND:
            return PrototypeEraseBkgnd;
         case WM_SHOWWINDOW:
            return PrototypeShowWindow;
         case WM_INITMENUPOPUP:
            return PrototypeInitMenuPopup;
#ifdef WINDOWS
         case WM_CTLCOLOR:
            return PrototypeCtlColor;
         case WM_CTLCOLOR + WM_REFLECT_BASE:
            return PrototypeCtlColorReflect;
#endif
         case WM_SETFOCUS:
            return PrototypeSetFocus;
         case WM_WINDOWPOSCHANGING:
            return PrototypeWindowPos;
         case WM_NCCALCSIZE:
            return PrototypeNcCalcSize;
         case WM_PAINT:
            return PrototypeNone;
         default:
            return PrototypeNone;
         }
      }

      base::base(sp(::ca::application) papp, ::ca::signal * psignal) :
         ca(papp),
         signal_object(psignal)
      {
         m_lresult = 0;
         m_plresult = &m_lresult;
      }

      base::base(sp(::ca::application) papp, sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult) :
         ca(papp),
         signal_object(papp)
      {
         m_lresult = 0;
         set(pwnd, uiMessage, wparam, lparam, lresult);
      }

      void base::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         m_pwnd         = pwnd;
         m_uiMessage    = uiMessage;
         m_wparam       = wparam;
         m_lparam       = lparam;
         m_plresult     = &lresult;
      }

      void base::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam)
      {
         set(pwnd, uiMessage, wparam, lparam, m_lresult);
      }

      void base::set_lresult(LRESULT lresult)
      {
         *m_plresult = lresult;
      }

      LRESULT & base::get_lresult()
      {
         return *m_plresult;
      }

      void create::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_lpcreatestruct = reinterpret_cast<LPCREATESTRUCT>(lparam);
      }

      void create::set_lresult(LRESULT lresult)
      {
         base::set_lresult(lresult);
         if(get_lresult() == -1)
            m_bRet = true;
         else
            m_bRet = false;
      }

      void create::failed(const char * lpcszErrorMessage)
      {
         error(lpcszErrorMessage);
      }

      void create::error(const char * lpcszErrorMessage)
      {
         set_lresult(-1);
         TRACE0(lpcszErrorMessage);
         System.log().print(lpcszErrorMessage);
      }

      void timer::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_nIDEvent = static_cast<UINT>(wparam);
      }

      activate::activate(sp(::ca::application) papp) :
         ca(papp),
         ::ca::message::base(papp)
      {
      }

      void activate::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_nState = (UINT)(LOWORD(wparam));
         m_pWndOther = System.window_from_os_data((void *) lparam);
         m_bMinimized = HIWORD(wparam) != FALSE;
      }



      erase_bkgnd::erase_bkgnd(sp(::ca::application) papp) :
         ca(papp),
         ::ca::message::base(papp)
      {
      }

      void erase_bkgnd::set_result(bool bResult)
      {
         set_lresult(bResult);
      }

      key::key(sp(::ca::application) papp) :
         ca(papp),
         ::ca::message::base(papp)
      {
      }

      void key::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {

         base::set(pwnd, uiMessage, wparam, lparam, lresult);

         m_nChar = static_cast<UINT>(wparam);

         m_nRepCnt = LOWORD(lparam);

         m_nFlags = HIWORD(lparam);

         System.user()->keyboard().translate_os_key_message(this);

      }

      nc_activate::nc_activate(sp(::ca::application) papp) :
         ca(papp),
         ::ca::message::base(papp)
      {
      }

      void nc_activate::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_bActive = wparam != FALSE;
      }

      void size::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_nType     = static_cast < UINT > (wparam);
         m_size      = ::size(LOWORD(lparam), HIWORD(lparam));
      }

      mouse::mouse(sp(::ca::application) papp) :
         ca(papp),
         base(papp),
         m_ecursor(::visual::cursor_unmodified)
      {
      }

      mouse::~mouse()
      {
         try
         {
            if(m_ecursor != ::visual::cursor_unmodified && m_papp != ::null() && m_papp->m_psession != ::null())
            {
               Session.set_cursor(m_ecursor);
            }
         }
         catch(...)
         {
         }
      }

      void mouse::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_nFlags    = wparam;
         m_pt        = point(lparam);
#ifdef LINUX
         m_bTranslated = true;  // in root coordinates
#elif defined(WINDOWS)
         m_bTranslated = false; // not in root coordinates
#else
         m_bTranslated = false; // not in root coordinates
#endif
      }

      void mouse_wheel::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_nFlags    = wparam;
         m_pt        = point(lparam);
         m_bTranslated = true;
      }

      sp(::user::interaction) mouse_activate::GetDesktopWindow()
      {
         throw not_implemented(get_app());
         return ::null();
//            return ::ca::window::from_handle(reinterpret_cast<oswindow>(m_wparam));
      }

      UINT mouse_activate::GetHitTest()
      {
         return LOWORD(m_lparam);
      }

      UINT mouse_activate::GetMessage()
      {
         return HIWORD(m_lparam);
      }

      sp(::ca::window) context_menu::GetWindow()
      {
         throw not_implemented(get_app());
         return ::null();
//            return ::ca::window::from_handle(reinterpret_cast<oswindow>(m_wparam));
      }

      point context_menu::GetPoint()
      {
         return point(m_lparam);
      }


      void scroll::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_nSBCode = (int16_t) LOWORD(wparam);
         m_nPos = (int16_t) HIWORD(wparam);
         m_pScrollBar = (sp(::user::interaction)) lparam;
      }

      void show_window::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_bShow = wparam != FALSE;
         m_nStatus = static_cast<UINT>(lparam);
      }

      void set_focus::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         //m_pwnd = System.window_from_os_data(reinterpret_cast<oswindow>(wparam));
         m_pwnd = ::null();
      }

      void window_pos::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_pwindowpos = reinterpret_cast<WINDOWPOS*>(lparam);
      }

      void nc_calc_size::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_pparams = reinterpret_cast<NCCALCSIZE_PARAMS*>(lparam);
      }

      bool nc_calc_size::GetCalcValidRects()
      {
         return m_wparam != FALSE;
      }


      bool enable::get_enable()
      {
         return m_wparam != 0;
      }





      UINT mouse_wheel::GetFlags()
      {
         return LOWORD(m_wparam);
      }

      int16_t mouse_wheel::GetDelta()
      {
         return (int16_t)HIWORD(m_wparam);
      }

      point mouse_wheel::GetPoint()
      {
         return point(GET_X_LPARAM(m_lparam), GET_Y_LPARAM(m_lparam));
      }

      UINT command::GetNotifyCode()
      {
         return HIWORD(m_wparam);
      }

      UINT command::GetId()
      {
         return LOWORD(m_wparam);
      }

#ifdef WINDOWS

      oswindow command::get_oswindow()
      {
         return (oswindow) m_lparam;
      }

#endif

#ifdef WINDOWSEX

      LPNMHDR notify::get_lpnmhdr()
      {
         return (LPNMHDR) m_lparam;
      }

      int32_t notify::get_ctrl_id()
      {
         return (int32_t) m_wparam;
      }

#endif

      dispatch::Signal::Signal()
      {
         m_psignal = ::null();
      }

      dispatch::Signal::~Signal()
      {
         if(m_psignal != ::null())
         {
            delete m_psignal;
            m_psignal = ::null();
         }
      }

      dispatch::HandlerItemBase::~HandlerItemBase()
      {

      }

      dispatch::HandlerItemArray::~HandlerItemArray()
      {
         for(int32_t i = 0; i < this->get_size(); i++)
         {
            delete this->element_at(i);
         }
      }

      bool dispatch::HandlerItemArray::HasSignalizable(::ca::signalizable * psignalizable)
      {
         for(int32_t i = 0; i < this->get_size(); i++)
         {
            if(this->element_at(i)->get_signalizable() == psignalizable)
               return true;
         }
         return false;
      }

      void dispatch::_start_user_message_handler(::ca::signal_object * pobj)
      {
         single_lock sl(dispatch_mutex(), true);
         _on_start_user_message_handler();
         install_message_handling(this);
         if(get_app() == ::null())
         {
            set_app(calc_app());
         }
         dispatch_event_ok()->SetEvent();
         sl.unlock();
         return _user_message_handler(pobj);
      }

      void dispatch::install_message_handling(dispatch * pinterface)
      {
         UNREFERENCED_PARAMETER(pinterface);
      }

      void dispatch::_on_start_user_message_handler()
      {
         m_pfnDispatchWindowProc = &dispatch::_user_message_handler;
      }

      sp(::ca::application) dispatch::calc_app()
      {
         return ::null();
      }

      void dispatch::_001ClearMessageHandling()
      {
         m_signala.remove_all();
         //m_signalInstallMessageHandling.remove_all();
      }


      UINT translate_to_os_message(UINT uiMessage)
      {

#ifdef WINDOWS

         switch(uiMessage)
         {
            case message_create:
               return WM_CREATE;
            default:
               return uiMessage;
         };
#elif defined(LINUX)
         switch(uiMessage)
         {
            case message_create:
               return WM_CREATE;
            default:
               return uiMessage;
         };

#else
         switch(uiMessage)
         {
            default:
               return uiMessage;
         };
#endif

      }


   } // namespace user


} // namespace win





   //         e_prototype eprototype = signal.m_eprototype;
   /*         switch(eprototype)
            {
            case PrototypeNone:
               {
                  base base(get_app());
                  base.m_psignal = psignal;
                  base.set(message, wparam, lparam, lresult);
                  psignal->emit(&base);
                  if(base.m_bRet)
                     return true;
               }
               break;

            case PrototypeCreate:
               {
                  create create(allocer());
                  create.m_psignal = psignal;
                  create.set(message, wparam, lparam, lresult);
                  psignal->emit(&create);
                  if(create.m_bRet)
                     return true;
               }
               break;
            case PrototypeNcActivate:
               {
                  nc_activate ncactivate(get_app());
                  ncactivate.m_psignal = psignal;
                  ncactivate.set(message, wparam, lparam, lresult);
                  ncactivate.m_bActive = static_cast<bool>(wparam);
                  psignal->emit(&ncactivate);
                  if(ncactivate.m_bRet)
                     return true;
               }
               break;
            case PrototypeKey:
               {
                  key key(get_app());
                  key.m_psignal = psignal;
                  key.set(message, wparam, lparam, lresult);
                  psignal->emit(&key);
                  if(key.m_bRet)
                     return true;
               }
               break;
            case PrototypeTimer:
               {
                  timer timer(get_app());
                  timer.m_psignal = psignal;
                  timer.set(message, wparam, lparam, lresult);
                  timer.m_nIDEvent = static_cast<UINT>(wparam);
                  psignal->emit(&timer);
                  if(timer.m_bRet)
                     return true;
               }
               break;
            case PrototypeShowWindow:
               {
                  show_window showwindow(get_app());
                  showwindow.m_psignal = psignal;
                  showwindow.set(message, wparam, lparam, lresult);
                  showwindow.m_bShow = static_cast<UINT>(wparam);
                  showwindow.m_nStatus = static_cast<UINT>(lparam);
                  psignal->emit(&showwindow);
                  if(showwindow.m_bRet)
                     return true;
               }
               break;
            case PrototypeSetCursor:
               {
                  set_cursor setcursor(get_app());
                  setcursor.m_psignal = psignal;
                  setcursor.set(message, wparam, lparam, lresult);
                  //setcursor.m_pWnd = ::ca::window::from_os_data(reinterpret_cast<oswindow>(wparam));
                  setcursor.m_nHitTest = LOWORD(lparam);
                  setcursor.m_message = HIWORD(lparam);
                  psignal->emit(&setcursor);
                  if(setcursor.m_bRet)
                     return true;
               }
               break;
            case PrototypeNcHitTest:
               {
                  nchittest nchittest(get_app());
                  nchittest.m_psignal = psignal;
                  nchittest.set(message, wparam, lparam, lresult);
                  nchittest.m_pt = point(lparam);
                  psignal->emit(&nchittest);
                  if(nchittest.m_bRet)
                     return true;
               }
               break;
            case PrototypeMove:
               {
                  move move(get_app());
                  move.m_psignal = psignal;
                  move.set(message, wparam, lparam, lresult);
                  move.m_pt = point(lparam);
                  psignal->emit(&move);
                  if(move.m_bRet)
                     return true;
               }
               break;
            case PrototypeEraseBkgnd:
               {
                  erase_bkgnd erasebkgnd(get_app());
                  erasebkgnd.m_psignal = psignal;
                  erasebkgnd.set(message, wparam, lparam, lresult);
   //               erasebkgnd.m_pdc = ::ca::graphics_sp::from_handle(reinterpret_cast<HDC>(wparam));
                  psignal->emit(&erasebkgnd);
                  if(erasebkgnd.m_bRet)
                     return true;
               }
               break;

            case PrototypeScroll:
               {
                  scroll scroll(get_app());
                  scroll.m_psignal = psignal;
                  scroll.set(message, wparam, lparam, lresult);
                  psignal->emit(&scroll);
                  if(scroll.m_bRet)
                     return true;
               }
               break;
            case PrototypeSetFocus:
               {
                  set_focus setfocus(get_app());
                  setfocus.set(message, wparam, lparam, lresult);
                  psignal->emit(&setfocus);
                  if(setfocus.m_bRet)
                     return true;
               }
               break;
            case PrototypeWindowPos:
               {
                  window_pos windowpos(get_app());
                  windowpos.set(message, wparam, lparam, lresult);
                  psignal->emit(&windowpos);
                  if(windowpos.m_bRet)
                     return true;
               }
               break;
            case PrototypeNcCalcSize:
               {
                  nc_calc_size nccalcsize(get_app());
                  nccalcsize.set(message, wparam, lparam, lresult);
                  psignal->emit(&nccalcsize);
                  if(nccalcsize.m_bRet)
                     return true;
               }
               break;
            case PrototypeMouse:
            {
               mouse mouse(get_app());
               mouse.m_psignal = psignal;
               mouse.set(message, wparam, lparam, lresult);
               psignal->emit(&mouse);
               if(mouse.m_bRet)
                  return true;
            }
            break;
            case PrototypeSize:
            {
               size size(get_app());
               size.m_psignal = psignal;
               size.set(message, wparam, lparam, lresult);
               psignal->emit(&size);
               if(size.m_bRet)
                  return true;
            }
            break;

            case PrototypeActivate:
            {
               activate activate(get_app());
               activate.m_psignal = psignal;
               activate.set(message, wparam, lparam, lresult);
               activate.m_nState = (UINT)(LOWORD(wparam));
               activate.m_pWndOther = System.window_from_os_data(lparam);
               activate.m_bMinimized = (bool)HIWORD(wparam);
               psignal->emit(&activate);
               if(activate.m_bRet)
                  return true;
               }
               break;
               case PrototypeCtlColor:
                  {
                  // special case for OnCtlColor to avoid too many temporary objects
                  ASSERT(message == WM_CTLCOLOR);
                  myfx_CTLCOLOR* pCtl = reinterpret_cast<myfx_CTLCOLOR*>(lparam);
                  ::ca::graphics_sp dcTemp;
   //               dcTemp.set_handle1(pCtl->hDC);
                  ::ca::window wndTemp;
   //               wndTemp.set_handle(pCtl->oswindow);
                  UINT nCtlType = pCtl->nCtlType;
                  // if not coming from a permanent ::ca::window, use stack temporary
   //               sp(::ca::window) pWnd = ::ca::window::FromHandlePermanent(wndTemp.get_handle());
   //               if (pWnd == ::null())
               {

   //               pWnd = &wndTemp;
      /*         }
               ctl_color ctlcolor(get_app());
               ctlcolor.m_psignal   = psignal;
   //            ctlcolor.m_pdc       = &dcTemp;
   //            ctlcolor.m_pwnd      = pWnd;
               ctlcolor.m_nCtlType  = nCtlType;
               ctlcolor.m_hbrush    = ::null();
               psignal->emit(&ctlcolor);
               // fast detach of temporary objects
   //            dcTemp.set_handle1(::null());
   //            wndTemp.set_handle(::null());
               lresult = reinterpret_cast<LRESULT>(ctlcolor.m_hbrush);
               if(ctlcolor.m_bRet)
                  return true;
               }
                  break;


            /*case PrototypeCtlColorReflect:
               {         // special case for CtlColor to avoid too many temporary objects
                  ASSERT(message == WM_REFLECT_BASE+WM_CTLCOLOR);
                  myfx_CTLCOLOR* pCtl = reinterpret_cast<myfx_CTLCOLOR*>(lparam);
                  ::ca::graphics_sp dcTemp;
   //               dcTemp.set_handle1(pCtl->hDC);
                  UINT nCtlType = pCtl->nCtlType;
                  ctl_color ctlcolor(get_app());
                  ctlcolor.m_psignal   = psignal;
   //               ctlcolor.m_pdc       = &dcTemp;
                  ctlcolor.m_pwnd      = ::null();
                  ctlcolor.m_nCtlType  = nCtlType;
                  ctlcolor.m_hbrush    = ::null();
                  psignal->emit(&ctlcolor);
                  // fast detach of temporary objects
   //               dcTemp.set_handle1(::null());
                  lresult = reinterpret_cast<LRESULT>(ctlcolor.m_hbrush);
                  if(ctlcolor.m_bRet)
                     return true;

               }
               break;*/

         //    default:;
   /*            if(message == WM_COMMAND)
               {
                  command command;
                  command.set(message, wparam, lparam, lresult);
                  psignal->emit(&command);
                  if(command.m_bRet)
                     return true;
               }
               else if(message == WM_NOTIFY)
               {
                  notify notify;
                  notify.set(message, wparam, lparam, lresult);

                  psignal->emit(&notify);
                  if(notify.m_bRet)
                     return true;
               }
               else
               {
                  // Unknown Prototype
                  ASSERT(FALSE);
                  return false;
               }*/
            //  }

#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)

#define IMPLEMENT_SIGNAL_OBJECT_FIXED_ALLOC(class_name) IMPLEMENT_FIXED_ALLOC(class_name, ROUND4(sizeof(class_name) * 32))

