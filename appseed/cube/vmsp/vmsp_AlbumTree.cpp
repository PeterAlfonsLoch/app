#include "StdAfx.h"
#include "AlbumTree.h"


AlbumTree::AlbumTree(::ca::application * papp) :
   ca(papp),
   ::ca::data_container(papp),
   ::user::scroll_view(papp),
   ::user::tree(papp),
   ::userbase::tree_window(papp),
   ex1::tree(papp)
{
}

AlbumTree::~AlbumTree()
{
   RemoveAllItemSqlMap();

}


 // BEGIN_MESSAGE_MAP(AlbumTree, ::ca::window)
/*   //{{AFX_MSG_MAP(AlbumTree)
   ON_WM_CREATE()
   ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
   ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
   //}}AFX_MSG_MAP*/
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AlbumTree message handlers

int AlbumTree::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
//   if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
//      return -1;
//   ModifyStyleEx(0, WS_EX_CLIENTEDGE);

    CGroupDataV001 gdv001;
   string str;
//   str.load_string(IDS_ALBUM_PLAYLISTS);
//   m_hGroup1.m_hPlaylist = InsertItem(str, 2, 2);
  //  gdv001.m_hti 

   throw not_implemented_exception();
//   str.load_string(IDS_ALBUM_PLAYLISTS);
//   InsertItem(str, 2, 2);

  /*   gdv001.m_uiDisplayName = IDS_ALBUM_AUTHOR;
    gdv001.m_lpcszTable = CDBCentral::GetTableName(CDBCentral::eTableAuthor);
    gdv001.m_lpcszField = CDBSongSet::GetFieldName(CDBSongSet::FieldAuthor);
    gdv001.m_lpcszTableSong = CDBCentral::GetTableName(CDBCentral::eTableAuthorSong);
    gdv001.m_lpcszFieldSong = CDBSongSet::GetTableName();
    m_gdv001a.add(gdv001);

   gdv001.m_uiDisplayName = IDS_ALBUM_COPYRIGHT;
    gdv001.m_lpcszTable = CDBCentral::GetTableName(CDBCentral::eTableCopyright);
    gdv001.m_lpcszField = CDBSongSet::GetFieldName(CDBSongSet::FieldCopyright);
    gdv001.m_lpcszTableSong = CDBCentral::GetTableName(CDBCentral::eTableCopyrightSong);
    gdv001.m_lpcszFieldSong = CDBSongSet::GetTableName();
    m_gdv001a.add(gdv001);

    gdv001.m_uiDisplayName = IDS_ALBUM_COMPOSER;
    gdv001.m_lpcszTable = CDBCentral::GetTableName(CDBCentral::eTableComposer);
    gdv001.m_lpcszField = CDBSongSet::GetFieldName(CDBSongSet::FieldComposer);
    gdv001.m_lpcszTableSong = CDBCentral::GetTableName(CDBCentral::eTableComposerSong);
    gdv001.m_lpcszFieldSong = CDBSongSet::GetTableName();
    m_gdv001a.add(gdv001);

   gdv001.m_uiDisplayName = IDS_ALBUM_LYRICIST;
    gdv001.m_lpcszTable = CDBCentral::GetTableName(CDBCentral::eTableLyricist);
    gdv001.m_lpcszField = CDBSongSet::GetFieldName(CDBSongSet::FieldLyricist);
    gdv001.m_lpcszTableSong = CDBCentral::GetTableName(CDBCentral::eTableLyricistSong);
    gdv001.m_lpcszFieldSong = CDBSongSet::GetTableName();
    m_gdv001a.add(gdv001);

   gdv001.m_uiDisplayName = IDS_ALBUM_ARRANGER;
    gdv001.m_lpcszTable = CDBCentral::GetTableName(CDBCentral::eTableArranger);
    gdv001.m_lpcszField = CDBSongSet::GetFieldName(CDBSongSet::FieldArranger);
    gdv001.m_lpcszTableSong = CDBCentral::GetTableName(CDBCentral::eTableArrangerSong);
    gdv001.m_lpcszFieldSong = CDBSongSet::GetTableName();
    m_gdv001a.add(gdv001);

   gdv001.m_uiDisplayName = IDS_ALBUM_PERFORMER;
    gdv001.m_lpcszTable = CDBCentral::GetTableName(CDBCentral::eTablePerformer);
    gdv001.m_lpcszField = CDBSongSet::GetFieldName(CDBSongSet::FieldPerformer);
    gdv001.m_lpcszTableSong = CDBCentral::GetTableName(CDBCentral::eTablePerformerSong);
    gdv001.m_lpcszFieldSong = CDBSongSet::GetTableName();
    m_gdv001a.add(gdv001);

/*   gdv001.m_uiDisplayName = IDS_ALBUM_PROGRAMMER;
    gdv001.m_lpcszTable = CDBCentral::GetTableName(CDBCentral::eTableProgrammer);
    gdv001.m_lpcszField = CDBSongSet::GetFieldName(CDBSongSet::FieldProgrammer);
    gdv001.m_lpcszTableSong = CDBCentral::GetTableName(CDBCentral::eTableProgrammerSong);
    gdv001.m_lpcszFieldSong = CDBSongSet::GetTableName();
    m_gdv001a.add(gdv001);
*/
/*   gdv001.m_uiDisplayName = IDS_ALBUM_KEYWORD;
    gdv001.m_lpcszTable = CDBCentral::GetTableName(CDBCentral::eTableKeyword);
    gdv001.m_lpcszField = CDBSongSet::GetFieldName(CDBSongSet::FieldKeyword);
    gdv001.m_lpcszTableSong = CDBCentral::GetTableName(CDBCentral::eTableKeywordSong);
    gdv001.m_lpcszFieldSong = CDBSongSet::GetTableName();
    m_gdv001a.add(gdv001);*/
   //m_gGroup1.m_hKeyword = InsertItem(str, 2, 2);

   throw not_implemented_exception();
   /*
    for(int i = 0; i < m_gdv001a.get_size(); i++)
    {
        CGroupDataV001 & rgdv001 = m_gdv001a.element_at(i);
        str.load_string(rgdv001.m_uiDisplayName);
//        rgdv001.m_hti = InsertItem(str, 2, 2);
    }*/

   // TODO: add your specialized creation code here
   
   return 0;
}

void AlbumTree::UpdateTree()
{

   
   //CVMSApp * pApp = (CVMSApp *) &System;
/*    CDBCentral * pDataCentral = db();
   CDBSetV002 dbSet(DBDataCentral());
   HRESULT hr;
    string strSql;
   try
   {
      RemoveAllItemSqlMap();
//      DeleteChildren(m_hGroup1.m_hComposer);
      
        for(int i = 0; i < m_gdv001a.get_size(); i++)
        {
            AlbumTree::CGroupDataV001 & rgdv001 = m_gdv001a.element_at(i);
          strSql.Format("SELECT * FROM %s ORDER BY Text;", rgdv001.m_lpcszTable);
            hr = dbSet.open(
             pDataCentral->GetDataSource(),
             strSql);
//          SubdivideSet(rgdv001.m_lpcszTable, rgdv001.m_hti, &dbSet);
         PopulateTree(rgdv001.m_lpcszTable, rgdv001.m_hti, &dbSet);
          dbSet.close();
        }
      
/*        strSql = "SELECT * FROM Copyright ORDER BY Text;";
      hr = dbSet.open(
         pDataCentral->GetDataSource(),
         strSql);
      SubdivideSet("Copyright", m_hGroup1.m_hCopyright, &dbSet);
      dbSet.close();

        strSql = "SELECT * FROM Composer ORDER BY Text;";
      hr = dbSet.open(
         pDataCentral->GetDataSource(),
         strSql);
      SubdivideSet("Composer", m_hGroup1.m_hComposer, &dbSet);
      dbSet.close();
      
      strSql = "SELECT * FROM Lyricist ORDER BY Text;";
      DeleteChildren(m_hGroup1.m_hLyricist);
      hr = dbSet.open(
         pDataCentral->GetDataSource(),
         strSql);
      SubdivideSet("Lyricist", m_hGroup1.m_hLyricist, &dbSet);
      dbSet.close();

      strSql = "SELECT * FROM Arranger ORDER BY Text;";
      DeleteChildren(m_hGroup1.m_hArranger);
      hr = dbSet.open(
         pDataCentral->GetDataSource(),
         strSql);
      SubdivideSet("Arranger", m_hGroup1.m_hArranger, &dbSet);
      dbSet.close();

      strSql = "SELECT * FROM Performer ORDER BY Text;";
      DeleteChildren(m_hGroup1.m_hPerformer);
      hr = dbSet.open(
         pDataCentral->GetDataSource(),
         strSql);
      SubdivideSet("Performer", m_hGroup1.m_hPerformer, &dbSet);
      dbSet.close();

      strSql = "SELECT * FROM Programmer ORDER BY Text;";
      DeleteChildren(m_hGroup1.m_hProgrammer);
      hr = dbSet.open(
         pDataCentral->GetDataSource(),
         strSql);
      SubdivideSet("Programmer", m_hGroup1.m_hProgrammer, &dbSet);
      dbSet.close();
   
      strSql = "SELECT * FROM Keyword ORDER BY Text;";
      DeleteChildren(m_hGroup1.m_hKeyword);
      hr = dbSet.open(
         pDataCentral->GetDataSource(),
         strSql);
      SubdivideSet("Keyword", m_hGroup1.m_hKeyword, &dbSet);
      dbSet.close();*/

/*   } catch(COLEDBException *e)
   {
      CDBErrorDialog dlg;
      dlg.Init(e->m_spUnk, e->m_iid);
      dlg.DoModal();
      e->Delete();
      return;
   }
*/
}

BOOL AlbumTree::DeleteChildren(HTREEITEM hTreeItem)
{
/*   HTREEITEM hChild = GetChildItem(hTreeItem);
   while(hChild != NULL)
   {
      HTREEITEM hNextChild = GetNextSiblingItem(hChild);
      DeleteItem(hChild);
      hChild = hNextChild;
   }*/
   return TRUE;
}

void AlbumTree::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
   NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
   // TODO: add your control notification handler code here
//   Invalidate();
//   RedrawWindow(NULL, NULL,
//      RDW_NOERASE |
//      RDW_INTERNALPAINT |
//      RDW_INVALIDATE);
   *pResult = 0;
}

/*
void AlbumTree::SubdivideSet(
   const char * lpcszTable,
   HTREEITEM hParent, CDBSetV002 *pSet)
{
   if(!db()->IsWorking())
      return;
   stringa strArray;
   pSet->GetStringArray(&strArray);
   int iBundleSize = 10;
   double dLevelCount = log((double) strArray.get_size()) / log((double) iBundleSize);
   int iLevelCount = (int) dLevelCount;
   iBundleSize = (int) pow((double) iBundleSize, (double) iLevelCount / dLevelCount);
   SubdivideSet(
      lpcszTable,
      hParent,
      &strArray,
      0,
      strArray.get_size() - 1,
      iBundleSize,
      iLevelCount);

}*/

void AlbumTree::PopulateTree(
   stringa & stra,
   HTREEITEM hitemParent,
   const char * lpcszPrefix,
   int iLen,
   int iMaxBundleSize)
{
   stringa straPrefix;

   ASSERT(iLen >= 1);

/*   straPrefix.ExtractPrefixNoSortNoCase(stra, NULL, iLen, iLen);

   for(int i = 0; i < straPrefix.get_size(); i++)
   {
      HTREEITEM hitemChild = InsertItem(
         straPrefix[i],
         1, 1,
         hitemParent);

      if(stra.CountPrefixNoCase(straPrefix[i])
         >= iMaxBundleSize)
      {
         PopulateTree(
            stra,
            hitemChild,
            straPrefix[i],
            iLen + 1,
            iMaxBundleSize);
      }
   }
   */
}

/*
void AlbumTree::PopulateTree(
   const char * lpcszTable,
   HTREEITEM hitemParent,
   CDBSetV002 * pdbset)
{
   if(!db()->IsWorking())
      return;
   
   stringa stra;

   pdbset->GetStringArray(&stra);

   int iMaxBundleSize = 10;

   PopulateTree(
      stra,
      hitemParent,
      NULL,
      1,
      10);


}

*/

void AlbumTree::SubdivideSet(
   const char * lpcszTable,
   HTREEITEM hParent,
   stringa * lpstrArray,
   int iStartIndex,
   int iEndIndex,
   int iBundleSize,
   int iLevel)
{
   
   if(iLevel == 0)
   {
      int iIndex;
      for(iIndex = iStartIndex;
         iIndex <= iEndIndex &&
         iIndex < lpstrArray->get_size();
         iIndex++)
      {
/*         HTREEITEM hChild = InsertItem(
            lpstrArray->get_at(iIndex),
            1, 1,
            hParent);*/
      }
   }
   else
   {
      int iFirstIndex, iLastIndex; //, iIndex;
      int iPreFirstIndex, iPosLastIndex;
      int iPosFirstIndex, iPreLastIndex;
      string str;
      string strSql;
      string strFirst0, strLast0;
      string strFirstA, strLastA;
      string strFirst, strLast;
      string strPreFirst, strPosLast;
      string strPosFirst, strPreLast;
      iFirstIndex = iStartIndex;
      while(iFirstIndex <= iEndIndex)
      {
         iPreFirstIndex = iFirstIndex - 1;
         iPosFirstIndex = iFirstIndex + iBundleSize - 1;
//         iLastIndex = iFirstIndex + (int) pow(iBundleSize, iLevel) - 1;
         iPreLastIndex = iLastIndex - iBundleSize + 1;
         iPosLastIndex = iLastIndex + 1;
         if(iPosFirstIndex  >= lpstrArray->get_size())
            iPosFirstIndex = lpstrArray->get_size() - 1;
         if(iLastIndex >= lpstrArray->get_size())
            iLastIndex = lpstrArray->get_size() - 1;
         if(iPreLastIndex >= lpstrArray->get_size())
            iPreLastIndex = lpstrArray->get_size() - 1;
         if(iPosLastIndex >= lpstrArray->get_size())
            iPosLastIndex = lpstrArray->get_size() - 1;
         if(iPreFirstIndex >= 0)
            strPreFirst = lpstrArray->get_at(iPreFirstIndex);
         else
            strPreFirst ="";
         strFirst0 = lpstrArray->get_at(iFirstIndex);
         if(strFirst0.is_empty())
            strFirst0 = " ";
         strLast0 = lpstrArray->get_at(iLastIndex);
         if(strLast0.is_empty())
            strLast0 = " ";
         strPosFirst = lpstrArray->get_at(iPosFirstIndex);
         if(strPosFirst.is_empty())
            strPosFirst = " ";
         strPreLast = lpstrArray->get_at(iPreLastIndex);
         if(strPreLast.is_empty())
            strPreLast = " ";
         strPosLast = lpstrArray->get_at(iPosLastIndex);
         if(strPosLast.is_empty())
            strPosLast = " ";
         if(iPreFirstIndex >= 0)
         {
            strFirst = strFirst0;
            GetFirstDiff(strPreFirst, strFirst, strPosFirst);
         }
         else
         {
            strFirst = strFirst0;
            strLastA = strLast0;
            GetFirstDiff(strFirst, strPosFirst);
         }
         if(iPosLastIndex < lpstrArray->get_size())
         {
            strLast = strLast0;
            GetFirstDiff(strPreLast, strLast, strPosLast);
         }
         else
         {
            strFirstA = strFirst0;
            strLast = strLast0;
            GetFirstDiff(strPreLast, strLast);
         }
         strFirst.replace(" ", "");
         strLast.replace(" ", "");
         str.Format("%s - %s", strFirst, strLast);
         strFirstA = strFirst0;
         strLastA = strLast0;
/*         HTREEITEM hChild = InsertItem(
            str,
            3, 3,
            hParent);
         strFirstA.replace("'", "''");
         strLastA.replace("'", "''");
         strSql.Format(
            "%s.Text >= '%s' AND %s.Text <= '%s'",
            lpcszTable,
            strFirstA,
            lpcszTable,
            strLastA);
         AddItemSqlMapping(
            hChild,
            strSql);
         SubdivideSet(
            lpcszTable,
            hChild,
            lpstrArray,
            iFirstIndex,
            iLastIndex,
            iBundleSize,
            iLevel - 1);
         iFirstIndex = iLastIndex + 1;*/
      }
   }

}

void AlbumTree::GetFirstDiff(string &strA, string &strB)
{
   int i;
   strA.make_lower();
   strB.make_lower();
   for(i = 0; i < strA.get_length() && i < strB.get_length(); i++)
   {
      if(strA[i] == strB[i])
         continue;
      else
      {
         strA = strA.Left(i + 1);
         strB = strB.Left(i + 1);
         return;
      }
   }
   if(strA.get_length() > strB.get_length())
   {
      strA = strA.Left(strB.get_length());
   }
   else if(strB.get_length() > strA.get_length())
   {
      strB = strB.Left(strA.get_length());
   }
      

}

BOOL AlbumTree::PreCreateWindow(CREATESTRUCT& cs) 
{
   // TODO: add your specialized code here and/or call the base class
   cs.style = cs.style
      | WS_CHILD
      | WS_BORDER
      | WS_TABSTOP;
   cs.dwExStyle = cs.dwExStyle | WS_EX_CLIENTEDGE;
   return ::user::interaction::PreCreateWindow(cs);
}

HTREEITEM AlbumTree::FindItem(HTREEITEM hParent, const char * lpStr, BOOL bRecursive)
{
/*   HTREEITEM hItem = GetChildItem(hParent);
   while(hItem != NULL)
   {
      if(bRecursive)
      {
         HTREEITEM lhItem;
         lhItem = FindItem(hItem, lpStr, bRecursive);
         if(lhItem != NULL)
         {
            hItem = lhItem;
            break;
         }
      }
      if(GetItemText(hItem) == lpStr)
         break;
      hItem = GetNextSiblingItem(hItem);
   }*/
   //return hItem;
   return NULL;

}

void AlbumTree::GetFirstDiff(const string &cstrA, string &strB, const string &cstrC)
{
   string strA(cstrA), strC(cstrC);
   string strB1(strB), strB2(strB);
   
   GetFirstDiff(strA, strB1);
   GetFirstDiff(strB2, strC);
   strB = strB.Left(
      max(strA.get_length(),
      max(strB1.get_length(),
      max(strB2.get_length(),
      strC.get_length()))));

}

bool AlbumTree::IsItemDescendantOf(HTREEITEM hParent, HTREEITEM hItem)
{
   if(hItem == NULL)
      return false;
   if(hParent == NULL)
      return false;
   while(true)
   {
/*      hItem = GetParentItem(hItem);
      if(hItem == NULL)
         return false;
      if(hItem == hParent)
         return true;*/
      return true;
   }

}

BOOL AlbumTree::AddItemSqlMapping(HTREEITEM hItem, const string &lpData)
{
   string * pStr = new string(lpData);
   m_itemSqlMap.set_at(hItem, pStr);
   return TRUE;
}

BOOL AlbumTree::RemoveItemSqlMap(HTREEITEM hItem)
{
   string * pStr;
   if(m_itemSqlMap.Lookup(hItem, pStr))
   {
      m_itemSqlMap.RemoveKey(hItem);
      delete pStr;
      return TRUE;
   }
   return FALSE;
}

const char * AlbumTree::GetItemSqlMap(
   HTREEITEM hItem)
{
   string *pStr;
   if(m_itemSqlMap.Lookup(hItem, pStr))
      return *pStr;
   else
      return NULL;
}

BOOL AlbumTree::RemoveAllItemSqlMap()
{
   string *pStr;
   HTREEITEM hItem;
   POSITION pos = m_itemSqlMap.get_start_position();
   if(pos != NULL)
   {
      while(true)
      {
         m_itemSqlMap.get_next_assoc(pos, hItem, pStr);
         delete pStr;
         if(pos == NULL)
            break;
         
      }
   }
   m_itemSqlMap.remove_all();
   return TRUE;
}

void AlbumTree::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
   NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
   // TODO: add your control notification handler code here
   
   *pResult = 0;
}
