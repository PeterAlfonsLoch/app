#include "framework.h"

string & get_command_line_string()
{
   static string g_strCommandLine;
   return g_strCommandLine;
}

wstring & get_command_line_wstring()
{
   static wstring g_wstrCommandLine;
   return g_wstrCommandLine;
}


void SetCommandLineA(const char * psz)
{

   get_command_line_string()     = psz;
   get_command_line_wstring()    = psz;

}

void SetCommandLineW(const wchar_t * pwsz)
{

   get_command_line_string()     = pwsz;
      get_command_line_wstring()     = pwsz;

}


LPSTR GetCommandLineA()
{

   return (LPSTR) (LPCSTR) get_command_line_string();

}

LPWSTR GetCommandLineW()
{

   return (LPWSTR) (LPCWSTR)    get_command_line_wstring() ;

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


