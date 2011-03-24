#include "StdAfx.h"
#include "DDEFrameWnd.h"


DDEFrameWnd::DDEFrameWnd(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_frame_window(papp)
{
}

DDEFrameWnd::~DDEFrameWnd()
{
}


 // BEGIN_MESSAGE_MAP(DDEFrameWnd, simple_frame_window)
   //{{AFX_MSG_MAP(DDEFrameWnd)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DDEFrameWnd message handlers
