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


   void geometry::RandomPoint(POINT & pt, const RECT & rect)
   {
      pt.x = (LONG)System.math().RandRange(rect.left,rect.right);
      pt.y = (LONG)System.math().RandRange(rect.top,rect.bottom);
   }

   //////////////////////////////////////////////////////////////////////
   //
   // Function Name: deflate
   //
   // Purpose:
   // Change rectangle dimension using its dimensions and the specified
   // rates. For example, the dLeftRate change the left position of the
   // rectangle. If 0.0, it remains the same as the original left.
   // If 1.0, it turns as the original right. If 0.4, it will be 40%
   // of the width from left to right.
   //
   // Output:
   // -1 if the creation of the ::user::impact failed.
   // 0 if the creation of the ::user::impact succeeded.
   //
   // Author:
   // Vanessa Testoni
   //
   //////////////////////////////////////////////////////////////////////
   void geometry::deflate(LPRECT lprect, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate)
   {
      rect rect(lprect);
      lprect->left      = System.math().RangeRate(rect.left, rect.right, dLeftRate);
      lprect->right     = System.math().RangeRate(rect.right, rect.left, dRightRate);
      lprect->top       = System.math().RangeRate(rect.top, rect.bottom, dTopRate);
      lprect->bottom    = System.math().RangeRate(rect.bottom, rect.top, dBottomRate);

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
