//
//  ios_mm.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 8/3/15.
//
//

#include "framework.h"

bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage);;

int _get_exe_path_len()
{
   
   return strlen([[[NSBundle mainBundle] executablePath] UTF8String]);
   
}

void _get_exe_path(char * pszPath, int size)
{
   
   strncpy(pszPath, [[[NSBundle mainBundle] executablePath] UTF8String], size);
   
}



bool mm2_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz)
{
   
   NSString * str = [NSString stringWithUTF8String:psz];
   
   if(str == NULL)
   {
      
      return false;
      
   }
   
   NSURL *URL = [NSURL fileURLWithPath: str];
   
   UIDocumentInteractionController *documentInteractionController =[UIDocumentInteractionController interactionControllerWithURL:URL];
   
   int iFind = 0;
   
   for(; iFind < [[documentInteractionController icons] count]; iFind++)
   {
      
      UIImage *image = [[documentInteractionController icons] objectAtIndex:iFind];
      
      if([image size].width > cx && [image size].height > cy)
      {
         
         if(iFind > 0)
         {
            
            iFind--;
            
         }
         
         break;
         
      }
      
   }
   
   if(iFind >= [[documentInteractionController icons] count])
   {
      
      return false;
      
   }
   
   UIImage *image = [[documentInteractionController icons] objectAtIndex:iFind];
   
   if(image == NULL)
   {
      
      return false;
      
   }
   
   CGImageRef i = [image CGImage];
   
   bool bOk = GetImagePixelData(pcr, cx, cy, iScan,  i);
   
   //CFRelease(i);
   
   return bOk;
   
   
   
}





bool mm1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz)
{
   
   return mm2_get_file_image(pcr, cx, cy, iScan, psz);
}
