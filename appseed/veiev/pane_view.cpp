#include "StdAfx.h"
#include "pane_view.h"
#include "application.h"
#include "html/html_view.h"
#include "html/html_document.h"

namespace veiev
{

   pane_view::pane_view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

      m_etranslucency      = TranslucencyPresent;

   }

   pane_view::~pane_view()
   {
   }

#ifdef _DEBUG
   void pane_view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
	   ::userbase::view::dump(dumpcontext);
   }
#endif //_DEBUG

   void pane_view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;

      add_tab("3-action-launch", veiev::PaneViewThreeActionLaunch);
      add_tab("menu", veiev::PaneViewContextMenu);
      add_tab("primary verbing", veiev::PaneViewPrimaryCommand);
      add_tab("second command", veiev::PaneViewSecondCommand);
      add_tab("options", veiev::PaneViewConfiguration);
      add_tab("file manager", veiev::PaneViewFileManager);

      int iCurrentTab = veiev::PaneViewPrimaryCommand;
      data_get("tab", iCurrentTab);
      set_cur_tab_by_id(iCurrentTab);
      
   }

   void pane_view::on_update(::view* pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      ::userbase::tab_view::on_update(pSender, lHint, pHint);
      if(lHint == 543218)
      {
         set_cur_tab_by_id(veiev::PaneViewPrimaryCommand);
      }
      if(pHint != NULL)
      {
         if(base < pane_view_update_hint >::bases(pHint))
         {
            pane_view_update_hint * puh = (pane_view_update_hint *) pHint;
            if(puh->is_type_of(pane_view_update_hint::TypeGetView))
            {
            }
            else if(puh->is_type_of(pane_view_update_hint::TypeSetView))
            {
               set_cur_tab_by_id(puh->m_eview);
            }
         }
      }
	      if(pHint != NULL)
      {
   	   if(base < pane_view_update_hint >::bases(pHint))
         {
            pane_view_update_hint * puh = (pane_view_update_hint * ) pHint;
            if(puh->is_type_of(pane_view_update_hint::TypeOnShowKaraoke))
            {
               (dynamic_cast < userbase::frame_window * > (GetTopLevelFrame()))->SetActiveView(this);
            }
            else if(puh->is_type_of(pane_view_update_hint::TypeOnShowView))
            {
               
            }
         }
      }


   }

   void pane_view::on_show_view() 
   {
      
      ::userex::pane_tab_view::on_show_view();
      frame * pframe = dynamic_cast < frame *> (
         GetParentFrame());

      if(get_view_id() == veiev::PaneViewFileManager)
      {
         
         pframe->m_bAutoHideOnOutClick = false;
         pframe->ShowWindow(SW_MAXIMIZE);
      }
      else if(get_view_id() == veiev::PaneViewContextMenu)
      {
         ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (get_view_uie());
         pdoc->FileManagerBrowse(Application.dir().userappdata("veiev\\menu"));
      }
      else
      {
         pframe->m_bAutoHideOnOutClick = true;
         //pframe->OnHoverAction(false);
      }
      if(get_view_id() == veiev::PaneViewPrimaryCommand
      || get_view_id() == veiev::PaneViewSecondCommand)
      {
         data_set("tab", (int) get_view_id());
      }
   }


   void pane_view::on_create_view(view_data * pviewdata)
   {
      application * papp = dynamic_cast < application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->get_app());
      switch(pviewdata->m_id)
      {
      case PaneViewContextMenu:
         {
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChildList(papp, false, true);
            if(pdoc != NULL)
            {
               pdoc->get_filemanager_data()->m_iIconSize = 16;
               pdoc->get_filemanager_data()->m_bListText = true;
               pdoc->get_filemanager_data()->m_bListSelection = false;
               pdoc->get_filemanager_data()->m_ptemplate->m_strFilePopup = "filemanager\\file_popup.xml";
               pdoc->get_filemanager_data()->m_strDISection = "winactionarea_menu";
               pdoc->get_filemanager_data()->m_pcallback = this;
               pdoc->Initialize(true);
               pdoc->update_all_views(NULL, 1234);
               pdoc->update_all_views(NULL, 123458);
               ::view * pview = pdoc->get_view();
               pdoc->FileManagerBrowse(Application.dir().userappdata("veiev\\menu"));
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->SetParent(this);
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
            }
         }
         break;
      case PaneViewPrimaryCommand:
         {
            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (create_view(typeid(primary_command_view), get_document(), this, 101));
            if(pview != NULL)
            {
               pviewdata->m_pdoc = get_document();
               pviewdata->m_pwnd = pview;
               pviewdata->m_iExtendOnParent = 0;
            }
         }
         break;
      case PaneViewSecondCommand:
         {
            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (create_view(typeid(second_command_view), get_document(), this, 102));
            if(pview != NULL)
            {
               pviewdata->m_pdoc = get_document();
               pviewdata->m_pwnd = pview;
               pviewdata->m_iExtendOnParent = 0;
            }
         }
         break;
      case PaneViewFileManager:
         {
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true);
            if(pdoc != NULL)
            {
               pdoc->get_filemanager_data()->m_strDISection = "winactionarea_filemanager";
               pdoc->Initialize(true);
               pdoc->update_all_views(NULL, 1234);
               pdoc->update_all_views(NULL, 123458);
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->SetParent(this);
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;


                  }
               }
            }
         }
         break;
      case PaneViewThreeActionLaunch:
         {
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChildList(papp, false, true);
            if(pdoc != NULL)
            {
               pdoc->get_filemanager_data()->m_iIconSize = 48;
               pdoc->get_filemanager_data()->m_bListText = false;
               pdoc->get_filemanager_data()->m_bListSelection = false;
               pdoc->get_filemanager_data()->m_pcallback = this;
               pdoc->get_filemanager_data()->m_strDISection = "winactionarea_3-action-launch";
               pdoc->Initialize(true);
               pdoc->update_all_views(NULL, 1234);
               pdoc->update_all_views(NULL, 123458);
               ::view * pview = pdoc->get_view();
               pdoc->FileManagerBrowse(Application.dir().userappdata("veiev\\3-action-launch"));
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->SetParent(this);
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;


                  }
               }
            }
         }
         break;
      case PaneViewConfiguration:
      {
         form_document * pdoc = Application.create_form(this, this);
         if(pdoc == NULL)
            return;
         ::user::create_view::view_data * pviewdata = new ::user::create_view::view_data;
         ::view * pview = pdoc->get_typed_view < ::view > ();
         form_update_hint uh;
         uh.m_etype = form_update_hint::type_browse;
         uh.m_strForm = "filemanager\\replace_name_in_file_system.xhtml";
         pdoc->update_all_views(NULL, 0, &uh);
         
         uh.m_etype = form_update_hint::type_get_form_view;
         pdoc->update_all_views(NULL, 0, &uh);

         uh.m_etype = form_update_hint::type_after_browse;
         pdoc->update_all_views(NULL, 0, &uh);


         pviewdata->m_pwnd = dynamic_cast < ::ca::window * >(pview->GetParentFrame());
//         form_child_frame * pframe = dynamic_cast < form_child_frame * >(pviewdata->m_pwnd);
         //pframe->m_iTabId = iId;
         pviewdata->m_pdoc = pdoc;
      }
      break;
      default:
         ASSERT(FALSE);
         break;
      }
   }

   void pane_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::_001InstallMessageHandling(pinterface);

	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);

   }


   void pane_view::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         int i = (int) ::ShellExecuteW(
            GetTopLevelParent()->_get_handle(),
            NULL, 
            gen::international::utf8_to_unicode("\"" + itema[0].m_strPath + "\""),
            NULL,
            gen::international::utf8_to_unicode("\"" +  System.dir().name(itema[0].m_strPath) + "\""),
            SW_SHOWNORMAL);
         string str;
         str.Format("%d", i);
         //Application.simple_message_box(str);
         if(i == ERROR_FILE_NOT_FOUND)
         {
         }
      }
      GetParentFrame()->ShowWindow(SW_HIDE);
   }

} // namespace veiev