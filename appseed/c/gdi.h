#pragma once


CLASS_DECL_c bool    TextOutU_dup(HDC hdc, int x, int y, const char * pszUtf8, int iSize);
CLASS_DECL_c void    FillSolidRect_dup(HDC hdc, LPCRECT lpRect, COLORREF clr);
CLASS_DECL_c HFONT   CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);
CLASS_DECL_c HFONT   CreatePointFont_dup(int nPointSize, const char * lpszFaceName, HDC hdc);
CLASS_DECL_c HFONT   CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc);
CLASS_DECL_c HFONT   CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);
