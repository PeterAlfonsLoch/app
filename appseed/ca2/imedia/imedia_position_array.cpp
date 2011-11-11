#include "StdAfx.h"

namespace imedia
{

   position_array::position_array()
   {
   }

   position_array::position_array(const position_array & base_array) :
      numeric_array < position >(base_array)
   {
      operator = (base_array);
   }

} // namespace imedia

