// npvmpDoc.h : interface of the CNpvmpDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPVMPDOC_H__162BEED6_96A0_47C3_AEC2_241D832C3366__INCLUDED_)
#define AFX_NPVMPDOC_H__162BEED6_96A0_47C3_AEC2_241D832C3366__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNpvmpDoc : public COleDocument
{
protected: // create from serialization only
	CNpvmpDoc();
	DECLARE_DYNCREATE(CNpvmpDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNpvmpDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNpvmpDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNpvmpDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CNpvmpDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NPVMPDOC_H__162BEED6_96A0_47C3_AEC2_241D832C3366__INCLUDED_)
