// EditV017.cpp : implementation file
//

#include "stdafx.h"
//#include "VMSApp.h"
#include "EditV017.h"

#include "VMS_.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditV017

CEditV017::CEditV017()
{
}

CEditV017::~CEditV017()
{
}

/*
BEGIN_MESSAGE_MAP(CEditV017, CEdit)
	//{{AFX_MSG_MAP(CEditV017)
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
// CEditV017 message handlers

void CEditV017::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
/*    E17_KEYDOWN ekd;
    ekd.hdr.hwndFrom = GetSafeHwnd();
    ekd.hdr.idFrom = GetDlgCtrlID();
    ekd.wVKey = nChar;
    ekd.flags = nFlags;
    ekd.hdr.code = E17N_KEYDOWN;

    if(!GetParent()->SendMessage(VMSM_NOTIFY, ekd.hdr.idFrom, (LPARAM) &ekd))
        CEdit::OnKeyDown(nChar, nRepCnt, nFlags);*/
}

void CEditV017::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
/*    E17_SYSKEYDOWN ekd;
    ekd.hdr.hwndFrom = GetSafeHwnd();
    ekd.hdr.idFrom = GetDlgCtrlID();
    ekd.wVKey = nChar;
    ekd.flags = nFlags;
    ekd.hdr.code = E17N_SYSKEYDOWN;

    if(!GetParent()->SendMessage(VMSM_NOTIFY, ekd.hdr.idFrom, (LPARAM) &ekd))
	    CEdit::OnSysKeyDown(nChar, nRepCnt, nFlags);*/
}
