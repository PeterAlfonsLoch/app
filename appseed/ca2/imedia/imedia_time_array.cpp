#include "StdAfx.h"

namespace imedia
{

   time_array::time_array()
   {
   }

   time_array::time_array(const time_array & base_array) :
      numeric_array < time >(base_array)
   {
      operator = (base_array);
   }

} // namespace imedia
