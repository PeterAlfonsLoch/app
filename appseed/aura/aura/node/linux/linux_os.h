#pragma once


namespace linux
{


   class CLASS_DECL_AURA os :
      public ::aura::os
   {
   public:


      os(sp(::aura::application) papp);
      virtual ~os();


      virtual bool reboot();
      virtual bool shutdown(bool bPowerOff);

      virtual void terminate_processes_by_title(const char * pszName);
      virtual string get_module_path(HMODULE hmodule);
      virtual bool get_pid_by_path(const char * pszName, DWORD & dwPid);
      virtual bool get_pid_by_title(const char * pszName, DWORD & dwPid);
      virtual void get_all_processes(uint_array & dwa);
      virtual ::file::path get_process_path(DWORD dwPid);
      virtual int get_pid();

      virtual bool connection_settings_get_auto_detect();
      virtual string connection_settings_get_auto_config_url();


      virtual bool local_machine_set_run(const char * pszKey, const char * pszCommand);
      virtual bool local_machine_set_run_once(const char * pszKey, const char * pszCommand);
      virtual bool current_user_set_run(const char * pszKey, const char * pszCommand);
      virtual bool current_user_set_run_once(const char * pszKey, const char * pszCommand);
      virtual bool defer_register_ca2_plugin_for_mozilla();

      virtual bool file_extension_get_open_with_list_keys(stringa & straKey, const char * pszExtension);
      virtual bool file_extension_get_open_with_list_commands(stringa & straCommand, const char * pszExtension);

      virtual bool file_association_set_default_icon(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszIconPath);
      virtual bool file_association_set_shell_open_command(const char * pszExtension, const char * pszExtensionNamingClass,  const char * pszCommand, const char * pszParam);
      virtual bool file_association_get_shell_open_command(const char * pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam);


      virtual bool open_in_ie(const char * lpcsz);

      virtual bool create_service(::aura::application * papp);
      virtual bool remove_service(::aura::application * papp);

      virtual bool start_service(::aura::application * papp);
      virtual bool stop_service(::aura::application * papp);

      void raise_exception( DWORD dwExceptionCode, DWORD dwExceptionFlags);

      virtual bool is_remote_session();

      virtual void post_to_all_threads(UINT message, WPARAM wParam, LPARAM lParam);


      virtual bool initialize_wallpaper_fileset(::file::set * pfileset, bool bAddSearch) override;

      virtual bool get_default_browser(string & strId, ::file::path & path, string & strParam) override;

   };


} // namespace linux




