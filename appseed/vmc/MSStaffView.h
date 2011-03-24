#pragma once

class CMSDoc;

class CMSStaffView :
	public BaseScrollView,
	public DBInterface
{
public:
   CMSStaffView(::ca::application * papp);
public:

    CMSDoc * GetDocument();
    CCriticalSection					m_csGdi;
protected:
    bool								m_bOnSizeEnabled;
//    CBitmap								m_bmpSource;
//	CBitmap								m_bmpSourceOld;
//	CBitmap								m_bmpScaled;
//	CBitmap								m_bmpScaledOld;
//	CBitmap								m_bmpBack;
//	CBitmap								m_bmpBackOld;
	CBitmap								m_bmpBuffer;
	CBitmap								m_bmpBufferOld;
	CDC									m_dcScreen;
    CDC									m_dcBuffer;
    CFont                               m_fontSymbols;
//	CDC									m_dcSource;
//	CDC									m_dcScaled;
//	CDC									m_dcBack;
// Operations
public:
	void UpdateBuffer();
	void UpdateBufferImage(int cx, int cy);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSStaffView)
	public:
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMSStaffView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:
    void Render(BOOL bGdiLocked);
	void Render(LPRECT lpRect, BOOL bGdiLocked);
	void Render(CRgn *pRgn, BOOL bGdiLocked);

	// Generated message map functions
	//{{AFX_MSG(CMSStaffView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in xfplayer4View.cpp
inline CMSDoc* CMSStaffView::GetDocument()
   { return (CMSDoc*)m_pDocument; }
#endif

