#import "c_mm.h"


bool oswindow::is_window_visible()
{
   
   return 1;
   
}


bool oswindow::is_iconic()
{
   
   [window() miniaturize : 0];
   
   return 1;
   
   
}


bool oswindow::show_window(int32_t nCmdShow)
{

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
