#import "ca_mm.h"


bool oswindow_data::is_window_visible()
{
   
   return 1;
   
}


bool oswindow_data::is_iconic()
{
   
   [window() miniaturize : 0];
   
   return 1;
   
   
}


bool oswindow_data::show_window(int32_t nCmdShow)
{

   [m_nswindow orderFrontRegardless];
   return 1;
   
}



WINBOOL set_nswindow_frame(oswindow hwnd, LPCRECT lpcrect, int iDisplay)
{

   NSRect rect;
   
   rect.origin.x     = lpcrect->left;
   rect.origin.y     = lpcrect->top;
   rect.size.width   = lpcrect->right     -     lpcrect->left;
   rect.size.height  = lpcrect->bottom    -     lpcrect->top;
   
   
   [hwnd->window() setFrame : rect display : iDisplay];
   
   return 1;
   
}



WINBOOL move_nswindow(oswindow hwnd, int x, int y)
{
   
   NSPoint point;
   
   point.x = x;
   point.y = y;
   
   [hwnd->window() setFrameTopLeftPoint : point];
   
   return 1;
   
   
}


CLASS_DECL_THREAD NSAutoreleasePool * g_ns_pool = NULL;




NSAutoreleasePool * new_ns_pool()
{
 
   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

   return pool;

}


void release_pool(NSAutoreleasePool * pool)
{
   
   [pool release];
   
}

void on_start_thread()
{
   
   g_ns_pool = new_ns_pool();
   
}


void on_end_thread()
{
   
   release_pool(g_ns_pool);
   
   g_ns_pool = NULL;
   
}


void ns_redraw_window(oswindow w)
{
   
   [w->window() display];
   
}