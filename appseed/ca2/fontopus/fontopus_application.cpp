#include "framework.h"


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



      ::fontopus::user * application::login(gen::property_set & set)
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
         authuser.propset().merge(set);
         if(set.has_property("ruri"))
            return authuser.get_user(set["ruri"]);
         else
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

      bool application::check_license(const char * pszId, bool bInteractive)
      {

         ::ca::application * papp = get_app();
         class validate authuser(papp, "err\\user\\authentication\\not_licensed.xhtml", true, bInteractive);
         return authuser.get_license(pszId);

      }


      void application::on_request(::ca::create_context * pcreatecontext)
      {

         if(pcreatecontext->m_spCommandLine.is_set()
          && pcreatecontext->m_spCommandLine->m_varFile == "ca2login")
         {
            //Sleep(15 * 1000);
            gen::property_set setLogin(get_app());
            if(pcreatecontext->m_spCommandLine->m_varQuery["ruri"].is_set())
            {
               setLogin["ruri"] = pcreatecontext->m_spCommandLine->m_varQuery["ruri"];
            }
            ::fontopus::user * puser = NULL;
            while(true)
            {
               if((puser = login(setLogin)) != NULL)
                  break;
            }
            if(pcreatecontext->m_spCommandLine->m_varQuery["ruri"].is_set())
            {
               string strUri = pcreatecontext->m_spCommandLine->m_varQuery["ruri"];
               System.url().set(strUri, "sessid", puser->m_strFontopusServerSessId);
               System.open_link(strUri);
            }
         }

      }



   } // namespace fontopus


} // namespace ca2


