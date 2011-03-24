#if !defined(AFX_MPLIGHTVIEW_H__15CAB85D_D5F4_4447_AB34_9BCBB3D3B907__INCLUDED_)
#define AFX_MPLIGHTVIEW_H__15CAB85D_D5F4_4447_AB34_9BCBB3D3B907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MPLightView.h : header file
//

#include "AudioSpectrumVirtualView.h"

#include "guibase/ElasticSlider.h"
#include "guibase/StepSlider.h"


class PaneView;
class MusicalPlayerLightDoc;
class CVirtualBaseCtrlInterface;
/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightView view

class CLASS_DECL_MPLITE MusicalPlayerLightView :
   public mediaplay::MediaView,
   public VmsDataClientInterface,
   public Ex1TabCallback,
   public audWaveInListener,
   public DoubleScalar,
   public IntScalar
{
public:
	MusicalPlayerLightView(bergedge_application * papp);
	// DECLARE_DYNCREATE(MusicalPlayerLightView)

// Attributes
protected:
   MusicalPlayerLightPlaylistCallback * m_pplaylistcallback;


   ElasticSlider              m_elasticslider;
   StepSlider                 m_sliderKeyShift;
   AudioSpectrumVirtualView   m_audiospectrum;
   gdi::_w001Gdi           m_gdi;
   PIXELFORMATDESCRIPTOR m_pixelformatdescriptor;				// pfd Tells Windows How We Want Things To Be
   HGLRC		      m_hglrc;		// Permanent Rendering Context
   bool           m_bWaitingToPlay;
   bool           m_bDestroy;
   DWORD          m_dwFileOverrideKaraokeCodePage;
   bool           m_bFileOverrideKaraokeCodePage;
   bool           m_bOverrideKaraokeCodePage;
//   CBitmap        m_bmpBuffer;
//   CBitmap *      m_pbmpBufferOld;
//   CDC            m_dcBuffer;
   DWORD          m_dw100Timer;
   CSimpleWndRender                    m_wndrender;
   WString          m_wstrCurrentLink;
   int            m_iDelay;
public:
   BaseVirtualTab            m_tab;
   MusicalPlayerLightDoc* GetDocument(); // non-debug version is inline

// Operations
public:
   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);

	void SetCurrentBackgroundImagePath(string & wstr);
	string GetNextBackgroundImagePath();
   virtual void WaveInDataProc(audWaveIn * pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr);
	virtual void OnMediaPlaybackEnd();
	virtual bool OnExecuteBeforePlay();
	virtual void OnMediaPlaybackStart();
	PaneView * GetParentPane();
	Ex1VirtualGuieContainer * Create(int i);
	int KaraokeGetLyricsDelay();
	virtual HCURSOR KaraokeGetHandCursor();
	virtual void OnLinkClick(WString & wstr);
	virtual WndRenderInterface * KaraokeGetWndRender();

	void SetKaraokeCodePage(DWORD dw, bool bOverride);
	DWORD CommandToCodePage(UINT ui);
	virtual DWORD KaraokeGetOverridingCodePage(LPCSTR lpsz);
	virtual bool KaraokeDoesOverrideCodePage();


   gdi::Gdi * GetGdi();

   virtual void _001OnTabClick(int iTab);

	int InitGL();
// Overrides
   DECL_GEN_SIGNAL(VmsDataOnAfterChange);
   //virtual VMSRESULT UpdateScreen(CBaseRectArray & recta);
   virtual base_wnd * KaraokeGetWnd();
   virtual PlaylistCallbackInterface * GetPlaylistCallback();

   virtual CWinThread * GetMidiPlayerCallbackThread();
   virtual MidiSequence & GetMidiSequence();
   virtual void OnMidiPlayerNotifyEvent(midi::player::NotifyEvent * pdata);;
   virtual void OnMidiLyricEvent(BaseArray<LyricEventV1, LyricEventV1&> * pevents);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MusicalPlayerLightView)
	protected:
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
   virtual void OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/);
   virtual void OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/);
   DECL_GEN_SIGNAL(_001OnInitialUpdate)
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint);
	//}}AFX_VIRTUAL

// Implementation

protected:
	virtual ~MusicalPlayerLightView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//virtual void _001OnDraw(CDC * pdc);
	//{{AFX_MSG(MusicalPlayerLightView)
   DECL_GEN_SIGNAL(_001OnCancelEditSrvr)
   DECL_GEN_SIGNAL(_001OnExecutePlay)
   DECL_GEN_SIGNAL(_001OnUpdateExecutePlay)
	DECL_GEN_SIGNAL(_001OnDestroy)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnPaint)
	DECL_GEN_SIGNAL(_001OnKaraokeBouncingBall)
	DECL_GEN_SIGNAL(_001OnUpdateKaraokeBouncingBall)
	DECL_GEN_SIGNAL(_001OnKaraokeGradualFilling)
	DECL_GEN_SIGNAL(_001OnUpdateKaraokeGradualFilling)
	DECL_GEN_SIGNAL(_001OnExecuteStop)
	DECL_GEN_SIGNAL(_001OnUpdateExecuteStop)
	DECL_GEN_SIGNAL(_001OnExecutePause)
	DECL_GEN_SIGNAL(_001OnUpdateExecutePause)
	DECL_GEN_SIGNAL(_001OnExecuteMinusOne)
	DECL_GEN_SIGNAL(_001OnUpdateExecuteMinusOne)
	DECL_GEN_SIGNAL(_001OnCreate)
	DECL_GEN_SIGNAL(_001OnContextMenu)
	DECL_GEN_SIGNAL(_001OnOpenLinkInNewWindow)
	DECL_GEN_SIGNAL(_001OnSetCursor)
	DECL_GEN_SIGNAL(_001OnCopyLinkLocation)
	DECL_GEN_SIGNAL(_001OnPlaylistExecutePlay)
	DECL_GEN_SIGNAL(_001OnUpdatePlaylistExecutePlay)
	DECL_GEN_SIGNAL(_001OnExecutePrevious)
	DECL_GEN_SIGNAL(_001OnUpdateExecutePrevious)
	DECL_GEN_SIGNAL(_001OnExecuteNext)
	DECL_GEN_SIGNAL(_001OnUpdateExecuteNext)
   DECL_GEN_SIGNAL(_001OnExecuteAutoRecord)
   DECL_GEN_SIGNAL(_001OnUpdateExecuteAutoRecord)
	//}}AFX_MSG
	DECL_GEN_SIGNAL(_001OnUpdateViewEncoding)
   DECL_GEN_SIGNAL(_001OnViewEncoding)
	DECLARE_MESSAGE_MAP()

   int m_iTempo;
   int m_iPos;
   int m_iKeyShift;
   virtual void OnSetScalar(int i, double d);
   virtual double GetMinScalar(int i);
   virtual double GetScalar(int i);
   virtual double GetMaxScalar(int i);
   virtual void OnSetScalar(int i, int iValue);
   virtual void GetMinScalar(int i, int & iValue);
   virtual void GetScalar(int i, int & iValue);
   virtual void GetMaxScalar(int i, int & iValue);
};

#ifndef _DEBUG
inline MusicalPlayerLightDoc* MusicalPlayerLightView::GetDocument() // non-debug version is inline
{
	return (MusicalPlayerLightDoc*)m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MPLIGHTVIEW_H__15CAB85D_D5F4_4447_AB34_9BCBB3D3B907__INCLUDED_)
