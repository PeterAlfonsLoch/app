#if !defined(AFX_MEDIALIBRARYEXPLORERVIEW_H__853960F2_8BEC_4777_A863_E62656CA4287__INCLUDED_)
#define AFX_MEDIALIBRARYEXPLORERVIEW_H__853960F2_8BEC_4777_A863_E62656CA4287__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MediaLibraryExplorerView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryExplorerView view

class MediaLibraryExplorerView :
   public BaseSplitView
{
protected:
	MediaLibraryExplorerView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(MediaLibraryExplorerView)

// Attributes
public:

// Operations
public:
	void CreateViews();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MediaLibraryExplorerView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~MediaLibraryExplorerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(MediaLibraryExplorerView)
	DECL_GEN_SIGNAL(_001OnCreate)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIALIBRARYEXPLORERVIEW_H__853960F2_8BEC_4777_A863_E62656CA4287__INCLUDED_)
