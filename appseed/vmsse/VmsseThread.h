#if !defined(AFX_VMSSETHREAD_H__7A749454_D9CC_49C8_B729_99AA4C90E172__INCLUDED_)
#define AFX_VMSSETHREAD_H__7A749454_D9CC_49C8_B729_99AA4C90E172__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VmsseThread.h : header file
//

#include "VMSException.h"
#include "RelationV001.h"
#include "DBClient.h"
#include "PointerInterface.h"

class COptionsDialog;
//class CDBCentral;

/////////////////////////////////////////////////////////////////////////////
// CVmsseThread thread

class CVmsseThread :
	public CWinThread,
	public CDBClient,
	public CPointerInterface<CVmsseThread>
{
	DECLARE_DYNCREATE(CVmsseThread)
protected:
	CVmsseThread();           // protected constructor used by dynamic creation

// Attributes
public:
    COptionsDialog * m_poptionsdlg;
    bool        m_bTaskDialogPendingShowCommand;
	CTypedPtrArray<CObArray, CWnd *> m_wndptra;

// Operations
public:
	bool InitializeDataCentral();
	LRESULT SendMessageToWindows(UINT message, WPARAM wParam, LPARAM lParam);
	bool ShowBuildAlbumTaskDialog();
	CImageList * MenuV033GetImageList();
	VMSRESULT MenuV033GetImageMap(CRelationV001<UINT, UINT, UINT, UINT> ** pprel);
	VMSRESULT MenuV033CreateImageMap();
    //CDBCentral *				    m_pdbcentral;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmsseThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CVmsseThread();

	// Generated message map functions
	//{{AFX_MSG(CVmsseThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

    afx_msg void OnVmsmV001(WPARAM wParam, LPARAM lParam );
    afx_msg void OnUserMessage(WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMSSETHREAD_H__7A749454_D9CC_49C8_B729_99AA4C90E172__INCLUDED_)
