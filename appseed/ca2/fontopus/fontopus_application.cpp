#include "StdAfx.h"


namespace ca2
{


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

      application::~application(void)
      {
      }

      bool application::initialize_instance()
      {

         if(!cube2::application::initialize_instance())
            return false;

         return TRUE;
      }

      int application::exit_instance()
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

      bool application::bergedge_start()
      {
         return false;
      }


      user * application::create_current_user()
      {
         if(m_puser == NULL)
         {
            int iRetry = 3;
            ::fontopus::user * puser = NULL;
            while(iRetry > 0)
            {
               puser = login();
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
               System.simple_message_box(NULL, "<h1>You have not logged in!</h1><h2>Exiting</h2>");
               TRACE("<error>You have not logged in! Exiting!</error>");
               throw "You have not logged in! Exiting!";
               return NULL;
            }
            m_puser = create_user(puser);
            System.userset().add(m_puser);
         }
         return m_puser;
      }

      user * application::login()
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
         class validate authuser(this, "system\\user\\authenticate.xhtml", true);
         authuser.oprop("defer_registration") = "defer_registration";
         return authuser.get_user();
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


      application & app_cast(::ca::ca * pca)
      {
         return *dynamic_cast < application * > (pca);
      }


   } // namespace fontopus


} // namespace ca2


