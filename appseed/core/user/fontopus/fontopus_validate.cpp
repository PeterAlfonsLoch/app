#include "framework.h"


#ifdef BSD_STYLE_SOCKETS

#include <openssl/rsa.h>
#include <openssl/engine.h>
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

typedef string ( *SALT)(sp(base_application), const char * , stringa &);

namespace fontopus
{

   validate::validate(sp(base_application) papp, const char * pszForm, bool bAuth, bool bInteractive) :
      element(papp),
      m_loginthread(papp),
      m_netcfg(papp)
   {
      m_bInteractive          = bInteractive;
      m_bAuth          = bAuth;
      m_strForm               = pszForm;
      m_bDeferRegistration    = false;
      sp(base_application) pgenapp = (papp);
      if(pgenapp != NULL)
      {
         try
         {
            pgenapp->m_pplaneapp->keep_alive();
         }
         catch(...)
         {
         }
      }
      //Sleep(15 * 1000);
      m_ptemplatePane   = new ::user::single_document_template(
         papp,
         "system/auth",
         System.type_info < form_document > (),
         System.type_info < simple_main_frame > (),
         System.type_info < userex::pane_tab_view > ());
      m_pauth           = NULL;
      m_pviewAuth       = NULL;
      m_pdocAuth        = NULL;
      m_pdoc            = NULL;
      m_ptabview        = NULL;
      m_pvOldWindow     = NULL;
      m_bInteractive    = bInteractive;
      m_bAuth    = bAuth;
      m_strForm         = pszForm;
      m_puser           = NULL;
      m_pauth           = NULL;
   }

   validate::~validate()
   {
      //m_loginthread.wait();
#if defined(LINUX) || defined(MACOS)
      //((HTHREAD) m_loginthread.get_os_data())->wait();
#else
      ::WaitForSingleObjectEx((HANDLE) m_loginthread.get_os_data(), INFINITE, FALSE);
#endif
   }

   ::fontopus::user * validate::get_user(const char * pszRequestingParty, const char * pszSessId)
   {
      m_loginthread.m_strSalt.Empty();
      if(command_thread()->property("app") == "simpledbcfg"
         || (command_thread()->property("app") == "core_netnodelite" && command_thread()->property("root_handler") == "webserver")
         || (command_thread()->property("app") == "core_netnodelite")
         || command_thread()->property("app") == "veievserver"
         || command_thread()->property("app") == "simpledbcfg"
         //|| command_thread()->property("app") == "veriwell_mplite"      // churrasco 2011 m_strLicense
         || command_thread()->property("app") == "app-core/netnodecfg"
         || command_thread()->property("app") == "app-core/netnode_dynamic_web_server"
         || command_thread()->property("app") == "app-core/netnode_dynamic_web_server_cfg"
		   || command_thread()->property("app") == "app-gtech/alarm"
         || command_thread()->property("app") == "app-gtech/sensible_service")
      {
         m_puser = Application.m_pfontopus->allocate_user();
         m_puser->m_strPathPrefix = "system" + ::str::has_char(Application.command()->m_varTopicQuery["systemid"], "-");
         m_puser->m_strLogin = system_user_1;
         return m_puser;
      }
      else if(command_thread()->property("app") == "app-core/mydns"
         || command_thread()->has_property("install")
         || command_thread()->has_property("uninstall"))
      {
         m_puser = Application.m_pfontopus->allocate_user();
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
         m_puser = Application.m_pfontopus->allocate_user();
         m_puser->m_strPathPrefix = "system" + ::str::has_char(Application.command()->m_varTopicQuery["systemid"], "-");
         m_puser->m_strLogin = system_user_2;
         return m_puser;
      }
      string strDir;
      string strUsername;
      string strPasshash;
      //System.crypt().file_get(Application.dir().usersystemappdata(Application.dir().default_os_user_path_prefix(), "license_auth", "00001.data"), strUsername, "", get_app());
      crypt_file_get(::dir::userappdata("license_auth/00001.data"), strUsername, "");
      m_loginthread.m_strUsername = strUsername;
      string strHost(pszRequestingParty);

      stringa straRequestingServer;
      straRequestingServer.add("account.ca2.cc");
      straRequestingServer.add("eu-account.ca2.cc");
      straRequestingServer.add("asia-account.ca2.cc");
      if(strHost.is_empty())
      {
         if(::get_thread() != NULL && ::get_thread()->m_pthread->m_strWorkUrl.has_char())
         {
            strHost = ::get_thread()->m_pthread->m_strWorkUrl;
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
         m_loginthread.m_puser = Application.m_pfontopus->allocate_user();
         m_loginthread.m_puser->m_sessionidmap[Application.command_thread()->m_varTopicQuery["fontopus"].get_string()] = Application.command_thread()->m_varTopicQuery["sessid"].get_string();
         m_loginthread.m_puser->m_sessionidmap[strHost] = Application.command_thread()->m_varTopicQuery["sessid"].get_string();
         m_loginthread.m_puser->m_strFontopusServerSessId = Application.command_thread()->m_varTopicQuery["sessid"].get_string();
         m_loginthread.m_puser->m_strRequestingServer = strHost;
         xml::document documentBasicInfo(get_app());

         string strApiServer;

         strApiServer = Application.command_thread()->m_varTopicQuery["fontopus"];

         strApiServer.replace("account", "api");

         if(documentBasicInfo.load(Application.http().get("https://" + strApiServer + "/account/get_basic_info", m_loginthread.m_puser)))
         {
            string strLogin;
            if(documentBasicInfo.get_root()->get_attr("login", strLogin) && strLogin.find("@") > 0)
            {
               m_loginthread.m_puser->m_strLogin = strLogin;
               return  m_loginthread.m_puser;
            }
         }
      }

      m_loginthread.m_puser = Application.m_pfontopus->allocate_user();

      if(pszSessId != NULL && string(pszSessId).get_length() > 16)
      {
         m_loginthread.m_puser->m_sessionidmap[strHost] = pszSessId;
      }

      m_loginthread.m_strRequestingServer = strHost;
      crypt_file_get(::dir::userappdata("license_auth/00002.data"), strPasshash, calc_key_hash());
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
         ensure_main_document();
         page1();
         show_and_request_auth();
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
         || (strLicense == "core_netnodelite" && command_thread()->property("root_handler") == "webserver")
         || (strLicense == "core_netnodelite")
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
		   || strLicense == "app-gtech/alarm"
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
      straRequestingServer.add("eu-account.ca2.cc");
      straRequestingServer.add("asia-account.ca2.cc");
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

      property_set post;
      property_set headers;
      property_set set;

      string strAuth;
      post["entered_license"] = m_strLicense;
      //m_puser->set_sessid(ApplicationUser.m_str, strAuthUrl);
      //      uint32_t dwTimeProfile1 = get_tick_count();

      post["entered_license"] = m_strLicense;

      Application.http().get(strAuthUrl, strAuth, post, headers, set);

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
      crypt_file_get(::dir::userappdata("license_auth/00001.data"), strUsername, "");
      m_loginthread.m_strUsername = strUsername;
      crypt_file_get(::dir::userappdata("license_auth/00002.data"), strPasshash, calc_key_hash());
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







   login_thread::login_thread(sp(base_application) papp) :
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
      m_loginthread.m_strModHash = System.crypt().md5(straHash.implode(";"));
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
      string strUrl("https://api.ca2.cc/account/check_hash");
      property_set post;
      property_set headers;
      property_set set;
      string strResponse;
      stringa straHash;
      stringa straSource;
      get_mod(straHash, straSource);
      straHash.insert_at(0, m_loginthread.m_strPasshash);
      straHash.insert_at(0, m_loginthread.m_strUsername);

      post["hash"] = straHash.implode(";");
      post["source"] = straHash.implode(";");
      for(int32_t i = 0; i < 3; i++)
      {
         if(Application.http().get(strUrl, strResponse, post, headers, set))
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
            System.m_authmap[m_strUsername].m_mapServer[m_strRequestingServer] = strResponse;
            System.m_authmap[m_strUsername].m_mapFontopus[m_strFontopusServer] = strResponse;
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
         straRequestingServer.add("eu-account.ca2.cc");
         straRequestingServer.add("asia-account.ca2.cc");
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

      if(System.m_authmap[m_strUsername].m_mapServer[m_strRequestingServer].get_length() > 32)
      {
         return System.m_authmap[m_strUsername].m_mapServer[m_strRequestingServer];
      }

      string strGetFontopus("http://" + m_strRequestingServer + "/get_fontopus");

      m_strFontopusServer.Empty();

      sp(base_application) papp = get_app();

      url_domain domainFontopus;

      m_strFontopusServer = System.get_fontopus_server(strGetFontopus, papp, 8);

      domainFontopus.create(m_strFontopusServer);

      if(domainFontopus.m_strRadix != "ca2")
         return "";

      if(System.m_authmap[m_strUsername].m_mapFontopus[m_strFontopusServer].get_length() > 32)
      {
         return System.m_authmap[m_strUsername].m_mapFontopus[m_strFontopusServer];
      }




      string strLogin;

      string strApiServer;

      strApiServer = m_strFontopusServer;

      strApiServer.replace("account", "api");

      m_strLoginUrl = "https://" + strApiServer + "/account/login";

      xml::document doc(get_app());

      string strSessId;

      string strRsaModulus;

      for(int32_t iRetry = 0; iRetry <= 8; iRetry++)
      {

         if(iRetry > 0)
         {
            Sleep(iRetry * 584);
         }

         try
         {


            property_set post;
            property_set headers;
            property_set set;

            //Sleep(15 * 1000);

            string strSessid = System.url().get_param(System.directrix()->m_varTopicQuery["ruri"], "sessid");

            if(strSessid.has_char())
            {
               m_puser->set_sessid(strSessid, m_strLoginUrl);
            }
            else if(m_puser->m_sessionidmap[m_strRequestingServer].get_length() > 16)
            {
               m_puser->set_sessid(m_puser->m_sessionidmap[m_strRequestingServer], m_strLoginUrl);
            }
            else
            {
               m_puser->set_sessid("not_auth", m_strLoginUrl);
            }

            set["app"] = papp;

            Application.http().get(m_strLoginUrl, strLogin, post, headers, set, m_puser->m_phttpcookies, m_puser, NULL, pestatus);

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


      string strPass;
      if(m_strPasshash.is_empty())
      {
         strPass = System.crypt().nessie(m_strPassword);
      }
      else
      {
         strPass = m_strPasshash;
      }

#ifdef MACOS_DEPRECATED

      CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

      CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeRSA);

      // not needed, defaults to true    CFDictionaryAddValue(parameters, kSecAttrCanEncrypt, kCFBooleanTrue);

      primitive::memory memKeyData;

      memKeyData.from_hex(strPass);

      CFDataRef keyData = memKeyData.get_os_cf_data();

      CFErrorRef error = NULL;

      SecKeyRef key = SecKeyCreateFromData(parameters, keyData, &error);

      if(error != NULL)
      {

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(error);

         return "";

      }

      SecTransformRef transform = SecEncryptTransformCreate(key, &error);

      if(error != NULL)
      {

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(key);

         CFRelease(error);

         return "";

      }

      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

      if(error != NULL)
      {

         CFRelease(transform);

         CFRelease(keyData);

         CFRelease(parameters);

         CFRelease(key);

         CFRelease(error);

         return "";

      }

      primitive::memory memDataIn;

      memDataIn.from_hex(strRsaModulus);

      CFDataRef dataIn = memDataIn.get_os_cf_data();

      SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);

      if(error != NULL)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(key);

         CFRelease(error);

         return "";

      }

      /* Encrypt the data. */

      CFDataRef data = (CFDataRef) SecTransformExecute(transform, &error);

      if(error != NULL)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(key);

         CFRelease(error);

         return "";

      }


      string strHex;

      primitive::memory memory;

      memory.set_os_cf_data(data);

      memory.to_hex(strHex);

      CFRelease(data);

      CFRelease(dataIn);

      CFRelease(transform);

      CFRelease(keyData);

      CFRelease(parameters);

      CFRelease(key);

#elif defined(METROWIN)


      typedef struct _BCRYPT_RSAKEY_BLOB {
         ULONG Magic;
         ULONG BitLength;
         ULONG cbPublicExp;
         ULONG cbModulus;
         ULONG cbPrime1;
         ULONG cbPrime2;
      } BCRYPT_RSAKEY_BLOB;

      BCRYPT_RSAKEY_BLOB blob;

      ::file::memory_buffer memfile(get_app());

      blob.Magic = 0x31415352; // BCRYPT_RSAPUBLIC_MAGIC;
      blob.BitLength = 1024;
      blob.cbPublicExp = 3;
      blob.cbModulus = 1024 / 8;
      blob.cbPrime1 = 0;
      blob.cbPrime2 = 0;

      primitive::memory memVer(get_app());

      memVer.from_hex("00");

      memVer.prefix_der_uint();

      memfile.write(&blob, sizeof(blob));

      primitive::memory memMod(get_app());

      memMod.from_hex(strRsaModulus);

      //memMod.reverse();



      //memMod.prefix_der_uint();

      primitive::memory memExp(get_app());

      memExp.from_hex("10001");

      //memExp.reverse();

      memfile.write(memExp.get_data(), memExp.get_size());

      memfile.write(memMod.get_data(), memMod.get_size());

      //memExp.prefix_der_uint();

      ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider ^ cipher =
         ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider::OpenAlgorithm(::Windows::Security::Cryptography::Core::AsymmetricAlgorithmNames::RsaPkcs1);


      primitive::memory memKey(get_app());

      //memKey = memVer;
      //memKey += memMod;
      memKey = memMod;
      memKey += memExp;


      memKey.prefix_der_sequence();

      //      string strRsaPrivateKey = "-----BEGIN RSA PRIVATE KEY-----\r\n";
      //    strRsaPrivateKey += chunk_split(System.base64().encode(memKey));
      //  strRsaPrivateKey += "-----END RSA PRIVATE KEY-----";

      //memKey.allocate(strRsaPrivateKey.get_length());

      //memcpy(memKey.get_data(), strRsaPrivateKey, memKey.get_size());

      ::Windows::Security::Cryptography::Core::CryptographicKey ^ cipherkey = cipher->ImportPublicKey(memfile.get_memory()->get_os_crypt_buffer(), ::Windows::Security::Cryptography::Core::CryptographicPublicKeyBlobType::BCryptPublicKey);

      primitive::memory memIn;

      Application.hex_to_memory(memIn, strPass);

      primitive::memory memory;

      memory.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Encrypt(cipherkey, memIn.get_os_crypt_buffer(), nullptr));

      string strHex;
      Application.memory_to_hex(strHex, memory);

#else

      RSA * rsa = RSA_new();

      BN_hex2bn(&rsa->n, strRsaModulus);
      BN_hex2bn(&rsa->e, "10001");


      primitive::memory memory;
      primitive::memory memIn;

      Application.hex_to_memory(memIn, strPass);

      memory.allocate(2048);

      int32_t i = RSA_public_encrypt((int32_t) memIn.get_size(), (const uchar * ) (const char *) memIn.get_data(), memory.get_data(), rsa, RSA_PKCS1_PADDING);

      const char * psz = ERR_error_string(ERR_get_error(), NULL);

      TRACE(psz);

      memory.allocate(i);

      string strHex;
      Application.memory_to_hex(strHex, memory);

      RSA_free(rsa);

#endif

      m_puser->m_strLogin = m_strUsername;

      string strAuth;

      {

         string strAuthUrl("https://" + strApiServer + "/account/auth?" + m_pcallback->oprop("defer_registration").get_string()
            +"&ruri=" + System.url().url_encode((m_pcallback->oprop("ruri").get_string())));

         property_set post;
         property_set headers;
         property_set set;

         if(m_strPasshash.is_empty())
         {
            post["entered_password"] = strHex;
         }
         else
         {
            post["entered_passhash"] = strHex;
         }
         string strCrypt;

         string strUsername = m_strUsername;

         post["entered_login"] = m_strUsername;
         if(m_strLicense.has_char())
         {
            post["entered_license"] = m_strLicense;
         }

         m_puser->set_sessid(strSessId, strAuthUrl);
         set["app"] = papp;
         uint32_t dwTimeProfile1 = get_tick_count();
         Application.http().get(strAuthUrl, strAuth, post, headers, set, m_puser->m_phttpcookies, m_puser, NULL, pestatus);
         uint32_t dwTimeProfile2 = get_tick_count();

         TRACE0("login_thread::NetLogin Total time Application.http().get(\"" + strAuthUrl + "\") : " + ::str::from(dwTimeProfile2 - dwTimeProfile1));

      }

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
         System.http().download(
            m_httpexecutea[i].m_strUrl,
            strFilename,
            m_httpexecutea[i].m_propertysetPost,
            m_httpexecutea[i].m_propertysetHeaders,
            set,
            m_puser->m_phttpcookies,
            m_puser);
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
      crypt_file_get(::dir::userappdata("license_auth/00001.data"), strUsernamePrevious, "");
      crypt_file_get(::dir::userappdata("license_auth/00002.data"), strPasshashPrevious, calc_key_hash());

      if((strUsername.has_char() && strPasshash.has_char())
         && (strUsernamePrevious != strUsername || strPasshashPrevious != strPasshash))
      {
         crypt_file_set(::dir::userappdata("license_auth/00001.data"), strUsername, "");
         crypt_file_set(::dir::userappdata("license_auth/00002.data"), strPasshash, calc_key_hash());
         if(strPassword.has_char())
         {
            string strSalt = System.crypt().v5_get_password_salt();
            crypt_file_set(::dir::userappdata("license_auth/00005.data"), strSalt, calc_key_hash());
            string strPasshash2 = System.crypt().v5_get_password_hash(strSalt, strPassword);
            crypt_file_set(::dir::userappdata("license_auth/00010.data"), strPasshash2, calc_key_hash());
         }
      }
      if(m_loginthread.m_strLicense.has_char())
      {
         stringa straLicense;
         straLicense.add(m_loginthread.m_strValidUntil);
         straLicense.add(System.datetime().international().get_gmt_date_time());
         crypt_file_set(::dir::userappdata("license_auth/" + m_loginthread.m_strLicense + ".data"), straLicense.implode(";"), calc_ca2_hash());
      }
      m_bLicense = true;
      m_puser = m_loginthread.m_puser;
   }


   void validate::close_all()
   {

      if(m_ptabview != NULL)
      {
         m_ptabview->get_wnd()->EndAllModalLoops(IDOK);
      }

      if(m_ptemplatePane != NULL)
      {
         m_ptemplatePane->close_all_documents(FALSE);
      }

   }


   bool validate::get_defer_registration()
   {

      return m_bDeferRegistration;

   }



   void validate::show_and_request_auth()
   {

      if(m_loginthread.m_strLicense.is_empty())
      {
         m_pviewAuth->SetTimer(1984, 484, NULL);
      }
      ::core::live_signal livesignal;
      livesignal.keep(get_app()->m_pplaneapp);
      m_ptabview->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE, &livesignal);
      m_ptemplatePane->close_all_documents(FALSE);

   }



   void validate::ensure_main_document()
   {

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

   }

   void validate::page1(const stringa & straMatter)
   {

      m_pdocAuth->get_html_data()->m_puser = m_loginthread.m_puser;

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

         sp(::user::interaction) pguie = m_pviewAuth->get_child_by_name("user");
         sp(text_interface) ptext =  (pguie.m_p);
         if(ptext != NULL)
         {
            ptext->_001SetText(m_loginthread.m_strUsername);
            if(m_loginthread.m_strUsername.is_empty())
               Application.user()->set_keyboard_focus(pguie);
            else
            {
               pguie = m_pviewAuth->get_child_by_name("password");
               Application.user()->set_keyboard_focus(pguie);
            }
         }

      }

   }

   void validate::display_main_frame()
   {

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
      int_ptr ui2 = m_ptabview->GetTopLevelFrame()->m_pthread->m_pthread->get_os_int();
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
      {
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
      if(m_ptabview->GetTopLevelFrame()->SetForegroundWindow())
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

   }

   void validate::pageMessage(const stringa & straMatter, property_set & set)
   {
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
   }

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
   void validate::on_show_view()
   {
      switch(m_ptabview->get_view_id())
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
      }
   }










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
               sp(::user::interaction) pguie = m_pviewAuth->get_child_by_name("user");
               sp(text_interface) ptext =  (pguie.m_p);
               //m_loginthread.m_puser = dynamic_cast < ::fontopus::user * > (System.allocate_user());
               ptext->_001GetText(m_loginthread.m_strUsername);
               pguie = m_pviewAuth->get_child_by_name("password");
               ptext =  (pguie.m_p);
               ptext->_001GetText(m_loginthread.m_strPassword);
               m_loginthread.m_pcallback = this;
               m_loginthread.begin();
            }
            else
            {
               m_pauth = new auth;
               sp(::user::interaction) pguie = m_pviewAuth->get_child_by_name("user");
               sp(text_interface) ptext =  (pguie.m_p);
               ptext->_001GetText(m_pauth->m_strUsername);
               pguie = m_pviewAuth->get_child_by_name("password");
               ptext =  (pguie.m_p);
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

         System.crypt().file_get(strPathUsername, strUsername, "", get_app());
         m_loginthread.m_strUsername = strUsername;

         System.crypt().file_get(strPathPasshash, strPasshash, calc_key_hash(), get_app());

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

   void validate::authentication_failed(::fontopus::e_result iAuth, const char * pszResponse)
   {

      UNREFERENCED_PARAMETER(pszResponse);

      property_set propertyset;

      string strUsername = m_loginthread.m_strUsername;

      m_bLicense = false;
      m_puser = NULL;

      if(m_pdocAuth != NULL)
      {

         m_pdocAuth->get_html_data()->m_puser = NULL;

      }

      if(m_strLicense.has_char())
      {
         if(m_bInteractive)
         {
            string strUrl;
            strUrl = "http://api.ca2.cc/spaignition/query?node=install_application&id=";
            strUrl += m_strLicense;
            strUrl += "&key=launch_name";
            string strName = Application.http().get(strUrl);
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

      if(m_ptabview != NULL)
      {
         m_ptabview->get_wnd()->EndAllModalLoops(IDOK);
      }

   }

   validate::auth * validate::get_auth()
   {
      sp(::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible = true;
      sp(::form_document) pdoc = (m_ptemplatePane->open_document_file(createcontext));
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
      return m_pauth;
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

