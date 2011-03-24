#if !defined(AFX_PLAYLISTVIEW_H__F33C4413_90CA_4EC6_B82A_06B1F9FFEAAA__INCLUDED_)
#define AFX_PLAYLISTVIEW_H__F33C4413_90CA_4EC6_B82A_06B1F9FFEAAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlaylistView.h : header file
//

class PlaylistDoc;

/////////////////////////////////////////////////////////////////////////////
// CPlaylistView view

class CPlaylistView : public SimpleListView
{
protected:
	CPlaylistView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPlaylistView)

// Attributes
public:

// Operations
public:
	PlaylistDoc * GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlaylistView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPlaylistView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	virtual void _001InsertColumns();
	//{{AFX_MSG(CPlaylistView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYLISTVIEW_H__F33C4413_90CA_4EC6_B82A_06B1F9FFEAAA__INCLUDED_)
