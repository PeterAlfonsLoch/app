// MainFrm.cpp : implementation of the CCDFrame class
//

#include "stdafx.h"
#include "VmsGenApp.h"
#include "VmsGuiApp.h"
//#include "VmpApp.h"
#include "HelpCentral.h"
#include "VmspHelp.h"
//#include "MainFrame.h"

//#include "vmsguiresource.h"

#include "DBCentral.h"
#include "FontCentral.h"
#include "Savings.h"

#include "MenuCentral.h"

#include "CDFrame.h"

#include "DBLong.h"
#include "DataCentral.h"

#include "MidiSequence.h"

#include "vmsmixresource.h"
#include "MixerDialog.h"


#include "PlaylistFrame.h"
#include "ToolBarCtrlV017.h"

#include "MixerThread.h"

//#include "MainFrameInPlaceWnd.h"

#include "BaseRect.h"

#include "MenuV033.h"
#include "WndFrameworkV033.h"

#include "ddraw.h"

//#include "MenuV033.h"

#include "PushingRoutingFrame.h"

//extern CVmpApp theApp;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCDFrame


IMPLEMENT_DYNCREATE(CCDFrame, CTransparentMDIChildWnd)

BEGIN_MESSAGE_MAP(CCDFrame, CTransparentMDIChildWnd)
	//{{AFX_MSG_MAP(CCDFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_VIEW_FULL_SCREEN, OnViewFullScreen)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FULL_SCREEN, OnUpdateViewFullScreen)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_EXIT_FULL_SCREEN, OnExitFullScreen)
	ON_UPDATE_COMMAND_UI(ID_EXIT_FULL_SCREEN, OnUpdateExitFullScreen)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_OPTIONS, OnUpdateToolsOptions)
	ON_WM_HELPINFO()
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_TOOLS_MIXER, OnToolsMixer)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_MIXER, OnUpdateToolsMixer)
	ON_WM_SIZE()
	ON_COMMAND(ID_TOOLS_COMPACTDATABASE, OnToolsCompactdatabase)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_COMPACTDATABASE, OnUpdateToolsCompactdatabase)
	ON_COMMAND(ID_PLAYER, OnPlayer)
	ON_UPDATE_COMMAND_UI(ID_PLAYER, OnUpdatePlayer)
	ON_COMMAND(ID_WINDOW_CASCADE, OnWindowCascade)
	ON_COMMAND(ID_TOOLS_SAVEMEMORY, OnToolsSaveMemory)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SAVEMEMORY, OnUpdateToolsSaveMemory)
	ON_WM_ACTIVATE()
	ON_WM_INITMENU()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_KEYDOWN()
	ON_WM_SHOWWINDOW()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_CLOSE()
	ON_WM_MOVE()
	ON_COMMAND(ID_VIEW_COMPACT_SIZE, OnViewCompactSize)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COMPACT_SIZE, OnUpdateViewCompactSize)
	ON_UPDATE_COMMAND_UI(ID_VMSGUI_CLOSE, OnUpdateVmsguiClose)
	ON_UPDATE_COMMAND_UI(ID_VMSGUI_WINDOW_MINIMIZE, OnUpdateVmsguiWindowMinimize)
	ON_WM_HSCROLL()
	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
	//}}AFX_MSG_MAP
	// Global help commands
    ON_MESSAGE(VMSM_ECONOMODECHANGE, OnEconoModeChange)
	ON_MESSAGE(APPM_NOTIFY, OnAppNotify)
	ON_MESSAGE(UM_FRAMEWORKV033_COMMAND, OnFrameworkV033Command)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CCDFrame construction/destruction

CCDFrame::CCDFrame()
{
	m_pruntimeclassMainFrame = RUNTIME_CLASS(CMainFrame);
	m_uiIDMainFrame = IDR_MAINFRAME;
	// TODO: add member initialization code here
//	m_pAlbumDialog = NULL;
	m_pEditFont = NULL;
//	m_bFullScreen = false;
//	m_pwndFullScrnBar = NULL;
    m_bCompactSize = true;
//	m_bOnSizeSaving = false;
	m_pmixerthread = NULL;
//	m_bCreate = false;
//	m_pmenuV033 = NULL;

//    m_pMenuManager = new CMenuManagerV003;

//    m_pkmcwnd = new CCDFrameInPlaceWnd();
//    m_pMainFrame = new CKaraokeMainFrame();
}

CCDFrame::~CCDFrame()
{
	if(m_pEditFont != NULL)
	{
		m_pEditFont->DeleteObject();
		delete m_pEditFont;
	}
    
//    if(m_pMainFrame != NULL)
  //  {
    //    m_pMainFrame->DestroyWindow();
      //  m_pMainFrame = NULL;
    //}
//	if(m_pAlbumDialog != NULL)
//	{
//		delete m_pAlbumDialog;
//	}
//	if(m_pmenuV033 != NULL)
//	{
//		delete m_pmenuV033;
//	}
//    if(m_pkmcwnd != NULL)
  //  {
    //    delete m_pkmcwnd;
    //}
}

int CCDFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_strRegistrySection = _T("KaraokeSDIFrame");
    //lpCreateStruct->hwndParent = m_pMainFrame->GetSafeHwnd();
    HICON hicon = GetIcon(false);
	if (CTransparentMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

//	if(VMS_FAILED(TwcInitialize(true, CTransparentWndContainer::GlobalBuffer)))
//		return -1;

    
    hicon = GetIcon(false);

    m_wndframework.SetAppearanceTransparency(CWndFrameworkV033::ClientTransparent);

    hicon = GetIcon(FALSE);
    //m_wndframework.SetSWPFlags(SWP_NOCOPYBITS | SWP_SHOWWINDOW);
//    m_wndframework.SetSWPFlags(SWP_SHOWWINDOW);

    CWnd * pwnd = GetParent();

    SetDlgCtrlID(AFX_IDW_PANE_FIRST);

    int _db_style = GetStyle();
    CWinApp * pApp = AfxGetApp();
//    ModifyStyle(WS_CAPTION | WS_THICKFRAME, 0);
  //  SetDlgCtrlID(IDR_MAINFRAME);
    
//    if(!m_pkmcwnd->CreateEx(0, AfxRegisterWndClass(NULL, 0, 0, 0), NULL, WS_VISIBLE, CRect(0, 0, 0, 0), NULL, 0, NULL))
  //      return -1;
    //m_pkmcwnd->SetMenu(GetMenu());
//    ModifyStyle(0, WS_CHILD);
  //  SetParent(m_pkmcwnd);

//    CWnd * pWnd = GetParent();
  //  UINT nID = GetDlgCtrlID();
    //UINT nID2 = IDR_MAINFRAME;
    //AfxMessageBox(_T("7.5"));
//	EnableDocking(CBRS_ALIGN_ANY);
	
    CMenu * pMenu = GetMenu();

//    m_pmenuV033 = new CMenuV033();
//    if(pMenu == NULL)
//    {
//        m_pmenuV033->LoadMenu(IDR_XFPLAYER);
//    }
//    else
//    {
//        m_pmenuV033->LoadMenu(pMenu, pApp->MenuV033GetImageList());
//    }
//    m_hMenuDefault = m_pmenuV033->GetSafeHmenu();
//    SetMenu(m_pmenuV033);
    m_hMenuDefault = NULL;
    //SetMenu(NULL);
    //CMenu * pmenuDebug =GetMenu();
    //if(pMenu != NULL)
    //{
        //pMenu->DestroyMenu();
    //}

//    CVmpApp * pApp = (CVmpApp * ) AfxGetApp();
//    CVmpApp * pApp = (CVmpApp * ) AfxGetApp();

	

    


	DBMoveWindow(
		_T("Karaoke"));
//	m_bOnSizeSaving = true;
	TransparentFrameWndUpdateBars();
	LoadBarState();

//	m_bCreate = true;
	return 0;
}

BOOL CCDFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    //AfxMessageBox(_T("7.7"));
	if( !CTransparentMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//cs.style &= ~WS_CLIPSIBLINGS;
    cs.style &= ~WS_CAPTION;
    cs.style &= ~WS_THICKFRAME;
    cs.style |= WS_CLIPCHILDREN;
//    cs.style |= WS_MINIMIZEBOX ;
  //  cs.style |= WS_MAXIMIZEBOX ;
    //cs.style |= WS_CHILD;
     
    //AfxMessageBox(_T("7.6"));
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCDFrame diagnostics

#ifdef _DEBUG
void CCDFrame::AssertValid() const
{
	CTransparentMDIChildWnd::AssertValid();
}

void CCDFrame::Dump(CDumpContext& dc) const
{
	CTransparentMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCDFrame message handlers



//void CCDFrame::OnToolsAlbum() 
//{
	// TODO: Add your command handler code here
//    ViewToolsAlbum();

//}

CToolBarV033 * CCDFrame::GetToolBar()
{

	return &m_toolbarStandard;

}

CXfplayerDialogBar * CCDFrame::GetDialogBar()
{
	return &m_dialogbar;
}




void CCDFrame::OnDestroy() 
{
	SaveBarState();
//	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
//	if(m_pAlbumDialog != NULL)
//		m_pAlbumDialog->DestroyWindow();
//	CMenu * pMenu = GetMenu();
//	delete pMenu;
//	m_hMenuDefault = NULL;
	CTransparentMDIChildWnd::OnDestroy();
	
//    GetParent()->DestroyWindow();
//    if(m_pMainFrame != NULL)
  //  {
    //    m_pMainFrame->DestroyWindow();
      //  m_pMainFrame = NULL;
    //}

	// TODO: Add your message handler code here
	
}

void CCDFrame::UpdateReserveList()
{
//	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
//	CXfplayerDoc *pDoc = pApp->GetActiveDocument();
//	POSITION pos = pDoc->GetFirstViewPosition();
//	if(pos != NULL)
//	{
//		CXfplayerView *pView = (CXfplayerView *) pDoc->GetNextView(pos);
//		pView->UpdateReserveList();
//	}

}

void CCDFrame::OnViewFullScreen() 
{
    ViewFullScreen();
	// TODO: Add your command handler code here
       
}

void CCDFrame::OnUpdateViewFullScreen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
	if (IsFullScreen())
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}

void CCDFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if (IsFullScreen())
	{
		lpMMI->ptMaxSize.y = m_fullscreen.m_FullScreenWindowRect.Height();
		lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
		lpMMI->ptMaxSize.x = m_fullscreen.m_FullScreenWindowRect.Width();
		lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;
	}
	else
	{
		CTransparentMDIChildWnd::OnGetMinMaxInfo(lpMMI);
	}
}

bool CCDFrame::IsFullScreen()
{
	return m_wndframework.IsFullScreen();
}

void CCDFrame::OnExitFullScreen() 
{
	// TODO: Add your command handler code here
	if(IsFullScreen())
	{
		OnViewFullScreen();
	}
}

void CCDFrame::OnUpdateExitFullScreen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(IsFullScreen());
}

void CCDFrame::OnToolsOptions() 
{
	// TODO: Add your command handler code here
	//if(DB()->IsWorking())
	//{
		COptionsDialog optionsDialog;
		optionsDialog.DoModal();
	//}
	//else
	//{
	//	AfxMessageBox(IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE, MB_ICONINFORMATION);
	//}

}

void CCDFrame::OnUpdateToolsOptions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

/*void CCDFrame::OnFileProperties() 
{
	// TODO: Add your command handler code here
	CXfPropertiesDialog propertiesDialog(this);
	propertiesDialog.DoModal();
	
}

void CCDFrame::OnUpdateFileProperties(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
	ASSERT(pApp != NULL);
	CXfplayerDoc * pDoc = pApp->GetPlayerDocument();
    if(pDoc == NULL)
    {
        pCmdUI->Enable(FALSE);
        return;
    }
	ASSERT(pDoc != NULL);
	pCmdUI->Enable(pDoc->GetMidiPlayer() &&
		pDoc->GetMidiSequenceState() !=
		CMidiSequence::StatusNoFile &&
        !pDoc->IsPlaying());
	
}*/


BOOL CCDFrame::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CTransparentMDIChildWnd::OnHelpInfo(pHelpInfo);
}



void CCDFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CTransparentMDIChildWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	// TODO: Add your message handler code here
//	m_pMenuManager->ModifyMenu(pPopupMenu);
}

BOOL CCDFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{

	return CTransparentMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);

/*	CPushRoutingFrame push(this);



    CWnd * pWnd = GetActiveWindow();
    if(pWnd != NULL 
        && (pWnd = FromHandlePermanent(pWnd->m_hWnd)) != NULL 
        && pWnd != NULL
        && pWnd != this
        && pWnd->GetParent() == NULL
        && pWnd->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
        return TRUE;

//    CMDIChildWnd* pActiveChild = MDIGetActive();
	// pump through active child FIRST
//	if (pActiveChild != NULL
  //      && pActiveChild->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	//		return TRUE;
	// pump through current view FIRST
	CView* pView = GetActiveView();
	if (pView != NULL && pView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// then pump through frame
	if (CWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

    if(m_wndframework.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
        return TRUE;

	// last but not least, pump through app
	CWinApp* pApp = AfxGetApp();
	if (pApp != NULL && pApp->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;*/

	return FALSE;

}

void CCDFrame::OnToolsMixer() 
{
//    CMixerDialog * pNewDialog = new CMixerDialog();
  //  m_ptraMixerDialogs.Add(pNewDialog);
    //pNewDialog->Create(IDD_MIXER);
    //pNewDialog->SetNewDestination(MIXERLINE_COMPONENTTYPE_DST_SPEAKERS);
    //pNewDialog->ShowWindow(SW_SHOWNORMAL);

	if(m_pmixerthread == NULL)
	{
		m_pmixerthread = (CMixerThread *)
			AfxBeginThread(RUNTIME_CLASS(CMixerThread));
	}
	if(m_pmixerthread != NULL)
	{
		m_pmixerthread->PostMessageViewMixer(true);
	}
	
}

void CCDFrame::OnUpdateToolsMixer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

void CCDFrame::OnSize(UINT nType, int cx, int cy) 
{
    CTransparentMDIChildWnd::OnSize(nType, cx, cy);

/*   	CDBCentral * pDataCentral = DB();
	CDBLongSet * pLongsSet = pDataCentral->GetDBLongSet();
	if(m_bOnSizeSaving)
	{
		DBSaveWindowRect(
			_T("Karaoke"));
	}*/

	

/*    if(IsFullScreen())
    {
        m_wndframework.SetAppearanceMode(CWndFrameworkV033::AppearanceModeFullScreen);
    }
    else if(nType == SIZE_MAXIMIZED)
    {
        m_wndframework.SetAppearanceMode(CWndFrameworkV033::AppearanceModeZoomed);
    }
    else if(nType == SIZE_MINIMIZED)
    {
        m_wndframework.SetAppearanceMode(CWndFrameworkV033::AppearanceModeIconic);
    }
    else if(nType == SIZE_RESTORED)
    {
        m_wndframework.SetAppearanceMode(CWndFrameworkV033::AppearanceModeNormal);
    }
    else
    {
        m_wndframework.SetAppearanceMode(CWndFrameworkV033::AppearanceModeNormal);
    }
  */      

//	m_wndframework.OnSizeRegion(nType, cx, cy);

//    TwcOnSize();
}

void CCDFrame::OnToolsCompactdatabase() 
{
	// TODO: Add your command handler code here
//	CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    CDBCentral * pDataCentral = DB();
    pDataCentral->CompactDatabase(NULL);
}

void CCDFrame::OnUpdateToolsCompactdatabase(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCDFrame::OnPlayer() 
{
	// TODO: Add your command handler code here
	//CVmpApp * pApp = (CVmpApp *) AfxGetApp();
//	ASSERT(pApp != NULL);
	CXfplayerDoc * pDoc = (CXfplayerDoc *) CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc();
    if(pDoc == NULL)
    {
        CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->OpenDocumentFile(NULL);
    }
    else
    {
        CXfplayerView * pView = pDoc->GetLyricView();
        if(pView != NULL)
        {
            pView->GetParentFrame()->BringWindowToTop();
        }
    }
	
}

void CCDFrame::OnUpdatePlayer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCDFrame::OnWindowCascade() 
{
	// TODO: Add your command handler code here
    CFrameWnd * pFrameWnd = GetActiveFrame();
    if(pFrameWnd != NULL)
    {
        CWnd * pWnd = pFrameWnd;
        while(true)
        {
            if(pWnd->IsKindOf(RUNTIME_CLASS(CPlaylistFrame)))
            {
                CFrameWnd * pParent = pWnd->GetParentFrame();
                pWnd->ModifyStyle(0, WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, SWP_NOACTIVATE | SWP_FRAMECHANGED);
            }
            pWnd = pWnd->GetNextWindow();
            if(pWnd == NULL ||
                pWnd->m_hWnd == pFrameWnd->m_hWnd)
                break;
        }
    }
//	MDICascade();
    pFrameWnd = GetActiveFrame();
    if(pFrameWnd != NULL)
    {
        CWnd * pWnd = pFrameWnd;
        while(true)
        {
            if(pWnd->IsKindOf(RUNTIME_CLASS(CPlaylistFrame)))
            {
                pWnd->ModifyStyle(WS_CAPTION, 0, SWP_NOACTIVATE | SWP_FRAMECHANGED);
            }
            pWnd = pWnd->GetNextWindow();
            if(pWnd == NULL ||
                pWnd->m_hWnd == pFrameWnd->m_hWnd)
                break;
        }
    }
}


BOOL CCDFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
/*    m_pkmcwnd = new CPlaylistInPlaceWnd();
    if(m_pkmcwnd == NULL)
        return FALSE;

	if(!m_pkmcwnd->CreateEx(WS_EX_TRANSPARENT, NULL, NULL, WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, IDR_PLAYLIST, NULL))
        return FALSE;*/
	if(!CTransparentMDIChildWnd::OnCreateClient(lpcs, pContext))
		return FALSE;

	CVmsGuiApp * papp = (CVmsGuiApp *) AfxGetApp();

	papp->TwfInitializeDescendants(this, true);

	    CRelationV001<UINT, UINT, UINT, UINT> * prel;
    CMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);

    if (/*!m_menubar.CreateEx(
		this, 
        TBSTYLE_FLAT
		| TBSTYLE_LIST
		| CCS_TOP
		| CCS_NOPARENTALIGN
		| CCS_NOMOVEY 
		| CCS_NODIVIDER 
		| CCS_NORESIZE 
		| WS_CHILD 
		|  WS_VISIBLE,
		WS_CHILD
		| WS_VISIBLE 
		| CBRS_TOP,
        CRect(0, 0, 0, 0),
        IDR_XFPLAYER_MENUBAR) ||*/
        !m_menubar.Initialize(
                CMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
                CMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
                prel,
                CFontCentral::AppGetFontCentral()->GetMenuFont()) ||
		VMS_FAILED(m_menubar.LoadMenuBar(IDR_XFPLAYER_MENUBAR)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_uiIDMenuBar = IDR_XFPLAYER_MENUBAR;

    if (!m_toolbarStandard.CreateEx(
        this,
        TBSTYLE_FLAT
		| TBSTYLE_LIST
        | WS_CHILD
		| WS_VISIBLE,
        CBRS_TOOLTIPS
		| CBRS_FLYBY
		| CBRS_TOP
		| CBRS_SIZE_FIXED,
        CRect(0, 0, 0, 0),
        IDR_XFPLAYER_STANDARD))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
    if (!m_toolbarStandard.LoadToolBar(IDR_XFPLAYER_STANDARD))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
    
    CString str;


    if (!m_toolbarView1.CreateEx(
        this,
        TBSTYLE_FLAT
		| TBSTYLE_LIST
		| WS_CHILD
		| WS_VISIBLE,
        CBRS_TOOLTIPS
		| CBRS_FLYBY
		| CBRS_TOP
		| CBRS_SIZE_FIXED,
        CRect(0, 0, 0, 0),
        IDR_XFPLAYER_VIEW1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	#define TBBSTYLE_EX_DRAWDDARROWS 0x00000080
	m_toolbarView1.ModifyStyleEx(0, TBBSTYLE_EX_DRAWDDARROWS, SWP_SHOWWINDOW);

    if (!m_toolbarView2.CreateEx(
        this,
        TBSTYLE_FLAT
		| TBSTYLE_LIST
		| WS_CHILD
		| WS_VISIBLE,
        CBRS_TOOLTIPS
		| CBRS_FLYBY
		| CBRS_TOP
		| CBRS_SIZE_FIXED,
        CRect(0, 0, 0, 0),
        IDR_XFPLAYER_VIEW2))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	#define TBBSTYLE_EX_DRAWDDARROWS 0x00000080
	m_toolbarView2.ModifyStyleEx(0, TBBSTYLE_EX_DRAWDDARROWS, SWP_SHOWWINDOW);

    if (!m_toolbarPlay.CreateEx(
        this,
        TBSTYLE_FLAT  |
        TBSTYLE_LIST
		| WS_CHILD
		| WS_VISIBLE,
		CBRS_TOP
        | CBRS_TOOLTIPS
		| CBRS_FLYBY
		| CBRS_SIZE_FIXED,
        CRect(0, 0, 0, 0),
        IDR_XFPLAYER_PLAY) ||
		!m_toolbarPlay.LoadToolBar(IDR_XFPLAYER_PLAY))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_dialogbar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	m_dialogbar.FillCodePageCombo();

	OnUpdateLyricsCodePage();

	if (//!m_rebar.Create(this,
          //  RBS_BANDBORDERS,
            //WS_CHILD
            /*| WS_VISIBLE
            | WS_CLIPSIBLINGS
            | WS_CLIPCHILDREN
            | CBRS_TOP
            | WS_BORDER)
        || !m_rebar.AddBar(
				&m_menubar, NULL, NULL,
				RBBS_BREAK
				| RBBS_FIXEDBMP)*/
		!m_rebar.AddBar(
				&m_toolbarStandard,
				NULL, 
				NULL,
				RBBS_BREAK 
				| RBBS_FIXEDBMP)
		|| !m_rebar.AddBar(
				&m_dialogbar,
				NULL, 
				NULL,  
				RBBS_FIXEDBMP)
		|| !m_rebar.AddBar(
				&m_toolbarView1, 
				NULL, 
				NULL,
				RBBS_BREAK 
				| RBBS_FIXEDBMP)
		|| !m_rebar.AddBar(
				&m_toolbarView2, 
				NULL, 
				NULL,
				RBBS_BREAK 
				| RBBS_FIXEDBMP)
        || !m_rebar.AddBar(
				&m_toolbarPlay,
				NULL, NULL,
				RBBS_BREAK 
				| RBBS_FIXEDBMP)
		)
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_statusbar.Create(this) ||
		!m_statusbar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_toolbarStandard.SetBarStyle(m_toolbarStandard.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	CEdit *pEdit = (CEdit * ) m_dialogbar.GetDlgItem(IDC_EDIT_TIME);
//	CEdit *pEdit = NULL;
	if(pEdit)
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
	}


	return TRUE;
}

afx_msg LRESULT CCDFrame::OnEconoModeChange(WPARAM wParam, LPARAM lParam)
{
    int iEconoMode = wParam;
    SendMessageToDescendants(VMSM_ECONOMODECHANGE, iEconoMode);
    return true;
}

void CCDFrame::OnToolsSaveMemory() 
{
	// TODO: Add your command handler code here
	//CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    int iEconoMode = CSavings::AppGetEconoMode();
    if((iEconoMode & CSavings::SaveMemory) > 0)
        CSavings::AppSetEconoMode(iEconoMode & ~ CSavings::SaveMemory);
    else
        CSavings::AppSetEconoMode(iEconoMode | CSavings::SaveMemory);
}

void CCDFrame::OnUpdateToolsSaveMemory(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//CVmpApp * pApp = (CVmpApp *) AfxGetApp();
    pCmdUI->SetCheck((CSavings::AppGetEconoMode() & CSavings::SaveMemory) > 0 ? 1 : 0);
    pCmdUI->Enable();
}

void CCDFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{

	CTransparentMDIChildWnd::OnActivate(nState, pWndOther, bMinimized);

    m_wndframework.SetActiveFlag(nState == WA_ACTIVE    ||
        nState == WA_CLICKACTIVE);


    //RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_FRAME);
	// TODO: Add your message handler code here
	
}

BOOL CCDFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	pParentWnd = NULL;
	// TODO: Add your specialized code here and/or call the base class
    //AfxMessageBox(_T("7.8"));
    CString str;
    str.Format(_T("nIDResource %d"), nIDResource);
    //AfxMessageBox(str);
    //if(pParentWnd == NULL);
//    if(!m_pMainFrame->Create(
  //      NULL,NULL))
    //    return FALSE;

//    pParentWnd = m_pMainFrame;
    ASSERT(pParentWnd == NULL);

//    str.LoadString(IDR_XFPLAYER);
  //  m_pMainFrame->SetWindowText(str);
    
/*    CVmpApp * pApp = (CVmpApp *) AfxGetApp();

    HICON hIcon = (HICON) LoadImage(pApp->m_hInstance,
        MAKEINTRESOURCE(IDR_XFPLAYER),
        IMAGE_ICON,
        16, 16,
        0);


    m_pMainFrame->SetIcon(hIcon, false);

    hIcon = (HICON) LoadImage(pApp->m_hInstance,
        MAKEINTRESOURCE(IDR_XFPLAYER),
        IMAGE_ICON,
        32, 32,
        0);


    m_pMainFrame->SetIcon(hIcon, true); */


	if(!CTransparentMDIChildWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
        return FALSE;
    //AfxMessageBox(_T("7.9"));

//    delete m_pMenu;
//
  //  m_pMenu = new CMenu();
    //m_pMenu->LoadMenu(IDR_MAINFRAME);
    //SetMenu(m_pMenu);

    return TRUE;
}

void CCDFrame::OnInitMenu(CMenu* pMenu) 
{
	CTransparentMDIChildWnd::OnInitMenu(pMenu);
	
//    m_pMenuManager->ModifyMenu(pMenu);
	// TODO: Add your message handler code here
	
}

void CCDFrame::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	//if(m_pMenuManager->RelayDrawItem(nIDCtl, lpDrawItemStruct) == VMSR_SUCCESS)
        //return;
//    m_pMenuManager->RelayDrawItem(nIDCtl, lpDrawItemStruct);
	CTransparentMDIChildWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

/*void CCDFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
//    m_pMenuManager->RelayMeasureItem(this, nIDCtl, lpMeasureItemStruct);
	CTransparentMDIChildWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}*/

void CCDFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	if (lpMeasureItemStruct->CtlType == ODT_MENU)
	{
		ASSERT(lpMeasureItemStruct->CtlID == 0);
		CMenu* pMenu;

		_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
		if (pThreadState->m_hTrackingWindow == m_hWnd)
		{
			// start from popup
			pMenu = CMenu::FromHandle(pThreadState->m_hTrackingMenu);
		}
        else if(GetStyle() & WS_CHILD)
        {
            //if(VMS_FAILED(m_menubar.GetMenu((CMenuV033**) &pMenu)))
                 pMenu = NULL;
        }
		else
		{
			// start from menubar
			pMenu = GetMenu();
		}
    
        if(pMenu)
        {
            if(pMenu->IsKindOf(RUNTIME_CLASS(CMenuV033)))
            {
                CMenuV033 * pPopup = CMenuV033::FindPopupMenuFromID((CMenuV033*) pMenu, lpMeasureItemStruct->itemID, lpMeasureItemStruct->itemData);
                if(pPopup != NULL)
                {
                    pPopup->MeasureItem(lpMeasureItemStruct);
                    return;
                }
            }
            else
            {
	            CMenu * pPopup = FindPopupMenuFromID(pMenu, lpMeasureItemStruct->itemID, lpMeasureItemStruct->itemData);
                if(pPopup != NULL)
                {
                    pPopup->MeasureItem(lpMeasureItemStruct);
                    return;
                }
            }
        }
    } 

	CTransparentMDIChildWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

/*void CCDFrame::OpenToolsAlbum()
{
    CVmpApp * pApp = (CVmpApp *)AfxGetApp();
    if(DB()->IsWorking())
    {
	    if(m_pAlbumDialog == NULL)
	    {
		    m_pAlbumDialog = new CAlbumDialog();
		    if(!m_pAlbumDialog->Create(IDD_ALBUM))
		    {
			    delete m_pAlbumDialog;
			    m_pAlbumDialog = NULL;
		    }
	    }
	    //dlg.DoModal();
	    if(m_pAlbumDialog != NULL)
	    {
            if(DB()->IsBuildingSongsAlbum())
            {
                CCriticalSection *pcs;
                LPBUILDALBUMTHREADDATA lpData =
                    DB()->GetActiveBuildAlbumThreadData(&pcs);
                if(lpData != NULL)
                {
                    lpData->m_taskDialog.m_pCloseWindow = m_pAlbumDialog;
					lpData->m_taskDialog.SetPendingShowCommandFlag(true);
                }
                pcs->Unlock();
            }
            else
            {
//                m_pAlbumDialog->Update(); // retirar se possível
		        m_pAlbumDialog->ShowWindow(SW_SHOWNORMAL);
		        m_pAlbumDialog->SetWindowPos(
			        &wndTop,
			        0, 0,
			        0, 0,
			        SWP_NOMOVE |
			        SWP_NOSIZE); //|
			        //SWP_SHOWWINDOW);
            }
	    }
	    
	    CWnd * pParent = GetParent();
    }
    else
    {
        AfxMessageBox(
            IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE,
            MB_OK |
            MB_ICONINFORMATION);

    }

}*/

void CCDFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar == VK_ESCAPE &&
        IsFullScreen())
    {
        SendMessage(WM_COMMAND, MAKEWORD(ID_EXIT_FULL_SCREEN, 1), NULL);
    }
    else
    {
        CTransparentMDIChildWnd::OnKeyDown(nChar, nRepCnt, nFlags);
    }
}
VMSRESULT CCDFrame::ViewFullScreen()
{
	WfiFullScreen(!IsFullScreen());
	return VMSR_SUCCESS;
}

/*void CCDFrame::ViewFullScreen(bool bFullScreen)
{   
	TransparentFrameWndFullScreen(bFullScreen);

}*/

//VMSRESULT CCDFrame::ViewToolsAlbum()
//{
  //  OpenToolsAlbum();
    //return VMSR_SUCCESS;
//}

BOOL CCDFrame::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CTransparentMDIChildWnd::DestroyWindow();
}

void CCDFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CTransparentMDIChildWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
}

void CCDFrame::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CTransparentMDIChildWnd::PostNcDestroy();
}

void CCDFrame::OnPaint() 
{
	TRACE("\nCCDFrame::OnPaint()\n");
	TwiOnPaint();
/*	TRACE(_T("CCDFrame::OnPaint\n")); 
    CRgn rgn;
    CPaintDC dc(this); 
	//TwiInvalidate(&dc);
    CRect rectClient;
    CRect rectWindow;
    GetWindowRect(rectWindow);
    rectClient = rectWindow;
    ScreenToClient(rectClient);
    rgn.CreateRectRgnIndirect(rectClient);
    int i = GetClipRgn(dc.GetSafeHdc(), rgn);
    if(i == 0)
    {
        rgn.SetRectRgn(rectClient);
    }
    rgn.OffsetRgn(rectWindow.TopLeft());
	TwcRedraw(&rgn);*/

    
}


void CCDFrame::OnNcPaint() 
{
	// There is no non client area to be painted.
}

void CCDFrame::RecalcLayout(BOOL bNotify) 
{
    m_wndframework.RecalcLayout();
	SaveBarState();
	//CTransparentMDIChildWnd::RecalcLayout(bNotify);
}

/*BOOL CCDFrame::OnNcActivate(BOOL bActive) 
{
	// TODO: Add your message handler code here and/or call default
	
    m_wndframework.SetNcActiveFlag(bActive);

	return CTransparentMDIChildWnd::OnNcActivate(bActive);
}*/

void CCDFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CTransparentMDIChildWnd::OnClose();

}

void CCDFrame::TwcRenderBackground(CDC *pdc, LPCRECT lpcrect)
{

	m_wndframework.OnDraw(pdc, lpcrect);

}

void CCDFrame::OnMove(int x, int y) 
{
	CTransparentMDIChildWnd::OnMove(x, y);
	

	
}

void CCDFrame::OnViewCompactSize() 
{
    ViewCompactMode(!m_bCompactSize);
}

void CCDFrame::OnUpdateViewCompactSize(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
    pCmdUI->SetCheck(m_bCompactSize ? 1: 0);
}

bool CCDFrame::ViewCompactMode(bool bCompact)
{
    bool bCompacted = m_bCompactSize;
    CXfplayerDoc * pdoc = dynamic_cast<CXfplayerDoc *>( GetActiveDocument());
    CXfplayerView * pview = NULL;
    if(pdoc != NULL)
    {
        pview = pdoc->GetLyricView();
    }
	CDBCentral * pdatacentral = DB();
    CDBLongSet * plongset = pdatacentral->GetDBLongSet();
	// TODO: Add your command handler code here
    if(bCompact)
    {
		DBSave(_T("Compact Mode"), 1);
        if(IsFullScreen())
        {
        }
        else
        {
			TransparentFrameWndShowBars(SW_HIDE);
            //m_rebar.ShowWindow(SW_HIDE);
		    //m_wndStatusBar.ShowWindow(SW_HIDE);
        }
        if(pview != NULL)
        {
            if(pview->IsPlaylistViewAttached())
            {
                pview->DetachPlaylistView();
            }
        }
    }
    else
    {
		DBSave(_T("Compact Mode"), 0);
        if(IsFullScreen())
        {
        }
        else
        {
			TransparentFrameWndShowBars(SW_SHOWNORMAL);
            //m_rebar.ShowWindow(SW_SHOWNORMAL);
            //m_wndStatusBar.ShowWindow(SW_SHOWNORMAL);
        }
    }
	m_bCompactSize = bCompact;
    RecalcLayout();
    CXfplayerViewUpdateHint uh;
    uh.SetType(CXfplayerViewUpdateHint::CompactModeChange);
    if(GetActiveDocument())
        GetActiveDocument()->UpdateAllViews(NULL, 0, &uh);
    return bCompacted;
}

void CCDFrame::OnUpdateVmsguiClose(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

void CCDFrame::OnUpdateVmsguiWindowMinimize(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

bool CCDFrame::IsCompactMode()
{
	return m_bCompactSize;
}

LRESULT CCDFrame::OnAppLanguage(WPARAM wparam, LPARAM lparam)
{
	return CTransparentMDIChildWnd::OnAppLanguage(wparam, lparam);
}

void CCDFrame::TransparentFrameWndUpdateBars()
{
	CTransparentMDIChildWnd::TransparentFrameWndUpdateBars();
	bool bResult = true;
	CRelationV001<UINT, UINT, UINT, UINT> * prel;
	CMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
	

	while(m_toolbarStandard.GetToolBarCtrl().DeleteButton(0));
    if (!m_toolbarStandard.LoadToolBar(IDR_XFPLAYER_STANDARD))
	{
		bResult = false;
	}
    CString str;

    
//    int i;

	UpdateToolBarText(m_toolbarStandard);
	UpdateToolBarStyle(m_toolbarStandard);
	TransparentFrameWndFixedReBarToolBarLayoutVR(m_toolbarStandard, 1);


	//while(m_toolbarView.GetToolBarCtrl().DeleteButton(0));
    if (!m_toolbarView1.LoadToolBar(IDR_XFPLAYER_VIEW1))
	{
		bResult = false;
	}

	UpdateToolBarText(m_toolbarView1);
	UpdateToolBarStyle(m_toolbarView1);
	TransparentFrameWndFixedReBarToolBarLayoutVR(m_toolbarView1, 3);
    
	if (!m_toolbarView2.LoadToolBar(IDR_XFPLAYER_VIEW2))
	{
		bResult = false;
	}

	UpdateToolBarText(m_toolbarView2);
	UpdateToolBarStyle(m_toolbarView2);
	TransparentFrameWndFixedReBarToolBarLayoutVR(m_toolbarView2, 4);

    if (!m_toolbarPlay.LoadToolBar(IDR_XFPLAYER_PLAY))
	{
		bResult = false;
	}

	UpdateToolBarText(m_toolbarPlay);
	UpdateToolBarStyle(m_toolbarPlay);
	TransparentFrameWndFixedReBarToolBarLayoutVR(m_toolbarPlay, 5);

	if (!m_statusbar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		bResult = false;
	}

	m_toolbarStandard.SetBarStyle(m_toolbarStandard.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	CEdit *pEdit = (CEdit * ) m_dialogbar.GetDlgItem(IDC_EDIT_TIME);
	if(pEdit)
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
	}

	CReBarCtrl & rebarctrl = m_rebar.GetReBarCtrl();

	for(UINT ui = 0; ui < rebarctrl.GetBandCount(); ui++)
	{
		rebarctrl.MaximizeBand(ui);
	}

	RecalcLayout();

//	CSliderCtrl *pSlider = (CSliderCtrl *) m_dialogbar.GetDlgItem(IDC_SLIDER);
//	if(pSlider)
//	{
//		pSlider->SetRange(0, 1000000);
//	}
	
	
}

afx_msg LRESULT CCDFrame::OnAppNotify(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
afx_msg LRESULT CCDFrame::OnFrameworkV033Command(WPARAM wParam, LPARAM lParam)
{
	if(wParam == 1)
	{
		if(lParam == ID_VMSGUI_CLOSE)
		{
			PostMessage(WM_CLOSE);
			return TRUE;
		}
		else if(lParam == ID_VMSGUI_UP)
		{
			ASSERT(FALSE);
			return TRUE;
		}
		else if(lParam == ID_VMSGUI_DOWN)
		{
			ASSERT(FALSE);
			return TRUE;
		}
		else if(lParam == ID_VMSGUI_WINDOW_MAXIMIZE)
		{
			ShowWindow(SW_MAXIMIZE);
			return TRUE;
		}
		else if(lParam == ID_VMSGUI_WINDOW_MINIMIZE)
		{
			ShowWindow(SW_MINIMIZE);
			return TRUE;
		}
		else if(lParam == ID_VMSGUI_WINDOW_RESTORE)
		{
			ShowWindow(SW_RESTORE);
			return TRUE;
		}
	}
	return FALSE;
}

void CCDFrame::TwiOnDraw(CDC *pdc)
{

	m_wndframework.OnDraw(pdc);

}

bool CCDFrame::GetToolButtonText(CWStr &wstr, UINT uiCmd)
{
	UINT uiText = -1;
	switch(uiCmd)
	{
	case ID_TOOLS_ALBUM:
		uiText = IDS_XFPLAYER_ALBUM;
		break;
	case ID_VIEW_PLAYLIST:
		uiText = IDS_XFPLAYER_PLAYLIST;
		break;
	case ID_VIEW_LYRICS:
		uiText = IDS_XFPLAYER_LYRICS;
		break;
	case ID_VIEW_FULL_SCREEN:
		uiText = IDS_XFPLAYER_FULLSCREEN;
		break;
	case ID_PLAY:
		uiText = IDS_XFPLAYER_PLAY;
		break;
	case ID_PAUSE:
		uiText = IDS_XFPLAYER_PAUSE;
		break;
	case ID_STOP:
		uiText = IDS_XFPLAYER_STOP;
		break;
	case ID_NEXTSONG:
		uiText = IDS_XFPLAYER_NEXTSONG;
		break;
	}

	if(uiText == -1)
		return FALSE;
	else
	{
		return wstr.LoadString(uiText) != 0;
	}
}

void CCDFrame::UpdateToolBarText(CToolBarV033 &toolbar)
{
	UINT uiID;
	CWStr wstr;
	for(int i = 0; i < toolbar.GetCount(); i++)
	{
		uiID = toolbar.GetItemID(i);
		if(GetToolButtonText(wstr, uiID))
		{
			toolbar.SetButtonText(i, wstr);
		}
	}
}

void CCDFrame::UpdateToolBarStyle(CToolBarCtrlV017 &toolbar)
{
	UINT uiID;
	CWStr wstr;
	TBBUTTONINFOW tbbi;
    tbbi.cbSize = sizeof(tbbi);
    
	CRect rect;
	TBBUTTON tbb;
	for(int i = 0; i < toolbar.GetButtonCount(); i++)
	{
		toolbar.GetButton(i, &tbb);
		uiID = tbb.idCommand;
		tbbi.dwMask = TBIF_STYLE;
        toolbar.GetButtonText(uiID, wstr);
		if(!wstr.IsEmpty()
			&& !(tbbi.fsStyle & TBSTYLE_SEP))
		{
			tbbi.fsStyle |= TBSTYLE_AUTOSIZE;
		}
		else
		{
			tbbi.fsStyle &= ~TBSTYLE_AUTOSIZE;
		}
		tbbi.dwMask = TBIF_STYLE ;
        toolbar.SetButtonInfo(uiID, &tbbi);

		toolbar.GetItemRect(i, rect);
		TRACE(_T("button.Width %d\n"), rect.Width());
		TRACE(_T("button.Height %d\n"), rect.Height());
	}
}

void CCDFrame::UpdateToolBarStyle(CToolBarV033 &toolbar)
{
	UINT uiID;
	CWStr wstr;
	TBBUTTONINFOW tbbi;
    tbbi.cbSize = sizeof(tbbi);
    tbbi.dwMask = TBIF_STYLE ;
	CRect rect;
	for(int i = 0; i < toolbar.GetCount(); i++)
	{
		uiID = toolbar.GetItemID(i);
		toolbar.GetButtonText(i, wstr);
        toolbar.GetToolBarCtrl().GetButtonInfo(uiID, &tbbi);
//		if(!wstr.IsEmpty()
		//	&& !(tbbi.fsStyle & TBSTYLE_SEP))
		if(!(tbbi.fsStyle & TBSTYLE_SEP))
		{
			tbbi.fsStyle |= TBSTYLE_AUTOSIZE;
		}
		else
		{
			tbbi.fsStyle &= ~TBSTYLE_AUTOSIZE;
		}
        toolbar.GetToolBarCtrl().SetButtonInfo(uiID, &tbbi);

		toolbar.GetItemRect(i, rect);
		TRACE(_T("button.Width %d\n"), rect.Width());
		TRACE(_T("button.Height %d\n"), rect.Height());
	}
}


void CCDFrame::UpdateToolBarText(CToolBarCtrlV017 &toolbar)
{
	UINT uiID;
	CWStr wstr;
	TBBUTTONINFOW tbbi;
    tbbi.cbSize = sizeof(tbbi);
	TBBUTTON tbb;
	for(int i = 0; i < toolbar.GetButtonCount(); i++)
	{
		toolbar.GetButton(i, &tbb);
		uiID = tbb.idCommand;
		if(GetToolButtonText(wstr, uiID))
		{
			tbbi.pszText = (LPWSTR) (LPCWSTR) wstr;
			tbbi.cchText = wstr.GetLength();
			tbbi.dwMask = TBIF_TEXT ;
			toolbar.SetButtonInfo(uiID, &tbbi);
		}
	}
}

bool CCDFrame::TransparentFrameWndShowBars(int nCmdShow)
{
//	m_menubar.ShowWindow(nCmdShow);
//	m_toolbarStandard.ShowWindow(nCmdShow);
//	m_toolbarView.ShowWindow(nCmdShow);
//	m_toolbarPlay.ShowWindow(nCmdShow);
	if(nCmdShow == SW_HIDE)
	{
		SaveBarState();
	}
	m_rebar.ShowWindow(nCmdShow);
	m_statusbar.ShowWindow(nCmdShow);
	if(nCmdShow == SW_SHOW)
	{
		LoadBarState();
	}
	RecalcLayout();
	return true;
}

void CCDFrame::OnHelpFinder() 
{
	CVmsGenApp * papp = (CVmsGenApp *) AfxGetApp();
	CWStr wstrFolder;
	wstrFolder.SetOEM(papp->m_strModuleFolder);
	CWStr wstr;
	wstr.LoadString(IDS_HELP_FINDER);
	HtmlHelpW(m_hWnd, wstrFolder + wstr, HH_DISPLAY_TOPIC, 0);
	
}

void CCDFrame::SaveBarState()
{
	if(_000IsWindowCreated())
	{
		CTransparentMDIChildWnd::SaveBarState(m_strRegistrySection);
	}
}

void CCDFrame::LoadBarState()
{
	//CTransparentMDIChildWnd::LoadBarState(m_strRegistrySection);
}

void CCDFrame::WinHelp(DWORD dwData, UINT nCmd) 
{
//	CWndHtmlHelp(this, dwData, nCmd);
	CHelpCentral::WndHtmlHelp(
		this, 
		dwData,
		nCmd,
		VmspHelp::rowaContextSensitive);
}


CXfplayerView * CCDFrame::GetLyricView()
{
	CWnd * pwnd = GetTopWindow();
	while(pwnd != NULL)
	{
		if(pwnd->IsKindOf(RUNTIME_CLASS(CXfplayerView)))
			return (CXfplayerView *) pwnd;
		pwnd = pwnd->GetNextWindow();
	}
	return NULL;

}

void CCDFrame::OnUpdateLyricsCodePage()
{
	CXfplayerDoc * pdoc = (CXfplayerDoc *) GetActiveDocument();
	if(pdoc->IsKindOf(RUNTIME_CLASS(CXfplayerDoc)))
	{
		m_dialogbar.SetCodePage(pdoc->GetCodePage());
	}
}

bool CCDFrame::_000OnPosCreate()
{
	
	int iCompactMode = 0;
	DBLoad(_T("Compact Mode"), iCompactMode);

	

    
    ViewCompactMode(iCompactMode != 0);

	return CTransparentMDIChildWnd::_000OnPosCreate();
}

bool CCDFrame::TransparentFrameWndIsCompactMode()
{
	return IsCompactMode();
}

CMDIFrameWnd * CCDFrame::TransparentMDIChildWndGetMDIFrameEx()
{
	return CTransparentMDIChildWnd::TransparentMDIChildWndGetMDIFrameEx();
}

void CCDFrame::WfiOnAfterFullScreen(bool bFullScreen)
{
	CTransparentFrameWndInterface::WfiOnAfterFullScreen(bFullScreen);
}
