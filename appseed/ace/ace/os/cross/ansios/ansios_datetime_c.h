#pragma once


CLASS_DECL_ACE struct tm *gmtime_r(const time_t *timep,struct tm *result);

CLASS_DECL_ACE int gettimeofday(struct timeval* tp, void* tz);



