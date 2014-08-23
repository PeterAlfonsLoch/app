#include "framework.h"


namespace fontopus
{


   fontopus::fontopus(::axis::application * papp) :
      element(papp),
      ::aura::departament(papp)
   {

      m_puser                       = NULL;

      m_pthreadCreatingUser      = NULL;

      Application.gudo_get("fontopus::fontopus::m_mapFontopusServer",m_mapFontopusServer);

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


   user * fontopus::create_current_user(const char * pszRequestUrl)
   {
      
      property_set set(get_app());

      if(m_puser == NULL)
      {

         if(pszRequestUrl != NULL)
         {
            
            set["ruri"] = pszRequestUrl;

         }

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
            //throw string("You have not logged in! Exiting!");
            debug_box("You have not logged in!","Debug Message",MB_OK);
            return NULL;
         }
         m_puser = create_user(puser);
         System.userset().add(m_puser);


         if(m_puser != NULL
            && !::str::begins(m_puser->m_strLogin, "system")
            && m_pauraapp->m_strAppId != "app-core/deepfish"
            && !::str::begins(m_pauraapp->m_strAppName, "app-core/deepfish_")
            && !m_pauraapp->is_serviceable())
         {

            on_user_login(m_puser);

         }



      }
      return m_puser;
   }

   user * fontopus::login(property_set & set)
   {

      user * puser = NULL;

      class validate authuser(get_app(), "system\\user\\authenticate.xhtml", true);
      
      authuser.m_bDeferRegistration = true;

      authuser.propset().merge(set);

      if(set.has_property("ruri"))
      {
         
         puser = authuser.get_user(set["ruri"]);

      }
      else
      {

         puser = authuser.get_user();

      }

      return puser;

   }

   bool fontopus::get_auth(const char * psz, string & strUsername, string & strPassword)
   {
          /*::draw2d::fontopus * papp;
      if(m_puiInitialPlaceHolderContainer != NULL)
      {
      papp = m_puiInitialPlaceHolderContainer->m_pauraapp;
      }
      else if(System.m_puiInitialPlaceHolderContainer != NULL)
      {
      papp = System.m_puiInitialPlaceHolderContainer->m_pauraapp;
      }
      else
      {
      papp = this;
      }*/
      //class validate authuser(papp, psz);
      class validate authuser(get_app(), psz);
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
      return new class user(m_pauraapp);
   }

   user * fontopus::create_user(::fontopus::user * puser)
   {
      if(puser->m_strPathPrefix.is_empty())
      {
         puser->m_strPathPrefix = Application.dir().default_os_user_path_prefix();
      }
      puser->m_strPath = Application.dir().default_userfolder(puser->m_strPathPrefix, puser->m_strLogin);
      Sess(m_pauraapp).dir().mk(puser->m_strPath);
      puser->m_strDataPath = Application.dir().default_userdata(puser->m_strPathPrefix, puser->m_strLogin);
      Sess(m_pauraapp).dir().mk(puser->m_strDataPath);
      puser->m_strAppDataPath = Application.dir().default_userappdata(puser->m_strPathPrefix, puser->m_strLogin);
      Sess(m_pauraapp).dir().mk(puser->m_strAppDataPath);
      puser->create_ifs();
      return puser;
   }


   user * fontopus::create_system_user(const string & strSystemUserName)
   {

      m_puser                 = new ::fontopus::user(get_app());

      m_puser->m_strLogin     = strSystemUserName;

      user * puserNew = create_user(m_puser);

      if(puserNew == NULL)
      {

         delete m_puser;

         m_puser = NULL;

      }

      return m_puser;

   }



   user * fontopus::get_user(bool bSynch, const char * pszRequestUrl)
   {

      if(m_puser == NULL)
      {

         if(m_pthreadCreatingUser == ::get_thread())
            return NULL;

         if(m_pthreadCreatingUser != NULL)
         {

            if(!bSynch)
               return m_puser;

            while(m_pthreadCreatingUser != NULL && m_pthreadCreatingUser->m_bRun && ::get_thread()->m_bRun)
            {

               do_events(millis(84));

               if(m_pthreadCreatingUser == NULL)
                  break;

               m_pthreadCreatingUser->m_evReady.wait(millis(0));

            }

            if(m_puser != NULL)
               return m_puser;

            return NULL;

         }

         m_pthreadCreatingUser = new create_user_thread(get_app());

         if(pszRequestUrl != NULL)
         {

            m_pthreadCreatingUser->m_strRequestUrl = pszRequestUrl;

         }

         m_pthreadCreatingUser->m_bAutoDelete = true;

         m_pthreadCreatingUser->begin();

         if(!bSynch)
            return m_puser;

         while(m_pthreadCreatingUser != NULL && m_pthreadCreatingUser->m_bRun && ::get_thread()->m_bRun)
         {

            do_events(millis(84));

            if(m_pthreadCreatingUser == NULL)
               break;

            try
            {

               m_pthreadCreatingUser->m_evReady.wait(millis(0));

            }
            catch(...)
            {

               break;

            }

         }

         if(m_puser != NULL)
            return m_puser;

         return NULL;

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

      class validate authuser(get_app(), "err\\user\\authentication\\not_licensed.xhtml", true, bInteractive);
      return authuser.get_license(pszId);


   }

   void fontopus::on_user_login(user * puser)
   {




#ifdef METROWIN

      if(!System.directrix()->m_varTopicQuery.has_property("install")
         && !System.directrix()->m_varTopicQuery.has_property("uninstall"))
      {

         sp(::create_context) spcreatecontext(allocer());

         sp(::axis::application) papp = Session.start_application("application", "app-core/deepfish", spcreatecontext);

         if(papp == NULL)
         {
            Application.simple_message_box("deepfish subsystem - responsible for running background applications - could not be started", MB_ICONEXCLAMATION);
         }

      }

#endif

   }







   void fontopus::on_request(sp(::create_context) pcreatecontext)
   {

      if(pcreatecontext->m_spCommandLine.is_set()
         && pcreatecontext->m_spCommandLine->m_varFile == "ca2login")
      {
         //Sleep(15 * 1000);
         property_set setLogin(get_app());
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
            System.url().string_set(strUri, "sessid", puser->m_strFontopusServerSessId);
            System.open_link(strUri);
         }
      }

   }

   string fontopus::get_server(const char * pszUrl, int32_t iRetry)
   {

      string strHost(url_get_server(pszUrl));

      if(strHost.is_empty())
      {

         strHost = System.url().get_server(pszUrl);

      }

      string strFontopusServer;

      if (m_mapFontopusServer.Lookup(strHost, strFontopusServer) && strFontopusServer.has_char())
      {
         return strFontopusServer;
      }

      ::sockets::socket_handler h(get_app());

   retry:

      if (iRetry < 0)
         return ""; // should not retry or lookup is valid and strFontopusServer is really empty

      string strGetFontopus("http://" + strHost + "/get_fontopus");

      sp(::sockets::http_session) psession;
      try
      {

         ::property_set set(get_app());

         set["raw_http"] = true;

         set["get_response"] = "";

         psession = System.http().request(psession,strGetFontopus,set);

         strFontopusServer = set["get_response"];

      }
      catch (...)
      {
      }

      m_mapFontopusSession.set_at(strFontopusServer, psession);

      m_mapFontopusServer.set_at(strHost, strFontopusServer);

      Application.gudo_set("fontopus::fontopus::m_mapFontopusServer",m_mapFontopusServer);

      iRetry--;

      if (strFontopusServer.is_empty())
         goto retry;

      return strFontopusServer;

   }

   string fontopus::get_fontopus_server(const char * pszRequestingServerOrUrl,int32_t iRetry)
   {

      string strRequestingServer = System.url().get_server(pszRequestingServerOrUrl);

      DWORD dwGetFontopusBeg = ::get_tick_count();

      string strGetFontopus("http://" + strRequestingServer + "/get_fontopus");

      sp(::axis::application) papp = get_app();

      url_domain domainFontopus;

      string strFontopusServer = Session.fontopus()->get_server(strGetFontopus,8);

      domainFontopus.create(strFontopusServer);

      if(domainFontopus.m_strRadix != "ca2")
         return "";

      DWORD dwGetFontopusEnd = ::get_tick_count();

      TRACE("NetLogin: Get Fontopus Millis = %d",dwGetFontopusEnd - dwGetFontopusBeg);

      return strFontopusServer;

   }


   create_user_thread::create_user_thread(sp(::axis::application) papp) :
      element(papp),
      ::thread(papp),
      m_evReady(papp)
   {

      m_evReady.ResetEvent();

   }


   create_user_thread::~create_user_thread()
   {


   }

   int32_t create_user_thread::run()
   {


#ifdef WINDOWSEX

      ::attach_thread_input_to_main_thread(false);

#endif

      ::fontopus::user * puser = Session.fontopus()->create_current_user(m_strRequestUrl);

      if(puser != NULL)
      {

         if(!puser->initialize())
         {

            delete puser;

            Session.fontopus()->m_puser = NULL;

         }
         else
         {

            Session.fontopus()->m_puser = puser;

         }

      }
      else
      {

         Session.fontopus()->m_puser = NULL;

      }

      m_evReady.SetEvent();

      Session.fontopus()->m_pthreadCreatingUser = NULL;

      return 0;

   }


} // namespace fontopus



