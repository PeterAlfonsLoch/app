#include "framework.h"


namespace fontopus
{


   fontopus::fontopus()
   {
      m_puser              = NULL;
      m_bIsCreatingUser    = false;
   }


   fontopus::~fontopus()
   {
   }


   bool fontopus::initialize_instance()
   {

      return true;

   }


   int32_t fontopus::exit_instance()
   {

      int32_t iExitCode = 0;

      return iExitCode;

   }


   user * fontopus::create_current_user()
   {
      gen::property_set set(get_app());
      if(m_puser == NULL)
      {
         int32_t iRetry = 3;
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

         if(m_puser != NULL && m_papp->m_pappThis->m_strAppId != "app-core/deepfish"
            && !gen::str::begins(m_papp->m_pappThis->m_strAppName, "app-core/deepfish_")
            && !m_papp->m_pappThis->is_serviceable())
         {

            on_user_login(m_puser);

         }



      }
      return m_puser;
   }

   user * fontopus::login(gen::property_set & set)
   {
      /*::ca::fontopus * papp;
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

      if(m_papp->m_pappThis->m_psession != NULL && m_papp->m_pappThis->m_psession->m_pbergedge != NULL)
      {
       
         puser = m_papp->m_pappThis->m_psession->m_pbergedgeInterface->login(set);

      }
      else
      {

         class validate authuser(m_papp->m_pappThis, "system\\user\\authenticate.xhtml", true);
         authuser.m_bDeferRegistration = true;
         authuser.propset().merge(set);
         puser = authuser.get_user();

      }

      return puser;

   }

   bool fontopus::get_auth(const char * psz, string & strUsername, string & strPassword)
   {
      /*::ca::fontopus * papp;
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
      class validate authuser(m_papp->m_pappThis, psz);
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

   void fontopus::logout()
   {
      if(m_puser != NULL)
      {
         try
         {
            System.file().del(::dir::userappdata("license_auth/00001.data"));
         }
         catch(...)
         {
         }
         try
         {
            System.file().del(::dir::userappdata("license_auth/00002.data"));
         }
         catch(...)
         {
         }
         delete m_puser;
      }
      m_puser = NULL;
   }



   user * fontopus::allocate_user()
   {
      return new class user(m_papp->m_pappThis);
   }

   user * fontopus::create_user(::fontopus::user * puser)
   {
      if(puser->m_strPathPrefix.is_empty())
      {
         puser->m_strPathPrefix = Application.dir().default_os_user_path_prefix();
      }
      puser->m_strPath = Application.dir().default_userfolder(puser->m_strPathPrefix, puser->m_strLogin);
      App(m_papp->m_pappThis).dir().mk(puser->m_strPath);
      puser->m_strDataPath = Application.dir().default_userdata(puser->m_strPathPrefix, puser->m_strLogin);
      App(m_papp->m_pappThis).dir().mk(puser->m_strDataPath);
      puser->m_strAppDataPath = Application.dir().default_userappdata(puser->m_strPathPrefix, puser->m_strLogin);
      App(m_papp->m_pappThis).dir().mk(puser->m_strAppDataPath);
      puser->create_ifs();
      return puser;
   }


   user * fontopus::get_user()
   {
      if(m_papp->m_pappThis->is_session())
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
         if(m_puser != NULL)
         {
            if(m_puser->m_pifs == NULL)
            {
               m_puser->create_ifs();
            }
         }
         return m_puser;
      }
      else if(m_papp == NULL || m_papp->m_psession == NULL)
      {
         return NULL;
      }
      else
      {
         return Sess(m_papp->m_pappThis).get_user();
      }
   }

   void fontopus::set_user(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void fontopus::set_user(user * puser)
   {
      m_puser = puser;
   }

   bool fontopus::check_license(const char * pszId, bool bInteractive)
   {

      class validate authuser(m_papp->m_pappThis, "err\\user\\authentication\\not_licensed.xhtml", true, bInteractive);
      return authuser.get_license(pszId);

   }

   void fontopus::on_user_login(user * puser)
   {
      UNREFERENCED_PARAMETER(puser);
   }


} // namespace fontopus


