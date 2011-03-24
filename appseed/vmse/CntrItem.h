// CntrItem.h : interface of the CVmeCntrItem class
//

#if !defined(AFX_CNTRITEM_H__B042E500_8DD0_40E1_8E3F_73CB3FC20765__INCLUDED_)
#define AFX_CNTRITEM_H__B042E500_8DD0_40E1_8E3F_73CB3FC20765__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVmeDoc;
class CVmeView;

class CVmeCntrItem : public COleDocObjectItem
{
	DECLARE_SERIAL(CVmeCntrItem)

// Constructors
public:
	CVmeCntrItem(CVmeDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CVmeDoc* GetDocument()
		{ return (CVmeDoc*)COleDocObjectItem::GetDocument(); }
	CVmeView* GetActiveView()
		{ return (CVmeView*)COleDocObjectItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVmeCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	virtual BOOL CanActivate();
	//}}AFX_VIRTUAL

// Implementation
public:
	~CVmeCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__B042E500_8DD0_40E1_8E3F_73CB3FC20765__INCLUDED_)
