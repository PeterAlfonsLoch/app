#include "framework.h"



bool optca_fastblur(DWORD * pdata, int w, int h, int radius, DWORD * prgba, byte * dv)
{

   if(radius < 1)
   {
      return false;
   }

   register int rsum,gsum,bsum,asum;
   int x;
   int y;
   int i;
   int yp;
   int yw;
   register byte * p1;
   register byte * p2;
   int wm      = w - 1;
   int hm      = h - 1;
   int wr      = wm - radius;
   int hr      = hm - radius;
   int div     = radius + radius + 1;
   int * pix   = (int *) pdata;
   byte * p;
   byte * pwork = (byte *) prgba;

   yw = 0;

   for (y=0;y<h;y++)
   {
      
      asum = 0;
      rsum = 0;
      gsum = 0;
      bsum = 0;

      for(i=-radius;i<=radius;i++)
      {

         p     =     (byte*)&pix[yw+min(wm,max(i,0))];
         rsum  +=    p[0];
         gsum  +=    p[1];
         bsum  +=    p[2];
         asum  +=    p[3];

      }

      p1 = (byte *) &pix[yw + radius + 1];
      p2 = (byte *) &pix[yw];

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

      p1--;

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

      yw += w;

   }

   int w4 = w * 4;


   for (x=0;x<w;x++)
   {
      
      asum = 0;
      rsum = 0;
      gsum = 0;
      bsum = 0;
      
      yp = -radius*w;

      for(i=-radius;i<=radius;i++)
      {
         p = (byte*) &((int *)prgba)[max(0, yp) + x];
         rsum  += p[0];
         gsum  += p[1];
         bsum  += p[2];
         asum  += p[3];
         yp += w;
      }
      byte * r1 = (byte *) &prgba[x + (radius + 1) * w];
      byte * r2 = (byte *) &prgba[x + 0];

      p1 = (byte *) &pix[x];

      for (y=0;y<radius;y++)
      {
         
         p1[0] = dv[rsum];
         p1[1] = dv[gsum];
         p1[2] = dv[bsum];
         p1[3] = dv[asum];

         rsum += r1[0] - r2[0];
         gsum += r1[1] - r2[1];
         bsum += r1[2] - r2[2];
         asum += r1[3] - r2[3];

         p1 += w4;
         r1 += w4;
      }

      for (;y<hr;y++)
      {

         p1[0] = dv[rsum];
         p1[1] = dv[gsum];
         p1[2] = dv[bsum];
         p1[3] = dv[asum];

         rsum += r1[0] - r2[0];
         gsum += r1[1] - r2[1];
         bsum += r1[2] - r2[2];
         asum += r1[3] - r2[3];

         p1 += w4;
         r1 += w4;
         r2 += w4;
      }
      
      p1 -= w4;
      r1 -= w4;

      for(;y<h;y++)
      {
      
         p1[0] = dv[rsum];
         p1[1] = dv[gsum];
         p1[2] = dv[bsum];
         p1[3] = dv[asum];

         rsum += r1[0] - r2[0];
         gsum += r1[1] - r2[1];
         bsum += r1[2] - r2[2];
         asum += r1[3] - r2[3];

         p1 += w4;
         r2 += w4;
      }

   }

   return true;

}
