#pragma once

class CLASS_DECL_CAFX CHtmlEditDoc : public CDocument
{
public:
	// Construction
	CHtmlEditDoc();

	// Get the CHtmlEditView associated with this document
	virtual CHtmlEditView* GetView() const;

	// Open a URL into the view associated with this document
	virtual BOOL OpenURL(LPCTSTR lpszURL);

	// See if the associated view's WebBrowser control contains a 
	// document that has been modified by the user.
	virtual BOOL IsModified();

// Implementation
public:
	virtual ~CHtmlEditDoc();
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszFileName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszFileName);
	virtual BOOL OnNewDocument();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DECLARE_DYNCREATE(CHtmlEditDoc)
};

