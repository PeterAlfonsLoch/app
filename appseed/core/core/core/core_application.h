#pragma once






CLASS_DECL_CORE UINT c_cdecl application_thread_procedure(LPVOID pvoid);

typedef sp(::base::application) (*LPFN_instantiate_application)(sp(::base::application) pappParent, const char * pszId);

extern CLASS_DECL_CORE LPFN_instantiate_application g_lpfn_instantiate_application;


class type;
class system;
class window_draw;







class CLASS_DECL_CORE application :
   virtual public ::base::application,
   virtual public ::database::client
{
public:

   ::calculator::calculator *          m_pcalculator;
   ::colorertake5::colorertake5 *      m_pcolorertake5;


   sp(::userfs::userfs)                m_spuserfs;
   
   ::simpledb::simpledb                m_simpledb;
   sp(::userex::userex)                m_spuserex;



   ::core::main_init_data *            m_pinitmaindata;
   bool                                m_bService;
   ::plane::system *                   m_psystem;
   sp(base_session)                    m_psession;

   class signal                        m_signalAppLanguageChange;
   string                              m_strHelpFilePath;
   mutex                               m_mutex;

   application_bias                    m_biasCalling;


#ifdef WINDOWS


   HGLOBAL                             m_hDevMode;             // printer Dev Mode
   HGLOBAL                             m_hDevNames;            // printer Device Names


#endif

   uint32_t                            m_dwPromptContext;        // help context override for message box
   // LKG
   uint32_t                            m_dwPolicies;            // block for storing boolean system policies

   // Name of registry key for this application. See
   // SetRegistryKey() member function.
   const char *                        m_pszRegistryKey;

   // Pointer to ::user::document_manager used to manage document templates
   // for this application instance.
   sp(::user::document_manager)        m_pdocmanager;

   // Support for Shift+F1 help mode.
   // TRUE if we're in SHIFT+F1 mode.
   bool                                m_bHelpMode;

   // set in constructor to override default


   // Default based on this module's path.
   const char *                  m_pszHelpFilePath;

   // Default based on this application's name.
   const char *                  m_pszProfileName;
   // help mode used by the cast
   //      __HELP_TYPE m_eHelpType;

   //CCommandLineInfo* m_pCmdInfo;

   ATOM m_atomApp, m_atomSystemTopic;   // for DDE open
   UINT m_nNumPreviewPages;        // number of default printed pages

   string                           m_strId;

   //mutex                            m_mutexObjectLock;
   //map < ::waitable *, ::waitable *, mutex *, mutex * > m_mapObjectMutex;

   //mutex                            m_mutexObjectEvent;
   //map < object *, object *, map < int32_t, int32_t, event *, event * > *, map < int32_t, int32_t, event *, event * >  * > m_mapObjectEvent;

   //typedef map < object *, object *, property_set, property_set > oset;
   //oset                             m_mapObjectSet;



   int32_t                          m_iResourceId;

   //BaseIdSpaceIntegerMap      m_imapResource;
   //BaseIdSpaceStringKeyMap    m_strmapResource;
   //   id_space                   m_idspace;
   sp(::user::uinteraction::uinteraction) m_puinteraction;
   //sp(::user::user)              m_puserbase;
   //sp(::userex::userex) m_puserex;
   sp(::usermail::usermail)         m_pusermail;
#ifdef WINDOWSEX
   raw_array < MONITORINFO >            m_monitorinfoa;
   raw_array < MONITORINFO >            m_monitorinfoaDesk;
#endif

   stringa                          m_straAppInterest;
   string_map < oswindow, oswindow > m_mapAppInterest;



   application();
   virtual ~application();


   virtual bool init_main_data(::core::main_init_data * pdata);
   virtual bool set_main_init_data(::core::main_init_data * pdata);

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

   virtual application * get_app() const;

   virtual bool is_system();
   virtual bool is_session();

   virtual bool is_installing();
   virtual bool is_uninstalling();

   virtual bool is_serviceable();



   virtual void pre_translate_message(signal_details * pobj);


   virtual void install_message_handling(::message::dispatch * pdispatch);

   //virtual int32_t run();


   virtual void EnableShellOpen();




   virtual void _001CloseApplication();



   virtual bool start_application(bool bSynch, application_bias * pbias);


   //virtual bool update_module_paths();


   inline ::calculator::calculator           & calculator() { return *m_pcalculator; }
   inline ::colorertake5::colorertake5       & colorertake5() { return *m_pcolorertake5; }

   inline sp(::html::html)                   html()         { return m_phtml; }
   inline class ::simpledb::simpledb         & simpledb()   { return m_simpledb; }
   inline sp(::userex::userex)               userex()       { return m_spuserex; }



   virtual bool base_support();

   virtual string message_box(const string & pszMatter, property_set & propertyset);


   virtual sp(::user::interaction) uie_from_point(point pt);


   virtual void set_env_var(const string & var, const string & value);
   //virtual uint32_t get_thread_id();

   virtual bool on_install();
   virtual bool on_uninstall();
   virtual bool on_run_install();
   virtual bool on_run_uninstall();

   DECL_GEN_SIGNAL(_001OnApplicationRequest);




      DECL_GEN_SIGNAL(on_application_signal);


   // open named file, trying to match a regsitered
   // document template to it.
   virtual void on_request(sp(::create_context) pline);

   virtual void defer_add_document_template(sp(::user::impact_system) ptemplate);

   // overrides for implementation
   virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
   virtual void ProcessWndProcException(::exception::base* e, signal_details * pobj);


   void EnableModelessEx(bool bEnable);
#ifdef WINDOWS
   HENHMETAFILE LoadEnhMetaFile(UINT uiResource);
#endif
   bool GetResourceData(UINT nID, const char * lcszType, primitive::memory & storage);

#ifdef WINDOWS
   virtual bool OnMessageWindowMessage(LPMESSAGE lpmsg);
#elif defined(LINUX)
   virtual bool OnMessageWindowMessage(XEvent * pev);
#endif

   bool CreateFileFromRawResource(UINT nID, const char * lcszType, const char * lpcszFilePath);
   virtual LRESULT GetPaintMsgProc(int32_t nCode, WPARAM wParam, LPARAM lParam);


   void OnUpdateRecentFileMenu(cmd_ui * pcmdui);

   virtual DECL_GEN_SIGNAL(OnAppLanguage);
      virtual bool _001OnCmdMsg(base_cmd_msg * pcmdmsg);




   void EnableHtmlHelp();


   virtual int32_t simple_message_box_timeout(sp(::user::interaction) puiOwner, const char * pszMessage, ::duration durationTimeout, UINT fuStyle = MB_OK);
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


   virtual bool on_run_exception(::exception::exception &);


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

   // Finds number of opened document items owned by templates
   // registered with the doc manager.
   int32_t get_open_document_count();

   bool do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, sp(::user::impact_system) ptemplate, sp(::user::object) pdocument);

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
   virtual bool LoadSysPolicies(); // Override to load policies other than the system policies that core API loads.
   bool GetSysPolicyValue(uint32_t dwPolicyID, bool *pbValue); // returns the policy's setting in the out parameter
   bool _LoadSysPolicies() throw(); // Implementation helper
   static const char gen_FileSection[];
   static const char gen_FileEntry[];
   static const char gen_PreviewSection[];
   static const char gen_PreviewEntry[];



   virtual void delete_temp();

   //using thread::propset;
   //property_set & propset(object * pobject);
   //property_set * existing_propset(object * pobject);

   virtual oswindow get_ca2_app_wnd(const char * psz);


   //   virtual void get_screen_rect(LPRECT lprect);



   virtual int32_t get_document_count();

   // transparent window framework


   //mutex * get_mutex(::waitable * pobject);
   //using thread::lock;
   //void wait(::waitable * pobject);
   //wait_result wait(::waitable * pobject, duration dwTimeout);
   //void lock(::waitable * pobject);
   //bool lock(::waitable * pobject, duration dwTimeout);
   //using thread::unlock;
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



   // Temporary map management (locks temp map on current thread)
   virtual void LockTempMaps();
   virtual bool UnlockTempMaps(bool bDeleteTemps = TRUE);
   virtual void TermThread(HINSTANCE hInstTerm);

   //virtual ::draw2d::graphics * graphics_from_os_data(void * pdata);


   virtual ::window_sp FindWindow(const char * lpszClassName, const char * lpszWindowName);
   virtual ::window_sp FindWindowEx(oswindow oswindowParent, oswindow oswindowChildAfter, const char * lpszClass, const char * lpszWindow);



   virtual bool final_handle_exception(::exception::exception &);





   virtual sp(::user::interaction) get_request_parent_ui(sp(::user::interaction) pinteraction, sp(::create_context) pcontext);




   //      virtual ::core::file_system & file_system();
   virtual bool _001OnDDECommand(const char * lpcsz);
   virtual void _001EnableShellOpen();
   virtual sp(::user::object) _001OpenDocumentFile(var varFile);
   DECL_GEN_SIGNAL(_001OnFileNew);


   virtual string get_version();

   virtual bool Ex2OnAppInstall();
   virtual bool Ex2OnAppUninstall();

   //virtual thread * GetThread();
   //virtual void set_thread(thread * pthread);


   virtual ::window_sp get_desktop_window();



   //      virtual void construct();


   //virtual bool final_handle_exception(::exception::exception &);
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

   //      virtual void on_request(sp(::create_context) pcreatecontext);

   //      sp(::user::object) _001OpenDocumentFile(var varFile);

   sp(::base::application) get_system();



   //      virtual void defer_add_document_template(sp(::user::impact_system) ptemplate);

   void enum_display_monitors();

#if defined(WINDOWS)

   static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

   void monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor);

#endif





   virtual bool set_keyboard_layout(const char * pszPath, ::action::context actioncontext);


   inline ::user::uinteraction::uinteraction          & uinteraction() { return *m_puinteraction; }
   ///inline ::user::user                  & user     () { return *m_puserbase      ; }
   //      inline ::userex::userex                      & userex       () { return *m_puserex        ; }
   inline ::usermail::usermail                          & usermail() { return *m_pusermail; }


   string message_box(const char * pszMatter, property_set & propertyset);
   //using application::simple_message_box;
   //virtual int32_t simple_message_box_timeout(sp(::user::interaction) puiOwner, const char * pszMessage, ::duration durationTimeout, UINT fuStyle = MB_OK);
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


   //virtual void request_create(sp(::create_context) pcreatecontext);

   //      virtual void on_exclusive_instance_local_conflict();

   virtual int32_t send_simple_command(const char * psz, void * osdataSender);
   virtual int32_t send_simple_command(void * osdata, const char * psz, void * osdataSender);

   virtual sp(::user::printer) get_printer(const char * pszDeviceName);

   /*
   virtual string draw2d_get_default_library_name();
   virtual string multimedia_audio_get_default_library_name();
   virtual string multimedia_audio_mixer_get_default_library_name();
   virtual string veriwell_multimedia_music_midi_get_default_library_name();
   */


   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;













   virtual sp(::base::application) instantiate_application(const char * pszType, const char * pszId, application_bias * pbias);
   virtual sp(::base::application) create_application(const char * pszType, const char * pszId, bool bSynch, application_bias * pbias);




   //////////////////////////////////////////////////////////////////////////////////////////////////
   // System/System
   //
   sp(::user::object) place_hold(sp(::user::interaction) pui);

   virtual ::count get_monitor_count();
   virtual bool  get_monitor_rect(index i, LPRECT lprect);
   virtual ::count get_desk_monitor_count();
   virtual bool  get_desk_monitor_rect(index i, LPRECT lprect);



   //////////////////////////////////////////////////////////////////////////////////////////////////
   // Session/Session
   //
   //         virtual sp(::bergedge::view) get_view();
   //       virtual sp(::bergedge::document) get_document();


   virtual bool add_library(::core::library * plibrary);

   virtual ::userex::userex * create_userex();
   virtual ::userfs::userfs * create_userfs();
   virtual ::html::html * create_html();


   //virtual void assert_valid() const;
   //virtual void dump(dump_context & context) const;


   //virtual void construct();
   //virtual void construct(const char * pszId);


   //virtual void _001OnFileNew();


   //virtual void on_request(sp(::create_context) pcreatecontext);

   //sp(::user::object) _001OpenDocumentFile(var varFile);

   //sp(::base::application) get_system();

   //virtual sp(::application) assert_running(const char * pszAppdId);









   // smart_pointer < ::cubebase::application >::oattrib
   // or any function needing it
   application & operator = (const application & app)
   {

      UNREFERENCED_PARAMETER(app);

      // do nothing

      return *this;

   }

   // get a file and if there are exceptions, should show end user friendly messages
   virtual ::file::binary_buffer_sp friendly_get_file(var varFile, UINT nOpenFlags);


   virtual void data_on_after_change(signal_details * pobj);

//   virtual int32_t simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
//   virtual int32_t simple_message_box_timeout(sp(::user::interaction) pwndOwner, const char * pszMessage, ::duration durationTimeOut, UINT fuStyle = MB_OK);


};


CLASS_DECL_CORE UINT c_cdecl application_thread_procedure(LPVOID pvoid);

typedef sp(::base::application) (*LPFN_instantiate_application)(sp(::base::application) pappParent, const char * pszId);

extern CLASS_DECL_CORE LPFN_instantiate_application g_lpfn_instantiate_application;


namespace core
{

   // impl
   template < class APP >
   sp(::base::application) single_application_library < APP > ::get_new_app(const char * pszAppId)
   {

      if (!contains_app(pszAppId))
         return NULL;

      sp(application) papp = canew(APP());

      if (papp == NULL)
         return NULL;

      try
      {
         papp->m_pplaneapp->construct(pszAppId);
      }
      catch (...)
      {
         try
         {
            papp.release();
         }
         catch (...)
         {
         }
         return NULL;
      }

      return papp;

   }


} // namespace core








