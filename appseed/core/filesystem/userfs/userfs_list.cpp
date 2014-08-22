#include "framework.h"


namespace userfs
{


   list::list(sp(::axis::application) papp) :
      element(papp),
      ::user::scroll_view(papp),
      m_headerctrl(papp),
      user::list(papp),
      ::user::form_interface(papp),
      user::form(papp),
      user::form_list(papp)
   {

      m_headerctrl.m_dataid = "veiev::list::header_ctrl";


      m_dataid = "mail::list";
      m_pdata = new list_data(papp);
      //m_pdata->m_plist  = this;
      SetDataInterface(m_pdata);


      m_scrollinfo.m_rectMargin.left = -23;
      m_scrollinfo.m_rectMargin.top = -8;
      m_scrollinfo.m_rectMargin.bottom = 0;
      m_scrollinfo.m_rectMargin.right = 0;
      
   }

   list::~list()
   {

      delete m_pdata;

   }

   void list::install_message_handling(::message::dispatch * pinterface)
   {
      ::user::form_list::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_HSCROLL, pinterface, this, &list::_001OnHScroll);
      IGUI_WIN_MSG_LINK(WM_VSCROLL, pinterface, this, &list::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &list::_001OnShowWindow);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &list::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &list::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &list::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_CANCELMODE, pinterface, this, &list::_001OnCancelMode);
   }

   void list::_001OnCreate(signal_details * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
   }


   void list::_001OnTimer(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   void list::_001OnClick(uint_ptr uiFlags, point point)
   {
      UNREFERENCED_PARAMETER(uiFlags);
      UNREFERENCED_PARAMETER(point);
      range range;
      _001GetSelection(range);
      if(range.get_item_count() > 0)
      {
         list_data * pdata = get_fs_list_data();
         item_range & itemrange = range.ItemAt(0);
         index iLItem = itemrange.get_lower_bound();
         index iUItem = itemrange.get_upper_bound();
         if(iUItem < iLItem)
         {
            iUItem = pdata->m_itema.get_upper_bound();
         }
         if(iLItem < 0)
            return;
         if(iLItem >= pdata->m_itema.get_size())
            return;
         if(iUItem >= pdata->m_itema.get_size())
            iUItem = pdata->m_itema.get_upper_bound();
         var varFile;
         var varQuery;
         if(iUItem == iLItem)
         {
            varFile = get_fs_list_data()->m_itema.get_item(iLItem).m_strPath;
         }
         else
         {
            stringa stra;
            for(index iItem = iLItem; iItem < iLItem; iItem++)
            {
               stra.add(pdata->m_itema.get_item(iItem).m_strPath);
            }
            varFile = stra;
         }
         get_document()->request_file_query(varFile, varQuery);
      }
   }


#ifdef DEBUG
   void list::assert_valid() const
   {
      ::user::form_list::assert_valid();
   }

   void list::dump(dump_context & dumpcontext) const
   {
      ::user::form_list::dump(dumpcontext);
   }
#endif //DEBUG

   void list::on_update(sp(::user::impact) pSender, LPARAM lHint, object * phint)
   {


   }

   void list::_001OnLButtonDblClk(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::mouse, pmouse, pobj)
/*         index iItem;
      list_data * pdata = get_fs_list_data();
      if(_001HitTest_(pmouse->m_pt, iItem))
      {
         ::fs::item item;
         item.m_strPath         = pdata->m_foldera.GetFolder(iItem).m_strPath;
         get_filemanager_template()->get_filemanager_data()->OnFileManagerOpenFolder(item);
      }*/
   }

   void list::_001OnCancelMode(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   // trans   ::user::impact::OnCancelMode();

      // TODO: add your message handler code here

   }

   bool list::pre_create_window(::user::create_struct& cs)
   {

      cs.style |= WS_CLIPCHILDREN;

      return ::user::form_list::pre_create_window(cs);
   }

   void list::_001InsertColumns()
   {
      ::user::list_column column;
      column.m_iWidth = 200;
      column.m_iSubItem = 0;

      _001InsertColumn(column);
      column.m_iWidth = 300;
      column.m_iSubItem = 1;

      _001InsertColumn(column);
      column.m_iWidth = 100;
      column.m_iSubItem = 2;

      _001InsertColumn(column);
   }


   bool list::_001OnUpdateItemCount(uint32_t dwFlags)
   {
      return ::user::list::_001OnUpdateItemCount(dwFlags);
   }

   void list::GetSelectedFilePath(stringa & array)
   {
      range range;

      _001GetSelection(range);

      list_data * pdata = get_fs_list_data();
      string str;
      //      HRESULT hr;
      for (index i = 0; i < range.get_item_count(); i++)
      {
         item_range & itemrange = range.ItemAt(i);
         for (index iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
         {
            index iStrict;
            if (m_eview == ViewIcon)
            {
               iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
            }
            else
            {
               iStrict = m_listlayout.m_iaDisplayToStrict[iItem];
            }
            list_item & item = pdata->m_itema.get_item(iStrict);
            if (!item.IsFolder())
            {
               array.add(item.m_strPath);
            }
         }
      }

   }



   void list::_001OnDraw(::draw2d::graphics *pdc)
   {
      ::user::form_list::_001OnDraw(pdc);

   }

   void list::StartAnimation()
   {
      //         m_iAnimate = 1;
   }

   void list::TakeAnimationSnapshot()
   {
      //       m_iAnimate = 1;
      //     ::user::list::_001OnDraw(m_gdibuffer.GetBuffer());
   }


   void list::_017OpenSelected(bool bOpenFile, ::action::context actioncontext)
   {
      list_data * pdata = get_fs_list_data();
      ::fs::item_array itema;
      index iItemRange, iItem;
      range range;
      _001GetSelection(range);
      for (iItemRange = 0;
         iItemRange < range.get_item_count();
         iItemRange++)
      {
         item_range itemrange = range.ItemAt(iItemRange);
         for (iItem = itemrange.get_lower_bound();
            iItem <= itemrange.get_upper_bound();
            iItem++)
         {
            if (iItem < 0)
               continue;
            if (iItem >= _001GetItemCount())
               continue;
            index iStrict;
            if (m_eview == ViewIcon)
            {
               iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
            }
            else
            {
               iStrict = m_listlayout.m_iaDisplayToStrict[iItem];
            }
            list_item & item = pdata->m_itema.get_item(iStrict);
            sp(::fs::item) pitem(new ::fs::item(item));
            if (item.IsFolder())
            {
               _017OpenFolder(pitem, ::action::source::sel(actioncontext));
               break;
            }
            else
            {
               itema.add(pitem);
            }
         }
      }
      if (bOpenFile && itema.get_size() > 0)
      {
         _017OpenFile(itema, ::action::source::sel(actioncontext));
      }
      _001ClearSelection();
   }

   void list::_017OpenContextMenuSelected(::action::context actioncontext)
   {
      list_data * pdata = get_fs_list_data();
      ::fs::item_array itema;
      index iItemRange, iItem;
      range range;
      _001GetSelection(range);
      for (iItemRange = 0;
         iItemRange < range.get_item_count();
         iItemRange++)
      {
         item_range itemrange = range.ItemAt(iItemRange);
         for (iItem = itemrange.get_lower_bound();
            iItem <= itemrange.get_upper_bound();
            iItem++)
         {
            if (iItem < 0)
               continue;
            if (iItem >= pdata->m_itema.get_count())
               continue;
            index iStrict;
            if (m_eview == ViewIcon)
            {
               iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
            }
            else
            {
               iStrict = m_listlayout.m_iaDisplayToStrict[iItem];
            }
            list_item & item = pdata->m_itema.get_item(iStrict);
            if (pdata->m_itema.get_item(iStrict).IsFolder())
            {
               _017OpenContextMenuFolder(new ::fs::item(item), actioncontext);
               break;
            }
            else
            {
               itema.add(new ::fs::item(item));
            }
         }
      }
      if (itema.get_size() > 0)
      {
         _017OpenContextMenuFile(itema, actioncontext);
      }
      else
      {
         _017OpenContextMenu(actioncontext);
      }
      _001ClearSelection();
   }

   void list::_017OpenContextMenuFolder(sp(::fs::item) item, ::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(item);
      UNREFERENCED_PARAMETER(actioncontext);
   }

   void list::_017OpenContextMenuFile(const ::fs::item_array &itema, ::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(itema);
      UNREFERENCED_PARAMETER(actioncontext);
   }

   void list::_017OpenContextMenu(::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(actioncontext);
   }

   void list::_017OpenFolder(sp(::fs::item) item, ::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(item);
      UNREFERENCED_PARAMETER(actioncontext);
      ASSERT(FALSE);
   }

   void list::_017OpenFolder(const ::userfs::list_item &item, ::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(item);
      UNREFERENCED_PARAMETER(actioncontext);
      ASSERT(FALSE);
   }

   void list::_017OpenFile(const ::fs::item_array &itema, ::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(itema);
      UNREFERENCED_PARAMETER(actioncontext);
      ASSERT(FALSE);
   }

   void list::_001OnInitializeForm(sp(::user::control) pcontrol)
   {
      ASSERT(pcontrol != NULL);
      if (pcontrol == NULL)
         return;

      /*      filemanager::file_list_callback * pcallback =
      get_filemanager_template()->get_filemanager_template()->m_pfilelistcallback;

      sp(BaseButtonControl) pbutton =  (pcontrol);
      if(pcallback != NULL && pbutton != NULL)
      {
      pcallback->InitializeActionButton(((int32_t) pcontrol->descriptor().m_id) - 1000, pbutton);
      } */
   }

   void list::_001OnButtonAction(sp(::user::control) pcontrol)
   {
      UNREFERENCED_PARAMETER(pcontrol);
      //      list_data * pdata = get_fs_list_data();
      /* filemanager::file_list_callback * pcallback =
      get_filemanager_template()->get_filemanager_template()->m_pfilelistcallback;

      if(pcallback != NULL)
      {
      ::fs::item item;
      int32_t iItem = pcontrol->GetEditItem();
      int32_t iStrict;
      if(m_eview == ViewIcon)
      {
      iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
      }
      else
      {
      iStrict = m_listlayout.m_iaDisplayToStrict[iItem];
      }
      item.m_strPath         = pdata->m_itema.get_item(iStrict).m_strPath;
      item.m_strExtra        = pdata->m_itema.get_item(iStrict).m_strExtra;
      pcallback->OnButtonAction((int32_t) pcontrol->descriptor().m_id - 1000, item);
      } */
   }

   void list::GetSelected(::fs::item_array &itema)
   {
      list_data * pdata = get_fs_list_data();
      index iItemRange, iItem;
      range range;
      _001GetSelection(range);
      index_array iaItem;
      for (iItemRange = 0;
         iItemRange < range.get_item_count();
         iItemRange++)
      {
         item_range itemrange = range.ItemAt(iItemRange);
         for (iItem = MAX(0, itemrange.get_lower_bound());
            iItem <= itemrange.get_upper_bound();
            iItem++)
         {
            ::fs::item item;
            if (iItem < pdata->m_itema.get_count() && !iaItem.contains(iItem))
            {
               iaItem.add(iItem);
               index iStrict;
               if (m_eview == ViewIcon)
               {
                  iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
               }
               else
               {
                  if (iItem >= m_listlayout.m_iaDisplayToStrict.get_count())
                     continue;
                  iStrict = m_listlayout.m_iaDisplayToStrict[iItem];
               }
               itema.add(new ::fs::item(pdata->m_itema.get_item(iStrict)));
            }
         }
      }
   }

   void list::_001OnVScroll(signal_details * pobj)
   {
      //      SCAST_PTR(::message::scroll, pscroll, pobj)
      //m_iCreateImageListStep = pscroll->m_nPos;
      //m_bRestartCreateImageList = true;
      pobj->m_bRet = false;
   }

   void list::_001OnHScroll(signal_details * pobj)
   {
      pobj->m_bRet = false;
   }

   ::count list::_001GetItemCount()
   {
      return get_fs_list_data()->m_itema.get_count();
   }

   void list::add_item(const char * pszPath, const char * pszTitle)
   {
      
      list_item item(get_app());
      
      item.m_strPath = pszPath;
      
      item.m_strName = pszTitle;
      
      if (get_document()->get_fs_data()->is_dir(pszPath))
      {

         item.m_flags.signalize(::fs::FlagFolder);

      }

      get_fs_list_data()->m_itema.add_item(item);

      _001OnUpdateItemCount();

   }


   sp(image_list) list::GetActionButtonImageList(index i)
   {
      if (i == 0)
      {
         return System.userex()->shellimageset().GetImageList16();
      }
      return NULL;
   }

   void list::_001OnFileRename(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      sp(::user::control) pcontrol = _001GetControlBySubItem(get_fs_list_data()->m_iNameSubItem);
      range range;
      _001GetSelection(range);
      if (range.get_item_count() == 1 && range.ItemAt(0).get_lower_bound() == range.ItemAt(0).get_upper_bound())
      {
         _001PlaceControl(pcontrol);
      }
   }

   void list::_001OnUpdateFileRename(signal_details * pobj)
   {
      SCAST_PTR(::axis::cmd_ui, pcmdui, pobj)
         range range;
      _001GetSelection(range);
      pcmdui->m_pcmdui->Enable(
         range.get_item_count() == 1
         && range.ItemAt(0).get_lower_bound() == range.ItemAt(0).get_upper_bound());
      pobj->m_bRet = true;
   }

   void list::_001OnShowWindow(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //      SCAST_PTR(::message::show_window, pshow, pobj)

      db_server * pcentral = dynamic_cast < db_server * > (&System.m_simpledb.db());
      if (pcentral == NULL)
         return;
      //DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;
      /*if(pshow->m_bShow)
      {
      for(int32_t i = 0; i < m_itema.get_item_count(); i++)
      {
      pset->m_table.add_request(m_itema.get_item(i).m_strPath);
      }
      }
      else
      {
      for(int32_t i = 0; i < m_itema.get_item_count(); i++)
      {
      pset->m_table.remove_request(m_itema.get_item(i).m_strPath);
      }
      }*/
   }


   void list::_001InitializeFormPreData()
   {
      /*      ::filemanager::data * pdata = get_filemanager_template()->get_filemanager_data();
      pdata->m_pcallback->OnFileManagerInitializeFormPreData(
      pdata,
      GetDlgCtrlId(),
      this);*/
   }


   bool list::query_drop(index iDisplayDrop, index iDisplayDrag)
   {
      list_data * pdata = get_fs_list_data();
      if (iDisplayDrag < 0)
         return false;
      if (iDisplayDrop < 0)
         return false;
      if (m_iItemDrag != m_iItemDrop)
      {
         index strict;
         if (m_eview == ViewIcon)
            strict = m_iconlayout.m_iaDisplayToStrict[iDisplayDrop];
         else
            strict = m_listlayout.m_iaDisplayToStrict[iDisplayDrop];
         if (strict <= -1)
            return true; // can drop in is_empty place
         else if (strict >= _001GetItemCount())
            return true; // can drop if destination is invalid
         else
         {
            // can drop if destination is folder
            return pdata->m_itema.get_item(strict).IsFolder();
         }
      }

      return false;

   }


   bool list::do_drop(index iDisplayDrop, index iDisplayDrag)
   {

      list_data * pdata = get_fs_list_data();

      index strict;

      index strictDrag;

      if (m_eview == ViewIcon)
      {

         strict = m_iconlayout.m_iaDisplayToStrict[iDisplayDrop];

         strictDrag = m_iconlayout.m_iaDisplayToStrict[iDisplayDrag];

      }
      else
      {

         strict = m_listlayout.m_iaDisplayToStrict[iDisplayDrop];

         strictDrag = m_listlayout.m_iaDisplayToStrict[iDisplayDrag];

      }

      if (strict >= 0 && pdata->m_itema.get_item(strict).IsFolder())
      {

         string strPath = pdata->m_itema.get_item(strictDrag).m_strPath;

         string strName = get_document()->get_fs_data()->file_name(strPath);

         get_document()->get_fs_data()->file_move(pdata->m_itema.get_item(strict).m_strPath, strPath);

//         _017Synchronize(::action::source::add(::action::source_paste, ::action::source_user));

      }
      else
      {

         ::user::list::do_drop(iDisplayDrop, iDisplayDrag);

      }

      return true;

   }


   COLORREF list::get_background_color()
   {
      //if(get_filemanager_template() != NULL && get_filemanager_template()->get_filemanager_data()->is_saving())
      {
         return RGB(255, 177, 84);
      }
      //      else
      {
      return RGB(200, 255, 255);
   }
   }

   list_data * list::get_fs_list_data()
   {
      return dynamic_cast < list_data * > (m_pdata);
   }


   sp(::userfs::document) list::get_document()
   {
      return  (::user::form_list::get_document());
   }

   void list::_001GetItemText(::user::list_item * pitem)
   {
      return ::user::form_list::_001GetItemText(pitem);
   }

   void list::_001GetItemImage(::user::list_item * pitem)
   {
      return ::user::form_list::_001GetItemImage(pitem);
   }




} // namespace userfs

