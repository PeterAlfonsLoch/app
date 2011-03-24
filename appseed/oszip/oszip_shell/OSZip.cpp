// OSZip.cpp : implementation file
//

#include "stdafx.h"
#include "OSZip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OSZip

IMPLEMENT_DYNCREATE(OSZip, CWnd)

OSZip::OSZip()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

OSZip::~OSZip()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void OSZip::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CWnd::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(OSZip, CWnd)
	//{{AFX_MSG_MAP(OSZip)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(OSZip, CWnd)
	//{{AFX_DISPATCH_MAP(OSZip)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IOSZip to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {E0280AE1-0C16-4E29-BFE6-AA8F98C903FD}
static const IID IID_IOSZip =
{ 0xe0280ae1, 0xc16, 0x4e29, { 0xbf, 0xe6, 0xaa, 0x8f, 0x98, 0xc9, 0x3, 0xfd } };

BEGIN_INTERFACE_MAP(OSZip, CWnd)
	INTERFACE_PART(OSZip, IID_IOSZip, Dispatch)
END_INTERFACE_MAP()

// {EB903F95-E909-4BA6-86CF-9BDFE4F5F9D5}
IMPLEMENT_OLECREATE(OSZip, "fontopus.OSZip", 0xeb903f95, 0xe909, 0x4ba6, 0x86, 0xcf, 0x9b, 0xdf, 0xe4, 0xf5, 0xf9, 0xd5)

/////////////////////////////////////////////////////////////////////////////
// OSZip message handlers
