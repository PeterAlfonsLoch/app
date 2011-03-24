#if !defined(AFX_VERIWELLKARAOKELIBRARYEXPLORERTREEVIEW_H__671F72D0_0944_4E8F_AF57_D02C0046A645__INCLUDED_)

#define AFX_VERIWELLKARAOKELIBRARYEXPLORERTREEVIEW_H__671F72D0_0944_4E8F_AF57_D02C0046A645__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// veriwellKaraokeLibraryExplorerTreeView.h : header file
//
class veriwellKaraokeLibraryExplorerView;


namespace _vmskar
{
enum EFolderType
{
   FolderTypeNormal,
   FolderTypeArtist,
};
class Folder
{
public:
   String m_strId;
   String m_strTitle;
   EFolderType m_etype;
   int m_iImage;
   int m_iImageSelected;
};

class FolderArray :
   public BaseArrayPtrAlloc < Folder, Folder & >
{
public:
	int FindAbsolute(LPCTSTR lpszId);
};
}
/////////////////////////////////////////////////////////////////////////////
// veriwellKaraokeLibraryExplorerTreeView view

class veriwellKaraokeLibraryExplorerTreeView :
   virtual public BaseView,
   virtual public Ex1TreeInterface
{
protected:
	veriwellKaraokeLibraryExplorerTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(veriwellKaraokeLibraryExplorerTreeView)

   void _001InstallMessageHandling(::igui::win::message::Dispatch * pdispatch);

// Attributes
public:

   veriwellKaraokeLibraryExplorerView *   m_pserver;
   _vmskar::FolderArray                            m_foldera; 

   void _001OnItemExpand(Ex1TreeDataItem *pitem);

   CSimpleWndRender        m_wndrender;
   //SimpleListHeaderCtrl    m_headerctrl;
   SimpleScrollBar         m_scrollbarVert;
   SimpleScrollBar         m_scrollbarHorz;

   virtual base_wnd * OnDrawInterfaceGetWnd();
   virtual WndRenderInterface * _GetWndRenderInterface();
   virtual base_wnd * _GetWnd();
   virtual bool TwiHasTranslucency();


   int   m_iIconFolderNormal;
   int   m_iIconFolderSelected;
   int   m_iIconArtistNormal;
   int   m_iIconArtistSelected;

// Operations
public:
	void Parse(LPCTSTR lpszParentId, LPCTSTR lpszSource);

   Ex1TreeDataItem * FindTreeItem(LPCTSTR lpszId);
   int _001GetItemImage(
   Ex1TreeDataItem * pitem,
   bool bSelected
   );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(veriwellKaraokeLibraryExplorerTreeView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~veriwellKaraokeLibraryExplorerTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(veriwellKaraokeLibraryExplorerTreeView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VERIWELLKARAOKELIBRARYEXPLORERTREEVIEW_H__671F72D0_0944_4E8F_AF57_D02C0046A645__INCLUDED_)

