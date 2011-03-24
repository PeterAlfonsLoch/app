#if !defined(AFX_SYNCHEDITORTOKENLISTVIEW_H__8B6A61F4_660C_4235_9459_C9692A9640DB__INCLUDED_)
#define AFX_SYNCHEDITORTOKENLISTVIEW_H__8B6A61F4_660C_4235_9459_C9692A9640DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SynchEditorTokenListView.h : header file
//

#include "WStr.h"
#include "SimpleFormListView.h"


class _vmssyncheditorDoc;

/////////////////////////////////////////////////////////////////////////////
// CSynchEditorTokenListView view

class CSynchEditorTokenListView :
   public SimpleFormListView
{
protected:
	CSynchEditorTokenListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSynchEditorTokenListView)

// Attributes
public:

	_vmssyncheditorDoc* GetDocument();

// Operations
public:
	bool GetToken(int i, CString & str);
	bool SetToken(int i, LPCSTR lpcsz, VmsDataUpdateHint * puh = NULL);
	void _001OnClick(UINT uiFlags, CPoint point, int iItem, int iSubItem);
   bool _001GetItemText(WString &wstr, int iItem, int iSubItem, int iListItem);
	virtual void _001InsertColumns();



// Overrides
//	virtual bool VmsDataOnBeforeChange(int iConfigurationId, int iLine, int iColumn, COleVariant & var, VmsDataUpdateHint * puh);
	virtual void VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSynchEditorTokenListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSynchEditorTokenListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
   bool CSynchEditorTokenListView::_001OnMessageNotify(WPARAM wparam, LPARAM lparam, LRESULT & lresult);
protected:
	//{{AFX_MSG(CSynchEditorTokenListView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline _vmssyncheditorDoc* CSynchEditorTokenListView::GetDocument() // non-debug version is inline
{
	return (_vmssyncheditorDoc*)m_pDocument;
}
#endif // _DEBUG
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYNCHEDITORTOKENLISTVIEW_H__8B6A61F4_660C_4235_9459_C9692A9640DB__INCLUDED_)
