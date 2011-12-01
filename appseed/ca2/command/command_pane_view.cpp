#include "StdAfx.h"

namespace command
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

   /////////////////////////////////////////////////////////////////////////////
   // pane_view message handlers

   void pane_view::_001OnCreate(gen::signal_object * pobj)
   {
//      SCAST_PTR(::gen::message::create, pcreate, pobj)
      if(pobj->previous())
         return;

      add_tab("3-action-launch", command::PaneViewThreeActionLaunch);
      add_tab("menu", command::PaneViewContextMenu);
      add_tab("primary verbing", command::PaneViewPrimaryCommand);
      add_tab("options", command::PaneViewConfiguration);
      add_tab("file manager", command::PaneViewFileManager);

      set_cur_tab_by_id(command::PaneViewPrimaryCommand);

   }

   void pane_view::on_update(::view* pSender, LPARAM lHint, ::radix::object* pHint)
   {
      ::userbase::tab_view::on_update(pSender, lHint, pHint);
      if(lHint == 543218)
      {
         set_cur_tab_by_id(command::PaneViewPrimaryCommand);
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
      frame * pframe = GetTypedParent < frame > ();

      if(get_view_id() == command::PaneViewFileManager)
      {
         pframe->m_bAutoHideOnOutClick = false;
         pframe->ShowWindow(SW_MAXIMIZE);
      }
      else if(get_view_id() == command::PaneViewContextMenu)
      {
         ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (get_view_uie());
         pdoc->FileManagerBrowse(Application.dir().userappdata("command\\menu"));
      }
      else
      {
         pframe->m_bAutoHideOnOutClick = true;
         //pframe->OnHoverAction(false);
      }
   }


   void pane_view::_001OnSize(gen::signal_object * pobj)
   {
	   pobj->previous();

   }


   BOOL pane_view::PreCreateWindow(CREATESTRUCT& cs)
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	   return ::userbase::view::PreCreateWindow(cs);
   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      application * papp = dynamic_cast < application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->get_app());
      switch(pcreatordata->m_id)
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
               pdoc->FileManagerBrowse(Application.dir().userappdata("command\\menu"));
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->SetParent(this);
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;
                  }
               }
            }
         }
         break;
      case PaneViewPrimaryCommand:
         {
            ::userbase::view * pview = create_view < primary_view > ();
            if(pview != NULL)
            {
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
               pcreatordata->m_iExtendOnParent = 0;
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
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;


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
               pdoc->FileManagerBrowse(Application.dir().userappdata("command\\3-action-launch"));
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->SetParent(this);
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;


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
         ::user::view_creator_data * pcreatordata = new ::user::view_creator_data;
         ::view * pview = pdoc->get_typed_view < ::view > ();
         form_update_hint uh;
         uh.m_etype = form_update_hint::type_browse;
         uh.m_strForm = "filemanager\\replace_name_in_file_system.xhtml";
         pdoc->update_all_views(NULL, 0, &uh);

         uh.m_etype = form_update_hint::type_get_form_view;
         pdoc->update_all_views(NULL, 0, &uh);

         uh.m_etype = form_update_hint::type_after_browse;
         pdoc->update_all_views(NULL, 0, &uh);


         pcreatordata->m_pwnd = dynamic_cast < ::ca::window * >(pview->GetParentFrame());
//         form_child_frame * pframe = dynamic_cast < form_child_frame * >(pcreatordata->m_pwnd);
         //pframe->m_iTabId = iId;
         pcreatordata->m_pdoc = pdoc;
      }
      break;
      default:
         ASSERT(FALSE);
         break;
      }
   }

   void pane_view::_001OnMenuMessage(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      set_cur_tab_by_id(m_pviewdataOld->m_id);
   }

   void pane_view::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::userbase::view::install_message_handling(pinterface);

	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
	   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &pane_view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , this, this, &pane_view::_001OnMenuMessage);

   }

   void pane_view::rotate()
   {
      command::EPaneView eviewNew;
      switch(get_view_id())
      {
      case command::PaneViewContextMenu:
         eviewNew = command::PaneViewPrimaryCommand;
         break;
      case command::PaneViewPrimaryCommand:
         eviewNew = command::PaneViewFileManager;
         break;
      case command::PaneViewFileManager:
         eviewNew = command::PaneViewContextMenu;
         break;
      default:
         eviewNew = command::PaneViewPrimaryCommand;
      }

      set_cur_tab_by_id(eviewNew);
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

} // namespace command
