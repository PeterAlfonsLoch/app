#pragma once


namespace message
{


   class dispatch;

   typedef void (dispatch::*PFN_DISPATCH_MESSAGE_HANDLER)(signal_details * pobj);

   class CLASS_DECL_AURA dispatch:
      virtual public ::object
   {
   public:



      class CLASS_DECL_AURA Signal:
         virtual public object
      {
      public:


         e_prototype             m_eprototype;
         UINT                    m_uiMessage;
         UINT                    m_uiCode;
         UINT                    m_uiIdStart;
         UINT                    m_uiIdEnd;
         class ::signal *        m_psignal;

         //HandlerItemArray        m_handlera;

         Signal();
         ~Signal();


      };


      class CLASS_DECL_AURA SignalPtrArray:
         public ref_array < Signal >
      {


      };

      class CLASS_DECL_AURA SignalArray:
         public ptr_array < Signal >
      {
      public:


         SignalArray();
         virtual ~SignalArray();

         void GetSignalsByMessage(SignalPtrArray & signalptra,UINT uiMessage,UINT uiCode,UINT uiId);
         Signal * GetSignalByMessage(UINT uiMessage,UINT uiCode,UINT uiIdStart,UINT uiIdEnd);
         inline Signal * GetSignal(UINT uiMessage,UINT uiCode,UINT uiId,int & i);


      };


      int32_t                       m_iHandling;
      SignalArray                   m_signala;
      class ::signal                m_signalInstallMessageHandling;
      PFN_DISPATCH_MESSAGE_HANDLER  m_pfnDispatchWindowProc;


      dispatch();
      virtual ~dispatch();

      virtual sp(::ace::application) calc_app();

      sp(::signal_details) get_base(UINT uiMessage,WPARAM wparam,LPARAM lparam);

      sp(::signal_details) get_base(LPMESSAGE lpmsg);

      void RemoveMessageHandler(signalizable* psignalizable);

      template < class T >
      bool AddMessageHandler(UINT message, UINT uiCode, UINT uiIdStart, UINT uiIdEnd, T * psignalizable, void (T::*pfn)(signal_details *), bool bAddUnique = true);

      template < class T >
      bool RemoveMessageHandler(UINT message,UINT uiCode,UINT uiIdStart,UINT uiIdEnd,T * psignalizable,void (T::*pfn)(signal_details *));

      virtual e_prototype GetMessagePrototype(UINT uiMessage,UINT uiCode);

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _001ClearMessageHandling();

      virtual void message_handler(signal_details * pobj);

      virtual void _on_start_user_message_handler();

      virtual void _start_user_message_handler(signal_details * pobj);

      virtual void _user_message_handler(signal_details * pobj);

      virtual PFN_DISPATCH_MESSAGE_HANDLER _calc_user_message_handler();


   };


   template < class T >
   bool dispatch::AddMessageHandler(UINT message, UINT uiCode, UINT uiIdStart, UINT uiIdEnd, T * psignalizable, void (T::*pfn)(signal_details *), bool bAddUnique)
   {

      synch_lock sl(m_pmutex);

      Signal * psignal = m_signala.GetSignalByMessage(message,uiCode,uiIdStart,uiIdEnd);

      // If not found a existing Signal, create one
      if(psignal == NULL)
      {
         psignal = new Signal;
         psignal->m_uiMessage = message;
         psignal->m_uiCode = uiCode;
         psignal->m_uiIdStart = uiIdStart;
         psignal->m_uiIdEnd = uiIdEnd;
         psignal->m_eprototype = GetMessagePrototype(message,0);
         psignal->m_psignal = new class ::signal();
         m_signala.add(psignal);
      }
      else
      {
         if(bAddUnique && psignal->m_psignal->is_connected(psignalizable,pfn))
            return true;
      }

      // connect to this signal.
      psignal->m_psignal->connect(psignalizable, pfn);

      m_iHandling++;

      return true;

   }

   template < class T >
   bool dispatch::RemoveMessageHandler(UINT message,UINT uiCode,UINT uiIdStart,UINT uiIdEnd,T * psignalizable,void (T::*pfn)(signal_details *))
   {

      synch_lock sl(m_pmutex);

      Signal * psignal = m_signala.GetSignalByMessage(message,uiCode,uiIdStart,uiIdEnd);

      if(psignal == NULL)
      {
         return true;
      }
      else
      {
         if(!psignal->m_psignal->is_connected(psignalizable,pfn))
            return true;
         do
         {
            psignal->m_psignal->disconnect(psignalizable,pfn);
         } while(psignal->m_psignal->is_connected(psignalizable,pfn));
      }

      m_iHandling--;


      return true;

   }


} // namespace message







