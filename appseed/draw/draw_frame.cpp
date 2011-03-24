// MainFrm.cpp : implementation of the html_frame class
//

#include "stdafx.h"
#include "resource.h"

#include "html_frame.h"
#include "html_view.h"

HHOOK g_mousehook;
html_frame  * g_pframe;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// html_frame

IMPLEMENT_DYNCREATE(html_frame, SimpleFrameWnd)

BEGIN_MESSAGE_MAP(html_frame, SimpleFrameWnd)
	//{{AFX_MSG_MAP(html_frame)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_MOVE()
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_NCPAINT()
	ON_COMMAND(ID_TOGGLECUSTOMFRAME, OnTogglecustomframe)
	ON_UPDATE_COMMAND_UI(ID_TOGGLECUSTOMFRAME, OnUpdateTogglecustomframe)
	ON_WM_INITMENUPOPUP()
	ON_WM_INITMENU()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, SimpleFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, SimpleFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, SimpleFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, SimpleFrameWnd::OnHelpFinder)
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
// html_frame construction/destruction

html_frame::html_frame()
{
   m_iFrameData = 10;
   DISetSection("MusicalPlayerscreencaptureFrame");
   m_iAnimateStep = 0;

   WfiEnableFullScreen();

   m_datakeyWindow = VMSDATAKEY(WindowData);
}

html_frame::~html_frame()
{
}

int html_frame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (SimpleFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

   m_bTimerOn = false;

   SetTimer(8913, 5000, 0);
   SetTimer(4033, 100, 0);
   ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

   MouseHook();

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

BOOL html_frame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !SimpleFrameWnd::PreCreateWindow(cs) )
		return FALSE;
   cs.dwExStyle &= ~WS_EX_WINDOWEDGE;
   ::DestroyMenu(cs.hMenu);
   cs.hMenu = NULL;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// html_frame diagnostics

#ifdef _DEBUG
void html_frame::AssertValid() const
{
	SimpleFrameWnd::AssertValid();
}

void html_frame::Dump(CDumpContext& dc) const
{
	SimpleFrameWnd::Dump(dc);
}


#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// html_frame message handlers


void html_frame::WfiOnFullScreen(bool bFullScreen)
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

void html_frame::OnViewFullScreen() 
{
	ToggleFullScreen();
}

void html_frame::OnUpdateViewFullScreen(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();	
   pCmdUI->SetCheck(WfiIsFullScreen() ? 1 : 0);	
}

void html_frame::ToggleFullScreen()
{
   WfiFullScreen(!WfiIsFullScreen(), true);
}

void html_frame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
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

bool html_frame::IsFullScreen()
{
   return WfiIsFullScreen();
}


void html_frame::OnMove(int x, int y) 
{
	SimpleFrameWnd::OnMove(x, y);
}

void html_frame::OnClose() 
{
	SimpleFrameWnd::OnClose();
}

void html_frame::OnSysCommand(UINT nID, LPARAM lParam) 
{

   if(nID == SC_SCREENSAVE)
   {
   }
	
	SimpleFrameWnd::OnSysCommand(nID, lParam);
}





void html_frame::OnTimer(UINT nIDEvent) 
{
   static float theta;
   if(nIDEvent == 3)
   {
      //AnimateStatusBar();
   }
   else if(nIDEvent == 1000)
   {
      ShowWindow(SW_RESTORE);
      KillTimer(nIDEvent);
      m_bTimerOn = false;
   }
   else if(nIDEvent == 8913)
   {
   }
   else if(nIDEvent == 4033)
   {
      point pt;
      if(m_bHoverMouse && GetTickCount() > m_dwLastHover + 300)
      {
         OnHoverAction();
      }
      if(::GetCursorPos(&pt))
      {
         if(!m_bHoverMouse && pt.x == 0 && pt.y == 0)
         {
            m_dwLastHover = ::GetTickCount();
            m_bHoverMouse = true;
            
         }
         else if(m_bHoverMouse && (pt.x > 10 || pt.y > 0))
         {
            m_bHoverMouse = false;
         }

      }
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

void html_frame::SetAnimatedStatusBarText(LPCTSTR lpcsz)
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

void html_frame::AnimateStatusBar()
{
   if(m_strAnimatedStatusBarText.is_empty())
      return;

   int iLen = m_strAnimatedStatusBarText.GetLength();
   m_iAnimateStep++;
   if(m_iAnimateStep > iLen)
      m_iAnimateStep = 0;


//   m_statusbar.SetPaneText(0, m_strAnimatedStatusBarText.Mid(m_iAnimateStep));
}


void html_frame::ShowControlBars(bool bShow)
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

void html_frame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	SimpleFrameWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

void html_frame::OnNcPaint() 
{
	// TODO: Add your message handler code here
	
	// Do not call SimpleFrameWnd::OnNcPaint() for painting messages
}

void html_frame::OnTogglecustomframe() 
{
	SetCustomFrame(!GetCustomFrame());
	
}

void html_frame::OnUpdateTogglecustomframe(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();
   pCmdUI->SetCheck(m_bCustomFrame ? 1 : 0);
}


BOOL html_frame::OnCopyData(base_wnd * pwnd, COPYDATASTRUCT* pcds)
{

   return FALSE;
}


BOOL html_frame::OnCmdMsg(UINT nID, int nCode, void* pExtra, CAFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return SimpleFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void html_frame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	SimpleFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	// TODO: Add your message handler code here
	
}

void html_frame::OnInitMenu(CMenu* pMenu) 
{
	SimpleFrameWnd::OnInitMenu(pMenu);
	
	// TODO: Add your message handler code here
	
}

void html_frame::OnActivate(UINT nState, base_wnd* pWndOther, BOOL bMinimized) 
{
	SimpleFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
}



bool html_frame::MouseHook()
{
   g_pframe = this;
   if((g_mousehook =
      SetWindowsHookEx(
      WH_MOUSE_LL,
      MouseProc,
      AfxGetInstanceHandle(),
      NULL)) == NULL)
   {
      return false;
   }
   
   return true;
}

void html_frame::MouseMessage(          int nCode,
    WPARAM wparam,
    LPARAM lparam
)
{
   if(wparam == WM_MOUSEMOVE)
   {
/*      MSLLHOOKSTRUCT * pstruct = (MSLLHOOKSTRUCT *) lparam;
      if(!m_bTimerOn && pstruct->pt.x == 0 && pstruct->pt.y == 0)
      {
      }
      else if(m_bTimerOn && (pstruct->pt.x > 10 || pstruct->pt.y > 10))
      {
      }*/
   }
}

LRESULT CALLBACK html_frame::MouseProc(          int nCode,
    WPARAM wparam,
    LPARAM lparam
)
{

   if(nCode < 0)
   {
      return CallNextHookEx(g_mousehook, nCode, wparam, lparam);
   }
   else
   {
      g_pframe->MouseMessage(nCode, wparam, lparam);
      CallNextHookEx(g_mousehook, nCode, wparam, lparam);
      return 0;
   }
}



bool html_frame::MouseUnhook()
{
   return UnhookWindowsHookEx(g_mousehook);
}



void html_frame::OnHoverAction()
{
   ShowWindow(SW_RESTORE);
}
