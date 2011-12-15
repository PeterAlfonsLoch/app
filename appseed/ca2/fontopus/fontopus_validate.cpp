#include "StdAfx.h"


namespace ca2
{


   namespace fontopus
   {

      validate::validate(::ca::application * papp, const char * pszForm, bool bVotagusAuth, bool bInteractive) :
         ca(papp),
         ::fontopus::validate(papp, pszForm, bVotagusAuth, bInteractive),
         m_netcfg(papp)
      {
         m_bInteractive    = bInteractive;
         m_bVotagusAuth    = bVotagusAuth;
         m_strForm         = pszForm;
         ::radix::application * pradixapp = dynamic_cast < ::radix::application * > (papp);
         if(pradixapp != NULL)
         {
            try
            {
               pradixapp->keep_alive();
            }
            catch(...)
            {
            }
         }
         //Sleep(15 * 1000);
         m_ptemplatePane   = new ::userbase::single_document_template(
            papp,
            "system/auth",
            System.template type_info < form_document > (),
            System.template type_info < simple_frame_window > (),
            System.template type_info < userex::pane_tab_view > ());
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

      void validate::show_and_request_auth()
      {
         
         m_pviewAuth->SetTimer(1984, 484, NULL);
         ::ca::live_signal livesignal;
         livesignal.keep(get_app());
         m_ptabview->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE, &livesignal);
         m_ptemplatePane->close_all_documents(FALSE);

      }



      void validate::ensure_main_document()
      {
         if(m_pdoc != NULL)
            return;
         ::ca::create_context_sp createcontext(get_app());
         createcontext->m_bMakeVisible = false;
         createcontext->m_puiParent = Sys(get_app()).oprop("top_parent").ca2 < ::user::interaction > ();
         createcontext->m_bOuterPopupAlertLike = true;
         m_pdoc = dynamic_cast < form_document * > (m_ptemplatePane->open_document_file(createcontext));
         userex::pane_tab_view * pview = m_pdoc->get_typed_view < userex::pane_tab_view >();
         pview->set_view_creator(this);
         m_ptabview = pview;
         pview->set_tab("ca2open", 1);
         pview->set_tab("network", 2);
         pview->set_image_tab("", Application.dir().matter("image/keyboard-h21.png"), 3);
         pview->set_cur_tab_by_id(1);
      }

      void validate::page1()
      {
         m_pdocAuth->get_html_data()->m_puser = m_loginthread.m_puser;
         //string strUrl;
         //strUrl = "http://spaignition.api.veriterse.net/query?node=install_application&id=";
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
         if(!m_pdocAuth->on_open_document(Application.dir().matter(m_strForm)))
         {
            authentication_failed(0, "Cannot open form for authentication!!");
            return;
         }
         display_main_frame();
         ::user::interaction * pguie = m_pviewAuth->GetChildByName("user");
         text_interface * ptext = dynamic_cast < text_interface * > (pguie);
         ptext->_001SetText(m_loginthread.m_strUsername);
         if(m_loginthread.m_strUsername.is_empty())
            Application.set_keyboard_focus(pguie);
         else
         {
            pguie = m_pviewAuth->GetChildByName("password");
            Application.set_keyboard_focus(pguie);
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
   /*      if(System.m_puiInitialPlaceHolderContainer != NULL)
         {
            System.m_puiInitialPlaceHolderContainer->GetTopLevelParent()->ShowWindow(SW_SHOW);
         }
         else*/
         {
            m_ptabview->GetTopLevelFrame()->ShowWindow(SW_SHOW);
         }
         m_ptabview->GetTopLevelFrame()->SetWindowPos(
            ZORDER_TOP,
            rectOpen.left, rectOpen.top,
            rectOpen.width(), rectOpen.height(),
            SWP_SHOWWINDOW);
         if(m_ptabview->GetTopLevelFrame()->GetParent() != NULL)
         {
            try
            {
               m_ptabview->GetTopLevelFrame()->GetParent()->layout();
            }
            catch(...)
            {
            }
         }
         else
         {
         }
         /*UINT ui1 = GetCurrentThreadId();
         UINT ui2 = m_ptabview->GetTopLevelFrame()->m_pthread->get_os_int();
         if(::AttachThreadInput(ui1, ui2, TRUE)) 
         {
            TRACE("AttachedThreadInput");
         }*/
         if(m_ptabview->GetTopLevelFrame()->SetForegroundWindow())
         {
            TRACE("fontopus_validate tab_view top_level_frame set_foreground_window OK");
            if(m_ptabview->GetTopLevelFrame()->BringWindowToTop())
            {
               TRACE("fontopus_validate tab_view top_level_frame bring_window_to_top OK");
            }
         }

      

         /*
         m_ptabview->GetTopLevelFrame()->ActivateFrame();
         m_ptabview->GetTopLevelFrame()->SetFocus();*/
      

         //m_pviewAuth->GetTopLevelParent()->SetForegroundWindow();
         //m_pviewAuth->GetTopLevelParent()->BringWindowToTop();
      }

      void validate::pageMessage(const char * pszMatter, gen::property_set & set)
      {
         ensure_main_document();
         m_pdocAuth->get_html_data()->m_propertyset = set;
         m_pdocAuth->on_open_document(Application.dir().matter(pszMatter));
         display_main_frame();
         ::ca::live_signal livesignal;
         livesignal.keep(get_app());
         m_ptabview->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE, &livesignal);
         m_ptabview->get_wnd()->EndAllModalLoops(IDOK);
      }

      void validate::on_create_view(::user::view_creator_data * pcreatordata)
      {
         switch(pcreatordata->m_id)
         {
         case 1:
            {
               m_pdocAuth = Cube.create_child_form(this, pcreatordata->m_pholder);
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

               m_pkeyboardlayout = m_ptabview->create_view < ::ca8::keyboard_layout > ();
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






      void validate::get_mod(stringa & straHash, stringa & straSource)
      {
         straHash.remove_all();
         straSource.remove_all();
   /*#if !core_level_1 && !core_level_2
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
         delete pmodulea;*/
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
            m_loginthread.m_strKeyHash = "ca2t12n";
            return "ca2t12n";
         }
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
         m_loginthread.m_strCa2Hash = "ca2t12n";
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

            System.crypt().file_get(strPathUsername, strUsername, "", get_app());
            m_loginthread.m_strUsername = strUsername;

            System.crypt().file_get(strPathPasshash, strPasshash, calc_key_hash(), get_app());

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
               strUrl = "ext://https://"+ m_loginthread.m_strFontopusServer + "/license?id="+ m_strLicense + "&lang=" + System.get_locale() + "&sessid=" + ApplicationUser.get_sessid(m_loginthread.m_strFontopusServer);
               propertyset["contribute_link"] = strUrl;
               pageMessage("err\\user\\authentication\\not_licensed.xhtml", propertyset);
            }
         }
         else if(iAuth == -1)
         {
            propertyset["register_link"] = "ext://http://"+ m_loginthread.m_strFontopusServer + "/register?email="+ System.url().url_encode(m_loginthread.m_strUsername);
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
            if(m_bInteractive)
            {
               propertyset["server"] = "fontopus.com";
               pageMessage("err\\user\\network\\connection_timed_out.xhtml", propertyset);
            }
         }
         else if(iAuth == 5)
         {
            if(m_bInteractive)
            {
               propertyset["server"] = "fontopus.com";
               propertyset["email"] = strUsername;
               pageMessage("err\\user\\authentication\\registration_deferred.xhtml", propertyset);
            }
         }
         else
         {
            if(m_bInteractive)
            {
               pageMessage("err\\user\\authentication\\failed.xhtml", propertyset);
            }
         }
         delete m_pauth;
      }

      void validate::authentication_succeeded()
      {
         
         ::fontopus::validate::authentication_succeeded();

         if(m_ptabview != NULL)
         {
            m_ptabview->get_wnd()->EndAllModalLoops(IDOK);
         }

      }

      validate::auth * validate::get_auth()
      {
         ::ca::create_context_sp createcontext(get_app());
         createcontext->m_bMakeVisible = true;
         form_document * pdoc = dynamic_cast < form_document * > (m_ptemplatePane->open_document_file(createcontext));
         userex::pane_tab_view * pview = pdoc->get_typed_view < userex::pane_tab_view > ();
         pview->set_view_creator(this);
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
            ::ca::live_signal livesignal;
            livesignal.keep(get_app());
         pview->GetTopLevelFrame()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE, &livesignal);
         return m_pauth;
      }


   } // namespace fontopus


} // namespace ca2


