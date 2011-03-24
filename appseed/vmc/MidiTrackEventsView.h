#pragma once

class CXfplayerDoc;

class CMidiDoc;
class MidiEventBase;
class CMidiEventsNoteEdit;
class CMidiTracksEventsView;


class CMidiTrackEventsView : public BaseScrollView
{
    friend class CMidiTracksEventsView;
public:
   CMidiTrackEventsView(::ca::application * papp);

   CMidiDoc * GetDocument();
   int             m_iMidiTrackIndex;
   int             m_iTrackIndex;
    
protected:
//    class point          m_ptScroll;
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
	VMSRESULT GetItemText(string & rstr, MidiEventBase * lpEvent, int iCol);
	VMSRESULT GetViewSize(LPSIZE lpsize);
	VMSRESULT GetItemRect(LPRECT lprect,  int iRow, int iCol);
	int GetRowPositionOffset(int iy);
	int HitTestRow(int iy);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMidiTrackEventsView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint);
    virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); 
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
	afx_msg void OnMouseMove(UINT nFlags, class point point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, class point point);
	afx_msg void OnLButtonUp(UINT nFlags, class point point);
	//}}AFX_MSG
    afx_msg LRESULT OnUserMessage(WPARAM wParam, LPARAM lParam);

	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUG  // debug version in xfplayer4View.cpp
inline CMidiDoc* CMidiTrackEventsView::GetDocument()
   { return (CMidiDoc*)m_pDocument; }
#endif

inline CMidiEventsNoteEdit * CMidiTrackEventsView::GetNoteEdit()
{
    return m_pNoteEdit;
}
