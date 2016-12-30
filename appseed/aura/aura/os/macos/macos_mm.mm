//
//  macos_mm.m
//  aura
//
//  Created by Carlos Gustavo Cecyn Lundgren on 3/8/16.
//
//

#import <Foundation/Foundation.h>
//
//char * str_clip_dup()
//{
// 
//   NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
//   
//   NSArray *classes = [[NSArray alloc] initWithObjects:[NSString class], nil];
//   
//   NSDictionary *options = [NSDictionary dictionary];
//   
//   NSArray *copiedItems = [pasteboard readObjectsForClasses:classes options:options];
//   
//   if (copiedItems == nil)
//   {
//      
//      return NULL;
//
//   }
//   
//   if([copiedItems count] <= 0)
//   {
//    
//      return NULL;
//      
//   }
//  
//   NSString * pstr = [copiedItems objectAtIndex:0];
//   
//   return strdup([pstr UTF8String]);
//
//}


char * ns_get_default_browser_path()
{
   
   CFURLRef appURL = LSCopyDefaultApplicationURLForURL((CFURLRef)[NSURL URLWithString: @"http:"], kLSRolesAll, NULL);
   
   CFStringRef str = CFURLGetString(appURL);
   
   char * psz = strdup([(NSString *)str UTF8String]);
   
   CFRelease(appURL);
   
   //CFRelease(str);
   
   return psz;
   
}


bool ns_open_file(const char * psz)
{
   
   NSString * path = [NSString stringWithUTF8String:psz];
   
   if(path == NULL)
   {
      
      return false;
      
   }
   
   if(![[NSWorkspace sharedWorkspace] openFile: path])
   {
      
      return false;
      
   }
   
   return true;
   
}
