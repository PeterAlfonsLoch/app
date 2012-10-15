#pragma once




class CLASS_DECL_c simple_graphics
{
public:

   
   Gdiplus::Graphics *     m_pgraphics;
   HDC                     m_hdc;
   HWND                    m_hwnd;
   simple_bitmap *         m_pbitmap;
   simple_pen *            m_ppen;
   simple_font *           m_pfont;
   simple_brush *          m_pbrush;
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
   bool select(simple_font & font);
   bool select(simple_brush & brush);
   bool select(simple_pen & brush);
   bool text_out(int x, int y, const char * pszUtf8, int iLen = -1);
   bool blend_bitmap_data(int x, int y, int cx, int cy, COLORREF * pdata);
   bool fill_polygon(POINT * p, int iCount, ::ca::e_fill_mode);
   SIZE get_text_extent(const char * psz, int iLen = -1);
   bool set_text_color(COLORREF cr);
   
   bool draw_line(int x1, int y1, int x2, int y2, simple_pen & pen);
   
   inline bool draw_line(int x1, int y1, int x2, int y2);
   inline bool draw_line(POINT p1, POINT p2, simple_pen & pen);
   inline bool draw_line(POINT p1, POINT p2);

   bool rectangle(LPCRECT lpcrect);
   bool draw_rect(LPCRECT lpcrect, simple_pen & pen);
   bool fill_rect(LPCRECT lpcrect, simple_brush & brush);
   void fill_solid_rect(LPCRECT lpRect, COLORREF clr);

   inline bool rectangle(const RECT & rect);
   inline bool draw_rect(const RECT & rect);
   inline bool draw_rect(const RECT & rect, simple_pen & pen);
   inline bool fill_rect(const RECT & rect);
   inline bool fill_rect(const RECT & rect, simple_brush & brush);
   inline void fill_solid_rect(const RECT & rect, COLORREF clr);

   bool draw_path(simple_path & path, simple_pen & pen);
   bool fill_path(simple_path & path, simple_brush & brush);

   bool set_alpha_mode(::ca::e_alpha_mode emode);


   bool replace_clip(simple_path & path);
   bool exclude_clip(simple_path & path);
   bool replace_clip(const RECT & r);
   bool remove_clip();


   // may be multi-platform
   bool create_from_screen();
   bool set_offset(int x, int y);
   bool offset(int x, int y);
   

   // platform-specific
   bool create(HDC hdc);
   bool from_entire_window(HWND hwnd);
   bool from_window(HWND hwnd);
   bool from_window_paint(HWND hwnd, LPRECT lprectPaint = NULL);
   bool reference_os_data(Gdiplus::Graphics * pgraphics);
   operator Gdiplus::Graphics *() { return m_pgraphics; }






};




inline bool simple_graphics::draw_line(int x1, int y1, int x2, int y2)
{
   
   if(m_ppen == NULL)
      return true;

   return draw_line(x1, y1, x2, y2, *m_ppen);

}

inline bool simple_graphics::draw_line(POINT p1, POINT p2, simple_pen & pen)
{
   return draw_line(p1.x, p1.y, p2.x, p2.y, pen);
}

inline bool simple_graphics::draw_line(POINT p1, POINT p2)
{
   
   if(m_ppen == NULL)
      return true;

   return draw_line(p1, p2, *m_ppen);

}




inline bool simple_graphics::draw_rect(const RECT & rect)
{
   
   if(m_ppen == NULL)
      return true;

   return draw_rect(&rect, *m_ppen);

}

inline bool simple_graphics::draw_rect(const RECT & rect, simple_pen & pen)
{
   return draw_rect(&rect, pen);
}

inline bool simple_graphics::fill_rect(const RECT & rect)
{
   
   if(m_pbrush == NULL)
      return true;

   return fill_rect(&rect, *m_pbrush);

}

inline bool simple_graphics::fill_rect(const RECT & rect, simple_brush & brush)
{
   return fill_rect(&rect, brush);
}

inline bool simple_graphics::rectangle(const RECT & rect)
{
   return rectangle(&rect);
}





