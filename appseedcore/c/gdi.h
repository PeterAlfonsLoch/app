#pragma once


CLASS_DECL_____ BOOL    TextOutU_dup(HDC hdc, int x, int y, const char * pszUtf8, int iSize);
CLASS_DECL_____ void    FillSolidRect_dup(HDC hdc, LPCRECT lpRect, COLORREF clr);
CLASS_DECL_____ HFONT   CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);
CLASS_DECL_____ HFONT   CreatePointFont_dup(int nPointSize, const char * lpszFaceName, HDC hdc);
CLASS_DECL_____ HFONT   CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, HDC hdc);
CLASS_DECL_____ HFONT   CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, HDC hdcParam);
