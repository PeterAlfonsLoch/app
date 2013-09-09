#include "framework.h"
#include "FileManagerViewUpdateHint.h"
#include "SimpleFileListView.h"

#define SHELL_COMMAND_FIRST 0x1000
#define SHELL_COMMAND_LAST 0x2000


namespace filemanager
{

   SimpleFileListView::SimpleFileListView(sp(base_application) papp) :
      element(papp),
      ::user::interaction(papp),
      ::user::form(papp),
      ::user::form_list(papp),
      SimpleFileListInterface(papp),
      ::user::scroll_view(papp),
      ::user::list(papp),
      ::userfs::list_interface(papp),
      ::userfs::list(papp)
   {

      m_bFileSize = false;
      m_bShow = false;
      m_dwLastFileSize = ::get_tick_count();

      m_pheaderctrl     = &m_headerctrl;
      m_pheaderctrl->SetBaseListCtrlInterface(this);

      connect_update_cmd_ui("edit_copy", &SimpleFileListView::_001OnUpdateEditCopy);
      connect_command("edit_copy", &SimpleFileListView::_001OnEditCopy);
      connect_update_cmd_ui("edit_paste", &SimpleFileListView::_001OnUpdateEditPaste);
      connect_command("edit_paste", &SimpleFileListView::_001OnEditPaste);
      connect_update_cmd_ui("trash_that_is_not_trash", &SimpleFileListView::_001OnUpdateTrashThatIsNotTrash);
      connect_command("trash_that_is_not_trash", &SimpleFileListView::_001OnTrashThatIsNotTrash);
      connect_update_cmd_ui("open_with", &SimpleFileListView::_001OnUpdateOpenWith);
      connect_update_cmd_ui("spafy", &SimpleFileListView::_001OnUpdateSpafy);
      connect_command("spafy", &SimpleFileListView::_001OnSpafy);
      connect_update_cmd_ui("spafy2", &SimpleFileListView::_001OnUpdateSpafy2);
      connect_command("spafy2", &SimpleFileListView::_001OnSpafy2);
      connect_update_cmd_ui("file_rename", &SimpleFileListView::_001OnUpdateFileRename);
      connect_command("file_rename", &SimpleFileListView::_001OnFileRename);

   }

   SimpleFileListView::~SimpleFileListView()
   {
   }

   void SimpleFileListView::install_message_handling(::message::dispatch * pinterface)
   {
      ::user::view::install_message_handling(pinterface);
      SimpleFileListInterface::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &SimpleFileListView::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &SimpleFileListView::_001OnTimer);
      connect_command_range(SHELL_COMMAND_FIRST, SHELL_COMMAND_LAST, &SimpleFileListView::_001OnShellCommand);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &SimpleFileListView::_001OnShowWindow);

   }





   #ifdef DEBUG
   void SimpleFileListView::assert_valid() const
   {
      ::user::view::assert_valid();
   }

   void SimpleFileListView::dump(dump_context & dumpcontext) const
   {
      ::user::view::dump(dumpcontext);
   }
   #endif //DEBUG


   void SimpleFileListView::on_update(sp(::user::view) pSender, LPARAM lHint, object* phint)
   {

      FileManagerViewInterface::on_update(pSender, lHint, phint);

      if(m_bStatic && lHint == hint_add_location)
      {

         stringa stra;

         GetFileManager()->data_get(GetFileManager()->get_filemanager_data()->m_ptemplate->m_dataidStatic, ::core::system::idEmpty, stra);

         string strPath = GetFileManager()->get_item().m_strPath;

         strPath.trim();

         if(strPath.has_char() && GetFileManager()->get_fs_data()->is_dir(strPath))
         {

            if(stra.add_unique(strPath) >= 0)
            {

               GetFileManager()->data_set(GetFileManager()->get_filemanager_data()->m_ptemplate->m_dataidStatic, ::core::system::idEmpty, stra);

               add_item(GetFileManager()->get_item().m_strPath, System.file().name_(GetFileManager()->get_item().m_strPath));
            
               _001OnUpdateItemCount();

            }

         }

      }
      else if(lHint == 123)
      {
         _017UpdateList();
      }
      else if(lHint == 1234)
      {
         _001UpdateColumns();
         _017UpdateList();
      }
      else if(lHint == 123458)
      {
         _001SetView(ViewList);
      }
      else if(lHint == 1234511)
      {
         _001SetView(ViewReport);
      }
      else if(lHint == 1234525)
      {
         _001SetView(ViewIcon);
      }
      if(phint != NULL)
      {
         if(base < FileManagerViewUpdateHint >::bases(phint))
         {
            FileManagerViewUpdateHint * puh = (FileManagerViewUpdateHint *) phint;
            if(puh->is_type_of(FileManagerViewUpdateHint::TypeInitialize))
            {
               m_pbaseapp = get_app()->m_pplaneapp;
               db_server * pcentral = dynamic_cast < db_server * > (&System.m_simpledb.db());
               if(pcentral == NULL)
                  return;
               //DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;
               SetTimer(5432185, 230, NULL);
               //::user::window::SetTimer(5432184, 23, NULL);
   // dbbreak            m_pserverNext = simpledb::get(get_app())->GetDataServer();
   //            AddClient(this);
     //          SetDataInterface(&m_datainterface);
       //        AddClient(&m_datainterface);
               string str;
               str.Format("SimpleFileListView(%s)", GetFileManager()->get_filemanager_data()->m_strDISection);
               if(GetFileManager()->get_filemanager_data()->m_bPassBk)
               {
                  ::user::list::m_bBackgroundBypass = true;
               }
               else if(GetFileManager()->get_filemanager_data()->m_bTransparentBackground)
               {
                  ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
               }
               m_dataid = str;
               _001UpdateColumns();

            }
            else if(!m_bStatic && puh->is_type_of(FileManagerViewUpdateHint::TypeSynchronizePath))
            {
               if(GetFileManager()->get_filemanager_data()->m_pholderFileList != NULL)
               {
                  if(GetFileManager()->get_filemanager_data()->m_pholderFileList->m_uiptraHold.get_size() > 0)
                  {
                     GetFileManager()->get_filemanager_data()->m_pholderFileList->m_uiptraHold[0].ShowWindow(SW_HIDE);
                  }
                  GetFileManager()->get_filemanager_data()->m_pholderFileList->hold(this);
                  GetFileManager()->get_filemanager_data()->m_pholderFileList->layout();
               }
               _017PreSynchronize();
               _017Synchronize();
               data_get_DisplayToStrict();
               _001OnUpdateItemCount();
               /*string str;
               if(data_get("sort-" + GetFileManager()->get_item().m_strPath, ::core::system::idEmpty, str))
               {
                  stringa stra;
                  stra.add_tokens(str, ";", true);
                  if(stra.get_size() == m_iaDisplayToStrict.get_size())
                  {
                     for(int32_t i = 0; i < m_iaDisplayToStrict.get_size(); i++)
                     {
                        m_iaDisplayToStrict.set(i, atoi(stra[i]));
                     }
                  }
               }*/
            }
            else if(m_bStatic && puh->is_type_of(FileManagerViewUpdateHint::TypeSynchronizeLocations))
            {
               _017UpdateList();
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeFilter))
            {
               if(puh->m_wstrFilter.is_empty())
               {
                  FilterClose();
               }
               else
               {
                  FilterBegin();
                  Filter1(puh->m_wstrFilter);
//                  FilterApply();
               }
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeGetActiveViewSelection))
            {
               if(GetParentFrame()->GetActiveView() ==  (this))
               {
                  GetSelected(puh->m_itemaSelected);
               }
            }
         }
         else if(base < form_update_hint > :: bases(phint))
         {
            form_update_hint * puh = dynamic_cast<form_update_hint * > (phint);
            if(puh->m_etype == form_update_hint::type_after_browse)
            {
               if(puh->m_strForm == "filemanager\\replace_name_in_file_system.xhtml")
               {
                  html::elemental * pelemental = dynamic_cast < html::elemental * > (puh->m_pformview->get_html_data()->get_element_by_name("encontrar"));
                  html::impl::input_text * pinput = dynamic_cast < html::impl::input_text * > (pelemental->m_pimpl);
                  sp(text_interface) ptext =  (pinput->m_pedit);
                  range range;
                  _001GetSelection(range);
                  if(range.get_item_count() > 0)
                  {
                     ptext->_001SetText(get_fs_list_data()->m_itema.get_item(range.ItemAt(0).get_lower_bound()).m_strName);
                  }
               }
            }
            file_manager_form_update_hint * pmanageruh = dynamic_cast<file_manager_form_update_hint * > (phint);
            if(pmanageruh != NULL)
            {
               if(!pmanageruh->m_strFind.is_empty())
               {
                  Application.file().replace(m_strPath, pmanageruh->m_strFind, pmanageruh->m_strReplace);
                  _017UpdateList();
               }
            }
         }

      }
   }

   void SimpleFileListView::_001OnClick(UINT nFlags, point point)
   {
      UNREFERENCED_PARAMETER(nFlags);
      index iItem;
      index iSubItem;
      if(_001HitTest_(point, iItem, iSubItem))
      {
         if(iSubItem == m_iNameSubItem || (m_eview == ViewList && iSubItem == 0))
         {
           _017OpenSelected(true);
         }
      }
   }

   void SimpleFileListView::_001OnRightClick(UINT nFlags, point point)
   {
      UNREFERENCED_PARAMETER(nFlags);
      index iItem;
      index iSubItem;
      if(_001HitTest_(point, iItem, iSubItem))
      {
         _017OpenContextMenuSelected();
      }
      else
      {
         _017OpenContextMenu();
      }
   }

   /*bool SimpleFileListView::OnSetData(
      const ::database::id & key,
      int32_t iLine,
      int32_t iColumn,
      var & var, ::database::update_hint * puh)
   {
      if(key.get_value() == _vms::FILE_MANAGER_ID_FILE_NAME)
      {
         ASSERT(var.get_type() == var::type_string || var.is_empty());
         string str;
         str = var.m_str;
         RenameFile(iLine, str);
         return true;
      }
      return data_server_interface::OnSetData(key, iLine, iColumn, var, puh);
   }

   bool SimpleFileListView::get_data(
      const ::database::id & key,
      int32_t iLine,
      int32_t iColumn,
      var & var)
   {
      if(key.get_value() == _vms::FILE_MANAGER_ID_FILE_NAME)
      {
         string str;
         str = m_itema.get_item(iLine).m_strName;
         var.set_type(var::type_string);
         var.m_str = str;
         return true;
      }
      return data_server_interface::OnSetData(key, iLine, iColumn, var);
   }*/

   void SimpleFileListView::RenameFile(int32_t iLine, string &wstrNameNew)
   {

      string str = get_fs_list_data()->m_itema.get_item(iLine).m_strPath;

      strsize iFind = str.reverse_find(L'\\');

      string wstrNew = str.Left(iFind + 1) + wstrNameNew;

      System.file().path().rename(wstrNew, str, get_app());

      _017UpdateList();

   }

   void SimpleFileListView::_001OnContextMenu(signal_details * pobj)
   {
      //SCAST_PTR(::message::context_menu, pcontextmenu, pobj)
      SCAST_PTR(::message::mouse, pcontextmenu, pobj)
      index iItem;
//      HRESULT hr;
      point point = pcontextmenu->m_pt;
      class point ptClient = point;
      ::user::list::ScreenToClient(&ptClient);
        if(_001HitTest_(ptClient, iItem))
      {
         ::user::menu menu(get_app());
         if(get_fs_list_data()->m_itema.get_item(iItem).IsFolder())
         {
            _017OpenContextMenuFolder(new ::fs::item(get_fs_list_data()->m_itema.get_item(iItem)));
            /*if (menu.LoadXmlMenu(GetFileManager()->get_filemanager_data()->m_ptemplate->m_strFolderPopup))
            {
               ::user::menu menuPopup(get_app(), menu.GetSubMenu(0));
               //SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
               //ASSERT(pPopup != NULL);
               sp(::user::frame_window) pframe = ( (GetParentFrame()));
               pframe->SetActiveView(this);
               menuPopup.set_app(get_app());
               menuPopup.TrackPopupMenu(
                  point.x, point.y,
                  pframe);
            }*/
         }
         else if (menu.LoadXmlMenu(GetFileManager()->get_filemanager_data()->m_ptemplate->m_strFilePopup))
         {
            ::user::menu menuPopup(get_app(), menu.GetSubMenu(0));
            //SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
            //ASSERT(pPopup != NULL);
            sp(::user::frame_window) pframe = (GetTopLevelFrame());

            pframe->SetActiveView(this);

            //IContextMenu * pcontextmenu;
            //int32_t iInsertIndex = menu.FindMenuItemPos(GetFileManager()->get_filemanager_data()->m_ptemplate->m_uiFilePopupSubstId);
   /*         if(iInsertIndex >= 0)
            {
               pPopup->DeleteMenu(iInsertIndex, MF_BYPOSITION);
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
                        iInsertIndex,
                        SHELL_COMMAND_FIRST,
                        SHELL_COMMAND_LAST,
                        CMF_NORMAL);

               }
            }*/

            menuPopup.TrackPopupMenu(0, point.x, point.y, pframe);
         }
      }
      else
      {
         ::user::menu menu(get_app());
         if (menu.LoadXmlMenu(GetFileManager()->get_filemanager_data()->m_ptemplate->m_strPopup))
         {
            ::user::menu menuPopup(get_app(), menu.GetSubMenu(0));
            //ASSERT(pPopup != NULL);
            //sp(::user::frame_window) pframe = GetTopLevelFrame();



   /*         hr = m_spshellfolderParent->GetUIObjectOf(
               NULL,
               1,
               (LPCITEMIDLIST *) &m_lpiidlRelative,
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

            }*/


            sp(::user::frame_window) pframe = (GetTopLevelFrame());

            pframe->SetActiveView(this);

            menuPopup.TrackPopupMenu(0, point.x, point.y, pframe);

         }
      }
   }

   bool SimpleFileListView::pre_create_window(CREATESTRUCT& cs)
   {

      cs.style |= WS_CLIPCHILDREN;

      return ::user::view::pre_create_window(cs);
   }

   UINT c_cdecl SimpleFileListView::ThreadProcFileSize(LPVOID lpparam)
   {
      file_size * psize = (file_size *) lpparam;
      db_server * pcentral = dynamic_cast < db_server * > (&App(psize->m_pview->m_pbaseapp).simpledb().db());
      if(pcentral == NULL)
         return 0;
      DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;
      bool bPendingSize;
      int64_t i64Size;
      while(true)
      {
         bPendingSize = false;
         pset->get_fs_size(i64Size, psize->m_str, bPendingSize);
         if(!bPendingSize)
            break;
      }
      //psize->m_pview->_001RedrawWindow();
      delete psize;
      //SimpleFileListView * pview = (SimpleFileListView *) lpparam;
      //pview->FileSize();
      return 0;
   }

   void SimpleFileListView::FileSize()
   {
      if(m_bFileSize)
         return;
      m_bFileSize = true;

      db_server * pcentral = dynamic_cast < db_server * > (&System.m_simpledb.db());
      if(pcentral == NULL)
         return;
      DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;

      int32_t i;
      while(true)
      {
         i = 0;
         while(i < get_fs_list_data()->m_itema.get_count() || IsWindowVisible())
         {
            int64_t i64Size;
            bool bPendingSize;
            single_lock lock(m_pthread->m_pthread);
            if(!lock.lock(millis(1984)))
               return;
            if(i >= get_fs_list_data()->m_itema.get_count())
               i = 0;
            bPendingSize = false;
            try
            {
               pset->get_fs_size(i64Size, get_fs_list_data()->m_itema.get_item(i).m_strPath, bPendingSize);
            }
            catch(...)
            {
            }
            lock.unlock();
            i++;
            Sleep(23);
         }
         Sleep(84);
      }
      m_bFileSize = false;
   }


   void SimpleFileListView::_001OnTimer(signal_details * pobj)
   {
      SCAST_PTR(::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == 198477)
      {
         if(GetFileManager()->get_filemanager_data()->m_bSetBergedgeTopicFile)
         {
            stringa stra;
            GetSelectedFilePath(stra);
            if(stra.get_count() <= 0)
            {
               Session.m_varTopicFile.unset();
            }
            else if(stra.get_count() == 1)
            {
               Session.m_varTopicFile = stra[0];
            }
            else
            {
               Session.m_varTopicFile = stra;
            }

         }
         else
         {
            KillTimer(198477);
         }
      }
      else if(ptimer->m_nIDEvent == 1234567)
      {
         ASSERT(FALSE);
         m_iAnimate += 2;
         if(m_iAnimate >= 11)
         {
            m_iAnimate = 0;
            KillTimer(ptimer->m_nIDEvent);

         }
         RedrawWindow();
      }
      else if(ptimer->m_nIDEvent == 123)
      {
         RedrawWindow();
         KillTimer(123);
      }
      else if(ptimer->m_nIDEvent == 5432176)
      {
         _001CreateImageListStep();
      }
      else if(ptimer->m_nIDEvent == 5432185)
      {
/*         if(m_bPendingSize)
         {
            _001RedrawWindow();
         }
         if(::get_tick_count() - m_dwLastFileSize > 840)
         {
            m_dwLastFileSize = ::get_tick_count();
            sp(::user::interaction) pwnd = GetParentFrame();
//            bool b = pwnd->IsWindowVisible();
            if(pwnd->IsWindowVisible() && m_bFileSize)
            {
               m_bShow = true;
               file_size_add_request(false);
            }
         }*/
      }
      else if(ptimer->m_nIDEvent == 5432184)
      {
      }
   }

   void SimpleFileListView::StartAnimation()
   {
      //SetTimer(1234567, 50, NULL);
   }

   bool SimpleFileListView::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   {
      ::fs::item_array itema;
      GetSelected(itema);
      if(GetFileManagerDoc()->HandleDefaultFileManagerItemCmdMsg(pcmdmsg, itema))
         return TRUE;
      return ::user::view::_001OnCmdMsg(pcmdmsg);
   }

   void SimpleFileListView::_001OnShellCommand(signal_details * pobj)
   {
      SCAST_PTR(::message::command, pcommand, pobj)
      m_contextmenu.OnCommand(pcommand->GetId());
   }

   void SimpleFileListView::_001OnFileManagerItemCommand(signal_details * pobj)
   {
      SCAST_PTR(BaseCommand, pcommand, pobj)
      ::fs::item_array itema;
      index iItemRange, iItem;
      range range;
      _001GetSelection(range);
      for(iItemRange = 0;
          iItemRange < range.get_item_count();
          iItemRange++)
      {
         item_range itemrange = range.ItemAt(iItemRange);
         for(iItem = itemrange.get_lower_bound() ; iItem <= itemrange.get_upper_bound(); iItem ++)
         {
            itema.add(new  ::fs::item  (get_fs_list_data()->m_itema.get_item(iItem)));
         }
      }
      GetFileManager()->get_filemanager_data()->OnFileManagerItemCommand(
         pcommand->m_id,
         itema);
   }

   void SimpleFileListView::_001OnFileManagerItemUpdate(signal_details * pobj)
   {
      SCAST_PTR(::message::update_cmd_ui, pupdatecmdui, pobj)
      ::fs::item_array itema;
      index iItemRange, iItem;
      range range;
      _001GetSelection(range);
      for(iItemRange = 0;
          iItemRange < range.get_item_count();
          iItemRange++)
      {
         item_range itemrange = range.ItemAt(iItemRange);
         for(iItem = itemrange.get_lower_bound() ; iItem <= itemrange.get_upper_bound(); iItem ++)
         {
            itema.add(new  ::fs::item  (get_fs_list_data()->m_itema.get_item(iItem)));
         }
      }
      GetFileManager()->get_filemanager_data()->OnFileManagerItemUpdate(
         pupdatecmdui->m_pcmdui,
         itema);
      pobj->m_bRet = true;
   }

   void SimpleFileListView::_017OpenContextMenuFolder(sp(::fs::item)  item)
   {
      
      stringa straCommand;
      
      stringa straCommandTitle;
      
      GetFileManager()->get_filemanager_data()->OnFileManagerOpenContextMenuFolder(item, straCommand, straCommandTitle);
      
      if(straCommand.get_size() > 0)
      {
         
         ::user::menu menu(get_app());
         
         point ptCursor;
         
         Session.get_cursor_pos(&ptCursor);
      
         if(menu.create_menu(straCommand, straCommandTitle))
         {

            menu.TrackPopupMenu(0, ptCursor.x, ptCursor.y, GetParentFrame());

         }

      }

   }

   void SimpleFileListView::_017OpenContextMenuFile(const ::fs::item_array & itema)
   {
      GetFileManager()->get_filemanager_data()->OnFileManagerOpenContextMenuFile(itema);
   }

   void SimpleFileListView::_017OpenContextMenu()
   {
      GetFileManager()->get_filemanager_data()->OnFileManagerOpenContextMenu();
   }

   void SimpleFileListView::_017OpenFolder(sp(::fs::item) item)
   {
      GetFileManager()->FileManagerBrowse(item);
   }

   void SimpleFileListView::_017OpenFile(const ::fs::item_array &itema)
   {
      GetFileManager()->get_filemanager_data()->OnFileManagerOpenFile(itema);
   }

   void SimpleFileListView::_001OnFileRename(signal_details * pobj)
   {
      SimpleFileListInterface::_001OnFileRename(pobj);
   }

   void SimpleFileListView::_001OnUpdateFileRename(signal_details * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(_001GetSelectedItemCount() == 1);
      pobj->m_bRet = true;
   }


   void SimpleFileListView::_001OnUpdateEditCopy(signal_details * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      range range;
      _001GetSelection(range);
      pcmdui->m_pcmdui->Enable(range.get_item_count() > 0);
      pobj->m_bRet = true;
   }

   void SimpleFileListView::_001OnEditCopy(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::fs::item_array itema;
      GetSelected(itema);
      stringa stra;

      for(int32_t i = 0; i < itema.get_size(); i++)
      {
         stra.add(itema[i].m_strPath);
      }
      /*
      string str;
      if(itema.get_size() > 0)
      {
         str = itema[0].m_strPath;
      }
      for(int32_t i = 1; i < itema.get_size(); i++)
      {
         str += "|" + itema[i]->m_strPath;
      }
      System.m_strCopy = str;
   */


      System.copydesk().set_filea(stra);

   }

   void SimpleFileListView::_001OnUpdateEditPaste(signal_details * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(System.copydesk().get_file_count() > 0);
      pobj->m_bRet = true;
   }


   void SimpleFileListView::_001OnEditPaste(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      stringa stra;

      System.copydesk().get_filea(stra);
      string strDir;
      strDir = GetFileManagerItem().m_strPath;

      GetFileManagerDoc()->get_operation_doc(true)->m_thread.queue_copy(stra, strDir, NULL, true);
      GetFileManagerDoc()->get_operation_doc(true)->m_thread.kick();


     /* for(int32_t i = 0; i < stra.get_size(); i++)
      {
         ::CopyFileW(
            L"\\\\?\\" + ::str::international::utf8_to_unicode(stra[i]),
            L"\\\\?\\" + ::str::international::utf8_to_unicode(System.dir().path(strDir, System.file().title(stra[i]))), TRUE);
      }*/
      //get_document()->update_all_views(NULL, 123);
   }

   void SimpleFileListView::_001OnUpdateTrashThatIsNotTrash(signal_details * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      range range;
      _001GetSelection(range);
      pcmdui->m_pcmdui->Enable(range.get_item_count() > 0);
      pobj->m_bRet = true;
   }

   void SimpleFileListView::_001OnTrashThatIsNotTrash(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::fs::item_array itema;
      GetSelected(itema);
      stringa stra;
      for(int32_t i = 0; i < itema.get_size(); i++)
      {
         stra.add(itema[i].m_strPath);
      }
      Application.file().trash_that_is_not_trash(stra);
      _017UpdateList();
   }

   void SimpleFileListView::_001OnUpdateOpenWith(signal_details * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)

         ::user::menu_button_cmd_ui * pcmdui1 = dynamic_cast < ::user::menu_button_cmd_ui * > (pcmdui->m_pcmdui);
         if(pcmdui1 != NULL)
         {
            ::user::menu_item_ptra * pitema = pcmdui1->m_pitema;

            ::user::menu_base * pbase = pitema->element_at(pcmdui->m_pcmdui->m_iIndex)->m_pbase;
            pitema->remove_at(pcmdui->m_pcmdui->m_iIndex);


            index iStartIndex = pcmdui->m_pcmdui->m_iIndex;
            index iIndex = iStartIndex;


            ::fs::item_array itema;
            GetSelected(itema);

            string strPath = itema[0].m_strPath;

            string strExt = System.file().extension(strPath);

            stringa stra;
            System.os().file_extension_get_open_with_list_keys(stra, strExt);

            m_straOpenWith = stra;
            ::count iCount = stra.get_size();

            sp(::user::menu_item) pmenuitem(new ::user::menu_item(get_app()));
            string str;
            for(int32_t i = 0; i < iCount; i++)
            {
               pmenuitem->m_id = "open with" + stra[i];
               pmenuitem->m_button._001SetButtonText(stra[i]);
               pmenuitem->m_iLevel = pitema->m_pitemContainer != NULL ? pitema->m_pitemContainer->m_iLevel + 1 : 0;
               pmenuitem->m_pbase = pbase;
               pitema->inset(iIndex, pmenuitem);
               iIndex++;
            }
            pcmdui->m_pcmdui->m_iIndex = iStartIndex;

            pcmdui->m_pcmdui->m_iCount = iIndex;


            pbase->layout();

         }
      pobj->m_bRet = true;
   }


   bool SimpleFileListView::_001OnUpdateCmdUi(cmd_ui * pcmdui)
   {
      int32_t iPos = -1;
      for(int32_t i = 0; i < m_straOpenWith.get_size(); i++)
      {
         string strId = "open with" + m_straOpenWith[i];
         if(pcmdui->m_id == strId)
         {
            iPos = i;
            break;
         }
      }
      if(iPos >= 0)
      {
         pcmdui->Enable(TRUE);
         return true;
      }
      else
      {
         return ::user::view::_001OnUpdateCmdUi(pcmdui);
      }
   }

   bool SimpleFileListView::_001OnCommand(id id)
   {
      if(id == "1000")
      {
   //      _017OpenSelected(true);
         return true;
      }
      int32_t iPos = -1;
      for(int32_t i = 0; i < m_straOpenWith.get_size(); i++)
      {
         string strId = "open with" + m_straOpenWith[i];
         if(id == strId)
         {
            iPos = i;
            break;
         }
      }
      if(iPos >= 0)
      {
         ::fs::item_array itema;
         GetSelected(itema);
         string strPath = itema[0].m_strPath;

#ifdef WINDOWSEX

         simple_shell_launcher launcher(NULL, "open", m_straOpenWith[iPos], strPath, System.dir().name(strPath), SW_SHOW);

         launcher.execute();

#else

         throw todo(get_app());

#endif

         return true;

      }
      else
      {
         return ::user::view::_001OnCommand(id);
      }

   }

   void SimpleFileListView::_001OnUpdateSpafy(signal_details * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      range range;
      _001GetSelection(range);
      pcmdui->m_pcmdui->Enable(range.get_item_count() > 0);
      pobj->m_bRet = true;
   }

   void SimpleFileListView::_001OnSpafy(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::fs::item_array itema;
      GetSelected(itema);
      stringa stra;
      stringa straSub;

      string strFileList;
      string strFileCheck;
      for(int32_t i = 0; i < itema.get_size(); i++)
      {
         if(Application.dir().is(itema[i].m_strPath)
            && System.file().name_(itema[i].m_strPath) != ".svn")
         {
            Application.dir().rls(itema[i].m_strPath, &straSub);
            for(int32_t j = 0; j < straSub.get_size(); j++)
            {
               if(!Application.dir().is(straSub[j])
                && straSub[j].find(".svn") < 0)
               {
                  strFileList += straSub[j] + "\n";
                  strFileCheck += straSub[j] + ",";
                  strFileCheck += System.file().length(straSub[j]).get_string() + ",";
                  strFileCheck += System.file().md5(straSub[j]) +"\n";
               }
            }
         }
         else
         {
            strFileList += itema[i].m_strPath + "\n";
            strFileCheck += itema[i].m_strPath + ",";
            strFileCheck += System.file().length(itema[i].m_strPath).get_string() + ",";
            strFileCheck += System.file().md5(itema[i].m_strPath) +"\n";
         }
      }

      ::datetime::time time = ::datetime::time::get_current_time();

      string strTime;
      strTime.Format("%04d-%02d-%02d %02d-%02d",
         time.GetYear(),
         time.GetMonth(),
         time.GetDay(),
         time.GetHour(),
         time.GetMinute());
      string strBase = System.dir().path(GetFileManagerItem().m_strPath, "spafy_");
      string strList = strBase + "list_" + strTime + ".txt";
      string strCheck = strBase + "check_" + strTime + ".txt";


      Application.file().put_contents(strList, strFileList);
      Application.file().put_contents(strCheck, strFileCheck);

   }

   void SimpleFileListView::_001OnUpdateSpafy2(signal_details * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
      pobj->m_bRet = true;
   }

   void SimpleFileListView::_001OnSpafy2(signal_details * pobj)
   {
      ::userfs::list_data * pdata = get_fs_list_data();
      UNREFERENCED_PARAMETER(pobj);
      stringa stra;
      stringa straSub;

      string strFileList;
      string strFileCheck;
      for(int32_t i = 0; i < pdata->m_itema.get_count(); i++)
      {
         if(::userfs::list_interface::get_document()->set().is_dir(pdata->m_itema.get_item(i).m_strPath)
            && ::userfs::list_interface::get_document()->set().file_name(pdata->m_itema.get_item(i).m_strPath) != ".svn")
         {
            Application.dir().rls(pdata->m_itema.get_item(i).m_strPath, &straSub);
            for(int32_t j = 0; j < straSub.get_size(); j++)
            {
             string strExtension = System.file().extension(straSub[j]);

               if(!Application.dir().is(straSub[j])
         && (strExtension == "exe" || strExtension == "dll" || strExtension == "dll.manifest"
             || strExtension == "exe.manifest"))
               {
                  strFileList += straSub[j] + "\n";
                  strFileCheck += straSub[j] + ",";
                  strFileCheck += System.file().length(straSub[j]).get_string() + ",";
                  strFileCheck += System.file().md5(straSub[j]) +"\n";
               }
            }
         }
         else
         {
             string strExtension = System.file().extension(pdata->m_itema.get_item(i).m_strPath);
         if(strExtension == "exe" || strExtension == "dll" || strExtension == "dll.manifest"
             || strExtension == "exe.manifest")
         {

            strFileList += pdata->m_itema.get_item(i).m_strPath + "\n";
            strFileCheck += pdata->m_itema.get_item(i).m_strPath + ",";
            strFileCheck += System.file().length(pdata->m_itema.get_item(i).m_strPath).get_string() + ",";
            strFileCheck += System.file().md5(pdata->m_itema.get_item(i).m_strPath) +"\n";
         }
         }
      }

      ::datetime::time time = ::datetime::time::get_current_time();

      string strTime;
      strTime.Format("%04d-%02d-%02d %02d-%02d",
         time.GetYear(),
         time.GetMonth(),
         time.GetDay(),
         time.GetHour(),
         time.GetMinute());
      string strBase = System.dir().path(GetFileManagerItem().m_strPath, "spafy_");
      string strList = strBase + "list_" + strTime + ".txt";
      string strCheck = strBase + "check_" + strTime + ".txt";


      Application.file().put_contents(strList, strFileList);
      Application.file().put_contents(strCheck, strFileCheck);

   }


   void SimpleFileListView::_001OnAfterSort()
   {
      data_set_DisplayToStrict();
   }

   void SimpleFileListView::schedule_file_size(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
      if(!IsWindowVisible())
         return;
   //   file_size * psize = new file_size;
     // psize->m_pview = this;
      //psize->m_str = psz;
      //__begin_thread(ThreadProc4, psize, THREAD_PRIORITY_IDLE);
   }

   void SimpleFileListView::_001OnShowWindow(signal_details * pobj)
   {
      SCAST_PTR(::message::show_window, pshowwindow, pobj);

      if(!pshowwindow->m_bShow)
      {
   //      System.simple_message_box("hide");
      }

   }

   id SimpleFileListView::data_get_current_list_layout_id()
   {
      return GetFileManager()->get_item().m_strPath;
   }

} // namespace filemanager

