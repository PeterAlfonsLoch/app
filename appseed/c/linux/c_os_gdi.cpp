#include "framework.h"



#include "linux/c_os_cross_win_gdi_internal.h"







void FillSolidRect_dup(HDC hdc, LPCRECT lpRect, COLORREF clr)
{
   XSetBackground(hdc->m_display, hdc->m_gc, clr);
   XFillRectangle(hdc->m_display, hdc->m_d, hdc->m_gc, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);
}

HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);
HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc);

HFONT CreatePointFont_dup(int nPointSize, const char * lpszFaceName, HDC hdc)
{
   return CreatePointBoldFont_dup(nPointSize, lpszFaceName, FALSE, hdc);
}

HFONT CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc)
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
HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam)
{

   /*HDC hDC;
   if (hdcParam != NULL)
   {
      hDC = hdcParam;
   }
   else
      hDC = ::GetDC(NULL);*/

   return ::CreateFontIndirect(lpLogFont);

   /*if(hdcParam == NULL)
      ReleaseDC(NULL, hDC);*/


}



