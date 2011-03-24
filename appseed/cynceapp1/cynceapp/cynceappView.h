// cynceappView.h : interface of the CcynceappView class
//


#pragma once


class CcynceappView : public CFormView
{
protected: // create from serialization only
	CcynceappView();
	DECLARE_DYNCREATE(CcynceappView)

public:
	enum{ IDD = IDD_CYNCEAPP_FORM };

// Attributes
public:
	CcynceappDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CcynceappView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
   void GetHostIp(CString & strIp);
public:
   void UpdateHostIp(void);
public:
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in cynceappView.cpp
inline CcynceappDoc* CcynceappView::GetDocument() const
   { return reinterpret_cast<CcynceappDoc*>(m_pDocument); }
#endif

