#pragma once


#include "ios_window_boot.h"


namespace os
{


   class CLASS_DECL_AXIS simple_ui :
      virtual public ::simple_ui::interaction,
      virtual public ::boot_window
   {
   public:


      HINSTANCE                  m_hinstance;
      string                     m_strTitle;
      string                     m_strWindowClass;

      int                        m_w;
      int                        m_h;
      ::draw2d::dib_sp           m_dib;
      SIZE                       m_size;
      POINT                      m_pt;


      oswindow                   m_window;
      bool                       m_bShiftKey;
      rect                       m_rectDesktop;

      bool                       m_bNoDecorations;
      manual_reset_event         m_evDone;




      simple_ui(sp(base_application) papp);

      virtual ~simple_ui();

      virtual bool create_window(LPCRECT lprect);

      virtual bool prepare_window(LPCRECT lprect);

      virtual bool show_window(bool bShow = true);
      
      virtual bool destroy_window();

      virtual void client_to_screen(POINT * ppt);

      virtual void screen_to_client(POINT * ppt);

      virtual void GetWindowRect(RECT * prect);
      virtual void get_client_rect(RECT * prect);



//      virtual void on_windows_gdi_draw_framebuffer();


      virtual void set_capture();
      virtual void release_capture();


      virtual bool run_loop();

      virtual void boot_window_draw(CGContextRef cgc);
      virtual void boot_window_mouse_down(double x, double y);
      virtual void boot_window_mouse_up(double x, double y);
      virtual void boot_window_mouse_moved(double x, double y);
      virtual void boot_window_mouse_dragged(double x, double y);
      virtual bool boot_window_key_down(::user::e_key ekey, const char * characters);
      virtual bool boot_window_key_up(::user::e_key ekey, const char * characters);
      
      
      virtual void redraw_window();
      
      virtual interaction * get_focus();

      
      virtual bool move_window(int32_t x, int32_t y);
      virtual bool set_window_pos(int32_t x, int32_t y, int32_t cx, int32_t cy, bool bShow);
      

   };




} // namespace os





