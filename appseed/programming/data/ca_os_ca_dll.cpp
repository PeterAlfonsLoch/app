#include "StdAfx.h"


extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   // remove this if you use lpReserved
   UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      ::OutputDebugString("::ca2:: data.dll :: initializing!\n");

#ifndef METROWIN
      /* initialize client library */
      if(mysql_library_init(0,NULL,NULL))
      {
         TRACE("mysql_library_init() failed\n");
         return false;
      }
#endif

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
#ifndef METROWIN
      try
      {
         mysql_library_end();
      }
      catch(...)
      {
      }
#endif

      ::OutputDebugString("::ca2:: data.dll :: terminating!\n");
   }
   return 1;   // ok
}


