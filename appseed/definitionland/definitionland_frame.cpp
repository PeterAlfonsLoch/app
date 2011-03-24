// MainFrm.cpp : implementation of the definitionland_frame class
//

#include "stdafx.h"
#include "resource.h"

#include "definitionland_frame.h"
#include "definitionland_view.h"
#include <math.h>

definitionland_frame  * g_pframe;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// definitionland_frame

IMPLEMENT_DYNCREATE(definitionland_frame, SimpleFrameWnd)

BEGIN_MESSAGE_MAP(definitionland_frame, SimpleFrameWnd)
	//{{AFX_MSG_MAP(definitionland_frame)
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
// definitionland_frame construction/destruction

definitionland_frame::definitionland_frame()
{
   m_iFrameData = 10;
   DISetSection("MusicalPlayerscreencaptureFrame");
   m_iAnimateStep = 0;
   m_bTimerHide = false;

   WfiEnableFullScreen();

   m_datakeyWindow = VMSDATAKEY(WindowData);
   m_bMoveDrag = true;
   m_bLastLWin = false;

//   connect_command("app_exit", &definitionland_frame::_001OnAppExit);
//   connect_update_cmd_ui("app_exit", &definitionland_frame::_001OnUpdateAppExit);
}

definitionland_frame::~definitionland_frame()
{
}

int definitionland_frame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if(!DILoad("DockPosition", (int &) m_eposition))
   {
      m_eposition = PositionLeft;
   }
	if (SimpleFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;



/*BLENDFUNCTION blend;

    blend.BlendOp = AC_SRC_OVER;
    blend.BlendFlags = 0;
    blend.AlphaFormat = 0;
    blend.SourceConstantAlpha = 128;

    point ptSrc = point(0, 0);

    CDC dc;
    dc.CreateCompatibleDC(NULL);
 
    UpdateLayeredWindow( NULL, NULL, NULL, &dc, &ptSrc, 0,
            &blend, ULW_ALPHA);*/

   SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);

   
   m_bTimerOn = false;

   SetTimer(8913, 5000, 0);
   SetTimer(4033, 100, 0);
   ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

   SetTimer(4034, 500, 0);

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
   m_menubar.SetItemImage(m_menubar._001GetItemCount() - 1, 0);*/

   string str = ca2::app(get_app()).file().as_string(
      ca2::app().dir().matter("definitionland\\toolbar.xml"));

	if (!m_toolbar.CreateEx(this) ||
		 !m_toolbar.LoadXmlToolBar(str))
	{
		TRACE0("Failed to create toolbar\n");
		return false;      // fail to create
	}

	/*if (!m_toolbarView.CreateEx(this, TBSTYLE_FLAT,
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

BOOL definitionland_frame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !SimpleFrameWnd::PreCreateWindow(cs) )
		return FALSE;
   cs.dwExStyle &= ~WS_EX_WINDOWEDGE;
   cs.dwExStyle |= WS_EX_LAYERED;

   ::DestroyMenu(cs.hMenu);
   cs.hMenu = NULL;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// definitionland_frame diagnostics

#ifdef _DEBUG
void definitionland_frame::AssertValid() const
{
	SimpleFrameWnd::AssertValid();
}

void definitionland_frame::Dump(CDumpContext& dc) const
{
	SimpleFrameWnd::Dump(dc);
}


#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// definitionland_frame message handlers


void definitionland_frame::WfiOnFullScreen(bool bFullScreen)
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

void definitionland_frame::OnViewFullScreen() 
{
	ToggleFullScreen();
}

void definitionland_frame::OnUpdateViewFullScreen(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();	
   pCmdUI->SetCheck(WfiIsFullScreen() ? 1 : 0);	
}

void definitionland_frame::ToggleFullScreen()
{
   WfiFullScreen(!WfiIsFullScreen(), true);
}

void definitionland_frame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
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

bool definitionland_frame::IsFullScreen()
{
   return WfiIsFullScreen();
}


void definitionland_frame::OnMove(int x, int y) 
{
	SimpleFrameWnd::OnMove(x, y);
}

void definitionland_frame::OnClose() 
{
	SimpleFrameWnd::OnClose();
}

void definitionland_frame::OnSysCommand(UINT nID, LPARAM lParam) 
{

   if(nID == SC_SCREENSAVE)
   {
   }
	
	SimpleFrameWnd::OnSysCommand(nID, lParam);
}





void definitionland_frame::_001OnTimer(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::timer, ptimer, pobj);
   UINT nIDEvent = ptimer->m_nIDEvent;
   static float theta;
   if(nIDEvent == 4034)
   {
      if(IsWindowVisible())
      {
/*         BLENDFUNCTION blend;

         blend.BlendOp = AC_SRC_OVER;
         blend.BlendFlags = 0;
         blend.AlphaFormat = 0;
         blend.SourceConstantAlpha = 255;

         point ptSrc = point(0, 0);

         CDC dc;
         dc.CreateCompatibleDC(NULL);

         UpdateLayeredWindow( NULL, NULL, NULL, NULL, NULL, 0,
            &blend, ULW_OPAQUE);*/

         SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);
         base_wnd::RedrawWindow(NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
      }
   }
   else if(nIDEvent == 3)
   {
      //AnimateStatusBar();
   }
   else if(nIDEvent == 1000)
   {
      KillTimer(nIDEvent);
      m_bTimerOn = false;
      bool bLControlKeyDown = GetAsyncKeyState (VK_LCONTROL) >> ((sizeof(SHORT) * 8) - 1);
      bool bLAltKeyDown = GetAsyncKeyState (VK_LMENU) >> ((sizeof(SHORT) * 8) - 1);
      if(bLControlKeyDown && bLAltKeyDown)
      {
      }
      else
      {
      }
   }
   else if(nIDEvent == 1001)
   {
      KillTimer(nIDEvent);
   }
   else if(nIDEvent == 8913)
   {
   }
   // every 100 ms approximately
   else if(nIDEvent == 4033)
   {
/*      rect rectWindow;
      GetWindowRect(rectWindow);
      point pt;
      ::GetCursorPos(&pt);
      if(!rectWindow.PtInRect(pt) && !m_bTimerHide)
      {
         m_bTimerHide = true;
         SetTimer(1001, 800, NULL);
      }
      else
      {
         m_bTimerHide = false;
         KillTimer(1001);
      }*/
      /*point pt;
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

      }*/
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

void definitionland_frame::SetAnimatedStatusBarText(LPCTSTR lpcsz)
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

void definitionland_frame::AnimateStatusBar()
{
   if(m_strAnimatedStatusBarText.is_empty())
      return;

   int iLen = m_strAnimatedStatusBarText.GetLength();
   m_iAnimateStep++;
   if(m_iAnimateStep > iLen)
      m_iAnimateStep = 0;


//   m_statusbar.SetPaneText(0, m_strAnimatedStatusBarText.Mid(m_iAnimateStep));
}



void definitionland_frame::ShowControlBars(bool bShow)
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

void definitionland_frame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	SimpleFrameWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

void definitionland_frame::OnNcPaint() 
{
	// TODO: Add your message handler code here
	
	// Do not call SimpleFrameWnd::OnNcPaint() for definitionlanding messages
}

void definitionland_frame::OnTogglecustomframe() 
{
	SetCustomFrame(!GetCustomFrame());
	
}

void definitionland_frame::OnUpdateTogglecustomframe(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();
   pCmdUI->SetCheck(m_bCustomFrame ? 1 : 0);
}


BOOL definitionland_frame::OnCopyData(base_wnd * pwnd, COPYDATASTRUCT* pcds)
{

   return FALSE;
}


BOOL definitionland_frame::OnCmdMsg(UINT nID, int nCode, void* pExtra, CAFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return SimpleFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void definitionland_frame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	SimpleFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	// TODO: Add your message handler code here
	
}

void definitionland_frame::OnInitMenu(CMenu* pMenu) 
{
	SimpleFrameWnd::OnInitMenu(pMenu);
	
	// TODO: Add your message handler code here
	
}

void definitionland_frame::OnActivate(UINT nState, base_wnd* pWndOther, BOOL bMinimized) 
{
	SimpleFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
}






void definitionland_frame::_001OnClose(gen::signal_object * pobj)
{
   pobj->m_bRet = true;
}


void definitionland_frame::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   SimpleFrameWnd::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CLOSE       , this, this, &definitionland_frame::_001OnClose);
   IGUI_WIN_MSG_LINK(WM_TIMER       , this, this, &definitionland_frame::_001OnTimer);
   IGUI_WIN_MSG_LINK(WM_MOVE        , this, this, &definitionland_frame::_001OnMove);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW  , this, this, &definitionland_frame::_001OnShowWindow);
   IGUI_WIN_MSG_LINK(WM_DESTROY     , this, this, &definitionland_frame::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_APP + 2000  , this, this, &definitionland_frame::_001OnApp2000);
}

void definitionland_frame::_001OnMove(gen::signal_object * pobj)
{
   if(m_wndframework.GetMovingManager()->IsMoving())
   {
      HWND hwndDesktop = ::GetDesktopWindow();
      rect rectDesktop;
      ::GetWindowRect(hwndDesktop, rectDesktop);
      rect rectWindow;
      GetWindowRect(rectWindow);
      double a = (double) rectDesktop.Height() / (double) rectDesktop.Width();
      if(rectWindow.left < (rectDesktop.Width() / 2))
      {
         // to the left
         if(rectWindow.top < rectWindow.left * a)
         {
            // top
            m_eposition = PositionTop;
         }
         else if(rectWindow.top > (rectDesktop.Height() - rectWindow.left * a))
         {
            // bottom
            m_eposition = PositionBottom;
         }
         else
         {
            // left
            m_eposition = PositionLeft;
         }
      }
      else
      {
         // to the right
         // to the left
         if(rectWindow.top > rectWindow.left * a)
         {
            // bottom
            m_eposition = PositionBottom;
         }
         else if(rectWindow.top < (rectDesktop.Height() - rectWindow.left * a))
         {
            // top
            m_eposition = PositionTop;
         }
         else
         {
            // right
            m_eposition = PositionRight;
         }
      }
      DISave("DockPosition", m_eposition);
   }
}

void definitionland_frame::_001OnShowWindow(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::show_window, pshowwindow, pobj)
   
   if(!pshowwindow->m_bShow)
   {
      if(GetActiveDocument() != NULL)
         GetActiveDocument()->UpdateAllViews(NULL, 5432108);
   }
}



bool definitionland_frame::_001OnCommand(UINT nID)
{
   CommandIdSpace idspace;
   if(ca2::app(get_app()).GetResourceId(idspace, "app_exit"))
   {
      SimpleFrameWnd::OnClose();
      return true;
   }
   return false;
}

bool definitionland_frame::_001HasCommandHandler(UINT nID)
{
   CommandIdSpace idspace;
   if(ca2::app(get_app()).GetResourceId(idspace, "app_exit"))
   {
      return true;
   }
   return false;
}

void definitionland_frame::_001OnDestroy(gen::signal_object * pobj)
{
   show_task_bar(SW_SHOW);
}


void definitionland_frame::_001OnApp2000(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::base, pbase, pobj)


   if(pbase->m_wparam == 0)
   {
      if(pbase->m_lparam == 2)
      {
      }
      else if(pbase->m_lparam == 1)
      {
         m_bTimerOn = true;
         SetTimer(1000, 23, NULL);
      }
      else if(pbase->m_lparam == 0)
      {
         KillTimer(1000);
         m_bTimerOn = false;
      }
      else if(pbase->m_lparam == 3)
      {
      }
      
   }
   else if(pbase->m_wparam == 1)
   {
      pbase->set_lresult(2);
   }
   else if(pbase->m_wparam == 2)
   {
      pbase->set_lresult(4);
   }
   else if(pbase->m_wparam == 4)
   {
      pbase->set_lresult(5);
   }
   else if(pbase->m_wparam == 5)
   {
      pbase->set_lresult(8);
   }
   else if(pbase->m_wparam == 8)
   {
      pbase->set_lresult(11);
   }
   else if(pbase->m_wparam == 11)
   {
      pbase->set_lresult(23);
   }
   else if(pbase->m_wparam == 23)
   {
      pbase->set_lresult(33);
   }
   else if(pbase->m_wparam == 33)
   {
      pbase->set_lresult(68);
   }
   pbase->m_bRet = true;
}


void definitionland_frame::show_task_bar(int nCmdShow)
{
   base_wnd * pwnd = base_wnd::FindWindow("Shell_TrayWnd", "");
   pwnd->ShowWindow(nCmdShow);
}
