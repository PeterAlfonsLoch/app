#include "framework.h"



namespace os
{


   simple_ui::simple_ui(sp(::axis::application) papp) :
      element(papp),
      simple_ui::interaction(papp),
      m_eventReady(papp)
   {
      
         m_bLButtonDown = false;
      m_w = 840;
      m_h = 284;
      m_window = NULL;

      m_bVisible = false;

   }

   simple_ui::~simple_ui()
   {
   }

   /*

   string simple_ui::show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strRequestingServer)
   {

      m_rectDesktop = *lprect;

      m_strTitle = "simple_ui Auth Windows";

      m_strWindowClass = "simple_ui Auth Windows";

      if (!prepare_window(NULL, SW_SHOW))
      {
         return "";
      }

      m_login.m_strRequestingServer = strRequestingServer;

      m_eventReady.ResetEvent();

      m_eventReady.wait();

      m_bVisible = false;

      if (m_eresult == ::spa_login::result_ok)
      {

         strUsername = m_login.m_editUser.m_strText;
         strSessId = m_login.m_strSessId;
         strServerId = m_login.m_strSecureId;
         strLoginUrl = m_login.m_strLoginUrl;
         return "ok";
      }
      else
      {
         return "fail";
      }


   }

   */

   bool simple_ui::create_window(LPCRECT lpcrect)
   {
      
      m_bVisible = false;

      System.m_psimpleui = this;

      return true;


   }


   //
   //   FUNCTION: prepare_window(HINSTANCE, int)
   //
   //   PURPOSE: Saves instance handle and creates main window
   //
   //   COMMENTS:
   //
   //        In this function, we save the instance handle in a global variable and
   //        create and display the main program window.
   //
   bool simple_ui::prepare_window(LPCRECT lpcrect)
   {


      m_pt.x = lpcrect->left;
      m_pt.y = lpcrect->top;
      m_size.cx = width(lpcrect);
      m_size.cy = height(lpcrect);

      m_rect.left = m_pt.x;
      m_rect.top = m_pt.y;
      m_rect.right = m_rect.left + m_size.cx;
      m_rect.bottom = m_rect.top + m_size.cy;

      return true;

   }

   bool simple_ui::show_window(bool bShow)
   {

      if (!::simple_ui::interaction::show_window(bShow))
         return false;


      return true;

   }


   bool simple_ui::destroy_window()
   {

      m_bVisible = false;

      if (System.m_psimpleui == this)
         System.m_psimpleui = NULL;

      m_eventReady.set_event();

      return true;

   }


   void simple_ui::GetWindowRect(LPRECT lprect)
   {

      m_rect.left = m_pt.x;
      m_rect.top = m_pt.y;
      m_rect.right = m_rect.left + m_size.cx;
      m_rect.bottom = m_rect.top + m_size.cx;

      *lprect = m_rect;

   }

   /*
   bool simple_ui::on_lbutton_down(int32_t x, int32_t y)
   {

      //::ClientToScreen(m_window, &m_ptLButtonDown);

      if (m_login.on_lbutton_down(x - m_login.m_rect.left, y - m_login.m_rect.top))
         return true;

      m_bLButtonDown = true;
      m_bDrag = false;

      m_ptLButtonDownPos = m_pt;
      point ptCursor;
      ::GetCursorPos(&ptCursor);
      m_ptLButtonDown = ptCursor;
      return true;
   }

   bool simple_ui::on_lbutton_up(int32_t x, int32_t y)
   {

      m_bLButtonDown = false;

      if (m_login.on_lbutton_up(x - m_login.m_rect.left, y - m_login.m_rect.top))
         return true;

      /*
      rect rectLogin;

      m_login.get_window_rect(rectLogin);

      point pt(x, y);

      if (!rectLogin.contains(pt))
      {
      ReleaseCapture();
      DestroyWindow(m_window);
      }
      */

      /*      {
      rect rectWindow;
      m_login.get_window_rect(&rectWindow);
      POINT ptCursor;
      ::GetCursorPos(&ptCursor);
      if (!rectWindow.contains(ptCursor))
      DestroyWindow(hWnd);
      }

      return true;


   }*/
   /*
   bool simple_ui::on_mouse_move(int32_t x, int32_t y)
   {

      if (m_bLButtonDown)
      {
         if (!m_bDrag)
         {
            m_bDrag = true;
            POINT ptNow;
            ::GetCursorPos(&ptNow);
            
            m_pt.x = ptNow.x - m_ptLButtonDown.x + m_ptLButtonDownPos.x;
            m_pt.y = ptNow.y - m_ptLButtonDown.y + m_ptLButtonDownPos.y;
            m_rect.left = m_pt.x;
            m_rect.top = m_pt.y;
//            SetWindowPos(m_window, NULL, m_pt.x, m_pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            m_bDrag = false;
         }
         return true;
      }

      if (m_login.on_mouse_move(x - m_login.m_rect.left, y - m_login.m_rect.top))
         return true;

      return true;

   }
   */
   /*

   bool simple_ui::on_windows_key_down(WPARAM wparam, LPARAM lparam)
   {
      if (wparam == VK_SHIFT)
      {
         m_bShiftKey = true;
      }
      else if (wparam == VK_ESCAPE)
      {
         on_action("escape");
      }

      return false;

   }

   bool simple_ui::on_windows_key_up(WPARAM wparam, LPARAM lparam)
   {

      string str;
      wchar_t wsz[32];

      BYTE baState[256];

      ZERO(baState);
      for (int i = 0; i < 256; i++)
      {
         //baState[i] = (BYTE)GetAsyncKeyState(i);
      }

      baState[wparam & 0xff] = 0x80;

      /*if((GetAsyncKeyState(::user::key_shift) & 0x80000000) != 0)
      {
      baState[::user::key_shift] |= 0x80;
      }
        if (m_bShiftKey)
      {
         baState[VK_SHIFT] |= 0x80;
      }

      //int32_t iRet = ToUnicodeEx((UINT)wparam, 0, baState, wsz, 32, 0, GetKeyboardLayout(GetCurrentThreadId()));
      str = wsz;
      m_login.on_char(static_cast<UINT>(wparam), str);

      if (m_bShiftKey && wparam == VK_SHIFT)
      {
         m_bShiftKey = false;
      }


      return false;

   }
*/


   void simple_ui::get_client_rect(RECT * prect)
   {

      prect->left = 0;
      prect->top = 0;
      prect->right = m_size.cx;
      prect->bottom = m_size.cy;

   }

   /*
   void simple_ui::draw_dark_glass(simple_graphics & g)
   {

      rect rectWindow;

      get_window_rect(rectWindow);


      g.fill_solid_rect(rectWindow, ARGB(84, 127, 127, 127));

   }*/

   /*
   void simple_ui::draw(simple_graphics & g)
   {

      //draw_pestana(g);

      draw_auth_box(g);

      simple_ui::draw(g);

   }




   bool simple_ui::on_action(const char * pszId)
   {

      if (!strcmp(pszId, "submit"))
      {

         m_login.m_tap.m_bDown = true;

         m_bVisible = false;

         m_login.login_result(m_login.login());

         if (m_eresult == ::spa_login::result_fail)
         {
            m_bVisible = true;
         }
         else
         {
            m_eventReady.SetEvent();
         }

         return true;

      }
      else if (!strcmp(pszId, "escape"))
      {
         m_eventReady.SetEvent();
      }

      return false;


   }
   */
   /*
   void simple_ui::login_result(::spa_login::e_result eresult)
   {

      m_eresult = eresult;

   }


   void on_lbutton_up(int32_t x, int32_t y)
   {
      x -= ::simple_ui::simple_ui::s_fontopus.m_rect.left;
      y -= ::simple_ui::simple_ui::s_fontopus.m_rect.top;
      simple_ui::s_fontopus.on_lbutton_up(x, y);
   }

   void on_lbutton_down(int32_t x, int32_t y)
   {
      x -= ::simple_ui::simple_ui::s_fontopus.m_rect.left;
      y -= ::simple_ui::simple_ui::s_fontopus.m_rect.top;
      simple_ui::s_fontopus.on_lbutton_down(x, y);
   }

   void on_mouse_move(int32_t x, int32_t y)
   {
      x -= ::simple_ui::simple_ui::s_fontopus.m_rect.left;
      y -= ::simple_ui::simple_ui::s_fontopus.m_rect.top;
      simple_ui::s_fontopus.on_mouse_move(x, y);
   }

   void on_char(int32_t iKey, const string & strChar)
   {
      simple_ui::s_fontopus.on_char(iKey, strChar);
   }

   simple_ui simple_ui::s_fontopus;

   string CLASS_DECL_BOOT show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer)
   {

      return ::simple_ui::simple_ui::s_fontopus.show_auth_window(lprect, strUsername, strSessId, strServerId, strLoginUrl, strFontopusServer);

   }


   bool get_visible()
   {
      return ::simple_ui::simple_ui::s_fontopus.m_bVisible;
   }

   */
/*   void draw(ID2D1DeviceContext * pctx)
   {

      simple_graphics g;

      g.m_pdc = pctx;

      g.set_offset(::simple_ui::simple_ui::s_fontopus.m_rect.left, ::simple_ui::simple_ui::s_fontopus.m_rect.top);

      ::simple_ui::simple_ui::s_fontopus.draw(g);

      g.m_pdc = NULL;

   }*/

   bool simple_ui::run_loop()
   {

      m_eventReady.wait();

      return true;

   }

   bool simple_ui::set_window_pos(int x, int y, int cx, int cy, bool bShow)
   {

      m_pt.x = x;
      m_pt.y = y;
      m_size.cx = cx;
      m_size.cy = cy;
      m_rect.left = m_pt.x;
      m_rect.top = m_pt.y;
      m_rect.right = m_rect.left + m_size.cx;
      m_rect.bottom = m_rect.top + m_size.cy;


      if (bShow)
      {

         show_window();

      }

      return true;

   }


   bool simple_ui::move_window(int x, int y)
   {

      m_pt.x = x;
      m_pt.y = y;

      m_rect.left = m_pt.x;
      m_rect.top = m_pt.y;
      m_rect.right = m_rect.left + m_size.cx;
      m_rect.bottom = m_rect.top + m_size.cy;

      return true;

   }

   void simple_ui::viewport_client_to_screen(POINT * ppt)
   {

   }


   void simple_ui::viewport_screen_to_client(POINT * ppt)
   {

   }


   void simple_ui::client_to_screen(POINT * ppt)
   {
   
      ::simple_ui::interaction::client_to_screen(ppt);

   }


   void simple_ui::screen_to_client(POINT * ppt)
   {

      ::simple_ui::interaction::screen_to_client(ppt);

   }


   void simple_ui::client_to_screen(RECT * prect)
   {

      client_to_screen((POINT *)&prect->left);
      client_to_screen((POINT *)&prect->right);

   }


   void simple_ui::screen_to_client(RECT * prect)
   {

      screen_to_client((POINT *)&prect->left);
      screen_to_client((POINT *)&prect->right);

   }

   void simple_ui::get_window_rect(RECT * prect)
   {

      *prect = m_rect;

   }


   void simple_ui::set_capture()
   {


   }


   void simple_ui::release_capture()
   {


   }

   void simple_ui::get_cursor_pos(POINT * ppt)
   {

      *ppt = m_ptCursor;

   }

} // namespace simple_ui


