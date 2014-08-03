#pragma once


namespace gen
{


   class command_line;


} // namespace gen


namespace metrowin
{


   class CLASS_DECL_BASE main_init_data :
      public ::base::main_init_data
   {
   public:


      HINSTANCE   m_hInstance;
      HINSTANCE   m_hPrevInstance;
      int         m_nCmdShow;


   };


   class CLASS_DECL_BASE application :
      virtual public ::base::application
   {
   public:



      USHORT               m_atomApp;
      USHORT               m_atomSystemTopic;

      main_init_data *     m_pmaininitdata;


      application(::base::application * papp);
      virtual ~application();
      
      virtual HINSTANCE GetHinstance();
      bool _001OnDDECommand(const char * lpcsz);
      virtual void _001EnableShellOpen();
      virtual sp(::user::document) _001OpenDocumentFile(var varFile);
      virtual void _001OnFileNew();

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

      virtual string get_version();

      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();

//      virtual bool DeferRegisterClass(LONG fToRegister, const char ** ppszClass);
      virtual void LockTempMaps();
      virtual bool UnlockTempMaps(bool bDeleteTemps = TRUE);
      virtual void TermThread(HINSTANCE hInstTerm);
      //virtual const char * RegisterWndClass(UINT nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);


      virtual void SetCurrentHandles();

      virtual bool set_main_init_data(::base::main_init_data * pdata);

      virtual bool process_initialize();
      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize3();
      virtual int  exit_instance();



      
      virtual bool win_init(main_init_data * pdata);



      virtual bool update_module_paths();



























      /*virtual void construct(__THREADPROC pfnThreadProc, LPVOID pParam);

      virtual bool begin(int nPriority = THREAD_PRIORITY_NORMAL, UINT nStackSize = 0,
         DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

      bool CreateThread(DWORD dwCreateFlags = 0, UINT nStackSize = 0,
         LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

      virtual int_ptr get_os_data();
      virtual int_ptr get_os_int();


      int GetThreadPriority();
      bool SetThreadPriority(int nPriority);

   // Operations
      DWORD SuspendThread();
      DWORD ResumeThread();
      bool PostThreadMessage(UINT message, WPARAM wParam, LPARAM lParam);
      bool post_message(::user::interaction * pguie, UINT message, WPARAM wParam, LPARAM lParam);

      virtual bool PreInitInstance();

      // called when occurs an standard_exception exception in run
      // return true to call run again
      virtual bool on_run_exception(::exception::exception & e);

   // Overridables
      // thread initialization
      virtual bool initialize_instance();

      virtual ::message::e_prototype GetMessagePrototype(UINT uiMessage, UINT uiCode); 

      // running and idle processing
      virtual int run();
      virtual void pre_translate_message(signal_details * pobj);
      virtual bool pump_message();     // low level message pump
      virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
      virtual bool is_idle_message(MSG* pMsg);  // checks for special messages

      // thread termination
      virtual int exit_instance(); // default will 'delete this'

      // Advanced: exception handling
      virtual LRESULT ProcessWndProcException(::exception::base* e, const MSG* pMsg);

      // Advanced: handling messages sent to message filter hook
      virtual bool ProcessMessageFilter(int code, LPMSG lpMsg);

      // Advanced: virtual access to GetMainWnd()
      virtual ::user::interaction* GetMainWnd();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
      virtual void CommonConstruct();
      virtual void Delete();
         // 'delete this' only if m_bAutoDelete == TRUE



      bool DispatchThreadMessageEx(MSG* msg);  // helper*/

      //::draw2d::graphics * graphics_from_os_data(void * pdata);

      
      sp(::user::interaction) window_from_os_data(void * pdata);
      sp(::user::interaction) window_from_os_data_permanent(void * pdata);

      virtual ::thread * GetThread();
      virtual void set_thread(::thread * pthread);

      virtual sp(::user::interaction) FindWindow(const char * lpszClassName, const char * lpszWindowName);
      virtual sp(::user::interaction) FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow);

      virtual void get_time(struct timeval *p);
      virtual void set_env_var(const string & var,const string & value);
      virtual uint32_t get_thread_id();
   
      sp(::user::printer) get_printer(const char * pszDeviceName);


      void ShowWaitCursor(bool bShow);

      virtual string draw2d_get_default_library_name();

      string veriwell_multimedia_music_midi_get_default_library_name();


         string multimedia_audio_mixer_get_default_library_name();

         string multimedia_audio_get_default_library_name();

   };


} // namespace metrowin

