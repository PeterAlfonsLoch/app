#pragma once


namespace ca2
{


   class signal_details;
   class signal;


} // namespace ca2


namespace user
{


   class interaction;


}


namespace uinteraction
{

   class uinteraction;

}


typedef  void (* PFN_ca2_factory_exchange)(sp(::application) papp);


namespace plane
{


   class application;
   class system;


}


namespace fontopus
{


   class user;


} // namespace fontopus


namespace fontopus
{


   class user;


} // namespace fontopus








namespace ca2
{


 CLASS_DECL_ca2 UINT c_cdecl application_thread_procedure(LPVOID pvoid);

   typedef sp(::application) (* LPFN_instantiate_application)(sp(::application) pappParent, const char * pszId);

   extern CLASS_DECL_ca2 LPFN_instantiate_application g_lpfn_instantiate_application;


   class type;
   class system;
   class window_draw;


   enum EExclusiveInstance
   {
      ExclusiveInstanceNone,
      ExclusiveInstanceLocal,
      ExclusiveInstanceLocalId,
      ExclusiveInstanceGlobal,
      ExclusiveInstanceGlobalId,
      ExclusiveInstanceLicense,
   };


   

   class application_base;


   class CLASS_DECL_ca2 application_ptra :
      virtual public spa(application_base)
   {
   public:



   };


   class CLASS_DECL_ca2 application_base :
      virtual public ::ca::application,
      virtual public ::ca2::live_object,
      virtual public ::ca2::thread
   {
   public:

      // Running args (can be changed in initialize_instance)
      // Human-redable name of the application. Normally set in
      // constructor or retreived from __IDS_APP_TITLE.
      smart_pointer < application_base >  m_p;
      string                                          m_strAppId;
      string                                          m_strLibraryName;
      ::plane::application *                          m_pappThis;
      //::plane::application *         m_pappCube;


      virtual void construct() = 0;


      virtual bool process_initialize() = 0;

      virtual bool initialize1() = 0;
      virtual bool initialize2() = 0;
      virtual bool initialize3() = 0;

      virtual bool initialize() = 0;

      virtual void LockTempMaps() = 0;
      virtual bool UnlockTempMaps(bool bDeleteTemps = TRUE) = 0;
      virtual void TermThread(HINSTANCE hInstTerm) = 0;


#ifdef METROWIN
      virtual sp(::user::interaction) window_from_os_data(void * pdata) = 0;
      virtual sp(::user::interaction) window_from_os_data_permanent(void * pdata) = 0;
#else
      virtual sp(::ca2::window) window_from_os_data(void * pdata) = 0;
      virtual sp(::ca2::window) window_from_os_data_permanent(void * pdata) = 0;
#endif

      virtual sp(::ca2::window) FindWindow(const char * lpszClassName, const char * lpszWindowName) = 0;
      virtual sp(::ca2::window) FindWindowEx(oswindow oswindowParent, oswindow oswindowChildAfter, const char * lpszClass, const char * lpszWindow) = 0;

      virtual string get_version() = 0;

      virtual ::ca2::thread * GetThread() = 0;
      virtual void set_thread(::ca2::thread * pthread) = 0;

      virtual void SetCurrentHandles() = 0;

#ifndef METROWIN
      virtual void get_time(timeval *p) = 0;
#endif
      virtual void set_env_var(const string & var,const string & value) = 0;
      virtual uint32_t get_thread_id() = 0;


      virtual bool set_main_init_data(main_init_data * pdata) = 0;

      virtual bool is_session() = 0;
      virtual bool is_system() = 0;

      virtual bool is_serviceable() = 0;

      virtual bool _001OnDDECommand(const char * lpcsz) = 0;
      virtual void _001EnableShellOpen() = 0;
      virtual sp(::user::document_interface) _001OpenDocumentFile(var varFile) = 0;
      virtual void _001OnFileNew(signal_details * pobj) = 0;

      virtual void ShowWaitCursor(bool bShow = true) = 0;


      virtual ::user::printer * get_printer(const char * pszDeviceName) = 0;


      virtual bool update_module_paths() = 0;

      virtual string draw2d_get_default_library_name() = 0;
      virtual string multimedia_audio_get_default_library_name() = 0;
      virtual string multimedia_audio_mixer_get_default_library_name() = 0;
      virtual string veriwell_multimedia_music_midi_get_default_library_name() = 0;

   };


   class CLASS_DECL_ca2 application :
      virtual public application_base,
      virtual public command_target_interface,
      virtual public request_interface,
      virtual public ::ca2::message_window_simple_callback
   {
   public:



      const string OAUTHLIB_CONSUMERKEY_KEY;
      const string OAUTHLIB_CALLBACK_KEY;
      const string OAUTHLIB_VERSION_KEY;
      const string OAUTHLIB_SIGNATUREMETHOD_KEY;
      const string OAUTHLIB_SIGNATURE_KEY;
      const string OAUTHLIB_TIMESTAMP_KEY;
      const string OAUTHLIB_NONCE_KEY;
      const string OAUTHLIB_TOKEN_KEY;
      const string OAUTHLIB_TOKENSECRET_KEY;
      const string OAUTHLIB_VERIFIER_KEY;
      const string OAUTHLIB_SCREENNAME_KEY;


      const string OAUTHLIB_TWITTER_REQUEST_TOKEN_URL;
      const string OAUTHLIB_TWITTER_AUTHORIZE_URL;
      const string OAUTHLIB_TWITTER_ACCESS_TOKEN_URL;

      /* Constants */
      const string TWIT_COLON;
      const char TWIT_EOS;

      /* Miscellaneous data used to build twitter URLs*/
      const string TWIT_SEARCHQUERYSTRING;
      const string TWIT_SCREENNAME;
      const string TWIT_USERID;
      const string TWIT_EXTENSIONFORMAT;
      const string TWIT_TARGETSCREENNAME;
      const string TWIT_TARGETUSERID;

      /* Search URLs */
      const string TWIT_SEARCH_URL;

      /* Status URLs */
      const string TWIT_STATUSUPDATE_URL;
      const string TWIT_STATUSSHOW_URL;
      const string TWIT_STATUDESTROY_URL;

      /* Timeline URLs */
      const string TWIT_PUBLIC_TIMELINE_URL;
      const string TWIT_FEATURED_USERS_URL;
      const string TWIT_FRIENDS_TIMELINE_URL;
      const string TWIT_MENTIONS_URL;
      const string TWIT_USERTIMELINE_URL;

      /* Users URLs */
      const string TWIT_SHOWUSERS_URL;
      const string TWIT_SHOWFRIENDS_URL;
      const string TWIT_SHOWFOLLOWERS_URL;

      /* Direct messages URLs */
      const string TWIT_DIRECTMESSAGES_URL;
      const string TWIT_DIRECTMESSAGENEW_URL;
      const string TWIT_DIRECTMESSAGESSENT_URL;
      const string TWIT_DIRECTMESSAGEDESTROY_URL;

      /* Friendships URLs */
      const string TWIT_FRIENDSHIPSCREATE_URL;
      const string TWIT_FRIENDSHIPSDESTROY_URL;
      const string TWIT_FRIENDSHIPSSHOW_URL;

      /* Social graphs URLs */
      const string TWIT_FRIENDSIDS_URL;
      const string TWIT_FOLLOWERSIDS_URL;

      /* Ac::count URLs */
      const string TWIT_ACCOUNTRATELIMIT_URL;

      /* Favorites URLs */
      const string TWIT_FAVORITESGET_URL;
      const string TWIT_FAVORITECREATE_URL;
      const string TWIT_FAVORITEDESTROY_URL;

      /* Block URLs */
      const string TWIT_BLOCKSCREATE_URL;
      const string TWIT_BLOCKSDESTROY_URL;

      /* Saved Search URLs */
      const string TWIT_SAVEDSEARCHGET_URL;
      const string TWIT_SAVEDSEARCHSHOW_URL;
      const string TWIT_SAVEDSEARCHCREATE_URL;
      const string TWIT_SAVEDSEARCHDESTROY_URL;

      /* Trends URLs */
      const string TWIT_TRENDS_URL;
      const string TWIT_TRENDSDAILY_URL;
      const string TWIT_TRENDSCURRENT_URL;
      const string TWIT_TRENDSWEEKLY_URL;
      const string TWIT_TRENDSAVAILABLE_URL;


      ::calculator::calculator                                                                * m_pcalculator;
      ::sockets::sockets                                                                      * m_psockets;
      ::colorertake5::colorertake5                                                            * m_pcolorertake5;
      //string                                                                                    m_strFontopusServer;
      //string                                                                                    m_strMatterUrl;
      //string                                                                                    m_strMatterSecureUrl;

      string_map < string_to_string_map *, string_to_string_map * >               m_stringtablemap;
      string_map < string_to_string_map *, string_to_string_map * >               m_stringtablemapStd;
      manual_reset_event *                                                                      m_peventReady;


      //string                                                                                  m_strLicense;
      bool                                                                                      m_bLicense;
      string                                                                                    m_strBaseSupportId;
      map < ::user::e_key, ::user::e_key, bool, bool > *                            m_pmapKeyPressed;


      string                                                                                    m_strRoot;
      string                                                                                    m_strDomain;
      string                                                                                    m_strLocale;
      string                                                                                    m_strSchema;




      sp(::fs::fs)                        m_spfs;

      bool                          m_bInitializeProDevianMode;
      main_init_data *              m_pinitmaindata;
      bool                          m_bService;
      bool                          m_bZipIsDir;
      ::plane::system *             m_psystem;
      sp(::plane::session)            m_psession;

      class ::ca2::base64                 m_base64;
      signal                              m_signalAppLanguageChange;
      math::math *                        m_pmath;
      geometry::geometry *                m_pgeometry;
      class savings *                     m_psavings;
      string                              m_strCa2ModulePath;
      string                              m_strCa2ModuleFolder;
      string                              m_strModulePath;
      string                              m_strModuleFolder;
      string                              m_strHelpFilePath;
      mutex                               m_mutex;

      string                        m_strInstallType;
      string                        m_strInstallToken;
      //sp(::user::interaction)         m_puiInitialPlaceHolderContainer;
      application_bias        m_biasCalling;


#ifdef WINDOWS


      HGLOBAL                       m_hDevMode;             // printer Dev Mode
      HGLOBAL                       m_hDevNames;            // printer Device Names


#endif


      uint32_t                      m_dwPromptContext;        // help context override for message box
      // LKG
      //   uint32_t m_dwPolicies;      // block for storing boolean system policies

      int32_t                       m_iWaitCursorCount;         // for wait cursor (>0 => waiting)
      HCURSOR                       m_hcurWaitCursorRestore; // old cursor to restore after wait cursor

      uint32_t                      m_dwPolicies;            // block for storing boolean system policies

      EExclusiveInstance            m_eexclusiveinstance;

      sp(::mutex)                    m_pmutexLocal;
      sp(::mutex)                    m_pmutexLocalId;
      sp(::mutex)                     m_pmutexGlobal;
      sp(::mutex)                     m_pmutexGlobalId;
      // This module's hInstance.
#ifdef WINDOWS
      HINSTANCE                     m_hInstance;
#endif
      // Pointer to the command-line.
      string                        m_strCmdLine;
      // Initial state of the application's ::ca2::window; normally,
      // this is an argument to ShowWindow().
      int32_t                           m_nCmdShow;

//      sp(file_manager_interface)      m_pfilemanager;

      // Name of registry key for this application. See
      // SetRegistryKey() member function.
      const char *                  m_pszRegistryKey;

      // Pointer to ::user::document_manager used to manage document templates
      // for this application instance.
      sp(::user::document_manager)            m_pdocmanager;

      // Support for Shift+F1 help mode.

      // TRUE if we're in SHIFT+F1 mode.
      bool                          m_bHelpMode;

      mutex                         m_mutexMatterLocator;
      string                        m_strMatterLocator;

      // set in constructor to override default


      // Default based on this module's path.
      const char *                  m_pszHelpFilePath;

      // Default based on this application's name.
      const char *                  m_pszProfileName;
      // help mode used by the cast
      //      __HELP_TYPE m_eHelpType;

      sp(::user::interaction_ptr_array) m_pframea;


      //CCommandLineInfo* m_pCmdInfo;

      ATOM m_atomApp, m_atomSystemTopic;   // for DDE open
      UINT m_nNumPreviewPages;        // number of default printed pages

      size_t  m_nSafetyPoolSize;      // ideal size



      string                           m_strId;

      //mutex                            m_mutexObjectLock;
      //map < ::waitable *, ::waitable *, mutex *, mutex * > m_mapObjectMutex;

      //mutex                            m_mutexObjectEvent;
      //map < object *, object *, map < int32_t, int32_t, event *, event * > *, map < int32_t, int32_t, event *, event * >  * > m_mapObjectEvent;

      //typedef map < object *, object *, property_set, property_set > oset;
      //oset                             m_mapObjectSet;

      sp(::user::str_context)      m_puserstrcontext;
      bool                             m_bShouldInitializeGTwf;
      point                            m_ptCursor;
      bool                             m_bSessionSynchronizedCursor;
      rect                             m_rectScreen;
      bool                             m_bSessionSynchronizedScreen;
      sp(::user::interaction)          m_pwndMain;
      allocatorsp                m_allocer;


      int32_t                          m_iResourceId;

      string_to_ptr                    m_appmap;

      //BaseIdSpaceIntegerMap      m_imapResource;
      //BaseIdSpaceStringKeyMap    m_strmapResource;
      //   id_space                   m_idspace;
      sp(::uinteraction::uinteraction) m_puinteraction;
      //sp(::user::user)              m_puserbase;
      //sp(::userex::userex) m_puserex;
      sp(::filemanager::filemanager)   m_pfilemanager;
      sp(::usermail::usermail)         m_pusermail;
#ifdef WINDOWSEX
      array < MONITORINFO >            m_monitorinfoa;
      array < MONITORINFO >            m_monitorinfoaDesk;
#endif

      stringa                          m_straAppInterest;
      string_map < oswindow, oswindow > m_mapAppInterest;



      application();
      virtual ~application();


      virtual bool init_main_data(main_init_data * pdata);
      virtual bool set_main_init_data(main_init_data * pdata);

      virtual void construct(const char * pszId);
      virtual void construct();

      virtual bool process_initialize();

      virtual bool initialize1(); // cgcl // first initialization
      virtual bool initialize2(); // cst  // second initialization
      virtual bool initialize3(); // third initialization and so on...

      virtual bool initialize(); // last initialization

      virtual bool bergedge_start();
      virtual bool os_native_bergedge_start();

      virtual int32_t exit();

      virtual int32_t exit_instance();

      virtual bool finalize();

      virtual int32_t main();

      virtual ::ca2::application * get_app() const;

      virtual bool is_system();
      virtual bool is_session();

      virtual bool is_installing();
      virtual bool is_uninstalling();

      virtual bool is_serviceable();

      virtual bool app_map_lookup(const char * psz, void * &);
      virtual void app_map_set(const char * psz, void *);


      virtual void pre_translate_message(signal_details * pobj);


      virtual ::fontopus::user * get_safe_user();


      template < class APP >
      APP & cast_app()
      {
         if(this == NULL)
            return (*(APP *) NULL);
         void * papp;
#ifdef WINDOWS
         if(!app_map_lookup(typeid(APP).name(), papp))
#else
         if(!app_map_lookup(typeid(APP).name(), papp))
#endif
         {
            papp = dynamic_cast < APP * > (this);
#ifdef WINDOWS
            app_map_set(typeid(APP).name(), papp);
#else
            app_map_set(typeid(APP).name(), papp);
#endif
         }
         return (*(APP *) papp);
      }


      virtual void install_message_handling(::ca2::message::dispatch * pdispatch);

      //virtual int32_t run();

      virtual string get_locale();
      virtual string get_schema();
      virtual string get_locale_schema_dir(const string & strLocale, const string & strSchema);
      virtual string get_locale_schema_dir(const string & strLocale);
      virtual string get_locale_schema_dir();

      virtual void EnableShellOpen();

      virtual bool open_link(const string & strLink, const string & pszTarget = "");




      virtual void set_locale(const string & lpcsz, bool bUser);
      virtual void set_schema(const string & lpcsz, bool bUser);
      virtual void on_set_locale(const string & lpcsz, bool bUser);
      virtual void on_set_schema(const string & lpcsz, bool bUser);


      virtual ::fontopus::user * create_current_user();



      virtual void _001CloseApplication();



      virtual bool start_application(bool bSynch, application_bias * pbias);


      virtual bool update_module_paths();


      inline ::calculator::calculator           & calculator      () { return *m_pcalculator    ; }
      inline ::sockets::sockets                 & sockets         () { return *m_psockets       ; }
      inline ::colorertake5::colorertake5       & colorertake5    () { return *m_pcolorertake5  ; }


      //virtual string get_current_user_login();

      virtual string load_string(id id);
      virtual bool load_string(string & str, id id);
      bool load_cached_string(string & str, id id, bool bLoadStringTable);
      bool load_cached_string_by_id(string & str, id id, const string & pszFallbackValue, bool bLoadStringTable);
      void load_string_table(const string & pszApp, const string & pszId);

      virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword);

      virtual bool base_support();

      virtual string message_box(const string & pszMatter, property_set & propertyset);


      virtual void load_string_table();

      virtual sp(::user::interaction) uie_from_point(point pt);

      void process(machine_event_data * pdata);

      ::mutex * get_local_mutex();
      ::mutex * get_global_mutex();

      virtual string get_license_id();

#ifndef METROWIN
      virtual void get_time(timeval *p);
#endif
      virtual void set_env_var(const string & var,const string & value);
      virtual uint32_t get_thread_id();

      virtual void message_window_message_handler(signal_details * pobj);

      virtual bool on_install();
      virtual bool on_uninstall();
      virtual bool on_run_install();
      virtual bool on_run_uninstall();

      DECL_GEN_SIGNAL(_001OnApplicationRequest)

         virtual bool is_key_pressed(::user::e_key ekey);
      virtual void set_key_pressed(::user::e_key ekey, bool bPressed);


      virtual bool is_running();

      DECL_GEN_SIGNAL(on_application_signal);


      virtual void Ex1OnFactoryExchange();
      virtual void draw2d_factory_exchange();

      // open named file, trying to match a regsitered
      // document template to it.
      virtual void on_request(sp(create_context) pline);

      math::math & math();
      geometry::geometry & geometry();
      class savings & savings();

      lemon::array * m_plemonarray;

      lemon::array & lemon_array();

      virtual void defer_add_document_template(sp(::user::document_template) ptemplate);

      // overrides for implementation
      virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
      virtual void ProcessWndProcException(::exception::base* e, signal_details * pobj);


      void EnableModelessEx(bool bEnable);
#ifdef WINDOWS
      HENHMETAFILE LoadEnhMetaFile(UINT uiResource);
#endif
      bool GetResourceData(UINT nID, const char * lcszType, primitive::memory & storage);
      virtual string get_ca2_module_folder();
      virtual string get_ca2_module_file_path();
      virtual string get_module_folder();
      virtual string get_module_file_path();
      virtual string get_module_title();
      virtual string get_module_name();

      static UINT   APPM_LANGUAGE;
      static WPARAM WPARAM_LANGUAGE_UPDATE;
#ifdef WINDOWS
      virtual bool OnMessageWindowMessage(LPMESSAGE lpmsg);
#elif defined(LINUX)
      virtual bool OnMessageWindowMessage(XEvent * pev);
#endif

      bool CreateFileFromRawResource(UINT nID, const char * lcszType, const char * lpcszFilePath);
      virtual LRESULT GetPaintMsgProc(int32_t nCode, WPARAM wParam, LPARAM lParam);


      void OnUpdateRecentFileMenu(cmd_ui * pcmdui) ;

      virtual DECL_GEN_SIGNAL(OnAppLanguage)
         virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);


      class ::ca2::base64 & base64();

      virtual string get_local_mutex_id();
      virtual string get_global_mutex_id();

      virtual bool hex_to_memory(primitive::memory & memory, const char * pszHex);
      virtual void memory_to_hex(string & strHex, primitive::memory & memory);



      virtual bool check_exclusive();
      virtual bool release_exclusive();


      // Sets and initializes usage of HtmlHelp instead of WinHelp.
      void EnableHtmlHelp();

      // Sets and initializes usage of HtmlHelp instead of WinHelp.
      //      void SetHelpMode( __HELP_TYPE eHelpType );
      //    __HELP_TYPE GetHelpMode();

      // Initialization Operations - should be done in initialize_instance

      sp(::user::interaction) get_active_guie();
      sp(::user::interaction) get_focus_guie();
      //      virtual sp(::user::interaction) get_place_holder_container();


      ::user::interaction_ptr_array & frames();
      virtual void add_frame(sp(::user::interaction) pwnd);
      virtual void remove_frame(sp(::user::interaction) pwnd);


      virtual int32_t simple_message_box_timeout(sp(::user::interaction) puiOwner, const char * pszMessage, int32_t iTimeout, UINT fuStyle = MB_OK);
      virtual int32_t simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);


#ifdef WINDOWS

      virtual int32_t simple_message_box(sp(::user::interaction) puiOwner, UINT fuStyle, const char * pszFormat, ...);

#else

      template<typename T, typename... Args>
      int32_t simple_message_box(sp(::user::interaction) puiOwner, UINT fuStyle, const char * pszFormat, const T & value, Args... args)
      {

         string str;

         string_format format(&str, &::string::FormatPrinter, NULL);

         format.printf(pszFormat, value, args...);

         return simple_message_box(puiOwner, str, fuStyle);

      }


#endif


      virtual bool on_run_exception(exception & e);


      // set regsitry key name to be used by application's
      // profile member functions; prevents writing to an INI spfile->
      void SetRegistryKey(const char * lpszRegistryKey);
      void SetRegistryKey(UINT nIDRegistryKey);


      void RegisterShellFileTypes(bool bCompat = FALSE);

      // call after all doc templates are registered
      void UnregisterShellFileTypes();

      // Loads a cursor resource.
      HCURSOR LoadCursor(const char * lpszResourceName) const;
      HCURSOR LoadCursor(UINT nIDResource) const;

      // Loads a stock cursor resource; for for IDC_* values.
      HCURSOR LoadStandardCursor(const char * lpszCursorName) const;

      // Loads an OEM cursor; for all OCR_* values.
      HCURSOR LoadOEMCursor(UINT nIDCursor) const;

#ifdef WINDOWS
      // Loads an icon resource.
      HICON LoadIcon(const char * lpszResourceName) const;
      HICON LoadIcon(UINT nIDResource) const;

      // Loads an icon resource; for stock IDI_ values.
      HICON LoadStandardIcon(const char * lpszIconName) const;

      // Loads an OEM icon resource; for all OIC_* values.
      HICON LoadOEMIcon(UINT nIDIcon) const;
#endif

      /*
      // Retrieve an integer value from INI file or registry.
      UINT GetProfileInt(const char * lpszSection, const char * lpszEntry, int32_t nDefault);

      // Sets an integer value to INI file or registry.
      bool WriteProfileInt(const char * lpszSection, const char * lpszEntry, int32_t nValue);

      // Retrieve a string value from INI file or registry.
      string GetProfileString(const char * lpszSection, const char * lpszEntry,
      const char * lpszDefault = NULL);

      // Sets a string value to INI file or registry.
      bool WriteProfileString(const char * lpszSection, const char * lpszEntry,
      const char * lpszValue);

      // Retrieve an arbitrary binary value from INI file or registry.
      bool GetProfileBinary(const char * lpszSection, const char * lpszEntry,
      LPBYTE* ppData, UINT* pBytes);

      // Sets an arbitrary binary value to INI file or registry.
      bool WriteProfileBinary(const char * lpszSection, const char * lpszEntry,
      LPBYTE pData, UINT nBytes);

      // Override in derived class.
      virtual void InitLibId();

      // Register
      virtual bool Register();

      // Unregisters everything this cast was known to register.
      virtual bool Unregister();*/

#ifdef WINDOWS
      // Delete a registry key entry (and all its subkeys, too).
      //LONG DelRegTree(HKEY hParentKey, const string & strKeyName);
#endif


      // Printer DC Setup routine, 'struct tagPD' is a PRINTDLG structure.
      void SelectPrinter(HANDLE hDevNames, HANDLE hDevMode, bool bFreeOld = TRUE);

      // create a DC for the system default printer.
      ::draw2d::graphics * CreatePrinterDC();


      //   bool GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg);

      // run this cast as an embedded object.
      bool RunEmbedded();

      // run this cast as an OLE automation server.
      bool RunAutomated();

      // Parse the command line for stock options and commands.
      //   void ParseCommandLine(CCommandLineInfo& rCmdInfo);

      // React to a shell-issued command line directive.
      //   bool ProcessShellCommand(CCommandLineInfo& rCmdInfo);

      // Overridables


      // exiting
      virtual bool save_all_modified(); // save before exit
      void HideApplication();
      void close_all_documents(bool bEndSession); // close documents before exiting

      // Advanced: to override message boxes and other hooks
      virtual int32_t DoMessageBox(const char * lpszPrompt, UINT nType, UINT nIDPrompt);
      virtual void DoWaitCursor(int32_t nCode); // 0 => restore, 1=> begin, -1=> end
      virtual void ShowWaitCursor(bool bShow = true);

      // Advanced: process async DDE request
      virtual bool OnDDECommand(LPTSTR lpszCommand);

#ifdef WINDOWSEX
      // Advanced: Help support
      virtual void WinHelp(uint_ptr dwData, UINT nCmd = HELP_CONTEXT);
      virtual void HtmlHelp(uint_ptr dwData, UINT nCmd = 0x000F);
      virtual void WinHelpInternal(uint_ptr dwData, UINT nCmd = HELP_CONTEXT);
#endif

      // Command Handlers
      // map to the following for file new/open
      void _001OnFileNew();
      void on_file_open();

      // map to the following to enable print setup
      void OnFilePrintSetup();

      // map to the following to enable help
      void OnContextHelp();   // shift-F1
      void OnHelp();          // F1 (uses current context)
      void OnHelpIndex();     // ID_HELP_INDEX
      void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      void OnHelpUsing();     // ID_HELP_USING

      // Implementation

      void UpdatePrinterSelection(bool bForceDefaults);
      void SaveStdProfileSettings();  // save options to .INI file



      void DevModeChange(LPTSTR lpDeviceName);
      virtual void SetCurrentHandles();

      // Finds number of opened document items owned by templates
      // registered with the doc manager.
      int32_t get_open_document_count();

      // helpers for standard commdlg dialogs
      bool do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, sp(::user::document_template) ptemplate, sp(::user::document_interface) pdocument);

      void EnableModeless(bool bEnable); // to disable OLE in-place dialogs


      // Helper for message boxes; can work when no application can be found
      static int32_t ShowAppMessageBox(sp(application)pApp, const char * lpszPrompt, UINT nType, UINT nIDPrompt);
      static void DoEnableModeless(bool bEnable); // to disable OLE in-place dialogs

#ifdef WINDOWSEX
      // helpers for registration
      HKEY GetSectionKey(const char * lpszSection);
      HKEY GetAppRegistryKey();
#endif

      void OnAppExit();
      // System Policy Settings
      virtual bool LoadSysPolicies(); // Override to load policies other than the system policies that ca2 API loads.
      bool GetSysPolicyValue(uint32_t dwPolicyID, bool *pbValue); // returns the policy's setting in the out parameter
      bool _LoadSysPolicies() throw(); // Implementation helper
      static const char gen_FileSection[];
      static const char gen_FileEntry[];
      static const char gen_PreviewSection[];
      static const char gen_PreviewEntry[];

      virtual string get_mutex_name_gen();

      virtual void on_exclusive_instance_conflict(EExclusiveInstance eexclusive);
      virtual void on_exclusive_instance_local_conflict();


      virtual void delete_temp();

      //using ::ca2::thread::propset;
      //property_set & propset(object * pobject);
      //property_set * existing_propset(object * pobject);

      virtual oswindow get_ca2_app_wnd(const char * psz);


      virtual void get_cursor_pos(LPPOINT lppoint);
      virtual void get_screen_rect(LPRECT lprect);

      virtual sp(::user::interaction) release_capture_uie();
      virtual sp(::user::interaction) get_capture_uie();


      virtual int32_t get_document_count();

      // transparent ::ca2::window framework


      //mutex * get_mutex(::waitable * pobject);
      //using ::ca2::thread::lock;
      //void wait(::waitable * pobject);
      //wait_result wait(::waitable * pobject, duration dwTimeout);
      //void lock(::waitable * pobject);
      //bool lock(::waitable * pobject, duration dwTimeout);
      //using ::ca2::thread::unlock;
      //bool unlock(::waitable * pobject);

      //      event * get_event(::waitable * pobject, int32_t iEvent = 0);
      //      bool event_lock(::waitable * pobject, int32_t iEvent = 0, duration dwTimeout = duration::infinite());
      //      bool event_unlock(::waitable * pobject, int32_t iEvent = 0);

      /*   int32_t GetResourceId(const id_space * pspace, int32_t iKey);
      int32_t GetResourceId(const id_space & pspace, int32_t iKey);
      int32_t GetResourceId(const id_space * pspace, const char * lpcszKey);
      int32_t GetResourceId(const id_space & pspace, const char * lpcszKey);*/


      virtual string matter_as_string(const char * pszMatter, const char * pszMatter2 = NULL);
      virtual string dir_matter(const char * pszMatter, const char * pszMatter2 = NULL);
      virtual bool is_inside_time_dir(const char * pszPath);
      virtual bool file_is_read_only(const char * pszPath);
      virtual string file_as_string(var varFile);
      virtual string dir_path(const char * psz1, const char * psz2, const char * psz3 = NULL);
      virtual string dir_name(const char * psz);
      virtual bool dir_mk(const char * psz);
      virtual string file_title(const char * psz);
      virtual string file_name(const char * psz);



      virtual bool does_launch_window_on_startup();
      virtual bool activate_app();

      // Hooks for your initialization code
      virtual bool InitApplication();



      virtual bool initialize_instance();



      ::user::str_context * str_context();

      //      virtual bool open_link(const char * pszLink, const char * pszTarget = NULL);

      // Temporary map management (locks temp map on current thread)
      virtual void LockTempMaps();
      virtual bool UnlockTempMaps(bool bDeleteTemps = TRUE);
      virtual void TermThread(HINSTANCE hInstTerm);

      //virtual ::draw2d::graphics * graphics_from_os_data(void * pdata);

#ifdef METROWIN
      virtual sp(::user::interaction) window_from_os_data(void * pdata);
      virtual sp(::user::interaction) window_from_os_data_permanent(void * pdata);
#else
      virtual sp(::ca2::window) window_from_os_data(void * pdata);
      virtual sp(::ca2::window) window_from_os_data_permanent(void * pdata);
#endif

      virtual sp(::ca2::window) FindWindow(const char * lpszClassName, const char * lpszWindowName);
      virtual sp(::ca2::window) FindWindowEx(oswindow oswindowParent, oswindow oswindowChildAfter, const char * lpszClass, const char * lpszWindow);

      virtual string get_local_mutex_name(const char * pszAppName);
      virtual string get_local_id_mutex_name(const char * pszAppName, const char * pszId);
      virtual string get_global_mutex_name(const char * pszAppName);
      virtual string get_global_id_mutex_name(const char * pszAppName, const char * pszId);

      virtual string get_local_mutex_name();
      virtual string get_local_id_mutex_name();
      virtual string get_global_mutex_name();
      virtual string get_global_id_mutex_name();


      virtual bool final_handle_exception(exception & e);

      bool ca_process_initialize();
      bool ca_initialize1();

      bool ca_finalize();




      virtual sp(::user::interaction) get_request_parent_ui(sp(::user::interaction) pinteraction, sp(create_context) pcontext);




      //      virtual ::ca2::file_system & file_system();
      virtual bool _001OnDDECommand(const char * lpcsz);
      virtual void _001EnableShellOpen();
      virtual sp(::user::document_interface) _001OpenDocumentFile(var varFile);
      DECL_GEN_SIGNAL(_001OnFileNew);


      virtual string get_version();

      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();

      virtual ::ca2::thread * GetThread();
      virtual void set_thread(::ca2::thread * pthread);


      virtual sp(::ca2::window) get_desktop_window();



//      virtual void construct();
      

      //virtual bool final_handle_exception(exception & e);
      //virtual bool initialize();
      //virtual bool initialize1();
      //virtual bool initialize2();

      //virtual bool initialize_instance();
      //virtual int32_t  exit_instance();

      //virtual void _001OnFileNew();
      //virtual bool bergedge_start();


      //virtual bool is_serviceable();
      //virtual service_base * allocate_new_service();


      //virtual bool on_install();
      //virtual bool on_uninstall();

      virtual int32_t run();

//      virtual void on_request(sp(create_context) pcreatecontext);

//      sp(::user::document_interface) _001OpenDocumentFile(var varFile);

      sp(::application) get_system();

      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index i, LPRECT lprect);
      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index i, LPRECT lprect);


//      virtual void defer_add_document_template(sp(::user::document_template) ptemplate);

      void enum_display_monitors();

#if defined(WINDOWS)

      static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

      void monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor);

#endif





      virtual bool set_keyboard_layout(const char * pszPath, bool bUser);

      
      inline ::uinteraction::uinteraction          & uinteraction () { return *m_puinteraction  ; }
      ///inline ::user::user                  & user     () { return *m_puserbase      ; }
//      inline ::userex::userex                      & userex       () { return *m_puserex        ; }
      inline ::filemanager::filemanager            & filemanager  () { return *m_pfilemanager   ; }
      inline ::usermail::usermail                          & usermail         () { return *m_pusermail          ; }

      
      string message_box(const char * pszMatter, property_set & propertyset);
      //using ::ca2::application::simple_message_box;
      //virtual int32_t simple_message_box_timeout(sp(::user::interaction) puiOwner, const char * pszMessage, int32_t iTimeout, UINT fuStyle = MB_OK);
      //virtual int32_t simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
      virtual int32_t track_popup_menu(const char * pszMatter, point pt, sp(::user::interaction) puie);

      virtual bool get_fs_size(string & strSize, const char * pszPath, bool & bPending);
      virtual bool get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending);
   
      virtual void set_title(const char * pszTitle);


      virtual bool _001CloseApplicationByUser(sp(::user::interaction) pwndExcept);


#ifdef WINDOWSEX

      static BOOL CALLBACK GetAppsEnumWindowsProc(oswindow oswindow, LPARAM lParam);

#endif

      void update_app_interest();
      void ensure_app_interest();


      //virtual oswindow get_ca2_app_wnd(const char * psz);


      //virtual void request_create(sp(create_context) pcreatecontext);

//      virtual void on_exclusive_instance_local_conflict();

      virtual int32_t send_simple_command(const char * psz, void * osdataSender);
      virtual int32_t send_simple_command(void * osdata, const char * psz, void * osdataSender);

      virtual ::user::printer * get_printer(const char * pszDeviceName);

      virtual string draw2d_get_default_library_name();
      virtual string multimedia_audio_get_default_library_name();
      virtual string multimedia_audio_mixer_get_default_library_name();
      virtual string veriwell_multimedia_music_midi_get_default_library_name();



      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual ::visual::icon * set_icon(object * pobject, ::visual::icon * picon, bool bBigIcon);
      virtual ::visual::icon * get_icon(object * pobject, bool bBigIcon) const;


   };


   inline application & get(sp(::application) papp)
   {
      return papp;
   }

   // impl
   template < class APP >
   sp(::application) single_application_library < APP > :: get_new_app(const char * pszAppId)
   {

      if(!contains_app(pszAppId))
         return NULL;

      sp(::application) papp = canew(APP());

      if(papp == NULL)
         return NULL;

      try
      {
         papp->construct(pszAppId);
      }
      catch(...)
      {
         try
         {
            papp.release();
         }
         catch(...)
         {
         }
         return NULL;
      }

      return papp;

   }


   inline allocatorsp ca2::allocer()
   {
      return m_papp->m_allocer;
   }


} // namespace ca2







