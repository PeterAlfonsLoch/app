

#include <Cocoa/Cocoa.h>
#include "c_os_cross_win_user_internal.h"

int IsWindowVisible(HWND hwnd)
{
}


int IsIconic(HWND hwnd)
{
   [(NSWindow * ) hwnd->m_pnswindow miniaturize];
   return TRUE;
   
   
}