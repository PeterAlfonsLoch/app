#if !defined(AFX_ALBUMVIEW_H__5D141D18_C24C_46FB_A132_3266B9280CDB__INCLUDED_)
#define AFX_ALBUMVIEW_H__5D141D18_C24C_46FB_A132_3266B9280CDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlbumView.h : header file
//

class MediaLibraryDoc;

/////////////////////////////////////////////////////////////////////////////
// MediaLibraryListView view

class MediaLibraryListView :
	public SimpleListView
{
public:

   enum EFieldIndex
   {
      FieldIndexNone = -1,
      FieldIndexId = 0,
      FieldIndexTitle,
      FieldIndexArtist,
      FieldIndexFileName,
      FieldIndexFilePath,
   };

   enum ESubItem
   {
      SubItemId,
      SubItemTitle,
      SubItemArtist,
      SubItemFileName,
      SubItemFilePath,
   };

protected:
	MediaLibraryListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(MediaLibraryListView)

// Attributes
public:
   Ex1ListCache        m_cache;
   bool                 m_bKickActive;

   class BuildHelper
   {
   public:
      BuildHelper();
      int      m_iTopIndex;
      int      m_iDisplayItemCount;
      int      m_iStep;
      bool     m_bActive;
   };

   BuildHelper          m_buildhelper;

   static UINT AFX_CDECL ThreadProcFillTask(LPVOID lpParameter);

   class FillTask
   {
   public:
      //FillTask(MAlbumView * pview, LPCWSTR lpcsz);
//      MediaLibraryListView *      m_pview;
      WString             m_wstrFile;
      UINT              m_uiTimer;

   };


// Operations
public:
	void KickBuild(int iItem = -1);
	
	//void PostFillTask(WString & wstrFile, CTime & time);
   void PostFillTask(CString & wstrFile, UINT uiTimer);

	virtual void _001OnSort();
	bool GetSongPath(CString & wstr, int iItem);
	MediaLibraryDoc * GetDocument();

// Overrides
	virtual int _001GetItemImage(int iItem, int iSubItem, int iListItem);
	virtual void _001InsertColumns();
	virtual bool _001GetItemText(CString &wstr, int iItem, int iSubItem, int iListItem);
   virtual int _001GetItemCount();
   virtual bool _001SearchGetItemText(CString &wstr, int iItem, int iSubItem, int iListItem);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MediaLibraryListView)
	protected:
	virtual void OnUpdate(BaseView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~MediaLibraryListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(MediaLibraryListView)
	DECL_GEN_SIGNAL(_001OnLButtonDblClk)
	DECL_GEN_SIGNAL(_001OnTimer)
	DECL_GEN_SIGNAL(_001OnSize)
	DECL_GEN_SIGNAL(_001OnContextMenu)
	DECL_GEN_SIGNAL(_001OnAlbumExecutePlay)
	DECL_GEN_SIGNAL(_001OnUpdateAlbumExecutePlay)
	DECL_GEN_SIGNAL(_001OnExecutePrevious)
	DECL_GEN_SIGNAL(_001OnUpdateExecutePrevious)
	DECL_GEN_SIGNAL(_001OnExecuteNext)
	DECL_GEN_SIGNAL(_001OnUpdateExecuteNext)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
   DECL_GEN_SIGNAL(_001OnFillTaskResponse)

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALBUMVIEW_H__5D141D18_C24C_46FB_A132_3266B9280CDB__INCLUDED_)
