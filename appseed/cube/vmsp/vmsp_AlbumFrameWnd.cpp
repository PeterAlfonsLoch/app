#include "StdAfx.h"
#include "AlbumFrameWnd.h"
#include "AlbumOptionsDialog.h"
#include "AlbumMainView.h"


AlbumFrameWnd::AlbumFrameWnd(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_frame_window(papp),
   m_toolbar(papp),
   m_toolbarExport(papp),
   m_toolbarHtmlView(papp),
   m_toolbarExplorer(papp),
   m_statusbar(papp)
{
   m_pMainView = NULL;
   m_poptionsdlg = NULL;

}

AlbumFrameWnd::~AlbumFrameWnd()
{
}


 // BEGIN_MESSAGE_MAP(AlbumFrameWnd, simple_frame_window)
   //{{AFX_MSG_MAP(AlbumFrameWnd)
/* xxx   ON_WM_CREATE()
   ON_WM_DESTROY()
   ON_WM_MEASUREITEM()
   ON_WM_CLOSE()
   ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
   ON_WM_ERASEBKGND()
   //}}AFX_MSG_MAP
    ON_MESSAGE(WM_USER, OnUserMessage) */
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AlbumFrameWnd message handlers

BOOL AlbumFrameWnd::OnCreateClient(LPCREATESTRUCT lpcs, create_context* pContext) 
{
   if(!simple_frame_window::OnCreateClient(lpcs, pContext))
      return FALSE;
   // TODO: add your specialized code here and/or call the base class
//    EnableDocking(CBRS_ALIGN_ANY);

/* xxx
    if (!m_toolbar.CreateEx(
        this,
        TBSTYLE_FLAT  |
        TBSTYLE_LIST,
        WS_CHILD | CBRS_ALIGN_TOP,// |
//        CBRS_TOOLTIPS | CBRS_FLYBY, 
        rect(0, 0, 0, 0),
        IDR_ALBUM) ||
      !m_toolbar.LoadToolBar(IDR_ALBUM))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }
   */
    
/* xxx
    if (!m_toolbarExport.CreateEx(
        this,
        TBSTYLE_FLAT  |
        TBSTYLE_LIST,
        WS_CHILD | CBRS_ALIGN_TOP,// |
//        CBRS_TOOLTIPS | CBRS_FLYBY, 
        rect(0, 0, 0, 0),
        IDR_ALBUM_EXPORT) ||
      !m_toolbarExport.LoadToolBar(IDR_ALBUM_EXPORT))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }
   */

//   UpdateToolBarText(m_toolbarExport);
//    str.load_string(IDS_ALBUM_EXPORTTEXT);
//    m_toolbarExport.SetButtonText(0, str);
    m_toolbarExport.SetButtonStyle(
        0, 
        m_toolbarExport.GetButtonStyle(0) |
        TBSTYLE_AUTOSIZE);

//    str.load_string(IDS_ALBUM_EXPORTMSWORD9);
  //  m_toolbarExport.SetButtonText(1, str);
    m_toolbarExport.SetButtonStyle(
        1, 
        m_toolbarExport.GetButtonStyle(1) |
        TBSTYLE_AUTOSIZE);



    rect rectWnd;
    m_toolbar.GetWindowRect(rectWnd);
    size size;
    //simple_menu_bar::CalcSize(m_toolbar.GetToolBarCtrl(), size);
    m_toolbar.SetWindowPos(NULL, 0, 0, size.cx, size.cy, SWP_NOMOVE | SWP_NOZORDER);
    //m_toolbar.GetToolBarCtrl().AutoSize();
    m_toolbar.GetWindowRect(rectWnd);
    m_toolbar.ModifyStyle(0, WS_VISIBLE);

    m_toolbarExport.GetWindowRect(rectWnd);
    //simple_menu_bar::CalcSize(m_toolbarExport.GetToolBarCtrl(), size);
    m_toolbarExport.SetWindowPos(NULL, 0, 0, size.cx, size.cy, SWP_NOMOVE | SWP_NOZORDER);
    //m_toolbar.GetToolBarCtrl().AutoSize();
    m_toolbarExport.GetWindowRect(rectWnd);
    m_toolbarExport.ModifyStyle(0, WS_VISIBLE);

/*
    if (!m_toolbarHtmlView.CreateEx(
        this,
        TBSTYLE_FLAT  |
        TBSTYLE_LIST,
        WS_CHILD | CBRS_ALIGN_TOP |
        CBRS_TOOLTIPS | CBRS_FLYBY,
        rect(0, 0, 0, 0),
        IDR_ALBUM_NAVIGATOR) ||
      !m_toolbarHtmlView.LoadToolBar(IDR_ALBUM_NAVIGATOR))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }

   */
  //  AlbumFrameWnd *pFrame = (AlbumFrameWnd *) GetParent()->GetParentFrame();

//    pFrame->m_rebar.AddBar(&m_toolbarHtmlView);

//  
//   string str;
    
//   UpdateToolBarText(m_toolbarHtmlView);
//    str.load_string(IDS_ALBUM_NAVIGATOR_GOBACK);
  //  m_toolbarHtmlView.SetButtonText(0, str);

    //str.load_string(IDS_ALBUM_NAVIGATOR_GOFORWARD);
    //m_toolbarHtmlView.SetButtonText(1, str);

    m_toolbarHtmlView.SetButtonStyle(0,
        m_toolbarHtmlView.GetButtonStyle(2) |
        TBSTYLE_AUTOSIZE);

    m_toolbarHtmlView.SetButtonStyle(1,
        m_toolbarHtmlView.GetButtonStyle(2) |
        TBSTYLE_AUTOSIZE);

    m_toolbarHtmlView.SetButtonStyle(2,
        m_toolbarHtmlView.GetButtonStyle(2) |
        TBSTYLE_AUTOSIZE);

//    m_toolbarHtmlView.GetToolBarCtrl().AutoSize();
    m_toolbarHtmlView.ModifyStyle(0, WS_VISIBLE);

/*    m_toolbarHtmlView.SetButtonStyle(3,
        m_toolbarHtmlView.GetButtonStyle(3) |
        TBSTYLE_AUTOSIZE);

    m_toolbarHtmlView.SetButtonStyle(4,
    m_toolbarHtmlView.GetButtonStyle(4) |
    TBSTYLE_AUTOSIZE);

    m_toolbarHtmlView.SetButtonStyle(5,
    m_toolbarHtmlView.GetButtonStyle(5) |
    TBSTYLE_AUTOSIZE);

    m_toolbarHtmlView.SetButtonStyle(6,
    m_toolbarHtmlView.GetButtonStyle(6) |
    TBSTYLE_AUTOSIZE);

    m_toolbarHtmlView.SetButtonStyle(7,
    m_toolbarHtmlView.GetButtonStyle(7) |
    TBSTYLE_AUTOSIZE);

    m_toolbarHtmlView.SetButtonStyle(8,
    m_toolbarHtmlView.GetButtonStyle(8) |
    TBSTYLE_AUTOSIZE); */

//    m_toolbarHtmlView.ShowWindow(SW_HIDE);

    
//    m_toolbarHtmlView.SetBarStyle(m_toolbarHtmlView.GetBarStyle() |
//      CBRS_TOOLTIPS | CBRS_FLYBY);


/*    if (!m_rebar.create(
            this,
            RBS_BANDBORDERS,
            WS_CHILD
                | WS_VISIBLE
                | WS_CLIPSIBLINGS
                | WS_CLIPCHILDREN
                | CBRS_TOP
                | WS_BORDER) ||
        !m_rebar.GetReBarCtrl().ModifyStyleEx(
            0,
            WS_EX_TOOLWINDOW,
            SWP_NOSIZE
                | SWP_NOMOVE) ||
        !m_rebar.GetReBarCtrl().ModifyStyle(
            CCS_NORESIZE
                |CCS_NOMOVEY,
            0,
            SWP_NOSIZE
                | SWP_NOMOVE) ||
         !m_rebar.AddBar(&m_menubar) ||
      !m_rebar.AddBar(&m_toolbar) ||
        !m_rebar.AddBar(
            &m_toolbarHtmlView, 
            NULL,
            NULL,
            RBBS_GRIPPERALWAYS
                | RBBS_FIXEDBMP
                | RBBS_BREAK
                | RBBS_CHILDEDGE ))
   {
      TRACE0("Failed to create rebar\n");
      return -1;       fail to create
   }
*/
    /*
    if (!m_toolbarExplorer.CreateEx(
        this,
        TBSTYLE_FLAT  |
        TBSTYLE_LIST
      | WS_CHILD
      | WS_VISIBLE,
      CBRS_TOP
        | CBRS_TOOLTIPS
      | CBRS_FLYBY
      | CBRS_SIZE_FIXED,
        rect(0, 0, 0, 0),
        IDR_XFPLAYER_PLAY) ||
      !m_toolbarExplorer.LoadToolBar(IDR_ALBUM_EXPLORER))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }
   */
    //    m_toolbar.ModifyStyleEx(WS_EX_STATICEDGE, 0);
  /*if (
         
      !m_rebar.AddBar(&m_toolbar,
         NULL, 
         NULL,
         RBBS_BREAK 
         | RBBS_FIXEDBMP)
      || !m_rebar.AddBar(&m_toolbarExport)
      || !m_rebar.AddBar(&m_toolbarHtmlView)
      || !m_rebar.AddBar(&m_toolbarExplorer))
   {
      TRACE0("Failed to create rebar\n");
      return -1;      // fail to create
   }*/

  // TODO: remove this if you don't want tool tips
   m_toolbar.SetBarStyle(m_toolbar.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY);

   m_toolbarExport.SetBarStyle(m_toolbar.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY);

   stringa straIndicator;
   
   straIndicator.add("IDS_APP_TITLE");
   straIndicator.add("IDS_APP_TITLE");

   if(!m_statusbar.create(this) ||
      !m_statusbar.SetIndicators(straIndicator))
   {
      TRACE0("Failed to create status bar\n");
      return -1;      // fail to create
   }

   m_statusbar.SetPaneInfo(0, "IDS_APP_TITLE", SBPS_STRETCH | SBPS_NORMAL, 0);
   m_statusbar.SetPaneInfo(0, "IDS_APP_TITLE", SBPS_NORMAL, 0);

   return TRUE;   
}

int AlbumFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   UNREFERENCED_PARAMETER(lpCreateStruct);
   m_dataid = "Album.Frame";
//   if (simple_frame_window::OnCreate(lpCreateStruct) == -1)
//      return -1;


      

//    m_pDialog = new CAlbumDialog(this);
  //  m_pDialog->create(IDD_ALBUM, this);
    //m_pDialog->SetDlgCtrlID(AFX_IDW_PANE_FIRST);

    //return TRUE;

    //m_pDialog->create(this);
    
    m_pMainView = dynamic_cast < ::userbase::view * > (GetDlgItem(AFX_IDW_PANE_FIRST));

    ::user::interaction* pWnd = GetDlgItem(AFX_IDW_PANE_FIRST);
    if(pWnd != NULL)
    {
        pWnd->ModifyStyleEx(
                   WS_EX_CLIENTEDGE,
         0,
         SWP_FRAMECHANGED |
            SWP_NOSENDCHANGING);
    }

//   DIMoveWindow("Álbum");


//    SetMenu(NULL);

   return 0;
}

AlbumMainView * AlbumFrameWnd::GetAlbumView()
{
    return dynamic_cast < AlbumMainView * > (GetActiveView());
}

bool AlbumFrameWnd::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
{
   ::user::interaction* pWnd = m_pMainView;
    if(pWnd != NULL 
        && pWnd != NULL
        && pWnd != this
//        && pWnd->GetParent() == NULL
        && pWnd->_001OnCmdMsg(pcmdmsg))
        return TRUE;

   return simple_frame_window::_001OnCmdMsg(pcmdmsg);
}

AlbumMainView * AlbumFrameWnd::GetMainView()
{
    ASSERT(base < AlbumMainView >::bases(m_pMainView));
    return (AlbumMainView *) m_pMainView;
}


void AlbumFrameWnd::OnDestroy() 
{
//   simple_frame_window::OnDestroy();
   
//   db_server *pDataCentral = (db_server *) m_pdbcentral;
//   CDBLongSet *pLongsSet = pDataCentral->get_db_long_set();

//   DISaveWindowRect("Álbum");

}

LRESULT AlbumFrameWnd::OnUserMessage(WPARAM wParam, LPARAM lParam)
{
    if(wParam == 54) // ::view Changed
    {
        AlbumMainView::EView iCurrentView = (AlbumMainView::EView) lParam;
        if(iCurrentView == AlbumMainView::ViewNavigator)
        {
            //m_toolbarHtmlView.ShowWindow(SW_SHOW);
//            m_rebar.GetReBarCtrl().ShowBand(3, TRUE);
        }
        else
        {
            //m_toolbarHtmlView.ShowWindow(SW_HIDE);
            //m_rebar.GetReBarCtrl().ShowBand(3, FALSE);
        }
        if(iCurrentView == AlbumMainView::ViewExplorer)
        {
            //m_rebar.GetReBarCtrl().ShowBand(4, TRUE);
        }
        else
        {
            //m_rebar.GetReBarCtrl().ShowBand(4, FALSE);
        }
        layout();
    }
    else if(wParam == 5678)
    {
        string str;
        m_statusbar.SetPaneInfo(0, "1", SBPS_STRETCH | SBPS_NORMAL, 0);
        throw not_implemented_exception();
        //       str.load_string(IDS_ALBUM_SEARCHINGINDICATOR);
        m_statusbar.SetPaneText(0, str);

    }
    else if(wParam == 56789)
    {
        m_statusbar.SetPaneInfo(0, ID_SEPARATOR, SBPS_STRETCH | SBPS_NORMAL, 0);
    }
    else if(wParam == 51678)
    {
        string str((const char *) lParam);
        m_statusbar.SetPaneInfo(0, "1", SBPS_STRETCH | SBPS_NORMAL, 0);
        m_statusbar.SetPaneText(0, str);
    }

    return 0;
}

BOOL AlbumFrameWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
   // TODO: add your specialized code here and/or call the base class
//        ::userbase::menu * pMenu = GetMenu();
//    m_pmenuv033 = new SimpleMenu();
//    m_pmenuv033->LoadMenu(IDR_ALBUM);
//    m_hMenuDefault = m_pmenuv033->GetSafeHmenu();
  //  if(GetStyle() & WS_VISIBLE)
    //{
      //  TRACE("VISIVEL\n");
    //}

    //VERIFY(SetMenu(m_pmenuv033));
    //pMenu->DestroyMenu();

//   cs.hMenu = m_pmenuv033->GetSafeHmenu();
   return simple_frame_window::PreCreateWindow(cs);
}

void AlbumFrameWnd::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
   UNREFERENCED_PARAMETER(nIDCtl);
   // TODO: add your message handler code here and/or call default
   if (lpMeasureItemStruct->CtlType == ODT_MENU)
   {
      ASSERT(lpMeasureItemStruct->CtlID == 0);
      ::userbase::menu* pMenu;

//      _AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
//      if (pThreadState->m_hTrackingWindow == _get_handle())
      {
         // start from popup
//         pMenu = ::userbase::menu::from_handle(pThreadState->m_hTrackingMenu);
      }
//      else
      {
         // start from menubar
//         pMenu = GetMenu();
      }
        if(pMenu)
        {
//            if(base < SimpleMenu >::bases(pMenu))
            {
//                SimpleMenu * pPopup = SimpleMenu::FindPopupMenuFromID((SimpleMenu *) pMenu, lpMeasureItemStruct->itemID, lpMeasureItemStruct->itemData);
/*                if(pPopup != NULL)
                {pPopup->MeasureItem(lpMeasureItemStruct);
                    return;
                }*/
            }
  //          else
            {
/*            ::userbase::menu * pPopup = CMenuUtil::FindPopupMenuFromID(pMenu, lpMeasureItemStruct->itemID);
                if(pPopup != NULL)
                {
                    pPopup->MeasureItem(lpMeasureItemStruct);
                    return;
                }*/
            }
        }
    }

//   simple_frame_window::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

/*bool AlbumFrameWnd::Initialize(db_server *pdbcentral)
{
    m_pdbcentral = pdbcentral;

    m_pdbcentral->get_db_long_set()->LoadWindowCoordinates(
      "Janelas",
      "Álbum",
      this);
    return true;
}*/

void AlbumFrameWnd::OnClose() 
{
   // TODO: add your message handler code here and/or call default

   simple_frame_window::OnClose();
}


void AlbumFrameWnd::OnToolsOptions() 
{
   if(m_poptionsdlg == NULL)
   {
/*      m_poptionsdlg = new AlbumOptionsDialog;
      m_poptionsdlg->create(&m_poptionsdlg);
      m_poptionsdlg->ShowWindow(SW_SHOWNORMAL);*/
   }
   
}

LRESULT AlbumFrameWnd::OnAppLanguage(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
//   return simple_frame_window::OnAppLanguage(wParam, lParam);

   return 0;
/*   if(wParam == CVmsGenApp::WPARAM_LANGUAGE_UPDATE)
   {
      InitializeBars();
   }
   return 0;*/

}

/*bool AlbumFrameWnd::InitializeBars()
{

   bool bResult = true;
    CRelationV001<UINT, UINT, UINT, UINT> * prel;
    CMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);

//   m_menubar.RemoveAllButtons();
    if (!m_menubar.Initialize(
                CMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
            CMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
                prel,
                CFontCentral::AppGetFontCentral()->GetMenuFont()) ||
      VMS_FAILED(m_menubar.LoadMenuBar(IDR_ALBUM)))
   {
      TRACE0("Failed to create toolbar\n");
      bResult = false;      // fail to create
   }

   string str;
   rect rectWnd;
   m_toolbar.GetWindowRect(rectWnd);
   size size;

   while(m_toolbar.GetToolBarCtrl().DeleteButton(0));
    if (!m_toolbar.LoadToolBar(IDR_ALBUM))
   {
      TRACE0("Failed to create toolbar\n");
      bResult = false;      // fail to create
   }
   else
   {
//      UpdateToolBarText(m_toolbar);
      //str.load_string(IDS_ALBUM_NAVIGATOR);
      //m_toolbar.SetButtonText(0, str);
      m_toolbar.SetButtonStyle(
         0, 
         m_toolbar.GetButtonStyle(0) | TBBS_GROUP |
         TBSTYLE_AUTOSIZE);

      //str.load_string(IDS_ALBUM_FULLLIST);
      //m_toolbar.SetButtonText(1, str);
      m_toolbar.SetButtonStyle(
         1, 
         m_toolbar.GetButtonStyle(1) | TBBS_GROUP |
         TBSTYLE_AUTOSIZE);

      //str.load_string(IDS_ALBUM_EXPLORE);
      //m_toolbar.SetButtonText(2, str);
      m_toolbar.SetButtonStyle(
         2, 
         m_toolbar.GetButtonStyle(2) | TBBS_GROUP  |
         TBSTYLE_AUTOSIZE);


      //str.load_string(IDS_ALBUM_SEARCH);
      //m_toolbar.SetButtonText(3, str);
      m_toolbar.SetButtonStyle(
         3, 
         m_toolbar.GetButtonStyle(3) | TBBS_GROUP |
         TBSTYLE_AUTOSIZE);

      //str.load_string(IDS_ALBUM_DUPLICATESLIST);
      //m_toolbar.SetButtonText(4, str);
      m_toolbar.SetButtonStyle(
         4, 
         m_toolbar.GetButtonStyle(4) | TBBS_GROUP |
         TBSTYLE_AUTOSIZE);

      m_toolbar.SetButtonStyle(5,
         m_toolbar.GetButtonStyle(5) |
         TBSTYLE_AUTOSIZE);

      m_toolbar.SetButtonStyle(6,
         m_toolbar.GetButtonStyle(6) |
         TBSTYLE_AUTOSIZE);
      simple_menu_bar::CalcSize(m_toolbar.GetToolBarCtrl(), size);
      m_toolbar.SetWindowPos(NULL, 0, 0, size.cx, size.cy, SWP_NOMOVE | SWP_NOZORDER);
      //m_toolbar.GetToolBarCtrl().AutoSize();
      m_toolbar.GetWindowRect(rectWnd);
      m_toolbar.ModifyStyle(0, WS_VISIBLE);
   m_toolbar.SetBarStyle(m_toolbar.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY);

   m_toolbarExport.SetBarStyle(m_toolbar.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY);
   }


   while(m_toolbarExport.GetToolBarCtrl().DeleteButton(0));
    if (!m_toolbarExport.LoadToolBar(IDR_ALBUM_EXPORT))
   {
      TRACE0("Failed to create toolbar\n");
      bResult = false;      // fail to create
   }
   else
   {
//      UpdateToolBarText(m_toolbarExport);
      //str.load_string(IDS_ALBUM_EXPORTTEXT);
      //m_toolbarExport.SetButtonText(0, str);
      m_toolbarExport.SetButtonStyle(
         0, 
         m_toolbarExport.GetButtonStyle(0) |
         TBSTYLE_AUTOSIZE);

      //str.load_string(IDS_ALBUM_EXPORTMSWORD9);
      //m_toolbarExport.SetButtonText(1, str);
      m_toolbarExport.SetButtonStyle(
         1, 
         m_toolbarExport.GetButtonStyle(1) |
         TBSTYLE_AUTOSIZE);
      m_toolbarExport.GetWindowRect(rectWnd);
      simple_menu_bar::CalcSize(m_toolbarExport.GetToolBarCtrl(), size);
      m_toolbarExport.SetWindowPos(NULL, 0, 0, size.cx, size.cy, SWP_NOMOVE | SWP_NOZORDER);
      //m_toolbar.GetToolBarCtrl().AutoSize();
      m_toolbarExport.GetWindowRect(rectWnd);
      m_toolbarExport.ModifyStyle(0, WS_VISIBLE);
   }





   while(m_toolbarHtmlView.GetToolBarCtrl().DeleteButton(0));
    if (!m_toolbarHtmlView.LoadToolBar(IDR_ALBUM_NAVIGATOR))
   {
      TRACE0("Failed to create toolbar\n");
      bResult = false;      // fail to create
   }
   else
   {
      UpdateToolBarText(m_toolbarHtmlView);
//      str.load_string(IDS_ALBUM_NAVIGATOR_GOBACK);
//      m_toolbarHtmlView.SetButtonText(0, str);

//      str.load_string(IDS_ALBUM_NAVIGATOR_GOFORWARD);
//      m_toolbarHtmlView.SetButtonText(1, str);

      m_toolbarHtmlView.SetButtonStyle(0,
         m_toolbarHtmlView.GetButtonStyle(2) |
         TBSTYLE_AUTOSIZE);

      m_toolbarHtmlView.SetButtonStyle(1,
         m_toolbarHtmlView.GetButtonStyle(2) |
         TBSTYLE_AUTOSIZE);

      m_toolbarHtmlView.SetButtonStyle(2,
         m_toolbarHtmlView.GetButtonStyle(2) |
         TBSTYLE_AUTOSIZE);

      m_toolbarHtmlView.GetToolBarCtrl().AutoSize();
      m_toolbarHtmlView.ModifyStyle(0, WS_VISIBLE);
   }



    const UINT indicators[] =
    {
        AFX_IDS_APP_TITLE,
        AFX_IDS_APP_TITLE
    };
    if (!m_statusbar.SetIndicators(indicators,
        sizeof(indicators)/sizeof(UINT)))
   {
      TRACE0("Failed to create status bar\n");
      return false;      // fail to create
   }
    m_statusbar.SetPaneInfo(0, AFX_IDS_APP_TITLE, SBPS_STRETCH | SBPS_NORMAL, 0);
    m_statusbar.SetPaneInfo(0, AFX_IDS_APP_TITLE, SBPS_NORMAL, 0);
      

    

    SetMenu(NULL);

   return bResult;
}*/

/*bool AlbumFrameWnd::GetToolButtonText(string &str, UINT uiCmd)
{
   UINT uiText = -1;
   switch(uiCmd)
   {
   case ID_ALBUM_NAVIGATOR:
      uiText = IDS_ALBUM_NAVIGATOR;
      break;
   case ID_ALBUM_FULLLIST:
      uiText = IDS_ALBUM_FULLLIST;
      break;
   case ID_ALBUM_TREELIST:
      uiText = IDS_ALBUM_EXPLORE;
      break;
   case ID_ALBUM_SEARCHLIST:
      uiText = IDS_ALBUM_SEARCH;
      break;
   case ID_ALBUM_DUPLICATESLIST:
      uiText = IDS_ALBUM_DUPLICATESLIST;
      break;
   case ID_VIEW_NOTEPAD:
      uiText = IDS_ALBUM_EXPORTTEXT;
      break;
   case ID_MSWORD9:
      uiText = IDS_ALBUM_EXPORTMSWORD9;
      break;
   case ID_GOBACK:
      uiText = IDS_ALBUM_NAVIGATOR_GOBACK;
      break;
   case ID_GOFORWARD:
      uiText = IDS_ALBUM_NAVIGATOR_GOFORWARD;
      break;
   }

   if(uiText == -1)
      return FALSE;
   else
   {
      return str.load_string(uiText) > 0;
   }

}*/

/*void AlbumFrameWnd::UpdateToolBarText(CToolBarV033 &toolbar)
{
   UINT uiID;
   string str;
   for(int i = 0; i < toolbar.get_count(); i++)
   {
      uiID = toolbar.GetItemID(i);
      if(GetToolButtonText(str, uiID))
      {
         toolbar.SetButtonText(i, str);
      }
   }

}*/


BOOL AlbumFrameWnd::OnEraseBkgnd(::ca::graphics * pgraphics) 
{
   UNREFERENCED_PARAMETER(pgraphics);
   return TRUE;
}

void AlbumFrameWnd::TransparentFrameWndUpdateBars()
{
    //if(m_toolbar.LoadToolBar(IDR_ALBUM))
   {
/*      TransparentFrameWndUpdateToolBarText(m_toolbar);
      TransparentFrameWndUpdateToolBarStyle(m_toolbar);
      TransparentFrameWndFixedReBarToolBarLayoutVR(m_toolbar, 1);*/
   }

    //if(m_toolbarExport.LoadToolBar(IDR_ALBUM_EXPORT))
   {
      /*TransparentFrameWndUpdateToolBarText(m_toolbarExport);
      TransparentFrameWndUpdateToolBarStyle(m_toolbarExport);
      TransparentFrameWndFixedReBarToolBarLayoutVR(m_toolbarExport, 2);*/
   }
    
   // if(m_toolbarHtmlView.LoadToolBar(IDR_ALBUM_NAVIGATOR))
   {
      /*TransparentFrameWndUpdateToolBarText(m_toolbarHtmlView);
      TransparentFrameWndUpdateToolBarStyle(m_toolbarHtmlView);
      TransparentFrameWndFixedReBarToolBarLayoutVR(m_toolbarHtmlView, 3);*/
   }

    // if(m_toolbarExplorer.LoadToolBar(IDR_ALBUM_EXPLORER))
   {
      /*TransparentFrameWndUpdateToolBarText(m_toolbarExplorer);
      TransparentFrameWndUpdateToolBarStyle(m_toolbarExplorer);
      TransparentFrameWndFixedReBarToolBarLayoutVR(m_toolbarExplorer, 4);*/
   }

}
