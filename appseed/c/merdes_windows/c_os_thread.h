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
class m_waiter
{
   simple_event ev;
   ::Windows::Foundation::IAsyncOperation < T ^ > ^ op;
   m_waiter(::Windows::Foundation::IAsyncOperation < T ^ > ^ op)
   {
      this->op = op;
      op->Completed = new ::Windows::Foundation::AsyncOperationCompletedHandler(this, &m_waiter::cOMPLETed);
   }
   
   
   void cOMPLETed(::Windows::Foundation::IAsyncOperation < T ^ > ^ op, ::Windows::Foundation::AsyncStatus st)
   {
      if(st == Windows::Foundation::AsyncStatus::Completed)
      {
         mer = op->GetResults();
      }
      ev.set_event();
   }

   T ^ wait()
   {
      ev.lock();
      return op->GetResults();
   }

};


/*template < typename T >
auto m_wait(T op)
{
   return m_waiter < T > (op).wait();
};*/

template < typename T >
T ^ m_wait(::Windows::Foundation::IAsyncOperation < T ^ > ^ op)
{
   return m_waiter < T > (op).wait();
};
