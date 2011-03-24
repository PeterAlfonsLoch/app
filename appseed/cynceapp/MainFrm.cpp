// MainFrm.cpp : implementation of the MainFrame class
//

#include "stdafx.h"

#include "MainFrm.h"
#include "VmpLightViewUpdateHint.h"
#include "MPLightView.h"

#include "PaneView1.h"

#include "MediaLibraryViewUpdateHint.h"
#include "mediamanager/AlbumBuild.h"


#include <gl/gl.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MainFrame

IMPLEMENT_DYNCREATE(MainFrame, SimpleFrameWnd)

BEGIN_MESSAGE_MAP(MainFrame, SimpleFrameWnd)
	//{{AFX_MSG_MAP(MainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullScreen)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, OnUpdateViewFullScreen)
	ON_WM_GETMINMAXINFO()
	ON_WM_MOVE()
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
	ON_COMMAND(ID_VIEW_KARAOKE, OnViewKaraoke)
	ON_UPDATE_COMMAND_UI(ID_VIEW_KARAOKE, OnUpdateViewKaraoke)
	ON_COMMAND(ID_VIEW_PLAYLIST, OnViewPlaylist)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PLAYLIST, OnUpdateViewPlaylist)
	ON_COMMAND(ID_VIEW_ALBUM, OnViewAlbum)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALBUM, OnUpdateViewAlbum)
	ON_COMMAND(ID_FILE_OPEN_EX, OnFileOpenEx)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN_EX, OnUpdateFileOpenEx)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_NCPAINT()
	ON_COMMAND(ID_TOGGLECUSTOMFRAME, OnTogglecustomframe)
	ON_UPDATE_COMMAND_UI(ID_TOGGLECUSTOMFRAME, OnUpdateTogglecustomframe)
	ON_COMMAND(ID_VIEW_OPTIONS, OnViewOptions)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OPTIONS, OnUpdateViewOptions)
	ON_COMMAND(ID_VIEW_NEXT_PANE, OnViewNextPane)
	ON_WM_INITMENUPOPUP()
	ON_WM_INITMENU()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, SimpleFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, SimpleFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, SimpleFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, SimpleFrameWnd::OnHelpFinder)
	ON_REGISTERED_MESSAGE(VM_SIMPLE, OnVmSimple)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// MainFrame construction/destruction

MainFrame::MainFrame()
{
   m_iFrameData = 10;
   DISetSection("MusicalPlayerMainFrame");
   m_iAnimateStep = 0;

   WfiEnableFullScreen();

   m_datakeyWindow = VMSDATAKEY(WindowData);
   m_iWindowDataId = vmplite::WindowDataMainFrame;
}

MainFrame::~MainFrame()
{
}

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (SimpleFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

   SetTimer(8913, 5000, 0);
   SetTimer(4033, 100, 0);
   ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

   m_menuhook.Initialize(
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      NULL,
      FontCentral::AppGetFontCentral()->GetMenuFont());

   m_menuhook.Install(this);



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

   m_imagelist.Create(16, 16, 0, 10, 10);
   m_imagelist.Add(
      (HICON)
      ::LoadImage(
         AfxGetApp()->m_hInstance,
         MAKEINTRESOURCE(IDI_LANGUAGE_CHANGE),
         IMAGE_ICON,
         16, 16, 0));

   /*m_menubar._001SetImageList(&m_imagelist);
   m_menubar.SetItemImage(m_menubar._001GetItemCount() - 1, 0);

	if (!m_toolbar.CreateEx(this, TBSTYLE_FLAT,
		WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC
      | CBRS_DRAGMOVE,
		CRect(0, 0, 0, 0),
		AFX_IDW_TOOLBAR) ||
		!m_toolbar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_toolbarView.CreateEx(this, TBSTYLE_FLAT,
		WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC
      | CBRS_DRAGMOVE,
      CRect(0, 0, 0, 0),
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

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !SimpleFrameWnd::PreCreateWindow(cs) )
		return FALSE;
   cs.dwExStyle &= ~WS_EX_WINDOWEDGE;
   ::DestroyMenu(cs.hMenu);
   cs.hMenu = NULL;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// MainFrame diagnostics

#ifdef _DEBUG
void MainFrame::AssertValid() const
{
	SimpleFrameWnd::AssertValid();
}

void MainFrame::Dump(CDumpContext& dc) const
{
	SimpleFrameWnd::Dump(dc);
}


#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MainFrame message handlers


void MainFrame::WfiOnFullScreen(bool bFullScreen)
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

      CRect rectDesktop;
		
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
      CVmpLightViewUpdateHint uh;
      uh.SetType(CVmpLightViewUpdateHint::TypeFullScreen);
      uh.m_bFullScreen = bFullScreen;
      GetActiveView()->GetDocument()->UpdateAllViews(NULL, 0, &uh);
   }
   
   DISave("FullScreen", bFullScreen);

}

void MainFrame::OnViewFullScreen() 
{
	ToggleFullScreen();
}

void MainFrame::OnUpdateViewFullScreen(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();	
   pCmdUI->SetCheck(WfiIsFullScreen() ? 1 : 0);	
}

void MainFrame::ToggleFullScreen()
{
   WfiFullScreen(!WfiIsFullScreen(), true);
}

void MainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
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
   	SimpleFrameWnd::OnGetMinMaxInfo(lpMMI);
	}
}

bool MainFrame::IsFullScreen()
{
   return WfiIsFullScreen();
}


void MainFrame::OnMove(int x, int y) 
{
	SimpleFrameWnd::OnMove(x, y);
}

void MainFrame::OnClose() 
{
	SimpleFrameWnd::OnClose();
}

void MainFrame::OnSysCommand(UINT nID, LPARAM lParam) 
{

   if(nID == SC_SCREENSAVE)
   {
      if(GetActiveView() != NULL
         && GetActiveView()->IsKindOf(RUNTIME_CLASS(MusicalPlayerLightView)))
      {
         MusicalPlayerLightView * pview = (MusicalPlayerLightView *) GetActiveView();
         if(pview->_ExecuteIsEntertaining())
         {
            return;
         }
      }
   }
	
	SimpleFrameWnd::OnSysCommand(nID, lParam);
}

void MainFrame::OnViewKaraoke() 
{
   ShowView(PaneViewKaraoke);
}

void MainFrame::OnUpdateViewKaraoke(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(GetViewId() != PaneViewKaraoke);
   pCmdUI->SetCheck(GetViewId() == PaneViewKaraoke);
}

void MainFrame::OnFileOpenEx() 
{
   ShowView(PaneViewFileManager);
}

void MainFrame::OnUpdateFileOpenEx(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetViewId() != PaneViewFileManager);
   pCmdUI->SetCheck(GetViewId() == PaneViewFileManager);
}

void MainFrame::OnViewPlaylist() 
{
   ShowView(PaneViewPlaylist);
}

void MainFrame::OnUpdateViewPlaylist(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetViewId() != PaneViewPlaylist);
   pCmdUI->SetCheck(GetViewId() == PaneViewPlaylist);
}

void MainFrame::OnViewAlbum() 
{
   ShowView(PaneViewMediaLibrary);
}

void MainFrame::OnUpdateViewAlbum(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(GetViewId() != PaneViewMediaLibrary);
   pCmdUI->SetCheck(GetViewId() == PaneViewMediaLibrary);
}

void MainFrame::ShowView(EPaneView eview)
{
   PaneView * pview = GetPaneView();
   if(pview != NULL)
   {
      pview->ShowView(eview);
      
   }
}

EPaneView MainFrame::GetViewId()
{
   PaneView * pview = GetPaneView();
   if(pview != NULL)
   {
      return pview->GetViewId();
   }
   return PaneViewNone;
}

PaneView * MainFrame::GetPaneView()
{
   CWnd * pwnd = GetDlgItem(AFX_IDW_PANE_FIRST);
   if(pwnd->IsKindOf(RUNTIME_CLASS(PaneView)))
   {
      return dynamic_cast < PaneView * > (pwnd);
   }
   return NULL;
}



void MainFrame::OnTimer(UINT nIDEvent) 
{
   static float theta;
   if(nIDEvent == 3)
   {
      //AnimateStatusBar();
   }
   else if(nIDEvent == 8913)
   {
      if(!mediamanager::GetMediaManager()->GetAlbumBuild().IsBuilding())
      {
         AStrArray wstra;
         VmsDataGet(VMSDATAKEY(SongDirectorySet), 0, 0, wstra);

         mediamanager::GetMediaManager()->BuildAlbum(wstra);
      }
      KillTimer(8913);
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
	SimpleFrameWnd::OnTimer(nIDEvent);
}

void MainFrame::SetAnimatedStatusBarText(LPCTSTR lpcsz)
{
   m_strAnimatedStatusBarText = lpcsz;
   if(m_strAnimatedStatusBarText.IsEmpty())
   {
      KillTimer(3);
   }
   else
   {
      SetTimer(3, 500, NULL);
   }
}

void MainFrame::AnimateStatusBar()
{
   if(m_strAnimatedStatusBarText.IsEmpty())
      return;

   int iLen = m_strAnimatedStatusBarText.GetLength();
   m_iAnimateStep++;
   if(m_iAnimateStep > iLen)
      m_iAnimateStep = 0;


//   m_statusbar.SetPaneText(0, m_strAnimatedStatusBarText.Mid(m_iAnimateStep));
}

void MainFrame::OnViewMediaExplorer() 
{
   ShowView(PaneViewMediaLibrary);	
   MediaLibraryViewUpdateHint uh;
   uh.SetType(MediaLibraryViewUpdateHint::TypeSetView);
   uh.m_eview = MediaLibraryViewMediaExplorer;
   GetPaneView()->GetDocument()->UpdateAllViews(NULL, 0, &uh);
}

void MainFrame::OnViewAllMedia() 
{
	ShowView(PaneViewMediaLibrary);
   MediaLibraryViewUpdateHint uh;
   uh.SetType(MediaLibraryViewUpdateHint::TypeSetView);
   uh.m_eview = MediaLibraryViewAllMedia;
   GetPaneView()->GetDocument()->UpdateAllViews(NULL, 0, &uh);

}

void MainFrame::ShowControlBars(bool bShow)
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

void MainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	SimpleFrameWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

void MainFrame::OnNcPaint() 
{
	// TODO: Add your message handler code here
	
	// Do not call SimpleFrameWnd::OnNcPaint() for painting messages
}

void MainFrame::OnTogglecustomframe() 
{
	SetCustomFrame(!GetCustomFrame());
	
}

void MainFrame::OnUpdateTogglecustomframe(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();
   pCmdUI->SetCheck(m_bCustomFrame ? 1 : 0);
}

LRESULT MainFrame::OnVmSimple(WPARAM wparam, LPARAM lparam)
{
   if(wparam == 123)
   {
      return VM_SIMPLE;
   }
   return 0;
}

BOOL MainFrame::OnCopyData(CWnd * pwnd, COPYDATASTRUCT* pcds)
{
   if(pcds->dwData == 123)
   {
      WString wstr((LPWSTR) pcds->lpData);
      MusicalPlayerLightApp * papp = (MusicalPlayerLightApp *) AfxGetApp();
      papp->ProcessCommandLine(wstr);
      return TRUE;
   }

   return FALSE;
}

void MainFrame::OnViewOptions() 
{
	ShowView(PaneViewOptions);
	
}

void MainFrame::OnUpdateViewOptions(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(GetViewId() != PaneViewOptions);
   pCmdUI->SetCheck(GetViewId() == PaneViewOptions);
}

void MainFrame::OnViewNextPane() 
{
	GetPaneView()->Rotate();
	
}

BOOL MainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return SimpleFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void MainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	SimpleFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	// TODO: Add your message handler code here
	
}

void MainFrame::OnInitMenu(CMenu* pMenu) 
{
	SimpleFrameWnd::OnInitMenu(pMenu);
	
	// TODO: Add your message handler code here
	
}

void MainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	SimpleFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
}
