#pragma once


namespace fontopus
{


   class CLASS_DECL_BASE login :
      virtual public ::simple_ui::interaction
   {
   public:


      ::simple_ui::label            m_labelUser;
      ::simple_ui::edit_box         m_editUser;
      ::simple_ui::label            m_labelPassword;
      ::simple_ui::password         m_password;
      ::simple_ui::tap              m_tap;

      string                        m_strUsername;
      string                        m_strPassword;

      bool                          m_bSelfLayout;
      double                        m_dRateX;
      double                        m_dRateY;

      bool                          m_bCred;
      string                        m_strCred;

      visual::icon *                m_picon95; // the best size to fit current ca2 icon (as of 2014)


      login(sp(::base::application) papp, int left, int top);
      virtual ~login();


      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual bool on_action(const char * pszId);

      void initialize();

      void defer_translate(::simple_ui::style * pstyle);

      virtual void layout();

      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace fontopus




