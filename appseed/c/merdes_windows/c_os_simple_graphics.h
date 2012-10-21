#pragma once


class CLASS_DECL_c os_simple_graphics
{
public:


   ID2D1Device *           m_pd;
   ID2D1DeviceContext *    m_pdc;
   IDXGIAdapter *          m_pad;
   IDXGIFactory2 *         m_pfax;
   simple_font             m_font;
   simple_brush            m_brush;
   simple_pen              m_pen;
   simple_bitmap           m_bitmap;

   ID2D1Layer *            m_player;
   ID2D1PathGeometry *     m_pclip;

   int                     m_iType;
   IDXGISwapChain1 *       m_pswapchain;


   os_simple_graphics();
   ~os_simple_graphics();

   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create();
   bool destroy();
   bool bit_blt(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, DWORD rop);
   //bool alpha_blend(int x, int y, int cx, int cy, simple_graphics & gSrc, int x1, int y1, int cx1, int cy1, BLENDFUNCTION bf);
   bool create_from_bitmap(simple_bitmap & b);
   //bool detach_bitmap();
   bool create_device();
   void fill_solid_rect(LPCRECT lpRect, COLORREF clr);
   bool draw_path(simple_path & path, simple_pen & pen);
   bool fill_path(simple_path & path, simple_brush & brush);
   bool fill_polygon(LPPOINT lpa, int iCount, ::ca::e_fill_mode emode);
   bool select(simple_font & font);
   bool select(simple_brush & brush);
   bool select(simple_pen & brush);
   bool text_out(int x, int y, const char * pszUtf8, int iLen = -1);
   bool blend_bitmap_data(int x, int y, int cx, int cy, COLORREF * pdata);
   bool rectangle(LPCRECT lpcrect);
   SIZE get_text_extent(const char * psz, int iLen = -1);
//   bool set_text_color(COLORREF cr);

   void set_alpha_mode(::ca::e_alpha_mode emode);

   bool draw_line(int x1, int y1, int x2, int y2, simple_pen & pen);
   bool draw_rect(LPCRECT lpcrect, simple_pen & pen);
   bool replace_clip(simple_path & path);
   bool exclude_clip(simple_path & path);
   bool replace_clip(const RECT & rect);

   bool fill_rect(LPCRECT lpcrect, simple_brush & brush);


   // may be multi-platform
   //bool create(simple_graphics & g);
   //bool create_from_screen();
   bool set_offset(int x, int y);
   bool offset(int x, int y);
   

   // platform-specific
   bool reference_os_data(ID2D1DeviceContext * pdc);
   bool from_window( Windows::UI::Core::CoreWindow ^ w);
   //bool reference_os_data(ID2D1RenderTarget * pdc);
   operator ID2D1RenderTarget *() { return m_pdc; }







};
