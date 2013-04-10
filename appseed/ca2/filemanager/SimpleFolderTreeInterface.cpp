#include "framework.h"


namespace filemanager
{


   SimpleFolderTreeInterface::SimpleFolderTreeInterface(sp(::ca::application) papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::fs::tree(papp),
      m_mutexMissinUpdate(papp)
   {
      m_pdataitemCreateImageListStep = ::null();

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

      //   m_pimagelist = ::null();


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

      //for(int32_t i = stra.get_size() - 1; i >= 0; i--)
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         string strAscendant = stra[i];
         sp(::ca::tree_item) pitem = find_item(strAscendant);
         if(pitem == ::null())
         {
            string str;
            str = strAscendant;
            if(i == 0)
            {
               _017UpdateList("", ::null(), 1);
            }
            else
            {
               get_document()->set().eat_end_level(str, 1);
               _017UpdateList(str, ::null(), 1);
            }
         }
         pitem = find_item(strAscendant);
         if(pitem == ::null())
            break;

         if(!(pitem->m_dwState & ::ca::tree_item_state_expanded))
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

      sp(::ca::tree_item) pitem = find_item(lpcsz);

      if(pitem != ::null())
      {
         index iLevel = 0;

         index iIndex = get_proper_item_index(pitem, &iLevel);

         index iLastVisibleIndex = (index) (m_scrollinfo.m_ptScroll.y + _001GetVisibleItemCount() - 5);

         index iObscured; // obscured proper descendants
         iObscured = iIndex  - iLastVisibleIndex;

         if(iObscured > 0)
         {
            int32_t iNewScroll = (int32_t) (m_scrollinfo.m_ptScroll.y + iIndex * _001GetItemHeight());
            m_scrollinfo.m_ptScroll.y = max(iNewScroll, 0);
         }
      }
      layout();
      _001RedrawWindow();
   }

   sp(::ca::tree_item) SimpleFolderTreeInterface::find_item(const char * lpcsz)
   {
      return find_absolute(lpcsz);
   }

   void SimpleFolderTreeInterface::_017Browse(const char * lpcsz, bool bForceUpdate)
   {
      if(!bForceUpdate)
      {
         sp(::ca::tree_item) pitem = find_item(lpcsz);
         if(pitem != ::null())
         {
            if(is_tree_item_selected(pitem))
               return;
            if(is_tree_item_selected(pitem->m_pparent))
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

   void SimpleFolderTreeInterface::_017UpdateZipList(const char * lpcsz, sp(::ca::tree_item) pitemParent, int32_t iLevel)
   {

      string szPath(lpcsz);

      string wstrExtraPath;
      string wstrItemExtra;

      index iFind;
      ::ca::filesp spfile(allocer());

      //spfile->open(szPath, ::ca::file::mode_read | ::ca::file::type_binary);

      /*array < ::primitive::memory_file, ::primitive::memory_file & > filea;
      _vmszipFile zipfile;

      zipfile.m_pfile = &file;

      unzFile pf = _vmszipApi::unzipOpen(&zipfile);

      array < ::primitive::memory_file, ::primitive::memory_file & > filea;
      int32_t iStart = 0;
      int32_t iFind;
      while((iFind  = wstrExtra.find(L".zip:", iStart)) >= 0)
      {
      filea.add(::primitive::memory_file());
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
      ::ca::tree_item_ptr_array ptraRemove;
      pitemParent->get_children(ptraRemove);

      for(int32_t i = 0; i < wstraItem.get_size(); i++)
      {
         wstrItem = wstraItem[i];

         sp(::fs::tree_item_data) pitemNew = new ::fs::tree_item_data;

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
            ::ca::tree_item  * pitem    = find_item(pitemNew->m_strPath);
            if(pitem == ::null())
            {
               pitem = insert_item_data(get_fs_tree_data(), pitemNew, ::ca::RelativeLastChild, pitemParent);
            }
            else
            {
               pitem = insert_item_data(get_fs_tree_data(), pitemNew, ::ca::RelativeReplace, pitem);
            }
            str = szPath;
            wstraChildItem.remove_all();
            if(zip::Util().HasSubFolder(get_app(), str))
            {
               pitem->m_dwState |= ::ca::tree_item_state_expandable;
            }
            if(iLevel > 1)
            {
               _017UpdateZipList(pitemNew->m_strPath, pitem, iLevel - 1);
            }
         }
      }

      
      remove_tree_item_array(ptraRemove);

   }

   void SimpleFolderTreeInterface::_017UpdateList(const char * lpcsz, sp(::ca::tree_item) pitemParent, int32_t iLevel)
   {
      if(lpcsz == ::null())
         lpcsz = "";


      /*if(lpcsz == ::null())
      {
      if(zip::Util(get_app()).IsUnzipable(pitemParent->m_strPath))
      {
      _017UpdateZipList(lpcsz, ::null(), pitemParent, iLevel - 1);
      }
      return;
      }*/

      m_strPath = lpcsz;

      if(pitemParent == ::null())
      {
         pitemParent =  get_base_item();
      }
      else if(get_base_item() == ::null())
      {
         m_pitem = pitemParent;
      }


      stringa straAscendants;

      sp(::ca::tree_item) pitem;

      sp(::ca::tree_item) pitemBase;

      sp(::fs::tree_item_data) pitemChild;

      string strNew;

      System.file().get_ascendants_path(lpcsz, straAscendants);

      pitemBase = get_base_item();

      for(int32_t i = 0; i < straAscendants.get_count(); i++)
      {
         string strItem = straAscendants[i];
         strItem.trim("/\\");
         if(strItem.is_empty())
            continue;
         pitem = find_item(strItem);
         if(pitem == ::null())
         {
            pitem = find_item(strItem + "\\");
            if(pitem == ::null())
            {
               pitem = find_item(strItem + "/");
               if(pitem == ::null())
               {
                  pitem = find_item(strItem + "//");
                  if(pitem == ::null())
                  {
                     strItem.replace("\\", "/");
                     pitem = find_item(strItem);
                     if(pitem == ::null())
                     {
                        pitem = find_item(strItem + "/");
                     }
                  }
               }
            }

         }
         strNew.Empty();
         if(pitem != ::null())
         {
            pitemBase = pitem;
            continue;
         }
         else
         {
            // pitem == ::null()
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

         pitemChild = new ::fs::tree_item_data;

         pitemChild->m_pdata = get_fs_tree_data();

         pitemChild->m_strPath = get_document()->set().dir_path(strNew, "");

         //if(m_straUpdatePtrFilter.find_first(straPath[i]) >= 0)
         //{
         //   continue;
         //}
         pitemChild->m_strName = System.file().name_(strNew);

         pitemChild->m_flags.signalize(::fs::FlagFolder);
//         pitemChild->m_iImage = m_iDefaultImage;

#ifdef WINDOWSEX

         pitemChild->m_iImage = System.user()->shellimageset().GetImage(
            ::null(),
            pitemChild->m_strPath,
            ::null(),
            _shell::IconNormal,
            true);

#else

         pitemChild->m_iImage = -1;

#endif

         pitemChild->m_iImageSelected = m_iDefaultImageSelected;

         pitem = find_item(pitemChild->m_strPath);
         if(pitem != ::null())
         {
            //pitem = insert_item(pitemChild, ::ca::RelativeReplace, pitem);
            // a refresh or a file monitoring event for folder deletion or creation should
            // the most precisely possible way reset this flag
            //pitemChild->m_flags.signalize(::fs::FlagHasSubFolderUnknown);
            // error
            return;
         }
         else
         {
            pitem = insert_item(get_fs_tree_data(), pitemChild, ::ca::RelativeLastChild, pitemBase);
         }

         if(pitemChild->m_flags.is_signalized(::fs::FlagHasSubFolder))
         {
            pitem->m_dwState |= ::ca::tree_item_state_expandable;
         }


         pitemBase = pitem;

         //if(iLevel > 1)
         //{
           // _017UpdateList(pitemChild->m_strPath,  pitem, iLevel - 1);
         //}

      }


      pitemParent = pitemBase;



      if(GetFileManager() != ::null() && GetFileManager()->get_filemanager_data()->m_ptreeFileTreeMerge != ::null()
         && !(dynamic_cast < ::user::tree * > (GetFileManager()->get_filemanager_data()->m_ptreeFileTreeMerge.m_p))->m_treeptra.contains(this))
      {
         GetFileManager()->get_filemanager_data()->m_ptreeFileTreeMerge->merge(this);
      }

      sp(::fs::tree_item_data) pitemFolder = ::null();

      string strRawName1 = typeid(*pitemParent).name();
      string strRawName2 = typeid(::fs::tree_item_data).name();
      if(strRawName1 == strRawName2)
      {
         pitemFolder = (sp(::fs::tree_item_data)) pitemParent;
      }


      if(pitemFolder != ::null() && pitemFolder->m_flags.is_signalized(::fs::FlagHasSubFolderUnknown))
      {
         if(get_document()->set().has_subdir(pitemFolder->m_strPath))
         {
            pitemFolder->m_flags.signalize(::fs::FlagHasSubFolder);
         }
         pitemFolder->m_flags.unsignalize(::fs::FlagHasSubFolderUnknown);
      }

      stringa straChildItem;
      string str;

      uint32_t dwTimeIn;
      uint32_t dwTimeOut;

      dwTimeIn = get_tick_count();

      int32_t iMaxSize;
      iMaxSize = 1000;

      int32_t iSize;
      iSize = 0;

      int32_t iChildCount;

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

      ::ca::tree_item_ptr_array ptraRemove;

      while(pitem != ::null())
      {

         string strPathOld =  pitem->m_pitemdata.cast < ::fs::tree_item_data > ()->m_strPath;

         strPathOld.trim_right("/\\");

         if(!straNew.contains(strPathOld) || !GetFileManager()->get_fs_data()->is_dir(strPathOld))
         {
            ptraRemove.add(pitem);
         }

         pitem = pitem->m_pnext;

      }

      remove_tree_item_array(ptraRemove);



      int32_t i;

      for(i = 0; i < straPath.get_size(); i++)
      {

         pitemChild = new ::fs::tree_item_data;

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
               if(pitem != ::null())
               {
                  pitem = insert_item(get_fs_tree_data(), pitemChild, ::ca::RelativeReplace, pitem);
               }
               else
               {
                  pitem = insert_item(get_fs_tree_data(), pitemChild, ::ca::RelativeLastChild, pitemParent);
               }

               if(zip::Util().HasSubFolder(get_app(), pitemChild->m_strPath))
               {
                  pitem->m_dwState |= ::ca::tree_item_state_expandable;
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

#ifdef WINDOWSEX
         try
         {
            pitemChild->m_iImage = System.user()->shellimageset().GetImage(
               ::null(),
               pitemChild->m_strPath,
               ::null(),
               _shell::IconNormal,
               true);
            pitemChild->m_iImageSelected = System.user()->shellimageset().GetImage(
               ::null(),
               pitemChild->m_strPath,
               ::null(),
               _shell::IconOpen,
               true);
         }
         catch(...)
         {
            pitemChild->m_iImage = m_iDefaultImage;
            pitemChild->m_iImageSelected = m_iDefaultImageSelected;
         }
#else

         pitemChild->m_iImage = m_iDefaultImage;
         pitemChild->m_iImageSelected = m_iDefaultImageSelected;

#endif

         pitem = find_item(pitemChild->m_strPath);
         if(pitem != ::null())
         {
            pitem = insert_item(get_fs_tree_data(), pitemChild, ::ca::RelativeReplace, pitem);
            // a refresh or a file monitoring event for folder deletion or creation should
            // the most precisely possible way reset this flag
            pitemChild->m_flags.signalize(::fs::FlagHasSubFolderUnknown);
         }
         else
         {
            pitem = insert_item(get_fs_tree_data(), pitemChild, ::ca::RelativeLastChild, pitemParent);
         }

         if(pitemChild->m_flags.is_signalized(::fs::FlagHasSubFolder))
         {
            pitem->m_dwState |= ::ca::tree_item_state_expandable;
         }

         if(iLevel > 1)
         {
            _017UpdateList(pitemChild->m_strPath,  pitem, iLevel - 1);
         }

      }

      arrange(::fs::arrange_by_name);

      if(iChildCount == 0)
      {
         pitemParent->m_dwState &= ~::ca::tree_item_state_expandable;
      }

      dwTimeOut = get_tick_count();

      TRACE("timeIn%d\n", dwTimeIn);
      TRACE("timeOut%d\n", dwTimeIn);
      TRACE("timeDelta%d\n", dwTimeOut - dwTimeIn);


   }

   void SimpleFolderTreeInterface::_001UpdateImageList(sp(::ca::tree_item) pitem)
   {
      UNREFERENCED_PARAMETER(pitem);
      //         Item & item = m_itema.get_item(pitem->m_dwUser);

      //oswindow oswindow = get_handle();

      /*   IShellFolder * lpsf = item.m_spshellfolder;

      item.m_iImage =
      _shell::g_imageset.GetImage(
      oswindow,
      lpsf,
      item.m_lpiidlAbsolute,
      item.m_lpiidlRelative,
      ::ca::international::utf8_to_unicode(item.m_strExtra),
      _shell::IconNormal);

      item.m_iImageSelected =
      _shell::g_imageset.GetImage(
      oswindow,
      lpsf,
      item.m_lpiidlAbsolute,
      item.m_lpiidlRelative,
      ::ca::international::utf8_to_unicode(item.m_strExtra),
      _shell::IconOpen);*/


   }

   void SimpleFolderTreeInterface::_001InsertColumns()
   {

      /*::userbase::form_control control;

      control.set_type(::userbase::form_control::type_edit);
      control.m_iKey = FILE_MANAGER_ID_FILE_NAME;
      pcontrol->descriptor().m_id = FILE_MANAGER_ID_FILE_NAME;
      control.set_data_type(::userbase::form_control::DataTypeString);

      int32_t iControl =  _001AddControl(control);

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
      for(int32_t i = 0; i < m_itemptraSelected.get_size(); i++)
      {
         stra.add(( (m_itemptraSelected[0].m_pitemdata.cast < ::fs::tree_item_data > ()))->m_strPath);
      }
   }


   void SimpleFolderTreeInterface::_017UpdateList()
   {

   }


   void SimpleFolderTreeInterface::_001OnMainPostMessage(::ca::signal_object * pobj)
   {
      SCAST_PTR(::ca::message::base, pbase, pobj)
         switch(pbase->m_wparam)
      {
         case MessageMainPostCreateImageListItemRedraw:
            {
               RedrawWindow();
               KillTimer(123);
               /*
               rect rect;
               int32_t iArrange = (int32_t) lparam;
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

   void SimpleFolderTreeInterface::install_message_handling(::ca::message::dispatch *pinterface)
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

#ifdef WINDOWSEX

   IShellFolder * SimpleFolderTreeInterface::_001GetFolder(EFolder efolder)
   {
      IShellFolder * psf;

      if(m_mapFolder.Lookup(efolder, psf))
      {
         return psf;
      }
      else
      {
         int32_t iCSIDL = MapToCSIDL(efolder);

         ASSERT(iCSIDL >= 0);

         if(iCSIDL < 0)
            return ::null();

         IShellFolder * psfDesktop = ::null();
         HRESULT hr = SHGetDesktopFolder(&psfDesktop);
         LPITEMIDLIST lpidl;

         hr = SHGetSpecialFolderLocation(
            ::null(),
            iCSIDL,
            &lpidl);

         if(FAILED(hr))
            return ::null();

         hr = psfDesktop->BindToObject(
            lpidl,
            ::null(),
            IID_IShellFolder,
            (void **) &psf);

         if(FAILED(hr))
            return ::null();

         m_mapFolder.set_at(efolder, psf);

         psf->AddRef();
         psfDesktop->Release();
         return psf;
      }

   }

   int32_t SimpleFolderTreeInterface::MapToCSIDL(EFolder efolder)
   {
      switch(efolder)
      {
      case FolderMyComputer:
         return CSIDL_DRIVES;
      default:
         return -1;
      }
   }


#endif


   void SimpleFolderTreeInterface::_001OnItemExpand(sp(::ca::tree_item) pitem)
   {
      if(typeid(*pitem->m_pitemdata) == System.type_info < ::fs::tree_item_data > ())
      {
         _017UpdateList(pitem->m_pitemdata.cast < ::fs::tree_item_data > ()->m_strPath, pitem, 1);
      }
      else
      {
         _017UpdateList("", pitem, 1);
      }
   }

   void SimpleFolderTreeInterface::_001OnItemCollapse(sp(::ca::tree_item) pitem)
   {
      UNREFERENCED_PARAMETER(pitem);
   }

   bool SimpleFolderTreeInterface::_001IsTranslucent()
   {
      return true;
   }

   void SimpleFolderTreeInterface::_001OnOpenItem(sp(::ca::tree_item) pitem)
   {

      _017OpenFolder(new ::fs::item(*pitem->m_pitemdata.cast < ::fs::tree_item_data > ()));

   }

   void SimpleFolderTreeInterface::_017OpenFolder(sp(::fs::item)  item)
   {
      UNREFERENCED_PARAMETER(item);
      ASSERT(FALSE);
   }


   void SimpleFolderTreeInterface::_StartCreateImageList()
   {

      if(get_fs_tree_data()->m_pimagelist == ::null())
      {
         
         get_fs_tree_data()->m_pimagelist = System.user()->shellimageset().GetImageList16();

         m_iDefaultImage = System.user()->shellimageset().GetImage(
            "foo",
            _shell::FileAttributeDirectory,
            _shell::IconNormal);

         m_iDefaultImageSelected = System.user()->shellimageset().GetImage(
            "foo",
            _shell::FileAttributeDirectory,
            _shell::IconOpen);

      }



      m_pdataitemCreateImageListStep = (sp(::ca::tree_item)) get_base_item()->m_pchild;
      SetTimer(TimerCreateImageList, 80, ::null());
   }

   void SimpleFolderTreeInterface::_StopCreateImageList()
   {
      KillTimer(TimerCreateImageList);
   }

   void SimpleFolderTreeInterface::_CreateImageListStep()
   {
      if(m_pdataitemCreateImageListStep == ::null())
      {
         _StopCreateImageList();
         return;
      }

      _001UpdateImageList(m_pdataitemCreateImageListStep);

      m_pdataitemCreateImageListStep = m_pdataitemCreateImageListStep->get_item(::ca::TreeNavigationProperForward);


   }

   void SimpleFolderTreeInterface::_001OnTimer(::ca::signal_object * pobj)
   {

      SCAST_PTR(::ca::message::timer, ptimer, pobj);

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


   void SimpleFolderTreeInterface::_StartDelayedListUpdate()
   {

      SetTimer(TimerDelayedListUpdate, 500, ::null());

   }


   void SimpleFolderTreeInterface::_StopDelayedListUpdate()
   {

      KillTimer(TimerDelayedListUpdate);

   }


   void SimpleFolderTreeInterface::_DelayedListUpdate()
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


      sp(::ca::tree_item) pitem = find_item(m_straMissingUpdate[0]);
      if(pitem != ::null())
      {

         _017UpdateList(m_straMissingUpdate[0], pitem, 1);
      }

      m_straMissingUpdate.remove_at(0);

      m_bDelayedListUpdate = false;


   }

   COLORREF SimpleFolderTreeInterface::get_background_color()
   {

      if(GetFileManager() == ::null())
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


