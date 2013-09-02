#include "framework.h"

namespace ca2
{

   bool ok(para_return eret)
   {
      return ((int32_t)eret) >= 0;
   }


   var str_ends_get(const char * lpcsz, const char * lpcszSuffix)
   {
      
      string str(lpcsz);

      string strSuffix(lpcszSuffix);

      strsize iLen = strSuffix.get_length();

      if(str.Right(iLen) == lpcszSuffix)
      {

         return str.Left(str.get_length() - iLen);

      }

      return false;

   }

} // namespace ca2
