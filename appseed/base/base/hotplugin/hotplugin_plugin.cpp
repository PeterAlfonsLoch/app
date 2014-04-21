#include "framework.h"

#undef new

#if defined(LINUX) || defined(ANDROID) || defined(SOLARIS)
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif


#ifdef LINUX
#include "base/os/linux/linux_cross_win_gdi_internal.h"
#elif defined(ANDROID)
#include "base/os/android/android_cross_win_gdi_internal.h"
#endif


#ifdef WINDOWSEX
#include <gdiplus.h>
#endif


//void fastblur(uint32_t * pdata, int32_t w, int32_t h, int32_t radius);


namespace hotplugin
{


   plugin::plugin(sp(base_application) papp) :
      element(papp),
      ::simple_ui::style(papp),
      ::simple_ui::interaction(papp),
      ::os::simple_ui(papp)
   {

      m_phost           = NULL;
      m_bInitialized    = false;
      m_bOk             = false;
      m_rect.left       = 0;
      m_rect.top        = 0;
      m_rect.bottom     = 0;
      m_rect.right      = 0;



      m_strStatus       = "Thank you";

      m_bReload         = false;
      m_bInstalling     = false;

      m_ptCursorPhase.x = 0;
      m_ptCursorPhase.y = 0;

      m_eschema         = schema_normal;


   }


   plugin::~plugin()
   {
      free_memory();
#if !defined(MACOS) && !defined(LINUX) && !defined(METROWIN) && !defined(ANDROID) && !defined(SOLARIS)
      if(m_pbitmap != NULL)
         delete (Gdiplus::Bitmap *) m_pbitmap;
      if(m_pcolorref != NULL)
         memory_free_dbg(m_pcolorref, 0);
#endif
      //delete m_pinfo;
   }

   bool plugin::open_url(const char * psz)
   {

      if(m_phost != NULL)
      {

         return m_phost->open_url(psz);

      }

      return false;

   }


   bool plugin::reload_plugin()
   {
      if(m_phost != NULL)
      {
         return m_phost->reload_plugin();
      }
      return false;
   }

   string plugin::get_host_location_url()
   {
      if(m_phost != NULL)
      {
         return m_phost->get_host_location_url();
      }
      return "";
   }

   void plugin::redraw()
   {
      if(m_phost != NULL)
      {
         m_phost->redraw();
      }
   }

   void plugin::post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
      if(m_phost != NULL)
      {
         m_phost->post_message(uiMessage, wparam, lparam);
      }
   }

   oswindow plugin::get_host_window()
   {
      if(m_phost != NULL)
      {
         return m_phost->get_host_window();
      }
      return NULL;
   }

   // ca.dll-absence-(ca.dll-delay-load)-safe
   void plugin::get_window_rect(LPRECT lprect)
   {

      *lprect = m_rect;

   }

   void plugin::set_window_rect(LPCRECT lpcrect)
   {

      m_rect = *lpcrect;

   }

   void plugin::set_memory(void * puchMemory, ::count c)
   {
      if(m_phost != NULL)
      {
         m_phost->set_memory(puchMemory, c);
      }
   }

   void plugin::append_memory(void * puchMemory, ::count c)
   {
      if(m_phost != NULL)
      {
         m_phost->append_memory(puchMemory, c);
      }
   }

   ::count plugin::get_memory_length()
   {
      if(m_phost != NULL)
      {
         return m_phost->get_memory_length();
      }
      return 0;
   }

   ::count plugin::read_memory(void * puchMemory, ::count c)
   {
      if(m_phost != NULL)
      {
         return m_phost->read_memory(puchMemory, c);
      }
      return 0;
   }

   void plugin::free_memory()
   {
   }

   void plugin::on_paint(::draw2d::graphics * pgraphics, LPCRECT lprect)
   {

      on_bare_paint(pgraphics, lprect);

   }


#ifdef WINDOWS

/*   LRESULT plugin::message_handler(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
      return 0;
   }*/

#else

   int32_t plugin::message_handler(XEvent * pevent)
   {
      return 0;
   }

#endif


   int32_t plugin::start_ca2_system()
   {
      return -1;
   }

   bool plugin::is_ok()
   {
      return m_bOk;
   }

   void plugin::set_ready()
   {

      m_bOk = true;

      if(m_bOk && m_phost != NULL && m_phost->is_ok())
      {

         on_ready();

      }
      else if(m_phost != NULL)
      {

#ifdef WINDOWSEX

         ::PostMessage(m_phost->::small_ipc_channel::m_oswindow, WM_USER + 100, 3, 1);

#else

         throw "not implemented";

#endif

      }

   }

   void plugin::on_ready()
   {
   }

   bool plugin::initialize()
   {
      return true;
   }

   bool plugin::finalize()
   {
      return true;
   }

   /*double cos_prec_dup(double x,double prec)
   {
   double t , s ;
   int32_t p;
   p = 0;
   s = 1.0;
   t = 1.0;
   while(fabs(t/s) > prec)
   {
   p++;
   t = (-t * x * x) / ((2 * p - 1) * (2 * p));
   s += t;
   }
   return s;
   }*/

   double sin_dup(double x);

   double cos_dup(double x)
   {

      double sin = sin_dup(x / 2.0);

      return 1.0 - 2.0 * sin * sin;

   }

   double sin_dup(double x)
   {

      if(x < 0.0)
      {

         return -sin_dup(-x);

      }
      else if(x < 3.1415 / 16.0)
      {

         double sin = 0.0;
         double pow = x;
         double fact = 1.0;

         for(double d = 0.0; d < 16.0; d += 1.0)
         {
            sin += pow / fact;
            pow *= x * x;
            fact *= (2.0 * (d + 1.0)) * (2.0 * (d + 1.0) + 1.0);
         }

         return sin;

      }
      else
      {

         return 2.0 * sin_dup(x / 2.0) * cos_dup(x / 2.0);

      }

   }

   void plugin::get_progress_color(BYTE & uchR, BYTE & uchG, BYTE & uchB, double dRate, int32_t iProfile)
   {
      double dH = dRate; // blue ==> red => green
      double dL;
      double dS;

      if(iProfile == 0)
      {
         dL = 0.49;
         dS = 0.77;
      }
      else if(iProfile == 1)
      {
         dL = 0.63;
         dS = 0.84;
      }
      else
      {
         dL = 0.54;
         dS = 0.84;
      }

      {
         if(dH >= 1.0)
            dH = 0.0;
         else if(dH < 0.0)
            dH = 0.0;

         if(dL > 1.0)
            dL = 1.0;
         else if(dL < 0.0)
            dL = 0.0;

         if(dS > 1.0)
            dS = 1.0;
         else if(dS < 0.0)
            dS = 0.0;

         double dR;
         double dG;
         double dB;

         dH *= 6.0;

#if CA2_PLATFORM_VERSION == CA2_BASIS
         dH += 5.0;
#else
         dH += 2.0;
#endif
         if(dH >= 6.0)
            dH -= 6.0;

         double dA;
         if(dH >= 5.0)
            dA = dH - 5.0;
         else if(dH >= 4.0)
            dA = dH - 4.0;
         else if(dH >= 3.0)
            dA = dH - 3.0;
         else if(dH >= 2.0)
            dA = dH - 2.0;
         else if(dH >= 1.0)
            dA = dH - 1.0;
         else
            dA = dH;

         if(dH >= 3.0)
         {
            if(dH >= 4.0)
            {
               if(dH >= 5.0)
               {
                  // 5.0
                  // magenta to red
                  dR = 1.0;
                  dG = 0.0;
                  dB = 1.0 - dA;
               }
               else
               {
                  // 4.0
                  // blue to magenta
                  dR = dA;
                  dG = 0.0;
                  dB = 1.0;
               }
            }
            else
            {
               // 3.0
               // cyan to blue
               dR = 0.0;
               dG = 1.0 - dA;
               dB = 1.0;
            }
         }
         else /// if(dH >= 0.0)
         {
            if(dH >= 2.0)
            {
               // 2
               // green to cyan
               dR = 0.0;
               dG = 1.0;
               dB = dA;
            }
            else // (dH >= 0.0 && dH < 2.0)
            {
               if(dH >= 1.0)
               {
                  // 1
                  // yellow to green
                  dR = 1.0 - dA;
                  dG = 1.0;
                  dB = 0.0;
               }
               else // if(dh >= 0 && dH < 1.0);
               {
                  // 0
                  // red to yellow
                  dR = 1.0;
                  dG = dA;
                  dB = 0.0;
               }
            }
         }

         double dCMin;
         double dCAdd;
         double dSL = dS * dL;
         if(dL >= 0.5)
         {
            dCMin = dL - dS + dSL;
            dCAdd = 2.0 * dS - 2.0 * dSL;
         }
         else
         {
            dCMin = dL - dSL;
            dCAdd = 2.0 * dSL;
         }


         dR      = (dCMin + dR * dCAdd);
         dG      = (dCMin + dG * dCAdd);
         dB      = (dCMin + dB * dCAdd);

         /*uchR      = (BYTE) ftol(dR * 255.0);
         uchG      = (BYTE) ftol(dG * 255.0);
         uchB      = (BYTE) ftol(dB * 255.0);*/
         uchR      = (BYTE) (dR * 255.0);
         uchG      = (BYTE) (dG * 255.0);
         uchB      = (BYTE) (dB * 255.0);

      }

   }


   void plugin::on_bare_paint(::draw2d::graphics * pgraphics, LPCRECT lprect)
   {

      if(pgraphics == NULL)
         return;

      if (m_iHealingSurface == 0)
      {

         on_bare_paint_full_screen(pgraphics, lprect);

      }
      else
      {

         on_bare_paint_discreet(pgraphics, lprect);

      }

   }


   void plugin::start_ca2()
   {
   }

   /*void plugin::free_memory(byte ** ppuchMemory)
   {
      host::free_memory(ppuchMemory);
   }*/

   void plugin::set_progress_rate(double dRate)
   {
      if(m_phost != NULL)
      {
         m_phost->set_progress_rate(dRate);
      }
   }


   double plugin::get_progress_rate()
   {

      if(m_phost != NULL)
      {

         return m_phost->get_progress_rate();

      }

      return 0.0;

   }


   double plugin::extract_spa_progress_rate()
   {

      if (m_phost != NULL)
      {

         return m_phost->extract_spa_progress_rate();

      }

      return 0.0;

   }


   void plugin::on_update_progress()
   {

      set_progress_rate(extract_spa_progress_rate());

   }


   void plugin::on_paint_progress(::draw2d::graphics * pgraphics, LPCRECT lprect)
   {

      if(m_phost != NULL && !m_phost->m_bShowProgress)
         return;

      RECT rectWindow = *lprect;

      int32_t cx = rectWindow.right - rectWindow.left;

      int32_t cy = rectWindow.bottom - rectWindow.top;

      double dRate = get_progress_rate();

      int32_t iLineCount = 25;

      int32_t x;

      int32_t y = rectWindow.top;

      int32_t pcx = cx;

      int32_t pcy = cy / iLineCount;

      RECT rectP;

      for(int32_t iLine = 0; iLine < iLineCount; iLine++)
      {

         double dStart = (double) iLine / (double) iLineCount;

         double dEnd = (double) (iLine + 1) / (double) iLineCount;

         if(dRate <= dEnd)
         {

            if(dRate < dStart)
               x = rectWindow.left;
            else
               x = (int32_t) (rectWindow.left + ((((dRate - dStart) * (double) pcx) / (dEnd - dStart))));

            if(iLine >= (iLineCount - 1))
               pcy = rectWindow.bottom - y;

            rectP.top      = y;

            rectP.bottom   = y + pcy;

            rectP.left     = x;

            rectP.right    = rectWindow.right;

            pgraphics->FillSolidRect(&rectP, ARGB(84, 84, 84, 77));

         }

         y = y + pcy;

      }

   }


   void plugin::start_plugin()
   {

      if(m_phost != NULL)
      {
         m_phost->start_plugin();
      }

   }


   void plugin::deferred_prodevian_redraw()
   {

      m_phost->plugin_system_redraw();

   }


   void plugin::plugin_system_redraw()
   {

      if(m_phost != NULL)
      {
         m_phost->plugin_system_redraw();
      }

   }

   void plugin::set_ca2_installation_ready(bool bReady)
   {

      if(m_phost != NULL)
      {
         m_phost->set_ca2_installation_ready(bReady);
      }

   }


   void plugin::set_status(const char * pszStatus)
   {

      m_strStatus = pszStatus;

   }


   void plugin::restart_small_ipc_channel()
   {

      if(m_phost != NULL && m_phost != this)
      {

         m_phost->restart_small_ipc_channel();

      }
      else
      {

#ifndef METROWIN

         ::small_ipc_channel::close();

#endif

         m_phost->m_bReload = true;

      }

   }


   void plugin::ensure_bitmap_data(int32_t cx, int32_t cy, bool bCreateFile)
   {

      if(m_pcolorref == NULL
         || m_sizeBitmapData.cx != cx
         || m_sizeBitmapData.cy != cy)
      {

         m_sizeBitmapData.cx = cx;
         m_sizeBitmapData.cy = cy;

#ifdef WINDOWS
         if(m_pcolorref != NULL)
#else
         if(m_pcolorref != MAP_FAILED)
#endif
         {
            try
            {
#ifdef WINDOWS
               UnmapViewOfFile(m_pcolorref);
#else
               ::munmap(m_pcolorref, ::get_file_size(m_hfileBitmap));
#endif
            }
            catch(...)
            {
            }
#ifdef WINDOWS
            m_pcolorref = NULL;
#else
            m_pcolorref = (uint32_t *)  MAP_FAILED;
#endif
         }

#ifdef WINDOWS
         if(m_hfilemapBitmap != NULL)
         {
            try
            {
               ::CloseHandle(m_hfilemapBitmap);
            }
            catch(...)
            {
            }
            m_hfilemapBitmap = NULL;
         }
#endif

#ifdef WINDOWS
         if(m_hfileBitmap != INVALID_HANDLE_VALUE)
#else
         if(m_hfileBitmap != -1)
#endif
         {
            try
            {
#ifdef WINDOWS
               ::CloseHandle(m_hfileBitmap);
#else
               ::close(m_hfileBitmap);
#endif
            }
            catch(...)
            {
            }
#ifdef WINDOWS
            m_hfileBitmap = INVALID_HANDLE_VALUE;
#else
            m_hfileBitmap = -1;
#endif
         }

         dir::mk(dir::path(dir::userappdata("time"), "core"));

         int32_t iOpen;

         if(bCreateFile)
         {
#ifdef WINDOWS
            iOpen = OPEN_ALWAYS;
#else
            iOpen = O_RDWR | O_CREAT;
#endif
         }
         else
         {
#ifdef WINDOWS
            iOpen = OPEN_EXISTING;
#else
            iOpen = O_RDWR;
#endif
         }

#ifdef METROWIN
         CREATEFILE2_EXTENDED_PARAMETERS ps;
         zero(&ps, sizeof(ps));
         ps.dwSize = sizeof(ps);
         ps.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
         wstring wstr(dir::path(dir::userappdata("time"), string("core\\app.plugin.container-") + m_strBitmapChannel));
         m_hfileBitmap = CreateFile2(wstr, FILE_READ_DATA | FILE_WRITE_DATA, FILE_SHARE_WRITE | FILE_SHARE_READ, iOpen, &ps);
#elif defined(WINDOWS)
         wstring wstr(dir::path(dir::userappdata("time"), string("core\\app.plugin.container-") + m_strBitmapChannel));
         m_hfileBitmap = CreateFileW(wstr, FILE_READ_DATA | FILE_WRITE_DATA, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, iOpen, FILE_ATTRIBUTE_NORMAL, NULL);
#else
         m_hfileBitmap = ::open(dir::path(dir::userappdata("time"), string("core\\app.plugin.container-") + m_strBitmapChannel), iOpen, S_IRUSR | S_IWUSR);
#endif


#ifdef WINDOWS
         uint32_t dwError = GetLastError();
         if(m_hfileBitmap == INVALID_HANDLE_VALUE)
#else
         if(m_hfileBitmap == -1)
#endif
         {

            if(bCreateFile)
            {

               throw "resource exception";

            }
            else
            {

               return;

            }

         }

         uint_ptr size = m_sizeBitmapData.cx * m_sizeBitmapData.cy * sizeof(COLORREF);

         ensure_file_size(m_hfileBitmap, size);
#ifdef METROWIN
         m_hfilemapBitmap = CreateFileMappingFromApp(
            m_hfileBitmap,
            NULL,
            PAGE_READWRITE,
            size,
            NULL);

         if(m_hfilemapBitmap == NULL)
         {
            CloseHandle(m_hfileBitmap);
            m_hfileBitmap = INVALID_HANDLE_VALUE;
            throw "resource exception";
         }

#elif defined(WINDOWS)
         m_hfilemapBitmap = CreateFileMapping(
            m_hfileBitmap,
            NULL,
            PAGE_READWRITE,
            0,
            0,
            NULL);

         if(m_hfilemapBitmap == NULL)
         {
            CloseHandle(m_hfileBitmap);
            m_hfileBitmap = INVALID_HANDLE_VALUE;
            throw "resource exception";
         }

#endif

#ifdef METROWIN
      m_pcolorref = (COLORREF *) MapViewOfFileFromApp(
         m_hfilemapBitmap,
         FILE_MAP_READ | FILE_MAP_WRITE,
         0,
         0);
#elif defined(WINDOWS)
         m_pcolorref = (COLORREF *) MapViewOfFile(
            m_hfilemapBitmap,
            FILE_MAP_READ | FILE_MAP_WRITE,
            0,
            0,
            0
            );
#else
         m_pcolorref = (COLORREF *) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, m_hfileBitmap, 0);
#endif

#ifdef WINDOWS
         if(m_pcolorref == NULL)
#else
         if(m_pcolorref == MAP_FAILED)
#endif
         {
#ifdef WINDOWS
            CloseHandle(m_hfilemapBitmap);
            m_hfilemapBitmap = NULL;
            CloseHandle(m_hfileBitmap);
            m_hfileBitmap = INVALID_HANDLE_VALUE;
#else
            ::close(m_hfileBitmap);
            m_hfileBitmap = -1;
#endif
            throw "resource exception";
         }

         m_pmutexBitmap = new mutex(get_thread_app(), false, string("Global\\app.plugin.container-") + hex::lower_from((int_ptr)this));

      }


   }

   void plugin::client_to_screen(POINT * ppt)
   {

      ::simple_ui::interaction::client_to_screen(ppt);

   }

   void plugin::screen_to_client(POINT * ppt)
   {

      ::simple_ui::interaction::screen_to_client(ppt);

   }


   void plugin::translate_mouse_message(int * px, int * py)
   {

      if (m_phost != NULL)
      {

         m_phost->translate_mouse_message(px, py);

      }

   }


   bool plugin::show_window(bool bShow)
   {

      if (m_phost != NULL)
      {

         return m_phost->show_window(bShow);

      }

      return false;

   }


   bool plugin::destroy_window()
   {

      if (m_phost != NULL)
      {

         return m_phost->destroy_window();

      }
      
      return true;

   }


   bool plugin::set_host(::hotplugin::host * phost)
   {

      m_phost = phost;

      return true;


   }


} // namespace hotplugin


