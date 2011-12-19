#include "StdAfx.h"



bool optca_fastblur(DWORD * pdata, int w, int h, int radius, int * a, int * r, int * g, int * b)
{

   if(radius < 1)
   {
      return false;
   }

   register int rsum,gsum,bsum,asum;
   int x,y,i,yp,yi,yw,p;
   register int * p1;
   register int * p2;
   register int c1;
   register int c2;
   int wm      = w - 1;
   int hm      = h - 1;
   int wr      = wm - radius;
   int hr      = hm - radius;
   int div     = radius + radius + 1;
   int * pix   = (int *) pdata;

   yw = yi = 0;

   int * pr = r;
   int * pg = g;
   int * pb = b;
   int * pa = a;

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
      int i1 = x + (radius + 1) * w;
      int i2 = x + 0;
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
   }

   return true;

}
