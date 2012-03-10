#include "StdAfx.h"
#include "c_os_internal.h"


#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>


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
   CGFloat components[] = { GetRValue(cr) / 255.0, 
      GetGValue(cr) / 255.0,
      GetBValue(cr) / 255.0,
      GetAValue(cr) / 255.0};
   
   CGColorRef color = CGColorCreate(rgbColorSpace, components);
   
   CGColorSpaceRelease(rgbColorSpace);
   
   return color;
}


BOOL mac_release_color(CGColorRef colorref)
{
   CGColorRelease(colorref);
    return TRUE;
}



HDC GetWindowDC(HWND hwnd)
{
   return GetDC(hwnd);
}

HDC GetDC(HWND hwnd)
{
    
    HDC hdc = new device_context;
    
    
    hdc->m_window = hwnd;
    hdc->m_cgcontext = get_nswindow_cgcontext(hwnd);
/*    hdc->m_windowPort = GetWindowPort(hwnd);
    GetPortBounds(hdc->m_windowPort, &hdc->m_portBounds);
    
    hdc->m_wasSwapped = QDSwapPort(hdc->m_windowPort, &hwnd->m_savedPort);
    
    
    /* ... QuickDraw Drawing Commands ... */
    // at windowPort
    
    
  /*  QDBeginCGContext(hdc->m_windowPort, &hdc->m_cgcontext);
    SyncCGContextOriginWithPort(hdc->m_cgcontext, hdc->m_windowPort);
    //ClipCGContextToRegion(cgContext, &portBounds, clippingRegion);
    //DisposeRgn(clippingRegion);
    //clippingRegion = NULL;
    
    /* ... Quartz Drawing Commands ... */
    
    
    hdc->m_cgcolorrefText = mac_create_color(0);
    hdc->m_cgcolorrefBk = mac_create_color(RGB(255, 255, 255));
    
    return hdc;
    
}


BOOL ReleaseDC(HWND hwnd, HDC hdc)
{

   if(hdc == NULL)
      return FALSE;
   
   /*QDEndCGContext(hdc->m_windowPort, &hdc->m_cgcontext);
   
   if(hdc->m_wasSwapped)
   {
      QDSwapPort(hdc->m_savedPort, &hdc->m_savedPort);
   }*/

   delete hdc;
   return TRUE;

}


BOOL GetClientRect(HWND hwnd, LPRECT lprect)
{
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
    
    if(!GetWindowRect(hwnd, lprect))
        return FALSE;
    
    lprect->right   -=  lprect->left;
    lprect->bottom  -=  lprect->top;
    lprect->left    =   0;
    lprect->top     =   0;
    
    return TRUE;
    
}


BOOL GetWindowRect(HWND hwnd, LPRECT lprect)
{
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
    
   return get_nswindow_rect(hwnd, lprect) ? 1 : 0;
    
    
}



int FillRect(HDC hdc, const RECT * lprc, HBRUSH hbr)
{
    
   CGRect rect;
   
   rect.origin.x     = lprc->left;
   rect.origin.y     = lprc->top;
   rect.size.width   = lprc->right - lprc->left;
   rect.size.height  = lprc->bottom - lprc->top;
   
   CGContextSetRGBFillColor(hdc->m_cgcontext, GetRValue(hbr->lbColor), GetGValue(hbr->lbColor), GetBValue(hbr->lbColor), GetAValue(hbr->lbColor));
    
   CGContextFillRect(hdc->m_cgcontext, rect);
   
   return 1;
}


HDC BeginPaint(HWND hwnd, PAINTSTRUCT * ps)
{

   HDC hdc = GetDC(hwnd);

   GetClientRect(hwnd, &ps->rcPaint);

   return hdc;

}


BOOL EndPaint(HWND hwnd, PAINTSTRUCT * ps)
{

   return ReleaseDC(hwnd, ps->hdc);

}


BOOL GetCursorPos(LPPOINT lpptCursor)
{
   
   HIPoint point;
   
   HICoordinateSpace space = kHICoordSpaceScreenPixel;
   
   HIGetMousePosition(space, NULL, &point);
   
   
   lpptCursor->x = point.x;
   lpptCursor->y = point.y;


   return TRUE;

}






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
BOOL SelectObject(HDC hdc, HGDIOBJ hgdiobj)
{
    return FALSE;
}
BOOL Rectangle(HDC hdc, int x1, int y1, int x2, int y2)
{
    return FALSE;
}
BOOL DeleteObject(HGDIOBJ hgdiobj)
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
BOOL SetBkMode(HDC hdc, int iMode)
{
    return FALSE;
}
BOOL DeleteDC(HDC hdc)
{
    return FALSE;
}
BOOL AlphaBlend(HDC hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, HDC hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, BLENDFUNCTION ftn)
{
    return FALSE;
}
BOOL GetObject(HGDIOBJ hgdiobj, int iSize, void * object)
{
    return FALSE;
}
BOOL GetTextExtentPoint(HDC hdc, const char * pszText, int iSize, SIZE * psize)
{
    return FALSE;
}



BOOL SetTextColor(HDC hdc, COLORREF crText)
{
   
   mac_release_color(hdc->m_cgcolorrefText);
   hdc->m_cgcolorrefText = mac_create_color(crText);
   return TRUE;
}

HBRUSH CreateSolidBrush(COLORREF cr)
{
    return NULL;
}

