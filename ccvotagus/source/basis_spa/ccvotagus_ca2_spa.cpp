#include "StdAfx.h"

bool g_bAdmin = false;
e_version g_eversion = version_basis;


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
   return spalib_main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}