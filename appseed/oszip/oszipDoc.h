// oszipDoc.h : interface of the COszipDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OSZIPDOC_H__3BAD18E4_4FC9_4EEA_95F4_E7FB7F1537FE__INCLUDED_)
#define AFX_OSZIPDOC_H__3BAD18E4_4FC9_4EEA_95F4_E7FB7F1537FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLASS_DECL_OSZIP COszipDoc : public CDocument
{
protected: // create from serialization only
	COszipDoc();
	DECLARE_DYNCREATE(COszipDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COszipDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COszipDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COszipDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(COszipDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSZIPDOC_H__3BAD18E4_4FC9_4EEA_95F4_E7FB7F1537FE__INCLUDED_)
