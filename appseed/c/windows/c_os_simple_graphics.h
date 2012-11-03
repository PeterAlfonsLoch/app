#pragma once




class CLASS_DECL_c os_simple_graphics
{
public:

   
   Gdiplus::Graphics *     m_pgraphics;
   HDC                     m_hdc;
   oswindow_                    m_hwnd;
   simple_bitmap           m_bitmap;
   simple_pen              m_pen;
   os_simple_font          m_font;
   simple_brush            m_brush;
   int                     m_iType;
   PAINTSTRUCT             m_ps;


   os_simple_graphics();
   ~os_simple_graphics();


   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create();
   bool destroy();
   bool bit_blt(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, DWORD rop);
   bool create_from_bitmap(simple_bitmap & b);
   bool detach_bitmap();
   bool select(simple_font & font);
   bool select(simple_brush & brush);
   bool select(simple_pen & brush);
   bool text_out(int x, int y, const char * pszUtf8, int iLen = -1);
   bool blend_bitmap_data(int x, int y, int cx, int cy, COLORREF * pdata);
   SIZE get_text_extent(const char * psz, int iLen = -1);
   bool set_text_color(COLORREF cr);

   bool is_null();
   bool set_alpha_mode(::ca::e_alpha_mode emode);
   
   bool rectangle(LPCRECT lpcrect);
   bool draw_line(int x1, int y1, int x2, int y2, simple_pen & pen);
   bool draw_rect(LPCRECT lpcrect, simple_pen & pen);
   bool fill_rect(LPCRECT lpcrect, simple_brush & brush);
   void fill_solid_rect(LPCRECT lpRect, COLORREF clr);


   bool fill_polygon(POINT * p, int iCount, ::ca::e_fill_mode);


   bool draw_path(simple_path & path, simple_pen & pen);
   bool fill_path(simple_path & path, simple_brush & brush);



   bool replace_clip(simple_path & path);
   bool exclude_clip(simple_path & path);
   bool replace_clip(const RECT & r);
   bool remove_clip();


   // may be multi-platform
   bool create_from_screen();
   POINT get_offset();
   bool set_offset(int x, int y);
   bool offset(int x, int y);
   

   // platform-specific
   bool create(HDC hdc);
   bool from_entire_window(oswindow_ hwnd);
   bool from_window(oswindow_ hwnd);
   bool from_window_paint(oswindow_ hwnd, LPRECT lprectPaint = NULL);
   bool reference_os_data(Gdiplus::Graphics * pgraphics);
   operator Gdiplus::Graphics *() { return m_pgraphics; }






};




