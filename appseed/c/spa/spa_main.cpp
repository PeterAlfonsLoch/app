#include "framework.h"




CLASS_DECL_c int32_t spalib_main(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR    lpCmdLine,
                     int32_t       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
   spa::installer installer;
   installer.m_hinstance = hInstance;
   installer.m_nCmdShow = nCmdShow;
   return installer.spaadmin_main(lpCmdLine);
}



