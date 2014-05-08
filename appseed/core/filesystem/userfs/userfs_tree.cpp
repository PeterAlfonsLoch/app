#include "framework.h"


namespace userfs
{


   tree::tree(sp(base_application) papp) :
      element(papp),
      ::data::data(papp),
      ::data::tree(papp)
   {

      m_pdataitemCreateImageListStep = NULL;

      m_iAnimate = 0;
      m_bDelayedListUpdate = false;

   }

   tree::~tree()
   {
   }


#ifdef DEBUG
   void tree::assert_valid() const
   {
   }

   void tree::dump(dump_context &) const
   {
   }
#endif //DEBUG


   void tree::install_message_handling(::message::dispatch * pinterface)
   {
      
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &tree::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &tree::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &tree::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &tree::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &tree::_001OnContextMenu);

   }

   void tree::on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);

      //::filemanager::data_interface::on_update(pSender, lHint, phint);
      if (phint != NULL)
      {
         if (base_class < filemanager::update_hint > ::bases(phint))
         {
            filemanager::update_hint * puh = (filemanager::update_hint *)phint;
            if (puh->is_type_of(filemanager::update_hint::TypeInitialize))
            {
               //if (GetFileManager()->get_filemanager_data()->m_bTransparentBackground)
               //{
               //   ::user::tree::m_etranslucency = ::user::tree::TranslucencyPresent;
               //}
               /* xxx _001SetExpandImage(
                  System.LoadIcon(
                  GetFileManager()->get_filemanager_data()->m_pschema->m_uiExpandBox));
                  _001SetCollapseImage(
                  System.LoadIcon(
                  GetFileManager()->get_filemanager_data()->m_pschema->m_uiCollapseBox));*/


               //            VmsDataInitialize(this);
               //          SetDataInterface(&m_datainterface);
               //        AddClient(&m_datainterface);
               /*               string str;
                              str.Format("tree(%s)", GetFileManager()->get_filemanager_data()->m_strDISection);
                              m_dataid = str;*/
               //            _001UpdateColumns();
            }
            if (puh->is_type_of(filemanager::update_hint::TypeSynchronizePath))
            {
               _017PreSynchronize(::action::source::sync(puh->m_actioncontext));
               _017Synchronize(::action::source::sync(puh->m_actioncontext));
            }
            if (puh->is_type_of(filemanager::update_hint::TypeFilter))
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

         GetFileManager()->get_filemanager_data()->OnFileManagerOpenFile(itema);
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
      
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::context_menu, pcontextmenu, pobj)
         //   int32_t iItem;
         //   HRESULT hr;
//         point ptClient = pcontextmenu->GetPoint();
//      ::user::tree::ScreenToClient(&ptClient);
      /*     if(_001HitTest_(ptClient, iItem))
         {
         CSimpleMenu menu(CBaseMenuCentral::GetMenuCentral());
         if (menu.LoadMenu(GetFileManager()->get_filemanager_data()->m_pschema->m_uiFilePopup))
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
         if (menu.LoadMenu(GetFileManager()->get_filemanager_data()->m_pschema->m_uiPopup))
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



   void tree::_001OnTimer(signal_details * pobj)
   {
      SCAST_PTR(::message::timer, ptimer, pobj)
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

   void tree::StartAnimation(::user::interaction * pui)
   {
      m_iAnimate = 1;
      pui->SetTimer(1234567, 50, NULL);
   }

   void tree::_001OnShellCommand(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   void tree::_017OpenFolder(sp(::fs::item) item, ::action::context actioncontext)
   {

      get_document()->file_manager_browse(item->m_strPath, actioncontext);

   }


   void tree::_001OnCreate(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }




   void tree::update_list()
   {

   }


   void tree::_017UpdateList(const char * lpcsz, int32_t iLevel, ::action::context actioncontext)
   {
      if (lpcsz == NULL)
         lpcsz = "";

      m_strPath = lpcsz;

      //if (pitemParent == NULL)
      //{
        // pitemParent = get_base_item();
      //}
      //else if (get_base_item() == NULL)
      //{
        // m_proot = pitemParent;
      //}

      sp(::data::tree_item) pitemParent;

      stringa straRootPath;

      stringa straRootTitle;

      get_document()->set().root_ones(straRootPath, straRootTitle);


      /*if(GetFileManager() != NULL && GetFileManager()->get_filemanager_data()->m_ptreeFileTreeMerge != NULL
      && !(dynamic_cast < usersp(::tree) > (GetFileManager()->get_filemanager_data()->m_ptreeFileTreeMerge))->m_treeptra.contains(this))
      {
      GetFileManager()->get_filemanager_data()->m_ptreeFileTreeMerge->merge(this);
      }*/

      sp(::userfs::item) pitemFolder = NULL;

      string strRawName1 = typeid(*pitemParent->m_pitem.m_p).name();
      string strRawName2 = typeid(::userfs::item).name();
      if (strRawName1 == strRawName2)
      {
         pitemFolder = pitemParent->m_pitem;
      }


      sp(::userfs::item) pitemChild;
      sp(::data::tree_item) pitem;
      ::data::tree_item_ptr_array ptraRemove;

      if (pitemFolder != NULL && pitemFolder->m_flags.is_signalized(::fs::FlagHasSubFolderUnknown))
      {
         if (get_document()->set().has_subdir(pitemFolder->m_strPath))
         {
            pitemFolder->m_flags.signalize(::fs::FlagHasSubFolder);
         }
         pitemFolder->m_flags.unsignalize(::fs::FlagHasSubFolderUnknown);
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
      int64_array iaSize;
      if (strlen(lpcsz) == 0)
      {
         straPath = straRootPath;
         straTitle = straRootTitle;
      }
      else
      {
         get_document()->set().ls(lpcsz, &straPath, &straTitle, &iaSize);
      }

      int32_t i;

      for (i = 0; i < straPath.get_size(); i++)
      {

         pitemChild = canew(::userfs::item(this));

         pitemChild->m_strPath = straPath[i];

         //if(m_straUpdatePtrFilter.find_first(straPath[i]) >= 0)
         //{
         //   continue;
         //}
         pitemChild->m_strName = straTitle[i];
         if (!get_document()->set().is_dir(straPath[i]))
         {
            if (zip::Util().IsUnzipable(get_app(), pitemChild->m_strPath))
            {
               pitemChild->m_flags.signalize(::fs::FlagFolder);


               pitemChild->m_iImage = m_iDefaultImage;
               pitemChild->m_iImageSelected = m_iDefaultImageSelected;
               pitemChild->m_flags.signalize(::fs::FlagInZip);

               pitem = find_item(pitemChild->m_strPath);
               if (pitem != NULL)
               {
                  pitem = insert_item(pitemChild, ::data::RelativeReplace, pitem);
               }
               else
               {
                  pitem = insert_item(pitemChild, ::data::RelativeLastChild, pitemParent);
               }

               if (zip::Util().HasSubFolder(get_app(), pitemChild->m_strPath))
               {
                  pitem->m_dwState |= ::data::tree_item_state_expandable;
               }

               if (iLevel > 1)
               {
                  _017UpdateZipList(pitemChild->m_strPath, pitem, iLevel - 1, actioncontext);
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

         if (pitem != NULL)
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

         if (pitemChild->m_flags.is_signalized(::fs::FlagHasSubFolder))
         {

            pitem->m_dwState |= ::data::tree_item_state_expandable;

         }

         if (iLevel > 1)
         {

            _017UpdateList(pitemChild->m_strPath, iLevel - 1, actioncontext);

         }

      }

      for (int32_t j = 0; j < ptraRemove.get_size(); j++)
      {

         ptraRemove(j).release();

      }

      arrange(::fs::arrange_by_name);

      if (iChildCount == 0)
      {
         pitemParent->m_dwState &= ~::data::tree_item_state_expandable;
      }



   }


   void tree::_017EnsureVisible(const char * lpcsz, ::action::context actioncontext)
   {
      stringa stra;

      get_document()->set().get_ascendants_path(lpcsz, stra);

      m_straUpdatePtrFilter = stra;



      //for(int32_t i = stra.get_size() - 1; i >= 0; i--)
      for (index i = 0; i < stra.get_size(); i++)
      {
         string strAscendant = stra[i];
         sp(::data::tree_item) pitem = find_item(strAscendant);
         if (pitem == NULL)
         {
            string str;
            str = strAscendant;
            get_document()->set().eat_end_level(str, 1);
            _017UpdateList(str, 1, actioncontext);
         }
         pitem = find_item(strAscendant);
         if (pitem == NULL)
            break;

         if (!(pitem->m_dwState & ::data::tree_item_state_expanded))
         {
            _001ExpandItem(pitem, actioncontext, true, false, false);
         }
      }


      m_straUpdatePtrFilter.remove_all();

      m_straMissingUpdate = stra;


      _StartDelayedListUpdate();

      sp(::data::tree_item) pitem = find_item(lpcsz);

      _001EnsureVisible(pitem);

   }


   sp(::data::tree_item) tree::find_item(const char * lpcsz, ::data::tree_item * pitemStart)
   {

      return find_absolute(lpcsz, pitemStart);

   }


   void tree::_017Browse(const char * lpcsz, ::action::context actioncontext, bool bForceUpdate)
   {

      if (!bForceUpdate)
      {
         
         selection_set(find_item(lpcsz), true, true);
         
         return;

      }

      single_lock slBrowse(&m_csBrowse, TRUE);

      if (strlen(lpcsz) == 0)
      {

         _017UpdateList("",  1, actioncontext);

      }

      _017EnsureVisible(lpcsz, actioncontext);

      _001SelectItem(find_item(lpcsz));

      _StartCreateImageList();

   }

   void tree::_017UpdateZipList(const char * lpcsz, ::data::tree_item * pitemParent, int32_t iLevel, ::action::context actioncontext)
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
      pitemParent->get_children(ptraRemove);

      for (int32_t i = 0; i < wstraItem.get_size(); i++)
      {
         wstrItem = wstraItem[i];

         sp(::userfs::item) pitemNew = canew(::userfs::item(this));

         pitemNew->m_strPath = lpcsz;
         pitemNew->m_flags.signalize(::fs::FlagInZip);

         wstrExtraPath = wstrItem;

         // ignore this file if its not in the Extra sub folder
         /*         if(wstrExtraPath.Left(wstrExtra.get_length()) != wstrExtra ||
         wstrExtraPath == wstrExtra)
         continue;*/

         //         wstrItemExtra = wstrExtraPath.Mid(wstrExtra.get_length());

         pitemNew->m_flags.unsignalize_all();

         iFind = wstrItemExtra.find("/");
         if (iFind > 0)
         {
            wstrFolder = wstrItemExtra.Left(iFind);
            if (wstraFolder.find_first(wstrFolder) >= 0)
               continue;
            wstraFolder.add(wstrFolder);
            pitemNew->m_flags.signalize(::fs::FlagFolder);
            pitemNew->m_strPath = szPath;
            pitemNew->m_iImage = -1;
            pitemNew->m_strName = wstrFolder;
            //               pitemNew->m_strExtra  = wstrExtra + wstrFolder + "/";
         }
         else
         {
            pitemNew->m_strPath = szPath;
            pitemNew->m_iImage = -1;
            pitemNew->m_strName = wstrItemExtra;
            //             pitemNew->m_strExtra  = wstrExtraPath;
            string str;
            str = szPath + wstrExtraPath;
            if (zip::Util().IsUnzipable(get_app(), str))
            {
               pitemNew->m_flags.signalize(::fs::FlagFolder);
            }
         }
         if (pitemNew->m_flags.is_signalized(::fs::FlagFolder))
         {
            pitemNew->m_iImage = m_iDefaultImage;
            pitemNew->m_iImageSelected = m_iDefaultImageSelected;
            //         item.m_flags.signalize(FlagInZip);
            ::data::tree_item  * pitem = find_item(pitemNew->m_strPath);
            if (pitem == NULL)
            {
               pitem = insert_item(pitemNew, ::data::RelativeLastChild, pitemParent);
            }
            else
            {
               pitem = insert_item(pitemNew, ::data::RelativeReplace, pitem);
            }
            str = szPath;
            wstraChildItem.remove_all();
            if (zip::Util().HasSubFolder(get_app(), str))
            {
               pitem->m_dwState |= ::data::tree_item_state_expandable;
            }
            if (iLevel > 1)
            {
               _017UpdateZipList(pitemNew->m_strPath, pitem, iLevel - 1, actioncontext);
            }
         }
      }


      remove(ptraRemove);

   }


   void tree::_001UpdateImageList(::data::tree_item * pitem)
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

      for (int32_t i = 0; i < itemptraSelected.get_size(); i++)
      {

         stra.add(itemptraSelected(0)->m_pitem.cast < ::userfs::item >()->m_strPath);

      }

   }


   void tree::_017UpdateList(::action::context actioncontext)
   {

      UNREFERENCED_PARAMETER(actioncontext);

   }



   void tree::_017Synchronize(::action::context actioncontext)
   {
      _017Browse(get_document()->m_strFolder, actioncontext);
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

   /*   IShellFolder * tree::_001GetFolder(EFolder efolder)
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
   }*/

   /*   int32_t tree::MapToCSIDL(EFolder efolder)
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

   void tree::_001OnItemExpand(::data::tree_item * pitem, ::action::context actioncontext)
   {
      if (typeid(*pitem->m_pitem) == System.type_info < ::userfs::item >())
      {
         _017UpdateList(pitem->m_pitem.cast < ::userfs::item >()->m_strPath, 1, actioncontext);
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
      return true;
   }

   void tree::_001OnOpenItem(::data::tree_item * pitem, ::action::context actioncontext)
   {

      _017OpenFolder(canew(::fs::item(*pitem->m_pitem.cast < ::userfs::item >())), actioncontext);

   }



   void tree::_StartCreateImageList()
   {
      m_pdataitemCreateImageListStep = (sp(::data::tree_item)) get_base_item()->m_children.first_element();
      //         SetTimer(TimerCreateImageList, 80, NULL);
   }

   void tree::_StopCreateImageList()
   {
      //       KillTimer(TimerCreateImageList);
   }

   void tree::_CreateImageListStep()
   {
      if (m_pdataitemCreateImageListStep == NULL)
      {
         _StopCreateImageList();
         return;
      }

      _001UpdateImageList(m_pdataitemCreateImageListStep);

      m_pdataitemCreateImageListStep = m_pdataitemCreateImageListStep->get_item(::data::TreeNavigationProperForward);


   }


   void tree::_StartDelayedListUpdate()
   {
      //SetTimer(TimerDelayedListUpdate, 500, NULL);
   }

   void tree::_StopDelayedListUpdate()
   {
      //KillTimer(TimerDelayedListUpdate);
   }

   void tree::_DelayedListUpdate()
   {

      if (m_straMissingUpdate.get_size() == 0)
      {

         _StopDelayedListUpdate();

         return;

      }

      if (m_bDelayedListUpdate)
         return;

      m_bDelayedListUpdate = true;

      sp(::data::tree_item) pitem = find_item(m_straMissingUpdate[0]);
      
      if (pitem != NULL)
      {

         _017UpdateList(m_straMissingUpdate[0], 1, ::action::source_system);

      }

      m_straMissingUpdate.remove_at(0);

      m_bDelayedListUpdate = false;

   }

   COLORREF tree::get_background_color()
   {
      if (get_document() == NULL)
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

   sp(::data::tree_item) tree::find_absolute(const char * lpcszPath, ::data::tree_item * pitemStart)
   {
      sp(::data::tree_item) pitem;

      if(pitemStart == NULL)
         pitem = get_base_item();
      else
         pitem = pitemStart;

      if (lpcszPath == NULL || strlen(lpcszPath) == 0)
         return pitem;
      string strPath(lpcszPath);
      strPath.trim_right("\\/");
      while (pitem != NULL)
      {
         if (pitem->m_pitem != NULL
            && typeid(*pitem->m_pitem) == System.type_info < ::userfs::item >())
         {
            string strTreeItem(pitem->m_pitem.cast < ::userfs::item >()->m_strPath);
            strTreeItem.trim_right("\\/");
            if (strTreeItem.CompareNoCase(strPath) == 0)
               return pitem;
         }
         pitem = pitem->get_next();
         if(pitem == pitemStart)
            break;
      }
      return NULL;
   }

   void tree::arrange(::fs::e_arrange earrange)
   {

      if (earrange == ::fs::arrange_by_name)
      {
         sort(item::CompareArrangeByName);
      }

   }

   sp(::userfs::document) tree::get_document()
   {
      return  (::data::data::get_document());
   }



} // namespace userfs



