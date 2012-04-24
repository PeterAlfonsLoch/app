#include "StdAfx.h"

#include "html_frame.h"
#include "html_view.h"

HHOOK g_mousehook;
html_frame  * g_pframe;


// IMPLEMENT_DYNCREATE(html_frame, simple_frame_window)

 // BEGIN_MESSAGE_MAP(html_frame, simple_frame_window)
   //{{AFX_MSG_MAP(html_frame)
/*
   ON_WM_CREATE()
   ON_WM_GETMINMAXINFO()
   ON_WM_MOVE()
   ON_WM_CLOSE()
   ON_WM_TIMER()
   ON_WM_SHOWWINDOW()
   ON_WM_NCPAINT()
   ON_WM_INITMENUPOPUP()
   ON_WM_INITMENU()
   ON_WM_ACTIVATE()
   //}}AFX_MSG_MAP
   // Global help commands
   ON_COMMAND(ID_HELP_FINDER, simple_frame_window::OnHelpFinder)
   ON_COMMAND(ID_HELP, simple_frame_window::OnHelp)
   ON_COMMAND(ID_CONTEXT_HELP, simple_frame_window::OnContextHelp)
   ON_COMMAND(ID_DEFAULT_HELP, simple_frame_window::OnHelpFinder)
   ON_WM_COPYDATA()
   */
 // END_MESSAGE_MAP()

/*static UINT indicators[] =
{
   ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};*/

html_frame::html_frame(::ca::application * papp) :
   ca(papp),
   simple_frame_window(papp)
{
   m_pimagelist = NULL;
   m_iFrameData = 10;
   //DISetSection("MusicalPlayerscreencaptureFrame");
   m_iAnimateStep = 0;

   WfiEnableFullScreen();

   //m_dataidWindow = VMSDATAKEY(WindowData);
}

html_frame::~html_frame()
{
}

int html_frame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   UNREFERENCED_PARAMETER(lpCreateStruct);
/* trans    if (simple_frame_window::OnCreate(lpCreateStruct) == -1)
      return -1; */

   m_bTimerOn = false;

   SetTimer(8913, 5000, 0);
   SetTimer(4033, 100, 0);
   ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

   MouseHook();

   //m_menuhook.Initialize(
     // BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      //BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      //NULL,
      //System.font_central().GetMenuFont());

   //m_menuhook.Install(this);



   //m_hMenuDefault = NULL;

/*    if (!m_menubar.CreateEx(this))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }

   if(!m_menubar.Initialize(
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      NULL,
      System.font_central().GetMenuFont()) ||
      VMS_FAILED(m_menubar.LoadMenuBar(IDR_MAINFRAME)))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }*/

   m_pimagelist = new image_list(get_app());
   m_pimagelist->create(16, 16, 0, 10, 10);
/*   m_pimagelist->add(
      (HICON)
      ::LoadImage(
         System.m_hInstance,
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
   
   
   if (!m_dialogbar.create(this, IDR_MAINFRAME, 
      WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC
      | CBRS_DRAGMOVE, AFX_IDW_DIALOGBAR))
   {
      TRACE0("Failed to create dialogbar\n");
      return -1;      // fail to create
   }*/

/*   if (!m_wndReBar.create(this) ||
      !m_wndReBar.AddBar(&m_menubar) ||
      !m_wndReBar.AddBar(&m_wndToolBar) ||
      !m_wndReBar.AddBar(&m_toolbarView) ||
      !m_wndReBar.AddBar(&m_wndDlgBar))
   {
      TRACE0("Failed to create rebar\n");
      return -1;      // fail to create
   }*/

/*   if (!m_statusbar.create(this) ||
      !m_statusbar.SetIndicators(indicators,
        sizeof(indicators)/sizeof(UINT)))
   {
      TRACE0("Failed to create status bar\n");
      return -1;      // fail to create
   }*/

   // TODO: remove this if you don't want tool tips
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

BOOL html_frame::pre_create_window(CREATESTRUCT& cs)
{
   if( !simple_frame_window::pre_create_window(cs) )
      return FALSE;
   cs.dwExStyle &= ~WS_EX_WINDOWEDGE;
   ::DestroyMenu(cs.hMenu);
   cs.hMenu = NULL;
   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// html_frame diagnostics

#ifdef _DEBUG
void html_frame::assert_valid() const
{
   simple_frame_window::assert_valid();
}

void html_frame::dump(dump_context & dumpcontext) const
{
   simple_frame_window::dump(dumpcontext);
}


#endif //_DEBUG





void html_frame::SetAnimatedStatusBarText(const char * lpcsz)
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

   strsize iLen = m_strAnimatedStatusBarText.get_length();
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

bool html_frame::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
{
   // TODO: add your specialized code here and/or call the base class
   
   return simple_frame_window::_001OnCmdMsg(pcmdmsg);
}





bool html_frame::MouseHook()
{
   g_pframe = this;
   if((g_mousehook =
      SetWindowsHookEx(
      WH_MOUSE_LL,
      MouseProc,
      System.m_hInstance,
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
   UNREFERENCED_PARAMETER(nCode);
   UNREFERENCED_PARAMETER(lparam);
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
   return UnhookWindowsHookEx(g_mousehook) != FALSE;
}



void html_frame::OnHoverAction()
{
   ShowWindow(SW_RESTORE);
}



