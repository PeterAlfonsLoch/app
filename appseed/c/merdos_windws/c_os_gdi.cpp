#include "framework.h"


bool TextOutU_dup(simple_graphics & hdc, int x, int y, const char * pszUtf8, int iSize)
{
   WCHAR * pwsz = utf8_to_16(pszUtf8);
   D2D_RECT_F r;
   r.left = x;
   r.top = y;
   r.right = r.left + 16384;
   r.bottom = r.top + 16384;
   hdc.m_pfont->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
   hdc.m_pfont->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
   bool b = hdc.m_pdc->DrawText(pwsz, wcslen_dup(pwsz), hdc.m_pfont, r, hdc.m_pbrush) != FALSE;
   delete  [] pwsz;
   return b;
}

void FillSolidRect_dup(simple_graphics & hdc, LPCRECT lpRect, COLORREF clr)
{
   ::SetBkColor(hdc, clr);
   ::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
}

HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, simple_graphics & hdcParam);
HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, simple_graphics & hdc);

HFONT CreatePointFont_dup(int nPointSize, const char * lpszFaceName, simple_graphics & hdc)
{
   return CreatePointBoldFont_dup(nPointSize, lpszFaceName, FALSE, hdc);
}

HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, simple_graphics & hdc)
{
   LOGFONT logFont;
   memset_dup(&logFont, 0, sizeof(LOGFONT));
   logFont.lfCharSet = DEFAULT_CHARSET;
   logFont.lfHeight = nPointSize;
   logFont.lfWeight = BOLD ? FW_BOLD : FW_NORMAL;
   strncpy_dup(logFont.lfFaceName, lpszFaceName, sizeof(logFont.lfFaceName));

   return CreatePointFontIndirect_dup(&logFont, hdc);
}

// pLogFont->nHeight is interpreted as PointSize * 10
HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, simple_graphics & hdcParam)
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
   logFont.lfHeight = -abs_dup(pt.y - ptOrg.y);

   if(hdcParam == NULL)
      ReleaseDC(NULL, hDC);

   return ::CreateFontIndirect(&logFont);
}


                                        
                                        



