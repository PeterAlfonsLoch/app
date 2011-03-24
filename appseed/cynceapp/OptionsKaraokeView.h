#if !defined(AFX_OPTIONSKARAOKEFORM_H__66ECFDCF_5D92_4764_B29A_31995B1D79C7__INCLUDED_)
#define AFX_OPTIONSKARAOKEFORM_H__66ECFDCF_5D92_4764_B29A_31995B1D79C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileAssociationForm.h : header file
//

//#include "guibase/SimpleFormView.h"

/////////////////////////////////////////////////////////////////////////////
// CFileAssociationForm dialog

class OptionsKaraokeView :
   public SimpleFormView
{
   DECLARE_DYNCREATE(OptionsKaraokeView)

// Construction
public:
	OptionsKaraokeView();   // standard constructor

// Dialog Data
	//{{AFX_DATA(OptionsKaraokeView)
	enum { IDD = IDD_OPTIONS_GENERAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
   virtual void _001InitializeFormPreData();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OptionsKaraokeView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OptionsKaraokeView)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSKARAOKEFORM_H__66ECFDCF_5D92_4764_B29A_31995B1D79C7__INCLUDED_)
