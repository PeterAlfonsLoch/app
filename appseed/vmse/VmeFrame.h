// VmeFrame.h : interface of the CVmeFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMEFRAME_H__FF30A79C_B111_4AD3_8E20_AD8596A8C430__INCLUDED_)
#define AFX_VMEFRAME_H__FF30A79C_B111_4AD3_8E20_AD8596A8C430__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVmeView;

class CVmeFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CVmeFrame)
public:
	CVmeFrame();

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmeFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVmeFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CVmeView* GetRightPane();
// Generated message map functions
protected:
	CToolBar m_wndToolBar;
	//{{AFX_MSG(CVmeFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMEFRAME_H__FF30A79C_B111_4AD3_8E20_AD8596A8C430__INCLUDED_)
