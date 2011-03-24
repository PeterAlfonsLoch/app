#include "StdAfx.h"
#include "AlbumSongList.h"

AlbumSongList::AlbumSongList(::ca::application * papp) :
   ca(papp),
   ::user::form(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::user::list(papp),
   ::user::form_list(papp),
   ::userbase::form_list(papp),
   simple_list_view(papp),
   m_bmpBuffer(papp),
   m_dcBuffer(papp),
   m_rgnChildren(papp)
{
   m_iCacheNextIndex = 0;
//    m_pSongsSetAsynch = NULL;
    //m_pSongsSetSynch = NULL;
    m_bAutoMenuEnable = true;
    m_bSortEnabled = true;
    m_iNewColumnIndex = 1;
    m_rgnChildren->CreateRectRgn(0, 0, 0, 0);
}

AlbumSongList::~AlbumSongList()
{
/*   CDBSongRowBase *pSongBase;
   for(int i = m_cacheArray.get_size(); --i >=0 ;)
   {
      pSongBase = m_cacheArray[i];
      delete pSongBase;
   }
   if(m_pSongsSetAsynch != NULL)
      delete m_pSongsSetAsynch;
   if(m_pSongsSetSynch != NULL)
      delete m_pSongsSetSynch;

      */
}


 // BEGIN_MESSAGE_MAP(AlbumSongList, simple_list_view)
   //{{AFX_MSG_MAP(AlbumSongList)
   /*ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
   ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
   ON_NOTIFY_REFLECT(LVN_ODCACHEHINT, OnOdcachehint)
   ON_WM_CREATE()
   ON_WM_CONTEXTMENU()
   ON_WM_INITMENUPOPUP()
   ON_COMMAND(ID_ALBUM_LISTHEADER_ARRANGER, OnAlbumListheaderArranger)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_LISTHEADER_ARRANGER, OnUpdateAlbumListheaderArranger)
   ON_COMMAND(ID_ALBUM_LISTHEADER_CODE, OnAlbumListheaderCode)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_LISTHEADER_CODE, OnUpdateAlbumListheaderCode)
   ON_COMMAND(ID_ALBUM_LISTHEADER_COMPOSER, OnAlbumListheaderComposer)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_LISTHEADER_COMPOSER, OnUpdateAlbumListheaderComposer)
   ON_COMMAND(ID_ALBUM_LISTHEADER_COUNTRY, OnAlbumListheaderCountry)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_LISTHEADER_COUNTRY, OnUpdateAlbumListheaderCountry)
   ON_COMMAND(ID_ALBUM_LISTHEADER_LYRICIST, OnAlbumListheaderLyricist)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_LISTHEADER_LYRICIST, OnUpdateAlbumListheaderLyricist)
   ON_COMMAND(ID_ALBUM_LISTHEADER_NAME, OnAlbumListheaderName)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_LISTHEADER_NAME, OnUpdateAlbumListheaderName)
   ON_COMMAND(ID_ALBUM_LISTHEADER_PATH, OnAlbumListheaderPath)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_LISTHEADER_PATH, OnUpdateAlbumListheaderPath)
   ON_COMMAND(ID_ALBUM_LISTHEADER_PERFORMER, OnAlbumListheaderPerformer)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_LISTHEADER_PERFORMER, OnUpdateAlbumListheaderPerformer)
   ON_COMMAND(ID_ALBUM_LISTHEADER_PROGRAMMER, OnAlbumListheaderProgrammer)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_LISTHEADER_PROGRAMMER, OnUpdateAlbumListheaderProgrammer)
   ON_WM_DESTROY()
   ON_COMMAND(ID_ALBUM_LISTHEADER_AUTHOR, OnAlbumListheaderAuthor)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_LISTHEADER_AUTHOR, OnUpdateAlbumListheaderAuthor)
   ON_COMMAND(ID_ALBUM_LISTHEADER_COPYRIGHT, OnAlbumListheaderCopyright)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_LISTHEADER_COPYRIGHT, OnUpdateAlbumListheaderCopyright)
   ON_COMMAND(ID_ALBUM_LISTHEADER_FILENAME, OnAlbumListheaderFilename)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_LISTHEADER_FILENAME, OnUpdateAlbumListheaderFilename)
   ON_WM_PAINT()
   ON_WM_SIZE()
   ON_WM_ERASEBKGND()
   ON_WM_DRAWITEM()
   ON_WM_HSCROLL()
   ON_WM_VSCROLL()
   //}}AFX_MSG_MAP
    ON_NOTIFY(HDN_ITEMCHANGING, IDC_LIST_HEADER, OnHeaderCtrlItemChanging)*/
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AlbumSongList message handlers

void AlbumSongList::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
   NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
   // TODO: add your control notification handler code here
   
    if(!m_bSortEnabled)
    {
        *pResult = 0;
        return;
    }


    ESubItem subItem;
    subItem = (ESubItem) _001MapOrderToSubItem(pNMListView->iSubItem);

/*    CDBSongRowBase::Field iColumnIndex;
    MapSubItemToField(iColumnIndex, subItem);
    m_bFirstProgress = true;
   m_dwaQueryKeys.remove_all();
   m_cacheMap.remove_all();
   m_pSongsSetAsynch->Sort(iColumnIndex, true);
    
    
    HRESULT hr;
    if(SUCCEEDED(hr = m_pSongsSetAsynch->m_spRowset->QueryInterface(IID_IDBAsynchStatus, (void **)&m_spIdbas)))
    {
        Populate(m_spIdbas);
    }
    else
    {

        AddRef();
       CComPtr<IConnectionPointContainer> spCPC;
       IConnectionPointPtr pCP;
            DWORD dw;

       //if(FAILED(hr = spIdbas->QueryInterface(IID_IConnectionPointContainer, (void **) &spCPC)))
        if(SUCCEEDED(hr = m_pSongsSetAsynch->m_spRowset->QueryInterface(IID_IConnectionPointContainer, (void **) &spCPC)) &&
            SUCCEEDED(hr = spCPC->FindConnectionPoint(__uuidof(IDBAsynchNotify), &pCP)) &&
            SUCCEEDED(hr = pCP->Advise((IDBAsynchNotify *) this, &dw)))
       {
       }
        Populate();
    }
*/
   *pResult = 0;
}

void AlbumSongList::OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
/*   LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
   // TODO: add your control notification handler code here
   LV_ITEM* pItem= &(pDispInfo)->item;

   int iItemIndx= pItem->iItem;

    ESubItem esubitem;
    esubitem = (ESubItem) _001MapOrderToSubItem(pItem->iSubItem);

//   int iKey = m_dwaQueryKeys.get_at(iItemIndx);
//   CAlbumDialog * pParent = (CAlbumDialog *) GetParent();
//   CDBSongSet *pSet = pParent->m_pSongsSet;
   CDBSongRow * pSong;
   if(!m_cacheMap.Lookup(iItemIndx, pSong))
   {
//      TRACE("AlbumSongList::OnGetdispinfo iKey=%d iItemIdx=%d\n", iKey, iItemIndx);
      TRACE("AlbumSongList::OnGetdispinfo iItemIdx=%d\n", iItemIndx);
      DoCache(iItemIndx, iItemIndx);
      if(!m_cacheMap.Lookup(iItemIndx, pSong))
         goto End;
//      TRACE("XXXXXXXXXXXXXXXXX CANNOT CACHE!!!! AlbumSongList::OnGetdispinfo iKey=%d iItemIdx=%d\n", iKey, iItemIndx);
            TRACE("XXXXXXXXXXXXXXXXX CANNOT CACHE!!!! AlbumSongList::OnGetdispinfo iItemIdx=%d\n", iItemIndx);
   }

/*      if(!pSet->FindKey(iKey))
         return;
      if (pItem->mask & LVIF_TEXT) //valid text buffer?
      {
         switch(pItem->iSubItem)
         {
         case 0: //fill in main text
            pSet->get_data(4);
            lstrcpy(pItem->pszText, 
               pSet->m_Country);
            break;
         case 1: //fill in main text
            pSet->get_data(2);
            lstrcpy(pItem->pszText, 
               pSet->m_Name);
            break;
         case 2: //fill in sub item 1 text
            pSet->get_data(2);
            lstrcpy(pItem->pszText,
               pSet->m_Composer);
            break;
         case 3: //fill in sub item 1 text
            pSet->get_data(2);
            lstrcpy(pItem->pszText,
               pSet->m_Lyricist);
            break;
         case 4: //fill in sub item 1 text
            pSet->get_data(2);
            lstrcpy(pItem->pszText,
               pSet->m_Arranger);
            break;
         case 5: //fill in sub item 1 text
            pSet->get_data(2);
            lstrcpy(pItem->pszText,
               pSet->m_Performer);
            break;
         case 6: //fill in sub item 1 text
            pSet->get_data(2);
            lstrcpy(pItem->pszText,
               pSet->m_Programmer);
            break;
         case 7: //fill in sub item 2 text
            {
            string str;
            pSet->get_data(1);
            str.Format("%05d", pSet->m_iCode);
            lstrcpy(pItem->pszText,
               (const char *) str);
            break;
            }
         case 8: //fill in sub item 2 text
            pSet->get_data(3);
            string str;
            str = pSet->m_Path;
            lstrcpy(pItem->pszText,
               (const char *) str);
            break;
         }
      }
   } 
   else*/
   /*{
        
      if (pItem->mask & LVIF_TEXT) //valid text buffer?
      {
            CDBSongRowBase::Field efield;

            MapSubItemToField(efield, esubitem);

/*            if(_001GetItemText(
            m_str,
            pItem->iItem,
            pItem->iSubItem,
            -1))
         {
               _tcscpy(pItem->pszText, m_str);
         }*/
//            = pSong->GetFieldString(field);
  //          if(m_str.is_empty() &&
    //            subItem != SubItemIcon &&
      //          subItem != SubItemDelete)
        //    {
          //      m_str = "-";
            //}
         /*switch(iSubItem)
         {
         case 1: //fill in sub item 2 text
            m_str.Format("%05d", pSong->m_iCode);
            _tcscpy(pItem->pszText, m_str);
            break;
         case 2: //fill in main text
            m_str =   pSong->m_Country;
            _tcscpy(pItem->pszText, m_str);
            break;
         case 3: //fill in main text
            m_str =   pSong->m_bstrName;
            _tcscpy(pItem->pszText, m_str);
            break;
         case 4: //fill in main text
            m_str =   pSong->m_bstrAuthor;
            _tcscpy(pItem->pszText, m_str);
            break;
         case 5: //fill in main text
            m_str =   pSong->m_bstrCopyright;
            _tcscpy(pItem->pszText, m_str);
            break;
         case 6: //fill in sub item 1 text
            m_str =   pSong->m_bstrComposer;
            _tcscpy(pItem->pszText, m_str);
            break;
         case 7: //fill in sub item 1 text
            m_str =   pSong->m_bstrLyricist;
            _tcscpy(pItem->pszText, m_str);
            break;
         case 8: //fill in sub item 1 text
            m_str =   pSong->m_bstrArranger;
            _tcscpy(pItem->pszText, m_str);
            break;
         case 9: //fill in sub item 1 text
            m_str =   pSong->m_bstrPerformer;
            _tcscpy(pItem->pszText, m_str);
            break;
         case 10: //fill in sub item 1 text
            m_str =   pSong->m_bstrProgrammer;
            _tcscpy(pItem->pszText, m_str);
            break;
         case 11: //fill in sub item 2 text
            m_str =   pSong->m_bstrPath;
            _tcscpy(pItem->pszText, m_str);
            break;
         }*/
   /*   }
   }
    if(esubitem == SubItemIcon)
    {
       if(pItem->mask & LVIF_IMAGE) //valid image?
        {
         pItem->iImage = _001GetItemImage(pItem->iItem, 0, -1);
        }
    }*/
//End:   
//   *pResult = 0;
}

void AlbumSongList::OnOdcachehint(NMHDR* pNMHDR, LRESULT* pResult) 
{
   NMLVCACHEHINT* pCacheHint = (NMLVCACHEHINT*)pNMHDR;
   // TODO: add your control notification handler code here
      int iFrom = pCacheHint->iFrom;
   int iTo = pCacheHint->iTo;
   DoCache(iFrom, iTo);
   *pResult = 0;
}

int AlbumSongList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
/*   if (simple_list_view::OnCreate(lpCreateStruct) == -1)
      return -1;*/

/*   CDBCentral * pDataCentral = db();
   m_pDataSource = pDataCentral->GetDataSource();

    ::ca::graphics * pdc = GetDC();
    m_dcBuffer.CreateCompatibleDC(pdc);
    

    if(m_bmpBuffer->m_hObject != NULL)
    {
        m_bmpBuffer->delete_object();
    }

    rect rect;
    GetClientRect(&rect);
    m_bmpBuffer->CreateCompatibleBitmap(pdc, rect.width(), rect.height());
    m_pbmpBufferOld = m_dcBuffer.SelectObject(m_bmpBuffer);
    ReleaseDC(pdc);

    

   if(db()->IsBuildingSongsAlbum())
   {
      m_wstrTopText = L"Building Album";
      m_bTopText = true;
   }

  */  




   return 0;
}

HRESULT AlbumSongList::OpenSongsSet(const char * lpSQL, bool bFindInterface)
{
//   CVMSApp * pApp = (CVMSApp *) &System;
/*   CDBCentral * pDataCentral = db();
   HRESULT hr;
      try
   {
   {
      if(m_pDataSource->m_spInit == NULL)
         return E_FAIL;
      wait_cursor wait(get_app());
      if(m_pSongsSetSynch->m_spCommand != NULL)
      {
         m_pSongsSetSynch->close();
      }
      if(lpSQL == NULL)
         hr = m_pSongsSetSynch->open(m_pDataSource, bFindInterface);
      else
         hr = m_pSongsSetSynch->open(m_pDataSource, lpSQL, bFindInterface);
      if(FAILED(hr))
      {

      }
      return hr;


   }
   } catch(COLEDBException *e)
   {
      CDBErrorDialog dlg;
      dlg.Init(e->m_spUnk, e->m_iid);
      dlg.DoModal();
      e->Delete();
      return hr;
   }
*/
   return S_OK;
}

HRESULT AlbumSongList::OpenSongsSetIndexedOrdinal()
{
//   CVMSApp * pApp = (CVMSApp *) &System;
/*   CDBCentral * pDataCentral = db();
   HRESULT hr;
      try
   {
   {
      if(m_pDataSource->m_spInit == NULL)
         return E_FAIL;
      wait_cursor wait(get_app());
      if(m_pSongsSetSynch->m_spRowset != NULL)
      {
         m_pSongsSetSynch->close();
      }
      hr = m_pSongsSetSynch->OpenIndexedOrdinal(m_pDataSource);
      //hr = m_pSongsSet->open(m_DataSource);
      return hr;


   }
   } catch(COLEDBException *e)
   {
      CDBErrorDialog dlg;
      dlg.Init(e->m_spUnk, e->m_iid);
      dlg.DoModal();
      e->Delete();
      return hr;
   }
*/
   return S_OK;
}

HRESULT AlbumSongList::OpenSongsSetIndexedPath()
{
//   CVMSApp * pApp = (CVMSApp *) &System;
/*   CDBCentral * pDataCentral = db();
   HRESULT hr;
      try
   {
   {
      if(m_pDataSource->m_spInit == NULL)
         return E_FAIL;
      wait_cursor wait(get_app());
      if(m_pSongsSetSynch->m_spRowset != NULL)
      {
         m_pSongsSetSynch->close();
      }
      hr = m_pSongsSetSynch->OpenIndexedPath(m_pDataSource);
      //hr = m_pSongsSet->open(m_DataSource);
      return hr;


   }
   } catch(COLEDBException *e)
   {
      CDBErrorDialog dlg;
      dlg.Init(e->m_spUnk, e->m_iid);
      dlg.DoModal();
      e->Delete();
      return hr;
   }
*/
   return S_OK;
}

BOOL AlbumSongList::PreCreateWindow(CREATESTRUCT& cs) 
{
   // TODO: add your specialized code here and/or call the base class
/*   cs.style = cs.style
      | LVS_OWNERDATA
      | LVS_OWNERDRAWFIXED
      | WS_CHILD
      | LVS_SHAREIMAGELISTS
      | LVS_REPORT;
   cs.dwExStyle = cs.dwExStyle | WS_EX_CLIENTEDGE;*/
   return simple_list_view::PreCreateWindow(cs);
}

VMSRESULT AlbumSongList::UpdateList(dword_array * pdwaKeys)
{
   m_bFirstProgress = true;
   m_dwaQueryKeys.remove_all();
//   m_cacheMap.remove_all();

/*   if(!db()->IsWorking())
      return VMSR_E_FAIL;

    if(pdwaKeys != NULL)
    {
        m_dwaQueryKeys.copy(*pdwaKeys);
    }
    else
    {
        m_pSongsSetAsynch->Sort(true);
    }
    
    ASSERT(m_pSongsSetAsynch->m_spRowset != NULL);
    
    HRESULT hr;
    if(SUCCEEDED(hr = m_pSongsSetAsynch->m_spRowset->QueryInterface(IID_IDBAsynchStatus, (void **)&m_spIdbas)))
    {
        Populate(m_spIdbas);
        return VMSR_SUCCESS;
    }
    else
    {

        AddRef();
       CComPtr<IConnectionPointContainer> spCPC;
       IConnectionPointPtr pCP;
            DWORD dw;

       //if(FAILED(hr = spIdbas->QueryInterface(IID_IConnectionPointContainer, (void **) &spCPC)))
        if(SUCCEEDED(hr = m_pSongsSetAsynch->m_spRowset->QueryInterface(IID_IConnectionPointContainer, (void **) &spCPC)))
        {
            //System.simple_message_box("Good1!");
            if(SUCCEEDED(hr = spCPC->FindConnectionPoint(__uuidof(IDBAsynchNotify), &pCP)))
            {
              //  System.simple_message_box("Good2!");
                if(SUCCEEDED(hr = pCP->Advise((IDBAsynchNotify *) this, &dw)))
                {
               //    System.simple_message_box("Good3!");
                }
            }
       }
        Populate();
    }*/
   return VMSR_SUCCESS;
}

BOOL AlbumSongList::SetWhereClause(const char * lpcszSql)
{
   m_strWhereClause = lpcszSql;
   //m_pSongsSetAsynch->SetWhereClause(m_strWhereClause);
   return TRUE;
}

BOOL AlbumSongList::SetWhereClause(int iMask, const char * lpcszSql)
{
//   m_pSongsSetAsynch->SetWhereClause(iMask, lpcszSql);
  //  m_strWhereClause = m_pSongsSetAsynch->GetWhereClause();
   return TRUE;
}

BOOL AlbumSongList::SetFromClause(const char * lpcszSql)
{
   m_strFromClause = lpcszSql;
//   m_pSongsSetAsynch->SetFromClause(m_strFromClause);
   return TRUE;
}

BOOL AlbumSongList::DoCache(int iFrom, int iTo)
{
   static critical_section l_cs;
   CSingleLock sl(&l_cs, TRUE);
   int iIndex, iKey, i, iSize;
/*   CDBSongRow * pSong;
   iSize = iTo - iFrom + 1;
   if(iSize > m_cacheArray.get_size())
   {
      HANDLE hHeap = GetProcessHeap();
      while(iSize + 200> m_cacheArray.get_size())
      {
      //   pSong = (CDBSongRowBase *) HeapAlloc(hHeap, 0, sizeof(CDBSongRowBase));
      //   pSong->Construct();
         pSong = new CDBSongRow();
         //pSong = new CDBSongRowBase();
         m_cacheArray.add(pSong);
      }
   }
   ::ca::window * pParent = GetParent();
    CDBSongSet *pSet = db()->GetSongSetIndexedKey();
    //CDBSongSet *pSet = pParent->m_pSongsSet;
    //pParent->SendMessage(WM_USER, 10, (LPARAM) &pSet);
   
   critical_section * pCs = &pSet->m_cs;
   i = 0;
   int iCacheIndex = m_iCacheNextIndex;
   for(iIndex = iFrom; iIndex <= iTo; iIndex++)
   {
      if(iIndex >= m_dwaQueryKeys.get_size())
            break;
//      TRACE("AlbumSongList::DoCache iIndex = %d\n", iIndex);
      if(m_cacheMap.Lookup(iIndex, pSong))
         continue;
      iKey = m_dwaQueryKeys.get_at(iIndex);
//      TRACE("AlbumSongList::DoCache iKey = %d\n", iKey);
      pCs->Lock();
      if(!pSet->FindKey(iKey))
      {
            if(!SendMessage(WM_USER, 11))
            {
              pCs->Unlock();
                continue;

            }
         
      }
      
      if(iCacheIndex >= m_cacheArray.get_size())
      {
         iCacheIndex = 0;
         if(iCacheIndex >= m_cacheArray.get_size())
            break;
      }
      pSong = m_cacheArray.get_at(iCacheIndex);
      m_cacheMap.RemoveKey(pSong->m_iIndex);
      iCacheIndex++;
      pSet->get_data(0);
      pSet->get_data(1);
      pSet->get_data(2);
      pSet->get_data(3);
      pSet->get_data(4);
        pSet->get_data(8);
      pSet->Normalize();
      *pSong = *pSet;
      pCs->Unlock();
      pSong->m_iIndex = iIndex;      
      m_cacheMap.set_at(iIndex, pSong);
      i++;
   }*/
//   m_iCacheNextIndex = iCacheIndex;
   return TRUE;
}

void WINAPI AlbumSongList::ThreadProcOnContextMenu(void *lpParameter)
{

}

void AlbumSongList::OnContextMenu(::ca::window* pWnd, point point) 
{
    //simple_list_view::OnContextMenu();
    UINT nCtrlID = pWnd->GetDlgCtrlId();
    UINT nID = GetPopupMenuID(nCtrlID);
/*    CBaseRelation <UINT, UINT, UINT, UINT> * prel;
    CVmsGuiDll::AppGetDll()->MenuV033GetImageMap(&prel);
    CMenuV033 menu(
        CVmsGuiDll::AppGetDll()->MenuV033GetImageList(),
      CVmsGuiDll::AppGetDll()->MenuV033GetImageListDisabled(),
        prel,
        CVmsGuiDll::AppGetDll()->MenuV033GetFont()); 
        
   if (menu.LoadMenu(nID))
   {
      ::userbase::menu* pPopup = menu.GetSubMenu(0);
      ASSERT(pPopup != NULL);
        ::ca::window * pwnd = NULL;
        {
            frame_window * pframe = GetParentFrame();
            if(pframe == NULL)
            {
                pwnd = GetParent();
            }
            else
            {
                pwnd = pframe;
            }
        }
      pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
         point.x, point.y,
         pwnd);
   }*/
}


UINT AlbumSongList::GetPopupMenuID(UINT nID)
{

    /*UINT nPopupID;
    switch(nID)
    {
    case IDC_FULLLIST:
        nPopupID = IDR_POPUP_ALBUM_FULLLIST;
        break;
    case IDC_LIST:
        nPopupID = IDR_POPUP_ALBUM_FULLLIST;
        break;
    case IDC_LIST_SEARCH:
        nPopupID = IDR_POPUP_ALBUM_FULLLIST;
        break;
    case IDC_LISTHEADER_FULL:
        nPopupID = IDR_ALBUM_LIST_HEADER;
        break;
    case IDC_LISTHEADER_TREE:
        nPopupID = IDR_ALBUM_LIST_HEADER;
        break;
    case IDC_LISTHEADER_SEARCH:
        nPopupID = IDR_ALBUM_LIST_HEADER;
        break;
    case IDC_LIST_HEADER:
        nPopupID = IDR_ALBUM_LIST_HEADER;
        break;
    default:
        break;
    }*/
//    return nPopupID;
    return 0;

}

void AlbumSongList::OnAlbumListheaderArranger() 
{
   // TODO: add your command handler code here
    
    ToggleSubItem(SubItemArranger);
}

void AlbumSongList::OnUpdateAlbumListheaderArranger(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
    OnUpdateAlbumListHeaderItem(pcmdui, SubItemArranger);
}

void AlbumSongList::OnAlbumListheaderCode() 
{
   // TODO: add your command handler code here
    ToggleSubItem(SubItemCode);
}

void AlbumSongList::OnUpdateAlbumListheaderCode(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
    OnUpdateAlbumListHeaderItem(pcmdui, SubItemCode);
   
}

void AlbumSongList::OnAlbumListheaderComposer() 
{
   // TODO: add your command handler code here
    ToggleSubItem(SubItemComposer);
}

void AlbumSongList::OnUpdateAlbumListheaderComposer(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   int iColumn;
   iColumn = _001MapSubItemToOrder(SubItemComposer);
   pcmdui->_001SetCheck(iColumn >= 0);
}

void AlbumSongList::OnAlbumListheaderCountry() 
{
   // TODO: add your command handler code here
    ToggleSubItem(SubItemCountry);
/*   int iColumn = FindColumn(m_ciSubItemCountry);
    if(iColumn >= 0)
    {
        DeleteColumn(iColumn);
    }
    else
    {
        string str;
       CVMSApp * pApp = (CVMSApp *) &System;
       CDBCentral * pDataCentral = db();
      int width;
      str.Format("Column[%d].width", m_ciSubItemCountry);
      width = 100;
      pDataCentral->get_db_long_set()->Load(
         m_strRegistrySection,
         str,
         &width);
        str.load_string(IDS_ALBUM_COUNTRY);
       InsertColumn(1, str, LVCFMT_LEFT, width, m_ciSubItemCountry);
    }*/
}

void AlbumSongList::OnUpdateAlbumListheaderCountry(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   int iColumn = _001MapSubItemToOrder(SubItemCountry);
   pcmdui->_001SetCheck(iColumn >= 0);
}

void AlbumSongList::OnAlbumListheaderLyricist() 
{
   ToggleSubItem(SubItemLyricist);
}

void AlbumSongList::OnUpdateAlbumListheaderLyricist(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   int iColumn = _001MapSubItemToOrder(SubItemLyricist);
   pcmdui->_001SetCheck(iColumn >= 0);
}

void AlbumSongList::OnAlbumListheaderName() 
{
   ToggleSubItem(SubItemName);
}

void AlbumSongList::OnUpdateAlbumListheaderName(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   int iColumn = _001MapSubItemToOrder(SubItemName);
   pcmdui->_001SetCheck(iColumn >= 0);
}

void AlbumSongList::OnAlbumListheaderPath() 
{
    ToggleSubItem(SubItemPath);
}

void AlbumSongList::OnUpdateAlbumListheaderPath(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   int iColumn = _001MapSubItemToOrder(SubItemPath);
   pcmdui->_001SetCheck(iColumn >= 0);
}

void AlbumSongList::OnAlbumListheaderPerformer() 
{
    ToggleSubItem(SubItemPerformer);
}

void AlbumSongList::OnUpdateAlbumListheaderPerformer(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   int iColumn = _001MapSubItemToOrder(SubItemPerformer);
   pcmdui->_001SetCheck(iColumn >= 0);
}

void AlbumSongList::OnAlbumListheaderProgrammer() 
{
   ToggleSubItem(SubItemProgrammer);
}

void AlbumSongList::OnUpdateAlbumListheaderProgrammer(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   int iColumn = _001MapSubItemToOrder(SubItemProgrammer);
   pcmdui->_001SetCheck(iColumn >= 0);
}

void AlbumSongList::OnAlbumListheaderAuthor() 
{
   ToggleSubItem(SubItemAuthor);
}

void AlbumSongList::OnUpdateAlbumListheaderAuthor(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   int iColumn = _001MapSubItemToOrder(SubItemAuthor);
   pcmdui->_001SetCheck(iColumn >= 0);
   
}

void AlbumSongList::OnAlbumListheaderCopyright() 
{
   ToggleSubItem(SubItemCopyright);
}

void AlbumSongList::OnUpdateAlbumListheaderCopyright(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
    OnUpdateAlbumListHeaderItem(pcmdui, SubItemCopyright);

}





void AlbumSongList::_001OnDestroy(gen::signal_object * pobj) 
{
   simple_list_view::_001OnDestroy(pobj);
   
   
}


VMSRESULT AlbumSongList::ToggleSubItem(ESubItem iSubItem)
{
    int iColumn;
    iColumn = _001MapSubItemToColumn(iSubItem);
   if(iColumn == ColumnInvalid)
   {
      _001ShowSubItem(iSubItem);
   }
   else
   {
      _001ShowSubItem(iSubItem, false);
   }
   /*
    int iColumn;
    string str;
//    CVMSApp * pApp = (CVMSApp *) &System;
   CDBCentral * pDataCentral = db();
    iColumn = _001MapSubItemToOrder(iSubItem);
    if(iColumn >= 0)
    {
//        int iWidth = _001GetColumnWidth(iColumn);
//      str.Format("Column[%d].width", iSubItem);
//      pDataCentral->get_db_long_set()->Save(
//         m_strRegistrySection,
//         str,
//         iWidth);
//        _001DeleteColumn(iColumn);
    }
    else
    {
      int width;
      str.Format("Column[%d].width", iSubItem);
      width = 100;
      pDataCentral->get_db_long_set()->Load(
         m_strRegistrySection,
         str,
         &width);
        if(width < 64)
            width = 64;
        if(width > 2048)
            width = 2048;
        
      Column column;
      column.m_iColumn = m_iNewColumnIndex;
      column.m_uiText = GetColumnHeaderTextId(iSubItem);    
      column.m_iWidth = width;
      column.m_iSubItem = iSubItem;
       _001AddColumn(column);
    }*/
    return VMSR_SUCCESS;
}

UINT AlbumSongList::_001GetColumnTextId(int iColumn)
{
   return GetColumnHeaderTextId((ESubItem) _001MapColumnToSubItem(iColumn));
}

UINT AlbumSongList::GetColumnHeaderTextId(ESubItem esubitem)
{
/*    UINT user;
    switch(esubitem)
    {
    case SubItemCode:
        user = IDS_ALBUM_CODE;
        break;
    case SubItemCountry:
        user = IDS_ALBUM_COUNTRY;
        break;
    case SubItemName:
        user = IDS_ALBUM_SONGNAME;
        break;
    case SubItemFileName:
        user = IDS_ALBUM_FILENAME;
        break;
    case SubItemAuthor:
        user = IDS_ALBUM_AUTHOR;
        break;
    case SubItemCopyright:
        user = IDS_ALBUM_COPYRIGHT;
        break;
    case SubItemComposer:
        user = IDS_ALBUM_COMPOSER;
        break;
    case SubItemLyricist:
        user = IDS_ALBUM_LYRICIST;
        break;
    case SubItemArranger:
        user = IDS_ALBUM_ARRANGER;
        break;
    case SubItemPerformer:
        user = IDS_ALBUM_PERFORMER;
        break;
    case SubItemProgrammer:
        user = IDS_ALBUM_PROGRAMMER;
        break;
    case SubItemPath:
        user = IDS_ALBUM_PATH;
        break;
    default:
        user = -1;
    }

   return user;
*/
   return 0;
}

void AlbumSongList::OnAlbumListheaderFilename() 
{
   // TODO: add your command handler code here
    ToggleSubItem(SubItemFileName);

}

void AlbumSongList::OnUpdateAlbumListheaderFilename(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   OnUpdateAlbumListHeaderItem(pcmdui, SubItemFileName);

}

/*
VMSRESULT AlbumSongList::MapFieldToSubItem(ESubItem & nSubItem, CDBSongSet::Field iField)
{
    switch(iField)
    {
    case CDBSongSet::FieldName:
        nSubItem = SubItemName;
        break;
    case CDBSongSet::FieldAuthor:
        nSubItem = SubItemAuthor;
        break;
    case CDBSongSet::FieldCopyright:
        nSubItem = SubItemCopyright;
        break;
    case CDBSongSet::FieldComposer:
        nSubItem = SubItemComposer;
        break;
    case CDBSongSet::FieldLyricist:
        nSubItem = SubItemLyricist;
        break;
    case CDBSongSet::FieldArranger:
        nSubItem = SubItemArranger;
        break;
    case CDBSongSet::FieldPerformer:
        nSubItem = SubItemPerformer;
        break;
    case CDBSongSet::FieldProgrammer:
        nSubItem = SubItemProgrammer;
        break;
    case CDBSongSet::FieldFileName:
        nSubItem = SubItemFileName;
        break;
    case CDBSongSet::FieldKeyword:
        nSubItem = SubItemKeyword;
        break;
    case CDBSongSet::FieldPath:
        nSubItem = SubItemPath;
        break;
    default:
        nSubItem = SubItemNull;
    }
    return VMSR_SUCCESS;
}

VMSRESULT AlbumSongList::MapSubItemToField(CDBSongSet::Field & iField, ESubItem nSubItem)
{
    switch(nSubItem)
    {
    case SubItemCode:
        iField = CDBSongSet::FieldCode;
        break;
    case SubItemName:
        iField = CDBSongSet::FieldName;
        break;
    case SubItemAuthor:
        iField = CDBSongSet::FieldAuthor;
        break;
    case SubItemCopyright:
        iField = CDBSongSet::FieldCopyright;
        break;
    case SubItemComposer:
        iField = CDBSongSet::FieldComposer;
        break;
    case SubItemLyricist:
        iField = CDBSongSet::FieldLyricist;
        break;
    case SubItemArranger:
        iField = CDBSongSet::FieldArranger;
        break;
    case SubItemPerformer:
        iField = CDBSongSet::FieldPerformer;
        break;
    case SubItemProgrammer:
        iField = CDBSongSet::FieldProgrammer;
        break;
    case SubItemFileName:
        iField = CDBSongSet::FieldFileName;
        break;
    case SubItemKeyword:
        iField = CDBSongSet::FieldKeyword;
        break;
    case SubItemPath:
        iField = CDBSongSet::FieldPath;
        break;
    default:
        iField = CDBSongSet::FieldNoField;
    }
    return VMSR_SUCCESS;
}
*/

void AlbumSongList::OnUpdateAlbumListHeaderItem(cmd_ui *pcmdui, int iColumn)
{
   pcmdui->Enable();
    pcmdui->_001SetCheck(iColumn >= 0);

}

void AlbumSongList::OnUpdateAlbumListHeaderItem(cmd_ui *pcmdui, ESubItem esubitem)
{
    int iColumn;
    iColumn = _001MapSubItemToOrder(esubitem);
    OnUpdateAlbumListHeaderItem(pcmdui, iColumn);
}

void AlbumSongList::_001InsertColumns()
{
//    CDBCentral * pDataCentral = db();

   //LockWindowUpdate();

   Column column;

   column.m_iWidth = 18;
   column.m_iSubItem = SubItemIcon;
//   column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
   column.m_iSmallImageWidth = 16;
   column.m_crSmallMask = RGB(255, 0, 255);
   _001AddColumn(column);

//   column.m_uiText = IDS_ALBUM_CODE;
   column.m_iWidth = 30;
   column.m_iSubItem = SubItemCode;
   _001AddColumn(column);

//   column.m_uiText = IDS_ALBUM_COUNTRY;
   column.m_iWidth = 50;
   column.m_iSubItem = SubItemCountry;
   _001AddColumn(column);

//   column.m_uiText = IDS_ALBUM_SONG_NAME;
   column.m_iWidth = 50;
   column.m_iSubItem = SubItemName;
   _001AddColumn(column);

//   column.m_uiText = IDS_ALBUM_FILENAME;
   column.m_iWidth = 250;
   column.m_iSubItem = SubItemFileName;
   _001AddColumn(column);

//   column.m_uiText = IDS_ALBUM_AUTHOR;
   column.m_iWidth = 150;
   column.m_iSubItem = SubItemAuthor;
   _001AddColumn(column);

//   column.m_uiText = IDS_ALBUM_COPYRIGHT;
   column.m_iWidth = 150;
   column.m_iSubItem = SubItemCopyright;
   _001AddColumn(column);

//   column.m_uiText = IDS_ALBUM_COMPOSER;
   column.m_iWidth = 150;
   column.m_iSubItem = SubItemComposer;
   _001AddColumn(column);

//   column.m_uiText = IDS_ALBUM_LYRICIST;
   column.m_iWidth = 150;
   column.m_iSubItem = SubItemLyricist;
   _001AddColumn(column);

//   column.m_uiText = IDS_ALBUM_ARRANGER;
   column.m_iWidth = 150;
   column.m_iSubItem = SubItemArranger;
   _001AddColumn(column);

//   column.m_uiText = IDS_ALBUM_PERFORMER;
   column.m_iWidth = 150;
   column.m_iSubItem = SubItemPerformer;
   _001AddColumn(column);

//   column.m_uiText = IDS_ALBUM_PROGRAMMER;
   column.m_iWidth = 150;
   column.m_iSubItem = SubItemProgrammer;
   _001AddColumn(column);

//   column.m_uiText = IDS_ALBUM_PATH;
   column.m_iWidth = 500;
   column.m_iSubItem = SubItemPath;
   _001AddColumn(column);


   DILoadOrder();

   //UnlockWindowUpdate();

}

void AlbumSongList::OnHeaderCtrlItemChanging(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMHEADER lpnmh = (LPNMHEADER) pNMHDR;
    
    LPHDITEM  lphdi = lpnmh->pitem;

    if(lpnmh->iItem == 0 &&
        (lphdi->mask & (HDI_WIDTH | HDI_ORDER )) != 0 )
    {
        *pResult = TRUE;
    }
    else
    {
        *pResult = FALSE;
    }
}

VMSRESULT AlbumSongList::SetItemCountEx_(int iCount, DWORD dwFlags)
{
//    _001SetItemCountEx(iCount, dwFlags);
    GetParent()->SendMessage(WM_USER, 789);
    return VMSR_SUCCESS;
}


VMSRESULT AlbumSongList::Initialize()
{
/*    if(m_pSongsSetAsynch == NULL)
    {
        m_pSongsSetAsynch = new CDBSongSet(DBDataCentral());
    }
    if(m_pSongsSetSynch == NULL)
    {
        m_pSongsSetSynch = new CDBSongSet(DBDataCentral());
    }
   if(!db()->IsWorking())
   {
      string str;
      str.load_string(IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE);
      _001SetTopText(str);
      _001ShowTopText();
   }*/
    return VMSR_SUCCESS;
}

/*
VMSRESULT AlbumSongList::Initialize(CDBSongSet *psetAsynch, CDBSongSet *psetSynch)
{
//    m_pSongsSetAsynch = psetAsynch;
  //  m_pSongsSetSynch = psetSynch;
    return VMSR_SUCCESS;
}
*/

void AlbumSongList::AddKey(int iKey)
{
    m_dwaQueryKeys.add(iKey);
/*    db()->OpenSongSetIndexedKey();
    */
//    _001SetItemCountEx(m_dwaQueryKeys.get_size(), LVSICF_NOSCROLL);
}

void AlbumSongList::OnPaint() 
{
//    TwiOnPaint();
       //CPaintDC spgraphics(this); // device context for painting
    
    //spgraphics->FillSolidRect(rcClient, GetSysColor(COLOR_WINDOW));
    //ReleaseDC(pdc);
   // Do not call simple_list_view::OnPaint() for painting messages
}

void AlbumSongList::OnSize(UINT nType, int cx, int cy) 
{
//   simple_list_view::OnSize(nType, cx, cy);
   
    if(m_dcBuffer->get_os_data() == NULL)
        return;

    if(m_bmpBuffer->get_os_data() != NULL)
    {
        m_dcBuffer->SelectObject(m_pbmpBufferOld);
        m_bmpBuffer->delete_object();
    }
    ::ca::graphics * pdc = GetDC();
    m_bmpBuffer->CreateCompatibleBitmap(pdc, cx, cy);
    ReleaseDC(pdc);
    m_dcBuffer->SelectObject(m_bmpBuffer);


/*
if(m_scrollbarHorz.GetSafeHwnd() == NULL)
   {
      CScrollBar * pscrollbarHorz = GetScrollBarCtrl(SB_HORZ);

      if(pscrollbarHorz != NULL)
      {
      }
   }
*/

    /*
   if(m_scrollbarVert.GetSafeHwnd() == NULL)
   {
      CScrollBar * pscrollbarVert = GetScrollBarCtrl(SB_VERT);
      
      if(pscrollbarVert != NULL)
      {
      }
   }
*/

   // TODO: add your message handler code here
   
}

BOOL AlbumSongList::OnEraseBkgnd(::ca::graphics * pgraphics) 
{
   return TRUE;
}

BOOL AlbumSongList::UpdateChildrenClipRgn()
{
   ::user::interaction* pWndChild  = GetTopWindow();
   ::user::interaction* pWndFirstChild = pWndChild;
   ::ca::rgn_sp rgnChild(get_app());
   rect rectClient;
   rect rectChild;
   GetClientRect(rectClient);
   m_rgnChildren->SetRectRgn(rectClient);
   rgnChild->CreateRectRgn(0, 0, 0, 0);
   while(pWndChild != NULL)
   {
//        if(!base < CButtonV007 >::bases(pWndChild))
        {
           if(pWndChild->GetWindowRgn((HRGN)rgnChild->get_os_data()) != ERROR)
            {
                pWndChild->GetWindowRect(rectChild);
                ScreenToClient(rectChild);
                rgnChild->OffsetRgn(rectChild.top_left());
                m_rgnChildren->CombineRgn(m_rgnChildren, rgnChild, RGN_DIFF);
            }
            else
            {
                pWndChild->GetWindowRect(rectChild);
                ScreenToClient(rectChild);
                rgnChild->SetRectRgn(rectChild);
                m_rgnChildren->CombineRgn(m_rgnChildren, rgnChild, RGN_DIFF);
            }
        }
        pWndChild = pWndChild->GetNextWindow();
        if(pWndChild  == NULL || pWndChild->_get_handle() == pWndFirstChild->_get_handle())
            break;
    }
    return TRUE;

}

/*bool AlbumSongList::WriteNotepadFile(
    CArchive &ar,
    CTaskAnnotation * ptasknote)
{
    
    HINSTANCE hinst = AfxGetResourceHandle();
    AfxSetResourceHandle(GetModuleHandle("vmsgui"));
    int iCount = m_dwaQueryKeys.get_size();
    ptasknote->m_iSteps = iCount;
    ptasknote->UpdateTasks();
    string str;
    string wstrInformation;
    CDBSongRow * pSong;
    for(int i = 0; i < iCount; i++)
    {
        ptasknote->m_iStep = i;
        ptasknote->UpdateProgress();
        wstrInformation.Format(IDS_NOTEPADALBUM_PROCESSINGLINE, i, iCount);
        ptasknote->m_ptasks->m_strInformation1 = wstrInformation;
        ptasknote->UpdateStatus();

        if(!m_cacheMap.Lookup(i, pSong))
        {
            DoCache(i, i + 50);
            if(!m_cacheMap.Lookup(i, pSong))
            {
                continue;
            }   
        }   
        for(int j = 0; j < _001GetColumnCount(); j++)
        {
            ESubItem esubitem;
            esubitem = (ESubItem) _001MapOrderToSubItem(j);   
            CDBSongRowBase::Field field;
            MapSubItemToField(field, esubitem);
            str = pSong->GetFieldString(field);
            if(str.is_empty() ||
                esubitem == SubItemIcon ||
                esubitem == SubItemDelete)
            {
                continue;
            }
            ar.write_string(str);
            ar.write_string(", ");
        }
        ar.write_string("\n");
        
    }
    return true;
    AfxSetResourceHandle(hinst);
}*/

/*string AlbumSongList::GetTextV001(CTaskAnnotation * ptasknote)
{
    HINSTANCE hinst = AfxGetResourceHandle();
    AfxSetResourceHandle(GetModuleHandle("vmsgui"));

    string strText;
    int iCount = m_dwaQueryKeys.get_size();
    ptasknote->m_iSteps = iCount;
    ptasknote->UpdateTasks();
    string str;
    string wstrInformation;
    CDBSongRow * pSong;
    CMemFile file(4096);
    CArchive ar(&file, CArchive::store);
    for(int i = 0; i < iCount; i++)
    {
        wstrInformation.Format(IDS_NOTEPADALBUM_PROCESSINGLINE, i, iCount);
        ptasknote->m_ptasks->m_strInformation1 = wstrInformation;
        ptasknote->UpdateStatus();

        if(!m_cacheMap.Lookup(i, pSong))
        {
            DoCache(i, i + 50);
            if(!m_cacheMap.Lookup(i, pSong))
            {
                continue;
            }   
        }   
        for(int j = 0; j < _001GetColumnCount(); j++)
        {
            ESubItem esubitem;
            esubitem = (ESubItem) _001MapOrderToSubItem(j);   
            CDBSongRowBase::Field field;
            MapSubItemToField(field, esubitem);
            str = pSong->GetFieldString(field);
            if(str.is_empty() ||
                esubitem == SubItemIcon ||
                esubitem == SubItemDelete)
            {
                continue;
            }
            ar.write_string(str);
            ar.write_string(", ");
        }
        ar.write_string("\n");
        ptasknote->m_iStep = i + 1;
        ptasknote->UpdateProgress();
        
    }
    wstrInformation.Format(IDS_NOTEPADALBUM_PROCESSINGLINE, i, iCount);
    ptasknote->m_ptasks->m_strInformation1 = wstrInformation;
    ptasknote->UpdateStatus();
    ar.close();
    spfile->Flush();
    const char * lpcsz = (const char *) spfile->Detach();
    strText = lpcsz;
    free((void *)lpcsz);

    AfxSetResourceHandle(hinst);

    return strText;

}*/

/*void AlbumSongList::TwiOnDraw(::ca::graphics *pdc)
{
//   CTransparentWndBufferContainer * ptwbc = dynamic_cast<CTransparentWndBufferContainer *>( System.GetThread());
//   CTransparentWndBuffer * ptwb = papp->GetTwb();
//   CSingleLock sl(ptwb->GetMutex(), TRUE);
  //  rect rcClient;
   //GetClientRect(&rcClient);
    //rect rcWindow;
   //GetWindowRect(&rcWindow);
   //::ca::graphics * pdc = ptwb->GetBuffer(&spgraphics, rcClient, rcWindow);
    //pdc->FillSolidRect(rcClient, GetSysColor(COLOR_WINDOW));
        //m_dcBuffer.SetWindowOrg(0, 0);

      //BOOL bWin4 = afxData.bWin4;
        BOOL bWin4 = FALSE;
      _AfxFillPSOnStack();
      ::CallWindowProc(
            *GetSuperWndProcAddr(),
            m_hWnd, (bWin4 ? WM_PRINT : WM_PAINT),
            (WPARAM)(pdc->m_hDC),
            (LPARAM)(bWin4 ? PRF_CHILDREN | PRF_CLIENT : 0));
   // TODO: add your message handler code here
    
    //    ::ca::graphics * pdc = GetDCEx(NULL,DCX_WINDOW | DCX_CLIPCHILDREN); 
//    UpdateChildrenClipRgn();
  //  spgraphics->SelectClipRgn(&m_rgnChildren);
    //rect rc;
    //m_rgnChildren.GetRgnBox(rc);
    //spgraphics->BitBlt(rcClient.left, rcClient.top,
    //    rcClient.width(), rcClient.height(),
      //  pdc, 
        //0, 0,
        //SRCCOPY);

}*/

/*void AlbumSongList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
//   simple_list_view::OnDrawItem(nIDCtl, lpDrawItemStruct);

    int iEconoMode = CSavings::AppGetEconoMode();
    ::ca::graphics * pDCBuffer = ::ca::graphics_sp::from_handle(lpDrawItemStruct->hDC);
    rect rectItem = lpDrawItemStruct->rcItem;
    ::image_list * lpImageList = GetImageList(LVSIL_SMALL);

//    rect rectClipBox;// = lpDrawItemStruct->rcItem;
    rect rectClipBox = lpDrawItemStruct->rcItem;
/*    pDCBuffer->GetClipBox(rectClipBox);

    rectClipBox.intersect(rectClipBox, rectItem);

    if(rectClipBox.is_null())
    {
        return;
        GetClientRect(rectClipBox);
        rectClipBox += m_ptScroll;
    }*/

/*    int iColumn = 0;
    LVITEM lvi;
    lvi.mask = LVIF_STATE;
   lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED;
    lvi.iItem = lpDrawItemStruct->itemID;
    lvi.iSubItem = 0;
    get_item(&lvi);

   int iState = lvi.state;

   int iImage = _001GetItemImage(lpDrawItemStruct->itemID);

    if(iState & LVIS_SELECTED)
    {
      pDCBuffer->SetTextColor(m_crTextSelected);
        if(iEconoMode & CSavings::SaveProcessing)
        {
            pDCBuffer->FillSolidRect(
                rectClipBox,
                RGB(96,96,96));
        }
        else
        {
            CImaging * pImaging = CImaging::GetImaging();
//                COLORREF crTranslucid = m_crTranslucidSelect;
         COLORREF crTranslucid = RGB(0, 0, 0);
            imaging.color_blend(
                pDCBuffer,
                rectClipBox.left, rectClipBox.top,
                rectClipBox.width(), rectClipBox.height(),
                crTranslucid, 127);
        }
    }
   else
   {
      pDCBuffer->SetTextColor(m_crText);
        if(iEconoMode & CSavings::SaveProcessing)
        {
            pDCBuffer->FillSolidRect(
                rectClipBox,
                RGB(255,255,255));
        }
        else
        {
            CImaging * pImaging = CImaging::GetImaging();
//                COLORREF crTranslucid = m_crTranslucidSelect;
         COLORREF crTranslucid = RGB(255, 255, 255);
            imaging.color_blend(
                pDCBuffer,
                rectClipBox.left, rectClipBox.top,
                rectClipBox.width(), rectClipBox.height(),
                crTranslucid, 208);
        }
   }


    if(iState & LVIS_FOCUSED)
    {
        
        rect rectFocused = lpDrawItemStruct->rcItem;
        rectFocused.deflate(2, 2);
        pDCBuffer->SelectObject(m_penFocused);
        pDCBuffer->SelectObject(m_brushNull);
        pDCBuffer->Rectangle(rectFocused);

    }
/*    if(plvi.m_uiState & VMSPLVIS_PLAYING)
    {
        pDCBuffer->SetTextColor(m_crTextPlaying);
    }
    else*/
        

  /*  if(lpImageList != NULL)
    {
        IMAGEINFO ii;
        lpImageList->get_image_info(iImage, &ii);
        rect rectImage = ii.rcImage;
        lpImageList->DrawIndirect(pDCBuffer, iImage , rectItem.top_left(), rectImage.size(), point(0,0), ILD_TRANSPARENT, SRCCOPY, CLR_NONE);
        string str;
      _001GetItemText(str, lpDrawItemStruct->itemID, iColumn + 1);
        rectItem.left += rectImage.width();
        rectItem.right = rectItem.left + GetColumnWidth(iColumn) - rectImage.width();
        pDCBuffer->DrawText(str, rectItem, DT_TOP | DT_LEFT  | DT_PATH_ELLIPSIS);
        rectItem.left = rectItem.right;
        iColumn = 1;
    }
    for(; iColumn < GetColumnCount(); iColumn++)
    {

        string str;
      _001GetItemText(str, lpDrawItemStruct->itemID, iColumn + 1);
        rectItem.right = rectItem.left + GetColumnWidth(iColumn);
        pDCBuffer->DrawText(str, rectItem, DT_TOP | DT_LEFT | DT_END_ELLIPSIS);
        rectItem.left = rectItem.right;
    }
    

}*/

bool AlbumSongList::_001GetItemText(string &wstrParam, int iItem, int iSubItem, int iListItem)
{
   string str;

    ESubItem esubitem;
    esubitem = (ESubItem) iSubItem;

/*   CDBSongRow * pSong;
   if(!m_cacheMap.Lookup(iItem, pSong))
   {
      TRACE("AlbumSongList::OnGetdispinfo iItemIdx=%d\n", iItem);
      DoCache(iItem, iItem);
      if(!m_cacheMap.Lookup(iItem, pSong))
         return false;
   }

    CDBSongRowBase::Field field;

    MapSubItemToField(field, esubitem);

   pSong->GetFieldString(str, field);
    if(str.is_empty() &&
        esubitem != SubItemIcon &&
        esubitem != SubItemDelete)
    {
        str = L"-";
    }
   wstrParam = str;
*/
   return true;
}

void AlbumSongList::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pscrollbar) 
{
   //if(pscrollbar != NULL)
   //{
   //   m_scrollbarHorz.SubclassWindow(pscrollbar->GetSafeHwnd());
   //}

   
   //simple_list_view::OnHScroll(nSBCode, nPos, pscrollbar);
}

void AlbumSongList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pscrollbar) 
{
   //if(pscrollbar != NULL)
   //{
   //   m_scrollbarVert.SubclassWindow(pscrollbar->GetSafeHwnd());
   //}
   
   //simple_list_view::OnVScroll(nSBCode, nPos, pscrollbar);
}

/*CScrollBar * AlbumSongList::GetScrollBarCtrl(int nBar)
{
   string strClass;
   LPTSTR lpszClass;
   ::user::interaction* pwndFind = NULL;
   if(nBar == SB_HORZ)
   {
      ::user::interaction* pwnd = GetWindow(GW_HWNDFIRST);
      while(pwnd != NULL)
      {
         lpszClass = strClass.GetBuffer(100);
         GetClassName(pwnd->_get_handle(), lpszClass, 100);
         strClass.ReleaseBuffer();
         if(strClass == "ScrollBar" 
            && (pwnd->GetStyle() & SBS_HORZ) != 0)
         {
            if(pwndFind != NULL)
               return NULL;
            pwndFind = pwnd;
         }
         pwnd = pwnd->GetWindow(GW_HWNDNEXT);
      }
      return (CScrollBar *) pwndFind;

   }
   else if(nBar == SB_VERT)
   {
      ::user::interaction* pwnd = GetWindow(GW_HWNDFIRST);
      while(pwnd != NULL)
      {
         lpszClass = strClass.GetBuffer(100);
         GetClassName(pwnd->_get_handle(), lpszClass, 100);
         strClass.ReleaseBuffer();
         if(strClass == "ScrollBar" 
            && (pwnd->GetStyle() & SBS_VERT) != 0)
         {
            if(pwndFind != NULL)
               return NULL;
            pwndFind = pwnd;
         }
         pwnd = pwnd->GetWindow(GW_HWNDNEXT);
      }
      return (CScrollBar *) pwndFind;
   }
   else
   {
      return NULL;
   }

}*/

int AlbumSongList::_001GetItemImage(int iItem, int iSubItem, int iListItem)
{
/*   CDBSongRow * psongrow;

   if(iSubItem != SubItemIcon
      || iListItem != -1)
      return -1;

   if(!m_cacheMap.Lookup(iItem, psongrow))
   {
      DoCache(iItem, iItem);
      if(!m_cacheMap.Lookup(iItem, psongrow))
         goto End;
   }
    if(psongrow->IsInvalidFormat())
    {
        return 7;
    }
    else
    {
        return 0;
    }
End:*/
   return -1;
}
