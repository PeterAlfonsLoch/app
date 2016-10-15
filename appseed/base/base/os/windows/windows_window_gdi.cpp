//#include "framework.h"
//#include "windows_window_gdi.h"



window_gdi::window_gdi(::aura::application * papp) :
   object(papp),
   window_graphics(papp),
   window_buffer(papp)
{

   m_hbitmap         = NULL;
   m_pcolorref       = NULL;
   m_hdc             = NULL;
   m_hwnd            = NULL;
   m_hMapFile        = NULL;
   m_pBuf            = NULL;
   m_hmutex          = NULL;


}


window_gdi::~window_gdi()
{

   if (m_hmutex != NULL)
   {

      if (WaitForSingleObject(m_hmutex, INFINITE) == WAIT_OBJECT_0)
      {

         if (m_pBuf != NULL)
         {

            UnmapViewOfFile(m_pBuf);

            m_pBuf = NULL;

         }

         if (m_hMapFile != NULL)
         {

            CloseHandle(m_hMapFile);

            m_hMapFile = NULL;

         }

         ::ReleaseMutex(m_hmutex);

      }

      ::CloseHandle(m_hmutex);

   }

}


CHAR szName[] = "Local\\ca2screen-%d";
CHAR szNameMutex[] = "Local\\ca2screenmutex-%d";
void window_gdi::create_window_graphics(int64_t cxParam, int64_t cyParam, int iStrideParam)
{

   synch_lock sl(m_pmutex);

   destroy_window_graphics();

   if (m_pimpl == NULL)
   {

      return;

   }

   HWND hwnd = (HWND) m_pimpl->get_os_data();

   if (hwnd == NULL)
   {

      return;

   }

   ZERO(m_bitmapinfo);

   int iStride = iStrideParam;

   m_bitmapinfo.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
   m_bitmapinfo.bmiHeader.biWidth         = (LONG)iStrideParam / 4;
   m_bitmapinfo.bmiHeader.biHeight        = (LONG) -cyParam;
   m_bitmapinfo.bmiHeader.biPlanes        = 1;
   m_bitmapinfo.bmiHeader.biBitCount      = 32;
   m_bitmapinfo.bmiHeader.biCompression   = BI_RGB;
   m_bitmapinfo.bmiHeader.biSizeImage     = (LONG) (iStrideParam * cyParam);

   m_hbitmap = CreateDIBSection(NULL, &m_bitmapinfo, DIB_RGB_COLORS, (void **) &m_pcolorref, NULL, 0);

   if (m_hmutex == NULL || m_hwnd != hwnd)
   {

      m_hwnd = hwnd;

      if (m_hmutex != NULL)
      {

         if (WaitForSingleObject(m_hmutex, INFINITE) == WAIT_OBJECT_0)
         {

            if (m_pBuf != NULL)
            {

               UnmapViewOfFile(m_pBuf);

               m_pBuf = NULL;

            }

            if (m_hMapFile != NULL)
            {

               CloseHandle(m_hMapFile);

               m_hMapFile = NULL;

            }

            ::ReleaseMutex(m_hmutex);

         }

         ::CloseHandle(m_hmutex);

      }

      char szNameMutex2[2048];

      sprintf(szNameMutex2, szNameMutex, (INT_PTR)hwnd);

      m_hmutex = ::CreateMutex(NULL, FALSE, szNameMutex2);

      if (::WaitForSingleObject(m_hmutex, INFINITE) == WAIT_OBJECT_0)
      {

         char szName2[2048];

         sprintf(szName2, szName, (INT_PTR)hwnd);

         m_hMapFile = CreateFileMapping(
            INVALID_HANDLE_VALUE,    // use paging file
            NULL,                    // default security
            PAGE_READWRITE,          // read/write access
            0,                       // maximum object size (high-order DWORD)
            8192 * 4096 * 4,                // maximum object size (low-order DWORD)
            szName2);                 // name of mapping object

         if (m_hMapFile == NULL)
         {

            ::ReleaseMutex(m_hmutex);

            ::CloseHandle(m_hmutex);

         }
         else
         {

            m_pBuf = (LPTSTR)MapViewOfFile(m_hMapFile,   // handle to map object
               FILE_MAP_ALL_ACCESS, // read/write permission
               0,
               0,
               8192 * 4096 * 4);

            if (m_pBuf == NULL)
            {

               CloseHandle(m_hMapFile);

               ::ReleaseMutex(m_hmutex);

               ::CloseHandle(m_hmutex);

            }

         }

         ReleaseMutex(m_hmutex);

      }

   }

   m_hdc = ::CreateCompatibleDC(NULL);

   m_hbitmapOld = (HBITMAP) ::SelectObject(m_hdc, m_hbitmap);

   m_hdcScreen = ::GetDCEx(hwnd,NULL,DCX_WINDOW);

   if(m_hdcScreen == NULL)
   {

      // If it has failed to get interaction_impl
      // owned device context, try to get
      // a device context from the cache.
      //m_hdcScreen = ::GetDCEx(interaction_impl,NULL,DCX_CACHE | DCX_CLIPSIBLINGS | DCX_WINDOW);
      m_hdcScreen = ::GetDCEx(hwnd,NULL,DCX_CACHE | DCX_WINDOW);

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

   window_graphics::create_window_graphics(cxParam, cyParam, iStride);

}


void window_gdi::destroy_window_graphics()
{

   synch_lock sl(m_pmutex);

   if(m_hdcScreen != NULL)
   {

      ::ReleaseDC(m_pimpl->m_oswindow,m_hdcScreen);

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

   

   window_graphics::destroy_window_graphics();

}

// ::SetWindowPos(get_handle(), (oswindow)z, x, y, cx, cy, nFlags | SWP_NOREDRAW);

void window_gdi::update_window(COLORREF * pcolorref,int cxParam,int cyParam,int iStride)
{

   synch_lock sl(m_pmutex);

   if (cxParam <= 0 || cyParam <= 0)
   {

      return;

   }

   int cx = MIN(cxParam, m_cx);

   int cy = MIN(cyParam, m_cy);

   rect rectWindow = m_pimpl->m_rectParentClient;

   rectWindow.right = rectWindow.left + cx;
   rectWindow.bottom = rectWindow.top + cy;

   bool bLayered = (::GetWindowLong(m_pimpl->m_oswindow,GWL_EXSTYLE) & WS_EX_LAYERED) != 0;

   try
   {

      ::draw2d::copy_colorref(cx,cy,m_pcolorref,m_iScan,pcolorref,iStride);

   }
   catch(...)
   {

   }

   //::GdiFlush();

   if (m_pBuf != NULL)
   {

      if (::WaitForSingleObject(m_hmutex, INFINITE) == WAIT_OBJECT_0)
      {

         try
         {



            int64_t * p = (int64_t *)m_pBuf;

            *p++ = cx;
            *p++ = cy;
            *p++ = m_iScan;

            ::draw2d::copy_colorref(cx, cy, (COLORREF *)p, sizeof(COLORREF) * cx, m_pcolorref, m_iScan);

            //memset(p, 0, sizeof(COLORREF) * cxParam *cyParam / 2);

         }
         catch (...)
         {

         }

         ReleaseMutex(m_hmutex);

      }

   }


   if(bLayered)
   {

      POINT pt;

      pt.x = rectWindow.left;

      pt.y = rectWindow.top;

      SIZE sz;

      sz.cx = width(&rectWindow);

      sz.cy = height(&rectWindow);

      POINT ptSrc = { 0 };

      BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };


      bool bOk = ::UpdateLayeredWindow(m_pimpl->m_oswindow, m_hdcScreen, &pt, &sz, m_hdc, &ptSrc, RGB(0, 0, 0), &blendPixelFunction, ULW_ALPHA) != FALSE;

      {

         RECT r2;

         GetWindowRect(m_pimpl->m_oswindow, &r2);

         RECT64 r64;

         ::copy(&r64, &r2);

         if (!::is_equal(&r64, &m_pimpl->m_rectParentClient))
         {

            ::SetWindowPos(m_pimpl->m_oswindow, NULL,
               m_pimpl->m_rectParentClient.left,
               m_pimpl->m_rectParentClient.top,
               m_pimpl->m_rectParentClient.width(),
               m_pimpl->m_rectParentClient.height(), SWP_NOZORDER | SWP_NOREDRAW);

         }

      }

//      GdiFlush();

   }
   else
   {

      ::BitBlt(m_hdcScreen, 0, 0, m_cx, m_cy,  m_hdc, 0, 0, SRCCOPY);

   }

}


