#include "framework.h"


#define SHELL_COMMAND_FIRST 0x1000
#define SHELL_COMMAND_LAST 0x2000


namespace filemanager
{


   SimpleFolderTreeView::SimpleFolderTreeView(sp(base_application) papp) :
      element(papp),
      
      ::user::scroll_view(papp),
      SimpleFolderTreeInterface(papp),
      m_headerctrl(papp)
   {

      m_etranslucency = TranslucencyPresent;

   }

   SimpleFolderTreeView::~SimpleFolderTreeView()
   {
   }



   #ifdef DEBUG
   void SimpleFolderTreeView::assert_valid() const
   {
      SimpleFolderTreeInterface::assert_valid();
   }

   void SimpleFolderTreeView::dump(dump_context & dumpcontext) const
   {
      SimpleFolderTreeInterface::dump(dumpcontext);
   }
   #endif //DEBUG


   void SimpleFolderTreeView::on_update(sp(::user::view) pSender, LPARAM lHint, object* phint)
   {
      FileManagerViewInterface::on_update(pSender, lHint, phint);
      if(phint != NULL)
      {
         if(base < FileManagerViewUpdateHint > :: bases(phint))
         {
            FileManagerViewUpdateHint * puh = (FileManagerViewUpdateHint *) phint;
            if(puh->is_type_of(FileManagerViewUpdateHint::TypeInitialize))
            {
               /* xxx _001SetExpandImage(
                  System.LoadIcon(
                     GetFileManager()->get_filemanager_data()->m_ptemplate->m_uiExpandBox));
               _001SetCollapseImage(
                  System.LoadIcon(
                     GetFileManager()->get_filemanager_data()->m_ptemplate->m_uiCollapseBox));*/


   //            VmsDataInitialize(this);
     //          SetDataInterface(&m_datainterface);
       //        AddClient(&m_datainterface);
               string str;
               str.Format("SimpleFolderTreeView(%s)", GetFileManager()->get_filemanager_data()->m_strDISection);
               if(GetFileManager()->get_filemanager_data()->m_bTransparentBackground)
               {
                  ::user::tree::m_etranslucency = ::user::tree::TranslucencyPresent;
               }
               m_dataid = str;
   //            _001UpdateColumns();
            }
            if(puh->is_type_of(FileManagerViewUpdateHint::TypeSynchronizePath))
            {
               _017PreSynchronize();
              _017Synchronize();
            }
            if(puh->is_type_of(FileManagerViewUpdateHint::TypeFilter))
            {
               if(puh->m_wstrFilter.is_empty())
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


   void SimpleFolderTreeView::_001OnLButtonDblClk(signal_details * pobj)
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
   bool SimpleFolderTreeView::OnSetData(const ::database::id &key, int32_t iLine, int32_t iColumn, var & var, ::database::update_hint * puh)
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
   bool SimpleFolderTreeView::get_data(const ::database::id & key, int32_t iLine, int32_t iColumn, var & var)
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

   void SimpleFolderTreeView::RenameFile(int32_t iLine, string &wstrNameNew)
   {
      string str = m_itema.get_item(iLine).m_strPath;

      int32_t iFind = str.reverse_find(L'\\');


      string wstrNew = str.Left(iFind + 1) + wstrNameNew;

      if(!::win::shell::MoveFile(str, wstrNew))
      {
         System.simple_message_box("Could not rename the file");
      }

   }*/

   void SimpleFolderTreeView::_001OnContextMenu(signal_details * pobj)
   {
      SCAST_PTR(::ca2::message::context_menu, pcontextmenu, pobj)
   //   int32_t iItem;
   //   HRESULT hr;
      point ptClient = pcontextmenu->GetPoint();
      ::user::tree::ScreenToClient(&ptClient);
   /*     if(_001HitTest_(ptClient, iItem))
      {
         CSimpleMenu menu(CBaseMenuCentral::GetMenuCentral());
         if (menu.LoadMenu(GetFileManager()->get_filemanager_data()->m_ptemplate->m_uiFilePopup))
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
               (sp(::ca2::window)) pframe);
         }
      }
      else
      {
         ::user::menu menu;
         if (menu.LoadMenu(GetFileManager()->get_filemanager_data()->m_ptemplate->m_uiPopup))
         {
            ::user::menu* pPopup = menu.GetSubMenu(0);
            ASSERT(pPopup != NULL);
            sp(::user::frame_window) pframe = GetTopLevelFrame();
            pPopup->TrackPopupMenu(
               point.x, point.y,
               (sp(::ca2::window)) pframe);
         }
      }*/
   }

   bool SimpleFolderTreeView::pre_create_window(CREATESTRUCT& cs)
   {

      cs.style |= WS_CLIPCHILDREN;

      return SimpleFolderTreeInterface::pre_create_window(cs);
   }


   void SimpleFolderTreeView::_001OnTimer(signal_details * pobj)
   {
      SCAST_PTR(::ca2::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == 1234567)
      {
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
         _001RedrawWindow();
         m_bTimer123 = false;
         KillTimer(123);
      }
   }

   void SimpleFolderTreeView::StartAnimation()
   {
      SetTimer(1234567, 50, NULL);
   }

   bool SimpleFolderTreeView::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   {
      // TODO: add your specialized code here and/or call the base class

      return SimpleFolderTreeInterface::_001OnCmdMsg(pcmdmsg);
   }

   void SimpleFolderTreeView::_001OnShellCommand(signal_details * pobj)
   {
      SCAST_PTR(::ca2::message::command, pcommand, pobj)
      m_contextmenu.OnCommand(pcommand->GetId());
   }

   void SimpleFolderTreeView::_017OpenFolder(sp(::fs::item) item)
   {
      GetFileManager()->FileManagerBrowse(item);

   }

   void SimpleFolderTreeView::_001OnCreate(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   void SimpleFolderTreeView::install_message_handling(::ca2::message::dispatch * pinterface)
   {
      SimpleFolderTreeInterface::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &SimpleFolderTreeView::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &SimpleFolderTreeView::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &SimpleFolderTreeView::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &SimpleFolderTreeView::_001OnCreate);

      connect_command_range(SHELL_COMMAND_FIRST, SHELL_COMMAND_LAST, &SimpleFolderTreeView::_001OnShellCommand);
   }


} // namespace filemanager


