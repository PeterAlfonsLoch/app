#pragma once


namespace fontopus
{


   class CLASS_DECL_BASE login :
      virtual public ::simple_ui::interaction
   {
   public:


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


      login(sp(::aura::application) papp, int left, int top, const string & strRequestUrl);
      virtual ~login();


      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual bool on_action(const char * pszId);

      void initialize();

      void defer_translate(const string & strUser, const string & strPass, const string & strOpen);

      virtual void layout();

      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace fontopus




