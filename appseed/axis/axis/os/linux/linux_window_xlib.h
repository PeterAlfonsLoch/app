#pragma once


class CLASS_DECL_AURA window_xlib :
   public window_graphics
{
public:


   oswindow                      m_window;
   device_context *              m_pdc;
   ::primitive::memory           m_mem;
   size                          m_size;
   int                           m_iScan;
   XImage *                      m_pimage;


   window_xlib();
   virtual ~window_xlib();

   virtual void create_window_graphics(oswindow window, int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy_window_graphics();

   virtual void update_window(COLORREF * pOsBitmapData, const RECT & lpcrect, int cxParam, int cyParam, int iStride = -1);

};
