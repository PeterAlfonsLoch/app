#include "framework.h"
#include "windows_window_gdi.h"


window_gdi::window_gdi()
{

   m_hbitmap         = NULL;
   m_pcolorref       = NULL;
   m_hdc             = NULL;

}


window_gdi::~window_gdi()
{

}


void window_gdi::create(oswindow window, int64_t cxParam, int64_t cyParam, int iStrideParam)
{

   destroy();


   ZERO(m_bitmapinfo);


   int iStride = (int32_t) (cxParam * sizeof(COLORREF));

   m_bitmapinfo.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
   m_bitmapinfo.bmiHeader.biWidth         = (LONG) cxParam;
   m_bitmapinfo.bmiHeader.biHeight        = (LONG) -cyParam;
   m_bitmapinfo.bmiHeader.biPlanes        = 1;
   m_bitmapinfo.bmiHeader.biBitCount      = 32; 
   m_bitmapinfo.bmiHeader.biCompression   = BI_RGB;
   m_bitmapinfo.bmiHeader.biSizeImage     = (LONG) (iStride * cyParam);

   m_hbitmap = CreateDIBSection(NULL, &m_bitmapinfo, DIB_RGB_COLORS, (void **) &m_pcolorref, NULL, 0);

   m_hdc = ::CreateCompatibleDC(NULL);

   m_hbitmapOld = (HBITMAP) ::SelectObject(m_hdc, m_hbitmap);

   window_graphics::create(window, cxParam, cyParam, iStride);

}




void window_gdi::destroy()
{

   if(m_hdc != NULL)
   {

      ::SelectObject(m_hdc, m_hbitmapOld);

      ::DeleteDC(m_hdc);

   }


   if(m_hbitmap != NULL)
   {
      ::DeleteObject(m_hbitmap);

   }

   window_graphics::destroy();


}


void window_gdi::update_window(oswindow window, COLORREF * pcolorref, LPCRECT lpcrect, int iStride)
{

   if (width(lpcrect) <= 0 || height(lpcrect) <= 0)
      return;

   if (window == NULL)
      return;

   HDC hdcScreen = ::GetDCEx(window, NULL,  DCX_CLIPSIBLINGS | DCX_WINDOW);

   bool bOwnDC;

   if(hdcScreen == NULL)
   {

      // If it has failed to get window
      // owned device context, try to get
      // a device context from the cache.
      hdcScreen = ::GetDCEx(window, NULL, DCX_CACHE | DCX_CLIPSIBLINGS | DCX_WINDOW);

      // If no device context could be retrieved,
      // nothing can be drawn at the screen.
      // The function failed.
      if(hdcScreen == NULL)
         return;

      bOwnDC = false;

   }
   else
   {

      bOwnDC = true;

   }


   ::SelectClipRgn(hdcScreen, NULL);

   RECT rectWindow;
   
   rectWindow = *lpcrect;

   RECT rectOutputClient;

   rectOutputClient = *lpcrect;
   
   rectOutputClient.left   -= lpcrect->left;
   rectOutputClient.right  -= lpcrect->left;
   rectOutputClient.top    -= lpcrect->top;
   rectOutputClient.bottom -= lpcrect->top;

   bool bLayered = (::GetWindowLong(window, GWL_EXSTYLE) & WS_EX_LAYERED) != 0;

   try
   {
      copy_colorref(m_pcolorref, pcolorref, iStride);
   }
   catch (...)
   {

   }

   ::GdiFlush();

   ::SetViewportOrgEx(hdcScreen, 0, 0, NULL);

   if(bLayered)
   {

      POINT pt;

      pt.x = lpcrect->left;
      
      pt.y = lpcrect->top;

      SIZE sz;

      sz.cx = width(&rectWindow);

      sz.cy = height(&rectWindow);
      
      POINT ptSrc = { 0 };

      BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

      bool bOk = ::UpdateLayeredWindow(window, hdcScreen, &pt, &sz, m_hdc, &ptSrc, RGB(0, 0, 0), &blendPixelFunction, ULW_ALPHA) != FALSE;


   }
   else
   {

      ::BitBlt(hdcScreen, 0, 0, cx, cy,  m_hdc, 0, 0, SRCCOPY);

   }

   ::ReleaseDC(window, hdcScreen);

}



