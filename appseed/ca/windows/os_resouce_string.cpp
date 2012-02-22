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
