#pragma once


class CLASS_DECL_AURA device_context
{
public:


   ::Display *             m_pdisplay;
   ::Drawable              m_drawable;
   ::GC                    m_gc;
   ::Pixmap                m_pixmap;
   ::Window                m_window;
   int                     m_iDepth;
   int                     m_iScreen;

   point                   m_pt;
   point                   m_ptOffset;

   XFontSet                m_fontset;

   device_context();


};


/*HDC GetDC(oswindow hwnd);
HFONT CreateFontIndirect(const LOGFONT * lf);
HPEN CreatePen(int32_t iPenStyle, int32_t iWidth, COLORREF crColor);
HGDIOBJ GetStockObject(int32_t iStockObject);
HGDIOBJ SelectObject(HDC hdc, HGDIOBJ hgdiobj);
WINBOOL Rectangle(HDC hdc, int32_t x1, int32_t y1, int32_t x2, int32_t y2);
WINBOOL DeleteObject(HGDIOBJ hgdiobj);
HDC CreateCompatibleDC(HDC hdc);
//HBITMAP WINAPI CreateDIBSection(HDC hdc, const BITMAPINFO *lpbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset);
WINBOOL SetTextColor(HDC hdc, COLORREF cr);
WINBOOL SetBkMode(HDC hdc, int32_t iMode);
WINBOOL DeleteDC(HDC hdc);
WINBOOL AlphaBlend(HDC hdcDest, int32_t xoriginDest, int32_t yoriginDest, int32_t wDest, int32_t hDest, HDC hdcSrc, int32_t xoriginSrc, int32_t yoriginSrc, int32_t wSrc, int32_t hSrc, BLENDFUNCTION ftn);
WINBOOL GetObject(HGDIOBJ hgdiobj, int32_t iSize, void * object);
WINBOOL GetTextExtentPoint(HDC hdc, const char * pszText, int32_t iSize, SIZE * psize);
/*WINBOOL WINAPI TransparentBlt(HDC hdcDest,
    __in int32_t xoriginDest,
    __in int32_t yoriginDest,
    __in int32_t wDest,
    __in int32_t hDest,
    __in HDC hdcSrc,
    __in int32_t xoriginSrc,
    __in int32_t yoriginSrc,
    __in int32_t wSrc,
    __in int32_t hSrc,
    __in UINT crTransparent);

*/
