#include "StdAfx.h"
#include "ca2/radix/cafxdllx.h"


OSVERSIONINFO g_versionInformation;

static AFX_EXTENSION_MODULE MPLiteDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   // remove this if you use lpReserved
   UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      ::OutputDebugString("::ca2:: app_alatel.dll :: initializing!\n");
      
      // Extension DLL one-time initialization
      if (!AfxInitExtensionModule(MPLiteDLL, hInstance))
         return 0;

      // Insert this DLL into the resource chain
      // NOTE: If this Extension DLL is being implicitly linked to by
      //  an ca2 API Regular DLL (such as an ActiveX control)
      //  instead of an ca2 API application, then you will want to
      //  remove this line from DllMain and put it in a separate
      //  function exported from this Extension DLL.  The Regular DLL
      //  that uses this Extension DLL should then explicitly call that
      //  function to initialize this Extension DLL.  Otherwise,
      //  the CDynLinkLibrary object will not be attached to the
      //  Regular DLL's resource chain, and serious problems will
      //  result.

      new CDynLinkLibrary(MPLiteDLL);

   g_versionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
   GetVersionEx(&g_versionInformation);

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
      ::OutputDebugString("::ca2:: app_alatel.dll :: terminating!\n");
      // Terminate the library before destructors are called
      AfxTermExtensionModule(MPLiteDLL);
   }
   return 1;   // ok
}


