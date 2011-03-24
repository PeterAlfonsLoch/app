// ChildFrm.cpp : implementation of the CMidiTrackSelectFrame class
//

#include "StdAfx.h"
#include "vmssyncheditor.h"

#include "MidiTrackSelectFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMidiTrackSelectFrame

IMPLEMENT_DYNCREATE(CMidiTrackSelectFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CMidiTrackSelectFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CMidiTrackSelectFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMidiTrackSelectFrame construction/destruction

CMidiTrackSelectFrame::CMidiTrackSelectFrame()
{
	// TODO: add member initialization code here
	
}

CMidiTrackSelectFrame::~CMidiTrackSelectFrame()
{
}

BOOL CMidiTrackSelectFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMidiTrackSelectFrame diagnostics

#ifdef _DEBUG
void CMidiTrackSelectFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CMidiTrackSelectFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMidiTrackSelectFrame message handlers

int CMidiTrackSelectFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
