#include "framework.h"
#include "SimpleFileListInterface.h"


namespace filemanager
{

   SimpleFileListInterface::SimpleFileListInterface(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::user::form(papp),
      ::ca2::user::form(papp),
      ::user::form_list(papp),
      ::userbase::form_list(papp),
      ::user::scroll_view(papp),
      ::user::list(papp),
      ::fs::list_interface(papp),
      ::fs::list(papp),
      ::userbase::view(papp),
      m_gdibuffer(papp),
      m_mutex(papp)
   {
      m_iAnimate = 0;
      m_bRestartCreateImageList = false;
      m_bStatic = false;
      m_bPendingSize = false;
      m_pcreateimagelistthread = NULL;
   }

   SimpleFileListInterface::~SimpleFileListInterface()
   {

   }




   void SimpleFileListInterface::_017Browse(const char * lpcsz)
   {
      _001ClearSelection();

      m_scrollinfo.m_ptScroll = m_scrollinfo.m_rectMargin.top_left();

      m_strPath = lpcsz;

      if(GetFileManagerItem().m_strPath.is_empty())
      {
         m_strPath.Empty();
         _017UpdateList(m_strPath);
      }
      else
      {
         string str(lpcsz);
         /*if(str.Right(4) == ".zip")
         {
            _017UpdateZipList(str, lpszExtra);
            goto zipDone;
         }*/
         _017UpdateList(str);
      }
//   zipDone:;
   }

   void SimpleFileListInterface::_017UpdateList(const char * lpcsz)
   {
/*      UNREFERENCED_PARAMETER(lpcsz);
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

      m_straFileSize.remove_all();
      ::fs::list_item item;
      get_fs_list_data()->m_itema.clear(NULL);
      _001OnUpdateItemCount();*/
      if(m_bStatic)
      {

         ::fs::list_item item;

         stringa stra;

         GetFileManager()->data_get(GetFileManager()->get_filemanager_data()->m_ptemplate->m_dataidStatic, ::gen::system::idEmpty, stra);

         get_fs_list_data()->m_itema.SetItemCount(stra.get_size());

         for(int32_t i = 0; i < stra.get_size(); i++)
         {

            item.m_flags.unsignalize_all();

            if(Application.dir().is(stra[i]))
            {
               item.m_flags.signalize(::fs::FlagFolder);
            }
            else
            {
            }

            string strPath = stra[i];
            string strName = System.file().title_(strPath);


            item.m_iImage = -1;
            item.m_strPath = strPath;
            item.m_strName = strName;

            get_fs_list_data()->m_itema.SetItemAt(i, item);

         }

         _001OnUpdateItemCount();

         return;

      }
      /*


      string strParent = lpcsz;
//      ULONG ulRet;
//      STRRET strretDisplayName;
//      HRESULT hr;
      uint32_t dwTimeIn;
      uint32_t dwTimeOut;

      dwTimeIn = get_tick_count();

      int32_t iMaxSize;
      iMaxSize = 1000;

      int32_t iSize;
      iSize = 0;

      m_itema.SetItemCount(iMaxSize);

      m_straStrictOrder.remove_all();

      stringa straPath;
      stringa straTitle;
      if(strlen(lpcsz) == 0)
      {
         System.dir().root_ones(straPath);
         straTitle = straPath;
      }
      else
      {
         System.dir().ls(lpcsz, &straPath, & straTitle);
      }

      for(int32_t i = 0; i < straPath.get_size(); i++)
      {
         item.m_flags.unsignalize_all();
         if(Application.dir().is(straPath[i]))
         {
            item.m_flags.signalize(filemanager::FlagFolder);
         }
         else
         {
         }
         item.m_iImage = -1;
         item.m_strPath = straPath[i];
         item.m_strName = straTitle[i];
         m_straStrictOrder.add(straPath[i]);

         m_itema.SetItemAt(iSize, item);
         iSize++;
         if(iSize >= iMaxSize)
         {
            iMaxSize += 1000;
            m_itema.SetItemCount(iMaxSize);
         }
      }
      m_itema.SetItemCount(iSize);



      //iaDisplayToStrict

      dwTimeOut = get_tick_count();

      TRACE("timeIn%d\n", dwTimeIn);
      TRACE("timeOut%d\n", dwTimeIn);
      TRACE("timeDelta%d\n", dwTimeOut - dwTimeIn);


      _001OnUpdateItemCount();

      if(m_eview == ViewIcon)
      {
            // primeiro, todos System arquivos que foram removidos
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
  /*       for(index strictNew = 0; strictNew < m_straStrictOrder.get_count(); strictNew++)
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
         m_itema.Arrange(ArrangeByName);
      }

      _001CreateImageList();

      _001RedrawWindow();

      file_size_add_request(true);
      for(int32_t i = 0; i < m_itema.get_item_count(); i++)
      {
         pset->m_table.add_request(m_itema.get_item(i).m_strPath);
      }*/
    /*  if(m_eview == ViewIcon)
      {
         data_set(
            data_get_current_sort_id(),
            string(data_get_current_list_layout_id()) + ".straStrictOrder",
            m_straStrictOrder);
         m_iconlayout.m_iaDisplayToStrict = iaDisplayToStrictNew;
         data_set_DisplayToStrict();
      } */

      return ::fs::list::_017UpdateList(lpcsz);


   }


   void SimpleFileListInterface::_017UpdateZipList(const char * lpcsz)
   {
/*      ::fs::list_item item;

      get_fs_list_data()->m_itema.clear(NULL, NULL);
      _001OnUpdateItemCount();

      string szPath(lpcsz);
      string wstrExtra(lpszExtra);
      string wstrExtraPath;
      string wstrItemExtra;

      int32_t iFind;
      gen::filesp spfile(get_app());

      //spfile->open(szPath, ::gen::file::mode_read | ::gen::file::type_binary);

      base_array < gen::memory_file, gen::memory_file & > filea;
      _vmszipFile zipfile;

      zipfile.m_pfile = &file;

      unzFile pf = _vmszipApi::unzipOpen(&zipfile);

      base_array < gen::memory_file, gen::memory_file & > filea;
      int32_t iStart = 0;
      int32_t iFind;
      while((iFind  = wstrExtra.find(L".zip:", iStart)) >= 0)
      {
         filea.add(gen::memory_file());
         pf->dump(filea.last_element(), wstrExtra.Mid(iStart + 5, iFind - iStart + 5));
         iStart = iFind + 1;
      }*/


  /*    stringa wstraItem;

      string str;

      str = szPath;
      str += L":" + wstrExtra;
      str = str.Mid(0, str.reverse_find(".zip:") + 4);

      zip::Util(get_app()).ls(str, false, &wstraItem);

      string wstrFolder;
      stringa wstraFolder;
      string wstrItem;
      for(int32_t i = 0; i < wstraItem.get_size(); i++)
      {
         wstrItem = wstraItem[i];



         wstrExtraPath = wstrItem;

         // ignore this file if its not in the Extra sub folder
         if(wstrExtraPath.Left(wstrExtra.get_length()) != wstrExtra ||
            wstrExtraPath == wstrExtra)
            continue;

         wstrItemExtra = wstrExtraPath.Mid(wstrExtra.get_length());

         item.m_flags.unsignalize_all();

         iFind = wstrItemExtra.find("/");
         if(iFind > 0)
         {
            wstrFolder = wstrItemExtra.Left(iFind);
            if(wstraFolder.contains(wstrFolder))
               continue;
            wstraFolder.add(wstrFolder);
            item.m_flags.signalize(filemanager::FlagFolder);
            item.m_strPath    = szPath;
            item.m_iImage     = -1;
            item.m_strName    = wstrFolder;
            item.m_strExtra   = wstrExtra + wstrFolder + "/";
         }
         else
         {
            item.m_strPath    = szPath;
            item.m_iImage     = -1;
            item.m_strName    = wstrItemExtra;
            item.m_strExtra   = wstrExtraPath;
            if(!item.m_strExtra.Right(4).CompareNoCase(".zip"))
            {
               item.m_strExtra += ":";
            }
         }

         item.m_flags.signalize(FlagInZip);
         m_itema.add_item(item);
      }
      _001OnUpdateItemCount();
      _001CreateImageList();*/


      return ::fs::list::_017UpdateZipList(lpcsz);

   }

   void SimpleFileListInterface::_001CreateImageList()
   {

      icon_key iconkey;
      icon icon;

#ifdef WINDOWSEX
      for(POSITION pos = m_iconmap.get_start_position();
         pos != NULL;
         m_iconmap.get_next_assoc(pos, iconkey, icon))
      {
         DestroyIcon(icon.m_hicon);
      }
#endif

      m_iCreateImageListStep = 0;
      m_bCreateImageList = true;
      if(m_pcreateimagelistthread == NULL)
      {
         m_pcreateimagelistthread = new create_image_list_thread(get_app());
         m_pcreateimagelistthread->m_plist = this;
         m_pcreateimagelistthread->begin();
      }
   }

   SimpleFileListInterface::create_image_list_thread::create_image_list_thread(::ca::application * papp) :
      ca(papp),
      thread(papp)
   {
   }

   int32_t SimpleFileListInterface::create_image_list_thread::run()
   {
      int32_t iStepSetCount = 84;
      int32_t iStepSetSleep = 23;
      while(get_run())
      {
         int32_t i = iStepSetCount;
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
      synch_lock lock(m_plist->m_pthread->m_pthread);
      m_plist->m_pcreateimagelistthread = NULL;
      return 0;

   }

   bool SimpleFileListInterface::_001CreateImageListStep()
   {

      if(m_iCreateImageListStep < 0 || m_iCreateImageListStep >= get_fs_list_data()->m_itema.get_count())
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
         || m_iCreateImageListStep >= get_fs_list_data()->m_itema.get_count())
      {
         return false;
      }

      ::user::list_column * pcolumn = m_columna._001GetBySubItem(m_iNameSubItem);

      if(pcolumn != NULL && pcolumn->m_iSubItem == m_iNameSubItem)
      {
         ::fs::list_item & item = get_fs_list_data()->m_itema.get_item((int32_t) m_iCreateImageListStep);

         ///IShellFolder * lpsf = m_pshellfolder;
         item.m_iImage = System.user().shellimageset().GetImage(
            _GetWnd()->GetTopLevelParent()->get_handle(),
            item.m_strPath,
            NULL,
            _shell::IconNormal,
            get_document()->set().is_dir(item.m_strPath));

         m_iCreateImageListStep++;

      }
      else
      {
         ::user::list::_001CreateImageList(pcolumn);
      }

      return true;
   }

   void SimpleFileListInterface::_001InsertColumns()
   {
      class user::control::descriptor control;


      if(GetFileManager()->get_filemanager_data()->m_bIconView)
      {
         m_eview = ViewIcon;
      }

       ::user::list_column column;

      int32_t iCount = 0;

      FileManagerFileListCallback * pcallback =
         GetFileManager()->get_filemanager_data()->m_ptemplate->m_pfilelistcallback;

      if(pcallback != NULL)
      {
         iCount = pcallback->GetActionButtonCount();
      }

      index i;
      for(i = 0; i < iCount; i++)
      {
         control.m_bTransparent = true;
         control.set_type(user::control::type_button);
         control.m_typeinfo = System.type_info < BaseButtonControl > ();
         control.m_id = 1000 + i;
         control.add_function(user::control::function_action);
         index iControl = _001AddControl(control);

         column.m_iWidth               = 18;
         column.m_iSubItem             = i;
         column.m_iControl             = iControl;
         column.m_bCustomDraw          = true;
         column.m_bEditOnSecondClick   = true;
         column.m_pil                  = pcallback->GetActionButtonImageList(i);
         _001AddColumn(column);
      }


      if(GetFileManager()->get_filemanager_data()->m_bListSelection)
      {
         column.m_iWidth               = GetFileManager()->get_filemanager_data()->m_iIconSize;
         column.m_iSubItem             = i;
         //column.m_bIcon                = true;
         column.m_sizeIcon.cx          = GetFileManager()->get_filemanager_data()->m_iIconSize;
         column.m_sizeIcon.cy          = GetFileManager()->get_filemanager_data()->m_iIconSize;
         column.m_iControl             = -1;
         column.m_datakey = "FILE_MANAGER_ID_FILE_NAME";
         column.m_bEditOnSecondClick   = false;
         if(GetFileManager()->get_filemanager_data()->m_iIconSize >= 48)
         {
            column.m_pil                  = System.user().shellimageset().GetImageList48();
         }
         else
         {
            column.m_pil                  = System.user().shellimageset().GetImageList16();
         }
         _001AddColumn(column);
         m_iSelectionSubItem = i;

         i++;
      }
      else
      {
         m_iSelectionSubItem = -1;
      }

      control.set_type(user::control::type_edit_plain_text);
      control.m_dataid = "FILE_MANAGER_ID_FILE_NAME";
      //pcontrol->descriptor().m_id = _vms::FILE_MANAGER_ID_FILE_NAME;
      control.set_data_type(user::control::DataTypeString);
      control.add_function(user::control::function_vms_data_edit);
      //control.m_typeinfo = System.type_info < simple_edit_plain_text > ();
      control.m_typeinfo.name("");
      control.m_iSubItem = i;
      control.m_id = 1000 + i;
      index iControl =  _001AddControl(control);



      column.m_iSubItem             = i;
      m_iNameSubItem = i;
      if(GetFileManager()->get_filemanager_data()->m_bListText)
      {
         m_iNameSubItemText = i;
         column.m_iWidth               = 500;
      }
      else
      {
         m_iNameSubItemText = -1;
         column.m_iWidth               = GetFileManager()->get_filemanager_data()->m_iIconSize;
      }
      get_fs_list_data()->m_iNameSubItemText = m_iNameSubItemText;
      //column.m_bIcon                = true;
      column.m_sizeIcon.cx          = GetFileManager()->get_filemanager_data()->m_iIconSize;
      column.m_sizeIcon.cy          = GetFileManager()->get_filemanager_data()->m_iIconSize;
      column.m_iControl             = iControl;
      column.m_datakey = "FILE_MANAGER_ID_FILE_NAME";
      column.m_bEditOnSecondClick   = true;
      if(GetFileManager()->get_filemanager_data()->m_iIconSize >= 48)
      {
         column.m_pilHover             = System.user().shellimageset().GetImageList48Hover();
         column.m_pil                  = System.user().shellimageset().GetImageList48();
      }
      else
      {
         column.m_pil                  = System.user().shellimageset().GetImageList16();
      }
      _001AddColumn(column);

      i++;

      if(GetFileManager()->get_filemanager_data()->m_bFileSize)
      {
         // file/directory size
         column.m_iWidth               = 100;
         column.m_iSubItem             = i;
         m_iSizeSubItem = i;
         column.m_sizeIcon.cx          = 0;
         column.m_sizeIcon.cy          = 0;
         column.m_pilHover             = NULL;
         column.m_pil                  = NULL;
         _001AddColumn(column);
      }

   }


   void SimpleFileListInterface::_001GetItemText(::user::list_item * pitem)
   {
      return ::fs::list::_001GetItemText(pitem);
      /*UNREFERENCED_PARAMETER(iListItem);
      if(iSubItem == m_iNameSubItemText)
      {
         str = get_fs_lim_itema.get_item(iItem).m_strName;
         return true;
      }
      else if(iSubItem == m_iSizeSubItem)
      {
         bool bPendingSize = false;

         bool bGet;
         bGet = System.get_fs_size(str, m_itema.get_item(iItem).m_strPath, bPendingSize);
         if(bGet)
         {
            m_straFileSize.set_at_grow(iItem, str);
         }
         else
         {
            if(iItem < m_straFileSize.get_size())
            {
               str = m_straFileSize[iItem];
            }
         }
         if(bPendingSize)
         {
            schedule_file_size(m_itema.get_item(iItem).m_strPath);
            m_bPendingSize = true;
         }
         return true;
      }
      //else if(m_bStatic)
      //{
        // return ::user::list::_001GetItemText(str, iItem, iSubItem, iListItem);
      //}
      else
         return false;*/
   }

   void SimpleFileListInterface::_001GetItemImage(::user::list_item * pitem)
   {
      return ::fs::list::_001GetItemImage(pitem);
/*      if(iSubItem == m_iSelectionSubItem)
      {
         if(m_rangeSelection.HasItem(iItem))
         {
            return 1;
         }
         else
         {
            return 0;
         }
      }
      else if(iSubItem == m_iNameSubItem)
      {
         return m_itema.get_item(iItem).m_iImage;
      }
      else
         return ::user::list::_001GetItemImage(iItem, iSubItem, iListItem);*/

   }

   /*UINT c_cdecl SimpleFileListInterface::_017ThreadProcCreateImageList(LPVOID lpParameter)
   {
      try
      {
         ::SetThreadPriority(
               ::GetCurrentThread(),
               THREAD_PRIORITY_ABOVE_NORMAL);

         SimpleFileListInterface * plist =
            (SimpleFileListInterface *) lpParameter;
         plist->m_bCreateImageList = true;
         ::user::list_column & column = plist->m_columna.GetBySubItem(1);
   //      if(column.m_pil->GetSafeHandle() != NULL)
   //         column.m_pil->DeleteImageList();
         plist->_001CreateImageList(column);
         return 0;
      }
      catch(...)
      {
         return 1;
      }
   }*/


   bool SimpleFileListInterface::TwiHasTranslucency()
   {
      return ::user::list::TwiHasTranslucency() && !m_bCreateImageListRedraw;
   }


   void SimpleFileListInterface::GetSelectedFilePath(stringa & base_array)
   {
      Range range;

      _001GetSelection(range);

      string str;
//      HRESULT hr;
      for(index i = 0; i < range.get_item_count(); i++)
      {
         ItemRange & itemrange = range.ItemAt(i);
         for(index iItem = itemrange.GetLBound() ; iItem <= itemrange.GetUBound(); iItem ++)
         {
            index iStrict;
            if(m_eview == ViewIcon)
            {
               iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
            }
            else
            {
               iStrict = m_listlayout.m_iaDisplayToStrict[iItem];
            }
            ::fs::list_item & item = get_fs_list_data()->m_itema.get_item(iStrict);
            if(!item.IsFolder())
            {
               base_array.add(item.m_strPath);
            }
         }
      }

   }


   void SimpleFileListInterface::_017UpdateList()
   {

      if(GetFileManager()->get_filemanager_data()->m_bSetBergedgeTopicFile)
      {
         SetTimer(198477, 230, NULL);
      }


      ::fs::list_item folder;

//      HRESULT hr;
      string strPath = GetFileManagerItem().m_strPath;
//      LPMALLOC lpmalloc = NULL;
//      IShellFolder * lpsfDesktop;


      if(strPath.is_empty())
      {
         _017UpdateList(strPath);
      }
      else
      {
         _017UpdateList(strPath);

      }



   }

   /*void SimpleFileListInterface::_017OneLevelUp()
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

   void SimpleFileListInterface::_001OnMainPostMessage(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::base, pbase, pobj)
      switch(pbase->m_wparam)
      {
      case MessageMainPostCreateImageListItemStepSetRedraw:
         {
            uint32_t dwNow = get_tick_count();
            if(dwNow - m_dwLastRedraw > 284)
            {
               m_dwLastRedraw = dwNow;
               _001RedrawWindow();
            }
         }
         break;
      case MessageMainPostCreateImageListItemRedraw:
         {
            _001RedrawWindow();
         }
         break;
      }
      pbase->set_lresult(0);
      pbase->m_bRet = true;
   }

   ::fs::item & SimpleFileListInterface::GetFileManagerItem()
   {
      return GetFileManager()->get_item();
   }

   void SimpleFileListInterface::_017Synchronize()
   {
      ::ca::data::writing writing(m_pdata);
      _001HideEditingControls();
      _017Browse(GetFileManagerItem().m_strPath);
   }

   void SimpleFileListInterface::install_message_handling(::gen::message::dispatch *pinterface)
   {
      ::user::form_list::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(MessageMainPost, pinterface,  this, &SimpleFileListInterface::_001OnMainPostMessage);
      IGUI_WIN_MSG_LINK(WM_HSCROLL, pinterface, this, &SimpleFileListInterface::_001OnHScroll);
      IGUI_WIN_MSG_LINK(WM_VSCROLL, pinterface, this, &SimpleFileListInterface::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &SimpleFileListInterface::_001OnShowWindow);

   }

   void SimpleFileListInterface::_001OnDraw(::ca::graphics *pdc)
   {
      if(m_iAnimate <= 0)
      {
         // Normal Drawing
         ::user::form_list::_001OnDraw(pdc);
      }
      else
      {
         // Animation Drawing
         rect rectClipBox;
         pdc->GetClipBox(rectClipBox);
         class imaging & imaging = Application.m_visual.imaging();
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
      }

   }

   void SimpleFileListInterface::StartAnimation()
   {
      m_iAnimate = 1;
   }

   void SimpleFileListInterface::TakeAnimationSnapshot()
   {
      m_iAnimate = 1;
      ::user::list::_001OnDraw(m_gdibuffer.GetBuffer());
   }

   void SimpleFileListInterface::_017PreSynchronize()
   {
      //TakeAnimationSnapshot();
   }





   void SimpleFileListInterface::_017OpenSelected(bool bOpenFile)
   {
      ::fs::item_array itema;
      index iItemRange, iItem;
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
            index iStrict;
            if(m_eview == ViewIcon)
            {
               iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
            }
            else
            {
               iStrict = m_listlayout.m_iaDisplayToStrict[iItem];
            }
            if(get_fs_list_data()->m_itema.get_item(iStrict).IsFolder())
            {
               _017OpenFolder(cast < ::fs::item > (get_fs_list_data()->m_itema.get_item(iStrict)));
               break;
            }
            else
            {
               ::fs::item item;
               itema.add(cast < ::fs::item > (get_fs_list_data()->m_itema.get_item(iStrict)));
            }
         }
      }
      if(bOpenFile && itema.get_size() > 0)
      {
         _017OpenFile(itema);
      }
      _001ClearSelection();
   }

   void SimpleFileListInterface::_017OpenContextMenuSelected()
   {
      ::fs::item_array itema;
      index iItemRange, iItem;
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
            if(iItem >= get_fs_list_data()->m_itema.get_count())
               continue;
            index iStrict;
            if(m_eview == ViewIcon)
            {
               iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
            }
            else
            {
               iStrict = m_listlayout.m_iaDisplayToStrict[iItem];
            }
            if(get_fs_list_data()->m_itema.get_item(iStrict).IsFolder())
            {
               _017OpenContextMenuFolder(cast < ::fs::item > (get_fs_list_data()->m_itema.get_item(iStrict)));
               break;
            }
            else
            {
               itema.add(cast < ::fs::item > (get_fs_list_data()->m_itema.get_item(iStrict)));
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

   void SimpleFileListInterface::_017OpenContextMenuFolder(const ::fs::item &item)
   {
      UNREFERENCED_PARAMETER(item);
   }

   void SimpleFileListInterface::_017OpenContextMenuFile(const ::fs::item_array &itema)
   {
      UNREFERENCED_PARAMETER(itema);
   }

   void SimpleFileListInterface::_017OpenContextMenu()
   {
   }

   void SimpleFileListInterface::_017OpenFolder(const ::fs::item &item)
   {
      UNREFERENCED_PARAMETER(item);
      ASSERT(FALSE);
   }

   void SimpleFileListInterface::_017OpenFile(const ::fs::item_array &itema)
   {
      UNREFERENCED_PARAMETER(itema);
      ASSERT(FALSE);
   }

   void SimpleFileListInterface::_001OnInitializeForm(user::control * pcontrol)
   {
      ASSERT(pcontrol != NULL);
      if(pcontrol == NULL)
         return;

      FileManagerFileListCallback * pcallback =
         GetFileManager()->get_filemanager_data()->m_ptemplate->m_pfilelistcallback;

      BaseButtonControl * pbutton = dynamic_cast < BaseButtonControl * > (pcontrol);
      if(pcallback != NULL && pbutton != NULL)
      {
         pcallback->InitializeActionButton(((int32_t) pcontrol->descriptor().m_id) - 1000, pbutton);
      }
   }

   void SimpleFileListInterface::_001OnButtonAction(
      user::control * pcontrol)
   {
      FileManagerFileListCallback * pcallback =
         GetFileManager()->get_filemanager_data()->m_ptemplate->m_pfilelistcallback;

      if(pcallback != NULL)
      {
         ::fs::item item;
         index iItem = pcontrol->GetEditItem();
         index iStrict;
         if(m_eview == ViewIcon)
         {
            iStrict = m_iconlayout.m_iaDisplayToStrict.get_b(iItem);
         }
         else
         {
            iStrict = m_listlayout.m_iaDisplayToStrict[iItem];
         }
         pcallback->OnButtonAction((int32_t) pcontrol->descriptor().m_id - 1000, cast < ::fs::item > (get_fs_list_data()->m_itema.get_item(iStrict)));
      }
   }

   void SimpleFileListInterface::GetSelected(::fs::item_array &itema)
   {
      index iItemRange, iItem;
      Range range;
      _001GetSelection(range);
      index_array iaItem;
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
            if(iItem < get_fs_list_data()->m_itema.get_count() && !iaItem.contains(iItem))
            {
               iaItem.add(iItem);
               index iStrict;
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
               itema.add(cast < ::fs::item > (get_fs_list_data()->m_itema.get_item(iStrict)));
            }
         }
      }
   }

   void SimpleFileListInterface::_001OnVScroll(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::scroll, pscroll, pobj)
      m_iCreateImageListStep = pscroll->m_nPos;
      m_bRestartCreateImageList = true;
      pobj->m_bRet = false;
   }

   void SimpleFileListInterface::_001OnHScroll(gen::signal_object * pobj)
   {
      pobj->m_bRet = false;
   }

   count SimpleFileListInterface::_001GetItemCount()
   {
      return get_fs_list_data()->m_itema.get_count();
   }

   void SimpleFileListInterface::add_item(const char * pszPath, const char * pszTitle)
   {
      ::fs::list_item item;
      item.m_strPath = pszPath;
      item.m_strName = pszTitle;
      if(Application.dir().is(pszPath))
      {
         item.m_flags.signalize(::fs::FlagFolder);
      }
      get_fs_list_data()->m_itema.add_item(item);
      _001OnUpdateItemCount();
   }


   image_list * SimpleFileListInterface::GetActionButtonImageList(index i)
   {
      if(i == 0)
      {
         return System.user().shellimageset().GetImageList16();
      }
      return NULL;
   }

   void SimpleFileListInterface::_001OnFileRename(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      user::control * pcontrol = _001GetControlBySubItem(m_iNameSubItem);
      Range range;
      _001GetSelection(range);
      if(range.get_item_count() == 1 && range.ItemAt(0).GetLBound() == range.ItemAt(0).GetUBound())
      {
         _001PlaceControl(pcontrol);
      }
   }

   void SimpleFileListInterface::_001OnUpdateFileRename(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      Range range;
      _001GetSelection(range);
      pcmdui->m_pcmdui->Enable(
         range.get_item_count() == 1
         && range.ItemAt(0).GetLBound() == range.ItemAt(0).GetUBound());
      pobj->m_bRet = true;
   }

   void SimpleFileListInterface::_001OnShowWindow(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::gen::message::show_window, pshow, pobj)

      db_server * pcentral = dynamic_cast < db_server * > (&System.m_simpledb.db());
      if(pcentral == NULL)
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

   void SimpleFileListInterface::file_size_add_request(bool bClear)
   {
      UNREFERENCED_PARAMETER(bClear);
      db_server * pcentral = dynamic_cast < db_server * > (&System.m_simpledb.db());
      if(pcentral == NULL)
         return;
      DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;
      single_lock sl(pset->m_table.m_pmutex, TRUE);

//      int64_t iSize;
//      bool bPending;
      for(int32_t i = 0; i < get_fs_list_data()->m_itema.get_count(); i++)
      {
         //pset->get_cache_fs_size(iSize, m_itema.get_item(i).m_strPath, bPending);
      }
   }


   void SimpleFileListInterface::_001InitializeFormPreData()
   {
      ::filemanager::data * pdata = GetFileManager()->get_filemanager_data();
      pdata->m_pcallback->OnFileManagerInitializeFormPreData(pdata, GetDlgCtrlId(), this);
   }


   bool SimpleFileListInterface::query_drop(index iDisplayDrop, index iDisplayDrag)
   {
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
            return get_fs_list_data()->m_itema.get_item(strict).IsFolder();
         }
      }
      return false;
   }


   bool SimpleFileListInterface::do_drop(index iDisplayDrop, index iDisplayDrag)
   {
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
      if(strict >= 0 && get_fs_list_data()->m_itema.get_item(strict).IsFolder())
      {
         string strPath = get_fs_list_data()->m_itema.get_item(strictDrag).m_strPath;
         string strName = System.file().name_(strPath);
         System.file().move(
            System.dir().path(get_fs_list_data()->m_itema.get_item(strict).m_strPath, strName),
            strPath);
         _017Synchronize();
      }
      else
      {
         ::user::list::do_drop(iDisplayDrop, iDisplayDrag);
      }
      return true;
   }

   COLORREF SimpleFileListInterface::get_background_color()
   {
      if(GetFileManager() != NULL && GetFileManager()->get_filemanager_data()->is_saving())
      {
         return RGB(255, 177, 84);
      }
      else
      {
         return RGB(200, 255, 255);
      }
   }


} // namespace filemanager
