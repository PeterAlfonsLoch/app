#include "StdAfx.h"

#include "MixerDoc.h"
#include "MixerControlView.h"
#include "MixerControlData.h"
#include "MixerVisualCentral.h"

#include "mute_control.h"

#define IDC_MIXER_SLIDER 1000
#define IDC_BUTTON_RESERVE 1002
#define ID_VIEW_UPDATE 1003
#define IDI_ALBUM 1004
#define IDS_MIXER_DIALOG_TITLEFORMAT 1006
#define IDS_MIXER_SPEAKERSCONTROLS 1007
#define IDS_MIXER_WAVEINCONTROLS 1008


const int MixerMainView::cnListCount = 9;

MixerMainView::MixerMainView(::ca::application * papp) :
   ca(papp),
   ::user::tab(papp),
   ::userbase::view(papp),
   ::userbase::tab_view(papp),
   ::userex::pane_tab_view(papp),
   m_brushBackground(papp),
   place_holder_container(papp)
{

/*   ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, OnColumnclickList)
   ON_WM_SIZE()
   ON_WM_DESTROY()
   ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST, OnGetdispinfoList)
   ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
   ON_BN_CLICKED(IDC_BUTTON_RESERVE, OnButtonReserve)
   ON_WM_CREATE()
   ON_WM_TIMER()
   ON_WM_CONTEXTMENU()
   ON_UPDATE_COMMAND_UI(ID_VIEW_UPDATE, OnUpdateViewUpdate)
   ON_WM_INITMENUPOPUP()
   ON_WM_VSCROLL()
   ON_WM_CTLCOLOR()
   ON_WM_HSCROLL()*/



   m_pcontrol = NULL;

//   m_pruntimeclassMuteControl = &typeid(_vmsmixguserbaseMuteControl);

   m_etranslucency = TranslucencyPresent;

   m_bInitialized = false;
//   m_iCacheNextIndex = 0;
    m_uiNextSliderID = IDC_MIXER_SLIDER;

   //m_crForeground = GetSysColor(COLOR_BTNTEXT);
   //m_crForeground = RGB(255, 255, 255);
   //m_crForeground = RGB(255, 255, 255)
   //m_crBackground = RGB(58,80,110);
   //m_crBackground = GetSysColor(COLOR_3DFACE);
   m_crBackground = RGB(74, 70, 64);

   //m_brushBackground.CreateSolidBrush(m_crBackground);
   //m_crForeground = RGB(255, 255, 255);
   
   m_brushBackground->CreateStockObject(NULL_BRUSH);
   m_crForeground = RGB(0, 0, 0);


   m_dwUpdateTime = 0;
   TRACE("AlbumFormView this = %x \n", this);
}

MixerMainView::~MixerMainView()
{

}

void MixerMainView::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::userex::pane_tab_view::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &MixerMainView::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &MixerMainView::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &MixerMainView::_001OnCreate);
//   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &MixerMainView::_001OnTimer);
  // IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &MixerMainView::_001OnContextMenu);
//   IGUI_WIN_MSG_LINK(WM_VSCROLL, pinterface, this, &MixerMainView::_001OnVScroll);
   IGUI_WIN_MSG_LINK(WM_CTLCOLOR, pinterface, this, &MixerMainView::_001OnCtlColor);

//   IGUI_WIN_ON_NOTIFY(LVN_COLUMNCLICK  , IDC_LIST, this, this, &MixerMainView::_001OnColumnclickList);
  // IGUI_WIN_ON_NOTIFY(NM_DBLCLK        , IDC_LIST, this, this, &MixerMainView::_001OnDblclkList);
   //IGUI_WIN_ON_NOTIFY(LVN_GETDISPINFO  , IDC_LIST, this, this, &MixerMainView::_001OnGetdispinfoList);

   IGUI_WIN_ON_CONTROL(BN_CLICKED, IDC_BUTTON_RESERVE     , this, this, &MixerMainView::_001OnButtonReserve);

   connect_update_cmd_ui(ID_VIEW_UPDATE, &MixerMainView::_001OnUpdateViewUpdate);
}



#ifdef _DEBUG
void MixerMainView::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void MixerMainView::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}

MixerDoc* MixerMainView::get_document() // non-debug version is inline
{
   ASSERT(base < MixerDoc > :: bases(::view::get_document()));
   return dynamic_cast < MixerDoc * > (::view::get_document());
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MixerMainView message handlers

void MixerMainView::_001OnSize(gen::signal_object * pobj) 
{
   if(!m_bInitialized)
      return;
   if(pobj->previous())
      return;

   LayoutControl();
}

void MixerMainView::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   wait_cursor cwc(get_app());

   //CVMSApp *pApp = (CVMSApp *) &System;
//   db_server *pDataCentral = (db_server *) &System.db();


//   ::user::interaction* pWnd = GetParent();
   

   HINSTANCE hinstance = System.m_hInstance;

   /*HICON hIcon = (HICON) LoadImage(hinstance,
      MAKEINTRESOURCE(IDI_ALBUM),
      IMAGE_ICON,
      16, 16,
      0);*/

// dbbreak    SetIcon(hIcon, false);

    /*hIcon = (HICON) LoadImage(hinstance,
        MAKEINTRESOURCE(IDI_ALBUM),
        IMAGE_ICON,
        0, 0,
        LR_DEFAULTSIZE);*/

 // dbbreak   SetIcon(hIcon, true);
   

   return ;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

void MixerMainView::_001OnGetdispinfoList(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::notify, pnotify, pobj)
      //LV_DISPINFO* pDispInfo = (LV_DISPINFO*) pnotify->get_lpnmhdr();
   // TODO: add your control notification handler code here
//   LV_ITEM* pItem= &(pDispInfo)->item;

//   int iItemIndx= pItem->iItem;
   

   pnotify->set_lresult(0);
}

void MixerMainView::_001OnDestroy(gen::signal_object * pobj) 
{
   
   
   UNREFERENCED_PARAMETER(pobj);
   
}

void MixerMainView::_001OnColumnclickList(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::notify, pnotify, pobj)
//      NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pnotify->get_lpnmhdr();
   // TODO: add your control notification handler code here
   
/*   int iColumnIndex;
   switch(pNMListView->iSubItem)
   {
   case 0:
      iColumnIndex = DB_SONGS_COUNTRY;
      break;
   case 1:
      iColumnIndex = DB_SONGS_NAME;
      break;
   case 2:
      iColumnIndex = DB_SONGS_COMPOSER;
      break;
   case 3:
      iColumnIndex = DB_SONGS_LYRICIST;
      break;
   case 4:
      iColumnIndex = DB_SONGS_ARRANGER;
      break;
   case 5:
      iColumnIndex = DB_SONGS_PERFORMER;
      break;
   case 6:
      iColumnIndex = DB_SONGS_PROGRAMMER;
      break;
   case 7:
      iColumnIndex = DB_SONGS_CODE;
      break;
   case 8:
      iColumnIndex = DB_SONGS_PATH;
      break;
   default:
      iColumnIndex = -1;
   }

//   theApp.GetSongsSet()->Sort(iColumnIndex);
//   m_cacheMap.remove_all();
//   CListCtrl *pList = (CListCtrl *) GetDlgItem(IDC_LIST);
//   pList->RedrawItems(0, pList->get_item_count() - 1);

   *pResult = 0;*/
}



void MixerMainView::_001OnDblclkList(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::notify, pnotify, pobj)
   // TODO: add your control notification handler code here
//   LPNMLISTVIEW lpnmlv = (LPNMLISTVIEW) pnotify->get_lpnmhdr();
//   CListCtrl * pList = (CListCtrl *) GetDlgItem(lpnmlv->hdr.idFrom);
   pnotify->set_lresult(0);
}

void MixerMainView::_001OnButtonReserve(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   // TODO: add your control notification handler code here
}






void MixerMainView::pre_translate_message(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   if(pbase->m_uiMessage == MM_MIXM_CONTROL_CHANGE)
    {
      ASSERT(FALSE);
    }
    else if(pbase->m_uiMessage == MM_MIXM_LINE_CHANGE)
    {
      ASSERT(FALSE);
    }
   if(pbase->m_uiMessage == WM_DISPLAYCHANGE)
   {
//      SetImageLists();
   }

   return ::userbase::view::pre_translate_message(pobj);
}

/*BOOL MixerMainView::create(UINT nID) 
{
   // TODO: add your specialized code here and/or call the base class
   
   return create(MAKEINTRESOURCE(nID), NULL);
}*/

void MixerMainView::_001OnCreate(gen::signal_object * pobj) 
{
   wait_cursor cwc(get_app());
   if(pobj->previous())
      return ;
/*    m_enhmetafile = GetEnhMetaFile(papp->m_strModuleFolder + "vmsp.emf");
    VERIFY(
        GetEnhMetaFileHeader(
            m_enhmetafile,
            sizeof(m_emh),
            &m_emh)
            );*/

   rect clientRect(0, 0, 0, 0);

   mixeruserbase::application_interface * pappinterface = dynamic_cast < mixeruserbase::application_interface * > (get_app()); 
   MixerVisualCentral * pcentral = &pappinterface->GetMixerVisualCentral();

   add_image_tab(
      pcentral->m_idPlaybackTab, 
      pcentral->m_idPlaybackIcon);
   add_image_tab(
      pcentral->m_idRecordingTab,
      pcentral->m_idRecordingIcon);

   set_cur_tab_by_id(ControlPlayback);


   ::userbase::view::_001OnInitialUpdate(NULL);

   m_bInitialized = true;

}


BOOL MixerMainView::PreCreateWindow(CREATESTRUCT& cs) 
{
   cs.style = cs.style;
//   int i = WS_POPUP;
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
   cs.style |= WS_CLIPCHILDREN;
   return ::userbase::view::PreCreateWindow(cs);
}


/*void MixerMainView::SetImageLists()
{
   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateDC(
      "DISPLAY",
      NULL,
      NULL,
      NULL);
    //CTabCtrl * pTab = (CTabCtrl *) GetDlgItem(IDC_TAB);
   if(m_SmallImageList.GetSafeHandle() != NULL)
   {
      //  pTab->SetImageList(NULL);
   }
   int iBitCount = spgraphics->GetDeviceCaps(BITSPIXEL);
   if(iBitCount > 8)
   {
      m_SmallImageListBitmap.delete_object();
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
         1);
        //m_SmallImageList.SetBkColor(CLR_NONE);
        m_SmallImageList.SetBkColor(GetSysColor(COLOR_WINDOW));
      m_SmallImageList.add(&m_SmallImageListBitmap, RGB(255, 0, 255));
        m_SmallImageListV001.SetBkColor(GetSysColor(COLOR_BTNFACE));
      m_SmallImageListV001.add(&m_SmallImageListBitmapV001, RGB(255, 0, 255));
        
   }
   else
   {
      m_SmallImageListBitmap.delete_object();
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
        
   }
   if(m_SmallImageList.GetSafeHandle() != NULL)
   {
   }
   if(m_SmallImageListV001.GetSafeHandle() != NULL)
   {
//        pTab->SetImageList(&m_SmallImageListV001);
        
   }

   
   spgraphics->DeleteDC();
}
*/

void MixerMainView::_001OnUpdateViewUpdate(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
   pupdatecmdui->m_pcmdui->Enable();
   pupdatecmdui->m_bRet = true;
}







void MixerMainView::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
{
   UNREFERENCED_PARAMETER(pHint);
   UNREFERENCED_PARAMETER(pSender);
   switch(lHint)
   {
   case 13:
      break;
   case 4:
      break;
   case 14:
      break;
   case 17:
      //New destination set
      {
      }
      break;
    }
   
}




/*void MixerMainView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
   ::user::interaction * pWnd = pScrollBar;
    MixerControl * pControl;
    if(GetMixer()->m_pdevice->m_mapDlgItemIDToControl.Lookup(
        pWnd->GetDlgCtrlId(), pControl))
    {
        pControl->OnVHScroll(nSBCode, nPos, pScrollBar);
    }
    else
        ::userbase::view::OnVScroll(nSBCode, nPos, pScrollBar);
}*/

void MixerMainView::_001OnCtlColor(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::ctl_color, pctlcolor, pobj)
//   HBRUSH hbr = ::userbase::view::OnCtlColor(pgraphics, pWnd, nCtlColor);
/*   HBRUSH hbr;
   if(pctlcolor->m_nCtlType == CTLCOLOR_EDIT)
   {
      pctlcolor->m_pdc->SetTextColor(m_crForeground);
      hbr = m_brushBackground;
      pctlcolor->m_pdc->SetBkColor(m_crBackground);
   }
   else if(pctlcolor->m_nCtlType == CTLCOLOR_MSGBOX)
   {
      hbr = m_brushBackground;
   }
   else if(pctlcolor->m_nCtlType == CTLCOLOR_STATIC)
   {
      pctlcolor->m_pdc->SetTextColor(m_crForeground);
      hbr = m_brushBackground;
      pctlcolor->m_pdc->SetBkColor(m_crBackground);
      pctlcolor->m_pdc->SetBkMode(TRANSPARENT);
   }
   else if(pctlcolor->m_nCtlType == CTLCOLOR_DLG)
   {
//      pgraphics->SetTextColor(RGB(255, 255, 255));
//      hbr = m_brushBackground;
//      pgraphics->SetBkColor(RGB(0, 0, 0));
   }
   else
   {
// trans      pctlcolor->m_hbrush = ::userbase::view::OnCtlColor(pctlcolor->m_pdc, pctlcolor->m_pwnd, pctlcolor->m_nCtlType);
   }*/

}

/*void MixerMainView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
   ::user::interaction * pWnd = pScrollBar;
    MixerControl * pControl;
    if(GetMixer()->m_pdevice->m_mapDlgItemIDToControl.Lookup(
        pWnd->GetDlgCtrlId(), pControl))
    {
        pControl->OnVHScroll(nSBCode, nPos, pScrollBar);
    }
    else
        ::userbase::view::OnHScroll(nSBCode, nPos, pScrollBar);
}

*/

void MixerMainView::_001OnMixerSpeakerscontrols(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   if(_001GetSel() != 0)
   {
      _001SetSel(0);
   }
}

void MixerMainView::_001OnUpdateMixerSpeakerscontrols(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
   if(_001GetSel() == 0)
   {
      pupdatecmdui->m_pcmdui->_001SetCheck();
      pupdatecmdui->m_pcmdui->Enable(TRUE);
   }
   else
   {
      pupdatecmdui->m_pcmdui->_001SetCheck(check::unchecked);
      pupdatecmdui->m_pcmdui->Enable(TRUE);
   }
   pupdatecmdui->m_bRet = true;
}

void MixerMainView::_001OnMixerWaveincontrols(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   if(_001GetSel() != 1)
   {
      _001SetSel(1);
   }
}

void MixerMainView::_001OnUpdateMixerWaveincontrols(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
   if(_001GetSel() == 1)
   {
      pupdatecmdui->m_pcmdui->_001SetCheck();
      pupdatecmdui->m_pcmdui->Enable(TRUE);
   }
   else
   {
      pupdatecmdui->m_pcmdui->_001SetCheck(check::unchecked);
      pupdatecmdui->m_pcmdui->Enable(TRUE);
   }   
   pupdatecmdui->m_bRet = true;
}

/*Mixer * MixerMainView::GetMixer()
{
   return get_document()->GetMixer();
}

MixerDestination * MixerMainView::GetDestination()
{
   return get_document()->GetDestination();
}

*/


BOOL MixerMainView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   UNREFERENCED_PARAMETER(pResult);
/*    LPNMHDR lpnmhdr = (LPNMHDR) lParam;
    TRACE("MixerMainView::OnNotify code = %d\n", lpnmhdr->code);
    if(lpnmhdr->code == TB_BOTTOM
      || lpnmhdr->code == TB_ENDTRACK
      || lpnmhdr->code == TB_LINEDOWN 
      || lpnmhdr->code == TB_LINEUP 
      || lpnmhdr->code == TB_PAGEDOWN 
      || lpnmhdr->code == TB_PAGEUP 
      || lpnmhdr->code == TB_THUMBPOSITION 
      || lpnmhdr->code == TB_THUMBTRACK 
      || lpnmhdr->code == TB_TOP 
      || lpnmhdr->code == BN_CLICKED)
    {
        TRACE("CMixerDialog::OnNotify TB_?\n");
        MixerControl * pControl;
        if(GetMixer()->m_pdevice->m_mapDlgItemIDToControl.Lookup(
            lpnmhdr->idFrom, pControl))
        {
            if(pControl->OnNotify(wParam, lpnmhdr))
                return TRUE;
        }
    }*/
// trans   return ::userbase::view::OnNotify(wParam, lParam, pResult);
   return FALSE;
}

void MixerMainView::_001OnTabClick(int iTab)
{
   _001SetSel(iTab);
}



void MixerMainView::on_create_view(view_data * pviewdata)
{
   MMRESULT mmrc;
   MixerControlView * pcontrol = NULL;
   pcontrol = dynamic_cast < MixerControlView * > (view::create_view(
      typeid(MixerControlView), 
      get_document(),
      this, 
      pviewdata->m_id
      ));
   if(pviewdata->m_id == ControlPlayback)
   {
      pcontrol->get_data()->Initialize();
      pcontrol->get_data()->SetNewDevice(0);
      mmrc = pcontrol->get_data()->SetNewDestination(MIXERLINE_COMPONENTTYPE_DST_SPEAKERS);
      if(mmrc != MMSYSERR_NOERROR)
      {
         mmrc = pcontrol->get_data()->SetNewDestination(MIXERLINE_COMPONENTTYPE_DST_HEADPHONES);
         if(mmrc != MMSYSERR_NOERROR)
         {
            System.simple_message_box(NULL, "Could not open default mixer destination!");
         }
      }
   }
   else if(pviewdata->m_id == ControlRecording)
   {
      pcontrol->get_data()->Initialize();
      pcontrol->get_data()->SetNewDevice(0);
      pcontrol->get_data()->SetNewDestination(MIXERLINE_COMPONENTTYPE_DST_WAVEIN);
   }
   pviewdata->m_pwnd = pcontrol;
   pviewdata->m_pdoc = get_document();
}

void MixerMainView::LayoutControl()
{
   if(m_pcontrol != NULL)
   {
      rect rectClient;

      rect rectTabClient;
      GetClientRect(rectClient);
      m_pcontrol->SetWindowPos(
         NULL,
         rectClient.left, rectClient.top, 
         rectClient.width(), rectClient.height(),
         SWP_SHOWWINDOW);
      m_pcontrol->layout();
   }
}
