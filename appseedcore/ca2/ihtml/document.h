#pragma once

namespace ihtml
{
/////////////////////////////////////////////////////////////////////////////
// document document

class CLASS_DECL_CA2_IHTML document :
   public Document,
   public DBInterface,
   public VmsDataClientInterface
{
protected:
	document();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(document)

// Attributes
public:

   
   
   virtual document * get_document();
   virtual bergedge_application * get_app();
   virtual void VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh);

// Operations
public:

   virtual bool open_document(const char * pszPath);
public:
virtual void Serialize(CArchive& ar);   // overridden for document i/o
protected:
	virtual BOOL OnNewDocument();
public:
	virtual ~document();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   BOOL OnOpenDocument(LPCTSTR lpszPathName);

	// Generated message map functions
protected:
	//{{AFX_MSG(document)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   virtual bool _001OnUpdateCmdUi(CCmdUI * pcmdui);
   virtual bool _001OnCommand(UINT uiId);
};


} // namespace ihtml