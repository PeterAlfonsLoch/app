#include "StdAfx.h"
#include "BrowseCDMDIExChildWnd.h"

CBrowseCDMDIExChildWnd::CBrowseCDMDIExChildWnd(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   mdi_child_window(papp)
{
}

CBrowseCDMDIExChildWnd::~CBrowseCDMDIExChildWnd()
{
}


 // BEGIN_MESSAGE_MAP(CBrowseCDMDIExChildWnd, mdi_child_window)
   //{{AFX_MSG_MAP(CBrowseCDMDIExChildWnd)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowseCDMDIExChildWnd message handlers
