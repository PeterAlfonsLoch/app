#include "StdAfx.h"
#include "BSTR.h"
#include <comdef.h>

void CBSTR::copy(BSTR &bstrDest, const BSTR bstrSrc)
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

void CBSTR::copy(string &strDest, const BSTR bstrSrc)
{
   _bstr_t bstrt(bstrSrc);
   strDest = (LPTSTR) bstrt;
}

void CBSTR::copy( BSTR &bstrDest, const string &strSrc )
{
   _bstr_t bstrt(strSrc);
   bstrDest = bstrt;
}

bool CBSTR::IsEqual(const BSTR bstrA, const BSTR bstrB)
{
   _bstr_t bstr1(bstrA);
   _bstr_t bstr2(bstrB);
   return bstr1 == bstr2;

}