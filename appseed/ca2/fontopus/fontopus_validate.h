#pragma once


namespace ca2
{


   namespace fontopus
   {


      class CLASS_DECL_ca2 validate :
         virtual public ::user::form_callback,
         virtual public ::user::view_creator,
         virtual public ::user::tab_callback,
         virtual public ::fontopus::login_thread_callback
      {
      public:


         class CLASS_DECL_ca2 auth
         {
         public:
            string m_strUsername;
            string m_strPassword;
         };


         class CLASS_DECL_ca2 license
         {
         public:
            string m_strUsername;
            id m_id;
         };



         ::fontopus::user *                        m_puser;
         ::fontopus::login_thread                  m_loginthread;
         int                                       m_iView;
         ::userbase::single_document_template *    m_ptemplatePane;
         form_document *                           m_pdoc;
         ::userex::pane_tab_view *                 m_ptabview;
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


         validate(::ca::application * papp, const char * pszForm, bool bVotagusAuth = false, bool bInteractive = true);
         virtual ~validate();


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

         ::fontopus::user * get_user(const char * pszHost = NULL, const char * pszSessid = NULL);
         auth * get_auth();
         bool get_license(const char * pszId);

         void authentication_failed(int iAuth, const char * pszResponse);
         void authentication_succeeded();

         void on_create_view(::user::view_creator_data * pcreatordata);

         virtual void on_show_view();

      
         virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);


      };


   } // namespace ca8


} // namespace ca2


