#include "StdAfx.h"

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
         System.factory().creatable_small < mail_frame > ();
         System.factory().creatable_small < mail::view > ();
         System.factory().creatable_small < mail::main_view > ();
         System.factory().creatable_small < mail::right_view > ();
         System.factory().creatable_small < mail::tree_interface > ();
         System.factory().creatable_small < mail::list > ();
         System.factory().creatable_small < mail::child_frame > ();
         System.factory().creatable_small < mail::right_pane_view > ();
         System.factory().creatable_small < mail::tree > ();


         ::userbase::single_document_template* pDocTemplate;
         pDocTemplate = new ::userbase::single_document_template(
            this,
            "mail/frame",
            &typeid(mail::document),
            &typeid(mail_frame),       // main SDI frame ::ca::window
            &typeid(mail::main_view));
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

         mail::account * pacc = new mail::account(get_app());
         strUrl = System.url().set("https://fontopus.com/get_user_string", "key", "mail_server");
         strUrl = System.url().set(strUrl, "user" , strEmail);
         pacc->m_strServer = Application.http().get(strUrl);
         string strMailDb = Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strEmail,"mail.db");
         pacc->m_strMailDb = strMailDb;
         strUrl = System.url().set("https://fontopus.com/get_user_string", "key", "mail_login");
         strUrl = System.url().set(strUrl, "user" , strEmail);
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

      if(!ca84::application::initialize_instance())
         return FALSE;


      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";

      InitializeMail();


      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);

      SetRegistryKey("ca2core");


      return TRUE;
   }

   BOOL application::exit_instance()
   {
      try
      {
         ::ca84::application::exit_instance();
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

   void application::OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_ptemplate_html->open_document_file(itema[0].m_strPath);
   }

} // namespace mail
