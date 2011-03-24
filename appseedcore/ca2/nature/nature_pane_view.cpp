#include "StdAfx.h"

namespace nature
{

   pane_view::pane_view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      pane_tab_view(papp),
      place_holder_container(papp)
   {

      m_etranslucency      = TranslucencyPresent;
      
      m_pdoctemplateAppearance = new ::userbase::single_document_template(
         get_app(),
         "nature/appearance",
         &typeid(::userbase::document),
         &typeid(simple_child_frame),
         &typeid(appearance_view));

   }

   pane_view::~pane_view()
   {
   }

#ifdef _DEBUG
   void pane_view::assert_valid() const
   {
      ::userex::pane_tab_view::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::userex::pane_tab_view::dump(dumpcontext);
   }
#endif //_DEBUG


   void pane_view::_001OnCreate(gen::signal_object * pobj) 
   {
      //SCAST_PTR(::user::win::message::create, pcreate, pobj)
      if(pobj->previous())
         return;
      
      ::user::tab::get_data()->m_iHeightAddUp = 5;


      add_tab("DevEdge", nature::PaneViewDevEdge);
      add_tab("FileManager", nature::PaneViewFileManager);
      add_tab("Appearance", nature::PaneViewAppearance);
      add_image_tab("", System.dir().matter("image/keyboard-h21.png"), nature::PaneViewKeyboardLayout);
      add_image_tab("", System.dir().matter("earth.png"), nature::PaneViewIdioma);


      set_cur_tab_by_id(nature::PaneViewDevEdge);

      



      m_pviewdata->m_pwnd->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
      ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

   //   m_plightview = (MusicalPlayerLightView *) m_pviewdata->m_pwnd;

      layout();
   }

   void pane_view::on_create_view(view_data * pviewdata)
   {
      switch(pviewdata->m_id)
      {
      case nature::PaneViewIdioma:
         {
            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  &typeid(::userbase::menu_list_view);

            ::userbase::menu_list_view * pview = dynamic_cast < ::userbase::menu_list_view * > (view::create_view(typeid(::userbase::menu_list_view), get_document(), this, 101));
            if(pview != NULL)
            {
               ::userbase::menu_list_view * pmenuview = (::userbase::menu_list_view *) pview;
               pmenuview->LoadXmlMenu("idioma_nature_menu.xml");
               pmenuview->m_bAutoClose = false;
               pviewdata->m_pdoc = get_document();
               pviewdata->m_pwnd = pview;
            }
         }
         break;
         
   /*         create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  &typeid(::userbase::menu_list_view);

            ::userex::pane_tab_view * pview = dynamic_cast < ::userex::pane_tab_view * > (CreateView(&cc, 101, this));
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
      case nature::PaneViewDevEdge:
         {
            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  &typeid(nature::view);

            ::user::interaction * pview = dynamic_cast < ::user::interaction * > (view::create_view(typeid(nature::view), get_document(), this, 101));
            if(pview != NULL)
            {
               pviewdata->m_pdoc = get_document();
               pviewdata->m_pwnd = pview;
            }
         }
         break;
      case nature::PaneViewFileManager:
         {
            ::filemanager::document * pdoc = System.GetStdFileManagerTemplate()->OpenChild(&System, false, true);
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
      case PaneViewAppearance:
         {
            ::userbase::document * pdoc = dynamic_cast < ::userbase::document * > (m_pdoctemplateAppearance->open_document_file());   
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
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

      case PaneViewKeyboardLayout:
         {
            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  &typeid(::ca8::keyboard_layout);

            m_pkeyboardlayout = dynamic_cast < ::ca8::keyboard_layout * > (view::create_view(&cc, this, 100));
            m_pkeyboardlayout->CreateViews();
            pviewdata->m_pdoc = m_pkeyboardlayout->m_pdoc;
            pviewdata->m_pwnd = m_pkeyboardlayout;
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

      IGUI_WIN_MSG_LINK(WM_CREATE      , pinterface, this, &pane_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122 , pinterface, this, &pane_view::_001OnMenuMessage);

   }

   void pane_view::on_show_view() 
   {
      ::userex::pane_tab_view::on_show_view();
      if(m_pviewdata->m_id == nature::PaneViewIdioma)
      {
         ::userbase::menu_list_view * pmenuview = dynamic_cast < ::userbase::menu_list_view * > (m_pviewdata->m_pwnd);
         pmenuview->m_pguieNotify = m_pviewdataOld == NULL ? NULL : dynamic_cast < ::userex::pane_tab_view * > (m_pviewdataOld->m_pwnd);
         pmenuview->m_uiMessage = WM_USER + 1122;
         pmenuview->TrackPopupMenu(pmenuview, GetParentFrame());
      }
   }

   void pane_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(pHint);
   }

} // namespace nature