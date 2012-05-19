#pragma once



namespace user
{


   class document_interface;


} // namespace user


class document_template;

namespace userbase
{


   class main_frame;


} // namespace userbase


class file_manager_interface;
class document_manager;


namespace radix
{

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
      int                              m_iRet;
      bool                             m_bOk;


      application_signal_object(::ca::application * papp, ::gen::signal * psignal, ::ca::e_application_signal esignal);


   };


   class CLASS_DECL_ca application :
      virtual public ::ca::application,
      virtual public ::ca::message_window_simple_callback,
      virtual public ::radix::thread
   {
   public:



      gen::signal                   m_signal;
      string                        m_strInstallToken;
      //::user::interaction *         m_puiInitialPlaceHolderContainer;
      ::ca::application_bias        m_biasCalling;



      HGLOBAL                       m_hDevMode;             // printer Dev Mode
      HGLOBAL                       m_hDevNames;            // printer Device Names
      DWORD                         m_dwPromptContext;        // help context override for message box
   // LKG
   //   DWORD m_dwPolicies;            // block for storing boolean system policies

      int                           m_nWaitCursorCount;         // for wait cursor (>0 => waiting)
      HCURSOR                       m_hcurWaitCursorRestore; // old cursor to restore after wait cursor

      DWORD                         m_dwPolicies;            // block for storing boolean system policies

      EExclusiveInstance            m_eexclusiveinstance;

      ::mutex *                     m_pmutexLocal;
      ::mutex *                     m_pmutexLocalId;
      ::mutex *                     m_pmutexGlobal;
      ::mutex *                     m_pmutexGlobalId;
      // This module's hInstance.
      HINSTANCE                     m_hInstance;
      // Pointer to the command-line.
      string                        m_strCmdLine;
      // Initial state of the application's ::ca::window; normally,
      // this is an argument to ShowWindow().
      int                           m_nCmdShow;

      file_manager_interface *      m_pfilemanager;
      // Running args (can be changed in initialize_instance)
      // Human-redable name of the application. Normally set in
      // constructor or retreived from __IDS_APP_TITLE.
      string                        m_strAppName;
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

      ::user::LPWndArray * m_pframea;


      //CCommandLineInfo* m_pCmdInfo;

      ATOM m_atomApp, m_atomSystemTopic;   // for DDE open
      UINT m_nNumPreviewPages;        // number of default printed pages

      size_t  m_nSafetyPoolSize;      // ideal size



      string                           m_strId;

      mutex                            m_mutexObjectLock;
      ::collection::map < ::waitable *, ::waitable *, mutex *, mutex * > m_mapObjectMutex;

      mutex                            m_mutexObjectEvent;
      ::collection::map < ::radix::object *, ::radix::object *, ::collection::map < int, int, event *, event * > *, ::collection::map < int, int, event *, event * >  * > m_mapObjectEvent;

      typedef ::collection::map < ::radix::object *, ::radix::object *, gen::property_set, gen::property_set > oset;
      oset                             m_mapObjectSet;

      class ::user::str_context *      m_puserstrcontext;
      bool                             m_bShouldInitializeGTwf;
      point                            m_ptCursor;
      bool                             m_bSessionSynchronizedCursor;
      rect                             m_rectScreen;
      bool                             m_bSessionSynchronizedScreen;
      ::user::interaction *            m_pwndMain;


      int                              m_iResourceId;

      ::collection::string_to_ptr         m_appmap;

      //BaseIdSpaceIntegerMap      m_imapResource;
      //BaseIdSpaceStringKeyMap    m_strmapResource;
   //   id_space                   m_idspace;




      application();
      virtual ~application();



      //virtual void on_allocation_error(const ::ca::type_info & info);
      //virtual ::ca::ca * on_alloc(const ::ca::type_info & info);


      virtual bool process_initialize();



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


      ::user::LPWndArray & frames();
      virtual void add_frame(::user::interaction * pwnd);
      virtual void remove_frame(::user::interaction * pwnd);


      virtual int simple_message_box_timeout(::user::interaction * puiOwner, const char * pszMessage, int iTimeout, UINT fuStyle = MB_OK);
      virtual int simple_message_box(::user::interaction * puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
      virtual int simple_message_box(::user::interaction * puiOwner, UINT fuStyle, const char * pszFormat, ...);

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

   public:
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
      UINT GetProfileInt(const char * lpszSection, const char * lpszEntry, int nDefault);

      // Sets an integer value to INI file or registry.
      bool WriteProfileInt(const char * lpszSection, const char * lpszEntry, int nValue);

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


      // open named file, trying to match a regsitered
      // document template to it.
      virtual void on_request(::ca::create_context * pcreatecontext);


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

      // Hooks for your initialization code
      virtual bool InitApplication();

      virtual int    exit();
      virtual bool   finalize();

      // exiting
      virtual bool save_all_modified(); // save before exit
      void HideApplication();
      void close_all_documents(bool bEndSession); // close documents before exiting

      // Advanced: to override message boxes and other hooks
      virtual int DoMessageBox(const char * lpszPrompt, UINT nType, UINT nIDPrompt);
      virtual void DoWaitCursor(int nCode); // 0 => restore, 1=> begin, -1=> end

      // Advanced: process async DDE request
      virtual bool OnDDECommand(LPTSTR lpszCommand);

#ifdef WINDOWS
      // Advanced: Help support
      virtual void WinHelp(DWORD_PTR dwData, UINT nCmd = HELP_CONTEXT);
      virtual void HtmlHelp(DWORD_PTR dwData, UINT nCmd = 0x000F);
      virtual void WinHelpInternal(DWORD_PTR dwData, UINT nCmd = HELP_CONTEXT);
#endif

   // Command Handlers
   protected:
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
   public:

      void UpdatePrinterSelection(bool bForceDefaults);
      void SaveStdProfileSettings();  // save options to .INI file



      void DevModeChange(LPTSTR lpDeviceName);
      virtual void SetCurrentHandles() = 0;

      // Finds number of opened document items owned by templates
      // registered with the doc manager.
      int get_open_document_count();

      // helpers for standard commdlg dialogs
      bool do_prompt_file_name(var & varFile, UINT nIDSTitle, DWORD lFlags, bool bOpenFileDialog, document_template * ptemplate, ::user::document_interface * pdocument);

      void EnableModeless(bool bEnable); // to disable OLE in-place dialogs

      // overrides for implementation
      virtual bool initialize_instance();
      virtual int exit_instance(); // return cast exit code
      virtual int run();
      virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
      virtual void ProcessWndProcException(base_exception* e, gen::signal_object * pobj);

       // Helper for message boxes; can work when no application can be found
      static int ShowAppMessageBox(application *pApp, const char * lpszPrompt, UINT nType, UINT nIDPrompt);
      static void DoEnableModeless(bool bEnable); // to disable OLE in-place dialogs

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

#ifdef WINDOWS
      // helpers for registration
      HKEY GetSectionKey(const char * lpszSection);
      HKEY GetAppRegistryKey();
#endif

      void OnAppExit();
   public :
      // System Policy Settings
      virtual bool LoadSysPolicies(); // Override to load policies other than the system policies that ca2 API loads.
      bool GetSysPolicyValue(DWORD dwPolicyID, bool *pbValue); // returns the policy's setting in the out parameter
   protected :
      bool _LoadSysPolicies() throw(); // Implementation helper
   public:
      static const char gen_FileSection[];
      static const char gen_FileEntry[];
      static const char gen_PreviewSection[];
      static const char gen_PreviewEntry[];

      virtual ::ca::application * get_app() const;
      virtual string get_mutex_name_radix();

      virtual void on_exclusive_instance_conflict(EExclusiveInstance eexclusive);
      virtual void on_exclusive_instance_local_conflict();

      virtual void message_window_message_handler(gen::signal_object * pobj);

      virtual void delete_temp();

      using ::radix::thread::propset;
      gen::property_set & propset(::radix::object * pobject);

      virtual HWND get_ca2_app_wnd(const char * psz);

      virtual ::user::interaction * uie_from_point(point pt);

      virtual void get_cursor_pos(LPPOINT lppoint);
      virtual void get_screen_rect(LPRECT lprect);

      virtual ::user::interaction * release_capture_uie();
      virtual ::user::interaction * get_capture_uie();


      virtual int get_document_count();

      // transparent ::ca::window framework


      mutex * get_mutex(::waitable * pobject);
      using ::radix::thread::lock;
      void wait(::waitable * pobject);
      wait_result wait(::waitable * pobject, duration dwTimeout);
      bool lock(::waitable * pobject);
      bool lock(::waitable * pobject, duration dwTimeout);
      using ::radix::thread::unlock;
      bool unlock(::waitable * pobject);

      event * get_event(::radix::object * pobject, int iEvent = 0);
      bool event_lock(::radix::object * pobject, int iEvent = 0, duration dwTimeout = duration::infinite());
      bool event_unlock(::radix::object * pobject, int iEvent = 0);

   /*   int GetResourceId(const id_space * pspace, int iKey);
      int GetResourceId(const id_space & pspace, int iKey);
      int GetResourceId(const id_space * pspace, const char * lpcszKey);
      int GetResourceId(const id_space & pspace, const char * lpcszKey);*/


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

      virtual bool initialize1();

      ::user::str_context * str_context();

      using pha(::user::interaction)::on_delete;
      virtual void on_delete(::ca::ca * pobject);

      virtual bool open_link(const char * pszLink, const char * pszTarget = NULL);

      // Temporary ::collection::map management (locks temp ::collection::map on current thread)
      virtual void LockTempMaps();
      virtual bool UnlockTempMaps(bool bDeleteTemps = TRUE);
      virtual void TermThread(HINSTANCE hInstTerm);

      //virtual ::ca::graphics * graphics_from_os_data(void * pdata);

      virtual ::ca::window * window_from_os_data(void * pdata);
      virtual ::ca::window * window_from_os_data_permanent(void * pdata);

      virtual ::ca::window * FindWindow(const char * lpszClassName, const char * lpszWindowName);
      virtual ::ca::window * FindWindowEx(HWND hwndParent, HWND hwndChildAfter, const char * lpszClass, const char * lpszWindow);

      virtual string get_local_mutex_name(const char * pszAppName);
      virtual string get_local_id_mutex_name(const char * pszAppName, const char * pszId);
      virtual string get_global_mutex_name(const char * pszAppName);
      virtual string get_global_id_mutex_name(const char * pszAppName, const char * pszId);

      virtual string get_local_mutex_name();
      virtual string get_local_id_mutex_name();
      virtual string get_global_mutex_name();
      virtual string get_global_id_mutex_name();

      virtual string get_local_mutex_id() = 0;
      virtual string get_global_mutex_id() = 0;

      virtual bool final_handle_exception(::ca::exception & e);

      virtual bool is_system();
      virtual bool is_bergedge();
      bool ca_process_initialize();
      bool ca_initialize1();
      bool initialize2();
      bool initialize3();
      bool initialize();

      bool ca_finalize();

      virtual ::ca::ca * alloc(::ca::type_info & info);
      virtual ::ca::ca * alloc(const id & idType);

      virtual bool app_map_lookup(const char * psz, void * &);
      virtual void app_map_set(const char * psz, void *);


      virtual ::user::interaction * get_request_parent_ui(::user::interaction * pinteraction, ::ca::create_context * pcontext);
      virtual ::user::interaction * get_request_parent_ui(::userbase::main_frame * pmainframe, ::ca::create_context * pcontext);


   };


} // namespace radix







typedef ::ca::application * (* LP_GET_NEW_APP) ();


