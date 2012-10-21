#pragma once


/*
CLASS_DECL_c _Use_decl_annotations_ HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES unusedThreadAttributes, SIZE_T unusedStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD unusedThreadId);
CLASS_DECL_c _Use_decl_annotations_ DWORD WINAPI ResumeThread(HANDLE hThread);
CLASS_DECL_c _Use_decl_annotations_ BOOL WINAPI SetThreadPriority(HANDLE hThread, int nPriority);
CLASS_DECL_c _Use_decl_annotations_ VOID WINAPI Sleep(DWORD dwMilliseconds);
CLASS_DECL_c DWORD WINAPI TlsAlloc();
CLASS_DECL_c _Use_decl_annotations_ BOOL WINAPI TlsFree(DWORD dwTlsIndex);
CLASS_DECL_c _Use_decl_annotations_ LPVOID WINAPI TlsGetValue(DWORD dwTlsIndex);
CLASS_DECL_c _Use_decl_annotations_ BOOL WINAPI TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue);
CLASS_DECL_c void WINAPI TlsShutdown();
CLASS_DECL_c int WINAPI GetThreadPriority(_In_ HANDLE hThread);
*/

/*template < typename T >
class m_waiter
{
   simple_event ev;
   T op;
   m_waiter(T op)
   {
      this->op = op;
      op->Completed = new ::Windows::Foundation::AsyncOperationCompletedHandler(this, &m_waiter::cOMPLETed);
   }
   
   
   void cOMPLETed(T op, ::Windows::Foundation::AsyncStatus st)
   {
      if(st == Windows::Foundation::AsyncStatus::Completed)
      {
         mer = op->GetResults();
      }
      ev.set_event();
   }

   auto wait()
   {
      ev.lock();
      return op->GetResults();
   }

};
*/

template < typename T >
ref class waiter_for_Windows_Foundation_IAsyncOperation sealed
{
private:

   simple_event                                       m_event;
   ::Windows::Foundation::IAsyncOperation < T > ^     m_operation;
   ::Windows::Foundation::AsyncStatus                 m_status;
   T                                                  m_result;


public:


   waiter_for_Windows_Foundation_IAsyncOperation(::Windows::Foundation::IAsyncOperation < T > ^ operation, Platform::CallbackContext callbackcontext = Platform::CallbackContext::Any)
   {

      m_operation             = operation;

      m_operation->Completed  = ref new ::Windows::Foundation::AsyncOperationCompletedHandler < T > (this, &waiter_for_Windows_Foundation_IAsyncOperation < T > ::Completed, callbackcontext);

   }


   virtual ~waiter_for_Windows_Foundation_IAsyncOperation()
   {

   }
   
   
   void Completed(::Windows::Foundation::IAsyncOperation < T > ^ operation, ::Windows::Foundation::AsyncStatus status)
   {

      m_status = status;

      m_event.set_event();

   }

   T wait()
   {

      m_event.wait();


      if(m_status != ::Windows::Foundation::AsyncStatus::Completed)
      {

         throw "error waiting";

      }

      return m_operation->GetResults();

   }

};


ref class waiter_for_Windows_Foundation_IAsyncAction sealed
{
private:


   simple_event                                       m_event;
   ::Windows::Foundation::IAsyncAction ^              m_action;
   ::Windows::Foundation::AsyncStatus                 m_status;

public:


   waiter_for_Windows_Foundation_IAsyncAction(::Windows::Foundation::IAsyncAction ^ action, Platform::CallbackContext callbackcontext = Platform::CallbackContext::Any)
   {

      m_action                = action;

      m_action->Completed     = ref new ::Windows::Foundation::AsyncActionCompletedHandler(this, &waiter_for_Windows_Foundation_IAsyncAction::Completed, callbackcontext);

   }

   virtual ~waiter_for_Windows_Foundation_IAsyncAction()
   {

   }

   void Completed(::Windows::Foundation::IAsyncAction ^ action, ::Windows::Foundation::AsyncStatus status)
   {

      m_status = status;

      m_event.set_event();

   }


   void wait()
   {

      m_event.wait();

      if(m_status != ::Windows::Foundation::AsyncStatus::Completed)
      {

         throw "error waiting";

      }

      return m_action->GetResults();

   }


};


template < typename T >
inline T wait(::Windows::Foundation::IAsyncOperation < T > ^ operation, Platform::CallbackContext callbackcontext = Platform::CallbackContext::Any)
{
   
   return waiter_for_Windows_Foundation_IAsyncOperation < T > (operation, callbackcontext).wait();

}


inline  void wait(::Windows::Foundation::IAsyncAction ^ action, Platform::CallbackContext callbackcontext = Platform::CallbackContext::Any)
{

   return waiter_for_Windows_Foundation_IAsyncAction(action, callbackcontext).wait();

}
