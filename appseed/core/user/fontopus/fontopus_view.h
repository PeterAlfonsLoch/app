#pragma once


namespace fontopus
{


   class CLASS_DECL_CORE view :
      virtual public ::user::impact
   {
   public:

      mutex                         m_mutexResponse;
      manual_reset_event            m_evSubmit;
      string                        m_strResponse;
      ::simple_ui::label *          m_plabelUser;
      ::simple_ui::edit_box *       m_peditUser;
      ::simple_ui::label *          m_plabelPassword;
      ::simple_ui::password *       m_ppassword;
      ::simple_ui::tap *            m_ptap;
      ::simple_ui::tap *            m_ptapClose;
      string                        m_strRequestUrl;

      string                        m_strUsername;
      string                        m_strPassword;

      bool                          m_bSelfLayout;
      double                        m_dRateX;
      double                        m_dRateY;

      bool                          m_bCred;
      string                        m_strCred;

      visual::icon *                m_picon95; // the best size to fit current ca2 icon (as of 2014)


      view(::aura::application * papp);
      virtual ~view();


      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual bool on_action(const char * pszId);

      void initialize();

      void defer_translate(const string & strUser, const string & strPass, const string & strOpen);

      virtual void layout();

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void _000OnDraw(::draw2d::graphics * pgraphics);

      virtual void _001DrawChildren(::draw2d::graphics *pdc);

      string get_cred(const string & strRequestUrl, const RECT & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive);

   };


} // namespace fontopus




