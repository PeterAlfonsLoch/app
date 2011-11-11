#pragma once

HDC GetDC(HWND hwnd);
HFONT CreateFontIndirect(const LOGFONT * lf);
HPEN CreatePen(int iPenStyle, int iWidth, COLORREF crColor);
HGDIOBJ GetStockObject(int iStockObject);
BOOL SelectObject(HDC hdc, HGDIOBJ hgdiobj);
BOOL Rectangle(HDC hdc, int x1, int y1, int x2, int y2);
BOOL DeleteObject(HGDIOBJ hgdiobj);
HDC CreateCompatibleDC(HDC hdc);
HBITMAP WINAPI CreateDIBSection(HDC hdc, const BITMAPINFO *lpbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset);
BOOL SetTextColor(HDC hdc, COLORREF cr);
BOOL SetBkMode(HDC hdc, int iMode);
BOOL DeleteDC(HDC hdc);
BOOL AlphaBlend(HDC hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, HDC hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, BLENDFUNCTION ftn);
BOOL GetObject(HGDIOBJ hgdiobj, int iSize, void * object);
BOOL GetTextExtentPoint(HDC hdc, const char * pszText, int iSize, SIZE * psize);
/*BOOL WINAPI TransparentBlt(HDC hdcDest,
    __in int xoriginDest,
    __in int yoriginDest,
    __in int wDest,
    __in int hDest,
    __in HDC hdcSrc,
    __in int xoriginSrc,
    __in int yoriginSrc,
    __in int wSrc,
    __in int hSrc,
    __in UINT crTransparent);

*/
