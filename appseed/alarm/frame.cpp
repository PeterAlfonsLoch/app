#include "StdAfx.h"


/*BEGIN_MESSAGE_MAP(frame, simple_frame_window)
	//{{AFX_MSG_MAP(frame)
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
	ON_COMMAND(ID_HELP_FINDER, simple_frame_window::OnHelpFinder)
	ON_COMMAND(ID_HELP, simple_frame_window::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, simple_frame_window::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, simple_frame_window::OnHelpFinder)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};*/

namespace alarm
{

   frame::frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp)
   {


      m_dataid = "ca2.alarm.frame";
      m_dataidWindow = "WindowData";


      WfiEnableFullScreen();

   }

   frame::~frame()
   {
   }


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


   
} // namespace alarm