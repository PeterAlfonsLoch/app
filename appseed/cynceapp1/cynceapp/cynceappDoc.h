// cynceappDoc.h : interface of the CcynceappDoc class
//


#pragma once


class CcynceappDoc : public CDocument
{
protected: // create from serialization only
	CcynceappDoc();
	DECLARE_DYNCREATE(CcynceappDoc)

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
	virtual ~CcynceappDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


