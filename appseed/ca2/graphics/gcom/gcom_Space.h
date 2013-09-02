#pragma once

#include "gcom_Enum.h"

namespace gcom
{

   class Space  
   {
   public:
      Space();
      virtual ~Space();
      
      void Align(LPRECT lprectAlign, LPRECT lprectSpace, EAlign ealign, double dRate);
      void Deviate(LPRECT lprectDeviate, LPRECT lprectSpace, EDirection edirection, double dRate);
      void Slice(LPRECT lprectSliced, LPRECT lprectSlicing, EDirection edirection, double dRate, double dRateEx);
      void Slice(LPRECT lprectSliced1, LPRECT lprectSliced2, LPRECT lprectSliced3, LPRECT lprectSlicing, EDirection edirection, double dRate, double dRateEx);

      void Scale(LPRECT lprect, double dRate);
      void WipeIn(LPRECT lprect1, LPRECT lprect2, LPRECT lprect3, LPRECT lprect4, LPRECT lprect, double dRate, double dRateEx);

      void GetCenter(LPPOINT lppoint, LPRECT lprect);




   };

} // namespace gcom

