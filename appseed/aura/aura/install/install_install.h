#pragma once


namespace install
{


   class CLASS_DECL_AURA install :
      virtual public ::aura::department,
      virtual public int_scalar_source
   {
   public:


      bool                                m_bAdmin;

      string                              m_strId;

      HANDLE                              m_hmutexBoot;
      UINT                                m_nCa2StarterStartThreadID;
      bool                                m_bCa2Installed;
      bool                                m_bSpaInstalled;
      bool                                m_bSpaUpdated;
      string                              m_strCa2Build ;
      oswindow                            m_oswindowMessage;

      class trace                         m_trace;

      int_progress                        m_progressApp;

      int64_t                             m_iProgressAppInstallStart;
      int64_t                             m_iProgressAppInstallStep;
      int64_t                             m_iProgressAppInstallEnd;

      string                              m_strPlatform;
      string                              m_strConfiguration;

      ::sockets::socket_handler *         m_psockethandler;
      spa(::sockets::http_session)        m_httpsessionptra;


      install(::aura::application * papp);
      virtual ~install();


      inline class trace & trace() { return m_trace; }

      virtual bool is_file_ok(const ::file::path & path1,const char * pszTemplate,const char * pszFormatBuild);
      virtual bool is_file_ok(const ::file::patha & patha,const ::file::patha & straTemplate,stringa & straMd5,int_array & iaLen, int iRetry = 1);
      virtual bool reference_is_file_ok(const ::file::path & path1,const char * pszTemplate,const char * pszConfiguration,const char * pszFormatBuild);

      virtual int32_t synch_install(const char * pszCommand);
      virtual int32_t asynch_install(const char * pszCommand);

      virtual bool is_admin();
      virtual void set_admin(bool bSet);
      virtual string get_id();
      virtual void set_id(const char * psz);
      virtual string get_platform();
      virtual void set_platform(const string & strPlatform);

      virtual string get_latest_build_number(const char * pszConfiguration);

      int32_t spalib_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32_t nCmdShow);

      int32_t spaboot_registry_register(const char * lpszFile);

      int32_t start_app(const char * id);

      virtual void update_ca2_build();
      virtual const char * ca2_get_build();
      virtual void update_ca2_installed(bool bUnloadIfNotInstalled = true);
      virtual bool is_ca2_installed();

      virtual bool is_installing_ca2();

      virtual string app_install_get_extern_executable_path(stringa * pstraMd5 = NULL, int_array * piaLen = NULL, string_to_string * pmapMd5 = NULL, string_to_intptr * pmapLen = NULL);
      virtual string app_install_get_intern_executable_path();
      virtual void app_install_call_sync(const char * pszCommand);
      virtual bool app_install_send_short_message(const char * psz, bool bLaunch);
      virtual void app_install_send_response(const char * param);

      virtual void add_spa_start(const char * pszType, const char * pszId);
      virtual void remove_spa_start(const char * pszType, const char * pszId);
      virtual void add_app_install(const char * pszAppId, const char * pszAppType, const char * pszBuild, const char * pszLocale, const char * pszSchema);
      virtual bool is_application_installed(const char * pszAppId, const char * pszAppType, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema);
      virtual int32_t start(const char * pszCommandLine);
      virtual int32_t synch(const char * pszCommandLine);

      virtual void on_set_scalar(e_scalar escalar,int64_t iValue,int iFlags);
      virtual void get_scalar_minimum(e_scalar escalar, int64_t & i);
      virtual void get_scalar(e_scalar escalar, int64_t & i);
      virtual void get_scalar_maximum(e_scalar escalar, int64_t & i);


   };


} // namespace spa








