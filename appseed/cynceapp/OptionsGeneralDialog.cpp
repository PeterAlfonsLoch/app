// OptionsGeneralDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "OptionsGeneralDialog.h"


#include "_vmspConfiguration.h"

/*
#include "vmsguibase/SimpleButton.h"
#include "vmsguibase/SimpleEdit.h"
#include "vmsguibase/SimpleStatic.h"
*/

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OptionsGeneralDialog dialog


OptionsGeneralDialog::OptionsGeneralDialog(CWnd* pParent /*=NULL*/)
	: BaseForm(OptionsGeneralDialog::IDD, pParent)
{
//   ((CVmsDBApp *) AfxGetApp())->GetVmsDataServerInterface().AddClient(this);
	//{{AFX_DATA_INIT(OptionsGeneralDialog)
	//m_bMRUEnable = FALSE;
	//m_iMRUCount = 0;
	//m_iDelay = 0;
	//}}AFX_DATA_INIT
}


void OptionsGeneralDialog::DoDataExchange(CDataExchange* pDX)
{
	BaseForm::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OptionsGeneralDialog)
//	DDX_Check(pDX, IDC_CHECK_MRU, m_bMRUEnable);
//	DDX_Text(pDX, IDC_EDIT_MRU_COUNT, m_iMRUCount);
//	DDV_MinMaxInt(pDX, m_iMRUCount, 1, 10);
//	DDX_Text(pDX, IDC_EDIT_SYNCH_DELAY, m_iDelay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OptionsGeneralDialog, BaseForm)
	//{{AFX_MSG_MAP(OptionsGeneralDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OptionsGeneralDialog message handlers

BOOL OptionsGeneralDialog::Update(BOOL bSaveAndValidate)
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

BOOL OptionsGeneralDialog::UpdateDatabase(BOOL bSaveAndValidate)
{
	//try
	//{
/*	CDBCentral *pDataCentral = (CDBCentral *) DB();
	CDBLongSet *pSet = pDataCentral->GetDBLongSet();
	if(bSaveAndValidate)
	{
		pSet->Save(_T("MRU"), _T("Count"), m_iMRUCount);
		pSet->Save(_T("MRU"), _T("Enable"), m_bMRUEnable);
      VmsDataSet(VMSDATAKEY(GlobalLyricsDelay), 0, 0, m_iDelay);
	}
	else
	{
		if(!pSet->Load(_T("MRU"), _T("Count"), m_iMRUCount))
			m_iMRUCount = _AFX_MRU_COUNT;
		if(!pSet->Load(_T("MRU"), _T("Enable"), (int &) m_bMRUEnable))
			m_bMRUEnable = TRUE;
      if(!VmsDataGet(VMSDATAKEY(GlobalLyricsDelay), 0, 0, m_iDelay))
         m_iDelay = 0;

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

BOOL OptionsGeneralDialog::OnInitDialog() 
{
	BaseForm::OnInitDialog();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void OptionsGeneralDialog::_001InitializeFormPreData()
{
	Ex1FormInterfaceControl control;

	control.m_bTransparent = true;
	control.SetType(Ex1FormInterfaceControl::TypeStatic);
   control.m_pruntimeclass = RUNTIME_CLASS(SimpleStatic);
	control.m_uiId = IDC_STATIC_SYNCH_DELAY;
   control.m_uiText = IDS_APP_OPTIONS_GENERAL_SYNCH_DELAY;
	control.AddFunction(Ex1FormInterfaceControl::FunctionStatic2);
	_001AddControl(control);

   control.m_uiId = IDC_EDIT_SYNCH_DELAY;
	control.SetType(Ex1FormInterfaceControl::TypeEdit);
   control.AddFunction(Ex1FormInterfaceControl::FunctionVmsDataEdit);
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleEdit);
	control.m_datakey = VMSDATAKEY(GlobalLyricsDelay);
   control.SetDataType(Ex1FormInterfaceControl::DataTypeNatural);
	_001AddControl(control);

	control.SetType(Ex1FormInterfaceControl::TypeCheckBox);
	control.m_uiId = IDC_CHECK_MRU;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	control.m_datakey = VMSDATAKEY(MRUEnable);
	_001AddControl(control);

   control.m_uiId = IDC_EDIT_MRU_COUNT;
	control.SetType(Ex1FormInterfaceControl::TypeEdit);
   control.AddFunction(Ex1FormInterfaceControl::FunctionVmsDataEdit);
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleEdit);
	control.m_datakey = VMSDATAKEY(MRUCount);
   control.SetDataType(Ex1FormInterfaceControl::DataTypeNatural);
	_001AddControl(control);

   control.m_uiId = IDC_EDIT_MRU_COUNT;
	control.SetType(Ex1FormInterfaceControl::TypeEdit);
   control.AddFunction(Ex1FormInterfaceControl::FunctionVmsDataEdit);
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleEdit);
	control.m_datakey = VMSDATAKEY(AutoRecordFolder);
   control.SetDataType(Ex1FormInterfaceControl::DataTypeNatural);
	_001AddControl(control);
}
