#include "framework.h"

#ifdef WINDOWS
#include <cderr.h>      // Commdlg Error definitions
#include <winspool.h>
#endif

namespace ca
{


   void format_strings(string & rString, const char * lpszFormat, const char * const* rglpsz, int32_t nString)
   {
      ENSURE_ARG(lpszFormat != NULL);
      ENSURE_ARG(rglpsz != NULL);
      // determine length of destination string, not including null terminator
      strsize nTotalLen = 0;
      const char * pchSrc = lpszFormat;
      //      strsize count;
      while (*pchSrc != '\0')
      {
         if (pchSrc[0] == '%' &&
            ( (pchSrc[1] >= '1' && pchSrc[1] <= '9') ||
            (pchSrc[1] >= 'A' && pchSrc[1] <= 'Z')) )
         {
            // %A comes after %9 -- we'll need it someday
            int32_t i;
            if (pchSrc[1] > '9')
               i = 9 + (pchSrc[1] - 'A');
            else
               i = pchSrc[1] - '1';
            pchSrc += 2;
            if (i >= nString)
               ++nTotalLen;
            else if (rglpsz[i] != NULL)
               nTotalLen += strlen(rglpsz[i]);
         }
         else
         {
            pchSrc = ca::str::utf8_inc_slide(&nTotalLen, pchSrc);
         }
      }

      pchSrc = lpszFormat;
      char * pchDest = rString.GetBuffer(nTotalLen);
      while (*pchSrc != '\0')
      {
         if (pchSrc[0] == '%' &&
            ( (pchSrc[1] >= '1' && pchSrc[1] <= '9') ||
            (pchSrc[1] >= 'A' && pchSrc[1] <= 'Z')) )
         {
            // %A comes after %9 -- we'll need it someday
            int32_t i;
            if (pchSrc[1] > '9')
               i = 9 + (pchSrc[1] - 'A');
            else
               i = pchSrc[1] - '1';
            pchSrc += 2;
            if (i >= nString)
            {
               //               TRACE(::ca::trace::category_AppMsg, 0, "Error: illegal string index requested %d.\n", i);
               *pchDest++ = '?';
               nTotalLen--;
            }
            else if (rglpsz[i] != NULL)
            {
               size_t nLen = strlen(rglpsz[i]);
               ::ca::strcpy_s(pchDest, nTotalLen + 1, rglpsz[i]);
               nTotalLen -= nLen;
               pchDest += nLen;
            }
         }
         else
         {

            ca::str::utf8_inc_copy_slide_back(&nTotalLen, pchDest, pchSrc);

         }

      }
      rString.ReleaseBuffer((int32_t)((const char *)pchDest - (const char *)rString));
      // ReleaseBuffer will assert if we went too far
   }

   bool extract_sub_string(string & rString, const char * lpszFullString, int32_t iSubString, char chSep)
   {
      if (lpszFullString == NULL)
         return FALSE;

      while (iSubString--)
      {
         lpszFullString = strchr(lpszFullString, chSep);
         if (lpszFullString == NULL)
         {
            rString.Empty();        // return is_empty string as well
            return FALSE;
         }
         lpszFullString++;       // point past the separator
      }

      const char * lpchEnd = strchr(lpszFullString, chSep);

      strsize nLen = (lpchEnd == NULL) ? strlen(lpszFullString) : (int32_t)(lpchEnd - lpszFullString);

      ASSERT(nLen >= 0);

      ::ca::memcpy_s(rString.GetBufferSetLength(nLen), nLen*sizeof(char), lpszFullString, nLen*sizeof(char));

      rString.ReleaseBuffer();   // Need to call ReleaseBuffer after calling GetBufferSetLength

      return TRUE;
   }


} // namespace ca




