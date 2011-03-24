// vmsaudioprofileView.h : interface of the AudioProfileView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMSAUDIOPROFILEVIEW_H__363C298D_2D13_4023_BE24_84289D549395__INCLUDED_)
#define AFX_VMSAUDIOPROFILEVIEW_H__363C298D_2D13_4023_BE24_84289D549395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MixerMainView.h"

class AudioProfileView : public MixerMainView
{
protected: // create from serialization only
	AudioProfileView();
	DECLARE_DYNCREATE(AudioProfileView)

// Attributes
public:
	AudioProfileDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AudioProfileView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~AudioProfileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(AudioProfileView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in vmsaudioprofileView.cpp
inline AudioProfileDoc* AudioProfileView::GetDocument()
   { return (AudioProfileDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMSAUDIOPROFILEVIEW_H__363C298D_2D13_4023_BE24_84289D549395__INCLUDED_)
