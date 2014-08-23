#pragma once


class CLASS_DECL_AURA window_gdi :
   public window_graphics
{
public:


   HBITMAP              m_hbitmap;
   HBITMAP              m_hbitmapOld;
   BITMAPINFO           m_bitmapinfo;
   COLORREF *           m_pcolorref;
   HDC                  m_hdc;


   window_gdi();
   virtual ~window_gdi();

   virtual void create_window_graphics(oswindow interaction_impl, int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy_window_graphics();

   virtual void update_window(oswindow interaction_impl, COLORREF * pcolorref, const RECT & rect, int iStride = -1);

};
