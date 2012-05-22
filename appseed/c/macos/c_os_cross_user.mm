#include "c_os_internal.h"
#include <Cocoa/Cocoa.h>


WINBOOL IsWindowVisible(HWND hwnd)
{
   
   return 1;
   
}


WINBOOL IsIconic(HWND hwnd)
{
   
   [((NSWindow * ) hwnd->m_pnswindow) miniaturize : 0];
   
   return 1;
   
   
}



WINBOOL set_nswindow_frame(HWND hwnd, LPCRECT lpcrect, int iDisplay)
{

   NSRect rect;
   
   rect.origin.x     = lpcrect->left;
   rect.origin.y     = lpcrect->bottom;
   rect.size.width   = lpcrect->right     -     lpcrect->left;
   rect.size.height  = lpcrect->bottom    -     lpcrect->top;
   
   
   [((NSWindow * ) hwnd->m_pnswindow) setFrame : rect display : iDisplay];
   
   return 1;
   
}



WINBOOL move_nswindow(HWND hwnd, int x, int y)
{
   
   NSPoint point;
   
   point.x = x;
   point.y = y;
   
   [((NSWindow * ) hwnd->m_pnswindow) setFrameTopLeftPoint : point];
   
   return 1;
   
   
}
