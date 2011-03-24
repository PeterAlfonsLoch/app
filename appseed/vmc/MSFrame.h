#pragma once

class CMSFrame : public SimpleMDIChildWindow
{
public:
   CMSFrame(::ca::application * papp);

// Attributes
public:

// Operations
public:

protected:
	virtual ~CMSFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	// Generated message map functions
	//{{AFX_MSG(CMSFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};
