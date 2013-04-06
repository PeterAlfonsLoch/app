#include "framework.h"


namespace ca
{


   namespace fontopus
   {


      fontopus::fontopus()
      {

         m_puser                    = ::null();
         m_pthreadCreatingUser      = ::null();

      }


      void fontopus::construct(sp(::ca::application) papp)
      {

         ::fontopus::fontopus::construct(papp);

      }


      fontopus::~fontopus()
      {

      }


      bool fontopus::initialize_instance()
      {

         if(!::fontopus::fontopus::initialize_instance())
            return false;

         return TRUE;

      }


      int32_t fontopus::exit_instance()
      {

         try
         {

            ::fontopus::fontopus::exit_instance();

         }
         catch(...)
         {

         }
         return 0;
      }


      ::fontopus::user * fontopus::login(::ca::property_set & set)
      {
         /*::ca::fontopus * papp;
         if(m_puiInitialPlaceHolderContainer != ::null())
         {
            papp = m_puiInitialPlaceHolderContainer->m_papp;
         }
         else if(System.m_puiInitialPlaceHolderContainer != ::null())
         {
            papp = System.m_puiInitialPlaceHolderContainer->m_papp;
         }
         else
         {
            papp = this;
         }*/
         //class validate authuser(papp, "system\\user\\authenticate.xhtml", true);
         class validate authuser(get_app(), "system\\user\\authenticate.xhtml", true);
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
         if(m_puiInitialPlaceHolderContainer != ::null())
         {
            papp = m_puiInitialPlaceHolderContainer->m_papp;
         }
         else if(System.m_puiInitialPlaceHolderContainer != ::null())
         {
            papp = System.m_puiInitialPlaceHolderContainer->m_papp;
         }
         else
         {
            papp = this;
         }*/
         //class validate authuser(papp, psz);
         class validate authuser(get_app(), psz);
         validate::auth * pauth = authuser.get_auth();
         if(pauth == ::null())
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

         class validate authuser(get_app(), "err\\user\\authentication\\not_licensed.xhtml", true, bInteractive);
         return authuser.get_license(pszId);

      }


      void fontopus::on_request(sp(::ca::create_context) pcreatecontext)
      {

         if(pcreatecontext->m_spCommandLine.is_set()
          && pcreatecontext->m_spCommandLine->m_varFile == "ca2login")
         {
            //Sleep(15 * 1000);
            ::ca::property_set setLogin(get_app());
            if(pcreatecontext->m_spCommandLine->m_varQuery["ruri"].is_set())
            {
               setLogin["ruri"] = pcreatecontext->m_spCommandLine->m_varQuery["ruri"];
            }
            ::fontopus::user * puser = ::null();
            while(true)
            {
               if((puser = login(setLogin)) != ::null())
                  break;
            }
            if(pcreatecontext->m_spCommandLine->m_varQuery["ruri"].is_set())
            {
               string strUri = pcreatecontext->m_spCommandLine->m_varQuery["ruri"];
               System.url().string_set(strUri, "sessid", puser->m_strFontopusServerSessId);
               System.open_link(strUri);
            }
         }

      }



   } // namespace fontopus


} // namespace ca


