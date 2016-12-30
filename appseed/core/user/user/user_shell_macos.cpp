//
//  user_shell_macos.cpp
//  core
//
//  Created by Camilo Sasuke Tsumanuma on 30/12/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"

bool macos_get_file_image(::draw2d::dib * pdib, const char * psz);

CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy);
bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage);


bool mm_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);

bool macos_get_file_image(::draw2d::dib * pdib, const char * psz)
{
   
   if(!mm_get_file_image(pdib->m_pcolorref, pdib->m_size.cx, pdib->m_size.cy, pdib->m_iScan, psz))
   {
      
      return false;
      
   }
   
   return true;
   
}


bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage)
{

   CGContextRef cgctx = CreateARGBBitmapContext(inImage, cx, cy);
   
   if (cgctx == NULL)
   {
      
      return false;
      
   }
   
   CGRect rect = {{0,0},{(CGFloat)cx,(CGFloat)cy}};
   
   CGContextDrawImage(cgctx, rect, inImage);
   
   void *data = CGBitmapContextGetData (cgctx);
   
   byte * pdest = (byte * ) pcr;

   if (data != NULL)
   {
      
      for(int y = cy - 1; y >= 0; y--)
      {
         
         byte * pline = (byte *) &((unsigned int*)data)[y * cx];
   
         memcpy(pdest, pline, cx* 4);
         
         pdest += iScan;
         
      }

   }
   
   CGContextRelease(cgctx);
   
   return data != NULL;
   
}


CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy)
{
   
   CGContextRef    context = NULL;
   
   CGColorSpaceRef colorSpace;
   
   void *          bitmapData;
   
   int             bitmapByteCount;
   
   int             bitmapBytesPerRow;
   
   bitmapBytesPerRow   = (cx * 4);

   bitmapByteCount     = (bitmapBytesPerRow * cy);
   
   colorSpace = CGColorSpaceCreateDeviceRGB();
   
   if (colorSpace == NULL)
   {
      
      output_debug_string("CreateARGBBitmapContext: Error allocating color space\n");
      
      return NULL;
      
   }
   
//   bitmapData = malloc( bitmapByteCount );
//   
//   if (bitmapData == NULL)
//   {
//      
//      output_debug_string("CreateARGBBitmapContext: Memory not allocated!");
//      
//      CGColorSpaceRelease( colorSpace );
//      
//      return NULL;
//      
//   }
//   
//   memset(bitmapData, 0, bitmapByteCount);
   
   // Create the bitmap context. We want pre-multiplied ARGB, 8-bits
   // per component. Regardless of what the source image format is
   // (CMYK, Grayscale, and so on) it will be converted over to the format
   // specified here by CGBitmapContextCreate.
   context =
      CGBitmapContextCreate (
                             NULL,
                             cx,
                             cy,
                             8,
                             bitmapBytesPerRow,
                             colorSpace,
                             kCGImageAlphaPremultipliedLast);
   
//   if (context == NULL)
//   {
//      
//      free (bitmapData);
//      
//      output_debug_string("CreateARGBBitmapContext: Context not created!");
//      
//   }
   
   CGColorSpaceRelease( colorSpace );
   
   return context;
}
