#pragma once


namespace ca2
{


   namespace fontopus
   {


      class CLASS_DECL_ca2 validate :
         virtual public ::fontopus::validate,
         virtual public ::user::tab_callback
      {
      public:


         int32_t                                       m_iView;
         ::userbase::single_document_template *    m_ptemplatePane;
         form_document *                           m_pdoc;
         ::userex::pane_tab_view *                 m_ptabview;
         form_document *                           m_pdocAuth;
         form_document *                           m_pdocMessage;
         form_view *                               m_pviewAuth;
         ::ca8::network_configuration              m_netcfg;
         ::ca8::keyboard_layout *                  m_pkeyboardlayout;
         void *                                    m_pvOldWindow;
         

         validate(::ca::application * papp, const char * pszForm, bool bVotagusAuth = false, bool bInteractive = true);
         virtual ~validate();


         virtual void get_mod(stringa & straHash, stringa & straSource);
         virtual string calc_mod_hash();
         virtual string calc_key_hash();
         virtual string calc_ca2_hash();
         // return hash and check if hash is valid
         virtual bool check_ca2_hash();


         virtual void on_login_thread_response(::fontopus::e_result iAuth, const char * pszResponse);

         virtual void close_all();
         virtual void show_and_request_auth();
         virtual void ensure_main_document();
         virtual void display_main_frame();
         virtual void page1(const stringa & straMatter = stringa());
         virtual void pageMessage(const stringa & stra, gen::property_set & set);

         //virtual ::fontopus::user * get_user(const char * pszHost = NULL, const char * pszSessid = NULL);
         virtual auth * get_auth();
         //virtual bool get_license(const char * pszId);

         virtual void authentication_failed(::fontopus::e_result iAuth, const char * pszResponse);
         virtual void authentication_succeeded();

         virtual void on_create_view(::user::view_creator_data * pcreatordata);

         virtual void on_show_view();

      
         virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);


      };


   } // namespace ca8


} // namespace ca2


