// vmsmiditonetDoc.h : interface of the CVmsmiditonetDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMSMIDITONETDOC_H__93693BF0_2FE9_47A8_9F48_45C639FC9E5C__INCLUDED_)
#define AFX_VMSMIDITONETDOC_H__93693BF0_2FE9_47A8_9F48_45C639FC9E5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVmsmiditonetDoc : public CDocument
{
protected: // create from serialization only
	CVmsmiditonetDoc();
	DECLARE_DYNCREATE(CVmsmiditonetDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmsmiditonetDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVmsmiditonetDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVmsmiditonetDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VMSMIDITONETDOC_H__93693BF0_2FE9_47A8_9F48_45C639FC9E5C__INCLUDED_)
