#pragma once

class XfplayerFrameWndInterface;
class CSliderV017;
class KaraokeBouncingBall;
class CBaseRgnPtrArray;


class XfplayerScoring;
class KaraokeSDIFrame;
class CKaraokeControlSet1Wnd;
class CLevelMeterWnd;
class AudioSpectrumWnd;
class CImage;
class PlaylistDoc;
class PlaylistFrame;
class CPlaylistInPlaceWnd;
class PlaylistView;
class LyricViewLine;
class LyricViewLineTemplate;
class CSliderV008;
class XfplayerViewUpdateHint;
class CVmsTextDoc;
class MusicalPlayerPlaylistCallback;

class CLASS_DECL_CA2_CUBE XfplayerView :
   virtual public mplite::view,
   virtual public window_frame::WorkSetListener,
   virtual public gen::TimerCallback,
   virtual public window_frame::UpDownTarget
{
public:
   enum ETimer
   {
      TimerMain,
   };
   enum ETimeOut
   {
      TimeOutResolution = 20,
      TimeOutCenti = 100,
      TimeOutKilo = 1000,
   };

   enum e_message
   {
      ID_PLAY = WM_USER + 1011,
   };


   ::ca::graphics_sp m_spgraphics;

   LONG                             m_cnt;    
   CVmsTextDoc *                     m_pvmstextdocHelper;



   bool                             m_bCompactMode;
   bool                             m_bFullScreen;
   bool                              m_bDestroy;
   
   DWORD                            m_dwLastTimer1;
   double                           m_dScoreRate;
   double                           m_dProgressRate;
   bool                              m_bOnSizeEnabled;
   bool                             m_bInitialized;
   ::ca::font_sp                    m_font;

   DoubleScalar                     m_dscalarVelocity;
   DoubleScalar                     m_dscalarPosition;

   bool                              m_bHoverTimer;
   DWORD                              m_dwHoverTimer;
    
    
   rect                            m_rcLastBkImage;
   DWORD                            m_dwLastTime1;

   bool                                 m_bTitleVisible;
   size                                m_sizeBitmapScaled;
   PlaylistFrame *                     m_pplaylistframe;
   //CPlaylistInPlaceWnd *             m_pplaylistipwnd;
   PlaylistDoc *                       m_pplaylistdoc;
   UINT                                m_uiPlaylistID;
   CEvent                              m_evImageLoad;

   bool                                 m_bSettingNextSong;
   bool                                m_bWaitingToPlay;
   int                                 m_msPlayTimeOut;


   DWORD                                 m_dwTimerProcLastTime;
   DWORD                                 m_dwVMSTimerLastTime;
   DWORD                                 m_dwCentiTimerLastTime;
   DWORD                                 m_dwKiloTimerLastTime;

   HENHMETAFILE                        m_enhmetafile;
   ENHMETAHEADER                       m_emh;

   int                                 m_iRightVerticalShift;
   critical_section                    m_csGdi2;
   critical_section                    m_csTimer;

   CEvent                              m_evTransitionEffectRunStep;
   
   int                                 count;
   double                              m_dTextOffsetRate;
   DWORD                                 m_dwBackgroundLastUpdateTime;
   DWORD                                 m_dwBackgroundPreTransitionStartTime;
   bool                                m_bLastLoadImageSynch;

   DWORD                                 m_dwSliderLastUpdateTime;
   DWORD                                 m_dwTimeLastUpdateTime;
   
   DWORD                                 m_dwScoreLastUpdateTime;
   DWORD                               m_dwAdvancingTime;
   UINT                                 m_uiTimer;

//   CLyricViewLineTemplates             m_lyrictemplatelines;
    
   XfplayerViewLines                  m_extraLines;
   XfplayerViewLines                  m_titleLines;
   XfplayerViewLines                   m_lineSongLabel;
   DWORD                               m_dwLastShiftUpdate;

   bool m_bOnDraw;
   ::ca::pen_sp                                 m_penLeft;
   ::ca::pen_sp                                 m_penRight;
   ::ca::pen_sp                                 m_penLeftSmall;
   ::ca::pen_sp                                 m_penRightSmall;
   ::ca::pen_sp                                 m_penTitle;
   ::ca::pen_sp                                 m_penSubTitle;
   COLORREF                              m_crLeft;
   COLORREF                              m_crRight;
   COLORREF                              m_crTitle;
   COLORREF                              m_crSubTitle;
   XfplayerViewLine                     m_lineScore;
   ::ca::pen_sp                                 m_penScore;
   ::ca::rgn_sp                                m_rgnChildren;
   DWORD                               m_dwFileOverrideKaraokeCodePage;
   bool                                m_bFileOverrideKaraokeCodePage;
   bool                                m_bOverrideKaraokeCodePage;
     XfplayerScoring *                   m_pscoring;
   bool                                m_bScoring;

   userbase::single_document_template *            m_ptemplateTab;
  
   XfplayerView(::ca::application * papp);
   afx_msg void OnScoringEnable();
   XfplayerScoring *                   GetScoring();

//   ::mus::midi::sequence & GetMidiSequence();
   //thread * GetMidiPlayerCallbackThread();
   ::view *           GetPlaylistView();
   XfplayerDoc *    get_document();
//   LyricViewLines & GetLyricLines();
   KaraokeSDIFrame * GetKaraokeSDIFrame();
   XfplayerFrameWndInterface * GetParentFrameInterface();
   string GetPlainTextV001();
   int GetChildrenClip();


   void tabfy(const char * pszTitle, window_frame::CWorkSetDownUpInterface * pupdown);

   double GetScoreRate();

    

   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   DECL_GEN_VSIGNAL(_001OnInitialUpdate);
   virtual void pre_translate_message(gen::signal_object * pobj);
   virtual BOOL DestroyWindow();
   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
   protected:
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   //}}AFX_VIRTUAL
    

// Implementation
protected:
   void TransitionEffectRunStepAsync();
    
public:
//   void OnMmsgDone(::mus::midi::player::NotifyEvent * pdata);
   
   virtual void WFLOnClose(
      window_frame::WorkSet * pwf,
      ::user::interaction * pwnd);
   
   VMSRESULT RenderView(
        ::ca::graphics * pdc,
        LPRECT lprect,
        ::ca::rgn * lprgn);
   
   VMSRESULT RenderView(
        ::ca::graphics * pdc);
   
   VMSRESULT to(::ca::graphics * pdc, ::ca::rgn * prgn);
   VMSRESULT to(::ca::graphics * pdc, LPRECT lprect);
    
   void UpdateDrawingObjects();
   
   void OnProgressRateChange();
   void PrepareProgressSlider();
   VMSRESULT SetBkImageFlags(int iFlags);
   void OnDisplayChange(int iBitsPerPixel, size sizeScreen);
   
   bool OnDetachPlaylistDoc();
   bool OnAttachPlaylistDoc();
   ::view * DetachPlaylistView();
   bool AttachPlaylistView();
    


   void PrepareSongLabelLine();
   virtual void TimerProc(UINT nID);

   void PostPlayMessage();
   void SetOnSizeEnabled(bool bEnabled = true);
   void UpdateSubTitleFonts(const char * lpStr);
   void UpdateTitleFonts(const char * lpStr);
   void ShowTitle(bool bShow = true, bool bRedraw = true);
   void RedrawTitle();
   void PrepareTitle();

   void RedrawScore(bool bBackRedraw);

   void RenderScore(::ca::graphics * pdc, bool bClearBackground);

   void XFUpdateFonts(string2a * p2DTokens);
   HRESULT RestoreAllSurfaces();
   void ClearLyricLines(bool bRender);
   

   void UpdateReserveList();
   
   void Reset();
   void UpdateTime();


   virtual ~XfplayerView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

protected:

// Generated message ::collection::map functions
public:
   virtual bool OnOpenMidiPlayer();
   void OnImageDirectoryChange();
//   virtual void OnEvent(_vmsdb::EDBEvent event);

   
   //virtual void OnMmsgDone(::mus::midi::sequence *pSeq, LPMIDIDONEDATA lpmdd);
   virtual void OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata);

   // _vmsgcom::_backView
   /*::ca::window & BackViewGetWnd();
   gcom::backview::Interface & GetBackViewInterface();
   virtual void BackViewGetData(gcom::backview::CInterfaceData & data);
   virtual void BackViewSetData(gcom::backview::CInterfaceData & data);
   void BackViewUpdateScreen(LPCRECT lpcrect);
   void BackViewUpdateScreen();
   bool BackViewIsFullScreen();
   bool BackViewChangeBackgroundImage(bool bRedraw);
   bool BackViewRenderBuffer();
   bool BackViewGetDestroy();*/

   
   // CTransparentWndInterface
   virtual bool TwiHasTranslucency();
   void _001OnDraw(::ca::graphics *pdc);
   void _001OnTopDraw(::ca::graphics * pdcScreen);
   virtual void OnTwiInitialize();

   mutex m_mutexOnDraw;

   // layout
   void DefaultLayoutPlaylist();
   void layout();
   void LayoutDynamicChild(bool bMakeVisible = false);

   
   void OnUpdateProgress(::userbase::view * pview);
   void OnUpdateProgress(double dRate, ::userbase::view * pview);
   void ExecuteSetProgressRate(double dRate, ::userbase::view * pview);
   double GetProgressRate();
   void OnProgressRateChange(double dRate);
   bool SetProgressRate(double dRate);
   virtual void OnMainTimer();
   virtual void OnKiloTimer();
   virtual void OnCentiTimer();
   void OnImageDirectoriesChange();
   
   

   // Wait Play
   void SetWaitingToPlay(bool bWaitingToPlay);
   DWORD GetPlayTimeOut();

   bool  DBListenMinusOne(bool bSave, const char * lpcsz, bool & bMinusOne);
   int   GetListenMinusOneCheck();
   
   
   
   bool Initialize(midi_central * pmidicentral);
   virtual void WFLOnDock(window_frame::WorkSet * pwf, ::user::interaction * pwnd);
   
   
   
   bool IsCompactMode();
   //void OnPointerClear(PlaylistDoc * pdoc);
   bool TextDocHelperAdd(string &str);
   //bool ShowBouncingBall(bool bShow);
   
   bool ShowAudioSpectrum(bool bShow);
   //bool ShowLevelMeter(bool bShow);
   //bool ShowPlayerControlSetV19(bool bShow);
   
   
   void PrepareBouncingBall();
   
   bool CreateBitmap(::ca::graphics * pdc, ::ca::bitmap * pbitmapOld, ::ca::bitmap * pbitmap, BITMAP * pbmp, int cx, int cy);
   

   bool SetFullScreen(bool bFullScreen);
   bool SetCompactMode(bool bCompact);
   
   bool IsPlaylistViewAttached();
   bool GetProgressRate(double & dRate);

   // Drawing Functions

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);

   virtual void TimerMachine(ETimer etimer);
protected:
   void SynchronizeLyrics(double dRate);
   void SynchronizeLyrics(imedia::position tkPosition);

protected:
   void OnChangeFullScreen(XfplayerViewUpdateHint *puh);
   virtual void OnChangeCompactMode(XfplayerViewUpdateHint * puh);

   // Scoring
   bool IsScoringEnabled();
   VMSRESULT StartScoring(bool bStart);
   VMSRESULT EnableScoring(bool bEnable);
    void OnScoringEnable(bool bEnable);
   void OnUpdateScoringEnable(cmd_ui * pcmdui);



   //{{AFX_MSG(XfplayerView)
   DECL_GEN_SIGNAL(_001OnSize)
   afx_msg void OnStop();
   afx_msg void OnPause();
   DECL_GEN_SIGNAL(_001OnTimer);   
   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnContextMenu)
   afx_msg void OnPlaypause();
   afx_msg void OnUpdatePlaypause(cmd_ui * pcmdui);
   afx_msg BOOL OnEraseBkgnd(::ca::graphics * pgraphics);
   afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, point pt);
   afx_msg void OnViewImageTile();
   afx_msg void OnViewImageZoomall();
   afx_msg void OnViewImageStretch();
   afx_msg void OnViewImageZoomextend();
    afx_msg void OnUpdateViewImageTile(cmd_ui * pcmdui);
   afx_msg void OnUpdateViewImageZoomall(cmd_ui * pcmdui);
   afx_msg void OnUpdateViewImageZoomextend(cmd_ui * pcmdui);
   afx_msg void OnUpdateViewImageStretch(cmd_ui * pcmdui);
   afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg void OnViewPlaylist();
   afx_msg void OnViewLyricviewSpectrum();
   afx_msg void OnViewSongInfo();
   afx_msg void OnUpdateViewSongInfo(cmd_ui * pcmdui);
   afx_msg void OnUpdateViewLyricviewSpectrum(cmd_ui * pcmdui);
   afx_msg void OnViewNextImageNow();
   afx_msg void OnViewSkipImageAlways();
   afx_msg void OnParentNotify(UINT message, LPARAM lParam);
//   afx_msg void OnViewBouncingball();
//   afx_msg void OnUpdateViewBouncingball(cmd_ui * pcmdui);
//   afx_msg void OnViewGradualfilling();
//   afx_msg void OnUpdateViewGradualfilling(cmd_ui * pcmdui);
   afx_msg void OnRefresh();
   afx_msg void OnSetFocus(::ca::window* pOldWnd);
   afx_msg void OnViewBounceBall1();
   afx_msg void OnViewBounceBall2();
   afx_msg void OnXfplayerMenubar();
   //afx_msg void OnWindowLevelmeter();
   //afx_msg void OnViewLevelmeter();
   DECL_GEN_SIGNAL(_001OnViewAudioSpectrum)
   afx_msg void OnWindowAudiospectrum();
   //afx_msg void OnUpdateWindowLevelmeter(cmd_ui * pcmdui);
   afx_msg void OnUpdateWindowAudiospectrum(cmd_ui * pcmdui);
   //afx_msg void OnUpdateViewLevelmeter(cmd_ui * pcmdui);
   DECL_GEN_SIGNAL(_001OnUpdateViewAudioSpectrum)
   //afx_msg void OnViewPlayercontrolsetv19();
   //afx_msg void OnUpdateViewPlayercontrolsetv19(cmd_ui * pcmdui);
   //afx_msg void OnWindowPlayercontrolsetv19();
   //afx_msg void OnUpdateWindowPlayercontrolsetv19(cmd_ui * pcmdui);
   afx_msg void OnUpdateExecutePlay(cmd_ui * pcmdui);
   afx_msg void OnUpdateExecutePause(cmd_ui * pcmdui);
   afx_msg void OnUpdateExecuteStop(cmd_ui * pcmdui);
   afx_msg void OnOpenLink();
//   afx_msg void OnListenMinusOne();
//   afx_msg void OnUpdateListenMinusOne(cmd_ui * pcmdui);
//   afx_msg void OnExecuteTempoMinus();
//   afx_msg void OnUpdateExecuteTempoMinus(cmd_ui * pcmdui);
//   afx_msg void OnExecuteTempoPlus();
//   afx_msg void OnUpdateExecuteTempoPlus(cmd_ui * pcmdui);
//   afx_msg void OnExecuteTempoReset();
//   afx_msg void OnUpdateExecuteTempoReset(cmd_ui * pcmdui);
//   afx_msg void OnExecuteTransposeMinus();
//   afx_msg void OnUpdateExecuteTransposeMinus(cmd_ui * pcmdui);
   //afx_msg void OnExecuteTransposeMinusTone();
   //afx_msg void OnUpdateExecuteTransposeMinusTone(cmd_ui * pcmdui);
   //afx_msg void OnExecuteTransposePlus();
   //afx_msg void OnUpdateExecuteTransposePlus(cmd_ui * pcmdui);
   //afx_msg void OnExecuteTransposePlusTone();
   //afx_msg void OnUpdateExecuteTransposePlusTone(cmd_ui * pcmdui);
   //afx_msg void OnExecuteTransposeReset();
   //afx_msg void OnUpdateExecuteTransposeReset(cmd_ui * pcmdui);
   //}}AFX_MSG
   afx_msg LRESULT OnVMSNotify(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnEconoModeChange(WPARAM wParam, LPARAM lParam);
//   afx_msg void OnKeyDownEdit( _vmsgui::NMHDR * pNotifyStruct, LRESULT * result );
  // afx_msg void OnSysKeyDownEdit( _vmsgui::NMHDR * pNotifyStruct, LRESULT * result );
   afx_msg LRESULT OnUserMessage(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnAppMessage(WPARAM wParam, LPARAM lParam);
   //afx_msg LRESULT OnXFPlayerViewMessage(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnVMSTimer(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnAppNotify(WPARAM wParam, LPARAM lParam);
   afx_msg LRESULT OnAppLanguage(WPARAM wParam, LPARAM lParam);
   DECL_GEN_SIGNAL(_001OnMmsgDone)

   virtual void Attach(window_frame::CWorkSetDownUpInterface * pupdown);
   virtual void Detach(window_frame::CWorkSetDownUpInterface * pupdown);

   virtual void on_delete(::ca::ca * pca);
};

#ifndef _DEBUG  // debug version in xfplayer4View.cpp
inline XfplayerDoc* XfplayerView::get_document()
   { return dynamic_cast < XfplayerDoc * > (::view::get_document()); }
#endif

