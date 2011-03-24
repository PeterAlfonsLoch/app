#if !defined(AFX_OSZIPCONTEXTMENUHANDLER_H__95A1D7EC_ACDD_4464_AEBE_D27874192A7B__INCLUDED_)
#define AFX_OSZIPCONTEXTMENUHANDLER_H__95A1D7EC_ACDD_4464_AEBE_D27874192A7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OSZipContextMenuHandler.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OSZipContextMenuHandler window

class OSZipContextMenuHandler : public CWnd
{
DECLARE_DYNCREATE(OSZipContextMenuHandler)

// Construction
public:
	OSZipContextMenuHandler();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OSZipContextMenuHandler)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~OSZipContextMenuHandler();

	// Generated message map functions
protected:
	//{{AFX_MSG(OSZipContextMenuHandler)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
      DECLARE_OLECREATE(OSZipContextMenuHandler)
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(OSZipContextMenuHandler)
	afx_msg short teste(short xxx);
	afx_msg SCODE teste2(long l1, long l2);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

   HRESULT  Initialize(
    LPCITEMIDLIST pidlFolder,
    LPDATAOBJECT lpdobj,
    HKEY hkeyProgID);


   afx_msg SCODE QueryContextMenu(HMENU hMenu,
                                               UINT indexMenu,
                                               UINT idCmdFirst,
                                               UINT idCmdLast,
                                               UINT uFlags);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSZIPCONTEXTMENUHANDLER_H__95A1D7EC_ACDD_4464_AEBE_D27874192A7B__INCLUDED_)
