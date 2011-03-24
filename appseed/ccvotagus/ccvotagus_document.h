#pragma once


/////////////////////////////////////////////////////////////////////////////
// paint_document document

class CLASS_DECL_CA2_PAINT paint_document :
   public Document,
   public DBInterface,
   public VmsDataClientInterface
{
protected:
	paint_document();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(paint_document)

// Attributes
public:
   
   virtual ::paint::document * get_document();
   virtual void VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh);

// Operations
public:

   paint::document   m_document;

public:
virtual void Serialize(CArchive& ar);   // overridden for document i/o
protected:
	virtual BOOL OnNewDocument();
public:
	virtual ~paint_document();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   BOOL OnOpenDocument(LPCTSTR lpszPathName);

	// Generated message map functions
protected:
	//{{AFX_MSG(paint_document)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

