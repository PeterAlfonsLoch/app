// Super Fast Blur v1.1
// by Mario Klingemann <http://incubator.quasimondo.com>
//
// Tip: Multiple invovations of this filter with a small
// radius will approximate a gaussian blur quite well.
//
#include "framework.h"


bool optca_fastblur(uint32_t * pdata, int32_t w, int32_t h, int32_t radius, uint32_t * prgba, byte * dv, int32_t stride);


namespace visual
{

   
   fastblur::fastblur(::ca2::allocatorsp allocer) :
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
      
      if(!m_p->create(cx, cy))
         return false;

      int32_t h         = cy;
      int32_t scan      = m_p->scan;
      int32_t div       = radius + radius + 1;
      m_iRadius         = radius;
      m_uchaDiv.set_size(256 * div);
      byte * dv         = m_uchaDiv.get_data();

      m_size.cx         = cx;
      m_size.cy         = cy;


      for(int32_t i = 0; i < m_uchaDiv.get_count(); i++)
      {
         dv[i]= min(255, i/div);
      }

      return true;
      
   }

   bool fastblur::initialize(size sz, int32_t iRadius)
   {
      
      return initialize(sz.cx, sz.cy, iRadius);
      
   }



   bool fastblur::blur()
   {

      mutex_lock ml(user_mutex());

      m_p->map();
      m_ucha.set_size(m_p->scan * m_p->cy);

      bool b = false;

      try
      {

         b = optca_fastblur((uint32_t *) m_p->get_data(), m_size.cx, m_size.cy, m_iRadius, (uint32_t *) m_ucha.get_data(), m_uchaDiv.get_data(), m_p->scan);

      }
      catch(...)
      {
      }


      return b;

      /*int32_t radius  = m_iRadius;
      int32_t w       = m_size.cx;
      int32_t h       = m_size.cy;

      if(radius < 1)
      {
         return false;
      }

      if(w <= 0 || h <= 0)
      {
         return false;
      }

      register int32_t rsum,gsum,bsum,asum;
      int32_t x,y,i,yp,yi,yw,p;
      register int32_t * p1;
      register int32_t * p2;
      register int32_t c1;
      register int32_t c2;
      int32_t wm      = w - 1;
      int32_t hm      = h - 1;
      int32_t wr      = wm - radius;
      int32_t hr      = hm - radius;
      int32_t div     = radius + radius + 1;
      int32_t * r     = m_iaR.get_data();
      int32_t * g     = m_iaG.get_data();
      int32_t * b     = m_iaB.get_data();
      int32_t * a     = m_iaA.get_data();
      int32_t * pix   = (int32_t *) m_p->get_data();
  //    int32_t * dv    = m_iaDv.get_data();

      yw = yi = 0;

      int32_t * pr = r;
      int32_t * pg = g;
      int32_t * pb = b;
      int32_t * pa = a;


      for (y=0;y<h;y++)
      {
         asum=rsum=gsum=bsum=0;
         for(i=-radius;i<=radius;i++)
         {
            p=pix[yi+min(wm,max(i,0))];
            asum+=((p & 0xff000000)>>24);
            rsum+=((p & 0xff0000)>>16);
            gsum+=((p & 0x00ff00)>>8);
            bsum+=(p & 0x0000ff);
         }
         p1 = &pix[yw + radius + 1];
         p2 = &pix[yw];

         c2 = *p2;
         for(x = 0; x < radius; x++)
         {
            //*pa++ = dv[asum];
            //*pr++ = dv[rsum];
            //*pg++ = dv[gsum];
            //*pb++ = dv[bsum];
            *pa++ = asum / div;
            *pr++ = rsum / div;
            *pg++ = gsum / div;
            *pb++ = bsum / div;

            c1 = *p1++;

            asum+= ((c1 >> 24) & 0xff )-((c2 >> 24) & 0xff);
            rsum+= ((c1 & 0x00ff0000)-(c2 & 0x00ff0000))>>16;
            gsum+= ((c1 & 0x0000ff00)-(c2 & 0x0000ff00))>>8;
            bsum+= ((c1 & 0x000000ff)-(c2 & 0x000000ff));

            yi++;
         }

         for(; x < wr; x ++)
         {

            //*pa++ = dv[asum];
            //*pr++ = dv[rsum];
            //*pg++ = dv[gsum];
            //*pb++ = dv[bsum];
            *pa++ = asum / div;
            *pr++ = rsum / div;
            *pg++ = gsum / div;
            *pb++ = bsum / div;

            c1 = *p1++;
            c2 = *p2++;

            asum += ((c1 >> 24) & 0xff )-((c2 >> 24) & 0xff);
            rsum += ((c1 & 0x00ff0000)-(c2 & 0x00ff0000))>>16;
            gsum += ((c1 & 0x0000ff00)-(c2 & 0x0000ff00))>>8;
            bsum += ((c1 & 0x000000ff)-(c2 & 0x000000ff));

            yi++;

         }
         p1--;
         c1 = *p1;
         for(; x < w; x ++)
         {

            //*pa++ = dv[asum];
            //*pr++ = dv[rsum];
            //*pg++ = dv[gsum];
            //*pb++ = dv[bsum];
            *pa++ = asum / div;
            *pr++ = rsum / div;
            *pg++ = gsum / div;
            *pb++ = bsum / div;

            c2 = *p2++;

            asum += ((c1 >> 24) & 0xff )-((c2 >> 24) & 0xff);
            rsum += ((c1 & 0x00ff0000)-(c2 & 0x00ff0000))>>16;
            gsum += ((c1 & 0x0000ff00)-(c2 & 0x0000ff00))>>8;
            bsum += ((c1 & 0x000000ff)-(c2 & 0x000000ff));

            yi++;

         }


         yw+=w;
      }




      for (x=0;x<w;x++)
      {
         asum=rsum=gsum=bsum=0;
         yp=-radius*w;
         for(i=-radius;i<=radius;i++)
         {
            yi=max(0,yp)+x;
            rsum+=r[yi];
            gsum+=g[yi];
            bsum+=b[yi];
            asum+=a[yi];
            yp+=w;
         }
         int32_t i1 = x + (radius + 1) * w;
         int32_t i2 = x + 0;
         p1 = &pix[x];
         for (y=0;y<radius;y++)
         {
//            *p1 = (dv[asum]<<24) | (dv[rsum]<<16) | (dv[gsum]<<8) | dv[bsum];
            *p1 = ((asum / div) <<24) | ((rsum / div)<<16) | ((gsum / div)<<8) | (bsum / div);

            rsum+=r[i1]-r[i2];
            gsum+=g[i1]-g[i2];
            bsum+=b[i1]-b[i2];
            asum+=a[i1]-a[i2];

            p1+=w;
            i1+=w;
         }
         for (;y<hr;y++)
         {
//            *p1 = (dv[asum]<<24) | (dv[rsum]<<16) | (dv[gsum]<<8) | dv[bsum];
            *p1 = ((asum / div) <<24) | ((rsum / div)<<16) | ((gsum / div)<<8) | (bsum / div);

            rsum+=r[i1]-r[i2];
            gsum+=g[i1]-g[i2];
            bsum+=b[i1]-b[i2];
            asum+=a[i1]-a[i2];

            p1+=w;
            i1+=w;
            i2+=w;
         }
         i1-=w;
         for(;y<h;y++)
         {
//            *p1 = (dv[asum]<<24) | (dv[rsum]<<16) | (dv[gsum]<<8) | dv[bsum];
            *p1 = ((asum / div) <<24) | ((rsum / div)<<16) | ((gsum / div)<<8) | (bsum / div);

            rsum+=r[i1]-r[i2];
            gsum+=g[i1]-g[i2];
            bsum+=b[i1]-b[i2];
            asum+=a[i1]-a[i2];

            p1+=w;
            i2+=w;
         }
      }*/
   }


} // namespace visual
