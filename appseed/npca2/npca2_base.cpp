#include "npca2.h"



HANDLE g_hinstancePluginbase = NULL; 



int npca2_dll_main(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
	if(dwReason == DLL_PROCESS_ATTACH)
	{
      //MessageBox(NULL, "boxmain", "box", MB_OK);
      //Sleep(15 * 1000);
      initialize_primitive_heap();

      g_hinstancePluginbase = hinstance;

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
      finalize_primitive_heap();
	}
	return 1;   // ok
}



extern "C" int APIENTRY _DllMainCRTStartup(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
   return npca2_dll_main(hinstance, dwReason, lpReserved);
}


