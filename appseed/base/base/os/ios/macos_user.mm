//
//  macos_user.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#import "framework.h"


WINBOOL get_nswindow_rect(oswindow oswindow, LPRECT lprect);


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


