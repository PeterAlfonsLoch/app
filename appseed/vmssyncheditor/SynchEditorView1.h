#if !defined(AFX_SYNCHEDITORVIEW1_H__891DA68F_499B_471B_AF2E_FD7E0E479DA4__INCLUDED_)
#define AFX_SYNCHEDITORVIEW1_H__891DA68F_499B_471B_AF2E_FD7E0E479DA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SynchEditorView1.h : header file
//

#include "BaseSplitView.h"
#include "KaraokeUtil.h"
#include "_vmsmusMicroke1.h"
#include "XFInfoHeaders.h"

class _vmssyncheditorDoc;
class CMidiTrackSelectDoc;
struct CreateContext;

/////////////////////////////////////////////////////////////////////////////
// CSynchEditorView1 view

class CSynchEditorView1
   :
   public BaseSplitView
{
protected:
	CSynchEditorView1();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSynchEditorView1)

// Attributes
public:
	_vmssyncheditorDoc* GetDocument();
	CMultiDocTemplate* m_pdoctemplateMidiTrackSelect;
   CMidiTrackSelectDoc * m_pdocMidiTrackSelect;


// Operations
public:
	void PrepareMidiLyrics();
   CWnd * CreateView(CreateContext* pContext, UINT nID);
   KaraokeUtil         m_karaokeutil;
   _vmsmusMicroke1      m_microke1;
   CXFInfoHeaders		m_xfInfoHeaders;
	MidiSequence & GetMidiSequence();
	bool OpenDocument(LPCTSTR lpcsz);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSynchEditorView1)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSynchEditorView1();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSynchEditorView1)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileInsert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in _vmssyncheditorView.cpp
inline _vmssyncheditorDoc* CSynchEditorView1::GetDocument()
   { return (_vmssyncheditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYNCHEDITORVIEW1_H__891DA68F_499B_471B_AF2E_FD7E0E479DA4__INCLUDED_)
