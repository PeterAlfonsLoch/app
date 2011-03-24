#if !defined(AFX_VMSTEXTDOC_H__00C53311_54C3_4447_92E8_216088DC04FE__INCLUDED_)
#define AFX_VMSTEXTDOC_H__00C53311_54C3_4447_92E8_216088DC04FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VmsTextDoc.h : header file
//
#include <afxrich.h>
/////////////////////////////////////////////////////////////////////////////
// CVmsTextDoc document

class CVmsTextDoc : public CRichEditDoc
{
protected:
	CVmsTextDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CVmsTextDoc)

// Attributes
public:

	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo = NULL) const ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmsTextDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVmsTextDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CVmsTextDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMSTEXTDOC_H__00C53311_54C3_4447_92E8_216088DC04FE__INCLUDED_)
