// NpvmpFrame.cpp : implementation file
//

#include "stdafx.h"
#include "npvmp.h"
#include "NpvmpFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNpvmpFrame

IMPLEMENT_DYNCREATE(CNpvmpFrame, CFrameWnd)

CNpvmpFrame::CNpvmpFrame()
{
}

CNpvmpFrame::~CNpvmpFrame()
{
}


BEGIN_MESSAGE_MAP(CNpvmpFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CNpvmpFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNpvmpFrame message handlers

BOOL CNpvmpFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style &= ~WS_CAPTION;	
	cs.style &= ~WS_BORDER;
	cs.style &= ~WS_SYSMENU;
	cs.style &= ~WS_MAXIMIZE;
	cs.style &= ~WS_MAXIMIZEBOX;
	cs.style &= ~WS_MINIMIZEBOX;
	return CFrameWnd::PreCreateWindow(cs);
}

int CNpvmpFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CNpvmpFrame::OnDestroy() 
{
	m_hMenuDefault = NULL;

	CFrameWnd::OnDestroy();

}
