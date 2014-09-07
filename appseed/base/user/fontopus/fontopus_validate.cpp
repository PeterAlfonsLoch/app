#include "framework.h" // from "base/net/net_sockets.h"


#ifdef BSD_STYLE_SOCKETS

#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/bn.h>
#include <openssl/err.h>

#endif

string chunk_split(const string & body,int32_t chunklen = 76,const string & end = "\r\n");


string chunk_split(const string & body,int32_t chunklen,const string & end)
{

   strsize pos = 0;
   string strRet;
   strsize iRead;
   while(pos < body.get_length())
   {
      iRead = MIN(chunklen,body.get_length() - pos);
      strRet += body.Mid(pos,iRead);
      strRet += end;
      pos += iRead;
   }

   return strRet;

}

typedef string(*SALT)(sp(::aura::application),const char *,stringa &);

namespace fontopus
{

   validate::validate(sp(::aura::application) papp,const char * pszForm,bool bAuth,bool bInteractive):
      element(papp),
      m_loginthread(papp)
   {

      m_bInteractive          = bInteractive;
      if(bInteractive)
      {
         oprop("defer_registration") = "defer_registration";
      }

      m_bAuth          = bAuth;
      m_strForm               = pszForm;
      m_bDeferRegistration    = false;
      sp(::aura::application) pgenapp = (papp);
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
      ::WaitForSingleObjectEx((HANDLE)m_loginthread.get_os_data(),INFINITE,FALSE);
#endif
   }

   ::fontopus::user * validate::get_user(const char * pszRequestingParty,const char * pszSessId)
   {
      m_loginthread.m_strSalt.Empty();

      string strApp = command_thread()->property("app");
      if(strApp == "simpledbcfg"
         || (strApp == "app-core/netnodelite" && command_thread()->property("root_handler") == "webserver")
         || (strApp == "app-core/netnodelite")
         || strApp == "veievserver"
         || strApp == "simpledbcfg"
         //|| command_thread()->property("app") == "veriwell_mplite"      // churrasco 2011 m_strLicense
         || strApp == "app-core/netnodecfg"
         || strApp == "app-core/netnode_dynamic_web_server"
         || strApp == "app-core/netnode_dynamic_web_server_cfg"
         || strApp == "app-gtech/sensible_netnode"
         || strApp == "app-gtech/sensible_service")
      {
         m_puser = Session.fontopus()->allocate_user();
         m_puser->m_strPathPrefix = "system" + ::str::has_char(Application.command()->m_varTopicQuery["systemid"],"-");
         m_puser->m_strLogin = system_user_1;
         return m_puser;
      }
      else if(command_thread()->property("app") == "app-core/mydns"
         || command_thread()->has_property("install")
         || command_thread()->has_property("uninstall"))
      {
         m_puser = Session.fontopus()->allocate_user();
         m_puser->m_strPathPrefix = "system" + ::str::has_char(Application.command()->m_varTopicQuery["systemid"],"-");
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
         m_puser->m_strPathPrefix = "system" + ::str::has_char(Application.command()->m_varTopicQuery["systemid"],"-");
         m_puser->m_strLogin = system_user_2;
         return m_puser;
      }
      string strDir;
      string strUsername;
      string strPasshash;
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

         strApiServer.replace("account","api");

         property_set set(get_app());

         set["user"] = m_loginthread.m_puser;

         if(documentBasicInfo.load(Application.http().get("https://" + strApiServer + "/account/get_basic_info",set)))
         {
            string strLogin;
            if(documentBasicInfo.get_root()->get_attr("login",strLogin) && strLogin.find("@") > 0)
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

      string strPassword;

      string strResult = Application.get_cred(null_rect(),strUsername,strPassword,"ca2","ca2",m_bInteractive);

      if(strResult != "ok")
      {

         ::aura::del(m_puser);

         if(strResult == "cancel")
         {

            throw cancel_exception(get_app(),"User canceled login.");

         }

         return NULL;

      }

      if(strUsername.has_char() && strPassword.has_char())
      {

         m_loginthread.m_strUsername = strUsername;
         m_loginthread.m_strPassword = strPassword;
         m_loginthread.m_strPasshash.Empty();
         m_loginthread.m_pcallback = this;
         m_loginthread.run();

         if(m_puser != NULL)
         {

            ::fontopus::set_cred(get_app(),"ca2",strUsername,strPassword);
            ::fontopus::set_cred_ok(get_app(),"ca2",true);

         }
         else
         {
            ::fontopus::set_cred(get_app(),"ca2","","");
            ::fontopus::set_cred_ok(get_app(),"ca2",false);
         }

         return m_puser;

      }
      else
      {

         return NULL;

      }

   }


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
      if(System.url().get_server(strHost).has_char())
      {
         strHost = System.url().get_server(strHost);
      }
      else
      {
         strHost = "account.ca2.cc";
      }

      strHost = Session.fontopus()->get_server(strHost);

      if(straRequestingServer.contains(Application.command_thread()->m_varTopicQuery["fontopus"].get_string())
         && Application.command_thread()->m_varTopicQuery["sessid"].get_string().get_length() > 16)
      {
         strHost = Application.command_thread()->m_varTopicQuery["fontopus"].get_string();
      }

      string strAuthUrl;

      string strApiHost = strHost;

      strApiHost.replace("account","api");

      strAuthUrl = "https://" + strApiHost + "/account/license";

      property_set set;

      string strAuth;
      set["post"]["entered_license"] = m_strLicense;
      //m_puser->set_sessid(ApplicationUser.m_str, strAuthUrl);
      //      uint32_t dwTimeProfile1 = get_tick_count();

      set["post"]["entered_license"] = m_strLicense;

      Application.http().get(strAuthUrl,strAuth,set);

      m_loginthread.m_strFontopusServer = strHost;

      xml::document doc(get_app());
      doc.load(strAuth);
      if(doc.get_root()->get_name() == "response")
      {
         if(doc.get_root()->attr("id") == ApplicationUser.get_session_secret())
         {
            return true;
         }
      }

      if(m_bInteractive)
      {

#ifdef WINDOWS

         if(get_splash() != NULL)
         {

            ::KillTimer(get_splash(),123);

         }

#endif // WINDOWS

         {

            ::PostMessage(get_splash(),WM_CLOSE,0,0);

         }

         ::simple_message_box(NULL,"No license to use the application/feature \"" + string(psz) + "\" for the user \"" + ApplicationUser.m_strLogin + "\". Contact your system administrator.",psz,MB_ICONEXCLAMATION);


         return false;


         m_loginthread.m_strModHash.Empty();
         m_loginthread.m_strKeyHash.Empty();
         m_loginthread.m_strCa2Hash.Empty();
         return m_bLicense;

      }

      return false;

   }







   login_thread::login_thread(sp(::aura::application) papp):
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

   void validate::get_mod(stringa & straHash,stringa & straSource)
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

      get_mod(straHash,straSource);

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
      get_mod(straHash,straSource);
      straHash.insert_at(0,m_loginthread.m_strPasshash);
      straHash.insert_at(0,m_loginthread.m_strUsername);

      set["post"]["hash"] = straHash.implode(";");
      set["post"]["source"] = straHash.implode(";");
      for(int32_t i = 0; i < 3; i++)
      {
         if(Application.http().get(strUrl,strResponse,set))
            break;
      }
      if(strResponse == "OK")
         return true;
      else
         return false;
   }

   void validate::on_login_response(e_result iAuth,const char * pszResponse)
   {
      if(iAuth == result_auth)
      {
         authentication_succeeded();
      }
      else
      {
         authentication_failed(iAuth,pszResponse);
      }
   }

   void login_callback::on_login_response(e_result iAuth,const char * pszResponse)
   {
      UNREFERENCED_PARAMETER(iAuth);
      UNREFERENCED_PARAMETER(pszResponse);
   }

   string login_callback::calc_mod_hash()
   {
      return "";
   }

   string login_callback::calc_key_hash()
   {
      return "";
   }

   string login_callback::calc_ca2_hash()
   {
      return "";
   }


   bool login_callback::get_defer_registration()
   {
      return true;
   }

   int32_t login_thread::run()
   {
      
      ::http::e_status estatus;
      
      string strResponse = Login(&estatus);

      if(m_pcallback == NULL)
         return 2;

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
            m_puser->set_sessid(m_puser->m_strFontopusServerSessId,m_strLoginUrl);
            m_puser->m_strRequestingServer = m_strRequestingServer;
            m_puser->m_strFunUserId = doc.get_root()->attr("secureuserid");
            m_strPasshash = doc.get_root()->attr("passhash");
            iAuth = result_auth;
            if(m_bFontopusServer)
            {
               Application.file().put_contents(System.dir().appdata("database\\text\\last_good_known_fontopus_com.txt"),m_strFontopusServer);
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
      m_pcallback->on_login_response(iAuth,strResponse);
      
      return 0;

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
            straRequestingServer.insert_at(0,m_strRequestingServer);
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

      string strFontopusServer = Session.fontopus()->get_fontopus_server(m_strRequestingServer);

      if(strFontopusServer.is_empty())
         return "";

      m_strFontopusServer = strFontopusServer;

      if(Session.fontopus()->m_strFirstFontopusServer.is_empty())
      {

         Session.fontopus()->m_strFirstFontopusServer = m_strFontopusServer;

      }

      if(Session.fontopus()->m_authmap[m_strUsername].m_mapFontopus[m_strFontopusServer].get_length() > 32)
      {
         return Session.fontopus()->m_authmap[m_strUsername].m_mapFontopus[m_strFontopusServer];
      }



      string strLogin;

      string strApiServer;

      strApiServer = m_strFontopusServer;

      strApiServer.replace("account","api");

      m_strLoginUrl = "https://" + strApiServer + "/account/login";

      xml::document doc(get_app());

      string strSessId;

      string strRsaModulus;

      DWORD dwGetLoginBeg = ::get_tick_count();
      property_set set;


      set["app"] = get_app();

      sp(::sockets::http_session) psession = Session.fontopus()->m_mapFontopusSession[m_strFontopusServer];

      for(int32_t iRetry = 0; iRetry <= 8; iRetry++)
      {

         if(iRetry > 0)
         {
            Sleep(iRetry * 584);
         }

         try
         {

            set["get_response"] = "";

            set["raw_http"] = true;

            psession = System.http().request(psession,m_strLoginUrl,set);

            Session.fontopus()->m_mapFontopusSession.set_at(m_strFontopusServer,psession);

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

      DWORD dwGetLoginEnd = ::get_tick_count();

      TRACE("NetLogin: Get Login Millis = %d",dwGetLoginEnd - dwGetLoginBeg);

      string strPass;
      if(m_strPasshash.is_empty())
      {
         strPass = m_strPassword;
      }
      else
      {
         strPass = m_strPasshash;
      }

      string strHex = System.crypto().spa_login_crypt(strPass,strRsaModulus);

      string strSec = System.crypto().spa_login_crypt(m_puser == NULL ? string() : m_puser->m_strSessionSecret,strRsaModulus);

      if(m_puser != NULL)
      {

         m_puser->m_strLogin = m_strUsername;

      }

      string strAuth;

      DWORD dwAuthBeg = ::get_tick_count();
      {

         string strAuthUrl("https://" + strApiServer + "/account/auth?" + (m_pcallback == NULL ? string() : m_pcallback->oprop("defer_registration").get_string())
            + (m_pcallback == NULL ? string() : "&ruri=" + System.url().url_encode((m_pcallback->oprop("ruri").get_string()))));

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

         set["post"]["session_secret"] = strSec;

         string strUsername = m_strUsername;

         set["post"]["entered_login"] = m_strUsername;
         if(m_strLicense.has_char())
         {
            set["post"]["entered_license"] = m_strLicense;
         }

         if(m_puser != NULL)
         {

            m_puser->set_sessid(strSessId,strAuthUrl);
            m_puser->set_sessid(strSessId,strFontopusServer);

         }

         set["app"] = get_app();
         set["user"] = m_puser;
         if(m_puser != NULL)
         {
            set["cookies"] = m_puser->m_phttpcookies;
         }
         set["get_response"] = "";
         uint32_t dwTimeProfile1 = get_tick_count();
         psession = System.http().request(psession,strAuthUrl,set);

         strAuth = set["get_response"];

         *pestatus = (::http::e_status) set["get_status"].int64();
         uint32_t dwTimeProfile2 = get_tick_count();

         TRACE0("login_thread::NetLogin Total time Application.http().get(\"" + strAuthUrl + "\") : " + ::str::from(dwTimeProfile2 - dwTimeProfile1));

      }
      DWORD dwAuthEnd = ::get_tick_count();

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

         System.http().download(m_httpexecutea[i].m_strUrl,strFilename,set);

         strResponse = Application.file().as_string(strFilename);
         TRACE0(strResponse);
         m_httpexecutea[i].m_strResponse = strResponse;
      }
   }



   void validate::save_authentication_info()
   {
      TRACE0("The authentication has succeeded.");
      string strUsername = m_loginthread.m_strUsername;
      string strPasshash = m_loginthread.m_strPasshash;
      string strPassword = m_loginthread.m_strPassword;

      string strUsernamePrevious;
      string strPasshashPrevious;
      crypto_file_get(::dir::userappdata("license_auth/00001.data"),strUsernamePrevious,"");
      crypto_file_get(::dir::userappdata("license_auth/00002.data"),strPasshashPrevious,calc_key_hash());

      if((strUsername.has_char() && strPasshash.has_char())
         && (strUsernamePrevious != strUsername || strPasshashPrevious != strPasshash))
      {
         crypto_file_set(::dir::userappdata("license_auth/00001.data"),strUsername,"");
         crypto_file_set(::dir::userappdata("license_auth/00002.data"),strPasshash,calc_key_hash());
         if(strPassword.has_char())
         {
            string strSalt = System.crypto().v5_get_password_salt();
            crypto_file_set(::dir::userappdata("license_auth/00005.data"),strSalt,calc_key_hash());
            string strPasshash2 = System.crypto().v5_get_password_hash(strSalt,strPassword);
            crypto_file_set(::dir::userappdata("license_auth/00010.data"),strPasshash2,calc_key_hash());
         }
      }
      if(m_loginthread.m_strLicense.has_char())
      {
         stringa straLicense;
         straLicense.add(m_loginthread.m_strValidUntil);
         straLicense.add(System.datetime().international().get_gmt_date_time());
         crypto_file_set(::dir::userappdata("license_auth/" + m_loginthread.m_strLicense + ".data"),straLicense.implode(";"),calc_ca2_hash());
      }
      m_bLicense = true;
      m_puser = m_loginthread.m_puser;
   }




   bool validate::get_defer_registration()
   {

      return m_bDeferRegistration;

   }




   void validate::authentication_failed(::fontopus::e_result iAuth,const char * pszResponse)
   {

      UNREFERENCED_PARAMETER(pszResponse);

      property_set propertyset;

      string strUsername = m_loginthread.m_strUsername;

      m_bLicense = false;
      m_puser = NULL;

      if(m_strLicense.has_char())
      {
         if(m_bInteractive)
         {
            string strUrl;
            strUrl = "http://api.ca2.cc/spaignition/query?node=install_application&id=";
            strUrl += m_strLicense;
            strUrl += "&key=launch_name";

            property_set set(get_app());

            string strName = Application.http().get(strUrl,set);

            if(strName.is_empty())
               strName = m_strLicense;
            propertyset["project"] = strName;
            strUrl = "ext://https://" + m_loginthread.m_strFontopusServer + "/license?id=" + m_strLicense + "&lang=" + Session.get_locale() + "&sessid=" + ApplicationUser.get_sessid(m_loginthread.m_strFontopusServer);
            propertyset["contribute_link"] = strUrl;
            pageMessage("err\\user\\authentication\\not_licensed.xhtml",propertyset);
         }
      }
      else if(iAuth == ::fontopus::result_please_finish_registration)
      {
         if(m_bInteractive)
         {
            stringa stra;
            stra.add("err\\user\\authentication\\please_finish_registration.html");
            stra.add("err\\user\\authentication\\registration_deferred.html");
            pageMessage(stra,propertyset);
         }
      }
      else if(iAuth == ::fontopus::result_wrong_password_or_login)
      {
         if(m_bInteractive)
         {
            propertyset["register_link"] = "ext://http://" + m_loginthread.m_strFontopusServer + "/register?email=" + System.url().url_encode(m_loginthread.m_strUsername);
            pageMessage("err\\user\\authentication\\wrong_fontopus_login.html",propertyset);
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
            pageMessage("err\\user\\network\\connection_timed_out.html",propertyset);
         }
      }
      else if(iAuth == ::fontopus::result_registration_deferred)
      {
         if(m_bInteractive)
         {
            propertyset["server"] = "account.ca2.cc";
            propertyset["email"] = strUsername;
            pageMessage("err\\user\\authentication\\registration_deferred.html",propertyset);
         }
      }
      else if(iAuth == ::fontopus::result_no_login)
      {
         if(m_bInteractive)
         {
            pageMessage("err\\user\\authentication\\no_login.html",propertyset);
         }
      }
      else if(iAuth == ::fontopus::result_no_password)
      {
         if(m_bInteractive)
         {
            pageMessage("err\\user\\authentication\\no_password.html",propertyset);
         }
      }
      else
      {
         if(m_bInteractive)
         {
            pageMessage("err\\user\\authentication\\failed.html",propertyset);
         }
      }

      delete m_pauth;

   }

   void validate::authentication_succeeded()
   {

      save_authentication_info();

   }

   validate::auth * validate::get_auth()
   {
      sp(::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible = true;
      return NULL;
   }


   string validate::calc_ca2_hash()
   {
      if(m_loginthread.m_strCa2Hash.has_char())
         return m_loginthread.m_strCa2Hash;
      m_loginthread.m_strCa2Hash = "ca2_12n";
      return m_loginthread.m_strCa2Hash;
   }

   void validate::pageMessage(stringa straMessage,::property_set set)
   {

      UNREFERENCED_PARAMETER(straMessage);
      UNREFERENCED_PARAMETER(set);


   }


} // namespace fontopus





