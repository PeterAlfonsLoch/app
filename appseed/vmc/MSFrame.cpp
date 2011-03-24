#include "StdAfx.h"
#include "MSFrame.h"

CMSFrame::CMSFrame(::ca::application * papp) :
   ::ca::ca(papp),
   SimpleMDIChildWindow(papp),
   SimpleFrameWindow(papp)
{
}

CMSFrame::~CMSFrame()
{
}

/*
BEGIN_MESSAGE_MAP(CMSFrame, SimpleMDIChildWindow)
	//{{AFX_MSG_MAP(CMSFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// CXfplayerFrame diagnostics

#ifdef _DEBUG
void CMSFrame::AssertValid() const
{
	SimpleMDIChildWindow::AssertValid();
}

void CMSFrame::Dump(CDumpContext& dc) const
{
	SimpleMDIChildWindow::Dump(dc);
}

#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CMSFrame message handlers
