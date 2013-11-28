#include "framework.h"


CLASS_DECL_BASE void draw_ca2(::draw2d::graphics * pdc, int x, int y, int z, COLORREF crBk, COLORREF cr);
CLASS_DECL_BASE void draw_ca2_with_border(::draw2d::graphics * pdc, int x, int y, int z, int b, COLORREF crBk, COLORREF cr, COLORREF crOut);
CLASS_DECL_BASE void draw_ca2_with_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crBorderOut, COLORREF crIn);

namespace fontopus
{


   simple_ui::simple_ui(sp(base_application) papp) :
      element(papp),
      ::simple_ui::style(papp),
      interaction(papp),
      ::os::simple_ui(papp),
      m_login(papp, 0, 0)
   {

      m_eschema = schema_normal;
      m_login.set_parent(this);
      m_login.m_pstyle = this;
      m_login.m_pcallback = this;
      m_bLButtonDown = false;
      m_w = 840;
      m_h = 284;

      m_bNoDecorations = true;

      m_eresult = login::result_fail;

   }


   simple_ui::~simple_ui()
   {

   }


   byte brate(double dRate, double dMin, double dMax)
   {
      return (byte)(dRate * (dMax - dMin) + dMin);
   }

   bool simple_ui::on_char(int iKeyCode, const string & strChar)
   {

      if(iKeyCode == VK_RETURN)
      {

         on_action("submit");

         return true;

      }
      else
      {

         return ::os::simple_ui::on_char(iKeyCode, strChar);

      }

   }

   void simple_ui::draw_auth_box(::draw2d::graphics * pgraphics)
   {

      rect rect;

      get_client_rect(rect);

      pgraphics->set_alpha_mode(draw2d::alpha_mode_blend);

      // front
      point pa[4];
      //  0       1
      //
      //
      //  3       2

      // back
      point pb[4];


      // guards
      point pc[4];


      pa[0].x = rect.left;
      pa[0].y = rect.top;
      pa[1].x = rect.right - rect.width() / 10;
      pa[1].y = rect.top + rect.height() / 10;
      pa[2].x = rect.right - rect.width() / 8;
      pa[2].y = rect.bottom - rect.height() / 10;
      pa[3].x = rect.left;
      pa[3].y = rect.bottom;


      pb[0].x = rect.left + rect.width() / 6;
      pb[0].y = rect.top + rect.height() / 6;
      pb[1].x = rect.right - rect.width() / 6;
      pb[1].y = rect.top + rect.height() / 6;
      pb[2].x = rect.right - rect.width() / 5;
      pb[2].y = rect.bottom - rect.height() / 4;
      pb[3].x = rect.left + rect.width() / 5;
      pb[3].y = rect.bottom - rect.height() / 4;

      {

         ::draw2d::brush_sp b(allocer());

         b->create_solid(ARGB(184, 220, 220, 220));

         pgraphics->SelectObject(b);

         pgraphics->fill_polygon(pb, 4);

         ::draw2d::pen_sp p(allocer());

         p->create_solid(pgraphics, 1.0, ARGB(184, 184, 184, 184));

         pgraphics->SelectObject(p);

         pgraphics->draw_polygon(pb, 4);


      }













      // top
      memcpy(pc, pa, sizeof(pb));
      pc[2].x = pb[1].x;
      pc[2].y = pb[1].y;
      pc[3].x = pb[0].x;
      pc[3].y = pb[0].y;

      {

         ::draw2d::brush_sp b(allocer());

         b->create_solid(ARGB(177, 210, 210, 210));

         pgraphics->SelectObject(b);

         pgraphics->fill_polygon(pc, 4);

         ::draw2d::pen_sp p(allocer());

         p->create_solid(pgraphics, 1.0, ARGB(177, 177, 177, 177));

         pgraphics->SelectObject(p);

         pgraphics->draw_polygon(pc, 4);


      }
      // left
      memcpy(pc, pa, sizeof(pb));
      pc[1].x = pb[0].x;
      pc[1].y = pb[0].y;
      pc[2].x = pb[3].x;
      pc[2].y = pb[3].y;
      {

         ::draw2d::brush_sp b(allocer());

         b->create_solid(ARGB(123, 123, 123, 123));

         pgraphics->SelectObject(b);

         pgraphics->fill_polygon(pc, 4);

         ::draw2d::pen_sp p(allocer());

         p->create_solid(pgraphics, 1.0, ARGB(123, 84, 84, 84));

         pgraphics->SelectObject(p);

         pgraphics->draw_polygon(pc, 4);


      }
      // bottom
      memcpy(pc, pa, sizeof(pb));
      pc[0].x = pb[3].x;
      pc[0].y = pb[3].y;
      pc[1].x = pb[2].x;
      pc[1].y = pb[2].y;
      {

         ::draw2d::brush_sp b(allocer());

         b->create_solid(ARGB(149, 184, 184, 184));

         pgraphics->SelectObject(b);

         pgraphics->fill_polygon(pc, 4);

         ::draw2d::pen_sp p(allocer());

         p->create_solid(pgraphics, 1.0, ARGB(149, 177, 177, 177));

         pgraphics->SelectObject(p);

         pgraphics->draw_polygon(pc, 4);


      }
      // right
      memcpy(pc, pa, sizeof(pb));
      pc[0].x = pb[1].x;
      pc[0].y = pb[1].y;
      pc[3].x = pb[2].x;
      pc[3].y = pb[2].y;
      {

         ::draw2d::brush_sp b(allocer());

         b->create_solid(ARGB(84, 149, 149, 149));

         pgraphics->SelectObject(b);

         pgraphics->fill_polygon(pc, 4);

         ::draw2d::pen_sp p(allocer());

         p->create_solid(pgraphics, 1.0, ARGB(84, 123, 123, 123));

         pgraphics->SelectObject(p);

         pgraphics->draw_polygon(pc, 4);


      }





      {

         ::draw2d::pen_sp p(allocer());

         p->create_solid(pgraphics, 1.0, ARGB(184, 84, 84, 84));

         pgraphics->SelectObject(p);

         pgraphics->draw_polygon(pa, 4);

      }


   }


   void simple_ui::draw_pestana(::draw2d::graphics * pgraphics)
   {

      rect rectWindow;

      GetWindowRect(rectWindow);

      pgraphics->set_alpha_mode(draw2d::alpha_mode_blend);

      int iCount = rectWindow.height();
      ::draw2d::pen_sp p(allocer());
      for (int i = 0; i < iCount; i += 2)
      {
         double dRate = (double)i / (double)iCount;
         dRate = 1.0 - dRate;
         byte a1 = brate(1.0 - dRate, 23, 84);
         byte r1 = brate(dRate, 23, 127);
         byte g1 = brate(dRate, 23, 127);
         byte b1 = brate(dRate, 23, 127);
         p->create_solid(pgraphics, 1.0, ARGB(a1, r1, g1, b1));
         pgraphics->SelectObject(p);
         pgraphics->draw_line(rectWindow.left, i, rectWindow.right, i);

      }


   }









   string simple_ui::show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strRequestingServer)
   {

      if (lprect == NULL)
      {

         ::GetWindowRect(::GetDesktopWindow(), &m_rectDesktop);

      }
      else
      {

         m_rectDesktop = *lprect;

      }

      // TODO: Place code here.
      m_strTitle = "fontopus Auth Windows";
      m_strWindowClass = "fontopus Auth Windows";

      set_focus(&m_login.m_editUser);


      show_window();

      // Perform application initialization:

      m_login.m_strRequestingServer = strRequestingServer;

      m_login.m_bVisible = true;

      #if defined(WINDOWSEX)

         pass block below to run loop in windows ::os::simple_ui
         // Main message loop:
         m_hinstance = ::GetModuleHandle(NULL);

      if (!prepare_window(m_hinstance, SW_SHOW))
      {
         return "";
      }         // Initialize global strings
         register_window_class(m_hinstance);


         MSG msg;
         while (GetMessage(&msg, NULL, 0, 0))
         {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }

      #else


      run_loop();

      #endif

      if (m_eresult == login::result_ok)
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
   bool simple_ui::show_window()
   {

      rect & rectDesktop = m_rectDesktop;

      rect rectFontopus;

      int w = rectDesktop.width() * 2.0 / 5.0;
      int h = rectDesktop.height() * 2.0 / 5.0;

      int minW = 400;
      int minH = 320;
      int maxW = 1024;
      int maxH = 800;

      w = min(maxW, max(minW, w));
      h = 184 + 23 + 184;

      m_w = w - 49 * 2;
      m_h = h - 49 * 3;

      rectFontopus.left = rectDesktop.left + (width(rectDesktop) - w) / 2;
      rectFontopus.top = rectDesktop.top + (height(rectDesktop) - h) / 3;
      rectFontopus.right = rectFontopus.left + w;
      rectFontopus.bottom = rectFontopus.top + h;


      m_login.m_rect.left = 49;
      m_login.m_rect.top = 49 + 86;
      m_login.m_rect.right = m_login.m_rect.left + m_w;
      m_login.m_rect.bottom = m_login.m_rect.top + m_h;

      m_login.defer_translate(this);


      if (!::os::simple_ui::create_window(rectFontopus))
         return false;


      m_login.layout();


      if (!::os::simple_ui::prepare_window(rectFontopus))
         return false;

/*      SetTimer(m_window, 123, 23, NULL);

      ShowWindow(m_window, nCmdShow);

      UpdateWindow(m_window);

      ::SetWindowLong(m_window, GWL_STYLE, WS_VISIBLE);*/


      SetWindowPos(m_window, NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_SHOWWINDOW | SWP_NOZORDER);

      return TRUE;

   }


   /*
   void simple_ui::client_to_screen(POINT * ppt)
   {
      ::ClientToScreen(m_window, ppt);
   }

   void simple_ui::screen_to_client(POINT * ppt)
   {
      ::ScreenToClient(m_window, ppt);
   }
   */

   bool simple_ui::on_lbutton_down(int32_t x, int32_t y)
   {

      if (m_login.on_lbutton_down(x - m_login.m_rect.left, y - m_login.m_rect.top))
         return true;

      m_bLButtonDown = true;
      m_bDrag = false;

      m_ptLButtonDownPos = m_pt;
      ::GetCursorPos(&m_ptLButtonDown);
      set_capture();

      return true;
   }

   bool simple_ui::on_lbutton_up(int32_t x, int32_t y)
   {

      m_bLButtonDown = false;

      if (m_login.on_lbutton_up(x - m_login.m_rect.left, y - m_login.m_rect.top))
         return true;


         release_capture();

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

      return true;


   }

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
            SetWindowPos(m_window, NULL, m_pt.x, m_pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            m_bDrag = false;
         }
         return true;
      }

      if (m_login.on_mouse_move(x - m_login.m_rect.left, y - m_login.m_rect.top))
         return true;

      return true;

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
   void simple_ui::get_client_rect(RECT * prect)
   {

      ::GetClientRect(m_window, prect);

   }*/

   void simple_ui::draw_dark_glass(::draw2d::graphics * pgraphics)
   {

      rect rectWindow;

      GetWindowRect(rectWindow);

      pgraphics->FillSolidRect(rectWindow, ARGB(84, 127, 127, 127));

   }


   void simple_ui::draw_this(::draw2d::graphics * pgraphics)
   {

      draw_auth_rect(pgraphics);

      COLORREF crOut, crIn, crBorderOut, crBorderIn, cr, crBk;

//       if (is_hover() || m_bDown || m_bMouseMove)
/*       {

#if CA2_PLATFORM_VERSION == CA2_BASIS

            crOut = ARGB(184 + 49, 255, 230, 255);

            crIn = ARGB(255, 255, 84 + 49, 255);

            crBorderOut = ARGB(184, 150, 100, 150);

            crBorderIn = ARGB(184, 255, 240, 255);

#else

            crOut = ARGB(184 + 49, 230, 255, 225);

            crIn = ARGB(255, 84 + 49, 255, 77 + 49);

            crBorderOut = ARGB(184, 100, 150, 100);

            crBorderIn = ARGB(184, 240, 255, 235);

#endif

         }
         else*/
         {

#if CA2_PLATFORM_VERSION == CA2_BASIS

            crOut = ARGB(184, 255, 210, 255);

            crIn = ARGB(255, 255, 184 + 49, 255);

            crBorderOut = ARGB(184, 90, 20, 90);

            crBorderIn = ARGB(184, 255, 240, 255);

#else

            crOut = ARGB(184, 210, 255, 205);

            crIn = ARGB(255, 84 + 49, 255, 77 + 49);

            crBorderOut = ARGB(184, 20, 90, 20);

            crBorderIn = ARGB(184, 240, 255, 235);

#endif

         }


#if CA2_PLATFORM_VERSION == CA2_BASIS

      cr = ARGB(223, 84, 49, 77);

#else

      cr = ARGB(223, 49, 84, 23);

#endif

      crBk = ARGB(
               (GetAValue(crOut) + GetAValue(crIn)) / 2,
               (GetRValue(crOut) + GetRValue(crIn)) / 2,
               (GetGValue(crOut) + GetGValue(crIn)) / 2,
               (GetBValue(crOut) + GetBValue(crIn)) / 2);

      draw_ca2_with_border2(pgraphics, 49, 49, 84 + 1 + 1, 1, 1, crBk, cr, crBorderOut, crBorderIn);


   }


   void simple_ui::draw_auth_rect(::draw2d::graphics * pgraphics)
   {

      rect rectClient;

      get_client_rect(rectClient);

      ::draw2d::brush_sp b(allocer());

      b->create_solid(ARGB(255, 255, 255, 255));

      pgraphics->SelectObject(b);

      ::draw2d::pen_sp p(allocer());

      p->create_solid(pgraphics, 1.0, ARGB(255, 0, 0, 0));

      pgraphics->SelectObject(p);

      pgraphics->Rectangle(rectClient);

   }



   void simple_ui::draw_fuzzy_color_spread(::draw2d::graphics * pgraphics)
   {

      rect rectWindow;

      GetWindowRect(rectWindow);

      int i = 0;
      int j = 0;
      int iCount = rectWindow.width();
      int jCount = rectWindow.height();

      BYTE * p = (BYTE *)m_dib->get_data();

      for (i = 0; i < iCount; i++)
      {
         for (j = 0; j < jCount; j++)
         {
            double dPhase = fmod((((double) ::get_tick_count() * 360 * 0.5984 / 1000.0) + (i * 360.0 / (double)iCount) + (j * 360.0 / (double)jCount) + ((double)(sin(((double) ::get_tick_count() * 3.1415 * 2.0  *0.0484 / 1000.0) + i * 3.1415 * 2.0 * 2.0 / (double)(iCount)) * sin(((double) ::get_tick_count() * 3.1415 * 2.0  * 0.0484 / 1000.0) + j * 3.1415 * 2.0 * 2.0 / (double)(jCount)) * 360))), 360.0);
            int32_t iR;
            int32_t iG;
            int32_t iB;
            double dRate = fmod(dPhase, 60.0) / 60.0;
            int32_t iColor = (int32_t)(dRate * 155.0);
            if (dPhase < 60)
            {
               // purple to blue
               iR = 255 - iColor;
               iG = 100;
               iB = 255;
            }
            else if (dPhase < (120))
            {
               // blue to cyan
               iR = 100;
               iG = 100 + iColor;
               iB = 255;
            }
            else if (dPhase < (180))
            {
               // cyan to green
               iR = 100;
               iG = 255;
               iB = 255 - iColor;
            }
            else if (dPhase < (240))
            {
               // green to yellow
               iR = 100 + iColor;
               iG = 255;
               iB = 100;
            }
            else if (dPhase < (300))
            {
               // yellow to red
               iR = 255;
               iG = 255 - iColor;
               iB = 100;
            }
            else
            {
               // red to purple
               iR = 255;
               iG = 100;
               iB = 100 + iColor;
            }

            p[0] = iR;
            p[1] = iG;
            p[2] = iB;
            p[3] = 84;
            p += 4;

         }
      }



   }


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
   bool simple_ui::on_action(const char * pszId)
   {

      if (!strcmp(pszId, "submit"))
      {

         m_bVisible = false;

         ::ShowWindow(m_window, SW_HIDE);

         m_login.login_result(m_login.perform_login());

         if (m_eresult == ::fontopus::login::result_fail)
         {

            SetWindowPos(m_window, NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_SHOWWINDOW);

            m_bVisible = true;

         }
         else
         {
            ::DestroyWindow(m_window);
         }

         return true;

      }
      else if (!strcmp(pszId, "escape"))
      {
         ::DestroyWindow(m_window);
      }

      return false;


   }


   void simple_ui::login_result(login::e_result eresult)
   {

      m_eresult = eresult;

   }



   string CLASS_DECL_BASE show_auth_window(base_application * papp, LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer)
   {

      ::fontopus::simple_ui ui(papp);

      return ui.show_auth_window(lprect, strUsername, strSessId, strServerId, strLoginUrl, strFontopusServer);

   }




} // namespace fontopus


CLASS_DECL_BASE void draw_ca2_with_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crOut, COLORREF crIn)
{

   draw_ca2(pdc, x + bIn + bOut, y + bIn + bOut, z, crBk, cr);

   int w = z / 19;

   if (w < 1)
      w = 1;

   z = w * 19;

   rect r(x + bIn + bOut, y + bIn + bOut, x + bIn + bOut + z, y + bIn + bOut + z);

   ::draw2d::pen_sp p(pdc->allocer());

   p->create_solid(pdc, 1.0, crIn);

   for(int i = 0; i < bIn; i++)
   {

      r.inflate(1, 1);

      pdc->DrawRect(r, p);

   }

   p->create_solid(pdc, 1.0, crOut);

   for(int i = 0; i < bOut; i++)
   {

      r.inflate(1, 1);

      pdc->DrawRect(r, p);

   }


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

   p->create_solid(pdc, 1.0, crBorder);

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

