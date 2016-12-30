//
//  user_shell_macos_mm.m
//  core
//
//  Created by Camilo Sasuke Tsumanuma on 30/12/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

bool GetImagePixelData(unsigned int * pcr, int cx, int cy, CGImageRef inImage)
;

bool mm_get_file_image(unsigned int * pcr, int cx, int cy, const char * psz)
{
   
  NSString * str = [NSString stringWithUTF8String:psz];
   
   if(str == NULL)
   {
      
      return false;
      
   }

   NSImage *image = [[NSWorkspace sharedWorkspace] iconForFile:str];
   if(image == NULL)
   {
      
      return false;
      
   }
   
   NSRect r;
   
   r.origin.x = 0;
   r.origin.y = 0;
   r.size.width = cx;
   r.size.height = cy;
   
   CGImageRef i = [image CGImageForProposedRect: &r context:nil hints:nil];
   
   bool bOk = GetImagePixelData(pcr, cx, cy, i);
   
   CFRelease(i);
                                
                              return bOk;
   
   
   
}



