#if !defined(AFX_PLAYLISTLISTVIEW_H__7A1748B6_6F40_4614_A97E_1C3C4E59142C__INCLUDED_)
#define AFX_PLAYLISTLISTVIEW_H__7A1748B6_6F40_4614_A97E_1C3C4E59142C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlaylistListView.h : header file
//


class PlaylistDoc;
class PaneView;

/////////////////////////////////////////////////////////////////////////////
// PlaylistListView view

class PlaylistListView	:
	public SimpleFormListView,
   public Ex1VirtualGuieContainer
{
protected:
	PlaylistListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(PlaylistListView)

// Attributes
public:
   enum EMode
   {
      ModeMinimum    = 1,
      ModeNormal     = 2
   };

   Ex1ListCache         m_cache;
   HENHMETAFILE         m_enhmetafile;
   ENHMETAHEADER        m_emh;
   ::igui::Buffer       m_gdibuffer;
   ImageList            m_imagelistSubItemHover;
   ImageList            m_imagelistItemHover;
   ImageList            m_imagelistNormal;

	EMode		            m_emode;
protected:
	CString		         m_str;

// Attributes
public:
	PlaylistDoc * GetDocument() const;

// Operations
public:
   virtual void _001OnButtonAction(Ex1FormInterfaceControl &control);
	virtual void _001OnInitializeForm(Ex1FormInterfaceControl & control);
	virtual void _001InsertColumns();
	virtual void _001DrawBackground(CDC *pdc, LPRECT lprect);
	PaneView * GetParentPane();
	virtual bool _001OnRemoveItem(INT_PTR iItem);
	void _001OnDraw(CDC * pdc);
	void UpdateDrawingObjects();
	int _001GetItemImage(INT_PTR iItem, INT_PTR iSubItem, INT_PTR iListItem);
	EMode GetMode();

   void SetMode(EMode emode);
	
	virtual bool _001GetItemText(CString &wstr, INT_PTR iItem, INT_PTR iSubItem, INT_PTR iListItem);
   virtual int _001GetItemCount();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PlaylistListView)
	public:
   DECL_GEN_VSIGNAL(_001OnInitialUpdate)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~PlaylistListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual bool WndFrameworkDownUpGetUpEnable();
	virtual bool WndFrameworkDownUpGetDownEnable();
	virtual bool TransparentFrameWndDownUpGetDownEnable();
	virtual bool TransparentFrameWndDownUpGetUpEnable();

	// Generated message map functions
protected:
	//{{AFX_MSG(PlaylistListView)
	DECL_GEN_SIGNAL(_001OnLButtonDblClk)
	DECL_GEN_SIGNAL(_001OnContextMenu)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnEditRemove)
	DECL_GEN_SIGNAL(_001OnUpdateEditRemove)
	DECL_GEN_SIGNAL(_001OnPlaylistExecutePlay)
   DECL_GEN_SIGNAL(_001OnUpdatePlaylistExecutePlay)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in xfplayer4View.cpp
inline PlaylistDoc* PlaylistListView::GetDocument() const
   { return (PlaylistDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYLISTLISTVIEW_H__7A1748B6_6F40_4614_A97E_1C3C4E59142C__INCLUDED_)
