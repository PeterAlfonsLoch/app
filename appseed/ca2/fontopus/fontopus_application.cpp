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
         m_strAppName         = "fontopus2";
         m_strBaseSupportId   = "votagus_ca2_fontopus";
         m_strInstallToken    = "fontopus2";    
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



      ::fontopus::user * application::login()
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


   } // namespace fontopus


} // namespace ca2


