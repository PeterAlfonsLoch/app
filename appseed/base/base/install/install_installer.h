#pragma once


namespace install
{


   class CLASS_DECL_BASE installer :
      virtual public object,
      virtual public ::sockets::http_listener,
      virtual public int_scalar_source::listener
   {
   public:


      class CLASS_DECL_BASE launcher :
         virtual public ::launcher
      {
      public:

         string   m_strPath;
         string   m_strVersion;
         string   m_strBuild;


         launcher(sp(::aura::application) papp, const char * pszVersion, const char * pszBuild);

         virtual bool ensure_executable();

         virtual string get_executable_path();

      };


      mutex             m_mutex;

      stringa           m_straTerminateProcesses;
      stringa           m_straRestartCommandLine;
      stringa           m_straRestartProcess;
      string            m_strLastHost;
      string            m_strCurrentHost;
      bool              m_bStarterStart;
#ifdef WINDOWS
      MESSAGE           m_msg;
#endif
      string            m_strPlatform;

      string            m_strInstallLocale;
      string            m_strInstallSchema;

      string            m_strAppMatterList;

      uint32_t          m_dwDownloadCallbackLast100k;
      uint32_t          m_iDownloadCallbackColumn;
      uint64_t          m_dwDownloadLen;
      int32_t           m_cx;
      int32_t           m_cy;
      string            m_strHost;
      uint32_t          m_dwInstallStartTime;

      bool              m_bProgressModeAppInstall;
      double            m_dAppInstallProgressStart;
      double            m_dAppInstallProgressEnd;

      
#ifdef WINDOWS
      MESSAGE           m_msgSpaAdminWindow;
#endif
      bool              m_bShowPercentage;



      ::user::interaction * m_pwindow;

      string            m_strBuild;
      string            m_strBuildResource;
      string            m_strApplicationId;
      string            m_strApplicationType;
      string            m_strCommandLine;

      machine_event     m_machineevent;

      double            m_dProgress;
      double            m_dProgress1;
      double            m_dProgress2;
      ::xml::document   m_xmldocStringTable;
      int32_t           m_iStart;
      double_array      m_daDownloadRate;
      uint32_t          m_dwDownloadTick;
      uint64_t          m_dwDownload;
      int32_t           m_iDownloadRate;
      double            m_dDownloadRate;
      uint32_t          m_dwDownloadZeroRateTick;
      uint32_t          m_dwDownloadZeroRateRemain;
      uint32_t          m_dwDownloadRemain;
      bool              m_bForceUpdatedBuild;

      bool              m_bOfflineInstall;
      bool              m_bInternetInstall;
      string            m_strIndex;
      string            m_strIndexGz;
      string            m_strInstall;
      string            m_strInstallGz;
      string            m_strInstallStatusTemplate;

      bool              m_bInstallSet;

      double            m_dProgressStart;
      double            m_dProgressEnd;
      stringa           m_strSpa;
      stringa           m_straHost;
      double            m_dAnime;

      bool              m_NeedRestartBecauseOfReservedFile;
      bool              m_NeedRestartFatalError;
      bool              m_bLoginStartup;
      bool              m_bMsDownload;
      string            m_strTitle;
      string            m_strSpaIgnitionBaseUrl;
      uint64_t          m_dwCurFileLen;


      int32_t           m_nCmdShow;

      bool              m_bShow;

      int32_t           m_iScreen;
      int32_t           m_iProgressMode;
      int64_t           m_iTotalGzLen;
      int64_t           m_iProgressTotalGzLen;
      int64_t           m_iGzLen;
      int32_t           m_iStyle;
      string            m_strLogin;
      string            m_strSessid;
      string            m_strInstallFilter;
      string            m_strLocale;
      string            m_strLoginFailed;
      oswindow          m_oswindow;

      string            m_strFile;
      bool              m_bSynch;
      //bool              m_bInstalling;

      stringa           m_straHttpFailure;

      string            m_strVersion;

      installer(sp(::aura::application) papp);
      ~installer();

      uint32_t run();


      void set_progress(double dProgress);
      ::count download_file_list(stringa & stringa, string_to_intptr & mapLen, string_to_string & mapCrc, string_to_intptr & mapGzLen, string_to_intptr & mapFlag);

      static uint32_t thread_proc_run(void * lpParam);

      void PaintOpaqueBk(HDC hdc);

      bool get(const string& url_in, bool bExist, int64_t iLength, const char * pszCrc, int64_t iGzLen);

      bool download_file(const string& inplace, const string& url_in, bool bExist, bool bCheck, int64_t iLength, const char * pszCrc, int64_t iGzLen, int_ptr & iFlag);

      string ca2_get_dir(LPCSTR lpcszUrl);

      string ca2bz_get_dir(LPCSTR lpcszUrl);

      string ca2unbz_get_dir(LPCSTR lpcszUrl);

      string ca2inplace_get_dir(LPCSTR lpcszUrl);

      string ca2_get_file(LPCSTR lpcszUrl);

      string ca2bz_get_file(LPCSTR lpcszUrl, const char * pszCrc);

      string ca2unbz_get_file(LPCSTR lpcszUrl);

      string ca2inplace_get_file(LPCSTR lpcszUrl);

      bool ca2_fy_url(string & str, LPCSTR lpcszPath, bool bExist, int64_t iLength, const char * pszCrc, int64_t iGzLen, bool bIndex = false);

      int32_t GetFileList(stringa & stringa, LPCSTR lpcszPath, string_to_intptr & mapLen, string_to_intptr & mapGzLen, string_to_string & mapCrc, string_to_intptr & mapFlag);
      int32_t GetFileListEx(stringa & stringa, class stringa & straPath, string_to_intptr & mapLen, string_to_intptr & mapGzLen, string_to_string & mapCrc, string_to_intptr & mapFlag);

      int32_t GetLocalFileList(stringa & stringa, LPCSTR lpcszUrl);

      ::count UncompressFileList(stringa & stringa, string_to_string & strmapCrc);

      ::count CopyFileList(stringa & stringa, string_to_intptr & mapFlag);

      void ParseSpaIndex(::xml::node & node);

      string load_string(const char * pszId, const char * pszDefault);

      void ParseIndexFile(const char * psz, string_to_intptr & mapLen, string_to_string & mapCrc, string_to_intptr & mapGzLen, string_to_intptr & mapFlag);

      bool spa_exec(const char * psz);

      bool ignit_phase2();

      int32_t run_file(const char * pszFile, int32_t nCmdShow);

      int32_t starter_start(const char * pszCommandLine);

      int32_t application_name();

      int32_t appmatter_list();

      int32_t ca2_build_version();

      int32_t calc_host(string & strSpaHost, int32_t &iHostRetry);


      int32_t run_uninstall(const char * lpCmdLine, int32_t nCmdShow);

      int32_t run_uninstall_run(const char * lpCmdLine, int32_t nCmdShow);

      int32_t run_install(const char * lpCmdLine, int32_t nCmdShow);

      int32_t run_starter_start(int32_t nCmdShow);

      bool init_instance(int32_t nCmdShow);

      int32_t spaadmin_main(const char * pszCommandLine);

      bool is_application_opened(const char * psz);

      bool is_there_application_opened();

      void machine_signalize_close_application();

      bool machine_unsignalize_close_application();

      bool machine_check_close_application(bool bDefault);


      // it will install/update if there is a "breach"
      static void do_spa();

      // it will install forcing to install as it is possible
      void synch_starter_start();

      // it will install forcing to install as it is possible
      void start_starter_start();


      void add_spa_start(const char * pszId);


      bool m_reboot();


      void remove_spa_start(const char * pszId);


      virtual void on_http_complete(::sockets::http_socket * psocket, ::http::e_status estatus);


      //void ms_download_callback( int32_t i, uint_ptr dwLen);
      //void ms_get_callback( int32_t i, uint_ptr dwLen);

      // download rate
      void dlr(uint64_t dwDownload);

      void new_progress_end(double dMilestone);


      int32_t run_ca2_application_installer(const char * id);

      virtual int32_t install_synch(const char * pszCommandLine);
      virtual int32_t install_asynch(const char * pszCommandLine);

      virtual int32_t ca2_app_install_run(const char * pszCommandLine, uint32_t & dwStartError, bool bSynch);

      virtual void on_set_scalar(int_scalar_source * psource, e_scalar escalar, int64_t iValue);

   };


   CLASS_DECL_BASE int32_t ca2_app_install_run(const char * pszCommandLine, uint32_t & dwStartError, bool bSynch);


} // namespace install


