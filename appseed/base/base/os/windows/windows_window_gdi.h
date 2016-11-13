#pragma once


class CLASS_DECL_BASE window_gdi :
   virtual public window_buffer
{
   COLORREF *                    m_pcolorref;
   HBITMAP                       m_hbitmap;
   HDC                           m_hdc;
public:


   HBITMAP                       m_hbitmapOld;
   BITMAPINFO                    m_bitmapinfo;
   HDC                           m_hdcScreen;
   bool                          m_bOwnDC;
   HANDLE                        m_hmutex;
   rect                          m_rectLast;


   window_gdi(::aura::application * papp);
   virtual ~window_gdi();


   virtual void create_window_graphics_(int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy_window_graphics_();

   virtual void create_buffer(int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy_buffer();

   virtual void on_create_window(::user::interaction_impl * pimpl);

   virtual void update_window(::draw2d::dib * pdib) override;

   virtual void ipc_copy(int cx, int cy);

};
