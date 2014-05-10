#pragma once



namespace fontopus
{


   class simple_ui :
      virtual public ::user::interaction,
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


      //virtual void GetWindowRect(LPRECT lprect);

      void install_message_handling(::message::dispatch * pdispatch);


      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      
      virtual void layout();


   };




} // namespace fontopus
