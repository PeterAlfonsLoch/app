#pragma once


extern bool g_bInstalling;


namespace spa
{


   class window;


   class CLASS_DECL_c installer
   {
   public:


      class CLASS_DECL_c launcher :
         virtual public ::launcher
      {
      public:

         vsstring m_strPath;
         
         virtual bool ensure_executable();

         virtual vsstring get_executable_path();

      };

      DWORD          m_dwDownloadCallbackLast100k;
      DWORD          m_iDownloadCallbackColumn;
      DWORD          m_dwDownloadLen;
      int            m_cx;
      int            m_cy;
      vsstring       m_strHost;
      DWORD          m_dwInstallStartTime;

      HINSTANCE      m_hinstance;
#ifdef WINDOWS
      MSG            m_msgSpaAdminWindow;
#endif
      bool           m_bShowPercentage;



      window *       m_pwindow;

      vsstring       m_strBuild;
      vsstring       m_strBuildResource;
      vsstring       m_strApplicationId;
      vsstring       m_strCommandLine;

      machine_event  m_machineevent;

      double         m_dProgress;
      double         m_dProgress1;
      double         m_dProgress2;
      XNode          m_nodeStringTable;
      int            m_iStart;
      simple_double_array m_daDownloadRate;
      DWORD          m_dwDownloadTick;
      DWORD          m_dwDownload;
      int            m_iDownloadRate;
      double         m_dDownloadRate;
      DWORD          m_dwDownloadZeroRateTick;
      DWORD          m_dwDownloadZeroRateRemain;
      DWORD          m_dwDownloadRemain;
      bool           m_bForceUpdatedBuild;

      bool           m_bOfflineInstall;
      bool           m_bInternetInstall;
      vsstring       m_strIndex;
      vsstring       m_strIndexGz;
      vsstring       m_strInstall;
      vsstring       m_strInstallGz;

      bool           m_bInstallSet;

      bool           m_bStarterStart;
      double         m_dProgressStart;
      double         m_dProgressEnd;
      stra_dup       m_strSpa;
      stra_dup       m_straHost;
      double         m_dAnime;

      bool           m_NeedRestartBecauseOfReservedFile;
      bool           m_NeedRestartFatalError;
      bool           m_bLoginStartup;
      bool           m_bMsDownload;
      vsstring       m_strTitle;
      vsstring       m_strSpaIgnitionBaseUrl;
      DWORD          m_dwCurFileLen;


      int            m_nCmdShow;

      bool           m_bShow;

      int            m_iScreen;
      int            m_iProgressMode;
      int            m_iTotalGzLen;
      int            m_iGzLen;
      int            m_iStyle;
      vsstring       m_strLogin;
      vsstring       m_strSessid;
      vsstring       m_strInstallFilter;
      vsstring       m_strLocale;
      vsstring       m_strLoginFailed;
      HWND           m_hwnd;

      vsstring       m_strFile;
      bool           m_bSynch;


      installer();
      ~installer();

      DWORD run();


      void set_progress(double dProgress);
      int download_file_list(stra_dup & stra_dup, simple_string_to_intptr & mapLen, simple_string_to_string & mapCrc, simple_string_to_intptr & mapGzLen);

      static DWORD WINAPI thread_proc_run(LPVOID lpParam);

      void PaintOpaqueBk(HDC hdc);

      bool get(const vsstring& url_in, bool bExist, int iLength, const char * pszCrc, int iGzLen);

      bool download_file(const vsstring& url_in, bool bExist, int iLength, const char * pszCrc, int iGzLen);

      vsstring ca2_get_dir(LPCTSTR lpcszUrl);

      vsstring ca2bz_get_dir(LPCTSTR lpcszUrl);

      vsstring ca2unbz_get_dir(LPCTSTR lpcszUrl);

      vsstring ca2_get_file(LPCTSTR lpcszUrl);

      vsstring ca2bz_get_file(LPCTSTR lpcszUrl, const char * pszCrc);

      vsstring ca2unbz_get_file(LPCTSTR lpcszUrl);

      bool ca2_fy_url(vsstring & str, LPCTSTR lpcszPath, bool bExist, int iLength, const char * pszCrc, int iGzLen, bool bIndex = false);

      int GetFileList(stra_dup & stra_dup, LPCTSTR lpcszPath, simple_string_to_intptr & mapLen, simple_string_to_intptr & mapGzLen, simple_string_to_string & mapCrc);

      int GetLocalFileList(stra_dup & stra_dup, LPCTSTR lpcszUrl);

      int UncompressFileList(stra_dup & stra_dup, simple_string_to_string & strmapCrc);

      int CopyFileList(stra_dup & stra_dup);

      void ParseSpaIndex(XNode & node);

      vsstring load_string(const char * pszId, const char * pszDefault);

      void ParseIndexFile(const char * psz, simple_string_to_intptr & mapLen, simple_string_to_string & mapCrc, simple_string_to_intptr & mapGzLen);

      bool spa_exec(const char * psz);

      bool ignit_phase2();

      int run_file(const char * pszFile, int nCmdShow);

      int starter_start(const char * pszCommandLine);

      int application_name();

      int ca2_build_version();

      int calc_host(vsstring & strSpaHost, int &iHostRetry);


      int run_uninstall(const char * lpCmdLine, int nCmdShow);

      int run_uninstall_run(const char * lpCmdLine, int nCmdShow);

      int run_install(const char * lpCmdLine, int nCmdShow);

      int run_starter_start(int nCmdShow);

      bool init_instance(HINSTANCE hinstance, int nCmdShow);

      int spaadmin_main(const char * pszCommandLine);

      bool is_application_opened(const char * psz);

      bool is_there_application_opened();

      void machine_signalize_close_application();

      bool machine_unsignalize_close_application();

      bool machine_check_close_application(bool bDefault);


      // it will install/update if there is a "breach"
      static void spa();

      // it will install forcing to install as it is possible
      void synch_starter_start();

      // it will install forcing to install as it is possible
      void start_starter_start();


      void add_spa_start(const char * pszId);


      bool m_reboot();


      void remove_spa_start(const char * pszId);
      void ms_download_callback( int i, DWORD_PTR dwLen);
      void ms_get_callback( int i, DWORD_PTR dwLen);

      // download rate
      void dlr(DWORD dwDownload);

      void new_progress_end(double dMilestone);


      int run_ca2_application_installer(const char * id);

   };


   CLASS_DECL_c int ca2_app_install_run(const char * pszCommandLine, DWORD & dwStartError, bool bSynch);


} // namespace spa


