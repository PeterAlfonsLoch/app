#include "StdAfx.h"
#include "AlbumMainView.h"
#include "AlbumSongList.h"
#include "AlbumSearchFormView.h"
#include "AlbumTree.h"
#include "AlbumSongCheckList.h"
#include "AlbumSearchFormView.h"
#include "AlbumViewUpdateHint.h"

const int AlbumMainView::cnListCount = 9;

AlbumMainView::AlbumMainView(::ca::application * papp) :
   ca(papp),
   ::userbase::view(papp),      
   m_SmallImageList(papp),
   m_SmallImageListV001(papp),
   m_layoutFull(papp),
   m_layoutSongExplorer(papp),
   _layoutSearch(papp),
   m_layoutDuplicates(papp)
{
//   _001AttemptToInstallHook();
//   DISetSection("AlbumMainView");
//   db()->AddListener(this);
//   m_pfolderlistctrl = new C017SimpleFolderListCtrl();
   //m_ptwbListBackBuffer = new CTransparentWndBuffer();
//   m_iCacheNextIndex = 0;
   m_plistFull = new AlbumSongList(get_app());
   m_plistTree = new AlbumSongList(get_app());
   m_ptree = new AlbumTree(get_app());
//   m_psongsset = new CDBSongSet(DBDataCentral());
   //m_pstrlist = new CStrList();
   m_plistDuplicates = new AlbumSongCheckList(get_app());

   m_psearchformview = new AlbumSearchFormView(papp);
   m_plistSearch = new AlbumSongList(get_app());

//   ::ca::type_info pRuntimeClass = &typeid(AlbumHtmlView);
//   ::radix::object* pObject = pRuntimeClass->CreateObject();
//   ASSERT(base < AlbumHtmlView >::bases(pObject));
//    m_phtmlview = (AlbumHtmlView *) pObject;

    m_bFullListNeedUpdate = false;
    m_bSongExplorerNeedUpdate = false;
   m_bExplorerNeedUpdate = false;
    m_bSearchListNeedUpdate = false;
    m_dwUpdateTime = 0;
    TRACE("AlbumFormView this = %x \n", this);
}

AlbumMainView::~AlbumMainView()
{
//   if(m_ptwbListBackBuffer != NULL)
//      delete m_ptwbListBackBuffer;
//   HANDLE hHeap = GetProcessHeap();
//   CSongBase *pSongBase;
//   for(int i = m_cacheArray.get_size(); --i >=0 ;)
//   {
//      pSongBase = m_cacheArray[i];
//      delete pSongBase;
//      m_cacheArray.remove_at(i);
      //pSongBase->Destruct();
      //HeapFree(hHeap, 0, pSongBase);
      //delete
      //delete m_cacheArray.get_at(i);
//   }
///   if(m_plistFull != NULL)
   //   delete m_plistFull;
//   if(m_psongsset != NULL)
//      delete m_psongsset;
//   if(m_pstrlist != NULL)
//      delete m_pstrlist;
//   if(m_plistTree != NULL)
//      delete m_plistTree;
//   if(m_ptree != NULL)
//      delete m_ptree;
//   if(m_psearchformview != NULL)
//      delete m_psearchformview;
//   if(m_plistSearch != NULL)
//      delete m_plistSearch;

  //  if(m_plistDuplicates != NULL)
    //{
      //  delete m_plistDuplicates;
        //m_plistDuplicates = NULL;
    //}
/*   if(m_pfolderlistctrl != NULL)
   {
      delete m_pfolderlistctrl;
      m_pfolderlistctrl = NULL;
   }*/
}

//void AlbumMainView::DoDataExchange(CDataExchange* pDX)
//{
//::userbase::view::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AlbumMainView)
      // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
//}


 // BEGIN_MESSAGE_MAP(AlbumMainView, ::userbase::view)
/*   //{{AFX_MSG_MAP(AlbumMainView)
   ON_WM_SIZE()
   ON_WM_DESTROY()
   ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
   ON_BN_CLICKED(IDC_BUTTON_RESERVE, OnButtonReserve)
   ON_WM_CLOSE()
   ON_WM_CREATE()
   ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
   ON_NOTIFY(NM_DBLCLK, IDC_STRLIST, OnItemdblclickStrlist)
   ON_WM_TIMER()
   ON_WM_CONTEXTMENU()
   ON_COMMAND(ID_ALBUM_UPDATE, OnAlbumUpdate)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_UPDATE, OnUpdateAlbumUpdate)
   ON_COMMAND(ID_ALBUM_RESERVESONG, OnAlbumReserveSong)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_RESERVESONG, OnUpdateAlbumReserveSong)
   ON_COMMAND(ID_VIEW_UPDATE, OnViewUpdate)
   ON_UPDATE_COMMAND_UI(ID_VIEW_UPDATE, OnUpdateViewUpdate)
   ON_COMMAND(ID_ALBUM_FULLBUILD, OnAlbumFullbuild)
   ON_COMMAND(ID_ALBUM_PARTIALBUILD, OnAlbumPartialbuild)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_PARTIALBUILD, OnUpdateAlbumPartialbuild)
   ON_WM_INITMENUPOPUP()
   ON_NOTIFY(NM_SETFOCUS, IDC_FULLLIST, OnSetfocusFulllist)
   ON_NOTIFY(LVN_ODSTATECHANGED, IDC_FULLLIST, OnOdstatechangedList)
   ON_NOTIFY(NM_CLICK, IDC_FULLLIST, OnClickList)
   ON_NOTIFY(NM_RCLICK, IDC_FULLLIST, OnRclickList)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_FULLBUILD, OnUpdateAlbumFullbuild)
   ON_WM_SHOWWINDOW()
   ON_WM_ERASEBKGND()
   ON_COMMAND(ID_ALBUM_FULLLIST, OnAlbumFullList)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_FULLLIST, OnUpdateAlbumFullList)
   ON_COMMAND(ID_ALBUM_SEARCHLIST, OnAlbumSearchList)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_SEARCHLIST, OnUpdateAlbumSearchList)
   ON_COMMAND(ID_ALBUM_EXPLORER, OnAlbumExplorer)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_EXPLORER, OnUpdateAlbumExplorer)
   ON_COMMAND(ID_ALBUM_SONGEXPLORER, OnAlbumSongExplorer)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_SONGEXPLORER, OnUpdateAlbumSongExplorer)
   ON_COMMAND(ID_ALBUM_NAVIGATOR, OnAlbumNavigator)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_NAVIGATOR, OnUpdateAlbumNavigator)
   ON_COMMAND(ID_ALBUM_DUPLICATESLIST, OnAlbumDuplicatesList)
   ON_UPDATE_COMMAND_UI(ID_ALBUM_DUPLICATESLIST, OnUpdateAlbumDuplicatesList)
   ON_COMMAND(ID_MSWORD9, OnMsword9)
   ON_UPDATE_COMMAND_UI(ID_MSWORD9, OnUpdateMsword9)
   ON_COMMAND(ID_VIEW_NOTEPAD, OnViewNotepad)
   ON_NOTIFY(NM_SETFOCUS, IDC_LIST, OnSetfocusFulllist)
   ON_NOTIFY(NM_SETFOCUS, IDC_LIST_SEARCH, OnSetfocusFulllist)
   ON_NOTIFY(NM_SETFOCUS, IDC_LIST_DUPLICATES, OnSetfocusFulllist)
   ON_NOTIFY(LVN_ODSTATECHANGED, IDC_LIST, OnOdstatechangedList)
   ON_NOTIFY(LVN_ODSTATECHANGED, IDC_LIST_SEARCH, OnOdstatechangedList)
   ON_NOTIFY(LVN_ODSTATECHANGED, IDC_LIST_DUPLICATES, OnOdstatechangedList)
   ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
   ON_NOTIFY(NM_CLICK, IDC_LIST_SEARCH, OnClickList)
   ON_NOTIFY(NM_CLICK, IDC_LIST_DUPLICATES, OnClickList)
   ON_NOTIFY(NM_DBLCLK, IDC_FULLLIST, OnDblclkList)
   ON_NOTIFY(NM_DBLCLK, IDC_LIST_SEARCH, OnDblclkList)
   ON_COMMAND(ID_EXPLORE_UP, OnExploreUp)
   //}}AFX_MSG_MAP
   ON_MESSAGE(WM_USER, OnUserMessage)*/
 // END_MESSAGE_MAP()

#ifdef _DEBUG
void AlbumMainView::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void AlbumMainView::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}
#endif
/////////////////////////////////////////////////////////////////////////////
// AlbumMainView message handlers

void AlbumMainView::layout() 
{
   //::userbase::view::OnSize(nType, cx, cy);

   rect clientRect;
   
   GetClientRect(clientRect);
   

//   m_layoutNavigator.SetPlacement(clientRect);
   m_layoutFull.set_placement(clientRect);
   //m_explorer.SetPlacement(clientRect);
   m_layoutSongExplorer.set_placement(clientRect);
   //m_layoutSearch.SetPlacement(clientRect);
   m_layoutDuplicates.set_placement(clientRect);
   
}

void AlbumMainView::OnInitialUpdate() 
{
    wait_cursor cwc(get_app());

//   db_server *pDataCentral = (db_server *) db();

//   m_pdatasource = pDataCentral->GetDataSource();

//   ::ca::window * pWnd = GetParent();

//   if(db()->IsWorking())
//   {

      if(FAILED(OpenSongsSetIndexedKey()))
      {
         if(FAILED(OpenSongsSet(NULL, true)))
         {
            System.simple_message_box(NULL, "Record set failed to open.", MB_OK);
         }
      }

   
//      if(pDataCentral->GetDataSource()->m_spInit == NULL)
//         return ;
//   }


/*    HINSTANCE hinstance = _Module.GetModuleInstance();

    HICON hIcon = (HICON) LoadImage(hinstance,
        MAKEINTRESOURCE(IDI_ALBUM),
        IMAGE_ICON,
        16, 16,
        0);

    SetIcon(hIcon, false);

    hIcon = (HICON) LoadImage(hinstance,
        MAKEINTRESOURCE(IDI_ALBUM),
        IMAGE_ICON,
        0, 0,
        LR_DEFAULTSIZE);

    SetIcon(hIcon, true);
*/

   
   return;
}


void AlbumMainView::_001OnDestroy(gen::signal_object * pobj) 
{
//   try
//   {
   //CVMSApp *pApp = (CVMSApp *) &System;
//   db_server *pDataCentral = (db_server *) db();
//   CDBLongSet *pLongsSet = pDataCentral->get_db_long_set();

//   pLongsSet->SaveWindowCoordinates(
//      "Janelas",
//      "Álbum",
//      this);
   
/*   CListCtrl *pList = (CListCtrl *) GetDescendantWindow(IDC_FULLLIST);
   if(pList != NULL)
   {
//      int width;
      int i;
      string str;
      for(i = 0; i < cnListCount; i++)
      {
         str.Format("Album.FullList.Column[%d].width", i);
         pLongsSet->Save(
            "Janelas",
            str,
            pList->GetColumnWidth(i));
      }
   
/*   int * iaOrder = new int[m_plistFull->StdGetColumnCount()];
   m_plistFull->GetColumnOrderArray(iaOrder, m_plistFull->StdGetColumnCount());
   for(i = 0; i < m_plistTree->STdGetColumnCount(); i++)
   {
      str.Format("Album.FullList.Column[%d].Order", i);
      pDataCentral->get_db_long_set()->Save(
         "Janelas",
         str,
         iaOrder[i]);
   }
   
   m_plistTree->GetColumnOrderArray(iaOrder, m_plistFull->GetColumnCount());
   for(i = 0; i < m_plistTree->GetColumnCount(); i++)
   {
      str.Format("Album.List.Column[%d].Order", i);
      pDataCentral->get_db_long_set()->Save(
         "Janelas",
         str,
         iaOrder[i]);
   }
   
   delete [] iaOrder;
   m_plistFull->m_pSongsSetAsynch->SaveColumnSortArray(pDataCentral->get_db_long_set(), "Album.FullList.ColumnSort");
   m_plistTree->m_pSongsSetAsynch->SaveColumnSortArray(pDataCentral->get_db_long_set(), "Album.List.ColumnSort");
    pDataCentral->get_db_long_set()->Save("Janelas", "Álbum.::view", m_eviewCurrent);
   }
   } catch(COLEDBException *e)
   {
      CDBErrorDialog dlg;
      dlg.Init(e->m_spUnk, e->m_iid);
      dlg.DoModal();
      e->Delete();
      return;
   }*/
//   CMainFrame *pFrame = (CMainFrame *) theApp.GetMainWnd();
//   if(pFrame != NULL)
//   {
//      pFrame->m_pAlbumDialog = NULL;
//   }
   ::userbase::view::_001OnDestroy(pobj);
   
   // TODO: add your message handler code here
   
}




void AlbumMainView::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: add your control notification handler code here
   LPNMLISTVIEW lpnmlv = (LPNMLISTVIEW) pNMHDR;
   AlbumSongList * plist = dynamic_cast < AlbumSongList * > (GetDescendantWindow(lpnmlv->hdr.idFrom));
   if(plist != NULL)
   {
//      ReserveSelectedItems(*plist);
   }
   *pResult = 0;
}

void AlbumMainView::OnButtonReserve() 
{
   // TODO: add your control notification handler code here
   ReserveSelectedItems();
}

void AlbumMainView::ReserveSelectedItems()
{
    ASSERT(FALSE);
    return;
/*   CVMSApp *pApp = (CVMSApp *) &System;
   db_server *pDataCentral = (db_server *) db();
   CDBSongSet *pSet = pDataCentral->GetSongsSet();
   CListCtrl *pList = (CListCtrl *) GetDescendantWindow(IDC_LIST);
   CMainFrame *pFrame = (CMainFrame *) pApp->GetMainWnd();
   POSITION pos = pList->GetFirstSelectedItemPosition();
   while(pos != NULL)
   {
      int iIndex = pList->GetNextSelectedItem(pos);
      if(pSet->FindOrdinal(iIndex))
      {
         pSet->get_data(1);
//         pFrame->m_ReserveList.AddSong(pSet->m_iCode);
      }
   }
   pFrame->UpdateReserveList();*/

}

/*void AlbumMainView::ReserveSelectedItems(AlbumSongList & list)
{
    ::ca::application *pApp = &System;
   simple_list_control::Range selection;
   list._001GetSelection(selection);
    dword_array * pdwa  = new dword_array();
   int i = 0;
   int iItem;
    while((iItem = selection.get_item(i)) >= 0)
    {
      i++;
       int iKey = list.m_dwaQueryKeys.get_at(iItem);
       if(!m_psongsset->FindKey(iKey))
         if(FAILED(OpenSongsSetIndexedKey()))
         {
            if(FAILED(OpenSongsSet(NULL, true)))
            {
               System.simple_message_box("Record set failed to open.", MB_OK);
            }
         }

      if(m_psongsset->FindKey(iKey))
       {
            m_psongsset->get_data(1);
          pdwa->add(m_psongsset->m_iCode);
//            pPlaylistDoc->AddSong(m_psongsset->m_iCode);
       }
    }
    pdwa->insert_at(0, pdwa->get_size());
    pApp->PostThreadMessage(WM_USER, 22, (LPARAM) pdwa);
   //CListCtrl *pList = (CListCtrl *) GetDescendantWindow(IDC_LIST);
   /*AlbumSongList * pAlbumList = (AlbumSongList *)pList;
   CVMSApp *pApp = (CVMSApp *) &System;
    CXfplayerDoc * pPlayerDoc  = pApp->GetPlayerDocument();

    if(pPlayerDoc == NULL)
    {
        pPlayerDoc = (CXfplayerDoc *) pApp->GetPlayerDocTemplate()->open_document_file(NULL);
    }

    if(pPlayerDoc != NULL)
    {
        CXfplayerView * pLyricView = pPlayerDoc->GetLyricView();
        if(pLyricView != NULL)
        {
            //CPlaylistView * pPlaylistView = pLyricView->GetPlaylistView();
            playlist_document * pPlaylistDoc = pLyricView->GetPlaylistDoc();
            //if(pPlaylistView == NULL)
            if(pPlaylistDoc == NULL)
            {
                multiple_document_template * pPlaylistDocTemplate = pApp->GetPlaylistDocTemplate();
                pPlaylistDoc
                 = (playlist_document *) pPlaylistDocTemplate->open_document_file(NULL);
                pLyricView->AttachPlaylistDoc(pPlaylistDoc);
//                pPlaylistView = pPlaylistDoc->GetPlaylistView();
            }
//            else
  //          {
    //            pPlaylistDoc = pPlaylistView->get_document();
      //      }
            

             CMainFrame *pFrame = (CMainFrame *) pApp->GetMainWnd();
           pFrame->UpdateReserveList();
        }
    }*/

//}


void AlbumMainView::OnClose() 
{
   // TODO: add your message handler code here and/or call default
   
   //OnDestroy();
//   DestroyWindow();
//   CVMSApp *pApp = (CVMSApp *) &System;
//   CMainFrame *pFrame = (CMainFrame *) pApp->GetMainWnd();
//   if(pFrame != NULL)
//   {
//      
//      delete pFrame->m_pAlbumDialog;
//      pFrame->m_pAlbumDialog = NULL;
//   }
//::userbase::view::OnClose();
}


afx_msg LRESULT AlbumMainView::OnUserMessage(WPARAM wParam, LPARAM lParam)
{
   if(wParam == 0)
   {
      if(lParam == 0)
      {
//         m_explorer.Browse(CSIDL_DESKTOP);
      }
   }
   else if(wParam == 1)
   {
//   AFX_MANAGE_STATE(AfxGetAppModuleState());
//      CSongBase * pSong;
      int dummy = 1;
   }
    else if(wParam == 2)
   {
      string str;
      int iCount = lParam;
      if(iCount <= 0)
      {
/*            str.load_string(IDS_ALBUM_NOTFOUNDINDICATOR);
            GetParentFrame()->SendMessage(WM_USER, 51678, (LPARAM)(const char *) str);
*/           
      }
      else
      {
/*           str.Format(IDS_ALBUM_FOUNDINDICATOR, iCount);
            GetParentFrame()->SendMessage(WM_USER, 51678, (LPARAM)(const char *) str);
*/
      }

   }
    else if(wParam == 3)
    {
        Update(m_eviewCurrent);
    }
    else if(wParam == 33)
    {
//       LPMENUV033CONTEXTMENU lpmcm = (LPMENUV033CONTEXTMENU) lParam;
//        lpmcm->nPopupID = GetPopupMenuId(lpmcm->nControlID);
    }

    else if(wParam == 789)
    {
      AlbumSongList * plist = GetCurrentAlbumSongList();
      if(plist != NULL)
      {
         UpdateStatus(plist);
      }
    }
    else if(wParam == 10)
    {
        CDBSongSet **ppSet = (CDBSongSet **)lParam;
        *ppSet = m_psongsset;
    }
    else if(wParam == 11)
    {
        if(FAILED(OpenSongsSetIndexedKey()))
       {
          if(FAILED(OpenSongsSet(NULL, true)))
          {
             return 0;
          }
       }
        return -1;
    }
    else if(wParam == 1117)
    {
//      CWStrArray * lpwstrarray = (CWStrArray *) lParam;
//      CWStrArray * lpwstrarrayNew = new CWStrArray();
//      lpwstrarrayNew->copy(*lpwstrarray);
/*      stringa * lpstrarray = new stringa;
      for(int i = 0; i < lpwstrarray->get_size(); i++)
      {
         string str;
         CInternational::UnicodeToOEM(str, lpwstrarray->element_at(i));
         lpstrarray->add(str);
      }*/
      
//      System.PostThreadMessage(WM_USER, 24, (LPARAM) lpwstrarrayNew);

        return -1;
    }

   return TRUE;
}

void AlbumMainView::pre_translate_message(gen::signal_object * pobj) 
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   // TODO: add your specialized code here and/or call the base class
//   if(pMsg->message == WM_USER)
//   {
  //      if(pMsg->hwnd == m_hWnd)
    //    {
   //       OnUserMessage(pMsg->wParam, pMsg->lParam);
   //       return TRUE;
      //  }
//   }
//   else if(pMsg->message == WM_DISPLAYCHANGE)
   if(pbase->m_uiMessage == WM_DISPLAYCHANGE)
   {
      SetImageLists();
   }
   //if(pMsg->message == WM_USER
   //   && pMsg->hwnd == get_handle())
   //{
//      m_explorer.Browse(CSIDL_DESKTOP);
   //}

   ::userbase::view::pre_translate_message(pobj);
}

/*BOOL AlbumMainView::create(UINT nID) 
{
   // TODO: add your specialized code here and/or call the base class
   
   return create(MAKEINTRESOURCE(nID), NULL);
}*/

void AlbumMainView::_001OnCreate(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::create, pcreate, pobj);
    wait_cursor cwc(get_app());

   pobj->previous();


    rect clientRect(0, 0, 0, 0);


//   if(!m_explorer.create(this, 10113))
//      return -1;
//   m_explorer.SetOwner(this);



   m_plistFull->m_dataid = "Album.FullList";
//   m_plistFull->_001SetBackBuffer(m_ptwbListBackBuffer);
/*   if(!m_plistFull->create(
      WS_CHILD
      | WS_VISIBLE,
      clientRect,
      this,
      IDC_FULLLIST))
   {
      pcreate->set_lresult(-1);
      return;
   }*/
   m_plistFull->SetOwner(this);
   m_plistFull->SetWindowText("Album.FullList");
    m_plistFull->Initialize();
//    m_plistFull->GetHeaderCtrl()->SetDlgCtrlID(IDC_LISTHEADER_FULL);

   m_plistDuplicates->m_dataid = "Album.DuplicatesList";
   //m_plistDuplicates->_001SetBackBuffer(m_ptwbListBackBuffer);
/*   m_plistDuplicates->create(
      LVS_REPORT
      | WS_VISIBLE,
      clientRect,
      this,
      IDC_LIST_DUPLICATES);*/
   m_plistDuplicates->SetWindowText("Album.DuplicatesList");
    m_plistDuplicates->Initialize();
    //m_plistDuplicates->GetHeaderCtrl()->SetDlgCtrlID(IDC_LISTHEADER_DUPLICATES);
    
/*   m_ptree->create(
//      TVS_HASLINES |
      TVS_LINESATROOT |
      TVS_SHOWSELALWAYS |
      TVS_NOTOOLTIPS |
      TVS_HASBUTTONS
      | WS_VISIBLE,
      clientRect,
      this,
      IDC_TREE);*/
    m_plistTree->m_dataid = "Album.TreeList";
//   m_plistTree->_001SetBackBuffer(m_ptwbListBackBuffer);
   /*m_plistTree->create(
      LVS_REPORT
      | WS_VISIBLE,
      clientRect,
      this,
      IDC_LIST);*/
   m_plistTree->SetWindowText("Album.TreeList");
    m_plistTree->Initialize();
//    m_plistTree->GetHeaderCtrl()->SetDlgCtrlID(IDC_LISTHEADER_TREE);
/*   m_pstrlist->create(
      LVS_REPORT
      | WS_VISIBLE,
      clientRect,
      this,
      IDC_STRLIST);*/
    

   m_psearchformview->SetAlbumSongList(m_plistSearch);
/*    m_psearchformview->create(
        NULL,
        NULL,
        WS_VISIBLE | WS_CHILD,
        rect(0, 0, 0, 0),
        this,
        IDD_ALBUM_SEARCH,
        NULL);*/
//   m_plistSearch->DISetSection("Album.SearchList");
//   m_plistSearch->_001SetBackBuffer(m_ptwbListBackBuffer);
    /*m_plistSearch->create(
      LVS_REPORT
      | WS_VISIBLE,
      clientRect,
      this,
      IDC_LIST_SEARCH);*/
   m_plistSearch->SetWindowText("Album.SearchList");
    m_plistSearch->Initialize();
//    m_plistSearch->GetHeaderCtrl()->SetDlgCtrlID(IDC_LISTHEADER_SEARCH);


/*    m_phtmlview->create(
        NULL, NULL,
        WS_CHILD
      | WS_VISIBLE,
        rect(0, 0, 0, 0),
        this,
        IDC_HTMLVIEW,
        NULL);*/
   
//   m_pstrlist->m_iImage = 1;

//   SetImageLists();

/*   m_layoutNavigator.create(
      this,
        0,
      1,
      CSplitLayout::orientation_horizontal);*/
/*   m_layoutNavigator.SetPane(
      0,
      m_phtmlview,
        false);*/

   /*m_layoutFull.create(
      this,
        0,
      1,
      CSplitLayout::orientation_horizontal);
   m_layoutFull.SetPane(
      0,
      m_plistFull,
        false);*/

/*   m_layoutExplore.SetPane(
      1,
      m_pstrlist,
      false);
   m_layoutExplore.SetPane(
      1,
      m_plistTree,
      false);
   m_layoutExplore.SetPosition(
      0,
      200);
   m_layoutExplore.SetVisible(FALSE);
*/

/*   m_layoutSongExplorer.create(
      this,
        0,
      2,
      CSplitLayout::orientation_vertical);
   m_layoutSongExplorer.SetPane(
      0,
      m_ptree,
        false);
   m_layoutSongExplorer.SetPane(
      1,
      m_pstrlist,
      false);
   m_layoutSongExplorer.SetPane(
      1,
      m_plistTree,
      false);
   m_layoutSongExplorer.SetPosition(
      0,
      200);
   m_layoutSongExplorer.SetVisible(FALSE);

   m_layoutSearch.create(
      this,
        0,
      2,
      CSplitLayout::orientation_vertical);
   m_layoutSearch.SetPane(
      0,
      m_psearchformview,
        true);
    {
        rect rect;
        m_psearchformview->GetWindowRect(rect);
        size size = rect.size();
        m_layoutSearch.SetPaneFixedSize(0, &size);
    }
   m_layoutSearch.SetPane(
      1,
      m_plistSearch,
        false);
   m_layoutSearch.SetPosition(
      0,
      300);
   m_layoutSearch.SetVisible(FALSE);

   m_layoutDuplicates.create(
      this,
        0,
      1,
      CSplitLayout::orientation_horizontal);
   m_layoutDuplicates.SetPane(
      0,
      m_plistDuplicates,
        false);*/


//   CVMSApp *pApp = (CVMSApp *) &System;
   //::userbase::view::OnInitialUpdate();
   //db_server *pDataCentral = (db_server *) db();
   //CDBLongSet *pLongsSet = pDataCentral->get_db_long_set();
   
   //CListCtrl *pList = (CListCtrl *) GetDescendantWindow(IDC_LIST);
   //ASSERT(pList != NULL);
/*    int i;
   int * iaOrder = new int[m_plistFull->GetColumnCount()];
    string str;
   for(i = 0; i < m_plistTree->GetColumnCount(); i++)
   {
      str.Format("Album.FullList.Column[%d].Order", i);
      iaOrder[i] = i;
      pDataCentral->get_db_long_set()->Load(
         "Janelas",
         str,
         &iaOrder[i]);
        if(iaOrder[i] < 0)
            iaOrder[i] = 0;
        if(iaOrder[i] >= m_plistFull->GetColumnCount())
            iaOrder[i] = m_plistFull->GetColumnCount() - 1;
   }
   m_plistFull->SetColumnOrderArray(m_plistFull->GetColumnCount(), iaOrder);
   

   for(i = 0; i < m_plistTree->GetColumnCount(); i++)
   {
      str.Format("Album.List.Column[%d].Order", i);
      iaOrder[i] = i;
      pDataCentral->get_db_long_set()->Load(
         "Janelas",
         str,
         &iaOrder[i]);
        if(iaOrder[i] < 0)
            iaOrder[i] = 0;
        if(iaOrder[i] >= m_plistTree->GetColumnCount())
            iaOrder[i] = m_plistTree->GetColumnCount() - 1;
   }
   m_plistTree->SetColumnOrderArray(m_plistFull->GetColumnCount(), iaOrder);
   
   delete [] iaOrder;*/

//   m_plistFull->m_pSongsSetAsynch->LoadColumnSortArray(pDataCentral->get_db_long_set(), "Album.FullList.ColumnSort");
   //m_plistFull->UpdateList();

//   m_plistTree->m_pSongsSetAsynch->LoadColumnSortArray(pDataCentral->get_db_long_set(), "Album.List.ColumnSort");
   //m_plistTree->UpdateList();
   // TODO: add extra initialization here
   
//    m_plistSearch->SetWhereClause("IsNull(Key)");
  //  m_plistTree->SetWhereClause("IsNull(Key)");
    //m_uiUpdateTimer = SetTimer(UpdateTimer, 1000, NULL);

    
//    SetWindowPos(0,0,0,0,0,SWP_NOSIZE | SWP_NOMOVE);

   m_bFullListNeedUpdate = true;
   m_bSongExplorerNeedUpdate = true;
   m_bExplorerNeedUpdate = true;
   m_bSearchListNeedUpdate = true;
   m_bHtmlViewNeedUpdate = true;

   m_eviewCurrent = ViewNoView;

   PostMessage(WM_USER, 0, 0);


}


BOOL AlbumMainView::PreCreateWindow(CREATESTRUCT& cs) 
{
   // TODO: add your specialized code here and/or call the base class
   cs.style = cs.style;
   int i = WS_POPUP;
   //cs.dwExStyle = cs.dwExStyle | WS_EX_APPWINDOW;
    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    cs.style |= WS_CLIPCHILDREN;
   return ::userbase::view::PreCreateWindow(cs);
}


void AlbumMainView::SetImageLists()
{
   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateDC(
      "DISPLAY",
      NULL,
      NULL,
      NULL);
    //CTabCtrl * pTab = (CTabCtrl *) GetDescendantWindow(IDC_TAB);
//   if(m_SmallImageList.GetSafeHandle() != NULL)
   {
/*      m_plistFull->SetImageList(NULL, LVSIL_SMALL   );
      m_ptree->SetImageList(NULL, TVSIL_NORMAL   );
      m_plistTree->SetImageList(NULL, LVSIL_SMALL   );
      m_pstrlist->SetImageList(NULL, LVSIL_SMALL   );
        m_plistSearch->SetImageList(NULL, LVSIL_SMALL   );
        m_plistDuplicates->SetImageList(NULL, LVSIL_SMALL   );
        m_plistDuplicates->GetHeaderCtrl()->SetImageList(NULL);*/
      //  pTab->SetImageList(NULL);
   }
   int iBitCount = spgraphics->GetDeviceCaps(BITSPIXEL);
   if(iBitCount > 8)
   {
/*      m_SmallImageListBitmap.delete_object();
      m_SmallImageListBitmap.LoadBitmap(IDB_ALBUM_SMALL_256);
      m_SmallImageListBitmapV001.delete_object();
      m_SmallImageListBitmapV001.LoadBitmap(IDB_ALBUM_SMALL_256);
      m_SmallImageList.create(
         16, 16,
         ILC_COLOR32 |
         ILC_MASK,
         2,
         1);
      m_SmallImageListV001.create(
         16, 16,
         ILC_COLOR32 |
         ILC_MASK,
         2,
         1);*/
        //m_SmallImageList.SetBkColor(CLR_NONE);
        /*m_SmallImageList.SetBkColor(GetSysColor(COLOR_WINDOW));
      m_SmallImageList.add(&m_SmallImageListBitmap, RGB(255, 0, 255));
        m_SmallImageListV001.SetBkColor(GetSysColor(COLOR_BTNFACE));
      m_SmallImageListV001.add(&m_SmallImageListBitmapV001, RGB(255, 0, 255));
        */
   }
   else
   {
/*      m_SmallImageListBitmap.delete_object();
      m_SmallImageListBitmap.LoadBitmap(IDB_ALBUM_SMALL_16);
      m_SmallImageListBitmapV001.delete_object();
      m_SmallImageListBitmapV001.LoadBitmap(IDB_ALBUM_SMALL_16);
      m_SmallImageList.create(
         16, 16,
         ILC_COLOR32 |
         ILC_MASK,
         2,
         1);
      m_SmallImageListV001.create(
         16, 16,
         ILC_COLOR32 |
         ILC_MASK,
         2,
         1);
        m_SmallImageList.SetBkColor(CLR_NONE);
      m_SmallImageList.add(&m_SmallImageListBitmap, RGB(255, 0, 255));
        m_SmallImageListV001.SetBkColor(CLR_NONE);
      m_SmallImageListV001.add(&m_SmallImageListBitmapV001, RGB(255, 0, 255));
  */      
   }
//   if(m_SmallImageList.GetSafeHandle() != NULL)
   {
/*      m_plistFull->SetImageList(&m_SmallImageList, LVSIL_SMALL   );
      m_ptree->SetImageList(&m_SmallImageList, TVSIL_NORMAL   );
      m_plistTree->SetImageList(&m_SmallImageList, LVSIL_SMALL   );
      m_pstrlist->SetImageList(&m_SmallImageList, LVSIL_SMALL   );
        m_plistSearch->SetImageList(&m_SmallImageList, LVSIL_SMALL   );
       m_plistDuplicates->SetImageList(&m_SmallImageList, LVSIL_SMALL   );
       m_plistDuplicates->GetHeaderCtrl()->SetImageList(&m_SmallImageListV001);*/
   }
//if(m_SmallImageListV001.GetSafeHandle() != NULL)
   {
//        pTab->SetImageList(&m_SmallImageListV001);
        
   }

   
   spgraphics->DeleteDC();
}

void AlbumMainView::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
   m_cs.Lock();
/*   NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
   // TODO: add your control notification handler code here
//   CTreeCtrl * pTree = (CTreeCtrl *) GetDescendantWindow(IDC_TREE);
   HTREEITEM hItem = pNMTreeView->itemNew.hItem;
   HTREEITEM hParent = m_ptree->GetParentItem(hItem);
   string strText(m_ptree->GetItemText(hItem));
   strText.replace("'", "''");
   //string * pStr;
   string str;
    for(int i = 0; i < m_ptree->m_gdv001a.get_size(); i++)
    {
        AlbumTree::CGroupDataV001 & rgdv001 = m_ptree->m_gdv001a.element_at(i);
       if(m_ptree->IsItemDescendantOf(
          rgdv001.m_hti,
          hItem) &&
          m_ptree->GetChildItem(hItem) == NULL)
        {
            str += rgdv001.m_lpcszTable;
          str += ".Text = '";
          str += strText;
          str += "'";
          m_plistTree->SetWhereClause(str);
            str.Format(_T(
                "%s \
                INNER JOIN (%s \
                INNER JOIN %s \
                ON %s.Key = %s.%s) \
                ON %s.Key = %s.%s"),
                CDBSongSet::GetTableName(),
                rgdv001.m_lpcszTable,
                rgdv001.m_lpcszTableSong,
                rgdv001.m_lpcszTable,
                rgdv001.m_lpcszTableSong,
                rgdv001.m_lpcszField,
                CDBSongSet::GetTableName(),
                rgdv001.m_lpcszTableSong,
                rgdv001.m_lpcszFieldSong);
          m_plistTree->SetFromClause(str);
          m_plistTree->UpdateList(NULL);
          if(m_pstrlist->GetStyle() & WS_VISIBLE)
          {
             m_pstrlist->ShowWindow(SW_HIDE);
          }
          if(!(m_plistTree->GetStyle() & WS_VISIBLE))
          {
             m_plistTree->ShowWindow(SW_SHOW);
          }
          m_layoutSongExplorer.SetPane(
             1,
             m_plistTree,
                false);
          m_layoutSongExplorer.layout();
            break;
        }
       else if(m_ptree->IsItemDescendantOf(
          rgdv001.m_hti,
          hItem) ||
          hItem == rgdv001.m_hti)
       {
          ShowStrList(rgdv001.m_lpcszTable, rgdv001.m_hti, hItem);
            break;
       }
    }


/*   if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hAuthor,
      hItem) &&
      m_ptree->GetChildItem(hItem) == NULL)
   {
//      str = "InStr(Author, '";
//      str += strText;
//      str += "') > 0";
        str += CDataCentral::m_lpcszTableAuthor;
      str += ".Text = '";
      str += strText;
      str += "'";
      m_plistTree->SetWhereClause(str);
        str.Format(_T(
            "%s \
            INNER JOIN (Author \
            INNER JOIN AuthorSong \
            ON Author.Key = AuthorSong.Author) \
            ON %s.Key = AuthorSong.Song"),
            CDBSongSet::GetTableName(),
            CDBSongSet::GetTableName());
      m_plistTree->SetFromClause(
         "Songs INNER JOIN (Authors INNER JOIN AuthorsSongs ON Authors.Key = AuthorsSongs.Author) ON Songs.Key = AuthorsSongs.Song");
      m_plistTree->UpdateList();
      if(m_pstrlist->GetStyle() & WS_VISIBLE)
      {
         m_pstrlist->ShowWindow(SW_HIDE);
      }
      if(!(m_plistTree->GetStyle() & WS_VISIBLE))
      {
         m_plistTree->ShowWindow(SW_SHOW);
      }
      m_layoutExplore.SetPane(
         1,
         IDC_LIST,
            false);
      m_layoutExplore.layout();
//      m_ptree->RedrawWindow(NULL, NULL, RDW_INTERNALPAINT);
   }
   else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hAuthor,
      hItem) ||
      hItem == m_ptree->m_hGroup1.m_hAuthor)
   {
      ShowStrList("Author", m_ptree->m_hGroup1.m_hAuthor, hItem);
   }
    else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hCopyright,
      hItem) &&
      m_ptree->GetChildItem(hItem) == NULL)
   {
//      str = "InStr(Copyright, '";
//      str += strText;
//      str += "') > 0";
        str += CDataCentral::m_lpcszTableCopyright;
      str += ".Text = '";
      str += strText;
      str += "'";
      m_plistTree->SetWhereClause(str);
      m_plistTree->SetFromClause(
         "Songs INNER JOIN (Copyrights INNER JOIN CopyrightsSongs ON Copyrights.Key = CopyrightsSongs.Copyright) ON Songs.Key = CopyrightsSongs.Song");
      m_plistTree->UpdateList();
      if(m_pstrlist->GetStyle() & WS_VISIBLE)
      {
         m_pstrlist->ShowWindow(SW_HIDE);
      }
      if(!(m_plistTree->GetStyle() & WS_VISIBLE))
      {
         m_plistTree->ShowWindow(SW_SHOW);
      }
      m_layoutExplore.SetPane(
         1,
         IDC_LIST,
            false);
      m_layoutExplore.layout();
//      m_ptree->RedrawWindow(NULL, NULL, RDW_INTERNALPAINT);
   }
   else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hCopyright,
      hItem) ||
      hItem == m_ptree->m_hGroup1.m_hCopyright)
   {
      ShowStrList("Copyrights", m_ptree->m_hGroup1.m_hCopyright, hItem);
   }
    else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hComposer,
      hItem) &&
      m_ptree->GetChildItem(hItem) == NULL)
   {
//      str = "InStr(Composer, '";
//      str += strText;
//      str += "') > 0";
      str = "Composers.Text = '";
      str += strText;
      str += "'";
      m_plistTree->SetWhereClause(str);
      m_plistTree->SetFromClause(
         "Songs INNER JOIN (Composers INNER JOIN ComposersSongs ON Composers.Key = ComposersSongs.Composer) ON Songs.Key = ComposersSongs.Song");
      m_plistTree->UpdateList();
      if(m_pstrlist->GetStyle() & WS_VISIBLE)
      {
         m_pstrlist->ShowWindow(SW_HIDE);
      }
      if(!(m_plistTree->GetStyle() & WS_VISIBLE))
      {
         m_plistTree->ShowWindow(SW_SHOW);
      }
      m_layoutExplore.SetPane(
         1,
         IDC_LIST,
            false);
      m_layoutExplore.layout();
//      m_ptree->RedrawWindow(NULL, NULL, RDW_INTERNALPAINT);
   }
   else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hComposer,
      hItem) ||
      hItem == m_ptree->m_hGroup1.m_hComposer)
   {
      ShowStrList("Composers", m_ptree->m_hGroup1.m_hComposer, hItem);
   }
   else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hLyricist,
      hItem) &&
      m_ptree->GetChildItem(hItem) == NULL)
   {
//      string str;
//      str = "Lyricist = '";
//      str += strText;
//      str += "'";
      str = "Lyricists.Text = '";
      str += strText;
      str += "'";
      m_plistTree->SetWhereClause(str);
      m_plistTree->SetFromClause(
         "Songs INNER JOIN (Lyricists INNER JOIN LyricistsSongs ON Lyricists.Key = LyricistsSongs.Lyricist) ON Songs.Key = LyricistsSongs.Song");
      m_plistTree->UpdateList();
      if(m_pstrlist->GetStyle() & WS_VISIBLE)
      {
         m_pstrlist->ShowWindow(SW_HIDE);
      }
      if(!(m_plistTree->GetStyle() & WS_VISIBLE))
      {
         m_plistTree->ShowWindow(SW_SHOW);
      }
      m_layoutExplore.SetPane(
         1,
         IDC_LIST, 
            false);
      m_layoutExplore.layout();
//      m_ptree->RedrawWindow(NULL, NULL, RDW_INTERNALPAINT);
   }
   else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hLyricist,
      hItem) ||
      hItem == m_ptree->m_hGroup1.m_hLyricist)
   {
      ShowStrList("Lyricists",m_ptree->m_hGroup1.m_hLyricist, hItem);
   }
   else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hArranger,
      hItem) &&
      m_ptree->GetChildItem(hItem) == NULL)
   {
      //string str;
//      str = "Arranger = '";
//      str += strText;
//      str += "'";
      str = "Arrangers.Text = '";
      str += strText;
      str += "'";
      m_plistTree->SetWhereClause(str);
      m_plistTree->SetFromClause(
         "Songs INNER JOIN (Arrangers INNER JOIN ArrangersSongs ON Arrangers.Key = ArrangersSongs.Arranger) ON Songs.Key = ArrangersSongs.Song");
      m_plistTree->UpdateList();
      if(m_pstrlist->GetStyle() & WS_VISIBLE)
      {
         m_pstrlist->ShowWindow(SW_HIDE);
      }
      if(!(m_plistTree->GetStyle() & WS_VISIBLE))
      {
         m_plistTree->ShowWindow(SW_SHOW);
      }
      m_layoutExplore.SetPane(
         1,
         IDC_LIST, 
            false);
      m_layoutExplore.layout();
//      m_ptree->RedrawWindow(NULL, NULL, RDW_INTERNALPAINT);
   }
   else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hArranger,
      hItem) ||
      hItem == m_ptree->m_hGroup1.m_hArranger)
   {
      ShowStrList("Arrangers",m_ptree->m_hGroup1.m_hArranger, hItem);
   }
   else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hPerformer,
      hItem) &&
      m_ptree->GetChildItem(hItem) == NULL)
   {
//      string str;
      //str = "Performer = '";
      //str += strText;
      //str += "'";
//      string * pStr;
      str = m_ptree->GetItemSqlMap(hItem);
      str = "Performers.Text = '";
      str += strText;
      str += "'";
      m_plistTree->SetWhereClause(str);
      m_plistTree->SetFromClause(
         "Songs INNER JOIN (Performers INNER JOIN PerformersSongs ON Performers.Key = PerformersSongs.Performer) ON Songs.Key = PerformersSongs.Song");
      m_plistTree->UpdateList();
      if(m_pstrlist->GetStyle() & WS_VISIBLE)
      {
         m_pstrlist->ShowWindow(SW_HIDE);
      }
      if(!(m_plistTree->GetStyle() & WS_VISIBLE))
      {
         m_plistTree->ShowWindow(SW_SHOW);
      }
      m_layoutExplore.SetPane(
         1,
         IDC_LIST,
            false);
      m_layoutExplore.layout();
//      m_ptree->RedrawWindow(NULL, NULL, RDW_INTERNALPAINT);
   }
   else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hPerformer,
      hItem) ||
      hItem == m_ptree->m_hGroup1.m_hPerformer)
   {
      ShowStrList("Performers", m_ptree->m_hGroup1.m_hPerformer, hItem);
   }
   else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hProgrammer,
      hItem) &&
      m_ptree->GetChildItem(hItem) == NULL)
   {
//      string str;
//      str = "Programmer = '";
//      str += strText;
//      str += "'";
      str = m_ptree->GetItemSqlMap(hItem);
      str = "Programmers.Text = '";
      str += strText;
      str += "'";
      m_plistTree->SetWhereClause(str);
      m_plistTree->SetFromClause(
         "Songs INNER JOIN (Programmers INNER JOIN ProgrammersSongs ON Programmers.Key = ProgrammersSongs.Programmer) ON Songs.Key = ProgrammersSongs.Song");
      m_plistTree->UpdateList();
      if(m_pstrlist->GetStyle() & WS_VISIBLE)
      {
         m_pstrlist->ShowWindow(SW_HIDE);
      }
      if(!(m_plistTree->GetStyle() & WS_VISIBLE))
      {
         m_plistTree->ShowWindow(SW_SHOW);
      }
      m_layoutExplore.SetPane(
         1,
         IDC_LIST,
            false);
      m_layoutExplore.layout();
//      m_ptree->RedrawWindow(NULL, NULL, RDW_INTERNALPAINT);
   }
   else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hProgrammer,
      hItem) ||
      hItem == m_ptree->m_hGroup1.m_hProgrammer)
   {
      ShowStrList("Programmers", m_ptree->m_hGroup1.m_hProgrammer, hItem);
   }
   else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hKeyword,
      hItem) &&
      m_ptree->GetChildItem(hItem) == NULL)
   {
//      string str;
//      str = "Keyword = '";
//      str += strText;
//      str += "'";
      
      str = m_ptree->GetItemSqlMap(hItem);
      str = "Keywords.Text = '";
      str += strText;
      str += "'";

      m_plistTree->SetWhereClause(str);
      m_plistTree->SetFromClause(
         "Songs INNER JOIN (Keywords INNER JOIN KeywordsSongs ON Keywords.Key = KeywordsSongs.Keyword) ON Songs.Key = KeywordsSongs.Song");
      m_plistTree->UpdateList();
      if(m_pstrlist->GetStyle() & WS_VISIBLE)
      {
         m_pstrlist->ShowWindow(SW_HIDE);
      }
      if(!(m_plistTree->GetStyle() & WS_VISIBLE))
      {
         m_plistTree->ShowWindow(SW_SHOW);
      }
      m_layoutExplore.SetPane(
         1,
         IDC_LIST, 
            false);
      m_layoutExplore.layout();
//      m_ptree->RedrawWindow(NULL, NULL, RDW_INTERNALPAINT);
   }
   else if(m_ptree->IsItemDescendantOf(
      m_ptree->m_hGroup1.m_hKeyword,
      hItem) ||
      hItem == m_ptree->m_hGroup1.m_hKeyword)
   {
      ShowStrList("Keywords", m_ptree->m_hGroup1.m_hKeyword, hItem);
   }*/
/*   *pResult = 0;
   m_cs.Unlock();
}*/
}

HRESULT AlbumMainView::OpenSongsSet(const char * lpSQL, bool bFindInterface)
{
//   CVMSApp * pApp = (CVMSApp *) &System;
/*   db_server * pDataCentral = db();
   HRESULT hr;
      try
   {
   {
      if(m_pdatasource->m_spInit == NULL)
         return E_FAIL;
      wait_cursor wait(get_app());
      if(m_psongsset->m_spCommand != NULL)
      {
         m_psongsset->close();
      }
      if(lpSQL == NULL)
         hr = m_psongsset->open(m_pdatasource, bFindInterface);
      else
         hr = m_psongsset->open(m_pdatasource, lpSQL, bFindInterface);
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
   }*/
return S_OK;
}

HRESULT AlbumMainView::OpenSongsSetIndexedKey()
{
//   CVMSApp * pApp = (CVMSApp *) &System;
/*   db_server * pDataCentral = db();
   HRESULT hr;
      try
   {
   {
      if(m_pdatasource->m_spInit == NULL)
         return E_FAIL;
      wait_cursor wait(get_app());
      if(m_psongsset->m_spRowset != NULL)
      {
         m_psongsset->close();
      }
      hr = m_psongsset->OpenIndexedKey(m_pdatasource);
      //hr = m_psongsset->open(m_DataSource);
      return hr;


   }
   } catch(COLEDBException *e)
   {
      CDBErrorDialog dlg;
      dlg.Init(e->m_spUnk, e->m_iid);
      dlg.DoModal();
      e->Delete();
      return hr;
   }*/
return S_OK;
}

void AlbumMainView::ShowStrList(const char * lpctstrTable, HTREEITEM hParentItem, HTREEITEM hItem)
{
//   CVMSApp * pApp = (CVMSApp *) &System;
/*   db_server * pDataCentral = db();
   //CSTR255Set str255Set;
   CDBSetV002 dbSet(DBDataCentral());
   string strSql;
   HRESULT hr;
   try
   {
      if(hItem == hParentItem)
         strSql.Format("SELECT * FROM %s ORDER BY Text;", lpctstrTable);
      else
      {
         strSql.Format("SELECT * FROM %s WHERE %s ORDER BY Text;", lpctstrTable, m_ptree->GetItemSqlMap(hItem));
      }
      
      hr = dbSet.open(
         pDataCentral->GetDataSource(),
         strSql);
      m_pstrlist->m_strArray.remove_all();
      dbSet.GetStringArray(&m_pstrlist->m_strArray);
      m_pstrlist->m_strArray.XFV001Expand();
      m_pstrlist->UpdateList();
   } catch(COLEDBException *e)
   {
      CDBErrorDialog dlg;
      dlg.Init(e->m_spUnk, e->m_iid);
      dlg.DoModal();
      e->Delete();
      return;
   }


   if(m_plistTree->GetStyle() & WS_VISIBLE)
   {
      m_plistTree->ShowWindow(SW_HIDE);
   }
   if(!(m_pstrlist->GetStyle() & WS_VISIBLE))
   {
      m_pstrlist->ShowWindow(SW_SHOW);
   }
   m_layoutSongExplorer.SetPane(
      1,
      m_pstrlist, 
        false);
   m_layoutSongExplorer.layout();
   m_ptree->RedrawWindow();

*/
}


void AlbumMainView::OnItemdblclickStrlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
/*   LPNMLISTVIEW lpnmlv = (LPNMLISTVIEW) pNMHDR;
   CListCtrl * pList = (CListCtrl *) GetDescendantWindow(lpnmlv->hdr.idFrom);
   ASSERT(pList != NULL);
   POSITION pos = pList->GetFirstSelectedItemPosition();
   if (pos == NULL)
      TRACE0("No items were selected!\n");
   else
   {
      int nItem = pList->GetNextSelectedItem(pos);
      TRACE1("Item %d was selected!\n", nItem);
      // you could do your own processing on nItem here
      string str = pList->GetItemText(nItem, 0);
      HTREEITEM hItem = m_ptree->FindItem(
         m_ptree->GetSelectedItem(),
         str,
         TRUE);
      if(hItem != NULL)
      {
         m_ptree->Select(hItem, TVGN_CARET);
      }
   }
   *pResult = 0;*/
}

/*BOOL AlbumMainView::create(const char * lpszTemplateName, ::ca::window* pParentWnd)
{
   ASSERT(HIWORD(lpszTemplateName) == 0 ||
      AfxIsValidString(lpszTemplateName));

   m_lpszTemplateName = lpszTemplateName;  // used for help
   if (HIWORD(m_lpszTemplateName) == 0 && m_nIDHelp == 0)
      m_nIDHelp = LOWORD((DWORD)m_lpszTemplateName);

#ifdef _DEBUG
//   if (!_AfxCheckDialogTemplate(lpszTemplateName, FALSE))
//   {
//      ASSERT(FALSE);          // invalid dialog template name
//      PostNcDestroy();        // cleanup if create fails too soon
//      return FALSE;
//   }
#endif //_DEBUG

   HINSTANCE hInst = AfxFindResourceHandle(lpszTemplateName, RT_DIALOG);
   HRSRC hResource = ::FindResource(hInst, lpszTemplateName, RT_DIALOG);
   HGLOBAL hTemplate = LoadResource(hInst, hResource);
   BOOL bResult = CreateIndirect(hTemplate, pParentWnd, hInst);
   FreeResource(hTemplate);

   return bResult;
}
BOOL AlbumMainView::CreateIndirect(HGLOBAL hDialogTemplate, ::ca::window* pParentWnd,
   HINSTANCE hInst)
{
   ASSERT(hDialogTemplate != NULL);

   LPCDLGTEMPLATE lpDialogTemplate = (LPCDLGTEMPLATE)LockResource(hDialogTemplate);
   BOOL bResult = CreateIndirect(lpDialogTemplate, pParentWnd, NULL, hInst);
   UnlockResource(hDialogTemplate);

   return bResult;
}

BOOL AlbumMainView::CreateIndirect(LPCDLGTEMPLATE lpDialogTemplate, ::ca::window* pParentWnd,
   void * lpDialogInit, HINSTANCE hInst)
{
   ASSERT(lpDialogTemplate != NULL);

//   if (pParentWnd == NULL)
//      pParentWnd = System.GetMainWnd();
   m_lpDialogInit = lpDialogInit;

   return CreateDlgIndirect(lpDialogTemplate, pParentWnd, hInst);
}*/

void AlbumMainView::Update(int iView)
{
    wait_cursor cwc(get_app());

    TRACE("\n\nCAlbumMainView::Update\n\n");
//    CVMSApp * pApp = (CVMSApp *) &System;
/*   db_server * pDataCentral = db();
    //pDataCentral->Update();
      if(FAILED(OpenSongsSetIndexedKey()))
   {
      if(FAILED(OpenSongsSet(NULL, true)))
      {
         System.simple_message_box("Record set failed to open.", MB_OK);
      }
   }

    switch(iView)
   {
   case ViewFullList:
      m_plistFull->UpdateList(NULL);
        m_bFullListNeedUpdate = false;
      break;
    case ViewExplorer:
      m_explorer.Refresh();
      m_bExplorerNeedUpdate = false;
      break;
    case ViewSongExplorer:
      m_plistTree->UpdateList();
       m_ptree->UpdateTree();
       m_pstrlist->UpdateList();
        m_bSongExplorerNeedUpdate = false;
      break;
    case ViewSearchList:
      m_plistSearch->UpdateList();
        m_bSearchListNeedUpdate = false;
      break;
   case ViewNavigator:
//      m_phtmlview->UpdateList();
        m_bHtmlViewNeedUpdate = false;
      break;
    case ViewDuplicatesList:
      m_plistDuplicates->UpdateList();
        m_bDuplicatesListNeedUpdate = false;
      break;

    default:
        break;
   }
*/
    StateMachineUpdate(UpdateEventUpdated);
}

void AlbumMainView::OnSongsUpdated()
{
      if(FAILED(OpenSongsSetIndexedKey()))
   {
      if(FAILED(OpenSongsSet(NULL, true)))
      {
         System.simple_message_box(NULL, "Record set failed to open.", MB_OK);
      }
   }
    Update(m_eviewCurrent);
//   m_plistFull->UpdateList();
//   m_plistTree->UpdateList();
//   m_pstrlist->UpdateList();

}

void AlbumMainView::OnSongsInfoV001Updated()
{
//   m_ptree->UpdateTree();
}


void AlbumMainView::OnTimer(UINT nIDEvent) 
{
   // TODO: add your message handler code here and/or call default
   if(nIDEvent == UpdateTimer)
    {
        StateMachineUpdate(UpdateEventTimer);
    }
//::userbase::view::OnTimer(nIDEvent);
}

void AlbumMainView::StateMachineUpdate(UINT nIDEvent)
{
    
/*    switch(nIDEvent)
    {
    case UpdateEventTimer:
  //      {
//            if(m_dwUpdateTime + 15000 < timeGetTime())
            {
//                CVMSApp * pApp = (CVMSApp * ) &System;
  //              if(pApp == NULL)
    //                break;
/*                db_server * pDataCentral = db();
                if(pDataCentral == NULL)
                    break;
                ::ca::window * pWnd;
                if(pDataCentral->IsBuildingSongsAlbum())
                {
                    if(GetStyle() & WS_VISIBLE &&
                        ((pWnd = GetActiveWindow()) != NULL) &&
                        (pWnd->m_hWnd == m_hWnd))
                    {
                        m_uiUpdateState = UpdateStateUpdating;
                        Update(m_eviewCurrent);
                        m_dwUpdateTime = timeGetTime();
                    }
                }
            }*/
        //}
/*        break;
    case UpdateEventUpdated:
        {
            m_uiUpdateState = UpdateStateTiming;
        }
        break;
    default:
        ASSERT(FALSE);
    }*/
}

void AlbumMainView::OnContextMenu(::ca::window* pWnd, point point) 
{

}

void AlbumMainView::OnAlbumUpdate() 
{
   // TODO: add your command handler code here
/*        switch(m_eviewCurrent)
   {
   case ViewFullList:
      m_plistFull->UpdateList();
        m_bFullListNeedUpdate = false;
      break;
    case ViewExplorer:
      m_explorer.Refresh();
        m_bExplorerNeedUpdate = false;
      break;
    case ViewSongExplorer:
      m_plistTree->UpdateList();
       m_ptree->UpdateTree();
       m_pstrlist->UpdateList();
        m_bSongExplorerNeedUpdate = false;
      break;
    case ViewSearchList:
      m_plistSearch->UpdateList();
        m_bSearchListNeedUpdate = false;
      break;
   case ViewDuplicatesList:
      m_plistDuplicates->UpdateList();
        m_bDuplicatesListNeedUpdate = false;
      break;
    default:
        break;
   }
*/
}

void AlbumMainView::OnUpdateAlbumUpdate(cmd_ui * pcmdui) 
{
    if(m_uiUpdateState == UpdateStateUpdating)
        pcmdui->Enable(FALSE);
    else
        pcmdui->Enable();
}

void AlbumMainView::OnAlbumReserveSong() 
{
   // TODO: add your command handler code here
/*   AlbumSongList * plist = GetCurrentAlbumSongList();
   if(plist != NULL)
   {
      ReserveSelectedItems(*plist);
   }
*/   
}

void AlbumMainView::OnUpdateAlbumReserveSong(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   AlbumSongList *plist = GetCurrentAlbumSongList();
    if(plist == NULL)
    {
        pcmdui->Enable(FALSE);
    }
    else
    {
//      simple_list_control::Range range;
//      plist->_001GetSelection(range);
  /*      if(range.get_item_count() > 0)
        {
            pcmdui->Enable();
        }
        else
        {
            pcmdui->Enable(FALSE);
        }*/
    }
   
}

AlbumSongList * AlbumMainView::GetCurrentAlbumSongList()
{
//   CTabCtrl * pTab = (CTabCtrl *) GetDescendantWindow(IDC_TAB);
//   int index = pTab->get_cur_sel();
/*   int index = m_eviewCurrent;
   AlbumSongList *plist = NULL;
   switch(index)
   {
   case ViewFullList:
      plist = (AlbumSongList *) GetDescendantWindow(IDC_FULLLIST);
      break;
    case ViewSongExplorer:
      plist = (AlbumSongList *) GetDescendantWindow(IDC_LIST);
      break;
    case ViewSearchList:
      plist = (AlbumSongList *) GetDescendantWindow(IDC_LIST_SEARCH);
      break;
    case ViewDuplicatesList:
      plist = (AlbumSongList *) GetDescendantWindow(IDC_LIST_DUPLICATES);
      break;
    default:
        break;
   }*/
    //return plist;
   return NULL;
}

DWORD WINAPI AlbumMainView::ThreadProcOnContextMenu(void *lpParameter)
{
   // TODO: add your message handler code here
/*    LPCONTEXTMENUMESSAGEDATA lpData = (LPCONTEXTMENUMESSAGEDATA) lpParameter;
   ::userbase::menu menu;
   if (menu.LoadMenu(IDR_POPUP_ALBUM_FULLLIST))
   {
      ::userbase::menu* pPopup = menu.GetSubMenu(0);
      ASSERT(pPopup != NULL);
      pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
         lpData->m_point.x, lpData->m_point.y,
         lpData->m_pMsgWnd);
   }
    delete lpParameter;*/
    return 0;
}

UINT AlbumMainView::GetPopupMenuId(UINT nID)
{
/*    UINT nPopupId;
    switch(nID)
    {
    case IDC_FULLLIST:
        nPopupId = IDR_POPUP_ALBUM_FULLLIST;
        break;
    case IDC_LIST:
        nPopupId = IDR_POPUP_ALBUM_FULLLIST;
        break;
    case IDC_LIST_SEARCH:
        nPopupId = IDR_POPUP_ALBUM_FULLLIST;
        break;
    case IDC_LIST_DUPLICATES:
        nPopupId = IDR_POPUP_ALBUM_FULLLIST;
        break;
    default:
        nPopupId = 0xffffffff;
        break;
    }
    return nPopupId;*/
   return 0;
}

bool AlbumMainView::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
{
   // TODO: add your specialized code here and/or call the base class

/*    ::ca::window * pWnd = GetCurrentAlbumSongList();
   if(pWnd != NULL 
        && (pWnd = FromHandlePermanent(pWnd->m_hWnd)) != NULL 
        && pWnd != NULL
        && pWnd != this
        && pWnd->_001OnCmdMsg(pcmdmsg))
        return TRUE;*/

    int index = m_eviewCurrent;
/*    if(index == ViewNavigator
        && (pWnd = m_phtmlview) != NULL 
        && pWnd != this
        && pWnd->_001OnCmdMsg(pcmdmsg))
        return TRUE;*/

   return ::userbase::view::_001OnCmdMsg(pcmdmsg);
}

void AlbumMainView::OnViewUpdate() 
{
   // TODO: add your command handler code here
   Update(m_eviewCurrent);
}

void AlbumMainView::OnUpdateViewUpdate(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   pcmdui->Enable();
}

void AlbumMainView::OnAlbumFullbuild() 
{
   // TODO: add your command handler code here
//    CVMSApp * pApp = (CVMSApp *) &System;
/*   db_server * pDataCentral = db();
    pDataCentral->SongsPostBuildAlbumMessage(
        &System,
        (SongsAlbum::EBuildSongsAlbumOperation)
        0,
        true);
*/   
}

void AlbumMainView::OnUpdateAlbumFullbuild(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
    pcmdui->Enable();   
}

void AlbumMainView::OnAlbumPartialbuild() 
{
   // TODO: add your command handler code here
//    CVMSApp * pApp = (CVMSApp *) &System;
/*   db_server * pDataCentral = db();
    pDataCentral->SongsPostBuildAlbumMessage(
        &System,
        (SongsAlbum::EBuildSongsAlbumOperation)
        (SongsAlbum::eBuildSongsAlbumDeleteNotFound |
        SongsAlbum::eBuildSongsAlbumAddNew |
        SongsAlbum::eBuildSongsAlbumCreateSearchReferences),
        false);
*/   
}

void AlbumMainView::OnUpdateAlbumPartialbuild(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   pcmdui->Enable();
}

void AlbumMainView::OnBeforeChangeView()
{
    wait_cursor cwc(get_app());

/*    switch(m_eviewCurrent)
   {
   case ViewNavigator:
//      m_layoutNavigator.SetVisible(FALSE);
        break;
   case ViewFullList:
      m_layoutFull.SetVisible(FALSE);
      break;
   case ViewExplorer:
      m_explorer.SetVisible(FALSE);
        break;
   case ViewSongExplorer:
      m_layoutSongExplorer.SetVisible(FALSE);
        break;
   case ViewSearchList:
      m_layoutSearch.SetVisible(FALSE);
        break;
   case ViewDuplicatesList:
      m_layoutDuplicates.SetVisible(FALSE);
   default:
      break;
   }
*/
}

void AlbumMainView::OnAfterChangeView()
{
    wait_cursor cwc(get_app());

    string strTitleC;
   DoUpdateView(m_eviewCurrent, true);
/*   switch(m_eviewCurrent)
   {
   case ViewNavigator:
//      m_layoutNavigator.SetVisible(TRUE);
      break;
   case ViewFullList:
      m_layoutFull.SetVisible(TRUE);
        strTitleC.load_string(IDS_ALBUM_FULLLIST);
      break;
    case ViewExplorer:
      m_explorer.SetVisible(TRUE);
        strTitleC.load_string(IDS_ALBUM_EXPLORE);
      break;
    case ViewSongExplorer:
      m_layoutSongExplorer.SetVisible(TRUE);
        strTitleC.load_string(IDS_ALBUM_EXPLORE);
      break;
    case ViewSearchList:
      m_layoutSearch.SetVisible(TRUE);
        strTitleC.load_string(IDS_ALBUM_SEARCH);
      break;
    case ViewDuplicatesList:
      m_layoutDuplicates.SetVisible(TRUE);
        strTitleC.load_string(IDS_ALBUM_DUPLICATESLIST);
      break;
    default:
        break;
   }
   string strTitleA, strTitleB, strTitle;
   strTitleA.load_string(AFX_IDS_APP_TITLE);
   strTitleB.load_string(IDS_ALBUM_TITLE);
   strTitle = strTitleA + " - " + strTitleB + " - " + strTitleC;
   SetWindowText(strTitle);
    GetParentFrame()->SendMessage(WM_USER, 54, m_eviewCurrent);*/
}

void AlbumMainView::ChangeView(EView eview)
{
    
    OnBeforeChangeView();
    m_eviewCurrent = eview;
    OnAfterChangeView();
//    data_set("Álbum.::view", (int &) eview);


}



void AlbumMainView::OnSetfocusFulllist(NMHDR* pNMHDR, LRESULT* pResult) 
{

   /*if(pNMHDR->idFrom == IDC_FULLLIST
   || pNMHDR->idFrom == IDC_LIST 
   || pNMHDR->idFrom == IDC_LIST_SEARCH 
   || pNMHDR->idFrom == IDC_LIST_DUPLICATES)*/
   {
      AlbumSongList * plist = dynamic_cast < AlbumSongList * > (GetDescendantWindow(pNMHDR->idFrom));
      string str;
      throw not_implemented_exception();
      //       str.Format(IDS_ALBUM_SONGCOUNTINDICATOR, plist->m_dwaQueryKeys.get_size());
      GetParentFrame()->SendMessage(WM_USER, 51678, (LPARAM) (const char *) str);
   }
   
   *pResult = 0;

}

void AlbumMainView::OnOdstatechangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
   NMLVODSTATECHANGE* pStateChanged = (NMLVODSTATECHANGE*)pNMHDR;
   // TODO: add your control notification handler code here
/*   CListCtrl * pList = (CListCtrl *) GetDescendantWindow(pNMHDR->idFrom);
   if(pNMHDR->idFrom == IDC_FULLLIST ||
    pNMHDR->idFrom == IDC_LIST ||
    pNMHDR->idFrom == IDC_LIST_SEARCH ||
    pNMHDR->idFrom == IDC_LIST_DUPLICATES)
    {
        AlbumSongList * pAlbumList = (AlbumSongList *) pList;
//        int iSelectedCount = m_plistFull->GetSelectedCount();
  //      iSelectedCount = pList->GetSelectedCount();
/*        if(iSelectedCount <= 0)
        {
            string str;
            //GetParentFrame()->m_wndStatusBar.SetPaneInfo(0, 1, SBPS_STRETCH | SBPS_NORMAL, 0);
            str.Format(IDS_ALBUM_SONGCOUNTINDICATOR, pAlbumList->m_dwaQueryKeys.get_size());
            //GetParentFrame()->m_wndStatusBar.SetPaneText(0, str);
            GetParentFrame()->SendMessage(WM_USER, 51678, (LPARAM)(const char *) str);
        }
        else
        {
            string str;
           //GetParentFrame()-> m_wndStatusBar.SetPaneInfo(0, 1, SBPS_STRETCH | SBPS_NORMAL, 0);
            str.Format(IDS_ALBUM_SELECTEDSONGCOUNTINDICATOR, iSelectedCount);
             GetParentFrame()->SendMessage(WM_USER, 51678, (LPARAM)(const char *) str);
        }*/
  //  }
   *pResult = 0;
}

void AlbumMainView::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: add your control notification handler code here
    AlbumSongList * plist = dynamic_cast < AlbumSongList * > (GetDescendantWindow(pNMHDR->idFrom));
    UpdateStatus(plist);
   
   *pResult = 0;
}

void AlbumMainView::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
   // TODO: add your control notification handler code here
   
}



void AlbumMainView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
/*::userbase::view::OnShowWindow(bShow, nStatus);
   if(bShow)
    {
        if(!m_strSearch.is_empty())
        {
            SearchNow();
        }
    }
*/
}

VMSRESULT AlbumMainView::Search(const string &strSearch)
{
    m_strSearch = strSearch;
   
    if(IsWindowVisible())
    {
        SearchNow();
    }

    return VMSR_SUCCESS;


}

VMSRESULT AlbumMainView::SearchNow()
{
    ChangeView(ViewSearchList);
//    m_psearchformview->m_comboSearch.SetWindowText(m_strSearch);
    m_strSearch.Empty();
    m_psearchformview->SearchNow();
    return VMSR_SUCCESS;
}


/*AlbumFrameWnd * AlbumMainView::GetParentFrame()
{

//    AlbumFrameWnd *  pFrame = (AlbumFrameWnd *) GetParent();
    AlbumFrameWnd *  pFrame = (AlbumFrameWnd *) ::userbase::view::GetParentFrame();
    ASSERT(base < AlbumFrameWnd >::bases(pFrame));
    return pFrame;

}*/

void AlbumMainView::on_update(::view* pSender, LPARAM lHint, ::radix::object* pHint) 
{
    switch(lHint)
    {
    case 13:
        OnSongsUpdated();
        break;
    case 4:
        OnSongsInfoV001Updated();
        break;
    case 14:
        EView eview = ViewFullList;
//        data_get("Álbum.::view", (int &) eview);
        ChangeView(eview);
        break;
    }
    if(pHint != NULL)
        if(base < AlbumViewUpdateHint >::bases(pHint))
        {
            AlbumViewUpdateHint * pUpdateHint = (AlbumViewUpdateHint *) pHint;
            if(pUpdateHint->m_i == 15)
            {
                Search(pUpdateHint->m_str);
            }
            else if(pUpdateHint->m_i == 12342345)
            {
                m_plistFull->AddKey(pUpdateHint->m_iKey);
            }
            
        }
   
}


enum  AlbumMainView::EView AlbumMainView::GetCurrentViewIndex()
{
    return m_eviewCurrent;
}

BOOL AlbumMainView::OnEraseBkgnd(::ca::graphics * pgraphics) 
{
   // TODO: add your message handler code here and/or call default
   return true;
   //return ::userbase::view::OnEraseBkgnd(pgraphics);
}


void AlbumMainView::OnDraw(::ca::graphics * pdc) 
{
   //rect rectClient;
   //GetClientRect(rectClient);
   //pdc->FillSolidRect(rectClient, RGB(255, 255, 255));
   
}


void AlbumMainView::OnAlbumFullList() 
{
   // TODO: add your command handler code here
   ChangeView(ViewFullList);
}

void AlbumMainView::OnUpdateAlbumFullList(cmd_ui * pcmdui) 
{
   pcmdui->Enable(this != NULL);
   pcmdui->_001SetCheck( GetCurrentViewIndex() == ViewFullList);
}

void AlbumMainView::OnAlbumSearchList() 
{
    ChangeView(ViewSearchList);   
}

void AlbumMainView::OnUpdateAlbumSearchList(cmd_ui * pcmdui) 
{
   pcmdui->Enable(this != NULL);
   pcmdui->_001SetCheck(GetCurrentViewIndex() == ViewSearchList);
}
void AlbumMainView::OnAlbumExplorer() 
{
    ChangeView(ViewExplorer);

}

void AlbumMainView::OnUpdateAlbumExplorer(cmd_ui * pcmdui) 
{
   pcmdui->Enable(this != NULL);
   pcmdui->_001SetCheck(GetCurrentViewIndex() == ViewExplorer);
}

void AlbumMainView::OnAlbumSongExplorer() 
{
    ChangeView(ViewSongExplorer);

}

void AlbumMainView::OnUpdateAlbumSongExplorer(cmd_ui * pcmdui) 
{
   pcmdui->Enable(this != NULL);
   pcmdui->_001SetCheck(GetCurrentViewIndex() == ViewSongExplorer);
}

void AlbumMainView::OnAlbumNavigator() 
{
   ::ShellExecute(GetTopLevelParent()->_get_handle(), "open", "http://kar.veriwell.com", NULL, NULL, SW_RESTORE );
   //ChangeView(ViewNavigator);
}

void AlbumMainView::OnUpdateAlbumNavigator(cmd_ui * pcmdui) 
{
   pcmdui->Enable(this != NULL);
   pcmdui->_001SetCheck(GetCurrentViewIndex() == ViewNavigator);
   
}


void AlbumMainView::OnAlbumDuplicatesList() 
{
   ChangeView(ViewDuplicatesList);
}

void AlbumMainView::OnUpdateAlbumDuplicatesList(cmd_ui * pcmdui) 
{
   pcmdui->Enable(this != NULL);
   pcmdui->_001SetCheck(GetCurrentViewIndex() == ViewDuplicatesList);
}

void AlbumMainView::UpdateStatus(AlbumSongList *plist)
{
    UINT nID = plist->GetDlgCtrlId();
/*if(nID == IDC_FULLLIST ||
        nID == IDC_LIST ||
        nID == IDC_LIST_SEARCH ||
        nID == IDC_LIST_DUPLICATES)*/
    {
        AlbumSongList * pAlbumList = (AlbumSongList *) plist;
        int iSelectedCount = pAlbumList->_001GetSelectedItemCount();
        if(iSelectedCount <= 0)
        {
            string str;
            throw not_implemented_exception();
            //str.Format(IDS_ALBUM_SONGCOUNTINDICATOR, pAlbumList->m_dwaQueryKeys.get_size());
             GetParentFrame()->SendMessage(WM_USER, 51678, (LPARAM)(const char *) str);
        }
        else
        {
            string str;
            throw not_implemented_exception();
            //str.Format(IDS_ALBUM_SELECTEDSONGCOUNTINDICATOR, iSelectedCount);
            GetParentFrame()->SendMessage(WM_USER, 51678, (LPARAM)(const char *) str);
        }
    }

}

void AlbumMainView::OnMsword9() 
{
/*    Word9::_Application word;
    Word9::Options options;
    VARIANT_BOOL bCheckSpellingAsYouType;
    try
    {
    
    CTaskData taskdata;
    CTaskDialog taskdlg(&taskdata);
    taskdlg.create(IDD_TASK);

   string wstrText;
    
    {
        CTaskAnnotation tasknote;
        tasknote.m_iState = CTaskAnnotation::StateExecuting;
        tasknote.m_iStep = 0;
        tasknote.m_iSteps = 1;
      wstrText.load_string(IDS_MSWORD9_CREATING_TEXT);
        tasknote.m_strText = wstrText;
        taskdata.m_tasks.add(tasknote);

        tasknote.m_iState = CTaskAnnotation::StateInQueue;
        tasknote.m_iStep = 0;
        tasknote.m_iSteps = 1;
      wstrText.load_string(IDS_MSWORD9_TRANSFERING_TEXT);
        tasknote.m_strText = wstrText;
        taskdata.m_tasks.add(tasknote);
    }

    taskdata.SetCurrentTaskAnnotation(0);

    taskdlg.UpdateTasks();

    taskdlg.ShowWindow(SW_SHOW);

    

/*    if(!word.GetDispatch("Word.System", NULL))
    {
        System.simple_message_box(IDS_MSWORD_INITIALIZATION_FAILED, MB_ICONINFORMATION);
        return;
    }*/
/*    if(!word.CreateDispatch("Word.System", NULL))
    {
        System.simple_message_box(IDS_MSWORD_INITIALIZATION_FAILED, MB_ICONINFORMATION);
        return;
    }
    word.SetDisplayAlerts(Word9::wdAlertsNone);
    options = word.GetOptions();
    bCheckSpellingAsYouType = options.GetCheckSpellingAsYouType();
    options.SetCheckSpellingAsYouType(false);
    Word9::Documents documents(word.GetDocuments());
    COleVariant varOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);
    documents.add(varOptional, varOptional, varOptional, varOptional);
    Word9::_Document document(word.GetActiveDocument());
    Word9::Window ::ca::window(document.GetActiveWindow());
    //word.SetVisible(FALSE);
    word.SetScreenUpdating(FALSE);
    Word9::Selection selection(word.GetSelection());
    AlbumSongList * plist = (AlbumSongList *) GetCurrentAlbumSongList();
    CTaskAnnotation * ptasknote = taskdata.GetCurrentTaskAnnotation();
    string str = plist->GetTextV001(ptasknote);
    CStrTokenizer strTokenizer = str;
    string strToken;

    int iCount = 0;
    while(strTokenizer.GetNextToken(strToken, "\n", TRUE))
    {
        iCount++;
    }

    ptasknote->m_iState = CTaskAnnotation::StateConcluded;
    taskdata.SetCurrentTaskAnnotation(1);
    ptasknote = taskdata.GetCurrentTaskAnnotation();
    ptasknote->m_iState = CTaskAnnotation::StateExecuting;
    ptasknote->m_iSteps = iCount;
    taskdlg.UpdateTasks();

    string strBundle;
    strTokenizer.Restart();
    int iIndex = 0;
    string wstrInformation;
    while(strTokenizer.GetNextToken(strToken, "\n", TRUE))
    {
        wstrInformation.Format(IDS_MSWORD9_PROCESSINGLINE, iCount, iIndex);
        ptasknote->m_ptasks->m_strInformation1 = wstrInformation,
        ptasknote->UpdateStatus();
        strBundle += strToken;
        if(strBundle.get_length() > 4096)
        {
            selection.TypeText(strBundle);
            strBundle = "";
        }
        iIndex++;
        ptasknote->m_iStep = iIndex;
        ptasknote->UpdateProgress();
    }
    wstrInformation.Format(IDS_MSWORD9_PROCESSINGLINE, iCount, iIndex);
    ptasknote->m_ptasks->m_strInformation1 = wstrInformation,
    ptasknote->UpdateStatus();
    if(strBundle.get_length() > 0)
    {
        selection.TypeText(strBundle);
        strBundle = "";
    }

    

    COleVariant vtMissing(varOptional);
    COleVariant vtTrue((long) 1, VT_BOOL);
    COleVariant vtFalse((long) 0, VT_BOOL);


    selection.WholeStory();
    selection.ConvertToTable(
        &COleVariant((long) Word9::wdSeparateByParagraphs),
        &vtMissing,
        &COleVariant((long) 1),
        &vtMissing,
        COleVariant((long) Word9::wdTableFormatNone),
        &vtFalse, 
        &vtFalse,
        &vtFalse,
        &vtFalse,
        &vtFalse,
        &vtFalse,
        &vtFalse,
        &vtFalse,
        &vtTrue,
        &vtMissing, 
        &vtMissing);

    

    Word9::Rows rows(selection.GetRows());
    rows.SetHeightRule(Word9::wdRowHeightExactly);
    rows.SetHeight(12);

    Word9::Tables tables(selection.GetTables());

    Word9::Table table(tables.Item(1));

    Word9::Borders borders(table.GetBorders());

    borders.SetOutsideLineStyle(false);
    borders.SetInsideLineStyle(false);
    

    document.SetSaved(TRUE);
    COleVariant varTrue;
    varTrue.vt = VT_BOOL;
    varTrue.boolVal = TRUE;
    word.SetScreenUpdating(TRUE);
   word.SetVisible(TRUE);
    word.Activate();
    }
    catch(COleException *e)
   {
      LPVOID lpMsg;
      ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                     FORMAT_MESSAGE_FROM_SYSTEM | 
                     FORMAT_MESSAGE_IGNORE_INSERTS, NULL, e->m_sc,
                     MAKELANGID(LANG_NEUTRAL, 
                     SUBLANG_DEFAULT),(LPTSTR) &lpMsg,
                     0, NULL);
      ::MessageBox(NULL, (const char *)lpMsg, "COM Error", 
                  MB_OK | MB_SETFOREGROUND);
      ::LocalFree( lpMsg );
     word.ReleaseDispatch();
   }

   catch(COleDispatchException *e)
   {
      char msg[512];
      _stprintf(msg, "run-time error '%d':\n\n%s", 
           e->m_scError & 0x0000FFFF, e->m_strDescription);
      ::MessageBox(NULL, msg, "Server Error", 
                  MB_OK | MB_SETFOREGROUND);      
     word.ReleaseDispatch();
   }

    word.SetDisplayAlerts(Word9::wdAlertsAll);
    
    options.SetCheckSpellingAsYouType(bCheckSpellingAsYouType);*/
}

void AlbumMainView::OnUpdateMsword9(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
    enum  AlbumMainView::EView   eview = GetCurrentViewIndex();

    //if(eview == ViewNavigator &&
      //  m_phtmlview->GetLocationURL().Right(19) == "print.filename.html")
    if(eview == ViewFullList)
    {
        pcmdui->Enable();
    }
    else
    {
        pcmdui->Enable(FALSE);
    }


}

void AlbumMainView::OnViewNotepad() 
{
   // TODO: add your command handler code here
    
/*    CTaskData taskdata;
    CTaskDialog taskdlg(&taskdata);
    taskdlg.create(IDD_TASK);
    CTaskAnnotation tasknote;
    tasknote.m_iState = CTaskAnnotation::StateExecuting;
    tasknote.m_iStep = 0;
    tasknote.m_iSteps = 1;
    taskdata.m_tasks.add(tasknote);
    taskdlg.ShowWindow(SW_SHOW);
    CVmsGenApp * papp = (CVmsGenApp *) &System;
   string strModuleFolder(papp->m_strModuleFolder);
   string strFolder;
   strFolder = strModuleFolder;
    string str;
    str.load_string(IDS_FOLDER_ALBUM);
   strFolder += str;
    CFileFind fileFind;
    bool bOk = true;
    if(fileFind.FindFile(strFolder))
    {
        
        if(!fileFind.FindNextFile())
        {
            if(!fileFind.IsDirectory())
            {
                if(DeleteFile(strFolder))
                {
                    if(!CreateDirectory(strFolder, NULL))
                    {
                        System.simple_message_box("Não foi possível criar diretório de letras de músicas");
                        bOk = false;
                    }
                }
                else
                {
                    System.simple_message_box("Não foi possível criar diretório de letras de músicas. Existe um outro arquivo com mesmo nome que não pôde ser apagado.");
                    bOk = false;
                }
            }
        }
    }
    else
    {
        if(!CreateDirectory(strFolder, NULL))
        {
            System.simple_message_box("Não foi possível criar diretório de letras de músicas");
            bOk = false;
        }
    }

    string strPath;
    string strFile;
    int_to_int tasksMap;
    strFile.load_string(IDS_FILE_ALBUM);
    class time time = time::get_current_time();
    strFile += time.Format(" %Y-%m-%d %H-%M-%S");
    int i = 1;
    strPath.Format("%s\\%s.txt", strFolder, strFile);
    while(true)
    {
        if(!fileFind.FindFile(strPath))
            break;
        strPath.Format("%s\\%s[%d].txt", strFolder, strFile, i);
        i++;
    }
    CStdioFile file(
        strPath,
        ::ex1::file::mode_create |
        ::ex1::file::mode_write |
        ::ex1::file::shareDenyWrite |
        ::ex1::file::type_text);

    CArchive ar(&file, CArchive::store);

    ar.write_string("Album");
    ar.write_string("\n");
    ar.write_string(time.Format(" %Y-%m-%d %H-%M-%S"));
    ar.write_string("\n");
    ar.write_string("\n");

    EView eview = GetCurrentViewIndex();
    switch(eview)
    {
    case ViewFullList:
        {
            AlbumSongList * plist = (AlbumSongList *) GetCurrentAlbumSongList();
            plist->WriteNotepadFile(ar, &tasknote);
        }
    }

    ShellExecute(
        m_hWnd,
        "open",
        strPath,
        NULL,
        strFolder,
        SW_SHOWNORMAL);

*/
}

void AlbumMainView::TwiOnDraw(::ca::graphics *pdc)
{
   OnDraw(pdc);
}


void AlbumMainView::DoUpdateView(EView eview, bool bOnlyIfNeeded)
{

    switch(eview)
   {
   case ViewFullList:
      if(gen::logic::forward_conditional(bOnlyIfNeeded, m_bFullListNeedUpdate))
      {
         m_plistFull->UpdateList(NULL);
         m_bFullListNeedUpdate = false;
      }
      break;
    case ViewExplorer:
      if(gen::logic::forward_conditional(bOnlyIfNeeded, m_bExplorerNeedUpdate))
      {
//         m_explorer.Refresh();
         m_bExplorerNeedUpdate = false;
      }
      break;
    case ViewSongExplorer:
      if(gen::logic::forward_conditional(bOnlyIfNeeded, m_bSongExplorerNeedUpdate))
      {
         m_plistTree->UpdateList();
         m_ptree->UpdateTree();
//         m_pstrlist->UpdateList();
         m_bSongExplorerNeedUpdate = false;
      }
      break;
    case ViewSearchList:
      if(gen::logic::forward_conditional(bOnlyIfNeeded, m_bSearchListNeedUpdate))
      {
         m_plistSearch->UpdateList();
         m_bSearchListNeedUpdate = false;
      }
      break;
   case ViewNavigator:
      if(gen::logic::forward_conditional(bOnlyIfNeeded, m_bHtmlViewNeedUpdate))
      {
   //      m_phtmlview->UpdateList();
         m_bHtmlViewNeedUpdate = false;
      }
      break;
    case ViewDuplicatesList:
      if(gen::logic::forward_conditional(bOnlyIfNeeded, m_bDuplicatesListNeedUpdate))
      {
         m_plistDuplicates->AlbumSongCheckList::UpdateList();
         m_bDuplicatesListNeedUpdate = false;
      }
      break;

    default:
        break;
   }

}

void AlbumMainView::OnExploreUp() 
{
//   m_explorer.OneLevelUp();
}





void AlbumMainView::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &AlbumMainView::_001OnCreate);
}