#pragma once

namespace gen
{
   class command_line;
}

namespace ios
{

   class CLASS_DECL_AURA main_init_data :
      public ::core::main_init_data
   {
   public:
      HINSTANCE   m_hInstance;
     HINSTANCE   m_hPrevInstance;
      string      m_strCommandLine;
      int         m_nCmdShow;
   };

   class CLASS_DECL_AURA application :
   virtual public ::aura::application
   {
   public:

      USHORT               m_atomApp;
      USHORT               m_atomSystemTopic;
      
      main_init_data *     m_pmaininitdata;
      
      
      application(::aura::application * papp);
      virtual ~application();
      
      virtual HINSTANCE GetHinstance();
      bool _001OnDDECommand(const char * lpcsz);
      virtual void _001EnableShellOpen();
      virtual sp(::user::object) _001OpenDocumentFile(var varFile);
      virtual void _001OnFileNew();
      
      
      virtual void ShowWaitCursor(bool bShow);
      
      
      
      virtual string get_version();
      virtual void TermThread(HINSTANCE hInstTerm);
      
      virtual void SetCurrentHandles();
      
      virtual bool set_main_init_data(::core::main_init_data * pdata);
      
      virtual bool process_initialize();
      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize3();
      virtual int32_t  exit_instance();
      
      
      
      
      virtual bool win_init(main_init_data * pdata);
      
      virtual bool update_module_paths();
      
      
      
      
      
      sp(::user::interaction) window_from_os_data(void * pdata);
      sp(::user::interaction) window_from_os_data_permanent(void * pdata);
      
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

      virtual void ShowWaitCursor(bool bShow);
   
      
   };

   
} // namespace ios






