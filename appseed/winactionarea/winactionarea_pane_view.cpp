#include "StdAfx.h"

namespace winactionarea
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

      SetTimer(3004, 184, NULL);

      add_tab("3-action-launch", winactionarea::PaneViewThreeActionLaunch);
      add_tab("menu", winactionarea::PaneViewContextMenu);
      add_tab("win action area", winactionarea::PaneViewWinActionArea);
      add_tab("options", winactionarea::PaneViewConfiguration);
      add_tab("file manager", winactionarea::PaneViewFileManager);

      frame * pframe = dynamic_cast < frame *> (GetTopLevelParent());
      pframe->m_ppaneview = this;

      set_cur_tab_by_id(winactionarea::PaneViewWinActionArea);



   }

   void pane_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      if(lHint == 0)
      {
                  frame * pframe = dynamic_cast < frame *> (GetTopLevelParent());
                  pframe->SetActiveView(this);
      }
      ::userbase::tab_view::on_update(pSender, lHint, pHint);
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
      if(get_view_id() == winactionarea::PaneViewFileManager)
      {
         pframe->m_bAutoHideOnOutClick = false;
         if(!pframe->IsZoomed())
         {
            pframe->ShowWindow(SW_MAXIMIZE);
         }
      }
      else if(get_view_id() == winactionarea::PaneViewContextMenu)
      {
         winactionarea::menu_view * pview = dynamic_cast < winactionarea::menu_view *  > (get_view_uie());
         pview->on_show();
         pframe->m_bAutoHideOnOutClick = false;
         if(!pframe->IsZoomed())
         {
            pframe->ShowWindow(SW_MAXIMIZE);
         }
      }
      else
      {
         pframe->m_bAutoHideOnOutClick = true;
         //pframe->Dock();
         //pframe->OnHoverAction(false);
      }
      pframe->SetActiveView(dynamic_cast < ::view *  > (get_view_uie()));
   }

   BOOL pane_view::PreCreateWindow(CREATESTRUCT& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;	

	   return ::userbase::view::PreCreateWindow(cs);
   }

   void pane_view::_001OnShowWindow(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      application * papp = dynamic_cast < application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->get_app());
      switch(pcreatordata->m_id)
      {
      case PaneViewContextMenu:
         {
            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (::view::create_view(::ca::get_type_info < winactionarea::menu_view > (), get_document(), this, 102));
            if(pview != NULL)
            {
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }
         }
         break;
      case PaneViewWinActionArea:
         {
            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (::view::create_view(::ca::get_type_info < winactionarea::view > (), get_document(), this, 101));
            if(pview != NULL)
            {
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }
         }
         break;
      case PaneViewFileManager:
         {
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true, this);
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
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChildList(papp, false, true, this);
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
               string strDir = Application.dir().userappdata("winactionarea\\3-action-launch");
               check_3click_dir(strDir);
               pdoc->FileManagerBrowse(strDir);
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
         form_document * pdoc = System.create_form(this, this);
         if(pdoc == NULL)
            return;
         ::view * pview = pdoc->get_view();
         form_update_hint uh;
         uh.m_etype = form_update_hint::type_browse;
         uh.m_strForm = "winactionarea\\configuration.html";
         pdoc->update_all_views(NULL, 0, &uh);
         
         uh.m_etype = form_update_hint::type_get_form_view;
         pdoc->update_all_views(NULL, 0, &uh);

         uh.m_etype = form_update_hint::type_after_browse;
         pdoc->update_all_views(NULL, 0, &uh);


         pcreatordata->m_pwnd = dynamic_cast < ::user::interaction * >(pview->GetParentFrame());
//         form_child_frame * pframe = dynamic_cast < form_child_frame * >(pcreatordata->m_pwnd);
         //pframe->m_iTabId = iId;
         pcreatordata->m_pdoc = pdoc;

      }
      break;
   /*   case PaneViewPlaylist:
         {
            PlaylistDoc * pdoc = ((MusicalPlayerLightApp *) &System)->GetPlaylistCentral().GetCurrentPlaylist(true, false);
            
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
      if(pcreatordata->m_pwnd != NULL)
      {
         pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
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
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , this, this, &pane_view::_001OnMenuMessage);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &pane_view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &pane_view::_001OnShowWindow);

   }

   void pane_view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == 3004)
      {
         if(!GetTopLevelParent()->IsWindowVisible())
         {
            if(get_cur_tab_id() != winactionarea::PaneViewWinActionArea)
            {
               set_cur_tab_by_id(winactionarea::PaneViewWinActionArea);
            }
         }
      }
   }


   void pane_view::rotate()
   {
      winactionarea::EPaneView eviewNew;
      switch(get_view_id())
      {
      case winactionarea::PaneViewContextMenu:
         eviewNew = winactionarea::PaneViewWinActionArea;
         break;
      case winactionarea::PaneViewWinActionArea:
         eviewNew = winactionarea::PaneViewFileManager;
         break;
      case winactionarea::PaneViewFileManager:
         eviewNew = winactionarea::PaneViewContextMenu;
         break;
      default:
         eviewNew = winactionarea::PaneViewWinActionArea;
      }

      set_cur_tab_by_id(eviewNew);
   }

   void pane_view::request(gen::command_line * pline)
   {
      FileManagerCallbackInterface::request(pline);
      GetParentFrame()->ShowWindow(SW_HIDE);
   }


   void pane_view::check_3click_dir(const char * psz)
   {
      stringa straPath;
      System.dir().ls(psz, &straPath);
      stringa straRelative;
      straPath.remove_all();
      System.dir().rls(Application.dir().userquicklaunch(), &straPath, NULL, &straRelative);
      for(int i = 0; i < straPath.get_size(); i++)
      {
         string str = System.dir().path(psz, straRelative[i]);
         System.dir().mk(System.dir().name(str));
         ::CopyFile(straPath[i], str, TRUE);
      }
   }

   void pane_view::on_before_dock()
   {
      if(get_cur_tab_id() != winactionarea::PaneViewWinActionArea)
      {
         set_cur_tab_by_id(winactionarea::PaneViewWinActionArea);
      }
      m_pwinactionareaview->on_before_dock();
   }

   void pane_view::on_after_dock()
   {
      layout();
      m_pwinactionareaview->on_after_dock();
   }

} // namespace winactionarea