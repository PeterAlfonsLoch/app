//
//  c_os_simple_graphics.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 9/30/12.
//
//



class CLASS_DECL_c simple_graphics
{
public:
   
#ifdef __MM
   NSGraphicsContext *     m_nsgc;
#else
   void *                  m_pnsgc;
   
#endif
   
   //Display *               m_pdisplay;
   int                     m_iScreen;
   //Drawable                m_d;
   //GC                      m_gc;
   //Colormap                m_colormap;
   simple_pen              m_pen;
   simple_brush            m_brush;
   simple_font             m_font;
   simple_bitmap           m_bitmap;
   /*   HWND                    m_hwnd;
    HBITMAP                 m_hbitmapOld;
    HPEN                    m_hpenOld;
    HFONT                   m_hfontOld;
    HBRUSH                  m_hbrushOld;
    int                     m_iType;
    PAINTSTRUCT             m_ps;*/
   int                     m_iType;
   bool                    m_bForeColor;
   bool                    m_bBackColor;
   long unsigned int       m_uiForeColor;
   long unsigned int       m_uiBackColor;
   COLORREF                m_crTextColor;
   
   
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
//   XFontStruct * get_font(simple_font & font);
//   XFontStruct * get_font();
   void select_brush();
   void select_brush(simple_brush & brush);
   void select_pen();
   void select_pen(simple_pen & pen);
   long unsigned int alloc_color(COLORREF cr);
   bool free_color(long unsigned int pixel);
   void set_foreground(COLORREF cr);
   void set_background(COLORREF cr);

};
