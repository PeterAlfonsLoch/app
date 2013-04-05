#include "framework.h"


BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
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

