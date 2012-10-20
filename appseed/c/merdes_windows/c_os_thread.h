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

template < typename T >
class CLASS_DECL_c m_wait
{
public:

   T ^ m_result;

   m_wait(Windows::Foundation::IAsyncOperation <  T ^ > ^ op)
   {
      m_result = nullptr;
      simple_event ev;
      op->Completed = ([this](Windows::Foundation::IAsyncOperation < ::Windows::Storage::StorageFolder ^ > ^ op, Windows::Foundation::AsyncStatus status))
      {
         if(status == Windows::Foundation::AsyncStatus::Completed)
         {
            m_result = op->GetResults();
         }
         ev.set_event();
      };
      ev.wait();
   }


   operator T ^ () { return m_result; }

};

