#pragma once


namespace message
{


   class CLASS_DECL_AURA dispatch:
      virtual public ::object
   {
   public:


      class CLASS_DECL_AURA HandlerItemBase:
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


      class CLASS_DECL_AURA HandlerItemArray:
         public array < HandlerItemBase *,HandlerItemBase *>
      {
      public:


         virtual ~HandlerItemArray();
         bool HasSignalizable(signalizable* psignalizable);


      };


      class CLASS_DECL_AURA Signal:
         virtual public element
      {
      public:


         e_prototype             m_eprototype;
         UINT                    m_uiMessage;
         UINT                    m_uiCode;
         UINT                    m_uiIdStart;
         UINT                    m_uiIdEnd;
         sp(class ::signal)      m_psignal;

         HandlerItemArray        m_handlera;

         Signal();
         ~Signal();


      };


      class CLASS_DECL_AURA SignalPtrArray:
         public array < Signal *,Signal * >
      {


      };

      class CLASS_DECL_AURA SignalArray:
         public spa(Signal)
      {
      public:


         SignalArray();
         virtual ~SignalArray();

         void GetSignalsByMessage(SignalPtrArray & signalptra,UINT uiMessage,UINT uiCode,UINT uiId);
         Signal * GetSignalByMessage(UINT uiMessage,UINT uiCode,UINT uiIdStart,UINT uiIdEnd);


      };


      int32_t                       m_iHandling;
      SignalArray                   m_signala;
      class ::signal                m_signalInstallMessageHandling;
      void (dispatch::           *  m_pfnDispatchWindowProc)(signal_details * pobj);


      dispatch();
      virtual ~dispatch();

      virtual sp(::aura::application) calc_app();

      sp(::message::base) get_base(UINT uiMessage,WPARAM wparam,LPARAM lparam);

      sp(::message::base) get_base(LPMESSAGE lpmsg);


      void RemoveMessageHandler(signalizable* psignalizable);

      template < class T >
      bool AddMessageHandler(UINT message, UINT uiCode, UINT uiIdStart, UINT uiIdEnd, T * psignalizable, void (T::*pfn)(signal_details *), bool bAddUnique = true);

      virtual e_prototype GetMessagePrototype(UINT uiMessage,UINT uiCode);

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _001ClearMessageHandling();

      virtual void message_handler(signal_details * pobj);

      virtual void _on_start_user_message_handler();

      virtual void _start_user_message_handler(signal_details * pobj);

      virtual void _user_message_handler(signal_details * pobj);

//#ifdef WINDOWS
//      virtual bool igui_RelayEvent(LPMESSAGE lpmsg);
//#endif

//      virtual bool OnWndMsgPosCreate();


   };




   template < class T >
   bool dispatch::AddMessageHandler(UINT message, UINT uiCode, UINT uiIdStart, UINT uiIdEnd, T * psignalizable, void (T::*pfn)(signal_details *), bool bAddUnique)
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



} // namespace message







