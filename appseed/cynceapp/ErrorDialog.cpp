// ErrorDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "resource.h"
#include "ErrorDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErrorDialog dialog


CErrorDialog::CErrorDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CErrorDialog::IDD, pParent)
{
	
	//{{AFX_DATA_INIT(CErrorDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CErrorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CErrorDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CErrorDialog, CDialog)
	//{{AFX_MSG_MAP(CErrorDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErrorDialog message handlers

void CErrorDialog::Initialize(CMidiException * pMidiException)
{
	m_pMidiException = pMidiException;
}

BOOL CErrorDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CStatic * pImage = (CStatic *) GetDlgItem(IDC_STATIC_IMAGE);
	CWnd * pWndText = GetDlgItem(IDC_STATIC_TEXT);
	CEdit * pEditAdvanced = (CEdit *) GetDlgItem(IDC_EDIT_ADVANCED);
	
	if(m_pMidiException != NULL)
	{
		HICON hIcon = ::LoadIcon(NULL, IDI_EXCLAMATION);
		pImage->SetIcon(hIcon);
		pWndText->SetWindowText(m_pMidiException->GetUserText());
		pEditAdvanced->SetWindowText(m_pMidiException->GetDetailsText());
	}
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
