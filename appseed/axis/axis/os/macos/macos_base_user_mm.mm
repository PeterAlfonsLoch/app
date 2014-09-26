//
//  macos_user.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#import "framework.h"
#import "macos_windowing.h"


WINBOOL get_nswindow_rect(oswindow oswindow, LPRECT lprect);
void copy(LPRECT lprectDst, const CGRect & rectSrc);


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

   if(nCmdShow == SW_HIDE)
   {

      [m_nswindow orderOut : nil];
      
   }
   else
   {
   
      [m_nswindow makeKeyAndOrderFront : nil];
      
      [m_nswindow display];
      
   }
   
   return 1;
   
}


bool oswindow_data::client_to_screen(POINT *lppoint)
{
   RECT rect;
   get_nswindow_rect(this, &rect);
   lppoint->x += rect.left;
   lppoint->y += rect.top;
   return true;
}

bool oswindow_data::screen_to_client(POINT *lppoint)
{
   RECT rect;
   get_nswindow_rect(this, &rect);
   lppoint->x -= rect.left;
   lppoint->y -= rect.top;
   return true;
}



WINBOOL set_nswindow_frame(oswindow hwnd, LPCRECT lpcrect, int iDisplay)
{
   
   NSRect rect;
   
   NSRect frame = [[NSScreen mainScreen] frame];
   
   rect.origin.x     = lpcrect->left;
   rect.origin.y     = frame.size.height  -     lpcrect->bottom;
   rect.size.width   = lpcrect->right     -     lpcrect->left;
   rect.size.height  = lpcrect->bottom    -     lpcrect->top;
   
   //   rect.origin.x     = 500;
   //   rect.origin.y     = 400;
   //   rect.size.width   = 500;
   //   rect.size.height  = 500;
   
   
   [hwnd->window() setFrame : rect display : iDisplay];
   
   return 1;
   
}



WINBOOL move_nswindow(oswindow hwnd, int x, int y)
{
   
//   RECT rect;
   
//   get_nswindow_rect(hwnd, &rect);
   
   NSPoint point;
   
   point.x = x;
   point.y = [[NSScreen mainScreen] frame].size.height - y;
   
   [hwnd->window() setFrameTopLeftPoint : point];
   
   return 1;
   
   
}


WINBOOL make_key_and_order_front_nswindow(oswindow hwnd)
{
   
   [[hwnd->window() dd_invokeOnMainThreadAndWaitUntilDone:FALSE] makeKeyAndOrderFront: nil];
   
   return 1;
   
   
}


WINBOOL order_front_nswindow(oswindow hwnd)
{
   
   [[hwnd->window() dd_invokeOnMainThreadAndWaitUntilDone:FALSE] orderFront: nil];
   
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


WINBOOL get_nswindow_rect(oswindow oswindow, LPRECT lprect)
{
   
   NSRect rect = [oswindow->window() frame];
   
   lprect->left        = rect.origin.x;
   lprect->bottom      = [[NSScreen mainScreen] frame ].size.height - rect.origin.y;
   lprect->right       = rect.origin.x  + rect.size.width;
   lprect->top         = lprect->bottom - rect.size.height;
   
   return 1;
   
}


namespace macos
{

   CGFloat get_system_main_menu_bar_height()
   {
      return [[[NSApplication sharedApplication] mainMenu] menuBarHeight];
   }

   CGFloat get_system_dock_height()
   {
      return [[[NSApplication sharedApplication] mainMenu] menuBarHeight];
   }

} // namespace macos





 void window_copy(NSRect & rect, LPCRECT lpcrect)
 {
 
    rect.origin.x       = lpcrect->left;
    rect.origin.y       = [[NSScreen mainScreen] frame].size.height - lpcrect->bottom;
    rect.size.width     = lpcrect->right - lpcrect->left;
    rect.size.height    = lpcrect->bottom - lpcrect->top;
 
 }
 
 void window_copy(LPRECT lprect, const NSRect & rectSrc)
 {
 
    lprect->left        = rectSrc.origin.x;
    lprect->bottom      = [[NSScreen mainScreen] frame].size.height - rectSrc.origin.y;
    lprect->right       = lprect->left + rectSrc.size.width;
    lprect->top         = lprect->bottom - rectSrc.size.height;
 
 }


int GetMainScreenRect(LPRECT lprect)
{
   
   window_copy(lprect, [[NSScreen mainScreen] frame]);
   
   return 0;
   
}

int GetScreenRect(LPRECT lprect, int iMonitor)
{
   
   window_copy(lprect, [[[NSScreen screens] objectAtIndex:iMonitor ] frame]);
   
   return iMonitor;
   
}


int GetScreenCount()
{
   
   return [[NSScreen screens] count];
   
}



int GetWkspaceRect(LPRECT lprect, int iMonitor)
{
   
   window_copy(lprect, [[[NSScreen screens] objectAtIndex:iMonitor ] visibleFrame]);
   
   return iMonitor;
   
}


int GetWkspaceCount()
{
   
   return [[NSScreen screens] count];
   
}
