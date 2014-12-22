#pragma once


namespace os
{


   class CLASS_DECL_AURA simple_ui :
      virtual public ::simple_ui::interaction
   {
   public:


      string                     m_strTitle;
      string                     m_strWindowClass;

      int                        m_w;
      int                        m_h;
      SIZE                       m_size;
      POINT                      m_pt;
      bool                       m_bLButtonDown;
      POINT                      m_ptLButtonDown;
      POINT                      m_ptLButtonDownPos;

      bool                       m_bShiftKey;

      oswindow                   m_window;
      bool                       m_bDrag;
      manual_reset_event         m_eventReady;


      rect                       m_rectDesktop;

      bool                       m_bNoDecorations;

      point                      m_ptCursor;


      simple_ui(sp(::aura::application) papp);
      virtual ~simple_ui();



      virtual void get_cursor_pos(POINT * ppt);

      //void draw(ID2D1DeviceContext * pctx);



      //virtual string interactive_auth(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);


      virtual bool create_window(LPCRECT lpcrect);

      virtual bool prepare_window(LPCRECT lpcrect);


      virtual bool show_window(bool bShow = true);


      virtual bool destroy_window();

      virtual bool run_loop();


      virtual void GetWindowRect(RECT * prect);
      virtual void get_client_rect(RECT * prect);


      /*
      virtual bool on_lbutton_up(int32_t x, int32_t y);
      virtual bool on_lbutton_down(int32_t x, int32_t y);
      virtual bool on_mouse_move(int32_t x, int32_t y);
      virtual bool on_char(int32_t iKey, const string & strChar);
      */

      //virtual bool on_windows_key_down(WPARAM wparam, LPARAM lparam);
      //virtual bool on_windows_key_up(WPARAM wparam, LPARAM lparam);


      virtual bool set_window_pos(int x, int y, int cx, int cy, bool bShow);
      virtual bool move_window(int x, int y);

      void viewport_client_to_screen(POINT * ppt);
      void viewport_screen_to_client(POINT * ppt);

      void client_to_screen(POINT * ppt);
      void screen_to_client(POINT * ppt);

      void client_to_screen(RECT * prect);
      void screen_to_client(RECT * prect);

      void get_window_rect(RECT * prect);

      virtual void set_capture();
      virtual void release_capture();


   };

  


} // namespace fontopus






