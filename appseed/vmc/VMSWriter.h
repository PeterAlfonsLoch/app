#pragma once

class CVMSWriter : public Document
{
public:
   CVMSWriter(::ca::application * papp);
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVMSWriter)
	public:
	virtual void Serialize(Ex1Archive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVMSWriter();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

