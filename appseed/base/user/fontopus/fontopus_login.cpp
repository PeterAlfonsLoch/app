#include "framework.h"


CLASS_DECL_BASE string spa_login_crypt(const char * psz, const char * pszRsa);


namespace fontopus
{


   login::login(sp(base_application) papp, int left, int top) :
      element(papp),
      interaction(papp),
      m_labelUser(papp),
      m_editUser(papp),
      m_labelPassword(papp),
      m_password(papp),
      m_tap(papp)
   {
      m_pcallback = NULL;

      m_labelUser.set_parent(this);
      m_editUser.set_parent(this);
      m_labelPassword.set_parent(this);
      m_password.set_parent(this);
      m_tap.set_parent(this);

      m_rect.left = left;
      m_rect.top = top;
      m_rect.right = m_rect.left + 840;
      m_rect.bottom = m_rect.top + 284;

      layout();

      m_labelUser.m_strText = "e-mail:";
      m_labelPassword.m_strText = "password:";
      m_tap.m_strText = "open";


   }


   void login::defer_translate(::simple_ui::style * pstyle)
   {

      xxdebug_box("defer_translate", "login", 0);

      string strForm = pstyle->defer_get("http://account.ca2.cc/login_form");

      if (strForm.is_empty())
         return;

      ::xml::document doc;

      if (!doc.load(strForm))

         return;
      ::xml::node & node = *doc.get_root();

      string str;

      str = node.attr("email");

      if (str.has_char())
         m_labelUser.m_strText = str;

      str = node.attr("senha");

      if (str.has_char())
         m_labelPassword.m_strText = str;

      str = node.attr("abrir");

      if (str.has_char())
         m_tap.m_strText = str;

   }


   login::~login()
   {
   }


   void login::callback::login_result(e_result eresult)
   {

      UNREFERENCED_PARAMETER(eresult);

   }


   void login::initialize()
   {

      crypto_file_get(::dir::userappdata("license_auth/00001.data"), m_editUser.m_strText, "");
      crypto_file_get(::dir::userappdata("license_auth/00002.data"), m_strPasshash, calc_key_hash());

      //crypt_file_get(dir::usersystemappdata(dir::default_os_user_path_prefix(), "license_auth", "00001.data"), m_editUser.m_strText, "");

      //crypt_file_get(dir::default_userappdata(dir::default_os_user_path_prefix(), m_editUser.m_strText, "license_auth/00002.data"), m_strPasshash, calc_key_hash());

   }


   string login::calc_key_hash()
   {
      if (m_strKeyHash.has_char())
         return m_strKeyHash;
      /*#if !core_level_1 && !core_level_2
      ::SetDllDirectoryA(System.get_ca2_module_folder());
      #endif
      HMODULE hmoduleSalt = ::LoadLibraryA("salt.dll");
      SALT salt = (SALT) ::GetProcAddress(hmoduleSalt, "salt");
      stringa straSource;
      if(m_loginthread.m_strUsername.has_char())
      {
      m_loginthread.m_strKeyHash = salt(get_app(), m_loginthread.m_strUsername, straSource);
      return m_loginthread.m_strKeyHash;
      }
      else */
      {
         m_strKeyHash = "ca2_12n";
         return "ca2_12n";
      }
   }


   bool login::on_action(const char * pszId)
   {

      if (m_puiParent != NULL && m_puiParent->on_action(pszId))
         return true;

      if (strcmp(pszId, "submit") == 0)
      {

         start_login();

         return true;

      }

      return false;

   }

   void login::start_login()
   {

      ::create_thread(NULL, 0, &login::thread_proc_login, (LPVOID) this, 0, 0);

   }


   uint32_t login::thread_proc_login(void * lpParam)
   {

      login * plogin = (login *)lpParam;

      plogin->login_result(plogin->perform_login());

      return 0;

   }



   login::e_result login::perform_login()
   {

      if (m_editUser.m_strText.is_empty())
         return result_fail;

      if (m_password.m_strText.is_empty() && m_strPasshash.is_empty())
         return result_fail;

      string strUsername = m_editUser.m_strText;

      if (::fontopus::authentication_map::m_authmap[strUsername].m_mapServer[m_strRequestingServer].get_length() > 32)
      {

         return process_response(::fontopus::authentication_map::m_authmap[strUsername].m_mapServer[m_strRequestingServer]);

      }

      string strGetFontopus("http://" + m_strRequestingServer + "/get_fontopus");

      m_strFontopusServer = Application.fontopus()->get_server(strGetFontopus, 8);

      if (!str::ends(m_strFontopusServer, ".ca2.cc"))
         return ::fontopus::login::result_fail;

      if (::fontopus::authentication_map::m_authmap[strUsername].m_mapFontopus[m_strFontopusServer].get_length() > 32)
      {

         return process_response(::fontopus::authentication_map::m_authmap[strUsername].m_mapFontopus[m_strFontopusServer]);

      }

      string strLogin;

      string strApiServer;

      strApiServer = m_strFontopusServer;

      strApiServer.replace("account", "api");

      m_strLoginUrl = "https://" + strApiServer + "/account/login";

      ::xml::document doc;

      string strSessId;

      string strRsaModulus;

      for (int32_t iRetry = 0; iRetry <= 8; iRetry++)
      {

         if (iRetry > 0)
         {
            Sleep(iRetry * 584);
         }

         try
         {


            strLogin = Application.http().get(m_strLoginUrl);

         }
         catch (...)
         {
         }

         strLogin.trim();

         if (strLogin.is_empty())
            continue;

         if (!doc.load(strLogin))
            continue;

         if (doc.get_root()->get_name() != "login")
            continue;

         strSessId = doc.get_root()->attr("sessid");

         if (strSessId.is_empty())
            continue;

         strRsaModulus = doc.get_root()->attr("rsa_modulus");

         if (strRsaModulus.has_char())
            break;

      }

      if (strRsaModulus.is_empty())
         return result_fail;

      string strPass;
      if (m_strPasshash.is_empty())
      {
         strPass = crypt_nessie(m_password.m_strText);
      }
      else
      {
         strPass = m_strPasshash;
      }


      string strHex;

      strHex = spa_login_crypt(strPass, strRsaModulus);

      string strResponse;

      {

         string strAuthUrl("https://api.ca2.cc/account/auth?defer_registration&ruri=" + m_pstyle->m_strRuri);

         if (m_strPasshash.is_empty())
         {
            strAuthUrl += "&entered_password=" + strHex;
         }
         else
         {
            strAuthUrl += "&entered_passhash=" + strHex;
         }
         //string strCrypt;

         strAuthUrl += "&entered_login=" + m_editUser.m_strText;
         /*if(m_strLicense.has_char())
         {
         post["entered_license"] = m_strLicense;
         }*/

         strAuthUrl += "&sessid=" + strSessId;

         strResponse = Application.http().get(strAuthUrl);

      }

      return process_response(strResponse);

   }

   login::e_result login::process_response(string strResponse)
   {

      e_result eresult;

      ::xml::document doc;

      if (doc.load(strResponse))
      {

         if (doc.get_root()->get_name() == "response")
         {
            // Heuristical check
            if (stricmp_dup(doc.get_root()->attr("id"), "auth") == 0 && string(doc.get_root()->attr("passhash")).get_length() > 16 && atoi(doc.get_root()->attr("secureuserid")) > 0)
            {

               ::fontopus::authentication_map::m_authmap[m_editUser.m_strText].m_mapServer[m_strRequestingServer] = strResponse;
               ::fontopus::authentication_map::m_authmap[m_editUser.m_strText].m_mapFontopus[m_strFontopusServer] = strResponse;

               m_strPasshash = doc.get_root()->attr("passhash");
               m_strSessId = doc.get_root()->attr("sessid");
               m_strSecureId = doc.get_root()->attr("secureuserid");
               eresult = result_ok;
            }
            else if (stricmp_dup(doc.get_root()->attr("id"), "registration_deferred") == 0)
            {
               eresult = result_registration_deferred;
            }
            else
            {
               eresult = result_fail;
            }
         }
         else
         {

            eresult = result_fail;

         }

      }
      else
      {

         eresult = result_fail;

      }

      return eresult;

   }


   void login::login_result(e_result eresult)
   {

      if (eresult == result_ok)
      {

         authentication_succeeded();

      }
      else
      {

         authentication_failed();

      }


      if (m_pcallback != NULL)
      {

         m_pcallback->login_result(eresult);

      }

   }


   void login::authentication_succeeded()
   {

      string strUsername = m_editUser.m_strText;
      string strPasshash = m_strPasshash;
      string strPassword = m_password.m_strText;

      string strUsernamePrevious;
      string strPasshashPrevious;
      crypto_file_get(dir::userappdata("license_auth/00001.data"), strUsernamePrevious, "");
      crypto_file_get(dir::userappdata("license_auth/00002.data"), strPasshashPrevious, calc_key_hash());

      if ((strUsername.has_char() && strPasshash.has_char())
         && (strUsernamePrevious != strUsername || strPasshashPrevious != strPasshash))
      {
         dir::mk(::dir::userappdata("license_auth"));
         crypto_file_set(::dir::userappdata("license_auth/00001.data"), strUsername, "");
         crypto_file_set(::dir::userappdata("license_auth/00002.data"), strPasshash, calc_key_hash());
         /*if(strPassword.has_char())
         {
         string strSalt = System.crypto().v5_get_password_salt();
         System.crypto().file_set(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/00005.data"), strSalt, calc_key_hash(), get_app());
         string strPasshash2 = System.crypto().v5_get_password_hash(strSalt, strPassword);
         crypt_file_set(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/00010.data"), strPasshash2, calc_key_hash(), get_app());
         }*/
      }
      /*if(m_loginthread.m_strLicense.has_char())
      {
      stringa straLicense;
      straLicense.add(m_loginthread.m_strValidUntil);
      straLicense.add(System.datetime().international().get_gmt_date_time());
      crypt_file_set(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/" + m_loginthread.m_strLicense + ".data"), straLicense.implode(";"), calc_ca2_hash(), get_app());
      }*/

   }

   void login::authentication_failed()
   {

   }



   void login::layout()
   {



      int32_t x1 = 49;
      int32_t x2 = m_rect.width() - 49;
      int32_t h1 = 23;
      int32_t pad = 5;

      m_labelUser.m_rect.left = x1;
      m_labelUser.m_rect.right = x2;
      m_editUser.m_rect.left = x1;
      m_editUser.m_rect.right = x2;
      m_labelPassword.m_rect.left = x1;
      m_labelPassword.m_rect.right = x2;
      m_password.m_rect.left = x1;
      m_password.m_rect.right = x2;
      m_tap.m_rect.left = x1;
      m_tap.m_rect.right = x2;

      int32_t y = 5;
      m_labelUser.m_rect.top = y;
      y += h1;
      m_labelUser.m_rect.bottom = y;
      y += pad;
      m_editUser.m_rect.top = y;
      y += h1;
      m_editUser.m_rect.bottom = y;
      y += pad;
      m_labelPassword.m_rect.top = y;
      y += h1;
      m_labelPassword.m_rect.bottom = y;
      y += pad;
      m_password.m_rect.top = y;
      y += h1;
      m_password.m_rect.bottom = y;
      y += pad + h1 + pad;
      m_tap.m_rect.top = y;
      y += h1 * 3;
      m_tap.m_rect.bottom = y;


   }



} // namespace fontopus




