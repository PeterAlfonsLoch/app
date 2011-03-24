#pragma once

namespace audio
{
   class WaveBuffer;
}

class CLASS_DECL_CA2_CUBE AudioSpectrumVirtualView :
   public ::user::interaction,
   public audWaveInListener,
   public gen::TimerCallback
{
public:
   virtual void VirtualOnSize();
   virtual bool _001OnCreate();
   void layout();
   virtual void _001OnDraw(::ca::graphics * pdc);
   AudioSpectrumVirtualView(::ca::application * papp);
   virtual ~AudioSpectrumVirtualView();

   void Update(
      LPWAVEFORMATEX lpwaveformatex,
      double dDeltaScore,
      double dScoreAddUp);

   virtual void TimerProc(UINT uiIDEvent);

   LPWAVEFORMATEX m_lpwaveformatex;
   double m_dDeltaScore;
   double m_dScoreAddUp;

   ::ca::bitmap_sp      m_bmpTemplate;
   ::ca::bitmap_sp      m_bmpBuffer;
   ::ca::bitmap_sp      m_bmpMask;

   ::ca::graphics_sp    m_dcBack;
     ::ca::bitmap_sp      m_bmpBack;


   audWaveBuffer * m_pWaveBuffer;
   primitive_array < ::ca::pen *> m_pens;
   ::ca::pen_sp         m_pen;
   ::ca::font_sp        m_font;


   void InstallMessageHandling(::user::win::message::dispatch *pinterface);


   bool    m_bUsePlgBlt;

};
