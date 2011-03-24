// mk1expanderDoc.h : interface of the CMk1expanderDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MK1EXPANDERDOC_H__2BB3084E_2ECF_495B_A074_843430C3BA95__INCLUDED_)
#define AFX_MK1EXPANDERDOC_H__2BB3084E_2ECF_495B_A074_843430C3BA95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MemoryStorage;


class CMk1expanderDoc : public CDocument
{
protected: // create from serialization only
	CMk1expanderDoc();
	DECLARE_DYNCREATE(CMk1expanderDoc)

// Attributes
public:

// Operations
public:
   
   bool GetFile(LPCTSTR lpcszPath, MemoryStorage & storage);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMk1expanderDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMk1expanderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMk1expanderDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CMk1expanderDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MK1EXPANDERDOC_H__2BB3084E_2ECF_495B_A074_843430C3BA95__INCLUDED_)
