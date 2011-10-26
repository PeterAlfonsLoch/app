#include "StdAfx.h"


namespace winutil
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

      m_pviewdata              = NULL;
      m_pviewdataOld              = NULL;

   /*   ::userbase::single_document_template* pdoctemplate;
	   pdoctemplate = new ::userbase::single_document_template(
		   IDR_ALBUM,
		   ::ca::get_type_info < MediaLibraryDoc > (),
		   ::ca::get_type_info < MediaLibraryChildFrame > (),
		   ::ca::get_type_info < ::mplite::library::view) > ();
      m_pdoctemplateAlbum = pdoctemplate;

	   pdoctemplate = new ::userbase::single_document_template(
		   IDR_ALBUM,
		   ::ca::get_type_info < OptionsDoc > (),
		   ::ca::get_type_info < OptionsChildFrame > (),
		   ::ca::get_type_info < OptionsView) > ();

      
      m_pdoctemplateOptions = pdoctemplate;

	   pdoctemplate = new ::userbase::single_document_template(
		   IDR_ALBUM,
		   ::ca::get_type_info < GoodMixerDoc > (),
		   ::ca::get_type_info < simple_child_frame > (),
		   ::ca::get_type_info < MixerMainView) > ();

      m_pdoctemplateAudioControl = pdoctemplate;*/
      

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
//      SCAST_PTR(::user::win::message::create, pcreate, pobj)
      if(pobj->previous())
         return;

      add_tab("3-action-launch", winutil::PaneViewThreeActionLaunch);
      add_tab("menu", winutil::PaneViewContextMenu);
      add_tab("ca2 applications", winutil::PaneViewWinActionArea);
      add_tab("options", winutil::PaneViewConfiguration);
      add_tab("file manager", winutil::PaneViewFileManager);

      set_cur_tab_by_id(winutil::PaneViewWinActionArea);
   }

   void pane_view::on_update(::view* pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      ::userbase::tab_view::on_update(pSender, lHint, pHint);
      if(lHint == 543218)
      {
         set_cur_tab_by_id(winutil::PaneViewWinActionArea);
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
               
//               int iTab;
   //            if(puh->m_eview == PaneViewContextMenu)
     //          {
       //           m_tab._001AddSel(0);
         //      }
   //            else
               {
               }
               
            }
         }
      }


   }

   void pane_view::on_show_view()
   {
      ::userex::pane_tab_view::on_show_view();
      frame * pframe = dynamic_cast < frame *> (GetParentFrame());
      if(get_view_id() == winutil::PaneViewFileManager)
      {
         pframe->m_bAutoHideOnOutClick = false;
         pframe->ShowWindow(SW_MAXIMIZE);
      }
      else if(get_view_id() == winutil::PaneViewContextMenu)
      {
         ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (get_view_document());
         pdoc->FileManagerBrowse(Application.dir().userappdata("winutil\\menu"));
      }
      else
      {
         pframe->m_bAutoHideOnOutClick = true;
      }
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
               pdoc->get_filemanager_data()->m_strDISection = "winutil_menu";
               pdoc->get_filemanager_data()->m_pcallback = this;
               pdoc->Initialize(true);
               pdoc->update_all_views(NULL, 1234);
               pdoc->update_all_views(NULL, 123458);
               ::view * pview = pdoc->get_view();
               pdoc->FileManagerBrowse(Application.dir().userappdata("winutil\\menu"));
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
      case PaneViewWinActionArea:
         {
            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (::view::create_view(::ca::get_type_info < winutil::view > (), get_document(), this, 101));
            if(pview != NULL)
            {
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }
         }
         break;
      case PaneViewFileManager:
         {
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true);
            if(pdoc != NULL)
            {
               pdoc->get_filemanager_data()->m_strDISection = "winutil_filemanager";
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
               pdoc->get_filemanager_data()->m_strDISection = "winutil_3-action-launch";
               pdoc->Initialize(true);
               pdoc->update_all_views(NULL, 1234);
               pdoc->update_all_views(NULL, 123458);
               ::view * pview = pdoc->get_view();
               pdoc->FileManagerBrowse(Application.dir().userappdata("winutil\\3-action-launch"));
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
         ::view * pview = pdoc->get_view();
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
         pcreatordata->m_pdoc = pdoc;

      }
      break;
   /*   case PaneViewPlaylist:
         {
            PlaylistDoc * pdoc = ((MusicalPlayerLightApp *) &Application)->GetPlaylistCentral().GetCurrentPlaylist(true, false);
            
            if(pdoc != NULL)
            {
               MusicalPlayerLightDoc * pplayerdoc = (MusicalPlayerLightDoc *) get_document();
               if(pplayerdoc != NULL)
               {
                  pplayerdoc->AttachPlaylist(pdoc);
               }
               if(pdoc != NULL)
               {
                  POSITION pos = pdoc->get_view_count();
                  ::view * pview = pdoc->get_view(pos);
                  if(pview != NULL)
                  {
                     userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                        pframe->SetParent(this);
                        pcreatordata = new ViewData();
                        pcreatordata->m_eview = eview;
                        pcreatordata->m_pdoc = pdoc;
                        pcreatordata->m_pwnd = pframe;
                     }
                  }
               }
            }
         }
         break;
      case PaneViewMediaLibrary:
         {
            MediaLibraryDoc * pdoc = (MediaLibraryDoc *) m_pdoctemplateAlbum->open_document_file(NULL, FALSE);	
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->get_view_count();
               ::view * pview = pdoc->get_view(pos);
               if(pdoc != NULL)
               {
                  POSITION pos = pdoc->get_view_count();
                  ::view * pview = pdoc->get_view(pos);
                  if(pview != NULL)
                  {
                     userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                        pframe->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
                        pframe->SetParent(this);
                        pcreatordata = new ViewData();
                        pcreatordata->m_eview = eview;
                        pcreatordata->m_pdoc = pdoc;
                        pcreatordata->m_pwnd = pframe;
                     }
                  }
               }
            }
         }
         break;
      case PaneViewAudioControl:
         {
            GoodMixerDoc * pdoc = (GoodMixerDoc *) m_pdoctemplateAudioControl->open_document_file(NULL, FALSE);	
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->get_view_count();
               ::view * pview = pdoc->get_view(pos);
               if(pdoc != NULL)
               {
                  POSITION pos = pdoc->get_view_count();
                  ::view * pview = pdoc->get_view(pos);
                  if(pview != NULL)
                  {
                     userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                        pframe->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
                        pframe->SetParent(this);
                        pcreatordata = new ViewData();
                        pcreatordata->m_eview = eview;
                        pcreatordata->m_pdoc = pdoc;
                        pcreatordata->m_pwnd = pframe;
                     }
                  }
               }
            }
         }
         break;
      case PaneViewOptions:
         {
            OptionsDoc * pdoc = (OptionsDoc *) m_pdoctemplateOptions->open_document_file(NULL, FALSE);	
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->get_view_count();
               ::view * pview = pdoc->get_view(pos);
               if(pdoc != NULL)
               {
                  POSITION pos = pdoc->get_view_count();
                  ::view * pview = pdoc->get_view(pos);
                  if(pview != NULL)
                  {
                     userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                        pframe->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
                        pframe->SetParent(this);
                        pcreatordata = new ViewData();
                        pcreatordata->m_eview = eview;
                        pcreatordata->m_pdoc = pdoc;
                        pcreatordata->m_pwnd = pframe;
                     }
                  }
               }
            }
         }
         break;*/
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

   void pane_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);

	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
	   //IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &pane_view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , pinterface, this, &pane_view::_001OnMenuMessage);

   }

   void pane_view::rotate()
   {
      winutil::EPaneView eviewNew;
      switch(get_view_id())
      {
      case winutil::PaneViewContextMenu:
         eviewNew = winutil::PaneViewWinActionArea;
         break;
      case winutil::PaneViewWinActionArea:
         eviewNew = winutil::PaneViewFileManager;
         break;
      case winutil::PaneViewFileManager:
         eviewNew = winutil::PaneViewContextMenu;
         break;
      default:
         eviewNew = winutil::PaneViewWinActionArea;
      }

      set_cur_tab_by_id(eviewNew);
   }

   void pane_view::OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         int i = (int) ::ShellExecuteW(
            GetTopLevelParent()->_get_handle(), 
            NULL, 
            gen::international::utf8_to_unicode("\"" + itema[0].m_strPath + "\""),
            NULL,
            gen::international::utf8_to_unicode("\"" + System.dir().name(itema[0].m_strPath) + "\""),
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


} // namespace winutil

