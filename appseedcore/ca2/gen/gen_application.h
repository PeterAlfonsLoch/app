#pragma once


namespace gen
{

   namespace lemon
   {
      class array;
   }

   class CLASS_DECL_ca application :
      public ex1::application,
      virtual public command_target_interface
   {
   public:
      
      
      class base64               m_base64;
      signal                     m_signalAppLanguageChange;
      class gen::command_line *  m_pcommandline;
      math::math *               m_pmath;
      geometry::geometry *       m_pgeometry;
      class savings *            m_psavings;
      string                     m_strCa2ModulePath;
      string                     m_strCa2ModuleFolder;
      string                     m_strModulePath;
      string                     m_strModuleFolder;
      string                     m_strHelpFilePath;

      
      application();
      virtual ~application();



      math::math & math();
      geometry::geometry & geometry();
      class savings & savings();
      class command_line & command_line();

      lemon::array * m_plemonarray;

      lemon::array & lemon_array();


      virtual ::ca::application * get_app() const;

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual int run();
      virtual BOOL on_idle(LONG lCount); // return TRUE if more idle processing
      virtual void ProcessWndProcException(base_exception* e, gen::signal_object * pobj);


      void EnableModelessEx(BOOL bEnable);
      HENHMETAFILE LoadEnhMetaFile(UINT uiResource);
      bool GetResourceData(UINT nID, const char * lcszType, primitive::memory & storage);
      virtual string get_ca2_module_folder();
      virtual string get_ca2_module_file_path();
      virtual string get_module_folder();
      virtual string get_module_file_path();
      virtual string get_module_title();
      virtual string get_module_name();

      static UINT   APPM_LANGUAGE;
      static WPARAM WPARAM_LANGUAGE_UPDATE;

      virtual bool OnMessageWindowMessage(LPMSG lpmsg);

      bool CreateFileFromRawResource(UINT nID, const char * lcszType, const char * lpcszFilePath);
      virtual LRESULT GetPaintMsgProc(int nCode, WPARAM wParam, LPARAM lParam);
       
      virtual bool process_initialize();
      virtual void on_process_initialize_command_line();

      virtual bool initialize_instance();
      virtual int exit_instance();

      afx_msg void OnUpdateRecentFileMenu(cmd_ui * pcmdui) ;

      virtual DECL_GEN_SIGNAL(OnAppLanguage)
      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
         

      class base64 & base64();

      virtual string get_local_mutex_id();
      virtual string get_global_mutex_id();

   };


   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }



} // namespace gen


CLASS_DECL_ca void __cdecl wparse_cmdline (
    WCHAR *cmdstart,
    WCHAR **argv,
    WCHAR *args,
    int *numargs,
    int *numchars
    );
