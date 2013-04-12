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

typedef string ( *SALT)(sp(::ca::application), const char * , stringa &);

namespace fontopus
{

   validate::validate(sp(::ca::application) papp, const char * pszForm, bool bAuth, bool bInteractive) :
      ca(papp),
      m_loginthread(papp),
      m_netcfg(papp)
   {
      m_bInteractive    = bInteractive;
      m_bAuth    = bAuth;
      m_strForm         = pszForm;
      m_puser           = ::null();
      sp(::ca::application) pgenapp = papp;
      if(pgenapp != ::null())
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
      m_pauth           = ::null();
   }

   validate::~validate()
   {
       //m_loginthread.wait();
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
      || command_thread()->property("app") == "app-core/netnodecfg")
      {
         m_puser = Application.m_pfontopus->allocate_user();
         m_puser->m_strPathPrefix = "system" + ::ca::str::has_char(Application.command()->m_varTopicQuery["systemid"], "-");
         m_puser->m_strLogin = system_user_1;
         return m_puser;
      }
      else if(command_thread()->property("app") == "app-core/mydns"
           || command_thread()->has_property("install")
           || command_thread()->has_property("uninstall"))
      {
         m_puser = Application.m_pfontopus->allocate_user();
         m_puser->m_strPathPrefix = "system" + ::ca::str::has_char(Application.command()->m_varTopicQuery["systemid"], "-");
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
         m_puser->m_strPathPrefix = "system" + ::ca::str::has_char(Application.command()->m_varTopicQuery["systemid"], "-");
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
         if(::ca::get_thread() != ::null() && ::ca::get_thread()->m_strWorkUrl.has_char())
         {
            strHost = ::ca::get_thread()->m_strWorkUrl;
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

      if(pszSessId != ::null() && string(pszSessId).get_length() > 16)
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

         return ::null();

      }

   }

   void validate::ensure_main_document()
   {
      sp(::ca::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible = false;
      createcontext->m_puiParent = Sys(get_app()).oprop("top_parent").ca < ::user::interaction > ();
      createcontext->m_bOuterPopupAlertLike = true;
   }

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
         || strLicense == "app-core/netnodecfg")
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

      ::ca::property_set post;
      ::ca::property_set headers;
      ::ca::property_set set;

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

   void validate::page1(const stringa & straMatter)
   {
//      m_pdocAuth->get_html_data()->m_puser = m_loginthread.m_puser;
      //string strUrl;
      //strUrl = "http://spaignition.api.server.ca2.cc/query?node=install_application&id=";
      //string strAppName;
      //if(System.m_strAppName == "winactionarea")
      //{
        // strAppName = "_set_windesk";
      //}
      //else
      //{
        // strAppName = System.m_strAppName;
      //}
      //strUrl += strAppName;
      //strUrl += "&key=name";
      //m_pdocAuth->get_html_data()->m_propertyset["application_name"] = System.http().get(strUrl);
      //if(m_strLicense.is_empty())
      //{
        // m_pdocAuth->get_html_data()->m_propertyset["reason"] = "Authenticating";
      //}
      //else
      //{
        // m_pdocAuth->get_html_data()->m_propertyset["reason"] = "Licensing";
      //}
/*      if(!m_pdocAuth->on_open_document(Application.dir().matter(m_strForm)))
      {
         authentication_failed(result_fail, "Cannot open form for authentication!!");
         return;
      }*/
      display_main_frame();
      //sp(::user::interaction) pguie = m_pviewAuth->get_child_by_name("user");
//      sp(text_interface) ptext =  (pguie);
//      ptext->_001SetText(m_loginthread.m_strUsername);
//      if(m_loginthread.m_strUsername.is_empty())
  //       Application.user()->set_keyboard_focus(pguie);
    //  else
      //{
        // pguie = m_pviewAuth->get_child_by_name("password");
         //Application.user()->set_keyboard_focus(pguie);
      //}
   }

   void validate::display_main_frame()
   {
      rect rectOpen;
   }

   void validate::pageMessage(const stringa & straMatter, ::ca::property_set & set)
   {
      ensure_main_document();
   }


   void validate::on_show_view()
   {
   }






   login_thread::login_thread(sp(::ca::application) papp) :
   ca(papp),
      thread(papp),
      simple_thread(papp)
   {
      m_bOk                = false;
      m_puser              = ::null();
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
         m_loginthread.m_strKeyHash = "ca2t12n";
         return "ca2t12n";
      }
   }

   string validate::calc_ca2_hash()
   {
      if(m_loginthread.m_strCa2Hash.has_char())
         return m_loginthread.m_strCa2Hash;
      m_loginthread.m_strCa2Hash = "ca2t12n";
      return m_loginthread.m_strCa2Hash;
   }


   // return hash and check if hash is valid
   bool validate::check_ca2_hash()
   {
      string strUrl("https://api.ca2.cc/account/check_hash");
      ::ca::property_set post;
      ::ca::property_set headers;
      ::ca::property_set set;
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
      ::ca::http::e_status estatus;
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

         if(estatus == ::ca::http::status_connection_timed_out)
         {

            iAuth = result_time_out;

         }
         else
         {

            iAuth = result_fail;

         }

      }
      //      char * psz = ::null();
      //    *psz = '2';
      m_pcallback->on_login_thread_response(iAuth, strResponse);
      return TRUE;
   }

   string login_thread::Login(::ca::http::e_status * pestatus)
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


   string login_thread::NetLogin(::ca::http::e_status * pestatus)
   {

      if(System.m_authmap[m_strUsername].m_mapServer[m_strRequestingServer].get_length() > 32)
      {
         return System.m_authmap[m_strUsername].m_mapServer[m_strRequestingServer];
      }

      string strGetFontopus("http://" + m_strRequestingServer + "/get_fontopus");

      m_strFontopusServer.Empty();

      sp(::ca::application) papp = get_app();

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

      string strLoginUrl("https://" + strApiServer + "/account/login");

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


            ::ca::property_set post;
            ::ca::property_set headers;
            ::ca::property_set set;

            //Sleep(15 * 1000);

            string strSessid = System.url().get_param(System.directrix()->m_varTopicQuery["ruri"], "sessid");

            if(strSessid.has_char())
            {
               m_puser->set_sessid(strSessid, strLoginUrl);
            }
            else if(m_puser->m_sessionidmap[m_strRequestingServer].get_length() > 16)
            {
               m_puser->set_sessid(m_puser->m_sessionidmap[m_strRequestingServer], strLoginUrl);
            }
            else
            {
               m_puser->set_sessid("not_auth", strLoginUrl);
            }

            set["app"] = papp;

            Application.http().get(strLoginUrl, strLogin, post, headers, set, m_puser->m_phttpcookies, m_puser, ::null(), pestatus);

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

#ifdef MACOS

      CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(::null(), 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

      CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeRSA);

      // not needed, defaults to true    CFDictionaryAddValue(parameters, kSecAttrCanEncrypt, kCFBooleanTrue);

      primitive::memory memKeyData;

      memKeyData.from_hex(strPass);

      CFDataRef keyData = memKeyData.get_os_cf_data();

      CFErrorRef error = ::null();

      SecKeyRef key = SecKeyCreateFromData(parameters, keyData, &error);

      if(error != ::null())
      {

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(error);

         return "";

      }

      SecTransformRef transform = SecEncryptTransformCreate(key, &error);

      if(error != ::null())
      {

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(key);

         CFRelease(error);

         return "";

      }

      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

      if(error != ::null())
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

      if(error != ::null())
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

      if(error != ::null())
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

      primitive::memory_file memfile(get_app());

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

      const char * psz = ERR_error_string(ERR_get_error(), ::null());

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

         ::ca::property_set post;
         ::ca::property_set headers;
         ::ca::property_set set;

         if(m_strPasshash.is_empty())
         {
            post["entered_password"] = strHex;
         }
         else
         {
            post["entered_passhash"] = strHex;
         }
         string strCrypt;

         post["entered_login"] = m_strUsername;
         if(m_strLicense.has_char())
         {
            post["entered_license"] = m_strLicense;
         }

         m_puser->set_sessid(strSessId, strAuthUrl);
         set["app"] = papp;
         uint32_t dwTimeProfile1 = get_tick_count();
         Application.http().get(strAuthUrl, strAuth, post, headers, set, m_puser->m_phttpcookies, m_puser, ::null(), pestatus);
         uint32_t dwTimeProfile2 = get_tick_count();

         TRACE0("login_thread::NetLogin Total time Application.http().get(\"" + strAuthUrl + "\") : " + ::ca::str::from(dwTimeProfile2 - dwTimeProfile1));

      }

      return strAuth;
   }

   void login_thread::execute()
   {
      string strFilename;
      string strResponse;
      ::ca::property_set set;
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


   void validate::authentication_failed(e_result iAuth, const char * pszResponse)
   {
      UNREFERENCED_PARAMETER(pszResponse);
      ::ca::property_set propertyset;
      string strUsername = m_loginthread.m_strUsername;
      m_bLicense = false;
      m_puser = ::null();
   }

   void validate::authentication_succeeded()
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

   
   validate::auth * validate::get_auth()
   {
      return ::null();
   }


   void validate::close_all()
   {
   }

   void validate::show_and_request_auth()
   {
   }

   bool validate::get_defer_registration()
   {

      return m_bDeferRegistration;

   }

} // namespace fontopus

