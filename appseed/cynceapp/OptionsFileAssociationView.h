#if !defined(AFX_OPTIONSFILEASSOCIATIONFORM_H__66ECFDCF_5D92_4764_B29A_31995B1D79C7__INCLUDED_)
#define AFX_OPTIONSFILEASSOCIATIONFORM_H__66ECFDCF_5D92_4764_B29A_31995B1D79C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileAssociationForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileAssociationForm dialog

class OptionsFileAssociationView :
   public SimpleFormView
{
   DECLARE_DYNCREATE(OptionsFileAssociationView)

// Construction
public:
	OptionsFileAssociationView();   // standard constructor

// Dialog Data
	//{{AFX_DATA(OptionsFileAssociationView)
	enum { IDD = IDD_FILE_ASSOCIATIONS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
   virtual void _001InitializeFormPreData();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OptionsFileAssociationView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OptionsFileAssociationView)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSFILEASSOCIATIONFORM_H__66ECFDCF_5D92_4764_B29A_31995B1D79C7__INCLUDED_)
