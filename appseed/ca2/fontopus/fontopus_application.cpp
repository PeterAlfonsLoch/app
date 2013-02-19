#include "framework.h"


namespace ca2
{


   namespace fontopus
   {


      fontopus::fontopus()
      {
         m_puser              = NULL;
         m_bIsCreatingUser    = false;
      }

      void fontopus::construct()
      {
         m_strAppName         = "fontopus";
         m_strBaseSupportId   = "votagus_ca2_fontopus";
         m_strInstallToken    = "fontopus";    
      }

      fontopus::~fontopus()
      {
      }

      bool fontopus::initialize_instance()
      {

         if(!cube2::fontopus::initialize_instance())
            return false;

         return TRUE;
      }

      int32_t fontopus::exit_instance()
      {
         try
         {
            ::cube2::fontopus::exit_instance();
         }
         catch(...)
         {
         }
         return 0;
      }

      bool fontopus::bergedge_start()
      {
         return false;
      }



      ::fontopus::user * fontopus::login(gen::property_set & set)
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
         class validate authuser(this, "system\\user\\authenticate.xhtml", true);
         authuser.m_bDeferRegistration = true;
         authuser.propset().merge(set);
         if(set.has_property("ruri"))
            return authuser.get_user(set["ruri"]);
         else
            return authuser.get_user();
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

      bool fontopus::check_license(const char * pszId, bool bInteractive)
      {

         ::ca::fontopus * papp = get_app();
         class validate authuser(papp, "err\\user\\authentication\\not_licensed.xhtml", true, bInteractive);
         return authuser.get_license(pszId);

      }


      void fontopus::on_request(::ca::create_context * pcreatecontext)
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


