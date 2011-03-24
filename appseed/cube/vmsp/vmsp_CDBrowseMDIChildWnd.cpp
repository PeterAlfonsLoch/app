#include "StdAfx.h"
#include "CDBrowseMDIChildWnd.h"


CDBrowseMDIChildWnd::CDBrowseMDIChildWnd(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   mdi_child_window(papp)
{
}

CDBrowseMDIChildWnd::~CDBrowseMDIChildWnd()
{
}


 // BEGIN_MESSAGE_MAP(CDBrowseMDIChildWnd, mdi_child_window)
   //{{AFX_MSG_MAP(CDBrowseMDIChildWnd)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBrowseMDIChildWnd message handlers
