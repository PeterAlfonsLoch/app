#include "StdAfx.h"


extern HINSTANCE g_hinstance;

extern void __cdecl _ca2_purecall(void);


int spaboot_start(const char * pszVersion, const char * pszId);


BSTR BSTRFromCStr_dup(UINT codePage, LPCSTR s)
{
    int wideLen = MultiByteToWideChar(codePage, 0, s, -1, NULL, 0);
    if( wideLen > 0 )
    {
        WCHAR* wideStr = (WCHAR*)CoTaskMemAlloc(wideLen*sizeof(WCHAR));
        if( NULL != wideStr )
        {
            BSTR bstr;

            ZeroMemory(wideStr, wideLen*sizeof(WCHAR));
            MultiByteToWideChar(codePage, 0, s, -1, wideStr, wideLen);
            bstr = SysAllocStringLen(wideStr, wideLen-1);
            CoTaskMemFree(wideStr);

            return bstr;
        }
    }
    return NULL;
};


BOOL TextOutU_dup(HDC hdc, int x, int y, const char * pszUtf8, int iSize)
{
   std::string str;
   str.assign(pszUtf8, iSize);

   BSTR bstr = BSTRFromCStr_dup(CP_UTF8, str.c_str());
   BOOL b = TextOutW(hdc, x, y, bstr, wcslen(bstr));
   ::SysFreeString(bstr);
   return b;
}

void FillSolidRect_dup(HDC hdc, LPCRECT lpRect, COLORREF clr)
{
   ::SetBkColor(hdc, clr);
   ::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
}

HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);

HFONT CreatePointFont_dup(int nPointSize, const char * lpszFaceName, HDC hdc)
{
   LOGFONT logFont;
   memset(&logFont, 0, sizeof(LOGFONT));
   logFont.lfCharSet = DEFAULT_CHARSET;
   logFont.lfHeight = nPointSize;
   strncpy(logFont.lfFaceName, lpszFaceName, sizeof(logFont.lfFaceName));

   return CreatePointFontIndirect_dup(&logFont, hdc);
}

// pLogFont->nHeight is interpreted as PointSize * 10
HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam)
{
   HDC hDC;
   if (hdcParam != NULL)
   {
      hDC = hdcParam;
   }
   else
      hDC = ::GetDC(NULL);

   // convert nPointSize to logical units based on pgraphics
   LOGFONT logFont = *lpLogFont;
   POINT pt;
   // 72 points/inch, 10 decipoints/point
   pt.y = ::MulDiv(::GetDeviceCaps(hDC, LOGPIXELSY), logFont.lfHeight, 720);
   pt.x = 0;
   ::DPtoLP(hDC, &pt, 1);
   POINT ptOrg = { 0, 0 };
   ::DPtoLP(hDC, &ptOrg, 1);
   logFont.lfHeight = -abs(pt.y - ptOrg.y);

   if(hdcParam == NULL)
      ReleaseDC(NULL, hDC);

   return ::CreateFontIndirect(&logFont);
}

