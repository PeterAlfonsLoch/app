#include "StdAfx.h"
#include "pane_view.h"

namespace devedge
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
      m_pcreateview        = this;
      m_bShowDevEdge       = false;
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

      devedge::application * papp = dynamic_cast < devedge::application * > (get_app());

      papp->m_ppaneview = this;

      add_tab("Front", PaneViewContextMenu);
      add_tab("DevEdge", PaneViewDevEdge);
      add_tab("HtmlDesigner", PaneViewHtmlEdit);
      add_tab("HtmlView", PaneViewHtml);
      add_tab("FileManager", PaneViewFileManager);


      set_cur_tab_by_id(PaneViewDevEdge);


   }


   void pane_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {

      devedge::application * papp = dynamic_cast < devedge::application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->get_app());
      papp->devedge::application_interface::m_ptemplate_devedge->update_all_views(pSender, lHint, pHint);
      papp->m_ptemplateHtmlEdit->update_all_views(pSender, lHint, pHint);

      if(pHint != NULL)
      {
         if(base < PaneViewUpdateHint >::bases(pHint))
         {
            PaneViewUpdateHint * puh = (PaneViewUpdateHint *) pHint;
            if(puh->is_type_of(PaneViewUpdateHint::TypeGetView))
            {
               puh->m_eview = (EPaneView) atoi(get_cur_tab_id());
            }
            else if(puh->is_type_of(PaneViewUpdateHint::TypeSetView))
            {
               set_cur_tab_by_id(puh->m_eview);
            }
         }
      }
         if(pHint != NULL)
      {
         if(base < PaneViewUpdateHint >::bases(pHint))
         {
            PaneViewUpdateHint * puh = (PaneViewUpdateHint * ) pHint;
            if(puh->is_type_of(PaneViewUpdateHint::TypeOnShowKaraoke))
            {
               (dynamic_cast < userbase::frame_window * > (GetTopLevelFrame()))->SetActiveView(this);
            }
            else if(puh->is_type_of(PaneViewUpdateHint::TypeOnShowView))
            {
               int iTab;
   /*            if(puh->m_eview == PaneViewHtml)
               {
                  devedge::application * papp = dynamic_cast < devedge::application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->m_papp);
                  POSITION posDoc = papp->m_ptemplateHtmlEdit->get_document_count();
                  devedgeHtmlDoc * pdoc = (devedgeHtmlDoc *) papp->m_ptemplateHtmlEdit->get_document(posDoc);
                  posDoc = papp->devedge::application_interface::m_ptemplate_devedge->get_document_count();
                  document * pdocDev = (document *) papp->devedge::application_interface::m_ptemplate_devedge->get_document(posDoc);
                  if(pdoc != NULL)
                  {
                     if(pdocDev != NULL)
                     {
                        POSITION pos = pdocDev->get_view_count();
                        ::view * pview = dynamic_cast < ::view *> ( pdoc->get_view(pos));
                        string str;
                        pdocDev->m_plaintextboxa[0]._001GetText(str);
                        pdoc->m_document.load(str);
                     }
                  }
               }*/
   //            if(puh->m_eview == PaneViewContextMenu)
     //          {
       //           m_tab._001AddSel(0);
         //      }
   //            else
               if(puh->m_eview == PaneViewHtml)
               {
                  devedge::application * papp = dynamic_cast < devedge::application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->get_app());
                  devedgeHtmlDoc * pdocHtml = dynamic_cast < devedgeHtmlDoc * > (papp->devedge::application_interface::m_ptemplateHtml->get_document());
                  document * pdoc = dynamic_cast < document * > (papp->devedge::application_interface::m_ptemplate_devedge->get_document());
                  string str;
                  pdoc->m_pview->_001GetText(str);
                  pdocHtml->get_html_data()->load(str);
                  pdocHtml->update_all_views(NULL, 123);
               }
   //            else
               {
                  switch(puh->m_eview)
                  {
                  case PaneViewContextMenu:
                     iTab = 0;
                     break;
                  case PaneViewDevEdge:
                     iTab = 1;
                     break;
                  case PaneViewHtmlEdit:
                     iTab = 2;
                     break;
                  case PaneViewHtml:
                     iTab = 3;
                     break;
                  case PaneViewFileManager:
                     iTab = 4;
                     break;
                  case PaneViewAudioControl:
                     iTab = 6;
                     break;
                  case PaneViewOptions:
                     iTab = 5;
                     break;
                  }
                  _001SetSel(iTab);
               }
               
            }
         }
      }

   }

   /*void pane_view::ShowPlaylist()
   {
      ViewData * pview;
      if(!m_viewmap.Lookup(PaneViewPlaylist, pview))
      {
         CreatePlaylist();
      }

      if(m_pplaylistview != NULL)
      {
         Show(m_pplaylistview);
      }

   }*/

   /*void pane_view::ShowFileBrowser()
   {
      if(m_pfilemanagerview == NULL)
      {
         ::filemanager::document * pdoc = ((MusicalPlayerLightApp *) &System)->GetStdFileManagerTemplate()->OpenChild(((MusicalPlayerLightApp *) &System), false, true);

         if(pdoc != NULL)
         {
            POSITION pos = pdoc->get_view_count();
            ::view * pview = pdoc->get_view(pos);
            if(pview != NULL)
            {
               frame_window * pframe = pview->GetParentFrame();
               if(pframe != NULL)
               {
                  pframe->SetParent(this);
                  pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                  m_pfilemanagerview = pframe;
               }
            }
         }
      }

      if(m_pfilemanagerview != NULL)
      {
         Show(m_pfilemanagerview);
      }
   }*/




   void pane_view::on_create_view(view_data * pviewdata)
   {
      devedge::application & app = Application;
      if(pviewdata->m_id.is_text())
      {
         string strPath(pviewdata->m_id);
         if(gen::str::begins_eat_ci(strPath, "devedge://"))
         {
            document * pdoc = dynamic_cast < document * > (app.devedge::application_interface::m_ptemplate_devedge->open_document_file(strPath, true, this));
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


                  }
               }
            }
            return;
         }
      }
      switch(pviewdata->m_id)
      {
      case PaneViewContextMenu:
         {
            devedgeFrontDoc * pdoc = dynamic_cast < devedgeFrontDoc * > ((dynamic_cast < devedge::application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->get_app()))->devedge::application_interface::m_ptemplateFront->open_document_file("http://localhost:10011/"));
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


                  }
               }
            }
         }
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
      case PaneViewDevEdge:
         {
            document * pdoc = dynamic_cast < document * > (app.devedge::application_interface::m_ptemplate_devedge->open_document_file(NULL, true, this));
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


                  }
               }
            }
         }
         break;
      case PaneViewHtmlEdit:
         {
            document * pdoc = dynamic_cast < document * > (app.m_ptemplateHtmlEdit->open_document_file("E:\\temp\\html.html"));
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


                  }
               }
            }
         }
         break;
      case PaneViewHtml:
         {
            devedgeHtmlDoc * pdoc = dynamic_cast < devedgeHtmlDoc * > (app.devedge::application_interface::m_ptemplateHtml->open_document_file(NULL));
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


                  }
               }
            }
         }
         break;
      case PaneViewFileManager:
         {
            ::filemanager::document * pdoc = app.GetStdFileManagerTemplate()->OpenChild(&app, false, true, this);
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
                  }
               }
            }
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
      case PaneViewSolution:
         {
            devedge::solution_document * pdoc = dynamic_cast < devedge::solution_document * > (app.m_ptemplate_solution->open_document_file(NULL, true, this));
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


                  }
               }
            }
         }
         break;

      default:
         ASSERT(FALSE);
         break;
      }
   }


   void pane_view::rotate()
   {
      EPaneView eview = (EPaneView) atoi(get_view_id());
      EPaneView eviewNew = PaneViewDevEdge;
      switch(eview)
      {
      case PaneViewDevEdge:
         eviewNew = PaneViewFileManager;
         break;
      case PaneViewFileManager:
         eviewNew = PaneViewPlaylist;
         break;
      case PaneViewPlaylist:
         eviewNew = PaneViewMediaLibrary;
         break;
      case PaneViewMediaLibrary:
         eviewNew = PaneViewAudioControl;
         break;
      case PaneViewAudioControl:
         eviewNew = PaneViewDevEdge;
         break;
      case PaneViewOptions:
         eviewNew = PaneViewDevEdge;
         break;
      default:
         ASSERT(FALSE);
         break;
      }

      set_cur_tab_by_id(eviewNew);
   }

   void pane_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::tab_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
   }

   /*
   void pane_view::_001OnTabClick(int iTab)
   {
      EPaneView eview = PaneViewNone;
      switch(iTab)
      {
      case 0:
         eview = PaneViewContextMenu;
         break;
      case 1:
         eview = PaneViewDevEdge;
         break;
      case 2:
         eview = PaneViewHtmlEdit;
         break;
      case 3:
         eview = PaneViewHtml;
         break;
      case 4:
         eview = PaneViewFileManager;
         break;
   /*     case 3:
         eview = PaneViewPlaylist;
         break;
      case 4:
         eview = PaneViewMediaLibrary;
         break;
      case 5:
         eview = PaneViewOptions;
         break;
      case 6:
         eview = PaneViewAudioControl;
         break;*/
     // default:
   //      ASSERT(FALSE);
       /*  break;
      }
      if(
      set_cur_tab_by_id(eview);
      (dynamic_cast < userbase::frame_window * > (GetParentFrame()))->_001RedrawWindow();
      
   }*/

   void pane_view::on_show_view()
   {
      ::userex::pane_tab_view::on_show_view();
      if(m_pviewdata->m_id == PaneViewDevEdge 
      && !m_pviewdata->m_idSplit.has_char())
      {
         if(!m_bShowDevEdge)
         {
            keeper < bool > keepShowDevEdge(&m_bShowDevEdge, true, false, true);
            _001OnDropTab(PaneViewSolution, position_left);
            m_pviewdata->m_pwnd->m_etranslucency = TranslucencyNone;
         }
      }
   }

   ::document * pane_view::open_file(const char * lpcsz)
   {
      return ensure("devedge://" + string(lpcsz))->m_pdoc;
   }

} // namespace devedge