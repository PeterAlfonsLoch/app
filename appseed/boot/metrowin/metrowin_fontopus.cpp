#include "framework.h"
#undef new
#include <gdiplus.h>

#define MAX_LOADSTRING 100



namespace fontopus
{


   class fontopus :
      virtual public ::spa::style,
      virtual public ::simple_ui,
      virtual public ::spa_login::callback
   {
   public:

      static fontopus s_fontopus;

      spa_login::e_result          m_eresult;

      //HINSTANCE         m_hinstance;
      string            m_strTitle;
      string            m_strWindowClass;

      int               m_w;
      int               m_h;
      spa_login         m_login;
      simple_graphics   m_graphics;
      SIZE              m_size;
      POINT             m_pt;
      bool              m_bLButtonDown;
      POINT             m_ptLButtonDown;
      POINT             m_ptLButtonDownPos;

      bool              m_bShiftKey;

      HWND              m_hwnd;
      bool                 m_bDrag;
      manual_reset_event   m_eventReady;
      bool                 m_bVisible;


      rect              m_rectDesktop;



      fontopus();

      virtual ~fontopus();


      virtual string show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);

      virtual BOOL prepare_window(HINSTANCE hInstance, int nCmdShow);


      virtual void get_window_rect(RECT * prect);
      virtual void get_client_rect(RECT * prect);

      virtual void draw_dark_glass(simple_graphics & g);
      virtual void draw_pestana(simple_graphics &g);
      virtual void draw_auth_box(simple_graphics &g);


      virtual void draw(simple_graphics & g);


      virtual bool on_lbutton_down(int32_t x, int32_t y);
      virtual bool on_lbutton_up(int32_t x, int32_t y);
      virtual bool on_mouse_move(int32_t x, int32_t y);


      virtual bool on_windows_key_down(WPARAM wparam, LPARAM lparam);
      virtual bool on_windows_key_up(WPARAM wparam, LPARAM lparam);


      virtual bool on_action(const char * pszId);

      virtual void login_result(::spa_login::e_result eresult);

   };







   byte brate(double dRate, double dMin, double dMax)
   {
      return (byte)(dRate * (dMax - dMin) + dMin);
   }

   void fontopus::draw_auth_box(simple_graphics & g)
   {

      rect rect;

      get_client_rect(rect);

      g.set_alpha_mode(draw2d::alpha_mode_blend);

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

         simple_brush b;

         b.create_solid(g, ARGB(184, 220, 220, 220));

         g.select(b);

         g.fill_polygon(pb, 4, ::draw2d::fill_mode_winding);

         simple_pen p;

         p.create_solid(g, ARGB(184, 184, 184, 184));

         g.select(p);

         g.draw_polygon(pb, 4);


      }













      // top
      memcpy(pc, pa, sizeof(pb));
      pc[2].x = pb[1].x;
      pc[2].y = pb[1].y;
      pc[3].x = pb[0].x;
      pc[3].y = pb[0].y;

      {

         simple_brush b;

         b.create_solid(g, ARGB(177, 210, 210, 210));

         g.select(b);

         g.fill_polygon(pc, 4, ::draw2d::fill_mode_winding);

         simple_pen p;

         p.create_solid(g, ARGB(177, 177, 177, 177));

         g.select(p);

         g.draw_polygon(pc, 4);


      }
      // left
      memcpy(pc, pa, sizeof(pb));
      pc[1].x = pb[0].x;
      pc[1].y = pb[0].y;
      pc[2].x = pb[3].x;
      pc[2].y = pb[3].y;
      {

         simple_brush b;

         b.create_solid(g, ARGB(123, 123, 123, 123));

         g.select(b);

         g.fill_polygon(pc, 4, ::draw2d::fill_mode_winding);

         simple_pen p;

         p.create_solid(g, ARGB(123, 84, 84, 84));

         g.select(p);

         g.draw_polygon(pc, 4);


      }
      // bottom
      memcpy(pc, pa, sizeof(pb));
      pc[0].x = pb[3].x;
      pc[0].y = pb[3].y;
      pc[1].x = pb[2].x;
      pc[1].y = pb[2].y;
      {

         simple_brush b;

         b.create_solid(g, ARGB(149, 184, 184, 184));

         g.select(b);

         g.fill_polygon(pc, 4, ::draw2d::fill_mode_winding);

         simple_pen p;

         p.create_solid(g, ARGB(149, 177, 177, 177));

         g.select(p);

         g.draw_polygon(pc, 4);


      }
      // right
      memcpy(pc, pa, sizeof(pb));
      pc[0].x = pb[1].x;
      pc[0].y = pb[1].y;
      pc[3].x = pb[2].x;
      pc[3].y = pb[2].y;
      {

         simple_brush b;

         b.create_solid(g, ARGB(84, 149, 149, 149));

         g.select(b);

         g.fill_polygon(pc, 4, ::draw2d::fill_mode_winding);

         simple_pen p;

         p.create_solid(g, ARGB(84, 123, 123, 123));

         g.select(p);

         g.draw_polygon(pc, 4);


      }





      {

         simple_pen p;

         p.create_solid(g, ARGB(184, 84, 84, 84));

         g.select(p);

         g.draw_polygon(pa, 4);

      }


   }


   void fontopus::draw_pestana(simple_graphics & g)
   {

      rect rectWindow;

      get_window_rect(rectWindow);

      g.set_alpha_mode(draw2d::alpha_mode_blend);

      int iCount = rectWindow.height();
      simple_pen p;
      for (int i = 0; i < iCount; i += 2)
      {
         double dRate = (double)i / (double)iCount;
         dRate = 1.0 - dRate;
         byte a1 = brate(1.0 - dRate, 23, 84);
         byte r1 = brate(dRate, 23, 127);
         byte g1 = brate(dRate, 23, 127);
         byte b1 = brate(dRate, 23, 127);
         p.create_solid(g, ARGB(a1, r1, g1, b1));
         g.draw_line(rectWindow.left, i, rectWindow.right, i, p);

      }


   }









   fontopus::fontopus() :
      m_login(0, 0),
      m_eventReady(NULL)
   {
      m_eschema = schema_normal;
      m_login.set_parent(this);
      m_login.m_pstyle = this;
      m_login.m_pcallback = this;
      m_bLButtonDown = false;
      m_w = 840;
      m_h = 284;
      m_hwnd = NULL;

      m_eresult = ::spa_login::result_fail;
      m_bVisible = false;
   }

   fontopus::~fontopus()
   {
   }

   string fontopus::show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strRequestingServer)
   {
      m_rectDesktop = *lprect;

      // TODO: Place code here.
      MESSAGE msg;

      m_strTitle = "fontopus Auth Windows";
      m_strWindowClass = "fontopus Auth Windows";

//      m_hinstance = ::GetModuleHandle(NULL);

      // Perform application initialization:
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
   BOOL fontopus::prepare_window(HINSTANCE hInstance, int nCmdShow)
   {

      rect rectDesktop = m_rectDesktop;

      rect rectFontopus;

      int w = m_w + 184;
      int h = m_h + 284;

      rectFontopus.left = rectDesktop.left + (width(rectDesktop) - w) / 2;
      rectFontopus.top = rectDesktop.top + (height(rectDesktop) - h) / 3;
      rectFontopus.right = rectFontopus.left + w;
      rectFontopus.bottom = rectFontopus.top + h;


      m_pt.x = rectFontopus.left;
      m_pt.y = rectFontopus.top;
      m_rect.left = m_pt.x;
      m_rect.top = m_pt.y;
      m_size.cx = rectFontopus.width();
      m_size.cy = rectFontopus.height();



      m_login.m_rect.left = (w - m_w) / 2;
      m_login.m_rect.top = (h - m_h) / 2;
      m_login.m_rect.right = m_w;
      m_login.m_rect.bottom = m_h;

      m_login.defer_translate(this);


      m_login.layout();


      set_focus(&m_login.m_editUser);


      m_bVisible = true;

      //UpdateWindow(hWnd);

      //::SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE);


      return TRUE;

   }





   bool fontopus::on_lbutton_down(int32_t x, int32_t y)
   {

      //::ClientToScreen(m_hwnd, &m_ptLButtonDown);

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

   bool fontopus::on_lbutton_up(int32_t x, int32_t y)
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
      DestroyWindow(m_hwnd);
      }
      */

      /*      {
      rect rectWindow;
      m_login.get_window_rect(&rectWindow);
      POINT ptCursor;
      ::GetCursorPos(&ptCursor);
      if (!rectWindow.contains(ptCursor))
      DestroyWindow(hWnd);
      }*/

      return true;


   }

   bool fontopus::on_mouse_move(int32_t x, int32_t y)
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
//            SetWindowPos(m_hwnd, NULL, m_pt.x, m_pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            m_bDrag = false;
         }
         return true;
      }

      if (m_login.on_mouse_move(x - m_login.m_rect.left, y - m_login.m_rect.top))
         return true;

      return true;

   }

   bool fontopus::on_windows_key_down(WPARAM wparam, LPARAM lparam)
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

   bool fontopus::on_windows_key_up(WPARAM wparam, LPARAM lparam)
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
      */
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



   void fontopus::get_window_rect(RECT * prect)
   {
      prect->left = m_pt.x;
      prect->top= m_pt.y;
      prect->right = m_pt.x + m_size.cx;
      prect->bottom = m_pt.y + m_size.cy;
   }
   void fontopus::get_client_rect(RECT * prect)
   {

      prect->left = 0;
      prect->top = 0;
      prect->right = m_size.cx;
      prect->bottom = m_size.cy;

   }

   void fontopus::draw_dark_glass(simple_graphics & g)
   {

      rect rectWindow;

      get_window_rect(rectWindow);


      g.fill_solid_rect(rectWindow, ARGB(84, 127, 127, 127));

   }


   void fontopus::draw(simple_graphics & g)
   {

      //draw_pestana(g);

      draw_auth_box(g);

      simple_ui::draw(g);

   }




   bool fontopus::on_action(const char * pszId)
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


   void fontopus::login_result(::spa_login::e_result eresult)
   {

      m_eresult = eresult;

   }


   void on_lbutton_up(int32_t x, int32_t y)
   {
      x -= ::fontopus::fontopus::s_fontopus.m_rect.left;
      y -= ::fontopus::fontopus::s_fontopus.m_rect.top;
      fontopus::s_fontopus.on_lbutton_up(x, y);
   }

   void on_lbutton_down(int32_t x, int32_t y)
   {
      x -= ::fontopus::fontopus::s_fontopus.m_rect.left;
      y -= ::fontopus::fontopus::s_fontopus.m_rect.top;
      fontopus::s_fontopus.on_lbutton_down(x, y);
   }

   void on_mouse_move(int32_t x, int32_t y)
   {
      x -= ::fontopus::fontopus::s_fontopus.m_rect.left;
      y -= ::fontopus::fontopus::s_fontopus.m_rect.top;
      fontopus::s_fontopus.on_mouse_move(x, y);
   }

   void on_char(int32_t iKey, const string & strChar)
   {
      fontopus::s_fontopus.on_char(iKey, strChar);
   }

   fontopus fontopus::s_fontopus;

   string CLASS_DECL_BOOT show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer)
   {

      return ::fontopus::fontopus::s_fontopus.show_auth_window(lprect, strUsername, strSessId, strServerId, strLoginUrl, strFontopusServer);

   }


   bool get_visible()
   {
      return ::fontopus::fontopus::s_fontopus.m_bVisible;
   }


   void draw(ID2D1DeviceContext * pctx)
   {

      simple_graphics g;

      g.m_pdc = pctx;

      g.set_offset(::fontopus::fontopus::s_fontopus.m_rect.left, ::fontopus::fontopus::s_fontopus.m_rect.top);

      ::fontopus::fontopus::s_fontopus.draw(g);

      g.m_pdc = NULL;

   }

} // namespace fontopus


