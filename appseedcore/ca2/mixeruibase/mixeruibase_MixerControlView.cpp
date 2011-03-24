#include "StdAfx.h"

#include "MixerDoc.h"
#include "MixerControlView.h"
#include "MixerControlData.h"

#define IDC_MIXER_SLIDER 1000
//#define IDC_LIST 1001
#define IDC_BUTTON_RESERVE 1002
#define ID_VIEW_UPDATE 1003
#define IDI_ALBUM 1004
#define IDS_MIXER_DIALOG_TITLEFORMAT 1006

const int MixerControlView::cnListCount = 9;

MixerControlView::MixerControlView(::ca::application * papp) :
   ca(papp),
   ::userbase::view(papp),
   m_brushBackground(papp)
{

   m_pdata = new MixerControlData(this);

 
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

MixerControlView::~MixerControlView()
{
   if(m_pdata != NULL)
   {
      delete m_pdata;
      m_pdata = NULL;
   }
}

void MixerControlView::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::userbase::view::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &MixerControlView::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &MixerControlView::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &MixerControlView::_001OnCreate);
//   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &MixerControlView::_001OnTimer);
//   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &MixerControlView::_001OnContextMenu);
   IGUI_WIN_MSG_LINK(WM_VSCROLL, pinterface, this, &MixerControlView::_001OnVScroll);
   IGUI_WIN_MSG_LINK(WM_CTLCOLOR, pinterface, this, &MixerControlView::_001OnCtlColor);
   IGUI_WIN_MSG_LINK(WM_HSCROLL, pinterface, this, &MixerControlView::_001OnHScroll);

   connect_command(IDC_BUTTON_RESERVE, &MixerControlView::_001OnButtonReserve);
   connect_update_cmd_ui(ID_VIEW_UPDATE, &MixerControlView::_001OnUpdateViewUpdate);

//   IGUI_WIN_ON_NOTIFY(LVN_COLUMNCLICK  , IDC_LIST  , this, this, &MixerControlView::_001OnColumnclickList);
   //IGUI_WIN_ON_NOTIFY(LVN_GETDISPINFO  , IDC_LIST  , this, this, &MixerControlView::_001OnGetdispinfoList);
   //IGUI_WIN_ON_NOTIFY(NM_DBLCLK        , IDC_LIST  , this, this, &MixerControlView::_001OnDblclkList);
}


#ifdef _DEBUG
void MixerControlView::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void MixerControlView::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}

MixerDoc* MixerControlView::get_document() // non-debug version is inline
{
   ASSERT(base < MixerDoc >::bases(::view::get_document()));
   return dynamic_cast < MixerDoc * > (::view::get_document());
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MixerControlView message handlers

void MixerControlView::_001OnSize(gen::signal_object * pobj) 
{
   if(!m_bInitialized)
      return;
   pobj->previous();
//    ::user::interaction::RepositionBars(0, 0xffff, IDC_TAB);
    //CStatic * pStatic = (CStatic *) GetDlgItem(IDC_STATIC_CLIENT);
//   CTabCtrl * pTab   = (CTabCtrl *) GetDlgItem(IDC_TAB);
//   if(pTab)
//    if(pStatic)
//   {
//        m_wndStatusBar.SendMessage(WM_SIZE, SIZE_RESTORED, MAKELONG(cx, cy));
  //      rect statusRect;
    //    m_wndStatusBar.GetWindowRect(statusRect);
      //  ScreenToClient(statusRect);
//      if(IsWindow(pTab->m_hWnd))
//         pTab->MoveWindow(0, 0, cx, statusRect.top);
      rect clientRect;
//      pTab->GetClientRect(clientRect);
//        pTab->AdjustRect(false, clientRect);
//        pTab->ClientToScreen(clientRect);
//      ScreenToClient(clientRect);
        GetClientRect(clientRect);
//      m_layoutExplore.SetPlacement(clientRect);
//      m_layoutExplore.layout();
//      m_layoutSearch.SetPlacement(clientRect);
//      m_layoutSearch.layout();
   
}

void MixerControlView::OnInitialUpdate() 
{
    wait_cursor cwc(get_app());

   //CVMSApp *pApp = (CVMSApp *) &System;
//   db_server *pDataCentral = (db_server *) &System.db();


//   ::user::interaction* pWnd = GetParent();
   

    HINSTANCE hinstance = System.m_hInstance;

    HICON hIcon = (HICON) LoadImage(hinstance,
        MAKEINTRESOURCE(IDI_ALBUM),
        IMAGE_ICON,
        16, 16,
        0);

// dbbreak    SetIcon(hIcon, false);

    hIcon = (HICON) LoadImage(hinstance,
        MAKEINTRESOURCE(IDI_ALBUM),
        IMAGE_ICON,
        0, 0,
        LR_DEFAULTSIZE);

// dbbreak    SetIcon(hIcon, true);
   

   return ;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

void MixerControlView::_001OnGetdispinfoList(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::notify, pnotify, pobj)
//   LV_DISPINFO* pDispInfo = (LV_DISPINFO*) pnotify->get_lpnmhdr();
   // TODO: add your control notification handler code here
//   LV_ITEM* pItem= &(pDispInfo)->item;

//   int iItemIndx= pItem->iItem;
   

   pnotify->set_lresult(0);
}

void MixerControlView::_001OnDestroy(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
}

void MixerControlView::_001OnColumnclickList(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::notify, pnotify, pobj)
//   NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pnotify->get_lpnmhdr();
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



void MixerControlView::_001OnDblclkList(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::notify, pnotify, pobj)
   // TODO: add your control notification handler code here
//   LPNMLISTVIEW lpnmlv = (LPNMLISTVIEW) pnotify->get_lpnmhdr();
//   CListCtrl * pList = (CListCtrl *) GetDlgItem(lpnmlv->hdr.idFrom);
   pnotify->set_lresult(0);
}

void MixerControlView::_001OnButtonReserve(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   // TODO: add your control notification handler code here
}






void MixerControlView::pre_translate_message(gen::signal_object * pobj) 
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

/*BOOL MixerControlView::create(UINT nID) 
{
   // TODO: add your specialized code here and/or call the base class
   
   return create(MAKEINTRESOURCE(nID), NULL);
}*/

void MixerControlView::_001OnCreate(gen::signal_object * pobj) 
{
   wait_cursor cwc(get_app());
   if(pobj->previous())
      return;
/*    m_enhmetafile = GetEnhMetaFile(papp->m_strModuleFolder + "vmsp.emf");
    VERIFY(
        GetEnhMetaFileHeader(
            m_enhmetafile,
            sizeof(m_emh),
            &m_emh)
            );*/

      rect clientRect(0, 0, 0, 0);

    



//   SetImageLists();

   ::userbase::view::_001OnInitialUpdate(NULL);

   m_bInitialized = true;

}


BOOL MixerControlView::PreCreateWindow(CREATESTRUCT& cs) 
{
   cs.style = cs.style;
//   int i = WS_POPUP;
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
   cs.style |= WS_CLIPCHILDREN;
   return ::userbase::view::PreCreateWindow(cs);
}


/*void MixerControlView::SetImageLists()
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

void MixerControlView::_001OnUpdateViewUpdate(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
   pupdatecmdui->m_pcmdui->Enable();
   pupdatecmdui->m_bRet = true;
}







void MixerControlView::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(pHint);
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
          set_title();

         MixerDestination * pdestination = GetDestination();
         pdestination->GetAllControls();

         Mixer * pmixer = GetMixer();

         pmixer->m_pdevice->MapLines();
         pmixer->m_pdevice->MapControls();

         CreateControls();
         pmixer->m_pdevice->MapDlgCtrlIDToControls();
         pdestination->SendOnChangeAllControls();

         layout();

      }
      break;
    }
   
}

void MixerControlView::OnDraw(::ca::graphics * pgraphics) 
{
   UNREFERENCED_PARAMETER(pgraphics);
}

bool MixerControlView::CreateControls()
{
   delete_contents();

   CreateControls(GetDestination());

   MixerSourceArray & sourcea = GetDestination()->GetSources();

   for(int i = 0; i < sourcea.get_size(); i++)
   {
      CreateControls(sourcea.ptr_at(i));
   }

   return true;
}

bool MixerControlView::CreateControls(MixerSource *pSource)
{
   bool bHasControls = false;

   MixerControl * pcontrol;
   MixerControlArray & controla = pSource->m_mixercontrola;

   for(int iControl = 0; iControl < controla.get_size(); iControl++)
   {
      pcontrol = &controla[iControl];
      if(pcontrol->m_mixercontrol.dwControlType == MIXERCONTROL_CONTROLTYPE_VOLUME)
      {
         if(CreateVolumeControl(pcontrol))
            bHasControls = true;
      }
      else if((pcontrol->m_mixercontrol.dwControlType & MIXERCONTROL_CT_UNITS_MASK) == MIXERCONTROL_CT_UNITS_BOOLEAN)
      {
         if(CreateMuteControl(pcontrol))
            bHasControls = true;
      }
   }
   if(bHasControls)
   {
      rect rect(0, 0, 0, 0);
      simple_static * pst = new simple_static(get_app());
      pst->create(
         pSource->GetSZName(),
         WS_CHILD | WS_VISIBLE,
         rect,
         this);
      pst->ModifyStyleEx(0, WS_EX_TRANSPARENT, SWP_SHOWWINDOW);
      pst->SetFont(GetFont());
      m_staticsLines.set_at(pSource->GetLineID(), pst);
   }
   return true;
}

void MixerControlView::delete_contents()
{
    DWORD dwKey;
    simple_static * pst;
    POSITION pos = m_staticsLines.get_start_position();
    while(pos != NULL)
    {
        m_staticsLines.get_next_assoc(pos, dwKey, pst);
        delete pst;
    }
    m_staticsLines.remove_all();

}

bool MixerControlView::CreateVolumeControl(MixerControl *pControl)
{
    bool ok = pControl->CreateWindowsVolumeV001(this, m_uiNextSliderID, &m_uiNextSliderID);
    return ok;
}

bool MixerControlView::CreateMuteControl(MixerControl *pControl)
{
    bool ok = pControl->_001CreateMuteControl(
       this, 
       m_uiNextSliderID, 
       &m_uiNextSliderID);
    return ok;

}



void MixerControlView::layout()
{
    int iStartX = 0;
    int iEndX = 0;
    int iStartY = 0;
    int iEndY = 0;

    if(GetDestination() == NULL)
       return;

    LayoutLine(-1, GetDestination(), iStartX, iStartY, &iEndX, &iEndY);
    iStartX = iEndX;
    
    MixerSourceArray & sourcea = GetDestination()->GetSources();

    for(int i = 0; i < sourcea.get_size(); i++)
    {
        LayoutLine(i, sourcea.ptr_at(i), iStartX, iStartY, &iEndX, &iEndY);
        iStartX = iEndX;
    }
    //rect rect(0, 0, iEndX, iEndY);
    //::AdjustWindowRectEx(&rect, GetStyle(), FALSE,
   //      GetExStyle());
    //SetWindowPos(NULL, 0, 0, rect.width(), rect.height(), SWP_NOMOVE | SWP_NOACTIVATE);
    //rect rectClient;
    //GetClientRect(rectClient);

   _001RedrawWindow();

}

void MixerControlView::set_title()
{
    string strFormat;
//    strFormat.load_string(IDS_MIXER_DIALOG_TITLEFORMAT);
    
    string strAppTitle;
    //strAppTitle.load_string(AFX_IDS_APP_TITLE);

    string strTitle;
    ASSERT(GetDestination() != NULL);
    strTitle.Format(
        strFormat,
        strAppTitle,
        GetMixer()->m_pdevice->GetSZPName(),
        GetDestination()->GetSZName());

    SetWindowText(strTitle);

}

void MixerControlView::LayoutLine(int iSource, MixerSource *pSource, int iStartX, int iStartY, int *piEndX, int *piEndY)
{
   MixerControlArray & controla = pSource->m_mixercontrola;
   MixerControl * pcontrol;
   mixer::control * pWnd;
   bool bHasAtLeastOneControl = false;
   int y = iStartY;
   int y2;
   y += 2;
   simple_static * pst;
   if(m_staticsLines.Lookup(pSource->GetLineID(), pst))
   {
      pst->SetWindowPos(
         NULL,
         iStartX, y,
         70, 30,
         SWP_SHOWWINDOW);
   }
   y += 30;
   for(int iControl = 0; iControl < controla.get_size(); iControl++)
   {
      pcontrol = &controla[iControl];
      if(pcontrol->m_mixercontrol.dwControlType == MIXERCONTROL_CONTROLTYPE_VOLUME)
      {
         if(pcontrol->get_size() >= 2)
         {
            pWnd = pcontrol->GetControl(MixerCtrlData::TypeStereoBalanceLabel);
            y2 = y;
            if(pWnd != NULL)
            {
               bHasAtLeastOneControl = true;
               pWnd->GetWnd()->SetWindowPos(
                  NULL,
                  iStartX, y2,
                  80, 15,
                  SWP_SHOWWINDOW);
               y2 += 15;
               pWnd = pcontrol->GetControl(MixerCtrlData::TypeStereoBalance);
               if(pWnd != NULL)
               {
                  pWnd->GetWnd()->SetWindowPos(
                     NULL,
                     iStartX, y,
                     70, 30,
                     SWP_SHOWWINDOW);
               }
            }
            y += 45;
            y2 = y;
            pWnd = pcontrol->GetControl(MixerCtrlData::TypeStereoVolumeLabel);
            if(pWnd != NULL)
            {
               bHasAtLeastOneControl = true;
               pWnd->GetWnd()->SetWindowPos(
                  NULL,
                  iStartX, y2,
                  80, 15,
                  SWP_SHOWWINDOW);
               y2 += 15;
               pWnd = pcontrol->GetControl(MixerCtrlData::TypeStereoVolume);
               if(pWnd != NULL)
               {
                  bHasAtLeastOneControl = true;
                  pWnd->GetWnd()->SetWindowPos(
                     NULL,
                     iStartX, y,
                     50, 120,
                     SWP_SHOWWINDOW);
               }
            }
            y += 135;
         }
         
      }
   }
   for(int iControl = 0; iControl < controla.get_size(); iControl++)
   {
      pcontrol = &controla[iControl];
      if(pcontrol->m_mixercontrol.dwControlType == MIXERCONTROL_CONTROLTYPE_MUX)
      {
         m_controlptraMux.add_unique(pcontrol);
      }
      if((pcontrol->m_mixercontrol.dwControlType & MIXERCONTROL_CT_UNITS_MASK) == MIXERCONTROL_CT_UNITS_BOOLEAN)
      {
         int iSize = pcontrol->get_size();
         for(int i = 0; i < iSize; i++)
         {
            pWnd = pcontrol->GetControlByIndex(i);
            bHasAtLeastOneControl = true;
            pWnd->GetWnd()->SetWindowPos(
               NULL,
               iStartX, y,
               80, 30,
               SWP_SHOWWINDOW);
            y += 30;
         }
      }
   }
   if(iSource >= 0)
   {
      for(int iControl = 0; iControl < m_controlptraMux.get_size(); iControl++)
      {
         pcontrol = m_controlptraMux[iControl];
         if((pcontrol->m_mixercontrol.dwControlType & MIXERCONTROL_CT_UNITS_MASK) == MIXERCONTROL_CT_UNITS_BOOLEAN)
         {
            pWnd = pcontrol->GetControlByIndex(iSource);
            bHasAtLeastOneControl = true;
            pWnd->GetWnd()->SetWindowPos(
               NULL,
               iStartX, y,
               80, 30,
               SWP_SHOWWINDOW);
            y += 30;
         }
      }
   }
   if( bHasAtLeastOneControl)
   {
      *piEndX = iStartX + 80;
      *piEndY = 300;
   }
}

void MixerControlView::_001OnDraw(::ca::graphics * pdc)
{
   rect rectMeta;
   rect rectClient;
   GetClientRect(rectClient);

   if(System.savings().is_trying_to_save(gen::resource_processing))
   {
      pdc->FillSolidRect(rectClient, RGB(255,255,255));
   }
   else
   {
      System.imaging().color_blend(pdc, rectClient, RGB(255,255,255), 127);
   }


   rect rect;

   rect = rectClient;
   rect.ScaleHeightAspect(64, rectClient.right, rectClient.bottom);

   if(m_enhmetafile != NULL)
   {
      rectMeta.left = 0;
      rectMeta.top = 0;
      rectMeta.right = m_emh.rclBounds.right - m_emh.rclBounds.left;
      rectMeta.bottom = m_emh.rclBounds.bottom - m_emh.rclBounds.top;
      //rectMeta.FitOnCenter(rectClient);
      rectMeta.FitOnCenterOf(rect);
      rectMeta.Align(gen::AlignBottom | gen::AlignRight, rectClient);


      pdc->FillSolidRect(rectMeta, RGB(255, 255, 255));
      pdc->PlayMetaFile(m_enhmetafile, rectMeta);
   }
}

void MixerControlView::_001OnVScroll(gen::signal_object * pobj) 
{
   IGUI_WIN_CST(scroll);
   ::user::interaction* pWnd = pscroll->m_pScrollBar;
   MixerControl * pControl;
   if(GetMixer()->m_pdevice->m_mapDlgItemIDToControl.Lookup(pWnd->GetDlgCtrlId(), pControl))
   {
      pControl->OnVHScroll(pscroll->m_nSBCode, (uint) pscroll->m_nPos, pscroll->m_pScrollBar);
   }
}

void MixerControlView::_001OnCtlColor(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::ctl_color, pctlcolor, pobj)
   throw not_implemented_exception();
//   HBRUSH hbr = ::userbase::view::OnCtlColor(pgraphics, pWnd, nCtlColor);
   /*HBRUSH hbr;
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

void MixerControlView::_001OnHScroll(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   //SCAST_PTR(::user::win::message::scroll, pscroll, pobj)
}

/*void MixerControlView::OnMixerSpeakerscontrols() 
{
   MixerDoc * pdoc = get_document();
    if(GetDestination() == NULL ||
        GetDestination()->GetComponentType() != MIXERLINE_COMPONENTTYPE_DST_SPEAKERS)
    {

        SetNewDestination(MIXERLINE_COMPONENTTYPE_DST_SPEAKERS);
    }

   
}

void MixerControlView::OnUpdateMixerSpeakerscontrols(cmd_ui * pcmdui) 
{
   if(GetMixer()->m_pdevice->m_hMixer != NULL && 
        GetDestination() != NULL &&
        GetDestination()->GetComponentType() == MIXERLINE_COMPONENTTYPE_DST_SPEAKERS)
    {
        pcmdui->SetCheck();
        pcmdui->Enable(TRUE);
    }
    else
    {
        pcmdui->SetCheck(0);
        pcmdui->Enable(TRUE);
    }   
}

void MixerControlView::OnMixerWaveincontrols() 
{
   MixerDoc * pdoc = get_document();
   MixerDestination * pdestination = pdoc->GetDestination();
   if(pdestination == NULL ||
        pdestination->GetComponentType() != MIXERLINE_COMPONENTTYPE_DST_WAVEIN)
    {
        pdoc->SetNewDestination(MIXERLINE_COMPONENTTYPE_DST_WAVEIN);
    }
   
}

void MixerControlView::OnUpdateMixerWaveincontrols(cmd_ui * pcmdui) 
{
   MixerDoc * pdoc = get_document();
   Mixer * pmixer = pdoc->GetMixer();
   MixerDestination * pdestination = pdoc->GetDestination();
    if(pmixer->m_pdevice->m_hMixer != NULL &&
        pdestination != NULL &&
        pdestination->GetComponentType() == MIXERLINE_COMPONENTTYPE_DST_WAVEIN)
    {
        pcmdui->SetCheck();
        pcmdui->Enable(TRUE);
    }
    else
    {
        pcmdui->SetCheck(0);
        pcmdui->Enable(TRUE);
    }
   
}*/

Mixer * MixerControlView::GetMixer()
{
   return get_data()->GetMixer();
}

MixerDestination * MixerControlView::GetDestination()
{
   return get_data()->GetDestination();
}

BOOL MixerControlView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   UNREFERENCED_PARAMETER(pResult);
/*    LPNMHDR lpnmhdr = (LPNMHDR) lParam;
    TRACE("MixerControlView::OnNotify code = %d\n", lpnmhdr->code);
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

BOOL MixerControlView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
   if(GetMixer()->OnCommand(wParam, lParam))
      return TRUE;
   
// trans   return ::userbase::view::OnCommand(wParam, lParam);
   return FALSE;
}

MixerControlData * MixerControlView::get_data()
{
   return m_pdata;
}

void MixerControlView::_OnUpdate(::userbase::view * pview, LPARAM lhint, ::radix::object * phint)
{
   on_update(pview, lhint, phint);
}
