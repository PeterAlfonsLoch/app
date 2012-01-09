#include "StdAfx.h"


namespace ca2
{


   application::application()
   {
      m_eexclusiveinstance       = ::radix::ExclusiveInstanceNone;
      m_pmutexLocal              = NULL;
      m_pmutexGlobal             = NULL;
      m_peventReady              = NULL;
      m_pmapKeyPressed           = NULL;
   }

   application::~application()
   {
   }

   void application::install_message_handling(::gen::message::dispatch * pdispatch)
   {
      ::ex2::application::install_message_handling(pdispatch);
      IGUI_WIN_MSG_LINK(WM_APP + 2043, pdispatch, this, &::ca2::application::_001OnApplicationRequest);
   }


   string application::get_locale()
   {
      return m_strLocale;
   }

   string application::get_style()
   {
      return m_strStyle;
   }

   string application::get_locale_style_dir(const char * pszLocale, const char * pszStyle)
   {
      string strLocale(pszLocale);
      string strStyle(pszStyle);
      if(strLocale.is_empty())
         strLocale = get_locale();
      if(strStyle.is_empty())
         strStyle = get_style();
      return System.dir().path(strLocale, strStyle);
   }

   void application::set_locale(const char * lpcsz, bool bUser)
   {
      m_strLocale = lpcsz;
      on_set_locale(lpcsz, bUser);
   }

   void application::set_style(const char * lpcsz, bool bUser)
   {
      m_strStyle = lpcsz;
      on_set_style(lpcsz, bUser);
   }

   void application::on_set_locale(const char * lpcsz, bool bUser)
   {
      UNREFERENCED_PARAMETER(bUser);
      UNREFERENCED_PARAMETER(lpcsz);
      if(m_spwindowMessage.m_p != NULL)
      {
         m_spwindowMessage->SetTimer(123, 884, NULL);
      }
   }

   void application::on_set_style(const char * lpcsz, bool bUser)
   {
      UNREFERENCED_PARAMETER(bUser);
      UNREFERENCED_PARAMETER(lpcsz);
      if(m_spwindowMessage.m_p != NULL)
      {
         m_spwindowMessage->SetTimer(123, 884, NULL);
      }
   }


   bool application::base_support()
   {
      return true;
   };

   string application::message_box(const char * pszMatter, gen::property_set & propertyset)
   {
      UNREFERENCED_PARAMETER(propertyset);
      UNREFERENCED_PARAMETER(pszMatter);
      return "";
   }

   bool application::bergedge_start()
   {
      if(!gen::application::bergedge_start())
         return false;
      return true;
   }

   void application::load_string_table()
   {
      load_string_table("");
   }

   /*::fontopus::user * application::create_user(const char * pszLogin)
   {
      return NULL;
   }*/

   ::fontopus::user * application::create_current_user()
   {
      return NULL;
   /*   string str = get_current_user_login();
      return create_user(str);*/
   }

   /*string application::get_current_user_login()
   {
      return "";
   }*/


   bool application::get_auth(const char * pszForm, string & strUsername, string & strPassword)
   {
      UNREFERENCED_PARAMETER(pszForm);
      UNREFERENCED_PARAMETER(strUsername);
      UNREFERENCED_PARAMETER(strPassword);
      return false;
   }




   bool application::initialize1()
   {

      m_dwAlive = ::GetTickCount();

      if(m_biasCalling.m_strLicense.has_char() && m_strLicense.is_empty())
      {
         m_strLicense = m_biasCalling.m_strLicense;
      }

      if(!::xml::application::initialize1())
         return false;

      string strSystem = Application.file().as_string(System.dir().appdata("langstyle_settings.xml"));
      ::xml::node nodeSystem(get_app());
      string strLangSystem;
      string strStyleSystem;
      if(nodeSystem.load(strSystem))
      {
         if(nodeSystem.get_child("lang") != NULL)
         {
            strLangSystem = nodeSystem.get_child("lang")->m_strValue;
         }
         if(nodeSystem.get_child("style") != NULL)
         {
            strStyleSystem = nodeSystem.get_child("style")->m_strValue;
         }
      }

      string strLang;
      string strStyle;
      LANGID langid = ::GetUserDefaultLangID();
#ifdef WINDOWS
#define SPR_DEUTSCH LANG_GERMAN
      if(langid == LANG_SWEDISH)
      {
         strLang = "se";
         strStyle = "se";
      }
      else if(langid == MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN))
      {
         strLang = "pt-br";
         strStyle = "pt-br";
      }
      else if(PRIMARYLANGID(langid) == SPR_DEUTSCH)
      {
         strLang = "de";
         strStyle = "de";
      }
      else if(PRIMARYLANGID(langid) == LANG_ENGLISH)
      {
         strLang = "en";
         strStyle = "en";
      }
      else if(PRIMARYLANGID(langid) == LANG_JAPANESE)
      {
         strLang = "jp";
         strStyle = "jp";
      }
      else if(PRIMARYLANGID(langid) == LANG_POLISH)
      {
         strLang = "pl";
         strStyle = "pl";
      }
#endif
      if(strLang.is_empty())
         strLang = "se";
      if(strStyle.is_empty())
         strStyle = "se";

      if(strLangSystem.has_char())
         strLang = strLangSystem;
      if(strStyleSystem.has_char())
         strStyle = strStyleSystem;

      set_locale(strLang, false);
      set_style(strStyle, false);

      str_context()->param_locale_ex().add(strLang);
      str_context()->param_style_ex().add(strStyle);




      return ex2::application::initialize1();
   }

   bool application::finalize()
   {
      try
      {
         ex2::application::finalize();
      }
      catch(...)
      {
      }
      return true;
   }

#ifdef WINDOWS
   BOOL Is_Vista_or_Later ()
   {
      OSVERSIONINFOEX osvi;
      DWORDLONG dwlConditionMask = 0;
      byte op=VER_GREATER_EQUAL;

      // Initialize the OSVERSIONINFOEX structure.

      ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
      osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
      osvi.dwMajorVersion = 6;
   //   osvi.dwMinorVersion = 1;
   //   osvi.wServicePackMajor = 0;
   //   osvi.wServicePackMinor = 0;

      // Initialize the condition mask.

      VER_SET_CONDITION( dwlConditionMask, VER_MAJORVERSION, op );
      //VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION, op );
      //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMAJOR, op );
      //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMINOR, op );

      // Perform the test.

      return VerifyVersionInfo(
         &osvi,
         VER_MAJORVERSION | VER_MINORVERSION |
         VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR,
         dwlConditionMask);
   }
#endif

   bool application::initialize()
   {

      m_dwAlive = ::GetTickCount();

      if(is_system())
      {
         if(guideline().m_varTopicQuery.propset().has_property("save_processing"))
         {
            System.savings().save(gen::resource_processing);
         }
         if(guideline().m_varTopicQuery.propset().has_property("save_blur_back"))
         {
            System.savings().save(gen::resource_blur_background);
         }
         if(guideline().m_varTopicQuery.propset().has_property("save_transparent_back"))
         {
            System.savings().save(gen::resource_translucent_background);
         }
      }

      if(directrix().m_varTopicQuery.propset().has_property("install"))
      {
         // ex2 level app install
         if(!Ex2OnAppInstall())
            return false;
      }
      else if(directrix().m_varTopicQuery.propset().has_property("uninstall"))
      {
         // ex2 level app uninstall
         if(!Ex2OnAppUninstall())
            return false;
      }
      else
      {
#ifdef WINDOWS
         // when this process is started in the context of a system account,
         // for example, this code ensure that the process will
         // impersonate a loggen on ::fontopus::user
         HANDLE hprocess;
         HANDLE htoken;

         hprocess = ::GetCurrentProcess();

         if(!OpenProcessToken(
               hprocess,
               TOKEN_ALL_ACCESS,
               &htoken))
            return false;

         if(!ImpersonateLoggedOnUser(htoken))
         {
            TRACELASTERROR();
            return false;
         }
#endif
      }

      if(!::xml::application::initialize())
         return false;

      return true;
   }

   void application::pre_translate_message(gen::signal_object * pobj)
   {
      SCAST_PTR(gen::message::base, pbase, pobj);
      if(pbase->m_uiMessage == WM_USER + 124 && pbase->m_pwnd == NULL)
      {
   /*      OnMachineEvent((flags < machine_event::e_flag> *) pmsg->lParam);
         delete (flags < machine_event::e_flag> *) pmsg->lParam;*/
         pbase->m_bRet = true;
         return;
      }
      return gen::application::pre_translate_message(pobj);
   }

   void application::_001OnApplicationRequest(gen::signal_object * pobj)
   {
      SCAST_PTR(gen::message::base, pbase, pobj);
      if(pbase->m_wparam == 2)
      {
         // when wparam == 2 lparam is a pointer to a gen::command_fork
         // that should be treated as gen::command_line on request, i.e.,
         // a fork whose Forking part has been done, now
         // the parameters are going to be passed to this new application
         ::ca::create_context * pcreatecontext = (::ca::create_context *) pbase->m_lparam;
         try
         {
            on_request(pcreatecontext);
         }
         catch(...)
         {
         }
         pcreatecontext->m_spCommandLine->m_eventReady.SetEvent();
      }
   }


   ::mutex * application::get_local_mutex()
   {
      return m_pmutexLocal;
   }

   ::mutex * application::get_global_mutex()
   {
      return m_pmutexGlobal;
   }

   void application::_001CloseApplication()
   {
      set_run(false);
      PostThreadMessage(WM_QUIT, 0, 0);
   }


   ::ca::application * application::get_app() const
   {
      return ex2::application::get_app();
   }

   void application::process(machine_event_data * pdata)
   {
      if(pdata->m_fixed.m_bRequestCloseApplication)
      {
         _001CloseApplication();
      }
   }


   void application::EnableShellOpen()
   {
      ASSERT(m_atomApp == 0 && m_atomSystemTopic == 0); // do once
      if (m_atomApp != 0 || m_atomSystemTopic != 0)
      {
         return;
      }

      // Win95 & Win98 sends a WM_DDE_INITIATE with an atom that points to the
      // short file name so we need to use the short file name.
      string strShortName;
      strShortName = get_module_file_path();

      // strip out path
      //string strFileName = ::PathFindFileName(strShortName);
      // strip out extension
      //LPTSTR pszFileName = strFileName.GetBuffer();
      //::PathRemoveExtension(pszFileName);
      //strFileName.ReleaseBuffer();

//      m_atomApp = ::GlobalAddAtom(strFileName);
  //    m_atomSystemTopic = ::GlobalAddAtom("system");
   }


   string application::load_string(id id)
   {
      string str;
      if(!load_string(str, id))
      {
         return (const char *) id;
      }
      return str;
   }

   bool application::load_string(string & str, id id)
   {
      if(!load_cached_string(str, id, true))
      {
         return false;
      }
      return true;
   }

   bool application::load_cached_string(string & str, id id, bool bLoadStringTable)
   {
      ::xml::node node(this);
      if(id.is_text())
      {
         if(!node.load(id))
         {
            return load_cached_string_by_id(str, id, NULL, bLoadStringTable);
         }
      }
      if(node.m_strName == "string")
      {
         return load_cached_string_by_id(str, node.attr("id"), node.m_strValue, bLoadStringTable);
      }
      str = node.m_strValue;
      return true;
   }

   bool application::load_cached_string_by_id(string & str, id id, const char * pszFallbackValue, bool bLoadStringTable)
   {
      string strId(id.m_psz);
      string strTable;
      string strString;
      string_to_string_map * pmap = NULL;
      int iFind = 0;
      if((iFind = strId.find(':')) <= 0)
      {
         strTable = "";
         strString = strId;
      }
      else
      {
         strTable = strId.Mid(0, iFind);
         strString = strId.Mid(iFind + 1);
      }
      if(m_stringtablemapStd.Lookup(strTable, pmap))
      {
         if(pmap->Lookup(strString, str))
         {
            return true;
         }
      }
      else if(m_stringtablemap.Lookup(strTable, pmap))
      {
         if(pmap->Lookup(strString, str))
         {
            return true;
         }
      }
      else if(bLoadStringTable)
      {
         load_string_table(strTable);
         return load_cached_string_by_id(str, id, pszFallbackValue, false);
      }
      if(pszFallbackValue == NULL)
         str = strId;
      else
         str = pszFallbackValue;
      return true;
   }

   void application::load_string_table(const char * pszId)
   {
      string strMatter;
      strMatter = pszId;
      if(System.file().extension(strMatter) != "xml")
      {
         strMatter += "\\stringtable.xml";
      }
      ::xml::node node(get_app());
      string strFilePath = Application.dir().matter(strMatter);
      if(!System.file().exists(strFilePath, this))
      {
         if(m_stringtablemap[pszId] != NULL)
            delete m_stringtablemap[pszId];
         m_stringtablemapStd.set_at(pszId, new string_to_string_map);
         return;
      }
      string strFile = Application.file().as_string(strFilePath);
      if(!node.load(strFile))
         return;
      string_to_string_map * pmapNew = new string_to_string_map;
      for(int i = 0; i < node.children().get_count(); i++)
      {
         string strId      = node.child_at(i)->attr("id");
         string strValue   = node.child_at(i)->m_strValue;
         pmapNew->set_at(strId, strValue);
      }
      if(m_stringtablemap[pszId] != NULL)
         delete m_stringtablemap[pszId];
      m_stringtablemap[pszId] = pmapNew;
      ASSERT(m_stringtablemap[pszId] == pmapNew);
   }


   int application::run()
   {
      TRACE("::ca2::application::run");
      /*if(directrix().m_varTopicQuery.has_property("install"))
      {
         on_run_install();
      }
      else if(directrix().m_varTopicQuery.has_property("uninstall"))
      {
         on_run_uninstall();
      }*/
      return ex2::application::run();
   }

   bool application::open_link(const char * pszLink, const char * pszTarget)
   {
      if(is_system())
      {
#ifdef WINDOWS
         ::ShellExecuteA(NULL, "open", pszLink, NULL, NULL, SW_SHOW);
         return true;
#else
         throw not_implemented_exception();
#endif
      }
      else
      {
         return System.open_link(pszLink, pszTarget);
      }
   }

   ::user::interaction * application::uie_from_point(point pt)
   {
      user::LPWndArray wnda = frames();
      user::HWNDArray hwnda;
      wnda.get_wnda(hwnda);
      user::WndUtil::SortByZOrder(hwnda);
      for(int i = 0; i < hwnda.get_count(); i++)
      {
         ::user::interaction * puieWindow = wnda.find_first(hwnda[i]);
         ::user::interaction * puie = puieWindow->_001FromPoint(pt);
         if(puie != NULL)
            return puie;
      }
      return NULL;
   }

   void application::get_time(struct timeval *p)
   {
      ::ex2::application::get_time(p);
   }

   void application::set_env_var(const string & var,const string & value)
   {
      ::ex2::application::set_env_var(var, value);
   }

   unsigned long application::get_thread_id()
   {
      return ::ex2::application::get_thread_id();
   }

   void application::message_window_message_handler(gen::signal_object * pobj)
   {
      SCAST_PTR(gen::message::base, pbase, pobj);
      if(pbase->m_uiMessage == WM_TIMER)
      {
         SCAST_PTR(gen::message::timer, ptimer, pobj);
         if(ptimer->m_nIDEvent == 123)
         {
            m_spwindowMessage->KillTimer(ptimer->m_nIDEvent);
            frames().send_message_to_descendants(gen::application::APPM_LANGUAGE);
            System.appa_load_string_table();
         }
      }
   }

   bool application::on_install()
   {
      return true;
   }

   bool application::on_run_install()
   {
      if(m_strId == "bergedge" || m_strAppName == "bergedge")
      {
         if(!directrix().m_varTopicQuery.has_property("bergedge_start"))
         {
            System.PostThreadMessage(WM_QUIT, 0, 0);
         }
      }
      else
      {
         System.PostThreadMessage(WM_QUIT, 0, 0);
      }


      return true;
   }

   bool application::on_uninstall()
   {
      return true;
   }

   bool application::on_run_uninstall()
   {

      if(m_strId == "bergedge")
      {
         if(!directrix().m_varTopicQuery.has_property("bergedge_start"))
         {
            System.PostThreadMessage(WM_QUIT, 0, 0);
         }
      }
      else
      {
         System.PostThreadMessage(WM_QUIT, 0, 0);
      }

      return true;
   }


   bool application::is_key_pressed(int iKey)
   {

      if(is_session() || is_bergedge() || is_system() || is_cube() || (m_psession == NULL && m_psystem == NULL))
      {
         if((is_system() || is_cube()) && m_psession != NULL && !is_bergedge() && !is_session())
         {
            return Sess(this).is_key_pressed(iKey);
         }
         if(m_pmapKeyPressed  == NULL)
         {
            m_pmapKeyPressed = new ::collection::map < int, int, bool, bool >;
         }
         bool bPressed = false;
         m_pmapKeyPressed->Lookup(iKey, bPressed);
         return bPressed;
      }
      else if(m_psession != NULL)
      {
         return Sess(this).is_key_pressed(iKey);
      }
      else if(m_psystem != NULL)
      {
         return Sys(this).is_key_pressed(iKey);
      }
      else
      {
         throw "not expected";
      }

   }

   void application::set_key_pressed(int iKey, bool bPressed)
   {
      if(is_session() || is_bergedge() || is_system() || is_cube() || (m_psession == NULL && m_psystem == NULL))
      {
         if((is_system() || is_cube()) && m_psession != NULL && !is_bergedge() && !is_session())
         {
            return Sess(this).set_key_pressed(iKey, bPressed);
         }
         if(m_pmapKeyPressed  == NULL)
         {
            m_pmapKeyPressed = new ::collection::map < int, int, bool, bool >;
         }
         (*m_pmapKeyPressed)[iKey] = bPressed;
      }
      else if(m_psession != NULL)
      {
         return Sess(this).set_key_pressed(iKey, bPressed);
      }
      else if(m_psystem != NULL)
      {
         return Sys(this).set_key_pressed(iKey, bPressed);
      }
      else
      {
         throw "not expected";
      }
   }

   bool application::start_application(bool bSynch, ::ca::application_bias * pbias)
   {
/*      try
      {
         if(pbias != NULL)
         {
            papp->m_puiInitialPlaceHolderContainer = pbias->m_puiParent;
         }
      }
      catch(...)
      {
      }*/
      try
      {
         if(pbias != NULL)
         {
            if(pbias->m_pcallback != NULL)
            {
               pbias->m_pcallback->connect_to(this);
            }
         }
      }
      catch(...)
      {
      }

      manual_reset_event * peventReady = NULL;

      if(bSynch)
      {
         peventReady = new manual_reset_event();
         m_peventReady = peventReady;
         peventReady->ResetEvent();
      }

      ::ca::thread_sp::create(this);
      //dynamic_cast < ::radix::thread * > (papp->::ca::thread_sp::m_p)->m_p = papp->::ca::thread_sp::m_p;
      dynamic_cast < ::radix::thread * > (::ca::thread_sp::m_p)->m_p = this;
      if(pbias != NULL)
      {
         m_biasCalling = *pbias;
      }
      Begin();

      if(bSynch)
      {
         try
         {
            keep_alive();
         }
         catch(...)
         {
         }
         try
         {
            while(true)
            {
               if(!is_alive())
               {
                  return false;
               }
               if(m_bReady)
               {
                  if(m_iReturnCode == 0)
                     break;
                  return false;
               }
               Sleep(84);
            }
         }
         catch(...)
         {
            return false;
         }
      }

      return true;

   }


} //namespace _001ca1api00001

