// SrvrItem.h : interface of the CVmcSrvrItem class
//

#if !defined(AFX_SRVRITEM_H__9DEA8746_BEDC_4888_B0BC_05CB4A807BBD__INCLUDED_)
#define AFX_SRVRITEM_H__9DEA8746_BEDC_4888_B0BC_05CB4A807BBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVmcSrvrItem : public CDocObjectServerItem
{
	DECLARE_DYNAMIC(CVmcSrvrItem)

// Constructors
public:
	CVmcSrvrItem(CVmcDoc* pContainerDoc);

// Attributes
	CVmcDoc* GetDocument() const
		{ return (CVmcDoc*)CDocObjectServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmcSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, class size& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, class size& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CVmcSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVRITEM_H__9DEA8746_BEDC_4888_B0BC_05CB4A807BBD__INCLUDED_)
