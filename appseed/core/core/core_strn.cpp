#include "framework.h"

#ifdef LINUX
#include <ctype.h>
#endif


namespace core
{


   bool strn::to(const char * psz, int32_t iLen, int64_t & i)
   {

      char * pszEnd;

      int64_t iConversion = ::natoi64_dup(psz, &pszEnd, iLen);

      if(pszEnd == psz)
         return false;

      i = iConversion;

      return true;

   }

   bool strn::to(const char * psz, int32_t iLen, int32_t & i)
   {

      char * pszEnd;

      int64_t iConversion = ::natoi_dup(psz, (const char **) &pszEnd, iLen);

      if(pszEnd == psz)
         return false;

      if(iConversion > numeric_info::get_maximum_value < int32_t > ())
         return false;

      i = (int32_t) iConversion;

      return true;

   }


   bool strn::to(const char * psz, int32_t iLen, int64_t & i, int32_t iBase)
   {

      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;

      char * pszEnd;

      int64_t iConversion = ::natoi64_dup(psz, &pszEnd, iBase, iLen);

      if(pszEnd == psz)
         return false;

      i = iConversion;

      return true;

   }

   bool strn::to(const char * psz, int32_t iLen, int32_t & i, int32_t iBase)
   {

      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;

      char * pszEnd;

      int64_t iConversion = ::natoi64_dup(psz, &pszEnd, iBase, iLen);

      if(pszEnd == psz)
         return false;

      if(iConversion > numeric_info::get_maximum_value < int32_t > ())
         return false;

      i = (int32_t) iConversion;

      return true;

   }

} // namespace core



