#include "StdAfx.h"

namespace flag
{

   pane_view::pane_view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

      m_pcreateview = this;
      m_pviewdataOld = NULL;

      m_etranslucency      = TranslucencyPresent;

      m_pviewdata              = NULL;
      m_pviewdataOld              = NULL;

   /*   ::userbase::single_document_template* pdoctemplate;
	   pdoctemplate = new ::userbase::single_document_template(
		   IDR_ALBUM,
		   &typeid(MediaLibraryDoc),
		   &typeid(MediaLibraryChildFrame),
		   &typeid(::mplite::library::view));
      m_pdoctemplateAlbum = pdoctemplate;

	   pdoctemplate = new ::userbase::single_document_template(
		   IDR_ALBUM,
		   &typeid(OptionsDoc),
		   &typeid(OptionsChildFrame),
		   &typeid(OptionsView));

      
      m_pdoctemplateOptions = pdoctemplate;

	   pdoctemplate = new ::userbase::single_document_template(
		   IDR_ALBUM,
		   &typeid(GoodMixerDoc),
		   &typeid(simple_child_frame),
		   &typeid(MixerMainView));

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
      SCAST_PTR(::user::win::message::create, pcreate, pobj)
      if(pobj->previous())
         return;

      SetTimer(3004, 184, NULL);

      add_tab("3-action-launch", ::flag::PaneViewThreeActionLaunch);
      add_tab("menu", ::flag::PaneViewContextMenu);
      add_tab("win action area", ::flag::PaneViewVideo);
      add_tab("options", ::flag::PaneViewConfiguration);
      add_tab("file manager", ::flag::PaneViewFileManager);

      //frame * pframe = dynamic_cast < frame *> (GetTopLevelParent());
      //pframe->m_ppaneview = this;

      set_cur_tab_by_id(::flag::PaneViewVideo);



   }

   void pane_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      /*if(lHint == 0)
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
               
               int iTab;
   //            if(puh->m_eview == PaneViewContextMenu)
     //          {
       //           m_tab._001AddSel(0);
         //      }
   //            else
               {
               }
               
            }
         }
      }*/

   }

   void pane_view::on_show_view() 
   {
      ::userex::pane_tab_view::on_show_view();
      frame * pframe = dynamic_cast < frame *> (GetParentFrame());
      if(get_view_id() == ::flag::PaneViewFileManager)
      {
         /*pframe->m_bAutoHideOnOutClick = false;
         if(!pframe->IsZoomed())
         {
            pframe->ShowWindow(SW_MAXIMIZE);
         }*/
      }
      else if(get_view_id() == ::flag::PaneViewContextMenu)
      {
         ::flag::menu_view * pview = dynamic_cast < ::flag::menu_view *  > (get_view_uie());
         pview->on_show();
         pframe->m_bAutoHideOnOutClick = false;
         if(!pframe->IsZoomed())
         {
            pframe->ShowWindow(SW_MAXIMIZE);
         }
      }
      else
      {
//         pframe->m_bAutoHideOnOutClick = true;
         //pframe->Dock();
         //pframe->OnHoverAction(false);
      }
//      pframe->SetActiveView(dynamic_cast < ::view *  > (get_view_uie()));
   }

   BOOL pane_view::PreCreateWindow(CREATESTRUCT& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;	

	   return ::userbase::view::PreCreateWindow(cs);
   }

   void pane_view::_001OnShowWindow(gen::signal_object * pobj)
   {
   }

   void pane_view::on_create_view(view_data * pviewdata)
   {
      application * papp = dynamic_cast < application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->get_app());
      switch(pviewdata->m_id)
      {
      case PaneViewContextMenu:
         /*{
         devedgeFrontDoc * pdoc = (devedgeFrontDoc *) (dynamic_cast < ::ca::application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->m_papp))->m_ptemplateFront->open_document_file("http://localhost:10011/");
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
         pviewdata = new ViewData();
         pviewdata->m_eview = eview;
         pviewdata->m_pdoc = pdoc;
         pviewdata->m_pwnd = pframe;


         }
         }
         }
         }*/
         break;

         /*         create_context cc;
         cc.m_pCurrentDoc = get_document();
         cc.m_typeinfoNewView =  &typeid(::userbase::menu_list_view);

         ::userbase::view * pview = dynamic_cast < ::userbase::view * > (CreateView(&cc, 101, this));
         if(pview != NULL)
         {
         ::userbase::menu_list_view * pmenuview = (::userbase::menu_list_view *) pview;
         pmenuview->m_wnd.LoadMenu(IDR_POPUP_LYRICVIEW);
         pmenuview->m_wnd.m_bAutoClose = false;
         pviewdata = new ViewData();
         pviewdata->m_eview = eview;
         pviewdata->m_pdoc = get_document();
         pviewdata->m_pwnd = pview;
         }*/
      case PaneViewVideo:
         {
            ::flag::document * pdoc = dynamic_cast < ::flag::document * > (papp->m_ptemplateVideo->open_document_file(NULL, true, this));
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view(0);
               pview->on_update(NULL, 0, NULL);
               if(pview != NULL)
               {
                  ::flag::frame * pframe = dynamic_cast < ::flag::frame * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->SetParent(this);
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                     pviewdata->m_eflag.signalize(::user::create_view::view_data::flag_hide_all_others_on_show);

                     //                  pdoc->Initialize(true);
                  }
               }
            }
            /*         create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  &typeid(eluce::view);

            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (CreateView(&cc, 101, this));
            if(pview != NULL)
            {
            pviewdata = new ViewData();
            pviewdata->m_eview = eview;
            pviewdata->m_pdoc = get_document();
            pviewdata->m_pwnd = pview;
            }*/
         }
         break;
      case PaneViewFileManager:
         {
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true, this);
            if(pdoc != NULL)
            {
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

                     pdoc->Initialize(true);
                  }
               }
            }
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
         pviewdata = new ViewData();
         pviewdata->m_eview = eview;
         pviewdata->m_pdoc = pdoc;
         pviewdata->m_pwnd = pframe;
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
         pviewdata = new ViewData();
         pviewdata->m_eview = eview;
         pviewdata->m_pdoc = pdoc;
         pviewdata->m_pwnd = pframe;
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
         pviewdata = new ViewData();
         pviewdata->m_eview = eview;
         pviewdata->m_pdoc = pdoc;
         pviewdata->m_pwnd = pframe;
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
         pviewdata = new ViewData();
         pviewdata->m_eview = eview;
         pviewdata->m_pdoc = pdoc;
         pviewdata->m_pwnd = pframe;
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
      set_cur_tab_by_id(m_pviewdataOld->m_id);
   }

   void pane_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::_001InstallMessageHandling(pinterface);

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
            if(get_cur_tab_id() != ::flag::PaneViewVideo)
            {
               set_cur_tab_by_id(::flag::PaneViewVideo);
            }
         }
      }
   }


   void pane_view::rotate()
   {
      ::flag::EPaneView eviewNew;
      switch(get_view_id())
      {
      case ::flag::PaneViewContextMenu:
         eviewNew = ::flag::PaneViewVideo;
         break;
      case ::flag::PaneViewVideo:
         eviewNew = ::flag::PaneViewFileManager;
         break;
      case ::flag::PaneViewFileManager:
         eviewNew = ::flag::PaneViewContextMenu;
         break;
      default:
         eviewNew = ::flag::PaneViewVideo;
      }

      set_cur_tab_by_id(eviewNew);
   }

   void pane_view::request(var & varFile, var & varQuery)
   {
      FileManagerCallbackInterface::request(varFile, varQuery);
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

} // namespace flag