#if !defined(AFX_SYNCHEDITORMEDIAVIEW_H__8D06B642_6CD3_45FC_86B7_C861B2A8401E__INCLUDED_)
#define AFX_SYNCHEDITORMEDIAVIEW_H__8D06B642_6CD3_45FC_86B7_C861B2A8401E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SynchEditorMediaView.h : header file
//

#include "_vmsmediaplayMediaView.h"

/////////////////////////////////////////////////////////////////////////////
// SynchEditorMediaView view

class SynchEditorMediaView :
   public _vmsmediaplay::MediaView,
   public VmsDataClientInterface
{
protected:
	SynchEditorMediaView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(SynchEditorMediaView)

// Attributes
public:

// Operations
public:
   virtual void KaraokeGetPosition(_vmsmediai::Position & position);

// Overrides
	virtual void VmsDataOnAfterChange(int iConfigurationId, int iLine, int iColumn, VmsDataUpdateHint * puh);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SynchEditorMediaView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnUpdate(SimpleView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~SynchEditorMediaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(SynchEditorMediaView)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYNCHEDITORMEDIAVIEW_H__8D06B642_6CD3_45FC_86B7_C861B2A8401E__INCLUDED_)
