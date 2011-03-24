// AudioSpectrumVirtualView.h: interface for the AudioSpectrumVirtualView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUDIOSPECTRUMVIRTUALVIEW_H__E18A6CAA_541F_4240_BC18_12120C4D7A68__INCLUDED_)
#define AFX_AUDIOSPECTRUMVIRTUALVIEW_H__E18A6CAA_541F_4240_BC18_12120C4D7A68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gen/TimerCallback.h"

namespace audio
{
	class WaveBuffer;
}

//class CVmsGdiFont;

class AudioSpectrumVirtualView :
   public BaseVirtualGuie,
   public aud::WaveInListener,
	public gen::TimerCallback
{
public:
	virtual void VirtualOnSize();
	virtual bool _001OnCreate();
	void Layout(LPCRECT lpcrect);
	virtual void _001OnDraw(CDC * pdc);
	AudioSpectrumVirtualView();
	virtual ~AudioSpectrumVirtualView();

   void Update(
	   LPWAVEFORMATEX lpwaveformatex,
	   double dDeltaScore,
	   double dScoreAddUp);

   virtual void TimerProc(UINT uiIDEvent);

   LPWAVEFORMATEX m_lpwaveformatex;
	double m_dDeltaScore;
	double m_dScoreAddUp;

	CBitmap			m_bmpTemplate;
	CBitmap			m_bmpBuffer;
	CBitmap			m_bmpMask;

   CDC            m_dcBack;
  	CBitmap			m_bmpBack;


   aud::WaveBuffer * m_pWaveBuffer;
	CTypedPtrArray <CPtrArray, CPen *> m_pens;
   CPen           m_pen;
   gdi::Font *	   m_pFont;


   void InstallMessageHandling(igui::win::message::Dispatch *pinterface);


   bool    m_bUsePlgBlt;

};

#endif // !defined(AFX_AUDIOSPECTRUMVIRTUALVIEW_H__E18A6CAA_541F_4240_BC18_12120C4D7A68__INCLUDED_)
