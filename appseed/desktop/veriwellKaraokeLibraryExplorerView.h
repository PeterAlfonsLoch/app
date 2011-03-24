#if !defined(AFX_VERIWELLKARAOKELIBRARYEXPLORERVIEW_H__853960F2_8BEC_4777_A863_E62656CA4287__INCLUDED_)
#define AFX_VERIWELLKARAOKELIBRARYEXPLORERVIEW_H__853960F2_8BEC_4777_A863_E62656CA4287__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// veriwellKaraokeLibraryExplorerView.h : header file
//

//#include "vmsguibase/BaseSplitView.h"

class veriwellKaraokeLibraryExplorerTreeView;
class veriwellKaraokeLibraryListView;

/////////////////////////////////////////////////////////////////////////////
// veriwellKaraokeLibraryExplorerView view

class veriwellKaraokeLibraryExplorerView :
   public BaseSplitView
{
protected:
	veriwellKaraokeLibraryExplorerView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(veriwellKaraokeLibraryExplorerView)

// Attributes
public:

   CInternetSession * m_pinetsession;
   veriwellKaraokeLibraryExplorerTreeView * m_ptree;
   veriwellKaraokeLibraryListView * m_plist;

// Operations
public:
	void OpenSongFile(int iId, LPCSTR lpszFileName);
	void Request(LPCTSTR lpsz);
	void Start();
	void CreateViews();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(veriwellKaraokeLibraryExplorerView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~veriwellKaraokeLibraryExplorerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(veriwellKaraokeLibraryExplorerView)
	DECL_GEN_SIGNAL(_001OnCreate)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VERIWELLKARAOKELIBRARYEXPLORERVIEW_H__853960F2_8BEC_4777_A863_E62656CA4287__INCLUDED_)
