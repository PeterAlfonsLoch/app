// IpFrame.h : interface of the InPlaceFrame class
//

#if !defined(AFX_IPFRAME_H__965DDF3A_A32E_468D_9C32_CF38B213A72A__INCLUDED_)
#define AFX_IPFRAME_H__965DDF3A_A32E_468D_9C32_CF38B213A72A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class InPlaceChildFrame :
   public BaseFrameWnd
{
	DECLARE_DYNCREATE(InPlaceChildFrame)
public:
	InPlaceChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InPlaceFrame)
	public:
	virtual BOOL OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~InPlaceChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//SimpleToolBar    m_wndToolBar;
	//CDialogBar m_wndDlgBar;
	//CReBar m_wndReBar;
	//COleDropTarget	m_dropTarget;
	//COleResizeBar   m_wndResizeBar;

// Generated message map functions
protected:
	//{{AFX_MSG(InPlaceFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class InPlaceFrame :
   public OleIPFrameWnd
{
	DECLARE_DYNCREATE(InPlaceFrame)
public:
	InPlaceFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InPlaceFrame)
	public:
	virtual BOOL OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~InPlaceFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//SimpleToolBar    m_wndToolBar;
	//CDialogBar m_wndDlgBar;
	//CReBar m_wndReBar;
	//COleDropTarget	m_dropTarget;
	//COleResizeBar   m_wndResizeBar;

// Generated message map functions
protected:
	//{{AFX_MSG(InPlaceFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPFRAME_H__965DDF3A_A32E_468D_9C32_CF38B213A72A__INCLUDED_)
