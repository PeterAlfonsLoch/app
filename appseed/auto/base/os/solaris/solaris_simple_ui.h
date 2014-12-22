#pragma once


#include "base/os/solaris/solaris_window_xlib.h"


namespace os
{


   class CLASS_DECL_BASE simple_ui :
      virtual public ::simple_ui::interaction
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
      window_xlib                m_xlib;


      oswindow                   m_window;
      bool                       m_bShiftKey;
      rect                       m_rectDesktop;

      XWindowAttributes          m_attr;
      int32_t                    m_iDepth;
      XVisualInfo                m_visualinfo;
      int                        m_iScreen;


      window_graphics *          m_pgraphics;


      bool                       m_bComposite;

      mutex *                    m_pmutexGraphics;
      mutex *                    m_pmutexDisplay;

      bool                       m_bRunLoop;

      rect                       m_rectWindow;

      bool                       m_bNoDecorations;


      simple_ui(sp(base_application) papp);

      virtual ~simple_ui();

      virtual bool create_window(LPCRECT lprect);

      virtual bool prepare_window(LPCRECT lprect);


      using ::simple_ui::interaction::client_to_screen;
      virtual void client_to_screen(POINT * ppt);

      using ::simple_ui::interaction::screen_to_client;
      virtual void screen_to_client(POINT * ppt);

      virtual void GetWindowRect(RECT * prect);
      virtual void get_client_rect(RECT * prect);


      virtual bool show_window(bool bShow = true);

      virtual bool destroy_window();


      virtual bool on_key_down(uint32_t uiKey);
      virtual bool on_key_up(uint32_t uiKey);


      virtual bool on_move(int32_t x, int32_t y);
      virtual bool on_size(int32_t cx, int32_t cy);


      virtual void run_loop();


      virtual void on_draw_framebuffer();

      virtual void set_capture();
      virtual void release_capture();

      virtual bool move_window(int32_t x, int32_t y);
      virtual bool set_window_pos(int32_t x, int32_t y, int32_t cx, int32_t cy, bool bShow);

   };




} // namespace os



CLASS_DECL_BASE void wm_nodecorations(oswindow w, int map);



/* MWM decorations values */
 #define MWM_DECOR_NONE          0
 #define MWM_DECOR_ALL           (1L << 0)
 #define MWM_DECOR_BORDER        (1L << 1)
 #define MWM_DECOR_RESIZEH       (1L << 2)
 #define MWM_DECOR_TITLE         (1L << 3)
 #define MWM_DECOR_MENU          (1L << 4)
 #define MWM_DECOR_MINIMIZE      (1L << 5)
 #define MWM_DECOR_MAXIMIZE      (1L << 6)

 /* KDE decoration values */
 enum {
  KDE_noDecoration = 0,
  KDE_normalDecoration = 1,
  KDE_tinyDecoration = 2,
  KDE_noFocus = 256,
  KDE_standaloneMenuBar = 512,
  KDE_desktopIcon = 1024 ,
  KDE_staysOnTop = 2048
 };
