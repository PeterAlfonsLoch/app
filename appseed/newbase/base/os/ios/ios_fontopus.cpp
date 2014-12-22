#include "framework.h"
#include "ios_window.h"


#define MAX_LOADSTRING 100

/*
namespace fontopus
{


   class fontopus :
      virtual public ::spa::style,
      virtual public ::simple_ui,
      virtual public ::spa_login::callback,
      virtual public ::boot_window
   {
   public:

      static fontopus s_fontopus;

      spa_login::e_result  m_eresult;

      string               m_strTitle;
      string               m_strWindowClass;

      int                  m_w;
      int                  m_h;
      spa_login            m_login;
      simple_graphics      m_graphics;
      simple_bitmap        m_bitmap;
      SIZE                 m_size;
      POINT                m_pt;
      bool                 m_bLButtonDown;
      POINT                m_ptLButtonDown;
      POINT                m_ptLButtonDownPos;
      
      oswindow             m_oswindow;

      bool                 m_bShiftKey;

      bool                 m_bDrag;
      rect                 m_rectDesktop;

      manual_reset_event   m_eventReady;
      
      
      bool                 m_bVisible;
      

      fontopus();

      virtual ~fontopus();

      virtual string show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);

      virtual bool prepare_window(bool bShow);

      virtual void client_to_screen(POINT * ppt);

      virtual void screen_to_client(POINT * ppt);

      virtual void get_window_rect(RECT * prect);

      virtual void get_client_rect(RECT * prect);

      virtual void draw_dark_glass(simple_graphics & g);
      virtual void draw_pestana(simple_graphics &g);
      virtual void draw_auth_box(simple_graphics &g);


      virtual void draw(simple_graphics & g);


      virtual void draw_fuzzy_color_spread(simple_graphics & g);

      virtual bool on_lbutton_down(int32_t x, int32_t y);
      virtual bool on_lbutton_up(int32_t x, int32_t y);
      virtual bool on_mouse_move(int32_t x, int32_t y);


//      virtual bool on_windows_key_down(WPARAM wparam, LPARAM lparam);
  //    virtual bool on_windows_key_up(WPARAM wparam, LPARAM lparam);

    //  virtual void on_windows_gdi_draw_framebuffer();

      //virtual bool on_windows_move(int32_t x, int32_t y);
      //virtual bool on_windows_size(int32_t cx, int32_t cy);

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

         g.draw_polygon(pb, 4, ::draw2d::fill_mode_winding);


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

         g.draw_polygon(pc, 4, ::draw2d::fill_mode_winding);


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

         g.draw_polygon(pc, 4, ::draw2d::fill_mode_winding);


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

         g.draw_polygon(pc, 4, ::draw2d::fill_mode_winding);


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

         g.draw_polygon(pc, 4, ::draw2d::fill_mode_winding);


      }





      {

         simple_pen p;

         p.create_solid(g, ARGB(184, 84, 84, 84));

         g.select(p);

         g.draw_polygon(pa, 4, ::draw2d::fill_mode_winding);

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

      m_eresult = ::spa_login::result_fail;
      m_oswindow = NULL;
      
      m_bVisible = false;
      
   }

   fontopus::~fontopus()
   {
   }

   string fontopus::show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strRequestingServer)
   {

      if (lprect == NULL)
      {
         m_rectDesktop.left = 0;
         m_rectDesktop.top = 0;
         m_rectDesktop.right = 800;
         m_rectDesktop.bottom = 600;

//         ::GetWindowRect(::GetDesktopWindow(), &m_rectDesktop);

      }
      else
      {

         m_rectDesktop = *lprect;

      }

      // TODO: Place code here.

      m_strTitle = "fontopus Auth Windows";
      m_strWindowClass = "fontopus Auth Windows";


      // Perform application initialization:
      if (!prepare_window(true))
      {
         return "";
      }

      m_login.m_strRequestingServer = strRequestingServer;
      
      
      
      
      
      m_eventReady.wait();
      

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
   bool fontopus::prepare_window(bool bShow)
   {

      rect & rectDesktop = m_rectDesktop;

      CGRect rectFontopus;

      int w = m_w + 184;
      int h = m_h + 284;

      rectFontopus.origin.x = rectDesktop.left + (width(rectDesktop) - w) / 2;
      rectFontopus.origin.y = rectDesktop.top + (height(rectDesktop) - h) / 3;
      rectFontopus.size.width = w;
      rectFontopus.size.height = h;


      m_login.m_rect.left = (w - m_w) / 2;
      m_login.m_rect.top = (h - m_h) / 2;
      m_login.m_rect.right = m_w;
      m_login.m_rect.bottom = m_h;

      m_login.defer_translate(this);
      
      m_oswindow = oswindow_get(new_boot_window(this, rectFontopus));
      


      if (!m_oswindow)
      {
         return FALSE;
      }

      m_login.layout();
      
//      SetTimer(m_oswindow, 123, 23, NULL);

      ShowWindow(m_oswindow, SW_SHOW);



      return TRUE;

   }

   void fontopus::boot_window_draw(CGContextRef pdc)
   {
      
      simple_graphics g;
      
      g.m_pdc = pdc;
      
      draw(g);
      
      g.m_pdc = NULL;
      
   }
   
   void fontopus::boot_window_mouse_down(double x, double y)
   {
      on_lbutton_down(x, y);
   }
   
   void fontopus::boot_window_mouse_up(double x, double y)
   {
      on_lbutton_up(x, y);
   }
   
   void fontopus::boot_window_mouse_moved(double x, double y)
   {
      on_mouse_move(x, y);
   }
   
   void fontopus::boot_window_mouse_dragged(double x, double y)
   {
      SetWindowPos(m_oswindow, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
   }
   
   bool fontopus::boot_window_key_down(::user::e_key ekey)
   {
      return true;
   }
   
   bool fontopus::boot_window_key_up(::user::e_key ekey)
   {
      return true;
   }
   



   void fontopus::client_to_screen(POINT * ppt)
   {
      ::ClientToScreen(m_oswindow, ppt);
   }

   void fontopus::screen_to_client(POINT * ppt)
   {
      ::ScreenToClient(m_oswindow, ppt);
   }

   bool fontopus::on_lbutton_down(int32_t x, int32_t y)
   {

      ::ClientToScreen(m_oswindow, &m_ptLButtonDown);

      if (m_login.on_lbutton_down(x, y))
         return true;

      m_bLButtonDown = true;
      m_bDrag = false;

      m_ptLButtonDownPos = m_pt;
      ::GetCursorPos(&m_ptLButtonDown);

      return true;
   }

   bool fontopus::on_lbutton_up(int32_t x, int32_t y)
   {

      m_bLButtonDown = false;

      if (m_login.on_lbutton_up(x, y))
         return true;

      /*
      rect rectLogin;

      m_login.get_window_rect(rectLogin);

      point pt(x, y);

      if (!rectLogin.contains(pt))
      {
      ReleaseCapture();
      DestroyWindow(m_oswindow);
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
/*
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
            SetWindowPos(m_oswindow, NULL, m_pt.x, m_pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            m_bDrag = false;
         }
         return true;
      }

      if (m_login.on_mouse_move(x, y))
         return true;

      return true;

   }


   void fontopus::get_window_rect(RECT * prect)
   {
      ::GetWindowRect(m_oswindow, prect);
   }
   void fontopus::get_client_rect(RECT * prect)
   {

      ::GetClientRect(m_oswindow, prect);

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


   void fontopus::draw_fuzzy_color_spread(simple_graphics & g)
   {

      rect rectWindow;

      get_window_rect(rectWindow);

      int i = 0;
      int j = 0;
      int iCount = rectWindow.width();
      int jCount = rectWindow.height();

      BYTE * p = (BYTE *) m_bitmap.m_pdata;

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



   bool fontopus::on_action(const char * pszId)
   {

      if (!strcmp(pszId, "submit"))
      {


         ::ShowWindow(m_oswindow, SW_HIDE);

         m_login.login_result(m_login.login());

         if (m_eresult == ::spa_login::result_fail)
         {
            ::ShowWindow(m_oswindow, SW_SHOW);
         }
         else
         {
            m_eventReady.set_event();
         }

         return true;

      }
      else if (!strcmp(pszId, "escape"))
      {
         m_eventReady.set_event();
      }

      return false;


   }


   void fontopus::login_result(::spa_login::e_result eresult)
   {

      m_eresult = eresult;

   }



   fontopus fontopus::s_fontopus;

   string CLASS_DECL_BOOT show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer)
   {

      return ::fontopus::fontopus::s_fontopus.show_auth_window(lprect, strUsername, strSessId, strServerId, strLoginUrl, strFontopusServer);

   }




} // namespace fontopus


*/

