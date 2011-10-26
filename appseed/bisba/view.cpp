#include "StdAfx.h"
#include <math.h>


namespace bisba
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp)
   {
   }

   view::~view()
   {
   }

#ifdef _DEBUG
   void view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
	   ::userbase::view::dump(dumpcontext);
   }
#endif 


   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      rect rectClient;
      GetClientRect(rectClient);
      pdc->SetStretchBltMode(HALFTONE);

      ::ca::dib * pdib = get_document()->m_spdib;

      if(pdib->area() == 0)
         return;
      
      double r;
      if(Application.command().m_varTopicQuery.has_property("rate"))
      {
         r = Application.command().m_varTopicQuery["rate"].get_double();
         if(r < 0.01)
            r = 0.01;
      }
      else
      {
         r = 1.2;
      }

      double r1 = 0.4 * r;
      double r2 = 0.15 * r;
      double r3 = 0.0 * r;
      double r4 = 0.0 * r;
      double r5 = 0.28 * r;
      double r6 = 0.4 * r;
      double zamp = 33.0;

      ::ca::dib_sp dib(get_app());

      dib->create(pdib->width() * r1 + pdib->height() * r2 + zamp * r3 + 5,  pdib->width() * r4 + pdib->height() * r5 + zamp * r6 + 5);
      int aw = pdib->width();
      int bh = pdib->height();
      int w = dib->width();
      int h = dib->height();

      dib->Fill(0, 255, 255, 255);
      
      const double dBrightAngle = - 3.1415  * 60.0 / 180.0;
      int b5 = bh * r5;
      double darken = 0.40;
      DWORD dwTime = GetTickCount();
      double freq = 0.33f;
      double phiTime = dwTime * freq * 3.1415 * 2 / 1000.0;
      COLORREF * pdst = dib->get_data();
      double Arate = r * 0.25;
      for(int a = 0; a < aw; a++)
      {
         double phi = a / 84.0 +  phiTime;
         double cosa = cos(phi);
         double cosd = cos(phi + dBrightAngle);
         double m = (cosd + 1.0) * 0.5 * 153;
         double a1 = a * r1;
         double a4 = a * r4;
         double z = (cosa + 1.0) * zamp / 2.0;
         double z3 = z * r3;
         double z6 = z * r6;
         double ax = a1 + z3;
         double ay = a4 + z6;
         COLORREF * psrc = &pdib->get_data()[a];
         for(int b = 0; b < bh; b++)
         {
            double dx = ax + b * r2;
            double dy = ay + b * r5;
            int xref = (int) dx; 
            int yref = (int) dy;
            {
               int x = xref;
               int y = yref;

               COLORREF cr = *psrc;
               COLORREF crDst = pdst[x + w * y];

               int R = GetRValue(cr) * darken + m;
               int G = GetGValue(cr) * darken + m;
               int B = GetBValue(cr) * darken + m;
               if(R >= 255 || G >= 255 || B >= 255)
               {
                  R = 255;
                  G = 255;
                  B = 255;
               }
               if(crDst == 0x00ffffff)
               {
                  crDst = RGB(R, G, B);
               }
               else
               {
                  int R2 = GetRValue(crDst);
                  int G2 = GetGValue(crDst);
                  int B2 = GetBValue(crDst);
                  int A2 = (crDst & 0xff000000) >> 24;
                  A2 = min(A2 + ((256 - A2) * Arate), 255);
                  crDst = RGB((R2 + R) / 2, (G2 + G) / 2, (B2 + B) / 2) | (A2 << 24);
               }
               pdst[x + w * y] = crDst;
            }

            if((dx - (double) xref) >= 0.5)
            {
               int x = xref + 1;
               int y = yref;

               COLORREF cr = *psrc;
               COLORREF crDst = pdst[x + w * y];

               int R = GetRValue(cr) * darken + m;
               int G = GetGValue(cr) * darken + m;
               int B = GetBValue(cr) * darken + m;
               if(R >= 255 || G >= 255 || B >= 255)
               {
                  R = 255;
                  G = 255;
                  B = 255;
               }
               if(crDst == 0x00ffffff)
               {
                  crDst = RGB(R, G, B);
               }
               else
               {
                  int R2 = GetRValue(crDst);
                  int G2 = GetGValue(crDst);
                  int B2 = GetBValue(crDst);
                  int A2 = (crDst & 0xff000000) >> 24;
                  A2 = min(A2 + ((256 - A2) * Arate), 255);
                  crDst = RGB((R2 + R) / 2, (G2 + G) / 2, (B2 + B) / 2) | (A2 << 24);
               }
               pdst[x + w * y] = crDst;
            }
            if((dy - (double) yref) >= 0.5)
            {
               int x = xref;
               int y = yref + 1;

               COLORREF cr = *psrc;
               COLORREF crDst = pdst[x + w * y];

               int R = GetRValue(cr) * darken + m;
               int G = GetGValue(cr) * darken + m;
               int B = GetBValue(cr) * darken + m;
               if(R >= 255 || G >= 255 || B >= 255)
               {
                  R = 255;
                  G = 255;
                  B = 255;
               }
               if(crDst == 0x00ffffff)
               {
                  crDst = RGB(R, G, B);
               }
               else
               {
                  int R2 = GetRValue(crDst);
                  int G2 = GetGValue(crDst);
                  int B2 = GetBValue(crDst);
                  int A2 = (crDst & 0xff000000) >> 24;
                  A2 = min(A2 + ((256 - A2) * Arate), 255);
                  crDst = RGB((R2 + R) / 2, (G2 + G) / 2, (B2 + B) / 2) | (A2 << 24);
               }
               pdst[x + w * y] = crDst;
            }
            if((dx - (double) xref) >= 0.5 &&
            (dy - (double) yref) >= 0.5)
            {
               int x = xref + 1;
               int y = yref + 1;

               COLORREF cr = *psrc;
               COLORREF crDst = pdst[x + w * y];

               int R = GetRValue(cr) * darken + m;
               int G = GetGValue(cr) * darken + m;
               int B = GetBValue(cr) * darken + m;
               if(R >= 255 || G >= 255 || B >= 255)
               {
                  R = 255;
                  G = 255;
                  B = 255;
               }
               if(crDst == 0x00ffffff)
               {
                  crDst = RGB(R, G, B);
               }
               else
               {
                  int R2 = GetRValue(crDst);
                  int G2 = GetGValue(crDst);
                  int B2 = GetBValue(crDst);
                  int A2 = (crDst & 0xff000000) >> 24;
                  A2 = min(A2 + ((256 - A2) * Arate), 255);
                  crDst = RGB((R2 + R) / 2, (G2 + G) / 2, (B2 + B) / 2) | (A2 << 24);
               }
               pdst[x + w * y] = crDst;
            }
            psrc += aw;

         }
      }


      double dx = (double) rectClient.width() / (double) max(1, dib->width());
      double dy = (double) rectClient.height() / (double) max(1, dib->height());
      double dr = min(dx, dy);
      if(dr == 0)
         return;

      Application.imaging().bitmap_blend(pdc, point(0, 0), size((int) (dib->width() * dr), (int) (dib->height() * dr)),
         dib->get_graphics(),
         point(0, 0));

   }



   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }

} // namespace bisba
