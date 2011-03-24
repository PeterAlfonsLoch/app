#if !defined(AFX_APPMESSAGEWINDOW_H__034050B5_7B94_4AE1_BD8E_DC40BE236433__INCLUDED_)
#define AFX_APPMESSAGEWINDOW_H__034050B5_7B94_4AE1_BD8E_DC40BE236433__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppMessageWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppMessageWindow ::ca::window

class CAppMessageWindow : public ::ca::window
{
// Construction
public:
   CAppMessageWindow();

// Attributes
public:

// Operations
public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CAppMessageWindow)
   //}}AFX_VIRTUAL

// Implementation
public:
   virtual ~CAppMessageWindow();

   // Generated message ::collection::map functions
protected:
   //{{AFX_MSG(CAppMessageWindow)
      // NOTE - the ClassWizard will add and remove member functions here.
   //}}AFX_MSG
   ()

   afx_msg LRESULT OnAppMessage(WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPMESSAGEWINDOW_H__034050B5_7B94_4AE1_BD8E_DC40BE236433__INCLUDED_)
