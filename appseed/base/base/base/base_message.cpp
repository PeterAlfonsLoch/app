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


namespace message
{

   class ::signal * CreateSignal()
   {
      return new class ::signal();
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
         return NULL;
      return get_base(lpmsg, pwnd);
   }

   sp(base) dispatch::get_message(LPMESSAGE lpmsg, sp(::user::interaction) pwnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
   {
      if(!::GetMessage(lpmsg, pwnd->get_safe_handle(), wMsgFilterMin, wMsgFilterMax))
         return NULL;
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
      //if(oswindow != NULL)
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
            pbase = canew(::message::create(get_app()));
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
      if(pbase == NULL)
         return NULL;
      pbase->set(pwnd, uiMessage, wparam, lparam);
      return pbase;
   }

   sp(base) dispatch::get_base(LPMESSAGE lpmsg, sp(::user::interaction) pwnd)
   {
#if defined(METROWIN)
      if(pwnd == NULL && lpmsg->oswindow != NULL)
      {
         sp(::user::interaction) pwindow = lpmsg->oswindow->window();
#else
      if(pwnd == NULL && lpmsg->hwnd != NULL)
      {
         if(lpmsg->message == 126)
         {

            TRACE0("WM_DISPLAYCHANGE");
         }
         sp(::user::interaction) pwindow = System.window_from_os_data(lpmsg->hwnd);
#endif
         if(pwindow != NULL)
         {
            try
            {
               pwnd = pwindow->m_pui;
            }
            catch(...)
            {
               pwnd = NULL;
            }
         }

         if(pwnd == NULL)
            return NULL;

      }

      return get_base(pwnd, lpmsg->message, lpmsg->wParam, lpmsg->lParam);

   }


#if defined(LINUX)

   sp(base) dispatch::get_base(XEvent * pevent, sp(::user::interaction) pwnd)
   {

      throw todo(get_app());

   }


#endif

   dispatch::dispatch()// :
      //         m_pevOk(NULL),
      //       m_pmutex(NULL)
   {

      m_pfnDispatchWindowProc    = &dispatch::_start_user_message_handler;

   }


   dispatch::~dispatch()
   {

   }


   void dispatch::_user_message_handler(signal_details * pobj)
   {

      //         dispatch_event_ok()->wait();

      SignalPtrArray signalptra;
      SCAST_PTR(::message::base, pbase, pobj);
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
         class ::signal * psignal = signal.m_psignal;
         pobj->m_psignal = psignal;
         psignal->emit(pobj);
         if(pobj->m_bRet)
            return;
      }
   }


   /////////////////////////////////////////////////////////////////////////////
   // WM_NOTIFY support
#ifdef WINDOWS
   struct __NOTIFY
   {
      LRESULT* pResult;
      NMHDR* pNMHDR;
   };

#endif

   //bool dispatch::_iguimessageDispatchCommandMessage(
   // base_command * pcommand,
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


   void dispatch::RemoveMessageHandler(signalizable* psignalizable)
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
      while(ppair != NULL)
      {
      ppair = m_handlerset.m_map.PGetNextAssoc(ppair);
      }*/

   }

   dispatch::SignalArray::~SignalArray()
   {
   }


   ::window_sp dispatch::_GetWnd()
   {
      return dynamic_cast < window * > (this);
   }


   /*
   Handler::Handler()
   {
   //xxx      HookMessageHandler(this);
   }

   Handler::~Handler()
   {
   //xxx      UnhookMessageHandler(this);
   }
   */

   /////*      int32_t Handler::OnMessage(UINT /*message*/, UINT /*uiParam1*/, UINT /*uiParam2*/)
   //      {
   //         return 0;
   //      }
   //*/

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
/*#ifdef WINDOWS
      case WM_CTLCOLOR:
         if(pba)
         return PrototypeCtlColor;
      case WM_CTLCOLOR + WM_REFLECT_BASE:
         return PrototypeCtlColorReflect;
#endif*/
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

   base::base(sp(base_application) papp, class ::signal * psignal) :
      element(papp),
      signal_details(psignal)
   {
      m_lresult = 0;
      m_plresult = &m_lresult;
   }

   base::base(sp(base_application) papp, sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult) :
      element(papp),
      signal_details(papp)
   {
      m_lresult = 0;
      set(pwnd, uiMessage, wparam, lparam, lresult);
   }

   void base::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
   {
      m_pwnd            = pwnd;
      m_uiMessage       = uiMessage;
      m_wparam          = wparam;
      m_lparam          = lparam;
      m_plresult        = &lresult;
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

   activate::activate(sp(base_application) papp) :
      element(papp),
      message::base(papp)
   {
   }

   void activate::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
   {
      base::set(pwnd, uiMessage, wparam, lparam, lresult);
      m_nState = (UINT)(LOWORD(wparam));
      m_pWndOther = System.window_from_os_data((void *) lparam);
      m_bMinimized = HIWORD(wparam) != FALSE;
   }



   erase_bkgnd::erase_bkgnd(sp(base_application) papp) :
      element(papp),
      message::base(papp)
   {
   }

   void erase_bkgnd::set_result(bool bResult)
   {
      set_lresult(bResult);
   }

   key::key(sp(base_application) papp) :
      element(papp),
      message::base(papp)
   {
   }

   void key::set(sp(::user::interaction) pwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
   {

      base::set(pwnd, uiMessage, wparam, lparam, lresult);

      m_nChar = static_cast<UINT>(wparam);

      m_nRepCnt = LOWORD(lparam);

      m_nFlags = HIWORD(lparam);



   }

   nc_activate::nc_activate(sp(base_application) papp) :
      element(papp),
      message::base(papp)
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

   mouse::mouse(sp(base_application) papp) :
      element(papp),
      base(papp),
      m_ecursor(::visual::cursor_unmodified)
   {
   }

   mouse::~mouse()
   {
      try
      {
         if(m_ecursor != ::visual::cursor_unmodified && m_pbaseapp != NULL && m_pbaseapp->m_pbasesession != NULL)
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
//      return window::from_handle_dup(reinterpret_cast<oswindow>(m_wparam));
      return NULL;
   }

   UINT mouse_activate::GetHitTest()
   {
      return LOWORD(m_lparam);
   }

   UINT mouse_activate::get_message()
   {
      return HIWORD(m_lparam);
   }

   ::window_sp context_menu::GetWindow()
   {
      throw not_implemented(get_app());
      return NULL;
      //            return window::from_handle_dup(reinterpret_cast<oswindow>(m_wparam));
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
      m_pwnd = NULL;
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
      return (oswindow) m_lparam.m_lparam;
   }

#endif

#ifdef WINDOWSEX

   LPNMHDR notify::get_lpnmhdr()
   {
      return (LPNMHDR) m_lparam.m_lparam;
   }

   int32_t notify::get_ctrl_id()
   {
      return (int32_t) m_wparam;
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
         m_psignal.release();
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

   bool dispatch::HandlerItemArray::HasSignalizable(signalizable* psignalizable)
   {
      for(int32_t i = 0; i < this->get_size(); i++)
      {
         if(this->element_at(i)->get_signalizable() == psignalizable)
            return true;
      }
      return false;
   }

   void dispatch::_start_user_message_handler(signal_details * pobj)
   {


      synch_lock ml(&user_mutex());

      if(m_pfnDispatchWindowProc == &dispatch::_user_message_handler)
      {

         ml.unlock();

         _user_message_handler(pobj);

         return;

      }

      m_pfnDispatchWindowProc = &dispatch::_user_message_handler;

      _on_start_user_message_handler();

      install_message_handling(this);

      if(get_app() == NULL)
      {

         set_app(calc_app());

      }

      ml.unlock();

      return _user_message_handler(pobj);

   }


   void dispatch::install_message_handling(dispatch * pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
   }

   void dispatch::_on_start_user_message_handler()
   {
   }

   sp(base_application) dispatch::calc_app()
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
#elif defined(LINUX) ||  defined(MACOS)
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








#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)

#define IMPLEMENT_SIGNAL_OBJECT_FIXED_ALLOC(class_name) IMPLEMENT_FIXED_ALLOC(class_name, ROUND4(sizeof(class_name) * 32))

