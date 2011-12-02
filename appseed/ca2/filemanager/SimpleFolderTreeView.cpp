#include "StdAfx.h"
#include "FileManagerViewUpdateHint.h"
#include "SimpleFolderTreeView.h"
//#include "win/WindowsShell.h"


#define SHELL_COMMAND_FIRST 0x1000
#define SHELL_COMMAND_LAST 0x2000

namespace filemanager
{

   SimpleFolderTreeView::SimpleFolderTreeView(::ax::application * papp) : 
      ax(papp),
      ::ax::data_container(papp),
      ::user::scroll_view(papp),
      ::user::tree(papp),
      SimpleFolderTreeInterface(papp),
      m_headerctrl(papp),
      ex1::tree(papp),
      ::fs::tree_interface(papp),
      ::fs::tree(papp)
   {
      m_etranslucency = TranslucencyPresent;
   }

   SimpleFolderTreeView::~SimpleFolderTreeView()
   {
   }



   #ifdef _DEBUG
   void SimpleFolderTreeView::assert_valid() const
   {
      SimpleFolderTreeInterface::assert_valid();
   }

   void SimpleFolderTreeView::dump(dump_context & dumpcontext) const
   {
      SimpleFolderTreeInterface::dump(dumpcontext);
   }
   #endif //_DEBUG


   void SimpleFolderTreeView::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
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


   void SimpleFolderTreeView::_001OnLButtonDblClk(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
   //   int iItem;
      
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
   bool SimpleFolderTreeView::OnSetData(const ::database::id &key, int iLine, int iColumn, var & var, ::database::update_hint * puh)
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
   bool SimpleFolderTreeView::get_data(const ::database::id & key, int iLine, int iColumn, var & var)
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

   void SimpleFolderTreeView::RenameFile(int iLine, string &wstrNameNew)
   {
      string str = m_itema.get_item(iLine).m_strPath;

      int iFind = str.reverse_find(L'\\');


      string wstrNew = str.Left(iFind + 1) + wstrNameNew;

      if(!WindowsShell::MoveFile(str, wstrNew))
      {
         System.simple_message_box("Could not rename the file");
      }

   }*/

   void SimpleFolderTreeView::_001OnContextMenu(gen::signal_object * pobj) 
   {
      SCAST_PTR(::gen::message::context_menu, pcontextmenu, pobj)
   //   int iItem;
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
               (::ax::window *) pframe);
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
               (::ax::window *) pframe);
         }
      }*/
   }

   BOOL SimpleFolderTreeView::PreCreateWindow(CREATESTRUCT& cs) 
   {
      
      cs.style |= WS_CLIPCHILDREN;
      
      return SimpleFolderTreeInterface::PreCreateWindow(cs);
   }


   void SimpleFolderTreeView::_001OnTimer(gen::signal_object * pobj) 
   {
      SCAST_PTR(::gen::message::timer, ptimer, pobj)
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

   void SimpleFolderTreeView::_001OnShellCommand(gen::signal_object * pobj) 
   {
      SCAST_PTR(::gen::message::command, pcommand, pobj)
      m_contextmenu.OnCommand(pcommand->GetId());
   }

   void SimpleFolderTreeView::_017OpenFolder(const ::fs::item &item)
   {
      GetFileManager()->FileManagerBrowse(item);

   }

   void SimpleFolderTreeView::_001OnCreate(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);

      if(!ex1::tree::initialize())
         throw simple_exception();

      m_pimagelist = System.shellimageset().GetImageList16();
      m_iDefaultImage = System.shellimageset().GetImage(
         "foo",
         _shell::FileAttributeDirectory,
         _shell::IconNormal);

      m_iDefaultImageSelected = System.shellimageset().GetImage(
         "foo",
         _shell::FileAttributeDirectory,
         _shell::IconOpen);
   }


   void SimpleFolderTreeView::install_message_handling(::gen::message::dispatch * pinterface)
   {
      SimpleFolderTreeInterface::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &SimpleFolderTreeView::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &SimpleFolderTreeView::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &SimpleFolderTreeView::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &SimpleFolderTreeView::_001OnCreate);

      connect_command_range(SHELL_COMMAND_FIRST, SHELL_COMMAND_LAST, &SimpleFolderTreeView::_001OnShellCommand);
   }


} // namespace filemanager

