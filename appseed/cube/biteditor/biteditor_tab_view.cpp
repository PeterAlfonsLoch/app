#include "StdAfx.h"
#include "tab_view.h"
#include "biteditor_application.h"
#include "biteditor_view.h"
#include "biteditor_document.h"
#include "front_document.h"

namespace biteditor
{

   tab_view::tab_view(::ca::application * papp) :
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

   tab_view::~tab_view()
   {
   }

   void tab_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::tab_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &tab_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , pinterface, this, &tab_view::_001OnMenuMessage);
   }



   #ifdef _DEBUG
   void tab_view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void tab_view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // tab_view message handlers

   void tab_view::_001OnCreate(gen::signal_object * pobj) 
   {
//      SCAST_PTR(::user::win::message::create, pcreate, pobj)
      if(pobj->previous())
         return;

      add_tab("Front", pane_view_context_menu);
      add_tab("bit editor", pane_view_bit_editor);
      add_tab("file manager", pane_view_file_manager);

      //ensure_tab(pane_view_bit_editor);
      set_cur_tab_by_id(pane_view_bit_editor);


   }



   void tab_view::on_create_view(view_data * pviewdata)
   {
      biteditor_application * papp = dynamic_cast < biteditor_application * > (get_app());
      switch(pviewdata->m_id)
      {
      case pane_view_context_menu:
         {
            front_document * pdoc = dynamic_cast < front_document * > ((dynamic_cast < biteditor_application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->get_app()))->m_ptemplateFront->open_document_file("http://localhost:10011/"));
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
      case pane_view_bit_editor:
         {
            biteditor_document * pdoc = dynamic_cast < biteditor_document * > (papp->m_ptemplate_devedge->open_document_file(NULL, TRUE, this));
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
                     pviewdata->m_eflag.signalize(::user::create_view::view_data::flag_hide_all_others_on_show);
                  }
               }
            }
         }
         break;
      case pane_view_file_manager:
         {
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true, this);
            if(pdoc != NULL)
            {
               pdoc->m_dataid = "biteditor:filemanager";
               pdoc->Initialize(true);
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
      default:
         ASSERT(FALSE);
         break;
      }

   }

} // namespace biteditor