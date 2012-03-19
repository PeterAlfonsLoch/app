#include "StdAfx.h"

namespace gen
{

   bool ok(para_return eret)
   {
      return ((int)eret) >= 0;
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

} // namespace gen