#include "framework.h"

#ifdef LINUX
#include <ctype.h>
#endif


namespace gen
{


   bool strn::to_int(const char * psz, int iLen, int64_t & i)
   {

      char * pszEnd;

      int64_t iConversion = ::natoi64_dup(psz, &pszEnd, iLen);

      if(pszEnd == psz)
         return false;

      i = iConversion;

      return true;

   }

   bool strn::to_int(const char * psz, int iLen, int & i)
   {

      char * pszEnd;

      int64_t iConversion = ::natoi_dup(psz, (const char **) &pszEnd, iLen);

      if(pszEnd == psz)
         return false;

      if(iConversion > numeric_info::get_maximum_value < int > ())
         return false;

      i = (int) iConversion;

      return true;

   }


   bool strn::to_int(const char * psz, int iLen, int64_t & i, int iBase)
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

   bool strn::to_int(const char * psz, int iLen, int & i, int iBase)
   {

      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;

      char * pszEnd;

      int64_t iConversion = ::natoi64_dup(psz, &pszEnd, iBase, iLen);

      if(pszEnd == psz)
         return false;

      if(iConversion > numeric_info::get_maximum_value < int > ())
         return false;

      i = (int) iConversion;

      return true;

   }


} // namespace gen



