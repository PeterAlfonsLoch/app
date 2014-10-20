#include "framework.h"
#include <math.h>


os_max_int ceil_div(os_max_int num, os_max_int den)
{
   int64_t quo = num / den;
   if((num % den) > 0)
      quo++;
   return quo;
}


double tri(double angle)
{

   angle = fmod(angle,3.1415 * 2.0) * 2.0 / 3.1415;

   if(angle < 1.0)
      return angle;
   else if(angle >= 1.0 && angle < 3.0)
      return 2.0 - angle;
   else
      return angle - 4.0;


}
