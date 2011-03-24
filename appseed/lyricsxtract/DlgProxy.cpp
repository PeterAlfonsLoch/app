// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "lyricsxtract.h"
#include "DlgProxy.h"
#include "lyricsXtractDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLyricsXtractDlgAutoProxy

IMPLEMENT_DYNCREATE(CLyricsXtractDlgAutoProxy, CCmdTarget)

CLyricsXtractDlgAutoProxy::CLyricsXtractDlgAutoProxy()
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
	ASSERT_KINDOF(CLyricsXtractDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CLyricsXtractDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CLyricsXtractDlgAutoProxy::~CLyricsXtractDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CLyricsXtractDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CLyricsXtractDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CLyricsXtractDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLyricsXtractDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CLyricsXtractDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ILyricsxtract to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {51C65CB1-8184-46FB-BE41-98AE332BD8A2}
static const IID IID_ILyricsxtract =
{ 0x51c65cb1, 0x8184, 0x46fb, { 0xbe, 0x41, 0x98, 0xae, 0x33, 0x2b, 0xd8, 0xa2 } };

BEGIN_INTERFACE_MAP(CLyricsXtractDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CLyricsXtractDlgAutoProxy, IID_ILyricsxtract, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {616A33DD-3530-4DAC-9E9F-9773E2A7966D}
IMPLEMENT_OLECREATE2(CLyricsXtractDlgAutoProxy, "Lyricsxtract.Application", 0x616a33dd, 0x3530, 0x4dac, 0x9e, 0x9f, 0x97, 0x73, 0xe2, 0xa7, 0x96, 0x6d)

/////////////////////////////////////////////////////////////////////////////
// CLyricsXtractDlgAutoProxy message handlers
