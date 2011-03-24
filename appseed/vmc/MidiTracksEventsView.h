#pragma once

#include "VMS_.H"	// Added by ClassView
#include "resource.H"	// Added by ClassView

class CMidiTrackEventsView;
class CMidiDoc;

class CMidiTracksEventsView : public CFormView
{
protected:
	CMidiTracksEventsView();           // protected constructor used by dynamic creation
public:
	//{{AFX_DATA(CMidiTracksEventsView)
	enum { IDD = IDD_MIDITRACKSEVENTS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
    CMidiDoc * GetDocument();

protected:
    int m_iCurrentView;
  	void OnChangedView();
	void OnChangeView();
    BaseArray<CMidiTrackEventsView *, CMidiTrackEventsView *> m_tracksViews;

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
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(View* pSender, LPARAM lHint, base_object* pHint);
protected:
	virtual ~CMidiTracksEventsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUG  // debug version in xfplayer4View.cpp
inline CMidiDoc* CMidiTracksEventsView::GetDocument()
   { return (CMidiDoc*)m_pDocument; }
#endif
