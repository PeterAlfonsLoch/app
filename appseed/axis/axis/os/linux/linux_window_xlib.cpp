#include "framework.h"
#include "axis/os/linux/linux_window_xlib.h"


window_xlib::window_xlib()
{

   m_window = NULL;

   m_pdc = NULL;

   m_pimage = NULL;

   m_picture = NULL;

   m_pictureWindow = NULL;

   m_pixmap = NULL;

}


window_xlib::~window_xlib()
{

}


HDC GetDC(oswindow window);


void window_xlib::create_window_graphics(oswindow window, int64_t cxParam, int64_t cyParam, int iStrideParam)
{

   if(cxParam <= 0 || cyParam <= 0)
      return;

   if(window == NULL)
      return;

   destroy_window_graphics();

//   single_lock sl(&user_mutex(), true);

   m_window = window;

   m_size.cx = cxParam;

   m_size.cy = cyParam;

   //if(iStrideParam < 0 || iStrideParam < (m_size.cx * sizeof(COLORREF)))
   {

      m_iScan = m_size.cx * sizeof(COLORREF);

   }
   /*else
   {

      m_iScan = ((iStrideParam + sizeof(COLORREF) - 1) & ~sizeof(COLORREF));

   }*/

   m_mem.allocate(cyParam * m_iScan);

   m_pimage = XCreateImage(window->display(), window->visual(), window->m_iDepth, ZPixmap, 0, (char *) m_mem.get_data(), cxParam, cyParam, sizeof(COLORREF) * 8, m_iScan);

   m_pdc = new device_context();

   XGCValues gcvalues;

   m_pdc->m_gc = XCreateGC(window->display(), window->window(), 0, &gcvalues);

   window_graphics::create_window_graphics(window, cxParam, cyParam, m_iScan);

   if(m_picture != NULL)
   {

      XRenderFreePicture(window->display(), m_picture);

   }

   if(m_pictureWindow != NULL)
   {

      XRenderFreePicture(window->display(), m_picture);

   }

   if(m_pixmap != NULL)
   {

      XFreePixmap(window->display(), m_pixmap);

   }

   m_pixmap = XCreatePixmap(window->display(), window->window(),cxParam, cyParam,32);

   m_pictureWindow = XRenderCreatePicture(window->display(), window->window(), XRenderFindStandardFormat(window->display(), PictStandardARGB32), 0, 0);

   m_picture = XRenderCreatePicture(window->display(), m_pixmap, XRenderFindStandardFormat(window->display(), PictStandardARGB32), 0, 0);

}






void window_xlib::destroy_window_graphics()
{

   window_graphics::destroy_window_graphics();


}


void window_xlib::update_window(COLORREF * pOsBitmapData, const RECT & lpcrect, int cxParam, int cyParam, int iStride, bool bTransferBuffer)
{

   //single_lock sl(&user_mutex());

   if(m_pdc == NULL)
      return;

   if(m_window == NULL)
      return;

   if(m_pimage == NULL)
      return;

   if(pOsBitmapData == NULL)
      return;

   if(m_size.area() <= 0)
      return;

    if(bTransferBuffer)
    {

      ::draw2d::copy_colorref(cxParam, cyParam, (COLORREF *) m_mem.get_data(), m_iScan, pOsBitmapData, iStride);

    }

   try
   {

      XPutImage(m_window->display(), m_pixmap, m_pdc->m_gc, m_pimage, 0, 0, 0, 0, m_size.cx, m_size.cy);

      XRenderComposite(m_window->display(), PictOpOver, m_picture, None,
                         m_pictureWindow, 0, 0, 0, 0, 0, 0,
                         m_size.cx, m_size.cy);

   }
   catch(...)
   {


   }

}



