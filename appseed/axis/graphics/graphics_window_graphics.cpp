#include "framework.h"
#ifdef WINDOWSEX
#include "axis/os/windows/windows_window_gdi.h"
#elif defined (LINUX)
#include "axis/os/linux/linux_window_xlib.h"
#endif

window_graphics::window_graphics()
{

   cx = 0;
   cy = 0;

}


window_graphics::~window_graphics()
{

   destroy_window_graphics();

}


void window_graphics::create_window_graphics(oswindow interaction_impl, int64_t cxParam, int64_t cyParam, int iStride)
{

   cx = (int32_t)cxParam;
   cy = (int32_t)cyParam;
   scan = (int32_t)iStride;

}


void window_graphics::destroy_window_graphics()
{

   cx = 0;
   cy = 0;

}


void window_graphics::update_window(window_graphics * & pdata, oswindow interaction_impl, COLORREF * pOsBitmapData, const RECT & rect, int iStride)
{

   if (pdata == NULL || (pdata->cx != width(rect) || pdata->cy != height(rect)))
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

         pdata->create_window_graphics(interaction_impl, width(rect), height(rect), iStride);

      }

   }


   if (pdata != NULL)
   {

      pdata->update_window(pOsBitmapData, rect, iStride);

   }

}


void window_graphics::update_window(COLORREF * pOsBitmapData, const RECT & rect, int iStride)
{

   UNREFERENCED_PARAMETER(pOsBitmapData);
   UNREFERENCED_PARAMETER(rect);
   UNREFERENCED_PARAMETER(iStride);

}


void window_graphics::copy_colorref(int cxParam, int cyParam, COLORREF * pcolorrefDst, COLORREF * pcolorrefSrc, int iStrideSrc)
{

   if (iStrideSrc <= 0)
   {

      iStrideSrc = cxParam * sizeof(COLORREF);

   }

   if (scan == iStrideSrc)
   {

      memcpy(pcolorrefDst,pcolorrefSrc,cyParam * scan);

   }
   else
   {

      int wsrc = iStrideSrc / sizeof(COLORREF);
      int wdst = scan / sizeof(COLORREF);
      int cw = cxParam * sizeof(COLORREF);


      COLORREF * psrc = pcolorrefSrc;
      COLORREF * pdst = pcolorrefDst;

      for(int i = 0; i < cyParam; i++)
      {

         memcpy(pdst, psrc, cw);

         pdst += wdst;

         psrc += wsrc;

      }

   }

}
