

#include "StdAfx.h"
#include "c_os_cross_win_user_internal.h"
#include <Cocoa/Cocoa.h>

BOOL IsWindowVisible(HWND hwnd)
{
}


BOOL IsIconic(HWND hwnd)
{
   [(NSWindow * ) hwnd->m_pnswindow miniaturize];
   return TRUE;
   
   
}