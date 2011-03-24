// OptionsDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "../vmsp/resource.h"
#include "..\vms\Vms.h"
//#include "xfplayerdoc.h"
//#include "xfplayerview.h"
#include "OptionsDialog.h"
//#include "OptionsImagesDirectoriesDialog.h"
#include "OptionsSongsDirectoriesDialog.h"
//#include "OptionsImagesDialog.h"
//#include "OptionsAudioDevicesDialog.h"
#include "DBSongSet.h"
#include "songdirectory.h"
#include "DBImageFile.h"
#include "DBImageDirectory.h"

#include "DataCentral.h"
#include "DBCentral.h"

#include "VmsseApp.h"
#include "VmsseThread.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog


COptionsDialog::COptionsDialog()
	: CDialog(COptionsDialog::IDD)
{
	//{{AFX_DATA_INIT(COptionsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pSongsDirsDlg = NULL;
//	m_pImagesDirsDlg = NULL;
//	m_pImagesDlg = NULL;
}

COptionsDialog::COptionsDialog(CWnd* pParent)
	: CDialog(COptionsDialog::IDD, pParent)
{
	m_pSongsDirsDlg = NULL;
//	m_pImagesDirsDlg = NULL;
//	m_pImagesDlg = NULL;
}

COptionsDialog::~COptionsDialog()
{
}

void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDialog)
	DDX_Control(pDX, IDC_TAB, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	//{{AFX_MSG_MAP(COptionsDialog)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB, OnSelchangingTab)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_BN_CLICKED(IDAPPLY, OnApply)
	ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog message handlers

//void COptionsDialog::OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult) 
void COptionsDialog::OnSelchangingTab(NMHDR* , LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	int index = m_Tab.GetCurSel();
	switch(index)
	{
	case 0:
		if(!m_pSongsDirsDlg->UpdateData())
			*pResult = TRUE;
		if(!*pResult)
			m_pSongsDirsDlg->ShowWindow(SW_HIDE);
		break;
/*	case 1:
		if(!m_pImagesDlg->UpdateData())
			*pResult = TRUE;
		if(!*pResult)
			m_pImagesDlg->ShowWindow(SW_HIDE);
		break;
	case 2:
		if(!m_pImagesDirsDlg->UpdateData())
			*pResult = TRUE;
		if(!*pResult)
			m_pImagesDirsDlg->ShowWindow(SW_HIDE);
		break;
	case 3:
		if(!m_pAudioDevsDlg->UpdateData())
			*pResult = TRUE;
		if(!*pResult)
			m_pAudioDevsDlg->ShowWindow(SW_HIDE);
		break;*/
	default:
		break;
	}

}

//void COptionsDialog::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
void COptionsDialog::OnSelchangeTab(NMHDR* , LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int index = m_Tab.GetCurSel();
	switch(index)
	{
	case 0:
		
		m_pSongsDirsDlg->UpdateData(FALSE);
		m_pSongsDirsDlg->ShowWindow(SW_SHOW);
		break;
/*	case 1:
		m_pImagesDlg->UpdateData(FALSE);
		m_pImagesDlg->ShowWindow(SW_SHOW);
		break;
	case 2:
		m_pImagesDirsDlg->UpdateData(FALSE);
		m_pImagesDirsDlg->ShowWindow(SW_SHOW);
		break;
	case 3:
		m_pAudioDevsDlg->UpdateData(FALSE);
		m_pAudioDevsDlg->ShowWindow(SW_SHOW);
		break;*/
	default:
		break;
	}
	
	*pResult = 0;
}

BOOL COptionsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Tab.InsertItem(0, _T("Pastas das Músicas"));
	m_Tab.InsertItem(1, _T("Imagens"));
	m_Tab.InsertItem(2, _T("Pastas das Imagens"));
    CString str;
    str.LoadString(IDS_OPTIONS_AUDIODEVICES);
    m_Tab.InsertItem(3, str);
//	m_pImagesDlg = new COptionsImagesDialog();
	m_pSongsDirsDlg = new COptionsSongsDirectoriesDialog();
//	m_pImagesDirsDlg = new COptionsImagesDirectoriesDialog();
//    m_pAudioDevsDlg = new COptionsAudioDevicesDialog();
	//m_pSongsDirsPlg->m_pSet = m_pSet;
//	BOOL b = IsWindow(m_pPrincipalView->m_hWnd);
//	b = IsWindow(m_pContatosView->m_hWnd);
	//m_pSongsDirsDlg->Create(m_pSongsDirsDlg->IDD IDD_OPTIONS_SONGS_DIRECTORIES, &m_Tab);
    AfxSetResourceHandle(GetModuleHandle("vmsgui"));
    m_pSongsDirsDlg->Create(&m_Tab);
    AfxSetResourceHandle(GetModuleHandle(NULL));
//	m_pImagesDlg->Create(IDD_OPTIONS_IMAGES, &m_Tab);
//	m_pImagesDirsDlg->Create(IDD_OPTIONS_IMAGES_DIRECTORIES, &m_Tab);
//    m_pAudioDevsDlg->Create(&m_Tab);
//	b = IsWindow(m_pPrincipalView->m_hWnd);
//	b = IsWindow(m_pContatosView->m_hWnd);
	//RECT tabRect;
	//RECT parentRect;
	//RECT parentClientRect;
	RECT rect;
	//m_Tab.GetWindowRect(&tabRect);
	//GetWindowRect(&parentRect);
	//GetClientRect(&parentClientRect);
	//CDC *pDC = GetDC();
	//CPoint clientOrg = pDC->GetWindowOrg();
	//ReleaseDC(pDC);
	rect.left = 1;
	rect.top = 1;
	rect.right = 2; // not used
	rect.bottom = 2; // not used
	
//	bool bIsWindow = ::IsWindow(m_pSongsDirsDlg->m_hWnd);
//	if(bIsWindow)
//	{
	m_pSongsDirsDlg->MapDialogRect(&rect);
//	}
//	rect.left = rect.left + tabRect.left + parentClientRect.right - parentRect.right;
//	rect.top = rect.top + tabRect.top + parentClientRect.bottom - parentRect.bottom;
	m_Tab.AdjustRect(FALSE, &rect);
	m_pSongsDirsDlg->SetWindowPos
		(&wndTop,
		 rect.left,
		 rect.top,
		 0,
		 0,
		 SWP_NOSIZE);
/*	m_pImagesDlg->SetWindowPos
		(&wndTop,
		 rect.left,
		 rect.top,
		 0,
		 0,
		 SWP_NOSIZE);
	m_pImagesDirsDlg->SetWindowPos
		(&wndTop,
		 rect.left,
		 rect.top,
		 0,
		 0,
		 SWP_NOSIZE);
	m_pAudioDevsDlg->SetWindowPos
		(&wndTop,
		 rect.left,
		 rect.top,
		 0,
		 0,
		 SWP_NOSIZE);*/
	//m_pImagesDirsDlg->Update(FALSE);
	m_pSongsDirsDlg->Update(FALSE);
	//m_pImagesDlg->Update(FALSE);
    //m_pAudioDevsDlg->Update(FALSE);
	m_Tab.SetCurSel(0);
	NMHDR NMHDR;
	NMHDR.hwndFrom = m_Tab.m_hWnd;
	NMHDR.idFrom = IDC_TAB;
	NMHDR.code = TCN_SELCHANGE;
	//b = IsWindow(m_hWnd);
	this->SendMessage(WM_NOTIFY, IDC_TAB , (LPARAM) &NMHDR);
//	Update(FALSE);
	CStatic * pApply = (CStatic *) GetDlgItem(IDAPPLY);
    pApply->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void COptionsDialog::OnOK() 
{
	// TODO: Add extra validation here
    Apply();
	CDialog::OnOK();
}

BOOL COptionsDialog::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreCreateWindow(cs);
}

void COptionsDialog::Apply()
{
	bool bSongsDirsModified = m_pSongsDirsDlg->IsModified();
//	bool bImagesDirsModified = m_pImagesDirsDlg->IsModified();
//    bool bAudioDevsModified = m_pAudioDevsDlg->IsModified();
	if(bSongsDirsModified)
	{
		if(!m_pSongsDirsDlg->Update())
			return;
	}
//	if(!m_pImagesDlg->Update())
//		return;
/*	if(bImagesDirsModified)
	{
		if(!m_pImagesDirsDlg->Update())
			return;
	}*/
    /*if(bAudioDevsModified)
    {
        m_pAudioDevsDlg->Update();

    }*/
	CVmsseApp * pApp = (CVmsseApp *) AfxGetApp();
	CStringArray strArray;
//	HRESULT hr;
	if(bSongsDirsModified)
	{
		DB()->OnSongsDirsModified(pApp->m_pthread);
	}
/*	if(bImagesDirsModified)
    {
		CDataCentral::AppGetDBCentral()->OnImagesDirsModified();
	}*/

//	pApp->m_iBackgroundUpdateMillis = m_pImagesDlg->m_iChangeTime * 1000;
    CStatic * pApply = (CStatic *) GetDlgItem(IDAPPLY);
    pApply->EnableWindow(FALSE);

}

void COptionsDialog::OnApply() 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
	// TODO: Add your control notification handler code here
	Apply();
}

BOOL COptionsDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_USER)
    {
        if(pMsg->hwnd == m_hWnd)
        {
            if(pMsg->wParam == 1000)
            {
                CStatic * pApply = (CStatic *) GetDlgItem(IDAPPLY);
                pApply->EnableWindow(TRUE);
            }
        }
    }
	return CDialog::PreTranslateMessage(pMsg);
}

void COptionsDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
//   	if(m_pSongsDirsDlg != NULL)
//		m_pSongsDirsDlg->DestroyWindow();
//	if(m_pImagesDirsDlg != NULL)
//		m_pImagesDirsDlg->DestroyWindow();
//	if(m_pImagesDlg != NULL)
//		m_pImagesDlg->DestroyWindow();


	// TODO: Add your message handler code here
	
}

BOOL COptionsDialog::Create(CWnd *pwndParent)
{
    return CDialog::Create(IDD, pwndParent);
}
