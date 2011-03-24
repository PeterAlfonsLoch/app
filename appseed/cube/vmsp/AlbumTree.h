#pragma once

class AlbumMainView;


class CLASS_DECL_CA2_CUBE AlbumTree :
   virtual public ::userbase::tree_window
{
   friend AlbumMainView;
public:
   class CGroupDataV001
   {
   public:
      HTREEITEM   m_hti;
      const char *     m_lpcszTable;
      const char *     m_lpcszField;
      const char *     m_lpcszTableSong;
      const char *     m_lpcszFieldSong;
      UINT        m_uiDisplayName;

   };

   critical_section                                   m_cs;
   base_array < CGroupDataV001, CGroupDataV001 & >    m_gdv001a;
   typed_pointer_map<CMapPtrToPtr, HTREEITEM, string *>    m_itemSqlMap;

   AlbumTree(::ca::application * papp);
   virtual ~AlbumTree();

   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


   const char * GetItemSqlMap(HTREEITEM hItem);
   BOOL RemoveItemSqlMap(HTREEITEM hItem);
   BOOL RemoveAllItemSqlMap();
   BOOL AddItemSqlMapping(HTREEITEM hItem, const string &lpData);
   bool IsItemDescendantOf(HTREEITEM hParent, HTREEITEM hDescendant);
   void GetFirstDiff(const string &strA, string &strB, const string &strC);
   HTREEITEM FindItem(HTREEITEM hParent, const char * lpStr, BOOL bRecursive);
   void GetFirstDiff(string &strA, string &strB);


   void PopulateTree(
      stringa & stra,
      HTREEITEM hitemParent,
      const char * lpcszPrefix,
      int iLen,
      int iMaxBundleSize);


   void SubdivideSet(
      const char * lpcszTable,
      HTREEITEM hParent,
      stringa * lpstrArray,
      int iStartIndex,
      int iEndIndex,
      int iBundleSize,
      int iLevel);
   BOOL DeleteChildren(HTREEITEM hTreeItem);
   void UpdateTree();

   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);


};

