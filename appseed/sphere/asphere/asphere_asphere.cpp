#include "framework.h"


extern "C" int32_t WINAPI DllMain(HINSTANCE hInstance, uint32_t dwReason, LPVOID)
{

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      
      ::OutputDebugString("ca.dll Initializing");

   }
   else if (dwReason == DLL_THREAD_DETACH)
   {

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      ::OutputDebugString("ca.dll Terminating");

   }

   return TRUE;

}

