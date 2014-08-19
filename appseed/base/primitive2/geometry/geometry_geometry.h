#pragma once


namespace geometry
{


   class CLASS_DECL_BASE rotation
   {
   public:
      double   m_dCosPhi;
      double   m_dSinPhi;
      int32_t      m_iXCenter;
      int32_t      m_iYCenter;

      void rotate(LPPOINT lppoint, int32_t iCount);
   };

   class CLASS_DECL_BASE geometry :
      virtual public ::object
   {
   public:
      double rotate_y(double x, double y, double phi);
      double rotate_x(double x, double y, double phi);
      void rotate(int32_t x, int32_t y, LPPOINT lppoint, int32_t iCount, double phi);
      void rotate(int32_t x, int32_t y, LPPOINT lppoint, int32_t iCount, double cosphi, double sinphi);


      void RandomPoint(POINT & pt, const RECT & rect);
      void deflate(LPRECT lprect, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);


      geometry(sp(::axis::application) papp);
      virtual ~geometry();

   };


} // namespace geometry

