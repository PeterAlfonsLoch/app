//
//  user_shell_macos.cpp
//  core
//
//  Created by Camilo Sasuke Tsumanuma on 30/12/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"

CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy);
bool GetImagePixelData(unsigned int * pcr, int cx, int cy, CGImageRef inImage);


bool mm_get_file_image(unsigned int * pcr, int cx, int cy, const char * psz);

bool macos_get_file_image(::draw2d::dib * pdib, const char * psz)
{
   
   if(!mm_get_file_image(pdib->m_pcolorref, pdib->m_size.cx, pdib->m_size.cy, psz))
   {
      
      return false;
      
   }
   
   return true;
   
}


bool GetImagePixelData(unsigned int * pcr, int cx, int cy, CGImageRef inImage)
{
   // Get image width, height. We'll use the entire image.
   size_t w = CGImageGetWidth(inImage);
   size_t h = CGImageGetHeight(inImage);
   CGRect rect = {{0,0},{(CGFloat)cx,(CGFloat)cy}};
   
   // Create the bitmap context
   CGContextRef cgctx = CreateARGBBitmapContext(inImage, cx, cy);
   if (cgctx == NULL)
   {
      // error creating context
      return false;
   }
   
   
   // Draw the image to the bitmap context. Once we draw, the memory
   // allocated for the context for rendering will then contain the
   // raw image data in the specified color space.
   CGContextDrawImage(cgctx, rect, inImage);
   
   // Now we can get a pointer to the image data associated with the bitmap
   // context.
   void *data = CGBitmapContextGetData (cgctx);
   
   byte * pdest = (byte * ) pcr;
   if (data != NULL)
   {
      
      for(int y = 0; y < cy; y++)
      {
         byte * pline = (byte *) &((unsigned int*)data)[(cy - y -1) * cx];
         for(int x = 0; x < cx; x++)
         {
      
            pdest[0] = pline[0];
            pdest[1] = pline[2];
            pdest[2] = pline[1];
            pdest[3] = pline[3];
            
            pdest += 4;
            pline += 4;
           // memcpy(pcr, data, cx* );
            
         }
         
      }
      // **** You have a pointer to the image data ****
      
      // **** Do stuff with the data here ****
      
   }
   
   // When finished, release the context
   CGContextRelease(cgctx);
   // Free image data memory for the context
   if (data)
   {
      free(data);
   }
   return data != NULL;
}

CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy)
{
   CGContextRef    context = NULL;
   CGColorSpaceRef colorSpace;
   void *          bitmapData;
   int             bitmapByteCount;
   int             bitmapBytesPerRow;
   
   // Get image width, height. We'll use the entire image.
   //size_t pixelsWide = CGImageGetWidth(inImage);
   //size_t pixelsHigh = CGImageGetHeight(inImage);
   
   // Declare the number of bytes per row. Each pixel in the bitmap in this
   // example is represented by 4 bytes; 8 bits each of red, green, blue, and
   // alpha.
   bitmapBytesPerRow   = (cx * 4);
   bitmapByteCount     = (bitmapBytesPerRow * cy);
   
   // Use the generic RGB color space.
   colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
   if (colorSpace == NULL)
   {
      fprintf(stderr, "Error allocating color space\n");
      return NULL;
   }
   
   // Allocate memory for image data. This is the destination in memory
   // where any drawing to the bitmap context will be rendered.
   bitmapData = malloc( bitmapByteCount );
   if (bitmapData == NULL)
   {
      fprintf (stderr, "Memory not allocated!");
      CGColorSpaceRelease( colorSpace );
      return NULL;
   }
   
   // Create the bitmap context. We want pre-multiplied ARGB, 8-bits
   // per component. Regardless of what the source image format is
   // (CMYK, Grayscale, and so on) it will be converted over to the format
   // specified here by CGBitmapContextCreate.
   context = CGBitmapContextCreate (bitmapData,
cx                                    ,cy,
                                    8,      // bits per component
                                    bitmapBytesPerRow,
                                    colorSpace,
                                    kCGImageAlphaPremultipliedFirst);
   if (context == NULL)
   {
      free (bitmapData);
      fprintf (stderr, "Context not created!");
   }
   
   // Make sure and release colorspace before returning
   CGColorSpaceRelease( colorSpace );
   
   return context;
}
