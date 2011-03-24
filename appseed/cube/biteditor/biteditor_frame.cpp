#include "StdAfx.h"

#include "biteditor_frame.h"
#include "biteditor_view.h"

// // BEGIN_MESSAGE_MAP(biteditor_frame, simple_frame_window)
   //{{AFX_MSG_MAP(biteditor_frame)
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

biteditor_frame::biteditor_frame(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_frame_window(papp),
   m_imagelist(papp)
{
   m_iFrameData = 10;
   m_dataid = "ca2_fontopus_votagus::biteditor";
   m_iAnimateStep = 0;
   System.SetMainWnd(this);

   WfiEnableFullScreen();

   m_dataidWindow = "WindowData";
}

biteditor_frame::~biteditor_frame()
{
}

void biteditor_frame::_001OnCreate(gen::signal_object *pobj)
{

   pobj->previous();

   SetTimer(8913, 5000, 0);
   SetTimer(4033, 100, 0);
   ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

}

void biteditor_frame::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   simple_frame_window::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE   , pinterface, this, &biteditor_frame::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_CLOSE    , pinterface, this, &biteditor_frame::_001OnClose);
}


BOOL biteditor_frame::PreCreateWindow(CREATESTRUCT& cs)
{
   if( !simple_frame_window::PreCreateWindow(cs) )
      return FALSE;
   cs.dwExStyle &= ~WS_EX_WINDOWEDGE;
   ::DestroyMenu(cs.hMenu);
   cs.hMenu = NULL;

   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// biteditor_frame diagnostics

#ifdef _DEBUG
void biteditor_frame::assert_valid() const
{
   simple_frame_window::assert_valid();
}

void biteditor_frame::dump(dump_context & dumpcontext) const
{
   simple_frame_window::dump(dumpcontext);
}


#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// biteditor_frame message handlers




void biteditor_frame::OnTimer(UINT nIDEvent) 
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
// trans   simple_frame_window::OnTimer(nIDEvent);
}

void biteditor_frame::SetAnimatedStatusBarText(const char * lpcsz)
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

void biteditor_frame::AnimateStatusBar()
{
   if(m_strAnimatedStatusBarText.is_empty())
      return;

   int iLen = m_strAnimatedStatusBarText.get_length();
   m_iAnimateStep++;
   if(m_iAnimateStep > iLen)
      m_iAnimateStep = 0;


//   m_statusbar.SetPaneText(0, m_strAnimatedStatusBarText.Mid(m_iAnimateStep));
}


void biteditor_frame::ShowControlBars(bool bShow)
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

