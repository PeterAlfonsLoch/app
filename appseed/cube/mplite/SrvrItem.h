// SrvrItem.h : interface of the MusicalPlayerLightServerItem class
//

#if !defined(AFX_SRVRITEM_H__6AB76FE4_1D2A_4A4F_ABF3_A8D42CC6D42D__INCLUDED_)
#define AFX_SRVRITEM_H__6AB76FE4_1D2A_4A4F_ABF3_A8D42CC6D42D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLASS_DECL_MPLITE MusicalPlayerLightServerItem : public OleServerItem
{
	DECLARE_DYNAMIC(MusicalPlayerLightServerItem)

// Constructors
public:
	MusicalPlayerLightServerItem(MusicalPlayerLightDoc* pContainerDoc);

// Attributes
	MusicalPlayerLightDoc* GetDocument() const
		{ return (MusicalPlayerLightDoc*)OleServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MusicalPlayerLightServerItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, size& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, size& rSize);
	//}}AFX_VIRTUAL

   void OnDoVerb(LONG iVerb);
   void OnShowInPlace();


// Implementation
public:
	~MusicalPlayerLightServerItem();
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

#endif // !defined(AFX_SRVRITEM_H__6AB76FE4_1D2A_4A4F_ABF3_A8D42CC6D42D__INCLUDED_)
