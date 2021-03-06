#pragma once


class CLASS_DECL_BASE window_gdi :
   public window_graphics
{
public:


   HBITMAP                       m_hbitmap;
   HBITMAP                       m_hbitmapOld;
   BITMAPINFO                    m_bitmapinfo;
   COLORREF *                    m_pcolorref;
   HDC                           m_hdc;
   HWND                          m_hwnd;
   HDC                           m_hdcScreen;
   bool                          m_bOwnDC;

   ::visual::dib_sp              m_spdibBuffer;


   window_gdi(::aura::application * papp);
   virtual ~window_gdi();

   virtual void create_window_graphics(oswindow interaction_impl, int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy_window_graphics();

   virtual void update_window();
   virtual void update_window(COLORREF * pcolorref,int cxParam,int cyParam,int iStride = -1);

   
   ::draw2d::graphics * on_begin_draw();


};
