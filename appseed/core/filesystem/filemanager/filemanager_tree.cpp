#include "framework.h"


namespace filemanager
{


   tree::tree(sp(::base::application) papp) :
      element(papp),
      ::data::data(papp),
      ::userfs::tree(papp),
      m_mutexMissinUpdate(papp)
   {

      m_pdataitemCreateImageListStep = NULL;

      m_iAnimate = 0;

      m_bDelayedListUpdate = false;

   }


   tree::~tree()
   {

   }


   void tree::_017EnsureVisible(const char * lpcsz, ::action::context actioncontext)
   {
      stringa stra;
      sp(::data::tree_item) pitem = find_item(lpcsz);
      if(pitem == NULL)
      {
        _017UpdateList(lpcsz,1,actioncontext);
      }

/*      get_document()->set().get_ascendants_path(lpcsz, stra);

      m_straUpdatePtrFilter = stra;

      //for(int32_t i = stra.get_size() - 1; i >= 0; i--)
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         string strAscendant = stra[i];
         sp(::data::tree_item) pitem = find_item(strAscendant);
         if(pitem == NULL)
         {
            string str;
            str = strAscendant;
            if(i == 0)
            {
               _017UpdateList("", NULL, 1, actioncontext);
            }
            else
            {
               get_document()->set().eat_end_level(str, 1);
               _017UpdateList(str, NULL, 1, actioncontext);
            }
         }
         pitem = find_item(strAscendant);
         if(pitem == NULL)
            break;

         if(!(pitem->m_dwState & ::data::tree_item_state_expanded))
         {
            _001ExpandItem(pitem, actioncontext, true, false, false);
         }
      }*/

      pitem = find_item(lpcsz);

      if(pitem == NULL)
         return;

      if(!(pitem->m_dwState & ::data::tree_item_state_expanded))
      {
         _001ExpandItem(pitem,actioncontext,true,false,false);
      }

      m_straUpdatePtrFilter.remove_all();

      {

         single_lock sl(&m_mutexMissinUpdate, TRUE);

         m_straMissingUpdate = stra;

      }

      //_StartDelayedListUpdate();

//      _001EnsureVisible(find_item(lpcsz));

      _001EnsureVisible(pitem);

   }


   sp(::data::tree_item) tree::find_item(const char * lpcsz, ::data::tree_item * pitemStart)
   {
      return find_absolute(lpcsz, pitemStart);
   }

   void tree::_017Browse(const char * lpcsz, ::action::context actioncontext, bool bForceUpdate)
   {
      if(!bForceUpdate)
      {
         sp(::data::tree_item) pitem = find_item(lpcsz);
         if(pitem != NULL)
         {
            _001SelectItem(pitem);
         }
      }

      single_lock slBrowse(&m_csBrowse, TRUE);

      if(strlen(lpcsz) == 0)
      {
         _017UpdateList("", 1, actioncontext);
      }

      _017EnsureVisible(lpcsz, actioncontext);

      _001SelectItem(find_item(lpcsz));

      if (m_treeptra.has_elements())
      {

         _StartCreateImageList(m_treeptra(0));

      }

   }

   void tree::_017UpdateZipList(const char * lpcsz, int32_t iLevel, ::action::context actioncontext)
   {

      string szPath(lpcsz);

      string wstrExtraPath;
      string wstrItemExtra;

      index iFind;
      ::file::binary_buffer_sp spfile(allocer());

      //spfile->open(szPath, ::file::mode_read | ::file::type_binary);

      /*array < ::file::memory_buffer, ::file::memory_buffer & > filea;
      _vmszipFile zipfile;

      zipfile.m_pfile = &file;

      unzFile pf = _vmszipApi::unzipOpen(&zipfile);

      array < ::file::memory_buffer, ::file::memory_buffer & > filea;
      int32_t iStart = 0;
      int32_t iFind;
      while((iFind  = wstrExtra.find(L".zip:", iStart)) >= 0)
      {
      filea.add(::file::memory_buffer());
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
      ::data::tree_item_ptr_array ptraRemove;
//      pitemParent->get_children(ptraRemove);

      for(int32_t i = 0; i < wstraItem.get_size(); i++)
      {
         wstrItem = wstraItem[i];

         sp(::userfs::item) pitemNew = canew(::userfs::item(this));

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
            ::data::tree_item  * pitem    = find_item(pitemNew->m_strPath);
            if(pitem == NULL)
            {
//               pitem = insert_item(pitemNew, ::data::RelativeLastChild, pitemParent);
            }
            else
            {
               pitem = insert_item(pitemNew, ::data::RelativeReplace, pitem);
            }
            str = szPath;
            wstraChildItem.remove_all();
            if(zip::Util().HasSubFolder(get_app(), str))
            {
               pitem->m_dwState |= ::data::tree_item_state_expandable;
            }
            if(iLevel > 1)
            {
               _017UpdateZipList(pitemNew->m_strPath, iLevel - 1, actioncontext);
            }
         }
      }


      remove(ptraRemove);

   }

   void tree::_017UpdateList(const char * lpcsz, int32_t iLevel, ::action::context actioncontext)
   {
      
      if(lpcsz == NULL)
         lpcsz = "";

      stringa straRootPath;

      stringa straRootTitle;

      get_document()->set().root_ones(straRootPath, straRootTitle);

      ::userfs::item * pitemChild;

      m_strPath = lpcsz;

      string strDirParent = System.dir().name(lpcsz);

      sp(::data::tree_item) pitemParent = find_item(strDirParent);

      if(pitemParent.is_null())
      {

         pitemParent = get_base_item();

      }

      sp(::data::tree_item) pitem = find_item(lpcsz);
      

      if(strlen(lpcsz) > 0)
      {
         if(pitem == NULL)
         {

            pitemParent =  get_base_item();

            pitemChild = canew(::userfs::item(this));

            pitemChild->m_strPath = lpcsz;

            pitemChild->m_strName = System.file().name_(lpcsz);

            pitemChild->m_flags.signalize(::fs::FlagFolder);

#ifdef WINDOWSEX

            pitemChild->m_iImage = System.userex()->shellimageset().GetImage(
               NULL,
               pitemChild->m_strPath,
               NULL,
               _shell::IconNormal,
               true);

#else

            pitemChild->m_iImage = -1;

#endif

            pitemChild->m_iImageSelected = m_iDefaultImageSelected;

            pitem = insert_item(pitemChild,::data::RelativeLastChild,pitemParent);

            if(get_document()->set().has_subdir(pitemChild->m_strPath)
               && get_document()->set().tree_show_subdir(pitemChild->m_strPath))
            {
               pitemChild->m_flags.signalize(::fs::FlagHasSubFolder);
            }

            if(pitemChild->m_flags.is_signalized(::fs::FlagHasSubFolder))
            {
               pitem->m_dwState |= ::data::tree_item_state_expandable;
            }

         }
         else
         {

            if(pitem->m_pparent != pitemParent && !straRootPath.contains_ci(pitem->m_pitem.cast < ::fs::item >()->m_strPath))
            {

               pitem->SetParent(pitemParent);

            }

         }

      }

      pitemParent = pitem;

      if(get_filemanager_template() != NULL && get_filemanager_data()->m_ptreeFileTreeMerge != NULL
         && !(dynamic_cast < ::user::tree * > (get_filemanager_data()->m_ptreeFileTreeMerge.m_p))->m_treeptra.contains(this))
      {
         get_filemanager_data()->m_ptreeFileTreeMerge->merge(this);
      }

      sp(::userfs::item) pitemFolder = NULL;

      pitemFolder = pitemParent->m_pitem;

      if(pitemFolder != NULL && pitemFolder->m_flags.is_signalized(::fs::FlagHasSubFolderUnknown))
      {
         if(get_document()->set().has_subdir(pitemFolder->m_strPath)
            && (get_document()->set().tree_show_subdir(pitemFolder->m_strPath)))
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
      int64_array iaSize;


      bool bTreeShowSubdir = get_document()->set().tree_show_subdir(lpcsz);


      if(strlen(lpcsz) == 0)
      {

         straPath = straRootPath;

         straTitle = straRootTitle;

      }
      else
      {
         
         if(bTreeShowSubdir)
         {

            get_document()->set().ls(lpcsz,&straPath,& straTitle,&iaSize);

         }

      }

      pitem = pitemParent->first_child();

      stringa straNew = straPath;

      straNew.trim_right("/\\");

      ::data::tree_item_ptr_array ptraRemove;

      while(pitem != NULL)
      {

         string strPathOld =  pitem->m_pitem.cast < ::userfs::item > ()->m_strPath;

         strPathOld.trim_right("/\\");

         if(!straNew.contains(strPathOld) || !get_filemanager_manager()->get_fs_data()->is_dir(strPathOld))
         {
            ptraRemove.add(pitem);
         }

         pitem = pitem->get_next(false, false);

      }

      remove(ptraRemove);



      int32_t i;

      for(i = 0; i < straPath.get_size(); i++)
      {

         pitem = find_item(straPath[i]);

         string strPath;
         
         if(pitem != NULL)
         {

            strPath = pitem->m_pitem.cast < ::fs::item >()->m_strPath;

            strPath.trim_right(":\\/");

            if(!straRootPath.contains_ci(strPath))
            {
               // reparent

               if(pitem->m_pparent != pitemParent)
               {

                  pitem->SetParent(pitemParent);

               }

               continue;

            }

         }

         pitemChild = canew(::userfs::item(this));

         iChildCount++;

         pitemChild->m_strPath =get_document()->set().dir_path(straPath[i],"");

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

                  pitem = insert_item(pitemChild, ::data::RelativeReplace, pitem);

               }
               else
               {

                  pitem = insert_item(pitemChild, ::data::RelativeLastChild, pitemParent);

               }

               if(zip::Util().HasSubFolder(get_app(), pitemChild->m_strPath))
               {

                  pitem->m_dwState |= ::data::tree_item_state_expandable;

               }

               if(iLevel > 1)
               {

                  _017UpdateZipList(pitemChild->m_strPath, iLevel - 1, actioncontext);

               }

            }
            else
            {
               continue;
            }
         }

         if(get_document()->set().fast_has_subdir(pitemChild->m_strPath) 
            && (get_document()->set().node_path_data(lpcsz) == NULL
            || get_document()->set().node_path_data(lpcsz)->tree_show_subdir(pitemChild->m_strPath)))
         {
            pitemChild->m_flags.signalize(::fs::FlagHasSubFolder);
         }



         pitemChild->m_flags.signalize(::fs::FlagFolder);

#ifdef WINDOWSEX
         try
         {
            pitemChild->m_iImage = System.userex()->shellimageset().GetImage(
               NULL,
               pitemChild->m_strPath,
               NULL,
               _shell::IconNormal,
               true);
            pitemChild->m_iImageSelected = System.userex()->shellimageset().GetImage(
               NULL,
               pitemChild->m_strPath,
               NULL,
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

         pitem = find_item(pitemChild->m_strPath, pitemParent);
         if(pitem != NULL)
         {
            pitem = insert_item(pitemChild, ::data::RelativeReplace, pitem);
            // a refresh or a file monitoring event for folder deletion or creation should
            // the most precisely possible way reset this flag
            pitemChild->m_flags.signalize(::fs::FlagHasSubFolderUnknown);
         }
         else
         {
            pitem = insert_item(pitemChild, ::data::RelativeLastChild, pitemParent);
         }

         if(pitemChild->m_flags.is_signalized(::fs::FlagHasSubFolder))
         {
            pitem->m_dwState |= ::data::tree_item_state_expandable;
         }

         if(iLevel > 1)
         {
            _017UpdateList(pitemChild->m_strPath,  iLevel - 1, actioncontext);
         }

      }

      arrange(::fs::arrange_by_name);

      if(iChildCount == 0)
      {
         pitemParent->m_dwState &= ~::data::tree_item_state_expandable;
      }

      dwTimeOut = get_tick_count();

      TRACE("timeIn%d\n", dwTimeIn);
      TRACE("timeOut%d\n", dwTimeIn);
      TRACE("timeDelta%d\n", dwTimeOut - dwTimeIn);


   }

   void tree::_001UpdateImageList(sp(::data::tree_item) pitem)
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
      ::str::international::utf8_to_unicode(item.m_strExtra),
      _shell::IconNormal);

      item.m_iImageSelected =
      _shell::g_imageset.GetImage(
      oswindow,
      lpsf,
      item.m_lpiidlAbsolute,
      item.m_lpiidlRelative,
      ::str::international::utf8_to_unicode(item.m_strExtra),
      _shell::IconOpen);*/


   }

   void tree::_001InsertColumns()
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

   void tree::GetSelectedFilePath(stringa & stra)
   {

      ::data::tree_item_ptr_array itemptraSelected;

      get_selection(itemptraSelected);

      for(int32_t i = 0; i < itemptraSelected.get_size(); i++)
      {
         stra.add(( (itemptraSelected[0].m_pitem.cast < ::userfs::item > ()))->m_strPath);
      }

   }


   void tree::_017UpdateList(::action::context actioncontext)
   {

      UNREFERENCED_PARAMETER(actioncontext);

   }


   void tree::_001OnMainPostMessage(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
         switch(pbase->m_wparam)
      {
         case MessageMainPostCreateImageListItemRedraw:
         {
            pbase->m_pwnd->RedrawWindow();
            pbase->m_pwnd->KillTimer(123);
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
   ::fs::item & tree::get_filemanager_item()
   {
   return get_filemanager_item;
   }
   */

   void tree::_017Synchronize(::action::context actioncontext)
   {
      _017Browse(get_filemanager_item().m_strPath, actioncontext);
   }

   void tree::install_message_handling(::message::dispatch *pinterface)
   {
      ::userfs::tree::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(MessageMainPost, pinterface,  this,  &tree::_001OnMainPostMessage);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &tree::_001OnTimer);

      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &tree::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &tree::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &tree::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &tree::_001OnCreate);

      //connect_command_range(FILEMANAGER_SHELL_COMMAND_FIRST, FILEMANAGER_SHELL_COMMAND_LAST, &tree::_001OnShellCommand);

   }

   void tree::StartAnimation()
   {
      m_iAnimate = 1;
      m_treeptra(0)->SetTimer(1234567, 50, NULL);

   }

   void tree::TakeAnimationSnapshot()
   {
      m_iAnimate = 1;
      //   ::user::tree::_001OnDraw(m_gdibuffer.GetBuffer());
   }

   void tree::_017PreSynchronize(::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(actioncontext);
      TakeAnimationSnapshot();
   }

#ifdef WINDOWSEX

   IShellFolder * tree::_001GetFolder(EFolder efolder)
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

   int32_t tree::MapToCSIDL(EFolder efolder)
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


   void tree::_001OnItemExpand(::data::tree_item * pitem, ::action::context actioncontext)
   {

      if(typeid(*pitem->m_pitem) == System.type_info < ::userfs::item > ())
      {

         if(get_document()->set().is_link(pitem->m_pitem.cast < ::userfs::item >()->m_strPath))
         {

            string strTarget;

            System.os().resolve_link(strTarget,pitem->m_pitem.cast < ::userfs::item >()->m_strPath);

            pitem = find_item(strTarget);

            _017UpdateList(strTarget, 1,actioncontext);

         }
         else
         {

            _017UpdateList(pitem->m_pitem.cast < ::userfs::item >()->m_strPath,1,actioncontext);

         }

      }
      else
      {

         _017UpdateList("", 1, actioncontext);

      }

   }

   void tree::_001OnItemCollapse(::data::tree_item * pitem, ::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(pitem);
   }

   bool tree::_001IsTranslucent()
   {
      return get_filemanager_data()->m_bTransparentBackground;
   }

   void tree::_001OnOpenItem(::data::tree_item * pitem, ::action::context actioncontext)
   {

      _017OpenFolder(new ::fs::item(*pitem->m_pitem.cast < ::userfs::item > ()), actioncontext);



   }

   void tree::_017OpenFolder(sp(::fs::item)  item, ::action::context actioncontext)
   {

      if(get_document()->set().is_link(item->m_strPath))
      {

         string strTarget;

         System.os().resolve_link(strTarget, item->m_strPath);

         get_filemanager_manager()->FileManagerBrowse(strTarget,actioncontext);

      }
      else
      {

         get_filemanager_manager()->FileManagerBrowse(item,actioncontext);

      }

   }


   void tree::_StartCreateImageList(::user::interaction * pui)
   {

      if(m_pimagelist == NULL)
      {

         m_pimagelist = System.userex()->shellimageset().GetImageList16();

         m_iDefaultImage = System.userex()->shellimageset().GetImage(
            "foo",
            _shell::FileAttributeDirectory,
            _shell::IconNormal);

         m_iDefaultImageSelected = System.userex()->shellimageset().GetImage(
            "foo",
            _shell::FileAttributeDirectory,
            _shell::IconOpen);

      }



      m_pdataitemCreateImageListStep = (sp(::data::tree_item)) get_base_item()->first_child();
      pui->SetTimer(TimerCreateImageList, 80, NULL);

   }

   void tree::_StopCreateImageList(::user::interaction * pui)
   {
      pui->KillTimer(TimerCreateImageList);
   }

   void tree::_CreateImageListStep()
   {
      if(m_pdataitemCreateImageListStep == NULL)
      {
         if (m_treeptra.has_elements())
         {

            _StopCreateImageList(m_treeptra(0));

         }
         return;
      }

      _001UpdateImageList(m_pdataitemCreateImageListStep);

      m_pdataitemCreateImageListStep = m_pdataitemCreateImageListStep->get_item(::data::TreeNavigationProperForward);


   }

   void tree::_001OnTimer(signal_details * pobj)
   {

      SCAST_PTR(::message::timer, ptimer, pobj);

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
      if (ptimer->m_nIDEvent == 1234567)
      {
         m_iAnimate += 2;
         if (m_iAnimate >= 11)
         {
            m_iAnimate = 0;
            ptimer->m_pwnd->KillTimer(ptimer->m_nIDEvent);

         }
         ptimer->m_pwnd->RedrawWindow();
      }
      else if (ptimer->m_nIDEvent == 123)
      {
         ptimer->m_pwnd->_001RedrawWindow();
         m_bTimer123 = false;
         ptimer->m_pwnd->KillTimer(123);
      }

   }


   void tree::_StartDelayedListUpdate()
   {

      m_treeptra(0)->SetTimer(TimerDelayedListUpdate, 500, NULL);

   }


   void tree::_StopDelayedListUpdate()
   {

      m_treeptra(0)->KillTimer(TimerDelayedListUpdate);

   }


   void tree::_DelayedListUpdate()
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

      sp(::data::tree_item) pitem = find_item(m_straMissingUpdate[0]);

      if(pitem != NULL)
      {

         _017UpdateList(m_straMissingUpdate[0], 1, ::action::source_system);

      }

      m_straMissingUpdate.remove_at(0);

      m_bDelayedListUpdate = false;


   }

   COLORREF tree::get_background_color()
   {


   }




#ifdef DEBUG
      void tree::assert_valid() const
      {
         ::data::tree::assert_valid();
      }

      void tree::dump(dump_context & dumpcontext) const
      {
         ::data::tree::dump(dumpcontext);
      }
#endif //DEBUG


      void tree::on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint)
      {
         impact::on_update(pSender, lHint, phint);
         if (phint != NULL)
         {
            if (base_class < update_hint > ::bases(phint))
            {
               update_hint * puh = (update_hint *)phint;
               if (puh->is_type_of(update_hint::TypeInitialize))
               {
                  /* xxx _001SetExpandImage(
                  System.LoadIcon(
                  get_filemanager_template()->m_uiExpandBox));
                  _001SetCollapseImage(
                  System.LoadIcon(
                  get_filemanager_template()->m_uiCollapseBox));*/


                  //            VmsDataInitialize(this);
                  //          SetDataInterface(&m_datainterface);
                  //        AddClient(&m_datainterface);
                  string str;
                  str.Format("tree(%s)", get_filemanager_data()->m_strDISection);
//                  m_dataid = str;
                  //            _001UpdateColumns();

                  if(m_treeptra.get_count() == 1)
                  {

                     m_treeptra[0].m_etranslucency = get_filemanager_data()->m_bTransparentBackground ? ::user::interaction::TranslucencyPresent : ::user::interaction::TranslucencyNone;
                     m_treeptra[0].m_crDefaultBackgroundColor = get_background_color();

                  }

               }
               if (puh->is_type_of(update_hint::TypeSynchronizePath))
               {
                  _017PreSynchronize(::action::source::sync(puh->m_actioncontext));
                  _017Synchronize(::action::source::sync(puh->m_actioncontext));
               }
               if (puh->is_type_of(update_hint::TypeFilter))
               {
                  if (puh->m_wstrFilter.is_empty())
                  {
                     //               FilterClose();
                  }
                  else
                  {
                     //             FilterBegin();
                     //           Filter1(puh->m_wstrFilter);
                     //         FilterApply();
                  }
               }
            }
         }
      }


      void tree::_001OnLButtonDblClk(signal_details * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
         //   int32_t iItem;

         /*   if(_001HitTest_(point, iItem))
         {
         if(m_itema.get_item(iItem).IsFolder())
         {
         ::fs::item item;
         item.m_strPath         = m_itema.get_item(iItem).m_strPath;
         item.m_lpiidlAbsolute   = m_itema.get_item(iItem).m_lpiidlAbsolute;
         item.m_lpiidlRelative   = m_itema.get_item(iItem).m_lpiidlAbsolute;
         get_document()->OpenFolder(item);
         }
         else
         {
         ::fs::item item;
         item.m_strPath         = m_itema.get_item(iItem).m_strPath;
         item.m_lpiidlAbsolute   = m_itema.get_item(iItem).m_lpiidlAbsolute;
         item.m_lpiidlRelative   = m_itema.get_item(iItem).m_lpiidlAbsolute;

         ::fs::item_array itema;
         itema.add(item);

         get_filemanager_data()->OnFileManagerOpenFile(itema);
         }
         }*/
      }

      /*
      bool tree::OnSetData(const ::database::id &key, int32_t iLine, int32_t iColumn, var & var, ::database::update_hint * puh)
      {
      if(key.get_value() == FILE_MANAGER_ID_FILE_NAME)
      {
      ASSERT(var.get_type() == var::type_string
      || var.is_empty());
      string str;
      str = var.m_str;
      RenameFile(iLine, str);
      }
      return true;
      }
      */

      /*
      bool tree::get_data(const ::database::id & key, int32_t iLine, int32_t iColumn, var & var)
      {
      string str;
      if(key.get_value() == FILE_MANAGER_ID_FILE_NAME)
      {
      str = m_itema.get_item(iLine).m_wstrName;
      }
      var.set_type(var::type_string);
      var.m_str = str;
      return true;
      }

      void tree::RenameFile(int32_t iLine, string &wstrNameNew)
      {
      string str = m_itema.get_item(iLine).m_strPath;

      int32_t iFind = str.reverse_find(L'\\');


      string wstrNew = str.Left(iFind + 1) + wstrNameNew;

      if(!::win::shell::MoveFile(str, wstrNew))
      {
      System.simple_message_box("Could not rename the file");
      }

      }*/

      void tree::_001OnContextMenu(signal_details * pobj)
      {
//         SCAST_PTR(::message::context_menu, pcontextmenu, pobj)
            //   int32_t iItem;
            //   HRESULT hr;
//            point ptClient = pcontextmenu->GetPoint();
//         ::user::tree::ScreenToClient(&ptClient);
         /*     if(_001HitTest_(ptClient, iItem))
         {
         CSimpleMenu menu(CBaseMenuCentral::GetMenuCentral());
         if (menu.LoadMenu(get_filemanager_template()->m_uiFilePopup))
         {
         CSimpleMenu* pPopup = (CSimpleMenu *) menu.GetSubMenu(0);
         ASSERT(pPopup != NULL);
         sp(::user::frame_window) pframe = GetTopLevelFrame();

         pframe->SetActiveView(this);

         //IContextMenu * pcontextmenu;

         hr = m_spshellfolder->GetUIObjectOf(
         NULL,
         1,
         (LPCITEMIDLIST *) &m_itema.get_item(iItem).m_lpiidlRelative,
         IID_IContextMenu,
         NULL,
         (void **) &m_contextmenu.m_pcontextmenu);


         if(SUCCEEDED(hr))
         {
         hr = m_contextmenu.m_pcontextmenu->QueryContextMenu(
         pPopup->GetSafeHmenu(),
         0,
         SHELL_COMMAND_FIRST,
         SHELL_COMMAND_LAST,
         CMF_NORMAL);

         }


         pPopup->TrackPopupMenu(
         point.x, point.y,
         (::window_sp) pframe);
         }
         }
         else
         {
         ::user::menu menu;
         if (menu.LoadMenu(get_filemanager_template()->m_uiPopup))
         {
         ::user::menu* pPopup = menu.GetSubMenu(0);
         ASSERT(pPopup != NULL);
         sp(::user::frame_window) pframe = GetTopLevelFrame();
         pPopup->TrackPopupMenu(
         point.x, point.y,
         (::window_sp) pframe);
         }
         }*/
      }




      void tree::_001OnShellCommand(signal_details * pobj)
      {
         SCAST_PTR(::message::command, pcommand, pobj)
            m_contextmenu.OnCommand(pcommand->GetId());
      }

      void tree::_001OnCreate(signal_details * pobj)
      {

         UNREFERENCED_PARAMETER(pobj);

      }




} // namespace filemanager


