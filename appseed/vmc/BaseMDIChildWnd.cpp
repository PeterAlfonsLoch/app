// BaseMDIChildWnd.cpp : implementation file
//

#include "stdafx.h"
//#include "VMSApp.h"
#include "BaseMDIChildWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CBaseMDIChildWnd::CBaseMDIChildWnd(::ca::application * papp) :
   ::ca::ca(papp),
   SimpleMDIChildWindow(papp),
   SimpleFrameWindow(papp)
{
}

CBaseMDIChildWnd::~CBaseMDIChildWnd()
{
}


BEGIN_MESSAGE_MAP(CBaseMDIChildWnd, SimpleMDIChildWindow)
	//{{AFX_MSG_MAP(CBaseMDIChildWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseMDIChildWnd message handlers

CMDIFrameWnd* CBaseMDIChildWnd::GetMDIFrame()
{
	ASSERT_KINDOF(SimpleMDIChildWindow, this);
	ASSERT(get_handle() != NULL);
	HWND hWndMDIClient = ::GetParent(get_handle());
	ASSERT(hWndMDIClient != NULL);

	CMDIFrameWnd* pMDIFrame;
	pMDIFrame = dynamic_cast < CMDIFrameWnd * > (base_wnd::FromHandle(::GetParent(hWndMDIClient)));
	ASSERT(pMDIFrame != NULL);
	ASSERT_KINDOF(CMDIFrameWnd, pMDIFrame);
	ASSERT(pMDIFrame->m_hWndMDIClient == hWndMDIClient);
	ASSERT_VALID(pMDIFrame);
	return pMDIFrame;
}