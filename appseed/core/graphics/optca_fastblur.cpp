#include "framework.h"


bool optca_fastblur(uint32_t * pdata, int32_t w, int32_t h, int32_t radius, uint32_t * prgba, byte * dv, int32_t stride);


bool optca_fastblur(uint32_t * pdata, int32_t w, int32_t h, int32_t radius, uint32_t * prgba, byte * dv, int32_t stride)
{

   if(radius < 1)
   {
      return false;
   }

   register int32_t rsum,gsum,bsum,asum;
   int32_t x;
   int32_t y;
   int32_t i;
   int32_t yp;
   int32_t yw;
   register byte * p1;
   register byte * p2;
   int32_t wm         = w - 1;
   int32_t hm         = h - 1;
   int32_t wr         = wm - radius;
   int32_t hr         = hm - radius;
//   int32_t div        = radius + radius + 1;
   int32_t * pix      = (int32_t *) pdata;
   byte * pb      = (byte *) pdata;
   byte * pwork   = (byte *) prgba;
   byte * pwk     = (byte *) prgba;
   byte * p;

   yw = 0;

   for(y = 0; y < h; y++)
   {
      
      pwork = &pwk[stride * y];

      asum = 0;
      rsum = 0;
      gsum = 0;
      bsum = 0;

      for(i = -radius; i <= radius; i++)
      {

         p     =     &pb[yw +( min(wm, max(i, 0)) * 4)];
         rsum  +=    p[0];
         gsum  +=    p[1];
         bsum  +=    p[2];
         asum  +=    p[3];

      }

      p1 = &pb[yw + (radius + 1) * 4];
      p2 = &pb[yw];

      for(x = 0; x < radius; x++)
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
         p1    += 4;

      }

      for(; x < wr; x ++)
      {

         pwork[0] = dv[rsum];
         pwork[1] = dv[gsum];
         pwork[2] = dv[bsum];
         pwork[3] = dv[asum];


         rsum += p1[0] - p2[0];
         gsum += p1[1] - p2[1];
         bsum += p1[2] - p2[2];
         asum += p1[3] - p2[3];

         p1    += 4;
         p2    += 4;
         pwork += 4;

      }

      p1 -= 4;

      for(; x < w; x ++)
      {

         pwork[0] = dv[rsum];
         pwork[1] = dv[gsum];
         pwork[2] = dv[bsum];
         pwork[3] = dv[asum];


         rsum += p1[0] - p2[0];
         gsum += p1[1] - p2[1];
         bsum += p1[2] - p2[2];
         asum += p1[3] - p2[3];

         p2    += 4;
         pwork += 4;

      }

      yw += stride;

   }

   for(x = 0; x < w; x++)
   {
      
      asum = 0;
      rsum = 0;
      gsum = 0;
      bsum = 0;
      
      yp = -radius * stride;

      for(i = -radius; i <= radius; i++)
      {
         p = &pwk[max(0, yp) + x * 4];
         rsum  += p[0];
         gsum  += p[1];
         bsum  += p[2];
         asum  += p[3];
         yp += stride;
      }

      byte * r1 = &pwk[(x * 4) + (radius + 1) * stride];
      byte * r2 = &pwk[(x * 4)];

      p1 = (byte *) &pix[x];

      for(y = 0; y < radius; y++)
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

      for(; y < h; y++)
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
