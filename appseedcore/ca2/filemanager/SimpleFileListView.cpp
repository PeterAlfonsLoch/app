#include "StdAfx.h"
#include "FileManagerViewUpdateHint.h"
#include "SimpleFileListView.h"

#define SHELL_COMMAND_FIRST 0x1000
#define SHELL_COMMAND_LAST 0x2000


namespace filemanager
{

   SimpleFileListView::SimpleFileListView(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::user::form(papp),
      ::user::form_list(papp),
      SimpleFileListInterface(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::user::list(papp),
      ::userbase::form_list(papp),
      ::fs::list_interface(papp),
      ::fs::list(papp)
   {

      m_bFileSize = false;
      m_bShow = false;
      m_dwLastFileSize = ::GetTickCount();

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

   void SimpleFileListView::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::install_message_handling(pinterface);
      SimpleFileListInterface::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &SimpleFileListView::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &SimpleFileListView::_001OnTimer);
      connect_command_range(SHELL_COMMAND_FIRST, SHELL_COMMAND_LAST, &SimpleFileListView::_001OnShellCommand);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &SimpleFileListView::_001OnShowWindow);

   }





   #ifdef _DEBUG
   void SimpleFileListView::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void SimpleFileListView::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
   #endif //_DEBUG

   void SimpleFileListView::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint)
   {
      FileManagerViewInterface::on_update(pSender, lHint, phint);
      if(lHint == 123)
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
               m_papp = get_app();
               db_server * pcentral = dynamic_cast < db_server * > (&System.db());
               if(pcentral == NULL)
                  return;
               //DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;
               SetTimer(5432185, 230, NULL);
               //::ca::window::SetTimer(5432184, 23, NULL);
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
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypePreSynchronize))
            {
               if(GetFileManager()->get_filemanager_data()->m_pholderFileList != NULL)
               {
                  if(GetFileManager()->get_filemanager_data()->m_pholderFileList->m_uiptraHold.get_size() > 0)
                  {
                     GetFileManager()->get_filemanager_data()->m_pholderFileList->m_uiptraHold[0]->ShowWindow(SW_HIDE);
                  }
                  GetFileManager()->get_filemanager_data()->m_pholderFileList->hold(this);
                  GetFileManager()->get_filemanager_data()->m_pholderFileList->layout();
               }
               _017PreSynchronize();
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeSynchronize))
            {
               _017Synchronize();
               data_get_DisplayToStrict();
               _001OnUpdateItemCount();
               /*string str;
               if(data_get("sort-" + GetFileManager()->get_item().m_strPath, ::radix::system::idEmpty, str))
               {
                  stringa stra;
                  stra.add_tokens(str, ";", true);
                  if(stra.get_size() == m_iaDisplayToStrict.get_size())
                  {
                     for(int i = 0; i < m_iaDisplayToStrict.get_size(); i++)
                     {
                        m_iaDisplayToStrict.set(i, atoi(stra[i]));
                     }
                  }
               }*/
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
               if(GetParentFrame()->GetActiveView() == dynamic_cast < ::view * > (this))
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
                  text_interface * ptext = dynamic_cast < text_interface * > (pinput->m_pedit);
                  Range range;
                  _001GetSelection(range);
                  if(range.get_item_count() > 0)
                  {
                     ptext->_001SetText(get_fs_list_data()->m_itema.get_item(range.ItemAt(0).GetLBound()).m_strName);
                  }
               }
            }
            file_manager_form_update_hint * pmanageruh = dynamic_cast<file_manager_form_update_hint * > (phint);
            if(pmanageruh != NULL)
            {
               if(!pmanageruh->m_strFind.is_empty())
               {
                  System.file().replace(m_strPath, pmanageruh->m_strFind, pmanageruh->m_strReplace);
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
         if(iSubItem == m_iNameSubItem)
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
      int iLine,
      int iColumn,
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
      return VmsDataServerInterface::OnSetData(key, iLine, iColumn, var, puh);
   }

   bool SimpleFileListView::get_data(
      const ::database::id & key,
      int iLine,
      int iColumn,
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
      return VmsDataServerInterface::OnSetData(key, iLine, iColumn, var);
   }*/

   void SimpleFileListView::RenameFile(int iLine, string &wstrNameNew)
   {

      string str = get_fs_list_data()->m_itema.get_item(iLine).m_strPath;

      int iFind = str.reverse_find(L'\\');

      string wstrNew = str.Left(iFind + 1) + wstrNameNew;

      System.file36().path36().rename(wstrNew, str);

      _017UpdateList();

   }

   void SimpleFileListView::_001OnContextMenu(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
      index iItem;
//      HRESULT hr;
      point point = pcontextmenu->GetPoint();
      class point ptClient = point;
      ::user::list::ScreenToClient(&ptClient);
        if(_001HitTest_(ptClient, iItem))
      {
         ::userbase::menu menu(get_app());
         if(get_fs_list_data()->m_itema.get_item(iItem).IsFolder())
         {
            if (menu.LoadXmlMenu(GetFileManager()->get_filemanager_data()->m_ptemplate->m_strFolderPopup))
            {
               ::userbase::menu menuPopup(get_app(), menu.GetSubMenu(0));
               //SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
               //ASSERT(pPopup != NULL);
               userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > ( dynamic_cast < ::ca::window * > (GetParentFrame()));
               pframe->SetActiveView(this);
               menuPopup.set_app(get_app());
               menuPopup.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                  point.x, point.y,
                  pframe);
            }
         }
         else if (menu.LoadXmlMenu(GetFileManager()->get_filemanager_data()->m_ptemplate->m_strFilePopup))
         {
            ::userbase::menu menuPopup(get_app(), menu.GetSubMenu(0));
            //SimpleMenu* pPopup = (SimpleMenu *) menu.GetSubMenu(0);
            //ASSERT(pPopup != NULL);
            userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (GetTopLevelFrame());

            pframe->SetActiveView(this);

            //IContextMenu * pcontextmenu;
            //int iInsertIndex = menu.FindMenuItemPos(GetFileManager()->get_filemanager_data()->m_ptemplate->m_uiFilePopupSubstId);
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



            menuPopup.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
               point.x, point.y,
               pframe);
         }
      }
      else
      {
         ::userbase::menu menu(get_app());
         if (menu.LoadXmlMenu(GetFileManager()->get_filemanager_data()->m_ptemplate->m_strPopup))
         {
            ::userbase::menu menuPopup(get_app(), menu.GetSubMenu(0));
            //ASSERT(pPopup != NULL);
            //frame_window * pframe = GetTopLevelFrame();



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


            userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (GetTopLevelFrame());

            pframe->SetActiveView(this);

            menuPopup.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
               point.x, point.y,
               pframe);
         }
      }
   }

   BOOL SimpleFileListView::PreCreateWindow(CREATESTRUCT& cs)
   {

      cs.style |= WS_CLIPCHILDREN;

      return ::userbase::view::PreCreateWindow(cs);
   }

   UINT AFX_CDECL SimpleFileListView::ThreadProcFileSize(LPVOID lpparam)
   {
      file_size * psize = (file_size *) lpparam;
      db_server * pcentral = dynamic_cast < db_server * > (&App(psize->m_pview->m_papp).db());
      if(pcentral == NULL)
         return 0;
      DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;
      bool bPendingSize;
      __int64 i64Size;
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

      db_server * pcentral = dynamic_cast < db_server * > (&System.db());
      if(pcentral == NULL)
         return;
      DBFileSystemSizeSet * pset = pcentral->m_pfilesystemsizeset;

      int i;
      while(true)
      {
         i = 0;
         while(i < get_fs_list_data()->m_itema.get_count() || IsWindowVisible())
         {
            __int64 i64Size;
            bool bPendingSize;
            single_lock lock(m_pthread);
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
         Sleep(230);
      }
      m_bFileSize = false;
   }


   void SimpleFileListView::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == 198477)
      {
         if(GetFileManager()->get_filemanager_data()->m_bSetBergedgeTopicFile)
         {
            stringa stra;
            GetSelectedFilePath(stra);
            if(stra.get_count() <= 0)
            {
               Bergedge.m_varTopicFile.unset();
            }
            else if(stra.get_count() == 1)
            {
               Bergedge.m_varTopicFile = stra[0];
            }
            else
            {
               Bergedge.m_varTopicFile = stra;
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
         if(m_bPendingSize)
         {
            _001RedrawWindow();
         }
         if(::GetTickCount() - m_dwLastFileSize > 840)
         {
            m_dwLastFileSize = ::GetTickCount();
            ::user::interaction* pwnd = GetParentFrame();
//            BOOL b = pwnd->IsWindowVisible();
            if(pwnd->IsWindowVisible() && m_bFileSize)
            {
               m_bShow = true;
               file_size_add_request(false);
            }
         }
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
      return ::userbase::view::_001OnCmdMsg(pcmdmsg);
   }

   void SimpleFileListView::_001OnShellCommand(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::command, pcommand, pobj)
      m_contextmenu.OnCommand(pcommand->GetId());
   }

   void SimpleFileListView::_001OnFileManagerItemCommand(gen::signal_object * pobj)
   {
      SCAST_PTR(BaseCommand, pcommand, pobj)
      ::fs::item_array itema;
      index iItemRange, iItem;
      Range range;
      _001GetSelection(range);
      for(iItemRange = 0;
          iItemRange < range.get_item_count();
          iItemRange++)
      {
         ItemRange itemrange = range.ItemAt(iItemRange);
         for(iItem = itemrange.GetLBound() ; iItem <= itemrange.GetUBound(); iItem ++)
         {
            itema.add(::fs::item(get_fs_list_data()->m_itema.get_item(iItem)));
         }
      }
      GetFileManager()->get_filemanager_data()->OnFileManagerItemCommand(
         pcommand->m_id,
         itema);
   }

   void SimpleFileListView::_001OnFileManagerItemUpdate(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
      ::fs::item_array itema;
      index iItemRange, iItem;
      Range range;
      _001GetSelection(range);
      for(iItemRange = 0;
          iItemRange < range.get_item_count();
          iItemRange++)
      {
         ItemRange itemrange = range.ItemAt(iItemRange);
         for(iItem = itemrange.GetLBound() ; iItem <= itemrange.GetUBound(); iItem ++)
         {
            itema.add(::fs::item(get_fs_list_data()->m_itema.get_item(iItem)));
         }
      }
      GetFileManager()->get_filemanager_data()->OnFileManagerItemUpdate(
         pupdatecmdui->m_pcmdui,
         itema);
      pobj->m_bRet = true;
   }

   void SimpleFileListView::_017OpenContextMenuFolder(const ::fs::item & item)
   {
      GetFileManager()->get_filemanager_data()->OnFileManagerOpenContextMenuFolder(item);
   }

   void SimpleFileListView::_017OpenContextMenuFile(const ::fs::item_array & itema)
   {
      GetFileManager()->get_filemanager_data()->OnFileManagerOpenContextMenuFile(itema);
   }

   void SimpleFileListView::_017OpenContextMenu()
   {
      GetFileManager()->get_filemanager_data()->OnFileManagerOpenContextMenu();
   }

   void SimpleFileListView::_017OpenFolder(const ::fs::item &item)
   {
      GetFileManager()->FileManagerBrowse(item);
   }

   void SimpleFileListView::_017OpenFile(const ::fs::item_array &itema)
   {
      GetFileManager()->get_filemanager_data()->OnFileManagerOpenFile(itema);
   }

   void SimpleFileListView::_001OnFileRename(gen::signal_object * pobj)
   {
      SimpleFileListInterface::_001OnFileRename(pobj);
   }

   void SimpleFileListView::_001OnUpdateFileRename(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(_001GetSelectedItemCount() == 1);
      pobj->m_bRet = true;
   }


   void SimpleFileListView::_001OnUpdateEditCopy(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      Range range;
      _001GetSelection(range);
      pcmdui->m_pcmdui->Enable(range.get_item_count() > 0);
      pobj->m_bRet = true;
   }

   void SimpleFileListView::_001OnEditCopy(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::fs::item_array itema;
      GetSelected(itema);
      stringa stra;

      for(int i = 0; i < itema.get_size(); i++)
      {
         stra.add(itema[i].m_strPath);
      }
      /*
      string str;
      if(itema.get_size() > 0)
      {
         str = itema[0].m_strPath;
      }
      for(int i = 1; i < itema.get_size(); i++)
      {
         str += "|" + itema[i].m_strPath;
      }
      System.m_strCopy = str;
   */


      System.copydesk().set_filea(stra);

   }

   void SimpleFileListView::_001OnUpdateEditPaste(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(System.copydesk().get_file_count() > 0);
      pobj->m_bRet = true;
   }


   void SimpleFileListView::_001OnEditPaste(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      stringa stra;

      System.copydesk().get_filea(stra);
      string strDir;
      strDir = GetFileManagerItem().m_strPath;

      GetFileManagerDoc()->get_operation_doc(true)->m_thread.queue_copy(stra, strDir, NULL, true);
      GetFileManagerDoc()->get_operation_doc(true)->m_thread.kick();


     /* for(int i = 0; i < stra.get_size(); i++)
      {
         ::CopyFileW(
            L"\\\\?\\" + gen::international::utf8_to_unicode(stra[i]),
            L"\\\\?\\" + gen::international::utf8_to_unicode(System.dir().path(strDir, System.file().title(stra[i]))), TRUE);
      }*/
      //get_document()->update_all_views(NULL, 123);
   }

   void SimpleFileListView::_001OnUpdateTrashThatIsNotTrash(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      Range range;
      _001GetSelection(range);
      pcmdui->m_pcmdui->Enable(range.get_item_count() > 0);
      pobj->m_bRet = true;
   }

   void SimpleFileListView::_001OnTrashThatIsNotTrash(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::fs::item_array itema;
      GetSelected(itema);
      stringa stra;
      for(int i = 0; i < itema.get_size(); i++)
      {
         stra.add(itema[i].m_strPath);
      }
      System.file().trash_that_is_not_trash(stra);
      _017UpdateList();
   }

   void SimpleFileListView::_001OnUpdateOpenWith(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)

         ::userbase::menu_button_cmd_ui * pcmdui1 = dynamic_cast < ::userbase::menu_button_cmd_ui * > (pcmdui->m_pcmdui);
         if(pcmdui1 != NULL)
         {
            ::userbase::menu_item_ptra * pitema = pcmdui1->m_pitema;

            ::userbase::menu_base * pbase = pitema->ptr_at(pcmdui->m_pcmdui->m_nIndex)->m_pbase;
            pitema->remove_at(pcmdui->m_pcmdui->m_nIndex);


            int iStartIndex = pcmdui->m_pcmdui->m_nIndex;
            int iIndex = iStartIndex;


            ::fs::item_array itema;
            GetSelected(itema);

            string strPath = itema[0].m_strPath;

            string strExt = System.file().extension(strPath);
            strExt = "." + strExt;

            string strOpenWithKey;
            strOpenWithKey = strExt + "\\OpenWithList";




            win::registry::Key key;

            key.OpenKey(HKEY_CLASSES_ROOT, strOpenWithKey, false);


            stringa stra;
            key.EnumKey(stra);
            m_straOpenWith = stra;
            count iCount = stra.get_size();

            ::userbase::menu_item menuitem(get_app());
            string str;
            for(int i = 0; i < iCount; i++)
            {
               menuitem.m_id = "open with" + stra[i];
               menuitem.m_button._001SetButtonText(stra[i]);
               menuitem.m_iLevel = pitema->m_pitemContainer != NULL ? pitema->m_pitemContainer->m_iLevel + 1 : 0;
               menuitem.m_pbase = pbase;
               pitema->insert_at(iIndex, menuitem);
               iIndex++;
            }
            pcmdui->m_pcmdui->m_nIndex = iStartIndex;

            pcmdui->m_pcmdui->m_nIndexMax = iIndex;


            pbase->layout();

         }
      pobj->m_bRet = true;
   }


   bool SimpleFileListView::_001OnUpdateCmdUi(cmd_ui * pcmdui)
   {
      int iPos = -1;
      for(int i = 0; i < m_straOpenWith.get_size(); i++)
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
         return ::userbase::view::_001OnUpdateCmdUi(pcmdui);
      }
   }

   bool SimpleFileListView::_001OnCommand(id id)
   {
      if(id == "1000")
      {
   //      _017OpenSelected(true);
         return true;
      }
      int iPos = -1;
      for(int i = 0; i < m_straOpenWith.get_size(); i++)
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
         ::ShellExecute(NULL, "open", m_straOpenWith[iPos], strPath,
            System.dir().name(strPath), SW_SHOW);
         return true;
      }
      else
      {
         return ::userbase::view::_001OnCommand(id);
      }

   }

   void SimpleFileListView::_001OnUpdateSpafy(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      Range range;
      _001GetSelection(range);
      pcmdui->m_pcmdui->Enable(range.get_item_count() > 0);
      pobj->m_bRet = true;
   }

   void SimpleFileListView::_001OnSpafy(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      ::fs::item_array itema;
      GetSelected(itema);
      stringa stra;
      stringa straSub;

      string strFileList;
      string strFileCheck;
      for(int i = 0; i < itema.get_size(); i++)
      {
         if(System.dir().is(itema[i].m_strPath)
            && System.file().name_(itema[i].m_strPath) != ".svn")
         {
            System.dir().rls(itema[i].m_strPath, &straSub);
            for(int j = 0; j < straSub.get_size(); j++)
            {
               if(!System.dir().is(straSub[j])
                && straSub[j].find(".svn") < 0)
               {
                  strFileList += straSub[j] + "\n";
                  strFileCheck += straSub[j] + ",";
                  strFileCheck += System.file().length(straSub[j]).get_string() + ",";
                  strFileCheck += System.file36().md5(straSub[j]) +"\n";
               }
            }
         }
         else
         {
            strFileList += itema[i].m_strPath + "\n";
            strFileCheck += itema[i].m_strPath + ",";
            strFileCheck += System.file().length(itema[i].m_strPath).get_string() + ",";
            strFileCheck += System.file36().md5(itema[i].m_strPath) +"\n";
         }
      }

      class time time = time::get_current_time();

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

   void SimpleFileListView::_001OnUpdateSpafy2(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
      pobj->m_bRet = true;
   }

   void SimpleFileListView::_001OnSpafy2(gen::signal_object * pobj)
   {
      ::fs::list_data * pdata = get_fs_list_data();
      UNREFERENCED_PARAMETER(pobj);
      stringa stra;
      stringa straSub;

      string strFileList;
      string strFileCheck;
      for(int i = 0; i < pdata->m_itema.get_count(); i++)
      {
         if(::fs::list_interface::get_document()->is_dir(pdata->m_itema.get_item(i).m_strPath)
            && ::fs::list_interface::get_document()->file_name(pdata->m_itema.get_item(i).m_strPath) != ".svn")
         {
            System.dir().rls(pdata->m_itema.get_item(i).m_strPath, &straSub);
            for(int j = 0; j < straSub.get_size(); j++)
            {
             string strExtension = System.file().extension(straSub[j]);

               if(!System.dir().is(straSub[j])
         && (strExtension == "exe" || strExtension == "dll" || strExtension == "dll.manifest"
             || strExtension == "exe.manifest"))
               {
                  strFileList += straSub[j] + "\n";
                  strFileCheck += straSub[j] + ",";
                  strFileCheck += System.file().length(straSub[j]).get_string() + ",";
                  strFileCheck += System.file36().md5(straSub[j]) +"\n";
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
            strFileCheck += System.file36().md5(pdata->m_itema.get_item(i).m_strPath) +"\n";
         }
         }
      }

      class time time = time::get_current_time();

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
      //AfxBeginThread(ThreadProc4, psize, THREAD_PRIORITY_IDLE);
   }

   void SimpleFileListView::_001OnShowWindow(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::show_window, pshowwindow, pobj);

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

