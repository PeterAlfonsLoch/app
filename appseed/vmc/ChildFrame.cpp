// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "StdAfx.h"
#include "VmcApp.h"

#include "ChildFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

//IMPLEMENT_DYNCREATE(CChildFrame, SimpleMDIChildWindow)

/*
BEGIN_MESSAGE_MAP(CChildFrame, SimpleMDIChildWindow)
	//{{AFX_MSG_MAP(CChildFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame(::ca::application * papp) :
   ::ca::ca(papp),
   SimpleMDIChildWindow(papp),
   SimpleFrameWindow(papp)
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !SimpleMDIChildWindow::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	SimpleMDIChildWindow::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	SimpleMDIChildWindow::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
