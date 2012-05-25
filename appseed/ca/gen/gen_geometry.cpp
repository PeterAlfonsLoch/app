#include "framework.h"


namespace gen
{
   
   namespace geometry
   {


      geometry::geometry(::ca::application * papp) :
         ca(papp)
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

      void geometry::rotate(int xParam, int yParam, LPPOINT lppoint, int iCount, double phi)
      {
         double phicos = cos(phi);
         double phisin = sin(phi);
         rotate(xParam, yParam, lppoint, iCount, phicos, phisin);
      }

      void geometry::rotate(
         int xParam,
         int yParam,
         LPPOINT lppoint,
         int iCount, 
         double phicos,
         double phisin)
      {
         for(int i = 0; i < iCount; i++)
         {
            double x = lppoint[i].x - xParam;
            double y = lppoint[i].y - yParam;
            lppoint[i].x = (long) (((x * phicos - y * phisin)) + xParam);
            lppoint[i].y = (long) (((x * phisin + y * phicos)) + yParam);
         }
      }


      void geometry::RandomPoint(POINT & pt, LPCRECT lpcrect)
      {
         pt.x = System.math().RandRange(lpcrect->left, lpcrect->right);
         pt.y = System.math().RandRange(lpcrect->top, lpcrect->bottom);
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
      // -1 if the creation of the ::view failed.
      // 0 if the creation of the ::view succeeded.
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


      void rotation::rotate(LPPOINT lppoint, int iCount)
      {
         for(int i = 0; i < iCount; i++)
         {
            long x = lppoint[i].x - m_iXCenter;
            long y = lppoint[i].y - m_iYCenter;
            lppoint[i].x = ((long) (x * m_dCosPhi - y * m_dSinPhi)) + m_iXCenter;
            lppoint[i].y = ((long) (x * m_dSinPhi + y * m_dCosPhi)) + m_iYCenter;
         }
      }


   } // namespace geometry

} // namespace gen
