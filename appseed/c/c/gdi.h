#pragma once


#include <d2d1.h>


class simple_graphics
{
public:

#ifdef LINUX
   // X11
#elif defined(MACOS)
   //X11 or Cocoa
#elif defined(WINDOWSEX)
   HDC                     m_hdc;
#elif defined(MERDE_WINDOWS)
   ID2D1RenderTarget *     m_pdc;
   IDWriteTextFormat *     m_pfont;
   ID2D1Brush *            m_pbrush;
#else
#pragma error "what? how should implement or handle?";
#endif


};


CLASS_DECL_c bool    TextOutU_dup(simple_graphics & g, int x, int y, const char * pszUtf8, int iSize);
CLASS_DECL_c void    FillSolidRect_dup(simple_graphics & g, LPCRECT lpRect, COLORREF clr);
CLASS_DECL_c HFONT   CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, simple_graphics & g);
CLASS_DECL_c HFONT   CreatePointFont_dup(int nPointSize, const char * lpszFaceName, HDC hdc);
CLASS_DECL_c HFONT   CreatePointBoldFont_dup(int nPointSize, const char * lpszFaceName, int BOLD, simple_graphics & g);
CLASS_DECL_c HFONT   CreatePointFontIndirect_dup(const LOGFONT* lpLogFont, simple_graphics & g);
