#pragma once


BEGIN_EXTERN_C

struct tm *gmtime_r(const time_t *timep,struct tm *result);

int gettimeofday(struct timeval* tp, void* tz);


END_EXTERN_C