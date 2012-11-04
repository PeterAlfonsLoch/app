#include "framework.h"
#include <math.h>

#ifdef LINUX
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#endif



#ifdef LINUX
#include "c/linux/c_os_cross_win_gdi_internal.h"
#endif

#ifdef WINDOWSEX
#include <gdiplus.h>
#endif



void fastblur(DWORD * pdata, int w, int h, int radius);


namespace hotplugin
{


   plugin::plugin()
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
#if !defined(MACOS) && !defined(LINUX) && !defined(METROWIN)
      if(m_pbitmap != NULL)
         delete (Gdiplus::Bitmap *) m_pbitmap;
      if(m_pcolorref != NULL)
         _ca_free(m_pcolorref, 0);
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

   vsstring plugin::get_host_location_url()
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
      return ::ca::null();
   }

   // ca2.dll-absence-(ca2.dll-delay-load)-safe
   void plugin::get_window_rect(LPRECT lprect)
   {

      *lprect = m_rect;

   }

   void plugin::set_window_rect(LPCRECT lpcrect)
   {

      m_rect = *lpcrect;

   }

   void plugin::set_memory(void * puchMemory, count c)
   {
      if(m_phost != NULL)
      {
         m_phost->set_memory(puchMemory, c);
      }
   }

   void plugin::append_memory(void * puchMemory, count c)
   {
      if(m_phost != NULL)
      {
         m_phost->append_memory(puchMemory, c);
      }
   }

   count plugin::get_memory_length()
   {
      if(m_phost != NULL)
      {
         return m_phost->get_memory_length();
      }
      return 0;
   }

   count plugin::read_memory(void * puchMemory, count c)
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

   void plugin::on_paint(simple_graphics & gWindow, LPCRECT lprect)
   {

      on_bare_paint(gWindow, lprect);

   }

#ifdef WINDOWS
   uint_ptr plugin::message_handler(uint_ptr uiMessage, WPARAM wparam, LPARAM lparam)
   {
      return 0;
   }
#else
   int plugin::message_handler(XEvent * pevent)
   {
      return 0;
   }
#endif

   int plugin::start_ca2_system()
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
   int p;
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

   void get_progress_color(BYTE & uchR, BYTE & uchG, BYTE & uchB, double dRate, int iProfile)
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


   void plugin::on_bare_paint(simple_graphics & g, LPCRECT lprect)
   {

      if(g.is_null())
         return;


      static DWORD s_dwSync = 0;
      static int s_iDelta = 1984 + 1977;
      RECT rectWindow;
      get_window_rect(&rectWindow);
      int cx = rectWindow.right - rectWindow.left;
      int cy = rectWindow.bottom - rectWindow.top;
      RECT rect;
      rect.left      = 0;
      rect.top       = 0;
      rect.bottom    = cy;
      rect.right     = cx;

      simple_pen pen;

      pen.create_solid(g, 1, RGB(84, 84, 77));

      simple_brush brush;

      brush.from_stock(NULL_BRUSH);

      g.select(pen);

      g.select(brush);

      g.rectangle(&m_rect);

      on_paint_progress(g, lprect);

      double dRate = get_progress_rate();

      if(dRate <= 0.0)
      {

         return;

      }




      int iDelta = s_iDelta;
      int iRadius = 8;
      int iPhase = ((((get_tick_count()- s_dwSync)  % iDelta)  ) * iRadius * 2) / iDelta;

      if(iPhase == 0 && (get_tick_count() - s_dwSync) > 1977)
      {

         s_iDelta = 1984 + (get_tick_count() % ((1984 + 1977) * 2));
         s_dwSync = get_tick_count();
      }

      int iStep = iPhase;

      if(iStep > iRadius)
         iStep = iRadius * 2 - iStep;

      wstring wstr;

      wstr = m_strStatus;

      int iRate1 = 25;

      BYTE bA;

      {

         //int iARange = (184 - 23) * 2;
         //int iAClip = iARange / 2;
         double period = 8.4; // seconds
         double frequency = 1.0 / period;
         //int iA = (iARange * ::get_tick_count() / 8000) % iARange;
         double w = 2.0 * 3.1415 * frequency;
         double t = get_tick_count() / 1000.0;


         /*if(iA < iAClip)
         bA = iA + 23;
         else
         bA = 184 * 2 - iA;*/

         bA = min(255, max(0, (BYTE) ((184.0 * ((sin(w * t) + 1.0) / 2.0)) + 23.0)));



      }

      BYTE uchR;
      BYTE uchG;
      BYTE uchB;

      //graphics2.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

      int iRate = 10;

      const int iRowCount = cx - cx / (iRate / 2);
      int iProgressCount = max(min((int) (iRowCount * dRate), iRowCount), 0);



      int iBorder1 = max(cx / iRate1, cy / iRate1);

      simple_path pathClip1;

      RECT rectClip1;

      rectClip1.left    = lprect->left + iBorder1;
      rectClip1.top     = lprect->top + iBorder1;
      rectClip1.right   = rectClip1.left + cx - iBorder1 * 2;
      rectClip1.bottom  = rectClip1.top + cy - iBorder1 * 2;

      pathClip1.begin_figure(true, ::ca::fill_mode_winding);

      pathClip1.add_round_rect(rectClip1, iBorder1 * 2);

      pathClip1.end_figure(true);

      g.replace_clip(pathClip1);



      int iRatePercentMillis = ((int) (dRate * 100.0 * 1000.0)) % 1000;
      int iRatePercent = ((int) (dRate * 100.0));

      wstring wstrProgress;

      {

         vsstringtow strProgress(wstrProgress);

         vsstring strDecimal = itoa_dup(iRatePercentMillis);

         zero_pad(strDecimal, 3);

         strProgress = itoa_dup(iRatePercent) + "." + strDecimal + "%";

      }

      int iBarHeight = 23;



      int iBorder = 16;

      simple_path pathClip;

      RECT rectClip;

      rectClip.left     = lprect->left + cx / iRate - iBorder;
      rectClip.top      = lprect->top + (cy - iBarHeight) / 2 - iBorder;
      rectClip.right    = rectClip.left + iRowCount + iBorder * 2;
      rectClip.bottom   = rectClip.top + iBarHeight + iBorder * 2;


      pathClip.begin_figure(true, ::ca::fill_mode_winding);

      pathClip.add_round_rect(rectClip, iBorder);

      pathClip.end_figure(true);

      g.exclude_clip(pathClip);


      POINT pa[4];

      //Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(49, 177 + iBarHeight, 177 + iBarHeight, 177 + 19));
      //graphics2.FillRectangle(pbr, lprect->left , lprect->top, lprect->left + cx, lprect->top + cy);
      //delete pbr;

      simple_brush br;

      br.create_solid(g, ARGB(49, 184 + 23, 184 + 23, 184 + 19));

      int mcy = cy / 2;

      if(m_iHealingSurface == 1)
      {

         g.select(br);

         for(int x = 0; x < (cx + cy); x += 46)
         {

            pa[0].x = lprect->left + x;
            pa[0].y = lprect->top;

            pa[1].x = lprect->left + x + iBarHeight;
            pa[1].y = lprect->top;

            pa[2].x = lprect->left + x - mcy + iBarHeight;
            pa[2].y = lprect->top + mcy;

            pa[3].x = lprect->left + x - mcy;
            pa[3].y = lprect->top + mcy;

            g.fill_polygon(pa, 4, ::ca::fill_mode_winding);

            pa[0].x = lprect->left + x - mcy - iBarHeight;
            pa[0].y = lprect->top + mcy;

            pa[1].x = lprect->left + x - mcy;
            pa[1].y = lprect->top + mcy;

            pa[2].x = lprect->left + x - cy;
            pa[2].y = lprect->top + cy;

            pa[3].x = lprect->left + x - cy - iBarHeight;
            pa[3].y = lprect->top + cy;

            g.fill_polygon(pa, 4, ::ca::fill_mode_winding);


         }

      }


      inflate_rect(rectClip, 3);

      g.replace_clip(rectClip);

      br.create_solid(g, ARGB(84, 84, 84, 77));

      RECT r1;

      r1.left = lprect->left + cx / iRate - 1;
      r1.top = lprect->top + (cy - iBarHeight) / 2 - 1;
      r1.right = r1.left + iRowCount + 2;
      r1.bottom = r1.top + iBarHeight + 2;

      g.fill_rect(&r1, br);

      /*for(iRow = 0; iRow < iProgressCount; iRow++)
      {
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 0);
      Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.FillRectangle(pbr, lprect->left + iRow + cx / iRate , lprect->top + (cy - iBarHeight) / 2, 1, 5);
      delete pbr;
      }
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 1);
      Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.FillRectangle(pbr, lprect->left + iRow + cx / iRate , lprect->top + (cy - iBarHeight) / 2 + 5, 1, 5);
      delete pbr;
      }
      {
      get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount, 2);
      Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
      graphics2.FillRectangle(pbr, lprect->left + iRow + cx / iRate , lprect->top + (cy - iBarHeight) / 2 + 10, 1, 13);
      delete pbr;
      }
      }*/
      {
         get_progress_color(uchR, uchG, uchB, 0.0, 0);
         br.create_solid(g, ARGB(bA, uchR, uchG, uchB));
         g.fill_rect(rect_dim(lprect->left + cx / iRate , lprect->top + (cy - iBarHeight) / 2, iProgressCount, 5), br);
      }
      {
         get_progress_color(uchR, uchG, uchB, 0.0, 1);
         br.create_solid(g, ARGB(bA, uchR, uchG, uchB));
         g.fill_rect(rect_dim(lprect->left + cx / iRate , lprect->top + (cy - iBarHeight) / 2 + 5, iProgressCount, 5), br);
      }
      {
         get_progress_color(uchR, uchG, uchB, 0.0, 2);
         br.create_solid(g, ARGB(bA, uchR, uchG, uchB));
         g.fill_rect(rect_dim(lprect->left + cx / iRate , lprect->top + (cy - iBarHeight) / 2 + 10, iProgressCount, 13), br);
      }

      int iOffset = 3;

      pen.create_solid(g, ARGB(220, 180, 180, 180));
      g.draw_line(lprect->left + cx / iRate - iOffset, lprect->top + (cy - iBarHeight) / 2 - iOffset, lprect->left + cx - cx / iRate + iOffset, lprect->top + (cy - iBarHeight) / 2 - iOffset, pen);
      g.draw_line(lprect->left + cx / iRate - iOffset, lprect->top + (cy - iBarHeight) / 2 - iOffset, lprect->left + cx / iRate - iOffset, lprect->top + (cy + iBarHeight) / 2 + iOffset, pen);

      pen.create_solid(g, ARGB(220, 77, 77, 77));
      g.draw_line(lprect->left + cx / iRate - iOffset, lprect->top + (cy + iBarHeight) / 2 + iOffset, lprect->left + cx - cx / iRate + iOffset, lprect->top + (cy + iBarHeight) / 2 + iOffset, pen);
      g.draw_line(lprect->left + cx - cx / iRate + iOffset, lprect->top + (cy - iBarHeight) / 2 - iOffset, lprect->left + cx - cx / iRate + iOffset, lprect->top + (cy + iBarHeight) / 2 + iOffset, pen);

      iOffset = 2;
      pen.create_solid(g, ARGB(220, 84, 84, 84));
      g.draw_line(lprect->left + cx / iRate - iOffset, lprect->top + (cy - iBarHeight) / 2 - iOffset, lprect->left + cx - cx / iRate + iOffset, lprect->top + (cy - iBarHeight) / 2 - iOffset, pen);
      g.draw_line(lprect->left + cx / iRate - iOffset, lprect->top + (cy - iBarHeight) / 2 - iOffset, lprect->left + cx / iRate - iOffset, lprect->top + (cy + iBarHeight) / 2 + iOffset, pen);

      pen.create_solid(g, ARGB(220, 170, 170, 170));
      g.draw_line(lprect->left + cx / iRate - iOffset, lprect->top + (cy + iBarHeight) / 2 + iOffset, lprect->left + cx - cx / iRate + iOffset, lprect->top + (cy + iBarHeight) / 2 + iOffset, pen);
      g.draw_line(lprect->left + cx - cx / iRate + iOffset, lprect->top + (cy - iBarHeight) / 2 - iOffset, lprect->left + cx - cx / iRate + iOffset, lprect->top + (cy + iBarHeight) / 2 + iOffset, pen);


      br.create_solid(g, ARGB(127, 255, 255, 255));

      g.select(br);

      simple_pixel_font f(g, iBarHeight * 10, "Calibri");

      g.select(f);

      wstring wstrStatus;

      wstrStatus     = wstr;
      wstrStatus     = wstrStatus + L" : ";
      wstrStatus     = wstrStatus + wstrProgress;

      g.text_out(lprect->left + cx / iRate - 1 + 18, lprect->top + (cy - iBarHeight) / 2 - 1 + 1, vsstring(wstrStatus));

   }

   void plugin::start_ca2()
   {
   }

   void plugin::free_memory(byte ** ppuchMemory)
   {
      host::free_memory(ppuchMemory);
   }

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

   void plugin::on_paint_progress(simple_graphics & g, LPCRECT lprect)
   {

      if(m_phost != NULL && !m_phost->m_bShowProgress)
         return;

      RECT rectWindow = *lprect;
      int cx = rectWindow.right - rectWindow.left;
      int cy = rectWindow.bottom - rectWindow.top;

      double dRate = get_progress_rate();
      int iLineCount = 25;
      int x;
      int y = rectWindow.top;
      int pcx = cx;
      int pcy = cy / iLineCount;

      RECT rectP;

      for(int iLine = 0; iLine < iLineCount; iLine++)
      {
         double dStart = (double) iLine / (double) iLineCount;
         double dEnd = (double) (iLine + 1) / (double) iLineCount;
         if(dRate <= dEnd)
         {
            if(dRate < dStart)
               x = rectWindow.left;
            else
               x = rectWindow.left + (ftol(((dRate - dStart) * (double) pcx) / (dEnd - dStart)));
            if(iLine >= (iLineCount - 1))
               pcy = rectWindow.bottom - y;
            rectP.top      = y;
            rectP.bottom   = y + pcy;
            rectP.left     = x;
            rectP.right    = pcx;
            g.fill_solid_rect(&rectP, RGB(84, 84, 77));
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


   void plugin::ensure_bitmap_data(int cx, int cy, bool bCreateFile)
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

         dir::mk(dir::path(dir::userappdata("time"), "ca2"));

         int iOpen;

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
         wstring wstr(dir::path(dir::userappdata("time"), vsstring("ca2\\ca2plugin-container-") + m_strBitmapChannel));
         m_hfileBitmap = CreateFile2(wstr, FILE_READ_DATA | FILE_WRITE_DATA, FILE_SHARE_WRITE | FILE_SHARE_READ, iOpen, &ps);
#elif defined(WINDOWS)
         wstring wstr(dir::path(dir::userappdata("time"), vsstring("ca2\\ca2plugin-container-") + m_strBitmapChannel));
         m_hfileBitmap = CreateFileW(wstr, FILE_READ_DATA | FILE_WRITE_DATA, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, iOpen, FILE_ATTRIBUTE_NORMAL, NULL);
#else
         m_hfileBitmap = ::open(dir::path(dir::userappdata("time"), vsstring("ca2\\ca2plugin-container-") + m_strBitmapChannel).m_psz, iOpen, S_IRUSR | S_IWUSR);
#endif


#ifdef WINDOWS
         DWORD dwError = GetLastError();
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

         dword_ptr size = m_sizeBitmapData.cx * m_sizeBitmapData.cy * sizeof(COLORREF);

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

         m_pmutexBitmap = new simple_mutex(vsstring("Global\\ca2plugin-container-") + itohex_dup((int_ptr)this));

      }


   }


} // namespace hotplugin


