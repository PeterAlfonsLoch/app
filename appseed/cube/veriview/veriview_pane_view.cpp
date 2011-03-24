#include "StdAfx.h"
#include "pane_view.h"
#include "application.h"
#include "html/html_view.h"
#include "html/html_document.h"

namespace veriview
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


      m_etranslucency      = TranslucencyPresent;

      m_pviewdata              = NULL;
      m_pviewdataOld              = NULL;

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

      //add_tab("menu", PaneViewContextMenu);
      //add_tab("html", PaneViewHtml);
      //add_tab("html edit", PaneViewHtmlEdit);
      //add_tab("source edit", PaneViewSourceEdit);
      //add_tab("", 0);

      set_cur_tab_by_id(PaneViewHtml);
   }

   void pane_view::on_create_view(view_data * pviewdata)
   {
      application * papp = dynamic_cast < application * > (get_app());
      html_document * pdoc = dynamic_cast < html_document * > (papp->m_ptemplate_html->open_document_file(NULL, TRUE, this));
      if(pdoc != NULL)
      {
         ::view * pview = pdoc->get_view();
         if(pview != NULL)
         {
            userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
            if(pframe != NULL)
            {
               //pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
               //pframe->SetParent(this);
               pviewdata->m_pdoc = pdoc;
               pviewdata->m_pwnd = pframe;
            }
         }
      }

      //switch(pviewdata->m_id)
      //{
      //case PaneViewContextMenu:
         /*{
            devedgeFrontDoc * pdoc = (devedgeFrontDoc *) (dynamic_cast < application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->m_papp))->m_ptemplateFront->open_document_file("http://localhost:10011/");
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
                     pviewdata = new ::user::create_view::view_data();
                     pviewdata->m_eview = eview;
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;


                  }
               }
            }
         }*/
     //       break;
         
   /*         create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  &typeid(::userbase::menu_list_view);

            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (CreateView(&cc, 101, this));
            if(pview != NULL)
            {
               ::userbase::menu_list_view * pmenuview = (::userbase::menu_list_view *) pview;
               pmenuview->m_wnd.LoadMenu(IDR_POPUP_LYRICVIEW);
               pmenuview->m_wnd.m_bAutoClose = false;
               pviewdata = new ::user::create_view::view_data();
               pviewdata->m_eview = eview;
               pviewdata->m_pdoc = get_document();
               pviewdata->m_pwnd = pview;
            }*/
   /*   case PaneViewSourceEdit:
         {
            devedge_document * pdoc = dynamic_cast < devedge_document * > (papp->m_ptemplate_devedge->open_document_file(NULL));
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
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
            }
         }
         break;
      case PaneViewHtmlEdit:
         {
            devedge_document * pdoc = dynamic_cast < devedge_document * > (papp->m_ptemplate_html_edit->open_document_file(NULL));
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->get_view_count();
               ::view * pview = pdoc->get_view(pos);
               if(pview != NULL)
               {
                  html_child_frame * pframe = dynamic_cast < html_child_frame * > (pview->GetParentFrame());
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
            devedge_document * pdoc = dynamic_cast < devedge_document * > (papp->m_ptemplate_html->open_document_file(NULL, TRUE, this));
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->get_view_count();
               ::view * pview = pdoc->get_view(pos);
               if(pview != NULL)
               {
                  ::ca::window * pparentframe = dynamic_cast < ::ca::window *> (pview->GetParentFrame());
                  html_child_frame * pframe = dynamic_cast < html_child_frame * > (pparentframe);
                  if(pframe != NULL)
                  {
                     string str = System.dir().matter("html_reader\\html_toolbar.xml");
                     str = Application.file().as_string(str);
                     if (!pframe->m_toolbar.CreateEx(pframe) ||
                         !pframe->m_toolbar.LoadXmlToolBar(str))
                     {
                        TRACE0("Failed to create toolbar\n");
                     }
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
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true, this);
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
                     pviewdata->m_pdoc    = pdoc;
                     pviewdata->m_pwnd    = pframe;

                     pdoc->Initialize(true);
                  }
               }
            }
         }
         break;*/
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
                        pviewdata = new ::user::create_view::view_data();
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
                        pviewdata = new ::user::create_view::view_data();
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
                        pviewdata = new ::user::create_view::view_data();
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
                        pviewdata = new ::user::create_view::view_data();
                        pviewdata->m_eview = eview;
                        pviewdata->m_pdoc = pdoc;
                        pviewdata->m_pwnd = pframe;
                     }
                  }
               }
            }
         }
         break;*/
   /*  default:
         ASSERT(FALSE);
         break;
      }*/
   }



   void pane_view::rotate()
   {
      int eview = get_view_id();
      int eviewNew = PaneViewHtml;
      switch(eview)
      {
      case PaneViewHtml:
         eviewNew = PaneViewHtmlEdit;
         break;
      case PaneViewHtmlEdit:
         eviewNew = PaneViewSourceEdit;
         break;
      case PaneViewSourceEdit:
         eviewNew = PaneViewFileManager;
         break;
      case PaneViewFileManager:
         eviewNew = PaneViewHtml;
         break;
      default:
         ASSERT(FALSE);
         break;
      }

      set_cur_tab_by_id(eviewNew);
   }

   void pane_view::_001OnMenuMessage(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      set_cur_tab_by_id(m_pviewdataOld->m_id);
   }

   void pane_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::_001InstallMessageHandling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122, pinterface, this, &pane_view::_001OnMenuMessage);
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
         eview = PaneViewFileManager;
         break;
      default:
         ASSERT(FALSE);
         break;
      }
      ShowView(eview);
      (dynamic_cast < userbase::frame_window * > (GetParentFrame()))->_001RedrawWindow();
      
   }*/

   void pane_view::OnViewUpdateHint(::view * pSender, LPARAM lHint, view_update_hint * puh)
   {
      if(puh->m_etype == view_update_hint::TypeOpenDocument)
      {
         if(!get_document()->get_path_name().is_empty())
         {
            application * papp = dynamic_cast < application * > (get_app());
            papp->m_ptemplate_html->open_document_file(get_document()->get_path_name(), true, this);
            papp->m_ptemplate_html_edit->open_document_file(get_document()->get_path_name(), true, this);
            papp->m_ptemplate_devedge->open_document_file(get_document()->get_path_name(), true, this);
         }
      }
      ::userbase::tab_view::OnViewUpdateHint(pSender, lHint, puh);
   }


   void pane_view::on_update(::view * pSender, LPARAM lHint, ::radix::object * pHint)
   {
      if(pHint != NULL)
      {
         if(base < pane_view_update_hint > ::bases(pHint))
         {
//            pane_view_update_hint * puh = dynamic_cast < pane_view_update_hint * > (pHint);
         }
      }
      ::userbase::tab_view::on_update(pSender, lHint, pHint);
   }

   html::data * pane_view::get_html_data()
   {
      html_document * pdoc = get_view_html_document();
      if(pdoc == NULL)
         return NULL;
      return pdoc->get_html_data();
   }

   html_document * pane_view::get_view_html_document()
   {
      if(m_pviewdata == NULL)
         return NULL;
      return dynamic_cast < html_document * > (m_pviewdata->m_pdoc);
   }

} // namespace veriview