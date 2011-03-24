// IpFrame.h : interface of the InPlaceFrame class
//
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class InlineFrame :
   public SimpleFrameWnd
{
	DECLARE_DYNCREATE(InlineFrame)
public:
	InlineFrame();

// Attributes
public:

// Operations
public:

   DECL_GEN_SIGNAL(_001OnEraseBkgnd)

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
	virtual ~InlineFrame();
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



