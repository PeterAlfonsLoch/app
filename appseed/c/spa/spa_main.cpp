#include "framework.h"




CLASS_DECL_c int spalib_main(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
   spa::installer installer;
   installer.m_hinstance = hInstance;
   installer.m_nCmdShow = nCmdShow;
   return installer.spaadmin_main(lpCmdLine);
}



