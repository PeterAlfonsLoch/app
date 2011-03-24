// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "../vmsp/resource.h"
#include "resource.h"
#include "VmcApp.h"
#include "MainFrame.h"
#include "wndfrm/FrameSchemaHardCoded002.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMainFrame

/*
IMPLEMENT_DYNCREATE(CMainFrame, SimpleMDIFrameWindow)

BEGIN_MESSAGE_MAP(CMainFrame, SimpleMDIFrameWindow)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_VIEW_FULL_SCREEN, OnViewFullScreen)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FULL_SCREEN, OnUpdateViewFullScreen)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_EXIT_FULL_SCREEN, OnExitFullScreen)
	ON_UPDATE_COMMAND_UI(ID_EXIT_FULL_SCREEN, OnUpdateExitFullScreen)
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
	ON_WM_ACTIVATE()
	ON_WM_INITMENU()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_KEYDOWN()
	ON_WM_ENTERIDLE()
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SAVEMEMORY, OnUpdateToolsSaveMemory)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, SimpleMDIFrameWindow::OnHelpFinder)
	ON_COMMAND(ID_HELP, SimpleMDIFrameWindow::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, SimpleMDIFrameWindow::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, SimpleMDIFrameWindow::OnHelpFinder)
    ON_MESSAGE(VMSM_ECONOMODECHANGE, OnEconoModeChange)
END_MESSAGE_MAP()
*/
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame(::ca::application * papp) :
   ::ca::ca(papp),
   SimpleMDIFrameWindow(papp),
   SimpleFrameWindow(papp)
{
	m_pEditFont = NULL;
	m_bFullScreen = false;
	m_pwndFullScrnBar = NULL;
	m_pmenuV033 = NULL;
}

CMainFrame::~CMainFrame()
{
	if(m_pEditFont != NULL)
	{
		m_pEditFont->DeleteObject();
		delete m_pEditFont;
	}
//	if(m_pAlbumDialog != NULL)
//	{
//		delete m_pAlbumDialog;
//	}
	if(m_pmenuV033 != NULL)
	{
		delete m_pmenuV033;
	}
//    if(m_pIPWnd != NULL)
  //  {
    //    delete m_pIPWnd;
    //}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (SimpleMDIFrameWindow::OnCreate(lpCreateStruct) == -1)
		return -1;

	//m_wndframework.SetAppearanceStyle(FrameSchemaHardCoded001::StyleRedOrange);


//    ModifyStyle(WS_CAPTION | WS_THICKFRAME, 0);
  //  SetDlgCtrlID(IDR_MAINFRAME);
    
//    if(!m_pIPWnd->CreateEx(0, AfxRegisterWndClass(NULL, 0, 0, 0), NULL, WS_VISIBLE, class rect(0, 0, 0, 0), NULL, 0, NULL))
  //      return -1;
    //m_pIPWnd->SetMenu(GetMenu());
//    ModifyStyle(0, WS_CHILD);
  //  SetParent(m_pIPWnd);

//    base_wnd * pWnd = GetParent();
  //  UINT nID = GetDlgCtrlID();
    //UINT nID2 = IDR_MAINFRAME;
    //AfxMessageBox(_T("7.5"));
	EnableDocking(CBRS_ALIGN_ANY);
	
	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_WRAPABLE | TBSTYLE_LIST ) ||
    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_WRAPABLE) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

    //for(int i = 0; i < 24; i++)
    //{
      //  m_wndToolBar.SetButtonStyle(i, m_wndToolBar.GetButtonStyle(i) |
        //    TBSTYLE_AUTOSIZE);
    //}

//    string str;
    
  //  str.LoadString(IDS_MAINFRAME_FULLSCREEN);
    //m_wndToolBar.SetButtonText(9, str);

    //str.LoadString(IDS_MAINFRAME_ALBUM);
    //m_wndToolBar.SetButtonText(11, str);

    //str.LoadString(IDS_MAINFRAME_LYRICS);
    //m_wndToolBar.SetButtonText(12, str);

    //str.LoadString(IDS_MAINFRAME_MIXER);
    //m_wndToolBar.SetButtonText(13, str);


//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    CVmcApp * pApp = CVmcApp::app(get_app());
//    m_pMenuManager->m_pfont = pApp->GetMenuFont();

	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

//	m_wndDlgBar.EnableDocking(CBRS_ALIGN_ANY);

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

//	m_wndReBar.EnableDocking(CBRS_ALIGN_ANY);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

//	CEdit *pEdit = (CEdit * ) m_wndDlgBar.GetDlgItem(IDC_EDIT_TIME);
//	if(pEdit)
//	{
//		m_pEditFont = new CFont();
//		LOGFONT logFont;
//		RECT rect;
//		pEdit->GetWindowRect(&rect);
//		logFont.lfHeight = rect.bottom - rect.top ;
/*		logFont.lfWidth = 0;
		logFont.lfEscapement = 0;
		logFont.lfWeight = FW_NORMAL;
		logFont.lfItalic = FALSE;
		logFont.lfUnderline = FALSE;
		logFont.lfStrikeOut = FALSE;
		logFont.lfCharSet =	ANSI_CHARSET;
		logFont.lfOutPrecision = OUT_TT_PRECIS;
		logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		logFont.lfQuality = PROOF_QUALITY;
		logFont.lfPitchAndFamily =  FIXED_PITCH | FF_SWISS;
		logFont.lfPitchAndFamily = 0;
		lstrcpy(logFont.lfFaceName, _T("Arial"));
		m_pEditFont->CreateFontIndirect(&logFont);
		pEdit->SetFont(m_pEditFont);
	}*/

//	CSliderCtrl *pSlider = (CSliderCtrl *) m_wndDlgBar.GetDlgItem(IDC_SLIDER);
//	if(pSlider)
//	{
//		pSlider->SetRange(0, 1000000);
//	}
	
	
	//CDBCentral * pDataCentral = DB();
	//CDBLongSet * pLongsSet = pDataCentral->GetDBLongSet();
//	DBMoveWindow("This");
/*	base_wnd * pParent = GetParent();

    CMenu * pMenu = GetMenu();
    CRelationV001<UINT, UINT, UINT, UINT> * prel;
	CMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
    m_pmenuV033 = new CMenuV033(
        CMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
		NULL,
        prel,
        CFontCentral::AppGetFontCentral()->GetMenuFont());
    m_pmenuV033->LoadMenu(pMenu, CMenuCentral::GetMenuCentral()->MenuV033GetImageList());
    m_hMenuDefault = m_pmenuV033->GetSafeHmenu();
    base_wnd * pMainWnd = AfxGetMainWnd();
    if(GetStyle() & WS_VISIBLE)
    {
        TRACE("VISIVEL\n");
    }
    SetMenu(m_pmenuV033);
    pMenu->DestroyMenu();*/

	CMenu * pmenu = GetMenu();
	pmenu->DestroyMenu();
	SetMenu(NULL);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    //AfxMessageBox(_T("7.7"));
	if( !SimpleMDIFrameWindow::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~WS_CLIPSIBLINGS;
    cs.style &= ~WS_CAPTION;
    //AfxMessageBox(_T("7.6"));
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	SimpleMDIFrameWindow::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	SimpleMDIFrameWindow::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



//void CMainFrame::OnToolsAlbum() 
//{
	// TODO: Add your command handler code here
  //  ViewToolsAlbum();

//}

CToolBar * CMainFrame::GetToolBar()
{

	return &m_wndToolBar;

}

CXfplayerDialogBar * CMainFrame::GetDialogBar()
{
	return &m_wndDlgBar;
}




void CMainFrame::OnDestroy() 
{
	CVmcApp * pApp = CVmcApp::app(get_app());
//	CDBCentral * pDataCentral = DB();
//	CDBLongSet * pLongsSet = pDataCentral->GetDBLongSet();
//	DBSaveWindowRect(("This"));
//	if(m_pAlbumDialog != NULL)
//		m_pAlbumDialog->DestroyWindow();
//	CMenu * pMenu = GetMenu();
//	delete pMenu;
//	m_hMenuDefault = NULL;
	SimpleMDIFrameWindow::OnDestroy();
	

	// TODO: Add your message handler code here
	
}

void CMainFrame::UpdateReserveList()
{
//	CVmcApp * pApp = CVmcApp::app(get_app());
//	CXfplayerDoc *pDoc = pApp->GetActiveDocument();
//	POSITION pos = pDoc->GetFirstViewPosition();
//	if(pos != NULL)
//	{
//		CXfplayerView *pView = (CXfplayerView *) pDoc->GetNextView(pos);
//		pView->UpdateReserveList();
//	}

}

void CMainFrame::OnViewFullScreen() 
{
    ViewFullScreen();
	// TODO: Add your command handler code here
       
}

void CMainFrame::OnUpdateViewFullScreen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
	if (IsFullScreen())
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if (IsFullScreen())
	{
		lpMMI->ptMaxSize.y = m_FullScreenWindowRect.Height();
		lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
		lpMMI->ptMaxSize.x = m_FullScreenWindowRect.Width();
		lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;
	}
	else
	{
		SimpleMDIFrameWindow::OnGetMinMaxInfo(lpMMI);
	}
}

bool CMainFrame::IsFullScreen()
{
	return m_bFullScreen;
}

void CMainFrame::OnExitFullScreen() 
{
	// TODO: Add your command handler code here
	if(IsFullScreen())
	{
		OnViewFullScreen();
	}
}

void CMainFrame::OnUpdateExitFullScreen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(IsFullScreen());
}

/*void CMainFrame::OnToolsOptions() 
{
	// TODO: Add your command handler code here

}

void CMainFrame::OnUpdateToolsOptions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}*/

/*void CMainFrame::OnFileProperties() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateFileProperties(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}*/


BOOL CMainFrame::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return SimpleMDIFrameWindow::OnHelpInfo(pHelpInfo);
}



void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	SimpleMDIFrameWindow::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	// TODO: Add your message handler code here
//	m_pMenuManager->ModifyMenu(pPopupMenu);
}


void CMainFrame::OnToolsMixer() 
{
/*    CMixerDialog * pNewDialog = new CMixerDialog();
    m_ptraMixerDialogs.Add(pNewDialog);
    pNewDialog->Create(IDD_MIXER);
    pNewDialog->SetNewDestination(MIXERLINE_COMPONENTTYPE_DST_SPEAKERS);
    pNewDialog->ShowWindow(SW_SHOWNORMAL);*/
	
}

void CMainFrame::OnUpdateToolsMixer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	SimpleMDIFrameWindow::OnSize(nType, cx, cy);
    
	
}

void CMainFrame::OnToolsCompactdatabase() 
{
	CVmcApp * pApp = CVmcApp::app(get_app());
//    DBCentral * pDataCentral = DB();
//    pDataCentral->CompactDatabase(NULL);
}

void CMainFrame::OnUpdateToolsCompactdatabase(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

void CMainFrame::OnPlayer() 
{
	// TODO: Add your command handler code here
    OpenPlayerWindow();
	
}

void CMainFrame::OnUpdatePlayer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnWindowCascade() 
{
	// TODO: Add your command handler code here
    FrameWindow * pFrameWnd = GetActiveFrame();
    if(pFrameWnd != NULL)
    {
        base_wnd * pWnd = pFrameWnd;
        while(true)
        {
            pWnd = pWnd->GetNextWindow();
            if(pWnd == NULL ||
                pWnd->get_handle() == pFrameWnd->get_handle())
                break;
        }
    }
	MDICascade();
   pFrameWnd = GetActiveFrame();
   if(pFrameWnd != NULL)
   {
      base_wnd * pWnd = pFrameWnd;
      while(true)
      {
         pWnd = pWnd->GetNextWindow();
         if(pWnd == NULL ||
            pWnd->get_handle() == pFrameWnd->get_handle())
            break;
      }
   }
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
		switch(pMsg->message)
		{
		case WM_DISPLAYCHANGE:
			int i;
			i = 2;
			break;
		default:
			break;
		}
//	if(pMsg->hwnd == get_handle())
//	{
//		switch(pMsg->message)
//		{
//		case VMSM_ECONOMODECHANGE:
//			OnEconoModeChange(pMsg->wParam);
//			return true;
//			break;
//		default:
//			break;
//		}
//	}
	return SimpleMDIFrameWindow::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return SimpleMDIFrameWindow::OnCreateClient(lpcs, pContext);
}

afx_msg LRESULT CMainFrame::OnEconoModeChange(WPARAM wParam, LPARAM lParam)
{
    int iEconoMode = wParam;
    SendMessageToDescendants(VMSM_ECONOMODECHANGE, iEconoMode);
    return true;
}

void CMainFrame::OnToolsSaveMemory() 
{
	// TODO: Add your command handler code here
	//CVmcApp * pApp = CVmcApp::app(get_app());
    /*if((Savings::AppGetEconoMode() & CSavings::SaveMemory) > 0)
        Savings::AppSetEconoMode(Savings::AppGetEconoMode() & ~ CSavings::SaveMemory);
    else
        Savings::AppSetEconoMode(Savings::AppGetEconoMode() | CSavings::SaveMemory);*/
}

void CMainFrame::OnUpdateToolsSaveMemory(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
/*	CVmcApp * pApp = CVmcApp::app(get_app());
    pCmdUI->SetCheck((CSavings::AppGetEconoMode() & CSavings::SaveMemory) > 0 ? 1 : 0);
    pCmdUI->Enable();*/
}

void CMainFrame::OnActivate(UINT nState, base_wnd* pWndOther, BOOL bMinimized) 
{
	SimpleMDIFrameWindow::OnActivate(nState, pWndOther, bMinimized);
	
    CVmcApp * pApp = CVmcApp::app(get_app());
    /*if(pApp->GetWelcomeDialog() != NULL && 
        ::IsWindow(pApp->GetWelcomeDialog()->GetSafeHwnd()))
    {
        if(nState ==WA_INACTIVE && 
            pWndOther->GetSafeHwnd() != pApp->GetWelcomeDialog()->GetSafeHwnd())
        {
            pApp->GetWelcomeDialog()->ShowWindow(SW_HIDE);
        }
        else
        {
/*            pApp->GetWelcomeDialog()->SetWindowPos(&wndTopMost,
                0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW|SWP_NOACTIVATE);*/
  //          pApp->GetWelcomeDialog()->SetWindowPos(&wndTopMost,
    //            0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
      /*  }
    }*/

	// TODO: Add your message handler code here
	
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, base_wnd* pParentWnd, CreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
    //AfxMessageBox(_T("7.8"));
    string str;
    str.Format(_T("nIDResource %d"), nIDResource);
    //AfxMessageBox(str);

	if(!SimpleMDIFrameWindow::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
        return FALSE;
    //AfxMessageBox(_T("7.9"));

//    delete m_pMenu;
//
  //  m_pMenu = new CMenu();
    //m_pMenu->LoadMenu(IDR_MAINFRAME);
    //SetMenu(m_pMenu);

    return TRUE;
}

void CMainFrame::OnInitMenu(CMenu* pMenu) 
{
	SimpleMDIFrameWindow::OnInitMenu(pMenu);
	
//    m_pMenuManager->ModifyMenu(pMenu);
	// TODO: Add your message handler code here
	
}

void CMainFrame::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	//if(m_pMenuManager->RelayDrawItem(nIDCtl, lpDrawItemStruct) == VMSR_SUCCESS)
        //return;
//    m_pMenuManager->RelayDrawItem(nIDCtl, lpDrawItemStruct);
	SimpleMDIFrameWindow::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

/*void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
//    m_pMenuManager->RelayMeasureItem(this, nIDCtl, lpMeasureItemStruct);
	FrameWindow::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}*/

void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
    if (lpMeasureItemStruct->CtlType == ODT_MENU)
	{
		ASSERT(lpMeasureItemStruct->CtlID == 0);
		CMenu* pMenu;

		_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
		if (pThreadState->m_hTrackingWindow == get_handle())
		{
			// start from popup
			pMenu = CMenu::FromHandle(pThreadState->m_hTrackingMenu);
		}
		else
		{
			// start from menubar
			pMenu = GetMenu();
		}
        if(pMenu)
        {
            /*if(pMenu->IsKindOf(RUNTIME_CLASS(CMenuV033)))
            {
                CMenuV033 * pPopup = CMenuV033::FindPopupMenuFromID((CMenuV033 *) pMenu, lpMeasureItemStruct->itemID, lpMeasureItemStruct->itemData);
                if(pPopup != NULL)
                {pPopup->MeasureItem(lpMeasureItemStruct);
                    return;
                }
            }
            else
            {
				CMenu * pPopup = CMenuUtil::FindPopupMenuFromID(pMenu, lpMeasureItemStruct->itemID);
                if(pPopup != NULL)
                {
                    pPopup->MeasureItem(lpMeasureItemStruct);
                    return;
                }
            }*/
        }
    }


	SimpleMDIFrameWindow::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

/*void CMainFrame::OpenToolsAlbum()
{
    CVmcApp * pApp = (CVmcApp *)AfxGetApp();
    if(CDataCentral::AppGetDBCentral()->IsWorking())
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
            if(CDataCentral::AppGetDBCentral()->IsBuildingSongsAlbum())
            {
                CCriticalSection *pcs;
                LPBUILDALBUMTHREADDATA lpData =
                    CDataCentral::AppGetDBCentral()->GetActiveBuildAlbumThreadData(&pcs);
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
	    
	    base_wnd * pParent = GetParent();
    }
    else
    {
        AfxMessageBox(
            IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE,
            MB_OK |
            MB_ICONINFORMATION);

    }

}*/

void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar == VK_ESCAPE &&
        IsFullScreen())
    {
        SendMessage(WM_COMMAND, MAKEWORD(ID_EXIT_FULL_SCREEN, 1), NULL);
    }
    else
    {
        SimpleMDIFrameWindow::OnKeyDown(nChar, nRepCnt, nFlags);
    }
}

VMSRESULT CMainFrame::ViewFullScreen()
{
	RECT rectDesktop;
	WINDOWPLACEMENT wpNew;
    WINDOWPLACEMENT wpChildNew;
	CVmcApp * pApp = CVmcApp::app(get_app());
///	CXfplayerDoc * pDoc = (CXfplayerDoc *) CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc();
//	CXfplayerView *pPlayerView = NULL;
   SimpleMDIChildWindow * pChildWnd = MDIGetActive();
   View  * pView = NULL;
   if(pChildWnd != NULL)
   {
      pView = pChildWnd->GetActiveView();
   }
    if(pView != NULL)
    {
//        if(pView->IsKindOf(RUNTIME_CLASS(CXfplayerView)))
  //      {
    //        pPlayerView = (CXfplayerView*) pView;
      //  }
    }
//    CFullScreenItem * pItem = NULL;
	if (!IsFullScreen())
	{
//        if(pPlayerView != NULL)
  //      {
    //        pPlayerView->SetOnSizeEnabled(false);
      //  }
        
//        pItem = NULL;
  //      if(pView != NULL)
    //    {
      //      m_fullScreenData.IncrementSize();
        //    pItem = &m_fullScreenData.LastElement();
        //}
		// need to hide all status bars
		m_wndStatusBar.ShowWindow(SW_HIDE);
		m_wndToolBar.ShowWindow(SW_HIDE);
		m_wndDlgBar.ShowWindow(SW_HIDE);
	//	m_wndReBar.ShowWindow(SW_HIDE);
		//CMenu * pMenu = GetMenu();
		SetMenu(NULL);
		//pMenu->DestroyMenu();
//		int i = GetStyle();
//		ModifyStyle(
//			WS_OVERLAPPEDWINDOW,
//			0,
//			SWP_FRAMECHANGED |
//			SWP_NOSENDCHANGING);
  //      ModifyStyleEx(
    //            	WS_EX_CLIENTEDGE,
	//		0,
	//		SWP_FRAMECHANGED |
      //      SWP_NOSENDCHANGING);

        base_wnd * pWnd = GetDlgItem(AFX_IDW_PANE_FIRST);
        if(pWnd != NULL)
        {
            pWnd->ModifyStyleEx(
                	    WS_EX_CLIENTEDGE,
			    0,
			    SWP_FRAMECHANGED |
                SWP_NOSENDCHANGING);
        }
        /*if(pItem != NULL)
        {
            pItem->m_dwChildStyle = pChildWnd->GetStyle();
            DWORD dwExStyle = pChildWnd->GetExStyle();
            DWORD ce = WS_EX_CLIENTEDGE;
            pItem->m_dwViewStyle = pView->GetStyle();
            pItem->m_dwViewStyleEx = pView->GetExStyle();
            pItem->m_pChildWindow = pChildWnd;
            pItem->m_pView = pView;
            pChildWnd->GetWindowPlacement(&pItem->m_wpPrevChildWindow);
		    pChildWnd->ModifyStyle(
			    WS_OVERLAPPEDWINDOW,
			    0,
			    SWP_FRAMECHANGED |
			    SWP_NOSENDCHANGING);
		    pView->ModifyStyleEx(
			    WS_EX_CLIENTEDGE,
			    0,
			    SWP_FRAMECHANGED |
			    SWP_NOSENDCHANGING);
        }*/
// pView->GetScrollRange 

//		i = GetStyle();
//		ModifyStyle(
//			WS_VISIBLE | WS_CHILD | WS_CAPTION,
//			0,
//			SWP_SHOWWINDOW);

//		i = GetExStyle();
		// We'll need these to restore the original state.
		GetWindowPlacement (&m_wpPrev);

		m_wpPrev.length = sizeof m_wpPrev;
		
		//Adjust RECT to new size of window
        class rect rectChild;
		::GetWindowRect ( ::GetDesktopWindow(), &rectDesktop );
		::AdjustWindowRectEx(&rectDesktop, GetStyle(), FALSE,
			GetExStyle());
/*		if(pItem != NULL)
        {
            ::GetWindowRect ( ::GetDesktopWindow(), &rectChild );
            ::AdjustWindowRectEx(&rectChild, pChildWnd->GetStyle(), FALSE,
			    pChildWnd->GetExStyle());
    		wpChildNew = pItem->m_wpPrevChildWindow;
	    	wpChildNew.showCmd =  SW_SHOWNORMAL;
		    wpChildNew.rcNormalPosition = rectChild;
        }*/
		
		// Remember this for OnGetMinMaxInfo()
		m_FullScreenWindowRect = rectDesktop;
	
		wpNew = m_wpPrev;
		wpNew.showCmd =  SW_SHOWNORMAL;
		wpNew.rcNormalPosition = rectDesktop;

		m_pwndFullScrnBar=new CToolBar;

		if(!m_pwndFullScrnBar->Create(this,
			CBRS_SIZE_DYNAMIC|CBRS_FLOATING)
			|| !m_pwndFullScrnBar->LoadToolBar(IDR_FULLSCREEN))
		{
			TRACE0("Failed to create toolbar\n");
			return VMSR_E_FAIL;	  // fail to create
		}
	
//		m_wndReBar.AddBar(m_pwndFullScrnBar);
		//don't allow the toolbar to dock
//		m_pwndFullScrnBar->EnableDocking(0);
//		m_pwndFullScrnBar->SetWindowPos(0,100,100,
//			0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_SHOWWINDOW);
//		m_pwndFullScrnBar->SetWindowText(_T("Full Screen"));
		//FloatControlBar(m_pwndFullScrnBar, class point(100,100));
//		FloatControlBar(m_pwndFullScrnBar, class point(100,100));
		m_bFullScreen=TRUE;
//        if(pPlayerView != NULL)
  //      {
    //        pPlayerView->SetOnSizeEnabled();
      //  }
//        if(pItem != NULL)
        //{
//            pItem->m_pChildWindow->ShowWindow(SW_MAXIMIZE);
  //      }
	}
	else
	{	
		CVmcApp * pApp = CVmcApp::app(get_app());
//		CXfplayerDoc * pDoc = (CXfplayerDoc *) CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc();
//		CXfplayerView *pView = pDoc->GetLyricView();
//		pView->SetOnSizeEnabled(false);
		m_pwndFullScrnBar->DestroyWindow();
		
		delete m_pwndFullScrnBar;

		m_bFullScreen=FALSE;
//		ModifyStyle(
//			0,
//			WS_OVERLAPPEDWINDOW,
//			SWP_FRAMECHANGED);

        /*while(m_fullScreenData.GetSize() > 0)
        {
            CFullScreenItem * pItem = &m_fullScreenData.FirstElement();
            pItem->m_pChildWindow->ModifyStyle(
                ~pItem->m_dwChildStyle,
                pItem->m_dwChildStyle,
                SWP_FRAMECHANGED);
            pItem->m_pView->ModifyStyleEx(
                ~pItem->m_dwViewStyleEx,
                pItem->m_dwViewStyleEx,
                SWP_FRAMECHANGED);
            pItem->m_pChildWindow->SetWindowPlacement(
                &pItem->m_wpPrevChildWindow);
            m_fullScreenData.RemoveAt(0);
        }
		*/
		m_wndStatusBar.ShowWindow(SW_SHOWNORMAL);
		m_wndToolBar.ShowWindow(SW_SHOWNORMAL);
		m_wndDlgBar.ShowWindow(SW_SHOWNORMAL);
		m_wndReBar.ShowWindow(SW_SHOWNORMAL);
		//CMenu * pMenu = new CMenu();
		/*if(m_pmenuV033 == NULL)
		{
            CRelationV001<UINT, UINT, UINT, UINT> * prel;
            CMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
            m_pmenuV033 = new CMenuV033(
                CMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
				NULL,
                prel,
                CFontCentral::AppGetFontCentral()->GetMenuFont());
			m_pmenuV033->LoadMenu(IDR_MAINFRAME);
		}*/

		//CMenu menu;
		//menu.LoadMenu(IDR_MAINFRAME);
		
		//SetMenu(&menu);
		//SetMenu(m_pmenuV033);
		//menu.m_hMenu = NULL;
		//m_hMenuDefault = menu.GetSafeHmenu();
		//m_hMenuDefault = m_pmenuV033->GetSafeHmenu();
		//wpNew = m_wpPrev;
//		pView->SetOnSizeEnabled();
        //pItem = NULL;
	//}
      }
	SetWindowPlacement ( &wpNew );
    return VMSR_SUCCESS;
}

//VMSRESULT CMainFrame::ViewToolsAlbum()
//{
    //OpenToolsAlbum();
    //return VMSR_SUCCESS;
//}

void CMainFrame::OnEnterIdle(UINT nWhy, base_wnd* pWho) 
{
	SimpleMDIFrameWindow::OnEnterIdle(nWhy, pWho);
	
	// TODO: Add your message handler code here
	
}

VMSRESULT CMainFrame::OpenPlayerWindow()
{

    CVmcApp * pApp = CVmcApp::app(get_app());
	ASSERT(pApp != NULL);
//	CXfplayerDoc * pDoc = (CXfplayerDoc *) CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc();
  //  if(pDoc == NULL)
    //{
      //  CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->OpenDocumentFile(NULL);
    //}
    //else
    //{
      //  CXfplayerView * pView = pDoc->GetLyricView();
        //if(pView != NULL)
//        {
  //          pView->GetParentFrame()->BringWindowToTop();
    //    }
    //}
    return VMSR_SUCCESS;

}

window_frame::FrameSchema * CMainFrame::create_frame_schema()
{
   window_frame::FrameSchemaHardCoded002 * pschema = new window_frame::FrameSchemaHardCoded002(get_app());
   pschema->m_pruntimeclassControlBoxButton = &typeid(MetaButton);
   pschema->SetStyle(window_frame::FrameSchemaHardCoded002::StyleRedOrange);
   return pschema;
}
