// PlaylistFrame.cpp : implementation file
//

#include "stdafx.h"
#include "PlaylistFrame.h"

// vmsguibase
//#include "vmsguibase/BaseMenuCentral.h"
#include "guibase/UserInterfaceImageManager.h"

// vmsgen
#include "gen/PushingRoutingFrame.h"


#include "PlaylistListView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// PlaylistFrame

IMPLEMENT_DYNCREATE(PlaylistFrame, SimpleFrameWnd)

PlaylistFrame::PlaylistFrame()
{
}

PlaylistFrame::~PlaylistFrame()
{
}


BEGIN_MESSAGE_MAP(PlaylistFrame, SimpleFrameWnd)
	//{{AFX_MSG_MAP(PlaylistFrame)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
	ON_WM_ACTIVATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PlaylistFrame message handlers

BOOL PlaylistFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
//	cs.style &= ~WS_CAPTION;
  // cs.style &= ~WS_THICKFRAME;
   //cs.style |= WS_CLIPCHILDREN;
   //cs.dwExStyle |= WS_EX_TRANSPARENT;
	return SimpleFrameWnd::PreCreateWindow(cs);
}




BOOL PlaylistFrame::OnCreateClient(LPCREATESTRUCT lpcs, CreateContext* pContext) 
{
	if(!SimpleFrameWnd::OnCreateClient(lpcs, pContext))
        return FALSE;

/*    m_pipwnd = new CPlaylistInPlaceWnd();
    if(m_pipwnd == NULL)
        return FALSE;

	if(!m_pipwnd->CreateEx(WS_EX_TRANSPARENT, NULL, NULL, WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, IDR_PLAYLIST, NULL))
        return FALSE;*/
    ASSERT(pContext->m_pNewViewClass != NULL);
    
    return TRUE;
}

/*CPlaylistInPlaceWnd * PlaylistFrame::GetInPlaceWnd()
{
    return m_pipwnd;
}*/

void PlaylistFrame::OnSize(UINT nType, int cx, int cy) 
{
	CDC * pdc = GetDC();

	ReleaseDC(pdc);

	SimpleFrameWnd::OnSize(nType, cx, cy);
}

BOOL PlaylistFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CreateContext* pContext) 
{
	if(!SimpleFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
        return FALSE;
	return TRUE;
}

void PlaylistFrame::RecalcLayout(BOOL bNotify) 
{
//	if(m_pipwnd->m_pwf != NULL)
  //  {
    //    m_pipwnd->m_wndframework.RecalcLayout();
//    }
  //  else
    //{
        SimpleFrameWnd::RecalcLayout(bNotify);
    //}
}

int PlaylistFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   if(SimpleFrameWnd::OnCreate(lpCreateStruct) == -1)
	return -1;

   MusicalPlayerLightApp * papp = (MusicalPlayerLightApp *) AfxGetApp();
   m_menuhook.Initialize(
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      NULL,
      FontCentral::AppGetFontCentral()->GetMenuFont());

   m_menuhook.Install(this);


   SetMenu(NULL);


   UINT puiPlaylistToolBar[] =
      {
         ID_FILE_OPEN,
         0,
         ID_FILE_ADD,
         0,
         ID_FILE_PRINT,
         0,
         ID_EXECUTE_PLAY,
         0,
         ID_EDIT_REMOVE,
         0xffffffff
      };
   if (!m_toolbar.CreateEx(this))
	
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
   papp->GetImageManager().LoadToolbar(m_toolbar, puiPlaylistToolBar);

/*	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_toolbar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}*/


	SetMenu(NULL);

	return 0;
}


BOOL PlaylistFrame::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	//return SimpleFrameWnd::OnEraseBkgnd(pDC);
    return TRUE;
}

void PlaylistFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
    //CVMSApp * pApp = (CVMSApp *) AfxGetApp();

	SimpleFrameWnd::OnClose();


}



BOOL PlaylistFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{

	return SimpleFrameWnd::OnCmdMsg(
		nID,
		nCode,
		pExtra,
		pHandlerInfo);

}


BOOL PlaylistFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
//	if(m_pipwnd->m_pwf != NULL &&
  //      m_pipwnd->m_wndframework.RelayEvent(pMsg))
    //    return TRUE;

	return SimpleFrameWnd::PreTranslateMessage(pMsg);
}

void PlaylistFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
		SimpleFrameWnd::OnActivate(nState, pWndOther, bMinimized);

//    m_pipwnd->m_wndframework.SetActiveFlag(nState == WA_ACTIVE    ||
  //      nState == WA_CLICKACTIVE);


    //CRect rectWnd;
    //GetWindowRect(rectWnd);
    //TwcRedraw(rectWnd);
	
}

/*void PlaylistFrame::Child(CWnd * pwndParent)
{
	bool bVisible = IsWindowVisible() != 0;
	SetParent(pwndParent);
	bVisible = IsWindowVisible() != 0;
	ModifyStyle(
		WS_CAPTION
		| WS_BORDER,
		WS_CHILD,
		SWP_SHOWWINDOW);
	bVisible = IsWindowVisible() != 0;
	ModifyStyleEx(
		0,
		WS_EX_TOOLWINDOW, SWP_SHOWWINDOW);
//    m_pipwnd->OnChangeAttachment();
  //  m_pipwnd->m_wndframework.SetWindows(m_pipwnd, m_pipwnd, m_pipwnd, m_pipwnd);
    //m_pipwnd->m_wndframework.SetAppearanceTransparency(_vmswndfrm::Transparent);
	m_ptwc->TwcFinalize();
	UpdateControlBox();
	Layout();
	bVisible = IsWindowVisible() != 0;
    //m_pViewActive = NULL;
}*/


void PlaylistFrame::OnDestroy() 
{

//	TwcFinalize();

	SimpleFrameWnd::OnDestroy();
	
}

/*CPlaylistView * PlaylistFrame::GetPlaylistView()
{
	if(m_pViewActive != NULL
		&& m_pViewActive->IsKindOf(RUNTIME_CLASS(CPlaylistView)))
		return (CPlaylistView *) m_pViewActive;
	else
	{
		CView * pview = (CView *) GetDlgItem(AFX_IDW_PANE_FIRST);
		if(pview != NULL &&
			pview->IsKindOf(RUNTIME_CLASS(CPlaylistView)))
			return (CPlaylistView *) pview;
		else
			return NULL;
	}

}*/

/*void PlaylistFrame::UpdateControlBox()
{
    CPlaylistView * pplaylistview = GetPlaylistView();
    if(pplaylistview == NULL)
        return;
    CXfplayerView * pplayerview = GetParentLyricView();
	CWnd * pwndParent = GetParent();

    if(pwndParent == NULL)
    {
        m_wndframework.m_pwa->m_pbuttonUp->ShowWindow(SW_HIDE);
    }
    else
    {
        m_wndframework.m_pwa->m_pbuttonUp->ShowWindow(SW_SHOW);
    }
    if(pwndParent != NULL ||
        pplaylistview->GetMode() == CPlaylistView::ModeNormal)
    {
        m_wndframework.m_pwa->m_pbuttonDown->ShowWindow(SW_SHOW);
    }
    else
    {
        m_wndframework.m_pwa->m_pbuttonDown->ShowWindow(SW_HIDE);
    }
    
    m_wndframework.m_pwa->UpdateControlBox();
    
}*/

CView * PlaylistFrame::GetParentLyricView()
{
    CWnd * pParentWnd = GetParent();
    if(pParentWnd != NULL &&
        pParentWnd->IsKindOf(RUNTIME_CLASS(CView)))
        return (CView *) pParentWnd;
    return NULL;

}

void PlaylistFrame::PostNcDestroy() 
{
	SimpleFrameWnd::PostNcDestroy();
}

BOOL PlaylistFrame::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return SimpleFrameWnd::DestroyWindow();
}

void PlaylistFrame::TransparentFrameWndOnAfterFrame()
{
	if(GetActiveDocument() != NULL)
	{
		GetActiveDocument()->UpdateAllViews(NULL, PlaylistDoc::LHINT_FRAMEUP);
	}
}


void PlaylistFrame::TransparentFrameWndOnAfterChild()
{
	if(GetActiveDocument() != NULL)
	{
		GetActiveDocument()->UpdateAllViews(NULL, PlaylistDoc::LHINT_FRAMEDOWN);
	}
/*    CWnd * pwndParent = GetParent();
    if(pwndParent == NULL)
    {
		
        if(CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc() == NULL)
        {
            CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->OpenDocumentFile(NULL);
        }
		GetPlaylistView()->SetMode(CPlaylistView::ModeNormal);

        if(CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc() != NULL)
        {
			((CXfplayerDoc *) CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc())->Attach(GetPlaylistView()->GetDocument());
        }
		UpdateControlBox();
    }
	else if(GetPlaylistView()->GetMode() != CPlaylistView::ModeMinimum)
	{
        if(CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc() == NULL)
        {
            CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->OpenDocumentFile(NULL);
        }
		GetPlaylistView()->SetMode(CPlaylistView::ModeMinimum);

        if(CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc() != NULL)
        {
			((CXfplayerDoc *) CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc())->Attach(GetPlaylistView()->GetDocument());
        }
		UpdateControlBox();
	}
	m_wndframework.m_pwa->UpdateControlBox();    */

}


/*bool PlaylistFrame::WndFrameworkDownUpGetUpEnable()
{
	if(GetActiveDocument() != NULL)
}

bool PlaylistFrame::WndFrameworkDownUpGetDownEnable()
{
}*/


