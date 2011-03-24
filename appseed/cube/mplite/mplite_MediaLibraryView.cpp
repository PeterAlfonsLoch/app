#include "StdAfx.h"
#include "MediaLibraryExplorerView.h"
#include "MediaLibraryListView.h"
#include "MediaLibraryView.h"
#include "mplite_library_view.h"

namespace mplite
{

   MediaLibraryView::MediaLibraryView(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

      m_etranslucency = TranslucencyPresent;

      m_pviewdata = NULL;

   }

   MediaLibraryView::~MediaLibraryView()
   {
   }

   void MediaLibraryView::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &MediaLibraryView::_001OnCreate);
   }


   #ifdef _DEBUG
   void MediaLibraryView::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void MediaLibraryView::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
   #endif //_DEBUG

   void MediaLibraryView::_001OnCreate(gen::signal_object * pobj) 
   {

      if(pobj->previous())
         return;

      add_tab("<string id='mplite:media_library_tab_all'>All Local Media</string>", MediaLibraryViewAllMedia);
      add_tab("<string id='mplite:media_library_tab_explorer'>Explore Local Media</string>", MediaLibraryViewMediaExplorer);
      add_tab("<string id='mplite:media_library_tab_vmskarlib'>Explore karaoke.veriwell.com.br</string>", MediaLibraryViewKaraokeLibraryExplorer);
      add_tab(ApplicationUser.m_strName + " fs", MediaLibraryViewKaraokeFsExplorer);

      set_cur_tab_by_id(MediaLibraryViewAllMedia);

   }


   void MediaLibraryView::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      if(pHint != NULL)
      {
         if(base < MediaLibraryViewUpdateHint >::bases(pHint))
         {
            MediaLibraryViewUpdateHint * puh = (MediaLibraryViewUpdateHint *) pHint;
            if(puh->is_type_of(MediaLibraryViewUpdateHint::TypeGetView))
            {
               puh->m_eview = (EMediaLibraryView) (int) get_view_id();
            }
            else if(puh->is_type_of(MediaLibraryViewUpdateHint::TypeSetView))
            {
               set_cur_tab_by_id(puh->m_eview);
            }
         }
      }
      
      
   }

   void MediaLibraryView::on_create_view(view_data * pviewdata)
   {
      switch(pviewdata->m_id)
      {
      case MediaLibraryViewAllMedia:
         {
            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView = &typeid(MediaLibraryListView);

            ::user::interaction* pwnd = create_view(&cc, this, 101);
            if(pwnd != NULL)
            {
               pwnd->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
               pviewdata->m_pwnd = pwnd;
            }
         }
         break;
      case MediaLibraryViewMediaExplorer:
         {
            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView = &typeid(MediaLibraryExplorerView);

            ::user::interaction* pwnd = create_view(&cc, this, 102);
            if(pwnd != NULL)
            {
               pviewdata->m_pwnd = pwnd;
            }
         }
         break;
      case MediaLibraryViewKaraokeLibraryExplorer:
         {
            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  &typeid(::mplite::library::view);

            ::user::interaction* pwnd = create_view(&cc, this, 103);
            if(pwnd != NULL)
            {
               pviewdata->m_pwnd = pwnd;

               ::mplite::library::view * pview = dynamic_cast < ::mplite::library::view * > (pwnd);
               pview->CreateViews();
               pview->Start();
            }

         }
         break;
      case MediaLibraryViewKaraokeFsExplorer:
         {
            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  &typeid(::filemanager::fs::simple::view);

            ::user::interaction* pwnd = create_view(&cc, this, 103);
            if(pwnd != NULL)
            {
               pviewdata->m_pwnd = pwnd;

               ::filemanager::fs::simple::view * pview = dynamic_cast < ::filemanager::fs::simple::view * > (pwnd);
               pview->CreateViews();
               pview->start_music();
               pview->set_request_interface(&Application);
            }

         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }
   }

} // namespace mplite
