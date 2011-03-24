// WaitMessageDialog.cpp : implementation file
//

#include "stdafx.h"
#include "WaitMessageDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WaitMessageDialog dialog


WaitMessageDialog::WaitMessageDialog(base_wnd* pParent /*=NULL*/)
	: BaseForm(WaitMessageDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(WaitMessageDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

WaitMessageDialog::WaitMessageDialog(LPCWSTR lpcszMessage, UINT uiDelay)
	: BaseForm(WaitMessageDialog::IDD, NULL)
{
   m_wstrMessage = lpcszMessage;
   m_uiDelay = uiDelay;
}


void WaitMessageDialog::DoDataExchange(CDataExchange* pDX)
{
	BaseForm::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WaitMessageDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(WaitMessageDialog, BaseForm)
	//{{AFX_MSG_MAP(WaitMessageDialog)
	ON_BN_CLICKED(ID_CONTINUE, OnContinue)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WaitMessageDialog message handlers

void WaitMessageDialog::OnContinue() 
{
   EndModalLoop(ID_CONTINUE);
}

int WaitMessageDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (BaseForm::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void WaitMessageDialog::OnTimer(UINT nIDEvent) 
{
   if(nIDEvent == 0)
   {
      UpdateTimeout();
      if(GetTickCount() - m_uiStartTime > m_uiDelay)
      {
         KillTimer(nIDEvent);
         EndModalLoop(ID_CONTINUE);
      }
   }
   	
	BaseForm::OnTimer(nIDEvent);
}

BOOL WaitMessageDialog::OnInitDialog() 
{
	BaseForm::OnInitDialog();

   String str;

   International::UnicodeToACP(str, m_wstrMessage);

   GetDlgItem(IDC_EDIT_MESSAGE)->SetWindowText(str);

   

   m_uiStartTime = GetTickCount();
	
   SetTimer(0, 100, NULL);	

   UpdateTimeout();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void WaitMessageDialog::UpdateTimeout()
{
   String str;

   str.Format("%0.0fs", (m_uiDelay - (GetTickCount() - m_uiStartTime)) / 1000.0);

   GetDlgItem(IDC_EDIT_TIMEOUT)->SetWindowText(str);

}

void WaitMessageDialog::OnClose() 
{
   EndModalLoop(ID_CANCEL);
}

void WaitMessageDialog::OnCancel() 
{
	EndModalLoop(ID_CANCEL);
}


void WaitMessageDialog::_001InitializeFormPreData()
{
	Ex1FormInterfaceControl control;

//	control.m_bTransparent = true;
   control.m_uiId = IDC_STATIC_ICON;
   control.m_pruntimeclass = RUNTIME_CLASS(SimpleStatic);
	control.SetType(Ex1FormInterfaceControl::TypeStatic);
	control.AddFunction(Ex1FormInterfaceControl::FunctionStatic);
	_001AddControl(control);

   control.m_uiId = IDC_EDIT_MESSAGE;
	control.SetType(Ex1FormInterfaceControl::TypeEdit);
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleEdit);
//	control.m_datakey = VMSDATAKEY_VMPLIGHT(BackgroundImageChangeSecondsHint);
//   control.SetDataType(Ex1FormInterfaceControl::DataTypeNatural);
	_001AddControl(control);

   control.m_uiId = IDC_EDIT_TIMEOUT;
	control.SetType(Ex1FormInterfaceControl::TypeEdit);
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleEdit);
//	control.m_datakey = VMSDATAKEY_VMPLIGHT(BackgroundImageChangeSecondsHint);
//   control.SetDataType(Ex1FormInterfaceControl::DataTypeNatural);
	_001AddControl(control);

	/*control.SetType(Ex1FormInterfaceControl::TypeCheckBox);
	control.m_uiId = IDC_CHECK_MRU;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	control.m_datakey = VMSDATAKEY_VMPLIGHT(MRUEnable);
	_001AddControl(control);

	control.SetType(Ex1FormInterfaceControl::TypeEdit);
	control.m_uiId = IDC_EDIT_MRU_COUNT;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleEdit);
	control.m_datakey = VMSDATAKEY_VMPLIGHT(MRUCount);
   control.SetDataType(Ex1FormInterfaceControl::DataTypeNatural);
	_001AddControl(control);*/

	control.m_uiId = ID_CONTINUE;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	_001AddControl(control);

	control.m_uiId = ID_CANCEL;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	_001AddControl(control);

}
