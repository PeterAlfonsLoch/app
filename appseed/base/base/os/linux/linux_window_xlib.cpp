#include "framework.h"
#include "base/os/linux/linux_window_xlib.h"


window_xlib::window_xlib(::aura::application * papp) :
    object(papp),
    window_graphics(papp)
{

   m_window = NULL;

   m_pdc = NULL;

   m_pimage = NULL;

   //m_picture = NULL;

   //m_pictureWindow = NULL;

   //m_pixmap = NULL;

}


window_xlib::~window_xlib()
{
   ::aura::del(m_pdc);
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

   xdisplay d(window->display());

   m_mem.allocate(cyParam * m_iScan);

   m_pimage = XCreateImage(window->display(), window->visual(), window->m_iDepth, ZPixmap, 0, (char *) m_mem.get_data(), cxParam, cyParam, sizeof(COLORREF) * 8, m_iScan);

   ::aura::del(m_pdc);

   m_pdc = new device_context();

   XGCValues gcvalues;

   m_pdc->m_gc = XCreateGC(window->display(), window->window(), 0, &gcvalues);

   window_graphics::create_window_graphics(window, cxParam, cyParam, m_iScan);

//   if(m_picture != NULL)
//   {
//
//      XRenderFreePicture(window->display(), m_picture);
//
//   }
//
//   if(m_pictureWindow != NULL)
//   {
//
//      XRenderFreePicture(window->display(), m_picture);
//
//   }
//
//   if(m_pixmap != NULL)
//   {
//
//      XFreePixmap(window->display(), m_pixmap);
//
//   }
//
//   m_pixmap = XCreatePixmap(window->display(), window->window(),cxParam, cyParam,32);
//
//   m_pictureWindow = XRenderCreatePicture(window->display(), window->window(), XRenderFindStandardFormat(window->display(), PictStandardARGB32), 0, 0);
//
//   m_picture = XRenderCreatePicture(window->display(), m_pixmap, XRenderFindStandardFormat(window->display(), PictStandardARGB32), 0, 0);

}






void window_xlib::destroy_window_graphics()
{

   window_graphics::destroy_window_graphics();


}


void window_xlib::update_window(COLORREF * pOsBitmapData, int cxParam, int cyParam, int iStride)
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

   xdisplay d(m_window->display());

//   if(bTransferBuffer)
   {

      ::draw2d::copy_colorref(cxParam, cyParam, (COLORREF *) m_mem.get_data(), m_iScan, pOsBitmapData, iStride);

   }

   byte * pdata = (byte *) m_mem.get_data();

   int size = m_iScan * m_size.cy / sizeof(COLORREF);
   while(size > 0)
   {
      //if(pdata[3] != 0)
      {
         pdata[0] = pdata[0] * pdata[3] / 255;
         pdata[1] = pdata[1] * pdata[3] / 255;
         pdata[2] = pdata[2] * pdata[3] / 255;
      }
      pdata += 4;
      size--;
   }


   try
   {

/*      XColor xcolour;

      // I guess XParseColor will work here
      xcolour.red = 0;
      xcolour.green = 0;
      xcolour.blue = 0;
      xcolour.
      xcolour.flags = DoRed | DoGreen | DoBlue;
      XAllocColor(d, cmap, &xcolour);

      XSetForeground(d, gc, xcolour.pixel);
      XFillRectangle(d, w, gc, 0, 0, winatt.width, 30);
      XFlush(d);
      */

      /*XPutImage(m_window->display(), m_pixmap, m_pdc->m_gc, m_pimage, 0, 0, 0, 0, m_size.cx, m_size.cy);

      XRenderColor c;
      c.red = 0;
      c.green = 0;
      c.blue = 0;
      c.alpha = 0;

      XRenderFillRectangle(m_window->display(), PictOpSrc, m_pictureWindow, &c, 0, 0, m_size.cx, m_size.cy);


      XRenderComposite(m_window->display(), PictOpOver, m_picture, None, m_pictureWindow, 0, 0, 0, 0, 0, 0, m_size.cx, m_size.cy);*/


      XPutImage(m_window->display(), m_window->window(), m_pdc->m_gc, m_pimage, 0, 0, 0, 0, m_size.cx, m_size.cy);

   }
   catch(...)
   {


   }

}









void window_xlib::update_window()
{


   rect64 rectWindow;

//#if !NO_SCREEN_PRE_MULTIPLY_ALPHA
//   if (bTransferBuffer && pwnd->is_composite() && !m_bReduced)
//   {
//
//      m_bReduced = true;
//
//      m_spgraphics->SetViewportOrg(0, 0);
//
//      map();
//
//      //pre_multiply_alpha((unsigned int *) get_data(),m_size.cx,m_size.cy,m_size.cx * 4);
//
//      BYTE *dstR = (BYTE*)get_data();
//      BYTE *dstG = dstR + 1;
//      BYTE *dstB = dstR + 2;
//      BYTE *dstA = dstR + 3;
//      int64_t size = area() * 4;
//
//
//      // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255
//      //#if defined(_OPENMP)
//      //         #pragma omp parallel num_threads(3)
//      //                  {
//      //
//      //                     BYTE *dst = dstR + omp_get_thread_num();
//      //      #pragma omp parallel for
//      //                     for(index i = 0; i < size; i+=4)
//      //                     {
//      //                           dst[i] = LOBYTE(((int32_t)dst[i] * (int32_t)dstA[i]) >> 8);
//      //                     }
//      //                  }
//      //
//      ////#pragma omp parallel num_threads(4)
//      ////         {
//      ////
//      ////            if(omp_get_thread_num() == 3)
//      ////            {
//      ////               COLORREF *dst = get_data();
//      ////#pragma omp parallel for
//      ////               for(index i = 0; i < size; i+=4)
//      ////               {
//      ////                  if(dstA[i] <= 3)
//      ////                  {
//      ////                     dst[i>>2] = 0;
//      ////                  }
//      ////               }
//      ////            }
//      ////            else
//      ////            {
//      ////               BYTE *dst = dstR + omp_get_thread_num();
//      ////#pragma omp parallel for
//      ////               for(index i = 0; i < size; i+=4)
//      ////               {
//      ////                  if(dstA[i] > 3)
//      ////                  {
//      ////                     dst[i] = LOBYTE(((int32_t)dst[i] * (int32_t)dstA[i]) >> 8);
//      ////                  }
//      ////               }
//      ////            }
//      ////         }
//      //#else
//      //         for(index i = 0; i < size; i+=4)
//      //         {
//      //            dstR[i] = LOBYTE(((int32_t)dstR[i] * (int32_t)dstA[i]) >> 8);
//      //            dstG[i] = LOBYTE(((int32_t)dstG[i] * (int32_t)dstA[i]) >> 8);
//      //            dstB[i] = LOBYTE(((int32_t)dstB[i] * (int32_t)dstA[i]) >> 8);
//      //         }
//      //#endif
//      //
//   }
//#endif
//   rect rect(rectWindow);

   update_window(m_spdibBuffer->get_data(), m_spdibBuffer->m_size.cx, m_spdibBuffer->m_size.cy, m_spdibBuffer->m_iScan);

}




::draw2d::graphics * window_xlib::on_begin_draw()
{

   if (m_spdibBuffer.is_null())
   {

      m_spdibBuffer.alloc(allocer());

   }

   if(!m_spdibBuffer->create(m_pimpl->m_rectParentClient.size()))
   {

      return NULL;

   }

   if (m_window != m_pimpl->m_oswindow || cx != m_pimpl->m_rectParentClient.size().cx || cy != m_pimpl->m_rectParentClient.size().cy)
   {

      create_window_graphics(m_pimpl->m_oswindow, m_pimpl->m_rectParentClient.size().cx, m_pimpl->m_rectParentClient.size().cy, m_spdibBuffer->m_iScan);

   }

   return m_spdibBuffer->get_graphics();

}
