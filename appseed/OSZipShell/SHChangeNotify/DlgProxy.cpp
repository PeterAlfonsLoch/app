// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "SHChangeNotify.h"
#include "DlgProxy.h"
#include "SHChangeNotifyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSHChangeNotifyDlgAutoProxy

IMPLEMENT_DYNCREATE(CSHChangeNotifyDlgAutoProxy, CCmdTarget)

CSHChangeNotifyDlgAutoProxy::CSHChangeNotifyDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CSHChangeNotifyDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CSHChangeNotifyDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CSHChangeNotifyDlgAutoProxy::~CSHChangeNotifyDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CSHChangeNotifyDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CSHChangeNotifyDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CSHChangeNotifyDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSHChangeNotifyDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CSHChangeNotifyDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ISHChangeNotify to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {40840254-5504-42B6-B5F6-3C64EB4EBF52}
static const IID IID_ISHChangeNotify =
{ 0x40840254, 0x5504, 0x42b6, { 0xb5, 0xf6, 0x3c, 0x64, 0xeb, 0x4e, 0xbf, 0x52 } };

BEGIN_INTERFACE_MAP(CSHChangeNotifyDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CSHChangeNotifyDlgAutoProxy, IID_ISHChangeNotify, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {5BD1EB67-8B6B-4AFE-993C-3C40BFD01BA7}
IMPLEMENT_OLECREATE2(CSHChangeNotifyDlgAutoProxy, "SHChangeNotify.Application", 0x5bd1eb67, 0x8b6b, 0x4afe, 0x99, 0x3c, 0x3c, 0x40, 0xbf, 0xd0, 0x1b, 0xa7)

/////////////////////////////////////////////////////////////////////////////
// CSHChangeNotifyDlgAutoProxy message handlers
