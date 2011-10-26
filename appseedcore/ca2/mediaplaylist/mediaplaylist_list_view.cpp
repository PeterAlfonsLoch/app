#include "StdAfx.h"


namespace mediaplaylist
{


   list_view::list_view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::user::form(papp),
      ::user::scroll_view(papp),
      ::user::list(papp),
      ::user::form_list(papp),
      simple_form_list_view(papp)
   {
      ::ca::graphics_sp spgraphics(get_app());
      spgraphics->CreateCompatibleDC(NULL);

      m_iGroupMinHeight = 96;
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

      SetCacheInterface(&m_listcache);

       m_enhmetafile = NULL;
      ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
      m_emode = mode_normal;
      ::ca::type_info typeinfo = ::ca::get_type_info < list_view > ();
      m_dataid = typeinfo.raw_name();
      m_bGroup = true;
      m_bLateralGroup = true;


   }

   list_view::~list_view()
   {
   }

   void list_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      simple_form_list_view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &list_view::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &list_view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &list_view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &list_view::_001OnCreate);

      connect_command("edit_delete", &list_view::_001OnEditRemove);
      connect_update_cmd_ui("edit_delete", &list_view::_001OnUpdateEditRemove);
      connect_command("execute_play" , &list_view::_001OnPlaylistExecutePlay);
      connect_update_cmd_ui("execute_play" , &list_view::_001OnUpdatePlaylistExecutePlay);
   }



   #ifdef _DEBUG
   void list_view::assert_valid() const
   {
      simple_form_list_view::assert_valid();
   }

   void list_view::dump(dump_context & dumpcontext) const
   {
      simple_form_list_view::dump(dumpcontext);
   }

   ::mediaplaylist::document* list_view::get_document() const// non-debug version is inline
   {
      if(::view::get_document() == NULL)
         return NULL;
      ASSERT(base < ::mediaplaylist::document >::bases(::view::get_document()));
      return dynamic_cast < ::mediaplaylist::document * > (::view::get_document());
   }

   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // list_view message handlers

   BOOL list_view::PreCreateWindow(CREATESTRUCT& cs)
   {
   //   cs.style |= LVS_REPORT;
   //   cs.style |= LVS_OWNERDRAWFIXED;
   //   cs.style |= LVS_OWNERDATA;

      return simple_form_list_view::PreCreateWindow(cs);
   }



   void list_view::SetMode(e_mode emode)
   {
       m_emode = emode;
   //   CListCtrl & list = GetListCtrl();
   //   while(list.DeleteColumn(0));
      _001UpdateColumns();
      RedrawWindow();

   }


   void list_view::_001InsertColumns()
   {

      class ::user::control::descriptor control;

      control.m_bTransparent              = true;
      control.m_typeinfo                  = ::ca::get_type_info < BaseButtonControl > ();
      control.m_id                        = "play_button";
      control.add_function(::user::control::function_action);
      control.set_type(::user::control::type_button);

       ::user::list_column column;

      column.m_iWidth                     = 18;
      column.m_iSubItem                   = 1;
      column.m_iControl                   = _001AddControl(control);
      column.m_bCustomDraw                = true;
      _001AddColumn(column);




      e_mode emode = m_emode;

       if(emode == mode_minimum)
       {
         column.m_iWidth            = 300;
         column.m_uiText            = "<string id='mediaplaylist:list_view:file_name'>file name</string>";
         column.m_iSubItem          = 2;
         column.m_iSmallImageWidth  = 16;
         column.m_crSmallMask       = RGB(255, 0, 255);
         _001AddColumn(column);
       }
       else if(emode == mode_normal)
       {
         column.m_iWidth            = 170;
         column.m_uiText            = "<string id='mediaplaylist:list_view:file_name'>file name</string>";
         column.m_iSubItem          = 2;
         column.m_iSmallImageWidth  = 16;
         column.m_crSmallMask       = RGB(255, 0, 255);
         _001AddColumn(column);

         column.m_iWidth            = 400;
         column.m_uiText            = "<string id='mediaplaylist:list_view:file_path'>file path</string>";
         column.m_iSubItem          = 3;
         _001AddColumn(column);

       }



   }

   void list_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint)
   {
      UNREFERENCED_PARAMETER(pSender);
      if(lHint == 247)
      {
         _001UpdateColumns();
      }
      ::mediaplaylist::document * pdoc = get_document();
      ::ca::type_info typeinfo = ::ca::get_type_info < list_view > ();
      string str;
      str = typeinfo.raw_name();
      str += ".";
      str += get_document()->get_path_name();
      m_dataid = str;

      if(lHint == ::mediaplaylist::document::LHINT_FRAMEDOWN)
      {
         if(GetMode() == mode_normal)
            SetMode(mode_minimum);
         else
            SetMode(mode_normal);
      }
      else if(lHint == ::mediaplaylist::document::LHINT_FRAMEUP)
      {
         if(GetMode() == mode_minimum)
            SetMode(mode_normal);
         else
            SetMode(mode_minimum);
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
            itemrange.Set(pdoc->get_current_song(),
               pdoc->get_current_song(),
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
      m_listcache._001Invalidate();
      _001OnUpdateItemCount();


   }

   void list_view::_001OnInitialUpdate(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      simple_form_list_view::_001OnInitialUpdate(NULL);

      //_001UpdateColumns();

      RedrawWindow();

      TRACE("list_view::OnInitialUpdate() HWND = %d\n", _get_handle());

   /*   CTransparentFrameWndV4 * pframe = dynamic_cast < CTransparentFrameWndV4 * > (GetParentFrame());
      if(pframe != NULL)
      {
         pframe->GetWndFramework()->SetDownUpInterface(this);
         pframe->SetDownUpInterface(this);
      }*/
   }

   bool list_view::WndFrameworkDownUpGetUpEnable()
   {
      return GetParentFrame()->GetParent() != NULL
         || GetMode() == mode_minimum;
   }
   bool list_view::WndFrameworkDownUpGetDownEnable()
   {
      return GetParentFrame()->GetParent() == NULL
         || GetMode() == mode_normal;
   }

   bool list_view::TransparentFrameWndDownUpGetUpEnable()
   {
      return GetParentFrame()->GetParent() != NULL &&
         GetMode() == mode_normal;
   }
   bool list_view::TransparentFrameWndDownUpGetDownEnable()
   {
      return GetParentFrame()->GetParent() == NULL &&
         GetMode() == mode_minimum;
   }

   list_view::e_mode list_view::GetMode()
   {
      return m_emode;
   }

   void list_view::_001OnLButtonDblClk(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      index iItem;
      if(_001HitTest_(pmouse->m_pt, iItem))
      {
         info info;

         info.m_iCurrentSong = iItem;
         info.m_ehint = mediaplaylist::hint_do_play;
         info.m_bMakeVisible = true;

         get_document()->play(&info);
      }
   }




   void list_view::_001GetItemImage(::user::list_item * pitem)
   {
      if(pitem->m_iSubItem == 0 || pitem->m_iSubItem == 1)
      {
         pitem->m_iImage = 0;
         pitem->m_bOk = true;
      }
      else
      {
         pitem->m_iImage = -1;
         pitem->m_bOk = false;
      }
   }

   void list_view::_001OnContextMenu(gen::signal_object * pobj)
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

   void list_view::_001OnSize(gen::signal_object * pobj)
   {
      pobj->previous();

      UpdateDrawingObjects();
   }

   void list_view::UpdateDrawingObjects()
   {
      cube1::application * papp = dynamic_cast < cube1::application * > (get_app());
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

   void list_view::_001OnDraw(::ca::graphics *pdc)
   {
      simple_form_list_view::_001OnDraw(pdc);
   }

   void list_view::_001OnEditRemove(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      _001RemoveSelection();
   }

   void list_view::_001OnUpdateEditRemove(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)

      Range range;

      _001GetSelection(range);

      pupdatecmdui->m_pcmdui->Enable(range.get_item_count() > 0);
      pupdatecmdui->m_bRet = true;
   }

   bool list_view::_001OnRemoveItem(index iItem)
   {
      ::mediaplaylist::document * pdoc = get_document();
      return pdoc->RemoveSong(iItem);
   }

   /*PaneView * list_view::GetParentPane()
   {
      //::user::interaction * pwnd = GetParent();
   /*   if(base < PaneView >::bases(pwnd))
      {
         return dynamic_cast < PaneView * > (pwnd);
      }*/
     /* return NULL;
   }*/

   void list_view::_001DrawBackground(::ca::graphics *pdc, LPRECT lprect)
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

   void list_view::_001OnPlaylistExecutePlay(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Range range;
      _001GetSelection(range);
      if(range.get_item_count() > 0)
      {
         int iItem = range.ItemAt(0).GetLBound();

         info info;

         info.m_iCurrentSong  = iItem;
         info.m_ehint         = mediaplaylist::hint_do_play;
         info.m_bMakeVisible  = true;

         get_document()->play(&info);

      }


   }

   void list_view::_001OnUpdatePlaylistExecutePlay(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)
      Range range;
      _001GetSelection(range);
      pupdatecmdui->m_pcmdui->Enable(range.get_item_count() > 0);
      pupdatecmdui->m_bRet = true;
   }


   void list_view::_001OnInitializeForm(::user::control * pcontrol)
   {
      simple_form_list_view::_001OnInitializeForm(pcontrol);
      if(pcontrol->descriptor().m_id == "play_button")
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

   void list_view::_001OnButtonAction(::user::control * pcontrol)
   {
      if(pcontrol->descriptor().m_id == "play_button")
      {

         info info;

         info.m_iCurrentSong     = pcontrol->GetEditItem();
         info.m_ehint            = mediaplaylist::hint_do_play;
         info.m_bMakeVisible     = true;
         info.m_bUser            = true;

         get_document()->play(&info);

      }
   }

   count list_view::_001GetItemCount()
   {
      if(get_document() != NULL)
         return get_document()->get_song_count();
      else
         return -1;
   }


   void list_view::_001OnCreate(gen::signal_object * pobj)
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

      m_pilGroupHover   = new image_list(get_app());

      m_pilGroupHover->create(96, 96, 0,  10, 10);
      m_pilGroupHover->add_matter("mplite/mplite_playlist_96.png");
      m_pilGroup = m_pilGroupHover;
   }

   count list_view::_001GetGroupCount()
   {
      if(get_document() == NULL)
         return 0;
      if(get_document()->m_pnodePlaylist == NULL)
         return 0;
      if(get_document()->is_recursive())
      {
         return get_document()->m_pnodePlaylist->get_children_count("playlist", -1) + 1;
      }
      else
      {
         return 1;
      }
   }

   count list_view::_001GetGroupItemCount(index iGroup)
   {
      if(get_document() == NULL)
         return 0;
      if(get_document()->m_pnodePlaylist == NULL)
         return 0;
      if(get_document()->is_recursive())
      {
         if(iGroup == m_nGroupCount - 1)
         {
            return get_document()->m_pnodePlaylist->get_children_count("song");
         }
         else
         {
            xml::node * pnode = get_document()->m_pnodePlaylist->get_child_at("playlist", iGroup, -1);
            if(pnode == NULL)
               return 0;
            return pnode->get_children_count("song");
         }
      }
      else
      {
         return get_document()->m_pnodePlaylist->get_children_count("song");
      }
   }

   void list_view::_001GetItemText(::user::list_item * pitem)
   {

      simple_form_list_view::_001GetItemText(pitem);

      if(pitem->m_bOk)
         return;

      ASSERT_VALID(this);
      ::mediaplaylist::document * pdoc = get_document();
      string wstrSongPath;

      if(pdoc->get_song_at(wstrSongPath, pitem->m_iItem))
      {
         if(pitem->m_iSubItem == 0)
         {
            pitem->m_strText = wstrSongPath;
         }
         else if(pitem->m_iSubItem == 1)
         {
            pitem->m_strText = wstrSongPath;
         }
         else if(pitem->m_iSubItem == 2)
         {
            pitem->m_strText = System.file().name_(wstrSongPath);
         }
         else if(pitem->m_iSubItem == 3)
         {
            pitem->m_strText = wstrSongPath;
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
      pitem->m_bOk = true;
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
      pitem->m_bOk = true;
   }

   ::count list_view::_001GetGroupMetaItemCount(index iGroup)
   {
      UNREFERENCED_PARAMETER(iGroup);
      return 1;
   }

   void list_view::_001GetGroupText(::user::list_item * pitem)
   {
      if(get_document() == NULL)
         return_(pitem->m_bOk, false);
      if(get_document()->m_pnodePlaylist == NULL)
         return_(pitem->m_bOk, false);
      if(get_document()->is_recursive())
      {
         if(pitem->m_iGroup == m_nGroupCount - 1)
         {
            pitem->m_bOk = get_document()->m_pnodePlaylist->get_attr("name", pitem->m_strText);
         }
         else
         {
            xml::node * pnode = get_document()->m_pnodePlaylist->get_child_at("playlist", pitem->m_iGroup, -1);
            if(pnode == NULL)
               return_(pitem->m_bOk, false);
            pitem->m_bOk = pnode->get_attr("name", pitem->m_strText);
         }
      }
      else
      {
         pitem->m_bOk = get_document()->m_pnodePlaylist->get_attr("name", pitem->m_strText);
      }
   }

   void list_view::_001GetGroupImage(::user::list_item * pitem)
   {
      pitem->m_bOk = true;
      pitem->m_iImage = 0;
   }

} // namespace mediaplaylist


