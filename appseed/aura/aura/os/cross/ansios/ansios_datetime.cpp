#include "framework.h"



struct tm *gmtime_r(const time_t *timep,struct tm *result)
{

#ifdef WINDOWS


   if(gmtime_s(result,timep) != 0)
      return NULL;

   return result;

#else

   throw todo;

#endif

}


