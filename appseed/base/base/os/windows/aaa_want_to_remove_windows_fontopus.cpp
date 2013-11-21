#include "framework.h"
#include "user/simple/simple_fontopus.h"
#include "windows_simple_ui.h"

#undef new
#include <gdiplus.h>

#define MAX_LOADSTRING 100

#include "windows_window_gdi.h"


namespace fontopus
{


   class fontopus_login :
      virtual public ::spa::style,
      virtual public ::simple_ui,
      virtual public ::spa::login::callback
   {
   public:

      static fontopus_login      s_fontopus;

      ::spa::login::e_result     m_eresult;

      HINSTANCE                  m_hinstance;
      string                     m_strTitle;
      string                     m_strWindowClass;

      int                        m_w;
      int                        m_h;
      ::spa::login               m_login;
      //::draw2d::graphics_sp      m_dib->get_graphics();
      //::draw2d::bitmap     m_bitmap;
      ::draw2d::dib_sp           m_dib;
      SIZE                       m_size;
      POINT                      m_pt;
      bool                       m_bLButtonDown;
      POINT                      m_ptLButtonDown;
      POINT                      m_ptLButtonDownPos;
      window_gdi                 m_gdi;

      bool                       m_bShiftKey;

      HWND                       m_hwnd;
      bool                       m_bDrag;
      rect                       m_rectDesktop;


      fontopus_login();

      virtual ~fontopus_login();

      static LRESULT CALLBACK s_window_prodecure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


      virtual string show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);

      virtual ATOM register_window_class(HINSTANCE hInstance);

      virtual BOOL prepare_window(HINSTANCE hInstance, int nCmdShow);


      virtual void client_to_screen(POINT * ppt);

      virtual void screen_to_client(POINT * ppt);

      virtual LRESULT window_procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

      virtual void GetWindowRect(RECT * prect);
      virtual void get_client_rect(RECT * prect);

      virtual void draw_dark_glass(::draw2d::graphics * pgraphics);
      virtual void draw_pestana(::draw2d::graphics * pgraphics);
      virtual void draw_auth_box(::draw2d::graphics * pgraphics);


      virtual void draw(::draw2d::graphics * pgraphics);


      virtual void draw_fuzzy_color_spread(::draw2d::graphics * pgraphics);

      virtual bool on_lbutton_down(int32_t x, int32_t y);
      virtual bool on_lbutton_up(int32_t x, int32_t y);
      virtual bool on_mouse_move(int32_t x, int32_t y);


      virtual bool on_windows_key_down(WPARAM wparam, LPARAM lparam);
      virtual bool on_windows_key_up(WPARAM wparam, LPARAM lparam);

      virtual void on_windows_gdi_draw_framebuffer();

      virtual bool on_windows_move(int32_t x, int32_t y);
      virtual bool on_windows_size(int32_t cx, int32_t cy);

      virtual bool on_action(const char * pszId);

      virtual void login_result(::spa::login::e_result eresult);

   };







   byte brate(double dRate, double dMin, double dMax)
   {
      return (byte)(dRate * (dMax - dMin) + dMin);
   }

   void fontopus_login::draw_auth_box(::draw2d::graphics * pgraphics)
   {

      rect rect;

      get_client_rect(rect);

      pgraphics->set_alpha_mode(draw2d::alpha_mode_blend);

      // front
      point pa[4];  //  0       1
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


   void fontopus_login::draw_pestana(::draw2d::graphics * pgraphics)
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









   fontopus_login::fontopus_login() :
      m_login(0, 0)
   {
      m_eschema = schema_normal;
      m_login.set_parent(this);
      m_login.m_pstyle = this;
      m_login.m_pcallback = this;
      m_bLButtonDown = false;
      m_w = 840;
      m_h = 284;
      m_hwnd = NULL;

      m_eresult = ::spa::login::result_fail;
   }

   fontopus_login::~fontopus_login()
   {
   }

   string fontopus_login::show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strRequestingServer)
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
      MSG msg;

      m_strTitle = "fontopus Auth Windows";
      m_strWindowClass = "fontopus Auth Windows";

      m_hinstance = ::GetModuleHandle(NULL);

      // Initialize global strings
      register_window_class(m_hinstance);

      // Perform application initialization:
      if (!prepare_window(m_hinstance, SW_SHOW))
      {
         return "";
      }

      m_login.m_strRequestingServer = strRequestingServer;

      // Main message loop:
      while (GetMessage(&msg, NULL, 0, 0))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }

      if (m_eresult == ::spa::login::result_ok)
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
   //  FUNCTION: register_window_class()
   //
   //  PURPOSE: Registers the window class.
   //
   ATOM fontopus_login::register_window_class(HINSTANCE hInstance)
   {
      WNDCLASSEX wcex;

      wcex.cbSize = sizeof(WNDCLASSEX);

      wcex.style = CS_HREDRAW | CS_VREDRAW;
      wcex.lpfnWndProc = s_window_prodecure;
      wcex.cbClsExtra = 0;
      wcex.cbWndExtra = 0;
      wcex.hInstance = hInstance;
      //   wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
      wcex.hIcon = NULL;
      wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
      wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      //wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WIN32PROJECT1);
      wcex.lpszMenuName = NULL;
      wcex.lpszClassName = m_strWindowClass;
      //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
      wcex.hIconSm = NULL;

      return RegisterClassEx(&wcex);
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
   BOOL fontopus_login::prepare_window(HINSTANCE hInstance, int nCmdShow)
   {

      HWND hWnd;

      m_hinstance = hInstance; // Store instance handle in our global variable

      rect & rectDesktop = m_rectDesktop;

      rect rectFontopus;

      int w = m_w + 184;
      int h = m_h + 284;

      rectFontopus.left = rectDesktop.left + (width(rectDesktop) - w) / 2;
      rectFontopus.top = rectDesktop.top + (height(rectDesktop) - h) / 3;
      rectFontopus.right = rectFontopus.left + w;
      rectFontopus.bottom = rectFontopus.top + h;


      m_login.m_rect.left = (w - m_w) / 2;
      m_login.m_rect.top = (h - m_h) / 2;
      m_login.m_rect.right = m_w;
      m_login.m_rect.bottom = m_h;

      m_login.defer_translate(this);

      hWnd = CreateWindowEx(WS_EX_LAYERED, m_strWindowClass, m_strTitle, 0,
         rectFontopus.left,
         rectFontopus.top,
         rectFontopus.width(),
         rectFontopus.height(),
         NULL, NULL, hInstance, NULL);

      m_login.layout();

      if (!hWnd)
      {
         return FALSE;
      }

      m_hwnd = hWnd;

      SetTimer(hWnd, 123, 23, NULL);

      ShowWindow(hWnd, nCmdShow);

      UpdateWindow(hWnd);

      ::SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE);


      return TRUE;

   }


   LRESULT CALLBACK fontopus_login::s_window_prodecure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
   {
      return s_fontopus.window_procedure(hWnd, message, wParam, lParam);
   }


   void fontopus_login::client_to_screen(POINT * ppt)
   {
      ::ClientToScreen(m_hwnd, ppt);
   }

   void fontopus_login::screen_to_client(POINT * ppt)
   {
      ::ScreenToClient(m_hwnd, ppt);
   }

   bool fontopus_login::on_lbutton_down(int32_t x, int32_t y)
   {

      ::ClientToScreen(m_hwnd, &m_ptLButtonDown);

      if (m_login.on_lbutton_down(x, y))
         return true;

      m_bLButtonDown = true;
      m_bDrag = false;

      m_ptLButtonDownPos = m_pt;
      ::GetCursorPos(&m_ptLButtonDown);

      return true;
   }

   bool fontopus_login::on_lbutton_up(int32_t x, int32_t y)
   {

      m_bLButtonDown = false;

      if (m_login.on_lbutton_up(x, y))
         return true;

      /*
      rect rectLogin;

      m_login.GetWindowRect(rectLogin);

      point pt(x, y);

      if (!rectLogin.contains(pt))
      {
      ReleaseCapture();
      DestroyWindow(m_hwnd);
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

   bool fontopus_login::on_mouse_move(int32_t x, int32_t y)
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
            SetWindowPos(m_hwnd, NULL, m_pt.x, m_pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            m_bDrag = false;
         }
         return true;
      }

      if (m_login.on_mouse_move(x, y))
         return true;

      return true;

   }

   bool fontopus_login::on_windows_key_down(WPARAM wparam, LPARAM lparam)
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

   bool fontopus_login::on_windows_key_up(WPARAM wparam, LPARAM lparam)
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
      if (m_bShiftKey)
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


   LRESULT fontopus_login::window_procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

   }

   void fontopus_login::GetWindowRect(RECT * prect)
   {
      ::GetWindowRect(m_hwnd, prect);
   }
   void fontopus_login::get_client_rect(RECT * prect)
   {

      ::GetClientRect(m_hwnd, prect);

   }

   void fontopus_login::draw_dark_glass(::draw2d::graphics * pgraphics)
   {

      rect rectWindow;

      GetWindowRect(rectWindow);


      pgraphics->FillSolidRect(rectWindow, ARGB(84, 127, 127, 127));

   }


   void fontopus_login::draw(::draw2d::graphics * pgraphics)
   {

      //draw_pestana(g);

      draw_auth_box(pgraphics);

      simple_ui::draw(pgraphics);

   }


   void fontopus_login::draw_fuzzy_color_spread(::draw2d::graphics * pgraphics)
   {

      rect rectWindow;

      GetWindowRect(rectWindow);

      int i = 0;
      int j = 0;
      int iCount = rectWindow.width();
      int jCount = rectWindow.height();

      BYTE * p = (BYTE *) m_dib->get_data();

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


   void fontopus_login::on_windows_gdi_draw_framebuffer()
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

         m_gdi.update_window(m_hwnd, (COLORREF *)m_dib->get_data(), &rect);

      }

   }

   bool fontopus_login::on_windows_move(int32_t x, int32_t y)
   {

      m_pt.x = x;
      m_pt.y = y;

      return true;

   }

   bool fontopus_login::on_windows_size(int32_t cx, int32_t cy)
   {

      m_size.cx = cx;
      m_size.cy = cy;

      m_dib.create(::get_thread_app()->allocer());
      m_dib->create(m_size.cx, m_size.cy);

      layout();

      return true;

   }

   bool fontopus_login::on_action(const char * pszId)
   {

      if (!strcmp(pszId, "submit"))
      {


         ::ShowWindow(m_hwnd, SW_HIDE);

         m_login.login_result(m_login.perform_login());

         if (m_eresult == ::spa::login::result_fail)
         {
            ::ShowWindow(m_hwnd, SW_SHOW);
         }
         else
         {
            ::DestroyWindow(m_hwnd);
         }

         return true;

      }
      else if (!strcmp(pszId, "escape"))
      {
         ::DestroyWindow(m_hwnd);
      }

      return false;


   }


   void fontopus_login::login_result(::spa::login::e_result eresult)
   {

      m_eresult = eresult;

   }



   fontopus_login fontopus_login::s_fontopus;

   string CLASS_DECL_BASE show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer)
   {

      return ::fontopus::fontopus_login::s_fontopus.show_auth_window(lprect, strUsername, strSessId, strServerId, strLoginUrl, strFontopusServer);

   }




} // namespace fontopus


