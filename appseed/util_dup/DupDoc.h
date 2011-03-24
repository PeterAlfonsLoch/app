// DupDoc.h : interface of the DupDoc class
//


#pragma once


class DupDoc : public CDocument
{
protected: // create from serialization only
	DupDoc();
	DECLARE_DYNCREATE(DupDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~DupDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


