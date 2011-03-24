#if !defined(AFX_BITMAPWINDOW_H__3EFF0158_A827_4029_97C7_3B3B3D77D27B__INCLUDED_)
#define AFX_BITMAPWINDOW_H__3EFF0158_A827_4029_97C7_3B3B3D77D27B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BitmapWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBitmapWindow window

class CBitmapWindow : public base_wnd
{
// Construction
public:
	CBitmapWindow(UINT nIDBitmapResource);
	CBitmap			m_bitmap;
	string			m_strStatus;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapWindow)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetStatus(string &str);
	virtual ~CBitmapWindow();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBitmapWindow)
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPWINDOW_H__3EFF0158_A827_4029_97C7_3B3B3D77D27B__INCLUDED_)
