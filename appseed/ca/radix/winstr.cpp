// This is ca2 API library.
// 
// 
//
// 
// 
// 
// 
// 

#include "StdAfx.h"
#include "sal.h"



/////////////////////////////////////////////////////////////////////////////
// Windows extensions to strings

#ifndef _ApplicationFrameworkDLL
int AfxLoadString(UINT nID, __out_ecount(nMaxBuf) char * lpszBuf, UINT nMaxBuf)
{
   ASSERT(fx_is_valid_address(lpszBuf, nMaxBuf*sizeof(CHAR)));
   if( lpszBuf == NULL || nMaxBuf == 0)
      AfxThrowInvalidArgException();

   const ATLSTRINGRESOURCEIMAGE* pImage;
   int nBytes;

   pImage = _template::AtlGetStringResourceImage(AfxGetResourceHandle(), nID);
   if (pImage == NULL)
   {
      lpszBuf[0] = '\0';
      return 0;
   }
   ASSERT(pImage->nLength != 0);
   nBytes = ::WideCharToMultiByte(CP_ACP, 0, pImage->achString, pImage->nLength, lpszBuf, nMaxBuf-1, NULL, NULL);
   lpszBuf[nBytes] = '\0';

   return nBytes;
}

int AfxLoadString(UINT nID, __out_ecount(nMaxBuf) wchar_t * lpszBuf, UINT nMaxBuf)
{
   ASSERT(fx_is_valid_address(lpszBuf, nMaxBuf*sizeof(WCHAR)));
   if( lpszBuf == NULL || nMaxBuf == 0)
      AfxThrowInvalidArgException();

   const ATLSTRINGRESOURCEIMAGE* pImage;
   int nCharsToCopy;

   pImage = _template::AtlGetStringResourceImage(AfxGetResourceHandle(), nID);
   if (pImage == NULL)
   {
      lpszBuf[0] = L'\0';
      return 0;
   }
   ASSERT(pImage->nLength != 0);
   nCharsToCopy = min(nMaxBuf-1, pImage->nLength);
   _template::checked::memcpy_s(lpszBuf, nMaxBuf-1, pImage->achString, nCharsToCopy*sizeof(WCHAR));
   lpszBuf[nCharsToCopy] = L'\0';

   return nCharsToCopy;
}

HINSTANCE AfxFindStringResourceHandle(UINT /* nID */)
{
   return AfxGetResourceHandle();
}

#endif

/////////////////////////////////////////////////////////////////////////////

BOOL AfxExtractSubString(string & rString, const char * lpszFullString,
   int iSubString, char chSep)
{
   if (lpszFullString == NULL)
      return FALSE;

   while (iSubString--)
   {
      lpszFullString = _tcschr(lpszFullString, chSep);
      if (lpszFullString == NULL)
      {
         rString.Empty();        // return is_empty string as well
         return FALSE;
      }
      lpszFullString++;       // point past the separator
   }
   const char * lpchEnd = _tcschr(lpszFullString, chSep);
   int nLen = (lpchEnd == NULL) ?
      lstrlen(lpszFullString) : (int)(lpchEnd - lpszFullString);
   ASSERT(nLen >= 0);
   _template::checked::memcpy_s(rString.GetBufferSetLength(nLen), nLen*sizeof(char),
      lpszFullString, nLen*sizeof(char));
   rString.ReleaseBuffer();   // Need to call ReleaseBuffer 
                        // after calling GetBufferSetLength
   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
