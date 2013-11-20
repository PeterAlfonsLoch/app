#undef new

#include "base/spa/spa_style.h"
#include "user/simple/simple_ui.h"

#include <gdiplus.h>

#define MAX_LOADSTRING 100

#include "windows_window_gdi.h"


namespace os
{


   class CLASS_DECL_BASE simple_ui :
      virtual public ::simple_ui
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
      window_gdi                 m_gdi;


      HWND                       m_hwnd;
      bool                       m_bShiftKey;




      simple_ui();

      virtual ~simple_ui();

      static LRESULT CALLBACK s_window_prodecure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


      virtual ATOM register_window_class(HINSTANCE hInstance);

      virtual bool prepare_window(LPCRECT lprect);


      virtual void client_to_screen(POINT * ppt);

      virtual void screen_to_client(POINT * ppt);

      virtual LRESULT window_procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

      virtual void GetWindowRect(RECT * prect);
      virtual void get_client_rect(RECT * prect);



      virtual bool on_windows_key_down(WPARAM wparam, LPARAM lparam);
      virtual bool on_windows_key_up(WPARAM wparam, LPARAM lparam);

      virtual void on_windows_gdi_draw_framebuffer();

      virtual bool on_windows_move(int32_t x, int32_t y);
      virtual bool on_windows_size(int32_t cx, int32_t cy);



   };




} // namespace os





