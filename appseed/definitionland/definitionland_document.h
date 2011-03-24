#pragma once


/////////////////////////////////////////////////////////////////////////////
// definitionland_document document

class CLASS_DECL_CA2_DEFINITIONLAND definitionland_document :
   public Document,
   public DBInterface,
   public VmsDataClientInterface
{
protected:
	definitionland_document();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(definitionland_document)

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
	virtual ~definitionland_document();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   BOOL OnOpenDocument(LPCTSTR lpszPathName);

	// Generated message map functions
protected:
	//{{AFX_MSG(definitionland_document)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

