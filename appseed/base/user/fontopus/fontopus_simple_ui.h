#pragma once



namespace fontopus
{


   class simple_ui :
      virtual public ::os::simple_ui,
      virtual public ::simple_ui::style,
      virtual public login::callback
   {
   public:

      login::e_result            m_eresult;


      login                      m_login;
      bool                       m_bLButtonDown;
      POINT                      m_ptLButtonDown;
      POINT                      m_ptLButtonDownPos;

      bool                       m_bDrag;


      simple_ui(sp(base_application) papp);
      virtual ~simple_ui();


      virtual string show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);

      virtual BOOL prepare_window(HINSTANCE hInstance, int nCmdShow);


      virtual void draw_dark_glass(::draw2d::graphics * pgraphics);
      virtual void draw_pestana(::draw2d::graphics * pgraphics);
      virtual void draw_auth_box(::draw2d::graphics * pgraphics);


      virtual void draw_this(::draw2d::graphics * pgraphics);


      virtual void draw_fuzzy_color_spread(::draw2d::graphics * pgraphics);

      virtual bool on_lbutton_down(int32_t x, int32_t y);
      virtual bool on_lbutton_up(int32_t x, int32_t y);
      virtual bool on_mouse_move(int32_t x, int32_t y);


      virtual bool on_action(const char * pszId);

      virtual void login_result(login::e_result eresult);

   };




} // namespace fontopus