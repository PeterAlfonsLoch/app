#include "StdAfx.h"


namespace alatel
{

   frame::frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp),
      m_imagelist(papp)
   {


      m_dataid = "ca2.alatel.frame";
      m_dataidWindow = "WindowData";

      m_iFrameData = 10;
      m_iAnimateStep = 0;
      //m_bCustomFrame = false;

      WfiEnableFullScreen();


   }

   frame::~frame()
   {
   }


   void frame::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::_001InstallMessageHandling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &::alatel::frame::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &::alatel::frame::_001OnTimer);
   }

   void frame::_001OnCreate(gen::signal_object * pobj)
   {
	   pobj->previous();

      if(pobj->m_bRet)
         return;

      m_bTimerOn = false;



   }

   BOOL frame::PreCreateWindow(CREATESTRUCT& cs)
   {
	   if( !simple_frame_window::PreCreateWindow(cs) )
		   return FALSE;
      cs.dwExStyle &= ~WS_EX_WINDOWEDGE;
      ::DestroyMenu(cs.hMenu);
      cs.hMenu = NULL;
      cs.dwExStyle |= WS_EX_TRANSPARENT;
	   return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // frame diagnostics

   #ifdef _DEBUG
   void frame::assert_valid() const
   {
	   simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context& dc) const
   {
	   simple_frame_window::dump(dc);
   }


   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // frame message handlers


   void frame::WfiOnFullScreen(bool bFullScreen)
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
            ZORDER_TOP,
            rectDesktop.left, rectDesktop.top,
            rectDesktop.width(), rectDesktop.height(),
            SWP_FRAMECHANGED |
            SWP_SHOWWINDOW);
         layout();
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
         layout();
      }
      if(GetActiveView() != NULL)
      {
      }
   
      data_set("FullScreen", bFullScreen);

   }


   void frame::ToggleFullScreen()
   {
      WfiFullScreen(!WfiIsFullScreen(), true);
   }

   bool frame::IsFullScreen()
   {
      return WfiIsFullScreen();
   }

   void frame::_001OnSysCommand(gen::signal_object * pobject) 
   {

      /*if(nID == SC_SCREENSAVE)
      {
      }
	
	   simple_frame_window::OnSysCommand(nID, lParam);*/
   }

   void frame::_001OnTimer(gen::signal_object * pobj) 
   {
      SCAST_PTR(user::win::message::timer, ptimer, pobj)
      static float theta;
      if(ptimer->m_nIDEvent == 3)
      {
         //AnimateStatusBar();
      }
      else if(ptimer->m_nIDEvent == 1000)
      {
         ShowWindow(SW_RESTORE);
         KillTimer(ptimer->m_nIDEvent);
         m_bTimerOn = false;
      }
      else if(ptimer->m_nIDEvent == 8913)
      {
      }
      else if(ptimer->m_nIDEvent == 4033)
      {
         if(IsWindowVisible())
         {
            WfiFullScreen(true, false);
            SetWindowPos(ZORDER_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
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
   }

   void frame::SetAnimatedStatusBarText(LPCTSTR lpcsz)
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

   void frame::AnimateStatusBar()
   {
      if(m_strAnimatedStatusBarText.is_empty())
         return;

      int iLen = m_strAnimatedStatusBarText.get_length();
      m_iAnimateStep++;
      if(m_iAnimateStep > iLen)
         m_iAnimateStep = 0;


   //   m_statusbar.SetPaneText(0, m_strAnimatedStatusBarText.Mid(m_iAnimateStep));
   }


   void frame::ShowControlBars(bool bShow)
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

   void frame::alatel_fullscreen(bool bAlatel)
   {
      if(bAlatel)
      {
         m_etranslucency = TranslucencyPresent;
         SetTimer(4033, 984, 0);
      }
      else
      {
         m_etranslucency = TranslucencyNone;
         KillTimer(4033);
      }
   }

   void frame::OnHoverAction()
   {
      ShowWindow(SW_RESTORE);
   }

} // namespace alarm