#include "StdAfx.h"

#include "MediaLibraryChildFrame.h"
#include "MediaLibraryDoc.h"
#include "mplite_library_view.h"
#include "MediaLibraryViewUpdateHint.h"

#include "view.h"
#include "pane_view_update_hint.h"
#include "document.h"
 
// vmpLight - Options
#include "OptionsDoc.h"
#include "OptionsChildFrame.h"
#include "OptionsView.h"

namespace mplite
{

   pane_view::pane_view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {
    
      m_pviewdataOld = NULL;
      m_pdoctemplateAudioControl = NULL;
      m_pdoctemplateAlbum = NULL;
      m_pdoctemplateOptions = NULL;


      
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

   void pane_view::_001OnCreate(gen::signal_object * pobj) 
   {
      //SCAST_PTR(::user::win::message::create, pcreate, pobj)
      if(pobj->previous())
         return;

      mplite::application * papp = dynamic_cast < mplite::application * > (get_app());

      papp->m_pplaylistcentralcallback->m_ppaneview = this;

      GetTypedParent < ::mplite::main_frame > ()->m_ppaneview = this;
      
      ::userbase::single_document_template* pdoctemplate;
      pdoctemplate = new ::userbase::single_document_template(
         get_app(),
         "mplite/album",
         &typeid(MediaLibraryDoc),
         &typeid(MediaLibraryChildFrame),
         &typeid(MediaLibraryView));
      m_pdoctemplateAlbum = pdoctemplate;

      pdoctemplate = new ::userbase::single_document_template(
         get_app(),
         "mplite/options",
         &typeid(OptionsDoc),
         &typeid(OptionsChildFrame),
         &typeid(OptionsView));

      
      m_pdoctemplateOptions = pdoctemplate;

      pdoctemplate = new ::userbase::single_document_template(
         get_app(),
         "mplite/mixer",
         &typeid(GoodMixerDoc),
         &typeid(simple_child_frame),
         &typeid(MixerMainView));

      m_pdoctemplateAudioControl = pdoctemplate;

   /*   create_context cc;
      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView =  &typeid(view);*/




   //   m_plightview = (::view *) m_pviewdata->m_pwnd;


      add_image_tab("<string id='mplite:karaoke_view_tab_menu'>menu</string>", System.dir().matter("mplite/icon_context_menu.png"), PaneViewContextMenu);
      //m_tab.add_tab(IDS_KARAOKEVIEW_TAB_KARAOKE);
      add_tab("<string id='mplite:karaoke_view_tab_karaoke'>Karaoke</string>", PaneViewKaraoke);
      add_tab("<string id='mplite:karaoke_view_tab_open'>open</string>", PaneViewFileManager);
      add_tab("<string id='mplite:karaoke_view_tab_open_fs'>open fs</string>", PaneViewFsManager);
      add_tab("<string id='mplite:karaoke_view_tab_playlist'>Playlist</string>", PaneViewPlaylist);
      add_tab("<string id='mplite:karaoke_view_tab_album'>Album</string>", PaneViewMediaLibrary);
      add_tab("<string id='mplite:karaoke_view_tab_options'>Options</string>", PaneViewOptions);
      add_tab("<string id='mplite:karaoke_view_tab_audio_control'>Audio control</string>", PaneViewAudioControl);

      set_cur_tab_by_id(PaneViewKaraoke);

   }


   void pane_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {

      if(pHint != NULL)
      {
         if(base < pane_view_update_hint >::bases(pHint))
         {
            pane_view_update_hint * puh = (pane_view_update_hint *) pHint;
            if(puh->is_type_of(pane_view_update_hint::TypeGetView))
            {
               puh->m_eview = (EPaneView) (int) get_view_id();
            }
            else if(puh->is_type_of(pane_view_update_hint::TypeSetView))
            {
               set_cur_tab_by_id(puh->m_eview);
            }
         }
         else if(base < MediaLibraryViewUpdateHint >::bases(pHint))
         {
            ::document * pdoc = GetMediaLibraryDoc();
            if(pdoc != NULL)
            {
               pdoc->update_all_views(pSender, lHint, pHint);
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
         ::filemanager::document * pdoc = (dynamic_cast < application * > (&System))->GetStdFileManagerTemplate()->OpenChild((dynamic_cast < application * > (&System)), false, true);

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





   /*
   void pane_view::_001OnEraseBkgnd(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::erase_bkgnd, perasebkgnd, pobj)
      perasebkgnd->set_result(TRUE);
      perasebkgnd->m_bRet = true;
   }
   */

   BOOL pane_view::PreCreateWindow(CREATESTRUCT& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;   

      return ::userbase::view::PreCreateWindow(cs);
   }

   ::document * pane_view::GetMediaLibraryDoc()
   {
      return ensure_tab_by_id(PaneViewMediaLibrary)->m_pdoc;
   }

   void pane_view::on_create_view(view_data * pviewdata)
   {
      switch(pviewdata->m_id)
      {
      case PaneViewContextMenu:
         {
            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView = &typeid(::userbase::menu_list_view);

            ::view * pview = dynamic_cast < ::view * > (create_view(&cc, this, 101));
            if(pview != NULL)
            {
//               ::userbase::menu_list_view * pmenuview = (::userbase::menu_list_view *) pview;
               pviewdata->m_pdoc = get_document();
               pviewdata->m_pwnd = pview;
            }
         }
         break;
      case PaneViewKaraoke:
         {
            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  &typeid(mplite::view);

            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (create_view(&cc, this, 101));
            if(pview != NULL)
            {
               pviewdata->m_pdoc             = get_document();
               pviewdata->m_pwnd             = pview;
               pviewdata->m_iExtendOnParent  = -1;
            }
         }
         break;
      case PaneViewFileManager:
         {
            ::filemanager::document * pdoc = (dynamic_cast < application * > (get_app()))->GetStdFileManagerTemplate()->OpenChild((dynamic_cast < application * > (get_app())), false, true, this);
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                     pframe->m_bblur_Background = true;
                  }
               }
            }
         }
         break;

      case PaneViewFsManager:
         {
            ::ifs * pifs = new ifs(get_app(), "");
            ::filemanager::document * pdoc = (dynamic_cast < application * > (get_app()))->GetFsManagerTemplate()->OpenChild((dynamic_cast < application * > (get_app())), false, true, this, pifs);
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                     pframe->m_bblur_Background = true;
                  }
               }
            }
         }
         break;

      case PaneViewPlaylist:
         {
            PlaylistDoc * pdoc = (dynamic_cast < application * > (get_app()))->GetPlaylistCentral().GetCurrentPlaylist(false, this);
            
            if(pdoc != NULL)
            {
               document * pplayerdoc = dynamic_cast < document * > (get_document());
               if(pplayerdoc != NULL)
               {
                  pplayerdoc->AttachPlaylist(pdoc);
               }
               if(pdoc != NULL)
               {
                  ::view * pview = pdoc->get_view();
                  if(pview != NULL)
                  {
                     simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pviewdata->m_pdoc = pdoc;
                        pviewdata->m_pwnd = pframe;
                        pframe->m_bblur_Background = true;
                        pframe->m_bCustomFrame = false;
                        pframe->m_wndframework.Enable(false);
                     }
                  }
               }
            }
         }
         break;
      case PaneViewMediaLibrary:
         {
            MediaLibraryDoc * pdoc = dynamic_cast < MediaLibraryDoc * > (m_pdoctemplateAlbum->open_document_file(NULL, FALSE, this));   
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                     pframe->m_bblur_Background = true;
                  }
               }
            }
         }
         break;
      case PaneViewAudioControl:
         {
            GoodMixerDoc * pdoc = dynamic_cast < GoodMixerDoc * > (m_pdoctemplateAudioControl->open_document_file(NULL, FALSE, this));   
            if(pdoc != NULL)
            {
//               ::view * pview = pdoc->get_view();
               if(pdoc != NULL)
               {
                  ::view * pview = pdoc->get_view();
                  if(pview != NULL)
                  {
                     simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pviewdata->m_pdoc = pdoc;
                        pviewdata->m_pwnd = pframe;
                        pframe->m_bblur_Background = true;
                     }
                  }
               }
            }
         }
         break;
      case PaneViewOptions:
         {
            OptionsDoc * pdoc = dynamic_cast < OptionsDoc * > (m_pdoctemplateOptions->open_document_file(NULL, FALSE, this));   
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                     pframe->m_bblur_Background = true;
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

   void pane_view::on_show_view()
   {
      ::userbase::tab_view::on_show_view();
      if(get_view_id() == PaneViewContextMenu)
      {
         xml::node node(get_app());
         node.load(Application.file().as_string(System.dir().matter(
            "mplite\\popup_lyricview.xml")));
         ::userbase::menu_list_view * pmenuview = dynamic_cast < ::userbase::menu_list_view * > (get_view_uie());
         pmenuview->clear();
         pmenuview->LoadMenu(&node, m_pviewdataOld->m_pwnd, WM_USER + 1122);
      }
      else if(get_view_id() == PaneViewKaraoke)
      {
         hide_all_except(get_view_id());
      }
      else if(get_view_id() == PaneViewContextMenu)
      {
         m_pviewdataOld->m_pwnd->ShowWindow(SW_HIDE);
      }
   }


   ::user::interaction * pane_view::GetKaraokeWindow()
   {
      return ensure_tab_by_id(PaneViewKaraoke)->m_pwnd;
   }


   void pane_view::rotate()
   {
      EPaneView eview = (EPaneView) (int) get_view_id();
      EPaneView eviewNew = PaneViewKaraoke;
      switch(eview)
      {
      case PaneViewKaraoke:
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
         eviewNew = PaneViewKaraoke;
         break;
      case PaneViewOptions:
         eviewNew = PaneViewKaraoke;
         break;
      default:
         ASSERT(FALSE);
         break;
      }

      set_cur_tab_by_id(eviewNew);
   }

   void pane_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::_001InstallMessageHandling(pinterface);   
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
   }

} // namespace mplite