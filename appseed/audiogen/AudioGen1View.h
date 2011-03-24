#if !defined(AFX_AUDIOGEN1VIEW_H__5E61C22D_8CC1_4339_9B81_2F603289FC15__INCLUDED_)
#define AFX_AUDIOGEN1VIEW_H__5E61C22D_8CC1_4339_9B81_2F603289FC15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AudioGen1View.h : header file
//

#include "_vmsaudioWaveOut.h"
#include "AudioGen1.h"

/////////////////////////////////////////////////////////////////////////////
// CAudioGen1View form view


class CAudioGen1View : public CFormView
{
protected:
	CAudioGen1View();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAudioGen1View)

   _vmsaudio::WaveOut      *m_pwaveout;
   AudioGen                *m_paudiogen;

// Form Data
public:
	//{{AFX_DATA(CAudioGen1View)
	enum { IDD = IDD_AUDIOGEN_1 };
	double	m_dFreq;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudioGen1View)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAudioGen1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAudioGen1View)
	afx_msg void OnButtonApply();
	afx_msg void OnExecutePlay();
	afx_msg void OnExecuteStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUDIOGEN1VIEW_H__5E61C22D_8CC1_4339_9B81_2F603289FC15__INCLUDED_)
