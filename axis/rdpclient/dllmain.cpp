
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <freerdp/client.h>

#include <freerdp/addin.h>
#include <freerdp/assistance.h>
#include <freerdp/client/file.h>
#include <freerdp/client/cmdline.h>
#include <freerdp/client/channels.h>



extern "C" int APIENTRY
DllMain(HINSTANCE hInstance,UINT dwReason,LPVOID lpReserved)
{


   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);


   if(dwReason == DLL_PROCESS_ATTACH)
   {
      //freerdp_channels_global_init();



      ::OutputDebugString("::ca2:: axisrdpclient.dll :: initializing!\n");


   }
   else if(dwReason == DLL_PROCESS_DETACH)
   {

      //freerdp_channels_global_uninit();

      ::OutputDebugString("::ca2:: axisrdpclient.dll :: terminating!\n");


   }


   return 1;   // ok


}


