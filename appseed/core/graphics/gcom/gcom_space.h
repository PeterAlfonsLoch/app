#pragma once


namespace gcom
{


   class space
   {
   public:



      space();
      ~space();


      void align(LPRECT lprectAlign, LPRECT lprectSpace, e_align ealign, double dRate);
      void deviate(LPRECT lprectDeviate, LPRECT lprectSpace, e_direction edirection, double dRate);
      void slice(LPRECT lprectSliced, LPRECT lprectSlicing, e_direction edirection, double dRate, double dRateEx);
      void slice(LPRECT lprectSliced1, LPRECT lprectSliced2, LPRECT lprectSliced3, LPRECT lprectSlicing, e_direction edirection, double dRate, double dRateEx);


      void scale(LPRECT lprect, double dRate);
      void wipe_in(LPRECT lprect1, LPRECT lprect2, LPRECT lprect3, LPRECT lprect4, LPRECT lprect, double dRate, double dRateEx);


      void get_center(LPPOINT lppoint, LPRECT lprect);


   };


} // namespace gcom




