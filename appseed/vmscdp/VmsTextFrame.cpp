// VmsTextFrame.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "VmsTextFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "WndFrameworkV033.h"
#include "MenuCentral.h"
#include "FontCentral.h"

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CVmsTextFrame

IMPLEMENT_DYNCREATE(CVmsTextFrame, CTransparentFrameWnd)

CVmsTextFrame::CVmsTextFrame()
{
}

CVmsTextFrame::~CVmsTextFrame()
{
}


BEGIN_MESSAGE_MAP(CVmsTextFrame, CTransparentFrameWnd)
	//{{AFX_MSG_MAP(CVmsTextFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmsTextFrame message handlers

int CVmsTextFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	m_strRegistrySection = "VmsText";
	if (CTransparentFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

    CWnd * pwnd = GetParent();

    SetDlgCtrlID(AFX_IDW_PANE_FIRST);

    int _db_style = GetStyle();
    CWinApp * pApp = AfxGetApp();
	
    CMenu * pMenu = GetMenu();

    m_hMenuDefault = NULL;
    SetMenu(NULL);
    //CMenu * pmenuDebug =GetMenu();
    if(pMenu != NULL)
    {
        pMenu->DestroyMenu();
    }



	
//	CDBCentral * pDataCentral = DB();
//	CDBLongSet * plongset = pDataCentral->GetDBLongSet();
	CWnd * pParent = GetParent();

    

/*	int iFullScreen = 0;
    plongset->Load(_T("Main Frame"), _T("Full Screen"), &iFullScreen);
	int iCompactMode = 1;
	plongset->Load(_T("Main Frame"), _T("Compact Mode"), &iCompactMode);

	
    //if(
    
    ViewCompactMode(iCompactMode != 0);
	ViewFullScreen(iFullScreen != 0);*/

//	m_bOnSizeSaving = true;
//	UpdateBars();
	return 0;
	
}




BOOL CVmsTextFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	m_uiIDMenuBar = IDR_VMSTEXT;
	if(!CTransparentFrameWnd::OnCreateClient(lpcs, pContext))
		return FALSE;
	    if (!m_wndToolBarStandard.CreateEx(
        this,
        TBSTYLE_FLAT  |
        TBSTYLE_LIST , //|
//        TBSTYLE_WRAPABLE,
        WS_CHILD | CBRS_ALIGN_TOP,// |
//        CBRS_TOOLTIPS | CBRS_FLYBY, 
        CRect(0, 0, 0, 0),
        IDR_VMSTEXT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
    if (!m_wndToolBarStandard.LoadToolBar(IDR_VMSTEXT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
    
    CString str;


/*    if (!m_wndToolBarView.CreateEx(
        this,
        TBSTYLE_FLAT  |
        TBSTYLE_LIST |
		WS_CHILD, 
        CBRS_ALIGN_TOP, 
        CRect(0, 0, 0, 0),
        IDR_XFPLAYER_VIEW))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	#define TBBSTYLE_EX_DRAWDDARROWS 0x00000080
	m_wndToolBarView.ModifyStyleEx(0, TBBSTYLE_EX_DRAWDDARROWS, SWP_SHOWWINDOW);


    if (!m_wndToolBarPlay.CreateEx(
        this,
        TBSTYLE_FLAT  |
        TBSTYLE_LIST, //|
//        TBSTYLE_WRAPABLE,
        WS_CHILD | CBRS_ALIGN_TOP,// |
//        CBRS_TOOLTIPS | CBRS_FLYBY, 
        CRect(0, 0, 0, 0),
        IDR_XFPLAYER_PLAY) ||
		!m_wndToolBarPlay.LoadToolBar(IDR_XFPLAYER_PLAY))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}*/


	if (
		!m_rebar.AddBar(&m_wndToolBarStandard, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP)
		//|| !m_rebar.AddBar(&m_wndDlgBar, NULL, NULL,  RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP)
		//|| !m_rebar.AddBar(&m_wndToolBarView, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP)
        //|| !m_rebar.AddBar(&m_wndToolBarPlay, NULL, NULL, RBBS_BREAK | RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP)
		)
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBarStandard.SetBarStyle(m_wndToolBarStandard.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

//	CEdit *pEdit = (CEdit * ) m_wndDlgBar.GetDlgItem(IDC_EDIT_TIME);
//	CEdit *pEdit = NULL;
/*	if(pEdit)
	{
		m_pEditFont = new CFont();
		LOGFONT logFont;
		RECT rect;
		pEdit->GetWindowRect(&rect);
		logFont.lfHeight = rect.bottom - rect.top ;
		logFont.lfWidth = 0;
		logFont.lfEscapement = 0;
		logFont.lfWeight = FW_NORMAL;
		logFont.lfItalic = FALSE;
		logFont.lfUnderline = FALSE;
		logFont.lfStrikeOut = FALSE;
		logFont.lfCharSet =	ANSI_CHARSET;
		logFont.lfOutPrecision = OUT_TT_PRECIS;
		logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		logFont.lfQuality = PROOF_QUALITY;
//		logFont.lfPitchAndFamily =  FIXED_PITCH | FF_SWISS;
		logFont.lfPitchAndFamily = 0;
		lstrcpy(logFont.lfFaceName, _T("Arial"));
		m_pEditFont->CreateFontIndirect(&logFont);
		pEdit->SetFont(m_pEditFont);
	}*/

	return TRUE;
}
