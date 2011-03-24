#pragma once

#pragma once

#include "template/trace_module_manager.h"
#include "user/user_str.h"
#include "user/user_draw_context.h"
#include "multithreading/multithreading.h"

#define CA2M_BERGEDGE 0xCA20
#define BERGEDGE_GETAPP 0

#include "factory.h"


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

   class CLASS_DECL_ca application : 
      virtual public ::ca::application,
      virtual public ::ca::message_window_simple_callback
   {
   protected:
      HGLOBAL m_hDevMode;             // printer Dev Mode
      HGLOBAL m_hDevNames;            // printer Device Names
      DWORD m_dwPromptContext;        // help context override for message box
   // LKG   
   //   DWORD m_dwPolicies;            // block for storing boolean system policies

      int m_nWaitCursorCount;         // for wait cursor (>0 => waiting)
      HCURSOR m_hcurWaitCursorRestore; // old cursor to restore after wait cursor

      CRecentFileList* m_pRecentFileList;
      DWORD m_dwPolicies;            // block for storing boolean system policies

   public:

      ::user::LPWndArray * m_pframea;


   
      EExclusiveInstance m_eexclusiveinstance;

      ::mutex *     m_pmutexLocal;
      ::mutex *     m_pmutexLocalId;
      ::mutex *     m_pmutexGlobal;
      ::mutex *     m_pmutexGlobalId;
      // This module's hInstance.
      HINSTANCE m_hInstance;
      // Pointer to the command-line.
      string m_strCmdLine;
      // Initial state of the application's ::ca::window; normally,
      // this is an argument to ShowWindow().
      int m_nCmdShow;

      file_manager_interface * m_pfilemanager;
      // Running args (can be changed in initialize_instance)
      // Human-redable name of the application. Normally set in
      // constructor or retreived from AFX_IDS_APP_TITLE.
      string m_strAppName;

      // Name of registry key for this application. See
      // SetRegistryKey() member function.
      const char * m_pszRegistryKey;

      // Pointer to document_manager used to manage document templates
      // for this application instance.
      document_manager* m_pdocmanager;

      // Support for Shift+F1 help mode.

      // TRUE if we're in SHIFT+F1 mode.
      BOOL m_bHelpMode;

      // set in constructor to override default

      // Executable name (no spaces).
      const char * m_pszExeName;

      // Default based on this module's path.
      const char * m_pszHelpFilePath;

      // Default based on this application's name.
      const char * m_pszProfileName;
      // help mode used by the cast
      AFX_HELP_TYPE m_eHelpType;


      //CCommandLineInfo* m_pCmdInfo;

      ATOM m_atomApp, m_atomSystemTopic;   // for DDE open
      UINT m_nNumPreviewPages;        // number of default printed pages

      size_t  m_nSafetyPoolSize;      // ideal size



   string                           m_strId;

   mutex                            m_mutexObjectLock;
   ::collection::map < ::radix::object *, ::radix::object *, mutex *, mutex * > m_mapObjectMutex;

   mutex                            m_mutexObjectEvent;
   ::collection::map < ::radix::object *, ::radix::object *, ::collection::map < int, int, CEvent *, CEvent * > *, ::collection::map < int, int, CEvent *, CEvent * >  * > m_mapObjectEvent;

   typedef ::collection::map < id, id, var, var > idvar;
   typedef ::collection::map < ::radix::object *, ::radix::object *, idvar, idvar > oidvar;
   mutex                            m_mutexObjectVar;
   oidvar                           m_mapObjectVar;

   class ::user::str_context *      m_puistrcontext;
   bool                             m_bShouldInitializeGTwf;
   point                            m_ptCursor;
   bool                             m_bSessionSynchronizedCursor;
   rect                             m_rectScreen;
   bool                             m_bSessionSynchronizedScreen;
   ::user::interaction *            m_pwndMain;

   ::user::keyboard_focus *         m_pkeyboardfocus;
   ::user::mouse_focus *            m_pmousefocusLButtonDown;

   ::user::str *                      m_puistr;

   int                              m_iResourceId;
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
      void SetHelpMode( AFX_HELP_TYPE eHelpType );
      AFX_HELP_TYPE GetHelpMode();

   // Initialization Operations - should be done in initialize_instance

      ::user::interaction * get_active_guie();
      ::user::interaction * get_focus_guie();

      ::user::LPWndArray & frames();
      virtual void add_frame(::user::interaction * pwnd);
      virtual void remove_frame(::user::interaction * pwnd);

      virtual int simple_message_box_timeout(::user::interaction * puiOwner, const char * pszMessage, int iTimeout, UINT fuStyle = MB_OK);
      virtual int simple_message_box(::user::interaction * puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
      virtual int simple_message_box(::user::interaction * puiOwner, UINT fuStyle, const char * pszFormat, ...);

      // Load MRU file list and last preview state.
      void LoadStdProfileSettings(UINT nMaxMRU = _AFX_MRU_COUNT);

      virtual void EnableShellOpen();

      virtual string load_string(id id);

      virtual bool on_run_exception(::ca::exception & e);


      // Set regsitry key name to be used by application's
      // profile member functions; prevents writing to an INI spfile->
      void SetRegistryKey(const char * lpszRegistryKey);
      void SetRegistryKey(UINT nIDRegistryKey);


      void RegisterShellFileTypes(BOOL bCompat = FALSE);

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

      // Loads an icon resource.
      HICON LoadIcon(const char * lpszResourceName) const;
      HICON LoadIcon(UINT nIDResource) const;

      // Loads an icon resource; for stock IDI_ values.
      HICON LoadStandardIcon(const char * lpszIconName) const;

      // Loads an OEM icon resource; for all OIC_* values.
      HICON LoadOEMIcon(UINT nIDIcon) const;

      // Retrieve an integer value from INI file or registry.
      UINT GetProfileInt(const char * lpszSection, const char * lpszEntry, int nDefault);

      // Sets an integer value to INI file or registry.
      BOOL WriteProfileInt(const char * lpszSection, const char * lpszEntry, int nValue);

      // Retrieve a string value from INI file or registry.
      string GetProfileString(const char * lpszSection, const char * lpszEntry,
               const char * lpszDefault = NULL);

      // Sets a string value to INI file or registry.
      BOOL WriteProfileString(const char * lpszSection, const char * lpszEntry,
               const char * lpszValue);

      // Retrieve an arbitrary binary value from INI file or registry.
      BOOL GetProfileBinary(const char * lpszSection, const char * lpszEntry,
               LPBYTE* ppData, UINT* pBytes);

      // Sets an arbitrary binary value to INI file or registry.
      BOOL WriteProfileBinary(const char * lpszSection, const char * lpszEntry,
               LPBYTE pData, UINT nBytes);

      // Override in derived class.
      virtual void InitLibId();

      // Register
      virtual BOOL Register();

      // Unregisters everything this cast was known to register.
      virtual BOOL Unregister();

      // Delete a registry key entry (and all its subkeys, too).
      LONG DelRegTree(HKEY hParentKey, const string & strKeyName);

   // Running Operations - to be done on a running application
      // Dealing with document templates
      void add_document_template(document_template * ptemplate);
      count get_template_count() const;
      document_template * get_template(index index) const;

      // open named file, trying to match a regsitered
      // document template to it.
      virtual void on_request(var & varFile, var & varQuery);


      // Printer DC Setup routine, 'struct tagPD' is a PRINTDLG structure.
      void SelectPrinter(HANDLE hDevNames, HANDLE hDevMode,
         BOOL bFreeOld = TRUE);

      // create a DC for the system default printer.
      BOOL CreatePrinterDC(::ca::graphics_sp& spgraphics);


   //   BOOL GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg);

      // run this cast as an embedded object.
      BOOL RunEmbedded();

      // run this cast as an OLE automation server.
      BOOL RunAutomated();

      // Parse the command line for stock options and commands.
   //   void ParseCommandLine(CCommandLineInfo& rCmdInfo);

      // React to a shell-issued command line directive.
   //   BOOL ProcessShellCommand(CCommandLineInfo& rCmdInfo);

   // Overridables

      // Hooks for your initialization code
      virtual BOOL InitApplication();

      // exiting
      virtual BOOL save_all_modified(); // save before exit
      void HideApplication();
      void close_all_documents(BOOL bEndSession); // close documents before exiting

      // Advanced: to override message boxes and other hooks
      virtual int DoMessageBox(const char * lpszPrompt, UINT nType, UINT nIDPrompt);
      virtual void DoWaitCursor(int nCode); // 0 => restore, 1=> begin, -1=> end

      // Advanced: process async DDE request
      virtual BOOL OnDDECommand(LPTSTR lpszCommand);

      // Advanced: Help support
      virtual void WinHelp(DWORD_PTR dwData, UINT nCmd = HELP_CONTEXT);
      virtual void HtmlHelp(DWORD_PTR dwData, UINT nCmd = 0x000F);
      virtual void WinHelpInternal(DWORD_PTR dwData, UINT nCmd = HELP_CONTEXT);

   // Command Handlers
   protected:
      // ::collection::map to the following for file new/open
      afx_msg void _001OnFileNew();
      afx_msg void on_file_open();

      // ::collection::map to the following to enable print setup
      afx_msg void OnFilePrintSetup();

      // ::collection::map to the following to enable help
      afx_msg void OnContextHelp();   // shift-F1
      afx_msg void OnHelp();          // F1 (uses current context)
      afx_msg void OnHelpIndex();     // ID_HELP_INDEX
      afx_msg void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      afx_msg void OnHelpUsing();     // ID_HELP_USING

   // Implementation
   public:

      void UpdatePrinterSelection(BOOL bForceDefaults);
      void SaveStdProfileSettings();  // save options to .INI file



      void DevModeChange(LPTSTR lpDeviceName);
      virtual void SetCurrentHandles() = 0;

      // Finds number of opened document items owned by templates
      // registered with the doc manager.
      int get_open_document_count();

      // helpers for standard commdlg dialogs
      BOOL do_prompt_file_name(string & fileName, UINT nIDSTitle,
            DWORD lFlags, BOOL bOpenFileDialog, document_template * ptemplate);

      void EnableModeless(BOOL bEnable); // to disable OLE in-place dialogs

      // overrides for implementation
      virtual bool initialize_instance();
      virtual int exit_instance(); // return cast exit code
      virtual int run();
      virtual BOOL on_idle(LONG lCount); // return TRUE if more idle processing
      virtual void ProcessWndProcException(base_exception* e, gen::signal_object * pobj);

       // Helper for message boxes; can work when no application can be found
      static int ShowAppMessageBox(application *pApp, const char * lpszPrompt, UINT nType, UINT nIDPrompt);
      static void DoEnableModeless(BOOL bEnable); // to disable OLE in-place dialogs

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      // helpers for registration
      HKEY GetSectionKey(const char * lpszSection);
      HKEY GetAppRegistryKey();

      afx_msg void OnAppExit();
   public :
      // System Policy Settings
      virtual BOOL LoadSysPolicies(); // Override to load policies other than the system policies that ca2 API loads.
      BOOL GetSysPolicyValue(DWORD dwPolicyID, BOOL *pbValue); // returns the policy's setting in the out parameter
   protected :
      BOOL _LoadSysPolicies() throw(); // Implementation helper
   public:
      static const char _afxFileSection[];
      static const char _afxFileEntry[];
      static const char _afxPreviewSection[];
      static const char _afxPreviewEntry[];

      virtual ::ca::application * get_app() const;
      virtual string get_mutex_name_radix();

      virtual void on_exclusive_instance_conflict(EExclusiveInstance eexclusive);
      virtual void on_exclusive_instance_local_conflict();

      virtual void message_window_message_handler(gen::signal_object * pobj);

      virtual void delete_temp();

   var & oprop(::radix::object * pobject, id id);

   virtual HWND get_ca2_app_wnd(const char * psz);

   virtual ::user::interaction * uie_from_point(point pt);

   virtual void get_cursor_pos(LPPOINT lppoint);
   virtual void get_screen_rect(LPRECT lprect);

   virtual ::user::interaction * release_capture_uie();
   virtual ::user::interaction * get_capture_uie();

   virtual ::user::keyboard_focus * get_keyboard_focus();
   virtual void set_keyboard_focus(::user::keyboard_focus * pkeyboardfocus);
   virtual ::user::mouse_focus * get_mouse_focus_LButtonDown();
   virtual void set_mouse_focus_LButtonDown(::user::mouse_focus * pmousefocus);

   virtual int get_document_count();

   // transparent ::ca::window framework
   

   mutex * get_mutex(::radix::object * pobject);
   bool lock(::radix::object * pobject, DWORD dwTimeout = INFINITE);
   bool unlock(::radix::object * pobject);

   CEvent * get_event(::radix::object * pobject, int iEvent = 0);
   bool event_lock(::radix::object * pobject, int iEvent = 0, DWORD dwTimeout = INFINITE);
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



   static inline application & app_cast(::ca::ca * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

   virtual bool initialize1();

   ::user::str & str();
   ::user::str_context * str_context();

   virtual void on_delete(::ca::object * pobject);

   };

} // namespace radix


typedef ::ca::application * (* LP_GET_NEW_APP) (void);
