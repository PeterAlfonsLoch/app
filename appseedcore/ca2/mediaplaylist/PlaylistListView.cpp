#include "StdAfx.h"
#include "PlaylistListView.h"

PlaylistListView::PlaylistListView(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp), 
   ::user::form(papp),
   ::user::scroll_view(papp),
   ::user::list(papp),
   ::user::form_list(papp),
   simple_form_list_view(papp),
   m_gdibuffer(papp)
{
   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateCompatibleDC(NULL);


/*   m_imagelistSubItemHover.add(
      (HICON) ::LoadImage(
         System.m_hInstance,
         MAKEINTRESOURCE(IDI_EXECUTE_PLAY),
         IMAGE_ICON,
         16,
         16,
         LR_SHARED));*/

/*  System.imaging().Createcolor_blend_ImageList(
      &m_imagelistNormal,
      &m_imagelistHover,
      RGB(255, 255, 240),
      64);*/



   SetCacheInterface(&m_cache);
   m_gdibuffer.InstallMessageHandling(this);
    m_enhmetafile = NULL;
   ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
   m_emode = ModeNormal;
   ::ca::type_info typeinfo = &typeid(PlaylistListView);
   m_dataid = typeinfo.raw_name();

}

PlaylistListView::~PlaylistListView()
{
}

void PlaylistListView::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   simple_form_list_view::_001InstallMessageHandling(pinterface);

   InstallBuffering(pinterface);
   IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &PlaylistListView::_001OnLButtonDblClk);
   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &PlaylistListView::_001OnContextMenu);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &PlaylistListView::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &PlaylistListView::_001OnCreate);
   
   connect_command("edit_delete", &PlaylistListView::_001OnEditRemove);
   connect_update_cmd_ui("edit_delete", &PlaylistListView::_001OnUpdateEditRemove);
   connect_command("execute_play" , &PlaylistListView::_001OnPlaylistExecutePlay);
   connect_update_cmd_ui("execute_play" , &PlaylistListView::_001OnUpdatePlaylistExecutePlay);
}



#ifdef _DEBUG
void PlaylistListView::assert_valid() const
{
   simple_form_list_view::assert_valid();
}

void PlaylistListView::dump(dump_context & dumpcontext) const
{
   simple_form_list_view::dump(dumpcontext);
}

PlaylistDoc* PlaylistListView::get_document() const// non-debug version is inline
{
   if(::view::get_document() == NULL)
      return NULL;
   ASSERT(base < PlaylistDoc >::bases(::view::get_document()));
   return dynamic_cast < PlaylistDoc * > (::view::get_document());
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// PlaylistListView message handlers

BOOL PlaylistListView::PreCreateWindow(CREATESTRUCT& cs) 
{
//   cs.style |= LVS_REPORT;
//   cs.style |= LVS_OWNERDRAWFIXED;   
//   cs.style |= LVS_OWNERDATA;   
   
   return simple_form_list_view::PreCreateWindow(cs);
}


bool PlaylistListView::_001GetItemText(string &str, INT_PTR iItem, INT_PTR iSubItem, INT_PTR iListItem)
{
   if(simple_form_list_view::_001GetItemText(
      str,
      iItem, 
      iSubItem, 
      iListItem))
   {
      return true;
   }
   
   ASSERT_VALID(this);
   PlaylistDoc * pdoc = get_document();
   string wstrSongPath;
   
   if(pdoc->get_song_at(wstrSongPath, iItem))
   {
      if(iSubItem == 0)
      {
         str.Format("?????");
      }
      else if(iSubItem == 1)
      {
         str.Format("?????");      
      }
      else if(iSubItem == 2)
      {
         int iFind1 = wstrSongPath.reverse_find('\\');
         int iFind2 = wstrSongPath.reverse_find('/');
         int iFind = 0;
         if(iFind1 >= 0)
         {
            if(iFind2 >= 0)
            {
               if(iFind1 >= iFind2)
               {
                  iFind = iFind1 + 1;
               }
               else
               {
                  iFind = iFind2 + 1;
               }
            }
            else
            {
               iFind = iFind1 + 1;
            }
         }
         else
         {
            if(iFind2 >= 0)
            {
               iFind = iFind2 + 1;
            }
         }

         str = wstrSongPath.Mid(iFind);

      }
      else if(iSubItem == 3)
      {
         str = wstrSongPath;
      }
   }
/*    else
    {
      if(iSubItem == 0)
      {
           str.Format(L"?????");
      }
      else if(iSubItem == 1)
      {
           str.Format(L"?????");
      }
      else if(iSubItem == 2)
      {
            str = wstrSongPath;
        }
    }*/
   return true;
/*    if(pDataCentral->IsWorking()
      &&   pdoc->GetSongPath(wstrSongPath, iItem)
      &&   pSongsSet->FindPath(wstrSongPath))
    {
      if(iSubItem == 0)
      {
         pSongsSet->GetData(1);
         str.Format(L"%d", pSongsSet->m_iCode);
      }
      else if(iSubItem == 1)
      {
         pSongsSet->GetData(1);
         str.Format(L"%d", pSongsSet->m_iCode);
      }
      else if(iSubItem == 2)
      {
           pSongsSet->GetData(2);
           str = pSongsSet->m_bstrName;
       }
   }
    else
    {
      if(iSubItem == 0)
      {
           str.Format("?????");
      }
      else if(iSubItem == 1)
      {
           str.Format("?????");
      }
      else if(iSubItem == 2)
      {
            str = wstrSongPath;
        }
    }*/
   return true;
}

void PlaylistListView::SetMode(EMode emode)
{
    m_emode = emode;
//   CListCtrl & list = GetListCtrl();
//   while(list.DeleteColumn(0));
   _001UpdateColumns();
   RedrawWindow();

}


void PlaylistListView::_001InsertColumns()
{
   //db_server * pDataCentral = (db_server *) &System.db();

   class ::user::control::descriptor control;

   control.m_bTransparent = true;
   control.set_type(::user::control::type_button);
   control.m_typeinfo = &typeid(BaseButtonControl);
   control.m_id = 123; // Play button
   control.add_function(::user::control::function_action);
   int iControl = _001AddControl(control);

    Column column;

   column.m_iWidth               = 18;
   column.m_iSubItem             = 1;
   //column.m_bIcon                = true;
   //column.m_sizeIcon.cx          = 16;
   //column.m_sizeIcon.cy          = 16;
   column.m_iControl             = iControl;
   column.m_bCustomDraw          = true;
   column.m_bEditOnSecondClick   = true;
   _001AddColumn(column);




   EMode emode = m_emode;

    if(emode == ModeMinimum)
    {
      column.m_iWidth = 300;
//      column.m_uiText = IDS_PLAYLIST_CODE;
      column.m_iSubItem = 0;
//      column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
      column.m_iSmallImageWidth = 16;
      column.m_crSmallMask = RGB(255, 0, 255);
      _001AddColumn(column);
    }
    else if(emode == ModeNormal)
    {
      column.m_iWidth = 170;
      //column.m_uiText = IDS_PLAYLIST_HEADER_FILENAME;
      column.m_iSubItem = 2;
//      column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
      column.m_iSmallImageWidth = 16;
      column.m_crSmallMask = RGB(255, 0, 255);
      _001AddColumn(column);

      //column.m_uiText = IDS_PLAYLIST_HEADER_FILEPATH;
      column.m_iWidth = 400;
      column.m_iSubItem = 3;
      _001AddColumn(column);

    }



}

void PlaylistListView::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
{
   UNREFERENCED_PARAMETER(pSender);
   if(lHint == 247)
   {  
      _001UpdateColumns();
   }
   PlaylistDoc * pdoc = get_document();
   ::ca::type_info typeinfo = &typeid(PlaylistListView);
   string str;
   str = typeinfo.raw_name();
   str += ".";
   str += get_document()->get_path_name();
   m_dataid = str;
   
   if(lHint == PlaylistDoc::LHINT_FRAMEDOWN)
   {
      if(GetMode() == ModeNormal)
         SetMode(ModeMinimum);
      else
         SetMode(ModeNormal);
   }
   else if(lHint == PlaylistDoc::LHINT_FRAMEUP)
   {
      if(GetMode() == ModeMinimum)
         SetMode(ModeNormal);
      else
         SetMode(ModeMinimum);
   }

   ASSERT_VALID(this);
   PlaylistViewUpdateHint * ppluh = (PlaylistViewUpdateHint *) pHint;
   PlaylistViewUpdateHint * puh = (PlaylistViewUpdateHint *) pHint;
   bool bAllUpdates = pHint == NULL
      ||
      (ppluh != NULL
      && ppluh->GetHint() == PlaylistViewUpdateHint::HintFull);
    if(bAllUpdates ||
      ppluh != NULL)
    {
      if(bAllUpdates ||
         ppluh->GetHint() == PlaylistViewUpdateHint::HintFull)
       {
         _001OnUpdateItemCount();
         Redraw();
        }

      if(bAllUpdates ||
           ppluh->GetHint() == PlaylistViewUpdateHint::HintCurrentSong)
      {
         Range range;
         ItemRange itemrange;
         itemrange.Set(pdoc->GetCurrentSong(),
            pdoc->GetCurrentSong(),
            0,
            m_columna.get_count(),
            -1, -1);
         range.add_item(itemrange);
         _001SetHighlightRange(range);
          Redraw();
      }
    }
   if(ppluh != NULL)
   {
      if(ppluh->GetHint() ==
         PlaylistViewUpdateHint::HintGetAttachableView)
      {
         ppluh->AddAttachableView(this);
      }
   }
   if(puh != NULL)
   {
      switch(puh->GetHint())
      {
      case PlaylistViewUpdateHint::HintPop:
         {
            simple_frame_window * pframewnd = dynamic_cast < simple_frame_window * > (::user::list::GetParentFrame());
            OnActivateFrame(WA_INACTIVE, pframewnd);
            pframewnd->ActivateFrame(SW_SHOW);
            OnActivateView(TRUE, this, this);
            RedrawWindow();
         }
         break;
      case PlaylistViewUpdateHint::HintInitial:
         {
            _001UpdateColumns();
            _001OnUpdateItemCount();
            _001OnInitialUpdate(NULL);
         }
         break;
      }
   }
   m_cache._001Invalidate();
   _001OnUpdateItemCount();
   
   
}

void PlaylistListView::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   simple_form_list_view::_001OnInitialUpdate(NULL);

   //_001UpdateColumns();

   RedrawWindow();

   TRACE("PlaylistListView::OnInitialUpdate() HWND = %d\n", _get_handle());
   
/*   CTransparentFrameWndV4 * pframe = dynamic_cast < CTransparentFrameWndV4 * > (GetParentFrame());
   if(pframe != NULL)
   {
      pframe->GetWndFramework()->SetDownUpInterface(this);
      pframe->SetDownUpInterface(this);
   }*/
}

bool PlaylistListView::WndFrameworkDownUpGetUpEnable()
{
   return GetParentFrame()->GetParent() != NULL
      || GetMode() == ModeMinimum;
}
bool PlaylistListView::WndFrameworkDownUpGetDownEnable()
{
   return GetParentFrame()->GetParent() == NULL
      || GetMode() == ModeNormal;
}

bool PlaylistListView::TransparentFrameWndDownUpGetUpEnable()
{
   return GetParentFrame()->GetParent() != NULL &&
      GetMode() == ModeNormal;
}
bool PlaylistListView::TransparentFrameWndDownUpGetDownEnable()
{
   return GetParentFrame()->GetParent() == NULL &&
      GetMode() == ModeMinimum;
}

PlaylistListView::EMode PlaylistListView::GetMode()
{
   return m_emode;
}

void PlaylistListView::_001OnLButtonDblClk(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   index iItem;
   if(_001HitTest_(pmouse->m_pt, iItem))
   {
      playlist_info info;
      
      info.m_iCurrentSong = iItem;
      info.m_ehint = mediaplaylist::SetCurrentSongHintDoPlay;
      info.m_bMakeVisible = true;

      get_document()->play(&info);
   }
}




index PlaylistListView::_001GetItemImage(index iItem, index iSubItem, index iListItem)
{
   UNREFERENCED_PARAMETER(iItem);
   UNREFERENCED_PARAMETER(iListItem);
   if(iSubItem == 0
      || iSubItem == 1)
   {
      return 0;
   }
   else
      return -1;
}

void PlaylistListView::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();
   index iItem;
   class point ptClient = point;
   ScreenToClient(&ptClient);
     if(_001HitTest_(ptClient, iItem))
   {
//     SimpleMenu menu(BaseMenuCentral::GetMenuCentral(get_app()));
/*      if (menu.LoadMenu(IDR_POPUP_PLAYLIST_ITEM))
      {
         SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
         ASSERT(pPopup != NULL);
         frame_window * pframe = GetParentFrame();
         pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            (::ca::window *) pframe);
      }*/
   }
   else
   {
//     ::userbase::menu menu;
/*      if (menu.LoadMenu(IDR_POPUP_PLAYLIST))
      {
         ::userbase::menu* pPopup = menu.GetSubMenu(0);
         ASSERT(pPopup != NULL);
         frame_window * pframe = GetParentFrame();
         pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            (::ca::window *) pframe);
      }*/
   }
}

void PlaylistListView::_001OnSize(gen::signal_object * pobj) 
{
   pobj->previous();
   
   UpdateDrawingObjects();
}

void PlaylistListView::UpdateDrawingObjects()
{
   ca77::application * papp = dynamic_cast < ca77::application * > (get_app());
   ASSERT(papp != NULL);
//   gen::savings & savings = System.savings();
/*   m_enhmetafile = papp->LoadEnhMetaFile(IDR_MUSICALPLAYER);*/
   if(m_enhmetafile != NULL)
   {
        GetEnhMetaFileHeader(
            m_enhmetafile,
            sizeof(m_emh),
            &m_emh);
   }

}

void PlaylistListView::_001OnDraw(::ca::graphics *pdc)
{
   simple_form_list_view::_001OnDraw(pdc);
}

void PlaylistListView::_001OnEditRemove(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   _001RemoveSelection();
}

void PlaylistListView::_001OnUpdateEditRemove(gen::signal_object * pobj) 
{
   SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)

   Range range;

   _001GetSelection(range);

   pupdatecmdui->m_pcmdui->Enable(range.get_item_count() > 0);
   pupdatecmdui->m_bRet = true;
}

bool PlaylistListView::_001OnRemoveItem(index iItem)
{
   PlaylistDoc * pdoc = get_document();
   return pdoc->RemoveSong(iItem);
}

PaneView * PlaylistListView::GetParentPane()
{
   //::user::interaction * pwnd = GetParent();
/*   if(base < PaneView >::bases(pwnd))
   {
      return dynamic_cast < PaneView * > (pwnd);
   }*/
   return NULL;
}

void PlaylistListView::_001DrawBackground(::ca::graphics *pdc, LPRECT lprect)
{
   rect rectThis;
   GetClientRect(rectThis);

   ::user::list::_001DrawBackground(pdc, lprect);
   
/*   if(m_enhmetafile != NULL)
   {
      rect rectUpdate;
      pdc->GetClipBox(rectUpdate);
      CBaseRect rectMeta;

      rectMeta.left = 0;
      rectMeta.top = 0;
      rectMeta.right = m_emh.rclBounds.right - m_emh.rclBounds.left;
      rectMeta.bottom = m_emh.rclBounds.bottom - m_emh.rclBounds.top;
      rectMeta.FitOnCenterOf(rectThis);

      m_gdibuffer.GetBuffer()->PlayMetaFile(m_enhmetafile, rectMeta);

      class imaging & imaging = System.imaging();
      imaging.bitmap_blend(
         pdc,
         rectUpdate.left,
         rectUpdate.top,
         rectUpdate.width(),
         rectUpdate.height(),
         m_gdibuffer.GetBuffer(),
         rectUpdate.left,
         rectUpdate.top,
         96);
   }*/

}

void PlaylistListView::_001OnPlaylistExecutePlay(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   Range range;
   _001GetSelection(range);
   if(range.get_item_count() > 0)
   {
      int iItem = range.ItemAt(0).GetLBound();

      playlist_info info;

      info.m_iCurrentSong  = iItem;
      info.m_ehint         = mediaplaylist::SetCurrentSongHintDoPlay;
      info.m_bMakeVisible  = true;

      get_document()->play(&info);

   }

   
}

void PlaylistListView::_001OnUpdatePlaylistExecutePlay(gen::signal_object * pobj) 
{
   SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)
   Range range;
   _001GetSelection(range);
   pupdatecmdui->m_pcmdui->Enable(range.get_item_count() > 0);
   pupdatecmdui->m_bRet = true;
}


void PlaylistListView::_001OnInitializeForm(::user::control * pcontrol)
{
   simple_form_list_view::_001OnInitializeForm(pcontrol);
   switch(pcontrol->descriptor().m_id)
   {
   case 123: // PlayButton
      {
         BaseButtonControl * pbutton = dynamic_cast < BaseButtonControl * > (pcontrol);
         pbutton->m_pimagelistNormal = m_pimagelistNormal;
         pbutton->m_iImageNormal = 0;
         pbutton->m_pimagelistItemHover = m_pimagelistItemHover;
         pbutton->m_iImageItemHover = 0;
         pbutton->m_pimagelistSubItemHover = m_pimagelistSubItemHover;
         pbutton->m_iImageSubItemHover = 0;
      }
   }

}

void PlaylistListView::_001OnButtonAction(
   ::user::control * pcontrol)
{
   if(pcontrol->descriptor().m_id == 123) // Play button
   {
      
      playlist_info info;

      info.m_iCurrentSong     = pcontrol->GetEditItem();
      info.m_ehint            = mediaplaylist::SetCurrentSongHintDoPlay,
      info.m_bMakeVisible     = true;
      info.m_bUser            = true;

      get_document()->play(&info);

   }
}

count PlaylistListView::_001GetItemCount()
{
   if(get_document() != NULL)
      return get_document()->GetSongCount();
   else
      return -1;
}


void PlaylistListView::_001OnCreate(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   m_pimagelistSubItemHover   = new image_list(get_app());
   m_pimagelistNormal         = new image_list(get_app());
   m_pimagelistItemHover      = new image_list(get_app());

   m_pimagelistSubItemHover->create(16, 16, 0,  10, 10);
   m_pimagelistSubItemHover->add_matter("execute_play_16.png");

   
   ::ca::graphics_sp spgraphics(get_app());
   spgraphics->CreateCompatibleDC(NULL);

   System.imaging().CreateHueImageList(
      spgraphics,
      m_pimagelistNormal,
      m_pimagelistSubItemHover,
      RGB(220, 220, 215),
      0.50);

   System.imaging().Createcolor_blend_ImageList(
      m_pimagelistItemHover,
      m_pimagelistSubItemHover,
      RGB(220, 220, 215),
      127);
}