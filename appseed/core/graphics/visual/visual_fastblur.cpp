// Super Fast Blur v1.1
// by Mario Klingemann <http://incubator.quasimondo.com>
//
// Tip: Multiple invovations of this filter with a small
// radius will approximate a gaussian blur quite well.
//
#include "framework.h"





namespace visual
{

   
   fastblur::fastblur(allocatorsp allocer) :
      dib_sp(allocer)
   {
      
      m_iRadius = 0;
      m_size.cx = 0;
      m_size.cy = 0;
      
   }


   bool fastblur::initialize(int32_t cx, int32_t cy, int32_t radius)
   {

      if(is_null())
         return false;

      if (m_p->m_size == size(cx, cy))
         return true;
      
      if(!m_p->create(cx, cy))
         return false;

//      int32_t h         = cy;
  //    int32_t scan      = m_p->scan;
      int32_t div       = radius + radius + 1;
      m_iRadius         = radius;
      m_uchaDiv.allocate(256 * div);
      byte * dv         = m_uchaDiv.get_data();

      m_size.cx         = cx;
      m_size.cy         = cy;


      for(int32_t i = 0; i < m_uchaDiv.get_count(); i++)
      {

         dv[i]= min(255, i/div);

      }

      m_p->map();

      int area = m_p->m_iScan * m_p->m_size.cy;

      m_ucha.allocate(area);

      area /= sizeof(COLORREF);

      m_uchaR.allocate(area);

      m_uchaG.allocate(area);

      m_uchaB.allocate(area);

      m_uchaA.allocate(area);

      int s = m_p->m_iScan / sizeof(COLORREF);

      int maxsh = max(s, m_size.cy);

      m_iaVmin.allocate(maxsh);

      m_iaVmax.allocate(maxsh);

      return true;
      
   }


   bool fastblur::initialize(size sz, int32_t iRadius)
   {
      
      return initialize(sz.cx, sz.cy, iRadius);
      
   }



   bool fastblur::blur()
   {

      synch_lock ml(&user_mutex());

      m_p->map();

      bool b = false;
      
      try
      {

         b = s_fastblur(
               (uint32_t *) m_p->get_data(),
               m_size.cx, 
               m_size.cy, 
               m_iRadius,
               (uint32_t *) m_ucha.get_data(),
               m_uchaDiv.get_data(),
               m_p->m_iScan);

      }
      catch(...)
      {
      }


      return b;

   }

   bool fastblur::s_fastblur(uint32_t * pdata, int32_t w, int32_t h, int32_t radius, uint32_t * prgba, byte * dv, int32_t stride)
   {

      if (radius <= 0)
      {
         return false;
      }

      int32_t rsum, gsum, bsum, asum;
      int32_t x;
      int32_t y;
      int32_t i;
      int32_t yp;
      int32_t yw;
       byte * p1;
       byte * p2;
      int32_t wm = w - 1;
      int32_t hm = h - 1;
      int32_t wr = wm - radius;
      int32_t hr = hm - radius;
      //   int32_t div        = radius + radius + 1;
      int32_t * pix = (int32_t *)pdata;
      byte * pb = (byte *)pdata;
      byte * pwork = (byte *)prgba;
      byte * pwk = (byte *)prgba;
      byte * p;

      yw = 0;

      for (y = 0; y < h; y++)
      {

         pwork = &pwk[stride * y];

         asum = 0;
         rsum = 0;
         gsum = 0;
         bsum = 0;

         for (i = -radius; i <= radius; i++)
         {

            p = &pb[yw + (min(wm, max(i, 0)) * 4)];
            rsum += p[0];
            gsum += p[1];
            bsum += p[2];
            asum += p[3];

         }

         p1 = &pb[yw + (radius + 1) * 4];
         p2 = &pb[yw];

         for (x = 0; x < radius; x++)
         {

            pwork[0] = dv[rsum];
            pwork[1] = dv[gsum];
            pwork[2] = dv[bsum];
            pwork[3] = dv[asum];

            rsum += p1[0] - p2[0];
            gsum += p1[1] - p2[1];
            bsum += p1[2] - p2[2];
            asum += p1[3] - p2[3];

            pwork += 4;
            p1 += 4;

         }

         for (; x < wr; x++)
         {

            pwork[0] = dv[rsum];
            pwork[1] = dv[gsum];
            pwork[2] = dv[bsum];
            pwork[3] = dv[asum];


            rsum += p1[0] - p2[0];
            gsum += p1[1] - p2[1];
            bsum += p1[2] - p2[2];
            asum += p1[3] - p2[3];

            p1 += 4;
            p2 += 4;
            pwork += 4;

         }

         p1 -= 4;

         for (; x < w; x++)
         {

            pwork[0] = dv[rsum];
            pwork[1] = dv[gsum];
            pwork[2] = dv[bsum];
            pwork[3] = dv[asum];


            rsum += p1[0] - p2[0];
            gsum += p1[1] - p2[1];
            bsum += p1[2] - p2[2];
            asum += p1[3] - p2[3];

            p2 += 4;
            pwork += 4;

         }

         yw += stride;

      }

      for (x = 0; x < w; x++)
      {

         asum = 0;
         rsum = 0;
         gsum = 0;
         bsum = 0;

         yp = -radius * stride;

         for (i = -radius; i <= radius; i++)
         {
            p = &pwk[max(0, yp) + x * 4];
            rsum += p[0];
            gsum += p[1];
            bsum += p[2];
            asum += p[3];
            yp += stride;
         }

         byte * r1 = &pwk[(x * 4) + (radius + 1) * stride];
         byte * r2 = &pwk[(x * 4)];

         p1 = (byte *)&pix[x];

         for (y = 0; y < radius; y++)
         {

            p1[0] = dv[rsum];
            p1[1] = dv[gsum];
            p1[2] = dv[bsum];
            p1[3] = dv[asum];

            rsum += r1[0] - r2[0];
            gsum += r1[1] - r2[1];
            bsum += r1[2] - r2[2];
            asum += r1[3] - r2[3];

            p1 += stride;
            r1 += stride;

         }

         for (; y < hr; y++)
         {

            p1[0] = dv[rsum];
            p1[1] = dv[gsum];
            p1[2] = dv[bsum];
            p1[3] = dv[asum];

            rsum += r1[0] - r2[0];
            gsum += r1[1] - r2[1];
            bsum += r1[2] - r2[2];
            asum += r1[3] - r2[3];

            p1 += stride;
            r1 += stride;
            r2 += stride;

         }

         p1 -= stride;
         r1 -= stride;

         for (; y < h; y++)
         {

            p1[0] = dv[rsum];
            p1[1] = dv[gsum];
            p1[2] = dv[bsum];
            p1[3] = dv[asum];

            rsum += r1[0] - r2[0];
            gsum += r1[1] - r2[1];
            bsum += r1[2] - r2[2];
            asum += r1[3] - r2[3];

            p1 += stride;
            r2 += stride;

         }

      }

      return true;

   }


   bool fastblur::s_fastblur(uint32_t * pix, int32_t w, int32_t h, int32_t radius, byte * r, byte * g, byte * b, byte * a, byte * dv, int32_t stride, int32_t * vmin, int32_t * vmax)
   {

      return false;

/*      

      if (radius <= 0)
      {

         return false;

      }

      int32_t asum, rsum, gsum, bsum, x, y, i, yp, yi, yw;
      int32_t s = stride / sizeof(COLORREF);
      int32_t wm = w - 1;
      int32_t hm = h - 1;
      int32_t div = radius + radius + 1;
      int32_t p;
      int32_t p1;
      int32_t p2;

      yw = yi = 0;

      for (x = 0; x < w; x++)
      {
         vmin[x] = min(x + radius + 1, wm);
         vmax[x] = max(x - radius, 0);
      }

      for (y = 0; y < h; y++)
      {
         asum = rsum = gsum = bsum = 0;
         yi = y * s;
         for (i = -radius; i <= radius; i++)
         {
            p = pix[yi + min(wm, max(i, 0))];
            asum += ((p & 0xff000000) >> 24);
            rsum += ((p & 0xff0000) >> 16);
            gsum += ((p & 0x00ff00) >> 8);
            bsum += (p & 0x0000ff);
         }
         for (x = 0; x < w; x++)
         {
            a[yi] = dv[asum];
            r[yi] = dv[rsum];
            g[yi] = dv[gsum];
            b[yi] = dv[bsum];

            p1 = pix[yw + vmin[x]];
            p2 = pix[yw + vmax[x]];

            asum += ((p1 >> 24) & 0xff) - ((p2 >> 24) & 0xff);
            rsum += ((p1 & 0x00ff0000) - (p2 & 0x00ff0000)) >> 16;
            gsum += ((p1 & 0x0000ff00) - (p2 & 0x0000ff00)) >> 8;
            bsum += ((p1 & 0x000000ff) - (p2 & 0x000000ff));
            yi++;
         }
         yw += s;
      }
      for (y = 0; y < h; y++)
      {
         vmin[y] = min(y + radius + 1, hm) * s;
         vmax[y] = max(y - radius, 0) * s;
      }

      for (x = 0; x < w; x++)
      {
         asum = rsum = gsum = bsum = 0;
         yp = -radius*s;
         for (i = -radius; i <= radius; i++)
         {
            yi = max(0, yp) + x;
            rsum += r[yi];
            gsum += g[yi];
            bsum += b[yi];
            asum += a[yi];
            yp += s;
         }
         yi = x;
         for (y = 0; y < h; y++)
         {
            pix[yi] = (dv[asum] << 24) | (dv[rsum] << 16) | (dv[gsum] << 8) | dv[bsum];

            p1 = x + vmin[y];
            p2 = x + vmax[y];

            rsum += r[p1] - r[p2];
            gsum += g[p1] - g[p2];
            bsum += b[p1] - b[p2];
            asum += a[p1] - a[p2];

            yi += s;

         }

      }

      return true;
      
*/

   }







} // namespace visual
