#pragma once




class CLASS_DECL_BOOT os_simple_graphics
{
public:

   
   Gdiplus::Graphics *     m_pgraphics;
   HDC                     m_hdc;
   oswindow                    m_oswindow;
   simple_bitmap           m_bitmap;
   simple_pen              m_pen;
   os_simple_font          m_font;
   simple_brush            m_brush;
   int32_t                     m_iType;
   PAINTSTRUCT             m_ps;


   os_simple_graphics();
   ~os_simple_graphics();


   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create();
   bool destroy();
   bool bit_blt(int32_t x, int32_t y, int32_t cx, int32_t cy, simple_graphics & gSrc, int32_t x1, int32_t y1, uint32_t rop);
   bool create_from_bitmap(simple_bitmap & b);
   bool detach_bitmap();
   bool select(simple_font & font);
   bool select(simple_brush & brush);
   bool select(simple_pen & brush);
   bool text_out(int32_t x, int32_t y, const char * pszUtf8, strsize iLen = -1);
   bool blend_bitmap_data(int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF * pdata);
   SIZE get_text_extent(const char * psz, strsize iLen = -1);
   bool set_text_color(COLORREF cr);

   bool is_null();
   bool set_alpha_mode(::draw2d::e_alpha_mode emode);
   
   bool rectangle(LPCRECT lpcrect);
   bool draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, simple_pen & pen);
   bool draw_rect(LPCRECT lpcrect, simple_pen & pen);
   bool fill_rect(LPCRECT lpcrect, simple_brush & brush);
   void fill_solid_rect(LPCRECT lpRect, COLORREF clr);


   bool fill_polygon(POINT * p, int32_t iCount, ::draw2d::e_fill_mode);


   bool draw_path(simple_path & path, simple_pen & pen);
   bool fill_path(simple_path & path, simple_brush & brush);



   bool replace_clip(simple_path & path);
   bool exclude_clip(simple_path & path);
   bool replace_clip(const RECT & r);
   bool remove_clip();


   // may be multi-platform
   bool create_from_screen();
   POINT get_offset();
   bool set_offset(int32_t x, int32_t y);
   bool offset(int32_t x, int32_t y);
   

   // platform-specific
   bool create(HDC hdc);
   bool from_entire_window(oswindow oswindow);
   bool from_window(oswindow oswindow);
   bool from_window_paint(oswindow oswindow, LPRECT lprectPaint = NULL);
   bool reference_os_data(Gdiplus::Graphics * pgraphics);
   operator Gdiplus::Graphics *() { return m_pgraphics; }






};




