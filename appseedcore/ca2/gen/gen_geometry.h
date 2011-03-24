#pragma once


namespace gen
{


   namespace geometry
   {


      class CLASS_DECL_ca rotation
      {
      public:
         double   m_dCosPhi;
         double   m_dSinPhi;
         int      m_iXCenter;
         int      m_iYCenter;
         
         void rotate(LPPOINT lppoint, int iCount);
      };

      class CLASS_DECL_ca geometry  :
         virtual public ::radix::object
      {
      public:
         double rotate_y(double x, double y, double phi);
         double rotate_x(double x, double y, double phi);
         void rotate(int x, int y, LPPOINT lppoint, int iCount, double phi);
         void rotate(int x, int y, LPPOINT lppoint, int iCount, double cosphi, double sinphi);


         void RandomPoint(POINT & pt, LPCRECT lpcrect);
         void deflate(LPRECT lprect, double dLeftRate, double dRightRate, double dTopRate, double dBottomRate);

         
         geometry(::ca::application * papp);
         virtual ~geometry();

      };


   } // namespace geometry


} // namespace gen
