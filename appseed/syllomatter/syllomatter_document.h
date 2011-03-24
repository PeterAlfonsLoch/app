#pragma once


/////////////////////////////////////////////////////////////////////////////
// syllomatter_document document

class CLASS_DECL_CA2_SYLLOMATTER syllomatter_document :
   public Document,
   public DBInterface,
   public VmsDataClientInterface
{
protected:
	syllomatter_document();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(syllomatter_document)

// Attributes
public:
   
   virtual void VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh);

// Operations
public:

public:
virtual void Serialize(CArchive& ar);   // overridden for document i/o
protected:
	virtual BOOL OnNewDocument();
public:
	virtual ~syllomatter_document();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   BOOL OnOpenDocument(LPCTSTR lpszPathName);

	// Generated message map functions
protected:
	//{{AFX_MSG(syllomatter_document)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

