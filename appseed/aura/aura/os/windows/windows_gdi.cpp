//#include "framework.h"
//#include "aura/graphics/graphics.h"











HFONT wingdi_CreatePointFont(int nPointSize, const char * lpszFaceName, HDC hdc, LOGFONTW *plf)
{

   LOGFONTW lF;

   if (plf == NULL)
   {
      plf = &lF;
      ZEROP(plf);
      plf->lfCharSet = DEFAULT_CHARSET;

   }

   

   plf->lfHeight = nPointSize;

   wstring wstr(lpszFaceName);

   wstr = wstr.substr(0, sizeof(plf->lfFaceName));

   wcsncpy(plf->lfFaceName, wstr, sizeof(plf->lfFaceName) / sizeof(wchar_t));

   return wingdi_CreatePointFontIndirect(plf, hdc);

}

// pLogFont->nHeight is interpreted as PointSize * 10
HFONT wingdi_CreatePointFontIndirect(LOGFONTW* lpLogFont, HDC hdc)
{

   LOGFONTW & logFont = *lpLogFont;

   POINT pt;
   // 72 points/inch, 10 decipoints/point
   pt.y = ::MulDiv(::GetDeviceCaps(hdc, LOGPIXELSY), logFont.lfHeight, 720);
   pt.x = 0;
   ::DPtoLP(hdc, &pt, 1);
   POINT ptOrg = { 0, 0 };
   ::DPtoLP(hdc, &ptOrg, 1);
   logFont.lfHeight = -abs(pt.y - ptOrg.y);

   logFont.lfQuality = ANTIALIASED_QUALITY;

   HFONT hfont = ::CreateFontIndirectW(&logFont);

   if (::GetObjectW(hfont, sizeof(logFont), lpLogFont))
   {

      output_debug_string("got log font");
   }



   return hfont;

}


