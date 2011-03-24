#include "StdAfx.h"


typedef string ( *SALT)(::ca::application *, const char * , stringa &);

namespace fontopus
{

   validate::validate(::ca::application * papp, const char * pszForm, bool bVotagusAuth) :
      ca(papp),
      m_loginthread(papp),
      m_netcfg(papp)
   {
      m_bInteractive    = true;
      m_bVotagusAuth    = bVotagusAuth;
      m_strForm         = pszForm;
      m_puser           = NULL;
      m_ptemplatePane   = new ::userbase::single_document_template(
         papp,
         "system/auth",
         &typeid(form_document),
         &typeid(simple_frame_window),
         &typeid(userex::pane_tab_view));
      m_pauth           = NULL;
      m_pviewAuth       = NULL;
      m_pdocAuth        = NULL;
      m_pdoc            = NULL;
      m_ptabview        = NULL;
   }

   validate::~validate()
   {
      ::WaitForSingleObject(m_loginthread.get_os_data(), INFINITE);
   }

   ::fontopus::user * validate::get_user()
   {
      m_loginthread.m_strSalt.Empty();
      if(!strcmp(Application.get_module_name(), "netnodeapp")
         || !strcmp(Application.get_module_name(), "netnodecfgapp")
         || Application.get_license_id() == "netnodecfg"
         || Application.get_license_id() == "netnode"
         || Application.get_license_id() == "veievserver"
         || Application.command_line().m_varQuery["app"] == "netnodecfg")
      {
         m_puser = Application.allocate_user();
         m_puser->m_strPathPrefix = "system" + gen::str::has_char(Application.command_line().m_varQuery["systemid"], "-");
         m_puser->m_strLogin = carlosgustavocecynlundgren;
         return m_puser;
      }
      else if(Application.get_license_id() == "mydns"
         || Application.command_line().m_varQuery.has_property("install")
         || Application.command_line().m_varQuery.has_property("uninstall"))
      {
         m_puser = Application.allocate_user();
         m_puser->m_strPathPrefix = "system" + gen::str::has_char(Application.command_line().m_varQuery["systemid"], "-");
         m_puser->m_strLogin = carlosgustavocecynlundgren;
         return m_puser;
      }
      //else if(!strcmp(System.get_module_name(), "productionapp")
      //   || !strcmp(System.get_module_name(), "productionbasisapp")
      //   || !strcmp(System.get_module_name(), "backupapp")
      //   || System.command_line().m_varQuery["app"] == "production"
      //   || System.get_license_id() == "winservice_filesystemsize")
      else if(!strcmp(Application.get_module_name(), "backupapp")
         || Application.get_license_id() == "winservice_filesystemsize")
      {
         m_puser = Application.allocate_user();
         m_puser->m_strPathPrefix = "system" + gen::str::has_char(Application.command_line().m_varQuery["systemid"], "-");
         m_puser->m_strLogin = camilosasuketsumanuma;
         return m_puser;
      }
      string strDir;
      string strUsername;
      string strPasshash;
      System.crypt().file_get(Application.dir().usersystemappdata(Application.dir().default_os_user_path_prefix(), "license_auth", "00001.data"), strUsername, "");
      m_loginthread.m_strUsername = strUsername;
      System.crypt().file_get(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/00002.data"), strPasshash, calc_key_hash());
      if(strUsername.has_char() && strPasshash.has_char())
      {
         
         m_loginthread.m_puser = System.allocate_user();

         m_loginthread.m_strPassword.Empty();
         m_loginthread.m_strPasshash = strPasshash;
         m_loginthread.m_pcallback = this;
         m_loginthread.run();

         if(m_ptabview != NULL)
         {
            m_ptabview->get_wnd()->EndAllModalLoops(IDOK);
         }
         if(m_ptemplatePane != NULL)
         {
            m_ptemplatePane->close_all_documents(FALSE);
         }

         return m_puser;
      }
      m_loginthread.m_strModHash.Empty();
      m_loginthread.m_strKeyHash.Empty();
      m_loginthread.m_strCa2Hash.Empty();
      ensure_main_document();
      page1();
      m_pviewAuth->SetTimer(1984, 484, NULL);
      m_ptabview->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE);
      m_ptemplatePane->close_all_documents(FALSE);
      return m_puser;
   }

   void validate::ensure_main_document()
   {
      if(m_pdoc != NULL)
         return;
      m_pdoc = dynamic_cast < form_document * > (m_ptemplatePane->open_document_file(NULL, FALSE, System.m_puiInitialPlaceHolderContainer));
      userex::pane_tab_view * pview = m_pdoc->get_typed_view < userex::pane_tab_view >();
      pview->set_create_view(this);
      m_ptabview = pview;
      pview->add_tab("ca2open", 1);
      pview->add_tab("network", 2);
      pview->add_image_tab("", System.dir().matter("image/keyboard-h21.png"), 3);
      pview->set_cur_tab_by_id(1);
   }

   bool validate::get_license(const char * psz, bool bInteractive)
   {
      m_bInteractive = bInteractive;
      string strLicense(psz);
      if(strLicense == "netnodeapp"
         || strLicense == "netnodecfgapp"
         || strLicense == "netnodecfg"
         || strLicense == "netnode"
         || strLicense == "veievserver"
         || strLicense == "mydns"
         || System.command_line().m_varQuery.has_property("install")
         || System.command_line().m_varQuery.has_property("uninstall"))
      {
         return true;
      }
      //else if(!strcmp(System.get_module_name(), "productionapp")
      //   || !strcmp(System.get_module_name(), "productionbasisapp")
      //   || !strcmp(System.get_module_name(), "backupapp")
      //   || System.get_license_id() == "winservice_filesystemsize")
      else if(strLicense == "backupapp"
         || strLicense == "winservice_filesystemsize")
      {
         return true;
      }
      m_strLicense = psz;
      m_loginthread.m_strLicense = m_strLicense;
      string strDir;
      string strUsername;
      string strPasshash;
      System.crypt().file_get(Application.dir().usersystemappdata(Application.dir().default_os_user_path_prefix(), "license_auth", "00001.data"), strUsername, "");
      m_loginthread.m_strUsername = strUsername;
      System.crypt().file_get(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/00002.data"), strPasshash, calc_key_hash());
      if(strUsername.has_char() && strPasshash.has_char())
      {
         
         m_loginthread.m_puser = System.allocate_user();

         m_loginthread.m_strPassword.Empty();
         m_loginthread.m_strPasshash = strPasshash;
         m_loginthread.m_pcallback = this;
         m_loginthread.run();

         if(m_ptabview != NULL)
         {
            m_ptabview->get_wnd()->EndAllModalLoops(IDOK);
         }
         if(m_ptemplatePane != NULL)
         {
            m_ptemplatePane->close_all_documents(FALSE);
         }
         return m_bLicense;
      }
      else if(bInteractive)
      {
         m_loginthread.m_strModHash.Empty();
         m_loginthread.m_strKeyHash.Empty();
         m_loginthread.m_strCa2Hash.Empty();
         ensure_main_document();
         page1();
         m_pviewAuth->SetTimer(1984, 484, NULL);
         m_ptabview->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE);
         m_ptemplatePane->close_all_documents(FALSE);
         return m_bLicense;
      }
      else
      {
         return false;
      }
   }

   void validate::page1()
   {
      m_loginthread.m_puser = System.allocate_user();
      m_pdocAuth->get_html_data()->m_puser = m_loginthread.m_puser;
      string strUrl;
      strUrl = "http://spaignition.api.veriterse.net/query?node=install_application&id=";
      string strAppName;
      if(System.m_strAppName == "winactionarea")
      {
         strAppName = "_set_windesk";
      }
      else
      {
         strAppName = System.m_strAppName;
      }
      strUrl += strAppName;
      strUrl += "&key=name";
      m_pdocAuth->get_html_data()->m_propertyset["application_name"] = System.http().get(strUrl);
      if(m_strLicense.is_empty())
      {
         m_pdocAuth->get_html_data()->m_propertyset["reason"] = "Authenticating";
      }
      else
      {
         m_pdocAuth->get_html_data()->m_propertyset["reason"] = "Licensing";
      }
      if(!m_pdocAuth->on_open_document(System.dir().matter(m_strForm)))
      {
         authentication_failed(0, "Cannot open form for authentication!!");
         return;
      }
      display_main_frame();
      ::user::interaction * pguie = m_pviewAuth->GetChildByName("user");
      text_interface * ptext = dynamic_cast < text_interface * > (pguie);
      ptext->_001SetText(m_loginthread.m_strUsername);
      if(m_loginthread.m_strUsername.is_empty())
         System.set_keyboard_focus(pguie);
      else
      {
         pguie = m_pviewAuth->GetChildByName("password");
         System.set_keyboard_focus(pguie);
      }
   }

   void validate::display_main_frame()
   {
      rect rectOpen;
      if(m_ptabview->GetParentFrame()->GetParent() == NULL)
      {

         System.get_screen_rect(rectOpen);
      }
      else
      {
         m_ptabview->GetParentFrame()->GetParent()->GetClientRect(rectOpen);
      }
      int iWidth = rectOpen.width();
      int iHeight = rectOpen.height();
      rectOpen.deflate(iWidth / 5, iHeight / 5);
      simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (m_pviewAuth->GetTopLevelParent());
      if(pframe != NULL)
      {
         pframe->m_bblur_Background = true;
      }
      if(System.m_puiInitialPlaceHolderContainer != NULL)
      {
         System.m_puiInitialPlaceHolderContainer->GetTopLevelParent()->ShowWindow(SW_SHOW);
      }
      else
      {
         m_ptabview->GetTopLevelFrame()->ShowWindow(SW_SHOW);
      }
      m_ptabview->GetParentFrame()->SetWindowPos(
         ZORDER_TOP,
         rectOpen.left, rectOpen.top,
         rectOpen.width(), rectOpen.height(), 
         SWP_SHOWWINDOW);
      m_pviewAuth->GetTopLevelParent()->SetForegroundWindow();
      m_pviewAuth->GetTopLevelParent()->BringWindowToTop();
   }

   void validate::pageMessage(const char * pszMatter, gen::property_set & set)
   {
      ensure_main_document();
      m_pdocAuth->get_html_data()->m_propertyset = set;
      m_pdocAuth->on_open_document(System.dir().matter(pszMatter));
      display_main_frame();
      m_ptabview->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE);
      m_ptabview->get_wnd()->EndAllModalLoops(IDOK);
   }

   void validate::on_create_view(view_data * pviewdata)
   {
      switch(pviewdata->m_id)
      {
      case 1:
         {
            m_pdocAuth = System.create_form(this, m_ptabview);
            if(m_pdocAuth != NULL)
            {
               m_pviewAuth = m_pdocAuth->get_typed_view < form_view > ();
               m_pviewAuth->m_pcallback = this;
               pviewdata->m_pdoc = m_pdocAuth;
               pviewdata->m_pwnd = m_pviewAuth->GetParentFrame();
            }
         }
         break;
      case 2:
         {
            if(m_netcfg.initialize(m_ptabview))
            {
               pviewdata->m_pdoc = m_netcfg.m_pdoc;
               pviewdata->m_pwnd = m_netcfg.m_pview->GetParentFrame();
            }

         }
         break;
      case 3:
         {
            create_context cc;
            cc.m_pCurrentDoc = m_ptabview->get_document();
            cc.m_typeinfoNewView =  &typeid(::ca8::keyboard_layout);

            m_pkeyboardlayout = dynamic_cast < ::ca8::keyboard_layout * > (view::create_view(&cc, m_ptabview, 100));
            m_pkeyboardlayout->CreateViews();
            pviewdata->m_pdoc = m_pkeyboardlayout->m_pdoc;
            pviewdata->m_pwnd = m_pkeyboardlayout;
         }
         break;
      }
      if(pviewdata->m_pwnd != NULL)
      {
         pviewdata->m_eflag.signalize(::user::create_view::view_data::flag_hide_all_others_on_show);
      }

   }
   void validate::on_show_view()
   {
      switch(get_view_id())
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






   login_thread::login_thread(::ca::application * papp) :
   ca(papp),
      thread(papp),
      simple_thread(papp)
   {
      m_bOk = false;
      m_puser = NULL;
   }

   login_thread::~login_thread()
   {
   }

   void validate::get_mod(stringa & straHash, stringa & straSource)
   {
      straHash.remove_all();
      straSource.remove_all();
#if !core_level_1 && !core_level_2
      SetDllDirectory(NULL);
#endif
      ::LoadLibraryA("salt.dll");
      DWORD dwNeeded;
      if(!EnumProcessModules(::GetCurrentProcess(),  NULL,  0,  &dwNeeded))
      {
         return;
      }
      DWORD dwAlloc = (dwNeeded + sizeof(HMODULE)) * 2;
      HMODULE * pmodulea = new HMODULE[dwAlloc / sizeof(HMODULE)];
      if(pmodulea == NULL)
         return;
      if(!EnumProcessModules(::GetCurrentProcess(),  pmodulea,  dwAlloc,  &dwNeeded))
      {
         delete pmodulea;
         return;
      }
      string strModule;
      ex1::file_system_sp fs(get_app());
      string strModuleFolder(System.get_ca2_module_folder());
      fs->FullPath(strModuleFolder, strModuleFolder);
      for(DWORD dw = 0; dw < dwNeeded / (sizeof(HMODULE)); dw++)
      {
         strModule.Empty();
         GetModuleFileName(pmodulea[dw], strModule.GetBufferSetLength(4096), 4096);
         strModule.ReleaseBuffer();
         fs->FullPath(strModule, strModule);
         if(gen::str::begins_ci(strModule, strModuleFolder))
         {
            straSource.add(strModule);
            straHash.add(System.file36().md5(strModule));
         }
      }
      straHash.QuickSort();
      delete pmodulea;
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
#if !core_level_1 && !core_level_2
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
      else
      {
         m_loginthread.m_strKeyHash.Empty();
         return "";
      }
   }

   string validate::calc_ca2_hash()
   {
      if(m_loginthread.m_strCa2Hash.has_char())
         return m_loginthread.m_strCa2Hash;
      stringa straHash;
      stringa straSource;
      get_mod(straHash, straSource);
      straHash.insert_at(0, m_loginthread.m_strUsername);
#if !core_level_1 && !core_level_2
      ::SetDllDirectoryA(System.get_ca2_module_folder());
#endif
      HMODULE hmoduleSalt = ::LoadLibraryA("salt.dll");
      SALT salt = (SALT) ::GetProcAddress(hmoduleSalt, "salt");
      m_loginthread.m_strCa2Hash = salt(get_app(), straHash.implode(";"), straSource);
      return m_loginthread.m_strCa2Hash;
   }


   // return hash and check if hash is valid
   bool validate::check_ca2_hash()
   {
      string strUrl("https://fontopus.com/ca2api/account/check_hash");
      gen::property_set post;
      gen::property_set headers;
      gen::property_set set;
      string strResponse;
      stringa straHash;
      stringa straSource;
      get_mod(straHash, straSource);
      straHash.insert_at(0, m_loginthread.m_strPasshash);
      straHash.insert_at(0, m_loginthread.m_strUsername);

      post["hash"] = straHash.implode(";");
      post["source"] = straHash.implode(";");
      for(int i = 0; i < 3; i++)
      {
         if(Application.http().get(strUrl, strResponse, post, headers, set))
            break;
      }
      if(strResponse == "OK")
         return true;
      else
         return false;
   }

   void validate::on_login_thread_response(int iAuth, const char * pszResponse)
   {
      if(iAuth == 1)
      {
         authentication_succeeded();
      }
      else
      {
         authentication_failed(iAuth, pszResponse);
      }
   }

   void login_thread_callback::on_login_thread_response(int iAuth, const char * pszResponse)
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

   BOOL login_thread::run()
   {
      ca4::http::e_status estatus;
      string strResponse = Login(&estatus);
      int iAuth;
      xml::node node(get_app());
      node.load(strResponse);
      if(node.m_strName == "response")
      {
         if(node.attr("id") == "auth")
         {
            m_puser->m_strLogin = m_strUsername;
            m_puser->m_strSessid = node.attr("sessid");
            m_puser->m_strFunUserId = node.attr("secureuserid");
            m_strPasshash = node.attr("passhash");
            iAuth = 1;
            execute();
            if(m_strLicense.has_char())
            {
               m_strValidUntil = node.attr("valid_until");
            }
         }
         else
         {
            delete m_puser;
            iAuth = -1;
         }
      }
      else
      {
         delete m_puser;
         if(estatus == ca4::http::status_connection_timed_out)
         {
            iAuth = -2;
         }
         else
         {
            iAuth = 0;
         }
      }
      //      char * psz = NULL;
      //    *psz = '2';
      m_pcallback->on_login_thread_response(iAuth, strResponse);
      return TRUE;
   }

   string login_thread::Login(ca4::http::e_status * pestatus)
   {
      string strLogin;
      // online validation throught NetLogin
      for(int i = 0; i < 3; i++)
      {
         strLogin = NetLogin(pestatus);
         if(strLogin.has_char())
            return strLogin;
      }
      // entering offline validation
      if(m_strLicense.is_empty()) // user auth
      {
         if(m_strPasshash.has_char()) // validated some time before
         {
            return "<response id=\"auth\" sessid=\"\" secureuserid=\"\">";
         }
         else
         {
            // check against last password saved in this computer
            if(m_strPassword.has_char())
            {
               string strSalt;
               System.crypt().file_get(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), m_strUsername, "license_auth/00005.data"), strSalt, m_pcallback->calc_key_hash());
               if(strSalt.is_empty())
                  return ""; // at least one time connected and validated to ca2open ca2anima
               string strPasshash2 = System.crypt().v5_get_password_hash(strSalt, m_strPassword);
               string strPasshash5;
               System.crypt().file_get(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), m_strUsername, "license_auth/00010.data"), strPasshash5, m_pcallback->calc_key_hash());
               if(strPasshash5.is_empty() || strPasshash2.is_empty())
                  return ""; // at least one time connected and validated to ca2open ca2anima
               if(strPasshash5 != strPasshash2)
                  return ""; // at least one time connected and validated to ca2open ca2anima
               return "<response id=\"auth\" sessid=\"\" secureuserid=\"\">";
            }
            else
            {
               return "";  // no password, no validation
            }
         }
      }
      else // license
      {
         // check against last password saved in this computer
         if(m_strPassword.has_char())
         {
            string strLicense;
            System.crypt().file_get(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), m_strUsername, "license_auth/" + m_strLicense + ".data"), strLicense, m_pcallback->calc_ca2_hash());
            if(strLicense.is_empty())
               return ""; // at least one time connected and validated to ca2open ca2anima
            stringa straLicense;
            straLicense.explode(";", strLicense);
            if(straLicense.get_count() != 2)
               return ""; // license validation
            int iPathCount = 0;
            time_t timeLicense = System.datetime().strtotime(NULL, straLicense[0], 0, iPathCount);
            // TODO: take with timeNow, it should be always be greater than before.
            time_t timeNow = time(NULL);
            time_t timeLast = System.datetime().strtotime(NULL, straLicense[1], 0, iPathCount);
            // should license at least 5 seconds after last licensing
            if(timeLicense > timeNow && timeNow > (timeLast + 5))
            {
               return "<response id=\"auth\" sessid=\"\" secureuserid=\"\">"; 
            }
            else
            {
               return ""; // license expired
            }
         }
         else
         {
            return "";  // no password, no validation, at least one time connected to ca2open ca2anima
         }
      }
   }


   string login_thread::NetLogin(ca4::http::e_status * pestatus)
   {

      //string strSaltUrl("https://fontopus.com/ca2api/account/salt");
      string strAuthUrl("https://fontopus.com/ca2api/account/auth");
      string document;
      gen::property_set post;
      gen::property_set headers;
      gen::property_set set;

      /*if(m_strPasshash.is_empty())
      {
         post["entered_login"] = m_strUser;
         string strSalt;
         if(!Application.http().get(strSaltUrl, strSalt, post, headers, m_puser->m_phttpcookies, m_puser, NULL, pestatus))
            return "";
         if(strSalt.is_empty())
            return "";
         m_strPasshash = System.crypt().nessie(strSalt + System.crypt().nessie(m_strPassword));
      }*/
      post["entered_login"] = m_strUsername;
      if(m_strPasshash.is_empty())
      {
         post["entered_password"] = m_strPassword;
      }
      else
      {
         post["entered_passhash"] = m_strPasshash;
      }
      if(m_strLicense.has_char())
      {
         post["entered_license"] = m_strLicense;
      }

      m_puser->m_strLogin = m_strUsername;
      string strLogin;
      Application.http().get(strAuthUrl, strLogin, post, headers, set, m_puser->m_phttpcookies, m_puser, NULL, pestatus);
      return strLogin;
   }

   void login_thread::execute()
   {
      string strFilename;
      string strResponse;
      gen::property_set set;
      for(int i = 0; i < m_httpexecutea.get_size(); i++)
      {
         strFilename = System.file().time_square();
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
            if(m_bVotagusAuth)
            {
               m_ptabview->GetParentFrame()->ShowWindow(SW_HIDE);
               ::user::interaction * pguie = m_pviewAuth->GetChildByName("user");
               text_interface * ptext = dynamic_cast < text_interface * > (pguie);
               //m_loginthread.m_puser = dynamic_cast < ::fontopus::user * > (System.allocate_user());
               ptext->_001GetText(m_loginthread.m_strUsername);
               pguie = m_pviewAuth->GetChildByName("password");
               ptext = dynamic_cast < text_interface * > (pguie);
               ptext->_001GetText(m_loginthread.m_strPassword);
               m_loginthread.m_pcallback = this;
               m_loginthread.Begin();
            }
            else
            {
               m_pauth = new auth;
               ::user::interaction * pguie = m_pviewAuth->GetChildByName("user");
               text_interface * ptext = dynamic_cast < text_interface * > (pguie);
               ptext->_001GetText(m_pauth->m_strUsername);
               pguie = m_pviewAuth->GetChildByName("password");
               ptext = dynamic_cast < text_interface * > (pguie);
               ptext->_001GetText(m_pauth->m_strPassword);
               m_ptabview->get_wnd()->EndModalLoop(IDOK);
               m_ptabview->GetParentFrame()->ShowWindow(SW_HIDE);
            }
            return true;
         }
      }
      else if(pevent->m_eevent == ::user::event_timer
         && pevent->m_uiEvent == 1984)
      {

         string strDir;
         string strUsername;
         string strPasshash;

         string strPathUsername = Application.dir().usersystemappdata(Application.dir().default_os_user_path_prefix(), "license_auth", "00001.data");
         string strPathPasshash = Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/00002.data");

         if(!System.file().exists(strPathUsername) || !System.file().exists(strPathPasshash))
            return true;

         System.crypt().file_get(strPathUsername, strUsername, "");
         m_loginthread.m_strUsername = strUsername;

         System.crypt().file_get(strPathPasshash, strPasshash, calc_key_hash());

         if(strUsername.is_empty() || strPasshash.is_empty())
            return true;

         m_pviewAuth->KillTimer(1984);
         m_loginthread.m_strPassword.Empty();
         m_loginthread.m_strPasshash = strPasshash;
         m_loginthread.m_pcallback = this;
         m_loginthread.Begin();

         return true;
      }
      return false;
   }

   void validate::authentication_failed(int iAuth, const char * pszResponse)
   {
      UNREFERENCED_PARAMETER(pszResponse);
      gen::property_set propertyset;
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
            strUrl = "http://spaignition.api.veriterse.net/query?node=install_application&id=";
            strUrl += m_strLicense;
            strUrl += "&key=launch_name";
            string strName = Application.http().get(strUrl);
            if(strName.is_empty())
               strName = m_strLicense;
            propertyset["project"] = strName;
            propertyset["contribute_link"] = "ext://http://fontopus.com/license?id="+ m_strLicense + "&lang=" + System.get_locale() + "&sessid=" + ApplicationUser.m_strSessid;
            pageMessage("err\\user\\authentication\\not_licensed.xhtml", propertyset);
         }
      }
      else if(iAuth == -1)
      {
         propertyset["register_link"] = "ext://http://fontopus.com/register?email="+ System.url().url_encode(m_loginthread.m_strUsername);
         pageMessage("err\\user\\authentication\\wrong_fontopus_login.xhtml", propertyset);
         try
         {
            System.file().del(Application.dir().usersystemappdata(Application.dir().default_os_user_path_prefix(), "license_auth", "00001.data"));
         }
         catch(...)
         {
         }
         try
         {
            System.file().del(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/00002.data"));
         }
         catch(...)
         {
         }
         m_loginthread.m_strModHash.Empty();
         m_loginthread.m_strKeyHash.Empty();
         m_loginthread.m_strCa2Hash.Empty();
      }
      else if(iAuth == -2)
      {
         propertyset["server"] = "fontopus.com";
         pageMessage("err\\user\\network\\connection_timed_out.xhtml", propertyset);
      }
      else
      {
         pageMessage("err\\user\\authentication\\failed.xhtml", propertyset);
      }
      delete m_pauth;
   }

   void validate::authentication_succeeded()
   {
      TRACE0("The authentication has succeeded.");
      string strUsername = m_loginthread.m_strUsername;
      string strPasshash = m_loginthread.m_strPasshash;
      string strPassword = m_loginthread.m_strPassword;

      string strUsernamePrevious;
      string strPasshashPrevious;
      System.crypt().file_get(Application.dir().usersystemappdata(Application.dir().default_os_user_path_prefix(), "license_auth", "00001.data"), strUsernamePrevious, "");
      System.crypt().file_get(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsernamePrevious, "license_auth/00002.data"), strPasshashPrevious, calc_key_hash());

      if(strUsernamePrevious != strUsername ||
         strPasshashPrevious != strPasshash)
      {
         System.crypt().file_set(Application.dir().usersystemappdata(Application.dir().default_os_user_path_prefix(), "license_auth", "00001.data"), strUsername, "");
         System.crypt().file_set(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/00002.data"), strPasshash, calc_key_hash());
         if(strPassword.has_char())
         {
            string strSalt = System.crypt().v5_get_password_salt();
            System.crypt().file_set(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/00005.data"), strSalt, calc_key_hash());
            string strPasshash2 = System.crypt().v5_get_password_hash(strSalt, strPassword);
            System.crypt().file_set(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/00010.data"), strPasshash2, calc_key_hash());
         }
      }
      if(m_loginthread.m_strLicense.has_char())
      {
         stringa straLicense;
         straLicense.add(m_loginthread.m_strValidUntil);
         straLicense.add(System.datetime().international().get_gmt_date_time());
         System.crypt().file_set(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/" + m_loginthread.m_strLicense + ".data"), straLicense.implode(";"), calc_ca2_hash());
      }
      m_bLicense = true;
      m_puser = m_loginthread.m_puser;
      if(m_ptabview != NULL)
      {
         m_ptabview->get_wnd()->EndAllModalLoops(IDOK);
      }
   }

   validate::auth * validate::get_auth()
   {
      form_document * pdoc = dynamic_cast < form_document * > (
         m_ptemplatePane->open_document_file(
         NULL,
         TRUE,
         System.m_puiInitialPlaceHolderContainer));
      userex::pane_tab_view * pview = pdoc->get_typed_view < userex::pane_tab_view > ();
      pview->set_create_view(this);
      rect rectOpen;
      System.get_screen_rect(rectOpen);
      int iWidth = rectOpen.width();
      int iHeight = rectOpen.width();
      rectOpen.deflate(iWidth / 5, iHeight / 5);
      m_ptabview->GetParentFrame()->SetWindowPos(ZORDER_TOP, rectOpen.left,
         rectOpen.top,
         rectOpen.width(), rectOpen.height(), SWP_SHOWWINDOW);
      m_ptabview = pview;
      pview->add_tab("login", 1);
      pview->set_cur_tab_by_id(1);
      pview->GetParentFrame()->RedrawWindow();
      pview->GetTopLevelFrame()->RunModalLoop();
      return m_pauth;
   }

} // namespace fontopus

