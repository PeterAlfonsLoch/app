#if !defined(AFX_VMSX173CTL_H__E69C49C0_CCD5_44E5_84D7_9EA9D794BC45__INCLUDED_)
#define AFX_VMSX173CTL_H__E69C49C0_CCD5_44E5_84D7_9EA9D794BC45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Vmsx173Ctl.h : Declaration of the CVmsx173Ctrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CVmsx173Ctrl : See Vmsx173Ctl.cpp for implementation.

class CVmsx173Ctrl : public COleControl
{
	DECLARE_DYNCREATE(CVmsx173Ctrl)

// Constructor
public:
	CVmsx173Ctrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmsx173Ctrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
public:
	~CVmsx173Ctrl();

	DECLARE_OLECREATE_EX(CVmsx173Ctrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CVmsx173Ctrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CVmsx173Ctrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CVmsx173Ctrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CVmsx173Ctrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CVmsx173Ctrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CVmsx173Ctrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CVmsx173Ctrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMSX173CTL_H__E69C49C0_CCD5_44E5_84D7_9EA9D794BC45__INCLUDED)
