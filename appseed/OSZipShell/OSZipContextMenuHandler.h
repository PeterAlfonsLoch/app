#if !defined(AFX_OSZIPCONTEXTMENUHANDLER_H__AEF6DCCE_5203_46E5_859C_8F1EC1D0D148__INCLUDED_)
#define AFX_OSZIPCONTEXTMENUHANDLER_H__AEF6DCCE_5203_46E5_859C_8F1EC1D0D148__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OSZipContextMenuHandler.h : header file
//

#include "ApplicationWindow.h"

/////////////////////////////////////////////////////////////////////////////
// OSZipContextMenuHandler window

class OSZipContextMenuHandler : public CCmdTarget
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
	CString GetMenuCommand(int i);
	int GetMenuCommandCount();
	virtual ~OSZipContextMenuHandler();

   CStringArray m_straFiles;



	// Generated message map functions
protected:
	//{{AFX_MSG(OSZipContextMenuHandler)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(OSZipContextMenuHandler)
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(OSZipContextMenuHandler)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

   BEGIN_INTERFACE_PART(ShellExtInit, IShellExtInit)
      STDMETHOD_(HRESULT, Initialize)(LPCITEMIDLIST pidlFolder, LPDATAOBJECT lpdobj, HKEY hkeyProgID);
   END_INTERFACE_PART(ShellExtInit)

   BEGIN_INTERFACE_PART(ContextMenu, IContextMenu)
      STDMETHOD_(HRESULT, QueryContextMenu)(HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
      STDMETHOD_(HRESULT, GetCommandString)(UINT idCommand, UINT uFlags, UINT * lpReserved, LPSTR pszName, UINT uMaxNameLen);
      STDMETHOD_(HRESULT, InvokeCommand)(LPCMINVOKECOMMANDINFO lpcmi);
   END_INTERFACE_PART(ContextMenu)


   // IShellExtInit
   //afx_msg HRESULT Initialize(LPCITEMIDLIST pidlFolder, LPDATAOBJECT lpdobj, HKEY hkeyProgID);

   // IContextMenu
   //afx_msg HRESULT QueryContextMenu(HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
   //afx_msg HRESULT GetCommandString(UINT idCommand, UINT uFlags, UINT * lpReserved, LPSTR pszName, UINT uMaxNameLen);
   //afx_msg HRESULT InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi);

   ApplicationWindow  m_window;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSZIPCONTEXTMENUHANDLER_H__AEF6DCCE_5203_46E5_859C_8F1EC1D0D148__INCLUDED_)
