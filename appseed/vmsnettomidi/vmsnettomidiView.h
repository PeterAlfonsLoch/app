// vmsnettomidiView.h : interface of the CVmsnettomidiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMSNETTOMIDIVIEW_H__590DB99E_C60B_4324_A168_E2177165F493__INCLUDED_)
#define AFX_VMSNETTOMIDIVIEW_H__590DB99E_C60B_4324_A168_E2177165F493__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class NetToMidiPoint;

class CVmsnettomidiView : public CFormView
{
protected: // create from serialization only
	CVmsnettomidiView();
	DECLARE_DYNCREATE(CVmsnettomidiView)

public:

   NetToMidiPoint * m_ppoint;

   
	//{{AFX_DATA(CVmsnettomidiView)
	enum { IDD = IDD_VMSNETTOMIDI_FORM };
	CIPAddressCtrl	m_ipaddressRemoteServer;
	UINT	m_uiLocalServerPort;
	UINT	m_uiRemoteServerPort;
	//}}AFX_DATA

// Attributes
public:
	CVmsnettomidiDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmsnettomidiView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool Call();
   bool Listen();
	void Stop();
	virtual ~CVmsnettomidiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVmsnettomidiView)
	afx_msg void OnUpdateActionStop(CCmdUI* pCmdUI);
	afx_msg void OnActionStop();
	afx_msg void OnChangeEditRemoteServerPort();
	afx_msg void OnChangeEditLocalServerPort();
	afx_msg void OnActionCall();
	afx_msg void OnUpdateActionCall(CCmdUI* pCmdUI);
	afx_msg void OnActionListen();
	afx_msg void OnUpdateActionListen(CCmdUI* pCmdUI);
	afx_msg void OnFieldchangedIpaddressRemoteServer(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in vmsnettomidiView.cpp
inline CVmsnettomidiDoc* CVmsnettomidiView::GetDocument()
   { return (CVmsnettomidiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMSNETTOMIDIVIEW_H__590DB99E_C60B_4324_A168_E2177165F493__INCLUDED_)
