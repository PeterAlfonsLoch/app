#include "framework.h"
#include <sys/time.h>


DWORD get_tick_count()
{
   timeval ts;
   gettimeofday(&ts,0);
   return (ts.tv_sec * 1000 + (ts.tv_usec / 1000)) % 0xffffffffu;

}

vsstring g_strCommandLine;
wstring g_wstrCommandLine;


void SetCommandLineA(const char * psz)
{

   g_strCommandLine     = psz;
   g_wstrCommandLine    = psz;

}

void SetCommandLineW(const wchar_t * pwsz)
{

   g_strCommandLine     = pwsz;
   g_wstrCommandLine    = pwsz;

}


LPSTR GetCommandLineA()
{

   return (LPSTR) (LPCSTR) g_strCommandLine;

}

LPWSTR GetCommandLineW()
{

   return (LPWSTR) (LPCWSTR) g_wstrCommandLine;

}


/*
struct thread_struct
{
   LPTHREAD_START_ROUTINE lpStartAddress;
   LPVOID lpParameter;

};

void * my_thread_proc(void * p)
{

   thread_struct * pst = (thread_struct *) p;

   DWORD dw = pst->lpStartAddress(pst->lpParameter);

   delete pst;

   return (void *) dw;

}


HANDLE
WINAPI
CreateThread(
             LPSECURITY_ATTRIBUTES lpThreadAttributes,
             SIZE_T dwStackSize,
             LPTHREAD_START_ROUTINE lpStartAddress,
             LPVOID lpParameter,
             DWORD dwCreationFlags,
             LPDWORD lpThreadId
             )
{

   HANDLE h = new win_handle;

   h->m_etype = win_handle::type_thread;

   thread_struct * pst = new thread_struct;

   pst->lpStartAddress = lpStartAddress;
   pst->lpParameter = lpParameter;

   pthread_create(&h->m_thread.m_thread, NULL, &my_thread_proc, (void *) pst);


   return h;

}


WINBOOL
WINAPI
__win_CloseThread(
                HANDLE hThread
                )
{
   if(hThread == INVALID_HANDLE_VALUE)
      return FALSE;
   if(hThread->m_etype != win_handle::type_thread)
      return FALSE;
   return TRUE;
}





*/


void output_debug_string(const char * psz)
{

   OutputDebugString(psz);

}


