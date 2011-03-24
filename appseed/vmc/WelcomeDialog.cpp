// WelcomeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "../vmsp/resource.h"
#include "VmcApp.h"
#include "resource.h"
#include "../vms/Vms.h"
#include "WelcomeDialog.h"

#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDialog dialog


CWelcomeDialog::CWelcomeDialog(base_wnd* pParent /*=NULL*/)
	: CDialog(CWelcomeDialog::IDD, pParent),
    m_brushBackground(GetSysColor(COLOR_WINDOW))
{
	//{{AFX_DATA_INIT(CWelcomeDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_crBackground = GetSysColor(COLOR_WINDOW);
    m_crForeground = GetSysColor(COLOR_WINDOWTEXT);

}


void CWelcomeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcomeDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

/*
BEGIN_MESSAGE_MAP(CWelcomeDialog, CDialog)
	//{{AFX_MSG_MAP(CWelcomeDialog)
	ON_BN_CLICKED(ID_TOOLS_ALBUM, OnToolsAlbum)
	ON_BN_CLICKED(ID_PLAYER, OnPlayer)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDialog message handlers

void CWelcomeDialog::OnToolsAlbum() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
    CVmcApp * pApp = CVmcApp::app(get_app());
//    CMainFrame* pFrame = (CMainFrame *) pApp->m_pMainWnd;
    pApp->ViewToolsAlbum();
}

BOOL CWelcomeDialog::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	 CVmcApp * pApp = CVmcApp::app(get_app());
     
     if(!CDialog::DestroyWindow())
         return FALSE;
     pApp->SetWelcomeDialog(NULL);
     delete this;
	 return TRUE; 
}

void CWelcomeDialog::OnPlayer() 
{
   SendMessage(WM_CLOSE);
   CVmcApp * pApp = CVmcApp::app(get_app());
   CMainFrame* pFrame = dynamic_cast < CMainFrame * > (pApp->m_pMainWnd);
   pFrame->OpenPlayerWindow();
	
}

HBRUSH CWelcomeDialog::OnCtlColor(CDC* pDC, base_wnd* pWnd, UINT nCtlColor) 
{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired

    	HBRUSH hbr;
	if(nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetTextColor(m_crForeground);
		hbr = m_brushBackground;
		pDC->SetBkColor(m_crBackground);
	}
//	else if(nCtlColor == CTLCOLOR_MSGBOX)
//	{
//		hbr = m_brushBackground;
//	}
	else if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(m_crForeground);
		hbr = m_brushBackground;
		pDC->SetBkColor(m_crBackground);
	}
	else if(nCtlColor == CTLCOLOR_DLG)
	{
//		pDC->SetTextColor(RGB(255, 255, 255));
		hbr = m_brushBackground;
//		pDC->SetBkColor(RGB(0, 0, 0));
	}
	else
	{
		hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	return hbr;
}

void CWelcomeDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	DestroyWindow();
	//CDialog::OnClose();
}
