#pragma once


//#include "user/user_form_callback.h"


namespace fontopus
{

   
   enum e_result
   {
      
      result_auth,
      result_registration_deferred,
      result_please_finish_registration,
      result_no_login,
      result_no_password,
      result_wrong_password_or_login,
      result_time_out,
      result_fail
         
   };
   

   class CLASS_DECL_BASE login_callback :
      virtual public ::object
   {
   public:
      
      
      virtual void on_login_response(e_result iAuth, const char * pszResponse);
      virtual string calc_mod_hash();
      virtual string calc_key_hash();
      virtual string calc_ca2_hash();
      virtual bool get_defer_registration();
      
      
   };


   class CLASS_DECL_BASE http_execute :
      virtual public element
   {
   public:
      
      
      string                  m_strUrl;
      property_set       m_propertysetPost;
      property_set       m_propertysetHeaders;
      string                  m_strResponse;
   };


   class CLASS_DECL_BASE http_execute_array :
      public spa(http_execute)
   {
   };


   class CLASS_DECL_BASE login_thread : public simple_thread
   {
   public:

      user *                     m_puser;

      string                     m_strFontopusServerAuthUrl;
      string                     m_strLoginUrl;
      string                     m_strRequestingServer;
      string                     m_strFontopusServer;
      string                     m_strUsername;
      string                     m_strPassword;
      string                     m_strPasshash;

      string                     m_strModHash;
      string                     m_strKeyHash;
      string                     m_strCa2Hash;

      stringa                    m_straRequestingServer;
      bool                       m_bFontopusServer;


      string                     m_strValidUntil;

      string                     m_strSalt;

      string                     m_strLicense;
      http_execute_array         m_httpexecutea;
      bool                       m_bOk;
      login_callback *           m_pcallback;





      login_thread(sp(::axis::application) papp);
      virtual ~login_thread();

      virtual int32_t run();
      virtual string Login(::http::e_status * pestatus);
      virtual string NetLogin(::http::e_status * pestatus);
      void execute();
   };


   class CLASS_DECL_BASE validate :
      virtual public login_callback
   {
   public:


      class CLASS_DECL_BASE auth
      {
      public:
         string m_strUsername;
         string m_strPassword;
      };


      class CLASS_DECL_BASE license
      {
      public:
         string m_strUsername;
         id m_id;
      };



      ::fontopus::user *                        m_puser;
      login_thread                              m_loginthread;
      int32_t                                       m_iView;
      bool                                      m_bAuth;
      auth *                                    m_pauth;
      string                                    m_strForm;
      string                                    m_strLicense;
      bool                                      m_bLicense;
      bool                                      m_bInteractive;
      bool                                      m_bDeferRegistration;
//      ::usernet::network_configuration              m_netcfg;
  //    sp(::userex::keyboard_layout)                  m_pkeyboardlayout;
      void *                                    m_pvOldWindow;


      validate(sp(::axis::application) papp, const char * pszForm, bool bAuth = false, bool bInteractive = true);
      virtual ~validate();


      virtual void get_mod(stringa & straHash, stringa & straSource);
      virtual string calc_mod_hash();
      virtual string calc_key_hash();
      virtual string calc_ca2_hash();
      // return hash and check if hash is valid
      virtual bool check_ca2_hash();


      virtual void on_login_response(e_result iAuth, const char * pszResponse);


      virtual ::fontopus::user * get_user(const char * pszHost = NULL, const char * pszSessid = NULL);
      virtual auth * get_auth();
      virtual bool get_license(const char * pszId);

      virtual void authentication_failed(e_result iAuth, const char * pszResponse);
      virtual void authentication_succeeded();

      virtual void save_authentication_info();

      virtual bool get_defer_registration();


      virtual void pageMessage(stringa straMessage,::property_set set);


   };


} // namespace user





