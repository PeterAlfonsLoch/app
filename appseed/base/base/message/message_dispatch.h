#pragma once


namespace message
{


   class CLASS_DECL_BASE dispatch:
      virtual public ::object
   {
   public:

      class CLASS_DECL_BASE HandlerItemBase:
         virtual public root
      {
      public:
         virtual ~HandlerItemBase();
         virtual signalizable* get_signalizable() = 0;
      };

      template < class T >
      class HandlerItem: public HandlerItemBase
      {
      public:
         T *                     m_psignalizable;
         // Pointer to signal object directly associate with the
         // prototype.
         // This is a cached value and not the
         // storage holder of the object.
         virtual signalizable* get_signalizable() { return m_psignalizable; }
      };

      class CLASS_DECL_BASE HandlerItemArray:
         public array < HandlerItemBase *,HandlerItemBase *>
      {
      public:
         virtual ~HandlerItemArray();
         bool HasSignalizable(signalizable* psignalizable);
      };

      class CLASS_DECL_BASE Signal:
         virtual public element
      {
      public:
         e_prototype          m_eprototype;
         UINT                 m_uiMessage;
         UINT                 m_uiCode;
         UINT                 m_uiIdStart;
         UINT                 m_uiIdEnd;
         sp(class ::signal)     m_psignal;

         HandlerItemArray     m_handlera;

         Signal();
         ~Signal();
      };

      class CLASS_DECL_BASE SignalPtrArray:
         public array < Signal *,Signal * >
      {
      };

      class CLASS_DECL_BASE SignalArray:
         public spa(Signal)
      {
      public:
         virtual ~SignalArray();
         void GetSignalsByMessage(SignalPtrArray & signalptra,UINT uiMessage,UINT uiCode,UINT uiId);
         Signal * GetSignalByMessage(UINT uiMessage,UINT uiCode,UINT uiIdStart,UINT uiIdEnd);
         };


      dispatch();
      virtual ~dispatch();


      virtual void _on_start_user_message_handler();

      virtual sp(::base::application) calc_app();

      virtual sp(base) peek_message(LPMESSAGE lpmsg,sp(::user::interaction) pwnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
      virtual sp(base) get_message(LPMESSAGE lpmsg,sp(::user::interaction) pwnd,UINT wMsgFilterMin,UINT wMsgFilterMax);
      virtual sp(base) peek_message(sp(::user::interaction) pwnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
      virtual sp(base) get_message(sp(::user::interaction) pwnd,UINT wMsgFilterMin,UINT wMsgFilterMax);

      virtual sp(base) get_base(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam);
      virtual sp(base) get_base(LPMESSAGE lpmsg,sp(::user::interaction) pwnd = NULL);

#ifdef LINUX

      virtual sp(base) get_base(XEvent * pevent,sp(::user::interaction) pwnd = NULL);

#endif

      void RemoveMessageHandler(signalizable* psignalizable);
      ::window_sp _GetWnd();
      // Prototype_bool_WPARAM_LPARAM;

      template < class T >
      bool AddMessageHandler(
         UINT message,
         UINT uiCode,
         UINT uiIdStart,
         UINT uiIdEnd,
         T * psignalizable,
         void (T::*pfn)(signal_details *),
         bool bAddUnique = true)
      {
         Signal * psignal = m_signala.GetSignalByMessage(message,uiCode,uiIdStart,uiIdEnd);
         // If not found a existing Signal, create one
         if(psignal == NULL)
         {
            psignal = canew(Signal);
            psignal->m_uiMessage = message;
            psignal->m_uiCode = uiCode;
            psignal->m_uiIdStart = uiIdStart;
            psignal->m_uiIdEnd = uiIdEnd;
            psignal->m_eprototype = GetMessagePrototype(message,0);
            psignal->m_psignal = canew(class ::signal());
            psignal->m_psignal->connect(psignalizable,pfn);
            HandlerItem <T> * pitem = canew(HandlerItem < T >);
            pitem->m_psignalizable = psignalizable;
            psignal->m_handlera.add(pitem);
            m_signala.add(psignal);
         }
         else
         {
            if(bAddUnique && psignal->m_psignal->is_connected(psignalizable,pfn))
               return true;
            // If a matching Signal is found, connect to
            // this signal.
            psignal->m_psignal->connect(psignalizable,pfn);
            HandlerItem <T> * pitem = canew(HandlerItem<T>);
            pitem->m_psignalizable = psignalizable;
            psignal->m_handlera.add(pitem);
         }
         m_iHandling++;
         return true;
      }


      virtual e_prototype GetMessagePrototype(UINT uiMessage,UINT uiCode);

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _001ClearMessageHandling();

      int32_t                    m_iHandling;
      SignalArray                m_signala;
      class ::signal               m_signalInstallMessageHandling;
      //         sp(manual_reset_event)     m_pevOk;
      //         sp(mutex)                  m_pmutex;

      virtual void _start_user_message_handler(signal_details * pobj);

      void (dispatch::*m_pfnDispatchWindowProc)(signal_details * pobj);

      virtual void _user_message_handler(signal_details * pobj);
      //bool _iguimessageDispatchCommandMessage(base_command * pcommand, bool & b);
      // return TRUE to stop routing
#ifdef WINDOWS
      virtual bool igui_RelayEvent(LPMESSAGE lpmsg);
#endif
      virtual bool OnWndMsgPosCreate();


      //         inline manual_reset_event * dispatch_event_ok() { if(m_pevOk != NULL) return m_pevOk; m_pevOk = canew(manual_reset_event(NULL)); return m_pevOk; }
      //         inline mutex * dispatch_mutex() { if(m_pmutex != NULL) return m_pmutex; m_pmutex = canew(::mutex(NULL)); return m_pmutex; }
   };


} // namespace message




