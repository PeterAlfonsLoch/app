#include "framework.h"
#include <malloc.h>


// interesting function
/*bool CLASS_DECL_AXIS __custom_log_font(UINT nIDS, LOGFONTW* pLogFont)
{
   ENSURE_ARG(pLogFont != NULL);
   ASSERT(nIDS != 0);

   char szFontInfo[256];
   if (!::core::LoadString(nIDS, szFontInfo,_countof(szFontInfo)))
      return FALSE;

   LPTSTR lpszSize = _tcschr(szFontInfo, '\n');
   if (lpszSize != NULL)
   {
      // get point size and convert to pixels
      pLogFont->lfHeight = _ttoi(lpszSize+1);
      pLogFont->lfHeight =
         MulDiv(pLogFont->lfHeight, afxData.cyPixelsPerInch, 72);
      *lpszSize = '\0';
   }
   ::core::tcsncpy_s(pLogFont->lfFaceName, _countof(pLogFont->lfFaceName), szFontInfo, _TRUNCATE);
   return TRUE;
}*/



