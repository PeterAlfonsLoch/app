#pragma once


class CLASS_DECL_c simple_graphics
{
public:


   ID2D1DeviceContext *    m_pdc;
   simple_font             m_font;
   simple_brush            m_brush;
   simple_pen              m_pen;
   simple_bitmap           m_bitmap;

   ID2D1Layer *            m_player;
   ID2D1PathGeometry *     m_pclip;

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

   bool draw_line(simple_pen * ppen, int x1, int y1, int x2, int y2);
   bool replace_clip(ID2D1PathGeometry * ppath);
   bool exclude_clip(ID2D1PathGeometry * ppath);

   // may be multi-platform
   bool create(simple_graphics & g);
   bool create_from_screen();
   bool set_offset(int x, int y);
   bool offset(int x, int y);
   

   // platform-specific
   bool create(ID2D1RenderTarget * pdc);
   bool from_entire_window(HWND hwnd);
   bool from_window(HWND hwnd);
   bool from_window_paint(HWND hwnd, LPRECT lprectPaint = NULL);
   bool reference_os_data(ID2D1RenderTarget * pdc);
   operator ID2D1RenderTarget *() { return m_pdc; }







};
