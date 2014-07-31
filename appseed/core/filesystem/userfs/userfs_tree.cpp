#include "framework.h"


namespace userfs
{


   tree::tree(sp(::base::application) papp) :
      element(papp),
      ::data::data(papp),
      ::data::tree(papp),
      ::user::tree_data(papp)
   {

      m_pdataitemCreateImageListStep = NULL;

      m_iAnimate = 0;

      m_iDefaultImage = -1;
      m_iDefaultImageSelected = -1;

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
               //if (get_filemanager_template()->get_filemanager_data()->m_bTransparentBackground)
               //{
               //   ::user::tree::m_etranslucency = ::user::tree::TranslucencyPresent;
               //}
               /* xxx _001SetExpandImage(
                  System.LoadIcon(
                  get_filemanager_template()->get_filemanager_template()->m_uiExpandBox));
                  _001SetCollapseImage(
                  System.LoadIcon(
                  get_filemanager_template()->get_filemanager_template()->m_uiCollapseBox));*/


               //            VmsDataInitialize(this);
               //          SetDataInterface(&m_datainterface);
               //        AddClient(&m_datainterface);
               /*               string str;
                              str.Format("tree(%s)", get_filemanager_template()->get_filemanager_data()->m_strDISection);
                              m_dataid = str;*/
               //            _001UpdateColumns();
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

         get_filemanager_template()->get_filemanager_data()->OnFileManagerOpenFile(itema);
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
         if (menu.LoadMenu(get_filemanager_template()->get_filemanager_template()->m_uiFilePopup))
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
         if (menu.LoadMenu(get_filemanager_template()->get_filemanager_template()->m_uiPopup))
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

      get_document()->browse(item->m_strPath, actioncontext);

   }


   void tree::_001OnCreate(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }




   void tree::update_list()
   {

   }


   void tree::browse_sync(::action::context actioncontext)
   {


   }


   void tree::_017EnsureVisible(const char * lpcsz, ::action::context actioncontext)
   {

   }


   sp(::data::tree_item) tree::find_item(const char * lpcsz, ::data::tree_item * pitemStart)
   {

      return find_absolute(lpcsz, pitemStart);

   }




   void tree::_001UpdateImageList(::data::tree_item * pitem)
   {
      UNREFERENCED_PARAMETER(pitem);

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


   void tree::TakeAnimationSnapshot()
   {
      m_iAnimate = 1;
      //   ::user::tree::_001OnDraw(m_gdibuffer.GetBuffer());
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


   COLORREF tree::get_background_color()
   {
      if (get_document() == NULL)
      {
         return RGB(200, 255, 255);
      }
      /*      else if(get_filemanager_template()->get_filemanager_data()->is_saving())
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



