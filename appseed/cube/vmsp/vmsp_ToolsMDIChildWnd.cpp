#include "StdAfx.h"
#include "ToolsMDIChildWnd.h"


CToolsMDIChildWnd::CToolsMDIChildWnd(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   mdi_child_window(papp)
{
}

CToolsMDIChildWnd::~CToolsMDIChildWnd()
{
}


 // BEGIN_MESSAGE_MAP(CToolsMDIChildWnd, mdi_child_window)
   //{{AFX_MSG_MAP(CToolsMDIChildWnd)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolsMDIChildWnd message handlers
