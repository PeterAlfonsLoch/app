#include "framework.h"


extern "C" int WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)
{

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      
      ::OutputDebugString("ca2.dll Initializing");

   }
   else if (dwReason == DLL_THREAD_DETACH)
   {

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      ::OutputDebugString("ca2.dll Terminating");

   }

   return TRUE;

}

