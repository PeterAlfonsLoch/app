#pragma once


#include "ansios_datetime.h"

struct tm *gmtime_r(const time_t *timep,struct tm *result);


# undef __gmtime_r
# define __gmtime_r gmtime_r
time_t __mktime_internal(struct tm *,
struct tm * (*) (time_t const *,struct tm *),
   time_t *);


#ifdef WINDOWS


struct tm *gmtime_r(const time_t *timep,struct tm *result)
{

   if(gmtime_s(result,timep) != 0)
      return NULL;

   return result;

}


#endif
