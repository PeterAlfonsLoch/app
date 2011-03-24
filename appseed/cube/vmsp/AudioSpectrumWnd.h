#pragma once


class visual::font;
class ::mus::midi::sequence;

class AudioSpectrumWnd :
   public ::ca::window
{
protected:
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
    ::ca::graphics *           m_pdc;
    ::ca::graphics *           m_pdcBack;
   LPWAVEFORMATEX   m_lpwaveformatex;
   double         m_dDeltaScore;
   double         m_dScoreAddUp;
   ::ca::graphics_sp            m_dcBack;
   ::ca::bitmap_sp         m_bmpBack;

//   LPVOID      m_lpBitmap;
public:
   bool Enable(bool bEnable = true);
   void TwiOnDraw(::ca::graphics * pdc);
   void Update(LPWAVEFORMATEX lpwaveformatex, double dDeltaScore, double dScoreAddUp);
   VMSRESULT SetDC(::ca::graphics * pdc, ::ca::graphics * pdcBack);
   VMSRESULT EraseBackground(::ca::graphics * pdc);
   void SetVisible(bool bVisible = true);
   bool GetVisible();
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
   AudioSpectrumWnd();
   virtual ~AudioSpectrumWnd();
   audWaveBuffer * m_pWaveBuffer;
   ::mus::midi::sequence * m_bEnabled;

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AudioSpectrumWnd)
   protected:
   virtual void PostNcDestroy();
   //}}AFX_VIRTUAL

   // Generated message ::collection::map functions
protected:
   //{{AFX_MSG(AudioSpectrumWnd)
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnDestroy();
   //}}AFX_MSG
   ()
};

