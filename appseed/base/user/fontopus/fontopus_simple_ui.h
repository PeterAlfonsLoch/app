#pragma once



namespace fontopus
{


   class simple_ui :
      virtual public ::os::simple_ui,
      virtual public ::spa::style,
      virtual public ::spa::login::callback
   {
   public:

      static simple_ui      s_fontopus;

      ::spa::login::e_result     m_eresult;


      ::spa::login               m_login;
      POINT                      m_pt;
      bool                       m_bLButtonDown;
      POINT                      m_ptLButtonDown;
      POINT                      m_ptLButtonDownPos;

      HWND                       m_hwnd;
      bool                       m_bDrag;
      rect                       m_rectDesktop;


      simple_ui(sp(base_application) papp);

      virtual ~simple_ui();

      virtual string show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);

      //virtual ATOM register_window_class(HINSTANCE hInstance);

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




} // namespace fontopus