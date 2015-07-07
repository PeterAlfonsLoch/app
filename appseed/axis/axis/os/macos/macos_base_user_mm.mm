//
//  macos_user.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#import "framework.h"
//#import "macos_windowing.h"


void copy(LPRECT lprectDst, const CGRect & rectSrc);



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


