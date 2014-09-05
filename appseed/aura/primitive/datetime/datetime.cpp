#include "framework.h"


namespace datetime
{




} // namespace datetime







extern "C" CLASS_DECL_AURA time_t timegm(struct tm *tmp)
{

   static time_t gmtime_offset;

   tmp->tm_isdst = 0;

   return __mktime_internal(tmp,gmtime_r,&gmtime_offset);

}

