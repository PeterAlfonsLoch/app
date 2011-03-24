// vrecDoc.h : interface of the VRecDocument class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VRECDOC_H__63D07C04_C423_441E_B681_D4B3325B06A3__INCLUDED_)
#define AFX_VRECDOC_H__63D07C04_C423_441E_B681_D4B3325B06A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vmsguibase/Document.h"


class VRecDocument : public Document
{
protected: // create from serialization only
	VRecDocument();
	DECLARE_DYNCREATE(VRecDocument)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VRecDocument)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VRecDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(VRecDocument)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VRECDOC_H__63D07C04_C423_441E_B681_D4B3325B06A3__INCLUDED_)
