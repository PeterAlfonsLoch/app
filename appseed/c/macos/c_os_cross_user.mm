#import "c_mm.h"


WINBOOL IsWindowVisible(oswindow hwnd)
{
   
   return 1;
   
}


WINBOOL IsIconic(oswindow hwnd)
{
   
   [hwnd.window() miniaturize : 0];
   
   return 1;
   
   
}



WINBOOL set_nswindow_frame(oswindow hwnd, LPCRECT lpcrect, int iDisplay)
{

   NSRect rect;
   
   rect.origin.x     = lpcrect->left;
   rect.origin.y     = lpcrect->bottom;
   rect.size.width   = lpcrect->right     -     lpcrect->left;
   rect.size.height  = lpcrect->bottom    -     lpcrect->top;
   
   
   [hwnd.window() setFrame : rect display : iDisplay];
   
   return 1;
   
}



WINBOOL move_nswindow(oswindow hwnd, int x, int y)
{
   
   NSPoint point;
   
   point.x = x;
   point.y = y;
   
   [hwnd.window() setFrameTopLeftPoint : point];
   
   return 1;
   
   
}
