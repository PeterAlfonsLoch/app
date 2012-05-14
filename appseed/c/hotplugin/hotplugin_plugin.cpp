#include "framework.h"

#ifdef WINDOWS
#include <GdiPlus.h>
#endif

#ifdef LINUX
#include "c/linux/c_os_cross_win_gdi_internal.h"
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


      m_sizeBitmap.cx = 994;
      m_sizeBitmap.cy = 394;


      m_pcolorref = (DWORD *) ca2_alloc(abs_dup(4 * m_sizeBitmap.cx * m_sizeBitmap.cy));

#if !defined(MACOS) && !defined(LINUX)
      m_pbitmap = new Gdiplus::Bitmap(abs_dup(m_sizeBitmap.cx), abs_dup(m_sizeBitmap.cy), abs_dup(m_sizeBitmap.cx) * 4, PixelFormat32bppARGB, (BYTE *) m_pcolorref);
#endif

      m_strStatus = "Thank you";

   }


   plugin::~plugin()
   {
      free_memory();
#if !defined(MACOS) && !defined(LINUX)
      if(m_pbitmap != NULL)
         delete (Gdiplus::Bitmap *) m_pbitmap;
      if(m_pcolorref != NULL)
         ca2_free(m_pcolorref);
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

   HWND plugin::get_host_window()
   {
      if(m_phost != NULL)
      {
         return m_phost->get_host_window();
      }
      return NULL;
   }

   // ca2.dll-absence-(ca2.dll-delay-load)-safe
   void plugin::get_window_rect(LPRECT lprect)
   {
      if(m_phost != NULL)
      {
         m_phost->get_window_rect(lprect);
      }
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

   void plugin::on_paint(HDC hdcWindow, LPCRECT lprect)
   {
      on_bare_paint(hdcWindow, lprect);
   }

#ifdef _WINDOWS
   UINT_PTR plugin::message_handler(UINT_PTR uiMessage, WPARAM wparam, LPARAM lparam)
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

void get_progress_color(BYTE & uchR, BYTE & uchG, BYTE & uchB, double dRate)
{
   double dH = dRate; // blue ==> red => green
   double dL = 0.49;
   double dS = 0.84;
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


   void plugin::on_bare_paint(HDC hdc, LPCRECT lprect)
   {
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
      {
         HPEN hpen = ::CreatePen(PS_SOLID, 1, RGB(84, 84, 77));
         HBRUSH hbrush = (HBRUSH) ::GetStockObject(NULL_BRUSH);
         ::SelectObject(hdc, hpen);
         ::SelectObject(hdc, hbrush);
         ::Rectangle(hdc, lprect->left, lprect->top, lprect->right, lprect->bottom);
         ::DeleteObject(hbrush);
         ::DeleteObject(hpen);
      }

      on_paint_progress(hdc, lprect);

      double dRate = get_progress_rate();

      int iDelta = s_iDelta;
      int iRadius = 8;
      int iPhase = ((((GetTickCount()- s_dwSync)  % iDelta)  ) * iRadius * 2) / iDelta;

      if(iPhase == 0 && (GetTickCount() - s_dwSync) > 1977)
      {

         s_iDelta = 1984 + (GetTickCount() % ((1984 + 1977) * 2));
         s_dwSync = GetTickCount();
      }

      int iStep = iPhase;

      if(iStep > iRadius)
         iStep = iRadius * 2 - iStep;

      wstring wstr;

      wstr = m_strStatus;

#ifdef WINDOWS

/*      HFONT hfont = ::CreatePointFont_dup(490, "Lucida Sans Unicode", hdc);

      HFONT hfontOld = (HFONT) ::SelectObject(hdc, hfont);

      const char * psz = "Thank You";

      ::SetBkMode(hdc, TRANSPARENT);

      ::SetTextColor(hdc, RGB(255, 255, 255));

      ::TextOut(hdc, lprect->left + 84, lprect->top + 84, psz, strlen_dup(psz));

      ::SelectObject(hdc, hfontOld);

      ::DeleteObject(hfont);*/


  /*    Gdiplus::FontFamily ff(L"Lucida Sans Unicode");

      Gdiplus::Font font(&ff, 49, Gdiplus::FontStyleBold, Gdiplus::UnitPoint);

      Gdiplus::StringFormat * psf = Gdiplus::StringFormat::GenericDefault()->Clone();

      psf->SetLineAlignment(Gdiplus::StringAlignmentCenter);

      psf->SetAlignment(Gdiplus::StringAlignmentNear);

      Gdiplus::RectF rectFull(0.0f, 0.0f, m_sizeBitmap.cx, m_sizeBitmap.cy);

      Gdiplus::RectF rectText(rectFull);

      Gdiplus::RectF rectCircle(84.0f, 84.0f, 84, 84);

      rectText.X = 84.0f;*/

      {

/*         {

            Gdiplus::Graphics graphics((Gdiplus::Bitmap *) m_pbitmap);

            graphics.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);

            Gdiplus::SolidBrush br1(Gdiplus::Color(0, 0, 0, 0));

            graphics.FillRectangle(&br1, rectFull);

            Gdiplus::SolidBrush br(Gdiplus::Color(255, 255, 255, 255));

            //graphics.DrawString(wstr, wstr.get_length(), &font, rectText, psf, &br);
            graphics.FillEllipse(&br, rectCircle);

            for(int i = 0; i < 3; i++)
            {
               fastblur(m_pcolorref, m_sizeBitmap.cx, m_sizeBitmap.cy, iStep + 4);
            }


            int area = m_sizeBitmap.cx * m_sizeBitmap.cy;

            for(int i = 0; i < area; i++)
            {
               BYTE bA = min((((m_pcolorref[i] & 0xff00) >> 8) & 0xff), 255);

               m_pcolorref[i] = ((bA << 24) & 0xff000000) | ((((uchR * bA) / 255) & 0xff) << 16) | ((((uchG * bA) / 255) & 0xff) << 8) | ((((uchB * bA) / 255) & 0xff));
            }

            graphics.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);

            //graphics.FillEllipse(&br, rectCircle);

         }*/



         /*
         BYTE bA = 84;
         BYTE uchR;
         BYTE uchG;
         BYTE uchB;

         Gdiplus::Graphics graphics2(hdc);

         graphics2.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

         const int iLineCount = 23;
         const int iRowCount = 49;

         int iProgressLine = iLineCount * dRate; 
         
         if(iProgressLine >= iLineCount)
            iProgressLine = iLineCount - 1;

         int iProgressRow = iRowCount * ((dRate - ((double)(iProgressLine) / (double) iLineCount)) * iLineCount);

         if(iProgressRow >= iRowCount)
            iProgressRow = iRowCount - 1;

         int iHeight = cy / iLineCount;
         int iWidth = cx / iRowCount;

         int iLine;
         int iRow;

         for(iLine = 0; iLine < iProgressLine; iLine++)
         {
            for(iRow = 0; iRow < iRowCount; iRow++)
            {
               get_progress_color(uchR, uchG, uchB, (((double) iLine + ((double) iRow / (double)iRowCount)) / (double) iLineCount));
               Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
               graphics2.FillRectangle(pbr, lprect->left + iRow * iWidth, lprect->top + iLine * iHeight, iWidth, iHeight);
               delete pbr;
            }
         }

         if(iLine < iLineCount)
         {

            for(iRow = 0; iRow < iProgressRow; iRow++)
            {
               get_progress_color(uchR, uchG, uchB, (((double) iLine + ((double) iRow / (double)iRowCount)) / (double) iLineCount));
               Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
               graphics2.FillRectangle(pbr, lprect->left + iRow * iWidth, lprect->top + iLine * iHeight, iWidth, iHeight);
               delete pbr;
            }

            if(iRow < iRowCount)
            {
               get_progress_color(uchR, uchG, uchB, (((double) iLine + ((double) iRow / (double)iRowCount)) / (double) iLineCount));
               Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
               graphics2.FillRectangle(pbr, lprect->left + iRow * iWidth, lprect->top + iLine * iHeight, iWidth * (dRate - ((double) iLine + ((double) iRow / (double)iRowCount) / (double) iLineCount)) , iHeight);
               delete pbr;
            }

         }

         //graphics2.DrawImage((Gdiplus::Bitmap *) m_pbitmap, lprect->left, lprect->top);

      //   delete psf;
      */


       BYTE bA = 84;
         BYTE uchR;
         BYTE uchG;
         BYTE uchB;

         Gdiplus::Graphics graphics2(hdc);

         graphics2.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

         const int iRowCount = cx;
         int iProgressCount = max(min((int) (iRowCount * dRate), iRowCount), 0);

         

         int iRow;

         for(iRow = 0; iRow < iProgressCount; iRow++)
         {
            get_progress_color(uchR, uchG, uchB, (double) iRow / (double) iRowCount);
            Gdiplus::SolidBrush * pbr = new Gdiplus::SolidBrush(Gdiplus::Color(bA, uchR, uchG, uchB));
            graphics2.FillRectangle(pbr, lprect->left + iRow , lprect->top, 1, cy);
            delete pbr;
         }


         //graphics2.DrawImage((Gdiplus::Bitmap *) m_pbitmap, lprect->left, lprect->top);

      //   delete psf;
      
      }
#endif



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

   void plugin::on_paint_progress(HDC hdc, LPCRECT lprect)
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
            ::FillSolidRect_dup(hdc, &rectP, RGB(84, 84, 77));
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


} // namespace hotplugin


