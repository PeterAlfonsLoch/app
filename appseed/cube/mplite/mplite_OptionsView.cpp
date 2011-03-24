#include "StdAfx.h"
#include "OptionsView.h"

#include "OptionsChildFrame.h"
#include "OptionsAudioDevicesView.h"
#include "OptionsFileAssociationView.h"
#include "OptionsKaraokeView.h"
#include "OptionsViewUpdateHint.h"
#include "OptionsFoldersView.h"

namespace mplite
{

   OptionsView::OptionsView(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

      m_etranslucency      = TranslucencyPresent;

   }

   OptionsView::~OptionsView()
   {
   }

   void OptionsView::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &OptionsView::_001OnCreate);
   }


#ifdef _DEBUG
   void OptionsView::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void OptionsView::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
#endif //_DEBUG

   void OptionsView::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;

      add_tab("<string id='mplite:options_view_tab_folders'>Folders</string>", OptionsViewFolders);
      add_tab("<string id='mplite:options_view_tab_file_association'>File Association</string>", OptionsViewFileAssociation);
      add_tab("<string id='mplite:options_view_tab_karaoke'>Karaoke</string>", OptionsViewKaraoke);
      add_tab("<string id='mplite:options_view_tab_audio_devices'>Audio Devices</string>", OptionsViewAudioDevices);

      set_cur_tab_by_id(OptionsViewFolders);
   }


   void OptionsView::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      if(pHint != NULL)
      {
         if(base < ::view_update_hint > :: bases(pHint))
         {
            ::view_update_hint * puh = dynamic_cast < ::view_update_hint * > (pHint);
            if(puh->m_etype == ::view_update_hint::TypeOpenDocument)
            {
               set_cur_tab_by_id(OptionsViewFolders);
            }
         }
      }

   }

   void OptionsView::on_show_view()
   {
      ::userbase::tab_view::on_show_view();
      OptionsChildFrame * pframe = dynamic_cast < OptionsChildFrame * > (GetParentFrame());
      switch(get_view_id())
      {
      case OptionsViewFileAssociation:
         {
            pframe->LoadToolBar(0, "mplite\\toolbar_options_frame.xml");
           }
         break;
      case OptionsViewFolders:
         {
            pframe->LoadToolBar(0, "mplite\\toolbar_options_frame.xml");
         }
         break;
      case OptionsViewAudioDevices:
         {
            pframe->LoadToolBar(0, "mplite\\toolbar_options_frame.xml");
         }
         break;
      case OptionsViewKaraoke:
         {
            pframe->LoadToolBar(0, "mplite\\toolbar_options_frame.xml");
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }
      
   }

   void OptionsView::on_create_view(view_data * pviewdata)
   {
      switch(pviewdata->m_id)
      {
      case OptionsViewFileAssociation:
         {
            create_context cc;
            cc.m_pCurrentDoc = NULL;
            cc.m_typeinfoNewView =  &typeid(OptionsFileAssociationView);

            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (create_view(&cc, this, OptionsViewFileAssociation));
            if(pview != NULL)
            {
               pviewdata->m_pdoc = get_document();
               pviewdata->m_pwnd = pview;
               pviewdata->m_eflag.signalize(view_data::flag_hide_all_others_on_show);
            }
         }
         break;
      case OptionsViewFolders:
         {
            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  &typeid(OptionsFoldersView);

            ::userbase::view * pview = dynamic_cast < OptionsFoldersView * > (create_view(&cc, this, OptionsViewFolders));
            if(pview != NULL)
            {
               pviewdata->m_pdoc = get_document();
               pviewdata->m_pwnd = pview;
               pviewdata->m_eflag.signalize(view_data::flag_hide_all_others_on_show);
            }
         }
         break;
      case OptionsViewAudioDevices:
         {
            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  &typeid(OptionsAudioDevicesView);

            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (create_view(&cc, this, OptionsViewAudioDevices));
            if(pview != NULL)
            {
               pviewdata->m_pdoc = get_document();
               pviewdata->m_pwnd = pview;
               pviewdata->m_eflag.signalize(view_data::flag_hide_all_others_on_show);
            }
         }
         break;
      case OptionsViewKaraoke:
         {
            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  &typeid(OptionsKaraokeView);

            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (create_view(&cc, this, OptionsViewKaraoke));
            if(pview != NULL)
            {
               pviewdata->m_pdoc = get_document();
               pviewdata->m_pwnd = pview;
               pviewdata->m_eflag.signalize(view_data::flag_hide_all_others_on_show);
            }
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }

   }


} // namespace mplite