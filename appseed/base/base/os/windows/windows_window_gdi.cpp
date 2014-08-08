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


void window_gdi::create_window_graphics(oswindow interaction_impl, int64_t cxParam, int64_t cyParam, int iStrideParam)
{

   destroy_window_graphics();


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

   window_graphics::create_window_graphics(interaction_impl, cxParam, cyParam, iStride);

}




void window_gdi::destroy_window_graphics()
{

   if(m_hdc != NULL)
   {

      ::SelectObject(m_hdc, m_hbitmapOld);

      ::DeleteDC(m_hdc);

      m_hdc = NULL;

      m_hbitmapOld = NULL;

   }


   if(m_hbitmap != NULL)
   {
      ::DeleteObject(m_hbitmap);

      m_hbitmap = NULL;

   }

   m_pcolorref = NULL;

   window_graphics::destroy_window_graphics();


}


void window_gdi::update_window(oswindow interaction_impl, COLORREF * pcolorref, const RECT & rect, int iStride)
{

   if (width(rect) <= 0 || height(rect) <= 0)
      return;

   if (interaction_impl == NULL)
      return;

   HDC hdcScreen = ::GetDCEx(interaction_impl, NULL,  DCX_CLIPSIBLINGS | DCX_WINDOW);

   bool bOwnDC;

   if(hdcScreen == NULL)
   {

      // If it has failed to get interaction_impl
      // owned device context, try to get
      // a device context from the cache.
      hdcScreen = ::GetDCEx(interaction_impl, NULL, DCX_CACHE | DCX_CLIPSIBLINGS | DCX_WINDOW);

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

   ::SelectClipRgn(m_hdc, NULL);

   RECT rectWindow;
   
   rectWindow =rect;

   RECT rectOutputClient;

   rectOutputClient = rect;
   
   rectOutputClient.left   -= rect.left;
   rectOutputClient.right  -= rect.left;
   rectOutputClient.top    -= rect.top;
   rectOutputClient.bottom -= rect.top;

   bool bLayered = (::GetWindowLong(interaction_impl, GWL_EXSTYLE) & WS_EX_LAYERED) != 0;

   try
   {

      copy_colorref(m_pcolorref, pcolorref, iStride);

   }
   catch (...)
   {

   }

/*   for (int i = 1920 * 32; i < 1920 * 64; i++)
   {
      m_pcolorref[i] = ARGB(255, 127, 255, 127);
   }*/

   ::GdiFlush();

   ::SetViewportOrgEx(hdcScreen, 0, 0, NULL);

   if(bLayered)
   {

      POINT pt;

      pt.x = rect.left;
      
      pt.y = rect.top;

      SIZE sz;

      sz.cx = width(&rectWindow);

      sz.cy = height(&rectWindow);
      
      POINT ptSrc = { 0 };

      BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

      bool bOk = ::UpdateLayeredWindow(interaction_impl, hdcScreen, &pt, &sz, m_hdc, &ptSrc, RGB(0, 0, 0), &blendPixelFunction, ULW_ALPHA) != FALSE;


   }
   else
   {

      ::BitBlt(hdcScreen, 0, 0, cx, cy,  m_hdc, 0, 0, SRCCOPY);

   }

   ::ReleaseDC(interaction_impl, hdcScreen);

}



