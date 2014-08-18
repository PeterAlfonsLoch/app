#include "framework.h"


namespace geometry
{


   geometry::geometry(sp(::axis::application) papp) :
      element(papp)
   {

   }

   geometry::~geometry()
   {

   }

   double geometry::rotate_x(double x, double y, double phi)
   {
      return x * cos(phi) - y * sin(phi);
   }

   double geometry::rotate_y(double x, double y, double phi)
   {
      return x * sin(phi) + y * cos(phi);
   }

   void geometry::rotate(int32_t xParam, int32_t yParam, LPPOINT lppoint, int32_t iCount, double phi)
   {
      double phicos = cos(phi);
      double phisin = sin(phi);
      rotate(xParam, yParam, lppoint, iCount, phicos, phisin);
   }

   void geometry::rotate(
      int32_t xParam,
      int32_t yParam,
      LPPOINT lppoint,
      int32_t iCount,
      double phicos,
      double phisin)
   {
      for(int32_t i = 0; i < iCount; i++)
      {
         double x = lppoint[i].x - xParam;
         double y = lppoint[i].y - yParam;
         lppoint[i].x = (LONG) (((x * phicos - y * phisin)) + xParam);
         lppoint[i].y = (LONG) (((x * phisin + y * phicos)) + yParam);
      }
   }




   void rotation::rotate(LPPOINT lppoint, int32_t iCount)
   {
      for(int32_t i = 0; i < iCount; i++)
      {
         long x = lppoint[i].x - m_iXCenter;
         long y = lppoint[i].y - m_iYCenter;
         lppoint[i].x = ((LONG) (x * m_dCosPhi - y * m_dSinPhi)) + m_iXCenter;
         lppoint[i].y = ((LONG) (x * m_dSinPhi + y * m_dCosPhi)) + m_iYCenter;
      }
   }


} // namespace geometry
