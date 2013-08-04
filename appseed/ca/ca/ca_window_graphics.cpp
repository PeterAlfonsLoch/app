#include "framework.h"


window_graphics::window_graphics()
{

   cx = 0;
   cy = 0;

}


window_graphics::~window_graphics()
{

   destroy();

}


void window_graphics::create(int64_t cxParam, int64_t cyParam)
{

   cx = (int32_t) cxParam;
   cy = (int32_t) cyParam;

}


void window_graphics::destroy()
{

   cx = 0;
   cy = 0;

}


void window_graphics::update_window(window_graphics * & pdata, oswindow window, COLORREF * pcolorref, LPCRECT lpcrect)
{

   if(pdata == NULL || (pdata->cx != width(lpcrect) || pdata->cy != height(lpcrect)))
   {

      if(pdata == NULL)
      {

#ifdef WINDOWSEX

         pdata = new window_gdi();

#endif

      }

      if(pdata != NULL)
      {
         
         pdata->create(width(lpcrect), height(lpcrect));

      }

   }


   if(pdata != NULL)
   {

      pdata->update_window(window, pcolorref, lpcrect);

   }

}


void window_graphics::update_window(oswindow window, COLORREF * pcolorref, LPCRECT lpcrect)
{

   UNREFERENCED_PARAMETER(window);
   UNREFERENCED_PARAMETER(pcolorref);

}