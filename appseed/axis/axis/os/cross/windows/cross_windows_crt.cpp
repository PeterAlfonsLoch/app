#include "framework.h"


#define EUNKNOWN        37               // Unknown error


CLASS_DECL_AXIS errno_t _ctime64_s(char * buf, int32_t iSize, const time_t * timer )
{

   char * ret = NULL;

   if((ret = ctime(timer)) == NULL)
   {
      if(errno == 0)
         return EUNKNOWN;
      else
         return errno;
   }

   int32_t iLen;

   if(((iLen = (int32_t) strlen(ret)) + 1) > iSize)
      return ERANGE;

   strncpy(buf, ret, min(iSize, iLen));

   return 0;

}
