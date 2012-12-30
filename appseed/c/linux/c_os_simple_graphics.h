#pragma once


class CLASS_DECL_c os_simple_graphics
{
public:


   cairo_t *               m_pdc; // Cairo drawing context
   int32_t                     m_iScreen;
   Drawable                m_d;
   GC                      m_gc;
   Colormap                m_colormap;
   simple_pen              m_pen;
   simple_brush            m_brush;
   os_simple_font          m_font;
   simple_bitmap           m_bitmap;
/*   oswindow                    m_hwnd;
   HBITMAP                 m_hbitmapOld;
   HPEN                    m_hpenOld;
   HFONT                   m_hfontOld;
   HBRUSH                  m_hbrushOld;
   int32_t                     m_iType;
   PAINTSTRUCT             m_ps;*/
   int32_t                     m_iType;


   os_simple_graphics();
   ~os_simple_graphics();


   bool is_null();




   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
//   bool create();
   bool destroy();
   bool bit_blt(int32_t x, int32_t y, int32_t cx, int32_t cy, simple_graphics & gSrc, int32_t x1, int32_t y1, DWORD rop);
//   bool alpha_blend(int32_t x, int32_t y, int32_t cx, int32_t cy, simple_graphics & gSrc, int32_t x1, int32_t y1, int32_t cx1, int32_t cy1, BLENDFUNCTION bf);
   bool create_from_bitmap(simple_bitmap & b);
   bool detach_bitmap();
   void fill_solid_rect(LPCRECT lpRect, COLORREF clr);
   bool select(simple_font & font);
   bool select(simple_brush & brush);
   bool select(simple_pen & brush);
   bool text_out(int32_t x, int32_t y, const char * pszUtf8, int32_t iLen = -1);
   bool blend_bitmap_data(int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF * pdata);
   bool rectangle(LPCRECT lpcrect);
   SIZE get_text_extent(const char * psz, int32_t iLen = -1);
//   bool set_text_color(COLORREF cr);

   // may be multi-platform
   //bool create(simple_graphics & g);
   //bool create_from_screen();
   bool set_offset(int32_t x, int32_t y);
   bool offset(int32_t x, int32_t y);


   bool set_alpha_mode(::ca::e_alpha_mode emode);

   bool draw_path(simple_path & path, simple_pen & pen);
   bool fill_path(simple_path & path, simple_brush & brush);


   bool draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, simple_pen & pen);
   bool draw_rect(LPCRECT lpcrect, simple_pen & pen);
   bool fill_rect(LPCRECT lpcrect, simple_brush & brush);
   bool fill_polygon(LPPOINT lpa, int32_t iCount, ::ca::e_fill_mode emode);

   bool replace_clip(simple_path & path);
   bool exclude_clip(simple_path & path);
   bool replace_clip(const RECT & rect);


   // platform-specific
   bool create(HDC hdc);
   bool from_entire_window(oswindow hwnd);
   bool from_window(oswindow hwnd);
   bool from_window_paint(oswindow hwnd, LPRECT lprectPaint = NULL);
   bool reference_os_data(HDC hdc);

   bool set(simple_font & font);
   bool set(simple_brush & brush);
   bool set(simple_pen & brush);
   bool set(simple_path & path);
   bool set(os_simple_path::element & e);
   bool set(os_simple_path::arc & a);
   bool set(os_simple_path::line & l);


};






