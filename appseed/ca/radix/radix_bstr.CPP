#include "framework.h"
#include "radix_bstr.h"

#ifdef WINDOWS

#include <comdef.h>

void bstr::copy(BSTR &bstrDest, const BSTR bstrSrc)
{
   if(bstrSrc == NULL)
   {
      if(bstrDest != NULL)
      {
         SysFreeString(bstrDest);
         bstrDest = NULL;
      }
   }
   else
      if(bstrDest == NULL)
      {
         bstrDest = SysAllocString(bstrSrc);
      }
      else
      {
         SysReAllocString(&bstrDest, bstrSrc);
      }

}

void bstr::copy(string &strDest, const BSTR bstrSrc)
{
   _bstr_t bstrt(bstrSrc);
   strDest = (LPTSTR) bstrt;
}

void bstr::copy( BSTR &bstrDest, const string &strSrc )
{
   _bstr_t bstrt(strSrc);
   bstrDest = bstrt;
}

bool bstr::IsEqual(const BSTR bstrA, const BSTR bstrB)
{
   _bstr_t bstr1(bstrA);
   _bstr_t bstr2(bstrB);
   return bstr1 == bstr2;

}

#endif