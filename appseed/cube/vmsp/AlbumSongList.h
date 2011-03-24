#pragma once

class CLASS_DECL_CA2_CUBE AlbumSongList :
   public simple_list_view
{
public:
   //    critical_section m_cs;
   enum ESubItem
   {
      SubItemNull = -1,
      SubItemIcon = 10,
      SubItemDelete = 20,
      SubItemCode = 100,
      SubItemCountry = 110,
      SubItemName = 120,
      SubItemFileName = 130,
      SubItemAuthor =140,
      SubItemCopyright = 150,
      SubItemComposer = 160,
      SubItemLyricist = 170,
      SubItemArranger = 180,
      SubItemPerformer = 190,
      SubItemProgrammer = 200,
      SubItemPath = 210,
      SubItemKeyword = 220
   };

   LONG                 m_cnt;    
   bool                  m_bSortEnabled;
   string               m_str;
   string               m_strSql;
   int                  m_iNewColumnIndex;
   ::ca::graphics_sp      m_dcBuffer;
   ::ca::bitmap_sp      m_bmpBuffer;
   ::ca::bitmap *         m_pbmpBufferOld;
   ::ca::rgn_sp         m_rgnChildren;


   bool                 m_bFirstProgress;
   int                  m_iCacheNextIndex;
   bool                 m_bAutoMenuEnable;

   AlbumSongList(::ca::application * papp);
   virtual ~AlbumSongList();









   HRESULT OpenSongsSet(const char * lpSQL, bool bFindInterface);
   HRESULT OpenSongsSetIndexedOrdinal();
   HRESULT OpenSongsSetIndexedPath();

   virtual void _001InsertColumns();
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual int _001GetItemImage(int iItem, int iSubItem, int iListItem);
   virtual bool _001GetItemText(string & str, int iItem, int iSubItem, int iListItem);
   //void TwiOnDraw(::ca::graphics * pdc);
   //   string GetTextV001(CTaskAnnotation * ptasknote);
   //   bool WriteNotepadFile(CArchive & ar, CTaskAnnotation * ptasknote);
   BOOL UpdateChildrenClipRgn();
   void AddKey(int iKey);
   //   VMSRESULT Initialize(CDBSongSet * psetAsynch, CDBSongSet * psetSynch);
   VMSRESULT Initialize();
   VMSRESULT SetItemCountEx_(int iCount, DWORD dwFlags = LVSICF_NOINVALIDATEALL);
   void OnUpdateAlbumListHeaderItem(cmd_ui * pcmdui, int iColumn);
   void OnUpdateAlbumListHeaderItem(cmd_ui * pcmdui, ESubItem subItem);
   UINT GetColumnHeaderTextId(ESubItem esubitem);
   virtual UINT _001GetColumnTextId(int iColumn);
   VMSRESULT ToggleSubItem(ESubItem iSubItem);
   UINT GetPopupMenuID(UINT nID);
   void WINAPI ThreadProcOnContextMenu(void * lpParameter);
   BOOL DoCache(int iFrom, int iTo);
   BOOL SetWhereClause(const char * lpcszSql);
   BOOL SetWhereClause(int iMask, const char * lpcszSql);
   BOOL SetFromClause(const char * lpcszSql);
   BOOL SetSql(string & strSQL);

   //void DrawItem(LPDRAWITEMSTRUCT);

   virtual VMSRESULT UpdateList(dword_array * pdwaKeys = NULL);

   string m_strWhereClause;
   string m_strFromClause;
   dword_array      m_dwaQueryKeys;
   //    string m_strRegistrySection;

   afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnOdcachehint(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnContextMenu(::ca::window* pWnd, point point);
   afx_msg void OnAlbumListheaderArranger();
   afx_msg void OnUpdateAlbumListheaderArranger(cmd_ui * pcmdui);
   afx_msg void OnAlbumListheaderCode();
   afx_msg void OnUpdateAlbumListheaderCode(cmd_ui * pcmdui);
   afx_msg void OnAlbumListheaderComposer();
   afx_msg void OnUpdateAlbumListheaderComposer(cmd_ui * pcmdui);
   afx_msg void OnAlbumListheaderCountry();
   afx_msg void OnUpdateAlbumListheaderCountry(cmd_ui * pcmdui);
   afx_msg void OnAlbumListheaderLyricist();
   afx_msg void OnUpdateAlbumListheaderLyricist(cmd_ui * pcmdui);
   afx_msg void OnAlbumListheaderName();
   afx_msg void OnUpdateAlbumListheaderName(cmd_ui * pcmdui);
   afx_msg void OnAlbumListheaderPath();
   afx_msg void OnUpdateAlbumListheaderPath(cmd_ui * pcmdui);
   afx_msg void OnAlbumListheaderPerformer();
   afx_msg void OnUpdateAlbumListheaderPerformer(cmd_ui * pcmdui);
   afx_msg void OnAlbumListheaderProgrammer();
   afx_msg void OnUpdateAlbumListheaderProgrammer(cmd_ui * pcmdui);
   DECL_GEN_SIGNAL(_001OnDestroy)
      afx_msg void OnAlbumListheaderAuthor();
   afx_msg void OnUpdateAlbumListheaderAuthor(cmd_ui * pcmdui);
   afx_msg void OnAlbumListheaderCopyright();
   afx_msg void OnUpdateAlbumListheaderCopyright(cmd_ui * pcmdui);
   afx_msg void OnAlbumListheaderFilename();
   afx_msg void OnUpdateAlbumListheaderFilename(cmd_ui * pcmdui);
   afx_msg void OnPaint();
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg BOOL OnEraseBkgnd(::ca::graphics * pgraphics);
   afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg void OnHeaderCtrlItemChanging(NMHDR* pNMHDR, LRESULT* pResult);
};

