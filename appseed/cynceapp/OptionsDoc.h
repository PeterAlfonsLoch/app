#if !defined(AFX_OPTIONSDOC_H__98457005_713C_478D_ABCA_0373925EB741__INCLUDED_)
#define AFX_OPTIONSDOC_H__98457005_713C_478D_ABCA_0373925EB741__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OptionsDoc document

class OptionsDoc : public Document
{
protected:
	OptionsDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(OptionsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OptionsDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~OptionsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(OptionsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDOC_H__98457005_713C_478D_ABCA_0373925EB741__INCLUDED_)
