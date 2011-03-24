#pragma once

class CMSMultiDocTemplate;
class DDEFrameWnd;
class KaraokeSDIFrame;
class CVmpHighThread;
class XfplayerThreadV2;
class CVmpPlaylistCallback;

// vmsp - veriwell musical studio player

namespace vmsp
{

   class notify_icon;
   class document_manager;

   class CLASS_DECL_CA2_CUBE application :
      virtual public ::veriedit::application,
      virtual public ::PlaylistCentralCallbackInterface
   {
   public:
      
      UINT                                 m_nDDECmdShow;

      ::userbase::single_document_template *        m_pdoctemplateCDBrowse;
      ::userbase::single_document_template *        m_pdoctemplateFileAssociations;
      ::userbase::single_document_template *        m_pdoctemplateSongDirectories;

      CMSMultiDocTemplate*                  m_pMainDocTemplate;
      ::userbase::multiple_document_template *      m_pMidiDocTemplate;
      ::userbase::document *                        m_pxfplayerdoc;
      ::userbase::single_document_template *        m_pAlbumDocTemplate;

      DDEFrameWnd *                        m_pddeframewnd;
      KaraokeSDIFrame *                   m_pKarWnd;

      MixerCentral *                      m_pMixerCentral;

      CVmpHighThread *                     m_phighthread;
      XfplayerThreadV2 *                  m_pthreadV2;
      vmsp::notify_icon *                  m_pnotifyicon;
      vmsp::document_manager *             m_pdocumentmanager;
      
      mediamanager::AlbumBuildThread *    m_pAlbumThread;
      ::userbase::multiple_document_template *      m_pvmstextdoctemplate;
      HMODULE                              m_hmoduleResource;
   //   CVmpPlaylistCallback *               m_pplaylistcallback;
      ::ca::window *                        m_pwndMessageBoxParent;

      CEvent                              m_evInitialized;

      CMenuV033  *                        m_pmenuPlayerShared;
      HACCEL                              m_hPlayerAccelTable;
      critical_section                     m_csLyricViewFonts;
      critical_section                     m_csTitleFonts;
      critical_section                     m_csSubTitleFonts;
      CEvent                              m_evWait;

      application();

      
      bool _001ProcessShellCommand(gen::command_line& rCmdInfo);
      virtual LRESULT GetPaintMsgProc(int nCode, WPARAM wParam, LPARAM lParam);

       
      void OnFileManagerOpenFile(
         ::filemanager::data * pdata,
         ::fs::item_array & itema);


      void construct();


      DECL_GEN_VSIGNAL(data_on_after_change)
      VMSRESULT OpenToolsAlbum();
      VMSRESULT CreateAlbumThread();
      int       GetEconoMode_();
      virtual bool MessageWindowListener(
         UINT message,
         WPARAM wparam,
         LPARAM lparam);

      ::document * _001OpenDocumentFile(var varFile);

      vmsp::notify_icon * GetNotifyIcon();
      vmsp::document_manager & GetDocumentManager();
      PlaylistCallbackInterface * GetPlaylistCallbackInterface();
      //ELanguage GetLanguage();
      DWORD GetKaraokeEncoding();
      void OnAfterKaraokeEncodingChange(::database::update_hint * puh);
      void SetKaraokeEnconding(DWORD dwCodePage);
   //   void OnAfterLanguageChange(ELanguage elanguage, ::database::update_hint * puh);
   //   ELanguage GetDefaultLanguage();
      void VerifyBrowsers();
      bool BeginVSeriesThreads();
      void GetDefaultSongFolderPath(string &strPath);
      //KaraokeSDIFrame * GetKaraokeSDIFrame();
      void SetXfplayerDoc(::userbase::document * pdoc);
      ::userbase::document * GetXfplayerDoc();
      //void OnCloseDefaultPlaylist();
      CVmsTextDoc * OpenTextFile(const char * lpcsz);
      //void GetDefaultPlaylistPathName(string & str);
      //PlaylistDoc * OpenDefaultPlaylist();
      //PlaylistDoc * GetDefaultPlaylist();
      
      virtual bool RestoreEnhancedMetaFiles();
      
      //bool InitializeDataCentral(CCommandLineInfo & cmdinfo);
      
      void UpdateMRU(BOOL bEnable, int nCount);
      
      void RegisterShellExtension(bool bRegister = true);

      //Savings * GetSavings();
   //   VMSRESULT ReserveSong(const char * lpcszPath, bool bDoPlay);
   //   VMSRESULT ReserveSongs(LPINT lpiaSongs, int iSongCount);
   //    VMSRESULT ReserveSong_(int iCode);
      string GetAppFolder();
      VMSRESULT SetAlbumThread(mediamanager::AlbumBuildThread * pAlbumThread);
      
      //::ca::font * GetStandartFont();
      ::userbase::multiple_document_template * GetMidiDocTemplate();
   //    CMessageFilterMainHook * GetMessageFilterMainHook();
      //::userbase::single_document_template * GetAlbumDocTemplate();
      mediamanager::AlbumBuildThread * GetAlbumThread();
      VMSRESULT ViewToolsAlbum();
      //KaraokeSDIFrame * GetKarWnd();
      //void SetEconoMode(int iNewEconoMode);
      void OnChangeEconoMode();

      //::userbase::multiple_document_template * GetPlaylistDocTemplate();
   //   void SetPlayerDocument(XfplayerDoc * lpDoc);
      
      //XfplayerDoc * GetPlayerDocument();
   //    inline LPDIRECT3D8 GetDirectDraw()
   //    {
   //        return m_spDirectDraw;
   //    }
   //   bool InitDirectDraw();
      void RegisterShellFileTypes( BOOL bCompat = FALSE );
       db_server * GetDBCentral();
       inline MixerCentral * GetMixerCentral();
   //   CSplash *                  m_pSplash;
      //PROCESS_INFORMATION            m_piImageLoader;
   //   LPDIRECTDRAW GetDirectDraw();
      inline CVmpHighThread * GetHighThread();
      inline XfplayerThreadV2 * GetThreadV2();
      //inline XfplayerThreadV3 * GetThreadV3();
      //CWaveIn * GetWaveIn();
   //   XfplayerDoc * GetOnlyDocument();
      
      void Exit();
      string m_XFToolTipV1ClassName;
      string m_XFViewClassName;
       string m_strMessageWndClassName;
      void LoadAppSettings();

      //UINT         m_uiMidiOutDevice;
   //    UINT            m_uiWaveInDevice;
      //::ca::font         m_font;
   //   XfplayerDoc   *GetPlayingDocument()
   //   {
   //      return m_pPlayingDocument;
   //   };
   //   void SetPlayingDocument(XfplayerDoc * playingDocument)
   //   {
   //      m_pPlayingDocument = playingDocument;
   //   };
      //CSongsDirectoriesSet *      m_SongsDirsSet;
      //CDataSource               m_DataSource;
   //   HANDLE                  m_hHeap;
      int                     m_iBackgroundUpdateMillis;
       UINT                        m_nMaxMRU;

      public:
      virtual bool initialize_instance();
      virtual int exit_instance();
      virtual void pre_translate_message(gen::signal_object * pobj);
      //virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
      //virtual ::document * _001OpenDocumentFile(const char * lpszFileName);
      virtual void AddToRecentFileList(const char * lpszPathName);
      //virtual int DoMessageBox(const char * lpszPrompt, UINT nType, UINT nIDPrompt);
      virtual BOOL OnDDECommand(LPTSTR lpszCommand);

      afx_msg void OnAppAbout();
      DECL_GEN_SIGNAL(_001OnFileOpen)
      afx_msg void on_file_open();
      afx_msg void _001OnFileNew();
      afx_msg void OnHelp();
      afx_msg void OnHelpFinder();
      afx_msg void OnFileNewFromplayerview();
      afx_msg void OnUpdateFileNewFromplayerview(cmd_ui * pcmdui);
      DECL_GEN_SIGNAL(_001OnToolsAlbum)
      afx_msg void OnUpdateToolsAlbum(cmd_ui * pcmdui);
      afx_msg void OnToolsOptions();
      afx_msg void OnUpdateToolsOptions(cmd_ui * pcmdui);
      afx_msg void OnUpdateRecentFileMenu(cmd_ui * pcmdui);
      afx_msg void OnUpdateLanguageChangeMenu(cmd_ui * pcmdui);
      afx_msg void OnLanguageEnus();
      afx_msg void OnUpdateLanguageEnus(cmd_ui * pcmdui);
      afx_msg void OnLanguagePtbr();
      afx_msg void OnUpdateLanguagePtbr(cmd_ui * pcmdui);
      afx_msg void OnLanguageDe();
      afx_msg void OnUpdateLanguageDe(cmd_ui * pcmdui);
      afx_msg void OnLanguageJp();
      afx_msg void OnUpdateLanguageJp(cmd_ui * pcmdui);
      afx_msg void OnContextHelp();
      afx_msg void OnPlayer();
      afx_msg void OnToolsOptionsFileAssociations();
      afx_msg void OnToolsOptionsSongDirectories();
      afx_msg void OnFileOpenCd();
      //}}AFX_MSG
      ()
       DECL_GEN_SIGNAL(OnUserMessage)
       DECL_GEN_SIGNAL(OnAppMessage)
   public:

      virtual bool _001OnUpdateCmdUi(cmd_ui * pcmdui);
      virtual bool _001OnCommand(class id id);

   };
   inline MixerCentral * application::GetMixerCentral()
   {
      return m_pMixerCentral;
   }

   inline vmsp::document_manager & application::GetDocumentManager()
   {
      return * m_pdocumentmanager;
   }

} // namespace vmsp

