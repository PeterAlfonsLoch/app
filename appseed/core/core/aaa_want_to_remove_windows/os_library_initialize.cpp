#include "framework.h"
#include <stdarg.h>
#include "sal.h"



extern "C" int32_t WINAPI RawDllMain(HINSTANCE, uint32_t dwReason, LPVOID);
extern "C" int32_t (WINAPI * const _pRawDllMain)(HINSTANCE , uint32_t , LPVOID) = &RawDllMain;

extern "C"
int32_t WINAPI RawDllMain(HINSTANCE hInstance, uint32_t dwReason, LPVOID)
{
   hInstance;
   try
   {
      if (dwReason == DLL_PROCESS_ATTACH)
      {

#ifdef WINDOWSEX
         
         SetErrorMode(SetErrorMode(0) | SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);

#endif

         // add a reference to thread local storage data
//         __tls_add_ref();

#ifdef WINDOWSEX
         
         // make sure we have enough primitive::memory to attempt to start (8kb)
         void * pMinHeap = LocalAlloc(NONZEROLPTR, 0x2000);
         if (pMinHeap == NULL)
            return FALSE;   // fail if primitive::memory alloc fails
         LocalFree(pMinHeap);

#endif

         // cause early initialization of gen_CriticalSection
//         if (!::core::CriticalInit())
  //          return FALSE;

      }
      else if (dwReason == DLL_PROCESS_DETACH)
      {

         // free up the gen_CriticalSection
//         ::core::CriticalTerm();

         // remove reference from thread local data
//         __tls_release();
      }
   }
   catch( ::exception::base* e )
   {
      e->Delete();
      return FALSE;
   }
   
   return TRUE;    // ok
}


BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   if (dwReason == DLL_PROCESS_ATTACH)
   {
      g_bExiting = false;
      //use_base_ca2_allocator();


   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
   }
   else if (dwReason == DLL_THREAD_DETACH)
   {
//      initialize_primitive_heap();
//      __term_thread();
   }

   return TRUE;    // ok
}



