#include "framework.h"


namespace fontopus
{


   application::application()
   {
      m_puser              = NULL;
      m_bIsCreatingUser    = false;
   }

   void application::construct()
   {
      m_strAppName         = "fontopus";
      m_strBaseSupportId   = "votagus_ca2_fontopus";
      m_strInstallToken    = "fontopus";    
   }


   application::~application()
   {
   }


   bool application::initialize_instance()
   {

      if(!fs::application::initialize_instance())
         return false;

      return TRUE;
   }


   int application::exit_instance()
   {

      int iExitCode = 0;

      try
      {

         iExitCode = ::fs::application::exit_instance();

      }
      catch(...)
      {

         iExitCode = -1;

      }

      return iExitCode;

   }


   bool application::bergedge_start()
   {
      return false;
   }


   user * application::create_current_user()
   {
      gen::property_set set(get_app());
      if(m_puser == NULL)
      {
         int iRetry = 3;
         ::fontopus::user * puser = NULL;
         while(iRetry > 0)
         {
            puser = login(set);
            if(puser != NULL)
               break;
            //bool bOk = false;
            //string strSection;
            //strSection.Format("license_auth");
            //string strDir;
            //strDir = Application.dir().usersystemappdata(puser->m_strPathPrefix, strSection);
            //::DeleteFile(System.dir().path(strDir, "00001"));
            //::DeleteFile(System.dir().path(strDir, "00002"));
            iRetry--;
         }
         if(puser == NULL)
         {
            //System.simple_message_box(NULL, "<h1>You have not logged in!</h1><h2>Exiting</h2>");
            TRACE("<error>You have not logged in! Exiting!</error>");
            throw string("You have not logged in! Exiting!");
            return NULL;
         }
         m_puser = create_user(puser);
         System.userset().add(m_puser);

         if(m_puser != NULL && m_strAppName != "core_deepfish"
            && !gen::str::begins(m_strAppName, "core_deepfish_")
            && !is_serviceable())
         {

            on_user_login(m_puser);

         }



      }
      return m_puser;
   }

   user * application::login(gen::property_set & set)
   {
      /*::ca::application * papp;
      if(m_puiInitialPlaceHolderContainer != NULL)
      {
         papp = m_puiInitialPlaceHolderContainer->m_papp;
      }
      else if(System.m_puiInitialPlaceHolderContainer != NULL)
      {
         papp = System.m_puiInitialPlaceHolderContainer->m_papp;
      }
      else
      {
         papp = this;
      }*/
      //class validate authuser(papp, "system\\user\\authenticate.xhtml", true);

      user * puser = NULL;

      if(m_psession != NULL && m_psession->m_pbergedge != NULL)
      {
       
         puser = m_psession->m_pbergedgeInterface->login(set);

      }
      else
      {

         class validate authuser(this, "system\\user\\authenticate.xhtml", true);
         authuser.oprop("defer_registration") = "defer_registration";
         authuser.propset().merge(set);
         puser = authuser.get_user();

      }

      return puser;

   }

   bool application::get_auth(const char * psz, string & strUsername, string & strPassword)
   {
      /*::ca::application * papp;
      if(m_puiInitialPlaceHolderContainer != NULL)
      {
         papp = m_puiInitialPlaceHolderContainer->m_papp;
      }
      else if(System.m_puiInitialPlaceHolderContainer != NULL)
      {
         papp = System.m_puiInitialPlaceHolderContainer->m_papp;
      }
      else
      {
         papp = this;
      }*/
      //class validate authuser(papp, psz);
      class validate authuser(this, psz);
      validate::auth * pauth = authuser.get_auth();
      if(pauth == NULL)
         return false;
      else
      {
         strUsername = pauth->m_strUsername;
         strPassword = pauth->m_strPassword;
         delete pauth;
         return true;
      }
   }

   void application::logout()
   {
      if(m_puser != NULL)
      {
         try
         {
            System.file().del(Application.dir().usersystemappdata(Application.dir().default_os_user_path_prefix(), "license_auth", "00001.data"));
         }
         catch(...)
         {
         }
         try
         {
            System.file().del(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), AppUser(this).m_strLogin, "license_auth/00002.data"));
         }
         catch(...)
         {
         }
         delete m_puser;
      }
      m_puser = NULL;
   }



   user * application::allocate_user()
   {
      return new class user(this);
   }

   user * application::create_user(::fontopus::user * puser)
   {
      if(puser->m_strPathPrefix.is_empty())
      {
         puser->m_strPathPrefix = Application.dir().default_os_user_path_prefix();
      }
      puser->m_strPath = Application.dir().default_userfolder(puser->m_strPathPrefix, puser->m_strLogin);
      App(this).dir().mk(puser->m_strPath);
      puser->m_strDataPath = Application.dir().default_userdata(puser->m_strPathPrefix, puser->m_strLogin);
      App(this).dir().mk(puser->m_strDataPath);
      puser->m_strAppDataPath = Application.dir().default_userappdata(puser->m_strPathPrefix, puser->m_strLogin);
      App(this).dir().mk(puser->m_strAppDataPath);
      puser->create_ifs();
      return puser;
   }


   user * application::get_user()
   {
      if(m_puser == NULL)
      {
         if(m_bIsCreatingUser)
            return NULL;
         keeper < bool > keepCreatingUser(&m_bIsCreatingUser, true, false, true);
         m_puser = create_current_user();
         if(!m_puser->initialize())
         {
            delete m_puser;
            m_puser = NULL;
            return NULL;
         }
      }
      return m_puser;
   }

   void application::set_user(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void application::set_user(user * puser)
   {
      m_puser = puser;
   }

   bool application::check_license(const char * pszId, bool bInteractive)
   {

      ::ca::application * papp = get_app();
      class validate authuser(papp, "err\\user\\authentication\\not_licensed.xhtml", true, bInteractive);
      return authuser.get_license(pszId);

   }

   void application::on_user_login(user * puser)
   {
      UNREFERENCED_PARAMETER(puser);
   }

} // namespace fontopus


