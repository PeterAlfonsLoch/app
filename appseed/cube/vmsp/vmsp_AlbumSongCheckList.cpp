#include "StdAfx.h"
#include "AlbumSongCheckList.h"


AlbumSongCheckList::AlbumSongCheckList(::ca::application * papp) :
   ca(papp),
   ::user::form(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::user::list(papp),
   ::user::form_list(papp),
   ::userbase::form_list(papp),
   AlbumSongList(papp)
{
    m_bSortEnabled = false;
    m_iNewColumnIndex = 2;
}

AlbumSongCheckList::~AlbumSongCheckList()
{
}


 // BEGIN_MESSAGE_MAP(AlbumSongCheckList, AlbumSongList)
   //{{AFX_MSG_MAP(AlbumSongCheckList)
/*   ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
   ON_WM_CREATE()
   ON_COMMAND(ID_FILE_AUTODELETEDUPLICATES, OnFileAutodeleteduplicates)
   ON_UPDATE_COMMAND_UI(ID_FILE_AUTODELETEDUPLICATES, OnUpdateFileAutodeleteduplicates)
   //}}AFX_MSG_MAP
    ON_NOTIFY(HDN_ITEMCHANGING, IDC_LIST_HEADER, OnHeaderCtrlItemChanging)*/
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AlbumSongCheckList message handlers

BOOL AlbumSongCheckList::PreCreateWindow(CREATESTRUCT& cs) 
{
    cs.style |= LVS_NOSORTHEADER;
    cs.dwExStyle |= LVS_EX_CHECKBOXES;

    return AlbumSongList::PreCreateWindow(cs);
}

VMSRESULT AlbumSongCheckList::UpdateList(dword_array * pdwa)
{
   UNREFERENCED_PARAMETER(pdwa);
   ::radix::thread * pthread = AfxBeginThread(get_app(), ThreadProcUpdateList, this);
   if(pthread == NULL)     
      return VMSR_E_FAIL;
   else
      return VMSR_SUCCESS;
}



void AlbumSongCheckList::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
    AlbumSongList::OnGetDispInfo(pNMHDR, pResult);

    LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

    LV_ITEM * pItem = &(pDispInfo)->item;

   int iItemIndex = pItem->iItem;

    ESubItem esubitem;
    esubitem = (ESubItem) _001MapOrderToSubItem(pItem->iSubItem);


    

    if(pItem->mask & LVIF_STATE) //valid image?
    {
        int iStateImageMask = INDEXTOSTATEIMAGEMASK(m_dwaState.element_at(iItemIndex));
        pItem->state &= 0xFFFF0FFF;
        pItem->state |= iStateImageMask;
        
        
    }
    if(esubitem == SubItemDelete)
    {
       if(pItem->mask & LVIF_IMAGE)
      {
         pItem->iImage = StdGetItemImage(pItem->iItem);
      }
    }

   *pResult = 0;
}

int AlbumSongCheckList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   if (AlbumSongList::OnCreate(lpCreateStruct) == -1)
      return -1;

   return 0;
}

void AlbumSongCheckList::_001InsertColumns()
{
//    CDBCentral * pDataCentral = db();

   Column column;

   column.m_iWidth = 18;
   column.m_iSubItem = SubItemIcon;
//   column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
   column.m_iSmallImageWidth = 16;
   _001AddColumn(column);

//   column.m_uiText = IDS_ALBUM_DELETE;
   column.m_iWidth = 50;
   column.m_iSubItem = SubItemDelete;
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


}

void AlbumSongCheckList::OnHeaderCtrlItemChanging(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMHEADER lpnmh = (LPNMHEADER) pNMHDR;
    
    LPHDITEM  lphdi = lpnmh->pitem;

    if((lpnmh->iItem == 0 ||
        lpnmh->iItem == 1 )&&
        (lphdi->mask & (HDI_WIDTH | HDI_ORDER )) != 0 )
    {
//        *pResult = TRUE;
                *pResult = FALSE;
    }
    else
    {
        *pResult = FALSE;
    }
}

void AlbumSongCheckList::OnFileAutodeleteduplicates() 
{
   // TODO: add your command handler code here
    stringa stra;
    
    GetCheckedPaths(&stra);

    LPTSTR lpstrv004 = stra.GetFormatV004();

    SHFILEOPSTRUCT shfops;
    shfops.hwnd = _get_handle();
    shfops.wFunc = FO_DELETE;
    shfops.pFrom = lpstrv004;
    shfops.pTo = NULL;
    shfops.fFlags = FOF_ALLOWUNDO;

    SHFileOperation(&shfops);

    free(lpstrv004);

    //UpdateList();
/*    db()->SongsPostBuildAlbumMessage(
        &System,
        SongsAlbum::eBuildSongsAlbumDeleteNotFound,
        false);*/
}

void AlbumSongCheckList::OnUpdateFileAutodeleteduplicates(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
    bool bEnable = false;
    for(int i = 0; i < m_dwaState.get_size(); i++)
    {
        if(m_dwaState.element_at(i) == 2)
        {
            bEnable = true;
            break;
        }
    }
    pcmdui->Enable(bEnable);
}

VMSRESULT AlbumSongCheckList::GetCheckedPaths(stringa * pstraPaths)
{
   UNREFERENCED_PARAMETER(pstraPaths);
/*    CDBSongRow * pSong;
    DoCache(0, m_dwaQueryKeys.get_size() - 1);
    for(int i = 0; i < m_dwaQueryKeys.get_size(); i++)
    {
        if(m_dwaState.element_at(i) == 2)
        {
             if(m_cacheMap.Lookup(i, pSong))
           {
                pstraPaths->add(pSong->GetPath());
            }
        }
    }*/
    return VMSR_SUCCESS;
}

UINT AlbumSongCheckList::ThreadProcUpdateList(
    LPVOID lpParameter)
{
    AlbumSongCheckList * lpascl = (AlbumSongCheckList *) lpParameter;
    lpascl->UpdateList_();
    return 0;
}

VMSRESULT AlbumSongCheckList::UpdateList_()
{
      m_dwaQueryKeys.remove_all();
    m_dwaState.remove_all();
    m_dwaGroup.remove_all();
//   m_cacheMap.remove_all();
    AlbumSongList::SetWhereClause("(((Song.CRC) In (SELECT [CRC] FROM [Song] As Tmp GROUP BY [CRC] HAVING Count(*)>1 )))");
//    m_pSongsSetAsynch->SetOrderClause("[Song].[CRC]");

  /*  CDBCentral * pDataCentral = db();
    HRESULT hr;
    if(FAILED(hr = m_pSongsSetAsynch->open(pDataCentral->GetDataSource(), false)))
    {
        return VMSR_E_FAIL;
    }
    
    if(FAILED(hr = m_pSongsSetAsynch->MoveFirst()))
    {
        return VMSR_SUCCESS;
    }
    
    if(hr == DB_S_ENDOFROWSET)
    {
        return VMSR_SUCCESS;
    }
    if(FAILED(hr = m_pSongsSetAsynch->get_data(10)))
    {
        return VMSR_E_FAIL;
    }

    if(FAILED(hr = m_pSongsSetAsynch->get_data(3)))
    {
        return VMSR_E_FAIL;
    }

    if(FAILED(hr = m_pSongsSetAsynch->get_data(0)))
    {
        return VMSR_E_FAIL;
    }

    int iLastKey = m_pSongsSetAsynch->m_iKey;
    int iKey;

    DWORD dwLastCRC = m_pSongsSetAsynch->m_iCRC;
    DWORD dwCRC;

    dword_array dwaKeys;
    stringa straPaths;

    dword_array dwaKeysN;
    stringa straPathsN;
    
    string strLastPath;
    string strFilePath;
   string   wstrFilePath;
    CDBComplement::DX_Text(false, &strLastPath, &m_pSongsSetAsynch->m_bstrPath,&m_pSongsSetAsynch->m_ulPathStatus);
    
    ex1::filesp fileA;
    ex1::filesp fileB;
    CMemoryStorage memstorageA(NULL);
    CMemoryStorage memstorageB(NULL);

    CFileFind findFile;

    bool bFirst = true;
    DWORD dwGroup = 0;
    
    while(true)
    {
        if(FAILED(hr = m_pSongsSetAsynch->MoveNext()))
        {
            break;
        }
    
        if(hr == DB_S_ENDOFROWSET)
        {
            break;
        }

        if(FAILED(hr = m_pSongsSetAsynch->get_data(10)))
        {
            return VMSR_E_FAIL;
        }

        if(FAILED(hr = m_pSongsSetAsynch->get_data(3)))
        {
            return VMSR_E_FAIL;
        }
        
        if(FAILED(hr = m_pSongsSetAsynch->get_data(0)))
        {
            return VMSR_E_FAIL;
        }

        iKey = m_pSongsSetAsynch->m_iKey;
        dwCRC = m_pSongsSetAsynch->m_iCRC;
        CDBComplement::DX_Text(
         false,
         wstrFilePath,
         &m_pSongsSetAsynch->m_bstrPath,
         &m_pSongsSetAsynch->m_ulPathStatus);

      CInternational::UnicodeToAnsi(strFilePath, wstrFilePath);

        if(dwCRC == dwLastCRC)
        {
            if(bFirst)
            {
                bFirst = false;
                straPaths.add(strLastPath);
                dwaKeys.add(iLastKey);
                
                straPaths.add(strFilePath);
                dwaKeys.add(iKey);
            }
            else
            {
                straPaths.add(strFilePath);
                dwaKeys.add(iKey);
            }

        }
        else
        {
         // Now, this routine will
         // verify if the last files that have equal CRC
         // (good candidates to be the identical files)
         // are really equal.
            ASSERT(straPaths.get_size() == 
                dwaKeys.get_size());
            while(straPaths.get_size() > 0)
            {
            while(straPaths.element_at(0).is_empty())
            {
               straPaths.remove_at(0);
               dwaKeys.remove_at(0);
               if(straPaths.get_size() <= 0)
                  break;
            }

            if(straPaths.get_size() <= 0)
               break;

                straPathsN.remove_all();
                dwaKeysN.remove_all();

                
                straPathsN.add(straPaths.element_at(0));
                dwaKeysN.add(dwaKeys.element_at(0));

                straPaths.remove_at(0);
                dwaKeys.remove_at(0);

                try
                {
                    if(!fileA.open(
                        straPathsN.element_at(0),
                        ::ex1::file::mode_read |
                    ::ex1::file::shareDenyWrite |
                   ::ex1::file::type_binary))
                  continue;
                    CArchive ar(&fileA, CArchive::load);
                    memstorageA.FullLoad(ar);
                    fileA.close();
                }
             catch(ex1::file_exception_sp *pfe)
             {
                pfe->ReportError();
    #ifdef _DEBUG
                pfe->dump(afxdump);
    #endif
                pfe->Delete();
                continue;
             }
                // find all files that are identical to fileA
                for(int j = 0; j < straPaths.get_size();)
                {
                    try
                    {
                        if(!fileB.open(
                            straPaths.element_at(j),
                            ::ex1::file::mode_read |
                        ::ex1::file::shareDenyWrite |
                       ::ex1::file::type_binary))
                     continue;
                        CArchive ar(&fileB, CArchive::load);
                        memstorageB.FullLoad(ar);
                        fileB.close();
                    }
                 catch(ex1::file_exception_sp *pfe)
                 {
                    pfe->ReportError();
        #ifdef _DEBUG
                    pfe->dump(afxdump);
        #endif
                    pfe->Delete();
                  j++;
                    continue;
                 }
                    if(memstorageA == memstorageB)
                    {
                        straPathsN.add(straPaths.element_at(j));
                        dwaKeysN.add(dwaKeys.element_at(j));
                        
                        straPaths.remove_at(j);
                        dwaKeys.remove_at(j);
                    }
                    else
                    {
                        j++;
                    }
                }
                
                if(straPathsN.get_size() > 1)
                {
                    // choose to preserve only the file with
                    // longer file title
                
                    int iMaxLen = 0;
                    int iLen;
                    int iPreserved = -1;
                    for(int i = 0; i < straPathsN.get_size(); i++)
                    {
                        iLen = straPathsN.element_at(i).get_length();
                        if(iLen > iMaxLen)
                        {
                            iMaxLen = iLen;
                            iPreserved = i;
                        }
                    }

                    if(iPreserved < 0)
                    {
                        iPreserved = 0;
                    }


                    for(i = 0; i < straPathsN.get_size(); i++)
                    {
                        m_dwaQueryKeys.add(dwaKeysN.element_at(i));
                        if(i == iPreserved)
                        {
                            m_dwaState.add(1);
                        }
                        else
                        {
                            m_dwaState.add(2);
                        }
                        m_dwaGroup.add(dwGroup);
                    }
                    dwGroup++;
                }
            }

            bFirst = true;

            straPaths.remove_all();
            dwaKeys.remove_all();

            dwLastCRC = dwCRC;

            SetItemCountEx_(m_dwaQueryKeys.get_size(), LVSICF_NOSCROLL | LVSICF_NOINVALIDATEALL);
        }

        
        strLastPath = strFilePath;
        iLastKey = iKey;

    }*/
    
    //SetItemCountEx(m_dwaQueryKeys.get_size(), LVSICF_NOSCROLL);

    //DoCache(0, m_dwaQueryKeys.get_size() - 1);
    return VMSR_SUCCESS;

}

int AlbumSongCheckList::StdGetItemImage(int iItem)
{
 
   if(iItem >= m_dwaState.get_size())
   {
      return -1;
   }
   else
    {
        int iState = m_dwaState.element_at(iItem);
        if((iState & 3) == 1)
        {
            return 0;
        }
        else
        {
            return 9;
        }
    }
}
