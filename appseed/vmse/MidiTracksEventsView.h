#if !defined(AFX_MIDITRACKSEVENTSVIEW_H__441F27E2_F527_4C16_A10D_20572FF382FA__INCLUDED_)
#define AFX_MIDITRACKSEVENTSVIEW_H__441F27E2_F527_4C16_A10D_20572FF382FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MidiTracksEventsView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMidiTracksEventsView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "BaseArray.h"
#include "MidiViewHelper.h"
#include "..\vmsgen\VMSException.h"	// Added by ClassView

class CMidiTrackEventsView;
class CMidiDoc;

class CMidiTracksEventsView :
	public CFormView,
	public CMidiViewHelper
{
protected:
	CMidiTracksEventsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMidiTracksEventsView)

// Form Data
public:
	//{{AFX_DATA(CMidiTracksEventsView)
	enum { IDD = IDV_MIDITRACKSEVENTS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
    //CMidiDoc * GetDocument();

protected:
    int m_iCurrentView;
  	void OnChangedView();
	void OnChangeView();
    CBaseArray<CMidiTrackEventsView *, CMidiTrackEventsView *> m_tracksViews;

// Operations
public:
	CMidiTrackEventsView * FindViewByTrackIndex(int iTrackIndex);
	CMidiTrackEventsView * FindViewByMidiTrackIndex(int iMidiTrackIndex);
	VMSRESULT CreateViews();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMidiTracksEventsView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMidiTracksEventsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMidiTracksEventsView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUG  // debug version in xfplayer4View.cpp
//inline CMidiDoc* CMidiTracksEventsView::GetDocument()
  // { return (CMidiDoc*)m_pDocument; }
#endif


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIDITRACKSEVENTSVIEW_H__441F27E2_F527_4C16_A10D_20572FF382FA__INCLUDED_)
