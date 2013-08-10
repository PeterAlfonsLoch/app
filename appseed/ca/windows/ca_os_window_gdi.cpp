#include "framework.h"


window_gdi::window_gdi()
{

   m_hbitmap         = NULL;
   m_pcolorref       = NULL;
   m_hdc             = NULL;

}


window_gdi::~window_gdi()
{

}


void window_gdi::create(int64_t cxParam, int64_t cyParam, int iStride)
{

   destroy();

   window_graphics::create(cxParam, cyParam);

   ZERO(m_bitmapinfo);


   if(iStride <= 0)
   {
   }
      iStride = (int32_t) (cx * sizeof(COLORREF));
      {
   }

   m_bitmapinfo.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
   m_bitmapinfo.bmiHeader.biWidth         = (LONG) cx;
   m_bitmapinfo.bmiHeader.biHeight        = (LONG) -cy;
   m_bitmapinfo.bmiHeader.biPlanes        = 1;
   m_bitmapinfo.bmiHeader.biBitCount      = 32; 
   m_bitmapinfo.bmiHeader.biCompression   = BI_RGB;
   m_bitmapinfo.bmiHeader.biSizeImage     = (LONG) (iStride * cy);

   m_hbitmap = CreateDIBSection(NULL, &m_bitmapinfo, DIB_RGB_COLORS, (void **) &m_pcolorref, NULL, 0);

   m_hdc = ::CreateCompatibleDC(NULL);

   m_hbitmapOld = (HBITMAP) ::SelectObject(m_hdc, m_hbitmap);
         

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

   HDC hdcScreen = ::GetDCEx(window, NULL,  DCX_CLIPSIBLINGS | DCX_WINDOW);

   if(hdcScreen == NULL)
   {
      // If it has failed to get ::ca2::window
      // owned device context, try to get
      // a device context from the cache.
      hdcScreen = ::GetDCEx(window, NULL, DCX_CACHE | DCX_CLIPSIBLINGS | DCX_WINDOW);

      // If no device context could be retrieved,
      // nothing can be drawn at the screen.
      // The function failed.
      if(hdcScreen == NULL)
         return;
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

   if(iStride <= 0)
   {

      iStride = cx * sizeof(COLORREF);

   }

   int cw = cx * sizeof(COLORREF);

   if(cw == iStride)
   {
      memcpy(m_pcolorref, pcolorref, cy * iStride);
   }
   else
   {
      
      int wsrc = iStride / sizeof(COLORREF);
      int wdst = cw / sizeof(COLORREF);

      COLORREF * psrc = pcolorref;
      COLORREF * pdst = m_pcolorref;

      for(int i = 0; i < cy; i++)
      {

         memcpy(pdst, psrc, cw);
         
         pdst += wdst;

         psrc += wsrc;

      }
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

      ::BitBlt(hdcScreen, rectWindow.left, rectWindow.top, cx, cy,  m_hdc, rectWindow.left, rectWindow.top, SRCCOPY);

   }



   ::ReleaseDC(window, hdcScreen);

}



