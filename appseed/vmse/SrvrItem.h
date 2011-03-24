// SrvrItem.h : interface of the CVmeSrvrItem class
//

#if !defined(AFX_SRVRITEM_H__C72EE6B1_4213_4419_A2D3_0949B57B26C4__INCLUDED_)
#define AFX_SRVRITEM_H__C72EE6B1_4213_4419_A2D3_0949B57B26C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVmeSrvrItem : public CDocObjectServerItem
{
	DECLARE_DYNAMIC(CVmeSrvrItem)

// Constructors
public:
	CVmeSrvrItem(CVmeDoc* pContainerDoc);

// Attributes
	CVmeDoc* GetDocument() const
		{ return (CVmeDoc*)CDocObjectServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmeSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CVmeSrvrItem();
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

#endif // !defined(AFX_SRVRITEM_H__C72EE6B1_4213_4419_A2D3_0949B57B26C4__INCLUDED_)
