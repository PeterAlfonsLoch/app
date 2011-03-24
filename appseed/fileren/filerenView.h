// filerenView.h : interface of the CFilerenView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILERENVIEW_H__1C690C86_7B57_49E8_B96E_83816228DB26__INCLUDED_)
#define AFX_FILERENVIEW_H__1C690C86_7B57_49E8_B96E_83816228DB26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFilerenView : public CFormView
{
protected: // create from serialization only
	CFilerenView();
	DECLARE_DYNCREATE(CFilerenView)

public:
	//{{AFX_DATA(CFilerenView)
	enum { IDD = IDD_FILEREN_FORM };
	CEdit	m_edit;
	//}}AFX_DATA

// Attributes
public:
	CFilerenDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilerenView)
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
	virtual ~CFilerenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFilerenView)
	afx_msg void OnButtonReplaceSpaceWithUnderscore();
	afx_msg void OnButtonMakeExtensionLowercase();
	afx_msg void OnButtonMove1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedButtonReplaceSpecial();
public:
   void ReplaceSpecial(String & str);
public:
   afx_msg void OnBnClickedButtonReplace();
public:
   CEdit m_editFind;
public:
   CEdit m_editReplace;
public:
   afx_msg void OnBnClickedEdit1Paste();
};

#ifndef _DEBUG  // debug version in filerenView.cpp
inline CFilerenDoc* CFilerenView::GetDocument()
   { return (CFilerenDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILERENVIEW_H__1C690C86_7B57_49E8_B96E_83816228DB26__INCLUDED_)
