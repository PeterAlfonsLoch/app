#include "framework.h"


namespace fs
{


   tree_interface::tree_interface(sp(::ca::application) papp) :
      ca(papp),
      
      ::user::scroll_view(papp),
      ::user::tree(papp)
   {

      m_dataid = "filemanager::fs::tree_interface";

      m_pdataitemCreateImageListStep = ::null();

      m_iAnimate = 0;
      m_bDelayedListUpdate = false;

      set_data(new ::fs::tree_data(get_app()));

   }


   tree_interface::~tree_interface()
   {

   }


   void tree_interface::update_list()
   {

   }


   void tree_interface::_017UpdateList(const char * lpcsz, sp(::ca::tree_item) pitemParent, int32_t iLevel)
   {
      if(lpcsz == ::null())
         lpcsz = "";

      m_strPath = lpcsz;

      if(pitemParent == ::null())
      {
         pitemParent =  get_base_item();
      }
      else if(get_base_item() == ::null())
      {
         m_pitem = pitemParent;
      }

      /*if(GetFileManager() != ::null() && GetFileManager()->get_filemanager_data()->m_ptreeFileTreeMerge != ::null()
      && !(dynamic_cast < usersp(::tree) > (GetFileManager()->get_filemanager_data()->m_ptreeFileTreeMerge))->m_treeptra.contains(this))
      {
         GetFileManager()->get_filemanager_data()->m_ptreeFileTreeMerge->merge(this);
      }*/

      sp(::fs::tree_item_data) pitemFolder = ::null();

      string strRawName1 = typeid(*pitemParent->m_pitemdata.m_p).name();
      string strRawName2 = typeid(::fs::tree_item_data).name();
      if(strRawName1 == strRawName2)
      {
         pitemFolder = pitemParent;
      }


      sp(::fs::tree_item_data) pitemChild;
      sp(::ca::tree_item) pitem;
      ::ca::tree_item_ptr_array ptraRemove;

      if(pitemFolder != ::null() && pitemFolder->m_flags.is_signalized(FlagHasSubFolderUnknown))
      {
         if(get_document()->set().has_subdir(pitemFolder->m_strPath))
         {
            pitemFolder->m_flags.signalize(FlagHasSubFolder);
         }
         pitemFolder->m_flags.unsignalize(FlagHasSubFolderUnknown);
      }

      stringa straChildItem;
      string str;

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

      int32_t i;

      for(i = 0; i < straPath.get_size(); i++)
      {

         pitemChild = new ::fs::tree_item_data;

         pitemChild->m_pdata = ::ca::tree::get_data();

         pitemChild->m_strPath = straPath[i];

         //if(m_straUpdatePtrFilter.find_first(straPath[i]) >= 0)
         //{
         //   continue;
         //}
         pitemChild->m_strName = straTitle[i];
         if(!get_document()->set().is_dir(straPath[i]))
         {
            if(zip::Util().IsUnzipable(get_app(), pitemChild->m_strPath))
            {
               pitemChild->m_flags.signalize(FlagFolder);


               pitemChild->m_iImage = m_iDefaultImage;
               pitemChild->m_iImageSelected = m_iDefaultImageSelected;
               pitemChild->m_flags.signalize(FlagInZip);

               pitem = find_item(pitemChild->m_strPath);
               if(pitem != ::null())
               {
                  pitem = insert_item(get_fs_tree_data(), pitemChild, ::ca::RelativeReplace, pitem);
               }
               else
               {
                  pitem = insert_item(get_fs_tree_data(),pitemChild, ::ca::RelativeLastChild, pitemParent);
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

         pitemChild->m_flags.signalize(FlagFolder);
         pitemChild->m_iImage = m_iDefaultImage;
         pitemChild->m_iImageSelected = m_iDefaultImageSelected;

         pitem = find_item(pitemChild->m_strPath);
         if(pitem != ::null())
         {
            pitem = insert_item(get_fs_tree_data(), pitemChild, ::ca::RelativeReplace, pitem);
            // a refresh or a file monitoring event for folder deletion or creation should
            // the most precisely possible way reset this flag
            pitemChild->m_flags.signalize(FlagHasSubFolderUnknown);
         }
         else
         {
               pitem = insert_item(get_fs_tree_data(), pitemChild, ::ca::RelativeLastChild, pitemParent);
         }

         if(pitemChild->m_flags.is_signalized(FlagHasSubFolder))
         {
            pitem->m_dwState |= ::ca::tree_item_state_expandable;
         }

         if(iLevel > 1)
         {
            _017UpdateList(pitemChild->m_strPath, pitem, iLevel - 1);
         }

      }
      for(int32_t j = 0; j < ptraRemove.get_size(); j++)
      {
         ptraRemove(j).release();
      }

      arrange(arrange_by_name);

      if(iChildCount == 0)
      {
         pitemParent->m_dwState &= ~::ca::tree_item_state_expandable;
      }



   }


   void tree_interface::_017EnsureVisible(const char * lpcsz)
   {
      stringa stra;

      get_document()->set().get_ascendants_path(lpcsz, stra);

      m_straUpdatePtrFilter = stra;



      //for(int32_t i = stra.get_size() - 1; i >= 0; i--)
      for(index i = 0; i < stra.get_size(); i++)
      {
         string strAscendant = stra[i];
         sp(::ca::tree_item) pitem = find_item(strAscendant);
         if(pitem == ::null())
         {
            string str;
            str = strAscendant;
            get_document()->set().eat_end_level(str, 1);
            _017UpdateList(str, ::null(), 1);
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

      m_straMissingUpdate = stra;


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

   sp(::ca::tree_item) tree_interface::find_item(const char * lpcsz)
   {
      return find_absolute(lpcsz);
   }

   void tree_interface::_017Browse(const char * lpcsz, bool bForceUpdate)
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

   void tree_interface::_017UpdateZipList(const char * lpcsz, sp(::ca::tree_item) pitemParent, int32_t iLevel)
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
         pitemNew->m_flags.signalize(FlagInZip);

         wstrExtraPath = wstrItem;

         // ignore this file if its not in the Extra sub folder
/*         if(wstrExtraPath.Left(wstrExtra.get_length()) != wstrExtra ||
            wstrExtraPath == wstrExtra)
            continue;*/

//         wstrItemExtra = wstrExtraPath.Mid(wstrExtra.get_length());

         pitemNew->m_flags.unsignalize_all();

         iFind = wstrItemExtra.find("/");
         if(iFind > 0)
         {
            wstrFolder = wstrItemExtra.Left(iFind);
            if(wstraFolder.find_first(wstrFolder) >= 0)
               continue;
            wstraFolder.add(wstrFolder);
            pitemNew->m_flags.signalize(FlagFolder);
            pitemNew->m_strPath   = szPath;
            pitemNew->m_iImage     = -1;
            pitemNew->m_strName   = wstrFolder;
//               pitemNew->m_strExtra  = wstrExtra + wstrFolder + "/";
         }
         else
         {
            pitemNew->m_strPath   = szPath;
            pitemNew->m_iImage     = -1;
            pitemNew->m_strName   = wstrItemExtra;
//             pitemNew->m_strExtra  = wstrExtraPath;
            string str;
            str = szPath + wstrExtraPath;
            if(zip::Util().IsUnzipable(get_app(), str))
            {
               pitemNew->m_flags.signalize(FlagFolder);
            }
         }
         if(pitemNew->m_flags.is_signalized(FlagFolder))
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


   void tree_interface::_001UpdateImageList(sp(::ca::tree_item) pitem)
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

   void tree_interface::_001InsertColumns()
   {

      /*::user::form_control control;

      control.set_type(::user::form_control::type_edit);
      control.m_iKey = FILE_MANAGER_ID_FILE_NAME;
      pcontrol->descriptor().m_id = FILE_MANAGER_ID_FILE_NAME;
      control.set_data_type(::user::form_control::DataTypeString);

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

   void tree_interface::GetSelectedFilePath(stringa & stra)
   {
      for(int32_t i = 0; i < m_itemptraSelected.get_size(); i++)
      {
         stra.add(m_itemptraSelected(0)->m_pitemdata.cast < ::fs::tree_item_data > ()->m_strPath);
      }
   }


   void tree_interface::_017UpdateList()
   {

   }



   void tree_interface::_017Synchronize()
   {
      _017Browse(get_document()->m_strFolder);
   }

   void tree_interface::install_message_handling(::ca::message::dispatch *pinterface)
   {
      ::user::tree::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &tree_interface::_001OnTimer);

   }


   void tree_interface::StartAnimation()
   {
      m_iAnimate = 1;
   }

   void tree_interface::TakeAnimationSnapshot()
   {
      m_iAnimate = 1;
      //   ::user::tree_interface::_001OnDraw(m_gdibuffer.GetBuffer());
   }

   void tree_interface::_017PreSynchronize()
   {
      TakeAnimationSnapshot();
   }

/*   IShellFolder * tree_interface::_001GetFolder(EFolder efolder)
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
   }*/

/*   int32_t tree_interface::MapToCSIDL(EFolder efolder)
   {
      switch(efolder)
      {
      case FolderMyComputer:
         return CSIDL_DRIVES;
      default:
         return -1;
      }
   }
   */

   void tree_interface::_001OnItemExpand(sp(::ca::tree_item) pitem)
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

   void tree_interface::_001OnItemCollapse(sp(::ca::tree_item) pitem)
   {
      UNREFERENCED_PARAMETER(pitem);
   }

   bool tree_interface::_001IsTranslucent()
   {
      return true;
   }

   void tree_interface::_001OnOpenItem(sp(::ca::tree_item) pitem)
   {
      
      _017OpenFolder(new ::fs::item(*pitem->m_pitemdata.cast < ::fs::tree_item_data > ()));

   }

   void tree_interface::_017OpenFolder(sp(::fs::item)  item)
   {
      UNREFERENCED_PARAMETER(item);
      ASSERT(FALSE);
   }


   void tree_interface::_StartCreateImageList()
   {
      m_pdataitemCreateImageListStep = (sp(::ca::tree_item)) get_base_item()->m_pchild;
//         SetTimer(TimerCreateImageList, 80, ::null());
   }

   void tree_interface::_StopCreateImageList()
   {
//       KillTimer(TimerCreateImageList);
   }

   void tree_interface::_CreateImageListStep()
   {
      if(m_pdataitemCreateImageListStep == ::null())
      {
         _StopCreateImageList();
         return;
      }

      _001UpdateImageList(m_pdataitemCreateImageListStep);

      m_pdataitemCreateImageListStep = m_pdataitemCreateImageListStep->get_item(::ca::TreeNavigationProperForward);


   }

   void tree_interface::_001OnTimer(::ca::signal_object * pobj)
   {
      SCAST_PTR(::ca::message::timer, ptimer, pobj)
/*            switch(ptimer->m_nIDEvent)
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
      }*/
      ptimer->m_bRet = false;
   }

   void tree_interface::_StartDelayedListUpdate()
   {
      //SetTimer(TimerDelayedListUpdate, 500, ::null());
   }

   void tree_interface::_StopDelayedListUpdate()
   {
      //KillTimer(TimerDelayedListUpdate);
   }

   void tree_interface::_DelayedListUpdate()
   {
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

   COLORREF tree_interface::get_background_color()
   {
      if(get_document() == ::null())
      {
         return RGB(200, 255, 255);
      }
/*      else if(GetFileManager()->get_filemanager_data()->is_saving())
      {
         return RGB(255, 177, 84);
      }*/
      else
      {
         return RGB(200, 255, 255);
      }
   }

   sp(::ca::tree_item) tree_interface::find_absolute(const char * lpcszPath)
   {
      sp(::ca::tree_item) pitem = get_base_item();
      if(lpcszPath == ::null() || strlen(lpcszPath) == 0)
         return pitem;
      string strPath(lpcszPath);
      strPath.trim_right("\\/");
      while(pitem != ::null())
      {
         if(pitem->m_pitemdata != ::null()
         && typeid(*pitem->m_pitemdata) == System.type_info < ::fs::tree_item_data > ())
         {
            string strTreeItem(pitem->m_pitemdata.cast < ::fs::tree_item_data > ()->m_strPath);
            strTreeItem.trim_right("\\/");
            if(strTreeItem.CompareNoCase(strPath) == 0)
               return pitem;
         }
         pitem = pitem->get_next();
      }
      return ::null();
   }

   void tree_interface::arrange(e_arrange earrange)
   {

      if(earrange == arrange_by_name)
      {
         sort(tree_item_data::CompareArrangeByName);
      }

   }

   sp(::fs::document) tree_interface::get_document()
   {
      return  (::user::tree::get_document());
   }

   sp(::fs::tree_data) tree_interface::get_fs_tree_data()
   {
      return ::ca::tree::get_tree_data();
   }


} // namespace fs


