#pragma once

typedef ::ca::application * (* LP_GET_NEW_APP) ();


namespace gen
{


   class command_line;


} // namespace gen

namespace visual
{


   class icon;


} // namespace visual



namespace math
{


   class math;


} // namespace math


namespace geometry
{


   class geometry;


} // namespace geometry


namespace userbase
{


   class main_frame;


} // namespace userbase



#if defined(LINUX) || defined(MACOS)

typedef ::visual::icon * HICON;

#endif




#pragma once


class file_system;
typedef ca::smart_pointer < file_system > file_system_sp;
class Ex1FactoryImpl;


namespace gen
{



   class document_interface;


   namespace lemon
   {


      class array;


   } // namespace lemon

   class main_frame;



   class file_manager_interface;
   class document_manager;



   enum EExclusiveInstance
   {
      ExclusiveInstanceNone,
      ExclusiveInstanceLocal,
      ExclusiveInstanceLocalId,
      ExclusiveInstanceGlobal,
      ExclusiveInstanceGlobalId,
      ExclusiveInstanceLicense,
   };


   class CLASS_DECL_ca application_signal_object :
         public gen::signal_object
   {
   public:


      ::ca::e_application_signal       m_esignal;
      int32_t                          m_iRet;
      bool                             m_bOk;


      application_signal_object(::ca::application * papp, ::gen::signal * psignal, ::ca::e_application_signal esignal);


   };

   class CLASS_DECL_ca application :
      virtual public ::ca::application,
      virtual public command_target_interface,
      virtual public request_interface,
      virtual public ::ca::message_window_simple_callback,
      virtual public ::gen::thread,
      virtual public ::ca::smart_pointer < ::gen::application >
   {
   public:


      class ::gen::base64                 m_base64;
      signal                              m_signalAppLanguageChange;
      math::math *                        m_pmath;
      geometry::geometry *                m_pgeometry;
      class savings *                     m_psavings;
      string                              m_strCa2ModulePath;
      string                              m_strCa2ModuleFolder;
      string                              m_strModulePath;
      string                              m_strModuleFolder;
      string                              m_strHelpFilePath;
      ::gen::command_thread *             m_pcommandthread;
      mutex                               m_mutex;

      string                        m_strInstallType;
      string                        m_strInstallToken;
      //::user::interaction *         m_puiInitialPlaceHolderContainer;
      ::ca::application_bias        m_biasCalling;


#ifdef WINDOWS


      HGLOBAL                       m_hDevMode;             // printer Dev Mode
      HGLOBAL                       m_hDevNames;            // printer Device Names


#endif


      uint32_t                         m_dwPromptContext;        // help context override for message box
   // LKG
   //   uint32_t m_dwPolicies;            // block for storing boolean system policies

      int32_t                           m_nWaitCursorCount;         // for wait cursor (>0 => waiting)
      HCURSOR                       m_hcurWaitCursorRestore; // old cursor to restore after wait cursor

      uint32_t                         m_dwPolicies;            // block for storing boolean system policies

      EExclusiveInstance            m_eexclusiveinstance;

      ::mutex *                     m_pmutexLocal;
      ::mutex *                     m_pmutexLocalId;
      ::mutex *                     m_pmutexGlobal;
      ::mutex *                     m_pmutexGlobalId;
      // This module's hInstance.
#ifdef WINDOWS
      HINSTANCE                     m_hInstance;
#endif
      // Pointer to the command-line.
      string                        m_strCmdLine;
      // Initial state of the application's ::ca::window; normally,
      // this is an argument to ShowWindow().
      int32_t                           m_nCmdShow;

      file_manager_interface *      m_pfilemanager;
      // Running args (can be changed in initialize_instance)
      // Human-redable name of the application. Normally set in
      // constructor or retreived from __IDS_APP_TITLE.
      string                        m_strAppName;
      string                        m_strAppId;
      string                        m_strLibraryName;

      // Name of registry key for this application. See
      // SetRegistryKey() member function.
      const char *                  m_pszRegistryKey;

      // Pointer to document_manager used to manage document templates
      // for this application instance.
      document_manager *            m_pdocmanager;

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

      ::user::interaction_ptr_array * m_pframea;


      //CCommandLineInfo* m_pCmdInfo;

      ATOM m_atomApp, m_atomSystemTopic;   // for DDE open
      UINT m_nNumPreviewPages;        // number of default printed pages

      size_t  m_nSafetyPoolSize;      // ideal size



      string                           m_strId;

      //mutex                            m_mutexObjectLock;
      //::collection::map < ::waitable *, ::waitable *, mutex *, mutex * > m_mapObjectMutex;

      //mutex                            m_mutexObjectEvent;
      //::collection::map < ::gen::object *, ::gen::object *, ::collection::map < int32_t, int32_t, event *, event * > *, ::collection::map < int32_t, int32_t, event *, event * >  * > m_mapObjectEvent;

      //typedef ::collection::map < ::gen::object *, ::gen::object *, gen::property_set, gen::property_set > oset;
      //oset                             m_mapObjectSet;

      class ::user::str_context *      m_puserstrcontext;
      bool                             m_bShouldInitializeGTwf;
      point                            m_ptCursor;
      bool                             m_bSessionSynchronizedCursor;
      rect                             m_rectScreen;
      bool                             m_bSessionSynchronizedScreen;
      ::user::interaction *            m_pwndMain;


      int32_t                              m_iResourceId;

      ::collection::string_to_ptr         m_appmap;

      //BaseIdSpaceIntegerMap      m_imapResource;
      //BaseIdSpaceStringKeyMap    m_strmapResource;
   //   id_space                   m_idspace;


      application();
      virtual ~application();


      virtual void Ex1OnFactoryExchange();

      // open named file, trying to match a regsitered
      // document template to it.
      virtual void on_request(::ca::create_context * pline);

      math::math & math();
      geometry::geometry & geometry();
      class savings & savings();

      lemon::array * m_plemonarray;

      lemon::array & lemon_array();


      // overrides for implementation
      virtual int32_t run();
      virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
      virtual void ProcessWndProcException(base_exception* e, gen::signal_object * pobj);


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


      virtual bool verb();

      void OnUpdateRecentFileMenu(cmd_ui * pcmdui) ;

      virtual DECL_GEN_SIGNAL(OnAppLanguage)
      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);


      class ::gen::base64 & base64();

      virtual string get_local_mutex_id();
      virtual string get_global_mutex_id();

      virtual bool hex_to_memory(primitive::memory & memory, const char * pszHex);
      virtual void memory_to_hex(string & strHex, primitive::memory & memory);

      // Wall-eeeeee aliases
      ::gen::command_thread & command_central();
      ::gen::command_thread & command();
      ::gen::command_thread & guideline();
      ::gen::command_thread & directrix();
      ::gen::command_thread & axiom();
      ::gen::command_thread & creation();

      //virtual void on_allocation_error(const ::ca::type_info & info);
      //virtual ::ca::ca * on_alloc(const ::ca::type_info & info);


      virtual bool check_exclusive();
      virtual bool release_exclusive();


      // Sets and initializes usage of HtmlHelp instead of WinHelp.
      void EnableHtmlHelp();

      // Sets and initializes usage of HtmlHelp instead of WinHelp.
//      void SetHelpMode( __HELP_TYPE eHelpType );
  //    __HELP_TYPE GetHelpMode();

   // Initialization Operations - should be done in initialize_instance

      ::user::interaction * get_active_guie();
      ::user::interaction * get_focus_guie();
//      virtual ::user::interaction * get_place_holder_container();


      ::user::interaction_ptr_array & frames();
      virtual void add_frame(::user::interaction * pwnd);
      virtual void remove_frame(::user::interaction * pwnd);


      virtual int32_t simple_message_box_timeout(::user::interaction * puiOwner, const char * pszMessage, int32_t iTimeout, UINT fuStyle = MB_OK);
      virtual int32_t simple_message_box(::user::interaction * puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
      virtual int32_t simple_message_box(::user::interaction * puiOwner, UINT fuStyle, const char * pszFormat, ...);

      virtual void EnableShellOpen();

      virtual string load_string(id id);

      virtual bool on_run_exception(::ca::exception & e);

      virtual void pre_translate_message(::gen::signal_object * pobj);

      // Set regsitry key name to be used by application's
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
      ::ca::graphics * CreatePrinterDC();


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

      // Advanced: process async DDE request
      virtual bool OnDDECommand(LPTSTR lpszCommand);

#ifdef WINDOWSEX
      // Advanced: Help support
      virtual void WinHelp(uint_ptr dwData, UINT nCmd = HELP_CONTEXT);
      virtual void HtmlHelp(uint_ptr dwData, UINT nCmd = 0x000F);
      virtual void WinHelpInternal(uint_ptr dwData, UINT nCmd = HELP_CONTEXT);
#endif

   // Command Handlers
      // ::collection::map to the following for file new/open
      void _001OnFileNew();
      void on_file_open();

      // ::collection::map to the following to enable print setup
      void OnFilePrintSetup();

      // ::collection::map to the following to enable help
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
      bool do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, document_template * ptemplate, ::user::document_interface * pdocument);

      void EnableModeless(bool bEnable); // to disable OLE in-place dialogs


       // Helper for message boxes; can work when no application can be found
      static int32_t ShowAppMessageBox(application *pApp, const char * lpszPrompt, UINT nType, UINT nIDPrompt);
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

      virtual void message_window_message_handler(gen::signal_object * pobj);

      virtual void delete_temp();

      //using ::gen::thread::propset;
      //gen::property_set & propset(::gen::object * pobject);
      //gen::property_set * existing_propset(::gen::object * pobject);

      virtual oswindow get_ca2_app_wnd(const char * psz);

      virtual ::user::interaction * uie_from_point(point pt);

      virtual void get_cursor_pos(LPPOINT lppoint);
      virtual void get_screen_rect(LPRECT lprect);

      virtual ::user::interaction * release_capture_uie();
      virtual ::user::interaction * get_capture_uie();


      virtual int32_t get_document_count();

      // transparent ::ca::window framework


      //mutex * get_mutex(::waitable * pobject);
      //using ::gen::thread::lock;
      //void wait(::waitable * pobject);
      //wait_result wait(::waitable * pobject, duration dwTimeout);
      //void lock(::waitable * pobject);
      //bool lock(::waitable * pobject, duration dwTimeout);
      //using ::gen::thread::unlock;
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
      virtual string file_as_string(const char * pszPath);
      virtual string dir_path(const char * psz1, const char * psz2, const char * psz3 = NULL);
      virtual string dir_name(const char * psz);
      virtual bool dir_mk(const char * psz);
      virtual string file_title(const char * psz);
      virtual string file_name(const char * psz);


      virtual bool bergedge_start();

      virtual bool does_launch_window_on_startup();
      virtual bool activate_app();

      // Hooks for your initialization code
      virtual bool InitApplication();

      virtual int32_t    exit();

      virtual bool process_initialize();

      virtual bool initialize_instance();


      virtual bool initialize1(); // cgcl // first initialization
      virtual bool initialize2(); // cst  // second initialization
      virtual bool initialize3(); // third initialization and so on...

      virtual bool initialize(); // last initialization

      virtual bool finalize();

      virtual int32_t exit_instance();

      ::user::str_context * str_context();

      using pha(::user::interaction)::on_delete;
      virtual void on_delete(::ca::ca * pobject);

      virtual bool open_link(const char * pszLink, const char * pszTarget = NULL);

      // Temporary ::collection::map management (locks temp ::collection::map on current thread)
      virtual void LockTempMaps();
      virtual bool UnlockTempMaps(bool bDeleteTemps = TRUE);
      virtual void TermThread(HINSTANCE hInstTerm);
      virtual const char * RegisterWndClass(UINT nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);

      //virtual ::ca::graphics * graphics_from_os_data(void * pdata);

#ifdef METROWIN
      virtual ::user::interaction * window_from_os_data(void * pdata);
      virtual ::user::interaction * window_from_os_data_permanent(void * pdata);
#else
      virtual ::ca::window * window_from_os_data(void * pdata);
      virtual ::ca::window * window_from_os_data_permanent(void * pdata);
#endif

      virtual ::ca::window * FindWindow(const char * lpszClassName, const char * lpszWindowName);
      virtual ::ca::window * FindWindowEx(oswindow oswindowParent, oswindow oswindowChildAfter, const char * lpszClass, const char * lpszWindow);

      virtual string get_local_mutex_name(const char * pszAppName);
      virtual string get_local_id_mutex_name(const char * pszAppName, const char * pszId);
      virtual string get_global_mutex_name(const char * pszAppName);
      virtual string get_global_id_mutex_name(const char * pszAppName, const char * pszId);

      virtual string get_local_mutex_name();
      virtual string get_local_id_mutex_name();
      virtual string get_global_mutex_name();
      virtual string get_global_id_mutex_name();


      virtual bool final_handle_exception(::ca::exception & e);

      virtual bool is_system();
      virtual bool is_bergedge();
      bool ca_process_initialize();
      bool ca_initialize1();

      bool ca_finalize();

      virtual ::ca::ca * alloc(::ca::type_info & info);
      virtual ::ca::ca * alloc(const id & idType);

      virtual bool app_map_lookup(const char * psz, void * &);
      virtual void app_map_set(const char * psz, void *);


      virtual ::user::interaction * get_request_parent_ui(::user::interaction * pinteraction, ::ca::create_context * pcontext);
      virtual ::user::interaction * get_request_parent_ui(::userbase::main_frame * pmainframe, ::ca::create_context * pcontext);
//      gen::file_system_sp m_spfilesystem;


      virtual void construct();
      virtual void construct(const char * pszId);

      virtual bool set_main_init_data(::ca::main_init_data * pdata);


//      virtual ::gen::file_system & file_system();
      virtual bool _001OnDDECommand(const char * lpcsz);
      virtual void _001EnableShellOpen();
      virtual ::user::document_interface * _001OpenDocumentFile(var varFile);
      DECL_GEN_SIGNAL(_001OnFileNew);


      virtual string get_version();

      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();

      virtual bool DeferRegisterClass(LONG fToRegister, const char ** ppszClass);


      virtual ::gen::thread * GetThread();
      virtual void set_thread(::gen::thread * pthread);
      virtual ::user::interaction * GetMainWnd();


      virtual ::ca::window * get_desktop_window();


#ifndef METROWIN
      virtual void get_time(timeval *p);
#endif
      virtual void set_env_var(const string & var,const string & value);
      virtual uint32_t get_thread_id();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


   };


} // namespace gen










