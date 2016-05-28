#pragma once


class CLASS_DECL_BASE window_opengl :
   public window_graphics
{
public:


   //oswindow                      m_hwnd;
   ::draw2d::graphics_sp         m_spgraphics;


   window_opengl(::aura::application * papp);
   virtual ~window_opengl();


   // BOOL CreateHGLRC(HWND hWnd);


   virtual void on_create_window(oswindow wnd);


   virtual void create_window_graphics(oswindow interaction_impl, int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy_window_graphics();

   virtual void update_window();
   //virtual void update_window(COLORREF * pcolorref, int cxParam, int cyParam, int iStride = -1);

   ::draw2d::graphics * on_begin_draw();

};
