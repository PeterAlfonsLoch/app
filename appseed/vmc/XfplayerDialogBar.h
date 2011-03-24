#if !defined(AFX_XFPLAYERDIALOGBAR_H__9E15633F_33E7_46CE_B383_B5E952078FE1__INCLUDED_)
#define AFX_XFPLAYERDIALOGBAR_H__9E15633F_33E7_46CE_B383_B5E952078FE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XfplayerDialogBar.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CXfplayerDialogBar dialog

class CXfplayerDialogBar : public CDialogBar
{
// Construction
public:
//	double GetSliderPos();
//	inline CSliderCtrl * GetSliderCtrl();
//	void SetSliderPos(double rate);
	//CXfplayerDialogBar(base_wnd* pParent = NULL);   // standard constructor
	CXfplayerDialogBar();   // standard constructor

// Attributes
	BOOL		m_bSliderPressed;


// Dialog Data
	//{{AFX_DATA(CXfplayerDialogBar)
	enum { IDD = IDR_MAINFRAME };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXfplayerDialogBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXfplayerDialogBar)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XFPLAYERDIALOGBAR_H__9E15633F_33E7_46CE_B383_B5E952078FE1__INCLUDED_)
