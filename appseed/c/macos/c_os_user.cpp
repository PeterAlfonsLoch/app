//
//  c_os_cross_win_user.cpp
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "framework.h"
#include "c_os_internal.h"


#ifdef DEBUG
#undef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>

#if DEBUG
#undef DEBUG
#define DEBUG
#else
#undef DEBUG
#endif


WINBOOL SetWindowPos(HWND hwnd, HWND hwndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
   
//   int   value_mask = 0;
   bool  bMove = !(uFlags & SWP_NOMOVE);
   bool  bSize = !(uFlags & SWP_NOSIZE);
   
   if(bMove && bSize)
   {
      
      RECT rect;
      
      rect.left      = x;
      rect.top       = y;
      rect.right     = rect.left + cx;
      rect.bottom    = rect.top + cy;
      
      set_nswindow_frame(hwnd, &rect, (uFlags & SWP_SHOWWINDOW));
      
   }
   else if(bSize) // bSize only
   {
      
      RECT rect;
      
      GetWindowRect(hwnd, &rect);

      rect.right     = rect.left + cx;
      rect.bottom    = rect.top + cy;
      
      set_nswindow_frame(hwnd, &rect, (uFlags & SWP_SHOWWINDOW));
      
   }
   else if(bMove) // bMove only
   {
      
      move_nswindow(hwnd, x, y);
      
   }
   
   /*   if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter >= 0)
    {
    value_mask |= CWSibling;
    values.sibling = hwndInsertAfter;
    values.stack_mode = Above;
    }
    
    XConfigureWindow(display, hwnd, value_mask, &values);
    
    if(uFlags & SWP_SHOWWINDOW)
    {
    XMapWindow(display, hwnd);
    }
    
    if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter < 0)
    {
    if(hwndInsertAfter == ZORDER_TOP || hwndInsertAfter == ZORDER_TOPMOST)
    {
    XRaiseWindow(display, hwnd);
    }
    else if(hwndInsertAfter == ZORDER_BOTTOM)
    {
    XLowerWindow(display, hwnd);
    }
    
    }
    
    XCloseDisplay(display);*/
   
   return 1;
   
}




int MessageBoxA(HWND hwnd, const char* header, const char* message, unsigned int message_type )
{
   //convert the strings from char* to CFStringRef
   CFStringRef header_ref      = CFStringCreateWithCString( NULL, header, (int)    strlen(header)    );
   CFStringRef message_ref  = CFStringCreateWithCString( NULL, message, (int) strlen(message) );
   
   CFOptionFlags result;  //result code from the message box
   
   //launch the message box
   CFUserNotificationDisplayAlert(
                                  0, // no timeout
                                  kCFUserNotificationNoteAlertLevel, //change it depending message_type flags ( MB_ICONASTERISK.... etc.)
                                  NULL, //icon url, use default, you can change it depending message_type flags
                                  NULL, //not used
                                  NULL, //localization of strings
                                  header_ref, //header text 
                                  message_ref, //message text
                                  NULL, //default "ok" text in button
                                  CFSTR("Cancel"), //alternate button title
                                  NULL, //other button title, null--> no other button
                                  &result //response flags
                                  );
   
   //Clean up the strings
   CFRelease( header_ref );
   CFRelease( message_ref );
   
   //Convert the result
   if( result == kCFUserNotificationDefaultResponse )
      return IDOK;
   else
      return IDCANCEL;
   
}


WINBOOL RedrawWindow(HWND hWnd, CONST RECT *lprcUpdate, HRGN hrgnUpdate, UINT flags)
{
   
   return TRUE;
   
}



