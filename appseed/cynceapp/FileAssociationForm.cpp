// FileAssociationForm.cpp : implementation file
//

#include "stdafx.h"
#include "FileAssociationForm.h"
#include "_vmspConfiguration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileAssociationForm dialog


CFileAssociationForm::CFileAssociationForm(CWnd* pParent /*=NULL*/)
	: BaseForm(CFileAssociationForm::IDD, pParent)
{
//   ((CVmsDBApp *) AfxGetApp())->GetVmsDataServerInterface().AddClient(this);
	//{{AFX_DATA_INIT(CFileAssociationForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFileAssociationForm::DoDataExchange(CDataExchange* pDX)
{
	BaseForm::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileAssociationForm)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileAssociationForm, BaseForm)
	//{{AFX_MSG_MAP(CFileAssociationForm)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileAssociationForm message handlers


void CFileAssociationForm::_001InitializeFormPreData()
{
	Ex1FormInterfaceControl control;

/*	control.m_bTransparent = true;
	control.m_etype = Ex1FormInterfaceControl::TypeStatic;
	control.m_uiId = IDC_ST_FILE_EXTENSION;
	control.AddFunction(Ex1FormInterfaceControl::FunctionStatic);
	_001AddControl(control);*/


	control.SetType(Ex1FormInterfaceControl::TypeCheckBox);
	control.m_uiId = IDC_CHECK_MID;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	control.m_datakey = VMSDATAKEY(ForceMidRegistration);
	_001AddControl(control);

	control.SetType(Ex1FormInterfaceControl::TypeCheckBox);
	control.m_uiId = IDC_CHECK_KAR;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	control.m_datakey = VMSDATAKEY(ForceKarRegistration);
	_001AddControl(control);

	control.SetType(Ex1FormInterfaceControl::TypeCheckBox);
	control.m_uiId = IDC_CHECK_ST3;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	control.m_datakey = VMSDATAKEY(ForceSt3Registration);
	_001AddControl(control);

}
