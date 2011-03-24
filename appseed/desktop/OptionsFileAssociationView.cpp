// FileAssociationForm.cpp : implementation file
//

#include "stdafx.h"
#include "OptionsFileAssociationView.h"
#include "_vmspConfiguration.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(OptionsFileAssociationView, SimpleFormView)
/////////////////////////////////////////////////////////////////////////////
// OptionsFileAssociationView dialog


OptionsFileAssociationView::OptionsFileAssociationView() :
SimpleFormView(OptionsFileAssociationView::IDD),
BaseFormView(OptionsFileAssociationView::IDD)
{
   m_etranslucency = TranslucencyPresent;

//   ((CVmsDBApp *) AfxGetApp())->GetVmsDataServerInterface().AddClient(this);
	//{{AFX_DATA_INIT(OptionsFileAssociationView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void OptionsFileAssociationView::DoDataExchange(CDataExchange* pDX)
{
	SimpleFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OptionsFileAssociationView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OptionsFileAssociationView, SimpleFormView)
	//{{AFX_MSG_MAP(OptionsFileAssociationView)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OptionsFileAssociationView message handlers


void OptionsFileAssociationView::_001InitializeFormPreData()
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
