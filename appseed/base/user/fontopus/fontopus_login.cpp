#include "framework.h"


CLASS_DECL_BASE void draw_ca2(::draw2d::graphics * pdc, int x, int y, int z, COLORREF crBk, COLORREF cr);
CLASS_DECL_BASE void draw_ca2_with_border(::draw2d::graphics * pdc, int x, int y, int z, int b, COLORREF crBk, COLORREF cr, COLORREF crOut);
CLASS_DECL_BASE void draw_ca2_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crBorderOut, COLORREF crIn);
CLASS_DECL_BASE void draw_ca2_with_border2(::draw2d::graphics * pdc, int x, int y, int z, int bOut, int bIn, COLORREF crBk, COLORREF cr, COLORREF crBorderOut, COLORREF crIn);


namespace fontopus
{


   login::login(sp(::base::application) papp, int left, int top) :
      element(papp),
      ::thread(papp),
      m_labelUser(papp),
      m_editUser(papp),
      m_labelPassword(papp),
      m_password(papp),
      m_tap(papp)
   {

      m_bSelfLayout = false;

      m_pcallback = NULL;

      m_picon95 = NULL;

#if defined(WINDOWS)

      {

         HICON hicon95 = (HICON) ::LoadImage(::GetModuleHandle(NULL),MAKEINTRESOURCE(95),IMAGE_ICON,95,95,LR_VGACOLOR);

         if(hicon95 != NULL)
         {

            m_picon95 = new ::visual::icon(hicon95);

         }

      }

#endif
      m_bCred = false;


   }


   void login::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::interaction::install_message_handling(pdispatch);

      IGUI_CREATE(login);

   }


   void login::defer_translate(::simple_ui::style * pstyle)
   {

      xxdebug_box("defer_translate", "login", 0);

      string strForm = pstyle->defer_get("http://account.ca2.cc/login_form");

      if (strForm.is_empty())
         return;

      ::xml::document doc(get_app());

      if (!doc.load(strForm))

         return;
      ::xml::node & node = *doc.get_root();

      string str;

      str = node.attr("email");

      if (str.has_char())
         m_labelUser.SetWindowText(str);

      str = node.attr("senha");

      if (str.has_char())
         m_labelPassword.SetWindowText(str);

      str = node.attr("abrir");

      if (str.has_char())
         m_tap.SetWindowText(str);

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

      string strText;

      crypto_file_get(::dir::userappdata("license_auth/00001.data"), strText, "");

      m_editUser.SetWindowText(strText);

      string strPasshash;

      crypto_file_get(::dir::userappdata("license_auth/00002.data"), strPasshash, calc_key_hash());

      m_strPasshash = strPasshash;

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


   /*bool login::on_action(const char * pszId)
   {

      if (m_puiParent != NULL && m_puiParent->on_action(pszId))
         return true;

      if (strcmp(pszId, "submit") == 0)
      {

         start_login();

         return true;

      }

      return false;

   }*/

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

      string strUsername = m_editUser.get_window_text();

      if(strUsername.is_empty())
         return result_fail;

      string strPassword = m_password.get_window_text();

      if(strPassword.is_empty() && m_strPasshash.is_empty())
         return result_fail;

      

      {

         string_timeout & strtimeout = Session.fontopus()->m_authmap[strUsername].m_mapServer[m_strRequestingServer];

         if (strtimeout.get_length() > 32 && strtimeout.valid())
         {

            return process_response(strtimeout);

         }

      }

      if (m_strRequestingServer.is_empty())
         m_strRequestingServer = "https://account.ca2.cc";

      string strGetFontopus("http://" + m_strRequestingServer + "/get_fontopus");

      m_strFontopusServer = Session.fontopus()->get_server(strGetFontopus, 8);

      if (!str::ends(m_strFontopusServer, ".ca2.cc"))
         return ::fontopus::login::result_fail;

      {

         string_timeout & strtimeout = Session.fontopus()->m_authmap[strUsername].m_mapFontopus[m_strFontopusServer];

         if (strtimeout.get_length() > 32 && strtimeout.valid())
         {

            return process_response(strtimeout);

         }

      }

      string strLogin;

      string strApiServer;

      strApiServer = m_strFontopusServer;

      strApiServer.replace("account", "api");

      m_strLoginUrl = "https://" + strApiServer + "/account/login";

      ::xml::document doc(get_app());

      string strSessId;

      string strRsaModulus;

      for (int32_t iRetry = 0; iRetry <= 8; iRetry++)
      {

         if (iRetry > 0)
         {
            Sleep(iRetry * (1984 + 1977));
         }

         strLogin.empty_string();

         try
         {

            ::property_set set(get_app());

            set["disable_ca2_sessid"] = true;

            Application.http().get(m_strLoginUrl, strLogin, set);

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
         strPass = crypt_nessie(m_password.get_window_text());
      }
      else
      {
         strPass = m_strPasshash;
      }


      string strHex;

      strHex = System.crypto().spa_login_crypt(strPass, strRsaModulus);



      string strResponse;

      {

         string strAuthUrl("https://" + strApiServer + "/account/auth?defer_registration&ruri=" + m_pstyle->m_strRuri);

         if (m_strPasshash.is_empty())
         {
            strAuthUrl += "&entered_password=" + strHex;
         }
         else
         {
            strAuthUrl += "&entered_passhash=" + strHex;
         }
         //string strCrypt;

         strAuthUrl += "&entered_login=" + m_editUser.get_window_text();
         /*if(m_strLicense.has_char())
         {
         post["entered_license"] = m_strLicense;
         }*/

         strAuthUrl += "&sessid=" + strSessId;

         ::property_set set(get_app());

         set["disable_ca2_sessid"] = true;

         strResponse.empty_string();

         Application.http().get(strAuthUrl, strResponse, set);

      }

      return process_response(strResponse);

   }

   login::e_result login::process_response(string strResponse)
   {

      e_result eresult;

      ::xml::document doc(get_app());

      if (doc.load(strResponse))
      {

         if (doc.get_root()->get_name() == "response")
         {
            // Heuristical check
            if (stricmp_dup(doc.get_root()->attr("id"), "auth") == 0 && string(doc.get_root()->attr("passhash")).get_length() > 16 && atoi(doc.get_root()->attr("secureuserid")) > 0)
            {

               Session.fontopus()->m_authmap[m_editUser.get_window_text()].m_mapServer[m_strRequestingServer] = strResponse;
               Session.fontopus()->m_authmap[m_editUser.get_window_text()].m_mapFontopus[m_strFontopusServer] = strResponse;

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

      m_eresult = eresult;

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
      if (m_bCred)
      {

         set_cred(get_app(),m_strRequestingServer,false,m_editUser.get_window_text(),m_password.get_window_text());

      }
      else
      {
         string strUsername = m_editUser.get_window_text();
         string strPasshash = m_strPasshash;
         string strPassword = m_password.get_window_text();

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
            crypto_file_set(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/00010.data"), strPasshash2, calc_key_hash(), get_app());
            }*/
         }
         /*if(m_loginthread.m_strLicense.has_char())
         {
         stringa straLicense;
         straLicense.add(m_loginthread.m_strValidUntil);
         straLicense.add(System.datetime().international().get_gmt_date_time());
         crypto_file_set(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/" + m_loginthread.m_strLicense + ".data"), straLicense.implode(";"), calc_ca2_hash(), get_app());
         }*/

      }

   }

   void login::authentication_failed()
   {

      layout();

      ShowWindow(SW_SHOW);

   }



   void login::layout()
   {

      m_labelUser.m_bVisible = true;
      m_labelPassword.m_bVisible = true;
      m_editUser.m_bVisible = true;
      m_password.m_bVisible = true;
      m_tap.m_bVisible = true;


      int stdw = 884;
      int stdh = 184 + 23 + 184;

      int h;
      int w;

      rect rectClient;

      GetClientRect(rectClient);

      if (m_bSelfLayout)
      {
         

         double dwh = (double)stdw / (double)stdh;

         int availw = (int) (rectClient.width() * (1.0 - 0.14));
         int availh = (int) (rectClient.height() * (1.0 - 0.14));

         double davailwh;

         if (availh == 0.0)
         {
            davailwh = 1.0;
         }
         else
         {
            davailwh = (double)availw / (double)availh;
         }


         if (davailwh > dwh) // remaining width
         {

            h = (int) min(stdh, availh);
            w = (int) min(stdw, h  * dwh);

         }
         else // remaining height
         {

            w = (int) min(stdw, availw);
            h = (int) min(stdh, w / dwh);

         }

         m_dRate = (double)w / (double)stdw;
         rectClient.left = (rectClient.width() - w) / 2;
         rectClient.top = (rectClient.height() - h) / 3;
         rectClient.right = rectClient.left + w;
         rectClient.bottom = rectClient.top + h;

         SetPlacement(rectClient);

      }
      else
      {


         double dwh = (double)stdw / (double)stdh;

         int availw = (int)(rectClient.width());
         int availh = (int)(rectClient.height());

         double davailwh;

         if (availh == 0.0)
         {
            davailwh = 1.0;
         }
         else
         {
            davailwh = (double)availw / (double)availh;
         }


         if (davailwh > dwh) // remaining width
         {

            h = (int)min(stdh, availh);
            w = (int)min(stdw, h  * dwh);

         }
         else // remaining height
         {

            w = (int)min(stdw, availw);
            h = (int)min(stdh, w / dwh);

         }

         m_dRate = (double)w / (double)stdw;
      }

      double r = m_dRate;



      int32_t x1 = (int) (49 * r);
      int32_t x2 = (int) (x1 + (rectClient.width() - 49 * 2) * r);
      int32_t h1 = (int) (23 * r);
      int32_t pad = (int) (5 * r);

      int32_t y = (int) ((49 + 86) * r);
      m_labelUser.RepositionWindow(x1,y,x2,y + h1);
      y += h1 + pad;
      m_editUser.RepositionWindow(x1,y,x2,y + h1);
      y += h1 + pad;
      m_labelPassword.RepositionWindow(x1,y,x2,y + h1);
      y += h1 + pad;
      m_password.RepositionWindow(x1,y,x2,y + h1);
      y += h1 + pad;
      y += pad + h1 + pad;
      m_tap.RepositionWindow(x1,y,x2,y + h1 * 3);;


   }



   void login::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      simple_ui_draw_frame_window_rect(pgraphics);

      COLORREF crOut, crIn, crBorderOut, crBorderIn, cr, crBk;

      //       if (is_hover() || m_bDown || m_bMouseMove)
      /*       {

      #if CA2_PLATFORM_VERSION == CA2_BASIS

      crOut = ARGB(184 + 49, 255, 230, 255);

      crIn = ARGB(255, 255, 84 + 49, 255);

      crBorderOut = ARGB(184, 150, 100, 150);

      crBorderIn = ARGB(184, 255, 240, 255);

      #else

      crOut = ARGB(184 + 49, 230, 255, 225);

      crIn = ARGB(255, 84 + 49, 255, 77 + 49);

      crBorderOut = ARGB(184, 100, 150, 100);

      crBorderIn = ARGB(184, 240, 255, 235);

      #endif

      }
      else*/
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         /*crOut = ARGB(184, 255, 210, 255);

         crIn = ARGB(255, 255, 184 + 49, 255);

         crBorderOut = ARGB(184, 90, 20, 90);

         crBorderIn = ARGB(184, 255, 240, 255);*/

         crOut = ARGB(255, 255, 210, 255);

         crIn = ARGB(255, 255, 184 + 49, 255);

         crBorderOut = ARGB(255, 90, 20, 90);

         crBorderIn = ARGB(255, 255, 240, 255);

#else

         crOut = ARGB(184, 210, 255, 205);

         crIn = ARGB(255, 84 + 49, 255, 77 + 49);

         crBorderOut = ARGB(184, 20, 90, 20);

         crBorderIn = ARGB(184, 240, 255, 235);

#endif

      }


#if CA2_PLATFORM_VERSION == CA2_BASIS

      //cr = ARGB(223, 84, 49, 77);
      cr = ARGB(255, 84, 49, 77);

#else

      //cr = ARGB(223, 49, 84, 23);
      cr = ARGB(255, 49, 84, 23);

#endif

      crBk = ARGB(
         (argb_get_a_value(crOut) + argb_get_a_value(crIn)) / 2,
         (argb_get_r_value(crOut) + argb_get_r_value(crIn)) / 2,
         (argb_get_g_value(crOut) + argb_get_g_value(crIn)) / 2,
         (argb_get_b_value(crOut) + argb_get_b_value(crIn)) / 2);

      double r = m_dRate;

      if (m_bCred && m_strCred.has_char())
      {
         float fHeight = 18.0;

         ::draw2d::font_sp f(allocer());

         /*f->create_pixel_font("Geneva", (int32_t)height(rectClient) * 0.7);

         float fMargin = (height(rectClient) * ((1.0f - 0.7f) / 2.0f));*/

         f->create_point_font("Geneva", fHeight * 1.0);


         pgraphics->SelectObject(f);

         pgraphics->set_text_color(crBorderOut);
         pgraphics->TextOut((int)(49 * r), (int)(49 * r), m_strCred);
      }
      else if (m_picon95)
      {

         draw_ca2_border2(pgraphics, (int)(49 * r), (int)(49 * r) - 11, (int)((91 + 2 + 2) * r), 1, 1, crBk, cr, crBorderOut, crBorderIn);

         pgraphics->DrawIcon((int)(49 * r) + 2, (int)(49 * r) + 2 - 11, m_picon95, (int)((91 + 2 + 2) * r), (int)((91 + 2 + 2) * r), 0, NULL, 0);

      }
      else
      {

         draw_ca2_with_border2(pgraphics, (int)(49 * r), (int)(49 * r) - 11, (int)((91 + 2 + 2) * r), 1, 1, crBk, cr, crBorderOut, crBorderIn);

      }


   }

   bool login::on_action(const char * pszId)
   {

      if (!strcmp(pszId, "submit"))
      {

         if (m_bCred)
         {

            if (m_editUser.get_window_text().is_empty())
               return true;

            if(m_password.get_window_text().is_empty())
               return true;

            login_result(::fontopus::login::result_ok);

            GetTopLevelParent()->DestroyWindow();

            return true;

         }
         else
         {

            if (get_os_data() == NULL)
            {

               m_bVisible = false;

               GetTopLevelParent()->ShowWindow(SW_HIDE);

               ::thread::m_p.create(allocer());

               begin();

            }

         }

         return true;

      }
      else if (!strcmp(pszId, "escape"))
      {

         GetTopLevelParent()->DestroyWindow();

      }

      return false;


   }



   int32_t login::run()
   {

      try
      {

         login_result(perform_login());

         if (m_eresult == ::fontopus::login::result_fail)
         {

            GetTopLevelParent()->ShowWindow(SW_SHOW);

            m_bVisible = true;

         }
         else
         {

            GetTopLevelParent()->DestroyWindow();

         }
      }
      catch (...)
      {
      }

      set_os_data(NULL);

      return 0;

   }

   void login::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      if(pcreate->previous())
         return;

      if(!m_labelUser.create(this,"label_user")
         || !m_editUser.create(this, "edit_user")
         || !m_labelPassword.create(this, "label_password")
         || !m_password.create(this, "password")
         || !m_tap.create(this, "submit_button"))
      {
         pcreate->set_lresult(-1);
         pcreate->m_bRet = true;
         return;
      }
      

      m_labelUser.SetWindowText("e-mail:");
      m_labelPassword.SetWindowText("password:");
      m_tap.SetWindowText("open");

      m_eresult = login::result_fail;

      int stdw = 884;
      int stdh = 177 + 23 + 184 + 49;

      RepositionWindow(0,0,stdw,stdh);


      
   }


} // namespace fontopus




