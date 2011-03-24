// CntrItem.h : interface of the CNpvmpCntrItem class
//

#if !defined(AFX_CNTRITEM_H__DD1B1022_8A52_4401_B054_65014AB69D68__INCLUDED_)
#define AFX_CNTRITEM_H__DD1B1022_8A52_4401_B054_65014AB69D68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNpvmpDoc;
class CNpvmpView;

class CNpvmpCntrItem : public COleDocObjectItem
{
	DECLARE_SERIAL(CNpvmpCntrItem)

// Constructors
public:
	CNpvmpCntrItem(CNpvmpDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	BOOL FinishCreate(SCODE sc);
	CNpvmpDoc* GetDocument()
		{ return (CNpvmpDoc*)COleDocObjectItem::GetDocument(); }
	CNpvmpView* GetActiveView()
		{ return (CNpvmpView*)COleDocObjectItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNpvmpCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CNpvmpCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__DD1B1022_8A52_4401_B054_65014AB69D68__INCLUDED_)
