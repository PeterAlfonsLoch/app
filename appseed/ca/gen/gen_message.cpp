#include "framework.h"

#if defined(LINUX) || defined(MACOS)
// Ubuntu apt-get install libx11-dev
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#endif

#undef new

struct myfx_CTLCOLOR
{
   HWND hWnd;
   HDC hDC;
   UINT nCtlType;
};


namespace gen
{


   namespace message
   {

      gen::signal * CreateSignal()
      {
         return new gen::signal();
      }


      /*
      base_array < Handler *, Handler * > theMessageHandlerArray;

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
         for(int i = 0; i < theMessageHandlerArray.get_size(); i++)
         {
            theMessageHandlerArray[i]->OnMessage(mparam, nparam, oparam);
         }
      }
      */

#ifdef WINDOWS

      bool dispatch::igui_RelayEvent(LPMSG lpmsg)
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

#ifdef WINDOWS

      base * dispatch::peek_message(LPMSG lpmsg, ::user::interaction * pwnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
      {
         if(!::PeekMessageA(lpmsg, pwnd->get_safe_handle(), wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
            return NULL;
         return get_base(lpmsg, pwnd);
      }

      base * dispatch::get_message(LPMSG lpmsg, ::user::interaction * pwnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
      {
         if(!::GetMessageA(lpmsg, pwnd->get_safe_handle(), wMsgFilterMin, wMsgFilterMax))
            return NULL;
         return get_base(lpmsg, pwnd);
      }

      base * dispatch::peek_message(::user::interaction * pwnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
      {
         MSG msg;
         return peek_message(&msg, pwnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
      }


      base * dispatch::get_message(::user::interaction * pwnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
      {
         MSG msg;
         return get_message(&msg, pwnd, wMsgFilterMin, wMsgFilterMax);
      }

      base * dispatch::get_base(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam)
      {
         base * pbase;
         e_prototype eprototype = PrototypeNone;
         //if(hwnd != NULL)
         {
            eprototype = dispatch::GetMessagePrototype(uiMessage, 0);
         }
         switch(eprototype)
         {
         case PrototypeNone:
            {
               pbase = new base(get_app());
            }
            break;
         case PrototypeCreate:
            {
               pbase = new ::gen::message::create(get_app());
            }
            break;
         case PrototypeNcActivate:
            {
               pbase = new nc_activate(get_app());
            }
            break;
         case PrototypeKey:
            {
               pbase = new key(get_app());
            }
            break;
         case PrototypeTimer:
            {
               pbase = new timer(get_app());
            }
            break;
         case PrototypeShowWindow:
            {
               pbase = new show_window(get_app());
            }
            break;
         case PrototypeSetCursor:
            {
               pbase = new set_cursor(get_app());
            }
            break;
         case PrototypeNcHitTest:
            {
               pbase = new nchittest(get_app());
            }
            break;
         case PrototypeMove:
            {
               pbase = new move(get_app());
            }
            break;
         case PrototypeEraseBkgnd:
            {
               pbase = new erase_bkgnd(get_app());
            }
            break;
         case PrototypeScroll:
            {
               pbase = new scroll(get_app());
            }
            break;
         case PrototypeSetFocus:
            {
               pbase = new set_focus(get_app());
            }
            break;
         case PrototypeWindowPos:
            {
               pbase = new window_pos(get_app());
            }
            break;
         case PrototypeNcCalcSize:
            {
               pbase = new nc_calc_size(get_app());
            }
            break;
         case PrototypeMouse:
            {
               pbase = new mouse(get_app());
            }
            break;
         case PrototypeMouseWheel:
            {
               pbase = new mouse_wheel(get_app());
            }
            break;
         case PrototypeSize:
            {
               pbase = new size(get_app());
            }
            break;
         case PrototypeActivate:
            {
               pbase = new activate(get_app());
            }
            break;
         default:
            {
               pbase = new base(get_app());
            }
            break;
         }
         if(pbase == NULL)
            return NULL;
         pbase->set(pwnd, uiMessage, wparam, lparam);
         return pbase;
      }

      base * dispatch::get_base(LPMSG lpmsg, ::user::interaction * pwnd)
      {
         if(pwnd == NULL && lpmsg->hwnd != NULL)
         {
            ::ca::window * pwindow = System.window_from_os_data(lpmsg->hwnd);
            if(pwindow != NULL)
            {
               try
               {
                  pwnd = pwindow->m_pguie;
               }
               catch(...)
               {
                  pwnd = NULL;
               }
            }
         }

         return get_base(pwnd, lpmsg->message, lpmsg->wParam, lpmsg->lParam);
      }

#endif

      dispatch::dispatch()
      {
         m_pfnDispatchWindowProc    = &dispatch::_start_user_message_handler;
      }

      void dispatch::_user_message_handler(gen::signal_object * pobj)
      {
         SignalPtrArray signalptra;
         SCAST_PTR(gen::message::base, pbase, pobj);
         if(pbase->m_uiMessage == (WM_APP + 2014))
         {
            base * pbase2 = (base *) pbase->m_lparam;
            _user_message_handler(pbase2);
            if(pbase2->m_wparam != 0)
            {
               delete pbase;
            }
            return;
         }
         m_signala.GetSignalsByMessage(signalptra, pbase->m_uiMessage, 0, 0);
         for(int i = 0; i < signalptra.get_size(); i++)
         {
            Signal & signal = *signalptra[i];
            gen::signal * psignal = signal.m_psignal;
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
         /*int & i = m_iHandling;
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
                     ASSERT(pNotify != NULL);
                     ASSERT(pNotify->pResult != NULL);
                     ASSERT(pNotify->pNMHDR != NULL);
                     notify notify;
                     notify.m_lparam = (LPARAM) pNotify->pNMHDR;
                     signal.m_psignal->emit(&notify);
                     if(notify.m_bRet)
                        return true;
                  }
                  break;*/
               /*case PrototypeCommand:
                  {
                     if (pHandlerInfo != NULL)
                     {
                        // just fill in the information, don't do it
                        //pHandlerInfo->pTarget = (command_target *) 1;
                        //pHandlerInfo->pmf = (void (__MSG_CALL command_target::*)()) NULL;
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


      void dispatch::RemoveMessageHandler(gen::signalizable * psignalizable)
      {
         UNREFERENCED_PARAMETER(psignalizable);
   /* xxx     HandlerItemArray & itema = m_handlerset.m_itema;
         for(int i = 0; i < itema.get_size();)
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
         while(ppair != NULL)
         {
            ppair = m_handlerset.m_map.PGetNextAssoc(ppair);
         }*/

      }

      dispatch::SignalArray::~SignalArray()
      {
      }


      ::ca::window * dispatch::_GetWnd()
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

      int Handler::OnMessage(UINT /*message*/, UINT /*uiParam1*/, UINT /*uiParam2*/)
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
         default:
            return PrototypeNone;
         }
      }

      base::base(::ca::application * papp, gen::signal * psignal) :
         ca(papp),
         signal_object(psignal)
      {
         m_lresult = 0;
         m_plresult = &m_lresult;
      }

      base::base(::ca::application * papp, ::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult) :
         ca(papp),
         signal_object(papp)
      {
         m_lresult = 0;
         set(pwnd, uiMessage, wparam, lparam, lresult);
      }

      void base::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         m_pwnd         = pwnd;
         m_uiMessage    = uiMessage;
         m_wparam       = wparam;
         m_lparam       = lparam;
         m_plresult     = &lresult;
      }

      void base::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam)
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

      void create::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
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

      void create::error(const char * lpcszErrorMessage)
      {
         set_lresult(-1);
         TRACE(lpcszErrorMessage);
         System.log().print(lpcszErrorMessage);
      }

      void timer::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_nIDEvent = static_cast<UINT>(wparam);
      }

      activate::activate(::ca::application * papp) :
         ca(papp),
         ::gen::message::base(papp)
      {
      }

      void activate::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_nState = (UINT)(LOWORD(wparam));
         m_pWndOther = System.window_from_os_data((HWND)lparam);
         m_bMinimized = HIWORD(wparam) != FALSE;
      }



      erase_bkgnd::erase_bkgnd(::ca::application * papp) :
         ca(papp),
         ::gen::message::base(papp)
      {
      }

      void erase_bkgnd::set_result(bool bResult)
      {
         set_lresult(bResult);
      }

      key::key(::ca::application * papp) :
         ca(papp),
         ::gen::message::base(papp)
      {
      }

      void key::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_nChar = static_cast<UINT>(wparam);
         m_nRepCnt = LOWORD(lparam);
         m_nFlags = HIWORD(lparam);
      }

      nc_activate::nc_activate(::ca::application * papp) :
         ca(papp),
         ::gen::message::base(papp)
      {
      }

      void nc_activate::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_bActive = wparam != FALSE;
      }

      void size::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_nType     = static_cast < UINT > (wparam);
         m_size      = ::size(LOWORD(lparam), HIWORD(lparam));
      }

      mouse::mouse(::ca::application * papp) :
         ca(papp),
         base(papp),
         m_ecursor(::visual::cursor_unmodified)
      {
      }

      mouse::~mouse()
      {
         try
         {
            if(m_ecursor != ::visual::cursor_unmodified && m_psession != NULL)
            {
               Application.set_cursor(m_ecursor);
            }
         }
         catch(...)
         {
         }
      }

#ifdef WINDOWS

      void mouse::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_nFlags    = wparam;
         m_pt        = point(lparam);
         m_bTranslated = false;
      }

#endif

      void mouse_wheel::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_nFlags    = wparam;
         m_pt        = point(lparam);
         m_bTranslated = true;
      }

      ::user::interaction * mouse_activate::GetDesktopWindow()
      {
         throw not_implemented_exception();
         return NULL;
//            return ::ca::window::from_handle(reinterpret_cast<HWND>(m_wparam));
      }

      UINT mouse_activate::GetHitTest()
      {
         return LOWORD(m_lparam);
      }

      UINT mouse_activate::GetMessage()
      {
         return HIWORD(m_lparam);
      }

      ::ca::window * context_menu::GetWindow()
      {
         throw not_implemented_exception();
         return NULL;
//            return ::ca::window::from_handle(reinterpret_cast<HWND>(m_wparam));
      }

      point context_menu::GetPoint()
      {
         return point(m_lparam);
      }


      void scroll::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_nSBCode = (short) LOWORD(wparam);
         m_nPos = (short) HIWORD(wparam);
         m_pScrollBar = (::user::interaction *) lparam;
      }

      void show_window::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_bShow = wparam != FALSE;
         m_nStatus = static_cast<UINT>(lparam);
      }

      void set_focus::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         //m_pwnd = System.window_from_os_data(reinterpret_cast<HWND>(wparam));
         m_pwnd = NULL;
      }

      void window_pos::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_pwindowpos = reinterpret_cast<WINDOWPOS*>(lparam);
      }

      void nc_calc_size::set(::user::interaction * pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
      {
         base::set(pwnd, uiMessage, wparam, lparam, lresult);
         m_pparams = reinterpret_cast<NCCALCSIZE_PARAMS*>(lparam);
      }


      bool enable::get_enable()
      {
         return m_wparam != 0;
      }

      bool nc_calc_size::GetCalcValidRects()
      {
         return m_wparam != FALSE;
      }




      UINT mouse_wheel::GetFlags()
      {
         return LOWORD(m_wparam);
      }

      short mouse_wheel::GetDelta()
      {
         return (short)HIWORD(m_wparam);
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

      HWND command::GetHwnd()
      {
         return (HWND) m_lparam;
      }

#ifdef WINDOWS

      LPNMHDR notify::get_lpnmhdr()
      {
         return (LPNMHDR) m_lparam;
      }

      int notify::get_ctrl_id()
      {
         return (int) m_wparam;
      }

#endif

      dispatch::Signal::Signal()
      {
         m_psignal = NULL;
      }

      dispatch::Signal::~Signal()
      {
         if(m_psignal != NULL)
         {
            delete m_psignal;
            m_psignal = NULL;
         }
      }

      dispatch::HandlerItemArray::~HandlerItemArray()
      {
         for(int i = 0; i < this->get_size(); i++)
         {
            delete this->element_at(i);
         }
      }

      bool dispatch::HandlerItemArray::HasSignalizable(gen::signalizable * psignalizable)
      {
         for(int i = 0; i < this->get_size(); i++)
         {
            if(this->element_at(i)->get_signalizable() == psignalizable)
               return true;
         }
         return false;
      }

      void dispatch::_start_user_message_handler(gen::signal_object * pobj)
      {
         _on_start_user_message_handler();
         install_message_handling(this);
         if(get_app() == NULL)
         {
            set_app(calc_app());
         }
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

      ::ca::application * dispatch::calc_app()
      {
         return NULL;
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

#else
         switch(uiMessage)
         {
            case message_create:
               return CreateNotify;
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
                  create create(get_app());
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
                  //setcursor.m_pWnd = ::ca::window::from_os_data(reinterpret_cast<HWND>(wparam));
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
               activate.m_pWndOther = System.window_from_os_data((HWND)lparam);
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
   //               wndTemp.set_handle(pCtl->hWnd);
                  UINT nCtlType = pCtl->nCtlType;
                  // if not coming from a permanent ::ca::window, use stack temporary
   //               ::ca::window* pWnd = ::ca::window::FromHandlePermanent(wndTemp.get_handle());
   //               if (pWnd == NULL)
               {

   //               pWnd = &wndTemp;
      /*         }
               ctl_color ctlcolor(get_app());
               ctlcolor.m_psignal   = psignal;
   //            ctlcolor.m_pdc       = &dcTemp;
   //            ctlcolor.m_pwnd      = pWnd;
               ctlcolor.m_nCtlType  = nCtlType;
               ctlcolor.m_hbrush    = NULL;
               psignal->emit(&ctlcolor);
               // fast detach of temporary objects
   //            dcTemp.set_handle1(NULL);
   //            wndTemp.set_handle(NULL);
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
                  ctlcolor.m_pwnd      = NULL;
                  ctlcolor.m_nCtlType  = nCtlType;
                  ctlcolor.m_hbrush    = NULL;
                  psignal->emit(&ctlcolor);
                  // fast detach of temporary objects
   //               dcTemp.set_handle1(NULL);
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

