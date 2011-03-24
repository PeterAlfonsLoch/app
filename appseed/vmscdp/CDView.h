// CDVIEW.h : interface of the CCDView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDVIEW_H__A75120B2_F7F2_4E0D_AF07_32AC0CE5D582__INCLUDED_)
#define AFX_CDVIEW_H__A75120B2_F7F2_4E0D_AF07_32AC0CE5D582__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include <afxmt.h>

#include "Math_.h"
#include "BaseRect.h"
#include "lyriceventv1.h"
#include "AudioSpectrumWnd.h"
#include "WaveBuffer.h"
#include "xfplayerfont.h"
#include "SliderV017.h"
#include "_vmsgcomBackViewInterface.h"

//#include "dummycs.h"
#include "TimerCallback.h"

#include "LyricViewLines.h"
#include "LyricViewLineTemplates.h"
#include "VMSException.h"	// Added by ClassView
#include "../vms/Vms.h"	// Added by ClassView
#include "TransparentFrameWndArray.h"
#include "FastArray.h"



class CSliderV017;

class CKaraokeBouncingBall;

#include "TransparentWndInterface.h"
#include "WndFrameworkListener.h"
#include "DBInterface.h"
#include "PointerListener.h"

class CKaraokeSDIFrame;
class CKaraokeControlSet1Wnd;
class CLevelMeterWnd;
class CAudioSpectrumWnd;
class CImage;
class CPlaylistDoc;
class CPlaylistFrame;
class CPlaylistInPlaceWnd;
class CPlaylistView;
class CLyricViewLine;
class CLyricViewLineTemplate;
class CSliderV008;
class CCDViewUpdateHint;
class CVmsTextDoc;
class CXfplayerThreadV3;
//class CEditV017;
//#include "xfplayerviewthread.h"
//#import "D:\Arquivos\prg\vc\Image\2001-02-23\ImageLoader\ImageLoader.tlb" no_namespace

#define VMSPM_XFVIEW WM_USER + 1026
#define VMSPN_XFVIEW_INIT 1



class CCDView :
    public CView,
    public CTimerCallback,
    public CTransparentWndInterface,
	public CDBInterface,
	public CWndFrameworkListener,
	public _vmsgcom::CBackViewInterface
                   
{
	friend CXfplayerThreadV1;
	friend CXfplayerThreadV3;
    enum ImageFlags
    {
        ifZoomAll = 1,
        ifStretch = 2,
        ifTile = 3,
        ifZoomExtend = 4
    };
	enum ETransitionEffect
	{
		TransitionEffectStart,
		TransitionEffectSquaryPixelate,
		TransitionEffectHexagonalPixelate,
		TransitionEffectCirclyPixelate,
		TransitionEffectEllipsoidalPixelate,
		TransitionEffectLinearFadingTopBottom,
		TransitionEffectLinearFadingBottomTop,
		TransitionEffectLinearFadingLeftRight,
		TransitionEffectLinearFadingRightLeft,
		TransitionEffectAccumulLinearFadingTopBottom,
		TransitionEffectAccumulLinearFadingBottomTop,
		TransitionEffectAccumulLinearFadingLeftRight,
		TransitionEffectAccumulLinearFadingRightLeft,
		TransitionEffectFlyInTopBottom,
		TransitionEffectFlyInBottomTop,
		TransitionEffectFlyInLeftRight,
		TransitionEffectFlyInRightLeft,
		TransitionEffectFlyInLeftBottom,
		TransitionEffectFlyInLeftTop,
		TransitionEffectFlyInRightBottom,
		TransitionEffectFlyInRightTop,
		TransitionEffectWipeTopBottom,
		TransitionEffectWipeBottomTop,
		TransitionEffectWipeLeftRight,
		TransitionEffectWipeRightLeft,
		TransitionEffectWipeTopRight,
		TransitionEffectWipeBottomRight,
		TransitionEffectWipeTopLeft,
		TransitionEffectWipeBottomLeft,
		TransitionEffectWipeCenter,
		TransitionEffectWipeOut,
		TransitionEffectScaleTopBottom,
		TransitionEffectScaleBottomTop,
		TransitionEffectScaleLeftRight,
		TransitionEffectScaleRightLeft,
		TransitionEffectScaleTopRight,
		TransitionEffectScaleBottomRight,
		TransitionEffectScaleTopLeft,
		TransitionEffectScaleBottomLeft,
		TransitionEffectScaleCenter,
		TransitionEffectEnd,
	};
public:

	

	class CTransitionEffect
	{
		friend class CCDView;
	protected:

		class CTool001
		{
		public:
			union DATA
			{
				struct SQUARY_PIXELATE
				{
					double xyz;
				} m_squarypixelate;
				struct HEXAGON_PIXELATE
				{
					double xyz;
				} m_hexagonpixelate;
				struct SLICE_FRAME
				{
					int m_iTileCount;
					int m_iFrameCount;
				} m_sliceframe;
			} m_data;
			enum EAlign
			{
				AlignTop,
				AlignBottom,
				AlignLeft,
				AlignRight,
				AlignLeftTop,
				AlignTopRight,
				AlignBottomLeft,
				AlignRightBottom,
				AlignCenter,
			};
			void Start(int cx, int cy, double dRate, double dRateEx);
//			void Go(ETransitionEffect etransitioneffect);
			void Go();
			void GetRect(EAlign aelign, LPRECT lprect);
			void GetSliceRect(EAlign aelign, LPRECT lprect);
			void GetRect(LPRECT lprect);
			void GetRectAB(LPRECT lprectA, LPRECT lprectB);
			void GetHorizontalHexagon(LPRECT lprect, LPPOINT lppointa);
			int FindRandomEnglobingEllipse(LPCRECT lprect, LPRECT lprectCircle, int iMaxRand);
			int FindRandomEnglobingCircle(LPCRECT lprect, LPRECT lprectCircle, int iMaxRand);
			

		protected:
			CCDView &		m_view;
			ETransitionEffect	m_etransitioneffect;
			CSize				m_size;
			int					m_cx;
			int					m_cy;
			double				m_dRate;
			double				m_dRateEx;
			double				m_phi;
			int					m_iRadius;
		public:
			CFastArray < CPoint, CPoint > m_pointa;
			CFastArray<int, int>	m_iaTransitionEffect;
			void GetRect(LPPOINT lppoint, LPCRECT lpcrect);
			void GetRotateRect(int w, int h, int i, int j, double phi, LPPOINT lppoint);
			void GetRotateRect(int i, int j, LPPOINT lppoint);
			void TranslateRect(LPRECT lprect, int w, int h, int i, int j);
			void GetRotateHexagon(int iRadius, int i, int j, double phi, LPPOINT lppoint);
			void GetRotateHexagon(int i, int j, LPPOINT lppoint);
			int					m_iStep; // 0 - Inactive, >= 1 Active
			int					m_iStepCount; // -1 - Infinite, 0 and 1 - invalid, > 1 count out
			void Initialize(ETransitionEffect eeffect, int cx, int cy);
			static void GetSimplePolyBox(LPRECT lprect, LPPOINT lppoint, int iCount);
			CTool001(CCDView & view);
			CBaseRect			m_rect;
			CPoint				m_point;
			CBaseRect			m_rectIn;
			CBaseRect			m_rectOut;
			CBaseRect			m_rectA;
			CBaseRect			m_rectB;

		};
		DWORD					m_dwTransitionStepLastRunTime;
		DWORD					m_dwTransitionEffectDelay;
		bool					m_bTransitionStepRunActive;
		bool					m_bTransitionStepPostActive;
		DWORD					m_dwTransitionStepPostActive;
	
		DWORD					m_dwLastTransitionTime;


		ETransitionEffect		m_etransitioneffect;

		CBaseArray < ETransitionEffect, ETransitionEffect >
								m_etransitioneffecta;

		CCDView &			m_view;	
		CTool001				m_tool001;
	public:
		void DisableEffect(ETransitionEffect eeffect);
		void EnableEffect(ETransitionEffect eeffect);
		


		CTransitionEffect(CCDView & view);
		void OnTransitionTimer();
		void Reset();
		bool IsInTransition();
		bool TestEnd();
		void UpdateBuffer(CRect & rectUpdate);
		void RunStep();
		
		void Initialize();
	};

	friend class CTransitionEffect;
	friend class CTransitionEffect::CTool001;

	public:
    HENHMETAFILE                        m_enhmetafile;
    ENHMETAHEADER                       m_emh;
	//CKaraokeControlSet1Wnd *			m_pkcs1wndLevelMeter;
	//CLevelMeterWnd *					m_plevelmeterwnd;
	//CKaraokeControlSet1Wnd *			m_pkcs1wndAudioSpectrum;
	//CAudioSpectrumWnd *					m_paudiospectrumwnd;
//	CAudioSpectrumView *    			m_paudiospectrumview;
//	CLevelMeterView *	    			m_plevelmeterview;
//	CTransparentFrameWndV4 *			m_pframeAudioSpectrum;
//	CTransparentFrameWndV4 *			m_pframeLevelMeter;

	static WPARAM USERMESSAGE_WPARAM_UPDATESCREEN_LPCRECT;
	static WPARAM USERMESSAGE_WPARAM_UPDATESCREEN_NEWRECT;
	static WPARAM USERMESSAGE_WPARAM_RAND_LPINT;
private:
// data
    LONG m_cnt;    
public:
    //CCriticalSection					m_csGdi;
    //CMutex                      m_mutexGdi;
    int                                 m_iRightVerticalShift;
    CCriticalSection                    m_csGdi;
	CCriticalSection                    m_csGdi2;
    CCriticalSection                    m_csTimer;
protected:

	CTransitionEffect					m_transitioneffect;

	static UINT AFX_CDECL ThreadProcTransitionEffectRunStep(LPVOID lpParameter);
	void TransitionEffectRunStepAsync();

	CTransparentFrameWndArray			m_transparentframewnda;
    CVmsTextDoc *						m_pvmstextdocHelper;

    bool                                m_bCompactMode;
    bool                                m_bFullScreen;
	bool								m_bDestroy;

	CWinThread *						m_pthreadTransitionEffectRunStep;
	
	bool								m_bPendingFullBufferUpdate;
	DWORD								m_dwLastFullBufferUpdate;

    DWORD                               m_dwLastTimer1;
    double                              m_dScoreRate;
    double                              m_dProgressRate;
	CCriticalSection							m_csBkImageChangeStateMachine;
	bool								m_bOnSizeEnabled;
	//bool								m_bOnSizeUpdateTimerOn;
    bool                                m_bBackgroundUpdateTimerOn;
	DWORD								m_dwBackgroundUpdateTimeIn;	
	static const DWORD					m_dwBackgroundUpdateTimeOut;
    bool                                m_bInitialized;
    CSliderV017                         m_sliderProgress;
    int                                 m_iBkImageFlags;
//    CEditV017 *                         m_pedit;
    CFont                               m_font;
//    bool                   m_bDirectDrawPresenceChecked;
  //  bool                   m_bDirectDrawPresent;
    //bool                   m_bDirectDrawActive;
    CWinThread *    m_pthreadV1;
    CWinThread *    m_pthreadV2;
    CWinThread *    m_pthreadV3;
	
	
	bool							m_bHoverTimer;
	DWORD							m_dwHoverTimer;
    
    CMath m_math;
    
    CRect               m_rcLastBkImage;
    DWORD               m_dwLastTime1;

	
	CWStr   			m_wstrCurrentLink;


//	CCriticalSection					m_csSourceBitmap;
//	CCriticalSection					m_csSourceDC;
//	CCriticalSection					m_csScaledBitmap;
//	CCriticalSection					m_csScaledDC;
//	CCriticalSection					m_csBufferBitmap;
//	CCriticalSection					m_csBufferDC;
//	CCriticalSection					m_csScreenDC;
//	CCriticalSection					m_csLockGroup;
//	CCriticalSection					m_csPens;
protected: // create from serialization only
	CCDView();
	DECLARE_DYNCREATE(CCDView)
    
// Attributes
private:
	//CRect *								m_pRect;
//	CRgn *								m_pRgn;
public:
    
	//CTypedPtrArray <CPtrArray, CVmsGdiFont *> *
      //  GetLyricFonts();

    CVmsGdiFont  *
        GetLyricFont();

    
	CView * GetPlaylistView();


	static void CALLBACK WaveInProc(
		HWAVEIN hwi,       
		UINT uMsg,         
		DWORD dwInstance,  
		DWORD dwParam1,    
		DWORD dwParam2);
    
//	int count;
	enum EImageChangeState
	{
		BkImageStateTiming,
		BkImageStateLoading,
        BkImageStatePreTransition,
        BkImageStateInTransitionEffect,
		BkImageStateFinish,
	} m_bkImageChangeState;
	enum EImageChangeEvent
	{
		BkImageEventTimer,
		BkImageEventLoaded,
        BkImageEventPreTransitionFinished,
        BkImageEventTransitionEffectFinished,
		BkImageEventLoadFailed,
        BkImageEventLoadNow,
		BkImageEventFlagChanged,
		BkImageEventResize,
	};
protected:
	int _ImageChangeSetState(EImageChangeState estate);
	int _ImageChangePulseEvent(EImageChangeEvent eevent);

	void _ImageChangeTransitionEffectRunStep();
	void _ImageChangeTransitionEffectInitialize();

	
public:
	void _ImageChangePostEvent(EImageChangeEvent eevent);
	CEvent								m_evTransitionEffectRunStep;
	CEvent								m_evImageChangeFinish;
	int count;
    double m_dTextOffsetRate;
	DWORD								m_dwBackgroundLastUpdateTime;
	DWORD								m_dwBackgroundPreTransitionStartTime;
	bool m_bLastLoadImageSynch;

	DWORD								m_dwSliderLastUpdateTime;
	DWORD								m_dwTimeLastUpdateTime;
	DWORD								m_dwPlayStartTime;
	DWORD								m_dwScoreLastUpdateTime;
    DWORD                               m_dwAdvancingTime;
	UINT								m_uiTimer;
	//CFont								m_font;
	CBitmap								m_bmpSource;
	CBitmap								m_bmpSourceOld;
	CBitmap								m_bmpBack2;
	CBitmap								m_bmpBack2Old;
	CBitmap								m_bmpBack;
	CBitmap								m_bmpBackOld;
//	CBitmap								m_bmpBuffer;
//	CBitmap								m_bmpBufferOld;
	CDC									m_dcScreen;
	CDC									m_dcSource;
	CDC									m_dcBack2;
	CDC									m_dcBack;
//	CDC									m_dcBuffer;
	//CComPtr<IDirectDrawSurface3>		m_lpDDSPrimary;
	//CComPtr<IDirectDrawSurface3>		m_lpDDSSource;
	//CComPtr<IDirectDrawSurface3>		m_lpDDSScaled;
	//CComPtr<IDirectDrawSurface3>		m_lpDDSBuffer;
	//CDC									m_dcBuffer;
	CXfplayerViewLines	                m_extraLines;
	CXfplayerViewLines	                m_titleLines;
    CCDViewLine                   m_lineSongLabel;
    bool                                m_bBouncingBall;
    bool                                m_bGradualFilling;
    CKaraokeBouncingBall *              m_lpbouncingball;
    DWORD                               m_dwLastShiftUpdate;
	CXfplayerDoc * GetDocument();
//	FIBITMAP *							m_pfiBitmap;
//	void OnDraw(CDC* pDC, CRgn *pRgn)
//	{
//		m_pRgn = pRgn;
//		OnDraw(pDC);
//	}
//	CCriticalSection					m_CriticalSection;
	//HANDLE								m_hThreadChangeBackgroundImage;
	//CCDViewThread					m_Thread;
	CWinThread *						m_pThreadBkImageChange;
	
//	CEvent								m_eventBkImageReady;
//	FIBITMAP *							m_pFreeImage;
    CString                             m_strCurrentImagePath;
	CString                             m_strNextImagePath;
//	CCriticalSection					m_csLyricEvent;
//	CCDViewVoiceSpectrum			m_voiceSpectrum;
//	CWaveBuffer							m_waveBuffer;
	static UINT ThreadProcChangeBackgroundImage(
		LPVOID lpParameter   // thread data
		);
	CPen								m_penLeft;
	CPen								m_penRight;
	CPen								m_penLeftSmall;
	CPen								m_penRightSmall;
	CPen								m_penTitle;
	CPen								m_penSubTitle;
	COLORREF							m_crLeft;
	COLORREF							m_crRight;
	COLORREF							m_crTitle;
	COLORREF							m_crSubTitle;
	CCDViewLine					m_lineScore;
	CPen								m_penScore;
    CRgn                                m_rgnChildren;
protected:
	bool								m_bTitleVisible;
    CSize                               m_sizeBitmapScaled;
    CPlaylistFrame *                    m_pplaylistframe;
    //CPlaylistInPlaceWnd *               m_pplaylistipwnd;
    CPlaylistDoc *                      m_pplaylistdoc;
    UINT                                m_uiPlaylistID;
    CEvent                              m_evImageLoad;
    
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL
    

// Implementation
protected:
    
public:
	virtual void WFLOnClose(
		CWndFrameworkV033 * pwf,
		CWnd * pwnd);
    //CDC * TWCGetBufferDC();
	//VMSRESULT TWCRedraw(LPRECT lprect);
    void TwiOnDraw(CDC *pdc);
//	VMSRESULT RenderTransparent(
  //      CDC * pdc,
    //    CWnd * pwnd,
      //  LPRECT lprect,
        //CRgn * prgn,
        //bool bGdiLocked);//, CDC * pdc);
	VMSRESULT RenderView(
        CDC * pdc,
        LPRECT lprect,
        CRgn * lprgn,
        bool bGdiLocked);
	VMSRESULT RenderView(
        CDC * pdc,
        bool bGdiLocked);
	VMSRESULT Render(CDC * pdc, CRgn * prgn, bool bGdiLocked);
	VMSRESULT Render(CDC * pdc, LPRECT lprect, bool bGdiLocked);
    
	VMSRESULT LoadImageSync();
	VMSRESULT LoadImageSync(LPCTSTR lpszImage);
	VMSRESULT LoadImageAsynch(CString strPath);
  	VMSRESULT LoadImageAsynch();
	void UpdateDrawingObjects();
	CSliderV017 * GetProgressSlider();
	void UpdateProgress();
	void PrepareProgressSlider();
	VMSRESULT SetBkImageFlags(int iFlags);
	void OnDisplayChange(int iBitsPerPixel, CSize sizeScreen);
	int GetChildrenClip();
	//CPlaylistInPlaceWnd * GetPlaylistInPlaceWnd();
    //CPlaylistDoc * GetPlaylistDoc();
	bool HasNextSong();
	
    bool OnDetachPlaylistDoc();
    bool OnAttachPlaylistDoc();
    CView * DetachPlaylistView();
    bool AttachPlaylistView();
    

	void DefaultLayoutPlaylist();
	void PrepareSongLabelLine();
	virtual void TimerProc(UINT nID);
	CWStr GetPlainTextV001();
	void PostPlayMessage();
	void PrepareLyricTemplateLines();
    
	void PrepareLyricLines();
	void SetOnSizeEnabled(bool bEnabled = true);
//	void OnSize_(int iType, int cx, int cy);
	void UpdateSubTitleFonts(LPCTSTR lpStr);
	void UpdateTitleFonts(LPCTSTR lpStr);
	void SetTitleVisible(bool bVisible);
	void PrepareTitle();
//	void Render(BOOL bGdiLocked);
//	void Render(LPRECT lpRect);
//	void Render(CRgn *pRgn);

	void RedrawScore(bool bBackRedraw);

	void RenderScore(CDC * pdc, bool bClearBackground);

	void XFUpdateFonts(C2DStrArray * p2DTokens);
	HRESULT RestoreAllSurfaces();
	void ClearLyricLines(bool bRender);
	
	afx_msg LRESULT OnMmsgDone(WPARAM wparam, LPARAM lparam);

	void UpdateReserveList();
	void UpdateTitle();
	void Reset();
	//void UpdateSlider();
	void UpdateTime();

	bool UpdateBuffer(bool bFastUpdate, LPRECT lprect = NULL);
	bool UpdateBuffer(int cx, int cy, bool bFastUpdate, LPRECT lprect = NULL);

    void UpdateScreen();
    void UpdateScreen(LPRECT lprect);

	BOOL LoadNextImage(bool bSynch);
	BOOL ChangeBackgroundImage(bool bRedraw);
	//LRESULT OnUserMessage(WPARAM wParam, LPARAM lParam);
	void OnLyricEvent(CLyricEventV1 *pEvent, bool bRepaint);
	void OnLyricEvent(CBaseArray<CLyricEventV1, CLyricEventV1&> * pEvents, bool bRepaint);
	virtual ~CCDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	CWinThread * CreateTransitionEffectRunStepThread();
	virtual bool TwiHasTranslucency();
	
	bool Initialize();
	virtual void WFLOnDock(CWndFrameworkV033 * pwf, CWnd * pwnd);
	
	void LayoutDynamicChild(bool bMakeVisible = false);
	CKaraokeSDIFrame * GetKaraokeSDIFrame();
	bool IsCompactMode();
	void OnPointerClear(CPlaylistDoc * pdoc);
	bool TextDocHelperAdd(CWStr &wstr);
	bool ShowBouncingBall(bool bShow);
	
	bool ShowAudioSpectrum(bool bShow);
	bool ShowLevelMeter(bool bShow);
	bool ShowPlayerControlSetV19(bool bShow);
	
	void OnScoringEnable(bool bEnable);
	
	void PrepareBouncingBall();
	
	bool CreateBitmap(CDC * pdc, CBitmap * pbitmapOld, CBitmap * pbitmap, BITMAP * pbmp, int cx, int cy);
	void LayoutKaraokeBouncingBall();
	void LayoutLyricTemplateLines(bool bGdiLocked);
	void LayoutLyricLines(bool bGdiLocked);
	virtual void OnTwiInitialize();
	void Layout();
	bool SetFullScreen(bool bFullScreen);
	bool SetCompactMode(bool bCompact);
	void RenderBack2();
	bool IsPlaylistViewAttached();
	VMSRESULT GetProgressRate(double * pdRate);
	VMSRESULT SetProgressRate(double dRate);
    virtual VMSRESULT UpdateScreen(CTypedPtrArray <CObArray, CBaseRgn *>  * rgna, bool bGdiLocked);
	virtual VMSRESULT UpdateScreen(CRgn * prgn, bool bGdiLocked);
    virtual VMSRESULT UpdateScreen(LPRECT lprect, bool bGdiLocked);
protected:
   	void SetPlayingPosition_(double dRate);
    void SetPlayingPosition_(TICKS tkPosition);

protected:
	void OnChangeFullScreen(CCDViewUpdateHint *puh);
	virtual void OnChangeCompactMode(CCDViewUpdateHint * puh);

	//{{AFX_MSG(CCDView)
	afx_msg void OnPlay();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnStop();
	afx_msg void OnPause();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNextSong();
	afx_msg void OnUpdateNextSong(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPlaypause();
	afx_msg void OnUpdatePlaypause(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnExecuteTransposeMinus();
	afx_msg void OnUpdateExecuteTransposeMinus(CCmdUI* pCmdUI);
	afx_msg void OnExecuteTransposePlus();
	afx_msg void OnUpdateExecuteTransposePlus(CCmdUI* pCmdUI);
	afx_msg void OnExecuteTransposeReset();
	afx_msg void OnUpdateExecuteTransposeReset(CCmdUI* pCmdUI);
	afx_msg void OnViewImageTile();
	afx_msg void OnViewImageZoomall();
	afx_msg void OnViewImageStretch();
	afx_msg void OnViewImageZoomextend();
    afx_msg void OnUpdateViewImageTile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewImageZoomall(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewImageZoomextend(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewImageStretch(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnExecuteTransposePlusTone();
	afx_msg void OnUpdateExecuteTransposePlusTone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateExecuteTransposeMinusTone(CCmdUI* pCmdUI);
	afx_msg void OnExecuteTransposeMinusTone();
	afx_msg void OnExecuteTempoReset();
	afx_msg void OnUpdateExecuteTempoReset(CCmdUI* pCmdUI);
	afx_msg void OnExecuteTempoPlus();
	afx_msg void OnUpdateExecuteTempoPlus(CCmdUI* pCmdUI);
	afx_msg void OnExecuteTempoMinus();
	afx_msg void OnUpdateExecuteTempoMinus(CCmdUI* pCmdUI);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnViewPlaylist();
	afx_msg void OnViewLyricviewSpectrum();
	afx_msg void OnViewSongInfo();
	afx_msg void OnUpdateViewSongInfo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewLyricviewSpectrum(CCmdUI* pCmdUI);
	afx_msg void OnViewNextImageNow();
	afx_msg void OnViewSkipImageAlways();
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnViewBouncingball();
	afx_msg void OnUpdateViewBouncingball(CCmdUI* pCmdUI);
	afx_msg void OnViewGradualfilling();
	afx_msg void OnUpdateViewGradualfilling(CCmdUI* pCmdUI);
	afx_msg void OnRefresh();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnViewBounceBall1();
	afx_msg void OnViewBounceBall2();
	afx_msg void OnXfplayerMenubar();
	afx_msg void OnWindowLevelmeter();
	afx_msg void OnViewLevelmeter();
	afx_msg void OnViewAudiospectrum();
	afx_msg void OnWindowAudiospectrum();
	afx_msg void OnUpdateWindowLevelmeter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowAudiospectrum(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewLevelmeter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewAudiospectrum(CCmdUI* pCmdUI);
	afx_msg void OnViewPlayercontrolsetv19();
	afx_msg void OnUpdateViewPlayercontrolsetv19(CCmdUI* pCmdUI);
	afx_msg void OnWindowPlayercontrolsetv19();
	afx_msg void OnUpdateWindowPlayercontrolsetv19(CCmdUI* pCmdUI);
	afx_msg void OnOpenLink();
	//}}AFX_MSG
    afx_msg LRESULT OnVMSNotify(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnEconoModeChange(WPARAM wParam, LPARAM lParam);
    afx_msg void OnKeyDownEdit( VMSNMHDR * pNotifyStruct, LRESULT * result );
    afx_msg void OnSysKeyDownEdit( VMSNMHDR * pNotifyStruct, LRESULT * result );
    afx_msg LRESULT OnUserMessage(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnAppMessage(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnXfplayerViewMessage(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnVMSTimer(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAppNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAppLanguage(WPARAM wParam, LPARAM lParam);
//    afx_msg LRESULT OnRenderTransparent(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnMidiPlayerNotifyEvent(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnApp3377Message(WPARAM wparam, LPARAM lparam);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CDVIEW.cpp
inline CXfplayerDoc* CCDView::GetDocument()
   { return (CXfplayerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDVIEW_H__A75120B2_F7F2_4E0D_AF07_32AC0CE5D582__INCLUDED_)
