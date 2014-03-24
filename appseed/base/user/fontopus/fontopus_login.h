#pragma once


namespace fontopus
{


   class CLASS_DECL_BASE login :
      virtual public ::simple_ui::interaction,
      virtual public thread
   {
   public:



      enum e_result
      {

         result_ok,
         result_wrong_password,
         result_fail,
         result_registration_deferred

      };

      class CLASS_DECL_BASE callback
      {
      public:

         virtual void login_result(e_result eresult);

      };


      login::e_result            m_eresult;


      ::simple_ui::label            m_labelUser;
      ::simple_ui::edit_box         m_editUser;
      ::simple_ui::label            m_labelPassword;
      ::simple_ui::password         m_password;
      ::simple_ui::tap              m_tap;

      string                        m_strPasshash;

      callback *                    m_pcallback;
      string                        m_strKeyHash;
      string                        m_strSessId;
      string                        m_strSecureId;
      string                        m_strLoginUrl;
      string                        m_strFontopusServer;
      string                        m_strRequestingServer;

      bool                          m_bSelfLayout;
      double                        m_dRate;

      bool                          m_bCred;
      string                        m_strCred;

      visual::icon *                m_picon84;



      login(sp(base_application) papp, int left, int top);
      virtual ~login();


      virtual void draw_this(::draw2d::graphics * pgraphics);

      virtual bool on_action(const char * pszId);

      void initialize();

      void defer_translate(::simple_ui::style * pstyle);

      void start_login();

      static uint32_t thread_proc_login(void * lpParam);

      e_result perform_login();

      string calc_key_hash();


      virtual void login_result(e_result eresult);

      virtual void authentication_succeeded();

      virtual void authentication_failed();

      virtual void layout();

      virtual ::fontopus::login::e_result process_response(string strResponse);

      virtual int32_t run();


   };


} // namespace fontopus




