#pragma once


class CLASS_DECL_c simple_graphics
{
public:

   
   HDC                     m_hdc;
   HWND                    m_hwnd;
   HBITMAP                 m_hbitmapOld;
   HPEN                    m_hpenOld;
   HFONT                   m_hfontOld;
   HBRUSH                  m_hbrushOld;
   int                     m_iType;
   PAINTSTRUCT             m_ps;


   simple_graphics();
   ~simple_graphics();


   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create();
   bool destroy();
   bool bit_blt(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, DWORD rop);
   bool alpha_blend(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, int cx1, int cy1, BLENDFUNCTION bf);
   bool create_from_bitmap(simple_bitmap & b);
   bool detach_bitmap();
   void fill_solid_rect(LPCRECT lpRect, COLORREF clr);
   bool select(simple_font & font);
   bool select(simple_brush & brush);
   bool select(simple_pen & brush);
   bool text_out(int x, int y, const char * pszUtf8, int iLen = -1);
   bool fill_rect(LPCRECT lpcrect, simple_brush & brush);
   bool blend_bitmap_data(int x, int y, int cx, int cy, COLORREF * pdata);
   bool rectangle(LPCRECT lpcrect);
   SIZE get_text_extent(const char * psz, int iLen = -1);
   bool set_text_color(COLORREF cr);

   // may be multi-platform
   bool create(simple_graphics & g);
   bool create_from_screen();
   bool set_offset(int x, int y);
   bool offset(int x, int y);
   

   // platform-specific
   bool create(HDC hdc);
   bool from_entire_window(HWND hwnd);
   bool from_window(HWND hwnd);
   bool from_window_paint(HWND hwnd, LPRECT lprectPaint = NULL);
   bool reference_os_data(HDC hdc);
   operator HDC() { return m_hdc; }






};


class CLASS_DECL_c simple_brush
{
public:

   
   HBRUSH                  m_hbrush;
   bool                    m_bDelete;


   simple_brush();
   ~simple_brush();


   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create_solid(COLORREF cr);
   bool destroy();


   // platform-specific
   bool from_stock(int iId);


};



class CLASS_DECL_c simple_bitmap
{
public:

   
   HBITMAP                  m_hbitmap;


   simple_bitmap();
   ~simple_bitmap();


   bool create(int cx, int cy, simple_graphics & g, COLORREF ** ppdata = NULL);
   bool create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g);
   bool destroy();


};

class CLASS_DECL_c simple_font
{
public:

   
   HFONT                  m_hfont;


   simple_font();
   ~simple_font();

   bool create_point(int nPointSize, const char * lpszFaceName, simple_graphics & g);
   bool create_point_bold(int nPointSize, const char * lpszFaceName, int BOLD, simple_graphics & g);
   
   // aim to be all-platoform
   bool destroy();


   // platform-specific
   bool create_indirect(LPLOGFONT lplf);

};



class CLASS_DECL_c simple_pen
{
public:

   
   HPEN                  m_hpen;


   simple_pen();
   ~simple_pen();

   bool create_solid(int iWidth, COLORREF cr);

   bool destroy();



};

