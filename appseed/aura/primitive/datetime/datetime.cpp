#include "framework.h"
#include <time.h>


namespace datetime
{




} // namespace datetime





#if 0

extern "C" CLASS_DECL_AURA time_t timegm(struct tm *tmp)
{

   static time_t gmtime_offset;

   tmp->tm_isdst = 0;

   return __mktime_internal(tmp,gmtime_r,&gmtime_offset);

}


#endif
