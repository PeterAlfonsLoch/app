#include "StdAfx.h"


namespace filemanager
{


   SimpleFolderTreeInterface::SimpleFolderTreeInterface(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::fs::tree(papp)
   {
      m_pdataitemCreateImageListStep = NULL;

      m_iAnimate = 0;
      //   IconKey iconkey;
      //iconkey.m_strExtension = "";
      //iconkey.m_strPath = "";
      //iconkey.m_iIcon = 0;
      //SHFILEINFO shfi;
      //SHGetFileInfo(
      // "foo",
      //FILE_ATTRIBUTE_DIRECTORY,
      //&shfi,
      //sizeof(shfi),
      //SHGFI_USEFILEATTRIBUTES
      //| SHGFI_ICON
      //| SHGFI_SMALLICON);
      //icon icon;
      //icon.m_hicon = shfi.hIcon;
      //icon.m_iImage = m_pimagelist->add(icon.m_hicon);

      //   m_pimagelist = NULL;


      //   m_iDefaultImage = icon.m_iImage;
      //   m_iconmap.set_at(iconkey, icon);

      //   iconkey.m_strExtension = "";
      // iconkey.m_strPath = "";
      //iconkey.m_iIcon = 1;
      /*SHGetFileInfo(
      "foo",
      FILE_ATTRIBUTE_DIRECTORY,
      &shfi,
      sizeof(shfi),
      SHGFI_USEFILEATTRIBUTES
      | SHGFI_ICON
      | SHGFI_SMALLICON
      | SHGFI_OPENICON);
      icon.m_hicon = shfi.hIcon;
      icon.m_iImage = m_pimagelist->add(icon.m_hicon);
      m_iDefaultImageSelected = icon.m_iImage;
      m_iconmap.set_at(iconkey, icon);*/


      m_bDelayedListUpdate = false;

   }

   SimpleFolderTreeInterface::~SimpleFolderTreeInterface()
   {

   }



   void SimpleFolderTreeInterface::_017EnsureVisible(const char * lpcsz)
   {
      stringa stra;

      get_document()->set().get_ascendants_path(lpcsz, stra);

      m_straUpdatePtrFilter = stra;

      //for(int i = stra.get_size() - 1; i >= 0; i--)
      for(int i = 0; i < stra.get_size(); i++)
      {
         string strAscendant = stra[i];
         ::ex1::tree_item * pitem = find_item(strAscendant);
         if(pitem == NULL)
         {
            string str;
            str = strAscendant;
            if(i == 0)
            {
               _017UpdateList("", NULL, 1);
            }
            else
            {
               get_document()->set().eat_end_level(str, 1);
               _017UpdateList(str, NULL, 1);
            }
         }
         pitem = find_item(strAscendant);
         if(pitem == NULL)
            break;

         if(!(pitem->m_dwState & ::ex1::tree_item_state_expanded))
         {
            _001ExpandItem(pitem, true, false, false);
         }
      }


      m_straUpdatePtrFilter.remove_all();

      {

         single_lock sl(&m_mutexMissinUpdate, TRUE);

         m_straMissingUpdate = stra;

      }

      _StartDelayedListUpdate();

      ::ex1::tree_item * pitem = find_item(lpcsz);

      if(pitem != NULL)
      {
         index iLevel = 0;

         index iIndex = get_proper_item_index(pitem, &iLevel);

         index iLastVisibleIndex = (index) (m_scrollinfo.m_ptScroll.y + _001GetVisibleItemCount() - 5);

         index iObscured; // obscured proper descendants
         iObscured = iIndex  - iLastVisibleIndex;

         if(iObscured > 0)
         {
            int iNewScroll = (int) (m_scrollinfo.m_ptScroll.y + iIndex * _001GetItemHeight());
            m_scrollinfo.m_ptScroll.y = max(iNewScroll, 0);
         }
      }
      layout();
      _001RedrawWindow();
   }

   ::ex1::tree_item * SimpleFolderTreeInterface::find_item(const char * lpcsz)
   {
      return find_absolute(lpcsz);
   }

   void SimpleFolderTreeInterface::_017Browse(const char * lpcsz, bool bForceUpdate)
   {
      if(!bForceUpdate)
      {
         ::ex1::tree_item * pitem = find_item(lpcsz);
         if(pitem != NULL)
         {
            if(is_selected(pitem))
               return;
            if(is_selected(pitem->m_pparent))
            {
               pitem->set_selection();
               return;
            }
         }
      }

      single_lock slBrowse(&m_csBrowse, TRUE);

      if(strlen(lpcsz) == 0)
      {
         _017UpdateList("", get_base_item(), 1);
      }

      _017EnsureVisible(lpcsz);

      _001SelectItem(find_item(lpcsz));


      _StartCreateImageList();

   }

   void SimpleFolderTreeInterface::_017UpdateZipList(const char * lpcsz, ::ex1::tree_item * pitemParent, int iLevel)
   {
      index i;

      //         ::fs::tree_item * pitemChild;

      string szPath(lpcsz);

      string wstrExtraPath;
      string wstrItemExtra;

      index iFind;
      ex1::filesp spfile(get_app());

      //spfile->open(szPath, ::ex1::file::mode_read | ::ex1::file::type_binary);

      /*base_array < gen::memory_file, gen::memory_file & > filea;
      _vmszipFile zipfile;

      zipfile.m_pfile = &file;

      unzFile pf = _vmszipApi::unzipOpen(&zipfile);

      base_array < gen::memory_file, gen::memory_file & > filea;
      int iStart = 0;
      int iFind;
      while((iFind  = wstrExtra.find(L".zip:", iStart)) >= 0)
      {
      filea.add(gen::memory_file());
      pf->dump(filea.last_element(), wstrExtra.Mid(iStart + 5, iFind - iStart + 5));
      iStart = iFind + 1;
      }*/


      stringa wstraItem;
      stringa wstraChildItem;

      string str;

      str = szPath;
      str = str.Mid(0, str.reverse_find(".zip:") + 4);

      zip::Util().ls(get_app(), str, false, &wstraItem);

      string wstrFolder;
      stringa wstraFolder;
      string wstrItem;
      ex1::tree_item_ptr_array ptraRemove;
      pitemParent->get_children(ptraRemove);

      for(int i = 0; i < wstraItem.get_size(); i++)
      {
         wstrItem = wstraItem[i];

         ::fs::tree_item * pitemNew = new ::fs::tree_item;

         pitemNew->m_strPath = lpcsz;
         pitemNew->m_flags.signalize(::fs::FlagInZip);

         wstrExtraPath = wstrItem;

         // ignore this file if its not in the Extra sub folder
         /*            if(wstrExtraPath.Left(wstrExtra.get_length()) != wstrExtra ||
         wstrExtraPath == wstrExtra)
         continue;*/

         //            wstrItemExtra = wstrExtraPath.Mid(wstrExtra.get_length());

         pitemNew->m_flags.unsignalize_all();

         iFind = wstrItemExtra.find("/");
         if(iFind > 0)
         {
            wstrFolder = wstrItemExtra.Left(iFind);
            if(wstraFolder.find_first(wstrFolder) >= 0)
               continue;
            wstraFolder.add(wstrFolder);
            pitemNew->m_flags.signalize(::fs::FlagFolder);
            pitemNew->m_strPath   = szPath;
            pitemNew->m_iImage     = -1;
            pitemNew->m_strName   = wstrFolder;
         }
         else
         {
            pitemNew->m_strPath   = szPath;
            pitemNew->m_iImage     = -1;
            pitemNew->m_strName   = wstrItemExtra;
            string str;
            str = szPath + wstrExtraPath;
            if(zip::Util().IsUnzipable(get_app(), str))
            {
               pitemNew->m_flags.signalize(::fs::FlagFolder);
            }
         }
         if(pitemNew->m_flags.is_signalized(::fs::FlagFolder))
         {
            pitemNew->m_iImage         = m_iDefaultImage;
            pitemNew->m_iImageSelected = m_iDefaultImageSelected;
            //         item.m_flags.signalize(FlagInZip);
            ::ex1::tree_item  * pitem    = find_item(pitemNew->m_strPath);
            if(pitem == NULL)
            {
               pitem = insert_item(pitemNew, ex1::RelativeLastChild, pitemParent);
            }
            else
            {
               pitem = insert_item(pitemNew, ex1::RelativeReplace, pitem);
            }
            str = szPath;
            wstraChildItem.remove_all();
            if(zip::Util().HasSubFolder(get_app(), str))
            {
               pitem->m_dwState |= ::ex1::tree_item_state_expandable;
            }
            if(iLevel > 1)
            {
               _017UpdateZipList(pitemNew->m_strPath, pitem, iLevel - 1);
            }
         }
      }
      for( i = 0; i < ptraRemove.get_size(); i++)
      {
         delete_item(ptraRemove[i]);
      }
   }

   void SimpleFolderTreeInterface::_017UpdateList(const char * lpcsz, ::ex1::tree_item * pitemParent, int iLevel)
   {
      if(lpcsz == NULL)
         lpcsz = "";
      /*if(lpcsz == NULL)
      {
      if(zip::Util(get_app()).IsUnzipable(pitemParent->m_strPath))
      {
      _017UpdateZipList(lpcsz, NULL, pitemParent, iLevel - 1);
      }
      return;
      }*/

      m_strPath = lpcsz;

      if(pitemParent == NULL)
      {
         pitemParent =  get_base_item();
      }
      else if(get_base_item() == NULL)
      {
         m_pitem = pitemParent;
      }


      stringa straAscendants;

      ::ex1::tree_item * pitem;

      ::ex1::tree_item * pitemBase;

      ::fs::tree_item * pitemChild;

      string strNew;

      System.file().get_ascendants_path(lpcsz, straAscendants);

      pitemBase = get_base_item();

      for(int i = 0; i < straAscendants.get_count(); i++)
      {
         string strItem = straAscendants[i];
         strItem.trim("/\\");
         if(strItem.is_empty())
            continue;
         pitem = find_item(strItem);
         if(pitem == NULL)
         {
            pitem = find_item(strItem + "\\");
            if(pitem == NULL)
            {
               pitem = find_item(strItem + "/");
               if(pitem == NULL)
               {
                  pitem = find_item(strItem + "//");
                  if(pitem == NULL)
                  {
                     strItem.replace("\\", "/");
                     pitem = find_item(strItem);
                     if(pitem == NULL)
                     {
                        pitem = find_item(strItem + "/");
                     }
                  }
               }
            }
            
         }
         strNew.Empty();
         if(pitem != NULL)
         {
            pitemBase = pitem;
            continue;
         }
         else 
         {
            // pitem == NULL
            if(i == 0)
            {
               if(strItem[1] == ':')
               {
                  strNew = strItem + "\\";
               }
               else if(strItem.find(':') >= 0)
               {
                  strNew = strItem + "//";
               }
            }
            else
            {
               strNew = strItem;
            }
         }
         if(strNew.is_empty())
         {
            // error
            return;
         }

         pitemChild = new ::fs::tree_item;

         pitemChild->m_pdata = get_fs_tree_data();

         pitemChild->m_strPath = get_document()->set().dir_path(strNew, "");

         //if(m_straUpdatePtrFilter.find_first(straPath[i]) >= 0)
         //{
         //   continue;
         //}
         pitemChild->m_strName = System.file().name_(strNew);

         pitemChild->m_flags.signalize(::fs::FlagFolder);
         pitemChild->m_iImage = m_iDefaultImage;
         pitemChild->m_iImageSelected = m_iDefaultImageSelected;

         pitem = find_item(pitemChild->m_strPath);
         if(pitem != NULL)
         {
            //pitem = insert_item(pitemChild, ex1::RelativeReplace, pitem);
            // a refresh or a file monitoring event for folder deletion or creation should
            // the most precisely possible way reset this flag
            //pitemChild->m_flags.signalize(::fs::FlagHasSubFolderUnknown);
            // error
            return;
         }
         else
         {
            pitem = insert_item(pitemChild, ex1::RelativeLastChild, pitemBase);
         }

         if(pitemChild->m_flags.is_signalized(::fs::FlagHasSubFolder))
         {
            pitem->m_dwState |= ::ex1::tree_item_state_expandable;
         }


         pitemBase = pitem;

         //if(iLevel > 1)
         //{
           // _017UpdateList(pitemChild->m_strPath,  pitem, iLevel - 1);
         //}

      }


      pitemParent = pitemBase;



      if(GetFileManager() != NULL && GetFileManager()->get_filemanager_data()->m_ptreeFileTreeMerge != NULL
         && !(dynamic_cast < user::tree * > (GetFileManager()->get_filemanager_data()->m_ptreeFileTreeMerge))->m_treeptra.contains(this))
      {
         GetFileManager()->get_filemanager_data()->m_ptreeFileTreeMerge->merge(this);
      }

      ::fs::tree_item * pitemFolder = NULL;

      string strRawName1 = typeid(*pitemParent).raw_name();
      string strRawName2 = typeid(::fs::tree_item).raw_name();
      if(strRawName1 == strRawName2)
      {
         pitemFolder = (::fs::tree_item *) pitemParent;
      }


      if(pitemFolder != NULL && pitemFolder->m_flags.is_signalized(::fs::FlagHasSubFolderUnknown))
      {
         if(get_document()->set().has_subdir(pitemFolder->m_strPath))
         {
            pitemFolder->m_flags.signalize(::fs::FlagHasSubFolder);
         }
         pitemFolder->m_flags.unsignalize(::fs::FlagHasSubFolderUnknown);
      }

      stringa straChildItem;
      string str;

      DWORD dwTimeIn;
      DWORD dwTimeOut;

      dwTimeIn = GetTickCount();

      int iMaxSize;
      iMaxSize = 1000;

      int iSize;
      iSize = 0;

      int iChildCount;

      iChildCount = 0;

      stringa straPath;
      stringa straTitle;
      if(strlen(lpcsz) == 0)
      {
         get_document()->set().root_ones(straPath);
         straTitle = straPath;
      }
      else
      {
         get_document()->set().ls(lpcsz, &straPath, & straTitle);
      }

      pitem = pitemParent->m_pchild;

      stringa straNew = straPath;

      straNew.trim_right("/\\");

      ex1::tree_item_ptr_array ptraRemove;

      while(pitem != NULL)
      {

         string strPathOld = ((::fs::tree_item *) pitem->m_pitemdata)->m_strPath;
         
         strPathOld.trim_right("/\\");

         if(!straNew.contains(strPathOld) || !GetFileManager()->get_fs_data()->is_dir(strPathOld))
         {
            ptraRemove.add(pitem);
         }

         pitem = pitem->m_pnext;

      }

      for(int j = 0; j < ptraRemove.get_size(); j++)
      {
         delete_item(ptraRemove[j]);
      }


//      ex1::tree_item_ptr_array ptraRemove;



      int i;

      for(i = 0; i < straPath.get_size(); i++)
      {

         pitemChild = new ::fs::tree_item;

         iChildCount++;

         pitemChild->m_pdata = get_fs_tree_data();

         pitemChild->m_strPath = get_document()->set().dir_path(straPath[i], "");

         //if(m_straUpdatePtrFilter.find_first(straPath[i]) >= 0)
         //{
         //   continue;
         //}
         pitemChild->m_strName = straTitle[i];
         if(!get_document()->set().is_dir(straPath[i]))
         {
            if(zip::Util().IsUnzipable(get_app(), pitemChild->m_strPath))
            {
               pitemChild->m_flags.signalize(::fs::FlagFolder);


               pitemChild->m_iImage = m_iDefaultImage;
               pitemChild->m_iImageSelected = m_iDefaultImageSelected;
               pitemChild->m_flags.signalize(::fs::FlagInZip);

               pitem = find_item(pitemChild->m_strPath);
               if(pitem != NULL)
               {
                  pitem = insert_item(pitemChild, ex1::RelativeReplace, pitem);
               }
               else
               {
                  pitem = insert_item(pitemChild, ex1::RelativeLastChild, pitemParent);
               }

               if(zip::Util().HasSubFolder(get_app(), pitemChild->m_strPath))
               {
                  pitem->m_dwState |= ::ex1::tree_item_state_expandable;
               }

               if(iLevel > 1)
               {
                  _017UpdateZipList(pitemChild->m_strPath, pitem, iLevel - 1);
               }

            }
            else
            {
               continue;
            }
         }

         /*      if(File::has_subfolder(straPath[i]))
         {
         item.m_flags.signalize(filemanager::FlagHasSubFolder);
         }*/

         pitemChild->m_flags.signalize(::fs::FlagFolder);
         pitemChild->m_iImage = m_iDefaultImage;
         pitemChild->m_iImageSelected = m_iDefaultImageSelected;

         pitem = find_item(pitemChild->m_strPath);
         if(pitem != NULL)
         {
            pitem = insert_item(pitemChild, ex1::RelativeReplace, pitem);
            // a refresh or a file monitoring event for folder deletion or creation should
            // the most precisely possible way reset this flag
            pitemChild->m_flags.signalize(::fs::FlagHasSubFolderUnknown);
         }
         else
         {
            pitem = insert_item(pitemChild, ex1::RelativeLastChild, pitemParent);
         }

         if(pitemChild->m_flags.is_signalized(::fs::FlagHasSubFolder))
         {
            pitem->m_dwState |= ::ex1::tree_item_state_expandable;
         }

         if(iLevel > 1)
         {
            _017UpdateList(pitemChild->m_strPath,  pitem, iLevel - 1);
         }

      }

      arrange(::fs::arrange_by_name);

      if(iChildCount == 0)
      {
         pitemParent->m_dwState &= ~::ex1::tree_item_state_expandable;
      }

      dwTimeOut = GetTickCount();

      TRACE("timeIn%d\n", dwTimeIn);
      TRACE("timeOut%d\n", dwTimeIn);
      TRACE("timeDelta%d\n", dwTimeOut - dwTimeIn);


   }

   void SimpleFolderTreeInterface::_001UpdateImageList(::ex1::tree_item * pitem)
   {
      UNREFERENCED_PARAMETER(pitem);
      //         Item & item = m_itema.get_item(pitem->m_dwUser);

      //HWND hwnd = _get_handle();

      /*   IShellFolder * lpsf = item.m_spshellfolder;

      item.m_iImage =
      _shell::g_imageset.GetImage(
      hwnd,
      lpsf,
      item.m_lpiidlAbsolute,
      item.m_lpiidlRelative,
      gen::international::utf8_to_unicode(item.m_strExtra),
      _shell::IconNormal);

      item.m_iImageSelected =
      _shell::g_imageset.GetImage(
      hwnd,
      lpsf,
      item.m_lpiidlAbsolute,
      item.m_lpiidlRelative,
      gen::international::utf8_to_unicode(item.m_strExtra),
      _shell::IconOpen);*/


   }

   void SimpleFolderTreeInterface::_001InsertColumns()
   {

      /*::userbase::form_control control;

      control.set_type(::userbase::form_control::type_edit);
      control.m_iKey = FILE_MANAGER_ID_FILE_NAME;
      pcontrol->descriptor().m_id = FILE_MANAGER_ID_FILE_NAME;
      control.set_data_type(::userbase::form_control::DataTypeString);

      int iControl =  _001AddControl(control);

      CColumn column;

      column.m_iWidth               = 500;
      column.m_iSubItem             = 1;
      column.m_bIcon                = true;
      column.m_sizeIcon.cx          = 16;
      column.m_sizeIcon.cy          = 16;
      column.m_iControl             = iControl;
      column.m_iConfigId            = FILE_MANAGER_ID_FILE_NAME;
      column.m_bEditOnSecondClick   = true;
      _001AddColumn(column);*/

   }

   void SimpleFolderTreeInterface::GetSelectedFilePath(stringa & stra)
   {
      for(int i = 0; i < m_itemptraSelected.get_size(); i++)
      {
         stra.add(((::fs::tree_item *)m_itemptraSelected[0]->m_pitemdata)->m_strPath);
      }
   }


   void SimpleFolderTreeInterface::_017UpdateList()
   {

   }


   void SimpleFolderTreeInterface::_001OnMainPostMessage(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::base, pbase, pobj)
         switch(pbase->m_wparam)
      {
         case MessageMainPostCreateImageListItemRedraw:
            {
               RedrawWindow();
               KillTimer(123);
               /*
               rect rect;
               int iArrange = (int) lparam;
               if(_001IsItemVisible(iArrange))
               {
               m_bCreateImageListRedraw = true;
               _001GetItemRect(iArrange, iArrange, rect);
               RedrawWindow(rect);
               m_bCreateImageListRedraw = false;
               }*/
            }
            break;
      }
      pbase->set_lresult(0);
      pbase->m_bRet = true;
   }

   /*
   ::fs::item & SimpleFolderTreeInterface::GetFileManagerItem()
   {
   return GetFileManager()->get_item();
   }
   */

   void SimpleFolderTreeInterface::_017Synchronize()
   {
      _017Browse(GetFileManagerItem().m_strPath);
   }

   void SimpleFolderTreeInterface::install_message_handling(::gen::message::dispatch *pinterface)
   {
      ::fs::tree::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(MessageMainPost, pinterface,  this,  &SimpleFolderTreeInterface::_001OnMainPostMessage);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &SimpleFolderTreeInterface::_001OnTimer);
   }

   void SimpleFolderTreeInterface::StartAnimation()
   {
      m_iAnimate = 1;
   }

   void SimpleFolderTreeInterface::TakeAnimationSnapshot()
   {
      m_iAnimate = 1;
      //   ::user::tree::_001OnDraw(m_gdibuffer.GetBuffer());
   }

   void SimpleFolderTreeInterface::_017PreSynchronize()
   {
      TakeAnimationSnapshot();
   }

   IShellFolder * SimpleFolderTreeInterface::_001GetFolder(EFolder efolder)
   {
      IShellFolder * psf;

      if(m_mapFolder.Lookup(efolder, psf))
      {
         return psf;
      }
      else
      {
         int iCSIDL = MapToCSIDL(efolder);

         ASSERT(iCSIDL >= 0);

         if(iCSIDL < 0)
            return NULL;

         IShellFolder * psfDesktop = NULL;
         HRESULT hr = SHGetDesktopFolder(&psfDesktop);
         LPITEMIDLIST lpidl;

         hr = SHGetSpecialFolderLocation(
            NULL,
            iCSIDL,
            &lpidl);

         if(FAILED(hr))
            return NULL;

         hr = psfDesktop->BindToObject(
            lpidl,
            NULL,
            IID_IShellFolder,
            (void **) &psf);

         if(FAILED(hr))
            return NULL;

         m_mapFolder.set_at(efolder, psf);

         psf->AddRef();
         psfDesktop->Release();
         return psf;
      }
   }

   int SimpleFolderTreeInterface::MapToCSIDL(EFolder efolder)
   {
      switch(efolder)
      {
      case FolderMyComputer:
         return CSIDL_DRIVES;
      default:
         return -1;
      }
   }

   void SimpleFolderTreeInterface::_001OnItemExpand(::ex1::tree_item * pitem)
   {
      if(typeid(*pitem->m_pitemdata) == System.template type_info < ::fs::tree_item > ())
      {
         _017UpdateList(((::fs::tree_item *)pitem->m_pitemdata)->m_strPath, pitem, 1);
      }
      else
      {
         _017UpdateList("", pitem, 1);
      }
   }

   void SimpleFolderTreeInterface::_001OnItemCollapse(::ex1::tree_item * pitem)
   {
      UNREFERENCED_PARAMETER(pitem);
   }

   bool SimpleFolderTreeInterface::_001IsTranslucent()
   {
      return true;
   }

   void SimpleFolderTreeInterface::_001OnOpenItem(::ex1::tree_item * pitem)
   {
      ::fs::item item;
      item.m_strPath         = ((::fs::tree_item *) pitem->m_pitemdata)->m_strPath;
      _017OpenFolder(item);
   }

   void SimpleFolderTreeInterface::_017OpenFolder(const ::fs::item & item)
   {
      UNREFERENCED_PARAMETER(item);
      ASSERT(FALSE);
   }


   void SimpleFolderTreeInterface::_StartCreateImageList()
   {
      m_pdataitemCreateImageListStep = (::ex1::tree_item *) get_base_item()->m_pchild;
      SetTimer(TimerCreateImageList, 80, NULL);
   }

   void SimpleFolderTreeInterface::_StopCreateImageList()
   {
      KillTimer(TimerCreateImageList);
   }

   void SimpleFolderTreeInterface::_CreateImageListStep()
   {
      if(m_pdataitemCreateImageListStep == NULL)
      {
         _StopCreateImageList();
         return;
      }

      _001UpdateImageList(m_pdataitemCreateImageListStep);

      m_pdataitemCreateImageListStep = m_pdataitemCreateImageListStep->get_item(ex1::TreeNavigationProperForward);


   }

   void SimpleFolderTreeInterface::_001OnTimer(gen::signal_object * pobj)
   {

      SCAST_PTR(::gen::message::timer, ptimer, pobj);
      
      switch(ptimer->m_nIDEvent)
      {
         case TimerDelayedListUpdate:
            {
               _DelayedListUpdate();
               break;
            }
         case TimerCreateImageList:
            {
               _CreateImageListStep();
            }
            break;
      }

      ptimer->m_bRet = false;

   }


   void filemanager::SimpleFolderTreeInterface::_StartDelayedListUpdate(void)
   {

      SetTimer(TimerDelayedListUpdate, 500, NULL);

   }


   void filemanager::SimpleFolderTreeInterface::_StopDelayedListUpdate(void)
   {

      KillTimer(TimerDelayedListUpdate);

   }


   void filemanager::SimpleFolderTreeInterface::_DelayedListUpdate(void)
   {
      
      single_lock sl(&m_mutexMissinUpdate, TRUE);

      if(m_straMissingUpdate.get_size() == 0)
      {
         _StopDelayedListUpdate();
         return;
      }

      if(m_bDelayedListUpdate)
         return;

      m_bDelayedListUpdate = true;


      ::ex1::tree_item * pitem = find_item(m_straMissingUpdate[0]);
      if(pitem != NULL)
      {

         _017UpdateList(m_straMissingUpdate[0], pitem, 1);
      }

      m_straMissingUpdate.remove_at(0);

      m_bDelayedListUpdate = false;


   }

   COLORREF SimpleFolderTreeInterface::get_background_color()
   {

      if(GetFileManager() == NULL)
      {
         return ARGB(255, 200, 255, 255);
      }
      else if(GetFileManager()->get_filemanager_data()->is_saving())
      {
         return ARGB(255, 255, 177, 84);
      }
      else
      {
         return ARGB(255, 200, 255, 255);
      }

   }


} // namespace filemanager


