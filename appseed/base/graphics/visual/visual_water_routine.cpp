#include "framework.h"


namespace visual
{

   water_routine::water_routine()
   {
      m_iHeightField1 = NULL;
      m_iHeightField2 = NULL;

      m_iWidth = 0;
      m_iHeight = 0;

      m_bDrawWithLight = TRUE;
      m_iLightModifier = 1;
      m_iHpage = 0;
      m_density = 5;
   }

   water_routine::~water_routine()
   {
      // Cleanup
      if(m_iHeightField1 != NULL)
         delete [] m_iHeightField1;
      if(m_iHeightField2 != NULL)
         delete [] m_iHeightField2;

      m_iHeightField1 = NULL;
      m_iHeightField2 = NULL;
   }
   void water_routine::create(int32_t iWidth,int32_t iHeight)
   {
      if(m_iHeightField1 != NULL)
         delete [] m_iHeightField1;
      if(m_iHeightField2 != NULL)
         delete [] m_iHeightField2;

      // create our height fields
      m_iHeightField1 = new int32_t[(iWidth*iHeight)];
      m_iHeightField2 = new int32_t[(iWidth*iHeight)];

      // clear our height fields
      memset(m_iHeightField1,0,(iWidth*iHeight)*sizeof(int32_t));
      memset(m_iHeightField2,0,(iWidth*iHeight)*sizeof(int32_t));

      m_iWidth = iWidth;
      m_iHeight = iHeight;

      // set our page to 0
      m_iHpage = 0;

   }
   void water_routine::FlattenWater()
   {
      // clear our height fields
      memset(m_iHeightField1,0,(m_iWidth*m_iHeight)*sizeof(int32_t));
      memset(m_iHeightField2,0,(m_iWidth*m_iHeight)*sizeof(int32_t));
   }
   void water_routine::to(COLORREF * pSrcImage, COLORREF * pTargetImage)
   {
      // Yes they have to be the same size...(for now)
      if(m_bDrawWithLight == FALSE)
      {
         DrawWaterNoLight(m_iHpage,pSrcImage,pTargetImage);
      }
      else
      {
         DrawWaterWithLight(m_iHpage,m_iLightModifier,pSrcImage,pTargetImage);
      }
      CalcWater(m_iHpage,m_density);


      m_iHpage ^= 1;

   }
   void water_routine::CalcWater(int32_t npage, int32_t density)
   {
     int32_t newh;
     int32_t count = m_iWidth + 1;
     int32_t *newptr;
     int32_t *oldptr;

     // set up the pointers
     if(npage == 0)
     {
      newptr = &m_iHeightField1[0];
      oldptr = &m_iHeightField2[0];
     }
     else
     {
      newptr = &m_iHeightField2[0];
      oldptr = &m_iHeightField1[0];
     }

     int32_t x, y;

     // Sorry, this function might not be as readable as I'd like, because
     // I optimized it somewhat.  (enough to make me feel satisfied with it)

     for (y = (m_iHeight-1)*m_iWidth; count < y; count += 2)
     {
       for (x = count+m_iWidth-2; count < x; count++)
       {

   // This does the eight-pixel method.  It looks much better.

         newh          = ((oldptr[count + m_iWidth]
                         + oldptr[count - m_iWidth]
                         + oldptr[count + 1]
                         + oldptr[count - 1]
                         + oldptr[count - m_iWidth - 1]
                         + oldptr[count - m_iWidth + 1]
                         + oldptr[count + m_iWidth - 1]
                         + oldptr[count + m_iWidth + 1]
                          ) >> 2 )
                         - newptr[count];


         newptr[count] =  newh - (newh >> density);
   /*
   // This is the "sludge" method...
         newh = (oldptr[count]<<2)
              +  oldptr[count-1-m_iWidth]
              +  oldptr[count+1-m_iWidth]
              +  oldptr[count-1+m_iWidth]
              +  oldptr[count+1+m_iWidth]
              + ((oldptr[count-1]
              +   oldptr[count+1]
              +   oldptr[count-m_iWidth]
              +   oldptr[count+m_iWidth])<<1);

         newptr[count] = (newh-(newh>>6)) >> density;
   */
       }
     }
   }
   void water_routine::SmoothWater(int32_t npage)
   {
     int32_t newh;
     int32_t count = m_iWidth + 1;

     int32_t *newptr;
     int32_t *oldptr;

     // set up the pointers
     if(npage == 0)
     {
      newptr = &m_iHeightField1[0];
      oldptr = &m_iHeightField2[0];
     }
     else
     {
      newptr = &m_iHeightField2[0];
      oldptr = &m_iHeightField1[0];
     }


     int32_t x, y;

     // Sorry, this function might not be as readable as I'd like, because
     // I optimized it somewhat.  (enough to make me feel satisfied with it)

     for(y=1; y<m_iHeight-1; y++)
     {
       for(x=1; x<m_iWidth-1; x++)
       {
   // This does the eight-pixel method.  It looks much better.

         newh          = ((oldptr[count + m_iWidth]
                         + oldptr[count - m_iWidth]
                         + oldptr[count + 1]
                         + oldptr[count - 1]
                         + oldptr[count - m_iWidth - 1]
                         + oldptr[count - m_iWidth + 1]
                         + oldptr[count + m_iWidth - 1]
                         + oldptr[count + m_iWidth + 1]
                          ) >> 3 )
                         + newptr[count];


         newptr[count] =  newh>>1;
         count++;
       }
       count += 2;
     }
   }

   void water_routine::CalcWaterBigFilter(int32_t npage, int32_t density)
   {
     int32_t newh;
     int32_t count = (2*m_iWidth) + 2;

     int32_t *newptr;
     int32_t *oldptr;

     // set up the pointers
     if(npage == 0)
     {
      newptr = &m_iHeightField1[0];
      oldptr = &m_iHeightField2[0];
     }
     else
     {
      newptr = &m_iHeightField2[0];
      oldptr = &m_iHeightField1[0];
     }

     int32_t x, y;

     // Sorry, this function might not be as readable as I'd like, because
     // I optimized it somewhat.  (enough to make me feel satisfied with it)

     for(y=2; y<m_iHeight-2; y++)
     {
       for(x=2; x<m_iWidth-2; x++)
       {
   // This does the 25-pixel method.  It looks much okay.

         newh        = (
                        (
                         (
                          (oldptr[count + m_iWidth]
                         + oldptr[count - m_iWidth]
                         + oldptr[count + 1]
                         + oldptr[count - 1]
                          )<<1)
                         + ((oldptr[count - m_iWidth - 1]
                         + oldptr[count - m_iWidth + 1]
                         + oldptr[count + m_iWidth - 1]
                         + oldptr[count + m_iWidth + 1]))
                         + ( (
                             oldptr[count - (m_iWidth*2)]
                           + oldptr[count + (m_iWidth*2)]
                           + oldptr[count - 2]
                           + oldptr[count + 2]
                           ) >> 1 )
                         + ( (
                             oldptr[count - (m_iWidth*2) - 1]
                           + oldptr[count - (m_iWidth*2) + 1]
                           + oldptr[count + (m_iWidth*2) - 1]
                           + oldptr[count + (m_iWidth*2) + 1]
                           + oldptr[count - 2 - m_iWidth]
                           + oldptr[count - 2 + m_iWidth]
                           + oldptr[count + 2 - m_iWidth]
                           + oldptr[count + 2 + m_iWidth]
                           ) >> 2 )
                        )
                       >> 3)
                       - (newptr[count]);


         newptr[count] =  newh - (newh >> density);
         count++;
       }
       count += 4;
     }
   }

   void water_routine::HeightBlob(int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page)
   {
     int32_t rquad;
     int32_t cx, cy, cyq;
     int32_t left, top, right, bottom;

     int32_t *newptr;
     int32_t *oldptr;

     // set up the pointers
     if(page == 0)
     {
      newptr = &m_iHeightField1[0];
      oldptr = &m_iHeightField2[0];
     }
     else
     {
      newptr = &m_iHeightField2[0];
      oldptr = &m_iHeightField1[0];
     }

     rquad = radius * radius;

     // Make a randomly-placed blob...
     if(x<0) x = 1+radius+ rand()%(m_iWidth-2*radius-1);
     if(y<0) y = 1+radius+ rand()%(m_iHeight-2*radius-1);

     left=-radius; right = radius;
     top=-radius; bottom = radius;

     // Perform edge clipping...
     if(x - radius < 1) left -= (x-radius-1);
     if(y - radius < 1) top  -= (y-radius-1);
     if(x + radius > m_iWidth-1) right -= (x+radius-m_iWidth+1);
     if(y + radius > m_iHeight-1) bottom-= (y+radius-m_iHeight+1);


     for(cy = top; cy < bottom; cy++)
     {
       cyq = cy*cy;
       for(cx = left; cx < right; cx++)
       {
         if(cx*cx + cyq < rquad)
           newptr[m_iWidth*(cy+y) + (cx+x)] += height;
       }
     }

   }

   void water_routine::HeightBox (int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page)
   {
     int32_t cx, cy;
     int32_t left, top, right, bottom;
     int32_t *newptr;
     int32_t *oldptr;

     // set up the pointers
     if(page == 0)
     {
      newptr = &m_iHeightField1[0];
      oldptr = &m_iHeightField2[0];
     }
     else
     {
      newptr = &m_iHeightField2[0];
      oldptr = &m_iHeightField1[0];
     }

     if(x<0) x = 1+radius+ rand()%(m_iWidth-2*radius-1);
     if(y<0) y = 1+radius+ rand()%(m_iHeight-2*radius-1);

     left=-radius; right = radius;
     top=-radius; bottom = radius;

     // Perform edge clipping...
     if(x - radius < 1) left -= (x-radius-1);
     if(y - radius < 1) top  -= (y-radius-1);
     if(x + radius > m_iWidth-1) right -= (x+radius-m_iWidth+1);
     if(y + radius > m_iHeight-1) bottom-= (y+radius-m_iHeight+1);

     for(cy = top; cy < bottom; cy++)
     {
       for(cx = left; cx < right; cx++)
       {
           newptr[m_iWidth*(cy+y) + (cx+x)] = height;
       }
     }

   }


   void water_routine::WarpBlob(int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page)
   {
     int32_t cx, cy;
     int32_t left,top,right,bottom;
     int32_t square;
     int32_t radsquare = radius * radius;
     int32_t *newptr;
     int32_t *oldptr;

     // set up the pointers
     if(page == 0)
     {
      newptr = &m_iHeightField1[0];
      oldptr = &m_iHeightField2[0];
     }
     else
     {
      newptr = &m_iHeightField2[0];
      oldptr = &m_iHeightField1[0];
     }
   //  radsquare = (radius*radius) << 8;
     radsquare = (radius*radius);

     height /= 64;

     left=-radius; right = radius;
     top=-radius; bottom = radius;

     // Perform edge clipping...
     if(x - radius < 1) left -= (x-radius-1);
     if(y - radius < 1) top  -= (y-radius-1);
     if(x + radius > m_iWidth-1) right -= (x+radius-m_iWidth+1);
     if(y + radius > m_iHeight-1) bottom-= (y+radius-m_iHeight+1);

     for(cy = top; cy < bottom; cy++)
     {
       for(cx = left; cx < right; cx++)
       {
         square = cy*cy + cx*cx;
   //      square <<= 8;
         if(square < radsquare)
         {
   //        height[page][WATERWID*(cy+y) + cx+x]
   //          += (sqrt(radsquare)-sqrt(square))*height;
           newptr[m_iWidth*(cy+y) + cx+x]
             += int32_t((radius-sqrt((float)square))*(float)(height));
         }
       }
     }
   }

   void water_routine::SineBlob(int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page)
   {
     int32_t cx, cy;
     int32_t left,top,right,bottom;
     int32_t square, dist;
     int32_t radsquare = radius * radius;
     float length = float((1024.0/(float)radius)*(1024.0/(float)radius));
     int32_t *newptr;
     int32_t *oldptr;

     // set up the pointers
     if(page == 0)
     {
      newptr = &m_iHeightField1[0];
      oldptr = &m_iHeightField2[0];
     }
     else
     {
      newptr = &m_iHeightField2[0];
      oldptr = &m_iHeightField1[0];
     }

     if(x<0) x = 1+radius+ rand()%(m_iWidth-2*radius-1);
     if(y<0) y = 1+radius+ rand()%(m_iHeight-2*radius-1);


   //  radsquare = (radius*radius) << 8;
     radsquare = (radius*radius);

   //  height /= 8;

     left=-radius; right = radius;
     top=-radius; bottom = radius;


     // Perform edge clipping...
     if(x - radius < 1) left -= (x-radius-1);
     if(y - radius < 1) top  -= (y-radius-1);
     if(x + radius > m_iWidth-1) right -= (x+radius-m_iWidth+1);
     if(y + radius > m_iHeight-1) bottom-= (y+radius-m_iHeight+1);

     for(cy = top; cy < bottom; cy++)
     {
       for(cx = left; cx < right; cx++)
       {
         square = cy*cy + cx*cx;
         if(square < radsquare)
         {
           dist = int32_t(sqrt(square*length));
           newptr[m_iWidth*(cy+y) + cx+x]
             += (int32_t)((cos((float) dist)+0xffff)*(height)) >> 19;
         }
       }
     }
   }

   void water_routine::DrawWaterNoLight(int32_t page, COLORREF * pSrcImage, COLORREF * pTargetImage)
   {
      UNREFERENCED_PARAMETER(page);
   //  int32_t ox, oy;
     int32_t dx, dy;
     int32_t x, y;
     uint32_t ca;

     int32_t offset=m_iWidth + 1;

     int32_t *ptr = &m_iHeightField1[0];

     for (y = (m_iHeight-1)*m_iWidth; offset < y; offset += 2)
     {
       for (x = offset+m_iWidth-2; offset < x; offset++)
       {
         dx = ptr[offset] - ptr[offset+1];
         dy = ptr[offset] - ptr[offset+m_iWidth];

        //Shading = dx;?
        // Water draw method?
   //      ca = BkGdImage[offset + WATERWID*(dy>>3) + (dx>>3)];
        ca = pSrcImage[offset + m_iWidth*(dy>>3) + (dx>>3)];

        // If anyone knows a better/faster way to do this, please tell me...
   //      temp[offset] = (ca < 0) ? 0 : (ca > 255) ? 255 : ca;
        pTargetImage[offset] = ca;

         offset++;
         dx = ptr[offset] - ptr[offset+1];
         dy = ptr[offset] - ptr[offset+m_iWidth];
   //    ca = BkGdImage[offset + m_iWidth*(dy>>3) + (dx>>3)];
        ca = pSrcImage[offset + m_iWidth*(dy>>3) + (dx>>3)];
        pTargetImage[offset] = ca;
   //      temp[offset] = (ca < 0) ? 0 : (ca > 255) ? 255 : ca;
    
       }
     }
   }

   void water_routine::DrawWaterWithLight(int32_t page, int32_t LightModifier ,COLORREF * pSrcImage, COLORREF * pTargetImage)
   {
      UNREFERENCED_PARAMETER(page);
      UNREFERENCED_PARAMETER(LightModifier);
   //  int32_t ox, oy;
     int32_t dx, dy;
     int32_t x, y;
     uint32_t ca;

     int32_t offset=m_iWidth + 1;
     long lIndex;
     long lBreak = m_iWidth*m_iHeight;

     int32_t *ptr = &m_iHeightField1[0];


     for (y = (m_iHeight-2)*m_iWidth; offset < y; )
     {
       for (x = offset+m_iWidth-2; offset < x; offset++)
       {
         dx = ptr[offset] - ptr[offset+1];
         dy = ptr[offset] - ptr[offset+m_iWidth];

        lIndex = offset + m_iWidth*(dy>>3) + (dx>>3);
        if(lIndex < lBreak && lIndex > 0)
        {
           ca = pSrcImage[lIndex];// - (dx>>LightModifier);
           // Now we shift it by the dx component...
           // 
           ca = GetShiftedColor(ca,dx);

            pTargetImage[offset] = ca;
         }

         offset++;
         dx = ptr[offset] - ptr[offset+1];
         dy = ptr[offset] - ptr[offset+m_iWidth];

        lIndex = offset + m_iWidth*(dy>>3) + (dx>>3);
        if(lIndex < lBreak && lIndex > 0)
        {
           ca = pSrcImage[lIndex];// - (dx>>LightModifier);
           ca = GetShiftedColor(ca,dx);
      //      temp[offset] = (ca < 0) ? 0 : (ca > 255) ? 255 : ca;
           pTargetImage[offset] = ca;
        }
    
       }
     }
    
   }
   inline COLORREF water_routine::GetShiftedColor(COLORREF color,int32_t shift)
   {
      long R;
      long G;
      long B;
      long ir;
      long ig;
      long ib;

      R = rgba_get_r(color)-shift;
      G = rgba_get_g(color)-shift;
      B = rgba_get_b(color)-shift;

      ir = (R < 0) ? 0 : (R > 255) ? 255 : R;
      ig = (G < 0) ? 0 : (G > 255) ? 255 : G;
      ib = (B < 0) ? 0 : (B > 255) ? 255 : B;

      return RGB(ir,ig,ib);
   }

} // namespace visual