#pragma once

namespace fontopus
{

   class CLASS_DECL_ca login_thread_callback
   {
   public:
      virtual void on_login_thread_response(int iAuth, const char * pszResponse);
      virtual string calc_mod_hash();
      virtual string calc_key_hash();
      virtual string calc_ca2_hash();
   };

   class CLASS_DECL_ca http_execute
   {
   public:
      string                  m_strUrl;
      gen::property_set       m_propertysetPost;
      gen::property_set       m_propertysetHeaders;
      string                  m_strResponse;
   };

   class CLASS_DECL_ca http_execute_array : 
      public array_ptr_alloc < http_execute, http_execute & >
   {
   };


   class CLASS_DECL_ca login_thread : public simple_thread
   {
   public:

      user *                     m_puser;

      string                     m_strUsername;
      string                     m_strPassword;
      string                     m_strPasshash;

      string                     m_strModHash;
      string                     m_strKeyHash;
      string                     m_strCa2Hash;
      
      
      string                     m_strValidUntil;

      string                     m_strSalt;

      string                     m_strLicense;
      http_execute_array         m_httpexecutea;
      bool                       m_bOk;
      login_thread_callback *    m_pcallback;


      login_thread(::ca::application * papp);
      virtual ~login_thread();

      virtual BOOL run();
      virtual string Login(ca4::http::e_status * pestatus);
      virtual string NetLogin(ca4::http::e_status * pestatus);
      void execute();
   };

   class CLASS_DECL_ca validate :
      virtual public ::user::form_callback,
      virtual public ::user::create_view,
      virtual public ::user::tab_callback,
      virtual public login_thread_callback
   {
   public:

      class CLASS_DECL_ca auth
      {
      public:
         string m_strUsername;
         string m_strPassword;
      };


      class CLASS_DECL_ca license
      {
      public:
         string m_strUsername;
         id m_id;
      };



      ::fontopus::user *                         m_puser;
      login_thread                              m_loginthread;
      int                                       m_iView;
      ::userbase::single_document_template *    m_ptemplatePane;
      form_document *                           m_pdoc;
      ::userex::pane_tab_view *                   m_ptabview;
      form_document *                           m_pdocAuth;
      form_document *                           m_pdocMessage;
      form_view *                               m_pviewAuth;
      bool                                      m_bVotagusAuth;
      auth *                                    m_pauth;
      string                                    m_strForm;
      string                                    m_strLicense;
      bool                                      m_bLicense;
      ::ca8::network_configuration              m_netcfg;
      ::ca8::keyboard_layout *                  m_pkeyboardlayout;
      bool                                      m_bInteractive;

      validate(::ca::application * papp, const char * pszForm, bool bVotagusAuth = false);
      virtual ~validate();

#if !core_level_1
      using ::user::tab_callback::on_show_view;
#endif

      virtual void get_mod(stringa & straHash, stringa & straSource);
      virtual string calc_mod_hash();
      virtual string calc_key_hash();
      virtual string calc_ca2_hash();
      // return hash and check if hash is valid
      virtual bool check_ca2_hash();


      void on_login_thread_response(int iAuth, const char * pszResponse);


      void ensure_main_document();
      void display_main_frame();
      void page1();
      void pageMessage(const char * pszMatter, gen::property_set & set);

      ::fontopus::user * get_user();
      auth * get_auth();
      bool get_license(const char * pszId, bool bInteractive = true);

      void authentication_failed(int iAuth, const char * pszResponse);
      void authentication_succeeded();

      void on_create_view(view_data * pviewdata);
      virtual void on_show_view();

      
      virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);
   };


} // namespace ca8
