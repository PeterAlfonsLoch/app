#include "framework.h"


namespace ca2
{


   application::application()
   {

      m_eexclusiveinstance       = ::radix::ExclusiveInstanceNone;
      m_pmutexLocal              = NULL;
      m_pmutexGlobal             = NULL;
      m_peventReady              = NULL;
      m_pmapKeyPressed           = NULL;
      m_bLicense                 = true;
      m_strLocale                = "_std";
      m_strSchema                = "_std";

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

   string application::get_schema()
   {
      return m_strSchema;
   }

   string application::get_locale_schema_dir()
   {

      return System.dir().simple_path(get_locale(), get_schema());

   }

   string application::get_locale_schema_dir(const string & strLocale)
   {

      if(strLocale.is_empty())
         return System.dir().simple_path(get_locale(), get_schema());
      else
         return System.dir().simple_path(strLocale, get_schema());

   }

   string application::get_locale_schema_dir(const string & strLocale, const string & strSchema)
   {
      if(strLocale.is_empty())
      {
         if(strSchema.is_empty())
            return System.dir().simple_path(get_locale(), get_schema());
         else
            return System.dir().simple_path(get_locale(), strSchema);
      }
      else
      {
         if(strSchema.is_empty())
            return System.dir().simple_path(strLocale, get_schema());
         else
            return System.dir().simple_path(strLocale, strSchema);
      }
   }

   void application::set_locale(const char * lpcsz, bool bUser)
   {
      m_strLocale = lpcsz;
      on_set_locale(lpcsz, bUser);
   }

   void application::set_schema(const char * lpcsz, bool bUser)
   {
      m_strSchema = lpcsz;
      on_set_schema(lpcsz, bUser);
   }

   void application::on_set_locale(const char * lpcsz, bool bUser)
   {
      UNREFERENCED_PARAMETER(bUser);
      UNREFERENCED_PARAMETER(lpcsz);
      //System.appa_load_string_table();
   }

   void application::on_set_schema(const char * lpcsz, bool bUser)
   {
      UNREFERENCED_PARAMETER(bUser);
      UNREFERENCED_PARAMETER(lpcsz);
      //System.appa_load_string_table();
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
      load_string_table("", "");
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

      m_dwAlive = ::get_tick_count();

      if(!::xml::application::initialize1())
         return false;

      string strSystem = Application.file().as_string(System.dir().appdata("langstyle_settings.xml"));

      ::xml::document docSystem(get_app());

      string strLocaleSystem;
      string strSchemaSystem;
      if(docSystem.load(strSystem))
      {
         if(docSystem.get_child("lang") != NULL)
         {
            strLocaleSystem = docSystem.get_child("lang")->get_value();
         }
         if(docSystem.get_child("style") != NULL)
         {
            strSchemaSystem = docSystem.get_child("style")->get_value();
         }
      }

      string strLocale;

      string strSchema;

#ifdef METROWIN

      stringa stra;

      Platform::String ^ str = ::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride;

      stra.explode("-", ::str(str));

      strLocale = stra[0];

      strSchema = stra[0];

#elif defined(WINDOWS)
      LANGID langid = ::GetUserDefaultLangID();
#define SPR_DEUTSCH LANG_GERMAN
      if(langid == LANG_SWEDISH)
      {
         strLocale = "se";
         strSchema = "se";
      }
      else if(langid == MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN))
      {
         strLocale = "pt-br";
         strSchema = "pt-br";
      }
      else if(PRIMARYLANGID(langid) == SPR_DEUTSCH)
      {
         strLocale = "de";
         strSchema = "de";
      }
      else if(PRIMARYLANGID(langid) == LANG_ENGLISH)
      {
         strLocale = "en";
         strSchema = "en";
      }
      else if(PRIMARYLANGID(langid) == LANG_JAPANESE)
      {
         strLocale = "jp";
         strSchema = "jp";
      }
      else if(PRIMARYLANGID(langid) == LANG_POLISH)
      {
         strLocale = "pl";
         strSchema = "pl";
      }
#endif

      if(strLocale.is_empty())
         strLocale = "se";

      if(strSchema.is_empty())
         strSchema = "se";

      if(strLocaleSystem.has_char())
         strLocale = strLocaleSystem;

      if(strSchemaSystem.has_char())
         strSchema = strSchemaSystem;

      if(Sys(this).directrix().m_varTopicQuery["locale"].get_string().has_char())
         strLocale = Sys(this).directrix().m_varTopicQuery["locale"];

      if(Sys(this).directrix().m_varTopicQuery["schema"].get_string().has_char())
         strSchema = Sys(this).directrix().m_varTopicQuery["schema"];

      if(App(this).directrix().m_varTopicQuery["locale"].get_string().has_char())
         strLocale = App(this).directrix().m_varTopicQuery["locale"];

      if(App(this).directrix().m_varTopicQuery["schema"].get_string().has_char())
         strSchema = App(this).directrix().m_varTopicQuery["schema"];



      set_locale(strLocale, false);
      set_schema(strSchema, false);


      str_context()->localeschema().m_idaLocale.add(strLocale);
      str_context()->localeschema().m_idaSchema.add(strSchema);


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

#ifdef WINDOWSEX
   bool Is_Vista_or_Later ()
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
         dwlConditionMask) != FALSE;
   }
#endif

   bool application::initialize()
   {

      m_dwAlive = ::get_tick_count();

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
#ifdef WINDOWSEX
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
      post_thread_message(WM_QUIT, 0, 0);
   }


   ::ca::application * application::get_app() const
   {

      return ex2::application::get_app();

   }

   string application::get_license_id()
   {

      return m_strAppId;

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
      ::xml::document doc(this);
      if(id.is_text())
      {
         if(!doc.load(id))
         {
            return load_cached_string_by_id(str, id, NULL, bLoadStringTable);
         }
      }
      ::xml::node * pnodeRoot = doc.get_root();
      if(pnodeRoot->get_name() == "string")
      {
         string strId = pnodeRoot->attr("id");
         string strValue = pnodeRoot->get_value();
         return load_cached_string_by_id(str, strId, strValue, bLoadStringTable);
      }
      str = doc.get_name();
      return true;
   }

   bool application::load_cached_string_by_id(string & str, id id, const char * pszFallbackValue, bool bLoadStringTable)
   {
      string strId(*id.m_pstr);
      string strTable;
      string strString;
      string_to_string_map * pmap = NULL;
      index iFind = 0;
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
         load_string_table(strTable, "");
         return load_cached_string_by_id(str, id, pszFallbackValue, false);
      }
      if(pszFallbackValue == NULL)
         str = strId;
      else
         str = pszFallbackValue;
      return true;
   }

   void application::load_string_table(const char * pszApp, const char * pszId)
   {
      string strApp(pszApp);
      string strMatter;
      string strLocator;

      if(strApp.is_empty())
      {
         strLocator = System.dir().appmatter_locator(this);
      }
      else
      {
         strLocator = System.dir().appmatter_locator(strApp);
      }

      if(strMatter.is_empty())
      {
         strMatter = "stringtable.xml";
      }
      else if(System.file().extension(strMatter) != "xml")
      {
         strMatter += ".xml";
      }

      string strTableId = strApp;

      if(pszId != NULL && *pszId != '\0')
      {
         strTableId += "\\";
         strTableId += pszId;
      }

      ::xml::document doc(get_app());
      string strFilePath = System.dir().matter_from_locator(App(this).str_context(), strLocator, strMatter);
      if(!System.file().exists(strFilePath, this))
      {
         if(m_stringtablemap[pszId] != NULL)
            delete m_stringtablemap[pszId];
         m_stringtablemapStd.set_at(pszId, new string_to_string_map);
         return;
      }
      string strFile = Application.file().as_string(strFilePath);
      if(!doc.load(strFile))
         return;
      string_to_string_map * pmapNew = new string_to_string_map;
      for(int i = 0; i < doc.get_root()->children().get_count(); i++)
      {
         string strId      = doc.get_root()->child_at(i)->attr("id");
         string strValue   = doc.get_root()->child_at(i)->get_value();
         pmapNew->set_at(strId, strValue);
      }

      string_to_string_map * pmapOld = m_stringtablemap[strTableId];

      m_stringtablemap[strTableId] = NULL;

      if(pmapOld != NULL)
      {

         try
         {

            delete pmapOld;

         }
         catch(...)
         {

         }

      }

      m_stringtablemap[strTableId] = pmapNew;
      ASSERT(m_stringtablemap[strTableId] == pmapNew);
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
#ifdef WINDOWSEX
         ::ShellExecuteA(NULL, "open", pszLink, NULL, NULL, SW_SHOW);
         return true;
#elif defined METROWIN
#pragma push_macro("System")
#undef System
         ::Windows::Foundation::Uri ^ uri = ref new ::Windows::Foundation::Uri(rtstr(pszLink));
         ::Windows::System::LauncherOptions ^ options = ref new ::Windows::System::LauncherOptions();
         options->TreatAsUntrusted = false;
         bool success = ::wait(::Windows::System::Launcher::LaunchUriAsync(uri, options));
#pragma pop_macro("System")
#else
         throw not_implemented(get_app());
#endif
      }
      else
      {
         return System.open_link(pszLink, pszTarget);
      }
   }

   ::user::interaction * application::uie_from_point(point pt)
   {
      user::interaction_ptr_array wnda = frames();
      user::oswindow_array oswindowa;
      wnda.get_wnda(oswindowa);
      user::window_util::SortByZOrder(oswindowa);
      for(int i = 0; i < oswindowa.get_count(); i++)
      {
         ::user::interaction * puieWindow = wnda.find_first(oswindowa[i]);
         ::user::interaction * puie = puieWindow->_001FromPoint(pt);
         if(puie != NULL)
            return puie;
      }
      return NULL;
   }

#ifdef BSD_STYLE_SOCKETS

   void application::get_time(struct timeval *p)
   {
      ::ex2::application::get_time(p);
   }

#endif

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
      if(m_strId == "session" || m_strAppName == "session")
      {
         if(!directrix().m_varTopicQuery.has_property("session_start"))
         {
            System.post_thread_message(WM_QUIT, 0, 0);
         }
      }
      else
      {
         System.post_thread_message(WM_QUIT, 0, 0);
      }


      return true;
   }

   bool application::on_uninstall()
   {
      return true;
   }

   bool application::on_run_uninstall()
   {

      if(m_strId == "session")
      {
         if(!directrix().m_varTopicQuery.has_property("session_start"))
         {
            System.post_thread_message(WM_QUIT, 0, 0);
         }
      }
      else
      {
         System.post_thread_message(WM_QUIT, 0, 0);
      }

      return true;
   }


   bool application::is_key_pressed(int iKey)
   {

      if(is_session())
      {
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
      if(is_session())
      {
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
         peventReady = new manual_reset_event(get_app());
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
//            MESSAGE msg;
            while(m_bRun)
            {
               // phase1: check to see if we can do idle work
               while (!has_message())
               {
                  if(!is_alive())
                  {
                     return false;
                  }
                  if(m_bReady)
                  {
                     if(m_iReturnCode == 0)
                        goto ok;
                     return false;
                  }
                  Sleep(84);
               }
               pump_message();
            }
         }
         catch(...)
         {
            return false;
         }
         ok:;
      }

      return true;

   }

   bool application::is_running()
   {
      return is_alive();
   }


} //namespace _001ca1api00001

