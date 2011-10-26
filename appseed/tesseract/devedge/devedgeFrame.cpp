// MainFrm.cpp : implementation of the devedgeFrame class
//

#include "stdafx.h"

#include "devedgeFrame.h"
#include "devedgeView.h"
#include "netnode/netnodeBergEdgeDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// devedgeFrame

// IMPLEMENT_DYNCREATE(devedgeFrame, SimpleFrameWindow)

BEGIN_MESSAGE_MAP(devedgeFrame, SimpleFrameWindow)
	//{{AFX_MSG_MAP(devedgeFrame)
/* xxx	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_MOVE()
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_NCPAINT()
	ON_WM_INITMENUPOPUP()
	ON_WM_INITMENU()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, SimpleFrameWindow::OnHelpFinder)
	ON_COMMAND(ID_HELP, SimpleFrameWindow::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, SimpleFrameWindow::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, SimpleFrameWindow::OnHelpFinder)
	ON_WM_COPYDATA() */
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// devedgeFrame construction/destruction

devedgeFrame::devedgeFrame(::ca::application * papp)
: SimpleFrameWindow(papp)
{
   m_iFrameData = 10;
   DISetSection("MusicalPlayerscreencaptureFrame");
   m_iAnimateStep = 0;
   AfxGetApp()->m_pMainWnd = this;

   WfiEnableFullScreen();

   m_datakeyWindow = VMSDATAKEY(WindowData);
}

devedgeFrame::~devedgeFrame()
{
}

int devedgeFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (SimpleFrameWindow::OnCreate(lpCreateStruct) == -1)
		return -1;

   SetTimer(8913, 5000, 0);
   SetTimer(4033, 100, 0);
   ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

   

   //m_menuhook.Initialize(
     // BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      //BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      //NULL,
      //FontCentral::AppGetFontCentral()->GetMenuFont());

   //m_menuhook.Install(this);



   //m_hMenuDefault = NULL;

/* 	if (!m_menubar.CreateEx(this))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

   if(!m_menubar.Initialize(
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      NULL,
      FontCentral::AppGetFontCentral()->GetMenuFont()) ||
		VMS_FAILED(m_menubar.LoadMenuBar(IDR_MAINFRAME)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}*/

/*   m_imagelist.Create(16, 16, 0, 10, 10);
   m_imagelist.Add(
      (HICON)
      ::LoadImage(
         AfxGetApp()->m_hInstance,
         MAKEINTRESOURCE(IDI_LANGUAGE_CHANGE),
         IMAGE_ICON,
         16, 16, 0));*/

   /*m_menubar._001SetImageList(&m_imagelist);
   m_menubar.SetItemImage(m_menubar._001GetItemCount() - 1, 0);

	if (!m_toolbar.CreateEx(this, TBSTYLE_FLAT,
		WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC
      | CBRS_DRAGMOVE,
		rect(0, 0, 0, 0),
		AFX_IDW_TOOLBAR) ||
		!m_toolbar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_toolbarView.CreateEx(this, TBSTYLE_FLAT,
		WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC
      | CBRS_DRAGMOVE,
      rect(0, 0, 0, 0),
		AFX_IDW_TOOLBAR + 1) ||
		!m_toolbarView.LoadToolBar(IDR_VIEW))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
   
   
	if (!m_dialogbar.Create(this, IDR_MAINFRAME, 
		WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC
      | CBRS_DRAGMOVE, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}*/

/*	if (!m_wndReBar.Create(this) ||
      !m_wndReBar.AddBar(&m_menubar) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
      !m_wndReBar.AddBar(&m_toolbarView) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}*/

/*	if (!m_statusbar.Create(this) ||
		!m_statusbar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}*/

	// TODO: Remove this if you don't want tool tips
	/*m_toolbar.SetBarStyle(m_toolbar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	m_dialogbar.SetBarStyle(m_dialogbar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

   EnableDocking(CBRS_ALIGN_ANY);

   m_toolbar.EnableDocking(CBRS_ALIGN_ANY);
   DockControlBar(&m_toolbar);

   m_toolbarView.EnableDocking(CBRS_ALIGN_ANY);
   DockControlBar(&m_toolbarView);

   m_dialogbar.EnableDocking(CBRS_ALIGN_TOP);
   m_dialogbar.EnableDocking(CBRS_ALIGN_BOTTOM);
   DockControlBar(&m_toolbar);*/

   WindowDataLoadWindowRect();
   WindowDataEnableSaveWindowRect(true);


	return 0;
}

void devedgeFrame::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
	SimpleFrameWindow::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CLOSE,          pinterface, this, &devedgeFrame::_001OnClose);
}


BOOL devedgeFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !SimpleFrameWindow::PreCreateWindow(cs) )
		return FALSE;
   cs.dwExStyle &= ~WS_EX_WINDOWEDGE;
   ::DestroyMenu(cs.hMenu);
   cs.hMenu = NULL;

   bergedge::application_interface * pbergedgeapp = bergedge::get_app();
   if(pbergedgeapp != NULL)
   {
      bergedge_document * pdoc = pbergedgeapp->get_edge(0);
      if(pdoc != NULL)
      {
         POSITION  pos = pdoc->GetFirstViewPosition();
         View * pview = pdoc->GetNextView(pos);
         cs.hwndParent = *pview;
      }
   }
   else
   {
      if(AfxGetApp()->m_pMainWnd != this)
      {
         cs.hwndParent = AfxGetApp()->m_pMainWnd->GetSafeHwnd();
      }
   }
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// devedgeFrame diagnostics

#ifdef _DEBUG
void devedgeFrame::AssertValid() const
{
	SimpleFrameWindow::AssertValid();
}

void devedgeFrame::Dump(CDumpContext& dc) const
{
	SimpleFrameWindow::Dump(dc);
}


#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// devedgeFrame message handlers


void devedgeFrame::WfiOnFullScreen(bool bFullScreen)
{
   if(bFullScreen)
   {
      ModifyStyle(
         WS_BORDER |
         WS_CAPTION |
         WS_THICKFRAME,
         0,
         0);

      ShowControlBars(false);

		DWORD dwStyle = GetStyle();

      DWORD dwStyleEx = GetExStyle();

      rect rectDesktop;
		
      ::GetWindowRect ( ::GetDesktopWindow(), &rectDesktop );

		::AdjustWindowRectEx(
			&rectDesktop,
			dwStyle,
			FALSE,
			dwStyleEx);

      m_FullScreenWindowRect = rectDesktop;
      
      SetWindowPos(
         &wndTop,
         rectDesktop.left, rectDesktop.top,
         rectDesktop.Width(), rectDesktop.Height(),
         SWP_FRAMECHANGED |
         SWP_SHOWWINDOW);
      RecalcLayout();
   }
   else
   {
      ShowControlBars(true);
      if(!m_bCustomFrame)
      {
         ModifyStyle(
            0,
            WS_BORDER |
            WS_CAPTION |
            WS_THICKFRAME,
            SWP_FRAMECHANGED);
      }
      RecalcLayout();
   }
   if(GetActiveView() != NULL)
   {
   }
   
   DISave("FullScreen", bFullScreen);

}

void devedgeFrame::OnViewFullScreen() 
{
	ToggleFullScreen();
}

void devedgeFrame::OnUpdateViewFullScreen(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();	
   pCmdUI->SetCheck(WfiIsFullScreen() ? 1 : 0);	
}

void devedgeFrame::ToggleFullScreen()
{
   WfiFullScreen(!WfiIsFullScreen(), true);
}

void devedgeFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	if (IsFullScreen())
	{
		lpMMI->ptMaxSize.y = m_FullScreenWindowRect.Height();
		lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
		lpMMI->ptMaxSize.x = m_FullScreenWindowRect.Width();
		lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;
	}
	else
	{
   	SimpleFrameWindow::OnGetMinMaxInfo(lpMMI);
	}
}

bool devedgeFrame::IsFullScreen()
{
   return WfiIsFullScreen();
}


void devedgeFrame::OnMove(int x, int y) 
{
	SimpleFrameWindow::OnMove(x, y);
}

void devedgeFrame::OnClose() 
{
	SimpleFrameWindow::OnClose();
}

void devedgeFrame::OnSysCommand(UINT nID, LPARAM lParam) 
{

   if(nID == SC_SCREENSAVE)
   {
   }
	
	SimpleFrameWindow::OnSysCommand(nID, lParam);
}





void devedgeFrame::OnTimer(UINT nIDEvent) 
{
   static float theta;
   if(nIDEvent == 3)
   {
      //AnimateStatusBar();
   }
   else if(nIDEvent == 8913)
   {
   }
   else if(nIDEvent == 4033)
   {
// OpenGL animation code goes here
			
			//glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			//glClear( GL_COLOR_BUFFER_BIT );
			
			/*glPushMatrix();
			glRotatef( theta, 0.0f, 1.0f, 1.0f );
			glBegin( GL_TRIANGLES );
			glColor3f( 1.0f, 0.0f, 0.0f ); glVertex2f( 0.0f, 1.0f );
			glColor3f( 0.0f, 1.0f, 0.0f ); glVertex2f( 0.87f, -0.5f );
			glColor3f( 0.0f, 0.0f, 1.0f ); glVertex2f( -0.87f, -0.5f );
			glEnd();
			glPopMatrix();*/
			
			//SwapBuffers( m_hdcOpenGL );
			
			theta += 2.0f;
		
   }
	SimpleFrameWindow::OnTimer(nIDEvent);
}

void devedgeFrame::SetAnimatedStatusBarText(LPCTSTR lpcsz)
{
   m_strAnimatedStatusBarText = lpcsz;
   if(m_strAnimatedStatusBarText.is_empty())
   {
      KillTimer(3);
   }
   else
   {
      SetTimer(3, 500, NULL);
   }
}

void devedgeFrame::AnimateStatusBar()
{
   if(m_strAnimatedStatusBarText.is_empty())
      return;

   int iLen = m_strAnimatedStatusBarText.GetLength();
   m_iAnimateStep++;
   if(m_iAnimateStep > iLen)
      m_iAnimateStep = 0;


//   m_statusbar.SetPaneText(0, m_strAnimatedStatusBarText.Mid(m_iAnimateStep));
}


void devedgeFrame::ShowControlBars(bool bShow)
{
   UINT nShow;
   if(bShow)
   {
      nShow = SW_SHOW;
   }
   else
   {
      nShow = SW_HIDE;
   }

/*   m_toolbar.ShowWindow(nShow);
   m_toolbarView.ShowWindow(nShow);
//   m_statusbar.ShowWindow(nShow);
   m_menubar.ShowWindow(nShow);
   m_dialogbar.ShowWindow(nShow);*/

}

void devedgeFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	SimpleFrameWindow::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

void devedgeFrame::OnNcPaint() 
{
	// TODO: Add your message handler code here
	
	// Do not call SimpleFrameWindow::OnNcPaint() for painting messages
}

void devedgeFrame::OnTogglecustomframe() 
{
	SetCustomFrame(!GetCustomFrame());
	
}

void devedgeFrame::OnUpdateTogglecustomframe(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();
   pCmdUI->SetCheck(m_bCustomFrame ? 1 : 0);
}


BOOL devedgeFrame::OnCopyData(base_wnd * pwnd, COPYDATASTRUCT* pcds)
{

   return FALSE;
}


BOOL devedgeFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, CAFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return SimpleFrameWindow::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void devedgeFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	SimpleFrameWindow::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	// TODO: Add your message handler code here
	
}

void devedgeFrame::OnInitMenu(CMenu* pMenu) 
{
	SimpleFrameWindow::OnInitMenu(pMenu);
	
	// TODO: Add your message handler code here
	
}

void devedgeFrame::OnActivate(UINT nState, base_wnd* pWndOther, BOOL bMinimized) 
{
	SimpleFrameWindow::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
}


void devedgeFrame::_001OnClose(gen::signal_object * pobj)
{
   pobj->m_bRet = true;
   ShowWindow(SW_HIDE);
}
