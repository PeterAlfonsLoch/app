#pragma once

class visual::font;
class ::mus::midi::sequence;

class CLASS_DECL_CA2_CUBE AudioSpectrumView :
   public ::userbase::view,
   public audWaveInListener,
   public gen::TimerCallback
{
public:
   void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   bool         m_bEnable;
   bool         m_bUsePlgBlt;
   //int            m_iLeft;
   //int            m_iTop;
   //int            m_iRight;
   //int            m_iBottom;
   primitive_array < ::ca::pen *> m_pens;
   ::ca::bitmap_sp         m_bmpTemplate;
   ::ca::bitmap_sp         m_bmpBuffer;
   ::ca::bitmap_sp         m_bmpMask;
   visual::font *   m_pFont;
   ::ca::pen_sp         m_pen;
    //bool            m_bVisible;
    ::ca::graphics *           m_pdc;
    ::ca::graphics *           m_pdcBack;
   LPWAVEFORMATEX   m_lpwaveformatex;
   double         m_dDeltaScore;
   double         m_dScoreAddUp;
   ::ca::graphics_sp            m_dcBack;
   ::ca::bitmap_sp         m_bmpBack;

//   LPVOID      m_lpBitmap;
public:
   virtual void TimerProc(UINT uiIDEvent);
   virtual void OnTimerProc(UINT nIDEvent);
   bool Enable(bool bEnable = true);
   void _001OnDraw(::ca::graphics * pdc);
   void Update(LPWAVEFORMATEX lpwaveformatex, double dDeltaScore, double dScoreAddUp);
   VMSRESULT SetDC(::ca::graphics * pdc, ::ca::graphics * pdcBack);
   VMSRESULT EraseBackground(::ca::graphics * pdc);
   //void SetVisible(bool bVisible = true);
   //bool GetVisible();
   int GetBottom();
//   void GetPlacement(LPRECT lpRect);
   void SetPlacement(
      ::ca::graphics * pgraphics,
      int iLeft,
      int iTop,
      int iRight,
      int iBottom);
//   int height();
//   int width();
   void to(
      ::ca::graphics * pdc);
//      LPWAVEFORMATEX pWaveFormatEx,
//      double dDeltaScore,
//      double dScoreAddUp);
   AudioSpectrumView(::ca::application * papp);
   virtual ~AudioSpectrumView();
   audWaveBuffer * m_pWaveBuffer;
   ::mus::midi::sequence * m_bEnabled;

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AudioSpectrumView)
   protected:
   virtual void PostNcDestroy();
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   virtual void OnDraw(::ca::graphics * pgraphics);

   virtual void WaveInDataProc(audWaveIn *pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr);

   //}}AFX_VIRTUAL

   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnSize)
   DECL_GEN_SIGNAL(_001OnTimer)
   DECL_GEN_SIGNAL(_001OnDestroy)
   afx_msg void OnContextMenu(::ca::window* pWnd, point point);
   DECL_GEN_SIGNAL(_001OnUserMessage)
};

