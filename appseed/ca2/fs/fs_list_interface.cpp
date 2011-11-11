#include "StdAfx.h"


namespace fs
{


   list_interface::list_interface(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::user::list(papp),
      user::form(papp),
      user::form_list(papp),
      userbase::form_list(papp)
   {

      m_dataid          = "mail::list_interface";
      m_pdata           = new list_data(papp);
      //m_pdata->m_plist  = this;
      SetDataInterface(m_pdata);

   }

   void list_interface::_001InsertColumns()
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


   list_interface::~list_interface()
   {
      delete m_pdata;
   }

   bool list_interface::_001OnUpdateItemCount(DWORD dwFlags)
   {
      return ::user::list::_001OnUpdateItemCount(dwFlags);
   }

   void list_interface::GetSelectedFilePath(stringa & base_array)
   {
      Range range;

      _001GetSelection(range);

      list_data * pdata = get_fs_list_data();
      string str;
//      HRESULT hr;
      for(int i = 0; i < range.get_item_count(); i++)
      {
         ItemRange & itemrange = range.ItemAt(i);
         for(int iItem = itemrange.GetLBound() ; iItem <= itemrange.GetUBound(); iItem ++)
         {
            int iStrict;
            if(m_eview == ViewIcon)
            {
               iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
            }
            else
            {
               iStrict = m_listlayout.m_iaDisplayToStrict[iItem];
            }
            list_item & item = pdata->m_itema.get_item(iStrict);
            if(!item.IsFolder())
            {
               base_array.add(item.m_strPath);
            }
         }
      }

   }


   void list_interface::_017UpdateList()
   {


      _017UpdateList(get_document()->m_strFolder);


   }

   void list_interface::_017UpdateZipList(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
   }

   void list_interface::_017UpdateList(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      //UNREFERENCED_PARAMETER(lpsz);
      stringa straStrictOrder;
      data_get(
         data_get_current_sort_id(),
         string(data_get_current_list_layout_id()) + ".straStrictOrder",
         straStrictOrder);
      index_biunique iaDisplayToStrict;
      icon_layout iconlayout;
      data_get(data_get_current_sort_id(), data_get_current_list_layout_id(),
         iconlayout);
      iaDisplayToStrict = iconlayout.m_iaDisplayToStrict;
      index_biunique iaDisplayToStrictNew;

      //m_straFileSize.remove_all();
      ::fs::list_item item;
//      get_fs_list_data()->m_itema.clear(NULL, NULL);
      _001OnUpdateItemCount();
      /*if(m_bStatic)
      {
         stringa stra;
         GetFileManager()->data_get(GetFileManager()->get_filemanager_data()->m_ptemplate->m_dataidStatic, ::radix::system::idEmpty, stra);
         for(int i = 0; i < stra.get_size(); i++)
         {
            item.m_flags.unsignalize_all();
            if(get_fs_data()->is_dir(stra[i]))
            {
               item.m_flags.signalize(filemanager::FlagFolder);
            }
            else
            {
            }
            item.m_iImage = -1;
            item.m_strPath = stra[i];
            item.m_strName = get_fs_data()->file_title(stra[i]);

            m_itema.add_item(item);
         }
         _001OnUpdateItemCount();
         return;
      }*/



      string strParent = lpcsz;

      int iMaxSize;
      iMaxSize = 1000;

      int iSize;
      iSize = 0;

      get_fs_list_data()->m_itema.SetItemCount(iMaxSize);

      m_straStrictOrder.remove_all();

      stringa straPath;
      stringa straTitle;
      if(strlen(lpcsz) == 0)
      {
         get_document()->root_ones(straPath);
         straTitle = straPath;
      }
      else
      {
         get_document()->ls(lpcsz, &straPath, & straTitle);
      }

      for(int i = 0; i < straPath.get_size(); i++)
      {
         item.m_flags.unsignalize_all();
         if(get_document()->is_dir(straPath[i]))
         {
            item.m_flags.signalize(::fs::FlagFolder);
         }
         else
         {
         }
         item.m_iImage = -1;
         item.m_strPath = straPath[i];
         item.m_strName = straTitle[i];
         m_straStrictOrder.add(straPath[i]);

         get_fs_list_data()->m_itema.SetItemAt(iSize, item);
         iSize++;
         if(iSize >= iMaxSize)
         {
            iMaxSize += 1000;
            get_fs_list_data()->m_itema.SetItemCount(iMaxSize);
         }
      }
      get_fs_list_data()->m_itema.SetItemCount(iSize);



      _001OnUpdateItemCount();

      if(m_eview == ViewIcon)
      {
         /*   // primeiro, todos System arquivos que foram removidos
         // ou seja, que existem no array antigo,
         // mas não existe no novo.
         for(index strictOld = 0; strictOld < straStrictOrder.get_count(); strictOld++)
         {
            string str = straStrictOrder[strictOld];
            index find = m_straStrictOrder.find_first(str);
            if(find < 0)
            {
               iaDisplayToStrictNew.remove_b(strictOld);
            }
         }*/
         // segundo, reordena conforme a
         // ordem que a listagem de arquivos fornecida pelo
         // sistema operacional pode ser fornecida.
         for(index strictNew = 0; strictNew < m_straStrictOrder.get_count(); strictNew++)
         {
            string str = m_straStrictOrder[strictNew];
            index strictOld = straStrictOrder.find_first(str);
            if(strictOld >= 0)
            {
               index iDisplay = iaDisplayToStrict.get_a(strictOld);
               iaDisplayToStrictNew.set(iDisplay, strictNew);
            }
         }
         // terceiro, adiciona System novos arquivos nos primeiros espaços
         // vazios
         for(index strictNew = 0; strictNew < m_straStrictOrder.get_count(); strictNew++)
         {
            string str = m_straStrictOrder[strictNew];
            index strictOld = straStrictOrder.find_first(str);
            if(strictOld < 0)
            {
               iaDisplayToStrictNew.add_b_in_first_free_a(strictNew);
            }
         }
         m_iconlayout.m_iaDisplayToStrict = iaDisplayToStrictNew;
      }
      else
      {
         get_fs_list_data()->m_itema.arrange(arrange_by_name);
      }

      _001CreateImageList();

      _001RedrawWindow();

      //file_size_add_request(true);
   /*   for(int i = 0; i < m_itema.get_item_count(); i++)
      {
         pset->m_table.add_request(m_itema.get_item(i).m_strPath);
      }*/
      if(m_eview == ViewIcon)
      {
         data_set(
            data_get_current_sort_id(),
            string(data_get_current_list_layout_id()) + ".straStrictOrder",
            m_straStrictOrder);
         m_iconlayout.m_iaDisplayToStrict = iaDisplayToStrictNew;
         data_set_DisplayToStrict();
      }
   }


   /*void list_interface::_017OneLevelUp()
   {
      if(m_lpiidlAbsolute == NULL)
         return;

      single_lock slBrowse(&m_csBrowse, TRUE);
      LPMALLOC lpmalloc = NULL;
      IShellFolder * lpsfDesktop;
      HRESULT hr;

      hr = SHGetMalloc(&lpmalloc);

      hr = SHGetDesktopFolder(&lpsfDesktop);

      LPITEMIDLIST lpiidl = _shell::_017ItemIDListGetFolderParent(m_lpiidlAbsolute);

      _017Browse(lpiidl);

      lpsfDesktop->Release();
      lpmalloc->Release();

   }*/



   void list_interface::_017Synchronize()
   {


      ::ca::data::writing writing(m_pdata);
      _001HideEditingControls();
      _017UpdateList(get_document()->m_strFolder);


   }

   void list_interface::install_message_handling(::user::win::message::dispatch *pinterface)
   {


      ::user::form_list::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_HSCROLL, pinterface, this, &list_interface::_001OnHScroll);
      IGUI_WIN_MSG_LINK(WM_VSCROLL, pinterface, this, &list_interface::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &list_interface::_001OnShowWindow);


   }

   void list_interface::_001OnDraw(::ca::graphics *pdc)
   {
/*         if(m_iAnimate <= 0)
      {*/
         // Normal Drawing
         ::userbase::form_list::_001OnDraw(pdc);
/*       }
      else
      {
         // Animation Drawing
         rect rectClipBox;
         pdc->GetClipBox(rectClipBox);
         class imaging & imaging = System.imaging();
   //      ::user::list::_001DrawBackground(pdc, rectClipBox);
         imaging.color_blend(
            pdc,
            rectClipBox,
            RGB(255, 255, 255),
            127);

         imaging.bitmap_blend(
            pdc,
            null_point(),
            rectClipBox.size(),
            m_gdibuffer.GetBuffer(),
            null_point(),
            (byte) (255 - m_iAnimate * 25));
      }*/

   }

   void list_interface::StartAnimation()
   {
//         m_iAnimate = 1;
   }

   void list_interface::TakeAnimationSnapshot()
   {
//       m_iAnimate = 1;
   //     ::user::list::_001OnDraw(m_gdibuffer.GetBuffer());
   }

   void list_interface::_017PreSynchronize()
   {
      //TakeAnimationSnapshot();
   }





   void list_interface::_017OpenSelected(bool bOpenFile)
   {
      list_data * pdata = get_fs_list_data();
      ::fs::item_array itema;
      int iItemRange, iItem;
      Range range;
      _001GetSelection(range);
      for(iItemRange = 0;
            iItemRange < range.get_item_count();
            iItemRange++)
      {
         ItemRange itemrange = range.ItemAt(iItemRange);
         for(iItem = itemrange.GetLBound();
               iItem <= itemrange.GetUBound();
               iItem++)
         {
            if(iItem < 0)
               continue;
            if(iItem >= _001GetItemCount())
               continue;
            int iStrict;
            if(m_eview == ViewIcon)
            {
               iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
            }
            else
            {
               iStrict = m_listlayout.m_iaDisplayToStrict[iItem];
            }
            if(pdata->m_itema.get_item(iStrict).IsFolder())
            {
               _017OpenFolder(::fs::item(pdata->m_itema.get_item(iStrict)));
               break;
            }
            else
            {
               itema.add(::fs::item(pdata->m_itema.get_item(iStrict)));
            }
         }
      }
      if(bOpenFile && itema.get_size() > 0)
      {
         _017OpenFile(itema);
      }
      _001ClearSelection();
   }

   void list_interface::_017OpenContextMenuSelected()
   {
      list_data * pdata = get_fs_list_data();
      ::fs::item_array itema;
      int iItemRange, iItem;
      Range range;
      _001GetSelection(range);
      for(iItemRange = 0;
            iItemRange < range.get_item_count();
            iItemRange++)
      {
         ItemRange itemrange = range.ItemAt(iItemRange);
         for(iItem = itemrange.GetLBound();
               iItem <= itemrange.GetUBound();
               iItem++)
         {
            if(iItem < 0)
               continue;
            if(iItem >= pdata->m_itema.get_count())
               continue;
            int iStrict;
            if(m_eview == ViewIcon)
            {
               iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
            }
            else
            {
               iStrict = m_listlayout.m_iaDisplayToStrict[iItem];
            }
            if(pdata->m_itema.get_item(iStrict).IsFolder())
            {
               _017OpenContextMenuFolder(::fs::item(pdata->m_itema.get_item(iStrict)));
               break;
            }
            else
            {
               itema.add(::fs::item(pdata->m_itema.get_item(iStrict)));
            }
         }
      }
      if(itema.get_size() > 0)
      {
         _017OpenContextMenuFile(itema);
      }
      else
      {
         _017OpenContextMenu();
      }
      _001ClearSelection();
   }

   void list_interface::_017OpenContextMenuFolder(const ::fs::item &item)
   {
      UNREFERENCED_PARAMETER(item);
   }

   void list_interface::_017OpenContextMenuFile(const ::fs::item_array &itema)
   {
      UNREFERENCED_PARAMETER(itema);
   }

   void list_interface::_017OpenContextMenu()
   {
   }

   void list_interface::_017OpenFolder(const ::fs::item &item)
   {
      UNREFERENCED_PARAMETER(item);
      ASSERT(FALSE);
   }

   void list_interface::_017OpenFile(const ::fs::item_array &itema)
   {
      UNREFERENCED_PARAMETER(itema);
      ASSERT(FALSE);
   }

   void list_interface::_001OnInitializeForm(user::control * pcontrol)
   {
      ASSERT(pcontrol != NULL);
      if(pcontrol == NULL)
         return;

/*      FileManagerFileListCallback * pcallback =
         GetFileManager()->get_filemanager_data()->m_ptemplate->m_pfilelistcallback;

      BaseButtonControl * pbutton = dynamic_cast < BaseButtonControl * > (pcontrol);
      if(pcallback != NULL && pbutton != NULL)
      {
         pcallback->InitializeActionButton(((int) pcontrol->descriptor().m_id) - 1000, pbutton);
      } */
   }

   void list_interface::_001OnButtonAction(::user::control * pcontrol)
   {
      UNREFERENCED_PARAMETER(pcontrol);
//      list_data * pdata = get_fs_list_data();
      /* FileManagerFileListCallback * pcallback =
         GetFileManager()->get_filemanager_data()->m_ptemplate->m_pfilelistcallback;

      if(pcallback != NULL)
      {
         ::fs::item item;
         int iItem = pcontrol->GetEditItem();
         int iStrict;
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
         pcallback->OnButtonAction((int) pcontrol->descriptor().m_id - 1000, item);
      } */
   }

   void list_interface::GetSelected(::fs::item_array &itema)
   {
      list_data * pdata = get_fs_list_data();
      int iItemRange, iItem;
      Range range;
      _001GetSelection(range);
      int_array iaItem;
      for(iItemRange = 0;
            iItemRange < range.get_item_count();
            iItemRange++)
      {
         ItemRange itemrange = range.ItemAt(iItemRange);
         for(iItem = max(0, itemrange.GetLBound());
               iItem <= itemrange.GetUBound();
               iItem++)
         {
            ::fs::item item;
            if(iItem < pdata->m_itema.get_count() && !iaItem.contains(iItem))
            {
               iaItem.add(iItem);
               int iStrict;
               if(m_eview == ViewIcon)
               {
                  iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
               }
               else
               {
                  if(iItem >= m_listlayout.m_iaDisplayToStrict.get_count())
                     continue;
                  iStrict = m_listlayout.m_iaDisplayToStrict[iItem];
               }
               itema.add(::fs::item(pdata->m_itema.get_item(iStrict)));
            }
         }
      }
   }

   void list_interface::_001OnVScroll(gen::signal_object * pobj)
   {
//      SCAST_PTR(::user::win::message::scroll, pscroll, pobj)
      //m_iCreateImageListStep = pscroll->m_nPos;
      //m_bRestartCreateImageList = true;
      pobj->m_bRet = false;
   }

   void list_interface::_001OnHScroll(gen::signal_object * pobj)
   {
      pobj->m_bRet = false;
   }

   count list_interface::_001GetItemCount()
   {
      return get_fs_list_data()->m_itema.get_count();
   }

   void list_interface::add_item(const char * pszPath, const char * pszTitle)
   {
      list_item item;
      item.m_strPath = pszPath;
      item.m_strName = pszTitle;
      if(get_document()->is_dir(pszPath))
      {
         item.m_flags.signalize(FlagFolder);
      }
      get_fs_list_data()->m_itema.add_item(item);
      _001OnUpdateItemCount();
   }


   image_list * list_interface::GetActionButtonImageList(index i)
   {
      if(i == 0)
      {
         return System.shellimageset().GetImageList16();
      }
      return NULL;
   }

   void list_interface::_001OnFileRename(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      user::control * pcontrol = _001GetControlBySubItem(get_fs_list_data()->m_iNameSubItem);
      Range range;
      _001GetSelection(range);
      if(range.get_item_count() == 1 && range.ItemAt(0).GetLBound() == range.ItemAt(0).GetUBound())
      {
         _001PlaceControl(pcontrol);
      }
   }

   void list_interface::_001OnUpdateFileRename(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      Range range;
      _001GetSelection(range);
      pcmdui->m_pcmdui->Enable(
         range.get_item_count() == 1
         && range.ItemAt(0).GetLBound() == range.ItemAt(0).GetUBound());
      pobj->m_bRet = true;
   }

   void list_interface::_001OnShowWindow(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::show_window, pshow, pobj)

      db_server * pcentral = dynamic_cast < db_server * > (&System.db());
      if(pcentral == NULL)
         return;
      //DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;
      /*if(pshow->m_bShow)
      {
         for(int i = 0; i < m_itema.get_item_count(); i++)
         {
            pset->m_table.add_request(m_itema.get_item(i).m_strPath);
         }
      }
      else
      {
         for(int i = 0; i < m_itema.get_item_count(); i++)
         {
            pset->m_table.remove_request(m_itema.get_item(i).m_strPath);
         }
      }*/
   }


   void list_interface::_001InitializeFormPreData()
   {
/*      ::filemanager::data * pdata = GetFileManager()->get_filemanager_data();
      pdata->m_pcallback->OnFileManagerInitializeFormPreData(
         pdata,
         GetDlgCtrlId(),
         this);*/
   }


   bool list_interface::query_drop(index iDisplayDrop, index iDisplayDrag)
   {
      list_data * pdata = get_fs_list_data();
      if(iDisplayDrag < 0)
         return false;
      if(iDisplayDrop < 0)
         return false;
      if(m_iItemDrag != m_iItemDrop)
      {
         index strict;
         if(m_eview == ViewIcon)
            strict = m_iconlayout.m_iaDisplayToStrict[iDisplayDrop];
         else
            strict = m_listlayout.m_iaDisplayToStrict[iDisplayDrop];
         if(strict <= -1)
            return true; // can drop in is_empty place
         else if(strict >= _001GetItemCount())
            return true; // can drop if destination is invalid
         else
         {
            // can drop if destination is folder
            return pdata->m_itema.get_item(strict).IsFolder();
         }
      }
      return false;
   }


   bool list_interface::do_drop(index iDisplayDrop, index iDisplayDrag)
   {
      list_data * pdata = get_fs_list_data();
      index strict;
      index strictDrag;
      if(m_eview == ViewIcon)
      {
         strict = m_iconlayout.m_iaDisplayToStrict[iDisplayDrop];
         strictDrag = m_iconlayout.m_iaDisplayToStrict[iDisplayDrag];
      }
      else
      {
         strict = m_listlayout.m_iaDisplayToStrict[iDisplayDrop];
         strictDrag = m_listlayout.m_iaDisplayToStrict[iDisplayDrag];
      }
      if(strict >= 0 && pdata->m_itema.get_item(strict).IsFolder())
      {
         string strPath = pdata->m_itema.get_item(strictDrag).m_strPath;
         string strName = get_document()->file_name(strPath);
         get_document()->file_move(pdata->m_itema.get_item(strict).m_strPath, strPath);
         _017Synchronize();
      }
      else
      {
         ::user::list::do_drop(iDisplayDrop, iDisplayDrag);
      }
      return true;
   }

   COLORREF list_interface::get_background_color()
   {
      //if(GetFileManager() != NULL && GetFileManager()->get_filemanager_data()->is_saving())
      {
         return RGB(255, 177, 84);
      }
//      else
      {
         return RGB(200, 255, 255);
      }
   }

   list_data * list_interface::get_fs_list_data()
   {
      return dynamic_cast < list_data * > (m_pdata);
   }


   document * list_interface::get_document()
   {
      return dynamic_cast < document * > (::userbase::form_list::get_document());
   }

   void list_interface::_001GetItemText(::user::list_item * pitem)
   {
      return ::userbase::form_list::_001GetItemText(pitem);
   }

   void list_interface::_001GetItemImage(::user::list_item * pitem)
   {
      return ::userbase::form_list::_001GetItemImage(pitem);
   }


   void list_interface::_001CreateImageList()
   {

/*      icon_key iconkey;
      icon icon;
      for(POSITION pos = m_iconmap.get_start_position();
         pos != NULL;
         m_iconmap.get_next_assoc(pos, iconkey, icon))
      {
         DestroyIcon(icon.m_hicon);
      }

      m_iCreateImageListStep = 0;
      m_bCreateImageList = true;
      if(m_pcreateimagelistthread == NULL)
      {
         m_pcreateimagelistthread = new create_image_list_thread(get_app());
         m_pcreateimagelistthread->m_plist = this;
         m_pcreateimagelistthread->Begin();
      }*/
   }

/*   list_interface::create_image_list_thread::create_image_list_thread(::ca::application * papp) :
      ca(papp),
      thread(papp)
   {
   }

   int list_interface::create_image_list_thread::run()
   {
      int iStepSetCount = 77;
      int iStepSetSleep = 84;
      while(get_run())
      {
         int i = iStepSetCount;
         while(i > 0 && get_run())
         {
            if(!m_plist->_001CreateImageListStep())
               goto endloop;
            i--;
         }
         m_plist->PostMessage(MessageMainPost, MessageMainPostCreateImageListItemStepSetRedraw);
         Sleep(iStepSetSleep);
      }
   endloop:
      m_plist->PostMessage(MessageMainPost, MessageMainPostCreateImageListItemRedraw);
      synch_lock lock(m_plist->m_pthread);
      m_plist->m_pcreateimagelistthread = NULL;
      return 0;
   }

   bool list_interface::_001CreateImageListStep()
   {

      if(m_iCreateImageListStep < 0
         || m_iCreateImageListStep >= m_itema.get_item_count())
      {
         if(m_bRestartCreateImageList)
         {
            m_bRestartCreateImageList = false;
            m_iCreateImageListStep = 0;
         }
         else
         {
            return false;
         }
      }
      if(m_iCreateImageListStep < 0
         || m_iCreateImageListStep >= m_itema.get_item_count())
      {
         return false;
      }

      ::user::list_column &column = m_columna.GetBySubItem(m_iNameSubItem);

      if(column.m_iSubItem == m_iNameSubItem)
      {
         Item & item = m_itema.get_item((int) m_iCreateImageListStep);

         ///IShellFolder * lpsf = m_pshellfolder;
         item.m_iImage = System.shellimageset().GetImage(
            _GetWnd()->GetTopLevelParent()->_get_handle(),
            item.m_strPath,
            gen::international::utf8_to_unicode(item.m_strExtra),
            _shell::IconNormal);

         m_iCreateImageListStep++;

      }
      else
      {
         ::user::list::_001CreateImageList(column);
      }

      return true;
   }*/



} // namespace fs


