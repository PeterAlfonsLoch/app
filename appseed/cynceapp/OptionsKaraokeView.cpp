// FileAssociationForm.cpp : implementation file
//

#include "stdafx.h"
#include "OptionsKaraokeView.h"
#include "_vmspConfiguration.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(OptionsKaraokeView, SimpleFormView)
/////////////////////////////////////////////////////////////////////////////
// OptionsKaraokeView dialog


OptionsKaraokeView::OptionsKaraokeView() :
SimpleFormView(OptionsKaraokeView::IDD),
BaseFormView(OptionsKaraokeView::IDD)
{
//   ((CVmsDBApp *) AfxGetApp())->GetVmsDataServerInterface().AddClient(this);
	//{{AFX_DATA_INIT(OptionsKaraokeView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void OptionsKaraokeView::DoDataExchange(CDataExchange* pDX)
{
	SimpleFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OptionsKaraokeView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OptionsKaraokeView, SimpleFormView)
	//{{AFX_MSG_MAP(OptionsKaraokeView)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OptionsKaraokeView message handlers


void OptionsKaraokeView::_001InitializeFormPreData()
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
}
