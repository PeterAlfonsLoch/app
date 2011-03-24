#include "StdAfx.h"
#include "main_frame.h"
#include "view.h"



// // BEGIN_MESSAGE_MAP(main_frame, simple_frame_window)
   //{{AFX_MSG_MAP(main_frame)
/* xxx   ON_WM_CREATE()
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
   ON_WM_COPYDATA() */
// // END_MESSAGE_MAP()

static UINT indicators[] =
{
   ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

namespace devedge 
{

   main_frame::main_frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp)
   {
      m_iFrameData = 10;
      m_dataid = "devedge::main_frame";
      m_iAnimateStep = 0;
      System.SetMainWnd(this);

      WfiEnableFullScreen();

      m_dataidWindow = "WindowData";
   }

   main_frame::~main_frame()
   {
   }

   int main_frame::OnCreate(LPCREATESTRUCT lpCreateStruct)
   {
      UNREFERENCED_PARAMETER(lpCreateStruct);
      //if (simple_frame_window::OnCreate(lpCreateStruct) == -1)
      //   return -1;

      SetTimer(8913, 5000, 0);
      SetTimer(4033, 100, 0);
      ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

      

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

   /*   m_imagelist.create(16, 16, 0, 10, 10);
      m_imagelist.add(
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

   void main_frame::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CLOSE,          pinterface, this, &main_frame::_001OnClose);
   }


   BOOL main_frame::PreCreateWindow(CREATESTRUCT& cs)
   {
      if( !simple_frame_window::PreCreateWindow(cs) )
         return FALSE;
      cs.dwExStyle &= ~WS_EX_WINDOWEDGE;
      ::DestroyMenu(cs.hMenu);
      cs.hMenu = NULL;

      bergedge::bergedge * pbergedge = System.get_bergedge(0);
      if(pbergedge != NULL)
      {
//            ::view * pview = pdoc->get_view();
      }
      return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // main_frame diagnostics

   #ifdef _DEBUG
   void main_frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void main_frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }


   #endif //_DEBUG

   
   void main_frame::OnTimer(UINT nIDEvent) 
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
      //simple_frame_window::OnTimer(nIDEvent);
   }

   void main_frame::SetAnimatedStatusBarText(const char * lpcsz)
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

   void main_frame::AnimateStatusBar()
   {
      if(m_strAnimatedStatusBarText.is_empty())
         return;

      int iLen = m_strAnimatedStatusBarText.get_length();
      m_iAnimateStep++;
      if(m_iAnimateStep > iLen)
         m_iAnimateStep = 0;


   //   m_statusbar.SetPaneText(0, m_strAnimatedStatusBarText.Mid(m_iAnimateStep));
   }


   void main_frame::ShowControlBars(bool bShow)
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

   
   bool main_frame::is_application_main_window()
   {
      return true;
   }

} // namespace devedge