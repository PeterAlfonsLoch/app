#include "stdafx.h"
#include "MidiEventsFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMidiEventsFrame::CMidiEventsFrame(::ca::application * papp) :
   ::ca::ca(papp),
   SimpleMDIChildWindow(papp),
   SimpleFrameWindow(papp)
{
}

CMidiEventsFrame::~CMidiEventsFrame()
{
}

/*
BEGIN_MESSAGE_MAP(CMidiEventsFrame, SimpleMDIChildWindow)
	//{{AFX_MSG_MAP(CMidiEventsFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// CMidiEventsFrame message handlers
