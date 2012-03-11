#include "StdAfx.h"
#include <stdarg.h>
#include "sal.h"




extern "C" BOOL WINAPI RawDllMain(HINSTANCE, DWORD dwReason, LPVOID);
extern "C" BOOL (WINAPI * const _pRawDllMain)(HINSTANCE , DWORD , LPVOID) = &RawDllMain;

extern "C"
BOOL WINAPI RawDllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)
{
   hInstance;
   try
   {
      if (dwReason == DLL_PROCESS_ATTACH)
      {
         SetErrorMode(SetErrorMode(0) |
            SEM_FAILCRITICALERRORS|SEM_NOOPENFILEERRORBOX);

         // add a reference to thread local storage data
//         AfxTlsAddRef();

         // make sure we have enough primitive::memory to attempt to start (8kb)
         void * pMinHeap = LocalAlloc(NONZEROLPTR, 0x2000);
         if (pMinHeap == NULL)
            return FALSE;   // fail if primitive::memory alloc fails
         LocalFree(pMinHeap);

         // cause early initialization of _afxCriticalSection
//         if (!AfxCriticalInit())
  //          return FALSE;

      }
      else if (dwReason == DLL_PROCESS_DETACH)
      {

         // free up the _afxCriticalSection
//         AfxCriticalTerm();

         // remove reference from thread local data
//         AfxTlsRelease();
      }
   }
   catch( base_exception* e )
   {
      e->Delete();
      return FALSE;
   }
   
   return TRUE;    // ok
}

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)
{
   if (dwReason == DLL_PROCESS_ATTACH)
   {

      use_base_ca2_allocator();


   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
   }
   else if (dwReason == DLL_THREAD_DETACH)
   {
//      AfxTermThread();
   }

   return TRUE;    // ok
}

