#include "framework.h"


os_max_int ceil_div(os_max_int num, os_max_int den)
{
   int64_t quo = num / den;
   if((num % den) > 0)
      quo++;
   return quo;
}
