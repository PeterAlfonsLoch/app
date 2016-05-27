#pragma once


class CLASS_DECL_BASE window_opengl :
   public window_graphics
{
public:


   HGLRC                m_hrc;


   window_opengl(::aura::application * papp);
   virtual ~window_opengl();


   BOOL CreateHGLRC(HWND hWnd);


   virtual void on_create_window(oswindow wnd);


   virtual void create_window_graphics(oswindow interaction_impl, int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy_window_graphics();


   virtual void update_window(COLORREF * pcolorref, const RECT & rect, int cxParam, int cyParam, int iStride = -1, bool bTransferBuffer = true);


};
