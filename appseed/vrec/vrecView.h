// vrecView.h : interface of the VRecView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VRECVIEW_H__BC8ABBBB_CAFB_4EC7_93A6_A59C5DD7001E__INCLUDED_)
#define AFX_VRECVIEW_H__BC8ABBBB_CAFB_4EC7_93A6_A59C5DD7001E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vmsguibase/BaseView.h"


class VRecView : public BaseView
{
protected: // create from serialization only
	VRecView();
	DECLARE_DYNCREATE(VRecView)

// Attributes
public:
	VRecDocument* GetDocument();

   enum EState
   {
      StateInitial,
      StatePlaying,
      StateRecording,
      

   };

   EState m_estate;

   audio::WaveRecorder * m_precorder;
   audio::WavePlayer * m_pplayer;
   //Ex1File * m_pfile;
   notsad::File   m_file;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VRecView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VRecView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(VRecView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   afx_msg void OnExecutePlay();
   afx_msg void OnExecuteRecord();
   afx_msg void OnExecuteStop();

   afx_msg void OnUpdateExecutePlay(CCmdUI * pcmdui);
   afx_msg void OnUpdateExecuteRecord(CCmdUI * pcmdui);
   afx_msg void OnUpdateExecuteStop(CCmdUI * pcmdui);

   afx_msg LRESULT OnPlayerEvent(WPARAM wparam, LPARAM lparam);
};

#ifndef _DEBUG  // debug version in vrecView.cpp
inline VRecDocument* VRecView::GetDocument()
   { return (VRecDocument*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VRECVIEW_H__BC8ABBBB_CAFB_4EC7_93A6_A59C5DD7001E__INCLUDED_)
