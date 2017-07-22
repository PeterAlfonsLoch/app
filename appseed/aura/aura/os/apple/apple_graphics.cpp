#include "framework.h"
#include <CoreFoundation/CoreFoundation.h>
#include <CoreText/CoreText.h>


#define user user2
#include <sys/param.h>
#include <sys/sysctl.h>
#undef user



CGColorRef cg_create_color(COLORREF cr)
{
   
   // Create a color and add it as an attribute to the string.
   CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
   CGFloat components[] = { argb_get_r_value(cr) / 255.0,
      argb_get_g_value(cr) / 255.0,
      argb_get_b_value(cr) / 255.0,
      argb_get_a_value(cr) / 255.0};
   
   CGColorRef color = CGColorCreate(rgbColorSpace, components);
   
   CGColorSpaceRelease(rgbColorSpace);
   
   return color;
}


WINBOOL cg_release_color(CGColorRef colorref)
{
   CGColorRelease(colorref);
   return TRUE;
}


device_context::device_context()
:
/*  m_colour(wxColourDisplay())
 , m_ok(true)
 , m_clipping(false)
 , m_isInteractive(0)
 , m_isBBoxValid(false)
 , */ m_logicalOriginX(0), m_logicalOriginY(0)
, m_deviceOriginX(0), m_deviceOriginY(0)
, m_logicalScaleX(1.0), m_logicalScaleY(1.0)
, m_userScaleX(1.0), m_userScaleY(1.0)
, m_scaleX(1.0), m_scaleY(1.0)
, m_signX(1), m_signY(1)
, m_minX(0), m_minY(0), m_maxX(0), m_maxY(0)
, m_clipX1(0), m_clipY1(0), m_clipX2(0), m_clipY2(0)
/*  , m_logicalFunction(wxCOPY)
 , m_backgroundMode(wxTRANSPARENT)
 , m_mappingMode(wxMM_TEXT)
 , m_pen() */
/* , m_brush()
 , m_backgroundBrush(*wxTRANSPARENT_BRUSH)
 , m_textForegroundColour(*wxBLACK)
 , m_textBackgroundColour(*wxWHITE)
 , m_font()
 #if wxUSE_PALETTE
 , m_palette()
 , m_hasCustomPalette(false)
 #endif // wxUSE_PALETTE */
{
   m_cgcontext = NULL;
}


CTFontDescriptorRef CreateFontDescriptorFromName(CFStringRef iPostScriptName, CGFloat iSize)
{
   assert(iPostScriptName != NULL);
   return CTFontDescriptorCreateWithNameAndSize(iPostScriptName, iSize);
}


CTFontDescriptorRef CreateFontDescriptorFromFamilyAndTraits(CFStringRef iFamilyName, CTFontSymbolicTraits iTraits, CGFloat iSize)
{
   
   CTFontDescriptorRef descriptor = NULL;
   CFMutableDictionaryRef attributes;
   assert(iFamilyName != NULL);
   
   // Create a mutable dictionary to hold our attributes.
   attributes = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
   
//   __Check(attributes != NULL);
   
   if (attributes != NULL)
   {
      
      CFMutableDictionaryRef traits;
      
      CFNumberRef symTraits;
      
      // add a family name to our attributes.
      CFDictionaryAddValue(attributes, kCTFontFamilyNameAttribute, iFamilyName);
      
      // Create the traits dictionary.
      symTraits = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &iTraits);
      
      (symTraits != NULL);
      
      if (symTraits != NULL)
      {
         // Create a dictionary to hold our traits values.
         traits = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
         
//         __Check(traits != NULL);
         
         if (traits != NULL)
         {
            
            // add the symbolic traits value to the traits dictionary.
            CFDictionaryAddValue(traits, kCTFontSymbolicTrait, symTraits);
            
            // add the traits attribute to our attributes.
            CFDictionaryAddValue(attributes, kCTFontTraitsAttribute, traits);
            
            CFRelease(traits);
            
         }
         
         CFRelease(symTraits);
         
      }
      
      // Create the font descriptor with our attributes and input size.
      descriptor = CTFontDescriptorCreateWithAttributes(attributes);
      
//      __Check(descriptor != NULL);
      
      CFRelease(attributes);
      
   }
   
   // Return our font descriptor.
   return descriptor;
   
}


CTFontRef CreateFont(CTFontDescriptorRef iFontDescriptor, CGFloat iSize)
{
   
//   __Check(iFontDescriptor != NULL);
   
   // Create the font from the font descriptor and input size. Pass
   // NULL for the matrix parameter to use the default matrix (identity).
   return CTFontCreateWithFontDescriptor(iFontDescriptor, iSize, NULL);
   
}


CTFontRef CreateBoldFont(CTFontRef iFont, Boolean iMakeBold)
{
   
   CTFontSymbolicTraits desiredTrait = 0;
   
   CTFontSymbolicTraits traitMask;
   
   // If we are trying to make the font bold, set the desired trait
   // to be bold.
   if (iMakeBold)
      desiredTrait = kCTFontBoldTrait;
   
   // Mask off the bold trait to indicate that it is the only trait
   // desired to be modified. As CTFontSymbolicTraits is a bit field,
   // we could choose to change multiple traits if we desired.
   traitMask = kCTFontBoldTrait;
   
   // Create a copy of the original font with the masked trait set to the
   // desired value. If the font family does not have the appropriate style,
   // this will return NULL.
   
   return CTFontCreateCopyWithSymbolicTraits(iFont, 0.0, NULL, desiredTrait, traitMask);
   
}


CTFontRef CreateFontConvertedToFamily(CTFontRef iFont, CFStringRef iFamily)
{
   
   // Create a copy of the original font with the new family. This call
   // attempts to preserve traits, and may return NULL if that is not possible.
   // Pass in 0.0 and NULL for size and matrix to preserve the values from
   // the original font.
   return CTFontCreateCopyWithFamily(iFont, 0.0, NULL, iFamily);
   
}

//bool TextOutU_dup(HDC hdc, int x, int y, const char * pszUtf8, int iSize)
//{    
//   
//   CGContextRef context = hdc->m_cgcontext;
//   
//
//   CGContextSetTextMatrix(context, CGAffineTransformIdentity);
//   
//   
//   // Initialize an attributed string.
//   CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, pszUtf8, kCFStringEncodingUTF8);
//   CTFontRef      ctfontrefText     = hdc->m_ctfontref; 
//   CGColorRef     cgcolorrefText    = hdc->m_cgcolorrefText;
//   
//   
//   
//   // Initialize string, font, and context
//   CFStringRef keys[] = { kCTFontAttributeName, kCTForegroundColorAttributeName };
//   CFTypeRef values[] = { ctfontrefText, cgcolorrefText };
//   CFDictionaryRef attributes = CFDictionaryCreate(
//                      kCFAllocatorDefault, (const void**)&keys,
//                      (const void**)&values, sizeof(keys) / sizeof(keys[0]),
//                      &kCFTypeDictionaryKeyCallBacks,
//                      &kCFTypeDictionaryValueCallBacks);
//   
//   
////   CFIndex iLen = CFStringGetLength(string);
//   
//   
//   CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);
//   
//   CFRelease(attributes);
//   
//   
//   
////   CFAttributedStringSetAttribute(attrString, CFRangeMake(0, iLen), (CFStringRef) , (CFTypeRef) textcolor);
//   
//   
//  // CFStringGetLength
//   
//   CTLineRef line = CTLineCreateWithAttributedString(attrString);
//   
//   
//   
//   // Set text position and draw the line into the graphics context
//   
//   CGContextSetTextPosition(context, x, y);
//   
//   CTLineDraw(line, context);
//   
//   CFRelease(line);
//   
//   
//   CFRelease(attrString);
//   CFRelease(string);
//   
//   
//   return TRUE;
//   
//   
//}



//void FillSolidRect_dup(HDC hdc, LPCRECT lpRect, COLORREF clr)
//{
//   CGColorRef color = cg_create_color(clr);
//   CGRect rect;
//   rect.origin.x = lpRect->left;
//   rect.origin.y = lpRect->top;
//   rect.size.width = lpRect->right - lpRect->left;
//   rect.size.height = lpRect->bottom - lpRect->top;
//   CGContextFillRect(hdc->m_cgcontext, rect);
//   cg_release_color(color);
//}

//HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);
//HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc);
//
//HFONT CreatePointFont_dup(int nPointSize, const char * lpszFaceName, HDC hdc)
//{
//   return CreatePointBoldFont_dup(nPointSize, lpszFaceName, FALSE, hdc);
//}
//
//HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc)
//{
//   CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, lpszFaceName, kCFStringEncodingUTF8);
//   CreateFontDescriptorFromFamilyAndTraits(string, BOLD, nPointSize);
//   CFRelease(string);
//   return NULL;
//}
//
//HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam)
//{
//   
//   
//   return ::CreateFontIndirect(lpLogFont);
//   
//   
//}
//
//
//



CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy);
bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage);


bool mm_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);










CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy);
bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage);


bool mm_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);




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







int get_processor_count()
{
   
   int nm[2];
   
   size_t len = 4;
   
   uint32_t count;
   
   nm[0] = CTL_HW;
   
   nm[1] = HW_AVAILCPU;
   
   sysctl(nm, 2, &count, &len, NULL, 0);
   
   if(count < 1)
   {
      
      nm[1] = HW_NCPU;
      
      sysctl(nm, 2, &count, &len, NULL, 0);
      
      if(count < 1)
      {
         count = 1;
         
      }
      
   }
   
   return count;
   
   //#else
   // return sysconf(_SC_NPROCESSORS_ONLN);
   //#endif
}
