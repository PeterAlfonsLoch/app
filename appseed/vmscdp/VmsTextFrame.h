#if !defined(AFX_VMSTEXTFRAME_H__28FED51F_1AF8_456E_B12B_93AA4B984E70__INCLUDED_)
#define AFX_VMSTEXTFRAME_H__28FED51F_1AF8_456E_B12B_93AA4B984E70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VmsTextFrame.h : header file
//
#include "VmsGenFrameWnd.h"
#include "MenuBarV033.h"
#include "ToolBarV033.h"
#include "TransparentFrameWnd.h"
class CWndFrameworkV033;
/////////////////////////////////////////////////////////////////////////////
// CVmsTextFrame frame

class CVmsTextFrame :
	public CTransparentFrameWnd
{
	DECLARE_DYNCREATE(CVmsTextFrame)
protected:
	CVmsTextFrame();           // protected constructor used by dynamic creation

// Attributes
public:

protected:
//	CMenuBarV033		m_wndMenuBar;
//	CReBar				m_wndReBar;
	CToolBarV033		m_wndToolBarStandard;
	CStatusBar			m_wndStatusBar;
// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmsTextFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CVmsTextFrame();

	// Generated message map functions
	//{{AFX_MSG(CVmsTextFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMSTEXTFRAME_H__28FED51F_1AF8_456E_B12B_93AA4B984E70__INCLUDED_)
