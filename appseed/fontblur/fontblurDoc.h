// fontblurDoc.h : interface of the CFontblurDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONTBLURDOC_H__00DD1FCA_7B39_42D9_B79F_3DD557BFB013__INCLUDED_)
#define AFX_FONTBLURDOC_H__00DD1FCA_7B39_42D9_B79F_3DD557BFB013__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFontblurDoc : public CDocument
{
protected: // create from serialization only
	CFontblurDoc();
	DECLARE_DYNCREATE(CFontblurDoc)

// Attributes
public:
   int m_iVersion;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontblurDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetVersion();
	virtual ~CFontblurDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFontblurDoc)
	afx_msg void OnVersion1();
	afx_msg void OnVersion2();
	afx_msg void OnVersion3();
	afx_msg void OnUpdateVersion1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVersion2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVersion3(CCmdUI* pCmdUI);
	afx_msg void OnVersion4();
	afx_msg void OnUpdateVersion4(CCmdUI* pCmdUI);
	afx_msg void OnVersion5();
	afx_msg void OnUpdateVersion5(CCmdUI* pCmdUI);
	afx_msg void OnVersion6();
	afx_msg void OnUpdateVersion6(CCmdUI* pCmdUI);
	afx_msg void OnVersion7();
	afx_msg void OnUpdateVersion7(CCmdUI* pCmdUI);
	afx_msg void OnVersion8();
	afx_msg void OnUpdateVersion8(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTBLURDOC_H__00DD1FCA_7B39_42D9_B79F_3DD557BFB013__INCLUDED_)
