#include "framework.h"



#ifdef LINUX
#include "linux/c_os_cross_win_gdi_internal.h"
#elif defined(MACOS)
#include "macos/c_os_internal.h"
#endif




#if defined(MACOS)


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
   
   __Check(attributes != NULL);
   
   if (attributes != NULL)
   {
      
      CFMutableDictionaryRef traits;
      
      CFNumberRef symTraits;
      
      // Add a family name to our attributes.
      CFDictionaryAddValue(attributes, kCTFontFamilyNameAttribute, iFamilyName);
      
      // Create the traits dictionary.
      symTraits = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &iTraits);
      
      (symTraits != NULL);
      
      if (symTraits != NULL)
      {
         // Create a dictionary to hold our traits values.
         traits = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
         
         __Check(traits != NULL);
         
         if (traits != NULL)
         {
            
            // Add the symbolic traits value to the traits dictionary.
            CFDictionaryAddValue(traits, kCTFontSymbolicTrait, symTraits);
            
            // Add the traits attribute to our attributes.
            CFDictionaryAddValue(attributes, kCTFontTraitsAttribute, traits);
            
            CFRelease(traits);
            
         }
         
         CFRelease(symTraits);
         
      }
      
      // Create the font descriptor with our attributes and input size.
      descriptor = CTFontDescriptorCreateWithAttributes(attributes);
      
      __Check(descriptor != NULL);
      
      CFRelease(attributes);
      
   }
   
   // Return our font descriptor.
   return descriptor;
   
}


CTFontRef CreateFont(CTFontDescriptorRef iFontDescriptor, CGFloat iSize)
{
   
   __Check(iFontDescriptor != NULL);
   
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

bool TextOutU_dup(HDC hdc, int x, int y, const char * pszUtf8, int iSize)
{    
   
   CGContextRef context = hdc->m_cgcontext;
   

   CGContextSetTextMatrix(context, CGAffineTransformIdentity);
   
   
   // Initialize an attributed string.
   CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, pszUtf8, kCFStringEncodingUTF8);
   CTFontRef      ctfontrefText     = hdc->m_ctfontref; 
   CGColorRef     cgcolorrefText    = hdc->m_cgcolorrefText;
   
   
   
   // Initialize string, font, and context
   CFStringRef keys[] = { kCTFontAttributeName, kCTForegroundColorAttributeName };
   CFTypeRef values[] = { ctfontrefText, cgcolorrefText };
   CFDictionaryRef attributes = CFDictionaryCreate(
                      kCFAllocatorDefault, (const void**)&keys,
                      (const void**)&values, sizeof(keys) / sizeof(keys[0]),
                      &kCFTypeDictionaryKeyCallBacks,
                      &kCFTypeDictionaryValueCallBacks);
   
   
//   CFIndex iLen = CFStringGetLength(string);
   
   
   CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);
   
   CFRelease(attributes);
   
   
   
//   CFAttributedStringSetAttribute(attrString, CFRangeMake(0, iLen), (CFStringRef) , (CFTypeRef) textcolor);
   
   
  // CFStringGetLength
   
   CTLineRef line = CTLineCreateWithAttributedString(attrString);
   
   
   
   // Set text position and draw the line into the graphics context
   
   CGContextSetTextPosition(context, x, y);
   
   CTLineDraw(line, context);
   
   CFRelease(line);
   
   
   CFRelease(attrString);
   CFRelease(string);
   
   
   return TRUE;
   
   
}



void FillSolidRect_dup(HDC hdc, LPCRECT lpRect, COLORREF clr)
{
   CGColorRef color = mac_create_color(clr);
   CGRect rect;
   rect.origin.x = lpRect->left;
   rect.origin.y = lpRect->top;
   rect.size.width = lpRect->right - lpRect->left;
   rect.size.height = lpRect->bottom - lpRect->top;
   CGContextFillRect(hdc->m_cgcontext, rect);
   mac_release_color(color);
}

HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);
HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc);

HFONT CreatePointFont_dup(int nPointSize, const char * lpszFaceName, HDC hdc)
{
   return CreatePointBoldFont_dup(nPointSize, lpszFaceName, FALSE, hdc);
}

HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc)
{
   CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, lpszFaceName, kCFStringEncodingUTF8);
   CreateFontDescriptorFromFamilyAndTraits(string, BOLD, nPointSize);
   CFRelease(string);
}

// pLogFont->nHeight is interpreted as PointSize * 10
HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam)
{
   
#ifdef WINDOWS
   
   HDC hDC;
   if (hdcParam != NULL)
   {
      hDC = hdcParam;
   }
   else
      hDC = ::GetDC(NULL);
   
   // convert nPointSize to logical units based on pgraphics
   LOGFONT logFont = *lpLogFont;
   POINT pt;
   // 72 points/inch, 10 decipoints/point
   pt.y = ::MulDiv(::GetDeviceCaps(hDC, LOGPIXELSY), logFont.lfHeight, 720);
   pt.x = 0;
   ::DPtoLP(hDC, &pt, 1);
   POINT ptOrg = { 0, 0 };
   ::DPtoLP(hDC, &ptOrg, 1);
   logFont.lfHeight = -abs_dup(pt.y - ptOrg.y);
   
   if(hdcParam == NULL)
      ReleaseDC(NULL, hDC);
   
   return ::CreateFontIndirect(&logFont);
   
#else
   
   /*HDC hDC;
    if (hdcParam != NULL)
    {
    hDC = hdcParam;
    }
    else
    hDC = ::GetDC(NULL);*/
   
   return ::CreateFontIndirect(lpLogFont);
   
   /*if(hdcParam == NULL)
    ReleaseDC(NULL, hDC);*/
   
#endif
   
}




#elif defined(LINUX)

void FillSolidRect_dup(HDC hdc, LPCRECT lpRect, COLORREF clr)
{
   XSetBackground(hdc->m_display, hdc->m_gc, clr);
   XFillRectangle(hdc->m_display, hdc->m_d, hdc->m_gc, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);
}

HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);
HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc);

HFONT CreatePointFont_dup(int nPointSize, const char * lpszFaceName, HDC hdc)
{
   return CreatePointBoldFont_dup(nPointSize, lpszFaceName, FALSE, hdc);
}

HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc)
{
   
   LOGFONT logFont;
   memset_dup(&logFont, 0, sizeof(LOGFONT));
   logFont.lfCharSet = DEFAULT_CHARSET;
   logFont.lfHeight = nPointSize;
   logFont.lfWeight = BOLD ? FW_BOLD : FW_NORMAL;
   strncpy_dup(logFont.lfFaceName, lpszFaceName, sizeof(logFont.lfFaceName));

   return CreatePointFontIndirect_dup(&logFont, hdc);
}

// pLogFont->nHeight is interpreted as PointSize * 10
HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam)
{

   /*HDC hDC;
   if (hdcParam != NULL)
   {
      hDC = hdcParam;
   }
   else
      hDC = ::GetDC(NULL);*/

   return ::CreateFontIndirect(lpLogFont);

   /*if(hdcParam == NULL)
      ReleaseDC(NULL, hDC);*/


}





#elif defined(WINDOWS)

bool TextOutU_dup(HDC hdc, int x, int y, const char * pszUtf8, int iSize)
{
   WCHAR * pwsz = utf8_to_16(pszUtf8);
   bool b = TextOutW(hdc, x, y, pwsz, (int) wcslen_dup(pwsz)) != FALSE;
   delete  [] pwsz;
   return b;
}

void FillSolidRect_dup(HDC hdc, LPCRECT lpRect, COLORREF clr)
{
   ::SetBkColor(hdc, clr);
   ::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
}

HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);
HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc);

HFONT CreatePointFont_dup(int nPointSize, const char * lpszFaceName, HDC hdc)
{
   return CreatePointBoldFont_dup(nPointSize, lpszFaceName, FALSE, hdc);
}

HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc)
{
   LOGFONT logFont;
   memset_dup(&logFont, 0, sizeof(LOGFONT));
   logFont.lfCharSet = DEFAULT_CHARSET;
   logFont.lfHeight = nPointSize;
   logFont.lfWeight = BOLD ? FW_BOLD : FW_NORMAL;
   strncpy_dup(logFont.lfFaceName, lpszFaceName, sizeof(logFont.lfFaceName));

   return CreatePointFontIndirect_dup(&logFont, hdc);
}

// pLogFont->nHeight is interpreted as PointSize * 10
HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam)
{
   HDC hDC;
   if (hdcParam != NULL)
   {
      hDC = hdcParam;
   }
   else
      hDC = ::GetDC(NULL);

   // convert nPointSize to logical units based on pgraphics
   LOGFONT logFont = *lpLogFont;
   POINT pt;
   // 72 points/inch, 10 decipoints/point
   pt.y = ::MulDiv(::GetDeviceCaps(hDC, LOGPIXELSY), logFont.lfHeight, 720);
   pt.x = 0;
   ::DPtoLP(hDC, &pt, 1);
   POINT ptOrg = { 0, 0 };
   ::DPtoLP(hDC, &ptOrg, 1);
   logFont.lfHeight = -abs_dup(pt.y - ptOrg.y);

   if(hdcParam == NULL)
      ReleaseDC(NULL, hDC);

   return ::CreateFontIndirect(&logFont);
}


                                        
                                        
#endif

void fastblur(DWORD * pdata, int w, int h, int radius)
{
   if(radius < 1)
   {
      return;
   }
  int wm=w-1;
  int hm=h-1;
  int wh=w*h;
  int div=radius+radius+1;
  simple_int_array iaA;
  iaA.set_size(wh);
  int * a = iaA.get_data();
  simple_int_array iaR;
  iaR.set_size(wh);
  int * r = iaR.get_data();
  simple_int_array iaG;
  iaG.set_size(wh);
  int * g = iaG.get_data();
  simple_int_array iaB;
  iaB.set_size(wh);
  int * b = iaB.get_data();
  int asum, rsum,gsum,bsum,x,y,i,yp,yi,yw;
  int p;
  int p1;
  int p2;
  simple_int_array iaVmin;
  iaVmin.set_size(max(w,h));
  int * vmin = iaVmin.get_data();
  simple_int_array iaVmax;
  iaVmax.set_size(max(w,h));
  int * vmax = iaVmax.get_data();
  int * pix=(int *) pdata;
  simple_int_array iaDv;
  iaDv.set_size(256*div);
  int * dv = iaDv.get_data();
  for (i=0;i<iaDv.get_count();i++)
  {
      dv[i]= min(255, i/div);
  }

  yw=yi=0;

   for(x=0;x<w;x++)
   {
      vmin[x]=min(x+radius+1,wm);
      vmax[x]=max(x-radius,0);
   }

   for (y=0;y<h;y++)
   {
      asum=rsum=gsum=bsum=0;
      for(i=-radius;i<=radius;i++)
      {
         p=pix[yi+min(wm,max(i,0))];
         asum+=((p & 0xff000000)>>24);
         rsum+=((p & 0xff0000)>>16);
         gsum+=((p & 0x00ff00)>>8);
         bsum+=(p & 0x0000ff);
      }
      for(x=0;x<w;x++)
      {
         a[yi]=dv[asum];
         r[yi]=dv[rsum];
         g[yi]=dv[gsum];
         b[yi]=dv[bsum];

         p1=pix[yw+vmin[x]];
         p2=pix[yw+vmax[x]];

         asum+= ((p1 >> 24) & 0xff )-((p2 >> 24) & 0xff);
         rsum+= ((p1 & 0x00ff0000)-(p2 & 0x00ff0000))>>16;
         gsum+= ((p1 & 0x0000ff00)-(p2 & 0x0000ff00))>>8;
         bsum+= ((p1 & 0x000000ff)-(p2 & 0x000000ff));
         yi++;
      }
      yw+=w;
  }
   for (y=0;y<h;y++)
   {
      vmin[y] = min(y+radius+1,hm) * w;
      vmax[y] = max(y-radius,0) * w;
   }

   for (x=0;x<w;x++)
   {
      asum=rsum=gsum=bsum=0;
      yp=-radius*w;
      for(i=-radius;i<=radius;i++)
      {
         yi=max(0,yp)+x;
         rsum+=r[yi];
         gsum+=g[yi];
         bsum+=b[yi];
         asum+=a[yi];
         yp+=w;
      }
      yi=x;
      for (y=0;y<h;y++)
      {
         pix[yi]=(dv[asum]<<24) | (dv[rsum]<<16) | (dv[gsum]<<8) | dv[bsum];

         p1=x+vmin[y];
         p2=x+vmax[y];

         rsum+=r[p1]-r[p2];
         gsum+=g[p1]-g[p2];
         bsum+=b[p1]-b[p2];
         asum+=a[p1]-a[p2];

      yi+=w;
      }
   }

}
