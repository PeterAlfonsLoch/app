//
//  MessageBoxA_W.m
//  aura
//
//  Created by Carlos Gustavo Cecyn Lundgren on 09/07/15.
//
//

#import "framework.h"

int ui_MessageBoxA(void * oswindow, const char * pszMessageParam, const char * pszHeaderParam, unsigned int uType )
{
   
   NSString * strMessage = [NSString stringWithUTF8String:pszMessageParam];

   NSString * strHeader = [NSString stringWithUTF8String:pszHeaderParam];
   
   
   const char * strButton1 = NULL;
   const char * strButton2 = NULL;
   const char * strButton3 = NULL;
   
   switch(uType)
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

   NSString * str1 = NULL;
   NSString * str2 = NULL;
   NSString * str3 = NULL;
   
   if(strButton1 != NULL)
   {
      
      str1 = [NSString stringWithUTF8String:strButton1];
      
   }
   
   if(strButton2 != NULL)
   {
      
      str2 = [NSString stringWithUTF8String:strButton2];
      
   }
   
   if(strButton3 != NULL)
   {
      
      str3 = [NSString stringWithUTF8String:strButton3];
      
   }
   
   
   __block    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
   
   UIAlertController* alert = [UIAlertController alertControllerWithTitle:strHeader
                                                               message:strMessage
                                                        preferredStyle:UIAlertControllerStyleAlert];
   
   __block BOOL b1 = FALSE;
   __block    BOOL b2 = FALSE;
   __block    BOOL b3 = FALSE;
   
   UIAlertAction * a1 = NULL;
   UIAlertAction * a2 = NULL;
   UIAlertAction * a3 = NULL;
   
   if(strButton1 != NULL)
   {
   
      a1 = [UIAlertAction actionWithTitle:str1 style:UIAlertActionStyleDefault
                                  handler:^(UIAlertAction * action) {  b1 = TRUE;}];

      [alert addAction:a1];
      
   }
   
   
   if(strButton2 != NULL)
   {
      
      a2 = [UIAlertAction actionWithTitle:str2 style:UIAlertActionStyleDefault
                                  handler:^(UIAlertAction * action) { b2 = TRUE;}];
      
      [alert addAction:a2];
      
   }
   
   if(strButton3 != NULL)
   {
      
      a3 = [UIAlertAction actionWithTitle:str3 style:UIAlertActionStyleDefault
                                  handler:^(UIAlertAction * action) { b3 = TRUE;}];
      
      [alert addAction:a3];
      
   }
   
//   Get the current keyWindow:
   
   UIWindow *window = [UIApplication sharedApplication].keyWindow;
   
  // Get its rootViewController:
   
   UIViewController *rootViewController = window.rootViewController;
[rootViewController presentViewController:alert animated:YES completion:^{
   dispatch_semaphore_signal(semaphore);
}];

dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
dispatch_release(semaphore);
   
   switch(uType)
   {
      case MB_OKCANCEL:
         if(b1)
            return IDOK;
         else if(b2)
            return IDCANCEL;
         break;
      case MB_ABORTRETRYIGNORE:
         if(b1)
            return IDABORT;
         else if(b2)
            return IDRETRY;
         else if(b3)
            return IDIGNORE;
         break;
      case MB_YESNOCANCEL:
         if(b1)
            return IDYES;
         else if(b2)
            return IDNO;
         else if(b3)
            return IDCANCEL;
         break;
      case MB_YESNO:
         if(b1)
            return IDYES;
         else if(b2)
            return IDNO;
         break;
      case MB_RETRYCANCEL:
         if(b1)
            return IDRETRY;
         else if(b2)
            return IDCANCEL;
         break;
      case MB_CANCELTRYCONTINUE:
         if(b1)
            return IDCANCEL;
         else if(b2)
            return IDTRYAGAIN;
         else if(b3)
            return IDCONTINUE;
         break;
      default:
         if(b1)
            return IDOK;
         break;
   }
   
   
   return IDCANCEL;

}

/*
 
int MessageBoxW(oswindow window, const wchar_t * pszMessageParam, const wchar_t * pszHeaderParam, UINT uType )
{
   
   string pszMessage(pszMessageParam);
   
   string pszHeader(pszHeaderParam);
   
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

*/