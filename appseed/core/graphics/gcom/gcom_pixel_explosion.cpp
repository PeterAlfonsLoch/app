#include "framework.h"


namespace gcom
{


   pixel_explosion::pixel_explosion()
   {

      m_iWidth = 0;
      m_iHeight = 0;

      m_bDrawWithLight = TRUE;
      m_iLightModifier = 1;
      m_iHpage = 0;
      m_density = 5;
   }

   pixel_explosion::~pixel_explosion()
   {
      // Cleanup
   }
   void pixel_explosion::create(int32_t iWidth,int32_t iHeight)
   {
      m_pointa.allocate(iWidth * iHeight);
      m_pointaM.allocate(iWidth * iHeight);


      m_iWidth = iWidth;
      m_iHeight = iHeight;

      // set our page to 0
      m_iHpage = 0;

   }
   void pixel_explosion::FlattenWater()
   {
      // clear our height fields
   }
   void pixel_explosion::to(COLORREF * pSrcImage, COLORREF * pTargetImage)
   {
      int32_t i = 0;

      // Yes they have to be the same size...(for now)
      DrawWaterNoLight(m_iHpage,pSrcImage,pTargetImage);
      if(i == 2)
      {
         Calc2(m_iHpage, (int32_t)m_density);
      }
      else
      {
         CalcWater(m_iHpage, (int32_t) m_density);
      }


      m_iHpage ^= 1;

   }

   void pixel_explosion::CalcWater(int32_t npage, int32_t density)
   {
      UNREFERENCED_PARAMETER(npage);
      UNREFERENCED_PARAMETER(density);
      int32_t imin = - m_iWidth / 2;
      int32_t imax = m_iWidth / 2;
      int32_t jmin = - m_iHeight / 2;
      int32_t jmax = m_iHeight / 2;
      int32_t i, j;
      int32_t x, y;

      double dr;
      double dcos;
      double dsin;



      double dmax = MIN(m_iWidth, m_iHeight);

      double dm = dmax / 3;

      if(m_minradius > 0.0)
      {
         dm = m_minradius;
      }


      double m, n;


      int32_t k = 0;
      for(y = 0, j = jmin; j < jmax; j++, y++)
      {
         for(x = 0, i = imin; i < imax; i++, x++)
         {
            m = m_pointa[k].x;
            n = m_pointa[k].y;


            dr = sqrt(m * m + n * n);
            double d;
            if(abs(dr) < dm)
            {
               double da = rand() * 3.1415 * 2 / RAND_MAX;
               dcos = cos(da);
               dsin = sin(da);
               dr = rand() * dm * 1.2 / RAND_MAX;;
               d = 1.0;
            }
            else
            {

               dcos = m / dr;
               dsin = n / dr;
            }

            d = dr / dmax;


            //d = sqrt(d);

            // i = x + y * width
            m_pointa[k].x = dr * dcos * (rand() * density * d / RAND_MAX + 1.0);
            m_pointa[k].y = dr * dsin * (rand() * density * d / RAND_MAX + 1.0);
            //m_pointa[k].x = dr * dcos * (1000 * 0.2 * d / RAND_MAX + 1.0);
            //m_pointa[k].y = dr * dsin * (1000 * 0.2 * d / RAND_MAX + 1.0);
            //m_pointa[k].x = dr * dcos * 1.2 * d;
            //m_pointa[k].y = dr * dsin * 1.2 * d;
            k++;
         }
      }


   }

   void pixel_explosion::Calc2(int32_t npage, int32_t density)
   {
      UNREFERENCED_PARAMETER(npage);
      UNREFERENCED_PARAMETER(density);
      m_z *= 1.1;

      int32_t imin = - m_iWidth / 2;
      int32_t imax = m_iWidth / 2;
      int32_t jmin = - m_iHeight / 2;
      int32_t jmax = m_iHeight / 2;
      int32_t i, j;
      int32_t x, y;

      double dr;
      double dcos;
      double dsin;

      double dmax = sqrt((double) (imax * imax + jmax * jmax));

      if(m_z > dmax) m_z = dmax;
      //double dmax = MIN(m_iWidth, m_iHeight);
      //double dmax = MAX(m_iWidth, m_iHeight) * 2;

      double m, n, o;


      int32_t k = 0;
      for(y = 0, j = jmin; j < jmax; j++, y++)
      {
         for(x = 0, i = imin; i < imax; i++, x++)
         {
            m = m_pointa[k].x;
            n = m_pointa[k].y;
            o = m_pointa[k].z;


            dr = sqrt(m * m + n * n);
            double d = m_z;
            if(dr < 10.0)
            {
               double da = rand() * 3.1415 * 2 / RAND_MAX;
               dcos = cos(da);
               dsin = sin(da);
               //dr = 1.0;
               dr = MAX(2.0, d);
               //o = 0;
            }
            else
            {

               dcos = m / dr;
               dsin = n / dr;
            }



            //d = sqrt(d);

            //int32_t rnd =
            // i = x + y * width
            m_pointa[k].x = dr * dcos * (rand() * 0.5 * d / RAND_MAX + 1.0);
            m_pointa[k].y = dr * dsin * (rand() * 0.5 * d / RAND_MAX + 1.0);
//               m_pointa[k].x = i * d;
//             m_pointa[k].y = j * d;
            m_pointa[k].x = dr * dcos * 1.2 * d;
            m_pointa[k].y = dr * dsin * 1.2 * d;
            k++;
         }
      }


   }
   void pixel_explosion::SmoothWater(int32_t npage)
   {
      UNREFERENCED_PARAMETER(npage);
   }

   void pixel_explosion::CalcWaterBigFilter(int32_t npage, int32_t density)
   {
      UNREFERENCED_PARAMETER(npage);
      UNREFERENCED_PARAMETER(density);
   }

   void pixel_explosion::Reset()
   {
      m_z = 0.1;
      int32_t imin = - m_iWidth / 2;
      int32_t imax = m_iWidth / 2;
      int32_t jmin = - m_iHeight / 2;
      int32_t jmax = m_iHeight / 2;

      double MAX = imax * imax + jmax * jmax;
      //double MAX = MAX(imax, jmax) * 2;
   //   MAX = 2 * MAX;

      int32_t k = 0;
      int32_t i, j;
      for(j = jmin; j < jmax; j++)
      {
         for(i = imin; i < imax; i++)
         {

            m_pointaM[k].x = i;
            m_pointaM[k].x = j;
            m_pointaM[k].z = sqrt(MAX - (i * i + j * j));
            m_pointa[k].x = i;
            m_pointa[k].y = j;
            m_pointa[k].z = m_pointaM[k].z;
            k++;
         }
      }

   }

   void pixel_explosion::HeightBox (int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(radius);
      UNREFERENCED_PARAMETER(height);
      UNREFERENCED_PARAMETER(page);
   }


   void pixel_explosion::WarpBlob(int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(radius);
      UNREFERENCED_PARAMETER(height);
      UNREFERENCED_PARAMETER(page);
   }

   void pixel_explosion::SineBlob(int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(radius);
      UNREFERENCED_PARAMETER(height);
      UNREFERENCED_PARAMETER(page);
   }

   void pixel_explosion::DrawWaterNoLight(int32_t page, COLORREF * pSrcImage, COLORREF * pTargetImage)
   {
      UNREFERENCED_PARAMETER(page);
   //  int32_t ox, oy;
     int32_t x, y;

      int32_t mx = m_iWidth / 2;
      int32_t my = m_iHeight / 2;


//        int32_t offset=m_iWidth + 1;


     for (y = 0; y < m_iHeight; y++)
     {
       for (x = 0; x < m_iWidth; x++)
       {
          int32_t i = x + y * m_iWidth;
          int32_t newx = (int32_t) m_pointa[i].x + mx;
          if(newx < 0 || newx >= m_iWidth)
             continue;
          int32_t newy = (int32_t) m_pointa[i].y + my;
          if(newy < 0 || newy >= m_iHeight)
             continue;

          pTargetImage[newx + newy * m_iWidth] =
               pSrcImage[x + y * m_iWidth];

       }
     }
   }

   COLORREF pixel_explosion::GetShiftedColor(COLORREF color,int32_t shift)
   {
      int32_t R;
      int32_t G;
      int32_t B;
      int32_t ir;
      int32_t ig;
      int32_t ib;

      R = rgba_get_r(color)-shift;
      G = rgba_get_g(color)-shift;
      B = rgba_get_b(color)-shift;

      ir = (R < 0) ? 0 : (R > 255) ? 255 : R;
      ig = (G < 0) ? 0 : (G > 255) ? 255 : G;
      ib = (B < 0) ? 0 : (B > 255) ? 255 : B;

      return ARGB(255, ir,ig,ib);
   }


} // namespace gcom



