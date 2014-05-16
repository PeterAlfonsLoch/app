#pragma once


namespace gen
{

    class command_line;
    
}


namespace mac
{

   
   class CLASS_DECL_mac main_init_data :
      public ::core::main_init_data
   {
   public:
       
       
       HINSTANCE    m_hInstance;
       HINSTANCE    m_hPrevInstance;
       string       m_strCommandLine;
       int          m_nCmdShow;
      
      
   };

   
   class CLASS_DECL_mac application :
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
      virtual sp(::user::object) _001OpenDocumentFile(var varFile);
      virtual void _001OnFileNew();
      
      // Loads a cursor resource.
      HCURSOR LoadCursor(const char * lpszResourceName) const;
      HCURSOR LoadCursor(UINT nIDResource) const;
      
      // Loads a stock cursor resource; for for IDC_* values.
      HCURSOR LoadStandardCursor(const char * lpszCursorName) const;
      
      // Loads an OEM cursor; for all OCR_* values.
      HCURSOR LoadOEMCursor(UINT nIDCursor) const;
      
      virtual void ShowWaitCursor(bool bShow);
      
      // Loads an icon resource.
//      HICON LoadIcon(const char * lpszResourceName) const;
//      HICON LoadIcon(UINT nIDResource) const;

      // Loads an icon resource; for stock IDI_ values.
//      HICON LoadStandardIcon(const char * lpszIconName) const;
      
      // Loads an OEM icon resource; for all OIC_* values.
//      HICON LoadOEMIcon(UINT nIDIcon) const;
      
      virtual string get_version();
      
      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();
      
      virtual bool DeferRegisterClass(LONG fToRegister, const char ** ppszClass);
      virtual void LockTempMaps();
      virtual bool UnlockTempMaps(bool bDeleteTemps = TRUE);
      virtual void TermThread(HINSTANCE hInstTerm);
//      virtual const char * RegisterWndClass(UINT nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);
      
      
      virtual void SetCurrentHandles();
      
      virtual bool set_main_init_data(::core::main_init_data * pdata);
      
      virtual bool process_initialize();
      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize3();
      virtual int32_t  exit_instance();
      
      
      
      
      virtual bool win_init(main_init_data * pdata);
      
      virtual bool update_module_paths();
      
      
            
      sp(::window) window_from_os_data(void * pdata);
      sp(::window) window_from_os_data_permanent(void * pdata);
      
      virtual ::thread * GetThread();
      virtual void set_thread(::thread * pthread);
      
      virtual sp(::window) FindWindow(const char * lpszClassName, const char * lpszWindowName);
      virtual sp(::window) FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow);
      
      virtual void get_time(struct timeval *p);
      virtual void set_env_var(const string & var,const string & value);
      virtual uint32_t get_thread_id();
      
      
      virtual sp(::user::printer) get_printer(const char * pszDeviceName);

      string draw2d_get_default_library_name();
      string multimedia_audio_mixer_get_default_library_name();
      string multimedia_audio_get_default_library_name();
      string veriwell_multimedia_music_midi_get_default_library_name();

   
   };

   
} // namespace mac






