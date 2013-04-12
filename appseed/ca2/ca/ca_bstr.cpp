#include "framework.h"
#include "ca_bstr.h"

#ifdef WINDOWS

void bstr::copy(BSTR &bstrDest, const BSTR bstrSrc)
{
   if(bstrSrc == ::null())
   {
      if(bstrDest != ::null())
      {
         SysFreeString(bstrDest);
         bstrDest = ::null();
      }
   }
   else
      if(bstrDest == ::null())
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
   strDest = ::ca::international::unicode_to_utf8((wchar_t *) bstrSrc);
}

void bstr::copy( BSTR &bstrDest, const string &strSrc )
{
   if(bstrDest != ::null())
      SysFreeString(bstrDest);
   bstrDest = SysAllocString((wchar_t *) ::ca::international::utf8_to_unicode(strSrc));
}

bool bstr::IsEqual(const BSTR bstrA, const BSTR bstrB)
{
   return wcscmp_dup((wchar_t *) bstrA, (wchar_t *) bstrB) == 0;

}

#endif