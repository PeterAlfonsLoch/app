#pragma once

namespace constraint
{
   template <class CLASS > void constraint_min(CLASS & c, const CLASS & cMin)
   {
      if(c < cMin)
      {
         c = cMin;
      }
   }
}
