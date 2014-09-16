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




int MessageBoxA(oswindow window, const char * pszMessage, const char * pszHeader, UINT uType )
{
   //convert the strings from char* to CFStringRef
   CFStringRef header_ref      = CFStringCreateWithCString( NULL, pszHeader,     strlen(pszHeader)    );
   CFStringRef message_ref  = CFStringCreateWithCString( NULL, pszMessage,  strlen(pszMessage) );
   
   CFOptionFlags result;  //result code from the message box
   
   uint32_t uiType = uType & MB_TYPEMASK;
   
   string strButton1;
   string strButton2;
   string strButton3;
   
   switch(uiType)
   {
      case MB_OKCANCEL:
         strButton1 = "OK";
         strButton2 = "Cancel";
         break;
      case MB_ABORTRETRYIGNORE:
         strButton1 = "Abort";
         strButton2 = "Retry";
         strButton3 = "Ignore";
         break;
      case MB_YESNOCANCEL:
         strButton1 = "Yes";
         strButton2 = "No";
         strButton3 = "Cancel";
         break;
      case MB_YESNO:
         strButton1 = "Yes";
         strButton2 = "No";
         break;
      case MB_RETRYCANCEL:
         strButton1 = "Retry";
         strButton2 = "Cancel";
         break;
      case MB_CANCELTRYCONTINUE:
         strButton1 = "Cancel";
         strButton2 = "Try";
         strButton3 = "Continue";
         break;
      default:
         strButton1 = "OK";
         break;
   }
   
   CFStringRef button1_ref = NULL;
   CFStringRef button2_ref = NULL;
   CFStringRef button3_ref = NULL;
   
   if(strButton1.has_char() || strButton1.CompareNoCase("ok") != 0)
      button1_ref = CFStringCreateWithCString(NULL, strButton1, strButton1.length());
   if(strButton2.has_char())
      button2_ref = CFStringCreateWithCString(NULL, strButton2, strButton2.length());
   if(strButton3.has_char())
      button3_ref = CFStringCreateWithCString(NULL, strButton3, strButton3.length());
   
   
   //launch the message box
   CFUserNotificationDisplayAlert(
                                  0, // no timeout
                                  kCFUserNotificationNoteAlertLevel, //change it depending message_type flags ( MB_ICONASTERISK.... etc.)
                                  NULL, //icon url, use default, you can change it depending message_type flags
                                  NULL, //not used
                                  NULL, //localization of strings
                                  header_ref, //header text
                                  message_ref, //message text
                                  button1_ref, //default "ok" text in button
                                  button2_ref, //alternate button title
                                  button3_ref, //other button title, null--> no other button
                                  &result //response flags
                                  );
   
   if(button1_ref != NULL)
      CFRelease(button1_ref);
   if(button2_ref != NULL)
      CFRelease(button1_ref);
   if(button3_ref != NULL)
      CFRelease(button1_ref);
   
   //Clean up the strings
   CFRelease( header_ref );
   CFRelease( message_ref );
   
   
   switch(uiType)
   {
      case MB_OKCANCEL:
         if( result == kCFUserNotificationDefaultResponse)
            return IDOK;
         else if( result == kCFUserNotificationAlternateResponse)
            return IDCANCEL;
         break;
      case MB_ABORTRETRYIGNORE:
         if( result == kCFUserNotificationDefaultResponse)
            return IDABORT;
         else if(result == kCFUserNotificationAlternateResponse)
            return IDRETRY;
         else if(result == kCFUserNotificationOtherResponse)
            return IDIGNORE;
         break;
      case MB_YESNOCANCEL:
         if( result == kCFUserNotificationDefaultResponse)
            return IDYES;
         else if(result == kCFUserNotificationAlternateResponse)
            return IDNO;
         else if(result == kCFUserNotificationOtherResponse)
            return IDCANCEL;
         break;
      case MB_YESNO:
         if( result == kCFUserNotificationDefaultResponse)
            return IDYES;
         else if(result == kCFUserNotificationAlternateResponse)
            return IDNO;
         break;
      case MB_RETRYCANCEL:
         if( result == kCFUserNotificationDefaultResponse)
            return IDRETRY;
         else if(result == kCFUserNotificationAlternateResponse)
            return IDCANCEL;
         break;
      case MB_CANCELTRYCONTINUE:
         if( result == kCFUserNotificationDefaultResponse)
            return IDCANCEL;
         else if(result == kCFUserNotificationAlternateResponse)
            return IDTRYAGAIN;
         else if(result == kCFUserNotificationOtherResponse)
            return IDCONTINUE;
         break;
      default:
         if( result == kCFUserNotificationDefaultResponse)
            return IDOK;
         break;
   }
   
   
   return IDCANCEL;
   
   
}
