#if !defined(AFX_MIDITRACKEVENTSVIEW_H__FC90554F_C8E3_45EB_9AC9_0BC06A489E88__INCLUDED_)
#define AFX_MIDITRACKEVENTSVIEW_H__FC90554F_C8E3_45EB_9AC9_0BC06A489E88__INCLUDED_

#include "../vms/VMS.H"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MidiEventsView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMidiTrackEventsView view
#include "MidiViewHelper.h"
class CXfplayerDoc;

class CMidiDoc;
class CMidiDocHelper;
class CMidiEventBase;
class CMidiEventsNoteEdit;
class CMidiTracksEventsView;


class CMidiTrackEventsView :
	public CScrollView,
	public CMidiViewHelper
{
    friend class CMidiTracksEventsView;
protected:
	CMidiTrackEventsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMidiTrackEventsView)

// Attributes
public:
    //CMidiDoc * GetDocument();
    //CMidiDocHelper * GetMidiDocHelper();
    int             m_iMidiTrackIndex;
    int             m_iTrackIndex;
    
protected:
//    CPoint          m_ptScroll;
    inline CMidiEventsNoteEdit * GetNoteEdit();
    int             m_iRowHeight;
    int             m_iFocused;
    CMidiEventsNoteEdit * m_pNoteEdit;
    int             m_iPressed;
    

// Operations
public:
	int HitTestColumn(int ix, int iy);
	VMSRESULT ShowEditWindow(int iRow);
	VMSRESULT HideEditWindows();
	VMSRESULT GetItemText(CString & rstr, CMidiEventBase * lpEvent, int iCol);
	VMSRESULT GetViewSize(LPSIZE lpsize);
	VMSRESULT GetItemRect(LPRECT lprect,  int iRow, int iCol);
	int GetRowPositionOffset(int iy);
	int HitTestRow(int iy);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMidiTrackEventsView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    public:
	virtual void OnInitialUpdate();     // first time after construct
    protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
    virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); 
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMidiTrackEventsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMidiTrackEventsView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
    afx_msg LRESULT OnUserMessage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUG  // debug version in xfplayer4View.cpp
//inline CMidiDoc* CMidiTrackEventsView::GetDocument()
//   { return (CMidiDoc*)m_pDocument; }
#endif

inline CMidiEventsNoteEdit * CMidiTrackEventsView::GetNoteEdit()
{
    return m_pNoteEdit;
}
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIDITRACKEVENTSVIEW_H__FC90554F_C8E3_45EB_9AC9_0BC06A489E88__INCLUDED_)
