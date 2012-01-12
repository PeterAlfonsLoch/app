#include "StdAfx.h"
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/err.h>

// from nessie.h
#define DIGESTBYTES 64

// from ca05_crypt.cpp
#define V5_FINAL_HASH_BYTES (DIGESTBYTES * 16)



namespace webserver
{



secure::secure()
{
}

void secure::ensure()
{
   prof_enter("secure::ensure()");
   gprop("secureuserid") = gen::g_newconst;
   gprop("param_login_request_uri") = current_url();

	gprop("g_secure_user_table_name") 				= "fun_user";
	gprop("g_secure_user_login_field_name") 		= "email";
	gprop("g_secure_user_password_field_name") 	= "password";
	gprop("g_secure_user_level_field_name") 	  	= "userlevel";
	gprop("g_secure_where_clause")        	  		= " AND (`register` & \"1\") = 1";

	if(gprop("g_secureLoginFront").get_string().is_empty())
	{
		gprop("g_secureLoginFront") = "https://fontopus.com/login?lang=" + gprop("param_locale");
	}

	dprint("dynsou.login= $login");
	dprint("dynsou.minUserLevel= $minUserLevel");


   if(strlen(request("ruri")) > 0)
   {
      gprop("login_request_uri") = request("ruri");
   }

   if (inattr("https") == true)
   {
      gprop("cfgUrl") = "https://";
   }
   else
   {
      gprop("cfgUrl") = "http://";
   }

   if(get("action") == "logout" || gprop("logout").is_set() || get("logout").is_set() || post("logout").is_set())
   {
      logout();
   }
   else
   {
      login_check();
   }
   prof_leave("secure::ensure()");
}


void secure::logout()
{
   string strUrl;
   strUrl = inattr("http_referer");
   System.url().set(strUrl, "action", "none");
   if(request("ruri").is_set())
      strUrl = request("ruri");

   set_session_value("login", gen::g_newconst);
   set_session_value("password", gen::g_newconst);
   set_session_value("password1", gen::g_newconst);
   set_session_value("password2", gen::g_newconst);
//   session_destroy();
   string strSessionPath = "/";
   string strSessionDomain = "fontopus.com";
   set_cookie("netnode_sessid", "", 1000);
   set_cookie("votagus_userid", "", 1000);
   set_cookie("votagus_pass1", "", 1000);
   set_cookie("votagus_pass2", "", 1000);
   set_session_value("secureuserid", gen::g_newconst);
   set_session_value("secureuserlevel", -1);
   set_session_value("auth", gen::g_newconst);

   if(!gen::str::ends(inattr("http_host"), ".fontopus.com") && inattr("http_host") != "fontopus.com")
   {
      outheader("Location") =
         "https://fontopus.com/sec?action=logout&ruri=" + System.url().url_encode(strUrl);
      exit(0);
   }

   if(((!gen::str::ends(inattr("http_host"), ".fontopus.com") && inattr("http_host") != "fontopus.com")
   || System.url().get_server(strUrl).is_empty())
   && (System.url().get_script(strUrl).CompareNoCase("sec") == 0
   || System.url().get_script(strUrl).is_empty()))
   {
      strUrl = "https://fontopus.com/";
   }
   strUrl = System.url().remove(strUrl, "sessid");
   if(System.url().get_server(strUrl) == "fontopus.com"
   && (System.url().get_script(strUrl) == "/main" || System.url().get_script(strUrl) == "/login"))
   {
      strUrl = System.url().set_script(strUrl, "/");
   }
   outheader("Location") = strUrl;
}

bool secure::login_check()
{
   bool bOptional = true;
   if(gprop("minUserLevel").is_new())
   {
      gprop("minUserLevel") = 30;
   }
   if(gprop("secure_optional").is_set())
   {
      if((bool)gprop("secure_optional"))
      {
         bOptional = true;
      }
      else
      {
         bOptional = false;
      }
   }
   else
   {
      if(!gprop("minUserLevel").is_new()
       && gprop("minUserLevel").get_integer() > 0)
      {
         bOptional = false;
      }
   }
   bool bEnforce = !bOptional;
   if(get("redir_cause") == "wrong_credentials")
   {
      set_session_value("auth", gen::g_newconst);
      set_session_value("login", gen::g_newconst);
      set_session_value("password1", gen::g_newconst);
      set_session_value("password2", gen::g_newconst);
      gprop("g_fontopus_login_prompt") = "wrong_credentials";
   }

   if(get_session_value("auth").is_set() && (bool) get_session_value("auth") && get_session_value("secureuserlevel").get_integer() > gprop("minUserLevel").get_integer())
   {
      dprint("secure::login_check() <strong>session auth</strong><br/>");
      until_here();
      gprop("secureuserid") = get_session_value("secureuserid");
      return true;
   }

   if(bOptional && ca2_fetch_mode() != 1 && !gen::str::ends(inattr("http_host"), ".fontopus.com") && inattr("http_host") != "fontopus.com")
   {
      //votagus_optional_login();
   }

   string strSessid;
   string strSessionPath;
   string strSessionDomain;
   dprint("!!!login_check!!!");


   gprop("login").unset();

   if(gen::str::begins(inattr("request_uri"), gprop("g_secureLoginFront")) && gprop("g_secureLoginFront").get_string().get_length() > 8)
   {
      gprop("minUserLevel") = 0;
   }
   if(request("ruri").is_set())
   {
      gprop("local_ruri") = request("ruri");
   }
   else
   {
      gprop("local_ruri") = gprop("param_login_request_uri");
   }
   gen::property_set params(get_app());
   params.parse_url_query(gprop("local_ruri"));
   gprop("g_secureLoginFrontEx") = uri_set_var(gprop("g_secureLoginFront"), "ruri", gprop("local_ruri"));
   gprop("g_secureLoginFrontEx") = uri_set_var(gprop("g_secureLoginFrontEx"), "lang", params["lang"]);
   if(isset(request("entered_login")))
   {
      gprop("g_secureLoginFrontEx") = uri_set_var(gprop("g_secureLoginFrontEx"), "email", request("entered_login"));
   }
   dprint(" secure Login =" + gprop("g_secureLoginFrontEx").get_string());

   string strPass;
   string strLevel;
   string strId;



   // check if login is necesary
   if(post("entered_login").get_string().has_char()
   && (post("entered_password").get_string().has_char() || post("entered_passhash").get_string().has_char()))
   {
      dprint("!!!logintest!!!");
      // encrypt entered login & password
      gprop("login")       = post("entered_login");
      string strLogin = gprop("login");
      strLogin.make_lower();
      if(post("entered_password").get_string().has_char())
      {
         gprop("password1")   = System.crypt().md5(post("entered_password"));
      }
      else
      {
         gprop("password1")   = "";
      }
      string strSql;
      strSql = eval("SELECT `$g_secure_user_password_field_name`, `$g_secure_user_level_field_name`, id FROM `$g_secure_user_table_name`  WHERE `$g_secure_user_login_field_name` = '$login' AND register = 1");
      dprint("<h2>Going to query fontopus database " + strSql + "</h2>");
      until_here();
      var row = musicdb().query_row(strSql);
      dprint("<h2>Queried fontopus database " + strSql + "</h2>");
      until_here();
      bool bDeferRegistration = false;
      if(row.is_array())
      {
         strPass     = row.at(0);
         strLevel    = row.at(1);
         strId       = row.at(2);
      }
      else
      {
         if(gprop("defer_registration") == "defer_registration" && post("entered_password").get_string().has_char())
         {
            bDeferRegistration = true;
         }
         strPass.Empty();
         strLevel.Empty();
         strId.Empty();
      }
      dprint(strSql);

      string strTryNessie = post("nessie");


      RSA * rsa = RSA_new();


      string rsa_n = get_session_value("rsa_n");

      BN_hex2bn(&rsa->n, rsa_n);


      string rsa_n_test = BN_bn2hex(rsa->n);
      BN_hex2bn(&rsa->e, get_session_value("rsa_e"));
      string rsa_e_test = BN_bn2hex(rsa->e);
      BN_hex2bn(&rsa->d, get_session_value("rsa_d"));
      string rsa_d_test = BN_bn2hex(rsa->d);
      BN_hex2bn(&rsa->p, get_session_value("rsa_p"));
      string rsa_p_test = BN_bn2hex(rsa->p);
      BN_hex2bn(&rsa->q, get_session_value("rsa_q"));
      string rsa_q_test = BN_bn2hex(rsa->q);
      BN_hex2bn(&rsa->dmp1, get_session_value("rsa_dmp1"));
      string rsa_dmp1_test = BN_bn2hex(rsa->dmp1);
      BN_hex2bn(&rsa->dmq1, get_session_value("rsa_dmq1"));
      string rsa_dmq1_test = BN_bn2hex(rsa->dmq1);
      BN_hex2bn(&rsa->iqmp, get_session_value("rsa_iqmp"));
      string rsa_iqmp_test = BN_bn2hex(rsa->iqmp);

      int iRsaSize = 8192;

      char * to = (char *) malloc(iRsaSize + 1);
	   string strPassword2;
      if(post("entered_password").get_string().has_char())
      {
         string strPassword = post("entered_password");
         //int iLenPass = strPassword.get_length();
         primitive::memory mem;
         Application.hex_to_memory(mem, strPassword);
         int i = RSA_private_decrypt(mem.get_size(), (const unsigned char *) (const char *) mem.get_data(), (unsigned char *) to, rsa, RSA_PKCS1_PADDING);
         if(i < 0 || i > (1024 * 1024))
         {
            gprop("message") = gprop("strUserNotExist");
            string strLocation = gprop("g_secureLoginFrontEx");
            System.url().set(strLocation, "redir_cause", "wrong_credentials");
            System.url().set(strLocation, "sessid", session_id());
            System.url().set(strLocation, "email", gprop("login"));
            outheader("Location") = strLocation;
            exit(0);
         }
         string strError(ERR_error_string(ERR_get_error(), NULL));
         primitive::memory memOut(to, i);
         string strNessie;
         Application.memory_to_hex(strNessie, memOut);
         strNessie.make_lower();

         if(bDeferRegistration)
         {
            string strFirstName;
            string strLastName;
            string strEmail;
            strEmail       = strLogin; 
            strFirstName   = strLogin.Left(strEmail.find("@"));
            strLastName    = strLogin.Mid(strEmail.find("@"));
            musicdb().secure_defer_register_login_email(strFirstName, strLastName, strLogin, strEmail, strNessie, "InitialGroup", get("ruri"));
            if(ca2_fetch_mode() == 1)
            {
               print("<response id=\"registration_deferred\" />");
            }
            else
            {
               //string strLocation = gprop("g_secureLoginFrontEx");
               //System.url().set(strLocation, "redir_cause", "wrong_credentials");
               //System.url().set(strLocation, "sessid", session_id());
               outheader("Location") = "https://fontopus.com/registration_deferred?login=$login";
            }
            exit(0);
         }

         strPassword2 = System.crypt().v5_get_password_hash(strPass, strNessie, 0);
         gprop("password2")   = strPassword2;
         string strPasshash = System.crypt().v5_get_passhash(strPass, strNessie, 10).Right(1088 - 960);
         gprop("passhash")    = strPasshash;
      }
      else
      {
         string strPasshash   = post("entered_passhash");
         //int iLenPass = strPasshash.get_length();
         primitive::memory mem;
         Application.hex_to_memory(mem, strPasshash);
         int i = RSA_private_decrypt(mem.get_size(), (const unsigned char *) (const char *) mem.get_data(), (unsigned char *) to, rsa, RSA_PKCS1_PADDING);
         if(i < 0 || i > (1024 * 1024))
         {
            gprop("message") = gprop("strUserNotExist");
            string strLocation = gprop("g_secureLoginFrontEx");
            System.url().set(strLocation, "redir_cause", "wrong_credentials");
            System.url().set(strLocation, "sessid", session_id());
            System.url().set(strLocation, "email", gprop("login"));
            outheader("Location") = strLocation;
            exit(0);
         }
         string strError(ERR_error_string(ERR_get_error(), NULL));
         primitive::memory memOut(to, i);
         string strNessie;
         Application.memory_to_hex(strNessie, memOut);
         strNessie.make_lower();
         strPassword2 = System.crypt().v5_get_password_hash(strPass, strNessie, 10);
         gprop("password2")  =strPassword2;
         gprop("passhash")    = strNessie;
      }
      RSA_free(rsa);
      free(to);
      gprop("password")       = gprop("password2");

      // session hack to make sessions on old php4 versions work
      dprint("<h5>session1</h5>");
      until_here();
      set_session_value("login", gprop("login"));
      dprint("<h5>session2</h5>");
      until_here();
      set_session_value("password", gprop("password"));
      set_session_value("password1", gprop("password1"));
      set_session_value("password2", gprop("password2"));
      dprint("<h5>session3</h5>");
      until_here();
      gprop("g_strict_secure_login") = true;
   }
   else
   {
      dprint("!!!loginthere!!!");
      gprop("login")       = get_session_value("login");
      gprop("password")    = get_session_value("password");
      gprop("password1")    = get_session_value("password1");
      gprop("password2")    = get_session_value("password2");
      dprint("login=" + gprop("login").get_string());
   }

   dprint("(111)minUserLevel=$minUserLevel");

   gprop("bCookieLogin") = false;
   if((gprop("g_strict_secure_login").is_new() ||
      gprop("g_strict_secure_login") == false) &&
      (gen::str::ends(inattr("http_host"), ".fontopus.com") || inattr("http_host") == "fontopus.com"))
   {
      if(cookie("votagus_userid").m_varValue.get_string().has_char())
      {
         gprop("userid") = cookie("votagus_userid");
         if(cookie("votagus_pass1").m_varValue.get_string().has_char())
         {
            string str;
            str = cookie("votagus_pass1").m_varValue.get_string();
            str.replace(".", "=");
            gprop("pass1") = str;
            if(cookie("votagus_pass2").m_varValue.get_string().has_char())
            {
               str = cookie("votagus_pass2").m_varValue.get_string();
               str.replace(".", "=");
               gprop("pass2") = str;
               gprop("dec") = musicdb().fun_str_decrypt(gprop("userid"), gprop("pass1"));
               dprint("dec=$dec<br>");
               string strDec1;
               System.crypt().decrypt(strDec1, gprop("pass2"), gprop("dec"));
               gprop("dec1") = strDec1;
               dprint("dec1=$dec1<br>");
               stringa stra;
               stra.add_tokens(strDec1, ",", TRUE);
               if(stra.get_count() > 0 &&
                  stra[0] == gprop("userid"))
               {
                  dprint("a0="+ stra[0] + "<br>");
                  string strSql;
                  bool bPass = false;
                  bool bLevel = false;
                  if(strPass.has_char() && strLevel.has_char()
                     && strPass == gprop("password"))
                  {
                     bPass = true;
                     bLevel = atoi(strLevel) > gprop("minUserLevel").get_integer();
                     if(bPass && bLevel)
                     {
//                        MYSQL_ROW row = presult->fetch_row();
   //                     gprop("login") = row[0];
      //                  gprop("password") = row[1];
                        set_session_value("secureuserlevel", strLevel);
                     }
                  }
                  if(bPass)
                  {
                     strSql = eval("SELECT `$g_secure_user_login_field_name`, `$g_secure_user_password_field_name`, `$g_secure_user_level_field_name` FROM `$g_secure_user_table_name` WHERE id = '$userid' AND `$g_secure_user_level_field_name` >= '$minUserLevel' $g_secure_where_clause");
                     dprint(strSql);
                     var rows = musicdb().query_rows(strSql);
                     if(rows.is_empty())
                     {
                        TRACE("No database");
                        exit(0);
                        //die("No Database");
                     }
                     bPass    = rows.is_array() && rows.array_get_count() > 0;
                     bLevel   = rows.is_array() && rows.array_get_count() > 0;
                     if(bPass && bLevel)
                     {
                        gprop("login")             = rows.at(0).at(0);
                        gprop("password")          = rows.at(0).at(1);
                        set_session_value("secureuserlevel", rows.at(0).at(2));
                     }
                  }
                  if(bLevel && bPass)
                  {
                     dprint("<h1>ok-----:secure</h1>");
                     until_here();
//                     MYSQL_ROW row = presult->fetch_row();
                     set_session_value("login", gprop("login"));
                     set_session_value("password", gprop("password"));
                     dprint("login=$login");
                     dprint("passwd=$password");
                     gprop("secureuserid") = gprop("userid");
                     gprop("bCookieLogin") = true;
                     set_session_value("secureuserid", gprop("secureuserid"));
                     set_session_value("auth",  true);
                  }
               }
            }
         }
      }
   }

   if(request("action") == "check")
   {
      if((bool) gprop("bCookieLogin"))
      {
         System.url().set(gprop("login_request_uri"), "sessid", session_id());
         if(ca2_fetch_mode() == 1)
         {
            return true;
         }
         outheader("Location") = gprop("login_request_uri");
         exit(0);
      }
   }
   else if(request("action") == "checkoptional")
   {
      System.url().set(gprop("login_request_uri"), "sessid", session_id());
      if(ca2_fetch_mode() == 1)
      {
         return true;
      }
      include("sharedapi/security/checkoptional");
      exit(0);
   }

   bool bOk = true;
   if(!(bool)gprop("bCookieLogin"))
   {
      if((int) gprop("minUserLevel") > 0 || gprop("login_request") == true)
      {
         if(gprop("minUserLevel").is_new())
         {
            gprop("minUserLevel") = 0;
         }
         dprint("x.minUserLevel=$minUserLevel");
         if(bOk && gprop("login").is_new())
         {
            bOk = false;
            if(bEnforce)
            {
               if(ca2_fetch_mode() == 1)
               {
                  //ob_end_clean();
                  print("<response id=\"not_auth\" detail=\"no_login\" hint=\"1\" />");
                  exit(0);
               }
               dprint("nologin");
               // no login available
               string strLocation = gprop("g_secureLoginFrontEx");
               System.url().set(strLocation, "redir_cause", "wrong_credentials");
               System.url().set(strLocation, "sessid", session_id());
               outheader("Location") = strLocation;
               exit(0);
            }
         }
         if(bOk && gprop("login").get_string().get_length() == 0)
         {
            bOk = false;
            if(bEnforce)
            {
               if(ca2_fetch_mode() == 1)
               {
                  //ob_end_clean();
                  print("<response id=\"not_auth\" detail=\"no_login\" hint=\"2\" />");
                  exit(0);
               }
               dprint("nologin");
               // no login available
               string strLocation = gprop("g_secureLoginFrontEx");
               System.url().set(strLocation, "redir_cause", "wrong_credentials");
               System.url().set(strLocation, "sessid", session_id());
               outheader("Location") = strLocation;
               exit(0);
            }
         }
         if(bOk && (gprop("password").get_string().get_length() == 0 &&
                   gprop("passhash").get_string().is_empty()))
         {
            bOk = false;
            if(bEnforce)
            {
               if(ca2_fetch_mode() == 1)
               {
                  //ob_end_clean();
                  print("<response id=\"not_auth\" detail=\"no_password\" hint=\"1\" />");
                  exit(0);
               }
               dprint("nopassword");
               // no login available
               string strLocation = gprop("g_secureLoginFrontEx");
               System.url().set(strLocation, "redir_cause", "wrong_credentials");
               System.url().set(strLocation, "sessid", session_id());
               System.url().set(strLocation, "email", gprop("login"));
               outheader("Location") = strLocation;
               exit(0);
            }
         }
         bool bPass = false;
         bool bLevel = false;
         if(bOk && strPass.has_char() && strLevel.has_char() && strId.has_char()
            && (strPass == gprop("password") || strPass == gprop("password1")))
         {
            bPass = true;
            bLevel = atoi(strLevel) >= gprop("minUserLevel").get_integer();
            if(bPass && bLevel)
            {
//                        MYSQL_ROW row = presult->fetch_row();
//                     gprop("login") = row[0];
//                  gprop("password") = row[1];
               gprop("secureuserid") = strId;
               set_session_value("secureuserlevel", strLevel);
            }
            if(strPass == gprop("password1") && post("entered_password").get_string().has_char())
            {
               string strPassword2 = System.crypt().v5_get_password_hash(post("entered_password"));
               if(strPassword2.get_length() > 200)
               {
                  string strSql =eval( "UPDATE `$g_secure_user_table_name` SET `$g_secure_user_password_field_name` = '"+strPassword2+"' WHERE `$g_secure_user_login_field_name` = '$login'");
                  mysql::result * presult = musicdb().query(strSql);
                  if(presult != NULL)
                  {
                     gprop("passhash")   = System.crypt().v5_get_passhash(strPassword2, post("entered_password"), 10).Right(1088 - 960);
                     if(gprop("passhash").get_string().get_length() < 10)
                     {
                        bPass = false;
                     }
                  }
                  else
                  {
                     bPass = false;
                  }
               }
               else
               {
                  bPass = false;
               }
            }
         }
         if(bOk && !bPass)
         {
            // contact database
            string strSql = eval("SELECT id, `$g_secure_user_level_field_name` FROM `$g_secure_user_table_name`WHERE `$g_secure_user_login_field_name` = '$login' AND (`$g_secure_user_password_field_name` = '$password1' OR `$g_secure_user_password_field_name` = '$password2' OR `$g_secure_user_password_field_name` = '$password') AND `$g_secure_user_level_field_name` >= '$minUserLevel' $g_secure_where_clause");
            dprint(strSql);
            var rows = musicdb().query_rows(strSql);
            if(rows.is_empty())
            {
               bOk = false;
               if(bEnforce)
               {
                  if(ca2_fetch_mode() == 1)
                  {
                     //ob_end_clean();
                     print("<response id=\"not_auth\" detail=\"no_login\" hint=\"2\" />");
                     exit(0);
                  }
                  dprint("nologin");
                  // no login available
                  string strLocation = gprop("g_secureLoginFrontEx");
                  System.url().set(strLocation, "redir_cause", "wrong_credentials");
                  System.url().set(strLocation, "sessid", session_id());
                  System.url().set(strLocation, "email", gprop("login"));
                  outheader("Location") = strLocation;
                  exit(0);
               }
            }
            bPass    = rows.array_get_count() > 0;
            bLevel   = rows.array_get_count() > 0;
            if(bPass && bLevel)
            {
               gprop("secureuserid")      = rows.at(0).at(0);
               set_session_value("secureuserlevel",  rows.at(0).at(1));
               //gprop("login") = row[0];
               //gprop("password") = row[1];
            }
         }
         if(bOk && bPass && bLevel)
         {
            dprint("<h1>ok-----:secure</h1>");
            until_here();
            set_session_value("secureuserid", gprop("secureuserid"));
            set_session_value("auth",  true);
            //if(request("store_auth_in_client").is_set() && cookie("votagus_userid").is_new())
//            if(cookie("votagus_userid").is_new())
            if(ca2_fetch_mode() != 1)
            {
               gprop("data") = System.crypt().strkey();
               string strEnc1;
               strEnc1 = musicdb().fun_str_encrypt(gprop("secureuserid"), gprop("data"));
               strEnc1.replace("=", ".");
               gprop("enc1") = strEnc1;
               string strEnc2;
               System.crypt().encrypt(strEnc2, gprop("secureuserid").get_string() + "," + gprop("data"), gprop("data"));
               strEnc2.replace("=", ".");
               gprop("enc2") = strEnc2;
               strSessionPath = "/";
               strSessionDomain = "fontopus.com";
               //set_cookie("votagus_userid", gprop("secureuserid"), strtotime("+7 day", time(NULL)), strSessionPath, strSessionDomain);
               //set_cookie("votagus_pass1", gprop("enc1"), strtotime("+7 day", time(NULL)), strSessionPath, strSessionDomain);
               //set_cookie("votagus_pass2", gprop("enc2"), strtotime("+7 day", time(NULL)), strSessionPath, strSessionDomain);
               set_cookie("votagus_userid", gprop("secureuserid"));
               set_cookie("votagus_pass1", gprop("enc1"));
               set_cookie("votagus_pass2", gprop("enc2"));
            }
         }
         else
         {
            bOk = false;
            dprint("---no rows---");
            if(bEnforce && request("action") != "checkoptional")
            {
               if(ca2_fetch_mode() == 1)
               {
//                  ob_end_clean();
                  print("<response id=\"not_auth\" detail=\"wrong_password_or_login\" />");
                  exit(0);
               }

               if(gprop("g_override_logout").is_set())
               {
                  outheader("Location") = gprop("g_override_logout");
                  //ob_end_clean();
                  exit(0);
               }
               // user not present in database
               {
                  gprop("message") = gprop("strUserNotExist");
                  string strLocation = gprop("g_secureLoginFrontEx");
                  System.url().set(strLocation, "redir_cause", "wrong_credentials");
                  System.url().set(strLocation, "sessid", session_id());
                  System.url().set(strLocation, "email", gprop("login"));
                  outheader("Location") = strLocation;
                  exit(0);
               }
            }
         }
      }
   }

   if(request("action") == "check")
   {
      if(gprop("secureuserid").is_set() && !votagus_is_in())
      {
         System.url().set(gprop("login_request_uri"), "sessid", session_id());
         if(ca2_fetch_mode() == 1)
         {
            return true;
         }
         outheader("Location") = gprop("login_request_uri");
         exit(0);
      }
      else
      {
         if(ca2_fetch_mode() == 1)
         {
            return true;
         }
         outheader("Location") = gprop("login_request_uri");
         exit(0);
      }
   }
   return true;
}



   bool secure::votagus_is_in()
   {
      return get_session_value("votagus_login_tested").is_set() && get_session_value("votagus_login_tested") == true;
   }

   bool secure::votagus_automatic_login()
   {
      if(!votagus_is_in())
      {
         set_session_value("votagus_login_tested", true);
         string strUrl = "https://fontopus.com/sec?action=check&ruri=" + System.url().url_encode(get_current_url());
         dprint("url=" + strUrl);
         outheader("Location") = strUrl;
         exit(0);
      }
      return true;
   }
   bool secure::votagus_optional_login()
   {
      if(!votagus_is_in() && (cookies().find_cookie("sessid") >= 0  && !cookie("sessid").m_varValue.is_new()
         && cookie("sessid").m_varValue.get_string().get_length() > 10) && get("authnone").is_new()
         && !gen::str::ends(inattr("http_host"), ".ca2ns.net"))
      {
         set_session_value("votagus_login_tested", true);
         string strRuri = get_current_url();
         strRuri = System.url().remove(strRuri, "sessid");
         string strUrl = "https://fontopus.com/sec";
         System.url().set(strUrl, "action", "checkoptional");
         System.url().set(strUrl, "ruri", strRuri);
         System.url().set(strUrl, "sessid", session_id());
         dprint("url=$url");
         //session_write_close();
         header("Location: " + strUrl);
         exit(0);
         return true;
      }
      return false;
   }


   void secure::login()
   {
      dprint("<h5>secure::login()</h5>");
      until_here();
      ensure();

      dprint("login=$login");
      dprint("secureuserid=$secureuserid");
      dprint("login_uri: $local_ruri");

       string strUrl =  urldecode(request("ruri"));
      if(System.url().get_server(strUrl).is_empty())
      {
         strUrl = "https://fontopus.com/";
      }
      System.url().set(strUrl, "sessid", session_id());
      if(ca2_fetch_mode() == 1)
      {
         print("<response id=\"auth\" sessid=\"" + session_id() + "\" passhash=\""+ gprop("passhash") +"\" secureuserid=\""+gprop("secureuserid")+"\" />");
      }
      else
      {
         outheader("Location") = strUrl;
      }
   }



   } // namespace webserver
