#include "framework.h"


namespace fs
{


   tree::tree(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::fs::tree_interface(papp)
   {

      m_etranslucency = TranslucencyPresent;

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


   void tree::install_message_handling(::ca::message::dispatch * pinterface)
   {
      ::fs::tree_interface::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &tree::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &tree::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &tree::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &tree::_001OnContextMenu);
   }

   void tree::on_update(::view * pSender, LPARAM lHint, ::ca::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);

      //FileManagerViewInterface::on_update(pSender, lHint, phint);
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
/*               string str;
               str.Format("tree(%s)", GetFileManager()->get_filemanager_data()->m_strDISection);
               if(GetFileManager()->get_filemanager_data()->m_bTransparentBackground)
               {
                  ::user::tree::m_etranslucency = ::user::tree::TranslucencyPresent;
               }
               m_dataid = str;*/
   //            _001UpdateColumns();
            }
            if(puh->is_type_of(FileManagerViewUpdateHint::TypePreSynchronize))
            {
               _017PreSynchronize();
            }
            if(puh->is_type_of(FileManagerViewUpdateHint::TypeSynchronize))
            {
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


   void tree::_001OnLButtonDblClk(::ca::signal_object * pobj)
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

   void tree::_001OnContextMenu(::ca::signal_object * pobj)
   {
      SCAST_PTR(::ca::message::context_menu, pcontextmenu, pobj)
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
            frame_window * pframe = GetTopLevelFrame();

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


            pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
               point.x, point.y,
               (::ca::window *) pframe);
         }
      }
      else
      {
         ::userbase::menu menu;
         if (menu.LoadMenu(GetFileManager()->get_filemanager_data()->m_ptemplate->m_uiPopup))
         {
            ::userbase::menu* pPopup = menu.GetSubMenu(0);
            ASSERT(pPopup != NULL);
            frame_window * pframe = GetTopLevelFrame();
            pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
               point.x, point.y,
               (::ca::window *) pframe);
         }
      }*/
   }

   bool tree::pre_create_window(CREATESTRUCT& cs)
   {

      cs.style |= WS_CLIPCHILDREN;

      return ::fs::tree_interface::pre_create_window(cs);
   }


   void tree::_001OnTimer(::ca::signal_object * pobj)
   {
      SCAST_PTR(::ca::message::timer, ptimer, pobj)
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

   void tree::StartAnimation()
   {
      SetTimer(1234567, 50, NULL);
   }

   bool tree::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   {
      return ::fs::tree_interface::_001OnCmdMsg(pcmdmsg);
   }

   void tree::_001OnShellCommand(::ca::signal_object * pobj)
   {
      //SCAST_PTR(::ca::message::command, pcommand, pobj)
      UNREFERENCED_PARAMETER(pobj);
   }

   void tree::_017OpenFolder(const ::fs::item &item)
   {
      get_document()->file_manager_browse(item.m_strPath);
   }

   void tree::_001OnCreate(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);

      if(!initialize())
         throw simple_exception(get_app());

      /*m_pimagelist = System.user().shellimageset().GetImageList16();
      m_iDefaultImage = System.user().shellimageset().GetImage(
         "foo",
         _shell::FileAttributeDirectory,
         _shell::IconNormal);

      m_iDefaultImageSelected = System.user().shellimageset().GetImage(
         "foo",
         _shell::FileAttributeDirectory,
         _shell::IconOpen);*/
   }


} // namespace fs


