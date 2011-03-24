#pragma once


extern HINSTANCE g_hinstance;

extern void __cdecl _ca2_purecall(void);

int spaboot_start(const char * pszVersion, const char * pszId);

BSTR BSTRFromCStr_dup(UINT codePage, LPCSTR s);

BOOL TextOutU_dup(HDC hdc, int x, int y, const char * pszUtf8, int iSize);

void FillSolidRect_dup(HDC hdc, LPCRECT lpRect, COLORREF clr);

HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);

HFONT CreatePointFont_dup(int nPointSize, const char * lpszFaceName, HDC hdc);

// pLogFont->nHeight is interpreted as PointSize * 10
HFONT CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);
