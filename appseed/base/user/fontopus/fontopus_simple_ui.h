#pragma once



namespace fontopus
{


   class simple_ui :
      virtual public ::os::simple_ui,
      virtual public ::simple_ui::style,
      virtual public login::callback
   {
   public:


      login                      m_login;
      bool                       m_bLButtonDown;
      POINT                      m_ptLButtonDown;
      POINT                      m_ptLButtonDownPos;

      bool                       m_bDrag;


      simple_ui(sp(base_application) papp);
      virtual ~simple_ui();


      virtual string interactive_auth(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer);

      virtual string get_cred(LPRECT lprect, string & strUsername, string & strPassword, string strToken, string strTitle);

      virtual string fontopus(LPRECT lprect);


      virtual void get_window_rect(LPRECT lprect);




      virtual bool on_char(int iKeyCode, const string & strChar);
      virtual bool on_lbutton_down(int32_t x, int32_t y);
      virtual bool on_lbutton_up(int32_t x, int32_t y);
      virtual bool on_mouse_move(int32_t x, int32_t y);

      virtual bool on_move(int32_t x, int32_t y);
      virtual bool on_size(int32_t cx, int32_t cy);


   };




} // namespace fontopus
