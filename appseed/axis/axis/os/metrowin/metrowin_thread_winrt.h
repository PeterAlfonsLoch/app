#pragma once


template < typename T >
inline void waiter_null_result(T & t)
{
   t = nullptr;
}

template < >
inline void waiter_null_result(bool & b)
{
   b = false;
}


template < typename T >
ref class waiter_for_Windows_Foundation_IAsyncOperation sealed
{
private:

   manual_reset_event                                 m_event;
   ::Windows::Foundation::IAsyncOperation < T > ^     m_operation;
   ::Windows::Foundation::AsyncStatus                 m_status;
   T                                                  m_result;


public:


   waiter_for_Windows_Foundation_IAsyncOperation(::Windows::Foundation::IAsyncOperation < T > ^ operation, Platform::CallbackContext callbackcontext = Platform::CallbackContext::Any) :
      m_event(get_thread_app())
   {

      m_operation             = operation;

      m_operation->Completed  = ref new ::Windows::Foundation::AsyncOperationCompletedHandler < T > ([this](::Windows::Foundation::IAsyncOperation < T > ^ operation, ::Windows::Foundation::AsyncStatus status)
      {
      
         m_status = status;

         m_event.set_event();

      });

   }


   virtual ~waiter_for_Windows_Foundation_IAsyncOperation()
   {

   }
   
   
   T wait(unsigned int dwMillis = INFINITE, ::Windows::Foundation::AsyncStatus * pstatus = NULL)
   {

      m_event.wait(millis(dwMillis));

      if(pstatus != NULL)
         *pstatus = m_status;

      if(m_status == ::Windows::Foundation::AsyncStatus::Completed)
      {

         return m_operation->GetResults();

      }
      else
      {

         T t;

         waiter_null_result(t);

         return t;

      }

   }

};


template < typename T, typename T2 >
ref class waiter_for_Windows_Foundation_IAsyncOperationWithProgress sealed
{
private:

   manual_reset_event                                                m_event;
   ::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > ^    m_operation;
   ::Windows::Foundation::AsyncStatus                                m_status;
   T                                                                 m_result;


public:


   waiter_for_Windows_Foundation_IAsyncOperationWithProgress(::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > ^ operation, Platform::CallbackContext callbackcontext = Platform::CallbackContext::Any) :
      m_event(get_thread_app())
   {

      m_operation = operation;

      m_operation->Completed = ref new ::Windows::Foundation::AsyncOperationWithProgressCompletedHandler < T, T2 >([this](::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > ^ operation, ::Windows::Foundation::AsyncStatus status)
      {

         m_status = status;

         m_event.set_event();

      });

   }


   virtual ~waiter_for_Windows_Foundation_IAsyncOperationWithProgress()
   {

   }


   T wait(unsigned int dwMillis = INFINITE, ::Windows::Foundation::AsyncStatus * pstatus = NULL)
   {

      m_event.wait(millis(dwMillis));

      if (pstatus != NULL)
         *pstatus = m_status;

      if (m_status == ::Windows::Foundation::AsyncStatus::Completed)
      {

         return m_operation->GetResults();

      }
      else
      {

         T t;

         waiter_null_result(t);

         return t;

      }

   }

};


ref class waiter_for_Windows_Foundation_IAsyncAction sealed
{
private:


   manual_reset_event                                 m_event;
   ::Windows::Foundation::IAsyncAction ^              m_action;
   ::Windows::Foundation::AsyncStatus                 m_status;

public:


   waiter_for_Windows_Foundation_IAsyncAction(::Windows::Foundation::IAsyncAction ^ action, Platform::CallbackContext callbackcontext = Platform::CallbackContext::Any) :
      m_event(get_thread_app())
   {

      m_action                = action;

      m_action->Completed     = ref new ::Windows::Foundation::AsyncActionCompletedHandler([this](::Windows::Foundation::IAsyncAction ^ action, ::Windows::Foundation::AsyncStatus status)
      {

         m_status = status;

         m_event.set_event();

      });

      if(m_action->Status != ::Windows::Foundation::AsyncStatus::Started)
      {

         m_status = m_action->Status;

         m_event.set_event();

      }

   }

   virtual ~waiter_for_Windows_Foundation_IAsyncAction()
   {

   }


   void wait(unsigned int dwMillis = INFINITE, ::Windows::Foundation::AsyncStatus * pstatus = NULL)
   {

      m_event.wait(millis(dwMillis));

      if(pstatus != NULL)
         *pstatus = m_status;

   }


};


template < typename T >
inline T wait(::Windows::Foundation::IAsyncOperation < T > ^ operation, DWORD dwMillis = INFINITE, ::Windows::Foundation::AsyncStatus * pstatus = NULL, Platform::CallbackContext callbackcontext = Platform::CallbackContext::Any)
{
   
   waiter_for_Windows_Foundation_IAsyncOperation < T > waiter(operation, callbackcontext);
      
   return waiter.wait(dwMillis, pstatus);

}


template < typename T, typename T2 >
inline T wait(::Windows::Foundation::IAsyncOperationWithProgress < T, T2 > ^ operation, DWORD dwMillis = INFINITE, ::Windows::Foundation::AsyncStatus * pstatus = NULL, Platform::CallbackContext callbackcontext = Platform::CallbackContext::Any)
{

   waiter_for_Windows_Foundation_IAsyncOperationWithProgress < T, T2 > waiter(operation, callbackcontext);

   return waiter.wait(dwMillis, pstatus);

}


inline ::Windows::Foundation::AsyncStatus wait(::Windows::Foundation::IAsyncAction ^ action,  DWORD dwMillis = INFINITE, Platform::CallbackContext callbackcontext = Platform::CallbackContext::Any)
{
   
   ::Windows::Foundation::AsyncStatus status;
   
   waiter_for_Windows_Foundation_IAsyncAction waiter(action, callbackcontext);
   
   waiter.wait(dwMillis, &status);

   return status;

}


class CLASS_DECL_AURA message_array :
   public raw_array < MESSAGE >
{
};

class CLASS_DECL_AURA mq
{
public:

   mutex                      m_mutex;
   message_array              ma;
   manual_reset_event         m_eventNewMessage;

   mq() : m_eventNewMessage(get_thread_app()) {}



};

CLASS_DECL_AURA mq * get_mq(HTHREAD h);



// Stored data for CREATE_SUSPENDED and ResumeThread.
struct PendingThreadInfo
{


   uint32_t (*       m_pfn)(void *);
   void *            m_pv;
   event *           m_peventCompletion;
   event *           m_peventSuspension;
   HTHREAD           m_hthread;
   int               m_iPriority;


   PendingThreadInfo()
   {

      m_peventSuspension = NULL;
      m_peventCompletion = NULL;

   }


};
