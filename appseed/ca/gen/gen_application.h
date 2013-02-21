#pragma once


namespace gen
{


   namespace lemon
   {


      class array;


   } // namespace lemon


   class CLASS_DECL_ca application :
      virtual public ex1::application,
      virtual public command_target_interface
   {
   public:


      class base64                        m_base64;
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


      application();
      virtual ~application();



      math::math & math();
      geometry::geometry & geometry();
      class savings & savings();

      lemon::array * m_plemonarray;

      lemon::array & lemon_array();


      virtual ::ca::application * get_app() const;

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

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

      virtual bool process_initialize();

      virtual bool initialize_instance();
      virtual int32_t exit_instance();

      virtual bool verb();

      void OnUpdateRecentFileMenu(cmd_ui * pcmdui) ;

      virtual DECL_GEN_SIGNAL(OnAppLanguage)
      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);


      class base64 & base64();

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


   };



} // namespace gen


/*CLASS_DECL_ca void __cdecl wparse_cmdline (
    WCHAR *cmdstart,
    WCHAR **argv,
    WCHAR *args,
    int32_t *numargs,
    int32_t *numchars
    );
*/
