#include "framework.h"
#include "ca2_bstr.h"

#ifdef WINDOWS

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
   strDest = ::ca2::international::unicode_to_utf8((wchar_t *) bstrSrc);
}

void bstr::copy( BSTR &bstrDest, const string &strSrc )
{
   if(bstrDest != NULL)
      SysFreeString(bstrDest);
   bstrDest = SysAllocString((wchar_t *) ::ca2::international::utf8_to_unicode(strSrc));
}

bool bstr::IsEqual(const BSTR bstrA, const BSTR bstrB)
{
   return wcscmp_dup((wchar_t *) bstrA, (wchar_t *) bstrB) == 0;

}

#endif