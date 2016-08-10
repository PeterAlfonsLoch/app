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


CGRect g_rectWorkspace;


void osx_init_workspace_rect()
{
   
   g_rectWorkspace = [[NSScreen mainScreen] frame];
   
}


CGRect osx_get_workspace_rect()
{
   
   return g_rectWorkspace;
   
}


 bool window_copy(NSRect & rect, LPCRECT lpcrect)
 {
    
    CGRect rectWorkspace = osx_get_workspace_rect();
    
    rect.origin.x       = lpcrect->left;
    rect.origin.y       = rectWorkspace.size.height - lpcrect->bottom;
    rect.size.width     = lpcrect->right - lpcrect->left;
    rect.size.height    = lpcrect->bottom - lpcrect->top;
    
    return true;
 
 }
 
 bool window_copy(LPRECT lprect, const NSRect & rectSrc)
 {
    
    CGRect rectWorkspace = osx_get_workspace_rect();
    
    lprect->left        = rectSrc.origin.x;
    lprect->bottom      = rectWorkspace.size.height - rectSrc.origin.y;
    lprect->right       = lprect->left + rectSrc.size.width;
    lprect->top         = lprect->bottom - rectSrc.size.height;
    
    return true;
 
 }


int GetMainScreenRect(LPRECT lprect)
{
   
   window_copy(lprect, [[NSScreen mainScreen] frame]);
   
   return 0;
   
}

int GetScreenRect(LPRECT lprect, int iMonitor)
{
   
   if([NSScreen screens] == nil)
   {
      
      return -1;
      
   }
   
   if(iMonitor >= [NSScreen screens].count)
   {
      
      return -1;
      
   }
   
   try
   {
      
      window_copy(lprect, [[[NSScreen screens] objectAtIndex:iMonitor ] frame]);
      
   }
   catch (...)
   {
      
      return -1;
      
   }
                   
   
   
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


