// xfplayer4View.cpp : implementation of the CCDView class
//

#include "StdAfx.h"

#include "WndFrameWorkV033.h"

#include "FontCentral.h"
#include "Savings.h"

#include "PlaylistDoc.h"
#include "PlaylistFrame.h"
#include "PlaylistListView.h"


#include "SliderV008.h"

#include "MidiCentral.h"
#include "MidiPlyr.h"
#include "Midi.h"
#include "MidiException.h"
#include "MidiTracks.h" 

#include "XF.h"
#include "Imaging.h"
//#include "MainFrame.h"
#include "debug.h"
#include "WaveIn.h"
#include "WaveBuffer.h"
#include "LyricEventsv2.h"


#include "DBImageFile.h"
#include "DBImageDirectory.h"
#include "DataCentral.h"
#include "XfplayerViewUpdateHint.h"
#include "Math.h"
#include "ErrorDialog.h"
#include "DWArray.h"
#include "VmpTimer.h"

#include "International.h"

#include "DBLong.h"
#include "DBStringSet.h"
#include "DBTableV004.h"

#include <math.h>
#include "Math_.h"
#include "BaseRect.h"

#include "EditV017.h"
#include "SliderV017.h"
#include "ToolV023Dialog.h"

#include "MenuCentral.h"
#include "MenuV033.h"

#include "../vms/VMS.h"



#include "VmsTextDoc.h"
#include "GenericViewUpdateHint.h"
#include "TransparentFrameWndV8.h"
#include "PlayerControlSetV19Frame.h"
#include "PlayerControlSetV19View.h"


#include "PlayerDoc.h"


//#include <objbase.h>

//extern CVmpApp theApp;
#include "KaraokeBouncingBall.h"
#include "KaraokeSDIFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCDView

WPARAM CCDView::USERMESSAGE_WPARAM_UPDATESCREEN_NEWRECT = 1234566;
WPARAM CCDView::USERMESSAGE_WPARAM_UPDATESCREEN_LPCRECT = 1234567;
WPARAM CCDView::USERMESSAGE_WPARAM_RAND_LPINT = 1234568;

IMPLEMENT_DYNCREATE(CCDView, CView)

BEGIN_MESSAGE_MAP(CCDView, CView)
	//{{AFX_MSG_MAP(CCDView)
	ON_COMMAND(ID_PLAY, OnPlay)
	ON_WM_SIZE()
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_PAUSE, OnPause)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_COMMAND(ID_NEXT_SONG, OnNextSong)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PLAYPAUSE, OnPlaypause)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_WM_PARENTNOTIFY()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_EXECUTE_TRANSPOSE_MINUS, OnExecuteTransposeMinus)
	ON_COMMAND(ID_EXECUTE_TRANSPOSE_PLUS, OnExecuteTransposePlus)
	ON_COMMAND(ID_EXECUTE_TRANSPOSE_RESET, OnExecuteTransposeReset)
	ON_COMMAND(ID_VIEW_IMAGE_TILE, OnViewImageTile)
	ON_COMMAND(ID_VIEW_IMAGE_ZOOMALL, OnViewImageZoomall)
	ON_COMMAND(ID_VIEW_IMAGE_STRETCH, OnViewImageStretch)
	ON_COMMAND(ID_VIEW_IMAGE_ZOOMEXTEND, OnViewImageZoomextend)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_EXECUTE_TRANSPOSE_PLUS_TONE, OnExecuteTransposePlusTone)
	ON_COMMAND(ID_EXECUTE_TRANSPOSE_MINUS_TONE, OnExecuteTransposeMinusTone)
	ON_COMMAND(ID_EXECUTE_TEMPO_RESET, OnExecuteTempoReset)
	ON_UPDATE_COMMAND_UI(ID_NEXT_SONG, OnUpdateNextSong)
	ON_UPDATE_COMMAND_UI(ID_PLAYPAUSE, OnUpdatePlaypause)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_TRANSPOSE_MINUS, OnUpdateExecuteTransposeMinus)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_TRANSPOSE_PLUS, OnUpdateExecuteTransposePlus)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_TRANSPOSE_RESET, OnUpdateExecuteTransposeReset)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_TRANSPOSE_PLUS_TONE, OnUpdateExecuteTransposePlusTone)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_TRANSPOSE_MINUS_TONE, OnUpdateExecuteTransposeMinusTone)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_TEMPO_RESET, OnUpdateExecuteTempoReset)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_TEMPO_PLUS, OnUpdateExecuteTempoPlus)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE_TEMPO_MINUS, OnUpdateExecuteTempoMinus)
	ON_UPDATE_COMMAND_UI(ID_VIEW_IMAGE_TILE, OnUpdateViewImageTile)
	ON_UPDATE_COMMAND_UI(ID_VIEW_IMAGE_ZOOMALL, OnUpdateViewImageZoomall)
	ON_UPDATE_COMMAND_UI(ID_VIEW_IMAGE_ZOOMEXTEND, OnUpdateViewImageZoomextend)
	ON_UPDATE_COMMAND_UI(ID_VIEW_IMAGE_STRETCH, OnUpdateViewImageStretch)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SONGINFO, OnUpdateViewSongInfo)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LEVELMETER, OnUpdateViewLevelmeter)
	ON_UPDATE_COMMAND_UI(ID_VIEW_AUDIOSPECTRUM, OnUpdateViewAudiospectrum)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PLAYERCONTROLSETV19, OnUpdateViewPlayercontrolsetv19)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRADUALFILLING, OnUpdateViewGradualfilling)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BOUNCINGBALL, OnUpdateViewBouncingball)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_LEVELMETER, OnUpdateWindowLevelmeter)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_AUDIOSPECTRUM, OnUpdateWindowAudiospectrum)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_PLAYERCONTROLSETV19, OnUpdateWindowPlayercontrolsetv19)
	ON_COMMAND(ID_EXECUTE_TEMPO_PLUS, OnExecuteTempoPlus)
	ON_COMMAND(ID_EXECUTE_TEMPO_MINUS, OnExecuteTempoMinus)
	ON_WM_HSCROLL()
	ON_COMMAND(ID_VIEW_PLAYLIST, OnViewPlaylist)
	ON_COMMAND(ID_VIEW_SONGINFO, OnViewSongInfo)
//	ON_COMMAND(ID_VIEW_LYRICVIEW_SPECTRUM, OnViewLyricviewSpectrum)
//	ON_COMMAND(ID_VIEW_LYRICVIEW_SONGINFO, OnViewLyricviewSonginfo)
//	ON_UPDATE_COMMAND_UI(ID_VIEW_LYRICVIEW_SPECTRUM, OnUpdateViewLyricviewSpectrum)
	ON_COMMAND(ID_VIEW_NEXT_IMAGE_NOW, OnViewNextImageNow)
	ON_COMMAND(ID_VIEW_SKIP_IMAGE_ALWAYS, OnViewSkipImageAlways)
	ON_COMMAND(ID_VIEW_BOUNCINGBALL, OnViewBouncingball)
	ON_COMMAND(ID_VIEW_GRADUALFILLING, OnViewGradualfilling)
	ON_COMMAND(ID_REFRESH, OnRefresh)
	ON_COMMAND(ID_VIEW_BOUNCE_BALL1, OnViewBounceBall1)
	ON_COMMAND(ID_VIEW_BOUNCE_BALL2, OnViewBounceBall2)
	ON_COMMAND(IDR_XFPLAYER_MENUBAR, OnXfplayerMenubar)
	ON_COMMAND(ID_WINDOW_LEVELMETER, OnWindowLevelmeter)
	ON_COMMAND(ID_VIEW_LEVELMETER, OnViewLevelmeter)
	ON_COMMAND(ID_VIEW_AUDIOSPECTRUM, OnViewAudiospectrum)
	ON_COMMAND(ID_WINDOW_AUDIOSPECTRUM, OnWindowAudiospectrum)
	ON_COMMAND(ID_VIEW_PLAYERCONTROLSETV19, OnViewPlayercontrolsetv19)
	ON_COMMAND(ID_WINDOW_PLAYERCONTROLSETV19, OnWindowPlayercontrolsetv19)
	ON_COMMAND(ID_OPEN_LINK, OnOpenLink)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
    ON_MESSAGE(VMSM_ECONOMODECHANGE, OnEconoModeChange)
    ON_MESSAGE(VMSM_NOTIFY, OnVMSNotify)
    ON_MESSAGE(WM_USER, OnUserMessage)
    ON_MESSAGE(WM_APP, OnAppMessage)
    ON_MESSAGE(VMSPM_XFVIEW, OnXfplayerViewMessage)
    ON_MESSAGE(VMSM_TIMER, OnVMSTimer)
	ON_MESSAGE(APPM_NOTIFY, OnAppNotify)
	ON_MESSAGE(CVmsGenApp::APPM_LANGUAGE, OnAppLanguage)
	ON_MESSAGE(MMSG_DONE, OnMmsgDone)
	ON_MESSAGE(MIDIPLAYERMESSAGE_NOTIFYEVENT, OnMidiPlayerNotifyEvent)
//    ON_MESSAGE(WM_USER + 100, OnRenderTransparent)
    ON_MESSAGE(WM_APP + 3377, OnApp3377Message)
	ON_MESSAGE(WM_APP_TRANSPARENT_PAINT, CTransparentWndInterface::OnTwiPaint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDView construction/destruction
//const DWORD CCDView::m_dwOnSizeUpdateTimeOut = 300;
///const DWORD CCDView::m_dwBackgroundUpdateTimeOut = 100;
const DWORD CCDView::m_dwBackgroundUpdateTimeOut = 300;

CCDView::CCDView()
:
m_lyricTemplateLines(this, &m_lyricLines),
m_transitioneffect(*this)

{
	m_evTransitionEffectRunStep.ResetEvent();
	m_pthreadTransitionEffectRunStep = NULL;
	m_sliderProgress.m_bPresenceOnHover = true;
	m_bDestroy = false;
	m_pvmstextdocHelper = NULL;
	m_iRightVerticalShift = 0;
	m_bHoverTimer = false;

//	m_pkcs1wndLevelMeter = NULL;
//	m_plevelmeterwnd = NULL;
//	m_pkcs1wndAudioSpectrum = NULL;
//	m_paudiospectrumwnd = NULL;
	// TODO: add construction code here
//	m_hBitmap = NULL;
//	m_hDblBufferBmp = NULL;
//	m_hScaledBitmap = NULL;
//	m_pRgn = NULL;
	m_uiTimer = 0;
	m_dwBackgroundLastUpdateTime = 0;
	m_dwSliderLastUpdateTime = 0;
	m_dwTimeLastUpdateTime = 0;
	m_dwPlayStartTime = 0;
	m_bLastLoadImageSynch = true;
//	m_pFreeImage = NULL;
//	m_hBitmap = NULL;
//	count = 0;
	m_cnt = 0L; 
//	m_Thread.m_bAutoDelete = FALSE;
//	m_Thread.CreateThread(0, 0, NULL);
//	m_Thread.SetThreadPriority(THREAD_PRIORITY_IDLE );
//	m_Thread.m_pParent = this;
//	InitializeCriticalSection(&m_csGdi);
//	m_sp
	
    LOGBRUSH lb;

    memset(&lb, 0, sizeof(lb));
/*    lb.lbColor = RGB(255, 255, 255);
    lb.lbStyle = BS_SOLID;
	m_penLeft.CreatePen(
        PS_SOLID |
        PS_GEOMETRIC |
        PS_JOIN_ROUND |
        PS_ENDCAP_ROUND, 2,
        &lb);*/
	
	m_penLeft.DeleteObject();
    m_penLeft.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));

	m_penRight.DeleteObject();
	m_penRight.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	m_penLeftSmall.DeleteObject();
    m_penLeftSmall.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	m_penRightSmall.DeleteObject();
	m_penRightSmall.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	m_penTitle.DeleteObject();
	m_penTitle.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	m_penSubTitle.DeleteObject();
	m_penSubTitle.CreatePen(PS_SOLID, 0, RGB(64, 64, 0));
	m_crLeft = RGB(255, 127, 0);
	m_crRight = RGB(255, 255, 0);
	m_crTitle = RGB(0, 255, 255);
	m_crSubTitle = RGB(255, 255, 192);
	m_dwScoreLastUpdateTime = 0;
	m_penScore.CreatePen(PS_SOLID, 3, RGB(255, 127, 0));
	m_bTitleVisible = false;
	m_bOnSizeEnabled = false;
    m_dwAdvancingTime = 0;
    m_bInitialized = false;
    
    m_pplaylistframe = NULL;
//    m_pplaylistipwnd = NULL;
    m_pplaylistdoc = NULL;
//	m_pfiBitmap = NULL;
    m_rgnChildren.CreateRectRgn(0 ,0 ,0 , 0);
    ///m_psliderProgress = new CSliderV017();
//    m_pedit = new CEditV017();
//    m_bDirectDrawPresenceChecked = false;
  //  m_bDirectDrawPresent = false;
    //m_bDirectDrawActive = false;

    m_lpbouncingball = new CKaraokeBouncingBall();
    m_lpbouncingball->SetIcons(AfxGetApp()->LoadIcon(IDI_BB1), AfxGetApp()->LoadIcon(IDI_BB1_PRESSED1));

    m_dProgressRate = 0.0;

    m_dScoreRate = 0.0;

//    m_dwOnSizeUpdateTimeIn = timeGetTime();
        m_dwBackgroundUpdateTimeIn = timeGetTime();
        m_dwLastTime1 = timeGetTime();

        m_bBouncingBall = false;
        m_bGradualFilling = true;
    
    m_enhmetafile = NULL;
    memset(&m_emh, 00, sizeof(m_emh));

    m_rcLastBkImage.SetRect(0, 0, 0, 0);
}

CCDView::~CCDView()
{
    //if(m_psliderProgress != NULL)
      //  delete m_psliderProgress;
    if(m_lpbouncingball != NULL)
    {
        delete m_lpbouncingball;
        m_lpbouncingball = NULL;
    }
/*	if(m_pkcs1wndAudioSpectrum != NULL)
	{
		delete m_pkcs1wndAudioSpectrum;
		m_pkcs1wndAudioSpectrum = NULL;
		CWaveCentral::AppGetWaveCentral()->WaveCentralGetWaveIn()->Release();
	}*/
}

BOOL CCDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	cs.lpszClass = pApp->m_XFViewClassName;
    //cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
    //cs.style &= ~WS_CLIPCHILDREN;
    if(!CView::PreCreateWindow(cs))
        return FALSE;
    cs.style |= WS_CLIPCHILDREN;
    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    //cs.style |= WS_CLIPCHILDREN;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCDView drawing

void CCDView::OnDraw(CDC* pDC)
{
    TwiInvalidate(pDC);
	TwiRedraw();
    return;
    CSingleLock slGdi(&m_csGdi, true);
    CRect rect;
        GetClientRect(rect);
        ClientToScreen(rect);
       
    return;
    pDC->GetClipBox(rect);
    if(rect.IsRectNull())
    {
        return;
    }

//    if(!m_dcScreen.BitBlt(
//		rect.left,
//		rect.top,
//		rect.Width(),
//		rect.Height(), 
//		&m_dcBuffer,
//		rect.left,
//		rect.top,
//		SRCCOPY))
	{
		TRACE0("CCDView::OnDraw Bitmap not painted.\n");
	} 

}

/////////////////////////////////////////////////////////////////////////////
// CCDView printing

BOOL CCDView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCDView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCDView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCDView diagnostics

#ifdef _DEBUG
void CCDView::AssertValid() const
{
	CView::AssertValid();
}

void CCDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXfplayerDoc* CCDView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXfplayerDoc)));
	return (CXfplayerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCDView message handlers

void CCDView::OnPlay() 
{
	// TODO: Add your command handler code here
	//ChangeBackgroundImage();
    double dRate = 0.0;
    GetProgressRate(&dRate);
    ((CXfplayerDoc *)GetDocument())->SetProgressRate(dRate);
	((CXfplayerDoc *)GetDocument())->Play(true);

}

void CCDView::OnNextSong() 
{
	// TODO: Add your command handler code here
	((CXfplayerDoc *)GetDocument())->NextSong(FALSE, true);
	
}

void CCDView::OnUpdateNextSong(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    bool bEnable;
    if(pApp->m_pMainWnd == NULL)
    {
        bEnable = true;
    }
    else if(pApp->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CKaraokeSDIFrame)))
    {
        bEnable = HasNextSong();
    }
    else
    {
        bEnable = true;
    }
	pCmdUI->Enable(bEnable);
}

void CCDView::OnInitialUpdate() 
{
    if(!m_bInitialized)
		Initialize();	


	CXfplayerDoc * pdoc = GetDocument();

	CFrameWnd     * pframe = GetParentFrame();

	pframe->SetActiveView(this);

	RECT rect;
	GetClientRect(&rect);

   	m_lyricTemplateLines.RemoveAll();
    m_lyricTemplateLines.SetSize(4);
    
	PrepareProgressSlider();
    PrepareSongLabelLine();
    PrepareLyricTemplateLines();
    

    m_lineScore.SetAutoSize(true);
	m_lineScore.SetAlign(CCDViewLine::AlignRight);
    

    m_lpbouncingball->SetTwi(this);
    m_lpbouncingball->SetBackgroundDC(&m_dcBack);

	OnScoringEnable(pdoc->GetScoring()->IsEnabled());

}

void CCDView::OnSize(UINT nType, int cx, int cy) 
{

	CView::OnSize(nType, cx, cy);
    
	Layout();

	_ImageChangePostEvent(BkImageEventResize);

	

}

void CCDView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if(lHint == 1314151617)
	{
		PrepareLyricLines();
		TwiRedraw();
		CKaraokeSDIFrame * pframe = (CKaraokeSDIFrame *) GetParentFrame();
		pframe->OnUpdateLyricsCodePage();
		return;
	}
    CXfplayerDoc * pDoc = GetDocument();
    CXfplayerDoc * pdoc = pDoc;
	CFrameWnd * pframe = GetParentFrame();
	CKaraokeSDIFrame * psdiframe = NULL;
	if(pframe->IsKindOf(RUNTIME_CLASS(CKaraokeSDIFrame)))
	{
		psdiframe = (CKaraokeSDIFrame *) pframe;
	}
	CCDViewUpdateHint * pUpdateHint = (CCDViewUpdateHint *) pHint;
	if(psdiframe == NULL)
	{
		m_bFullScreen = false;
		m_bCompactMode = false;
	}
	else
	{
		m_bCompactMode = psdiframe->m_bCompactSize;
		m_bFullScreen = psdiframe->IsFullScreen();
	}
	CCDViewUpdateHint * pxfpuh = NULL;
	if(pHint != NULL
		&& pHint->IsKindOf(RUNTIME_CLASS(CCDViewUpdateHint)))
	{
		pxfpuh = (CCDViewUpdateHint *) pHint;
	}
	

	if(pxfpuh != NULL)
	{
		switch(pxfpuh->GetType())
		{
		case CCDViewUpdateHint::UpdateStart:
			{
				Layout();

			}
		case CCDViewUpdateHint::FullScreenChange:
			{
				OnChangeFullScreen(pxfpuh);
			}
		case CCDViewUpdateHint::CompactModeChange:
			{
				OnChangeCompactMode(pxfpuh);
			}
		}

	}
	if(pHint != NULL &&
        pUpdateHint->GetType() == CCDViewUpdateHint::PreparePhaseA)
    {
		pdoc->GetMidiPlayer()->SetMessageWindow(GetSafeHwnd());
	}
	else if(pHint != NULL &&
        pUpdateHint->GetType() == CCDViewUpdateHint::PreparePhaseB)
    {

		PrepareTitle();
    	SetTitleVisible(true);
    	UpdateTitle();
	}
	else if(pHint != NULL &&
        pUpdateHint->GetType() == CCDViewUpdateHint::Prepare)
    {


		UpdateTime();

        PrepareLyricTemplateLines();
		PrepareLyricLines();
		PrepareBouncingBall();
    }
	if(pHint != NULL &&
        pUpdateHint->GetType() == CCDViewUpdateHint::UpdateFull)
    {
        PrepareLyricTemplateLines();
    }
	if(pHint == NULL ||
        pUpdateHint->GetType() == CCDViewUpdateHint::UpdateFull)
    {
        PrepareLyricLines();
        if(pDoc->GetMidiPlayer())
        {
//            m_psliderKeyShift->SetPos(pDoc->HelperGetMidiSequence()->GetFile()->GetKeyShift());
            
  //          m_psliderTempoShift->SetPos((WORD) (log(pDoc->HelperGetMidiSequence()->GetFile()->GetTempoShift()) * log(3)));

            int iDelay;
            if(VMS_SUCCEEDED(pDoc->HelperGetMidiSequence()->GetFile()->m_ptracks->GetLyricDelay(&iDelay)))
            {
    //            m_psliderDelay->SetPos(iDelay / 200);
            }
        }
        if(pDoc != NULL &&
            pDoc->HelperGetMidiSequence() != NULL &&
            pDoc->HelperGetMidiSequence()->GetFile() != NULL &&
            pDoc->HelperGetMidiSequence()->GetFile()->m_pFileHeader != NULL)
        {
        m_lpbouncingball->SetQuarterNoteDuration(
            pDoc->HelperGetMidiSequence()->GetFile()->m_pFileHeader->GetQuarterNoteTicks());
        }

        


    }
	if(pUpdateHint != NULL)
		if(pUpdateHint->GetType() == CCDViewUpdateHint::UpdateFull ||
            pUpdateHint->GetType() == CCDViewUpdateHint::UpdateRepaint)
        {
            Layout();
			UpdateBuffer(false);
            UpdateScreen();
        }
    if(pUpdateHint == NULL ||
        (pUpdateHint->GetType() & pUpdateHint->UpdateProgress) ||
        (pUpdateHint->GetType() & pUpdateHint->UpdateFull))
    {
        UpdateProgress();
//        SetPlayingPosition(pDoc->GetProgressRate());
    }

		if(pUpdateHint == NULL ||
            (!pUpdateHint->GetType() == CCDViewUpdateHint::UpdateFull &&
            !(pUpdateHint->GetType() == CCDViewUpdateHint::UpdateRepaint)))
        {
            InvalidateRect(NULL, FALSE);
        }


}

void CCDView::OnLyricEvent(CBaseArray<CLyricEventV1, CLyricEventV1&> * pevents, bool bRepaint)
{
//	for(int i = 0; i < pevents->GetSize(); i++)
//	{
//		OnLyricEvent(&pevents->GetAt(i), bRepaint);

//	}
    if(pevents->GetSize() > 0)
    {
        OnLyricEvent(&pevents->LastElement(), bRepaint);
    }
}

void CCDView::OnLyricEvent(CLyricEventV1 *pevent, bool bRepaint)
{
   
	
	CXfplayerDoc *pdoc = GetDocument();
	ASSERT(pdoc != NULL);
    
    if(pdoc->IsOpening())
        return;

	int iEventType = pevent->m_iType;
	int iTokenIndex = pevent->m_iCurrentToken;
	int	iNextTokenIndex = pevent->m_iCurrentToken;
	int iNoteIndex = pevent->m_iCurrentNote;
	int iPlayingIndex = -1;

    CSingleLock slSongData(&pdoc->m_csSongData, true);

	CVmpApp * papp = (CVmpApp *) AfxGetApp();
	ASSERT(papp != NULL);
	
	//CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pfonts = GetLyricFonts();
	CVmsGdiFont * pfont = GetLyricFont();
	ASSERT(pfont != NULL);

	CMidiSequence *pseq = pdoc->HelperGetMidiSequence();
	ASSERT(pseq != NULL);

	CMidiFile * pfile = pseq->GetFile();
	ASSERT(pfile != NULL);

	CLyricEventsV2 * pevents = NULL;
    CLyricEventsV2 * peventsBB = NULL;
    if(pfile->m_eventstracksV002.GetSize() > 0)
	{
        pevents = (CLyricEventsV2 *) pfile->m_eventstracksV002.operator [](0);
		ASSERT(pevents != NULL);
		ASSERT(pevents->GetClassOrder() == 2);
	}
    if(pfile->m_eventsTracksForBouncingBall.GetSize() > 0)
	{
        peventsBB = (CLyricEventsV2 *) pfile->m_eventsTracksForBouncingBall.operator [](0);
		ASSERT(peventsBB != NULL);
		ASSERT(peventsBB->GetClassOrder() == 2);
	}
    if(pevents == NULL)
        return;
	if(iEventType == 1)
	{
		pdoc->m_iBufferingTokenIndex = iTokenIndex;
	}
	else if(iEventType == 2)
	{
		pdoc->m_iPlayingTokenIndex = iTokenIndex;
		pdoc->m_iPlayingNoteIndex = iNoteIndex;
	}
	else if(iEventType == 3)
	{
		if(pseq->GetState() != CMidiSequence::StatusPlaying)
		{
			return;
		}
	}
    else if(iEventType == 4)
    {
		pdoc->m_iPlayingTokenIndex = iTokenIndex;
		pdoc->m_iPlayingNoteIndex = iNoteIndex;
    }


	CTypedPtrArray <CObArray, CBaseRgn *> rgna;


	if(m_lyricTemplateLines.GetSize() <= 0)
	{
		return;
		
	}
    CLyricViewLine * lpViewLine;

	m_lyricLines.m_bRenderEnable = false;

	// Se a linha do 'token' já está em uma das linhas,
	// não é necessário prepará-lo.
	if(iEventType == 1 &&
        !m_bBouncingBall)
	{

		int i;
        i = m_lyricLines.GetTokenLine(iTokenIndex, &lpViewLine);
        if(i >= 0 &&
            lpViewLine->GetVisible())
		{
    		return;
		}
	}

	CSingleLock slGdi(&m_csGdi, TRUE);
	//CSingleLock slBuffer(&m_ptwc->m_csGdi, TRUE);
    CDC * pdcForeground = &m_dcScreen;

	pdcForeground->SelectClipRgn(NULL);
//	CDC * pdcForeground = &m_dcBuffer;
	CRect rectClipBox;
    {
        
        pdcForeground->GetClipBox(rectClipBox);
        int i = 0;
    }

	// Prepara todos os aparatos para se desenhar
	CRect clientRect;
	GetClientRect(&clientRect);
	if(!m_dcScreen.SetMapMode(MM_TEXT))
	{
		TRACE(_T("GetLastError%d"), GetLastError());
		TRACE0("Could not set map mode to MM_TEXT.\n");
	}

    //CCDViewLine oViewLine;
    //CCDViewLine oTemplateLine;
    
    CLyricViewLineTemplate * lpTemplateLine;
    int iLineIndex; 

	// Desenha as linhas
    if(iEventType == 1 &&
        !m_bBouncingBall)
	{

        // Limpeza de todas as linhas já tocadas...
		// ou seja, as linhas já tocadas vão ser
		// deixadas em branco
        m_lyricLines.UpdateFalseVisibility(
            pdcForeground,
			false,
            &clientRect,
            &rgna,
            pdoc->m_iPlayingTokenIndex,
            pdoc->m_iPlayingNoteIndex,
            pevents,
            pfont);

		// se encontrar a linha do correspondente
		// ao token atual (iTokenIndex),
		// torna a linha visível.
        if(0 <= (iLineIndex = m_lyricLines.GetTokenLine(iTokenIndex, &lpViewLine)))
        {
            lpTemplateLine = &m_lyricTemplateLines.ElementAt(lpViewLine->m_iRelativeLineIndex);
            lpViewLine->SetVisible();
	        lpViewLine->m_dFillRate = 0.0;
            lpViewLine->SetNewTime();
		    lpViewLine->Render(
                pdcForeground,
				false,
			    &clientRect,
			    &rgna,
			    pdoc->m_iPlayingTokenIndex,
			    pdoc->m_iPlayingNoteIndex,
                XFPLYR_LINE_RENDER_FULL,
			    &count,
			    pfont,
			    pevents);
        }
		
	}
	else if(
        iEventType == 2
        || iEventType == 3
        || iEventType == 4)
	{
        if(iEventType == 4)
        {
            m_lyricLines.UpdateTrueVisibility(
                pdcForeground,
				false,
                &clientRect,
                &rgna,
                iTokenIndex,
                iNoteIndex,
                pevents,
                pfont);
        }
		// Encontra a linha do token sendo indicado para
		// grifo.
		int i;
        if(0 <= (iLineIndex =
            m_lyricLines.GetTokenLine(iTokenIndex, &lpViewLine)))
            goto Found;

		goto SkipFound;
	Found:
		iPlayingIndex = iLineIndex;
        if(m_bGradualFilling)
        {
		    if(
                (iEventType == 2 ||
                iEventType == 4))
		    {
			    if(lpViewLine->m_dFillRate < 1.0 && iTokenIndex > 0)
			    {
				    int iTokenIndexA, iNoteIndexA;
				    CArray<DWORD, DWORD> dwNotes;
				    if(iNoteIndex <= pevents->GetTokenFirstNote(iTokenIndex))
				    {
					    iTokenIndexA = iTokenIndex - 1;
					    iNoteIndexA = pevents->GetTokenLastNote(iTokenIndexA);
				    }
				    else
				    {
					    iTokenIndexA = iTokenIndex;
					    iNoteIndexA = iNoteIndex - 1;
				    }
				    lpViewLine->m_dFillRate = 1.0;
				    lpViewLine->Render(
					    pdcForeground,
						false,
                        &clientRect,
					    &rgna,
					    iTokenIndexA,
					    iNoteIndexA,
					    XFPLYR_LINE_RENDER_UPDATE,
					    &count,
					    pfont,
					    pevents);
			    }
                if(iEventType == 2)
                {
			    m_dwPlayStartTime = timeGetTime();
			    //pViewLine->m_dFillRate = 0.7;
			    if(iNoteIndex < pevents->m_msaNotesDuration.GetSize())
				    lpViewLine->UpdateFillRate(0, pevents->m_msaNotesDuration[iNoteIndex]);
			    else
				    lpViewLine->m_dFillRate = 1.0;
		        }
    	        else if(iEventType == 4)
                {
		            TICKS tkCurrentPosition;
                    TICKS tkNextPosition;
		            if(iTokenIndex >= pevents->m_tkaTokensPosition.GetSize())
		            {
			            tkCurrentPosition = pseq->m_tkLength;
			            tkNextPosition = pseq->m_tkLength;
		            }
		            else if(iTokenIndex + 1 >= pevents->m_tkaTokensPosition.GetSize())
		            {
			            tkCurrentPosition = pevents->m_tkaTokensPosition.GetAt(iTokenIndex);	
                        tkNextPosition = pseq->m_tkLength;
		            }
                    else
		            {
			            tkCurrentPosition = pevents->m_tkaTokensPosition.GetAt(iTokenIndex);
                        tkNextPosition = pevents->m_tkaTokensPosition.GetAt(iTokenIndex + 1);
		            }
		            TICKS tkNumerator = pevent->m_tkPosition - tkCurrentPosition;
		            TICKS tkDenominator = tkNextPosition - tkCurrentPosition;
		            if(tkDenominator == 0)
			            if(tkNumerator > 0)
				            lpViewLine->m_dFillRate = 1.0; 
			            else
				            lpViewLine->m_dFillRate = 0.0; 
		            else
			            lpViewLine->m_dFillRate = (double) tkNumerator / tkDenominator; 
                }
            }
            else
		    {
			    DWORD time = timeGetTime();
			    
			    if(iNoteIndex >= pevents->m_msaNotesDuration.GetSize())
			    {
				    lpViewLine->m_dFillRate = 1.0;
			    }
			    else if(iNoteIndex < 0)
                {
                    lpViewLine->m_dFillRate = 0.0;
                }
                else
			    {
				    lpViewLine->UpdateFillRate(time - m_dwPlayStartTime, pevents->m_msaNotesDuration[iNoteIndex] + 100); 
			    }
		    }
        }
        else
        {
            lpViewLine->m_dFillRate = 1.0;
        }
        
		lpViewLine->Render(
			pdcForeground,
			false,
            &clientRect,
			&rgna,
			pdoc->m_iPlayingTokenIndex,
			pdoc->m_iPlayingNoteIndex,
			XFPLYR_LINE_RENDER_UPDATE,
			&count,
			pfont,
			pevents);

		if(!m_bBouncingBall &&
            (iEventType == 2 || iEventType == 4 ||
            (iEventType == 3 &&
               timeGetTime() - m_dwAdvancingTime < 2000)))
		{
            m_dwAdvancingTime = timeGetTime();
            if(iEventType == 2 || iEventType == 4)
            {
              m_lyricLines.UpdateFalseVisibility(
                        pdcForeground,
						false,
                        &clientRect,
                        &rgna,
                        pdoc->m_iPlayingTokenIndex,
                        pdoc->m_iPlayingNoteIndex,
                        pevents,
                        pfont);
            }
          
            CLyricViewLine * lpPlayingViewLine = NULL;
            int iPlayingLineIndex;
            iPlayingLineIndex = m_lyricLines.GetTokenLine(pdoc->m_iPlayingTokenIndex, &lpPlayingViewLine);
//            TRACE(_T("iPlayingLineIndes = %d\n"), iPlayingLineIndex);
            if(iPlayingLineIndex >= 0 && lpPlayingViewLine != NULL)
            {
            
                int iLastLineIndex;
                int iForeLineIndex;
            
                CLyricViewLine * lpLastViewLine = NULL;
                CLyricViewLine * lpForeViewLine = NULL;

                CDWArray dwaVisibleLines;
  		    for(i = iPlayingLineIndex + 1;
                i < iPlayingLineIndex + m_lyricTemplateLines.GetSize() &&
                i < m_lyricLines.GetSize();
                i++)
		    {
                iLineIndex = i;
//                TRACE(_T("iLineIndex = %d\n"), iLineIndex);
                if(iLineIndex >= 0 &&
                    iLineIndex < m_lyricLines.GetSize())
                    
                {

                    lpViewLine = &m_lyricLines.ElementAt(iLineIndex);
                    if(dwaVisibleLines.HasItem(lpViewLine->m_iRelativeLineIndex))
                        break;
                    if(lpViewLine->m_iRelativeLineIndex == lpPlayingViewLine->m_iRelativeLineIndex)
                        break;

                    iLastLineIndex = iLineIndex - 1;
                    if(iLastLineIndex >= 0 &&
                        iLastLineIndex < m_lyricLines.GetSize())
                        lpLastViewLine = &m_lyricLines.ElementAt(iLastLineIndex);
                    else
                        lpLastViewLine = NULL;
                    
                    iForeLineIndex = iLineIndex;
                    while(true)
                    {
                        iForeLineIndex--;
                        if(iForeLineIndex < 0)
                        {
                            lpForeViewLine = NULL;
                            break;
                        }
                        lpForeViewLine = &m_lyricLines.ElementAt(iForeLineIndex);
                        if(lpForeViewLine->m_iRelativeLineIndex == lpViewLine->m_iRelativeLineIndex)
                            break;
                    }
			        if(lpForeViewLine == NULL
                        || CCDViewLine::StatusClean == lpForeViewLine->GetStatus(pdoc->m_iPlayingTokenIndex)
                        || (CCDViewLine::StatusNew == lpViewLine->GetStatus(pdoc->m_iPlayingTokenIndex) &&
                        iLineIndex > iPlayingLineIndex + m_lyricTemplateLines.GetSize()))
			        {
                        if(!lpViewLine->GetVisible() &&
                            (iEventType == 4 ||
                            ((lpLastViewLine == NULL)
//                            || lpLastViewLine->GetStatus(pDoc->m_iPlayingTokenIndex) != CCDViewLine::StatusNew
                            || lpLastViewLine->IsNewTimedOut())
                            && 
                            ((lpForeViewLine == NULL) ||
                                lpForeViewLine->IsCleanTimedOut())))
                                
                        {
//                            TRACE(_T("NEW LINE IN ADVANCE iLineIndex = %d\n"), iLineIndex);
                            lpTemplateLine = &m_lyricTemplateLines.ElementAt(lpViewLine->m_iRelativeLineIndex);
                            lpViewLine->SetVisible();
	                        lpViewLine->m_dFillRate = 0.0;
                            lpViewLine->SetNewTime();
		                    lpViewLine->Render(
			                    pdcForeground,
								false,
                                &clientRect,
			                    &rgna,
			                    pdoc->m_iPlayingTokenIndex,
			                    pdoc->m_iPlayingNoteIndex,
			                    XFPLYR_LINE_RENDER_CLEAR_FULL,
			                    &count,
			                    pfont,
			                    pevents);
                            //lpViewLine->SetStatus(CCDViewLine::StatusNew);
                        }
                    else
                    {
                        if(!lpViewLine->GetVisible())
                            break;
                    }
                    dwaVisibleLines.Add(lpViewLine->m_iRelativeLineIndex);
                    }

                    }
                }
		    }
		}
	SkipFound:;

	}
    
    //if(iType == 3)
    //{

    {
        CRect rectXX;
        pdcForeground->GetClipBox(rectXX);
        int i = 0;
    }


    
    if(m_bBouncingBall)
    {
        if(m_lpbouncingball->HasPendingBBArrange() &&
            timeGetTime() - m_dwLastShiftUpdate >  140 &&
            m_lyricLines.GetSize() > 0 &&
            (m_lpbouncingball->GetBBArrangeLine() !=
            this->m_lyricLines.GetSize() - 1))
        {
            m_dwLastShiftUpdate = timeGetTime();
            m_lpbouncingball->ClearPendingBBArrange();
            m_lyricLines.BBArrange(
                pdcForeground,
				false,
                m_lpbouncingball->GetBBArrangeLine(),
                &clientRect,
				&rgna,
				pdoc->m_iPlayingTokenIndex,
				pdoc->m_iPlayingNoteIndex,
				&count,
				pfont,
				pevents,
                m_lpbouncingball->GetBBArrangeRate());
        }
    }
        

    slSongData.Unlock();
    //TwiReleaseDC(pdcForeground);
//    slBuffer.Unlock();
    UpdateScreen(&rgna, true);
	slGdi.Unlock();


//	slBuffer.Lock();
//    pdcForeground = TwiGetDC();
	slGdi.Lock();

    if(m_bBouncingBall)
    {
        ASSERT(m_lpbouncingball != NULL);
        TICKS tkPosition;
        pseq->GetTime(&tkPosition);
		m_lpbouncingball->SetPosition(tkPosition);

        int iTokenIndexA = pdoc->m_iPlayingTokenIndex;

        if(iTokenIndexA < 0)
        {
            iTokenIndexA = 0;
        }

        int iNoteIndexA = pevents->GetTokenFirstNote(iTokenIndexA);
        if(0 <= (iLineIndex = 
            m_lyricLines.GetTokenLine(iTokenIndexA, &lpViewLine)))
        {
            m_lpbouncingball->Render(
                pdcForeground,
				false,
                pfile,
                lpViewLine,
                &rgna,
                peventsBB,
                GetSafeHwnd());
		}
                
        
    }

//	TwiReleaseDC(pdcForeground);
//    slBuffer.Unlock();
    UpdateScreen(&rgna, true);
	slGdi.Unlock();

}


afx_msg LRESULT CCDView::OnAppMessage(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case 534231:
		{
			CXfplayerDoc * pdoc = GetDocument();        
			if(pdoc->GetMidiPlayer())
			{
				pdoc->GetMidiPlayer()->SetMidiOutDevice(CMidiCentral::GetMidiCentral()->m_uiMidiOutDevice);
			}
		}
		break;
	case 178:
		{
			LayoutDynamicChild();
		}
		break;
	case 179:
		{
			LayoutDynamicChild(true);
		}
	default:
		break;
	}
	return 0;
}

afx_msg LRESULT CCDView::OnUserMessage(WPARAM wParam, LPARAM lParam)
{
	CVmpApp *papp = (CVmpApp *) AfxGetApp();
	ASSERT(papp != NULL);
	if(wParam == USERMESSAGE_WPARAM_UPDATESCREEN_LPCRECT)
	{
		LPCRECT lpcrect = (LPRECT) lParam;
		CRect rect(lpcrect);
		UpdateScreen(rect);
	}
	else if(wParam == USERMESSAGE_WPARAM_UPDATESCREEN_NEWRECT)
	{
		LPRECT lprect = (LPRECT) lParam;
		UpdateScreen(lprect);
		delete lprect;
	}
	else if(wParam == USERMESSAGE_WPARAM_RAND_LPINT)
	{
		LPINT lpint = (LPINT) lParam;
		*lpint = rand();
	}
    else if(wParam == 4)
    {
   		LPSCOREUPDATEMESSAGE lpsum = (LPSCOREUPDATEMESSAGE) lParam ;
        //TRACE(_T("CXfplayerThreadV1::TranslateUserMessage 2 slGdi.Lock\n"));
/*		if(m_paudiospectrumwnd != NULL)
		{
			m_paudiospectrumwnd->Update(
				papp->WaveCentralGetWaveIn()->GetFormatEx(),
				lpsum->dDeltaScore,
				lpsum->dScoreAddUp);
		}*/
//		CRect rect;
//		m_voiceSpectrum.GetPlacement(rect);
//		TwiRedraw(rect);

//		CSingleLock slGdi(&m_csGdi, TRUE);

//		m_voiceSpectrum.Render(pApp->GetWaveIn()->GetFormatEx(), lpSum->dDeltaScore, lpSum->dScoreAddUp);
//		CRect rect;
//		m_voiceSpectrum.GetPlacement(rect);
        //pView->ClientToScreen(rect);
		//InvalidateRect(&rect, FALSE);
        //TRACE(_T("CXfplayerThreadV1::TranslateUserMessage 2 slGdi.UnLock\n"));
		
//		pView->RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE | RDW_ALLCHILDREN);
//        pView->RenderTransparent(pView, rect, NULL, true);
//        UpdateScreen(rect, true);
//        slGdi.Unlock();


    }
	else if(wParam == 16384)
	{
		ChangeBackgroundImage(true);
	}
	else if(wParam == 3377)
	{
        ASSERT(FALSE);
		OnLyricEvent((CLyricEventV1 *) lParam, true);
		delete (CLyricEventV1 *)lParam;
	}
	else if(wParam == 3388)
	{
        // Lyric View Event 
		OnLyricEvent((CBaseArray<CLyricEventV1, CLyricEventV1&> *) lParam, true);
//		delete (CBaseArray<CLyricEventV1, CLyricEventV1&> *)lParam;
	}
    else if(wParam == 3389)
    {
        TRACE(_T("CCDView::OnUserMessage 1 slGdi.Lock\n"));
		CRect rect;
		ASSERT(FALSE);
//		if(m_paudiospectrumwnd != NULL)
//		{
//			m_paudiospectrumwnd->TwiRedraw();
//		}
		//m_voiceSpectrum.GetPlacement(rect);
		//TwiRedraw(rect);
//		CSingleLock slGdi(&m_csGdi, TRUE);
//		m_voiceSpectrum.Render(pApp->GetWaveIn()->GetFormatEx(), 0.0, 0.0);
//		RECT rect;
//		m_voiceSpectrum.GetPlacement(&rect);
		//InvalidateRect(&rect, FALSE);
  //      TRACE(_T("CCDView::OnUserMessage 1 slGdi.UnLock\n"));
        
//        pView->RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE | RDW_ALLCHILDREN);
    //    UpdateScreen(&rect, true);
      //  slGdi.Unlock();
    }
	else if(wParam == 7788)
	{
		ASSERT(FALSE);
        TRACE(_T("CCDView::OnUserMessage slGdi.Lock\n"));
//		CSingleLock slGdi(&m_csGdi, TRUE);
//		m_voiceSpectrum.Render(pApp->GetWaveIn()->GetFormatEx(), 0.0, 0.0);
//		RECT rect;
//		m_voiceSpectrum.GetPlacement(&rect);
		//InvalidateRect(&rect, FALSE);
  //      TRACE(_T("CCDView::OnUserMessage slGdi.UnLock\n"));
    //    slGdi.Unlock();
		//Render(&rect, TRUE);
      //  RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE | RDW_ALLCHILDREN);
		
		
	}

//	else if(wParam == XFM_RETURN_LOADED_IMAGE)
//	{
//		LPXFLOADIMAGESTRUCTURE lpLi = (LPXFLOADIMAGESTRUCTURE) lParam;
//		m_hBitmap = lpLi->m_hBitmap;
//		BkImageChangeStateMachine(BkImageChangeEventLoaded);
//		delete lpLi;
//	}

	else if(wParam == 33)
	{
//		m_freeImage = (LPVOID) lParam;
//		m_eventBkImageReady.PulseEvent();
//		m_pFreeImage = (FIBITMAP *) lParam;
//		BkImageChangeStateMachine(BkImageChangeEventLoaded);
        SetPlayingPosition_((TICKS) lParam);
	}
    else if(wParam == 1)
    {
        if(lParam == ID_PLAY)
        {
            OnPlay();
        }
    }
    else if(wParam == 17)
    {
        _ImageChangePostEvent((EImageChangeEvent) lParam);
    }
	else if(wParam == 18)
	{
		ASSERT(FALSE);
		if(lParam == 0)
		{
			_ImageChangeTransitionEffectRunStep();
		}
		else if(lParam == 3)
		{
			// BkImageEventFlagChanged:
			UpdateBuffer(false);
			UpdateScreen();
		}
		else if(lParam == 4)
		{
			// BkImageEventFlagChanged:
			UpdateBuffer(false);
			UpdateScreen();
		}
		

	}
    else if(wParam == 5)
    {
        bool bMakeVisible = lParam != 0;
        GetDocument()->Play(bMakeVisible);
    }
    else if(wParam == 201)
    {
        GetDocument()->OnUpdateProgress(NULL);
    }
    else if(wParam == 121314)
    {
        LPLYRICVIEWLINESHIFTEVENT plvlse = 
            (LPLYRICVIEWLINESHIFTEVENT) lParam;

        CLyricEventV1 event;

  		event.m_iType = 12;
		event.m_iCurrentToken = GetDocument()->m_iPlayingTokenIndex;
		event.m_iCurrentNote  = GetDocument()->m_iPlayingNoteIndex;
        event.m_iCurrentLine  = plvlse->nLine;

        m_dTextOffsetRate = plvlse->dRate;

		OnLyricEvent(&event, true); // cut proccessing

    }
    else if(wParam == 1213145)
    {
        LPLYRICVIEWLINESHIFTEVENT plvlse = 
            (LPLYRICVIEWLINESHIFTEVENT) lParam;
        CLyricEventV1 event;

  		event.m_iType = 71;
		event.m_iCurrentToken = GetDocument()->m_iPlayingTokenIndex;
		event.m_iCurrentNote  = GetDocument()->m_iPlayingNoteIndex;
        event.m_iCurrentLine  = plvlse->nLine;

        m_dTextOffsetRate = plvlse->dRate;

		OnLyricEvent(&event, true); // cut proccessing

    }
    else if(wParam == 1213146)
    {
        LPLYRICVIEWLINESHIFTEVENT plvlse = 
            (LPLYRICVIEWLINESHIFTEVENT) lParam;
        CLyricEventV1 event;

  		event.m_iType = 72;
		event.m_iCurrentToken = GetDocument()->m_iPlayingTokenIndex;
		event.m_iCurrentNote  = GetDocument()->m_iPlayingNoteIndex;
        event.m_iCurrentLine  = plvlse->nLine;

        m_dTextOffsetRate = plvlse->dRate;

		OnLyricEvent(&event, true); // cut proccessing

    }


    else if(wParam == 12131415)
    {
        CLyricEventV1 event;

  		event.m_iType = 14;
		event.m_iCurrentToken = GetDocument()->m_iPlayingTokenIndex;
		event.m_iCurrentNote  = GetDocument()->m_iPlayingNoteIndex;
        //event.m_iCurrentLine  = lParam;

		OnLyricEvent(&event, true); // cut proccessing

    }
    else if(wParam == 534231)
    {
        CXfplayerDoc * pdoc = GetDocument();        
        if(pdoc->GetMidiPlayer())
        {
            pdoc->GetMidiPlayer()->SetMidiOutDevice(CMidiCentral::GetMidiCentral()->m_uiMidiOutDevice);
        }
    }
	else if(wParam == 1945)
	{
		CWStr * pwstr = (CWStr *) lParam;
		TextDocHelperAdd(*pwstr);
		delete pwstr;
	}

	return 0;
}

void CCDView::OnStop() 
{
	// TODO: Add your command handler code here
	((CXfplayerDoc *)GetDocument())->Stop();
	if(m_lyricTemplateLines.GetSize() > 0)
	{
        //CCDViewLine objViewLine ;
		//CCDViewLine & refViewLine = objViewLine;
//        CCDViewLine * lpViewLine = NULL;
//		int i, iLineIndex;
//		for(i = 0; i < m_lyricTemplateLines.GetSize() ; i++)
//		{
//	        if(0 <= (iLineIndex = m_lyricLines.GetAt(
  //              &lpViewLine,
    //            m_lyricTemplateLines,
      //          i)))
        //    {
          //      lpViewLine->SetStatus(CCDViewLine::StatusEmpty);
			//}
			
		//}

        // Apaga todas as linhas visíveis
         int iStartIndex, iEndIndex;
        iStartIndex = m_lyricLines.GetFirstVisibleLineIndex();
        if(iStartIndex < 0)
            iStartIndex = 0;
        if(iStartIndex >= m_lyricLines.GetSize())
            iStartIndex = m_lyricLines.GetSize() - 1;
        iEndIndex = m_lyricLines.GetLastVisibleLineIndex();
        if(iEndIndex < iStartIndex)
            iEndIndex = iStartIndex;
        if(iEndIndex >= m_lyricLines.GetSize())
            iEndIndex = m_lyricLines.GetSize() - 1;

		//TRACE(_T("m_lyricLines.GetFirstVisibleLineIndex() = %d\n"), iStartIndex);
        bool bClear = false;
		for(int i = iEndIndex; i >= iStartIndex; i--)
		{
            if(i >= 0 &&
                i < m_lyricLines.GetSize())
            {
           CLyricViewLine * lpViewLine = &m_lyricLines.ElementAt(i);
           if(lpViewLine->GetVisible())
           {
               lpViewLine->SetVisible(false);
           }
            }
		}

	}

	UpdateBuffer(false);
    UpdateScreen();
	UpdateTime();

	
}

void CCDView::OnPause() 
{
	// TODO: Add your command handler code here
	((CXfplayerDoc *)GetDocument())->Pause();
	UpdateTime();
}

void CCDView::OnTimer(UINT nIDEvent) 
{
    CSingleLock slTimer(&m_csTimer, TRUE);
//	TRACE(_T("CCDView::OnTimer current thread %X\n"), GetCurrentThreadId());
	// TODO: Add your message handler code here and/or call default
//    TRACE("CCDView::OnTimer");
  //      TRACE(" IN");
//    MSG msg;
//    while(PeekMessage(
//        &msg, 
//        m_hWnd,
//        WM_TIMER,
//        WM_TIMER,
//        PM_NOREMOVE) &&
//        msg.wParam == 1)
//    {
//        PeekMessage(
//        &msg, 
//        m_hWnd,
//        WM_TIMER,
//        WM_TIMER,
//        PM_REMOVE);
//        ASSERT(msg.wParam == 1);
//        ASSERT(msg.message == WM_TIMER);
//        TRACE("*");
//    }
    
  //  TRACE("\n");
//    return;
    if(!m_bInitialized)
        return;

    if(!::IsWindow(m_hWnd))
        return;
    

	CVmpApp *pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
    CMidiSequence * pSeq = pDoc->HelperGetMidiSequence();
//    if(pDoc->GetMidiPlayer())
  //  {
	//    pSeq = pDoc->HelperGetMidiSequence();
    //}
//	ASSERT(pSeq != NULL);
    _ImageChangePostEvent(BkImageEventTimer);
    DWORD dwTime = timeGetTime();

	static DWORD ls_dwLastTime100 = timeGetTime();
	static DWORD ls_dwLastTime1000 = timeGetTime();
	if(nIDEvent == 1)
	{
		if(dwTime - ls_dwLastTime100 > 100)
		{
			ls_dwLastTime100 = dwTime;
			if(dwTime - ls_dwLastTime1000 > 1000)
			{
				ls_dwLastTime1000 = dwTime;
				if(m_pthreadTransitionEffectRunStep == NULL)
					m_pthreadTransitionEffectRunStep = CreateTransitionEffectRunStepThread();
			}
		}

		if(dwTime - m_dwLastTime1 >= 75)
		{
			if(pSeq &&
				!pDoc->IsOpening() &&
				!pDoc->IsClosing() &&
				(pSeq->GetState() == CMidiSequence::StatusPlaying ||
				pSeq->GetState() == CMidiSequence::StatusStopping))
			{
				CLyricEventV1 event;
				event.m_iType = 3;
				event.m_iCurrentToken = GetDocument()->m_iPlayingTokenIndex;
				event.m_iCurrentNote  = GetDocument()->m_iPlayingNoteIndex;
				OnLyricEvent(&event, true); // cut proccessing
				if(dwTime >= (DWORD) (m_dwTimeLastUpdateTime + 1000) &&
					m_dwTimeLastUpdateTime >= 0)
				{
					UpdateTime(); //cut processing
					m_dwTimeLastUpdateTime = dwTime;
					
				}
				if(dwTime >= (DWORD) (m_dwSliderLastUpdateTime + 500))
				{
					SendMessage(WM_USER, 201);//cut processing
				}
				
			}
		}

		if(dwTime - m_dwLastTime1 >= 100)
		{
		if(m_bHoverTimer
			&& timeGetTime() > m_dwHoverTimer + 1000)
		{
			m_bHoverTimer = false;
		}
		if(m_bPendingFullBufferUpdate)
		{
			if(UpdateBuffer(false))
				UpdateScreen();
		}

        m_dwLastTime1 = dwTime;
//        if(dwTime - m_dwLastTimer1 < 50)
  //          return;
//        if(dwTime - m_dwLastTimer1 > 70)
  //      {
    //        if(dwTime - m_dwLastTimer1 > 300)
      //      {
        //        m_dwLastTimer1 = dwTime;
          ////  }

        //return;
        //}
    
        m_dwLastTimer1 = dwTime;
        //const MSG * lpcmsg = GetCurrentMessage();
        
        //if(dwTime - lpcmsg->time > 50)
          
        //return;

        //TRACE(_T("CCDView::OnTimer slGdi.Lock\n"));
        CSingleLock slGdi(&m_csGdi, true);
        //CDC * pdcForeground = TwiGetDC();
		CDC * pdcForeground = &m_dcScreen;
//        CRgn rgn;
  //      rgn.CreateRectRgn(0, 0, 0, 0);
        //static int iSongLabelAnimate = 0;
        //if(iSongLabelAnimate == 0)
        CTypedPtrArray <CObArray, CBaseRgn *> rgna;
        m_lineSongLabel.OnTimerAnimate(
            pdcForeground,
            &rgna);
        //iSongLabelAnimate++;
        //if(iSongLabelAnimate > 5)
          //  iSongLabelAnimate = 0;
        //Render(&rgn, TRUE);
        //TRACE(_T("CCDView::OnTimer slGdi.UnLock\n"));
        //TwiReleaseDC(pdcForeground);
        UpdateScreen(&rgna, true);

        slGdi.Unlock();
        //CRect rgnBox;
//        rgn.GetRgnBox(rgnBox);
  //      if(!rgnBox.IsRectNull())
    //    {
      //     RedrawWindow(NULL, &rgn, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE | RDW_ALLCHILDREN);
        //}

		
//		if(m_pThreadBkImageChange)
//		{
//			DWORD status;
//			::GetExitCodeThread(m_pThreadBkImageChange->m_hThread, &status);
		//PostMessage(WM_USER, 17, BkImageChangeEventTimer);
//		}
		if(!m_bBackgroundUpdateTimerOn &&
            dwTime >= (DWORD) (m_dwScoreLastUpdateTime + 1000))
		{
            double dScoreRate = pDoc->GetScoreRate();
			if(dScoreRate != m_dScoreRate)
			{
				m_dScoreRate = dScoreRate;
				RedrawScore(false);
			}


            m_dwScoreLastUpdateTime = dwTime;
		}
//		if(m_bOnSizeUpdateTimerOn)
  //      {
    //        m_bOnSizeUpdateTimerOn = false;
      //  }
        if(m_bBackgroundUpdateTimerOn && 
            timeGetTime() 
			- m_dwBackgroundUpdateTimeIn 
				> m_dwBackgroundUpdateTimeOut )
        {
            m_bBackgroundUpdateTimerOn = false;
            UpdateBuffer(false);
            UpdateScreen();
        }
//		if(timeGetTime() >= (DWORD) (m_dwOnSizeUpdateTimeIn + m_dwOnSizeUpdateTimeOut))
//		{
//			m_bOnSizeUpdateTimerOn = false;
//			CVmpApp * pApp = (CVmpApp *) AfxGetApp();
//			CXfplayerThreadV3 * pThreadV3 = pApp->GetThreadV3();
//	//		pThreadV1->OnLyricViewSize(1, cx, cy);
//			pThreadV3->PostThreadMessage(WM_USER, 2, 1);
//			
//		}
        if(pDoc->IsWaitingToPlay())
        {
            if(timeGetTime() > pDoc->GetPlayTimeOut())
            {
                pDoc->SetWaitingToPlay(false);
                SendMessage(WM_USER, 12131415);
                CFrameWnd * pMainFrame = GetParentFrame();
                CMidiSequence * pMidiSequence = pDoc->GetMidiPlayer()->GetSequence();
	            ASSERT(pMidiSequence != NULL);
                CXfplayerScoring * pScoring = pDoc->GetScoring();
                ASSERT(pScoring != NULL);
                double dRate =	pDoc->GetProgressRate();
 	            try
	            {
		                pDoc->GetMidiPlayer()->SetMessageWindow(m_hWnd);
		                pDoc->GetMidiPlayer()->Play(dRate);
						pDoc->GetMidiPlayer()
							->GetSequence()
							->GetFile()
							->m_fdwSMF &= ~CMidiFile::FlagDisablePlayLevel1Operations;
						pDoc->GetMidiPlayer()
							->GetSequence()
							->GetFile()
							->m_ptracks
							->m_fdwSMF &= ~CMidiFile::FlagDisablePlayLevel1Operations;
	                }
	                catch(CMidiException * pe)
	                {
		                CErrorDialog ed;
		                ed.Initialize(pe);
		                ed.DoModal();
//		                pApp->SetPlayingDocument(NULL);
		                pe->Delete();
		                return;
	                }
                    pDoc->StartScoring(true);
	                
	                SetTitleVisible(false);
	                UpdateTitle();

            }
        }
	}
	else if(nIDEvent == CVmpTimer::ID_HOVER)
	{
		m_dwHoverTimer = timeGetTime();
	}
	}
//    TRACE(" OUT\n");
//	CView::OnTimer(nIDEvent);
    
//	TRACE(_T("CCDView::OnTimer 5000\n"));
}

VMSRESULT CCDView::LoadImageSync(LPCTSTR lpcszImage)
{
    
    HBITMAP hBitmap = CImaging::LoadImageSync(lpcszImage);
            TRACE(_T("CCDView::OnLoadImageSyn slGdi.Lock\n"));

    CSingleLock slGdi(&m_csGdi, TRUE);
	if(m_bmpSource.m_hObject != NULL)
		m_bmpSource.DeleteObject();
	m_bmpSource.Attach(hBitmap);
    TRACE(_T("CCDView::OnLoadImageSyn slGdi.UnLock\n"));
	slGdi.Unlock();
	_ImageChangePostEvent(BkImageEventLoaded);
    return VMSR_SUCCESS;

}

VMSRESULT CCDView::LoadImageSync()
{
    return LoadImageSync(m_strCurrentImagePath);
}

VMSRESULT CCDView::LoadImageAsynch()
{
    return LoadImageAsynch(m_strCurrentImagePath);
}

VMSRESULT CCDView::LoadImageAsynch(CString strPath)
{
    CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	LPLOADIMAGESTRUCTURE lpli = new LOADIMAGESTRUCTURE;
    lpli->m_lpImagePath = _tcsdup(strPath);
    m_strNextImagePath = strPath;
    //m_evImageLoad.ResetEvent();
    ((CXfplayerThreadV3 *)pApp->GetThreadV3())->m_evInitialized.Lock();
	pApp->GetThreadV3()->PostThreadMessage(WM_USER, 5, (LPARAM) lpli);
    return VMSR_SUCCESS;
}

BOOL CCDView::LoadNextImage(bool bSynch)
{
	CDBCentral * pdb = DB();

	CWStr wstrPath;

	wstrPath.SetOEM(m_strCurrentImagePath);
	wstrPath =	pdb->GetNextImagePath(wstrPath);
	CInternational::UnicodeToOEM(m_strNextImagePath, wstrPath);

	m_bLastLoadImageSynch = bSynch;
	if(bSynch)
		return LoadImageSync(m_strNextImagePath);
	else
		return LoadImageAsynch(m_strNextImagePath);
}

BOOL CCDView::ChangeBackgroundImage(bool bRedraw)
{
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	CXfplayerThreadV1 * pThreadV1 = (CXfplayerThreadV1 *) pApp->GetThreadV1();
	CXfplayerThreadV3 * pThreadV3 = (CXfplayerThreadV3 *) pApp->GetThreadV3();
    CDBCentral * pDataCentral = DB();
    CDBLongSet * pLongsSet = pDataCentral->GetDBLongSet();
    int iBkImageFlags;
    int iEconoMode = CSavings::AppGetEconoMode();
    
//	if(m_pFreeImage == NULL)
//		return FALSE;
//	if(pThreadV1->m_pfiBitmap == NULL)
//		return FALSE;
	HBITMAP hBitmap = NULL;
	{
        TRACE(_T("CCDView::ChangeBackgroundImage 1 slGdi.Lock\n"));
        CSingleLock slGdi(&m_csGdi, TRUE);
        hBitmap = (HBITMAP) pThreadV3->GetBitmap()->Detach(); 

        TRACE(_T("CCDView::ChangeBackgroundImage 1 slGdi.UnLock\n"));
		slGdi.Unlock();
	}
	if(hBitmap != NULL)
	{
        m_strCurrentImagePath = m_strNextImagePath;
        
		// if OnSizeUpdate timer is on, OnSizeUpdate is not
		// will be need triggered by the timer, because
		// it is being indirectly called here.
//		if(m_bOnSizeUpdateTimerOn)
//			m_bOnSizeUpdateTimerOn  = false;
        TRACE(_T("\nCCDView::ChangeBackgroundImage A before lock %X\n"), GetCurrentThreadId());
    
        TRACE(_T("CCDView::ChangeBackgroundImage 2 slGdi.Lock\n"));
        CSingleLock slGdi(&m_csGdi, true);

		//slGdi.Lock();
        TRACE(_T("\nCCDView::ChangeBackgroundImage A after lock %X\n"), GetCurrentThreadId());
		
		HBITMAP hBmpOld = (HBITMAP) m_bmpSource.Detach();
		m_bmpSource.Attach(hBitmap);
        CBitmap * pbmpOld  = m_dcSource.SelectObject(&m_bmpSource);
        if(!pbmpOld)
        {
	        TRACE(_T("GetLastError%d"), GetLastError());
		    TRACE0("Mem Bitmap not selected.\n");
		    TRACELASTERROR();
        }
        else
        {
            ASSERT(hBmpOld == pbmpOld->GetSafeHandle());

        }
		if(!DeleteObject(hBmpOld))
		{
			TRACE1("Failed to delete old template bitmap image.\nGetLastError() returned: %d.\n", GetLastError());
		}
        if(pLongsSet->Load(_T("Imagens"), m_strCurrentImagePath + _T(".Flags"), &iBkImageFlags))
        {
            m_iBkImageFlags = iBkImageFlags;
        }
        else
        {
            BITMAP bm;
            if(!m_bmpSource.GetObject(sizeof(bm), &bm))
            {
                m_iBkImageFlags = ifZoomAll;
            }
            else
            {
                if(bm.bmWidth < (GetSystemMetrics(SM_CXSCREEN) / 2) ||
                    bm.bmHeight < (GetSystemMetrics(SM_CYSCREEN) / 2))
                {
                    m_iBkImageFlags = ifTile;
                }
                else
                {
                    m_iBkImageFlags = ifZoomAll;
                }

            }
        }
        TRACE(_T("CCDView::ChangeBackgroundImage 2 slGdi.Lock\n"));
		slGdi.Unlock();
        
//		TRACE(_T("Bitmap file name: %s\n"), strFileName);
//		RECT rect;
//		GetClientRect(&rect);
		//UpdateBackgroundImage(rect.right, rect.bottom);
//		pThreadV3->PostThreadMessage(WM_USER, 2, 2);
//		CDC *pDC = GetDC();
//		OnDraw(NULL);
//		ReleaseDC(pDC);
		//InvalidateRect(&rect, FALSE);
//		Render(&rect);
//		m_mutexBkImageChange.Unlock();
        if(bRedraw)
        {
            UpdateBuffer(false);
            UpdateScreen();
        }
		return TRUE;
	}
	else
	{
       TRACE(_T("\nCCDView::ChangeBackgroundImage B hBitmap == NULL before lock %X\n"), GetCurrentThreadId());

        m_strCurrentImagePath = m_strNextImagePath;
        if(m_bmpSource.m_hObject != NULL)
        {
    //		pThreadV3->PostThreadMessage(WM_USER, 2, 2);
            if(pLongsSet->Load(_T("Imagens"), m_strCurrentImagePath + _T(".Flags"), &iBkImageFlags))
            {
                m_iBkImageFlags = iBkImageFlags;
            }
            else
            {
                BITMAP bm;
                if(!m_bmpSource.GetObject(sizeof(bm), &bm))
                {
                    m_iBkImageFlags = ifZoomAll;
                }
                else
                {
                    if(bm.bmWidth < (GetSystemMetrics(SM_CXSCREEN) / 2) ||
                        bm.bmHeight < (GetSystemMetrics(SM_CYSCREEN) / 2))
                    {
                        m_iBkImageFlags = ifTile;
                    }
                    else
                    {
                        m_iBkImageFlags = ifZoomAll;
                    }

                }
            }
        }
        if(bRedraw)
        {
            UpdateBuffer(false);
            UpdateScreen();
        }
		return TRUE;
	}
    //m_evImageLoad.SetEvent();
    


}

bool CCDView::UpdateBuffer(
    int cx,
    int cy,
    bool bFastUpdate,
    LPRECT lprect)
{

    if(!m_bInitialized)
        return false;

    CRect rectClient;
	rectClient.left = 0;
	rectClient.top = 0;
	rectClient.right = cx;
	rectClient.bottom = cy;

    CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    if(pApp == NULL)
    {
        // if main application is null, there's no reason
        // for painting anything...
        return false;
    }
    ASSERT(pApp != NULL);
    
    int iEconoMode = CSavings::AppGetEconoMode();

	//CFrameWnd * pframe = GetParentFrame();
    //if(pframe == NULL)
    //{
        // if main frame is null, there's no reason
        // for painting anything...
      //  return false;
    //}

    if(bFastUpdate)
    {
        return true;
    }

    if(cx <= 0 || cy <= 0)
        return true;

    //ASSERT(pframe != NULL);
	//CXfplayerDoc *pDoc = GetDocument();
	//ASSERT(pDoc != NULL); // if document is null, there's something wrong

    
    //CMidiSequence *pSeq = NULL;
    //if(pDoc->GetMidiPlayer())
    //{
	  //  pSeq = pDoc->HelperGetMidiSequence();
    //}

    
    //CMidiFile * pfile = NULL;
    //if(pSeq)
    //{
      //   pfile = pSeq->GetFile();
    //}
	

//	CDBCentral * pDataCentral = DB();

    //CRect rectPlaylist;
    //if(m_pplaylistipwnd != NULL)
	//if(m_pplaylistframe != NULL)
    //{
        //m_pplaylistipwnd->GetWindowRect(rectPlaylist);
	//	m_pplaylistframe->GetWindowRect(rectPlaylist);
      //  ScreenToClient(rectPlaylist);
    //}

	if(!::IsWindow(m_hWnd))
		return false;


    CSingleLock slGdi(&m_csGdi, true);

	const int ciBufferBitmapNotCreated = 1;
	const int ciBackBitmapNotCreated = 2;
	const int ciBufferBitmapNotSelected = 3;
	const int ciBackBitmapNotSelected = 4;
	const int ciBufferBitmapInfoNotAvailable = 5;
	const int ciScaledBitmapInfoNotAvailable = 6;
    CRect rectUpdate(0, 0, cx, cy);
	m_transitioneffect.UpdateBuffer(rectUpdate);
/*	try
	{	
//		BITMAP bmBuffer;
//		if(!CreateBitmap(
//			&m_dcBuffer,
//			&m_bmpBufferOld,
//			&m_bmpBuffer,
//			&bmBuffer,
//			cx, cy))
//			throw 0;

		ASSERT(m_dcBack.GetSafeHdc() != NULL);
			
		ASSERT(m_bmpBack.GetSafeHandle() != NULL);


		//BITMAP bmBack;
/*		if(!CreateBitmap(
			&m_dcBack,
			&m_bmpBackOld,
			&m_bmpBack,
			&bmBack,
			cx, cy))
			throw 0;*/

    
/*		if(m_bmpBack2.m_hObject != NULL)
		{

            BITMAP bmBack2;
			if(!m_bmpBack2.GetBitmap(&bmBack2))
			{
				TRACE0("Mem Bitmap info not available.\n");
				throw ciScaledBitmapInfoNotAvailable;
			}

            if(m_etransitioneffect == TransitionEffectSquaryPixelate
				|| m_etransitioneffect == TransitionEffectCirclyPixelate)
			{
				int finalX = 0;
				int finalY = 0;
				int finalW = cx;
				int finalH = cy;
            
				const int tilesx = max(4, cx / 96);
				const int tilesy = max(4, cy / 96);
				const int tiles = tilesx * tilesy;

				if(m_iTransitionEffectStep > 0)
				{
					if(m_iaTransitionEffect.GetSize() <= 0 &&
						m_iTransitionEffectStep == 1)
					{
						m_iaTransitionEffect.EnsureSize(tiles);
						for(int i = 0; i < tiles; i++)
						{
							m_iaTransitionEffect.ElementAt(i) = i;
						}
					}
					if(m_iaTransitionEffect.GetSize() > 0)
					{
						int iIndex = m_math.RandRange(
							0,
							m_iaTransitionEffect.GetSize() - 1);

//						SendMessage(WM_USER, USERMESSAGE_WPARAM_RAND_LPINT, (LPARAM) &iRand);

/*						int iIndex =
							m_math.LinearMap(
								0, m_iaTransitionEffect.GetSize() - 1,
								iRand, 0, RAND_MAX);*/
/*						if(m_iTransitionEffectStep <= 0)
							goto Skip1;
						int iStep = 0;
						try
						{
							iStep = m_iaTransitionEffect.ElementAt(iIndex);
							if(m_iTransitionEffectStep <= 0)
								goto Skip1;
							m_iaTransitionEffect.RemoveAt(iIndex);
						}
						catch(...)
						{
							goto Skip1;
						}
            
						int i = iStep % tilesx;
						int j = iStep / tilesx;
						double dUpdateH = (double) finalH / tilesy;
						double dUpdateW = (double) finalW / tilesx;
						double dX = dUpdateW * i;
						double dY = dUpdateH * j;
						rectUpdate.SetRect(
							(int) dX, 
							(int) dY, 
							(int) (dX + dUpdateW + 1.0),
							(int) (dY + dUpdateH + 1.0));
				}
					else
					{
						rectUpdate.SetRect(finalX, finalY, finalX + finalW, finalY + finalH);
					}
					if(lprect != NULL)
					{
						*lprect = rectUpdate;
					}
                
					CRgn rgnClip;
					if(m_etransitioneffect == TransitionEffectCirclyPixelate)
					{
						CRect rectEllipse;
						FindRandomEnglobingCircle(rectUpdate, rectEllipse, 64);
						rectUpdate = rectEllipse;
						rgnClip.CreateEllipticRgnIndirect(rectUpdate);
						m_dcBack.SelectClipRgn(&rgnClip);
						m_dcBack.BitBlt(
						   rectUpdate.left, rectUpdate.top,
						   rectUpdate.Width(), rectUpdate.Height(),
						   &m_dcBack2,
						   rectUpdate.left, rectUpdate.top,
						   SRCCOPY);
						m_dcBack.SelectClipRgn(NULL);
					}
					else
					{
						m_dcBack.BitBlt(
						   rectUpdate.left, rectUpdate.top,
						   rectUpdate.Width(), rectUpdate.Height(),
						   &m_dcBack2,
						   rectUpdate.left, rectUpdate.top,
						   SRCCOPY);

					}
					
				}
			}
			else if(
				m_etransitioneffect == TransitionEffectLinearFadingBottomTop
				|| m_etransitioneffect == TransitionEffectLinearFadingTopBottom
				|| m_etransitioneffect == TransitionEffectLinearFadingLeftRight
				|| m_etransitioneffect == TransitionEffectLinearFadingRightLeft)
			{
				int finalX = 0;
				int finalY = 0;
				int finalW = cx;
				int finalH = cy;

				const int iTileCount = max(4, cy / 32);
				const int iFrameCount = 16;

				int iIndex = m_iTransitionEffectStep - 1;
				int iTile = iIndex % iTileCount;
				int iFrame = iIndex / iTileCount;
        
				if(m_iTransitionEffectStep > 0)
				{
					if(m_iaTransitionEffect.GetSize() <= 0 &&
						m_iTransitionEffectStep == 1
						&& m_iTransitionEffectStepCount < 0)
					{
						m_iTransitionEffectStepCount = iTileCount * iFrameCount + 1;
					}
					if(m_iTransitionEffectStepCount > 0)
					{
						switch(m_etransitioneffect)
						{
						case TransitionEffectLinearFadingTopBottom:
							{
								rectUpdate.left = 0;
								rectUpdate.right = rectUpdate.left + cx;
								rectUpdate.top = iTile * cy / iTileCount;
								rectUpdate.bottom = (iTile + 1) * cy / iTileCount;
							}
							break;
						case TransitionEffectLinearFadingBottomTop:
							{
								rectUpdate.left = 0;
								rectUpdate.right = rectUpdate.left + cx;
								rectUpdate.top = (iTileCount - iTile) * cy / iTileCount;
								rectUpdate.bottom = (iTileCount - iTile + 1) * cy / iTileCount;
							}
							break;
						case TransitionEffectLinearFadingLeftRight:
							{
								rectUpdate.left =  iTile * cy / iTileCount;
								rectUpdate.right =  (iTile + 1) * cy / iTileCount;
								rectUpdate.top = 0;
								rectUpdate.bottom = rectUpdate.top + cy;;
							}
							break;
						case TransitionEffectLinearFadingRightLeft:
							{
								rectUpdate.left =  (iTileCount - iTile) * cy / iTileCount;
								rectUpdate.right =  (iTileCount - iTile + 1) * cy / iTileCount;
								rectUpdate.top = 0;
								rectUpdate.bottom = rectUpdate.top + cy;;
							}
							break;
						}
					}
				}
				else
				{
					rectUpdate.SetRect(finalX, finalY, finalX + finalW, finalY + finalH);
				}
				if(lprect != NULL)
				{
					*lprect = rectUpdate;
				}
				
				
            

				//int iFrameComplement = iFrameCount - iFrame;
				//int iFrameExp = iFrameComplement * iFrameComplement * iFrameComplement;
				int iFrameStd = iFrame * 2;
				int iFrameStdEx = iFrameStd * iFrameStd * iFrameStd;
				int iFrameStdCount = iFrameCount;
				int iFrameCountStdEx = iFrameStdCount * iFrameStdCount * iFrameStdCount;
				double dAlpha = m_math.LinearMap(
					(double) 35, (double) 255,
					(double) iFrameStdEx,
					(double) 0, (double) iFrameCountStdEx);
				dAlpha /= 8.0;
				pimaging->ColorBlend(
					&m_dcBack,
					rectUpdate.left,
					rectUpdate.top,
					rectUpdate.Width(),
					rectUpdate.Height(),
					&m_dcBack2,
					rectUpdate.left,
					rectUpdate.top,
					(BYTE) dAlpha);
			}
			else if(
				m_etransitioneffect == TransitionEffectFlyInBottomTop
				|| m_etransitioneffect == TransitionEffectFlyInTopBottom
				|| m_etransitioneffect == TransitionEffectFlyInLeftRight
				|| m_etransitioneffect == TransitionEffectFlyInRightLeft)
			{
				int finalX = 0;
				int finalY = 0;
				int finalW = cx;
				int finalH = cy;

				const int iFrameCount = 16;

				

				int iFrame = m_iTransitionEffectStep - 1;
				double  dFrameStd = 1.0 - ((double) iFrame / iFrameCount);
				double dRate = 1.0 - dFrameStd * dFrameStd;
        
				if(m_iTransitionEffectStep > 0)
				{
					if(m_iaTransitionEffect.GetSize() <= 0 &&
						m_iTransitionEffectStep == 1 &&
						m_iTransitionEffectStepCount < 0)
					{
						m_iTransitionEffectStepCount = iFrameCount + 1;
						m_dwTransitionEffectDelay = 50;
					}
					if(m_iTransitionEffectStepCount > 0)
					{
						switch(m_etransitioneffect)
						{
						case TransitionEffectFlyInTopBottom:
							{
								rectUpdate.left = 0;
								rectUpdate.right = rectUpdate.left + cx;
								rectUpdate.top = 0;
								rectUpdate.bottom = (long) dRate * cy;
							}
							break;
						case TransitionEffectFlyInBottomTop:
							{
								rectUpdate.left = 0;
								rectUpdate.right = rectUpdate.left + cx;
								rectUpdate.top = (long) ((1.0 - dRate) * cy);
								rectUpdate.bottom = cy;
							}
							break;
						case TransitionEffectFlyInLeftRight:
							{
								rectUpdate.left =  0;
								rectUpdate.right =  (long) (dRate * cy);
								rectUpdate.top = 0;
								rectUpdate.bottom = rectUpdate.top + cy;;
							}
							break;
						case TransitionEffectFlyInRightLeft:
							{
								rectUpdate.left =  (long) ((1.0 - dRate) * cy);
								rectUpdate.right =  cy;
								rectUpdate.top = 0;
								rectUpdate.bottom = rectUpdate.top + cy;;
							}
							break;
						}
					}
				}
				else
				{
					rectUpdate.SetRect(finalX, finalY, finalX + finalW, finalY + finalH);
				}
				if(lprect != NULL)
				{
					*lprect = rectUpdate;
				}
				
				//CImaging * pimaging = CImaging::GetImaging();
            

				m_dcBack.BitBlt(
					rectUpdate.left,
					rectUpdate.top,
					rectUpdate.Width(),
					rectUpdate.Height(),
					&m_dcBack2,
					0,
					0,
					SRCCOPY);
			}
			else if(
				m_etransitioneffect == TransitionEffectWipeBottomTop
				|| m_etransitioneffect == TransitionEffectWipeTopBottom
				|| m_etransitioneffect == TransitionEffectWipeLeftRight
				|| m_etransitioneffect == TransitionEffectWipeRightLeft)
			{
				int finalX = 0;
				int finalY = 0;
				int finalW = cx;
				int finalH = cy;

				const int iTileCount = max(4, cy / 32);

				int iIndex = m_iTransitionEffectStep - 1;
				int iTile = iIndex;
        
				if(m_iTransitionEffectStep > 0)
				{
					if(m_iaTransitionEffect.GetSize() <= 0 &&
						m_iTransitionEffectStep == 1)
					{
						m_iTransitionEffectStepCount = iTileCount + 1;
					}
					if(m_iTransitionEffectStepCount > 0)
					{
						switch(m_etransitioneffect)
						{
						case TransitionEffectWipeTopBottom:
							{
								rectUpdate.left = 0;
								rectUpdate.right = rectUpdate.left + cx;
								rectUpdate.top = iTile * cy / iTileCount;
								rectUpdate.bottom = (iTile + 1) * cy / iTileCount;
							}
							break;
						case TransitionEffectWipeBottomTop:
							{
								rectUpdate.left = 0;
								rectUpdate.right = rectUpdate.left + cx;
								rectUpdate.top = (iTileCount - iTile) * cy / iTileCount;
								rectUpdate.bottom = (iTileCount - iTile + 1) * cy / iTileCount;
							}
							break;
						case TransitionEffectWipeLeftRight:
							{
								rectUpdate.left =  iTile * cy / iTileCount;
								rectUpdate.right =  (iTile + 1) * cy / iTileCount;
								rectUpdate.top = 0;
								rectUpdate.bottom = rectUpdate.top + cy;;
							}
							break;
						case TransitionEffectWipeRightLeft:
							{
								rectUpdate.left =  (iTileCount - iTile) * cy / iTileCount;
								rectUpdate.right =  (iTileCount - iTile + 1) * cy / iTileCount;
								rectUpdate.top = 0;
								rectUpdate.bottom = rectUpdate.top + cy;;
							}
							break;
						}
					}
				}
				else
				{
					rectUpdate.SetRect(finalX, finalY, finalX + finalW, finalY + finalH);
				}
				if(lprect != NULL)
				{
					*lprect = rectUpdate;
				}
				
				m_dcBack.BitBlt(
					rectUpdate.left,
					rectUpdate.top,
					rectUpdate.Width(),
					rectUpdate.Height(),
					&m_dcBack2,
					rectUpdate.left,
					rectUpdate.top,
					SRCCOPY);
			}
		}
	Skip1:;

    }
    catch(int)
    {
    }*/

				
	CImaging * pimaging = CImaging::GetImaging();

	
	if(m_lineSongLabel.m_bVisible)
	{
		CRect rectSongLabel;
		m_lineSongLabel.GetPlacement(rectSongLabel);
		if(rectSongLabel.IntersectRect(rectSongLabel, rectUpdate))
		{
			pimaging->ColorBlend(
				&m_dcBack,
				rectSongLabel.left,
				rectSongLabel.top,
				rectSongLabel.Width(),
				rectSongLabel.Height(),
				RGB(240, 255, 240),
				150);

		}
	}
    if(lprect != NULL)
    {
        *lprect = rectUpdate;
    }
	//RenderView(&m_dcBuffer, rectUpdate, NULL, true);
    slGdi.Unlock();

	m_transitioneffect.TestEnd();
	return true;
}

void CCDView::OnDestroy() 
{
	if(m_pthreadTransitionEffectRunStep != NULL)
	{
		::TerminateThread(m_pthreadTransitionEffectRunStep->m_hThread, -1);
		m_pthreadTransitionEffectRunStep = NULL;
	}

	m_bDestroy = true;

	CVmpApp * papp = (CVmpApp *) AfxGetApp();
	CXfplayerThreadV3 * pthreadv3 = (CXfplayerThreadV3 *) papp->GetThreadV3();
	pthreadv3->m_bBkImageEnable = false;

	//if(m_pkcs1wndAudioSpectrum != NULL)
	//{
	//	ShowAudioSpectrum(false);
	//}

	

    if(m_pplaylistframe != NULL)
    m_pplaylistframe->PostMessage(WM_CLOSE);

    TRACE(_T("CCDView::OnDestroy"));
	((CTimerCallback *)this)->Enable(false);
    //if(!((CTimerCallback *)this)->m_pTimerWnd->m_evFree.Lock();

	CView::OnDestroy();

	// TODO: Add your specialized code here and/or call the base class
    CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    CXfplayerThreadV1 * pThreadV1 = (CXfplayerThreadV1 *) pApp->GetThreadV1();
    //if(GetCurrentThread() == pThreadV1->m_hThread)
    //{
        pThreadV1->DeleteTimerWnd(m_ptimerwnd);
    //}
    //else
    //{
      //  pThreadV1->PostThreadMessage(VMSM_V001, NOTIFY_TIMERCALLBACKDELETETIMER, (LPARAM) m_pTimerWnd);
    //}
	m_csGdi.Lock();
    if(m_dcSource.GetSafeHdc() != NULL)
        m_dcSource.SelectObject(&m_bmpSourceOld);
	m_dcBack.SelectObject(&m_bmpBackOld);
//	pdc->SelectObject(&m_bmpBufferOld);
    if(m_dcBack2.GetSafeHdc() != NULL)
        m_dcBack2.SelectObject(&m_bmpBack2Old);
//    if(m_pedit != NULL)
  //      delete m_pedit;
    m_csGdi.Unlock();

	
	// TODO: Add your message handler code here
//	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    VERIFY(
            VMS_SUCCEEDED(DB()->GetDBStringSet()->Save(_T("Images"), _T("CurrentPath"), m_strCurrentImagePath)));

//    pApp->GetThreadV1()->PostThreadMessage(
  //      WM_NULL,
    //    0,
      //  0);
    //pApp->GetThreadV1()->EnableTimers(false);

//    pApp->GetThreadV1()->PostThreadMessage(
  //      WM_USER_NOTIFY,
    //    NOTIFY_TIMERCALLBACKDELETETIMER,
      //  (LPARAM) m_pTimerWnd);
//    m_pTimerWnd->SendMessage(WM_CLOSE);
  //  while(!m_evTimerWndDeleted.Lock(0))
    //    ::Sleep(0);

	if(m_uiTimer)
	{
		KillTimer(m_uiTimer);
		m_uiTimer = 0;
	}
}

bool CCDView::UpdateBuffer(bool bFastUpdate, LPRECT lprect)
{
    if(!m_bInitialized)
        return false;

	if(!m_transitioneffect.IsInTransition())
	{
		if(timeGetTime()
			- m_dwLastFullBufferUpdate
			< 50
			)
		{
			m_bPendingFullBufferUpdate = true;
			return false;
		}
	}
	m_bPendingFullBufferUpdate = false;
    
	RECT rect;
	GetClientRect(&rect);
	bool bRet = UpdateBuffer(rect.right,rect.bottom, bFastUpdate, lprect);

	if(!m_transitioneffect.IsInTransition())
	{
		m_dwLastFullBufferUpdate = timeGetTime();
	}

	return bRet;

}

void CCDView::UpdateScreen()
{
    if(!m_bInitialized)
        return;

	RECT rect;
	GetClientRect(&rect);
	UpdateScreen(&rect);
}

// lprect should be in client coordinates
void CCDView::UpdateScreen(LPRECT lprect)
{
    if(!m_bInitialized)
        return;
    TwiRedraw(lprect);
}

void CCDView::UpdateTime()
{
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    CFrameWnd *pframe = GetParentFrame();
	if(!pframe->IsKindOf(RUNTIME_CLASS(CKaraokeSDIFrame)))
		return;
	CKaraokeSDIFrame * psdiframe = (CKaraokeSDIFrame * ) pframe;
	//CKaraokeSDIFrame *pframe = (CKaraokeSDIFrame *) AfxGetMGetParentFrame();
	if(!psdiframe)
		return;
	CDialogBar * lpDialogBar = psdiframe->GetDialogBar();
	if(!IsWindow(lpDialogBar->m_hWnd))
		return;
	CEdit *pEdit = (CEdit *) lpDialogBar->GetDlgItem(IDC_EDIT_TIME);
	if(!pEdit)
		return;
	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	CMidiSequence *pSeq = pDoc->HelperGetMidiSequence();
	ASSERT(pSeq != NULL);
	if(pSeq->IsPlaying())
	{
		CString str;
		TICKS tkTime;
		if(MMSYSERR_NOERROR != pSeq->GetTime(&tkTime))
			return;
		int millis = pSeq->TicksToMillisecs(tkTime);
		int centis = millis / 10;
		int seconds = centis / 100;
		int minutes = seconds / 60;
		int hours = minutes / 60;
		centis %= 100;
		seconds %= 60;
		minutes %= 60;
		//str.Format(_T("%02d:%02d:%02d %02d\""), hours, minutes, seconds, centis);
		str.Format(_T("%02d:%02d:%02d"), hours, minutes, seconds);
		pEdit->SetWindowText((LPCTSTR) str);
	}
	else if(pSeq->GetState() == CMidiSequence::StatusOpened)
	{
		CString str;
		TICKS tkTime = pSeq->m_tkEnd;
		int millis = pSeq->TicksToMillisecs(tkTime);
		int centis = millis / 10;
		int seconds = centis / 100;
		int minutes = seconds / 60;
		int hours = minutes / 60;
		centis %= 100;
		seconds %= 60;
		minutes %= 60;
		//str.Format(_T("%02d:%02d:%02d %02d\""), hours, minutes, seconds, centis);
		str.Format(_T("%02d:%02d:%02d"), hours, minutes, seconds);
		pEdit->SetWindowText((LPCTSTR) str);
	}

}

/*void CCDView::UpdateSlider()
{
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    CKaraokeSDIFrame *pframe = (CKaraokeSDIFrame *) pApp->m_pMainWnd;
	ASSERT(pframe != NULL);
	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	CMidiSequence * pSeq = pDoc->HelperGetMidiSequence();
	ASSERT(pSeq != NULL);
	TICKS	tkTime;
	if(MMSYSERR_NOERROR != pSeq->GetTime(&tkTime))
		return;
	double rate = ((double) tkTime) / pSeq->GetFile()->m_tkLength;
    pDoc
//	CXfplayerDialogBar * lpDialogBar = pframe->GetDialogBar();
//pDialogBar->SetSliderPos(rate);
	m_dwSliderLastUpdateTime = timeGetTime();

} */

void CCDView::SetPlayingPosition_(double dRate)
{
    CMath::MaxClip(&dRate, 1.0);
	CMath::MinClip(&dRate,  0.0);
    if(GetDocument()->HelperGetMidiSequence())
    {
	    SetPlayingPosition_((TICKS) (GetDocument()->HelperGetMidiSequence()->m_tkLength * dRate));
    }

}

void CCDView::SetPlayingPosition_(TICKS tkPosition)
{
    
	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
    CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	//CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts = GetLyricFonts();
	//ASSERT(pFonts != NULL);
	CVmsGdiFont * pfont = GetLyricFont();
	ASSERT(pfont != NULL);
	CMidiSequence *pSeq = pDoc->HelperGetMidiSequence();
	ASSERT(pSeq != NULL);
	CMidiFile * pfile = pSeq->GetFile();
	ASSERT(pfile != NULL);
    CEventsTracksV1 * peventsarray = &pfile->m_eventstracksV002;
	ASSERT(peventsarray != NULL);
	CLyricEventsV2 * pevents;
//	if(pDoc->m_p2DTokens == NULL)
//		pevents = NULL;
//	else if(pDoc->m_p2DTokens->GetSize() <= 0)
    if(pfile->m_str2aRawTokens.GetSize() <= 0)
		pevents = NULL;
	else if(peventsarray->GetSize() < pfile->m_str2aRawTokens.GetSize())
		pevents = NULL;
	else
	{
		//pevents = (CLyricEventsV2 *) peventsarray->operator [](pfile->m_str2aRawTokens.GetSize());
//        pevents = (CLyricEventsV2 *) peventsarray->operator [](peventsarray->GetSize() / 2);
        pevents = (CLyricEventsV2 *) peventsarray->operator [](0);
		ASSERT(pevents != NULL);
		ASSERT(pevents->GetClassOrder() == 2);
	}

    int i;
//	for(i = 0; i < m_lyricTemplateLines.GetSize(); i++)
//	{
//		m_lyricTemplateLines[i].Reset();
//	}
    
   CTypedPtrArray <CObArray, CBaseRgn *> rgna;
	//rgn.CreateRectRgn(0, 0, 0, 0);
	CRect rectClient;
	GetClientRect(rectClient);
    TRACE(_T("CCDView::SetPlayingPosition 1 slGdi.Lock\n"));
	CSingleLock slGdi(&m_csGdi, TRUE);
    CDC * pdcForeground = &m_dcScreen;
	// Prepara todos os aparatos para se desenhar
   
//    for(i = 0; i < pSeq->GetFile()->m_eventsTracksForPositionCB.GetSize(); i++)
  //  {
	//    pEventsV1 =	pSeq->GetFile()->m_eventsTracksForPositionCB.GetAt(i);
//        pEventsV1->m_iCurrentNote = 0;
  //      pEventsV1->m_iCurrentToken = 0;
    //}
//    CLyricEventsV1 * pEventsV1Found;
    CLyricEventsV1 * pEventsV1;
    CLyricEventsV2 * pEventsV2;
//    TICKS tk, tkFound;
    int iTokenIndex = -1;
    int iNoteIndex = -1;

    for(i = 0; i < pSeq->GetFile()->m_eventsTracksForPositionCB.GetSize(); i++)
    {
	    pEventsV1 =	pSeq->GetFile()->m_eventsTracksForPositionCB.GetAt(i);
    	if(pEventsV1->GetClassOrder() == 2)
        {
            pEventsV2 = (CLyricEventsV2 *) pEventsV1;
            iNoteIndex = pEventsV2->GetPositionNote(tkPosition);
            if(iNoteIndex >= 0)
            {
                iTokenIndex = pEventsV2->GetNoteFirstToken(iNoteIndex);
                break;
            }
            iTokenIndex = pEventsV2->GetPositionToken(tkPosition);
            if(iTokenIndex >= 0)
            {
                iNoteIndex = pEventsV2->GetTokenFirstNote(iTokenIndex);
                break;
            }
        }
    }
//    if(iTokenIndex < 0 && iNoteIndex < 0)
//    {
//        iTokenIndex = 0;
//        iNoteIndex = 0;
//    }
//    if(iTokenIndex < 0)
        
//    pDoc->m_iPlayingTokenIndex = iTokenIndex;
  //  pDoc->m_iPlayingNoteIndex = iNoteIndex;
    CLyricEventV1 event;
    event.m_iCurrentToken = iTokenIndex;
    event.m_iCurrentNote = iNoteIndex;
    event.m_iType = 4;
    event.m_tkPosition = tkPosition;
    OnLyricEvent(&event, true);
    return;
//	for(i = 0; i < peventsarray->GetSize(); i++)
//	{
//		peventsarray->GetAt(i)->m_iCurrentToken = iTokenIndex;
//		peventsarray->GetAt(i)->m_iCurrentNote = iNoteIndex;
//	}

    CLyricViewLine * lpViewLine;
    int iLineIndex, jLineIndex, j;
    if(0 <= (iLineIndex = m_lyricLines.GetTokenLine(iTokenIndex, &lpViewLine)))
    {
        int iStartLineIndex = iLineIndex;
        for(i = 0;
             i < m_lyricTemplateLines.GetSize(); i++)
        {
            iLineIndex = iStartLineIndex + i;
            if(iLineIndex >= m_lyricLines.GetSize())
            {
                iLineIndex--;
                break;
            }
            lpViewLine = &m_lyricLines[iLineIndex];
            for(j = i + 1; j < m_lyricTemplateLines.GetSize();j++)
            {
                jLineIndex = iStartLineIndex + j;
                if(jLineIndex >= m_lyricLines.GetSize())
                {
                    iLineIndex = jLineIndex - 1;
                    goto breakLoop1;
                }
                if(lpViewLine->m_iRelativeLineIndex ==
                    m_lyricLines[jLineIndex].m_iRelativeLineIndex)
                {
                    iLineIndex = jLineIndex - 1;
                    goto breakLoop1;
                }
            }
        }
breakLoop1:
        int iEndLineIndex = iLineIndex;

        m_lyricLines.UpdateFalseVisibility(
            pdcForeground,
			true,
            &rectClient,
            &rgna,
            pDoc->m_iPlayingTokenIndex,
            pDoc->m_iPlayingNoteIndex,
            pevents,
            pfont);

/*        for(iLineIndex = 0; 
            iLineIndex < iStartLineIndex &&
            iLineIndex < m_lyricLines.GetSize();
            iLineIndex++)
        {
            lpViewLine = &m_lyricLines[iLineIndex];
            if(lpViewLine->GetVisible())
            {
				//lpViewLine->SetStatus(CCDViewLine::StatusPlayed);
				lpViewLine->SetVisible(false);
                lpViewLine->RenderLyricLine(
				    rectClient,
				    &rgna,
				    iTokenIndex,
				    iNoteIndex,
				    XFPLYR_LINE_RENDER_CLEAR,
				    &count,
				    pFonts,
				    pevents);
            }
        }
        for(iLineIndex = iEndLineIndex + 1; 
            iLineIndex < m_lyricLines.GetSize();
            iLineIndex++)
        {
            lpViewLine = &m_lyricLines[iLineIndex];
            if(lpViewLine->GetVisible())
            {
				//lpViewLine->SetStatus(CCDViewLine::StatusPlayed);
				lpViewLine->SetVisible(false);
                lpViewLine->RenderLyricLine(
				    rectClient,
				    &rgna,
				    iTokenIndex,
				    iNoteIndex,
				    XFPLYR_LINE_RENDER_CLEAR,
				    &count,
				    pFonts,
				    pevents);
            }
        }*/
        for(iLineIndex = iStartLineIndex; 
            iLineIndex <= iEndLineIndex;
            iLineIndex++)
        {
            lpViewLine = &m_lyricLines[iLineIndex];
			lpViewLine->SetStatus(CCDViewLine::StatusNew);
            if(iLineIndex == iStartLineIndex)
            {
				TICKS tkCurrentPosition;
                TICKS tkNextPosition;
				if(iTokenIndex >= pEventsV2->m_tkaTokensPosition.GetSize())
				{
					tkCurrentPosition = pDoc->HelperGetMidiSequence()->m_tkLength;
					tkNextPosition = pDoc->HelperGetMidiSequence()->m_tkLength;
				}
				else if(iTokenIndex + 1 >= pEventsV2->m_tkaTokensPosition.GetSize())
				{
					tkCurrentPosition = pEventsV2->m_tkaTokensPosition.GetAt(iTokenIndex);	
                    tkNextPosition = pDoc->HelperGetMidiSequence()->m_tkLength;
				}
                else
				{
					tkCurrentPosition = pEventsV2->m_tkaTokensPosition.GetAt(iTokenIndex);
                    tkNextPosition = pEventsV2->m_tkaTokensPosition.GetAt(iTokenIndex + 1);
				}
				TICKS tkNumerator = tkPosition - tkCurrentPosition;
				TICKS tkDenominator = tkNextPosition - tkCurrentPosition;
				if(tkDenominator == 0)
					if(tkNumerator > 0)
						lpViewLine->m_dFillRate = 1.0; 
					else
						lpViewLine->m_dFillRate = 0.0; 
				else
					lpViewLine->m_dFillRate = (double) tkNumerator / tkDenominator; 
            }
            //if(lpViewLine->GetVisible())
            if(false)
            {
                lpViewLine->Render(
                    pdcForeground,
					true,
			            rectClient,
						
			            &rgna,
			            iTokenIndex,
			            iNoteIndex,
			            XFPLYR_LINE_RENDER_UPDATE,
			            &count,
			            pfont,
			            pevents);
                }
            else
            {
    			lpViewLine->SetVisible(true);
                lpViewLine->Render(
                    pdcForeground,
					true,
			        rectClient,
			        &rgna,
			        iTokenIndex,
			        iNoteIndex,
			        XFPLYR_LINE_RENDER_FULL,
			        &count,
			        pfont,
			        pevents);
    //            lpViewLine->m_iRelativeLineIndex = i;}
            }
        }

    }
    else
    {
        ASSERT(FALSE);
/*        for(i = 0; i < m_lyricTemplateLines.GetSize(); i++)
        {
            m_lyricTemplateLines[i].RenderLyricLine(
				    &clientRect,
				    &rgn,
				    iTokenIndex,
				    iNoteIndex,
				    XFPLYR_LINE_RENDER_CLEAR,
				    &count,
				    pFonts,
				    pevents,
                    false);
        }*/
    }




//	while(true)
//    {
//        pEventsV1Found = NULL;
//        tkFound = 0xffffffff;
//        for(i = 0; i < pSeq->GetFile()->m_eventsTracksForPositionCB.GetSize(); i++)
//        {
//	        pEventsV1 =	pSeq->GetFile()->m_eventsTracksForPositionCB.GetAt(i);
//    		if(pEventsV1->GetClassOrder() == 2)
//            {
//                pEventsV2 = (CLyricEventsV2 *) pEventsV1;
//               if(pEventsV2->m_iCurrentNote < pEventsV2->m_tkaNotesPosition.GetSize())
//                {
//                    if(tkFound > (tk = pEventsV2->m_tkaNotesPosition.GetAt(pEventsV2->m_iCurrentNote)))
//                    {
//                        tkFound = tk;
//                        pEventsV1Found = pEventsV1;
//                    }
//                }
//
 //           }
 //           else
 //           {
//                if(pEventsV1->m_iCurrentToken < pEventsV1->m_tkaTokensPosition.GetSize())
//                {
//                    if(tkFound > (tk = pEventsV1->m_tkaTokensPosition.GetAt(pEventsV1->m_iCurrentToken)))
//                    {
//                        tkFound = tk;
//                        pEventsV1Found = pEventsV1;
//                    }
//                }
//            }
//     
//       }
//        if(pEventsV1Found == NULL)
//            break;
//        if(tkFound > tkPosition)/
//            break;
//        OnLyricEvent(pEventsV1Found, false);
//        if(pEventsV1Found->GetClassOrder() == 2)
//        {
//            pEventsV2 = (CLyricEventsV2 *) pEventsV1Found;
//            pEventsV2->m_iCurrentNote++;
//            pEventsV2->m_iCurrentToken = pEventsV2->GetNoteFirstToken(pEventsV2->m_iCurrentNote++);
//        }
//        else
//        {
//            pEventsV1Found->m_iCurrentToken++;
//        }
//    }
//    Render(false);
//    Render(&rgn, TRUE);
    TRACE(_T("CCDView::SetPlayingPosition 1 slGdi.UnLock\n"));
	
//    CRect rgnBox;
//    rgn.GetRgnBox(rgnBox);
//    TwiReleaseDC(pdcForeground);
    UpdateScreen(&rgna, true);
//    RenderWindow(&clientRect,true);

    slGdi.Unlock();
    //for(i = 0; i < rgna.GetSize(); i++)
    //{
      //  RedrawWindow(NULL, rgna.ElementAt(i), RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE | RDW_ALLCHILDREN);
        //delete rgna.ElementAt(i);
    //}
//    if(!rgnBox.IsRectNull())
  //  {
    //    RedrawWindow(NULL, &rgn, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE | RDW_ALLCHILDREN);
    //}
//	rgn.DeleteObject();

}

void CCDView::Reset()
{
	int iSize = m_lyricLines.GetSize();
	int i;
//    CCDViewLine objViewLine;
//    CCDViewLine & refViewLine = objViewLine;
    CLyricViewLine * lpViewLine = NULL;
    for(i = 0; i < iSize; i++)
	{
//        if(m_lyricLines.GetAt(
  //          &lpViewLine,
    //        m_lyricTemplateLines,
      //      i))
        //{
        lpViewLine = &m_lyricLines.ElementAt(i);
            lpViewLine->Reset();
        //}
	}

}

void CCDView::UpdateReserveList()
{
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
//	CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts = GetLyricFonts();
//	ASSERT(pFonts != NULL);
	//CVmsGdiFont * pfont = GetLyricFont();
	//ASSERT(pfont != NULL);
	CDBCentral * pDataCentral = DB();
	ASSERT(pDataCentral != NULL);
	CRgn rgn;
	rgn.CreateRectRgn(0, 0, 0, 0);

	RECT clientRect;
	GetClientRect(&clientRect);
    TRACE(_T("CCDView::UpdateReserveList 1 slGdi.Lock\n"));
	CSingleLock slGdi(&m_csGdi, true);
	if(!m_dcScreen.SetMapMode(MM_TEXT))
	{
		TRACE0("Could not set map mode to MM_TEXT.\n");
	}
//	m_dcScreen.SelectObject(pFonts->operator [](0)->GetFont());
    CFrameWnd *pframe = GetParentFrame();
//	pframe->m_ReserveList.Render(
//		pdc->GetSafeHdc(),
//		m_dcBack.GetSafeHdc(),
//		pDataCentral->GetSongsSet(),
//		this,
//		&rgn);
//	Render(&rgn, TRUE);
    TRACE(_T("CCDView::UpdateReserveList 1 slGdi.UnLock\n"));
	slGdi.Unlock();
    CRect rgnBox;
    rgn.GetRgnBox(rgnBox);
    if(!rgnBox.IsRectNull())
    {
        RedrawWindow(NULL, &rgn, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE | RDW_ALLCHILDREN);
    }
	//InvalidateRgn(&rgn, FALSE);

}

void CCDView::UpdateTitle()
{
	if(m_titleLines.GetSize() <= 0)
		return;
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
//	CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts = CFontCentral::AppGetFontCentral()->GetLyricViewFonts();
//	ASSERT(pFonts != NULL);
	CXfplayerDoc * pDoc = (CXfplayerDoc *) GetDocument();
	ASSERT(pDoc != NULL);
	CFrameWnd *pframe = GetParentFrame();
    if(pframe == NULL)
        return;
    if(!pframe->IsKindOf(RUNTIME_CLASS(CKaraokeSDIFrame)))
        return;
	ASSERT(pframe != NULL);
//	CRgn rgn;
//	rgn.CreateRectRgn(0, 0, 0, 0);
    CTypedPtrArray <CObArray, CBaseRgn *> rgna;

	RECT rect;
	GetClientRect(&rect);
	CCDViewLine * lpViewLine;
    CView * pPlaylistView = GetPlaylistView();
    CRect rectPlaylist;
    if(pPlaylistView != NULL)
    {
        pPlaylistView->GetWindowRect(rectPlaylist);
        ScreenToClient(rectPlaylist);
    }
//    CCDViewLine objViewLine;
//    CCDViewLine & refViewLine = objViewLine;
	int i;
    TRACE(_T("CCDView::UpdateTitle 1 slGdi.Lock\n"));
    CSingleLock slGdi(&m_csGdi, true);
//    CDC * pdcForeground = TwiGetDC();
	    CDC * pdcForeground = &m_dcScreen;
	if(pDoc->m_bHasTitle)
	{
		lpViewLine = &m_titleLines[0];
//		if(pViewLine)
//		{
			lpViewLine->RenderLine(
                pdcForeground,
				true,
				&rect,
				&rgna,
				XFPLYR_LINE_RENDER_CLEAR,
				&count,
				CFontCentral::AppGetFontCentral()->GetTitleFonts(), 
				false,
				m_crTitle,
				m_penTitle);
//		}
		i = 1;
	}
	else 
		i = 0;
	for(; i < m_titleLines.GetSize() ; i++)
	{
		lpViewLine = &m_titleLines[i];
		//if(pViewLine)
		//{

			//if
			//pViewLine->m_dFillRate = (0.8 * (double) (timeGetTime() - m_iPlayStartTime)) / pDoc->m_TokensMillis.GetAt(pDoc->m_iPlayingTokenIndex) +0.2;
			//if(pViewLine->m_dFillRate > 1.0)
			//	pViewLine->m_dFillRate = 1.0;

				lpViewLine->RenderLine(
                    pdcForeground,
					true,
					&rect,
					&rgna,
					XFPLYR_LINE_RENDER_CLEAR,
					&count,
					CFontCentral::AppGetFontCentral()->GetSubTitleFonts(), 
					false,
					m_crSubTitle,
					m_penSubTitle);
//		}
	}int iStartTop = 100;
	if(m_bTitleVisible)
	{
		TEXTMETRIC textMetric;
		int yPos;
		if(m_titleLines.GetSize() >= 1)
		{
			m_dcScreen.SelectObject(CFontCentral::AppGetFontCentral()->GetTitleFonts()->operator [](0)->GetFont());
			lpViewLine = &m_titleLines[0];
            if(pPlaylistView != NULL)
            {
                //lpViewLine->m_iTop = max(rectPlaylist.bottom, m_voiceSpectrum.GetBottom());
				lpViewLine->m_iTop = max(rectPlaylist.bottom, iStartTop);
            }
            else
            {
                //lpViewLine->m_iTop = m_voiceSpectrum.GetBottom();
				lpViewLine->m_iTop = max(rectPlaylist.bottom, iStartTop);
            }
		}
		if(m_titleLines.GetSize() >= 2)
		{
			if(pDoc->m_bHasTitle)
			{
				m_dcScreen.SelectObject(CFontCentral::AppGetFontCentral()->GetTitleFonts()->operator [](0)->GetFont());
				m_dcScreen.GetTextMetrics(&textMetric);
				yPos = lpViewLine->m_iTop + textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading;
			}
			m_dcScreen.SelectObject(CFontCentral::AppGetFontCentral()->GetSubTitleFonts()->operator [](0)->GetFont());
			m_dcScreen.GetTextMetrics(&textMetric);
			if(!pDoc->m_bHasTitle)
			{
				yPos = lpViewLine->m_iTop + textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading;
			}
			int pos;
			for(pos = yPos, i = 1; i < m_titleLines.GetSize() ; i++)
			{
				lpViewLine = &m_titleLines[i];
//				if(pViewLine)
//				{
					lpViewLine->m_iTop = pos;
//				}
				pos += textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading;
			}
		}
		
		RECT clientRect;
		GetClientRect(&clientRect);
		
		if(!m_dcScreen.SetMapMode(MM_TEXT))
		{
			TRACE0("Could not set map mode to MM_TEXT.\n");
		}
			if(pDoc->m_bHasTitle)
		{
			lpViewLine = &m_titleLines[0];
//			if(pViewLine)
//			{
				lpViewLine->RenderLine(
                    pdcForeground,
					true,
					&rect,
					&rgna,
					XFPLYR_LINE_RENDER_FULL,
					&count,
					CFontCentral::AppGetFontCentral()->GetTitleFonts(), 
					true,
					m_crTitle,
					m_penTitle);
//			}
			i = 1;
		}
		else 
			i = 0;
		for(; i < m_titleLines.GetSize() ; i++)
		{
			lpViewLine = &m_titleLines[i];
//			if(pViewLine)
//			{

				//if
				//pViewLine->m_dFillRate = (0.8 * (double) (timeGetTime() - m_iPlayStartTime)) / pDoc->m_TokensMillis.GetAt(pDoc->m_iPlayingTokenIndex) +0.2;
				//if(pViewLine->m_dFillRate > 1.0)
				//	pViewLine->m_dFillRate = 1.0;

					lpViewLine->RenderLine(
                        pdcForeground,
						true,
						&rect,
						&rgna,
						XFPLYR_LINE_RENDER_FULL,
						&count,
						CFontCentral::AppGetFontCentral()->GetSubTitleFonts(), 
						true,
						m_crSubTitle,
						m_penSubTitle);
//			}
		}
		
	}
    UpdateScreen(&rgna, true);
	slGdi.Unlock();
    

}

BOOL CCDView::PreTranslateMessage(MSG* pMsg) 
{
	m_lyricTemplateLines.RelayEvent(pMsg);
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    
	ASSERT(pApp != NULL);
// TODO: Add your specialized code here and/or call the base class
    if(pApp->m_pMainWnd != NULL)
    {
        if(pApp->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CKaraokeSDIFrame)))
        {
            //((CKaraokeSDIFrame *) pApp->m_pMainWnd)->m_ReserveList.m_ToolTip.RelayEvent(pMsg);
        }
    }
	if(pMsg->hwnd == m_hWnd)
	{
		switch(pMsg->message)
		{
		case WM_DISPLAYCHANGE:
			OnDisplayChange(pMsg->wParam, CSize(LOWORD(pMsg->lParam), HIWORD(pMsg->lParam)));
			return TRUE;
		case WM_USER:
//			if(OnUserMessage(pMsg->wParam, pMsg->lParam))
//			    return TRUE;
            break;
        case WM_USER + 3:
            ASSERT(FALSE);
            switch(pMsg->wParam)
            {
            case 201:
                GetDocument()->OnUpdateProgress(NULL);
//                UpdateProgress(); // cut processing
                return true;
            default:
                break;
            }
            break;
        case WM_USER + 8:
            break;
		case MMSG_DONE:
		    //OnMmsgDone((CMidiSequence *) pMsg->wParam, (LPMIDIDONEDATA) pMsg->lParam);
            //delete (LPMIDIDONEDATA) pMsg->lParam;
		    return FALSE;
        case VMSM_RENDER_RECT:
//            Render((LPRECT) pMsg->wParam);
            break;
        case VMSM_RENDER_RGN:
  //          Render((CRgn *) pMsg->wParam);
            break;
        case WM_USER + 100:
            ASSERT(FALSE);
            break;
//            RenderTransparent(pdcForeground, (CWnd *) pMsg->wParam, (LPRECT) pMsg->lParam, NULL, false);
            break;
        case WM_MOUSEMOVE:
			if(!m_bHoverTimer)
			{
				m_bHoverTimer = true;
				SetTimer(CVmpTimer::ID_HOVER, 100, NULL);
			}
		default:
			break;
		}
	}

	return CView::PreTranslateMessage(pMsg);
}

LRESULT CCDView::OnMmsgDone(WPARAM wparam, LPARAM lparam)
{
	CMidiSequence * pseq = (CMidiSequence *) wparam;
	LPMIDIDONEDATA lpmdd = (LPMIDIDONEDATA) lparam;
	CXfplayerDoc *pdoc = GetDocument();
	ASSERT(pdoc != NULL);
    
    if(pseq->IsSettingPosition())
    {
        UpdateProgress();
    }

	pdoc->OnMmsgDone(pseq, lpmdd);
	return 0;
}

LRESULT CCDView::OnMidiPlayerNotifyEvent(WPARAM wparam, LPARAM lparam)
{
	CMidiPlayer::CNotifyEventData * pdata =
		(CMidiPlayer::CNotifyEventData *) wparam;
	CXfplayerDoc *pdoc = GetDocument();
	ASSERT(pdoc != NULL);
    
//    if(pdata->m_pplayer->GetSequence()->IsSettingPosition())
  //  {
    //    UpdateProgress();
    //}
	if(pdata->m_enotifyevent
		== CMidiPlayer::NotifyEventPositionSet)
    {
        UpdateProgress();
    }

	pdoc->OnMidiPlayerNotifyEvent(pdata);
	return 0;
}


UINT CCDView::ThreadProcChangeBackgroundImage(
  LPVOID lpParameter   // thread data
)
{
	//SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_IDLE);
	//SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	CCDView * pView =  (CCDView *) lpParameter;
	//pView->ChangeBackgroundImage();
	//CString *pStr = (CString *) lpParameter;
	TRACE(_T("\nLOADING %s\n"),pView->m_strNextImagePath);
//	LPVOID freeImage = CImage::LoadImageFile(pView->m_strNewBitmapPath);
//	pView->m_freeImage = (LPVOID) freeImage;
//	pView->m_eventBkImageReady.PulseEvent();

//	pView->PostMessage(WM_USER, 33, (LPARAM) freeImage);
	return 0;
}

int CCDView::_ImageChangeSetState(EImageChangeState estate)
{
	m_bkImageChangeState = estate;
	switch(estate)
	{
	case BkImageStateFinish:
		{
			m_evImageChangeFinish.SetEvent();
		}
		break;
	}
	return 1;
}

int CCDView::_ImageChangePulseEvent(EImageChangeEvent eevent)
{
//    TRACE(_T("\nCCDView::BkImageChangeStateMachine In\n"));
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	CXfplayerThreadV1 * pThreadV1 = (CXfplayerThreadV1 *) pApp->GetThreadV1();
    CXfplayerThreadV3 * pthreadV3 = (CXfplayerThreadV3 *) pApp->GetThreadV3();
    static DWORD ls_dwLastTime = 0;
    static bool bRunning = false;
    if(bRunning)
    {
		TRACE("CCDView::_ImageChangePostEvent bRunning == true");
        _ImageChangePostEvent(eevent);
        return 0;
    }
    
    //static CDWArray dwaCallStack;
    DWORD dwTime;


	ASSERT(pApp != NULL);
	CSingleLock sl(&m_csBkImageChangeStateMachine, true);
	CKeeper<bool> k(&bRunning, true, false, true);
  //  TRACE(_T("CCDView::BkImageChangeStateMachine Middle 1"));
	switch(m_bkImageChangeState)
	{
	case BkImageStateTiming:
		if(m_bDestroy)
		{
			sl.Unlock();
			_ImageChangeSetState(BkImageStateFinish);
			break;
		}
		switch(eevent)
		{
		case BkImageEventResize:
			{
				RenderBack2();
				PostMessage(WM_APP + 3377, 18, 4);
			}
			break;
		case BkImageEventFlagChanged:
			{
				RenderBack2();
				PostMessage(WM_APP + 3377, 18, 3);
			}
			break;
		case BkImageEventTimer:
    //    TRACE(_T("CCDView::BkImageChangeStateMachine case 10"));
			
            dwTime = timeGetTime();
			if(dwTime 
				- m_dwBackgroundLastUpdateTime
				>= (DWORD) pApp->m_iBackgroundUpdateMillis &&
                dwTime - ls_dwLastTime > 1000)
			{
                ls_dwLastTime = dwTime;
				if(VMS_SUCCEEDED(LoadNextImage(false)))
                {
                    _ImageChangeSetState(BkImageStateLoading);
                }
			}
			break;
		case BkImageEventLoadNow:
      //      TRACE(_T("CCDView::BkImageChangeStateMachine case 20"));
			m_transitioneffect.Reset();
            dwTime = timeGetTime();
            ls_dwLastTime = dwTime;
			if(VMS_SUCCEEDED(LoadNextImage(true)))
            {
                _ImageChangeSetState(BkImageStateLoading);
            }
			break;
		default:;
		}
		break;
	case BkImageStateLoading:
		switch(eevent)
		{
		case BkImageEventResize:
			{
				RenderBack2();
				PostMessage(WM_APP + 3377, 18, 4);
			}
			break;
		case BkImageEventFlagChanged:
			{
				RenderBack2();
				PostMessage(WM_APP + 3377, 18, 3);
			}
			break;
		case BkImageEventLoaded:
			if(m_bDestroy)
			{
				_ImageChangeSetState(BkImageStateFinish);
				break;
			}
			ChangeBackgroundImage(false);
			_ImageChangeSetState(BkImageStatePreTransition);
			m_dwBackgroundPreTransitionStartTime = timeGetTime();
			pthreadV3->PreTransitionImageAsync(this);
			break;
		case BkImageEventLoadFailed:
			if(m_bDestroy)
			{
				_ImageChangeSetState(BkImageStateFinish);
				break;
			}
			TRACE(_T("CCDView::BkImageChangeStateMachine case 120"));
			m_bkImageChangeState = BkImageStateLoading;
            dwTime = timeGetTime();
            ls_dwLastTime = dwTime;
			LoadNextImage(m_bLastLoadImageSynch);
			break;
		case BkImageEventTimer:
//        TRACE(_T("CCDView::BkImageChangeStateMachine case 130"));
            //dwTime = timeGetTime();
//			if(dwTime > (dwLastTime + 10000)) // Espera 10 segundos para carregar imagem
//			{
  //              dwLastTime = dwTime;
	//			if(VMS_SUCCEEDED(LoadNextImage()))
      //          {
        //            m_bkImageChangeState = BkImageChangeStateLoading;
          //      }
			//}
			break;
        }
        break;
        case BkImageStatePreTransition:
		    switch(eevent)
		    {
			case BkImageEventResize:
				{
					RenderBack2();
					PostMessage(WM_APP + 3377, 18, 4);
				}
				break;
			case BkImageEventTimer:
				break;
		    case BkImageEventPreTransitionFinished:
				if(m_bDestroy)
				{
					_ImageChangeSetState(BkImageStateFinish);
					break;
				}
				_ImageChangeTransitionEffectInitialize();
                TRACE(_T("CCDView::BkImageChangeStateMachine case 110"));
                m_bkImageChangeState = BkImageStateInTransitionEffect;
                break;
		    default:;
           }
		break;
        case BkImageStateInTransitionEffect:
			if(m_bDestroy)
			{
				_ImageChangeSetState(BkImageStateFinish);
				break;
			}
		    switch(eevent)
		    {
			case BkImageEventResize:
				{
					_ImageChangeTransitionEffectInitialize();
				}
				break;
			case BkImageEventFlagChanged:
				{
					RenderBack2();
					_ImageChangeTransitionEffectInitialize();
				}
				break;
			case BkImageEventTimer:
				{
					m_transitioneffect.OnTransitionTimer();
				}
                break;
            case BkImageEventTransitionEffectFinished:
                m_transitioneffect.Reset();
                m_dwBackgroundLastUpdateTime = timeGetTime();
                m_bkImageChangeState = BkImageStateTiming;
                break;
            case BkImageEventLoadNow:;
                m_transitioneffect.Reset();
				dwTime = timeGetTime();
				ls_dwLastTime = dwTime;
				if(VMS_SUCCEEDED(LoadNextImage(true)))
				{
					m_bkImageChangeState = BkImageStateLoading;
				}
		    default:;
           }
		break;
	default:;
	}
	return 1;
}

// Never call this function when m_csGdi is locked,
// because some state changes need to lock m_csGdi.
void CCDView::_ImageChangePostEvent(EImageChangeEvent eevent)
{
	CVmpApp * papp = (CVmpApp *) AfxGetApp();
	CXfplayerThreadV3 * pthreadv3 = (CXfplayerThreadV3 *) papp->GetThreadV3();
	pthreadv3->PostThreadMessage(WM_APP + 114, (WPARAM) this, (LPARAM) eevent);
}

void CCDView::_ImageChangeTransitionEffectInitialize()
{
	m_transitioneffect.Initialize();
}

void CCDView::_ImageChangeTransitionEffectRunStep()
{
	m_transitioneffect.RunStep();
}


LRESULT CCDView::OnApp3377Message(WPARAM wparam, LPARAM lparam)
{
	MSG msg;

	bool bRunStep =
		wparam == 18
		&& lparam == 0;

	while(PeekMessage(
		&msg,
		(HWND) INVALID_HANDLE_VALUE,
		WM_APP + 3377,
		WM_APP + 3377,
		PM_REMOVE))
	{
		if(
			msg.wParam == 18
			&& msg.lParam == 0)
		{
			bRunStep = true;
		}
	}

	if(bRunStep)
	{
		TransitionEffectRunStepAsync();
	}
	else if(wparam == 18)
	{
		if(lparam == 3)
		{
			// BkImageEventFlagChanged:
			UpdateBuffer(false);
			UpdateScreen();
		}
		else if(lparam == 4)
		{
			// BkImageEventFlagChanged:
			UpdateBuffer(false);
			UpdateScreen();
		}
	}
	return true;
}

int CCDView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	m_strRegistrySection = "KaraokeMainView";
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
    CXfplayerDoc * pDoc = GetDocument();


	DB()->UpdateImagePaths();
    m_sliderProgress.CreateEx(WS_EX_TRANSPARENT,NULL, NULL, WS_CHILD | WS_VISIBLE , CRect(0, 0, 0, 0), this, IDC_SLIDER_PROGRESS);
    m_sliderProgress.SetRange(0, 4096);

    CDBCentral * pdb = DB();
    CDBStringSet * pStringSet = pdb->GetDBStringSet();
    pStringSet->Load(_T("Images"), _T("CurrentPath"), m_strCurrentImagePath);


	CFrameWnd * pframe = GetParentFrame();
	pframe->SetActiveView(this);

	return 0;
}


void CCDView::ClearLyricLines(bool bRender)
{
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
//	CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts = GetLyricFonts();
//	ASSERT(pFonts != NULL);
	CVmsGdiFont * pfont = GetLyricFont();
	ASSERT(pfont != NULL);

	CRgn rgn;
	rgn.CreateRectRgn(0, 0, 0, 0);
	int i;
	RECT clientRect;
	GetClientRect(&clientRect);
    TRACE(_T("CCDView::ClearLyricLines 1 slGdi.Lock\n"));
	CSingleLock slGdi(&m_csGdi, TRUE);
//    CCDViewLine objViewLine;
//    CCDViewLine & refViewLine = objViewLine;
    CLyricViewLine * lpTemplateLine = NULL;
	for(i = 0; i < m_lyricTemplateLines.GetSize(); i++)
	{
		//CCDViewLine * pViewLine = m_lyricTemplateLines[i];
//        lpViewLine = &m_lyricTemplateLines[i];
//		lpViewLine->Reset();
//		lpViewLine->RenderLyricLine(
//					&clientRect,
//					&rgn,
//					0,
//					0,
//					XFPLYR_LINE_RENDER_CLEAR,
//					NULL,
//					pFonts,
//					NULL, 
  //                  false);
	}
//	if(bRender)
//		Render(&rgn, TRUE);
    TRACE(_T("CCDView::ClearLyricLines 1 slGdi.UnLock\n"));
    slGdi.Unlock();
    if(bRender)
    {
        CRect rgnBox;
        rgn.GetRgnBox(rgnBox);
        if(!rgnBox.IsRectNull())
        {
            RedrawWindow(NULL, &rgn, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE | RDW_ALLCHILDREN);
        }
    }
	rgn.DeleteObject();
}




void CCDView::XFUpdateFonts(C2DStrArray *p2DTokens)
{
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
//	CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts = GetLyricFonts();
//	ASSERT(pFonts != NULL);
	CVmsGdiFont *pfont = GetLyricFont();
	ASSERT(pfont != NULL);
//	CVmsGdiFont * pFont;
	/*int i, iSize;
	iSize = pFonts->GetSize();
	for(i = 0; i < iSize; i++)
	{
		pFont = pFonts->operator [](i);
		pFont->SetDC(&m_dcScreen);
		pFont->AddXFGlyphs(p2DTokens);
		pFont->ClearDC();
	}*/

}


void CCDView::RenderScore(CDC * pdc, bool bClearBackground)
{
    //CSingleLock slGdi(&m_csGdi, TRUE);

	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
//	CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts = GetLyricFonts();
//	ASSERT(pFonts != NULL);
	CVmsGdiFont * pfont = GetLyricFont();
	ASSERT(pfont != NULL);
	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);


	double dScoreRate = m_dScoreRate;
	if(dScoreRate > 1.0)
		dScoreRate = 1.0;
	else if(dScoreRate < 0.0)
		dScoreRate = 0.0;
	CWStr wstr;
	wstr.Format(L"%0.0f", dScoreRate * 100.0);
	CRect rect;
	GetClientRect(&rect);

	ASSERT(pdc != NULL);
    CPoint ptViewport = pdc->GetViewportOrg();

	CRect rectClipBox;
	pdc->GetClipBox(rectClipBox);

	CRect rectClipBoxClient = rectClipBox;
	rectClipBoxClient.OffsetRect(-ptViewport);

	CRect rectPlacement;
	m_lineScore.GetPlacement(rectPlacement);

	CRect rectIntersect;
	if(!rectIntersect.IntersectRect(
			rectPlacement,
			rectClipBoxClient))
	{
		return;
	}



   	m_lineScore.SetBackgroundDC(&m_dcBack);
    m_lineScore.SetTwi(this);
    m_lineScore.SetTextEffect(CCDViewLine::EffectEmbossed);

	m_lineScore.PrepareLine(
        pdc,
		wstr,
		0,
		pfont,
		&rect);

	m_lineScore.RenderLine(
        pdc,
		true,
		&rect,
		NULL,
		bClearBackground ?
            XFPLYR_LINE_RENDER_CLEAR_FULL :
            XFPLYR_LINE_RENDER_FULL,
		&count,
		pfont,
		false,
		RGB(0, 255, 255),
		m_penScore);

//	m_dwScoreLastUpdateTime = timeGetTime();
//	slGdi.Unlock();

}

void CCDView::RedrawScore(bool bBackRedraw)
{
	CRect rect;
    m_lineScore.GetRect(rect);
    TwiRedraw(rect);

}

/*void CCDView::Render(CRgn *pRgn)
{
    bool bWasLocked = !m_csGdi.Lock(0);

    CRect rect;
	pRgn->GetRgnBox(&rect);

    m_dcScreen.SelectClipRgn(NULL);
    GetChildrenClip();
    m_dcScreen.SelectClipRgn(&m_rgnChildren);
    if(!m_dcScreen.BitBlt(
		rect.left,
		rect.top,
		rect.Width(),
		rect.Height(), 
		&m_dcBuffer,
		rect.left,
		rect.top,
		SRCCOPY))
	{
		TRACE0("Bitmap not painted.\n");
	} 

    GdiFlush();
	
    if(!bWasLocked)
    {
        m_csGdi.Unlock();
    }
}

void CCDView::Render(LPRECT lpRect)
{
    bool bWasLocked = !m_csGdi.Lock(0);
//	if(!bGdiLocked)
//		m_csGdi.Lock();

    CRect rect;
	rect = *lpRect;
    
    GetChildrenClip();
    m_dcScreen.SelectClipRgn(&m_rgnChildren);
    if(!m_dcScreen.BitBlt(
		rect.left,
		rect.top,
		rect.Width(),
		rect.Height(), 
		&m_dcBuffer,
		rect.left,
		rect.top,
		SRCCOPY))
	{
		TRACE0("Bitmap not painted.\n");
	} 

    GdiFlush();
    if(!bWasLocked)
    {
        m_csGdi.Unlock();
    }
}*/

/*void CCDView::Render(BOOL bGdiLocked)
{
//	CSingleLock sl(&m_csGdi, TRUE);
	if(!bGdiLocked)
		m_csGdi.Lock();
	CRect rect;
	GetClientRect(&rect);
    CRect rectClient;
    GetClientRect(rectClient);
    CXfplayerDoc * pDoc = GetDocument();
    CPlaylistView * pPlaylistView = GetPlaylistView();
    //CPlaylistView * pPlaylistView =  GetPlaylistView();
    if(m_pplaylistipwnd == NULL)
    {
        m_dcScreen.SelectClipRgn(NULL);
    }
    else
    {
        CRect rectPlaylist;
        m_pplaylistipwnd->GetWindowRect(rectPlaylist);
        ScreenToClient(rectPlaylist);
        CRgn rgnA;
        CRgn rgnB;
        rgnA.CreateRectRgn(rectClient.left, rectClient.top, rectClient.right, rectClient.bottom);
        rgnB.CreateRectRgn(rectPlaylist.left, rectPlaylist.top, rectPlaylist.right,rectPlaylist.bottom);
        rgnA.CombineRgn(&rgnA, &rgnB,RGN_DIFF);
	    m_dcScreen.SelectClipRgn(&rgnA);
        CRect rectIntersect;
        rectIntersect.IntersectRect(rect, rectPlaylist);   
        if(!rectIntersect.IsRectEmpty())
        {
            InvalidateRect(rectIntersect, FALSE);
        }
    }
    m_dcScreen.SelectClipRgn(NULL);


	if(!m_dcScreen.BitBlt(
		rect.left,
		rect.top,
		rect.Width(),
		rect.Height(), 
		&m_dcBuffer,
		rect.left,
		rect.top,
		SRCCOPY))
	{
		TRACE0("Bitmap not painted.\n");
	} 
	else
	{
//		TRACE(_T("OnDraw:\n"));
//		TRACE(_T("rect.left  : %d\n"), rect.left);
//		TRACE(_T("rect.top   : %d\n"), rect.top);
//		TRACE(_T("rect.right : %d\n"), rect.right);
//		TRACE(_T("rect.bottom: %d\n"), rect.bottom);


	} 
	GdiFlush();
	if(!bGdiLocked)
		m_csGdi.Unlock();
    if(m_pplaylistipwnd != NULL)
    {
        m_pplaylistipwnd->RedrawWindow();
    }


}*/

void CCDView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
//    CRect rectSpectrum;
  //  m_voiceSpectrum.GetPlacement(rectSpectrum);
//    CPoint pointClient =  point;
  //  ScreenToClient(&pointClient);
    //if(m_voiceSpectrum.GetVisible() && rectSpectrum.PtInRect(pointClient))
//    {
  //      CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    //    CRelationV001<UINT, UINT, UINT, UINT> * prel;
      //  CMenuCentral * pmenucentral = CMenuCentral::GetMenuCentral();
//        pmenucentral->MenuV033GetImageMap(&prel);
  //      CMenuV033 menu(
    //        pmenucentral->MenuV033GetImageList(),
      //      pmenucentral->MenuV033GetImageListDisabled(),
        //    prel,
//            CFontCentral::AppGetFontCentral()->GetMenuFont());

//	    if (menu.LoadMenu(IDR_POPUP_LYRICVIEW_SPECTRUM))
//	    {
//		    CMenu* pPopup = menu.GetSubMenu(0);
//		    ASSERT(pPopup != NULL);
//		    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
//			    point.x, point.y,
//			    this);
//	    }
  //  }
   // else
	int iLine, iToken, iChar;
	CPoint ptCursor;
	ptCursor = point;
	if(
		m_lyricTemplateLines.HitTest(ptCursor, iLine, iToken, iChar)
		== CLyricViewLine::HitTestLink)
	{
		CWStr wstr;
		m_lyricLines.GetLink(wstr, iLine, iToken, iChar);
		m_wstrCurrentLink = wstr;
        CVmpApp * pApp = (CVmpApp *) AfxGetApp();
        CRelationV001<UINT, UINT, UINT, UINT> * prel;
        CMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
        CMenuV033 menu(
            CMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
			CMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
            prel,
            CFontCentral::AppGetFontCentral()->GetMenuFont());
	    if (menu.LoadMenu(IDR_POPUP_LYRICVIEW_LINK))
	    {
		    CMenuV033* pPopup = (CMenuV033 *) menu.GetSubMenu(0);
		    ASSERT(pPopup != NULL);
            CFrameWnd * pframe = GetParentFrame();
		    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			    point.x, point.y,
			    (CWnd *) pframe);
	    }
	}
	else
    {
        CVmpApp * pApp = (CVmpApp *) AfxGetApp();
        CRelationV001<UINT, UINT, UINT, UINT> * prel;
        CMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
        CMenuV033 menu(
            CMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
			CMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
            prel,
            CFontCentral::AppGetFontCentral()->GetMenuFont());
	    if (menu.LoadMenu(IDR_POPUP_LYRICVIEW))
	    {
		    CMenuV033* pPopup = (CMenuV033 *) menu.GetSubMenu(0);
		    ASSERT(pPopup != NULL);
            CFrameWnd * pframe = GetParentFrame();
		    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			    point.x, point.y,
			    (CWnd *) pframe);
	    }
    }
}

void CCDView::PrepareTitle()
{
	CXfplayerDoc * pDoc = GetDocument();
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	CXFInfoHeader * pInfoHeader = pDoc->HelperGetXFInfoHeader();
	LPCWSTR lpSongName = pDoc->HelperGetXFInfoHeaderSet()->m_wstrSongName;
	//CXFInfoHeaderLS *pInfoHeaderLS = pDoc->m_pInfoHeaderLS;

	CWStr wstr;
	CWStr wstrFormat;
	CWStrArray wstrArray;
	//bool bHasTitle;
	
/*	if(pInfoHeaderLS == NULL)
//	{ */
		if(lpSongName != NULL)
		{
			wstr = lpSongName;
			wstr.TrimLeft();
			wstr.TrimRight();
			pDoc->m_bHasTitle = !wstr.IsEmpty();
			if(pDoc->m_bHasTitle)
			{
				wstrArray.Add(wstr);
			}
		}
		if(pInfoHeader != NULL)
		{
			pInfoHeader->m_wstraComposer.GetFormatString(wstr, L"/");
			wstr.TrimLeft();
			wstr.TrimRight();
			if(!wstr.IsEmpty())
			{
				wstrFormat.Format(IDS_FORMAT001_COMPOSER, wstr);
				wstrArray.Add(wstrFormat);
			}

			pInfoHeader->m_wstraLyricist.GetFormatString(wstr, L"/");
			wstr.TrimLeft();
			wstr.TrimRight();
			if(!wstr.IsEmpty())
			{
				wstrFormat.Format(IDS_FORMAT001_LYRICIST, wstr);
				wstrArray.Add(wstrFormat);
			}

			pInfoHeader->m_wstraArranger.GetFormatString(wstr, L"/");
			wstr.TrimLeft();
			wstr.TrimRight();
			if(!wstr.IsEmpty())
			{
				wstrFormat.Format(IDS_FORMAT001_ARRANGER, wstr);
				wstrArray.Add(wstrFormat);
			}

			pInfoHeader->m_wstraPerformer.GetFormatString(wstr, L"/");
			wstr.TrimLeft();
			wstr.TrimRight();
			if(!wstr.IsEmpty())
			{
				wstrFormat.Format(IDS_FORMAT001_PERFORMER, wstr);
				wstrArray.Add(wstrFormat);
			}

			pInfoHeader->m_wstraProgrammer.GetFormatString(wstr, L"/");
			wstr.TrimLeft();
			wstr.TrimRight();
			if(!wstr.IsEmpty())
			{
				wstrFormat.Format(IDS_FORMAT001_PROGRAMMER, wstr);
				wstrArray.Add(wstrFormat);
			}

		}
	CCDViewLine * lpViewLine;
    CCDViewLine objViewLine;
//    CCDViewLine & refViewLine = objViewLine;
    
	while(wstrArray.GetSize() > m_titleLines.GetSize())
	{
		//refViewLine = new CCDViewLine();
		m_titleLines.Add(objViewLine);
        lpViewLine = &m_titleLines.ElementAt(m_titleLines.GetSize() - 1);
		lpViewLine->SetAutoSize(true);
		lpViewLine->m_iLeft = 0;
//        lpViewLine->SetRenderWindow(this);
//        lpViewLine->SetRenderCriticalSection(&m_csGdi);
	}
	m_titleLines.SetBackgroundDC(&m_dcBack);
    m_titleLines.SetTwi(this);
    m_titleLines.SetEffect(CCDViewLine::EffectEmbossed);
	int i;
	RECT rect;
	GetClientRect(&rect);
	if(pDoc->m_bHasTitle)
	{
//		UpdateTitleFonts(strArray[0]);
		m_titleLines[0].PrepareLine(
            &m_dcScreen,
			wstrArray.ElementAt(0),
			0,
			CFontCentral::AppGetFontCentral()->GetTitleFonts(),
			&rect);
		i = 1;
	}
	else
		i = 0;
	for(; i < wstrArray.GetSize(); i++)
	{
//		UpdateSubTitleFonts(strArray[i]);
		m_titleLines[i].PrepareLine(
            &m_dcScreen,
			wstrArray.ElementAt(i),
			0,
			CFontCentral::AppGetFontCentral()->GetSubTitleFonts(),
			&rect);
	}

	for(i = wstrArray.GetSize(); i < m_titleLines.GetSize(); i++)
	{
		m_titleLines[i].Reset();
	}

	//int i;
	//for(i = 0; i < m_titleLines.GetSize(); i++)
	//{
	//	delete m_titleLines[i];
	//}
	//m_titleLines.RemoveAll();

	


}

void CCDView::SetTitleVisible(bool bVisible)
{
	m_bTitleVisible = bVisible;

}

void CCDView::UpdateTitleFonts(LPCTSTR lpStr)
{
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts = CFontCentral::AppGetFontCentral()->GetTitleFonts();
	ASSERT(pFonts != NULL);
	CVmsGdiFont * pFont;
	int i, iSize;
	iSize = pFonts->GetSize();
	for(i = 0; i < iSize; i++)
	{
		pFont = pFonts->operator [](i);
		pFont->SetDC(&m_dcScreen);
//		pFont->AddGlyphs(lpStr);
		pFont->ClearDC();
	}

}

void CCDView::UpdateSubTitleFonts(LPCTSTR lpStr)
{

	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts = CFontCentral::AppGetFontCentral()->GetSubTitleFonts();
	ASSERT(pFonts != NULL);
	CVmsGdiFont * pFont;
	int i, iSize;
	iSize = pFonts->GetSize();
	for(i = 0; i < iSize; i++)
	{
		pFont = pFonts->operator [](i);
		pFont->SetDC(&m_dcScreen);
		pFont->AddGlyphs(lpStr);
		pFont->ClearDC();
	}

}


void CCDView::SetOnSizeEnabled(bool bEnabled)
{
	m_bOnSizeEnabled = bEnabled;
}


void CCDView::PrepareLyricLines()
{
    if(!m_bInitialized)
        return;
	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
//	CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts = GetLyricFonts();
//	ASSERT(pFonts != NULL);
	
	CVmsGdiFont * pfont = GetLyricFont();
	ASSERT(pfont != NULL);

	CMidiSequence *pSeq = NULL;
    if(pDoc->GetMidiPlayer())
    {
	    pSeq = pDoc->HelperGetMidiSequence();
    }

    
    CMidiFile * pfile = NULL;
    if(pSeq)
    {
         pfile = pSeq->GetFile();
    }
	
    CEventsTracksV1 * peventsarray = NULL;
    if(pfile)
    {
        peventsarray = &pfile->m_eventstracksV002;
    }

	CLyricEventsV2 * pevents;
//    if(pDoc->m_p2DTokens == NULL)
//		pevents = NULL;
//	else if(pDoc->m_p2DTokens->GetSize() <= 0)
    if(!peventsarray || 
        pfile->m_str2aRawTokens.GetSize() <= 0)
		pevents = NULL;
	else if(peventsarray->GetSize() < pfile->m_str2aRawTokens.GetSize())
		pevents = NULL;
	else
	{
		//pevents = (CLyricEventsV2 *) peventsarray->operator [](pfile->m_str2aRawTokens.GetSize());
        //pevents = (CLyricEventsV2 *) peventsarray->operator [](peventsarray->GetSize() / 2);
        pevents = (CLyricEventsV2 *) peventsarray->operator [](0);
		ASSERT(pevents != NULL);
		ASSERT(pevents->GetClassOrder() == 2);
	}

    CLyricViewLine viewLine;
    CRect clientRect;
//    CRect rect;
    
    GetClientRect(&clientRect);
    TRACE(_T("CCDView::PrepareLyricLines 1 slGdi.Lock\n"));
    CSingleLock slGdi(&m_csGdi, TRUE);
//    CDC * pdcForeground = TwiGetDC();
    CDC * pdcForeground = &m_dcScreen;
    int iRelativeLineIndex = 0;
    XFPLYR_LINE_RESULT xflr;
    int iTokenIndex = 0, iNextTokenIndex;

	if(pDoc->m_xflha.GetSize() > 0)
	{
		m_lyricTemplateLines.m_wstrLanguage = pDoc->m_xflha.ElementAt(0).m_wstrLanguage;
	}

    while(m_lyricLines.GetSize() > 0)
        m_lyricLines.RemoveAt(m_lyricLines.GetSize() - 1);

    viewLine.m_bAutoSizeX = true;
    viewLine.m_bAutoSizeY = true;

    if(pfile != NULL && pfile->m_str2aRawTokens.GetSize() > 0)
    {
		pfont->SetDC(pdcForeground);
//		pfont->AddXFGlyphs(&pfile->m_str2aRawTokens);
		pfont->ClearDC();

        while(true)
        {
//            m_lyricTemplateLines[iRelativeLineIndex].GetPlacement_(rect);
            viewLine.m_bFirstLine = m_lyricTemplateLines[iRelativeLineIndex].m_bFirstLine;
            viewLine.m_iRelativeLineIndex = iRelativeLineIndex;
//            viewLine.SetRenderWindow(this);
	        //viewLine.SetRect(rect);
            viewLine.SetBackgroundDC(&m_dcBack);
            viewLine.SetTwi(this);
            viewLine.SetTextEffect(CCDViewLine::EffectEmbossed);
            viewLine.SetTemplate(&m_lyricTemplateLines[iRelativeLineIndex]);
//            viewLine.SetColors(m_crLeft, m_crRight);
//            viewLine.SetPens(&m_penLeft, &m_penRight);
//            viewLine.SetRenderCriticalSection(&m_csGdi);
    	    xflr = viewLine.Prepare(
				pDoc->GetCodePage(),
				this,
		        pdcForeground,
                &pfile->m_str2aRawTokens.ElementAt(0),
		        iTokenIndex,
		        &iNextTokenIndex,
				CLyricViewLine::XFPLYR_LINE_PAGE_BREAK,
		        pfont,
		        &clientRect,
		        pevents);
//            viewLine.CalcLayout(
  //              pdcForeground, 
    //            pfont, clientRect);
	        if(xflr == CLyricViewLine::XFPLYR_LINE_PAGE_BREAK)
	        {
                iRelativeLineIndex = 0;
                continue;
            }
            else if(xflr == CLyricViewLine::XFPLYR_LINE_SUCCESS_NO_LINE)
            {
                break;
            }
            iTokenIndex = iNextTokenIndex;
            iRelativeLineIndex++;
            if(iRelativeLineIndex >= m_lyricTemplateLines.GetSize())
                iRelativeLineIndex = 0;



            m_lyricLines.Add(viewLine);
        }
    }
    m_lyricLines.Prepare();

    CKaraokeBouncingBall * lpbb = m_lpbouncingball;

    m_lpbouncingball->Prepare();

    TRACE(_T("CCDView::PrepareLyricLines 1 slGdi.UnLock\n"));
//    TwiReleaseDC(pdcForeground);
    slGdi.Unlock();

	LayoutLyricLines(false);
}

void CCDView::PrepareLyricTemplateLines()
{
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	CFrameWnd * pframe = GetParentFrame();
	ASSERT(pframe != NULL);
	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	CVmsGdiFont * pfont = GetLyricFont();
	ASSERT(pfont != NULL);
	CDBCentral * pDataCentral = DB();
	if(!::IsWindow(m_hWnd))
		return;

    CSingleLock slGdi(&m_csGdi, TRUE);
	
    CRect clientRect;
    GetClientRect(&clientRect);
    m_lyricTemplateLines.m_bEmbossed = !IsCompactMode();
    m_lyricTemplateLines.Prepare();

    if(m_lyricTemplateLines.GetSize() > 0)
	    m_lyricTemplateLines[0].m_bFirstLine = TRUE;

	//	CDC	*pDC = GetDC();
	TEXTMETRIC textMetric;
//	if(pFonts->GetSize() > 0)
//	{
//		m_dcScreen.SelectObject(pFonts->operator [](0)->GetFont());
		m_dcScreen.SelectObject(pfont->GetFont());
		m_dcScreen.GetTextMetrics(&textMetric);
//	}
	
	if(m_lyricTemplateLines.GetSize() > 0)
	{
        CLyricViewLineTemplate * lpViewLine = NULL;
        CRect rect;
		int i;
		for(i = 0; i < m_lyricTemplateLines.GetSize(); i++)
		{
			lpViewLine = &m_lyricTemplateLines[i];
            lpViewLine->SetColors(m_crLeft, m_crRight);
            lpViewLine->SetPens(
				&m_penLeft, &m_penRight,
				&m_penLeftSmall, &m_penRightSmall);

		}
		LayoutLyricTemplateLines(true);
		LayoutKaraokeBouncingBall();
        
        

	}
    slGdi.Unlock();
}

void CCDView::LayoutKaraokeBouncingBall()
{
	if(m_lyricTemplateLines.GetSize() > 0)
	{
		CRect rectClient;
		GetClientRect(rectClient);
		CKaraokeBouncingBall * lpbb = m_lpbouncingball;
		CVmsGdiFont * pfont = GetLyricFont();
		int iMegaHeight = pfont->GetMegaHeight();
		CLyricViewLineTemplate & templateline = m_lyricTemplateLines.ElementAt(0);
		CRect rect(rectClient);
		CRect rectTemplate;
		templateline.GetPlacement_(rectTemplate);
		rect.top = rectTemplate.top - iMegaHeight;
		rect.bottom = rectTemplate.top;
        lpbb->SetPlacement(rect);
	}

}

void CCDView::LayoutLyricLines(bool bGdiLocked)
{
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	CFrameWnd * pframe = GetParentFrame();
	ASSERT(pframe != NULL);
	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	CVmsGdiFont * pfont = GetLyricFont();
	ASSERT(pfont != NULL);
	CDBCentral * pDataCentral = DB();
	if(!::IsWindow(m_hWnd))
		return;

    CSingleLock slGdi(&m_csGdi, FALSE);
	if(!bGdiLocked)
	{
		slGdi.Lock();
	}

	for(int i = 0; i < m_lyricLines.GetSize(); i++)
	{
        CLyricViewLine * lpviewline = &m_lyricLines[i];
		lpviewline->SetPendingLayoutUpdate();
	}



}

void CCDView::LayoutLyricTemplateLines(bool bGdiLocked)
{
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	CFrameWnd * pframe = GetParentFrame();
	ASSERT(pframe != NULL);
	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	CVmsGdiFont * pfont = GetLyricFont();
	ASSERT(pfont != NULL);
	CDBCentral * pDataCentral = DB();
	if(!::IsWindow(m_hWnd))
		return;


    CSingleLock slGdi(&m_csGdi, FALSE);
	if(!bGdiLocked)
	{
		slGdi.Lock();
	}
	
    CRect rectClient;
    GetClientRect(&rectClient);

	TEXTMETRIC & textmetric = pfont->m_tm;
	int iFontMegaHeight =
		(textmetric.tmHeight +
		textmetric.tmInternalLeading +
		textmetric.tmExternalLeading);

	int iMainDeltaY = (int) (iFontMegaHeight * 0.3);

	iFontMegaHeight += iMainDeltaY;

	
	if(m_lyricTemplateLines.GetSize() > 0)
	{
        CLyricViewLineTemplate * lpTemplateLine = NULL;
		int i, pos;
		for(
			pos = iFontMegaHeight,
			i = m_lyricTemplateLines.GetSize() - 1; i >= 0 ; i--)
		{
			lpTemplateLine = &m_lyricTemplateLines[i];
	        CRect rect(
				rectClient.left,
				m_lineSongLabel.m_iTop - pos,
				rectClient.right,
				m_lineSongLabel.m_iTop - pos + iFontMegaHeight);
            lpTemplateLine->SetPlacement_(rect, iMainDeltaY);
			pos += iFontMegaHeight;
		}
	}
	m_lyricTemplateLines.m_bEmbossed = !m_bCompactMode;

}


void CCDView::PostPlayMessage()
{
    PostMessage(WM_USER, 1, ID_PLAY);
}

CWStr CCDView::GetPlainTextV001()
{
    CWStr wstr;
    CWStr wstrPlainTextV001;
    CWStr wstrText;
    CXfplayerDoc * pDoc = GetDocument();

	CWStr wstrPathName;
	wstrPathName.SetOEM(pDoc->GetPathName());
    
	wstr.LoadString(IDS_FILENAME);
    wstrText += wstr;
    wstrText += L": ";
    wstrText += wstrPathName;
    wstrText += L"\r\n";
    wstrText += L"\r\n";

    wstrPlainTextV001 += wstrText;
    wstrText.Empty();
    for(int i = 0; i < m_titleLines.GetSize(); i++)
    {
        //if(!m_titleLines[i].m_chars.IsEmpty())
        //{
            wstrText += m_titleLines[i].m_chars;
            wstrText += L"\r\n";
        //}
    }
    if(!wstrText.IsEmpty())
    {
        wstrPlainTextV001 += wstrText;
        wstrPlainTextV001 += L"\r\n";
    }
    wstrText.Empty();
	CWStr wstrMain;
    for(i = 0; i < m_lyricLines.GetSize(); i++)
    {
		wstrMain = m_lyricLines[i].GetMainString();
        wstrText += wstrMain;
        wstrText += L"\r\n";
    }
    if(!wstrText.IsEmpty())
    {
        wstrPlainTextV001 += wstrText;
    }
    return wstrPlainTextV001;
}

//BOOL CCDView::OnHelpInfo(HELPINFO* pHelpInfo) 
//{
	// TODO: Add your message handler code here and/or call default
//	
//	return CView::OnHelpInfo(pHelpInfo);
//}

void CCDView::OnPlaypause() 
{
	// TODO: Add your command handler code here
    CXfplayerDoc * pDoc = GetDocument();
    if(pDoc->GetPlayEnable())
        pDoc->Play(true);
    else if(pDoc->GetPauseEnable())
        pDoc->Pause();

	
}

void CCDView::OnUpdatePlaypause(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    CXfplayerDoc * pDoc = GetDocument();
    bool bEnable;
    bEnable = pDoc->GetPlayEnable() || pDoc->GetPauseEnable();
	pCmdUI->Enable(bEnable);
}

void CCDView::TimerProc(UINT nID)
{
	if(m_bDestroy)
		return;
 //   PostMessage(WM_USER + 3, nID);
    SendMessage(VMSM_TIMER, nID);
    //OnTimer(nID);
}

BOOL CCDView::DestroyWindow() 
{

	return CView::DestroyWindow();
}

void CCDView::PrepareSongLabelLine()
{
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	CFrameWnd * pframe = GetParentFrame();
	ASSERT(pframe != NULL);
	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);

	//CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts = GetLyricFonts();
	//ASSERT(pFonts != NULL);

	//TRACE(_T("Entered in CCDView::UpdateBackgroundImage(int, int)\n"));
	CDBCentral * pDataCentral = DB();
	if(!::IsWindow(m_hWnd))
		return;
    TRACE(_T("CCDView::PrepareSongLabeLine 1 slGdi.Lock\n"));
	CSingleLock slGdi(&m_csGdi, TRUE);
//	CLyricEventsV2 * pevents;
//	if(pDoc->m_p2DTokens == NULL)
//		pevents = NULL;
//	else if(peventsarray->GetSize() <= pDoc->m_p2DTokens->GetSize())
//		pevents = NULL;
//	else
//	{
//		pevents = (CLyricEventsV2 *) peventsarray->operator [](pDoc->m_p2DTokens->GetSize());
//		ASSERT(pevents != NULL);
//		ASSERT(pevents->GetClassOrder() == 2);
//	}
    CRect clientRect;
    GetClientRect(&clientRect);
    CVmsGdiFont * lpFont = CFontCentral::AppGetFontCentral()->GetSongLabelFont();
	TEXTMETRIC textMetric;
//	if(pFonts->GetSize() > 0)
//	{
		m_dcScreen.SelectObject(lpFont->GetFont());
		m_dcScreen.GetTextMetrics(&textMetric);
//	}
    CRect rectWindow;
    m_sliderProgress.GetWindowRect(rectWindow);
    ScreenToClient(rectWindow);
    m_lineSongLabel.m_iRight = clientRect.right;
	m_lineSongLabel.m_iTop = rectWindow.top - (textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading);
    //m_lineSongLabel.GetFonts()->Add(lpFont);
    m_lineSongLabel.SetTwi(this);
    m_lineSongLabel.SetBackgroundDC(&m_dcBack);
    m_lineSongLabel.SetEmbossPen(&m_penSubTitle);
    m_lineSongLabel.SetForegroundColor(RGB(0,0,0));
    m_lineSongLabel.m_bAutoSizeY = true;
    m_lineSongLabel.SetAnimateIncrement(2.0);
	if(m_lineSongLabel.GetVmsFontCount() <= 0)
	{
		m_lineSongLabel.AddVmsFont(CFontCentral::AppGetFontCentral()->GetSongLabelFont());
	}
    CWStr wstr;
    pDoc->HelperGetXFInfoHeader()->GetFormatV001(pDoc->HelperGetXFInfoHeaderSet()->m_wstrSongName, wstr);
    m_lineSongLabel.PrepareLine(&m_dcScreen, wstr,0, m_lineSongLabel.GetFonts(), clientRect);
    m_lineSongLabel.SetAnimateType(CCDViewLine::AnimateRHL);
    m_lineSongLabel.SetTextEffect(CCDViewLine::EffectSimple);
    TRACE(_T("CCDView::PrepareSongLabeLine 1 slGdi.UnLock\n"));
    slGdi.Unlock();

}

void CCDView::DefaultLayoutPlaylist()
{
    if(m_pplaylistframe == NULL)
        return;
    CRect rect;
    GetClientRect(rect);
    m_pplaylistframe->SetWindowPos(
		&CWnd::wndTop,
		rect.Width() / 4,
        0,
        rect.Width() / 2,
        rect.Height() / 5,
		SWP_SHOWWINDOW);
bool bVisible = m_pplaylistframe->IsWindowVisible() != 0;
    //CPlaylistView * m_pplaylistipwnd = GetPlaylistView();
	//return;
/*    if(m_pplaylistipwnd == NULL)
        return;
    CRect rect;
    GetClientRect(rect);
    m_pplaylistipwnd->MoveWindow(rect.Width() / 4,
                         0,
                         rect.Width() / 2,
                         rect.Height() / 5);
*/
}


CView *  CCDView:: GetPlaylistView()
{
//    if(m_pplaylistipwnd == NULL)
	    if(m_pplaylistframe == NULL)
        return NULL;
    else
//        return m_pplaylistipwnd->GetPlaylistView();
        return m_pplaylistframe->GetActiveView();
}


bool CCDView::OnAttachPlaylistDoc()
{
    AttachPlaylistView();
    return true;
}

bool CCDView::OnDetachPlaylistDoc()
{
    DetachPlaylistView();
    return true;
}

bool CCDView::AttachPlaylistView()
{
	CFrameWnd * pframe = GetParentFrame();
	if(pframe->IsKindOf(RUNTIME_CLASS(CKaraokeSDIFrame)))
	{
		CKaraokeSDIFrame * psdiframe = (CKaraokeSDIFrame *) pframe;
		if(psdiframe->m_bCompactSize)
		{
			return true;
		}
	}
    CPlaylistDoc * lpPlaylistDoc = GetDocument()->GetPlaylistDoc();
    ASSERT(lpPlaylistDoc != NULL);
    CView * lpPlaylistView = lpPlaylistDoc->GetPlaylistView();
    m_pplaylistframe = (CPlaylistFrame *) lpPlaylistView->GetParentFrame();
//	m_pplaylistframe = (CPlaylistFrame *) lpPlaylistDoc->View->GetParentFrame();
	VmsPointerInterfaceAddReference(m_pplaylistframe);
    m_pplaylistframe->ShowWindow(SW_HIDE);

	m_pplaylistframe->TransparentFrameWndChild(GetSafeHwnd());

    DefaultLayoutPlaylist();
    
	m_transparentframewnda.Update(this);
	m_transparentframewnda.Layout();

    UpdateBuffer(false);
    UpdateScreen();

    return true;
}


CView * CCDView::DetachPlaylistView()
{
    CView  * lpplaylistview = GetPlaylistView();
    //if(lpPlaylistView == NULL)
    //{
      //  return NULL;
    //}
	if(m_pplaylistframe == NULL)
	{
		return NULL;
	}
    ASSERT(m_pplaylistframe != NULL);
//    m_pplaylistframe->OnAttachWnd();
	m_pplaylistframe->TransparentFrameWndFrame();
    m_pplaylistframe = NULL;
    //m_pplaylistipwnd = NULL;
//    CPlaylistDoc * lpPlaylistDoc = lpPlaylistView->GetDocument();
  //  ASSERT(lpPlaylistDoc != NULL);
//    Render(FALSE);
    m_transparentframewnda.Update(this);

    UpdateBuffer(false);
    UpdateScreen();

    return lpplaylistview;
}

bool CCDView::HasNextSong()
{
    CPlaylistDoc * pPlaylistDoc = GetDocument()->GetPlaylistDoc();
    if(pPlaylistDoc == NULL)
        return false;
    else
    {
        return pPlaylistDoc->HasNextSong();
    }
}

/*CPlaylistInPlaceWnd * CCDView::GetPlaylistInPlaceWnd()
{
    return m_pplaylistipwnd;
}*/


int CCDView::GetChildrenClip()
{
    CWnd * pWndChild  = GetTopWindow();
    CWnd * pWndFirstChild = pWndChild;
    CRgn rgnChild;
    CRect rectClient;
    CRect rectChild;
    GetClientRect(rectClient);
    m_rgnChildren.SetRectRgn(rectClient);
    rgnChild.CreateRectRgn(0, 0, 0, 0);
    return TRUE;
    while(pWndChild != NULL)
    {

//        CPlaylistInPlaceWnd * pPlaylistWnd;
//        if(pWndChild->IsKindOf(RUNTIME_CLASS(CSliderV008)))
  //      {
//                rgnChild.SetRectRgn(rectChild);
  //              m_rgnChildren.CombineRgn(&m_rgnChildren, &rgnChild, RGN_DIFF);
    //    }
      //  else
        //{
        if(pWndChild->IsWindowVisible())
        {
            if(pWndChild->GetWindowRgn(rgnChild) != ERROR)
            {
                pWndChild->GetWindowRect(rectChild);
                ScreenToClient(rectChild);
                rgnChild.OffsetRgn(rectChild.TopLeft());
                m_rgnChildren.CombineRgn(&m_rgnChildren, &rgnChild, RGN_DIFF);
            }
            else
            {
                pWndChild->GetWindowRect(rectChild);
                ScreenToClient(rectChild);
                //TRACE(_T("CCDView::GetChildrenClip\n"));
                //TRACE(_T("rectClipBox.left  : %d, "), rectChild.left);
                //TRACE(_T("rectClipBox.top   : %d, "), rectChild.top);
                //TRACE(_T("rectClipBox.right : %d, "), rectChild.right);
                //TRACE(_T("rectClipBox.bottom: %d\n"), rectChild.bottom);

                rgnChild.SetRectRgn(rectChild);
                m_rgnChildren.CombineRgn(&m_rgnChildren, &rgnChild, RGN_DIFF);
            }
        }
//        }
        pWndChild = pWndChild->GetNextWindow();
        if(pWndChild  == NULL || pWndChild->m_hWnd == pWndFirstChild->m_hWnd)
            break;
    }
    return TRUE;
}

void CCDView::OnDisplayChange(int iBitsPerPixel, CSize sizeScreen)
{

}

BOOL CCDView::OnEraseBkgnd(CDC* pDC) 
{
/*    CRect rectClipBox;
    pDC->GetClipBox(rectClipBox);
	TRACE(_T("CCDView::OnEraseBkgnd:\n"));
	TRACE(_T("rect.left  : %d\n"),rectClipBox.left);
	TRACE(_T("rect.top   : %d\n"),rectClipBox.top);
	TRACE(_T("rect.right : %d\n"),rectClipBox.right);
	TRACE(_T("rect.bottom: %d\n"), rectClipBox.bottom);*/

//    OnDraw(pDC); retirado pq o desenho da lista de reproduçÃo
                // ficava estranho ao mover
    //InvalidateRect(rectClipBox, false);
    //UpdateWindow();
    //RedrawWindow(rectClipBox, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOERASE);
    //if(rectClipBox.IsRectNull())
    //    GetClientRect(rectClipBox);
    //InvalidateRect(rectClipBox, FALSE);
	// TODO: Add your message handler code here and/or call default
	//CRect rectClipBox;
    //pDC->GetClipBox(rectClipBox);
	//TRACE(_T("CCDView::OnEraseBkgnd:\n"));
	//	TRACE(_T("rect.left  : %d\n"),rectClipBox.left);
	//	TRACE(_T("rect.top   : %d\n"),rectClipBox.top);
	//	TRACE(_T("rect.right : %d\n"),rectClipBox.right);
	//	TRACE(_T("rect.bottom: %d\n"), rectClipBox.bottom);
        //return CView::OnEraseBkgnd(pDC);
    return TRUE;
}

BOOL CCDView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

	


void CCDView::OnViewImageTile() 
{
	// TODO: Add your command handler code here
    SetBkImageFlags(ifTile);
}

void CCDView::OnViewImageZoomall() 
{
	// TODO: Add your command handler code here
    SetBkImageFlags(ifZoomAll);
}

void CCDView::OnViewImageStretch() 
{
	// TODO: Add your command handler code here
    SetBkImageFlags(ifStretch);
	
}

void CCDView::OnViewImageZoomextend() 
{
	// TODO: Add your command handler code here
    SetBkImageFlags(ifZoomExtend);

}


void CCDView::OnUpdateViewImageTile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    bool bSelected = m_iBkImageFlags == ifTile;
	pCmdUI->Enable(!bSelected);
    pCmdUI->SetCheck(bSelected ? 1 : 0);

}

void CCDView::OnUpdateViewImageZoomall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    bool bSelected = m_iBkImageFlags == ifZoomAll;
	pCmdUI->Enable(!bSelected);
    pCmdUI->SetCheck(bSelected ? 1 : 0);
	
}

void CCDView::OnUpdateViewImageZoomextend(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    bool bSelected = m_iBkImageFlags == ifZoomExtend;
	pCmdUI->Enable(!bSelected);
    pCmdUI->SetCheck(bSelected ? 1 : 0);
	
}

VMSRESULT CCDView::SetBkImageFlags(int iFlags)
{
    CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    CDBCentral * pDataCentral = DB();
    CDBLongSet * pLongsSet = pDataCentral->GetDBLongSet();
    m_iBkImageFlags = iFlags;
    pLongsSet->Save(_T("Imagens"), m_strCurrentImagePath + _T(".Flags"), m_iBkImageFlags);
	_ImageChangePostEvent(BkImageEventFlagChanged);
    return VMSR_SUCCESS;
}

void CCDView::OnUpdateViewImageStretch(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    bool bSelected = m_iBkImageFlags == ifStretch;
	pCmdUI->Enable(!bSelected);
    pCmdUI->SetCheck(bSelected ? 1 : 0);

}

void CCDView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
    BOOL bAlpha = false;
    int iValue;
    switch(nChar)
    {
    case VK_NUMPAD0:
    case '0':
        iValue = 0;
        break;
    case VK_NUMPAD1:
    case '1':
        iValue = 1;
        break;
    case VK_NUMPAD2:
    case '2':
        iValue = 2;
        break;
    case VK_NUMPAD3:
    case '3':
        iValue = 3;
        break;
    case VK_NUMPAD4:
    case '4':
        iValue = 4;
        break;
    case VK_NUMPAD5:
    case '5':
        iValue = 5;
        break;
    case VK_NUMPAD6:
    case '6':
        iValue = 6;
        break;
    case VK_NUMPAD7:
    case '7':
        iValue = 7;
        break;
    case VK_NUMPAD8:
    case '8':
        iValue = 8;
        break;
    case VK_NUMPAD9:
    case '9':
        iValue = 9;
        break;
    default:
        {
        iValue = -1;
        bAlpha = isalpha(nChar);
        }
        break;
    }
    
    

    if(iValue >= 0 ||
        bAlpha)
    {
        CToolV023Dialog * pdlg = new CToolV023Dialog();
        pdlg->m_pobjSource = GetDocument();
        pdlg->Create(pdlg->IDD);
        CEdit * pEdit = (CEdit *) &pdlg->m_edit;
        CString str;
        if(bAlpha)
        {
            str = (TCHAR) nChar;
        }
        else
        {
            str.Format(_T("%d"), iValue);
        }
        pEdit->SetWindowText(str);
        int iLen = str.GetLength();
        pEdit->SetSel(iLen, iLen);
        CRect rectWindow;
        GetWindowRect(rectWindow);
        pdlg->SetWindowPos(
            &wndTop,
            rectWindow.CenterPoint().x,
            rectWindow.CenterPoint().y,
            0, 0,
            SWP_SHOWWINDOW |
            SWP_NOSIZE);
        pEdit->SetFocus();

    }
    else
    {
        CKaraokeSDIFrame * pframe = GetKaraokeSDIFrame();
      	if(pframe != NULL
			&& nChar == VK_ESCAPE
			&& pframe->IsFullScreen())
        {
            pframe->ViewFullScreen();
        }
        else
        {
            CView::OnKeyDown(nChar, nRepCnt, nFlags);
        }
    }

     
}
void CCDView::OnExecuteTransposeMinus() 
{
    CXfplayerDoc * pdoc = GetDocument();
	ASSERT(pdoc != NULL);
	pdoc->MusicTransposeMinus();
}

void CCDView::OnUpdateExecuteTransposeMinus(CCmdUI* pCmdUI) 
{
    CXfplayerDoc * pdoc = GetDocument();
	ASSERT(pdoc != NULL);
	pdoc->MusicUpdateTransposeMinus(pCmdUI);
}

void CCDView::OnExecuteTransposePlus() 
{
    CXfplayerDoc * pdoc = GetDocument();
	ASSERT(pdoc != NULL);
	pdoc->MusicTransposePlus();
}

void CCDView::OnUpdateExecuteTransposePlus(CCmdUI* pCmdUI) 
{
    CXfplayerDoc * pdoc = GetDocument();
	ASSERT(pdoc != NULL);
	pdoc->MusicUpdateTransposePlus(pCmdUI);
}

void CCDView::OnExecuteTransposeReset() 
{
    CXfplayerDoc * pdoc = GetDocument();
	ASSERT(pdoc != NULL);
	pdoc->MusicTransposeReset();
}

void CCDView::OnUpdateExecuteTransposeReset(CCmdUI* pCmdUI) 
{
    CXfplayerDoc * pdoc = GetDocument();
	ASSERT(pdoc != NULL);
	pdoc->MusicUpdateTransposeReset(pCmdUI);
}


void CCDView::OnExecuteTransposePlusTone() 
{
    CXfplayerDoc * pdoc = GetDocument();
	ASSERT(pdoc != NULL);
	pdoc->MusicTransposePlusTone();
	
}

void CCDView::OnUpdateExecuteTransposePlusTone(CCmdUI* pCmdUI) 
{
    CXfplayerDoc * pdoc = GetDocument();
	ASSERT(pdoc != NULL);
	pdoc->MusicUpdateTransposePlusTone(pCmdUI);
}

void CCDView::OnUpdateExecuteTransposeMinusTone(CCmdUI* pCmdUI) 
{
    CXfplayerDoc * pdoc = GetDocument();
	ASSERT(pdoc != NULL);
	pdoc->MusicUpdateTransposeMinusTone(pCmdUI);
}

void CCDView::OnExecuteTransposeMinusTone() 
{
    CXfplayerDoc * pdoc = GetDocument();
	ASSERT(pdoc != NULL);
	pdoc->MusicTransposeMinusTone();
}

void CCDView::OnExecuteTempoReset() 
{
    CXfplayerDoc * pdoc = GetDocument();
	ASSERT(pdoc != NULL);
	pdoc->MusicTempoReset();
}

void CCDView::OnUpdateExecuteTempoReset(CCmdUI* pCmdUI) 
{
    CXfplayerDoc * pdoc = GetDocument();
	pdoc->MusicUpdateTempoReset(pCmdUI);
}


void CCDView::OnExecuteTempoPlus() 
{
    CXfplayerDoc * pdoc = GetDocument();
	ASSERT(pdoc != NULL);
	pdoc->MusicTempoPlus();
	
}

void CCDView::OnUpdateExecuteTempoPlus(CCmdUI* pCmdUI) 
{
    CXfplayerDoc * pdoc = GetDocument();
	pdoc->MusicUpdateTempoPlus(pCmdUI);
}

void CCDView::OnExecuteTempoMinus() 
{
    CXfplayerDoc * pdoc = GetDocument();
	ASSERT(pdoc != NULL);
	pdoc->MusicTempoMinus();
}

void CCDView::OnUpdateExecuteTempoMinus(CCmdUI* pCmdUI) 
{
    CXfplayerDoc * pdoc = GetDocument();
	pdoc->MusicUpdateTempoMinus(pCmdUI);
}

void CCDView::PrepareProgressSlider()
{
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	CFrameWnd * pframe = GetParentFrame();
	ASSERT(pframe != NULL);
	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
//	CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts = GetLyricFonts();
//	ASSERT(pFonts != NULL);
	//TRACE(_T("Entered in CCDView::UpdateBackgroundImage(int, int)\n"));
	CDBCentral * pDataCentral = DB();
	if(!::IsWindow(m_hWnd))
		return;
    TRACE(_T("CCDView::PrepareProgressSlider 1 slGdi.Lock\n"));
    CSingleLock slGdi(&m_csGdi, true);
//	CLyricEventsV2 * pevents;
//	if(pDoc->m_p2DTokens == NULL)
//		pevents = NULL;
//	else if(peventsarray->GetSize() <= pDoc->m_p2DTokens->GetSize())
//		pevents = NULL;
//	else
//	{
//		pevents = (CLyricEventsV2 *) peventsarray->operator [](pDoc->m_p2DTokens->GetSize());
//		ASSERT(pevents != NULL);
//		ASSERT(pevents->GetClassOrder() == 2);
//	}
    CRect clientRect;
    GetClientRect(&clientRect);
    CVmsGdiFont * lpFont = CFontCentral::AppGetFontCentral()->GetSongLabelFont();
	TEXTMETRIC textMetric;
	m_dcScreen.SelectObject(lpFont->GetFont());
	m_dcScreen.GetTextMetrics(&textMetric);

    TRACE(_T("CCDView::PrepareProgressSlider 1 slGdi.UnLock\n"));
    slGdi.Unlock();

    CRect rectWindow;
    rectWindow.left = clientRect.left;
    rectWindow.right = clientRect.right;
    rectWindow.bottom = clientRect.bottom - 3;
    rectWindow.top = clientRect.bottom - (textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading);
    m_sliderProgress.MoveWindow(
        rectWindow.left, rectWindow.top,
        rectWindow.Width(), rectWindow.Height(),
        true);

    



}

void CCDView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(pScrollBar->GetDlgCtrlID() == IDC_SLIDER_PROGRESS)
	{
//		if(nSBCode == SB_THUMBTRACK ||
  //          nSBCode == SB_THUMBPOSITION)
	//	{
//            if(nSBCode == SB_THUMBTRACK)
//				m_bSliderPressed = TRUE;
  //          else if(nSBCode == SB_THUMBPOSITION)
    //            m_bSliderPressed = FALSE;
        CXfplayerDoc * pDoc = GetDocument();
        if(pDoc->IsPlaying())
        {
            pDoc->SetProgressRate(m_sliderProgress.GetRate(), NULL);
        }
        else
        {
            SetProgressRate(m_sliderProgress.GetRate());
        }
	//	}
	}

	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CCDView::UpdateProgress()
{

    double dRate = 0.0;
    GetProgressRate(&dRate);
    m_sliderProgress.SetRate(dRate);
    m_dwSliderLastUpdateTime = timeGetTime();

}

CSliderV017 * CCDView::GetProgressSlider()
{
    return &m_sliderProgress;
}

void CCDView::UpdateDrawingObjects()
{
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
    int iEconoMode = CSavings::AppGetEconoMode();

    if(m_dcScreen.m_hDC != NULL)
        m_dcScreen.Detach();
	m_dcScreen.Attach(GetDC()->GetSafeHdc());

    if(m_dcSource.m_hDC != NULL)
    {
        m_dcSource.SelectObject(m_bmpSourceOld.Detach());
        m_dcSource.DeleteDC();
    }
//    if(iEconoMode == CSavings::SaveNoSave)
  //  {
	    if(!m_dcSource.CreateCompatibleDC(&m_dcScreen))
	    {
            AfxMessageBox(_T("No memory to execute program"));
		    pApp->Exit();
	    }
        m_bmpSourceOld.Attach(m_dcSource.GetCurrentBitmap());
    //}
	
//    if(m_dcBuffer.m_hDC != NULL)
  //  {
    //    m_dcBuffer.SelectObject(m_bmpBufferOld.Detach());
      //  m_dcBuffer.DeleteDC();
//    }
//	if(!m_dcBuffer.CreateCompatibleDC(&m_dcScreen))
//	{
  //      AfxMessageBox(_T("No memory to execute program"));
	//	pApp->Exit();
//	}
//	m_bmpBufferOld.Attach(m_dcBuffer.GetCurrentBitmap());
  //  m_dcBuffer.SetStretchBltMode(HALFTONE);

    
//    if(pdc->m_hDC != NULL)
  //  {
    //    pdc->SelectObject(m_bmpBufferOld.Detach());
      //  pdc->DeleteDC();
    //}
//	if(!pdc->CreateCompatibleDC(&m_dcScreen))
//	{
  //      AfxMessageBox(_T("No memory to execute program"));
	//	pApp->Exit();
	//}
    //m_bmpBufferOld.Attach(pdc->GetCurrentBitmap());

    
    
    if(m_dcBack.m_hDC != NULL)
    {
        m_dcBack.SelectObject(m_bmpBackOld.Detach());
        m_dcBack.DeleteDC();
    }
	if(!m_dcBack.CreateCompatibleDC(&m_dcScreen))
	{
        AfxMessageBox(_T("No memory to execute program"));
		pApp->Exit();
	}
	m_bmpBackOld.Attach(m_dcBack.GetCurrentBitmap());
    m_dcBack.SetStretchBltMode(HALFTONE);
	
    
    if(m_dcBack2.m_hDC != NULL)
    {
        m_dcBack2.SelectObject(m_bmpBack2Old.Detach());
        m_dcBack2.DeleteDC();
    }
	if(!m_dcBack2.CreateCompatibleDC(&m_dcScreen))
    {
        AfxMessageBox(_T("No memory to execute program"));
		pApp->Exit();
    }
    m_bmpBack2Old.Attach(m_dcBack2.GetCurrentBitmap());
	m_dcBack2.SetStretchBltMode(HALFTONE);

    m_enhmetafile = GetEnhMetaFile(pApp->m_strModuleFolder + "vmp447cv.emf");
	if(m_enhmetafile == NULL)
	{
		pApp->RestoreEnhMetaFiles();
	}
	m_enhmetafile = GetEnhMetaFile(pApp->m_strModuleFolder + "vmp447cv.emf");
	if(m_enhmetafile != NULL)
	{
        GetEnhMetaFileHeader(
            m_enhmetafile,
            sizeof(m_emh),
            &m_emh);
	}
    CRect rectClient;
    GetClientRect(rectClient);
    int cx = rectClient.Width();
    int cy = rectClient.Height();
//    CDC * pdcForeground = TwiGetDC();
	    CDC * pdcForeground = &m_dcScreen;
//    m_voiceSpectrum.SetDC(pdcForeground, &m_dcBack);
//    TwiReleaseDC(pdcForeground);

}


afx_msg LRESULT CCDView::OnEconoModeChange(WPARAM wParam, LPARAM lParam)
{
    UpdateDrawingObjects();
    RedrawWindow();
    return true;
}



void CCDView::OnViewPlaylist() 
{
	// TODO: Add your command handler code here
	CPlaylistDoc * pplaylistdoc = GetDocument()->GetPlaylistDoc();
    if(pplaylistdoc == NULL)
    {
        CVmpApp * pApp = (CVmpApp *) AfxGetApp();
        pplaylistdoc = pApp->OpenDefaultPlaylist();
        GetDocument()->Attach(pplaylistdoc);
    }
    else if(GetPlaylistView() != pplaylistdoc->GetPlaylistView())
    {
        AttachPlaylistView();
    }

}


afx_msg LRESULT CCDView::OnVMSNotify(WPARAM wParam, LPARAM lParam)
{
    LRESULT lresult;
    VMSNMHDR * lpnmhdr = (VMSNMHDR *) lParam;
    if(wParam == IDC_EDIT)
    {
        if(lpnmhdr->code == E17N_KEYDOWN)
        {
            OnKeyDownEdit(lpnmhdr, &lresult);
            return lresult;
        }
        else if(lpnmhdr->code == E17N_SYSKEYDOWN)
        {
            OnSysKeyDownEdit(lpnmhdr, &lresult);
            return lresult;
        }


    }
    else
    {
        ASSERT(FALSE);
    }
    return -1;
}
afx_msg void CCDView::OnKeyDownEdit( VMSNMHDR * pNotifyStruct, LRESULT * result )
{
    ASSERT(FALSE);
    E17_KEYDOWN  & nmkey = *(E17_KEYDOWN*)pNotifyStruct;
    if(nmkey.wVKey == VK_RETURN)
    {
        CEdit * pEdit = (CEdit *) pEdit->FromHandle(nmkey.hdr.hwndFrom);
        CString str;
        pEdit->GetWindowText(str);
        LPCTSTR lpcsz = str;
        LPTSTR lpend;
        long lValue = _tcstol(lpcsz, &lpend, 10);
        if(lpend != lpcsz)
        {
            pEdit->ShowWindow(SW_HIDE);
            pEdit->Clear();
            CVmpApp *pApp = (CVmpApp *) AfxGetApp();
            CXfplayerDoc * pPlayerDoc  = GetDocument();
            if(pPlayerDoc != NULL)
            {
                CCDView * pLyricView = pPlayerDoc->GetLyricView();
                if(pLyricView != NULL)
                {
                    CPlaylistDoc * pPlaylistDoc = pPlayerDoc->GetPlaylistDoc();
                    if(pPlaylistDoc == NULL)
                    {
                        pPlaylistDoc = pApp->OpenDefaultPlaylist();
                        pPlayerDoc->Attach(pPlaylistDoc);
                    }
                    pPlaylistDoc->AddSong(lValue, true, true, true);
                    pPlaylistDoc->UpdateAllViews(NULL);
//          	        CKaraokeSDIFrame *pframe = (CKaraokeSDIFrame *) pApp->m_pMainWnd;
//        	        pframe->UpdateReserveList();
                }
            }
        }
        *result = -1;
    }
    else if(nmkey.wVKey == VK_ESCAPE)
    {
        CEdit * pEdit = (CEdit *) pEdit->FromHandle(nmkey.hdr.hwndFrom);
        pEdit->ShowWindow(SW_HIDE);
        *result = -1;
    }
    else if(nmkey.wVKey == VK_NUMPAD0 ||
        nmkey.wVKey == VK_NUMPAD1 ||
        nmkey.wVKey == VK_NUMPAD2 ||
        nmkey.wVKey == VK_NUMPAD3 ||
        nmkey.wVKey == VK_NUMPAD4 ||
        nmkey.wVKey == VK_NUMPAD5 ||
        nmkey.wVKey == VK_NUMPAD6 ||
        nmkey.wVKey == VK_NUMPAD7 ||
        nmkey.wVKey == VK_NUMPAD8 ||
        nmkey.wVKey == VK_NUMPAD9 ||
        nmkey.wVKey == '0' ||
        nmkey.wVKey == '1' ||
        nmkey.wVKey == '2' ||
        nmkey.wVKey == '3' ||
        nmkey.wVKey == '4' ||
        nmkey.wVKey == '5' ||
        nmkey.wVKey == '6' ||
        nmkey.wVKey == '7' ||
        nmkey.wVKey == '8' ||
        nmkey.wVKey == '9')
    {
        *result = 0;
    }
    else
    {
//        MessageBeep(MB_OK);
        *result = -1;
    }
}

afx_msg void CCDView::OnSysKeyDownEdit( VMSNMHDR * pNotifyStruct, LRESULT * result )
{
    E17_SYSKEYDOWN  & nmkey = *(E17_SYSKEYDOWN*)pNotifyStruct;
    if(nmkey.wVKey == VK_ESCAPE)
    {
        CEdit * pEdit = (CEdit *) pEdit->FromHandle(nmkey.hdr.hwndFrom);
        pEdit->ShowWindow(SW_HIDE);
        *result = -1;
    }
    else
    {
        *result = -1;
    }
}

void CCDView::OnViewLyricviewSpectrum() 
{
	// TODO: Add your command handler code here
//	m_voiceSpectrum.SetVisible(!m_voiceSpectrum.GetVisible());
//    if(!m_voiceSpectrum.GetVisible())
  //  {
    //    m_voiceSpectrum.Render(NULL, 0, 0);
    //}
}

void CCDView::OnUpdateViewLyricviewSpectrum(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//    pCmdUI->SetCheck(m_voiceSpectrum.GetVisible() ? 1 : 0);
	
}

void CCDView::OnViewSongInfo() 
{
	// TODO: Add your command handler code here
	m_lineSongLabel.SetVisible(!m_lineSongLabel.GetVisible());
    UpdateBuffer(false);
    UpdateScreen();
}

void CCDView::OnUpdateViewSongInfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_lineSongLabel.GetVisible() ? 1 : 0);
	pCmdUI->Enable();
}


void CCDView::OnViewNextImageNow() 
{
	// TODO: Add your command handler code here
    _ImageChangePostEvent(BkImageEventLoadNow);
    //PostMessage(WM_USER, 17, BkImageChangeEventLoadNow);	
}

void CCDView::OnViewSkipImageAlways() 
{
	// TODO: Add your command handler code here
    TRACE(_T("CCDView::OnViewSkipImageAlways In"));
    CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    CDBCentral * pDataCentral = DB();
    CDBTableV004 * pTable = pDataCentral->GetExcludedImageTable();
    TRACE(_T("CCDView::OnViewSkipImageAlways Middle 1"));
    pTable->AddText(m_strCurrentImagePath);
    TRACE(_T("CCDView::OnViewSkipImageAlways Middle 2"));
    pDataCentral->OnImagesDirsModified();
    TRACE(_T("CCDView::OnViewSkipImageAlways Middle 3"));
    //PostMessage(WM_USER, 17, BkImageChangeEventLoadNow);
    _ImageChangePostEvent(BkImageEventLoadNow);
	TRACE(_T("CCDView::OnViewSkipImageAlways Out"));
}

/*BOOL CCDView::RedrawWindow(CString str)
{

}
*/
VMSRESULT CCDView::Render(CDC * pdc, LPRECT lprect, bool bGdiLocked)
{
    CRect rectClient = lprect;
    if(lprect == NULL)
    {
        GetClientRect(rectClient);
    }
    else
    {
        rectClient = lprect;
    }
    CRect rectScreen = rectClient;
    ClientToScreen(rectScreen);
    CSingleLock slGdi(&m_csGdi);
    if(!bGdiLocked)
    {
        slGdi.Lock();
    }
//    m_ptwc->TWCRender(pdcForeground, this, rectClient, NULL, true);
    RenderView(pdc, rectClient, NULL,true);
//    SendMessage(WM_USER + 100, (WPARAM) this, (LPARAM) &rectScreen);
//    RenderTransparent(this, rectScreen, NULL, true);
    return VMSR_SUCCESS;
}


VMSRESULT CCDView::Render(CDC * pdc, CRgn *lprgn, bool bGdiLocked)
{
	ASSERT(FALSE);
    ASSERT(lprgn != NULL);

    CPoint ptOffset(0, 0);
    ClientToScreen(&ptOffset);

    CRgn rgnScreen;
    rgnScreen.CreateRectRgn(0, 0, 0, 0);
    rgnScreen.CopyRgn(lprgn);
    rgnScreen.OffsetRgn(ptOffset);

    CSingleLock slGdi(&m_csGdi);
    if(!bGdiLocked)
    {
        slGdi.Lock();
    }
    RenderView(pdc, NULL, lprgn, true);
//    SendMessage(WM_USER + 100, (WPARAM) this, (LPARAM) &rectScreen);
//    TwiRender(pdc, this, NULL, &rgnScreen, true, true);
    return VMSR_SUCCESS;
}


// lprect in client coordinates
VMSRESULT CCDView::RenderView(
    CDC * pdc,
    LPRECT lprect,
    CRgn * lprgn,
    bool bGdiLocked)
{
    
    ASSERT(pdc != NULL);
    CPoint ptViewport = pdc->GetViewportOrg();
	CRect rect;

    CWinApp * papp = AfxGetApp();
    if(papp == NULL)
    {
        // if main application is null, there's no reason
        // for painting anything...
        return VMSR_SUCCESS;
    }
    ASSERT(papp != NULL);
    
    int iEconoMode = CSavings::AppGetEconoMode();

//	CKaraokeSDIFrame * pframe = (CKaraokeSDIFrame *) GetParentFrame();
	CFrameWnd * pframe = GetParentFrame();
    if(pframe == NULL)
    {
        // if main frame is null, there's no reason
        // for painting anything...
        return VMSR_SUCCESS;
    }
    ASSERT(pframe != NULL);
    //ASSERT_KINDOF(CKaraokeSDIFrame, pframe);
	
    CXfplayerDoc *pdoc = GetDocument();
	ASSERT(pdoc != NULL); // if document is null, there's something wrong

    CMidiSequence *pseq = NULL;
    if(pdoc->GetMidiPlayer())
    {
	    pseq = pdoc->HelperGetMidiSequence();
    }

    
    CMidiFile * pfile = NULL;
    if(pseq)
    {
         pfile = pseq->GetFile();
    }
	
    CEventsTracksV1 * peventsarray = NULL;
    if(pfile)
    {
        peventsarray = &pfile->m_eventsTracksForPositionCB;
    }



//    CTypedPtrArray <CPtrArray, CVmsGdiFont *> *
  //      pFonts = GetLyricFonts();
    CVmsGdiFont *
        pfont = GetLyricFont();

	CDBCentral * pDataCentral = DB();

    CRect rectPlaylist;
	if(m_pplaylistframe != NULL)
    {
		m_pplaylistframe->GetWindowRect(rectPlaylist);
        ScreenToClient(rectPlaylist);
    }
/*    if(m_pplaylistipwnd != NULL)
    {
        m_pplaylistipwnd->GetWindowRect(rectPlaylist);
        ScreenToClient(rectPlaylist);
    }*/

	if(!::IsWindow(m_hWnd))
		return VMSR_SUCCESS;

    CRect rectClient;
    GetClientRect(rectClient);
    int cx = rectClient.Width();
    int cy = rectClient.Height();
    
	CLyricEventsV2 * pevents;
    if(peventsarray == NULL ||
        peventsarray->GetSize() <= pfile->m_str2aRawTokens.GetSize())
		pevents = NULL;
	else
	{
		pevents = (CLyricEventsV2 *) peventsarray->operator [](pfile->m_str2aRawTokens.GetSize());
		ASSERT(pevents != NULL);
		ASSERT(pevents->GetClassOrder() == 2);
	}

    CLyricEventsV2 * peventsBB = NULL;
    if(pfile != NULL && pfile->m_eventsTracksForBouncingBall.GetSize() > 0)
	{
        peventsBB = (CLyricEventsV2 *) pfile->m_eventsTracksForBouncingBall.operator [](0);
		ASSERT(peventsBB != NULL);
		ASSERT(peventsBB->GetClassOrder() == 2);
	}

	TEXTMETRIC & textMetric = pfont->m_tm;
    
    CSingleLock slGdi(&m_csGdi);
    if(!bGdiLocked)
    {
        slGdi.Lock();
    }


    CRgn rgnOld;
    CRect rectParam;
    if(lprgn != NULL)
    {
        rgnOld.CreateRectRgn(0, 0, 0, 0);
        GetClipRgn(pdc->GetSafeHdc(), rgnOld);
        CRgn rgn;
        rgn.CopyRgn(lprgn);
        rgn.OffsetRgn(ptViewport);
        pdc->SelectClipRgn(&rgn);
        lprgn->GetRgnBox(rectParam);
    }
    else if (lprect != NULL)
    {
        rgnOld.CreateRectRgn(0, 0, 0, 0);
        GetClipRgn(pdc->GetSafeHdc(), rgnOld);

        rectParam = lprect;
        CRgn rgn;
        rgn.CreateRectRgnIndirect(rectParam);
        rgn.OffsetRgn(ptViewport);
        pdc->SelectClipRgn(&rgn);
    }
    else
    {
        ASSERT(FALSE);
    }

    if(rectParam.Width() <= 0 || rectParam.Height() <= 0)
        return VMSR_SUCCESS;

	return RenderView(pdc, true);
}

VMSRESULT CCDView::RenderView(
    CDC * pdc,
    bool bGdiLocked)
{

	DWORD dwTimeIn = timeGetTime();
//	TRACE("CCDView::RenderView Enter dwTimeIn = %d\n", dwTimeIn);
    
    ASSERT(pdc != NULL);
    CPoint ptViewport = pdc->GetViewportOrg();
//	CRect rect;

    CWinApp * papp = AfxGetApp();
    if(papp == NULL)
    {
        // if main application is null, there's no reason
        // for painting anything...
        return VMSR_SUCCESS;
    }
    ASSERT(papp != NULL);
    
    int iEconoMode = CSavings::AppGetEconoMode();

	CFrameWnd * pframe = GetParentFrame();
    if(pframe == NULL)
    {
        // if main frame is null, there's no reason
        // for painting anything...
        return VMSR_SUCCESS;
    }
    ASSERT(pframe != NULL);
    //ASSERT_KINDOF(CKaraokeSDIFrame, pframe);
	
    CXfplayerDoc *pdoc = GetDocument();
	ASSERT(pdoc != NULL); // if document is null, there's something wrong

    CMidiSequence *pseq = NULL;
    if(pdoc->GetMidiPlayer())
    {
	    pseq = pdoc->HelperGetMidiSequence();
    }

    
    CMidiFile * pfile = NULL;
    if(pseq)
    {
         pfile = pseq->GetFile();
    }
	
    CEventsTracksV1 * peventsarray = NULL;
    if(pfile)
    {
        peventsarray = &pfile->m_eventsTracksForPositionCB;
    }



//    CTypedPtrArray <CPtrArray, CVmsGdiFont *> *
  //      pFonts = GetLyricFonts();
    CVmsGdiFont *
        pfont = GetLyricFont();

	CDBCentral * pDataCentral = DB();

    CRect rectPlaylist;
	if(m_pplaylistframe != NULL)
    {
		m_pplaylistframe->GetWindowRect(rectPlaylist);
        ScreenToClient(rectPlaylist);
    }

/*    if(m_pplaylistipwnd != NULL)
    {
        m_pplaylistipwnd->GetWindowRect(rectPlaylist);
        ScreenToClient(rectPlaylist);
    }*/

	if(!::IsWindow(m_hWnd))
		return VMSR_SUCCESS;

    CRect rectClient;
    GetClientRect(rectClient);
    int cx = rectClient.Width();
    int cy = rectClient.Height();
    
	CLyricEventsV2 * pevents;
    if(peventsarray == NULL ||
        peventsarray->GetSize() <= pfile->m_str2aRawTokens.GetSize())
		pevents = NULL;
	else
	{
		pevents = (CLyricEventsV2 *) peventsarray->operator [](pfile->m_str2aRawTokens.GetSize());
		ASSERT(pevents != NULL);
		ASSERT(pevents->GetClassOrder() == 2);
	}

    CLyricEventsV2 * peventsBB = NULL;
    if(pfile != NULL && pfile->m_eventsTracksForBouncingBall.GetSize() > 0)
	{
        peventsBB = (CLyricEventsV2 *) pfile->m_eventsTracksForBouncingBall.operator [](0);
		ASSERT(peventsBB != NULL);
		ASSERT(peventsBB->GetClassOrder() == 2);
	}

	TEXTMETRIC & textMetric = pfont->m_tm;
    
    CSingleLock slGdi(&m_csGdi);
    if(!bGdiLocked)
    {
        slGdi.Lock();
    }

	CRgn rgnClipOld;
	rgnClipOld.CreateRectRgn(0, 0, 0, 0);
	int iClipOld = ::GetClipRgn(pdc->GetSafeHdc(), rgnClipOld);

    CRect rectParam;
	CRgn rgnClip;
	rgnClip.CreateRectRgn(0, 0, 0, 0);

	
	
	if(::GetClipRgn(pdc->GetSafeHdc(), rgnClip) == 1)
	{
		rgnClip.GetRgnBox(rectParam);
		rectParam.OffsetRect(-ptViewport);
    }
    else
    {
		GetClientRect(rectParam);
    }

	rectParam.IntersectRect(rectParam, rectClient);

    if(rectParam.Width() <= 0 || rectParam.Height() <= 0)
        return VMSR_SUCCESS;


    CRect rectParamScreen;
    rectParamScreen = rectParam;
    ClientToScreen(rectParamScreen);

    DWORD timeM1 = timeGetTime();

	CRgn rgnx;
	rgnx.CreateRectRgn(0 , 0, 0, 0);
	int irgnx = ::GetClipRgn(pdc->GetSafeHdc(), rgnx);
    CRect rectx;
	rgnx.GetRgnBox(rectx);

	rgnx.DeleteObject();
	rgnx.CreateRectRgn(0 , 0, 0, 0);
	irgnx = ::GetClipRgn(pdc->GetSafeHdc(), rgnx);
	rgnx.GetRgnBox(rectx);

	pdc->BitBlt(
		rectParam.left, rectParam.top,
		rectParam.Width(), rectParam.Height(),
		&m_dcBack,
		rectParam.left, rectParam.top,
		SRCCOPY);

	rgnx.DeleteObject();
	rgnx.CreateRectRgn(0 , 0, 0, 0);
	irgnx = ::GetClipRgn(pdc->GetSafeHdc(), rgnx);
	rgnx.GetRgnBox(rectx);


	if(m_bTitleVisible && m_titleLines.GetSize() > 0)
	{
		RECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.right = cx;
		rect.bottom = cy;
        CCDViewLine objViewLine;
		CCDViewLine &refViewLine = objViewLine;
			int i;
		if(pdoc->m_bHasTitle)
		{
			refViewLine = m_titleLines[0];
			refViewLine.RenderLine(
                pdc,
				true,
				&rect,
				NULL,
				XFPLYR_LINE_RENDER_UPDATE,
				&count,
				CFontCentral::AppGetFontCentral()->GetTitleFonts(), 
				TRUE,
				m_crTitle,
				m_penTitle);
			i = 1;
		}
		else 
			i = 0;
		for(; i < m_titleLines.GetSize() ; i++)
		{
			refViewLine = m_titleLines[i];
			refViewLine.RenderLine(
                pdc,
				true,
				&rect,
				NULL,
				XFPLYR_LINE_RENDER_UPDATE,
				&count,
				CFontCentral::AppGetFontCentral()->GetSubTitleFonts(), 
				TRUE,
				m_crSubTitle,
				m_penSubTitle);
		}
	}

//    RECT rect;
//	rect.top = 0;
//	rect.left = 0;
///	rect.right = cx;
//	rect.bottom = cy;

	rgnx.DeleteObject();
	rgnx.CreateRectRgn(0 , 0, 0, 0);
	irgnx = ::GetClipRgn(pdc->GetSafeHdc(), rgnx);
	rgnx.GetRgnBox(rectx);

    CRect rectPlacement;
    CRect rectIntersect;
    
	pdc->GetClipBox(rectx);

	rgnx.DeleteObject();
	rgnx.CreateRectRgn(0 , 0, 0, 0);
	irgnx = ::GetClipRgn(pdc->GetSafeHdc(), rgnx);
	rgnx.GetRgnBox(rectx);

	m_lyricLines.m_bRenderEnable = true;
    if(m_lyricTemplateLines.GetSize() > 0 && 
            true)
		{
        int i;
            CLyricViewLine * lpViewLine = NULL;
            CRect rectLine;
        
        int iStartIndex, iEndIndex;
        iStartIndex = m_lyricLines.GetFirstVisibleLineIndex();
        if(iStartIndex >= m_lyricLines.GetSize())
            iStartIndex = m_lyricLines.GetSize() - 1;
        if(iStartIndex < 0)
            iStartIndex = 0;
        iEndIndex = m_lyricLines.GetLastVisibleLineIndex();
        if(iEndIndex < iStartIndex)
            iEndIndex = iStartIndex;
        if(iEndIndex >= m_lyricLines.GetSize())
            iEndIndex = m_lyricLines.GetSize() - 1;
        
        for( i = iStartIndex; i <= iEndIndex; i++)
			{
                lpViewLine = &m_lyricLines[i];
                if(lpViewLine->GetVisible())
                {
                    lpViewLine->GetPlacement(rectLine);
                    if(rectLine.IntersectRect(rectLine, rectParam))
                    {
					    lpViewLine->Render(
                            pdc,
							true,
						    rectClient,
						    NULL,
						    pdoc->m_iPlayingTokenIndex,
						    pdoc->m_iPlayingNoteIndex,
						    XFPLYR_LINE_RENDER_FULL,
						    &count,
						    pfont, 
						    pevents);
						pdc->GetClipBox(rectx);
                    }
                }
			}

		}
        DWORD timeM4 = timeGetTime();

//	CRect rectAudioSpectrum;
//	m_voiceSpectrum.GetPlacement(rectAudioSpectrum);
//	if(rectIntersect.IntersectRect(
//		rectAudioSpectrum,
//		rectParam))
//	{
//		m_voiceSpectrum.Render(
//			pdc);
//	}
	rgnx.DeleteObject();
	rgnx.CreateRectRgn(0 , 0, 0, 0);
    irgnx = ::GetClipRgn(pdc->GetSafeHdc(), rgnx);
	rgnx.GetRgnBox(rectx);

	RenderScore(pdc, false);

	rgnx.DeleteObject();
	rgnx.CreateRectRgn(0 , 0, 0, 0);
	irgnx = ::GetClipRgn(pdc->GetSafeHdc(), rgnx);
	rgnx.GetRgnBox(rectx);

    if(m_bBouncingBall && pseq != NULL &&
		pevents != NULL)
    {
        ASSERT(m_lpbouncingball != NULL);

        int iTokenIndexA = pdoc->m_iPlayingTokenIndex;

        if(iTokenIndexA < 0)
        {
            iTokenIndexA = 0;
        }
		CLyricViewLine * lpViewLine = NULL;
		int iLineIndex;
        int iNoteIndexA = pevents->GetTokenFirstNote(iTokenIndexA);
        if(0 <= (iLineIndex = 
            m_lyricLines.GetTokenLine(iTokenIndexA, &lpViewLine)))
        {
            m_lpbouncingball->Render(
                pdc,
				true,
                pfile,
                lpViewLine,
                NULL,
                peventsBB,
                GetSafeHwnd());
		}
                
        
    }
	rgnx.DeleteObject();
	rgnx.CreateRectRgn(0 , 0, 0, 0);
	irgnx = ::GetClipRgn(pdc->GetSafeHdc(), rgnx);
	rgnx.GetRgnBox(rectx);




	slGdi.Unlock();

	if(iClipOld == 1)
	{
		pdc->SelectClipRgn(&rgnClipOld);
	}
	else
	{
		pdc->SelectClipRgn(NULL);
	}


	DWORD dwTimeOut = timeGetTime();
//	TRACE("CCDView::RenderView Exit dwTimeOut = %d\n", dwTimeOut);
	DWORD dwTimeFunc = dwTimeOut - dwTimeIn;
//	TRACE("CCDView::RenderView Function Delta Time = %d\n", dwTimeFunc);

    return VMSR_SUCCESS;
}


VMSRESULT CCDView::UpdateScreen(
CTypedPtrArray <CObArray, CBaseRgn *> * lprgna, bool bGdiLocked)
{
    CSingleLock slGdi(&m_csGdi);
    if(bGdiLocked)
    {
        slGdi.Unlock();
    }

    CRgn rgnUpdated;
    rgnUpdated.CreateRectRgn(0, 0, 0, 0);
    CRgn rgnUpdate;
    rgnUpdate.CreateRectRgn(0, 0, 0, 0);
    for(int i = 0; i < lprgna->GetSize(); i++)
    {
        
        if(NULLREGION == rgnUpdate.CombineRgn(lprgna->ElementAt(i), &rgnUpdated, RGN_DIFF))
        {
            int i = 1;
        }
        else
        {
            UpdateScreen(&rgnUpdate, true);
        }
        rgnUpdated.CombineRgn(&rgnUpdated, lprgna->ElementAt(i), RGN_OR);
		delete lprgna->ElementAt(i);
    }
    // UpdateScreen(&rgnUpdated, true);
    if(bGdiLocked)
    {
        slGdi.Lock();
    }
	lprgna->RemoveAll();
    return VMSR_SUCCESS;
}

VMSRESULT CCDView::UpdateScreen(CRgn *lprgn, bool bGdiLocked)
{
	CRect rectRgn;
	lprgn->GetRgnBox(rectRgn);
	TwiRedraw(NULL, lprgn);
    //CDC * pdc = GetDC();
    //CRgn rgnOld;
    //rgnOld.CreateRectRgn(0, 0, 0, 0);
    //GetClipRgn(pdc->GetSafeHdc(), rgnOld);
    //int i = pdc->SelectClipRgn(lprgn);
    //if(i == 1)
    //{
//        ASSERT(FALSE);
//    }
    //CRect rect;
    //lprgn->GetRgnBox(rect);

    //CPoint ptOffset(0, 0);
    //ClientToScreen(&ptOffset);

//    CRgn rgnScreen;
  //  rgnScreen.CreateRectRgn(0, 0, 0, 0);
    //rgnScreen.CopyRgn(lprgn);
    //rgnScreen.OffsetRgn(ptOffset);

//    CSingleLock slGdi(&m_csGdi);
//    if(!bGdiLocked)
//    {
//        slGdi.Lock();
//    }
//    CDC * pdcForeground = TwiGetDC();
//    TwiRender(pdcForeground, this, NULL, &rgnScreen, true, true);
//    TwiReleaseDC(pdcForeground);

//    TwiDraw(pdc);
//    pdc->SelectClipRgn(&rgnOld);
//    ReleaseDC(pdc);
    return VMSR_SUCCESS;
NULLREGION;
//    TRACE(_T("CCDView::OnDraw slGdi.Lock\n"));
//	CRect rect = lprect;
    //CRect rectClient;
//    GetClientRect(rectClient);
  //  pDC->GetClipBox(rect);
//    pdc->SelectClipRgn(NULL);
//    prgn->GetRgnBox(rect);
//	TRACE(_T("CCDView::RenderWindow:\n"));
//	TRACE(_T("rect.left  : %d\n"), rect.left);
//	TRACE(_T("rect.top   : %d\n"), rect.top);
//	TRACE(_T("rect.right : %d\n"), rect.right);
//	TRACE(_T("rect.bottom: %d\n"), rect.bottom);

    
//    CPoint ptOffset(0, 0);
//    ClientToScreen(&ptOffset);

//    CRgn rgnScreen;
//    rgnScreen.CreateRectRgn(0, 0, 0, 0);
//    rgnScreen.CopyRgn(lprgn);
//    rgnScreen.OffsetRgn(ptOffset);

//    CSingleLock slGdi(&m_csGdi);
//    if(!bGdiLocked)
//    {
//        slGdi.Lock();
//    }
    //RenderTransparent(pdcForeground, this, NULL, &rgnScreen, true);

//    CRect rect;
//    lprgn->GetRgnBox(rect);
//	GdiFlush();
//end:;
    return VMSR_SUCCESS;
}

// lprect should be in client coordinates

VMSRESULT CCDView::UpdateScreen(LPRECT lprect, bool bGdiLocked)
{
	TwiRedraw(lprect, NULL);
    return VMSR_SUCCESS;
}





void CCDView::OnParentNotify(UINT message, LPARAM lParam) 
{
	CView::OnParentNotify(message, lParam);
	
}


afx_msg LRESULT CCDView::OnVMSTimer(WPARAM wParam, LPARAM lParam)
{
    
    OnTimer(wParam);

    return 0;
}


VMSRESULT CCDView::GetProgressRate(double * pdRate)
{
    double dRate;

  	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);

    if(pDoc->IsPlaying())
    {
        dRate = pDoc->GetProgressRate();
    }
    else
    {
        dRate = m_dProgressRate;
    }
	
    m_dwSliderLastUpdateTime = timeGetTime();

    *pdRate = dRate;

    return VMSR_SUCCESS;
}

VMSRESULT CCDView::SetProgressRate(double dRate)
{

    CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL);

    if(pDoc->IsPlaying())
    {
        pDoc->SetProgressRate(dRate, NULL);
    }
    else
    {
        m_dProgressRate = dRate;
        SetPlayingPosition_(m_dProgressRate);
    }

    return VMSR_SUCCESS;
}

bool CCDView::ShowBouncingBall(bool bShow)
{
	if(bShow)
	{
        m_bBouncingBall = true;
        PrepareLyricLines();
        PrepareLyricTemplateLines();
	}
	else
	{
        m_bBouncingBall = false;
        PrepareLyricLines();
		PrepareLyricTemplateLines();
	}
	CDBLongSet * pdbls = DB()->GetDBLongSet();
	DBSave(_T("Karaoke.Bouncing Ball"), (int) m_bBouncingBall);
    UpdateBuffer(false);
    UpdateScreen();
	return true;
}

void CCDView::OnViewBouncingball() 
{
	// TODO: Add your command handler code here
	if(m_bBouncingBall)
    {
		ShowBouncingBall(false);
    }
    else
	{
		ShowBouncingBall(true);
	}

}

void CCDView::OnUpdateViewBouncingball(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
    pCmdUI->SetCheck(
        m_bBouncingBall ? 1 : 0);
}

void CCDView::OnViewGradualfilling() 
{
	// TODO: Add your command handler code here
	if(m_bGradualFilling)
    {
        m_bGradualFilling = false;
    }
    else
        m_bGradualFilling = true;

    UpdateBuffer(false);
    UpdateScreen();

	
}

void CCDView::OnUpdateViewGradualfilling(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
    pCmdUI->SetCheck(
        m_bGradualFilling ? 1 : 0);
	
}

void CCDView::OnRefresh() 
{
	// TODO: Add your command handler code here
    UpdateBuffer(false);
    UpdateScreen();
}

void CCDView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	
}

afx_msg LRESULT CCDView::OnXfplayerViewMessage(WPARAM wParam, LPARAM lParam)
{
    if(wParam == VMSPN_XFVIEW_INIT)
    {
        LPXFPLAYERVIEWINIT lpviewinit = (LPXFPLAYERVIEWINIT) lParam;
        m_pthreadV1 = lpviewinit->pthreadV1;
        m_pthreadV2 = lpviewinit->pthreadV2;
        m_pthreadV3 = lpviewinit->pthreadV3;

    }
    return true;
}

/*CDC * CCDView::TWCGetBufferDC()
{
    return &m_dcBuffer;
}*/
void CCDView::OnViewBounceBall1() 
{
	// TODO: Add your command handler code here
    m_lpbouncingball->SetIcons(AfxGetApp()->LoadIcon(IDI_BB1),AfxGetApp()->LoadIcon(IDI_BB1_PRESSED1));	
}

void CCDView::OnViewBounceBall2() 
{
	// TODO: Add your command handler code here
    m_lpbouncingball->SetIcons(AfxGetApp()->LoadIcon(IDI_BB2), AfxGetApp()->LoadIcon(IDI_BB2_PRESSED1));	
	
}

void CCDView::TwiOnDraw(CDC * pdc)
{
    CSingleLock slGdi(&m_csGdi, TRUE);
    RenderView(pdc, true);
    slGdi.Unlock();
}

CVmsGdiFont *
	CCDView::GetLyricFont()
{
	CFrameWnd * pframe = GetParentFrame();
	if(pframe->IsKindOf(RUNTIME_CLASS(CKaraokeSDIFrame)))
	{
		CKaraokeSDIFrame * psdiframe = (CKaraokeSDIFrame *) pframe;
		if(psdiframe->m_bCompactSize)
			return CFontCentral::AppGetFontCentral()->GetLyricViewCompactFont();
		else
			return CFontCentral::AppGetFontCentral()->GetLyricViewFont();
	}
	else
	{
		return CFontCentral::AppGetFontCentral()->GetLyricViewFont();
	}
	

}

/*CTypedPtrArray <CPtrArray, CVmsGdiFont *> *
        CCDView::GetLyricFonts()
    {
CKaraokeSDIFrame * pframe = (CKaraokeSDIFrame *) GetParentFrame();

if(pframe->m_bCompactSize)
return CFontCentral::AppGetFontCentral()->GetLyricViewCompactFonts_();
else
return CFontCentral::AppGetFontCentral()->GetLyricViewFonts_();
    }*/

bool CCDView::IsPlaylistViewAttached()
{
//    return m_pplaylistipwnd != NULL;
	return m_pplaylistframe != NULL;
}

void CCDView::OnXfplayerMenubar() 
{
	// TODO: Add your command handler code here
        CVmpApp * pApp = (CVmpApp *) AfxGetApp();
        CRelationV001<UINT, UINT, UINT, UINT> * prel;
        CMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
        CMenuV033 menu(
            CMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
			CMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
            prel,
            CFontCentral::AppGetFontCentral()->GetMenuFont());
	    if (menu.LoadMenu(IDR_XFPLAYER_MENUBAR))
	    {
            CPoint point = GetCurrentMessage()->pt;
		    CMenuV033* pPopup = (CMenuV033 *) menu.GetSubMenu(0);
		    ASSERT(pPopup != NULL);
            CFrameWnd * pframe = GetParentFrame();
		    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			    point.x, point.y,
			    (CWnd *) pframe);
	    }	
}

void CCDView::RenderBack2()
{

    if(!m_bInitialized)
        return;


    CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    if(pApp == NULL)
    {
        // if main application is null, there's no reason
        // for painting anything...
        return;
    }
    ASSERT(pApp != NULL);
    
    int iEconoMode = CSavings::AppGetEconoMode();

	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL); // if document is null, there's something wrong

    
    CMidiSequence *pSeq = NULL;
    if(pDoc->GetMidiPlayer())
    {
	    pSeq = pDoc->HelperGetMidiSequence();
    }

    
    CMidiFile * pfile = NULL;
    if(pSeq)
    {
         pfile = pSeq->GetFile();
    }
	
    CEventsTracksV1 * peventsarray = NULL;
    if(pfile)
    {
        peventsarray = &pfile->m_eventsTracksForPositionCB;
    }


	CDBCentral * pDataCentral = DB();

    CRect rectPlaylist;
	if(m_pplaylistframe != NULL)
    {
		m_pplaylistframe->GetWindowRect(rectPlaylist);
        ScreenToClient(rectPlaylist);
    }
/*    if(m_pplaylistipwnd != NULL)
    {
        m_pplaylistipwnd->GetWindowRect(rectPlaylist);
        ScreenToClient(rectPlaylist);
    }*/

	if(!::IsWindow(m_hWnd))
		return;


    CRect rectClient;
    GetClientRect(rectClient);
    
    CRect rectScreen = rectClient;
    ClientToScreen(rectScreen);

    int cx = rectClient.Width();
    int cy = rectClient.Height();

	const int ciBufferBitmapNotCreated = 1;
	const int ciBackBitmapNotCreated = 2;
	const int ciBufferBitmapNotSelected = 3;
	const int ciBackBitmapNotSelected = 4;
	const int ciBufferBitmapInfoNotAvailable = 5;
	const int ciScaledBitmapInfoNotAvailable = 6;

	CSingleLock slGdi2(&m_csGdi2, TRUE);
    try
    {	
		BITMAP bmBack2;
		CreateBitmap(
			&m_dcBack2,
			&m_bmpBack2Old,
			&m_bmpBack2,
			&bmBack2,
			cx, cy);



        if(m_enhmetafile != NULL)
        {
			m_dcBack2.FillSolidRect(
				rectClient,
				RGB(30, 26, 21));
            
			CBaseRect rectMeta(0, 0, m_emh.rclBounds.right - m_emh.rclBounds.left, m_emh.rclBounds.bottom - m_emh.rclBounds.top);
            rectMeta.FitOnCenter(CRect(0, 0, 64, 64));
      
            int iW = rectMeta.Width();
            int iH = rectMeta.Height();
            int iXMod = (cx - iW) / 2;
            int iYMod = (cy - iH) / 2;
            int iXOffset =  iXMod;
            int iYOffset =  iYMod;
            iXOffset %= iW;
            while(iXOffset > 0)
            {
                iXOffset -= iW;
            }
            iYOffset %= iH;
            while(iYOffset > 0)
            {
                iYOffset -= iH;
            }
            int iCount = (iXMod < 0) ? 1 : cx / iW + (iXOffset == 0 ? 0 : 2);
            int jCount = (iYMod < 0) ? 1 : cy / iH + (iYOffset == 0 ? 0 : 2);

            rectMeta.left = iXOffset;
            for(int i = 0; i < iCount; i++)
            {
                rectMeta.top = iYOffset;
                for(int j = 0; j < jCount; j++)
                {
                    rectMeta.SetBottomRightSize(iW, iH);
			        m_dcBack2.PlayMetaFile(m_enhmetafile, rectMeta);
                    rectMeta.top += iH;
                }
                rectMeta.left += iW;
            }
        }
        else if(m_bFullScreen)
		{
			m_dcBack2.FillSolidRect(
				rectClient,
				0);
		}
		else
		{
			m_dcBack2.FillSolidRect(
				rectClient,
				GetSysColor(COLOR_APPWORKSPACE));
		}
    
		if(m_bmpSource.m_hObject != NULL)
		{

            BITMAP bmSource;
			if(!m_bmpSource.GetBitmap(&bmSource))
			{
				TRACE0("Mem Bitmap info not available.\n");
				throw ciScaledBitmapInfoNotAvailable;
			}


            int finalX;
            int finalY;
            int finalW;
            int finalH;
            
            double dRate;
            if(m_iBkImageFlags == ifZoomAll)
            {
                dRate = min((double) cx / bmSource.bmWidth, (double) cy / bmSource.bmHeight);
			    finalW = (int) (bmSource.bmWidth * dRate);
			    finalH = (int)(bmSource.bmHeight * dRate);
			    finalX = (cx - finalW) / 2;
			    finalY = (cy - finalH) / 2;
            }
            else if (m_iBkImageFlags == ifZoomExtend)
            {
                dRate = max((double) cx / bmSource.bmWidth, (double) cy / bmSource.bmHeight);
			    finalW = (int) (bmSource.bmWidth * dRate);
			    finalH = (int) (bmSource.bmHeight * dRate);
			    finalX = (cx - finalW) / 2;
			    finalY = (cy - finalH) / 2;
            }
            else if (m_iBkImageFlags == ifStretch)
            {
			    finalW = (int) cx;
			    finalH = (int) cy;
			    finalX = 0;
			    finalY = 0;
            }

            if(m_iBkImageFlags == ifTile)
            {
        		
                int iW = bmSource.bmWidth;
                int iH = bmSource.bmHeight;
                int iXMod = (cx - iW) / 2;
                int iYMod = (cy - iH) / 2;
                int iXOffset =  iXMod;
                int iYOffset =  iYMod;
                while(iXOffset > 0)
                {
                    iXOffset -= iW;
                }
                while(iYOffset > 0)
                {
                    iYOffset -= iH;
                }
                int iCount = (iXMod < 0) ? 1 : cx / iW + (iXOffset == 0 ? 0 : 2);
                int jCount = (iYMod < 0) ? 1 : cy / iH + (iYOffset == 0 ? 0 : 2);
                for(int i = 0; i < iCount; i++)
                {
                    int iX = iXOffset + iW * i;
                    for(int j = 0; j < jCount; j++)
                    {
                        int iY = iYOffset + iH * j;
			            m_dcBack2.BitBlt(
				               iX, iY,
				               iW, iH,
				               &m_dcSource,
				               0, 0,
				               SRCCOPY);
                    }
                }
            }
            else if(m_iBkImageFlags == ifZoomAll ||
                m_iBkImageFlags == ifZoomExtend ||
                m_iBkImageFlags == ifStretch)
            {
                
                int srcX = 0;
                int srcY = 0;
                int srcW = bmSource.bmWidth;
                int srcH = bmSource.bmHeight;
                
			    m_dcBack2.StretchBlt(
				       finalX, finalY,
				       finalW, finalH,
				       &m_dcSource,
				       srcX, srcY,
                       srcW, srcH,
				       SRCCOPY);
            }
            else if(m_lineSongLabel.GetVisible() && ! m_bCompactMode)
            {
                CImaging::GetImaging()->ColorBlend(&m_dcBack2, 0, m_lineSongLabel.m_iTop, cx, m_lineSongLabel.m_iBottom - m_lineSongLabel.m_iTop, RGB(255, 255, 255), 127);
            }
    	}
        if(m_bCompactMode)
        {
            CImaging::GetImaging()->ColorBlend(
                &m_dcBack2,
                rectClient.left ,
                rectClient.top,
                rectClient.Width(),
                rectClient.Height(),
                RGB(116, 160, 220), 190);
        }
    }
    catch(int)
    {
    }
	


}

bool CCDView::SetCompactMode(bool bCompact)
{
    bool b = m_bCompactMode;
    m_bCompactMode = bCompact;
    return b;

}

bool CCDView::SetFullScreen(bool bFullScreen)
{
    bool b = m_bFullScreen;
    m_bFullScreen = bFullScreen;
    return b;

}

void CCDView::Layout()
{


    if(!m_bInitialized)
        return;


	CRect rectClient;
	GetClientRect(rectClient);

	int cx = rectClient.Width();
	int cy = rectClient.Height();




    CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    if(pApp == NULL)
    {
        // if main application is null, there's no reason
        // for painting anything...
        return;
    }
    ASSERT(pApp != NULL);
    
    int iEconoMode = CSavings::AppGetEconoMode();

	CFrameWnd * pframe = GetParentFrame();
    if(pframe == NULL)
    {
        // if main frame is null, there's no reason
        // for painting anything...
        return;
    }

//    CRect rectClient;
  //  GetClientRect(rectClient);


//    int cx = rectClient.Width();
  //  int cy = rectClient.Height();


    if(cx <= 0 || cy <= 0)
        return;

    CSingleLock slGdi(&m_csGdi, true);

	BITMAP bmBack;
	VERIFY(CreateBitmap(
			&m_dcBack,
			&m_bmpBackOld,
			&m_bmpBack,
			&bmBack,
			cx, cy));

	slGdi.Unlock();

    ASSERT(pframe != NULL);
	CXfplayerDoc *pDoc = GetDocument();
	ASSERT(pDoc != NULL); // if document is null, there's something wrong

    
    CMidiSequence *pSeq = NULL;
    if(pDoc->GetMidiPlayer())
    {
	    pSeq = pDoc->HelperGetMidiSequence();
    }

    
    CMidiFile * pfile = NULL;
    if(pSeq)
    {
         pfile = pSeq->GetFile();
    }
	
    CEventsTracksV1 * peventsarray = NULL;
    if(pfile)
    {
        peventsarray = &pfile->m_eventsTracksForPositionCB;
    }

//    CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts = NULL;
  //  if(pApp)
    //{
      //  pFonts = GetLyricFonts();
    //}
	CVmsGdiFont * pfont = NULL;
    if(pApp)
	{
		pfont = GetLyricFont();
    }

	CDBCentral * pDataCentral = DB();

    CRect rectPlaylist;
	if(m_pplaylistframe != NULL)
    {
		m_pplaylistframe->GetWindowRect(rectPlaylist);
        ScreenToClient(rectPlaylist);
    }
/*    if(m_pplaylistipwnd != NULL)
    {
        m_pplaylistipwnd->GetWindowRect(rectPlaylist);
        ScreenToClient(rectPlaylist);
    }*/

	if(!::IsWindow(m_hWnd))
		return;


    PrepareProgressSlider();

    PrepareSongLabelLine();

    LayoutLyricTemplateLines(true);

	LayoutLyricLines(true);

	LayoutKaraokeBouncingBall();


	CLyricEventsV2 * pevents;
    if(peventsarray == NULL ||
        peventsarray->GetSize() <= pfile->m_str2aRawTokens.GetSize())
		pevents = NULL;
	else
	{
		pevents = (CLyricEventsV2 *) peventsarray->operator [](pfile->m_str2aRawTokens.GetSize());
		ASSERT(pevents != NULL);
		ASSERT(pevents->GetClassOrder() == 2);
	}
	m_lineScore.m_iRight = cx;
	m_lineScore.m_iTop = m_iRightVerticalShift;

	m_lineScore.PrepareLine(
        &m_dcScreen,
		L"0",
		0,
		GetLyricFont(),
		rectClient);

	int iBottom;
	if(m_lineScore.GetVisible())
	{
		iBottom = m_lineScore.m_iBottom;
	}
	else
	{
		iBottom = m_iRightVerticalShift;
	}



	TEXTMETRIC textMetric;
//	if(pFonts->GetSize() > 0)
//	{
//		m_dcScreen.SelectObject(pFonts->operator [](0)->GetFont());
		m_dcScreen.SelectObject(pfont->GetFont());
		m_dcScreen.GetTextMetrics(&textMetric);
//	}
//	m_voiceSpectrum.SetPlacement(
//		&m_dcScreen,
//		cx / 100,
//		cx / 100,
//		cx / 6,
//		cy / 7);

	CWStr wstr;
    
    CVmsGdiFont * lpFontSongLabel = CFontCentral::AppGetFontCentral()->GetSongLabelFont();
    

    slGdi.Lock();

    m_dcScreen.SelectObject(&m_font);
	m_dcScreen.GetTextMetrics(&textMetric);

	int iStartTop = 100;
    if(m_titleLines.GetSize() > 0)
	{
        CCDViewLine objViewLine;
		CCDViewLine &refViewLine = objViewLine;
		int i, yPos;
		if(m_titleLines.GetSize() >= 1)
		{
			m_dcScreen.SelectObject(pfont->GetFont());
			refViewLine = m_titleLines[0];
//            if(m_pplaylistipwnd != NULL)
			if(m_pplaylistframe != NULL)
            {
                //refViewLine.m_iTop = max(max(rectPlaylist.bottom, m_voiceSpectrum.GetBottom()), rectSliderKeyShift.bottom);
				//refViewLine.m_iTop = max(max(rectPlaylist.bottom, iStartTop), rectSliderKeyShift.bottom);
				refViewLine.m_iTop = max(rectPlaylist.bottom, iStartTop);
            }
            else
            {
                //refViewLine.m_iTop = m_voiceSpectrum.GetBottom();
				refViewLine.m_iTop = iStartTop;
            }
		}
		if(m_titleLines.GetSize() >= 2)
		{
			if(pDoc->m_bHasTitle)
			{
				m_dcScreen.SelectObject(CFontCentral::AppGetFontCentral()->GetTitleFonts()->operator [](0)->GetFont());
				m_dcScreen.GetTextMetrics(&textMetric);
				yPos = refViewLine.m_iTop + textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading;
			}
			m_dcScreen.SelectObject(CFontCentral::AppGetFontCentral()->GetSubTitleFonts()->operator [](0)->GetFont());
			m_dcScreen.GetTextMetrics(&textMetric);
			if(!pDoc->m_bHasTitle)
			{
				yPos = refViewLine.m_iTop + textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading;
			}
			int pos;
			for(pos = yPos, i = 1; i < m_titleLines.GetSize() ; i++)
			{
				refViewLine = m_titleLines[i];
				refViewLine.m_iTop = pos;
				pos += textMetric.tmHeight + textMetric.tmInternalLeading + textMetric.tmExternalLeading;
			}
		}
	}
    slGdi.Unlock();

	m_transparentframewnda.Update(this);
	m_transparentframewnda.Layout();

}

void CCDView::OnTwiInitialize()
{
    UpdateDrawingObjects();

    if(LoadNextImage(true))
    {
        m_bkImageChangeState = BkImageStateLoading;
    }
    else
    {
        m_bkImageChangeState = BkImageStateTiming;
    }

}



bool CCDView::CreateBitmap(CDC *pdc, CBitmap *pbitmapOld, CBitmap *pbitmap, BITMAP * pbmp, int cx, int cy)
{
	int cxout = cx + 30;
	int cyout = cy + 30;

	pdc->SelectObject(pbitmapOld);
	bool bCreate = true;
	if(pbitmap->m_hObject != NULL)
	{
		if(!pbitmap->GetBitmap(pbmp))
		{
			return false;
		}
		if(pbmp->bmWidth >= cx &&
			pbmp->bmHeight >= cy)
		{
			bCreate = false;
		}
		
	}
	if(bCreate)
	{
		pbitmap->DeleteObject();
		if(!pbitmap->CreateCompatibleBitmap(&m_dcScreen, cxout, cyout))
		{
			return false;
		}
	}
	if(!pdc->SelectObject(pbitmap))
	{
		return false;
	}
	if(bCreate)
	{
		pdc->FillSolidRect(CRect(0, 0, cxout, cyout), RGB (0, 0, 0));
	}
	return true;

}


void CCDView::PrepareBouncingBall()
{
	m_lpbouncingball->Prepare();
}

void CCDView::OnChangeCompactMode(CCDViewUpdateHint *puh)
{
    PrepareLyricTemplateLines();
	PrepareLyricLines();
	PrepareBouncingBall();
	CRect rectClient;
	GetClientRect(rectClient);
	TwiRedraw(rectClient);
}

void CCDView::OnChangeFullScreen(CCDViewUpdateHint *puh)
{
    PrepareLyricTemplateLines();
	PrepareLyricLines();
	PrepareBouncingBall();
}

bool CCDView::ShowAudioSpectrum(bool bShow)
{
	if(bShow)
	{
		CXfplayerDoc * pdoc = GetDocument();
		CDocument * pdocNew = (CDocument *) pdoc->OpenAudioSpectrumDoc(true);
		if(pdocNew != NULL)
		{
			CTransparentFrameWndV8 * pframe = pdoc->GetAudioSpectrumFrame();
			pframe->TransparentFrameWndSetChildModeParent(GetSafeHwnd());
			pframe->SetMaxSize(&CSize(400, 200), true);
			pframe->SetMinSize(&CSize(50, 50), true);
			pframe->GetWndFramework()->AddListener(this);
		}
		int iShow = 1;
		DBSave(_T("AudioSpectrum.Show"), iShow);
		GetParentFrame()->SetActiveView(this);
	}
	else
	{
		CXfplayerDoc * pdoc = GetDocument();
		pdoc->CloseAllAudioSpectrumDocuments();
		int iShow = 0;
		DBSave(_T("AudioSpectrum.Show"), iShow);
	}
	m_transparentframewnda.Update(this);
	return true;

}
bool CCDView::ShowLevelMeter(bool bShow)
{
	if(bShow)
	{
		CXfplayerDoc * pdoc = GetDocument();
		CDocument * pdocNew = (CDocument *) pdoc->OpenLevelMeterDoc(true);
		if(pdocNew != NULL)
		{
			CTransparentFrameWndV8 * pframe = (CTransparentFrameWndV8 *) pdoc->GetLevelMeterFrame();
			pframe->TransparentFrameWndSetChildModeParent(GetSafeHwnd());
			pframe->SetMaxSize(&CSize(400, 200), true);
			pframe->SetMinSize(&CSize(50, 50), true);
			pframe->ShowWindow(SW_SHOWNORMAL);
			pframe->GetWndFramework()->AddListener(this);
		}

		int iShow = 1;
		DBSave(_T("LevelMeter.Show"), iShow);
		GetParentFrame()->SetActiveView(this);	
	}
	else
	{

		CXfplayerDoc * pdoc = GetDocument();
		pdoc->CloseAllLevelMeterDocuments();
		int iShow = 0;
		DBSave(_T("LevelMeter.Show"), iShow);
	}
	m_transparentframewnda.Update(this);
	return true;
}

afx_msg LRESULT  CCDView::OnAppLanguage(WPARAM wParam, LPARAM lParam)
{
	if(wParam == CVmsGenApp::WPARAM_LANGUAGE_UPDATE)
	{
		Layout();
	}
	return 0;
}
afx_msg LRESULT CCDView::OnAppNotify(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case APPN_CHILDDELETE:
		{
			ASSERT(FALSE);
			/*void * lpvoid = (void *) lParam;
			if(lpvoid == m_pkcs1wndLevelMeter)
			{
				m_pkcs1wndLevelMeter = NULL;
			}
			else if(lpvoid == m_plevelmeterwnd)
			{
				m_plevelmeterwnd = NULL;
			}
			else if(lpvoid == m_pkcs1wndAudioSpectrum)
			{
				m_pkcs1wndAudioSpectrum = NULL;
			}
			else if(lpvoid == m_paudiospectrumwnd)
			{
				m_paudiospectrumwnd = NULL;
			}*/

		}
		break;
	case APPN_OPENLINK:
		{
			LPCWSTR lpcsz = (LPCWSTR) lParam;
			CString str;
			CInternational::UnicodeToOEM(str, lpcsz);
			::ShellExecute(m_hWnd, _T("open"), str, NULL, NULL, SW_RESTORE);
		}
		break;

	}
	return 0;
}

void CCDView::OnWindowLevelmeter() 
{
	CXfplayerDoc * pdoc = GetDocument();
	ShowLevelMeter(!pdoc->IsLevelMeterOpened());
	CTransparentFrameWndV8 * pframe = pdoc->GetLevelMeterFrame();
	if(pframe != NULL)
	{
		pframe->TransparentFrameWndFrame();
	}
	
}

void CCDView::OnViewLevelmeter() 
{
	CXfplayerDoc * pdoc = GetDocument();
	ShowLevelMeter(!pdoc->IsLevelMeterOpened());
	CTransparentFrameWndV8 * pframe = pdoc->GetLevelMeterFrame();
	if(pframe != NULL)
	{
		pframe->TransparentFrameWndChild();
	}
}

void CCDView::OnScoringEnable(bool bEnable)
{
	m_lineScore.SetVisible(bEnable);
	Layout();
}


void CCDView::OnViewAudiospectrum() 
{
	CXfplayerDoc * pdoc = GetDocument();
	ShowAudioSpectrum(!pdoc->IsAudioSpectrumOpened());
	CTransparentFrameWndV8 * pframe = pdoc->GetAudioSpectrumFrame();
	if(pframe != NULL)
	{
		pframe->TransparentFrameWndChild();
	}

}

void CCDView::OnWindowAudiospectrum() 
{
	CXfplayerDoc * pdoc = GetDocument();
	ShowAudioSpectrum(!pdoc->IsAudioSpectrumOpened());
	CTransparentFrameWndV8 * pframe = pdoc->GetAudioSpectrumFrame();
	if(pframe != NULL)
	{
		pframe->TransparentFrameWndFrame();
	}
	
}

void CCDView::OnViewPlayercontrolsetv19() 
{
	CXfplayerDoc * pdoc = GetDocument();
	ShowPlayerControlSetV19(!pdoc->IsPlayerControlSetV19ViewOpened());
	CTransparentFrameWndV8 * pframe = pdoc->GetPlayerControlSetV19Frame();
	if(pframe != NULL)
	{
		pframe->TransparentFrameWndChild();
	}
}

void CCDView::OnUpdateViewPlayercontrolsetv19(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	CXfplayerDoc * pdoc = GetDocument();
	pCmdUI->SetCheck(
		pdoc->IsPlayerControlSetV19ViewOpened());
}

void CCDView::OnWindowPlayercontrolsetv19() 
{
	CXfplayerDoc * pdoc = GetDocument();
	ShowPlayerControlSetV19(!pdoc->IsPlayerControlSetV19ViewOpened());
	CTransparentFrameWndV8 * pframe = pdoc->GetPlayerControlSetV19Frame();
	if(pframe != NULL)
	{
		pframe->TransparentFrameWndFrame();
	}
	
}

void CCDView::OnUpdateWindowPlayercontrolsetv19(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	CXfplayerDoc * pdoc = GetDocument();
	pCmdUI->SetCheck(
		pdoc->IsPlayerControlSetV19ViewOpened());

}


void CCDView::OnUpdateWindowLevelmeter(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	CXfplayerDoc * pdoc = GetDocument();
	pCmdUI->SetCheck(
		pdoc->IsLevelMeterOpened());
}

void CCDView::OnUpdateWindowAudiospectrum(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	CXfplayerDoc * pdoc = GetDocument();
	pCmdUI->SetCheck(
		pdoc->IsAudioSpectrumOpened());
	
}

void CCDView::OnUpdateViewLevelmeter(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	CXfplayerDoc * pdoc = GetDocument();
	pCmdUI->SetCheck(
		pdoc->IsLevelMeterOpened());
	
}

void CCDView::OnUpdateViewAudiospectrum(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	CXfplayerDoc * pdoc = GetDocument();
	pCmdUI->SetCheck(
		pdoc->IsAudioSpectrumOpened());
	
	
}


bool CCDView::TextDocHelperAdd(CWStr &wstr)
{
	CVmpApp * papp = (CVmpApp *) AfxGetApp();
	if(m_pvmstextdocHelper == NULL)
	{
		m_pvmstextdocHelper = papp->OpenTextFile(NULL);
	}
	if(m_pvmstextdocHelper == NULL)
		return false;
	CString str = wstr;
	m_pvmstextdocHelper->GetView()->GetRichEditCtrl().ReplaceSel(str);
	return true;
}

BOOL CCDView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	CFrameWnd * pframewnd = m_pplaylistframe;
	CWnd * pwndFocus = CWnd::GetFocus();
	if(pwndFocus != NULL)
	{
		pwndFocus = FromHandlePermanent(pwndFocus->m_hWnd);
	}
    if(pframewnd != NULL 
        && (pframewnd = (CFrameWnd *) FromHandlePermanent(pframewnd->m_hWnd)) != NULL 
        && pframewnd != NULL
		&&
			(pwndFocus == NULL
			||	pframewnd == pwndFocus
			|| 
				(pframewnd->GetActiveView() != NULL &&
				pframewnd->GetActiveView() == pwndFocus
				)
			)
		)
	{
		if(pframewnd->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
			return TRUE;
	}

	return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CCDView::OnPointerClear(CPlaylistDoc *pdoc)
{

}



bool CCDView::IsCompactMode()
{
	CKaraokeSDIFrame * psdiframe = GetKaraokeSDIFrame();
	if(psdiframe == NULL)
		return false;
	else
		return psdiframe->m_bCompactSize;
}

CKaraokeSDIFrame * CCDView::GetKaraokeSDIFrame()
{
	CFrameWnd * pframe = GetParentFrame();
	if(pframe->IsKindOf(RUNTIME_CLASS(CKaraokeSDIFrame)))
		return (CKaraokeSDIFrame *) pframe;
	else
		return NULL;

}

void CCDView::LayoutDynamicChild(bool bMakeVisible)
{
	m_transparentframewnda.Update(this);
	m_transparentframewnda.Layout();
	return;





	CRect rectClient;
	CBaseRect rectFrame;
	GetClientRect(rectClient);
	CWnd * pwnd = GetTopWindow();
	while(pwnd != NULL)
	{
		if(pwnd->IsKindOf(RUNTIME_CLASS(CTransparentFrameWndV4)))
		{
			CTransparentFrameWndV4 * pframe = (CTransparentFrameWndV4 *) pwnd;
			pframe->GetWindowRect(rectFrame);
			ScreenToClient(rectFrame);
			rectFrame.ConstraintV5(rectClient, CSize(30, 30));
			UINT nFlags;
			if(pframe->IsWindowVisible()
				|| bMakeVisible)
				nFlags = SWP_SHOWWINDOW
							| SWP_NOZORDER;
			else
				nFlags = SWP_HIDEWINDOW
							| SWP_NOZORDER;
			pframe->SetWindowPos(
				0,
				rectFrame.left,
				rectFrame.top,
				rectFrame.Width(),
				rectFrame.Height(),
				nFlags);
		}
		pwnd = pwnd->GetNextWindow();
	}

}

bool CCDView::ShowPlayerControlSetV19(bool bShow)
{
	if(bShow)
	{
		CXfplayerDoc * pdoc = GetDocument();
		CDocument * pdocNew = (CDocument *) pdoc->OpenPlayerDoc(true);
		if(pdocNew != NULL)
		{
			CPlayerControlSetV19Frame * pframe = pdoc->GetPlayerControlSetV19Frame();
			pframe->TransparentFrameWndSetChildModeParent(GetSafeHwnd());
			pframe->GetWndFramework()->AddListener(this);
			pframe->ShowWindow(SW_SHOWNORMAL);
		}
		int iShow = 1;
		DBSave(_T("PlayerControlSetV19.Show"), iShow);
	}
	else
	{
		CXfplayerDoc * pdoc = GetDocument();
		CPlayerDoc * pplayerdoc = pdoc->GetPlayerDoc();
		if(pplayerdoc != NULL)
		{
			POSITION pos = pplayerdoc->GetFirstViewPosition();
			CView * pview;
			while(pos != NULL)
			{
				pview = pplayerdoc->GetNextView(pos);
				if(pview->IsKindOf(RUNTIME_CLASS(CPlayerControlSetV19View)))
				{
					pplayerdoc->RemoveView(pview);
				}
			}
		}
		int iShow = 0;
		DBSave(_T("PlayerControlSetV19.Show"), iShow);
	}
	m_transparentframewnda.Update(this);
	return true;

}




void CCDView::WFLOnDock(CWndFrameworkV033 *pwf, CWnd *pwnd)
{
	m_transparentframewnda.Update(this);
	m_transparentframewnda.Layout();
}

void CCDView::OnOpenLink() 
{
	ASSERT(!m_wstrCurrentLink.IsEmpty());	
	CString str;
	CInternational::UnicodeToOEM(str, m_wstrCurrentLink);
	::ShellExecute(m_hWnd, _T("open"), str, NULL, NULL, SW_RESTORE);

}

bool CCDView::Initialize()
{
	CVmpApp * papp = (CVmpApp *) AfxGetApp();

    CXfplayerDoc * pdoc = GetDocument();
	
	CFrameWnd     * pframe = GetParentFrame();
	
	pframe->SetActiveView(this);

	RECT rect;
	GetClientRect(&rect);

    
	if(papp->m_cmdinfo.m_nShellCommand !=
		CCommandLineInfo::FileDDE)
	{
		if(!m_bInitialized)
		{
			
			int iShow = 0;
			DBLoad(_T("LevelMeter.Show"), iShow);
			ShowLevelMeter(iShow != 0);
						
			iShow = 0;
			DBLoad(_T("AudioSpectrum.Show"), iShow);
			ShowAudioSpectrum(iShow != 0);

			iShow = 0;
			DBLoad(_T("PlayerControlSetV19.Show"), iShow);
			ShowPlayerControlSetV19(iShow != 0);
		}
	}

	SetOnSizeEnabled();
	if(!m_bInitialized)
	{
		int iShow = m_bBouncingBall ? 1 : 0;
		DBLoad(_T("Karaoke.Bouncing Ball"), iShow);
		ShowBouncingBall(iShow != 0);

	}


    m_dwLastShiftUpdate = 0;
    CView::OnInitialUpdate();
	CCDViewUpdateHint uh;
	uh.SetType(CCDViewUpdateHint::UpdateStart);
	pdoc->UpdateAllViews(NULL, 0, &uh);

	m_bInitialized = true;

	Layout();
    RenderBack2();
    UpdateBuffer(false);
    UpdateScreen();

	if(m_ptimerwnd == NULL)
	{
		LPTIMERCALLBACKCREATETIMER lptcct = new TIMERCALLBACKCREATETIMER;
		lptcct->m_pTimerCallback = this;
		lptcct->m_uiElapse = 5;
		lptcct->m_uiIDEvent = 1;
		papp->GetThreadV1()->PostThreadMessage(
			VMSM_V001,
			NOTIFY_TIMERCALLBACKCREATETIMER,
			(LPARAM) lptcct);
	}


	
	return true;
}


void CCDView::WFLOnClose(
	CWndFrameworkV033 * pwf,
	CWnd * pwnd)
{
	if(pwnd->IsKindOf(RUNTIME_CLASS(CTransparentFrameWndV8)))
	{
		CTransparentFrameWndV8 * pframe = (CTransparentFrameWndV8 *) pwnd;
		CView * pview = pframe->GetActiveView();
		if(pview->IsKindOf(RUNTIME_CLASS(CLevelMeterView)))
		{
			DBSave(_T("LevelMeter.Show"), 0);
		}
		else if(pview->IsKindOf(RUNTIME_CLASS(CAudioSpectrumView)))
		{
			DBSave(_T("AudioSpectrum.Show"), 0);
		}
	}
	else if(pwnd->IsKindOf(RUNTIME_CLASS(CPlayerControlSetV19Frame)))
	{
		CPlayerControlSetV19Frame * pframe = (CPlayerControlSetV19Frame *) pwnd;
		CView * pview = pframe->GetActiveView();
		if(pview->IsKindOf(RUNTIME_CLASS(CPlayerControlSetV19View)))
		{
			DBSave(_T("PlayerControlSetV19.Show"), 0);
		}
	}

}

bool CCDView::TwiHasTranslucency()
{
	return false;
}

UINT AFX_CDECL CCDView::ThreadProcTransitionEffectRunStep(LPVOID lpParameter)
{
    ::SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_IDLE);
    CCDView * pview = (CCDView *) lpParameter;
	srand((unsigned int) time(NULL));
	try
	{

		while(AfxIsValidAddress(pview, sizeof(CCDView), TRUE)
			&& ::IsWindow(pview->m_hWnd))
		{
			pview->m_evTransitionEffectRunStep.Lock();
			pview->m_evTransitionEffectRunStep.ResetEvent();
			pview->_ImageChangeTransitionEffectRunStep();
		}
	}
	catch(...)
	{
		ASSERT(FALSE);
	}
	try
	{
		pview->m_pthreadTransitionEffectRunStep = NULL;
	}
	catch(...)
	{
		ASSERT(FALSE);
	}

    return 0;
}


void CCDView::TransitionEffectRunStepAsync()
{
	m_evTransitionEffectRunStep.SetEvent();
}

CWinThread * CCDView::CreateTransitionEffectRunStepThread()
{
	return AfxBeginThread(
		ThreadProcTransitionEffectRunStep,
		this,
		THREAD_PRIORITY_NORMAL,
		0,
		0,
		NULL);
}











