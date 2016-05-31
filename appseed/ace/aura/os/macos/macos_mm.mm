//
//  macos_mm.m
//  aura
//
//  Created by Carlos Gustavo Cecyn Lundgren on 3/8/16.
//
//

#import <Foundation/Foundation.h>

char * str_clip_dup()
{
 
   NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
   
   NSArray *classes = [[NSArray alloc] initWithObjects:[NSString class], nil];
   
   NSDictionary *options = [NSDictionary dictionary];
   
   NSArray *copiedItems = [pasteboard readObjectsForClasses:classes options:options];
   
   if (copiedItems == nil)
   {
      
      return NULL;

   }
   
   if([copiedItems count] <= 0)
   {
    
      return NULL;
      
   }
  
   NSString * pstr = [copiedItems objectAtIndex:0];
   
   return strdup([pstr UTF8String]);

}