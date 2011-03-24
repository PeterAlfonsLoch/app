#pragma once

class audWavePlayer;

namespace mediaplay
{

   class record_notify_view;

   enum EExecute
   {
      ExecuteNone,
      ExecuteNext,
      ExecutePrevious,
      ExecuteStop,
   };

   class document;
   class data;

   class CLASS_DECL_ca view_interface :
      virtual public kar::KaraokeView,
      virtual public MidiPlayerInterface,
      virtual public audio::WavePlayerInterface,
      virtual public audio::WaveRecorderInterface,
      virtual public gcom::backview::user::interaction,
      virtual public PlaylistCallbackContainerInterface,
      virtual public DoubleScalar,
      virtual public IntScalar
   {
   public:

      enum ETimer
      {
         TimerLyric,
         TimerBackView,
         TimerSongInfo,
         TimerFadeOut,
         TimerFadeIn,
      };

      bool                             m_bPassthroughBackground;
      ::ca::graphics_sp                m_spgraphics;
      midi_central *                   m_pmidicentral;
      ::mediaplay::record_notify_view *          m_precordnotifyview;
      id                               m_idPopup;
      id                               m_idPopupLink;
      rect                             m_rectKaraokeView;
      ex1::filesp                      m_fileRecord;
      document *                       m_pdocument;
      XfplayerViewLines                m_viewlineaStatus;
      ::ca::graphics_sp                m_gdi;
      //::user::buffer                  m_gdibuffer;
      // pfd Tells Windows How We Want Things To Be
      PIXELFORMATDESCRIPTOR            m_pixelformatdescriptor;            
      HGLRC                              m_hglrc;      // Permanent Rendering Context
      bool                             m_bWaitingToPlay;
      DWORD                            m_dwPlayWait;
      bool                             m_bDestroy;
      DWORD                            m_dw100Timer;
      string                           m_strCurrentLink;
      rect_array                  m_rectaUpdate;
      DWORD                            m_dwLastUpdate;
      double                           m_dBlend;
      DWORD                            m_dwLastFade;
      EExecute                         m_eexecuteAfterFadeOut;
      bool                             m_bAutoRecord;




      PlaylistCallbackInterface *      m_pplaylistcallback;


      int                              m_iScalarTempo;
      int                              m_iScalarPos;
      int                              m_iScalarKeyShift;

      int                              m_iDelay;



      view_interface(::ca::application * papp);
      virtual ~view_interface();


      bool Initialize(midi_central * pmidicentral);
      bool Finalize();


      data * get_data(); 

      virtual bool is_ok_for_rendering();

      virtual void OnFadeOutEnd();
      void StartFadeOut(EExecute eexecuteNow, EExecute eexecuteAfter);
      void StartFadeIn();
      virtual void BackViewFeedback(::ca::graphics *pdc);
      DECL_GEN_SIGNAL(_001OnTimer)
      void CloseDevice();
      virtual void OnMediaPlaybackStart();
      virtual void OnMediaPlaybackEnd();
      virtual bool OnExecuteBeforePlay();
      
      bool DBListenMinusOne(bool bSave, const char * lpcszPathName, bool &bMinusOne);


      DECL_GEN_SIGNAL(_001OnMessageX)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnCreate)

      virtual void _001OnDraw(::ca::graphics * pdc);
      virtual void _001OnTopDraw(::ca::graphics * pdc);

      void KaraokeBouncingBall();
      void KaraokeGradualFilling();
      void CopyLinkLocation();
      virtual HCURSOR KaraokeGetHandCursor();

      void SetKaraokeCodePage(DWORD dw);
      DWORD IdToCodePage(const char * pszCommandId);
      DWORD GetKaraokeCodePage(const char * lpsz);


      ::ca::graphics * GetGdi();
      int InitGL();
      virtual bool BackViewGetDestroy();
      void StartMusicRendering();
   // Overrides
   //   virtual void data_on_after_change(int iConfigurationId, int iLine, int iColumn, CVmsDataUpdateHint * puh);
      virtual VMSRESULT UpdateScreen(rect_array & recta, UINT uiRedraw);
      virtual PlaylistCallbackInterface * GetPlaylistCallback();

      virtual void on_delete_contents();

      virtual ::radix::thread * GetMidiPlayerCallbackThread();
      virtual ::mus::midi::sequence & GetMidiSequence();
      virtual void OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata);;
      virtual void OnMidiLyricEvent(base_array<LyricEventV1, LyricEventV1&> * pevents);

   // Implementation

      void _ToggleAutoRecord();
      void _AutoRecord(bool bRecord = true);
      void _StartRecording();
      void _StopRecording();

      void _Execute(EExecute eexecute);
      void _ExecutePlay(bool bMakeVisible, const imedia::position & position);
      void _ExecuteStop();
      void _ExecutePause();
      bool _ExecuteGetPlayEnable();
      bool _ExecuteIsWaitingToPlay();
      bool _ExecuteIsPaused();
      bool _ExecuteGetPauseEnable();
      virtual bool _ExecuteGetStopEnable();
      void _ExecuteListenMinusOne(bool bMinusOne);
      void _ExecuteToggleListenMinusOne();
      bool _ExecuteGetListenMinusOneEnable();
      bool _ExecuteIsPlaying();
      bool GetListenMinusOneCheck();
   public:
      bool _ExecuteIsEntertaining();


      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);

      static UINT AFX_CDECL ThreadProcLyricEvent(LPVOID lpParam);

      virtual void OnSetScalar(int i, double d);
      virtual double GetMinScalar(int i);
      virtual double GetScalar(int i);
      virtual double GetMaxScalar(int i);
      virtual void OnSetScalar(int i, int iValue);
      virtual void GetMinScalar(int i, int & iValue);
      virtual void GetScalar(int i, int & iValue);
      virtual void GetMaxScalar(int i, int & iValue);

      virtual int KaraokeGetLyricsDelay();

   };



} // namespace mediaplay

