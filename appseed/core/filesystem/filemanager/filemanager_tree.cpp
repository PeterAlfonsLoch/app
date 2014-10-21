#include "framework.h"


namespace filemanager
{


   tree::tree(sp(::aura::application) papp) :
      element(papp),
      ::data::data(papp),
      ::data::tree(papp),
      ::user::tree_data(papp),
      ::userfs::tree(papp),
      m_mutexData(papp),
      m_threadPolishing(m_mutexData),
      m_threadPolishingLowLatency(m_mutexData)
   {

      m_iAnimate = 0;

      m_pimagelist = Platform.userex()->shellimageset().GetImageList16();

   }


   tree::~tree()
   {

   }


   void tree::_017EnsureVisible(const char * lpcsz, ::action::context actioncontext)
   {
      stringa stra;
      sp(::data::tree_item) pitem = find_item(lpcsz);


      pitem = find_item(lpcsz);

      if(pitem == NULL)
         return;

      if(!(pitem->m_dwState & ::data::tree_item_state_expanded))
      {
         _001ExpandItem(pitem,actioncontext,true,false,false);
      }

      m_straUpdatePtrFilter.remove_all();

      _001EnsureVisible(pitem);

   }


   sp(::data::tree_item) tree::find_item(const char * lpcsz, ::data::tree_item * pitemStart)
   {

      return find_absolute(lpcsz, pitemStart);

   }


   void tree::knowledge(const string & strPath,::action::context actioncontext,bool bOnlyParent)
   {

      if(bOnlyParent && strPath.has_char() && find_item(strPath))
         return;

      stringa straPath;
      stringa straTitle;
      int64_array iaSize;
      bool_array baDir;

      string strDir;

      if(bOnlyParent && strPath.has_char())
      {

         strDir = System.dir().name(strPath);

         straPath.add(strPath);

         straTitle.add(System.file().name_(strPath));

         iaSize.add(-1);

         baDir.add(true);

      }
      else
      {

         strDir = strPath;

         get_document()->get_fs_data()->ls(strPath,&straPath,&straTitle,&iaSize,&baDir);

      }

      single_lock sl(&m_mutexData,true);

      filemanager_tree_insert(strDir,straPath,straTitle,iaSize,baDir,actioncontext, bOnlyParent);

      ::data::tree_item * pitem = find_item(strDir);

      if(pitem != NULL)
      {
         if(straPath.get_count() > 0)
         {

            pitem->m_dwState |= ::data::tree_item_state_expanded;
            pitem->m_dwState |= ::data::tree_item_state_expandable;

         }
      }


      if(!bOnlyParent)
      {

         arrange(::fs::arrange_by_name);

         if(m_treeptra.has_elements())
         {

            _polishing_start(m_treeptra[0]);

         }

      }

   }


   void tree::filemanager_tree_insert(const string & strPath, stringa & straPath,stringa & straTitle,int64_array & iaSize,bool_array & baDir,::action::context actioncontext, bool bOnlyParent)
   {

      single_lock sl(&m_mutexData,true);

      stringa & straRootPath = get_document()->m_straRootPath;

//      stringa & straRootTitle = get_document()->m_straRootTitle;

  //    bool bTreeShowSubdir = get_document()->get_fs_data()->tree_show_subdir(strPath);

      ::data::tree_item_ptr_array ptraRemove;

      sp(::data::tree_item) pitem = find_item(strPath);

      if(pitem.is_null())
         return;

      sp(::data::tree_item) pitemParent = pitem;

      if(strPath.has_char() && !bOnlyParent)
      {

         pitem = pitemParent->first_child();

         if(pitem.is_set())
         {

            stringa straPathTrim;

            straPathTrim = straPath;

            straPathTrim.trim_right("\\/");

            index iFind;

            while(pitem != NULL)
            {

               string strPathOld =  pitem->m_pitem.cast < ::userfs::item >()->m_strPath;

               strPathOld.trim_right("/\\");

               iFind = straPathTrim.find_first_ci(strPathOld);

               if(iFind < 0 || !baDir[iFind])
               {

                  ptraRemove.add(pitem);

               }

               pitem = pitem->get_next(false,false);

            }

            remove(ptraRemove);

         }

      }


      stringa straRootPathTrim;

      straRootPathTrim = straRootPath;

      straRootPathTrim.trim_right(":\\/");

      int32_t iChildCount= 0;

      int32_t i;

      string strItem;

      string strCheck;

      for(i = 0; i < straPath.get_size(); i++)
      {

         strItem = straPath[i];

         if(strItem.is_empty())
            continue;

         pitem = find_item(strItem);

         if(pitem != NULL)
         {

            if(pitem->m_pitem.is_set())
            {

               strCheck = pitem->m_pitem.cast < ::fs::item >()->m_strPath;

               strCheck.trim_right(":\\/");

               if(!straRootPathTrim.contains_ci(strCheck))
               {

                  // reparent

                  if(pitem->m_pparent != pitemParent)
                  {

                     pitem->SetParent(pitemParent);

                  }

                  continue;

               }

            }

         }

         ::userfs::item * pitemChild = canew(::userfs::item(this));

         iChildCount++;

         pitemChild->m_strPath = get_document()->get_fs_data()->dir_path(strItem,"");

         pitemChild->m_strName = straTitle[i];

         if(!baDir[i])
         {

            /*            if(zip::Util().IsUnzipable(get_app(), pitemChild->m_strPath))
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

/*               if(iLevel > 1)
               {

                  _017UpdateZipList(pitemChild->m_strPath, iLevel - 1, actioncontext);

               }*/

            //}
            //else
            {

               continue;

            }

         }

         pitemChild->m_flags.signalize(::fs::FlagFolder);

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

      }

      if(iChildCount == 0)
      {

         pitemParent->m_dwState &= ~::data::tree_item_state_expandable;

      }

   }


   void tree::browse_sync(::action::context actioncontext)
   {

      single_lock sl(&m_mutexData,true);

      stringa & straRootPath = get_document()->m_straRootPath;

//      stringa & straRootTitle = get_document()->m_straRootTitle;

      string strPath = get_filemanager_item().m_strPath;

      m_strPath = strPath;

      if(actioncontext.m_spdata.is_set() && (actioncontext.m_spdata->m_esource &::action::source_system))
      {

         knowledge("",actioncontext,true);

         if(strPath.has_char())
         {
            stringa stra;

            get_filemanager_manager()->get_fs_data()->get_ascendants_path(strPath,stra);

            for(index i = 0; i < stra.get_size(); i++)
            {

               string str = stra[i];

               knowledge(str,actioncontext,true);

            }

         }

      }



      ::userfs::item * pitemChild;

      string strDirParent = System.dir().name(m_strPath);

      sp(::data::tree_item) pitemParent = find_item(strDirParent);

      if(pitemParent.is_null())
      {

         pitemParent = get_base_item();

      }




      sp(::data::tree_item) pitem = find_item(strPath);

      if(strPath.has_char())
      {

         if(pitem == NULL)
         {

            pitemParent =  get_base_item();

            pitemChild = canew(::userfs::item(this));

            pitemChild->m_strPath = strPath;

            pitemChild->m_strName = System.file().name_(strPath);

            pitemChild->m_flags.signalize(::fs::FlagFolder);

            pitemChild->m_iImageSelected = m_iDefaultImageSelected;

            pitem = insert_item(pitemChild,::data::RelativeLastChild,pitemParent);

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

         get_filemanager_data()->m_ptreeFileTreeMerge->merge(this, true);

      }

      stringa straChildItem;

      string str;

      stringa & straPath = get_document()->m_straPath;

      stringa & straTitle = get_document()->m_straTitle;

      int64_array & iaSize = get_document()->m_iaSize;

      bool_array & baDir = get_document()->m_baDir;

      if(actioncontext.m_spdata.is_null() || !(actioncontext.m_spdata->m_esource &::action::source_system))
      {

         filemanager_tree_insert(strPath,straPath,straTitle,iaSize,baDir,actioncontext);

         _017EnsureVisible(strPath,actioncontext);

         _001SelectItem(find_item(strPath));

      }

      arrange(::fs::arrange_by_name);

      if(m_treeptra.has_elements())
      {

         _polishing_start(m_treeptra[0]);

      }

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
         stra.add(( (itemptraSelected[0]->m_pitem.cast < ::userfs::item > ()))->m_strPath);
      }

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
      m_treeptra[0]->SetTimer(1234567, 50, NULL);

   }

   void tree::TakeAnimationSnapshot()
   {
      m_iAnimate = 1;
      //   ::user::tree::_001OnDraw(m_gdibuffer.GetBuffer());
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

         if(get_document()->get_fs_data()->is_link(pitem->m_pitem.cast < ::userfs::item >()->m_strPath))
         {

            string strTarget;

            System.file().resolve_link(strTarget,pitem->m_pitem.cast < ::userfs::item >()->m_strPath);

            pitem = find_item(strTarget);

            knowledge(strTarget,actioncontext);

         }
         else
         {

            knowledge(pitem->m_pitem.cast < ::userfs::item >()->m_strPath,actioncontext);

         }

      }
      else
      {

         knowledge("",actioncontext);

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

      if(get_document()->get_fs_data()->is_link(item->m_strPath))
      {

         string strTarget;

         System.file().resolve_link(strTarget, item->m_strPath);

         get_filemanager_manager()->FileManagerBrowse(strTarget,actioncontext);

      }
      else
      {

         get_filemanager_manager()->FileManagerBrowse(item,actioncontext);

      }

   }


   tree::polishing::polishing(sp(::aura::application) papp, ::filemanager::tree * ptree,::user::tree * pusertree, bool bLowLatency) :
      element(papp),
      thread(papp)
   {

      m_ptree        = ptree;
      m_pusertree    = pusertree;
      m_bLowLatency  = bLowLatency;
      m_pdataitem    = NULL;



   }


   int32_t tree::polishing::run()
   {

      single_lock sl(&m_ptree->m_mutexData,true);

      int iBatchSize = 5;

      m_pdataitem = (::data::tree_item *) m_ptree->get_base_item()->first_child();

      m_estep = (e_step)(((int)step_start) + 1);

      while(m_bRun)
      {

         for(index i = 0; i < iBatchSize; i++)
         {
            if(!m_bRun || !step(sl))
               goto finish;
         }

         sl.unlock();

         sl.lock();


      }

   finish:

      return 0;

   }


   void tree::_polishing_start(::user::tree * pusertree)
   {

      m_threadPolishing.replace(canew(polishing(get_app(),this,pusertree, false)));
      m_threadPolishingLowLatency.replace(canew(polishing(get_app(),this,pusertree,true)));

   }


   bool tree::polishing::step(single_lock & sl)
   {

      if(m_pdataitem == NULL)
      {

         m_estep = (e_step)(((int)m_estep) + 1);

         if(m_estep >= step_end)
         {

            return false;

         }

         m_pdataitem = (sp(::data::tree_item)) m_ptree->get_base_item()->first_child();


         if(m_pdataitem == NULL)
            return false;


      }

      m_ptree->_polishing_step(sl, m_pdataitem, m_bLowLatency, m_estep);

      m_pdataitem = m_pdataitem->get_item(::data::TreeNavigationExpandedForward);

      return true;

   }


   void tree::_polishing_step(single_lock & sl, ::data::tree_item * pitem, bool bLowLatency, e_step estep)
   {

      if(pitem == NULL)
         return;


      sp(::userfs::item) item = pitem->m_pitem.cast < ::userfs::item >();

      if(bLowLatency)
      {
         if(get_document()->get_fs_data()->is_zero_latency(item->m_strPath))
            return;
      }
      else
      {
         if(!get_document()->get_fs_data()->is_zero_latency(item->m_strPath))
            return;
      }

      if(estep == step_has_subdir_visible)
      {
         if(pitem->m_pparent.is_set() && ((estep == step_has_subdir_visible && pitem->m_pparent->is_expanded())
            || (estep == step_has_subdir_hidden && !pitem->m_pparent->is_expanded())))
         {
            if(!(pitem->m_dwState & ::data::tree_item_state_expandable))
            {
               string strPath = item->m_strPath;
               if(bLowLatency)
               {
                  //sl.unlock();
                  //if(get_document()->get_fs_data()->tree_show_subdir(strPath)
                    // && get_document()->get_fs_data()->has_subdir(strPath))
                  {
                    // sl.lock();
                     //item->m_flags.signalize(::fs::FlagHasSubFolder);
                     pitem->m_dwState |= ::data::tree_item_state_expandable;
                     item->m_flags.signalize(::fs::FlagHasSubFolderUnknown);
                  }
                  //else
                  //{
                    // sl.lock();
                  //}
               }
               else
               {
                  if(get_document()->get_fs_data()->tree_show_subdir(strPath)
                     && get_document()->get_fs_data()->has_subdir(strPath))
                  {
                     item->m_flags.signalize(::fs::FlagHasSubFolder);
                     pitem->m_dwState |= ::data::tree_item_state_expandable;
                  }
               }
            }
         }
      }
      else if(estep == step_image_visible || estep == step_image_hidden)
      {

         if((item->m_iImage < 0 ||
            item->m_iImageSelected < 0) && pitem->m_pparent.is_set() && ((estep == step_image_visible && pitem->m_pparent->is_expanded())
            || (estep == step_image_hidden && !pitem->m_pparent->is_expanded())))
         {

#ifdef WINDOWSEX
            m_pimagelist = Platform.userex()->shellimageset().GetImageList16();
            try
            {
               item->m_iImage = Platform.userex()->shellimageset().GetImage(m_treeptra[0]->get_handle(),item->m_strPath,_shell::FileAttributeDirectory,_shell::IconNormal);
               item->m_iImageSelected = Platform.userex()->shellimageset().GetImage(m_treeptra[0]->get_handle(),item->m_strPath,_shell::FileAttributeDirectory,_shell::IconOpen);
            }
            catch(...)
            {
               item->m_iImage = m_iDefaultImage;
               item->m_iImageSelected = m_iDefaultImageSelected;
            }

            if(item->m_iImage < 0)
            {
               item->m_iImage = MAX(0,m_iDefaultImage);
            }
            if(item->m_iImageSelected < 0)
            {
               item->m_iImageSelected = MAX(0, m_iDefaultImageSelected);
            }
#else

            item->m_iImage = m_iDefaultImage;
            item->m_iImageSelected = m_iDefaultImageSelected;

#endif
         }

      }

   }


   void tree::_001OnTimer(signal_details * pobj)
   {

      SCAST_PTR(::message::timer, ptimer, pobj);



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
         ptimer->m_pwnd->RedrawWindow();
         m_bTimer123 = false;
         ptimer->m_pwnd->KillTimer(123);
      }

   }





      void tree::assert_valid() const
      {
         ::data::tree::assert_valid();
      }

      void tree::dump(dump_context & dumpcontext) const
      {
         ::data::tree::dump(dumpcontext);
      }


      void tree::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
      {
         ::filemanager::impact::on_update(pSender, lHint, phint);
         if (phint != NULL)
         {
            if (base_class < update_hint > ::bases(phint))
            {
               update_hint * puh = (update_hint *)phint;
               if (puh->is_type_of(update_hint::TypeInitialize))
               {


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

         pobj->previous();



      }


      void tree::on_merge_user_tree(::user::tree * pusertree)
      {

         m_iDefaultImage = Platform.userex()->shellimageset().GetImage(
            pusertree->get_handle(),
            "foo",
            _shell::FileAttributeDirectory,
            _shell::IconNormal);

         m_iDefaultImageSelected = Platform.userex()->shellimageset().GetImage(
            pusertree->get_handle(),
            "foo",
            _shell::FileAttributeDirectory,
            _shell::IconOpen);

      }


      void tree::on_bind_user_tree(::user::tree * pusertree)
      {

         UNREFERENCED_PARAMETER(pusertree);

      }




} // namespace filemanager


