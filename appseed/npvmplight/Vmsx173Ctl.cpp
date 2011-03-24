// Vmsx173Ctl.cpp : Implementation of the CVmsx173Ctrl ActiveX Control class.

#include "stdafx.h"
#include "vmsx173.h"
#include "Vmsx173Ctl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CVmsx173Ctrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CVmsx173Ctrl, COleControl)
	//{{AFX_MSG_MAP(CVmsx173Ctrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CVmsx173Ctrl, COleControl)
	//{{AFX_DISPATCH_MAP(CVmsx173Ctrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CVmsx173Ctrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CVmsx173Ctrl, COleControl)
	//{{AFX_EVENT_MAP(CVmsx173Ctrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages
_GUID * CVmsx173Ctrl::GetPropPageIDs(unsigned long &)
{
	return NULL;
}
// TODO: Add more property pages as needed.  Remember to increase the count!


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CVmsx173Ctrl, "VMSX173.Vmsx173Ctrl.1",
	0x876acde5, 0x5fbb, 0x44f4, 0xbe, 0x85, 0xcf, 0x40, 0xd, 0x2f, 0x6d, 0x2f)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CVmsx173Ctrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DVmsx173 =
		{ 0x43559a4, 0xe37f, 0x4cf9, { 0xa7, 0x5d, 0xb3, 0xfb, 0x79, 0x11, 0xcb, 0x81 } };
const IID BASED_CODE IID_DVmsx173Events =
		{ 0xf1f44316, 0x6578, 0x4fb0, { 0xb9, 0xf3, 0x17, 0x3a, 0x63, 0xa6, 0xc8, 0x69 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwVmsx173OleMisc =
	OLEMISC_SIMPLEFRAME |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CVmsx173Ctrl, IDS_VMSX173, _dwVmsx173OleMisc)


/////////////////////////////////////////////////////////////////////////////
// CVmsx173Ctrl::CVmsx173CtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CVmsx173Ctrl

BOOL CVmsx173Ctrl::CVmsx173CtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_VMSX173,
			IDB_VMSX173,
			afxRegApartmentThreading,
			_dwVmsx173OleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CVmsx173Ctrl::CVmsx173Ctrl - Constructor

CVmsx173Ctrl::CVmsx173Ctrl()
{
	InitializeIIDs(&IID_DVmsx173, &IID_DVmsx173Events);

	EnableSimpleFrame();

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CVmsx173Ctrl::~CVmsx173Ctrl - Destructor

CVmsx173Ctrl::~CVmsx173Ctrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CVmsx173Ctrl::OnDraw - Drawing function

void CVmsx173Ctrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CVmsx173Ctrl::DoPropExchange - Persistence support

void CVmsx173Ctrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CVmsx173Ctrl::OnResetState - Reset control to default state

void CVmsx173Ctrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CVmsx173Ctrl::AboutBox - Display an "About" box to the user

void CVmsx173Ctrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_VMSX173);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CVmsx173Ctrl message handlers
