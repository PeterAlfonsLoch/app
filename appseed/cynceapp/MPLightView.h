#if !defined(AFX_MPLIGHTVIEW_H__15CAB85D_D5F4_4447_AB34_9BCBB3D3B907__INCLUDED_)
#define AFX_MPLIGHTVIEW_H__15CAB85D_D5F4_4447_AB34_9BCBB3D3B907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MPLightView.h : header file
//

#include "AudioSpectrumVirtualView.h"

#include "MediaView.h"


class PaneView;
class MusicalPlayerLightDoc;
class CVirtualBaseCtrlInterface;
/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightView view

class MusicalPlayerLightView :
   public mediaplay::MediaView,
   public VmsDataClientInterface,
   public Ex1TabCallback,
   public aud::WaveInListener
{
protected:
	MusicalPlayerLightView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(MusicalPlayerLightView)

// Attributes
protected:
   MusicalPlayerLightPlaylistCallback * m_pplaylistcallback;


   AudioSpectrumVirtualView   m_audiospectrum;
   gdi::_w001Gdi           m_gdi;
   ::igui::Buffer            m_gdibuffer;
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

	void SetCurrentBackgroundImagePath(CString & wstr);
	CString GetNextBackgroundImagePath();
   virtual void WaveInDataProc(aud::WaveIn * pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr);
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
   virtual void VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh);
   //virtual VMSRESULT UpdateScreen(CBaseRectArray & recta);
   virtual CWnd * KaraokeGetWnd();
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
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, CObject* pHint);
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
