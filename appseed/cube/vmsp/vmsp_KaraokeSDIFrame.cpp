#include "StdAfx.h"
#include "VmspHelp.h"
#include "main_frame.h"
#include "notify_icon.h"
#include "XfplayerDocDataExchange.h"
#include "XfplayerViewUpdateHint.h"
#include "window_frame/FrameSchemaHardCoded001.h"
#include "window_frame/FrameSchemaHardCoded002.h"




#include "document.h"

#include "AlbumMainView.h"
#include "OptionsDialog.h"


static UINT indicators[] =
{
   ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};


KaraokeSDIFrame::KaraokeSDIFrame(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_frame_window(papp), 
   m_toolbarStandard(papp),
   m_toolbarView1(papp),
   m_toolbarView2(papp),
   m_toolbarPlay(papp),
   m_menubar(papp),
   //m_rebar(papp),
   m_statusbar(papp)
{
   m_bCustomFrame = true;
//   m_pruntimeclassMainFrame = &typeid(CMainFrame);
//   m_uiIDMainFrame = IDR_MAINFRAME;
   m_pEditFont = NULL;
   m_pmixerthread = NULL;
   m_wndframework.EnableFullScreen();
   m_wndframework.EnableNotifyIcon();
   m_etranslucency = TranslucencyPresent;
   m_bLayered = false;
}

KaraokeSDIFrame::~KaraokeSDIFrame()
{
   if(m_pEditFont != NULL)
   {
      m_pEditFont->delete_object();
      delete m_pEditFont;
   }
    
//    if(m_pMainFrame != NULL)
  //  {
    //    m_pMainFrame->DestroyWindow();
      //  m_pMainFrame = NULL;
    //}
//   if(m_pAlbumDialog != NULL)
//   {
//      delete m_pAlbumDialog;
//   }
//   if(m_pmenuV033 != NULL)
//   {
//      delete m_pmenuV033;
//   }
//    if(m_pkmcwnd != NULL)
  //  {
    //    delete m_pkmcwnd;
    //}
}

void KaraokeSDIFrame::_001OnCreate(gen::signal_object * pobj)
{

   m_dataid = "KaraokeSDIFrame";
   //lpCreateStruct->hwndParent = m_pMainFrame->GetSafeHwnd();
   //HICON hicon = GetIcon(false);
   pobj->previous();
   //   if(VMS_FAILED(TwcInitialize(true, CTransparentWndContainer::GlobalBuffer)))
   //      return -1;

   m_wndframework.Enable(true); 
   //hicon = GetIcon(false);

   m_wndframework.SetAppearanceTransparency(window_frame::ClientTransparent);

   //hicon = GetIcon(FALSE);
   //m_wndframework.SetSWPFlags(SWP_NOCOPYBITS | SWP_SHOWWINDOW);
   //    m_wndframework.SetSWPFlags(SWP_SHOWWINDOW);

   ::user::interaction* pwnd = GetParent();
   SetDlgCtrlId(AFX_IDW_PANE_FIRST);

    int _db_style = GetStyle();
    ::ca::application * pApp = &System;
//    ModifyStyle(WS_CAPTION | WS_THICKFRAME, 0);
  //  SetDlgCtrlID(IDR_MAINFRAME);
    
//    if(!m_pkmcwnd->CreateEx(0, System.RegisterWndClass(NULL, 0, 0, 0), NULL, WS_VISIBLE, rect(0, 0, 0, 0), NULL, 0, NULL))
  //      return -1;
    //m_pkmcwnd->SetMenu(GetMenu());
//    ModifyStyle(0, WS_CHILD);
  //  SetParent(m_pkmcwnd);

//    ::ca::window * pWnd = GetParent();
  //  UINT nID = GetDlgCtrlId();
    //UINT nID2 = IDR_MAINFRAME;
    //System.simple_message_box("7.5");
//   EnableDocking(CBRS_ALIGN_ANY);
   
//   ::userbase::menu * pMenu = GetMenu();

//    m_pmenuV033 = new CMenuV033();
//    if(pMenu == NULL)
//    {
//        m_pmenuV033->LoadMenu(IDR_XFPLAYER);
//    }
//    else
//    {
//        m_pmenuV033->LoadMenu(pMenu, pApp->MenuV033GetImageList());
//    }
//    m_hMenuDefault = m_pmenuV033->GetSafeHmenu();
//    SetMenu(m_pmenuV033);
    m_hMenuDefault = NULL;
    //SetMenu(NULL);
    //::userbase::menu * pmenuDebug =GetMenu();
    //if(pMenu != NULL)
    //{
        //pMenu->DestroyMenu();
    //}


   

    


/*DIMoveWindow(
      "Karaoke");*/
//   m_bOnSizeSaving = true;
   TransparentFrameWndUpdateBars();
   LoadBarState();



   //m_bCreate = true;
   //return 0;

   OnWndMsgPosCreate();
}

BOOL KaraokeSDIFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    //System.simple_message_box("7.7");
   if( !simple_frame_window::PreCreateWindow(cs) )
      return FALSE;
   // TODO: Modify the Window class or styles here by modifying
   //  the CREATESTRUCT cs
   //cs.style &= ~WS_CLIPSIBLINGS;
    cs.style &= ~WS_CAPTION;
    cs.style &= ~WS_THICKFRAME;
    cs.style |= WS_CLIPCHILDREN;
    cs.style |= WS_VISIBLE;
//    cs.style |= WS_MINIMIZEBOX ;
  //  cs.style |= WS_MAXIMIZEBOX ;
    //cs.style |= WS_CHILD;
     
    //System.simple_message_box("7.6");
   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// KaraokeSDIFrame diagnostics

#ifdef _DEBUG
void KaraokeSDIFrame::assert_valid() const
{
   simple_frame_window::assert_valid();
}

void KaraokeSDIFrame::dump(dump_context & dumpcontext) const
{
   simple_frame_window::dump(dumpcontext);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// KaraokeSDIFrame message handlers



//void KaraokeSDIFrame::OnToolsAlbum() 
//{
   // TODO: add your command handler code here
//    ViewToolsAlbum();

//}

/*simple_toolbar * KaraokeSDIFrame::GetToolBar()
{

   return &m_toolbarStandard;

}*/





void KaraokeSDIFrame::OnDestroy() 
{
   SaveBarState();
//simple_frame_window::OnDestroy();
   

   
}

void KaraokeSDIFrame::UpdateReserveList()
{
//   CXVmpApp * pApp = (CXVmpApp *) &System;
//   XfplayerDoc *pDoc = pApp->GetActiveDocument();
//   POSITION pos = pDoc->get_view_count();
//   if(pos != NULL)
//   {
//      XfplayerView *pview = (XfplayerView *) pDoc->get_view(pos);
//      pview->UpdateReserveList();
//   }

}


void KaraokeSDIFrame::OnExitFullScreen() 
{
   // TODO: add your command handler code here
   if(IsFullScreen())
   {
      WfiFullScreen(false, true);
   }
}

void KaraokeSDIFrame::OnUpdateExitFullScreen(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   pcmdui->Enable(IsFullScreen());
}

void KaraokeSDIFrame::OnToolsOptions() 
{
   // TODO: add your command handler code here
   //if(db()->IsWorking())
   //{
      OptionsDialog optionsDialog(get_app());
      ASSERT(FALSE);
      // optionsDialog.DoModal();
   //}
   //else
   //{
   //   System.simple_message_box(IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE, MB_ICONINFORMATION);
   //}

}

void KaraokeSDIFrame::OnUpdateToolsOptions(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   pcmdui->Enable();
}

/*void KaraokeSDIFrame::OnFileProperties() 
{
   // TODO: add your command handler code here
   CXfPropertiesDialog propertiesDialog(this);
   propertiesDialog.DoModal();
   
}

void KaraokeSDIFrame::OnUpdateFileProperties(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   CXVmpApp * pApp = (CXVmpApp *) &System;
   ASSERT(pApp != NULL);
   XfplayerDoc * pDoc = pApp->GetPlayerDocument();
    if(pDoc == NULL)
    {
        pcmdui->Enable(FALSE);
        return;
    }
   ASSERT(pDoc != NULL);
   pcmdui->Enable(pDoc->GetMidiPlayer() &&
      pDoc->GetMidiSequenceState() !=
      ::mus::midi::sequence::StatusNoFile &&
        !pDoc->IsPlaying());
   
}*/


BOOL KaraokeSDIFrame::OnHelpInfo(HELPINFO* pHelpInfo) 
{
   // TODO: add your message handler code here and/or call default
   
//return simple_frame_window::OnHelpInfo(pHelpInfo);
   return TRUE;
}




void KaraokeSDIFrame::OnToolsMixer() 
{
//    CMixerDialog * pNewDialog = new CMixerDialog();
  //  m_ptraMixerDialogs.add(pNewDialog);
    //pNewDialog->create(IDD_MIXER);
    //pNewDialog->SetNewDestination(MIXERLINE_COMPONENTTYPE_DST_SPEAKERS);
    //pNewDialog->ShowWindow(SW_SHOWNORMAL);

//   if(m_pmixerthread == NULL)
//   {
//      m_pmixerthread = (CMixerThread *)
//         AfxBeginThread(&typeid(CMixerThread));
//   }
//   if(m_pmixerthread != NULL)
//   {
//      m_pmixerthread->PostMessageViewMixer(true);
//   }

//   CMixerVisualCentral & mixercentral = CMixerVisualCentralContainer::AppGetMixerVisualCentral();
//   mixercentral.DisplayAMixer();
   
}

void KaraokeSDIFrame::OnUpdateToolsMixer(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
}

void KaraokeSDIFrame::OnSize(UINT nType, int cx, int cy) 
{
    simple_frame_window::OnSize(nType, cx, cy);

/*      db_server * pDataCentral = db();
   db_long_set * pLongsSet = pDataCentral->get_db_long_set();
   if(m_bOnSizeSaving)
   {
      DBSaveWindowRect(
         "Karaoke");
   }*/

   

/*    if(IsFullScreen())
    {
        m_wndframework.SetAppearanceMode(window_frame::AppearanceModeFullScreen);
    }
    else if(nType == SIZE_MAXIMIZED)
    {
        m_wndframework.SetAppearanceMode(window_frame::AppearanceModeZoomed);
    }
    else if(nType == SIZE_MINIMIZED)
    {
        m_wndframework.SetAppearanceMode(window_frame::AppearanceModeIconic);
    }
    else if(nType == SIZE_RESTORED)
    {
        m_wndframework.SetAppearanceMode(window_frame::AppearanceModeNormal);
    }
    else
    {
        m_wndframework.SetAppearanceMode(window_frame::AppearanceModeNormal);
    }
  */      

//   m_wndframework.OnSizeRegion(nType, cx, cy);

//    TwcOnSize();
}

void KaraokeSDIFrame::OnToolsCompactdatabase() 
{
}

void KaraokeSDIFrame::OnUpdateToolsCompactdatabase(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   pcmdui->Enable();
}

void KaraokeSDIFrame::OnPlayer() 
{
   musctrl::MusicalPlayerCentral & playercentral =
      musctrl::MusicalPlayerCentral::AppGetMusicalPlayerCentral(get_app());
   musctrl::single_document_template * pdoctemplate = playercentral.get_document_template();
   XfplayerDoc * pDoc = dynamic_cast < XfplayerDoc * > (pdoctemplate->get_document(0));
    if(pDoc == NULL)
    {
        pdoctemplate->open_document_file(NULL);
    }
   
}

void KaraokeSDIFrame::OnUpdatePlayer(cmd_ui * pcmdui) 
{
   // TODO: add your command update UI handler code here
   pcmdui->Enable();
}

void KaraokeSDIFrame::OnWindowCascade() 
{
   // TODO: add your command handler code here
   ::frame_window * pFrameWnd = GetActiveFrame();
    if(pFrameWnd != NULL)
    {
       ::user::interaction* pWnd = pFrameWnd;
        while(true)
        {
            if(base < PlaylistFrame >::bases(pWnd))
            {
               ::frame_window * pParent = pWnd->GetParentFrame();
                pWnd->ModifyStyle(0, WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, SWP_NOACTIVATE | SWP_FRAMECHANGED);
            }
            pWnd = pWnd->GetNextWindow();
            //trans//if(pWnd == NULL ||
              //  pWnd->set_handle(pFrameWnd->_get_handle()))
                //break;
        }
    }
//   MDICascade();
    pFrameWnd = GetActiveFrame();
    if(pFrameWnd != NULL)
    {
       ::user::interaction* pWnd = pFrameWnd;
        while(true)
        {
            if(base < PlaylistFrame >::bases(pWnd))
            {
                pWnd->ModifyStyle(WS_CAPTION, 0, SWP_NOACTIVATE | SWP_FRAMECHANGED);
            }
            pWnd = pWnd->GetNextWindow();
 //trans           if(pWnd == NULL ||
        //        pWnd->set_handle(pFrameWnd->_get_handle()))
          //      break;
        }
    }
}


BOOL KaraokeSDIFrame::OnCreateClient(LPCREATESTRUCT lpcs, create_context* pContext) 
{
   if(!simple_frame_window::OnCreateClient(lpcs, pContext))
      return FALSE;

   /*if(!m_menubar.Initialize(
                BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
                BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListHueLight(),
                prel,
                System.font_central().GetMenuFont()) ||
      VMS_FAILED(m_menubar.LoadMenuBar(IDR_XFPLAYER_MENUBAR)))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }*/

/*   if(!m_menubar.LoadMenuBar(IDR_XFPLAYER_MENUBAR))
   {
      return -1;
   }*/

//   m_uiIDMenuBar = IDR_XFPLAYER_MENUBAR;

/*   if(!m_toolbarStandard.CreateEx(
        this,
        TBSTYLE_FLAT
      | TBSTYLE_LIST
        | WS_CHILD
      | WS_VISIBLE,
        CBRS_TOOLTIPS
      | CBRS_FLYBY
      | CBRS_TOP
      | CBRS_SIZE_FIXED,
        rect(0, 0, 0, 0),
        IDR_XFPLAYER_STANDARD))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }
    if (!m_toolbarStandard.LoadToolBar(IDR_XFPLAYER_STANDARD))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }*/
    
    string str;


/*    if (!m_toolbarView1.CreateEx(
        this,
        TBSTYLE_FLAT
      | TBSTYLE_LIST
      | WS_CHILD
      | WS_VISIBLE,
        CBRS_TOOLTIPS
      | CBRS_FLYBY
      | CBRS_TOP
      | CBRS_SIZE_FIXED,
        rect(0, 0, 0, 0),
        IDR_XFPLAYER_VIEW1))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }
   #define TBBSTYLE_EX_DRAWDDARROWS 0x00000080
   m_toolbarView1.ModifyStyleEx(0, TBBSTYLE_EX_DRAWDDARROWS, SWP_SHOWWINDOW);

    if (!m_toolbarView2.CreateEx(
        this,
        TBSTYLE_FLAT
      | TBSTYLE_LIST
      | WS_CHILD
      | WS_VISIBLE,
        CBRS_TOOLTIPS
      | CBRS_FLYBY
      | CBRS_TOP
      | CBRS_SIZE_FIXED,
        rect(0, 0, 0, 0),
        IDR_XFPLAYER_VIEW2))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }
   #define TBBSTYLE_EX_DRAWDDARROWS 0x00000080
   m_toolbarView2.ModifyStyleEx(0, TBBSTYLE_EX_DRAWDDARROWS, SWP_SHOWWINDOW);

    if (!m_toolbarPlay.CreateEx(
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
      !m_toolbarPlay.LoadToolBar(IDR_XFPLAYER_PLAY))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }

   if (!m_dialogbar.create(this, IDR_MAINFRAME, 
      CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
   {
      TRACE0("Failed to create dialogbar\n");
      return -1;      // fail to create
   }

   m_dialogbar.FillCodePageCombo();

   OnUpdateLyricsCodePage();

   if (//!m_rebar.create(this,
          //  RBS_BANDBORDERS,
            //WS_CHILD
            /*| WS_VISIBLE
            | WS_CLIPSIBLINGS
            | WS_CLIPCHILDREN
            | CBRS_TOP
            | WS_BORDER)
        || !m_rebar.AddBar(
            &m_menubar, NULL, NULL,
            RBBS_BREAK
            | RBBS_FIXEDBMP)*/
   /*   !m_rebar.AddBar(
            &m_toolbarStandard,
            NULL, 
            NULL,
            RBBS_BREAK 
            | RBBS_FIXEDBMP)
      || !m_rebar.AddBar(
            &m_dialogbar,
            NULL, 
            NULL,  
            RBBS_FIXEDBMP)
      || !m_rebar.AddBar(
            &m_toolbarView1, 
            NULL, 
            NULL,
            RBBS_BREAK 
            | RBBS_FIXEDBMP)
      || !m_rebar.AddBar(
            &m_toolbarView2, 
            NULL, 
            NULL,
            RBBS_BREAK 
            | RBBS_FIXEDBMP)
        || !m_rebar.AddBar(
            &m_toolbarPlay,
            NULL, NULL,
            RBBS_BREAK 
            | RBBS_FIXEDBMP)
      )
   {
      TRACE0("Failed to create rebar\n");
      return -1;      // fail to create
   }

   if (!m_statusbar.create(this) ||
      !m_statusbar.SetIndicators(indicators,
        sizeof(indicators)/sizeof(UINT)))
   {
      TRACE0("Failed to create status bar\n");
      return -1;      // fail to create
   }

   // TODO: remove this if you don't want tool tips
   m_toolbarStandard.SetBarStyle(m_toolbarStandard.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY);

   simple_edit *pEdit = (simple_edit * ) m_dialogbar.GetDlgItem(IDC_EDIT_TIME);
//   simple_edit *pEdit = NULL;
   if(pEdit)
   {
      m_pEditFont = new ::ca::font();
      LOGFONT logFont;
      RECT rect;
      pEdit->GetWindowRect(&rect);
      logFont.lfHeight = rect.bottom - rect.top ;
      logFont.lfWidth = 0;
      logFont.lfEscapement = 0;
      logFont.lfWeight = FW_NORMAL;
      logFont.lfItalic = FALSE;
      logFont.lfUnderline = FALSE;
      logFont.lfStrikeOut = FALSE;
      logFont.lfCharSet =   ANSI_CHARSET;
      logFont.lfOutPrecision = OUT_TT_PRECIS;
      logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
      logFont.lfQuality = PROOF_QUALITY;
//      logFont.lfPitchAndFamily =  FIXED_PITCH | FF_SWISS;
      logFont.lfPitchAndFamily = 0;
      lstrcpy(logFont.lfFaceName, "Arial");
      m_pEditFont->CreateFontIndirect(&logFont);
      pEdit->SetFont(m_pEditFont);
   }*/


   return TRUE;
}

afx_msg LRESULT KaraokeSDIFrame::OnEconoModeChange(WPARAM wParam, LPARAM lParam)
{
    int iEconoMode = wParam;
    SendMessageToDescendants(VMSM_ECONOMODECHANGE, iEconoMode);
    return true;
}

void KaraokeSDIFrame::OnToolsSaveMemory() 
{
    gen::savings & savings = System.savings();
    savings.m_eresourceflagsShouldSave.toggle_signalization(gen::resource_memory);
    
}

void KaraokeSDIFrame::OnUpdateToolsSaveMemory(cmd_ui * pcmdui) 
{
   gen::savings & savings = System.savings();
   pcmdui->_001SetCheck(savings.is_trying_to_save(gen::resource_memory));
   pcmdui->Enable();
}

void KaraokeSDIFrame::OnActivate(UINT nState, ::ca::window* pWndOther, BOOL bMinimized) 
{

//simple_frame_window::OnActivate(nState, pWndOther, bMinimized);

    m_wndframework.SetActiveFlag(nState == WA_ACTIVE    ||
        nState == WA_CLICKACTIVE);


    //RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_FRAME);
   // TODO: add your message handler code here
   
}

/*
BOOL KaraokeSDIFrame::LoadFrame(const char * pszMatter, DWORD dwDefaultStyle, ::ca::window* pParentWnd, create_context* pContext) 
{
   pParentWnd = NULL;
   // TODO: add your specialized code here and/or call the base class
    //System.simple_message_box("7.8");
    string str;
    str.Format("nIDResource %s", pszMatter);
    //System.simple_message_box(str);
    //if(pParentWnd == NULL);
//    if(!m_pMainFrame->create(
  //      NULL,NULL))
    //    return FALSE;

//    pParentWnd = m_pMainFrame;
    ASSERT(pParentWnd == NULL);

//    str.load_string(IDR_XFPLAYER);
  //  m_pMainFrame->SetWindowText(str);
    

   if(!simple_frame_window::LoadFrame(pszMatter, dwDefaultStyle, pParentWnd, pContext))
        return FALSE;
    //System.simple_message_box("7.9");

//    delete m_pMenu;
//
  //  m_pMenu = new ::userbase::menu();
    //m_pMenu->LoadMenu(IDR_MAINFRAME);
    //SetMenu(m_pMenu);

    return TRUE;
}

*/
void KaraokeSDIFrame::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
   // TODO: add your message handler code here and/or call default
   //if(m_pMenuManager->RelayDrawItem(nIDCtl, lpDrawItemStruct) == VMSR_SUCCESS)
        //return;
//    m_pMenuManager->RelayDrawItem(nIDCtl, lpDrawItemStruct);
//simple_frame_window::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

/*void KaraokeSDIFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
   // TODO: add your message handler code here and/or call default
//    m_pMenuManager->RelayMeasureItem(this, nIDCtl, lpMeasureItemStruct);
   simple_frame_window::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}*/

void KaraokeSDIFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
   // TODO: add your message handler code here and/or call default
   if (lpMeasureItemStruct->CtlType == ODT_MENU)
   {
      ASSERT(lpMeasureItemStruct->CtlID == 0);
      ::userbase::menu* pMenu;

//   _AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
//      if (pThreadState->m_hTrackingWindow == _get_handle())
      {
         // start from popup
//      pMenu = ::userbase::menu::from_handle(pThreadState->m_hTrackingMenu);
      }
  //      else if(GetStyle() & WS_CHILD)
        {
            //if(VMS_FAILED(m_menubar.GetMenu((CMenuV033**) &pMenu)))
                 pMenu = NULL;
        }
   //   else
      {
         // start from menubar
//      pMenu = GetMenu();
      }
    
/*        if(pMenu)
        {
            if(base < CMenuV033 >::bases(pMenu))
            {
                CMenuV033 * pPopup = CMenuV033::FindPopupMenuFromID((CMenuV033*) pMenu, lpMeasureItemStruct->itemID, lpMeasureItemStruct->itemData);
                if(pPopup != NULL)
                {
                    pPopup->MeasureItem(lpMeasureItemStruct);
                    return;
                }
            }
            else
            {
            ::userbase::menu * pPopup = CMenuUtil::FindPopupMenuFromID(pMenu, lpMeasureItemStruct->itemID);
                if(pPopup != NULL)
                {
                    pPopup->MeasureItem(lpMeasureItemStruct);
                    return;
                }
            }
        }*/
    } 

   //simple_frame_window::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

/*void KaraokeSDIFrame::OpenToolsAlbum()
{
    CXVmpApp * pApp = (CXVmpApp *)&System;
    if(db()->IsWorking())
    {
       if(m_pAlbumDialog == NULL)
       {
          m_pAlbumDialog = new CAlbumDialog();
          if(!m_pAlbumDialog->create(IDD_ALBUM))
          {
             delete m_pAlbumDialog;
             m_pAlbumDialog = NULL;
          }
       }
       //dlg.DoModal();
       if(m_pAlbumDialog != NULL)
       {
            if(db()->IsBuildingSongsAlbum())
            {
                critical_section *pcs;
                LPBUILDALBUMTHREADDATA lpData =
                    db()->GetActiveBuildAlbumThreadData(&pcs);
                if(lpData != NULL)
                {
                    lpData->m_taskDialog.m_pCloseWindow = m_pAlbumDialog;
               lpData->m_taskDialog.SetPendingShowCommandFlag(true);
                }
                pcs->Unlock();
            }
            else
            {
//                m_pAlbumDialog->Update(); // retirar se possível
              m_pAlbumDialog->ShowWindow(SW_SHOWNORMAL);
              m_pAlbumDialog->SetWindowPos(
                 &wndTop,
                 0, 0,
                 0, 0,
                 SWP_NOMOVE |
                 SWP_NOSIZE); //|
                 //SWP_SHOWWINDOW);
            }
       }
       
       ::ca::window * pParent = GetParent();
    }
    else
    {
        System.simple_message_box(
            IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE,
            MB_OK |
            MB_ICONINFORMATION);

    }

}*/

void KaraokeSDIFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   // TODO: add your message handler code here and/or call default
   if(nChar == VK_ESCAPE &&
        IsFullScreen())
    {
        WfiFullScreen(false, true);
    }
    else
    {
//       simple_frame_window::OnKeyDown(nChar, nRepCnt, nFlags);
    }
}

/*void KaraokeSDIFrame::ViewFullScreen(bool bFullScreen)
{   
   TransparentFrameWndFullScreen(bFullScreen);

}*/

//VMSRESULT KaraokeSDIFrame::ViewToolsAlbum()
//{
  //  OpenToolsAlbum();
    //return VMSR_SUCCESS;
//}

BOOL KaraokeSDIFrame::DestroyWindow() 
{
   // TODO: add your specialized code here and/or call the base class
   
   return simple_frame_window::DestroyWindow();
}

void KaraokeSDIFrame::layout() 
{
    m_wndframework.layout();
   SaveBarState();
   //simple_frame_window::layout(bNotify);
}

/*BOOL KaraokeSDIFrame::OnNcActivate(BOOL bActive) 
{
   // TODO: add your message handler code here and/or call default
   
    m_wndframework.SetNcActiveFlag(bActive);

   return simple_frame_window::OnNcActivate(bActive);
}*/

void KaraokeSDIFrame::TwcRenderBackground(::ca::graphics *pdc, LPCRECT lpcrect)
{

   m_wndframework.OnDraw(pdc, lpcrect);

}

void KaraokeSDIFrame::OnViewCompactSize() 
{
   ToggleCompactMode();
}

void KaraokeSDIFrame::OnUpdateViewCompactSize(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
   pcmdui->_001SetCheck(IsCompactMode());
}


void KaraokeSDIFrame::OnUpdateVmsguiClose(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
}

void KaraokeSDIFrame::OnUpdateVmsguiWindowMinimize(cmd_ui * pcmdui) 
{
   pcmdui->Enable();
}


LRESULT KaraokeSDIFrame::OnAppLanguage(WPARAM wparam, LPARAM lparam)
{
   //return simple_frame_window::OnAppLanguage(wparam, lparam);
   return 0;
}

void KaraokeSDIFrame::TransparentFrameWndUpdateBars()
{
//   simple_frame_window::TransparentFrameWndUpdateBars();
   bool bResult = true;
   int_int_spreadset * prel;
//   BaseMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
   

/*   while(m_toolbarStandard.GetToolBarCtrl().DeleteButton(0));
    if (!m_toolbarStandard.LoadToolBar(IDR_XFPLAYER_STANDARD))
   {
      bResult = false;
   }*/
    string str;

    
//    int i;

/*   TransparentFrameWndUpdateToolBarText(m_toolbarStandard);
   TransparentFrameWndUpdateToolBarStyle(m_toolbarStandard);
   TransparentFrameWndFixedReBarToolBarLayoutVR(m_toolbarStandard, 1);
*/

   //while(m_toolbarView.GetToolBarCtrl().DeleteButton(0));
/*    if (!m_toolbarView1.LoadToolBar(IDR_XFPLAYER_VIEW1))
   {
      bResult = false;
   }
*/
/*   TransparentFrameWndUpdateToolBarText(m_toolbarView1);
   TransparentFrameWndUpdateToolBarStyle(m_toolbarView1);
   TransparentFrameWndFixedReBarToolBarLayoutVR(m_toolbarView1, 3);
  */  
/*   if (!m_toolbarView2.LoadToolBar(IDR_XFPLAYER_VIEW2))
   {
      bResult = false;
   }
*/
/*   TransparentFrameWndUpdateToolBarText(m_toolbarView2);
   TransparentFrameWndUpdateToolBarStyle(m_toolbarView2);
   TransparentFrameWndFixedReBarToolBarLayoutVR(m_toolbarView2, 4);
*/
  /*  if (!m_toolbarPlay.LoadToolBar(IDR_XFPLAYER_PLAY))
   {
      bResult = false;
   }*/
/*
   TransparentFrameWndUpdateToolBarText(m_toolbarPlay);
   TransparentFrameWndUpdateToolBarStyle(m_toolbarPlay);
   TransparentFrameWndFixedReBarToolBarLayoutVR(m_toolbarPlay, 5);
*/
/*   if (!m_statusbar.SetIndicators(indicators,
        sizeof(indicators)/sizeof(UINT)))
   {
      bResult = false;
   }
*/
/*   m_toolbarStandard.SetBarStyle(m_toolbarStandard.GetBarStyle() |
      CBRS_TOOLTIPS | CBRS_FLYBY);

   simple_edit *pEdit = (simple_edit * ) m_dialogbar.GetDlgItem(IDC_EDIT_TIME);
   if(pEdit)
   {
      m_pEditFont = new ::ca::font();
      LOGFONT logFont;
      RECT rect;
      pEdit->GetWindowRect(&rect);
      logFont.lfHeight = rect.bottom - rect.top ;
      logFont.lfWidth = 0;
      logFont.lfEscapement = 0;
      logFont.lfWeight = FW_NORMAL;
      logFont.lfItalic = FALSE;
      logFont.lfUnderline = FALSE;
      logFont.lfStrikeOut = FALSE;
      logFont.lfCharSet =   ANSI_CHARSET;
      logFont.lfOutPrecision = OUT_TT_PRECIS;
      logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
      logFont.lfQuality = PROOF_QUALITY;
//      logFont.lfPitchAndFamily =  FIXED_PITCH | FF_SWISS;
      logFont.lfPitchAndFamily = 0;
      lstrcpy(logFont.lfFaceName, "Arial");
      m_pEditFont->CreateFontIndirect(&logFont);
      pEdit->SetFont(m_pEditFont);
   }
*/
/*   CReBarCtrl & rebarctrl = m_rebar.GetReBarCtrl();

   for(UINT user = 0; user < rebarctrl.GetBandCount(); user++)
   {
      rebarctrl.MaximizeBand(user);
   }*/

   layout();

//   CSliderCtrl *pSlider = (CSliderCtrl *) m_dialogbar.GetDlgItem(IDC_SLIDER);
//   if(pSlider)
//   {
//      pSlider->SetRange(0, 1000000);
//   }
   
   
}

afx_msg LRESULT KaraokeSDIFrame::OnAppNotify(WPARAM wParam, LPARAM lParam)
{
   return 0;
}
/*afx_msg LRESULT KaraokeSDIFrame::OnFrameworkV033Command(WPARAM wParam, LPARAM lParam)
{
   if(wParam == 1)
   {
      if(lParam == ID_VMSGUI_CLOSE)
      {
         PostMessage(WM_CLOSE);
         return TRUE;
      }
      else if(lParam == ID_VMSGUI_UP)
      {
         ASSERT(FALSE);
         return TRUE;
      }
      else if(lParam == ID_VMSGUI_DOWN)
      {
         ASSERT(FALSE);
         return TRUE;
      }
      else if(lParam == ID_VMSGUI_WINDOW_MAXIMIZE)
      {
         ShowWindow(SW_MAXIMIZE);
         return TRUE;
      }
      else if(lParam == ID_VMSGUI_WINDOW_MINIMIZE)
      {
         ShowWindow(SW_MINIMIZE);
         return TRUE;
      }
      else if(lParam == ID_VMSGUI_WINDOW_RESTORE)
      {
         ShowWindow(SW_RESTORE);
         return TRUE;
      }
   }
   return FALSE;
}*/

/*void KaraokeSDIFrame::TwiOnDraw(::ca::graphics *pdc)
{

   m_wndframework.OnDraw(pdc);

}*/

/*bool KaraokeSDIFrame::GetToolButtonText(string &str, UINT uiCmd)
{
   UINT uiText = -1;
   switch(uiCmd)
   {
   case ID_TOOLS_ALBUM:
      uiText = IDS_XFPLAYER_ALBUM;
      break;
   case ID_VIEW_PLAYLIST:
      uiText = IDS_XFPLAYER_PLAYLIST;
      break;
   case ID_VIEW_LYRICS:
      uiText = IDS_XFPLAYER_LYRICS;
      break;
   case ID_VIEW_FULL_SCREEN:
      uiText = IDS_XFPLAYER_FULLSCREEN;
      break;
   case ID_PLAY:
      uiText = IDS_XFPLAYER_PLAY;
      break;
   case ID_PAUSE:
      uiText = IDS_XFPLAYER_PAUSE;
      break;
   case ID_STOP:
      uiText = IDS_XFPLAYER_STOP;
      break;
   case ID_NEXTSONG:
      uiText = IDS_XFPLAYER_NEXTSONG;
      break;
   }

   if(uiText == -1)
      return FALSE;
   else
   {
      return str.load_string(uiText) != 0;
   }
}
*/
/*void KaraokeSDIFrame::UpdateToolBarText(simple_toolbar &toolbar)
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

/*void KaraokeSDIFrame::UpdateToolBarStyle(CToolBarCtrlV017 &toolbar)
{
   UINT uiID;
   string str;
   TBBUTTONINFOW tbbi;
    tbbi.cbSize = sizeof(tbbi);
    
   rect rect;
   TBBUTTON tbb;
   for(int i = 0; i < toolbar.GetButtonCount(); i++)
   {
      toolbar.GetButton(i, &tbb);
      uiID = tbb.idCommand;
      tbbi.dwMask = TBIF_STYLE;
        toolbar.GetButtonText(uiID, str);
      if(!str.is_empty()
         && !(tbbi.fsStyle & TBSTYLE_SEP))
      {
         tbbi.fsStyle |= TBSTYLE_AUTOSIZE;
      }
      else
      {
         tbbi.fsStyle &= ~TBSTYLE_AUTOSIZE;
      }
      tbbi.dwMask = TBIF_STYLE ;
        toolbar.SetButtonInfo(uiID, &tbbi);

      toolbar.GetItemRect(i, rect);
      TRACE("button.width %d\n", rect.width());
      TRACE("button.height %d\n", rect.height());
   }
}*/

/*void KaraokeSDIFrame::UpdateToolBarStyle(simple_toolbar &toolbar)
{
   UINT uiID;
   string str;
   TBBUTTONINFOW tbbi;
    tbbi.cbSize = sizeof(tbbi);
    tbbi.dwMask = TBIF_STYLE ;
   rect rect;
   for(int i = 0; i < toolbar.get_count(); i++)
   {
      uiID = toolbar.GetItemID(i);
      toolbar.GetButtonText(i, str);
        toolbar.GetToolBarCtrl().GetButtonInfo(uiID, &tbbi);
//      if(!str.is_empty()
      //   && !(tbbi.fsStyle & TBSTYLE_SEP))
      if(!(tbbi.fsStyle & TBSTYLE_SEP))
      {
         tbbi.fsStyle |= TBSTYLE_AUTOSIZE;
      }
      else
      {
         tbbi.fsStyle &= ~TBSTYLE_AUTOSIZE;
      }
        toolbar.GetToolBarCtrl().SetButtonInfo(uiID, &tbbi);

      toolbar.GetItemRect(i, rect);
      TRACE("button.width %d\n", rect.width());
      TRACE("button.height %d\n", rect.height());
   }
}*/


/*void KaraokeSDIFrame::UpdateToolBarText(CToolBarCtrlV017 &toolbar)
{
   UINT uiID;
   string str;
   TBBUTTONINFOW tbbi;
    tbbi.cbSize = sizeof(tbbi);
   TBBUTTON tbb;
   for(int i = 0; i < toolbar.GetButtonCount(); i++)
   {
      toolbar.GetButton(i, &tbb);
      uiID = tbb.idCommand;
      if(GetToolButtonText(str, uiID))
      {
         tbbi.pszText = (wchar_t *) (const wchar_t *) str;
         tbbi.cchText = str.get_length();
         tbbi.dwMask = TBIF_TEXT ;
         toolbar.SetButtonInfo(uiID, &tbbi);
      }
   }
}*/

bool KaraokeSDIFrame::TransparentFrameWndShowBars(int nCmdShow)
{
//   m_menubar.ShowWindow(nCmdShow);
//   m_toolbarStandard.ShowWindow(nCmdShow);
//   m_toolbarView.ShowWindow(nCmdShow);
//   m_toolbarPlay.ShowWindow(nCmdShow);
   if(nCmdShow == SW_HIDE)
   {
      SaveBarState();
   }
//   m_rebar.ShowWindow(nCmdShow);
//   m_statusbar.ShowWindow(nCmdShow);
   if(nCmdShow == SW_SHOW)
   {
      LoadBarState();
   }
   layout();
   return true;
}

void KaraokeSDIFrame::OnHelpFinder() 
{
   gen::application * papp = dynamic_cast < gen::application  * > (get_app());
   string wstrFolder;
//   wstrFolder.SetOEM(papp->m_strModuleFolder);
   string str;
   throw not_implemented_exception();
   //str.load_string(IDS_HELP_FINDER);
/*   HtmlHelpW(m_hWnd, wstrFolder + str, HH_DISPLAY_TOPIC, 0);*/
   
}

void KaraokeSDIFrame::SaveBarState()
{
//   if(_000IsWindowCreated())
//   {
//   simple_frame_window::SaveBarState(DIGetSection());
//   }
}

void KaraokeSDIFrame::LoadBarState()
{
   //simple_frame_window::LoadBarState(m_strRegistrySection);
}

void KaraokeSDIFrame::WinHelp(DWORD dwData, UINT nCmd) 
{
//   CWndHtmlHelp(this, dwData, nCmd);
/*   CHelpCentral::WndHtmlHelp(
      this, 
      dwData,
      nCmd,
      VmspHelp::rowaContextSensitive);*/
}


/*XfplayerView * KaraokeSDIFrame::GetLyricView()
{
   ::ca::window * pwnd = GetTopWindow();
   while(pwnd != NULL)
   {
      if(base < XfplayerView >::bases(pwnd))
         return (XfplayerView *) pwnd;
      pwnd = pwnd->GetNextWindow();
   }
   return NULL;

}*/

void KaraokeSDIFrame::OnUpdateLyricsCodePage()
{
   vmsp::DocumentInterface * pdoc = GetActiveDocumentEx();
   XfplayerDocDataExchange dx(GetActiveDocumentEx());
// linux   m_dialogbar.SetCodePage(dx.GetSongEncoding());

}

bool KaraokeSDIFrame::OnWndMsgPosCreate()
{
   simple_frame_window::OnWndMsgPosCreate();
   
   int iCompactMode = 0;
   data_get("Compact Mode", iCompactMode);

   

    
   SetCompactMode(iCompactMode != 0);

   return true;
}

bool KaraokeSDIFrame::TransparentFrameWndIsCompactMode()
{
   return IsCompactMode();
}

CMDIFrameWnd * KaraokeSDIFrame::TransparentMDIChildWndGetMDIFrameEx()
{
//   return simple_frame_window::TransparentMDIChildWndGetMDIFrameEx();
   return NULL;
}

void KaraokeSDIFrame::WfiOnAfterFullScreen(bool bFullScreen)
{
//   CTransparentFrameWndInterface::WfiOnAfterFullScreen(bFullScreen);
}

void KaraokeSDIFrame::OnCompactModeChange(bool bCompact)
{
   if(bCompact)
   {
      data_set("Compact Mode", 1);
      if(IsFullScreen())
      {
      }
      else
      {
         TransparentFrameWndShowBars(SW_HIDE);
      }
   }
   else
   {
      data_set("Compact Mode", 0);
      if(IsFullScreen())
      {
      }
      else
      {
         TransparentFrameWndShowBars(SW_SHOWNORMAL);
      }
   }
   layout();
   XfplayerViewUpdateHint uh;
   uh.AddType(XfplayerViewUpdateHint::CompactModeChange);
   if(GetActiveDocument() != NULL)
      GetActiveDocument()->update_all_views(NULL, 0, &uh);
}

void KaraokeSDIFrame::WfiOnNotiyIcon()
{
   vmsp::notify_icon * pni = vmsp::notify_icon::AppGetNotifyIcon(get_app());

}

void KaraokeSDIFrame::WfiOnNotifyIcon()
{
   ShowWindow(SW_HIDE);
   vmsp::notify_icon * pni = vmsp::notify_icon::AppGetNotifyIcon(get_app());
// trans  pni->AddHiddenWindow(this);
}

vmsp::DocumentInterface * KaraokeSDIFrame::GetActiveDocumentEx()
{
   return dynamic_cast < vmsp::DocumentInterface * > (GetActiveDocument());

}

void KaraokeSDIFrame::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   simple_frame_window::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &KaraokeSDIFrame::_001OnCreate);
}


window_frame::FrameSchema * KaraokeSDIFrame::create_frame_schema()
{
   window_frame::FrameSchemaHardCoded002 * pschema = new window_frame::FrameSchemaHardCoded002(get_app());
   pschema->SetStyle(window_frame::FrameSchemaHardCoded002::StyleLightBlue);
   pschema->m_pruntimeclassControlBoxButton = typeid(MetaButton);
   return pschema;
}
