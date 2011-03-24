// InPlaceWndV033.cpp : implementation file
//

#include "stdafx.h"
#include "../vmsp/resource.h"
//#include "vmsguiresource.h"
#include "Vmsse.h"

#include "VmsseApp.h"
#include "VmsseThread.h"
#include "VmsseDll.h"

#include "util.h"
#include "MenuUtil.h"

//#include "	\ add additional includes here"
//#include "resource.h"
#include "AlbumSongMainWnd.h"

#include "AlbumSongView.h"

#include "DataCentral.h"
#include "AlbumSearchFormView.h"
#include "AlbumSongList.h"
#include "DBLong.h"

#include "DBComplement.h"
#include "StrArray.h"

#include "FontCentral.h"
#include "MenuV033.h"

#include "..\vmsp\vmsp_i.h"
#include "..\vmsp\vmsp_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlbumSongMainWnd

extern CVmsseApp theApp;

CAlbumSongMainWnd::CAlbumSongMainWnd(CAlbumSongView * pview)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
//    m_psongsetAsynch = new CDBSongSet(CDataCentral::AppGetDBCentral());
  //  m_psongsetSynch = new CDBSongSet(CDataCentral::AppGetDBCentral());
    m_pfulllist = NULL;
    //UpdateList();
    
	m_psearchform = NULL;
	m_psearchlist = NULL;

    m_pmenuShared = NULL;
    m_palbsngview = pview;
    
    m_palbsngview->AddRef();
}

CAlbumSongMainWnd::~CAlbumSongMainWnd()
{
    m_palbsngview->Release();
}


BEGIN_MESSAGE_MAP(CAlbumSongMainWnd, CWnd)
	//{{AFX_MSG_MAP(CAlbumSongMainWnd)
	ON_WM_SIZE()
	ON_WM_CREATE()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_FULL, OnDblclkList)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_SEARCH, OnDblclkList)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
    ON_COMMAND(FCIDM_SHVIEWFIRST + ID_RELATIVE_SONGS_OPTIONS, OnToolsOptionsSongs)
	ON_COMMAND(FCIDM_SHVIEWFIRST + ID_RELATIVE_SEARCH_FORM, OnViewSearchForm)
    ON_MESSAGE(WM_USER, OnUserMessage)
    ON_MESSAGE(VMSM_V001, OnVmsmV001)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAlbumSongMainWnd message handlers

BOOL CAlbumSongMainWnd::Create(
    DWORD dwStyle,
    LPCRECT lprect,
    CWnd * pwndParent,
    UINT nID,
    CCreateContext * pccontext)
{
    return CWnd::Create(
        NULL, NULL,
        dwStyle, *lprect,
        pwndParent, nID, pccontext);
        
        

}

void CAlbumSongMainWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	Layout();
	
	
}

int CAlbumSongMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

    m_pfulllist = new CAlbumSongList();

        m_pfulllist->m_strRegistrySection = _T("Album.FullList");
	m_pfulllist->Create(
        WS_CHILD | WS_VISIBLE |
		LVS_REPORT,
		CRect(0, 0, 0, 0),
	    this,
		IDC_LIST_FULL);
    m_pfulllist->GetHeaderCtrl()->SetDlgCtrlID(IDC_LISTHEADER_FULL);
    
	CDBCentral * pdb = DB();
    
    int i;
	int * iaOrder = new int[m_pfulllist->GetColumnCount()];
    CString str;
	for(i = 0; i < m_pfulllist->GetColumnCount(); i++)
	{
		str.Format(_T("Album.FullList.Column[%d].Order"), i);
		iaOrder[i] = i;
		pdb->GetDBLongSet()->Load(
			_T("Janelas"),
			str,
			&iaOrder[i]);
        if(iaOrder[i] < 0)
            iaOrder[i] = 0;
        if(iaOrder[i] >= m_pfulllist->GetColumnCount())
            iaOrder[i] = m_pfulllist->GetColumnCount() - 1;
	}
//    m_pfulllist->Initialize(m_psongsetAsynch, m_psongsetSynch);
	m_pfulllist->Initialize();
    m_pfulllist->SetColumnOrderArray(m_pfulllist->GetColumnCount(), iaOrder);
    //m_pfulllist->UpdateList(&m_dwaQueryKeys);
	m_pfulllist->UpdateList();

	// TODO: Add your specialized creation code here
	    SetImageLists();

	CVmsseApp * papp = (CVmsseApp *) AfxGetApp();
	CVmsseThread * pthread = (CVmsseThread *) papp->m_pthread;
	pthread->m_wndptra.Add(this);

	m_pfulllist->ShowWindow(SW_SHOW);
	Layout(true);

	return 0;
}

bool CAlbumSongMainWnd::IsChildValid()
{
    return m_pfulllist != NULL &&
        ::IsWindow(m_pfulllist->GetSafeHwnd());
}

void CAlbumSongMainWnd::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMLISTVIEW lpnmlv = (LPNMLISTVIEW) pNMHDR;
	CListCtrl * pList = (CListCtrl *) GetDlgItem(lpnmlv->hdr.idFrom);
	ReserveSelectedItems(pList);
	*pResult = 0;
}

void CAlbumSongMainWnd::ReserveSelectedItems(CListCtrl *pList)
{
    CAlbumSongList * pAlbumList = (CAlbumSongList *)pList;
    CWinApp *pApp = AfxGetApp();
    POSITION pos = pList->GetFirstSelectedItemPosition();
    CStrArray * pstra  = new CStrArray();
    CString str;
	CDBCentral * pdb = DB();
    while(pos != NULL)
    {
	    int iIndex = pList->GetNextSelectedItem(pos);
	    int iKey = pAlbumList->m_dwaQueryKeys.GetAt(iIndex);
        if(pdb->GetSongSetIndexedKey()->FindKey(iKey))
	    {
            pdb->GetSongSetIndexedKey()->GetData(3);
            CDBComplement::DX_Text(false, &str, 
                &pdb->GetSongSetIndexedKey()->m_bstrPath,
                &pdb->GetSongSetIndexedKey()->m_ulPathStatus);
		    pstra->Add(str);
//            pPlaylistDoc->AddSong(m_pSongsSet->m_iCode);
	    }
    }
    VARIANT var;
    pstra->CreateSafeArray(&var);
    //pApp->PostThreadMessage(WM_USER, 22, (LPARAM) pdwa);
    CComPtr<IVmsPlayer> spVmsPlayer;
    HRESULT hr = spVmsPlayer.CoCreateInstance(CLSID_VmsPlayer, NULL, CLSCTX_LOCAL_SERVER);
    if(FAILED(hr))
    {
        CString str;
        str.Format(_T("Could not start Veriwell Musical Player.(0x%X)"), hr);
        AfxMessageBox(str, MB_ICONINFORMATION);
		spVmsPlayer.Release();
        return;   
    }
    hr = spVmsPlayer->ReserveSongs(&var);
    if(FAILED(hr))
    {
        AfxMessageBox(_T("Could not select songs."));
        return;   
    }
    SafeArrayDestroy(var.parray);
	//CListCtrl *pList = (CListCtrl *) GetDlgItem(IDC_LIST);
	/*CAlbumSongList * pAlbumList = (CAlbumSongList *)pList;
	CVMSApp *pApp = (CVMSApp *) AfxGetApp();
    CXfplayerDoc * pPlayerDoc  = pApp->GetPlayerDocument();

    if(pPlayerDoc == NULL)
    {
        pPlayerDoc = (CXfplayerDoc *) pApp->GetPlayerDocTemplate()->OpenDocumentFile(NULL);
    }

    if(pPlayerDoc != NULL)
    {
        CXfplayerView * pLyricView = pPlayerDoc->GetLyricView();
        if(pLyricView != NULL)
        {
            //CPlaylistView * pPlaylistView = pLyricView->GetPlaylistView();
            CPlaylistDoc * pPlaylistDoc = pLyricView->GetPlaylistDoc();
            //if(pPlaylistView == NULL)
            if(pPlaylistDoc == NULL)
            {
                CMultiDocTemplate * pPlaylistDocTemplate = pApp->GetPlaylistDocTemplate();
                pPlaylistDoc
                 = (CPlaylistDoc *) pPlaylistDocTemplate->OpenDocumentFile(NULL);
                pLyricView->AttachPlaylistDoc(pPlaylistDoc);
//                pPlaylistView = pPlaylistDoc->GetPlaylistView();
            }
//            else
  //          {
    //            pPlaylistDoc = pPlaylistView->GetDocument();
      //      }
            

          	CMainFrame *pFrame = (CMainFrame *) pApp->m_pMainWnd;
        	pFrame->UpdateReserveList();
        }
    }*/

}


//afx_msg void CAlbumSongMainWnd::OnSetFocusList(NMHDR* pNMHDR, LRESULT* pResult)
//{
  //  if(GetFocus() == GetDlgItem(pNMHDR->idFrom))
    //    return;

//}

//afx_msg void CAlbumSongMainWnd::OnKillFocusList(NMHDR* pNMHDR, LRESULT* pResult)
//{
//}
LRESULT CAlbumSongMainWnd::OnVmsmV001(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case NOTIFY_BUILDALBUMFINISHED:
		UpdateList();
		break;
	default:
		break;
	}
	return 0;
}

LRESULT CAlbumSongMainWnd::OnUserMessage(WPARAM wParam, LPARAM lParam)
{
    if(wParam == 33)
    {
        LPMENUV033CONTEXTMENU lpmcm = (LPMENUV033CONTEXTMENU) lParam;
        lpmcm->nPopupID = GetPopupMenuId(lpmcm->nControlID);
    }
    return 0;
}

UINT CAlbumSongMainWnd::GetPopupMenuId(UINT nID)
{
    UINT nPopupId;
    switch(nID)
    {
    case IDC_LIST_FULL:
        nPopupId = IDR_POPUP_ALBUM_FULLLIST;
        break;
    default:
        nPopupId = 0xffffffff;
        break;
    }
    return nPopupId;

}

void CAlbumSongMainWnd::OnToolsOptionsSongs()
{
    ((CVmsseApp *)AfxGetApp())->m_pthread->PostThreadMessage(WM_USER, 543, 0);
}

void CAlbumSongMainWnd::OnViewSearchForm()
{
	if(m_psearchform == NULL)
	{
		m_psearchform = new CAlbumSearchFormView();
		if(!m_psearchform)
			return;
		if(!m_psearchform->Create(
			NULL,
			NULL,
			WS_VISIBLE | WS_CHILD,
			CRect(0, 0, 0, 0),
			this,
			IDD_ALBUM_SEARCH,
			NULL))
		{

			delete m_psearchform;
			m_psearchform = NULL;
			return;
		}
	}
	if(m_psearchlist == NULL)
	{
		m_psearchlist = new CAlbumSongList();
		if(!m_psearchlist)
		{
			delete m_psearchform;
			m_psearchform = NULL;
			return;
		}
		m_psearchform->SetAlbumSongList(m_psearchlist);
		m_psearchlist->m_strRegistrySection = _T("Album.SearchList");
		if(!m_psearchlist->Create(
			LVS_REPORT,
			CRect(0, 0, 0, 0),
			this,
			IDC_LIST_SEARCH))
		{
			delete m_psearchlist;
			delete m_psearchform;
			m_psearchform = NULL;
			m_psearchlist = NULL;
			return;
		}
		m_psearchlist->Initialize();
	}

	m_psearchform->OnInitialUpdate();

	if(!::IsWindow(m_splitlayout.GetSafeHwnd()))
	{
		if(!m_splitlayout.Create(
			this,
			0,
			2,
			CSplitLayout::OrientationVertical))
		{
			delete m_psearchlist;
			delete m_psearchform;
			m_psearchform = NULL;
			m_psearchlist = NULL;
			return;
		}
	}

	m_splitlayout.SetPane(
		0,
		m_psearchform,
		false);

	m_splitlayout.SetPane(
		1,
		m_psearchlist,
		false);

	m_splitlayout.SetPosition(0, 200);

	m_pfulllist->ShowWindow(SW_HIDE);
	m_splitlayout.SetVisible(TRUE);
	m_splitlayout.OnSizeParentWindow();

}

BOOL CAlbumSongMainWnd::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

VMSRESULT CAlbumSongMainWnd::UpdateList()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_pfulllist->UpdateList();
	return VMSR_SUCCESS;
/*	m_bFirstProgress = true;
	m_dwaQueryKeys.RemoveAll();
//	m_cacheMap.RemoveAll();
	m_psongsetAsynch->Sort(true);
    
    ASSERT(m_psongsetAsynch->m_spRowset != NULL);
    
    HRESULT hr;
    if(SUCCEEDED(hr = m_psongsetAsynch->m_spRowset->QueryInterface(IID_IDBAsynchStatus, (void **)&m_spIdbas)))
    {
        Populate(m_spIdbas);
        return VMSR_SUCCESS;
    }
    else
    {

        //AddRef();
	    CComPtr<IConnectionPointContainer> spCPC;
	    IConnectionPointPtr pCP;
            DWORD dw;

	    //if(FAILED(hr = spIdbas->QueryInterface(IID_IConnectionPointContainer, (void**) &spCPC)))
        if(SUCCEEDED(hr = m_psongsetAsynch->m_spRowset->QueryInterface(IID_IConnectionPointContainer, (void**) &spCPC)))
        {
            //AfxMessageBox(_T("Good1!"));
            if(SUCCEEDED(hr = spCPC->FindConnectionPoint(__uuidof(IDBAsynchNotify), &pCP)))
            {
              //  AfxMessageBox(_T("Good2!"));
                if(SUCCEEDED(hr = pCP->Advise((IDBAsynchNotify *) this, &dw)))
                {
        	    //    AfxMessageBox(_T("Good3!"));
                }
            }
    	}
        Populate();
    }
	return VMSR_SUCCESS;*/
}

/*void CAlbumSongMainWnd::Populate(IDBAsynchStatus *pDbas)
{
     AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if(pDbas != NULL)
    {
        ULONG ulProgress;
        ULONG ulProgressMax;
        DBASYNCHPHASE eAsynchPhase;
        LPOLESTR pwszStatusText;
        while(true)
        {
            if(FAILED(m_spIdbas->GetStatus(NULL, DBASYNCHOP_OPEN, &ulProgress, &ulProgressMax, &eAsynchPhase, &pwszStatusText)))
                break;
            Populate();
            if(eAsynchPhase ==DBASYNCHPHASE_COMPLETE)
                break;
        }
    }
    else
    {
        HRESULT hr;
            bool bAltered;
            if(m_bFirstProgress)
            {
                if(FAILED(hr = m_psongsetAsynch->MoveFirst()))
                    return;
                if(hr == DB_S_ENDOFROWSET)
                    return;
                m_bFirstProgress = false;
                m_psongsetAsynch->GetData(0);
                m_dwaQueryKeys.Add(m_psongsetAsynch->m_iKey);
                bAltered = true;
            }
            while(true)
            {
                if(FAILED(hr = m_psongsetAsynch->MoveNext()))
                    break;
                if(hr == DB_S_ENDOFROWSET)
                    break;
                m_psongsetAsynch->GetData(0);
                m_dwaQueryKeys.Add(m_psongsetAsynch->m_iKey);
                bAltered = true;
            }
            if(bAltered)
            {
                //SetItemCountEx_(m_dwaQueryKeys.GetSize(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
//                SetItemCountEx_(m_dwaQueryKeys.GetSize(), LVSICF_NOSCROLL);
            }

    }

}*/


void CAlbumSongMainWnd::SetImageLists()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    CImageList * pilSmall = CVmsseDll::AlbumSongGetSmallImageList(); 
    //CTabCtrl * pTab = (CTabCtrl *) GetDlgItem(IDC_TAB);
	if(pilSmall->GetSafeHandle() != NULL)
	{
		m_pfulllist->SetImageList(NULL, LVSIL_SMALL   );
//		m_pTree->SetImageList(NULL, TVSIL_NORMAL   );
//		m_pTreeList->SetImageList(NULL, LVSIL_SMALL   );
//		m_pStrList->SetImageList(NULL, LVSIL_SMALL   );
  //      m_pSearchList->SetImageList(NULL, LVSIL_SMALL   );
    //    m_pDuplicatesList->SetImageList(NULL, LVSIL_SMALL   );
      //  m_pDuplicatesList->GetHeaderCtrl()->SetImageList(NULL);
      //  pTab->SetImageList(NULL);
	}
    
	if(pilSmall->GetSafeHandle() != NULL)
	{
		m_pfulllist->SetImageList(pilSmall, LVSIL_SMALL   );
//		m_pTree->SetImageList(&m_SmallImageList, TVSIL_NORMAL   );
//		m_pTreeList->SetImageList(&m_SmallImageList, LVSIL_SMALL   );
//		m_pStrList->SetImageList(&m_SmallImageList, LVSIL_SMALL   );
  //      m_pSearchList->SetImageList(&m_SmallImageList, LVSIL_SMALL   );
    //	m_pDuplicatesList->SetImageList(&m_SmallImageList, LVSIL_SMALL   );
	  //  m_pDuplicatesList->GetHeaderCtrl()->SetImageList(&m_SmallImageListV001);
	}
//	if(m_SmallImageListV001.GetSafeHandle() != NULL)
//	{
//        pTab->SetImageList(&m_SmallImageListV001);
        
//	}

	


}

bool CAlbumSongMainWnd::InsertMenus()
{
	CString str;
    IShellBrowser * pishb;
    m_palbsngview->get_ShellBrowser(&pishb);
    pishb->OnViewWindowActive(m_palbsngview);
//    CMenuV033 * pmenu;
    CVmsseApp * pApp = &theApp;
//    CRelationV001<UINT, UINT, UINT, UINT> * prel;
//    pApp->MenuV033GetImageMap(&prel);
//    pmenu = new CMenuV033(
//        pApp->MenuV033GetImageList(),
//        prel,
//        CFontCentral::AppGetFontCentral()->GetMenuFont());
    CMenu * pmenu = new CMenu();

    m_pmenuShared = pmenu;

    BOOL bCreate = pmenu->CreateMenu();
    if(!bCreate)
        return false;

    OLEMENUGROUPWIDTHS mwidth = { { 1, 0, 0, 0, 0, 0 } };

    pishb->InsertMenusSB(pmenu->GetSafeHmenu(), &mwidth);

    UINT ui;
    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_CHECKMARKS |
        MIIM_DATA |
        MIIM_ID |
        MIIM_STATE |
        MIIM_SUBMENU |
        MIIM_TYPE;
    for(int i = 0; i < pmenu->GetMenuItemCount(); i++)
    {
        BOOL b = pmenu->GetMenuItemInfo(i, &mii, TRUE);
        if(b)
        {
            if(mii.fType & MFT_BITMAP)
            {
                TRACE("MFT_BITMAP\n");
            }
            
            TRACE("dwTypeData = %s\n", mii.dwTypeData);
            

        }
        if(ui == FCIDM_MENU_FILE)
        {
            CMenu * psubmenu = pmenu->GetSubMenu(i);

            psubmenu->InsertMenu(0, MF_BYPOSITION, FCIDM_BROWSERFIRST , "Teste");
        }
    }

    //CMenu * psubmenu = FindPopupMenuFromID(pmenu, FCIDM_MENU_FILE);
    //psubmenu = CMenuUtil::_GetMenuFromID(pmenu, FCIDM_MENU_TOOLS);
    //CMenu * psubmenu = pmenu->GetSubMenu(0);
	//AfxDebugBreak();
	//CMenu * psubmenu = FindPopupMenuFromID(pmenu, FCIDM_MENU_TOOLS);
	CMenu * psubmenu = CMenuUtil::_GetMenuFromID(pmenu, FCIDM_MENU_TOOLS);
	if(psubmenu != NULL)
	{
		str.LoadString(IDS_VMSSE_TOOLS_SONG_OPTIONS);
		bCreate = psubmenu->InsertMenu(psubmenu->GetMenuItemCount(), MF_BYPOSITION | MF_STRING, FCIDM_SHVIEWFIRST + ID_RELATIVE_SONGS_OPTIONS, str);

		if(!bCreate)
		{
			return false;
		}
	}
	//psubmenu = FindPopupMenuFromID(pmenu, FCIDM_MENU_VIEW);
	psubmenu = CMenuUtil::_GetMenuFromID(pmenu, FCIDM_MENU_VIEW);
	if(psubmenu != NULL)
	{
		str.LoadString(IDS_VMSSE_TOOLS_SONG_OPTIONS);
		bCreate = psubmenu->InsertMenu(psubmenu->GetMenuItemCount(), MF_BYPOSITION | MF_STRING, FCIDM_SHVIEWFIRST + ID_RELATIVE_SONGS_OPTIONS, str);

		if(!bCreate)
		{
			return false;
		}
		str.LoadString(IDS_VMSSE_VIEW_SEARCH_FORM);
		bCreate = psubmenu->InsertMenu(psubmenu->GetMenuItemCount(), MF_BYPOSITION | MF_STRING, FCIDM_SHVIEWFIRST + ID_RELATIVE_SEARCH_FORM, str);

		if(!bCreate)
		{
			return false;
		}
	}

	    pishb->SetMenuSB(pmenu->GetSafeHmenu(), NULL, GetSafeHwnd());

    //SetFocus();

	return true;

}

void CAlbumSongMainWnd::OnDestroy() 
{

	CVmsseApp * papp = (CVmsseApp *) AfxGetApp();
	CVmsseThread * pthread = (CVmsseThread *) papp->m_pthread;
	for(int i = 0; i < pthread->m_wndptra.GetSize(); i++)
	{
		if(pthread->m_wndptra.ElementAt(i) == this)
			pthread->m_wndptra.RemoveAt(i);
	}

	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

bool CAlbumSongMainWnd::Layout(bool bForceNonVisible)
{
	CRect rectClient;
	GetClientRect(rectClient);
	int ix = rectClient.left;
	int iy = rectClient.top;
	int cx = rectClient.Width();
	int cy = rectClient.Height();
    if(IsChildValid()
		&& (bForceNonVisible ||
		m_pfulllist->IsWindowVisible()))
    {
        m_pfulllist->SetWindowPos(
            &wndTop,
            ix, iy,
            cx, cy,
            SWP_SHOWWINDOW);
    }
	m_splitlayout.OnSizeParentWindow();
	return true;
}
