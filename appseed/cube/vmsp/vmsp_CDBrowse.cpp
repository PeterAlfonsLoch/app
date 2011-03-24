#include "StdAfx.h"
#include "CDBrowse.h"


CCDBrowse::CCDBrowse(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   mdi_child_window(papp)
{
}

CCDBrowse::~CCDBrowse()
{
}


 // BEGIN_MESSAGE_MAP(CCDBrowse, mdi_child_window)
   //{{AFX_MSG_MAP(CCDBrowse)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDBrowse message handlers
