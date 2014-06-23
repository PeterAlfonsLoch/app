#include "framework.h"
#ifdef WINDOWSEX
#include "base/os/windows/windows_window_gdi.h"
#endif

window_graphics::window_graphics()
{

   cx = 0;
   cy = 0;

}


window_graphics::~window_graphics()
{

   destroy();

}


void window_graphics::create(oswindow interaction_impl, int64_t cxParam, int64_t cyParam, int iStride)
{

   cx = (int32_t)cxParam;
   cy = (int32_t)cyParam;
   scan = (int32_t)iStride;

}


void window_graphics::destroy()
{

   cx = 0;
   cy = 0;

}


void window_graphics::update_window(window_graphics * & pdata, oswindow interaction_impl, COLORREF * pOsBitmapData, LPCRECT lpcrect, int iStride)
{

   if (pdata == NULL || (pdata->cx != width(lpcrect) || pdata->cy != height(lpcrect)))
   {

      if (pdata == NULL)
      {

#ifdef WINDOWSEX

         pdata = new window_gdi();

#elif defined(LINUX)

         pdata = new window_xlib();

#endif

      }

      if (pdata != NULL)
      {

         pdata->create(interaction_impl, width(lpcrect), height(lpcrect), iStride);

      }

   }


   if (pdata != NULL)
   {

      pdata->update_window(interaction_impl, pOsBitmapData, lpcrect, iStride);

   }

}


void window_graphics::update_window(oswindow interaction_impl, COLORREF * pOsBitmapData, LPCRECT lpcrect, int iStride)
{

   UNREFERENCED_PARAMETER(interaction_impl);
   UNREFERENCED_PARAMETER(pOsBitmapData);
   UNREFERENCED_PARAMETER(lpcrect);
   UNREFERENCED_PARAMETER(iStride);

}


void window_graphics::copy_colorref(COLORREF * pcolorrefDst, COLORREF * pcolorrefSrc, int iStrideSrc)
{

   if (iStrideSrc <= 0)
   {

      iStrideSrc = cx * sizeof(COLORREF);

   }

   if (scan == iStrideSrc)
   {

      memcpy(pcolorrefDst, pcolorrefSrc, cy * scan);

   }
   else
   {

      int wsrc = iStrideSrc / sizeof(COLORREF);
      int wdst = scan / sizeof(COLORREF);
      int cw = cx * sizeof(COLORREF);


      COLORREF * psrc = pcolorrefSrc;
      COLORREF * pdst = pcolorrefDst;

      for (int i = 0; i < cy; i++)
      {

         memcpy(pdst, psrc, cw);

         pdst += wdst;

         psrc += wsrc;

      }

   }

}
