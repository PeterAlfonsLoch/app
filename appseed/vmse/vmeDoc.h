// vmeDoc.h : interface of the CVmeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMEDOC_H__AF70C333_219F_4688_A4FA_A697DB6739CC__INCLUDED_)
#define AFX_VMEDOC_H__AF70C333_219F_4688_A4FA_A697DB6739CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MidiDocHelper.h"

class CVmeSrvrItem;

class CVmeDoc :
   public COleServerDoc,
   public MidiDocHelper
{
protected: // create from serialization only
	CVmeDoc();
	DECLARE_DYNCREATE(CVmeDoc)

// Attributes
public:
	CVmeSrvrItem* GetEmbeddedItem()
		{ return (CVmeSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVmeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual CDocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);

// Generated message map functions
protected:
	//{{AFX_MSG(CVmeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CVmeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMEDOC_H__AF70C333_219F_4688_A4FA_A697DB6739CC__INCLUDED_)
