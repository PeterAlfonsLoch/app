//#include "framework.h"
//#include "windows_window_gdi.h"



window_gdi::window_gdi(::aura::application * papp) :
   object(papp),
   window_graphics(papp)
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


   //::draw2d::dib * pdi = m_spdib;

   //if(cxParam < cx && cyParam < cy)
   // return;

   //cxParam += 100;
   //cyParam += 100;

   destroy_window_graphics();


   ZERO(m_bitmapinfo);


   //int iStride = (int32_t) (cxParam * sizeof(COLORREF));

   int iStride = iStrideParam;

   m_bitmapinfo.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
   m_bitmapinfo.bmiHeader.biWidth         = (LONG)iStrideParam / 4;
   m_bitmapinfo.bmiHeader.biHeight        = (LONG) -cyParam;
   m_bitmapinfo.bmiHeader.biPlanes        = 1;
   m_bitmapinfo.bmiHeader.biBitCount      = 32;
   m_bitmapinfo.bmiHeader.biCompression   = BI_RGB;
   m_bitmapinfo.bmiHeader.biSizeImage     = (LONG) (iStrideParam * cyParam);



   m_hbitmap = CreateDIBSection(NULL, &m_bitmapinfo, DIB_RGB_COLORS, (void **) &m_pcolorref, NULL, 0);

   m_hdc = ::CreateCompatibleDC(NULL);

   m_hbitmapOld = (HBITMAP) ::SelectObject(m_hdc, m_hbitmap);


   if(interaction_impl == NULL)
      return;

   //m_hdcScreen = ::GetDCEx(interaction_impl,NULL,DCX_CLIPSIBLINGS | DCX_WINDOW);

   m_hdcScreen = ::GetDCEx(interaction_impl,NULL,DCX_WINDOW);



   if(m_hdcScreen == NULL)
   {

      // If it has failed to get interaction_impl
      // owned device context, try to get
      // a device context from the cache.
      //m_hdcScreen = ::GetDCEx(interaction_impl,NULL,DCX_CACHE | DCX_CLIPSIBLINGS | DCX_WINDOW);
      m_hdcScreen = ::GetDCEx(interaction_impl,NULL,DCX_CACHE | DCX_WINDOW);

      // If no device context could be retrieved,
      // nothing can be drawn at the screen.
      // The function failed.
      if(m_hdcScreen == NULL)
         return;

      m_bOwnDC = false;

   }
   else
   {

      m_bOwnDC = true;

   }

   m_hwnd =interaction_impl;

   window_graphics::create_window_graphics(interaction_impl, cxParam, cyParam, iStride);

}




void window_gdi::destroy_window_graphics()
{

   if(m_hdcScreen != NULL)
   {

      ::ReleaseDC(m_hwnd,m_hdcScreen);

   }

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

   //m_pcolorref = NULL;

   m_hwnd = NULL;

   window_graphics::destroy_window_graphics();


}


void window_gdi::update_window()
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




void window_gdi::update_window(COLORREF * pcolorref,int cxParam,int cyParam,int iStride)
{

   if (cxParam <= 0 || cyParam <= 0)
      return;




   rect rectWindow = m_pimpl->m_rectParentClient;

   //GetWindowRect(m_hwnd, &rectWindow);

   bool bLayered = (::GetWindowLong(m_hwnd,GWL_EXSTYLE) & WS_EX_LAYERED) != 0;

   //if(bTransferBuffer)
   //{

   //   ::SelectClipRgn(m_hdcScreen,NULL);

   //   ::SelectClipRgn(m_hdc,NULL);


   //   RECT rectOutputClient;

   //   rectOutputClient = rect;

   //   rectOutputClient.left   -= rect.left;
   //   rectOutputClient.right  -= rect.left;
   //   rectOutputClient.top    -= rect.top;
   //   rectOutputClient.bottom -= rect.top;

   try
   {

      ::draw2d::copy_colorref(cxParam,cyParam,m_pcolorref,scan,pcolorref,iStride);

   }
   catch(...)
   {

   }

      //   /*   for (int i = 1920 * 32; i < 1920 * 64; i++)
   //      {
   //      m_pcolorref[i] = ARGB(255, 127, 255, 127);
   //      }*/

   //   ::GdiFlush();

   //   ::SetViewportOrgEx(m_hdcScreen,0,0,NULL);


   //}

   if(bLayered)
   {

      POINT pt;

      pt.x = rectWindow.left;

      pt.y = rectWindow.top;

      SIZE sz;

      sz.cx = width(&rectWindow);

      sz.cy = height(&rectWindow);

      POINT ptSrc = { 0 };

      //if(sz.cx < 800)
      //{

      //   ::SwitchToThread();

      //}

      BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

      bool bOk = ::UpdateLayeredWindow(m_hwnd, m_hdcScreen, &pt, &sz, m_hdc, &ptSrc, RGB(0, 0, 0), &blendPixelFunction, ULW_ALPHA) != FALSE;

      //::SwitchToThread();


   }
   else
   {

      ::BitBlt(m_hdcScreen, 0, 0, cx, cy,  m_hdc, 0, 0, SRCCOPY);

   }


}



::draw2d::graphics * window_gdi::on_begin_draw()
{

   if (m_spdibBuffer.is_null())
   {

      m_spdibBuffer.alloc(allocer());

   }

   if(!m_spdibBuffer->create(m_pimpl->m_rectParentClient.size()))
   {

      return NULL;

   }

   if (m_hwnd != m_pimpl->m_oswindow || cx != m_pimpl->m_rectParentClient.size().cx || cy != m_pimpl->m_rectParentClient.size().cy)
   {

      create_window_graphics(m_pimpl->m_oswindow, m_pimpl->m_rectParentClient.size().cx, m_pimpl->m_rectParentClient.size().cy, m_spdibBuffer->m_iScan);

   }

   return m_spdibBuffer->get_graphics();

}