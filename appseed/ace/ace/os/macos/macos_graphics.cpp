#include "framework.h"
#include "macos_internal.h"

#ifdef DEBUG
#undef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>

#if DEBUG
#undef DEBUG
#define DEBUG
#else
#undef DEBUG
#endif


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



CGColorRef mac_create_color(COLORREF cr)
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


WINBOOL mac_release_color(CGColorRef colorref)
{
   CGColorRelease(colorref);
    return TRUE;
}

/*

HDC GetWindowDC(oswindow hwnd)
{
   return GetDC(hwnd);
}



WINBOOL ReleaseDC(oswindow hwnd, HDC hdc)
{

   if(hdc == NULL)
      return FALSE;
   
   /*QDEndCGContext(hdc->m_windowPort, &hdc->m_cgcontext);
   
   if(hdc->m_wasSwapped)
   {
      QDSwapPort(hdc->m_savedPort, &hdc->m_savedPort);
   }*/

 /*  delete hdc;
   return TRUE;

}
  
  */


//WINBOOL GetClientRect(oswindow hwnd, LPRECT lprect)
//{
/*   XWindowAttributes attrs;
   /* Fill attribute structure with information about root window */
  /* if(XGetWindowAttributes(XOpenDisplay(NULL), hwnd, &attrs) == 0)
   {
      return false;
   }
   lprect->left      = 0;
   lprect->top       = 0;
   lprect->right     = lprect->left    + attrs.width;
   lprect->bottom    = lprect->top     + attrs.height;*/
    
    /*if(!GetWindowRect(hwnd, lprect))
        return FALSE;
    
    lprect->right   -=  lprect->left;
    lprect->bottom  -=  lprect->top;
    lprect->left    =   0;
    lprect->top     =   0;
    
    return TRUE;
    
}


WINBOOL GetWindowRect(oswindow hwnd, LPRECT lprect)
{*/
  /* XWindowAttributes attrs;
   /* Fill attribute structure with information about root window */
/*   if(XGetWindowAttributes(XOpenDisplay(NULL), hwnd, &attrs) == 0)
   {
      return false;
   }
   lprect->left      = attrs.x;
   lprect->top       = attrs.y;
   lprect->right     = lprect->left    + attrs.width;
   lprect->bottom    = lprect->top     + attrs.height;*/
    
/*   return get_nswindow_rect(hwnd, lprect) ? 1 : 0;
    
    
}
*/

/*
int FillRect(HDC hdc, const RECT * lprc, HBRUSH hbr)
{
    
   CGRect rect;
   
   rect.origin.x     = lprc->left;
   rect.origin.y     = lprc->top;
   rect.size.width   = lprc->right - lprc->left;
   rect.size.height  = lprc->bottom - lprc->top;
   
   CGContextSetRGBFillColor(hdc->m_cgcontext, argb_get_r_value(hbr->lbColor), argb_get_g_value(hbr->lbColor), argb_get_b_value(hbr->lbColor), argb_get_a_value(hbr->lbColor));
    
   CGContextFillRect(hdc->m_cgcontext, rect);
   
   return 1;
}
*/

/*

HDC BeginPaint(oswindow hwnd, PAINTSTRUCT * ps)
{

   HDC hdc = GetDC(hwnd);

   GetClientRect(hwnd, &ps->rcPaint);

   return hdc;

}


WINBOOL EndPaint(oswindow hwnd, PAINTSTRUCT * ps)
{

   return ReleaseDC(hwnd, ps->hdc);

}
*/






/*int _c_XErrorHandler(Display * display, XErrorEvent * perrorevent)
{
   return 0;
}*/




HFONT CreateFontIndirect(const LOGFONT * lf)
{
    return NULL;
}
HPEN CreatePen(int iPenStyle, int iWidth, COLORREF crColor)
{
    return NULL;
}
HGDIOBJ GetStockObject(int iStockObject)
{
    return NULL;
}
WINBOOL SelectObject(HDC hdc, HGDIOBJ hgdiobj)
{
    return FALSE;
}
WINBOOL Rectangle(HDC hdc, int x1, int y1, int x2, int y2)
{
    return FALSE;
}
WINBOOL DeleteObject(HGDIOBJ hgdiobj)
{
    return FALSE;
}
HDC CreateCompatibleDC(HDC hdc)
{
    return NULL;
}
HBITMAP WINAPI CreateDIBSection(HDC hdc, const BITMAPINFO *lpbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset)
{
    return NULL;
}
WINBOOL SetBkMode(HDC hdc, int iMode)
{
    return FALSE;
}
WINBOOL DeleteDC(HDC hdc)
{
    return FALSE;
}
WINBOOL AlphaBlend(HDC hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, HDC hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, BLENDFUNCTION ftn)
{
    return FALSE;
}
WINBOOL GetObject(HGDIOBJ hgdiobj, int iSize, void * object)
{
    return FALSE;
}
WINBOOL GetTextExtentPoint(HDC hdc, const char * pszText, int iSize, SIZE * psize)
{
    return FALSE;
}



WINBOOL SetTextColor(HDC hdc, COLORREF crText)
{
   
   mac_release_color(hdc->m_cgcolorrefText);
   hdc->m_cgcolorrefText = mac_create_color(crText);
   return TRUE;
}

HBRUSH CreateSolidBrush(COLORREF cr)
{
    return NULL;
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
   return NULL;
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





