#include "framework.h"



namespace message
{

   dispatch::SignalArray::SignalArray()
   {

   }


//#ifdef WINDOWS
//
//   bool dispatch::igui_RelayEvent(LPMESSAGE lpmsg)
//   {
//      switch(lpmsg->message)
//      {
//      case message_pos_create:
//         return OnWndMsgPosCreate();
//         break;
//      default:
//         return false;
//      }
//      return 0;
//   }
//
//#endif
//
//   bool dispatch::OnWndMsgPosCreate()
//   {
//      return true;
//   }

   sp(::signal_details) dispatch::get_base(UINT uiMessage,WPARAM wparam,LPARAM lparam)
   {

      sp(::signal_details) pbase;

      pbase = canew(::message::base(get_app()));

      pbase->m_uiMessage = uiMessage;
      pbase->m_wparam =wparam;
      pbase->m_lparam = lparam;

      return pbase;

   }

   sp(::signal_details) dispatch::get_base(LPMESSAGE lpmsg)
   {

      return m_pauraapp->get_message_base(lpmsg);

   }


   dispatch::dispatch()
   {

      m_pfnDispatchWindowProc    = &dispatch::_start_user_message_handler;

   }


   dispatch::~dispatch()
   {

   }


   void dispatch::message_handler(signal_details * pobj)
   {

      (this->*m_pfnDispatchWindowProc)(pobj);

   }


   void dispatch::_user_message_handler(signal_details * pbase)
   {

      if(pbase->m_uiMessage == (WM_APP + 2014))
      {
         sp(::signal_details) pbase2 = pbase->m_lparam;
         _user_message_handler(pbase2);
         if(pbase2->m_wparam != 0)
         {
            delete pbase;
         }
         return;
      }
      int i = 0;
      Signal * pSignal;
      while((pSignal = m_signala.GetSignal(pbase->m_uiMessage,0,0,i)) != NULL)
      {
         class ::signal * psignal = pSignal->m_psignal;
         pbase->m_psignal = psignal;
         psignal->emit(pbase);
         if(pbase->m_bRet)
            return;
      }


   }


   ::message::PFN_DISPATCH_MESSAGE_HANDLER dispatch::_calc_user_message_handler()
   {

      return &::message::dispatch::_user_message_handler;

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
   // ::ace::command * pcommand,
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

      remove_all();

   }



   e_prototype dispatch::GetMessagePrototype(UINT uiMessage,UINT uiCode)
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
         case WM_CTLCOLOR + WM_REFLECT_AXIS:
         return PrototypeCtlColorReflect;
         #endif*/
      case WM_SETFOCUS:
         return PrototypeSetFocus;
      case WM_WINDOWPOSCHANGING:
      case WM_WINDOWPOSCHANGED:
         return PrototypeWindowPos;
      case WM_NCCALCSIZE:
         return PrototypeNcCalcSize;
      case WM_PAINT:
         return PrototypeNone;
      default:
         return PrototypeNone;
      }
   }


   dispatch::Signal::Signal()
   {

      m_psignal = NULL;

   }

   dispatch::Signal::~Signal()
   {
      ::ace::del(m_psignal);
   }

//   dispatch::HandlerItemBase::~HandlerItemBase()
//   {
//
//   }
//

   void dispatch::_start_user_message_handler(signal_details * pobj)
   {


      synch_lock ml(&message_dispatch_mutex());

      if(m_pfnDispatchWindowProc == _calc_user_message_handler())
      {

         ml.unlock();

         _user_message_handler(pobj);

         return;

      }

      m_pfnDispatchWindowProc = _calc_user_message_handler();

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

   sp(::ace::application) dispatch::calc_app()
   {
      return NULL;
   }

   void dispatch::_001ClearMessageHandling()
   {
      m_signala.remove_all();
      //m_signalInstallMessageHandling.remove_all();
   }


} // namespace message
