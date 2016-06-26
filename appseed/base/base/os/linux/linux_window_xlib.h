#pragma once
//#include <X11/extensions/Xrender.h>


class CLASS_DECL_AURA window_xlib :
   virtual public window_buffer
{
public:


   //oswindow                      m_window;
   device_context *              m_pdc;
   memory           m_mem;
   size                          m_size;
   int                           m_iScan;
   XImage *                      m_pimage;
   //Pixmap                        m_pixmap;
   //Picture                       m_pictureWindow;
   //Picture                       m_picture;



   window_xlib(::aura::application * papp);
   virtual ~window_xlib();

   virtual void create_window_graphics(int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy_window_graphics();



   virtual void update_window(COLORREF * pOsBitmapData, int cxParam, int cyParam, int iStride = -1);


    //void update_window();

    ::draw2d::graphics * on_begin_draw();




};
