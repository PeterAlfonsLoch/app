#include "framework.h"

// IMPLEMENT_DYNCREATE(html_frame, simple_frame_window)

 // BEGIN_MESSAGE_MAP(html_frame, simple_frame_window)
   //{{__MSG_MAP(html_frame)
/*
   
   ON_WM_GETMINMAXINFO()
   ON_WM_MOVE()
   ON_WM_CLOSE()
   ON_WM_TIMER()
   ON_WM_SHOWWINDOW()
   ON_WM_NCPAINT()
   ON_WM_INITMENUPOPUP()
   ON_WM_INITMENU()
   ON_WM_ACTIVATE()
   //}}__MSG_MAP
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

html_frame::html_frame(sp(::base::application) papp) :
   element(papp),
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

void html_frame::_001OnCreate(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);

   m_bTimerOn = false;

   SetTimer(8913, 5000, 0);
   SetTimer(4033, 100, 0);
   ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);


   m_pimagelist = new image_list(get_app());
   m_pimagelist->create(16, 16, 0, 10, 10);
}


bool html_frame::pre_create_window(CREATESTRUCT& cs)
{

   if( !simple_frame_window::pre_create_window(cs) )
      return FALSE;

   cs.dwExStyle &= ~WS_EX_WINDOWEDGE;

   return TRUE;

}

/////////////////////////////////////////////////////////////////////////////
// html_frame diagnostics

#ifdef DEBUG
void html_frame::assert_valid() const
{
   simple_frame_window::assert_valid();
}

void html_frame::dump(dump_context & dumpcontext) const
{
   simple_frame_window::dump(dumpcontext);
}


#endif //DEBUG





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

bool html_frame::_001OnCmdMsg(::base::cmd_msg * pcmdmsg)
{
   // TODO: add your specialized code here and/or call the base class

   return simple_frame_window::_001OnCmdMsg(pcmdmsg);
}






void html_frame::OnHoverAction()
{

   WfiRestore();

}



