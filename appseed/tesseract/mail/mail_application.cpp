#include "StdAfx.h"


namespace tesseract
{

   namespace mail
   {

   application::application()
   {
      m_strAppName      = "mail";
      m_pmaillist       = NULL;
      m_pmaillist       = NULL;
      m_pmainview       = NULL;
      m_prightpaneview  = NULL;
      m_prightview      = NULL;
      m_ptemplate_html  = NULL;
   }

   application::~application()
   {
   }

   void application::InitializeMail()
   {

      if(m_ptemplate_html == NULL)
      {
         System.factory().creatable_small < mail::document > ();
         System.factory().creatable_small < mail::frame > ();
         System.factory().creatable_small < mail::view > ();
         System.factory().creatable_small < mail::main_view > ();
         System.factory().creatable_small < mail::right_view > ();
         System.factory().creatable_small < mail::list > ();
         System.factory().creatable_small < mail::child_frame > ();
         System.factory().creatable_small < mail::right_pane_view > ();
         System.factory().creatable_small < mail::tree > ();


         ::userbase::single_document_template* pDocTemplate;
         pDocTemplate = new ::userbase::single_document_template(
            this,
            "mail/frame",
            ::ca::get_type_info < mail::document > (),
            ::ca::get_type_info < mail::frame > (),       // main SDI frame ::ca::window
            ::ca::get_type_info < mail::main_view > ());
         userbase::application::add_document_template(pDocTemplate);
         m_ptemplate_html = pDocTemplate;
      }

      
      m_accounta.remove_all();

      string str;
      str = Application.http().get("https://fontopus.com/ca2api/account/associated_email");

      stringa straEmail;
      straEmail.explode(",", str);

      string strUrl;

      for(int i = 0; i < straEmail.get_count(); i++)
      {
         
         string strEmail = straEmail[i];

         ::mail::account * pacc = new ::mail::account(get_app());
         strUrl = System.url().set_key("https://fontopus.com/get_user_string", "key", "mail_server");
         System.url().set(strUrl, "user" , strEmail);
         pacc->m_strServer = Application.http().get(strUrl);
         string strMailDb = Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strEmail,"mail.db");
         pacc->m_strMailDb = strMailDb;
         strUrl = System.url().set_key("https://fontopus.com/get_user_string", "key", "mail_login");
         System.url().set(strUrl, "user" , strEmail);
         pacc->m_strLogin = Application.http().get(strUrl);
         pacc->m_id = gen::str::itoa(i + 1);
         pacc->m_pop3.set_app(get_app());
         pacc->m_pop3.m_paccount = pacc;
         pacc->m_strEmail = strEmail;
         m_accounta.add(pacc);

      }

   }

   void application::TimerStep()
   {
      for(int i = 0; i < m_accounta.get_size(); i++)
      {
         if((m_accounta[i].m_dwLastCheck + m_accounta[i].m_dwCheckTime) > ::GetTickCount())
         {
         }
      }
   }

   bool application::initialize_instance()
   {

      if(!cube2::application::initialize_instance())
         return FALSE;


      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";

      InitializeMail();

      return TRUE;
   }

   BOOL application::exit_instance()
   {
      try
      {
         ::cube2::application::exit_instance();
      }
      catch(...)
      {
      }
      return 0;
   }

   void application::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }

   void application::update_pop3_mail_lists()
   {
      if(m_pmailtree != NULL)
      {
         m_pmailtree->update_list();
      }
      if(m_pmaillist != NULL)
      {
         m_pmaillist->_001OnUpdateItemCount();
      }
   }

   } // namespace mail


} // namespace tesseract


