#include "framework.h"


namespace nature
{


   /////////////////////////////////////////////////////////////////////////////
   // frame

   // IMPLEMENT_DYNCREATE(frame, simple_frame_window)

    // BEGIN_MESSAGE_MAP(frame, simple_frame_window)
      //{{__MSG_MAP(frame)
   /* xxx   
      ON_COMMAND(ID_HELP_FINDER, simple_frame_window::OnHelpFinder)
      ON_COMMAND(ID_HELP, simple_frame_window::OnHelp)
      ON_COMMAND(ID_CONTEXT_HELP, simple_frame_window::OnContextHelp)
      ON_COMMAND(ID_DEFAULT_HELP, simple_frame_window::OnHelpFinder)
      ON_WM_COPYDATA() */
    // END_MESSAGE_MAP()

/*   static UINT indicators[] =
   {
      ID_SEPARATOR,           // status line indicator
      ID_INDICATOR_CAPS,
      ID_INDICATOR_NUM,
      ID_INDICATOR_SCRL,
   };
   */
   /////////////////////////////////////////////////////////////////////////////
   // frame construction/destruction

   frame::frame(sp(::base::application) papp) :
      element(papp),
      simple_frame_window(papp)
   {
      m_iFrameData = 10;
      m_dataid = "MusicalPlayerscreencaptureFrame";
      m_iAnimateStep = 0;

      WfiEnableFullScreen();

   //   m_datakeyWindow = VMSDATAKEY(WindowData);

      m_bWindowFrame    = true;
      m_pimagelist      = NULL;

   }

   frame::~frame()
   {
   }

   void frame::_001OnCreate(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      m_bTimerOn = false;

      SetTimer(8913, 5000, 0);
      SetTimer(4033, 100, 0);
      ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

      m_pimagelist = new image_list(get_app());

      m_pimagelist->create(16, 16, 0, 10, 10);
      m_pimagelist->add_matter_icon("system/language_icon.ico");

   }


   bool frame::pre_create_window(CREATESTRUCT& cs)
   {
   
      if( !simple_frame_window::pre_create_window(cs) )
         return FALSE;
      
      cs.dwExStyle &= ~WS_EX_WINDOWEDGE;

      return TRUE;

   }


   #ifdef DEBUG
   void frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }


   #endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // frame message handlers


   void frame::OnTimer(UINT nIDEvent) 
   {
      static float theta;
      if(nIDEvent == 3)
      {
         //AnimateStatusBar();
      }
      else if(nIDEvent == 1000)
      {
         
         WfiRestore(true);

         KillTimer(nIDEvent);

         m_bTimerOn = false;

      }
      else if(nIDEvent == 8913)
      {
      }
      else if(nIDEvent == 4033)
      {
         point pt;
         if(m_bHoverMouse && get_tick_count() > m_dwLastHover + 300)
         {
            OnHoverAction();
         }
         session().get_cursor_pos(&pt);
         if(!m_bHoverMouse && pt.x == 0 && pt.y == 0)
         {
            m_dwLastHover = ::get_tick_count();
            m_bHoverMouse = true;
            
         }
         else if(m_bHoverMouse && (pt.x > 10 || pt.y > 0))
         {
            m_bHoverMouse = false;
         }
   // OpenGL animation code goes here
         
            //glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
            //glClear( GL_COLOR_BUFFER_BIT );
         
            /*glPushMatrix();
            glRotatef( theta, 0.0f, 1.0f, 1.0f );
            glBegin( GL_TRIANGLES );
            glColor3f( 1.0f, 0.0f, 0.0f ); glVertgenf( 0.0f, 1.0f );
            glColor3f( 0.0f, 1.0f, 0.0f ); glVertgenf( 0.87f, -0.5f );
            glColor3f( 0.0f, 0.0f, 1.0f ); glVertgenf( -0.87f, -0.5f );
            glEnd();
            glPopMatrix();*/
         
            //SwapBuffers( m_hdcOpenGL );
         
            theta += 2.0f;
      
      }
   //   simple_frame_window::OnTimer(nIDEvent);
   }

   void frame::SetAnimatedStatusBarText(const char * lpcsz)
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

      strsize iLen = m_strAnimatedStatusBarText.get_length();
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

   void frame::OnHoverAction()
   {

      WfiRestore(true);

   }


} // namespace nature


