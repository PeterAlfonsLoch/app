#include "framework.h"


CLASS_DECL_BASE void draw_ca2(::draw2d::graphics * pdc, int x, int y, int z, COLORREF crBk, COLORREF cr);
CLASS_DECL_BASE void draw_ca2_with_border(::draw2d::graphics * pdc, int x, int y, int z, int b, COLORREF crBk, COLORREF cr, COLORREF crOut);
CLASS_DECL_BASE void draw_ca2_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crBorderOut, COLORREF crIn);
CLASS_DECL_BASE void draw_ca2_with_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crBorderOut, COLORREF crIn);

namespace fontopus
{


   simple_ui::simple_ui(sp(::base::application) papp) :
      element(papp),
      ::simple_ui::style(papp),
      ::user::interaction(papp),
      m_login(papp, 0, 0)
   {

      m_eschema = schema_normal;
      m_login.set_parent(this);
      m_login.m_pcallback = this;
      m_login.m_pstyle = this;
      m_bLButtonDown = false;
//      m_w = 840;
  //    m_h = 284;

    //  m_bNoDecorations = true;



   }


   simple_ui::~simple_ui()
   {

   }

   void simple_ui::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::interaction::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_CHAR,pdispatch,this,&simple_ui::_001OnChar);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,pdispatch,this,&simple_ui::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,pdispatch,this,&simple_ui::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,pdispatch,this,&simple_ui::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOVE,pdispatch,this,&simple_ui::_001OnMove);
      IGUI_WIN_MSG_LINK(WM_SIZE,pdispatch,this,&simple_ui::_001OnSize);

   }

   void simple_ui::_001OnChar(signal_details * pobj)
   {

      SCAST_PTR(::message::key, pkey, pobj)

      if(pkey->m_ekey == ::user::key_return)
      {

         m_login.on_action("submit");

         pobj->m_bRet = true;

      }

   }


   //void simple_ui::GetWindowRect(LPRECT lprect)
   //{

   //   *lprect = m_rect;

   //}







   string simple_ui::fontopus(LPRECT lprect)
   {

      Application.defer_initialize_twf();

      if(!CreateEx(WS_EX_LAYERED, NULL, NULL, 0, null_rect(), NULL, "fontopus"))
         return "";

      ::rect rectDesktop;

      if (lprect == NULL)
      {

         //         ::GetWindowRect(::GetDesktopWindow(), &m_rectDesktop);
         System.get_monitor_rect(0,&rectDesktop);

      }
      else
      {

         rectDesktop = *lprect;

      }

      SetWindowText( "fontopus Auth Windows");

      m_login.m_editUser.SetFocus();

      rect rectFontopus;

      rect rectLogin;

      m_login.GetWindowRect(rectLogin);

      int w = rectLogin.width();

      int h = rectLogin.height();
      
      double d = (double) w / (double) h;
      
      if(w > rectDesktop.width())
      {
         
         w = rectDesktop.width();
         
         if(d != 0.0)
         {

            h = (int) (w / d);
            
         }
         
      }
      
      if(h > rectDesktop.height())
      {
         
         h = rectDesktop.height();
         
         w = (int) (h  * d);
         
      }
      

      rectFontopus.left = rectDesktop.left + (width(rectDesktop) - w) / 2;
      rectFontopus.top = rectDesktop.top + (height(rectDesktop) - h) / 3;
      rectFontopus.right = rectFontopus.left + w;
      rectFontopus.bottom = rectFontopus.top + h;



      m_login.defer_translate(this);


      m_login.layout();

      SetWindowPos(ZORDER_TOP, rectFontopus, SWP_SHOWWINDOW);

      m_login.ShowWindow(SW_NORMAL);

      RunModalLoop();

      return "";
   }


   string simple_ui::interactive_auth(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strRequestingServer)
   {

      m_login.m_bCred = false;

      m_login.m_strRequestingServer = strRequestingServer;


      fontopus(lprect);

      if (m_login.m_eresult == login::result_ok)
      {

         strUsername = m_login.m_editUser.get_window_text();
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

   string simple_ui::get_cred(LPRECT lprect, string & strUsername, string & strPassword, string strToken, string strTitle)
   {

      m_login.m_bCred = true;

      m_login.m_strCred = strTitle;

      m_login.m_strRequestingServer = strToken;

      fontopus(lprect);

      if (m_login.m_eresult == login::result_ok)
      {

         m_login.m_editUser.GetWindowText(strUsername);
         m_login.m_password.GetWindowText(strPassword);

         return "ok";

      }
      else
      {

         return "fail";

      }


   }

   void simple_ui::layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      m_login.SetPlacement(rectClient);

      m_login.layout();

   }


   /*
   void simple_ui::ClientToScreen(POINT * ppt)
   {
      ::ClientToScreen(m_window, ppt);
   }

   void simple_ui::ScreenToClient(POINT * ppt)
   {
      ::ScreenToClient(m_window, ppt);
   }
   */

   void simple_ui::_001OnLButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if (pobj->previous())
         return;

      m_bLButtonDown = true;
      m_bDrag = false;

      m_ptLButtonDownPos = pmouse->m_pt;
      ::GetCursorPos(&m_ptLButtonDown);
      set_capture();

      pmouse->m_bRet = true;

   }

   void simple_ui::_001OnLButtonUp(signal_details * pobj)
   {

      m_bLButtonDown = false;

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if(pobj->previous())
         return;



         release_capture();

         m_bDrag = false;

      /*
      rect rectLogin;

      m_login.GetWindowRect(rectLogin);

      point pt(x, y);

      if (!rectLogin.contains(pt))
      {
      ReleaseCapture();
      DestroyWindow(m_window);
      }
      */

      /*      {
      rect rectWindow;
      m_login.GetWindowRect(&rectWindow);
      POINT ptCursor;
      ::GetCursorPos(&ptCursor);
      if (!rectWindow.contains(ptCursor))
      DestroyWindow(hWnd);
      }*/

      pobj->m_bRet = true;


   }


   void simple_ui::_001OnMouseMove(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if (m_bLButtonDown)
      {
         if (!m_bDrag)
         {
            m_bDrag = true;
            POINT ptNow = pmouse->m_pt;
            point pt;
            pt.x = ptNow.x - m_ptLButtonDown.x + m_ptLButtonDownPos.x;
            pt.y = ptNow.y - m_ptLButtonDown.y + m_ptLButtonDownPos.y;
            MoveWindow(pt);
            m_bDrag = false;
         }
         pobj->m_bRet = true;

      }
      else
      {
         if(pobj->previous())
            return;

         pobj->m_bRet = true;
      }

   }

/*   bool simple_ui::on_windows_key_down(WPARAM wparam, LPARAM lparam)
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
         baState[i] = (BYTE)GetAsyncKeyState(i);
      }

      baState[wparam & 0xff] = 0x80;

      /*if((GetAsyncKeyState(::user::key_shift) & 0x80000000) != 0)
      {
      baState[::user::key_shift] |= 0x80;
      }
      */
/*      if (m_bShiftKey)
      {
         baState[VK_SHIFT] |= 0x80;
      }

      int32_t iRet = ToUnicodeEx((UINT)wparam, 0, baState, wsz, 32, 0, GetKeyboardLayout(GetCurrentThreadId()));
      str = wsz;
      m_login.on_char(static_cast<UINT>(wparam), str);

      if (m_bShiftKey && wparam == VK_SHIFT)
      {
         m_bShiftKey = false;
      }


      return false;

   }
   */

   /*LRESULT simple_ui::window_procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
   {

      switch (message)
      {
      case WM_DESTROY:
         PostQuitMessage(0);
         break;
      case WM_LBUTTONDOWN:
         on_lbutton_down(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
         break;
      case WM_LBUTTONUP:
         on_lbutton_up(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
         break;
      case WM_MOUSEMOVE:
         on_mouse_move(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
         break;
      case WM_KEYDOWN:
         if (!on_windows_key_down(wParam, lParam))
            goto default_window_procedure;
         break;
      case WM_KEYUP:
         if (!on_windows_key_up(wParam, lParam))
            goto default_window_procedure;
         break;
      case WM_TIMER:
         on_windows_gdi_draw_framebuffer();
         goto default_window_procedure;
      case WM_MOVE:
         if (!on_windows_move(LOWORD(lParam), HIWORD(lParam)))
            goto default_window_procedure;
         break;
      case WM_SIZE:
         if (!on_windows_size(LOWORD(lParam), HIWORD(lParam)))
            goto default_window_procedure;
         break;
      default:
         goto default_window_procedure;
      }

      return 0;

   default_window_procedure:

      return DefWindowProc(hWnd, message, wParam, lParam);

   }*/

/*   void simple_ui::GetWindowRect(RECT * prect)
   {
      ::GetWindowRect(m_window, prect);
   }
   void simple_ui::GetClientRect(RECT * prect)
   {

      ::GetClientRect(m_window, prect);

   }*/





   /*void simple_ui::on_windows_gdi_draw_framebuffer()
   {
      if (m_dib->get_graphics() != NULL)
      {
         RECT rectClient;
         rectClient.left = 0;
         rectClient.top = 0;
         rectClient.right = m_size.cx;
         rectClient.bottom = m_size.cy;
         m_dib->get_graphics()->set_alpha_mode(draw2d::alpha_mode_set);
         m_dib->get_graphics()->FillSolidRect(&rectClient, ARGB(0, 0, 0, 0));
         draw(m_dib->get_graphics());
         RECT rect;
         rect.left = m_pt.x;
         rect.top = m_pt.y;

         rect.right = m_pt.x + m_size.cx;
         rect.bottom = m_pt.y + m_size.cy;

         BYTE *dst = (BYTE*)m_dib->get_data();
         int64_t size = m_size.cx * m_size.cy;


         // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


         while (size >= 8)
         {
            dst[0] = LOBYTE(((int32_t)dst[0] * (int32_t)dst[3]) >> 8);
            dst[1] = LOBYTE(((int32_t)dst[1] * (int32_t)dst[3]) >> 8);
            dst[2] = LOBYTE(((int32_t)dst[2] * (int32_t)dst[3]) >> 8);

            dst[4 + 0] = LOBYTE(((int32_t)dst[4 + 0] * (int32_t)dst[4 + 3]) >> 8);
            dst[4 + 1] = LOBYTE(((int32_t)dst[4 + 1] * (int32_t)dst[4 + 3]) >> 8);
            dst[4 + 2] = LOBYTE(((int32_t)dst[4 + 2] * (int32_t)dst[4 + 3]) >> 8);

            dst[8 + 0] = LOBYTE(((int32_t)dst[8 + 0] * (int32_t)dst[8 + 3]) >> 8);
            dst[8 + 1] = LOBYTE(((int32_t)dst[8 + 1] * (int32_t)dst[8 + 3]) >> 8);
            dst[8 + 2] = LOBYTE(((int32_t)dst[8 + 2] * (int32_t)dst[8 + 3]) >> 8);

            dst[12 + 0] = LOBYTE(((int32_t)dst[12 + 0] * (int32_t)dst[12 + 3]) >> 8);
            dst[12 + 1] = LOBYTE(((int32_t)dst[12 + 1] * (int32_t)dst[12 + 3]) >> 8);
            dst[12 + 2] = LOBYTE(((int32_t)dst[12 + 2] * (int32_t)dst[12 + 3]) >> 8);

            dst[16 + 0] = LOBYTE(((int32_t)dst[16 + 0] * (int32_t)dst[16 + 3]) >> 8);
            dst[16 + 1] = LOBYTE(((int32_t)dst[16 + 1] * (int32_t)dst[16 + 3]) >> 8);
            dst[16 + 2] = LOBYTE(((int32_t)dst[16 + 2] * (int32_t)dst[16 + 3]) >> 8);

            dst[20 + 0] = LOBYTE(((int32_t)dst[20 + 0] * (int32_t)dst[20 + 3]) >> 8);
            dst[20 + 1] = LOBYTE(((int32_t)dst[20 + 1] * (int32_t)dst[20 + 3]) >> 8);
            dst[20 + 2] = LOBYTE(((int32_t)dst[20 + 2] * (int32_t)dst[20 + 3]) >> 8);

            dst[24 + 0] = LOBYTE(((int32_t)dst[24 + 0] * (int32_t)dst[24 + 3]) >> 8);
            dst[24 + 1] = LOBYTE(((int32_t)dst[24 + 1] * (int32_t)dst[24 + 3]) >> 8);
            dst[24 + 2] = LOBYTE(((int32_t)dst[24 + 2] * (int32_t)dst[24 + 3]) >> 8);

            dst[28 + 0] = LOBYTE(((int32_t)dst[28 + 0] * (int32_t)dst[28 + 3]) >> 8);
            dst[28 + 1] = LOBYTE(((int32_t)dst[28 + 1] * (int32_t)dst[28 + 3]) >> 8);
            dst[28 + 2] = LOBYTE(((int32_t)dst[28 + 2] * (int32_t)dst[28 + 3]) >> 8);

            dst += 4 * 8;
            size -= 8;
         }
         while (size--)
         {
            dst[0] = LOBYTE(((int32_t)dst[0] * (int32_t)dst[3]) >> 8);
            dst[1] = LOBYTE(((int32_t)dst[1] * (int32_t)dst[3]) >> 8);
            dst[2] = LOBYTE(((int32_t)dst[2] * (int32_t)dst[3]) >> 8);
            dst += 4;
         }

         m_gdi.update_window(m_window, (COLORREF *)m_dib->get_data(), &rect);

      }

   }*/

   /*bool simple_ui::on_windows_move(int32_t x, int32_t y)
   {

      m_pt.x = x;
      m_pt.y = y;

      return true;

   }

   bool simple_ui::on_windows_size(int32_t cx, int32_t cy)
   {

      m_size.cx = cx;
      m_size.cy = cy;

      m_dib.create(::get_thread_app()->allocer());
      m_dib->create(m_size.cx, m_size.cy);

      layout();

      return true;

   }
   */



   string CLASS_DECL_BASE show_auth_window(::base::application * papp, LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer)
   {

      ::fontopus::simple_ui ui(papp);

      return ui.interactive_auth(lprect, strUsername, strSessId, strServerId, strLoginUrl, strFontopusServer);

   }


   string CLASS_DECL_BASE get_cred(::base::application * papp, LPRECT lprect, string & strUsername, string & strPassword, string strToken, string strTitle)
   {

      ::fontopus::simple_ui ui(papp);

      string str = get_cred(papp, strUsername, strPassword, strToken);

      if (str == "yes")
         return "ok";
         

      return ui.get_cred(lprect, strUsername, strPassword, strToken, strTitle);

   }

   string CLASS_DECL_BASE get_cred(::base::application * papp, string & strUsername, string & strPassword, string strToken)
   {

      string str;
      crypto_file_get(::dir::userappdata("cred/" + strToken + "_a.data"), strUsername, "");
      crypto_file_get(::dir::userappdata("cred/" + strToken + "_b.data"), strPassword, strToken);
      crypto_file_get(::dir::userappdata("cred/" + strToken + "_c.data"), str, strToken);

      return str;

   }

   void set_cred(::base::application * papp, string strToken, bool bOk, const char * pszUsername, const char * pszPassword)
   {

      if (!bOk)
      {
         string strUsername(pszUsername);
         string strPassword(pszPassword);
         string strUsernamePrevious;
         string strPasswordPrevious;

         get_cred(papp, strUsernamePrevious, strPasswordPrevious, strToken);

         if ((strUsername.has_char() && strPassword.has_char())
            && (strUsernamePrevious != strUsername || strPasswordPrevious != strPassword))
         {
            dir::mk(::dir::userappdata("cred"));
            crypto_file_set(::dir::userappdata("cred/" + strToken + "_a.data"), strUsername, "");
            crypto_file_set(::dir::userappdata("cred/" + strToken + "_b.data"), strPassword, strToken);
         }
      }

      if (bOk)
      {

         crypto_file_set(::dir::userappdata("cred/" + strToken + "_c.data"), "yes", strToken);

      }
      else
      {
         crypto_file_set(::dir::userappdata("cred/" + strToken + "_c.data"), "no", strToken);

      }

   }


} // namespace fontopus


CLASS_DECL_BASE void draw_ca2_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crOut, COLORREF crIn)
{


   rect r(x + bIn + bOut, y + bIn + bOut, x + bIn + bOut + z - 1, y + bIn + bOut + z - 1);

   ::draw2d::pen_sp p(pdc->allocer());

   p->create_solid(1.0, crIn);

   for (int i = 0; i < bIn; i++)
   {

      r.inflate(1, 1);

      pdc->DrawRect(r, p);

   }

   p->create_solid(1.0, crOut);

   for (int i = 0; i < bOut; i++)
   {

      r.inflate(1, 1);

      pdc->DrawRect(r, p);

   }


}

CLASS_DECL_BASE void draw_ca2_with_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crOut, COLORREF crIn)
{

   draw_ca2(pdc, x + bIn + bOut, y + bIn + bOut, z, crBk, cr);

   draw_ca2_border2(pdc, x, y, z, bOut, bIn, crBk, cr, crOut, crIn);

}


CLASS_DECL_BASE void draw_ca2_with_border(::draw2d::graphics * pdc, int x, int y, int z, int b, COLORREF crBk, COLORREF cr, COLORREF crBorder)
{

   draw_ca2(pdc, x + b, y + b, z, crBk, cr);

   int w = z / 19;

   if (w < 1)
      w = 1;

   z = w * 19;

   rect r(x + b, y + b, x + b + z, y + b + z);

   ::draw2d::pen_sp p(pdc->allocer());

   p->create_solid(1.0, crBorder);

   for(int i = 0; i < b; i++)
   {

      r.inflate(1, 1);

      pdc->DrawRect(r, p);

   }



}


CLASS_DECL_BASE void draw_ca2(::draw2d::graphics * pdc, int x, int y, int z, COLORREF crBk, COLORREF cr)
{

   ::draw2d::brush_sp b(pdc->allocer());

   // black rectangle

   int w = z / 19;

   if (w < 1)
      w = 1;

   z = w * 19;

   b->create_solid(crBk);

   rect r(x, y, x + z, y + z);

   pdc->FillRect(r, b);








   // bottom line

   b->create_solid(cr);

   r.top += w * 13;
   r.bottom -= w;









   // c

   r.left += w;
   r.right = r.left + w * 5;

   rect c = r;

   c.right = c.left + w;

   pdc->FillRect(c, b);

   c = r;

   c.bottom = c.top + w;

   pdc->FillRect(c, b);

   c = r;

   c.top = c.bottom - w;

   pdc->FillRect(c, b);








   // a

   r.left += w * 6;
   r.right = r.left + w * 5;

   c = r;

   c.bottom = c.top + w;

   pdc->FillRect(c, b);

   c = r;

   c.top = c.bottom - w;

   pdc->FillRect(c, b);

   c = r;

   c.right = c.left + w * 2;
   c.top += w * 2;
   c.bottom = c.top + w;

   pdc->FillRect(c, b);

   c = r;

   c.left += w * 5 / 2;
   c.right = c.left + w;
   c.top += w * 2;
   c.bottom = c.top + w;

   pdc->FillRect(c, b);

   c = r;

   c.left = c.right - w;

   pdc->FillRect(c, b);

   c = r;

   c.right = c.left + w;
   c.top += w * 2;

   pdc->FillRect(c, b);





   // 2

   r.left += w * 6;
   r.right = r.left + w * 5;

   c = r;

   c.bottom = c.top + w;

   pdc->FillRect(c, b);

   c = r;

   c.top = c.bottom - w;

   pdc->FillRect(c, b);

   c = r;

   c.top += w * 2;
   c.bottom = c.top + w;

   pdc->FillRect(c, b);

   c = r;

   c.right = c.left + w;
   c.top += w * 2;

   pdc->FillRect(c, b);

   c = r;

   c.left = c.right - w;
   c.bottom -= w * 2;

   pdc->FillRect(c, b);

}

