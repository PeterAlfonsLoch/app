#include "framework.h"


#ifdef BSD_STYLE_SOCKETS

#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/bn.h>
#include <openssl/err.h>

#endif

string chunk_split (const string & body, int32_t chunklen = 76, const string & end = "\r\n");


string chunk_split (const string & body, int32_t chunklen, const string & end)
{

   strsize pos = 0;
   string strRet;
   strsize iRead;
   while(pos < body.get_length())
   {
      iRead = min(chunklen, body.get_length() - pos);
      strRet += body.Mid(pos, iRead);
      strRet += end;
      pos += iRead;
   }

   return strRet;

}

typedef string ( *SALT)(sp(::base::application), const char * , stringa &);

namespace fontopus
{

   validate::validate(sp(::base::application) papp, const char * pszForm, bool bAuth, bool bInteractive) :
      element(papp),
      m_loginthread(papp)
   {

      m_bInteractive          = bInteractive;
      m_bAuth          = bAuth;
      m_strForm               = pszForm;
      m_bDeferRegistration    = false;
      sp(::base::application) pgenapp = (papp);
      if(pgenapp != NULL)
      {
         try
         {
            pgenapp->keep_alive();
         }
         catch(...)
         {
         }
      }
      //Sleep(15 * 1000);
      m_pauth           = NULL;
      m_pvOldWindow     = NULL;
      m_bInteractive    = bInteractive;
      m_bAuth           = bAuth;
      m_strForm         = pszForm;
      m_puser           = NULL;
      m_pauth           = NULL;
   }

   validate::~validate()
   {
      //m_loginthread.wait();
#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)
      //((HTHREAD) m_loginthread.get_os_data())->wait();
#else
      ::WaitForSingleObjectEx((HANDLE) m_loginthread.get_os_data(), INFINITE, FALSE);
#endif
   }

   ::fontopus::user * validate::get_user(const char * pszRequestingParty, const char * pszSessId)
   {
      m_loginthread.m_strSalt.Empty();
      if(command_thread()->property("app") == "simpledbcfg"
         || (command_thread()->property("app") == "app-core/netnodelite" && command_thread()->property("root_handler") == "webserver")
         || (command_thread()->property("app") == "app-core/netnodelite")
         || command_thread()->property("app") == "veievserver"
         || command_thread()->property("app") == "simpledbcfg"
         //|| command_thread()->property("app") == "veriwell_mplite"      // churrasco 2011 m_strLicense
         || command_thread()->property("app") == "app-core/netnodecfg"
         || command_thread()->property("app") == "app-core/netnode_dynamic_web_server"
         || command_thread()->property("app") == "app-core/netnode_dynamic_web_server_cfg"
		   || command_thread()->property("app") == "app-gtech/sensible_netnode"
         || command_thread()->property("app") == "app-gtech/sensible_service")
      {
         m_puser = Session.fontopus()->allocate_user();
         m_puser->m_strPathPrefix = "system" + ::str::has_char(Application.command()->m_varTopicQuery["systemid"], "-");
         m_puser->m_strLogin = system_user_1;
         return m_puser;
      }
      else if(command_thread()->property("app") == "app-core/mydns"
         || command_thread()->has_property("install")
         || command_thread()->has_property("uninstall"))
      {
         m_puser = Session.fontopus()->allocate_user();
         m_puser->m_strPathPrefix = "system" + ::str::has_char(Application.command()->m_varTopicQuery["systemid"], "-");
         m_puser->m_strLogin = system_user_1;
         return m_puser;
      }
      //else if(!strcmp(System.get_module_name(), "productionapp")
      //   || !strcmp(System.get_module_name(), "productionbasisapp")
      //   || !strcmp(System.get_module_name(), "backupapp")
      //   || System.command()->m_varTopicQuery["app"] == "production"
      //   || System.get_license_id() == "winservice_filesystemsize")
      else if(command_thread()->property("app") == "backup"
         || command_thread()->property("app") == "winservice_filesystemsize")
      {
         m_puser = Session.fontopus()->allocate_user();
         m_puser->m_strPathPrefix = "system" + ::str::has_char(Application.command()->m_varTopicQuery["systemid"], "-");
         m_puser->m_strLogin = system_user_2;
         return m_puser;
      }
      string strDir;
      string strUsername;
      string strPasshash;
      //System.crypto().file_get(Application.dir().usersystemappdata(Application.dir().default_os_user_path_prefix(), "license_auth", "00001.data"), strUsername, "", get_app());
      crypto_file_get(::dir::userappdata("license_auth/00001.data"), strUsername, "");
      m_loginthread.m_strUsername = strUsername;
      string strHost(pszRequestingParty);

      stringa straRequestingServer;
      straRequestingServer.add("account.ca2.cc");
      //straRequestingServer.add("eu-account.ca2.cc");
      ///straRequestingServer.add("asia-account.ca2.cc");
      if(strHost.is_empty())
      {
         if(::get_thread() != NULL && ::get_thread()->m_strWorkUrl.has_char())
         {
            strHost = ::get_thread()->m_strWorkUrl;
         }
         else
         {
            strHost = Application.file().as_string(System.dir().appdata("database\\text\\last_good_known_fontopus_com.txt"));
            if(!straRequestingServer.contains_ci(strHost))
            {
               strHost = "https://account.ca2.cc/";
            }
         }
      }
      if(System.url().get_server(strHost).has_char())
      {
         strHost = System.url().get_server(strHost);
      }

      if(straRequestingServer.contains(Application.command_thread()->m_varTopicQuery["fontopus"].get_string())
         && Application.command_thread()->m_varTopicQuery["sessid"].get_string().get_length() > 16)
      {
         m_loginthread.m_puser = Session.fontopus()->allocate_user();
         m_loginthread.m_puser->m_sessionidmap[Application.command_thread()->m_varTopicQuery["fontopus"].get_string()] = Application.command_thread()->m_varTopicQuery["sessid"].get_string();
         m_loginthread.m_puser->m_sessionidmap[strHost] = Application.command_thread()->m_varTopicQuery["sessid"].get_string();
         m_loginthread.m_puser->m_strFontopusServerSessId = Application.command_thread()->m_varTopicQuery["sessid"].get_string();
         m_loginthread.m_puser->m_strRequestingServer = strHost;
         xml::document documentBasicInfo(get_app());

         string strApiServer;

         strApiServer = Application.command_thread()->m_varTopicQuery["fontopus"];

         strApiServer.replace("account", "api");

         property_set set(get_app());

         set["user"] = m_loginthread.m_puser;

         if(documentBasicInfo.load(Application.http().get("https://" + strApiServer + "/account/get_basic_info", set)))
         {
            string strLogin;
            if(documentBasicInfo.get_root()->get_attr("login", strLogin) && strLogin.find("@") > 0)
            {
               m_loginthread.m_puser->m_strLogin = strLogin;
               return  m_loginthread.m_puser;
            }
         }
      }

      m_loginthread.m_puser = Session.fontopus()->allocate_user();

      if(pszSessId != NULL && string(pszSessId).get_length() > 16)
      {
         m_loginthread.m_puser->m_sessionidmap[strHost] = pszSessId;
      }

      m_loginthread.m_strRequestingServer = strHost;
      crypto_file_get(::dir::userappdata("license_auth/00002.data"), strPasshash, calc_key_hash());
      if(strUsername.has_char() && strPasshash.has_char())
      {

         m_loginthread.m_strPassword.Empty();
         m_loginthread.m_strPasshash = strPasshash;
         m_loginthread.m_pcallback = this;
         m_loginthread.run();

         close_all();

         return m_puser;
      }
      else if(m_bInteractive)
      {

         m_loginthread.m_strModHash.Empty();
         m_loginthread.m_strKeyHash.Empty();
         m_loginthread.m_strCa2Hash.Empty();

         string strUsername;
         string strSessId;
         string strSecureId;

         rect rectDesktop;

         System.get_monitor_rect(0, rectDesktop);

         if (::fontopus::show_auth_window(get_app(), rectDesktop, strUsername, strSessId, strSecureId, m_loginthread.m_strLoginUrl, m_loginthread.m_strRequestingServer) != "ok")
         {
            delete m_puser;
            return NULL;
         }

         m_puser = Session.fontopus()->allocate_user();

         m_puser->m_strLogin = strUsername;
         m_puser->m_strFontopusServerSessId = strSessId;
         m_puser->set_sessid(m_puser->m_strFontopusServerSessId, m_loginthread.m_strLoginUrl);
         m_puser->m_strRequestingServer = m_loginthread.m_strRequestingServer;
         m_puser->m_strFunUserId = strSecureId;

         //ensure_main_document();
         //page1();
         //show_and_request_auth();
         return m_puser;

      }
      else
      {

         return NULL;

      }

   }

   /*void validate::ensure_main_document()
   {
      sp(::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible = false;
      createcontext->m_puiParent = Sys(get_app()).oprop("top_parent").cast < ::user::interaction > ();
      createcontext->m_bOuterPopupAlertLike = true;
   }*/





   bool validate::get_license(const char * psz)
   {
      string strLicense(psz);
      if(strLicense == "netnodeapp"
         || strLicense == "netnodecfgapp"
         || strLicense == "simpledbcfg"
         || (strLicense == "app-core/netnodelite" && command_thread()->property("root_handler") == "webserver")
         || (strLicense == "app-core/netnodelite")
         || strLicense == "veievserver"
         //|| strLicense == "veriwell_mplite"      // churrasco 2011 m_strLicense
         || strLicense == "mydns"
         || Application.command()->m_varTopicQuery.has_property("install")
         || Application.command()->m_varTopicQuery.has_property("uninstall")
         || strLicense == "netnode"
         || strLicense == "netnode_dynamic_web_server"
         || strLicense == "app-core/netnodecfg"
         || strLicense == "app-core/netnode_dynamic_web_server"
         || strLicense == "app-core/netnode_dynamic_web_server_cfg"
		   || strLicense == "app-gtech/sensible_netnode"
         || strLicense == "app-gtech/sensible_service")
      {
         return true;
      }
      else if(strLicense == "flag"
         || strLicense == "alarm"
         || strLicense == "biteditor"
         || strLicense == "md5"
         || strLicense == "vmp"
         || strLicense == "veiev"
         || strLicense == "netshareservercfg"
         || strLicense == "netshareserver"
         || strLicense == "veriedit"
         || strLicense == "netshareclient"
         || strLicense == "verisimplevideo"
         || strLicense == "eluce"
         || strLicense == "whiteboard"
         || strLicense == "bergedge"
         || strLicense == "app.sysutils.igd"
         || strLicense == "projection"
         || strLicense == "querydb"
         )
      {
         return true;
      }
      //else if(!strcmp(System.get_module_name(), "productionapp")
      //   || !strcmp(System.get_module_name(), "productionbasisapp")
      //   || !strcmp(System.get_module_name(), "backupapp")
      //   || System.get_license_id() == "winservice_filesystemsize")
      else if(strLicense == "backupapp"
         || strLicense == "winservice_filesystemsize"
         || strLicense == "production")
      {
         return true;
      }
      else if(strLicense == "i2com")
      {
         return true;
      }
      m_strLicense = psz;
      m_loginthread.m_strLicense = m_strLicense;
      string strHost = Application.file().as_string(System.dir().appdata("database\\text\\last_good_known_fontopus_com.txt"));
      stringa straRequestingServer;
      straRequestingServer.add("account.ca2.cc");
      //straRequestingServer.add("eu-account.ca2.cc");
      //straRequestingServer.add("asia-account.ca2.cc");
      if(!straRequestingServer.contains_ci(strHost))
      {
         strHost = "account.ca2.cc";
      }

      if(straRequestingServer.contains(Application.command_thread()->m_varTopicQuery["fontopus"].get_string())
         && Application.command_thread()->m_varTopicQuery["sessid"].get_string().get_length() > 16)
      {
         strHost = Application.command_thread()->m_varTopicQuery["fontopus"].get_string();
      }

      string strAuthUrl;

      string strApiHost = strHost;

      strApiHost.replace("account", "api");

      strAuthUrl = "https://" + strApiHost + "/account/auth";

      property_set set;

      string strAuth;
      set["post"]["entered_license"] = m_strLicense;
      //m_puser->set_sessid(ApplicationUser.m_str, strAuthUrl);
      //      uint32_t dwTimeProfile1 = get_tick_count();

      set["post"]["entered_license"] = m_strLicense;

      Application.http().get(strAuthUrl, strAuth, set);

      m_loginthread.m_strFontopusServer = strHost;

      xml::document doc(get_app());
      doc.load(strAuth);
      if(doc.get_root()->get_name() == "response")
      {
         if(doc.get_root()->attr("id") == "auth")
         {
            return true;
         }
      }

      if(m_bInteractive)
      {

#ifdef WINDOWS

         if (get_splash() != NULL)
         {

            ::KillTimer(get_splash(), 123);

         }

#endif // WINDOWS

         {

            ::PostMessage(get_splash(), WM_CLOSE, 0, 0);

         }

         ::simple_message_box(NULL,"No license to use the application/feature \"" + string(psz) + "\" for the user \"" + ApplicationUser.m_strLogin + "\". Contact your system administrator.",psz,MB_ICONEXCLAMATION);


         return false;


         m_loginthread.m_strModHash.Empty();
         m_loginthread.m_strKeyHash.Empty();
         m_loginthread.m_strCa2Hash.Empty();
         ensure_main_document();
         page1();
         show_and_request_auth();
         return m_bLicense;
      }
      return false;
      string strDir;
      string strUsername;
      string strPasshash;
      crypto_file_get(::dir::userappdata("license_auth/00001.data"), strUsername, "");
      m_loginthread.m_strUsername = strUsername;
      crypto_file_get(::dir::userappdata("license_auth/00002.data"), strPasshash, calc_key_hash());
      if(strUsername.has_char() && strPasshash.has_char())
      {

         m_loginthread.m_strPassword.Empty();
         m_loginthread.m_strPasshash = strPasshash;
         m_loginthread.m_pcallback = this;
         m_loginthread.run();

         close_all();

         return m_bLicense;
      }
      else if(m_bInteractive)
      {
         m_loginthread.m_strModHash.Empty();
         m_loginthread.m_strKeyHash.Empty();
         m_loginthread.m_strCa2Hash.Empty();
         ensure_main_document();
         page1();
         show_and_request_auth();
         return m_bLicense;
      }
      else
      {
         return false;
      }
   }







   login_thread::login_thread(sp(::base::application) papp) :
      element(papp),
      thread(papp),
      simple_thread(papp)
   {
      m_bOk                = false;
      m_puser              = NULL;
      m_bFontopusServer    = false;
   }

   login_thread::~login_thread()
   {
   }

   void validate::get_mod(stringa & straHash, stringa & straSource)
   {
      straHash.remove_all();
      straSource.remove_all();
   }


   string validate::calc_mod_hash()
   {

      if(m_loginthread.m_strModHash.has_char())
         return m_loginthread.m_strModHash;

      stringa straHash;

      stringa straSource;

      get_mod(straHash, straSource);

      m_loginthread.m_strModHash = System.crypto().md5(straHash.implode(";"));

      return m_loginthread.m_strModHash;

   }


   string validate::calc_key_hash()
   {
      if(m_loginthread.m_strKeyHash.has_char())
         return m_loginthread.m_strKeyHash;
      {
         m_loginthread.m_strKeyHash = "ca2_12n";
         return "ca2_12n";
      }
   }

   // return hash and check if hash is valid
   bool validate::check_ca2_hash()
   {
      string strUrl("https://" + System.dir().get_api_cc() + "/account/check_hash");
      property_set set;
      string strResponse;
      stringa straHash;
      stringa straSource;
      get_mod(straHash, straSource);
      straHash.insert_at(0, m_loginthread.m_strPasshash);
      straHash.insert_at(0, m_loginthread.m_strUsername);

      set["post"]["hash"] = straHash.implode(";");
      set["post"]["source"] = straHash.implode(";");
      for(int32_t i = 0; i < 3; i++)
      {
         if(Application.http().get(strUrl, strResponse, set))
            break;
      }
      if(strResponse == "OK")
         return true;
      else
         return false;
   }

   void validate::on_login_thread_response(e_result iAuth, const char * pszResponse)
   {
      if(iAuth == result_auth)
      {
         authentication_succeeded();
      }
      else
      {
         authentication_failed(iAuth, pszResponse);
      }
   }

   void login_thread_callback::on_login_thread_response(e_result iAuth, const char * pszResponse)
   {
      UNREFERENCED_PARAMETER(iAuth);
      UNREFERENCED_PARAMETER(pszResponse);
   }

   string login_thread_callback::calc_mod_hash()
   {
      return "";
   }

   string login_thread_callback::calc_key_hash()
   {
      return "";
   }

   string login_thread_callback::calc_ca2_hash()
   {
      return "";
   }

   int32_t login_thread::run()
   {
      ::http::e_status estatus;
      string strResponse = Login(&estatus);
      e_result iAuth = result_fail;
      xml::document doc(get_app());
      doc.load(strResponse);
      if(doc.get_root()->get_name() == "response")
      {
         if(doc.get_root()->attr("id") == "auth" && doc.get_root()->attr("passhash").has_char() && doc.get_root()->attr("secureuserid").has_char())
         {
            Session.fontopus()->m_authmap[m_strUsername].m_mapServer[m_strRequestingServer] = strResponse;
            Session.fontopus()->m_authmap[m_strUsername].m_mapFontopus[m_strFontopusServer] = strResponse;
            m_puser->m_strLogin = m_strUsername;
            m_puser->m_strFontopusServerSessId = doc.get_root()->attr("sessid");
            m_puser->set_sessid(m_puser->m_strFontopusServerSessId, m_strLoginUrl);
            m_puser->m_strRequestingServer = m_strRequestingServer;
            m_puser->m_strFunUserId = doc.get_root()->attr("secureuserid");
            m_strPasshash = doc.get_root()->attr("passhash");
            iAuth = result_auth;
            if(m_bFontopusServer)
            {
               Application.file().put_contents(System.dir().appdata("database\\text\\last_good_known_fontopus_com.txt"), m_strRequestingServer);
            }
            execute();
            if(m_strLicense.has_char())
            {
               m_strValidUntil = doc.get_root()->attr("valid_until");
            }
         }
         else if(doc.get_root()->attr("id") == "registration_deferred")
         {
            delete m_puser;
            iAuth = result_registration_deferred;
         }
         else if(doc.get_root()->attr("id") == "not_auth")
         {

            if(doc.get_root()->attr("detail") == "please_finish_registration")
            {

               iAuth = result_please_finish_registration;

            }
            else if(doc.get_root()->attr("detail") == "wrong_password_or_login")
            {

               iAuth = result_wrong_password_or_login;

            }
            else if(doc.get_root()->attr("detail") == "no_login")
            {

               iAuth = result_no_login;

            }
            else if(doc.get_root()->attr("detail") == "no_password")
            {

               iAuth = result_no_password;

            }
            else
            {

               iAuth = result_fail;

            }

            delete m_puser;

         }
         else
         {
            delete m_puser;
            iAuth = result_fail;
         }

      }
      else
      {

         delete m_puser;

         if(estatus == ::http::status_connection_timed_out)
         {

            iAuth = result_time_out;

         }
         else
         {

            iAuth = result_fail;

         }

      }
      //      char * psz = NULL;
      //    *psz = '2';
      m_pcallback->on_login_thread_response(iAuth, strResponse);
      return TRUE;
   }

   string login_thread::Login(::http::e_status * pestatus)
   {
      if(m_straRequestingServer.get_count() <= 0)
      {
         stringa straRequestingServer;
         straRequestingServer.add("account.ca2.cc");
         //straRequestingServer.add("eu-account.ca2.cc");
         //straRequestingServer.add("asia-account.ca2.cc");
         if(straRequestingServer.contains_ci(m_strRequestingServer))
         {
            m_bFontopusServer = true;
            straRequestingServer.remove(m_strRequestingServer);
            straRequestingServer.insert_at(0, m_strRequestingServer);
            m_straRequestingServer = straRequestingServer;
         }
      }
      if(m_straRequestingServer.get_count() > 0)
      {
         string strLogin;
         for(int32_t i = 0; i < m_straRequestingServer.get_count(); i++)
         {
            m_strRequestingServer  = m_straRequestingServer[i];
            strLogin = NetLogin(pestatus);
            if(strLogin.has_char())
               return strLogin;
         }
         return "";
      }
      else
      {
         return NetLogin(pestatus);
      }
   }


   string login_thread::NetLogin(::http::e_status * pestatus)
   {

      if(Session.fontopus()->m_authmap[m_strUsername].m_mapServer[m_strRequestingServer].get_length() > 32)
      {
         return Session.fontopus()->m_authmap[m_strUsername].m_mapServer[m_strRequestingServer];
      }

      DWORD dwGetFontopusBeg = ::GetTickCount();

      string strGetFontopus("http://" + m_strRequestingServer + "/get_fontopus");

      m_strFontopusServer.Empty();

      sp(::base::application) papp = get_app();

      url_domain domainFontopus;

      m_strFontopusServer = Session.fontopus()->get_server(strGetFontopus,8);

      domainFontopus.create(m_strFontopusServer);

      if(domainFontopus.m_strRadix != "ca2")
         return "";

      if(Session.fontopus()->m_strFirstFontopusServer.is_empty())
      {
         
         Session.fontopus()->m_strFirstFontopusServer = m_strFontopusServer;

      }

      if(Session.fontopus()->m_authmap[m_strUsername].m_mapFontopus[m_strFontopusServer].get_length() > 32)
      {
         return Session.fontopus()->m_authmap[m_strUsername].m_mapFontopus[m_strFontopusServer];
      }


      DWORD dwGetFontopusEnd = ::GetTickCount();

      TRACE("NetLogin: Get Fontopus Millis = %d",dwGetFontopusEnd - dwGetFontopusBeg);

      string strLogin;

      string strApiServer;

      strApiServer = m_strFontopusServer;

      strApiServer.replace("account","api");

      m_strLoginUrl = "https://" + strApiServer + "/account/login";

      xml::document doc(get_app());

      string strSessId;

      string strRsaModulus;

      DWORD dwGetLoginBeg = ::GetTickCount();
      property_set set;


      ::sockets::socket_handler h(get_app());
      {
         //m_puser->set_sessid("not_auth", m_strLoginUrl);
         set["disable_ca2_sessid"] = true;
      }

      set["app"] = papp;

      sp(::sockets::http_session) psession = m_mapFontopusSession[m_strFontopusServer];


      for(int32_t iRetry = 0; iRetry <= 8; iRetry++)
      {

         if(iRetry > 0)
         {
            Sleep(iRetry * 584);
         }

         try
         {

            set["get_response"] = "";

            psession = System.http().request(h,psession,m_strLoginUrl,set);

            m_mapFontopusSession.set_at(m_strFontopusServer,psession);

            strLogin = set["get_response"];

         }
         catch(...)
         {
         }

         strLogin.trim();

         if(strLogin.is_empty())
            continue;

         if(!doc.load(strLogin))
            continue;

         if(doc.get_root()->get_name() != "login")
            continue;

         strSessId = doc.get_root()->attr("sessid");

         if(strSessId.is_empty())
            continue;

         strRsaModulus = doc.get_root()->attr("rsa_modulus");

         if(strRsaModulus.has_char())
            break;

      }

      if(strRsaModulus.is_empty())
         return "";

      DWORD dwGetLoginEnd = ::GetTickCount();

      TRACE("NetLogin: Get Login Millis = %d",dwGetLoginEnd - dwGetLoginBeg);

      string strPass;
      if(m_strPasshash.is_empty())
      {
         strPass = System.crypto().nessie(m_strPassword);
      }
      else
      {
         strPass = m_strPasshash;
      }


      string strHex = System.crypto().spa_login_crypt(strPass, strRsaModulus);

      m_puser->m_strLogin = m_strUsername;

      string strAuth;

      DWORD dwAuthBeg = ::GetTickCount();
      {

         string strAuthUrl("https://" + strApiServer + "/account/auth?" + m_pcallback->oprop("defer_registration").get_string()
            +"&ruri=" + System.url().url_encode((m_pcallback->oprop("ruri").get_string())));

         property_set set;

         if(m_strPasshash.is_empty())
         {
            set["post"]["entered_password"] = strHex;
         }
         else
         {
            set["post"]["entered_passhash"] = strHex;
         }
         string strCrypt;

         string strUsername = m_strUsername;

         set["post"]["entered_login"] = m_strUsername;
         if(m_strLicense.has_char())
         {
            set["post"]["entered_license"] = m_strLicense;
         }

         m_puser->set_sessid(strSessId, strAuthUrl);
         set["app"] = papp;
         set["user"] = m_puser;
         set["cookies"] = m_puser->m_phttpcookies;
         set["get_response"] = "";
         uint32_t dwTimeProfile1 = get_tick_count();
         psession = System.http().request(h, psession, strAuthUrl, set);

         strAuth = set["get_response"];

         *pestatus = (::http::e_status) set["get_status"].int64();
         uint32_t dwTimeProfile2 = get_tick_count();

         TRACE0("login_thread::NetLogin Total time Application.http().get(\"" + strAuthUrl + "\") : " + ::str::from(dwTimeProfile2 - dwTimeProfile1));

      }
      DWORD dwAuthEnd = ::GetTickCount();

      TRACE("NetLogin: Authentication Millis = %d",dwAuthEnd - dwAuthBeg);

      return strAuth;

   }


   void login_thread::execute()
   {
      string strFilename;
      string strResponse;
      property_set set;
      for(int32_t i = 0; i < m_httpexecutea.get_size(); i++)
      {

         strFilename = System.file().time_square(get_app());

         set["post"] = m_httpexecutea[i].m_propertysetPost;
         set["headers"] = m_httpexecutea[i].m_propertysetHeaders;
         set["cookies"] = m_puser->m_phttpcookies;
         set["user"] = m_puser;

         System.http().download(m_httpexecutea[i].m_strUrl, strFilename, set);

         strResponse = Application.file().as_string(strFilename);
         TRACE0(strResponse);
         m_httpexecutea[i].m_strResponse = strResponse;
      }
   }


   //void validate::authentication_failed(e_result iAuth, const char * pszResponse)
   //{
   //   UNREFERENCED_PARAMETER(pszResponse);
   //   property_set propertyset;
   //   string strUsername = m_loginthread.m_strUsername;
   //   m_bLicense = false;
   //   m_puser = NULL;
   //}

   void validate::save_authentication_info()
   {
      TRACE0("The authentication has succeeded.");
      string strUsername = m_loginthread.m_strUsername;
      string strPasshash = m_loginthread.m_strPasshash;
      string strPassword = m_loginthread.m_strPassword;

      string strUsernamePrevious;
      string strPasshashPrevious;
      crypto_file_get(::dir::userappdata("license_auth/00001.data"), strUsernamePrevious, "");
      crypto_file_get(::dir::userappdata("license_auth/00002.data"), strPasshashPrevious, calc_key_hash());

      if((strUsername.has_char() && strPasshash.has_char())
         && (strUsernamePrevious != strUsername || strPasshashPrevious != strPasshash))
      {
         crypto_file_set(::dir::userappdata("license_auth/00001.data"), strUsername, "");
         crypto_file_set(::dir::userappdata("license_auth/00002.data"), strPasshash, calc_key_hash());
         if(strPassword.has_char())
         {
            string strSalt = System.crypto().v5_get_password_salt();
            crypto_file_set(::dir::userappdata("license_auth/00005.data"), strSalt, calc_key_hash());
            string strPasshash2 = System.crypto().v5_get_password_hash(strSalt, strPassword);
            crypto_file_set(::dir::userappdata("license_auth/00010.data"), strPasshash2, calc_key_hash());
         }
      }
      if(m_loginthread.m_strLicense.has_char())
      {
         stringa straLicense;
         straLicense.add(m_loginthread.m_strValidUntil);
         straLicense.add(System.datetime().international().get_gmt_date_time());
         crypto_file_set(::dir::userappdata("license_auth/" + m_loginthread.m_strLicense + ".data"), straLicense.implode(";"), calc_ca2_hash());
      }
      m_bLicense = true;
      m_puser = m_loginthread.m_puser;
   }


   void validate::close_all()
   {

      /*
      if(m_ptabview != NULL)
      {
         m_ptabview->get_wnd()->EndAllModalLoops(IDOK);
      }

      if(m_ptemplatePane != NULL)
      {
         m_ptemplatePane->close_all_documents(FALSE);
      }
      */

   }


   bool validate::get_defer_registration()
   {

      return m_bDeferRegistration;

   }



   void validate::show_and_request_auth()
   {

      /*
      if(m_loginthread.m_strLicense.is_empty())
      {
         m_pviewAuth->SetTimer(1984, 484, NULL);
      }
      ::core::live_signal livesignal;
      livesignal.keep(get_app()->m_pplaneapp);
      m_ptabview->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE, &livesignal);
      m_ptemplatePane->close_all_documents(FALSE);
      */

   }



   void validate::ensure_main_document()
   {
/*      return;
      if(m_pdoc != NULL)
         return;


      sp(::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible = false;
      createcontext->m_puiParent = Sys(get_app()).oprop("top_parent").cast < ::user::interaction > ();
      createcontext->m_bOuterPopupAlertLike = true;
      //Sleep(15 * 1000);
      m_pdoc = m_ptemplatePane->open_document_file(createcontext);
      sp(userex::pane_tab_view) pview = m_pdoc->get_typed_view < userex::pane_tab_view >();
      pview->set_view_creator(this);
      m_ptabview = pview;
      pview->set_tab("ca2open", 1);
      pview->set_tab("network", 2);
      pview->set_image_tab("", Application.dir().matter("image/keyboard-h21.png"), 3);
      pview->set_cur_tab_by_id(1);
      */
   }

   void validate::page1(const stringa & straMatter)
   {

      /*m_pdocAuth->get_html_data()->m_puser = m_loginthread.m_puser;

      string strPath;

      if(straMatter.get_count() <= 0)
      {

         if(m_strLicense.is_empty())
         {

            m_pdocAuth->get_html_data()->m_propertyset["reason"] = "Authenticating";

         }
         else
         {

            m_pdocAuth->get_html_data()->m_propertyset["reason"] = "Licensing";
            string strUrl;
            strUrl = "http://api.ca2.cc/spaignition/query?node=install_application&id=";
            strUrl += m_strLicense;
            strUrl += "&key=name";
            m_pdocAuth->get_html_data()->m_propertyset["project"] = System.http().get(strUrl);

            strUrl = "ext://https://account.ca2.cc/license?id="+ m_strLicense + "&lang=" + System.get_locale() + "&sessid=" + ApplicationUser.get_sessid(m_loginthread.m_strFontopusServer);
            m_pdocAuth->get_html_data()->m_propertyset["contribute_link"] = strUrl;

         }

         strPath = Application.dir().matter(m_strForm);

      }
      else
      {
         strPath = Application.dir().matter(straMatter);
      }

      if(!m_pdocAuth->on_open_document(strPath))
      {
         authentication_failed(::fontopus::result_fail, "Cannot open form for authentication!!");
         return;
      }

      display_main_frame();

      if(straMatter.get_count() <= 0)
      {

         sp(::user::interaction) pui = m_pviewAuth->get_child_by_name("user");
         sp(text_interface) ptext =  (pui.m_p);
         if(ptext != NULL)
         {
            ptext->_001SetText(m_loginthread.m_strUsername);
            if(m_loginthread.m_strUsername.is_empty())
               Application.user()->set_keyboard_focus(pui);
            else
            {
               pui = m_pviewAuth->get_child_by_name("password");
               Application.user()->set_keyboard_focus(pui);
            }
         }

      }*/

   }

   void validate::display_main_frame()
   {

      /*
      rect rectOpen;
      if(m_ptabview->GetParentFrame()->get_parent() == NULL)
      {

         System.get_screen_rect(rectOpen);
      }
      else
      {
         m_ptabview->GetParentFrame()->get_parent()->GetClientRect(rectOpen);
      }

#if defined(WINDOWSEX) || defined(LINUX)
      m_pvOldWindow = (void *) ::GetFocus();
#endif

      int32_t iWidth = rectOpen.width();
      int32_t iHeight = rectOpen.height();
      rectOpen.deflate(iWidth / 5, iHeight / 5);
      sp(simple_frame_window) pframe =  (m_pviewAuth->GetTopLevelParent().m_p);
      if(pframe != NULL)
      {
         pframe->m_bblur_Background = true;
      }
#ifdef WINDOWSEX
      int_ptr ui1 = GetCurrentThreadId();
      int_ptr ui2 = m_ptabview->GetTopLevelFrame()->get_os_int();
      if(::AttachThreadInput((uint32_t) ui1, (uint32_t) ui2, TRUE))
      {
         TRACE("AttachedThreadInput");
      }
#endif
      /*      if(System.m_puiInitialPlaceHolderContainer != NULL)
      {
      System.m_puiInitialPlaceHolderContainer->GetTopLevelParent()->ShowWindow(SW_SHOW);
      }
      else*/
/*      {
         //            m_ptabview->GetTopLevelFrame()->ShowWindow(SW_SHOW);
      }
      //       m_ptabview->GetTopLevelFrame()->SetActiveWindow();
      //     ::SwitchToThisWindow(m_ptabview->GetTopLevelFrame()->get_wnd()->get_safe_handle(), FALSE);
      m_ptabview->GetTopLevelFrame()->SetWindowPos(
         ZORDER_TOP,
         rectOpen.left, rectOpen.top,
         rectOpen.width(), rectOpen.height(),
         SWP_SHOWWINDOW);
      /*         if(m_ptabview->GetTopLevelFrame()->get_parent() != NULL)
      {
      try
      {
      m_ptabview->GetTopLevelFrame()->get_parent()->layout();
      }
      catch(...)
      {
      }
      }
      else
      {
      }*/
  /*    if(m_ptabview->GetTopLevelFrame()->SetForegroundWindow())
      {
         TRACE("fontopus_validate tab_view top_level_frame set_foreground_window OK");
         if(m_ptabview->GetTopLevelFrame()->BringWindowToTop())
         {
            TRACE("fontopus_validate tab_view top_level_frame bring_window_to_top OK");
         }
      }

      m_ptabview->GetTopLevelFrame()->ActivateFrame();
      m_ptabview->GetTopLevelFrame()->SetFocus();

      //         m_ptabview->GetTopLevelFrame()->layout();




      //m_pviewAuth->GetTopLevelParent()->SetForegroundWindow();
      //m_pviewAuth->GetTopLevelParent()->BringWindowToTop();
      */
   }

   void validate::pageMessage(const stringa & straMatter, property_set & set)
   {
      /*
      ensure_main_document();
      m_pdocAuth->get_html_data()->m_propertyset = set;
      page1(straMatter);
      if(m_ptabview->get_wnd()->m_iModalCount <= 0)
      {
         ::core::live_signal livesignal;
         livesignal.keep(get_app()->m_pplaneapp);
         m_ptabview->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE, &livesignal);
         m_ptabview->get_wnd()->EndAllModalLoops(IDOK);
      }
      */
   }

   /*
   void validate::on_create_view(::user::view_creator_data * pcreatordata)
   {
      switch(pcreatordata->m_id)
      {
      case 1:
         {
            m_pdocAuth = System.user()->create_child_form(this, pcreatordata->m_pholder);
            if(m_pdocAuth != NULL)
            {
               m_pviewAuth = m_pdocAuth->get_typed_view < form_view > ();
               m_pviewAuth->m_pcallback = this;
               pcreatordata->m_pdoc = m_pdocAuth;
               pcreatordata->m_pwnd = m_pviewAuth->GetParentFrame();
            }
         }
         break;
      case 2:
         {
            if(m_netcfg.initialize_child(pcreatordata->m_pholder))
            {
               pcreatordata->m_pdoc = m_netcfg.m_pdoc;
               pcreatordata->m_pwnd = m_netcfg.m_pview->GetParentFrame();
            }

         }
         break;
      case 3:
         {

            m_pkeyboardlayout = m_ptabview->create_view < ::userex::keyboard_layout > ();
            m_pkeyboardlayout->CreateViews();
            pcreatordata->m_pdoc = m_pkeyboardlayout->m_pdoc;
            pcreatordata->m_pwnd = m_pkeyboardlayout;
         }
         break;
      }
      if(pcreatordata->m_pwnd != NULL)
      {
         pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
      }

   }

   */


   void validate::on_show_view()
   {
/*      switch(m_ptabview->get_view_id())
      {
      case 1:
         {
         }
         break;
      case 2:
         {
            m_netcfg.on_show();
         }
         break;
      }*/
   }









   /*
   bool validate::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pview);
      if(pevent->m_eevent == ::user::event_button_clicked
         || pevent->m_eevent == ::user::event_enter_key)
      {
         if(pevent->m_puie->m_id == "submit" ||
            pevent->m_eevent == ::user::event_enter_key)
         {
            if(m_loginthread.get_os_data() != NULL)
               return true;
            m_pviewAuth->KillTimer(1984);
            m_loginthread.oprop("defer_registration") = oprop("defer_registration");
            if(m_bAuth)
            {
               m_ptabview->GetParentFrame()->ShowWindow(SW_HIDE);
               sp(::user::interaction) pui = m_pviewAuth->get_child_by_name("user");
               sp(text_interface) ptext =  (pui.m_p);
               //m_loginthread.m_puser = dynamic_cast < ::fontopus::user * > (System.allocate_user());
               ptext->_001GetText(m_loginthread.m_strUsername);
               pui = m_pviewAuth->get_child_by_name("password");
               ptext =  (pui.m_p);
               ptext->_001GetText(m_loginthread.m_strPassword);
               m_loginthread.m_pcallback = this;
               m_loginthread.begin();
            }
            else
            {
               m_pauth = new auth;
               sp(::user::interaction) pui = m_pviewAuth->get_child_by_name("user");
               sp(text_interface) ptext =  (pui.m_p);
               ptext->_001GetText(m_pauth->m_strUsername);
               pui = m_pviewAuth->get_child_by_name("password");
               ptext =  (pui.m_p);
               ptext->_001GetText(m_pauth->m_strPassword);
            }
            ::oswindow oswindowPrevious = (::oswindow) m_pvOldWindow;
            if(oswindowPrevious != NULL)
            {
               sp(::user::interaction) puiPrevious = System.window_from_os_data(oswindowPrevious);
               if(puiPrevious != NULL)
               {
                  if(puiPrevious->SetForegroundWindow())
                  {
                     TRACE("fontopus_validate tab_view top_level_frame set_foreground_window OK");
                     if(puiPrevious->BringWindowToTop())
                     {
                        TRACE("fontopus_validate tab_view top_level_frame bring_window_to_top OK");
                     }
                  }
                  //puiPrevious->ActivateFrame();
                  puiPrevious->SetFocus();
                  puiPrevious->layout();
               }
            }
            m_ptabview->GetParentFrame()->ShowWindow(SW_HIDE);
            return true;
         }
      }
      else if(pevent->m_eevent == ::user::event_timer
         && pevent->m_uiEvent == 1984)
      {

         string strDir;
         string strUsername;
         string strPasshash;

         string strPathUsername = ::dir::userappdata("license_auth/00001.data");
         string strPathPasshash = ::dir::userappdata("license_auth/00002.data");

         if(!Application.file().exists(strPathUsername) || !Application.file().exists(strPathPasshash))
            return true;

         System.crypto().file_get(strPathUsername, strUsername, "", get_app());
         m_loginthread.m_strUsername = strUsername;

         System.crypto().file_get(strPathPasshash, strPasshash, calc_key_hash(), get_app());

         if(strUsername.is_empty() || strPasshash.is_empty())
            return true;

         m_pviewAuth->KillTimer(1984);
         m_loginthread.m_strPassword.Empty();
         m_loginthread.m_strPasshash = strPasshash;
         m_loginthread.m_pcallback = this;
         m_loginthread.begin();

         return true;
      }
      return false;
   }
   */

   void validate::authentication_failed(::fontopus::e_result iAuth, const char * pszResponse)
   {

      UNREFERENCED_PARAMETER(pszResponse);

      property_set propertyset;

      string strUsername = m_loginthread.m_strUsername;

      m_bLicense = false;
      m_puser = NULL;

/*      if(m_pdocAuth != NULL)
      {

         m_pdocAuth->get_html_data()->m_puser = NULL;

      }*/

      if(m_strLicense.has_char())
      {
         if(m_bInteractive)
         {
            string strUrl;
            strUrl = "http://api.ca2.cc/spaignition/query?node=install_application&id=";
            strUrl += m_strLicense;
            strUrl += "&key=launch_name";

            property_set set(get_app());

            string strName = Application.http().get(strUrl, set);

            if(strName.is_empty())
               strName = m_strLicense;
            propertyset["project"] = strName;
            strUrl = "ext://https://"+ m_loginthread.m_strFontopusServer + "/license?id="+ m_strLicense + "&lang=" + System.get_locale() + "&sessid=" + ApplicationUser.get_sessid(m_loginthread.m_strFontopusServer);
            propertyset["contribute_link"] = strUrl;
            pageMessage("err\\user\\authentication\\not_licensed.xhtml", propertyset);
         }
      }
      else if(iAuth == ::fontopus::result_please_finish_registration)
      {
         if(m_bInteractive)
         {
            stringa stra;
            stra.add("err\\user\\authentication\\please_finish_registration.html");
            stra.add("err\\user\\authentication\\registration_deferred.html");
            pageMessage(stra, propertyset);
         }
      }
      else if(iAuth == ::fontopus::result_wrong_password_or_login)
      {
         if(m_bInteractive)
         {
            propertyset["register_link"] = "ext://http://"+ m_loginthread.m_strFontopusServer + "/register?email="+ System.url().url_encode(m_loginthread.m_strUsername);
            pageMessage("err\\user\\authentication\\wrong_fontopus_login.html", propertyset);
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
            m_loginthread.m_strModHash.Empty();
            m_loginthread.m_strKeyHash.Empty();
            m_loginthread.m_strCa2Hash.Empty();
         }
      }
      else if(iAuth == ::fontopus::result_time_out)
      {
         if(m_bInteractive)
         {
            propertyset["server"] = "account.ca2.cc";
            pageMessage("err\\user\\network\\connection_timed_out.html", propertyset);
         }
      }
      else if(iAuth == ::fontopus::result_registration_deferred)
      {
         if(m_bInteractive)
         {
            propertyset["server"] = "account.ca2.cc";
            propertyset["email"] = strUsername;
            pageMessage("err\\user\\authentication\\registration_deferred.html", propertyset);
         }
      }
      else if(iAuth == ::fontopus::result_no_login)
      {
         if(m_bInteractive)
         {
            pageMessage("err\\user\\authentication\\no_login.html", propertyset);
         }
      }
      else if(iAuth == ::fontopus::result_no_password)
      {
         if(m_bInteractive)
         {
            pageMessage("err\\user\\authentication\\no_password.html", propertyset);
         }
      }
      else
      {
         if(m_bInteractive)
         {
            pageMessage("err\\user\\authentication\\failed.html", propertyset);
         }
      }

      delete m_pauth;

   }

   void validate::authentication_succeeded()
   {

      save_authentication_info();

      /*if(m_ptabview != NULL)
      {
         m_ptabview->get_wnd()->EndAllModalLoops(IDOK);
      }*/

   }

   validate::auth * validate::get_auth()
   {
      sp(::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible = true;
/*      sp(::form_document) pdoc = (m_ptemplatePane->open_document_file(createcontext));
      sp(userex::pane_tab_view) pview = pdoc->get_typed_view < userex::pane_tab_view > ();
      pview->set_view_creator(this);
      rect rectOpen;
      System.get_screen_rect(rectOpen);
      int32_t iWidth = rectOpen.width();
      int32_t iHeight = rectOpen.width();
      rectOpen.deflate(iWidth / 5, iHeight / 5);

      m_ptabview->GetParentFrame()->SetWindowPos(ZORDER_TOP, rectOpen.left,
         rectOpen.top,
         rectOpen.width(), rectOpen.height(), SWP_SHOWWINDOW);
      m_ptabview = pview;
      pview->add_tab("login", 1);
      pview->set_cur_tab_by_id(1);
      pview->GetParentFrame()->RedrawWindow();
      ::core::live_signal livesignal;
      livesignal.keep(get_app()->m_pplaneapp);
      pview->GetTopLevelFrame()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE, &livesignal);
      return m_pauth;*/
      return NULL;
   }


     string validate::calc_ca2_hash()
      {
         if(m_loginthread.m_strCa2Hash.has_char())
            return m_loginthread.m_strCa2Hash;
         /*stringa straHash;
         stringa straSource;
         get_mod(straHash, straSource);
         straHash.insert_at(0, m_loginthread.m_strUsername);
   #if !core_level_1 && !core_level_2
         ::SetDllDirectoryA(System.get_ca2_module_folder());
   #endif*/
         /*HMODULE hmoduleSalt = ::LoadLibraryA("salt.dll");
         SALT salt = (SALT) ::GetProcAddress(hmoduleSalt, "salt");
         m_loginthread.m_strCa2Hash = salt(get_app(), straHash.implode(";"), straSource);*/
         m_loginthread.m_strCa2Hash = "ca2_12n";
         return m_loginthread.m_strCa2Hash;
      }


} // namespace fontopus

