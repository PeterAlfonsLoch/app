// OptionsImagesDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "resource.h"
#include "OptionsImagesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsImagesDialog dialog


COptionsImagesDialog::COptionsImagesDialog()
	: BaseForm(COptionsImagesDialog::IDD)
{
	//{{AFX_DATA_INIT(COptionsImagesDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COptionsImagesDialog::COptionsImagesDialog(CWnd* pParent /*=NULL*/)
	: BaseForm(COptionsImagesDialog::IDD, pParent)
{
}


void COptionsImagesDialog::DoDataExchange(CDataExchange* pDX)
{
	BaseForm::DoDataExchange(pDX);
	//CDDX::DDXRadio(pDX, IDC_RADIO_SEQUENTIAL, 1, &m_lChangeType);
	//CDDX::DDXRadio(pDX, IDC_RADIO_RANDOM, 2, &m_lChangeType);
	//CDDX::DDVEditIntegerRange(pDX, IDC_EDIT_CHANGE_TIME, BACKGROUND_IMAGE_CHANGE_MIN_SECONDS, BACKGROUND_IMAGE_CHANGE_MAX_SECONDS);
	//CDDX::DDXEdit(pDX, IDC_EDIT_CHANGE_TIME, &m_iChangeTime);
	//{{AFX_DATA_MAP(COptionsImagesDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsImagesDialog, BaseForm)
	//{{AFX_MSG_MAP(COptionsImagesDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsImagesDialog message handlers

BOOL COptionsImagesDialog::Update(BOOL bSaveAndValidate)
{
	if(bSaveAndValidate)
	{
		if(!UpdateData())
			return FALSE;
		if(!UpdateDatabase())
			return FALSE;
	}
	else
	{
		if(!UpdateDatabase(FALSE))
			return FALSE;
		if(!UpdateData(FALSE))
			return FALSE;
	}
	return TRUE;
}

BOOL COptionsImagesDialog::UpdateDatabase(BOOL bSaveAndValidate)
{
	//try
	//{
/*	CDBCentral *pDataCentral = (CDBCentral *) DB();
	CDBLongSet *pSet = pDataCentral->GetDBLongSet();
	if(bSaveAndValidate)
	{
		pSet->Save(_T("Images"), _T("ChangeType"), m_lChangeType);
		pSet->Save(_T("Images"), _T("ChangeTime"), m_iChangeTime);
	}
	else
	{
		if(!pSet->Load(_T("Images"), _T("ChangeType"), &m_lChangeType))
			m_lChangeType = 1;
		if(!pSet->Load(_T("Images"), _T("ChangeTime"), (long*) &m_iChangeTime))
			m_iChangeTime = 30;
	}
	return TRUE;*/
	
/*	} catch(COLEDBException *e)
	{
		CDBErrorDialog dlg;
		dlg.Init(e->m_spUnk, e->m_iid);
		dlg.DoModal();
		e->Delete();
	}*/
	return FALSE;
}


BOOL COptionsImagesDialog::OnInitDialog() 
{
	BaseForm::OnInitDialog();
	
	// TODO: Add extra initialization here
/*	CDBCentral *pDataCentral = (CDBCentral *) DB();
	CDBLongSet *pSet = pDataCentral->GetDBLongSet();
	
	if(DB()->IsWorking())
	{
	}

	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl *) GetDlgItem(IDC_SPIN_CHANGE_TIME);
	CEdit *pEdit = (CEdit *) GetDlgItem(IDC_EDIT_CHANGE_TIME);
	if(pSpin && pEdit)
	{
		pSpin->SetBuddy(pEdit);
		pSpin->SetRange(
			BACKGROUND_IMAGE_CHANGE_MIN_SECONDS,
			BACKGROUND_IMAGE_CHANGE_MAX_SECONDS);
	}*/

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}

BOOL COptionsImagesDialog::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if(BaseForm::DestroyWindow())
    {
        delete this;
	    return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void COptionsImagesDialog::_001InitializeFormPreData()
{
	Ex1FormInterfaceControl control;

/*	control.m_bTransparent = true;
	control.m_etype = Ex1FormInterfaceControl::TypeStatic;
	control.m_uiId = IDC_ST_FILE_EXTENSION;
	control.AddFunction(Ex1FormInterfaceControl::FunctionStatic);
	_001AddControl(control);*/

	control.SetType(Ex1FormInterfaceControl::TypeEdit);
	control.m_uiId = IDC_EDIT_CHANGE_TIME;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleEdit);
	control.m_datakey = VMSDATAKEY(BackgroundImageChangeSecondsHint);
   control.SetDataType(Ex1FormInterfaceControl::DataTypeNatural);
	_001AddControl(control);

	/*control.SetType(Ex1FormInterfaceControl::TypeCheckBox);
	control.m_uiId = IDC_CHECK_MRU;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	control.m_datakey = VMSDATAKEY(MRUEnable);
	_001AddControl(control);

	control.SetType(Ex1FormInterfaceControl::TypeEdit);
	control.m_uiId = IDC_EDIT_MRU_COUNT;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleEdit);
	control.m_datakey = VMSDATAKEY(MRUCount);
   control.SetDataType(Ex1FormInterfaceControl::DataTypeNatural);
	_001AddControl(control);*/

}
