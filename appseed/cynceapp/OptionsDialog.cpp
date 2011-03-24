// OptionsDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "resource.h"
#include "OptionsDialog.h"
#include "OptionsImagesDirectoriesDialog.h"
#include "OptionsSongsDirectoriesDialog.h"
#include "OptionsGeneralDialog.h"
#include "OptionsImagesDialog.h"
#include "OptionsAudioDevicesDialog.h"
#include "FileAssociationForm.h"
//#include "DBSongSet.h"
//#include "songdirectory.h"
#include "DBImageFile.h"
#include "DBImageDirectory.h"





#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OptionsDialog dialog


OptionsDialog::OptionsDialog()
	: BaseForm(OptionsDialog::IDD)
{
	//{{AFX_DATA_INIT(OptionsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pImagesDlg = NULL;
	m_pSongsDirsDlg = NULL;
	m_pdlgGeneral = NULL;
	m_pImagesDirsDlg = NULL;
	m_pAudioDevsDlg = NULL;
   m_pfileassociationform = NULL;
}

OptionsDialog::OptionsDialog(CWnd* pParent)
	: BaseForm(OptionsDialog::IDD, pParent)
{
	m_pImagesDlg = NULL;
	m_pSongsDirsDlg = NULL;
	m_pdlgGeneral = NULL;
	m_pImagesDirsDlg = NULL;
	m_pAudioDevsDlg = NULL;
}

OptionsDialog::~OptionsDialog()
{
		if(m_pImagesDlg != NULL)
	{
		delete m_pImagesDlg;
		m_pImagesDlg = NULL;
	}
	if(m_pSongsDirsDlg != NULL)
	{
		delete m_pSongsDirsDlg;
		m_pSongsDirsDlg = NULL;
	}
	if(m_pdlgGeneral != NULL)
	{
		delete m_pdlgGeneral;
		m_pdlgGeneral = NULL;
	}
	if(m_pImagesDirsDlg != NULL)
	{
		delete m_pImagesDirsDlg;
		m_pImagesDirsDlg = NULL;
	}
	if(m_pAudioDevsDlg != NULL)
	{
		delete m_pAudioDevsDlg;
		m_pAudioDevsDlg = NULL;
	}

}

void OptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	BaseForm::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OptionsDialog)
	DDX_Control(pDX, IDC_TAB, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OptionsDialog, BaseForm)
	//{{AFX_MSG_MAP(OptionsDialog)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB, OnSelchangingTab)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_BN_CLICKED(IDAPPLY, OnApply)
	ON_WM_DESTROY()
    //}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OptionsDialog message handlers

//void OptionsDialog::OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult) 
void OptionsDialog::OnSelchangingTab(NMHDR* , LRESULT* pResult) 
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
	case 1:
		if(!m_pdlgGeneral->UpdateData())
			*pResult = TRUE;
		if(!*pResult)
			m_pdlgGeneral->ShowWindow(SW_HIDE);
		break;
	case 2:
		if(!m_pfileassociationform->UpdateData())
			*pResult = TRUE;
		if(!*pResult)
			m_pfileassociationform->ShowWindow(SW_HIDE);
		break;

	case 3:
		if(!m_pImagesDlg->UpdateData())
			*pResult = TRUE;
		if(!*pResult)
			m_pImagesDlg->ShowWindow(SW_HIDE);
		break;
	case 4:
		if(!m_pImagesDirsDlg->UpdateData())
			*pResult = TRUE;
		if(!*pResult)
			m_pImagesDirsDlg->ShowWindow(SW_HIDE);
		break;
	case 5:
		if(!m_pAudioDevsDlg->UpdateData())
			*pResult = TRUE;
		if(!*pResult)
			m_pAudioDevsDlg->ShowWindow(SW_HIDE);
		break;
	default:
		break;
	}

}

//void OptionsDialog::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
void OptionsDialog::OnSelchangeTab(NMHDR* , LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int index = m_Tab.GetCurSel();
	switch(index)
	{
	case 0:
		
		m_pSongsDirsDlg->UpdateData(FALSE);
		m_pSongsDirsDlg->ShowWindow(SW_SHOW);
		break;
	case 1:
		m_pdlgGeneral->UpdateData(FALSE);
		m_pdlgGeneral->ShowWindow(SW_SHOW);
		break;
	case 2:
		m_pfileassociationform->Update(false);
		m_pfileassociationform->ShowWindow(SW_SHOW);
		break;
	case 3:
		m_pImagesDlg->UpdateData(FALSE);
		m_pImagesDlg->ShowWindow(SW_SHOW);
		break;
	case 4:
		m_pImagesDirsDlg->UpdateData(FALSE);
		m_pImagesDirsDlg->ShowWindow(SW_SHOW);
		break;
	case 5:
		m_pAudioDevsDlg->UpdateData(FALSE);
		m_pAudioDevsDlg->ShowWindow(SW_SHOW);
		break;

	default:
		break;
	}
	
	*pResult = 0;
}

BOOL OptionsDialog::OnInitDialog() 
{
	BaseForm::OnInitDialog();
	
   CString str;

   str.LoadString(IDS_OPTIONS_SONGSFOLDER);
	m_Tab.InsertItem(0, str);

   str.LoadString(IDS_OPTIONS_GENERAL);
   m_Tab.InsertItem(1, str);

   str.LoadString(IDS_OPTIONS_FILE_ASSOCIATIONS);
   m_Tab.InsertItem(2, str);

   str.LoadString(IDS_OPTIONS_IMAGES);
	m_Tab.InsertItem(3, str);

   str.LoadString(IDS_OPTIONS_IMAGESFOLDERS);
	m_Tab.InsertItem(4, str);

   str.LoadString(IDS_OPTIONS_AUDIODEVICES);
   m_Tab.InsertItem(5, str);


   m_pImagesDlg = new COptionsImagesDialog();
   m_pSongsDirsDlg = new COptionsSongsDirectoriesDialog();
   m_pdlgGeneral = new OptionsGeneralDialog();
   m_pImagesDirsDlg = new COptionsImagesDirectoriesDialog();
   m_pAudioDevsDlg = new COptionsAudioDevicesDialog();
   m_pfileassociationform = new CFileAssociationForm();
	
    
   m_pImagesDlg->Create(IDD_OPTIONS_IMAGES, &m_Tab);
   m_pSongsDirsDlg->Create(&m_Tab);
   m_pdlgGeneral->Create(IDD_OPTIONS_GENERAL, &m_Tab);
   m_pImagesDirsDlg->Create(IDD_OPTIONS_IMAGES_DIRECTORIES, &m_Tab);
   m_pAudioDevsDlg->Create(&m_Tab);
   m_pfileassociationform->Create(IDD_FILE_ASSOCIATIONS, &m_Tab);

   RECT rect;
	rect.left = 1;
	rect.top = 1;
	rect.right = 2; // not used
	rect.bottom = 2; // not used
	
	m_pSongsDirsDlg->MapDialogRect(&rect);
	m_Tab.AdjustRect(FALSE, &rect);
	m_pSongsDirsDlg->SetWindowPos
		(&wndTop,
		 rect.left,
		 rect.top,
		 0,
		 0,
		 SWP_NOSIZE);
	m_pdlgGeneral->SetWindowPos
		(&wndTop,
		 rect.left,
		 rect.top,
		 0,
		 0,
		 SWP_NOSIZE);
	m_pImagesDlg->SetWindowPos
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
		 SWP_NOSIZE);
	m_pfileassociationform->SetWindowPos
		(&wndTop,
		 rect.left,
		 rect.top,
		 0,
		 0,
		 SWP_NOSIZE);

   m_pImagesDirsDlg->Update(FALSE);
	m_pSongsDirsDlg->Update(FALSE);
   m_pdlgGeneral->Update(FALSE);
	m_pImagesDlg->Update(FALSE);
   m_pAudioDevsDlg->Update(FALSE);
   m_pfileassociationform->Update(FALSE);

	m_Tab.SetCurSel(0);

	NMHDR NMHDR;
	NMHDR.hwndFrom = m_Tab.m_hWnd;
	NMHDR.idFrom = IDC_TAB;
	NMHDR.code = TCN_SELCHANGE;

   SendMessage(WM_NOTIFY, IDC_TAB , (LPARAM) &NMHDR);

   CStatic * pApply = (CStatic *) GetDlgItem(IDAPPLY);
   pApply->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void OptionsDialog::OnOK() 
{
	// TODO: Add extra validation here
    if(Apply())
	{
		BaseForm::OnOK();
	}
}

BOOL OptionsDialog::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return BaseForm::PreCreateWindow(cs);
}

bool OptionsDialog::Apply()
{
	bool bImagesDirsModified = m_pImagesDirsDlg->IsModified();
    bool bAudioDevsModified = m_pAudioDevsDlg->IsModified();
	if(!m_pdlgGeneral->Update())
		return false;

	if(!m_pSongsDirsDlg->Apply())
		return false;

	if(!m_pImagesDlg->Update())
		return false;
	if(bImagesDirsModified)
	{
		if(!m_pImagesDirsDlg->Update())
			return false;
	}
    if(bAudioDevsModified)
    {
        m_pAudioDevsDlg->Update();

    }

	MusicalPlayerLightApp * pApp = (MusicalPlayerLightApp *) AfxGetApp();
	CStringArray strArray;
//	HRESULT hr;
	if(bImagesDirsModified)
	{
		DB()->OnImagesDirsModified();
	}

	pApp->m_iBackgroundUpdateMillis = m_pImagesDlg->m_iChangeTime * 1000;
    CStatic * pApply = (CStatic *) GetDlgItem(IDAPPLY);
    pApply->EnableWindow(FALSE);
//    pApp->UpdateMRU(m_pdlgGeneral->m_bMRUEnable, m_pdlgGeneral->m_iMRUCount); TODO
	return true;
}

void OptionsDialog::OnApply() 
{
	// TODO: Add your control notification handler code here
	Apply();
}

BOOL OptionsDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_USER)
    {
        if(pMsg->hwnd = m_hWnd)
        {
            if(pMsg->wParam == 1000)
            {
                CStatic * pApply = (CStatic *) GetDlgItem(IDAPPLY);
                pApply->EnableWindow(TRUE);
            }
        }
    }
	return BaseForm::PreTranslateMessage(pMsg);
}

void OptionsDialog::OnDestroy() 
{

	BaseForm::OnDestroy();
	
//   	if(m_pSongsDirsDlg != NULL)
//		m_pSongsDirsDlg->DestroyWindow();
//	if(m_pImagesDirsDlg != NULL)
//		m_pImagesDirsDlg->DestroyWindow();
//	if(m_pImagesDlg != NULL)
//		m_pImagesDlg->DestroyWindow();


	// TODO: Add your message handler code here
	
}


void OptionsDialog::_001InitializeFormPreData()
{
	Ex1FormInterfaceControl control;

	control.m_uiId = IDOK;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	_001AddControl(control);

	control.m_uiId = IDCANCEL;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	_001AddControl(control);

	control.m_uiId = IDAPPLY;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	_001AddControl(control);

}