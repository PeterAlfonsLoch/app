#include "install_spaboot.h"

int spaboot_start();

extern "C" int WinMainCRTStartup()
{
   
   initialize_heap();

   initialize_http_dup();

   LPSTR lpsz = ::GetCommandLineA();

   int iRet = 0;

   if(stristr_dup(lpsz, "-install_spaboot"))
   {
      iRet = install_spaboot();
   }
   else if(stristr_dup(lpsz, "-install_npca2plugin"))
   {
      iRet = install_npca2plugin();
   }
   else
   {
      iRet = spaboot_start();
   }


   finalize_heap();

   ::ExitProcess(iRet);

   return iRet;

}
