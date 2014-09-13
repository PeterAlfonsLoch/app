//
//  macos_MessageBoxA.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 13/09/14.
//  from http://blog.jorgearimany.com/2010/05/messagebox-from-windows-to-mac.html
//  El blog de Jorge Arimany Españaque

#include "framework.h"
//int32_t
//WINAPI
//MessageBoxW(
  //          oswindow hWnd,
    //        LPCWSTR lpText,
      //      LPCWSTR lpcaption,
        //    UINT uType);




#define IDOK       1
#define IDCANCEL   2
int MessageBoxA(oswindow window, const char * pszMessage, const char * pszHeader, UINT uType )
{
   //convert the strings from char* to CFStringRef
   CFStringRef header_ref      = CFStringCreateWithCString( NULL, pszHeader,     strlen(pszHeader)    );
   CFStringRef message_ref  = CFStringCreateWithCString( NULL, pszMessage,  strlen(pszMessage) );
   
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
