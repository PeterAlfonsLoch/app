#include "framework.h"

namespace platform
{

   pane_view::pane_view(sp(::ca::application) papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

      m_pviewdataOld = ::null();


      m_etranslucency      = TranslucencyPresent;

      m_pviewdata              = ::null();
      m_pviewdataOld              = ::null();

   /*   ::userbase::single_document_template* pdoctemplate;
      pdoctemplate = new ::userbase::single_document_template(
         IDR_ALBUM,
         System.type_info < MediaLibraryDoc > (),
         System.type_info < MediaLibraryChildFrame > (),
         System.type_info < ::mplite::library::view > ());
      m_pdoctemplateAlbum = pdoctemplate;

      pdoctemplate = new ::userbase::single_document_template(
         IDR_ALBUM,
         System.type_info < OptionsDoc > (),
         System.type_info < OptionsChildFrame > (),
         System.type_info < OptionsView > ());


      m_pdoctemplateOptions = pdoctemplate;

      pdoctemplate = new ::userbase::single_document_template(
         IDR_ALBUM,
         System.type_info < GoodMixerDoc > (),
         System.type_info < simple_child_frame > (),
         System.type_info < MixerMainView > ());

      m_pdoctemplateAudioControl = pdoctemplate;*/


   }

   pane_view::~pane_view()
   {
   }




   /////////////////////////////////////////////////////////////////////////////
   // pane_view diagnostics

   #ifdef DEBUG
   void pane_view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
   #endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // pane_view message handlers

   void pane_view::_001OnCreate(::ca::signal_object * pobj)
   {
//      SCAST_PTR(::ca::message::create, pcreate, pobj)
      if(pobj->previous())
         return;

      add_tab("menu", platform::PaneViewContextMenu);
      add_tab("DevEdge", platform::PaneViewDevEdge);
      add_tab("FileManager", platform::PaneViewFileManager);

      set_cur_tab_by_id(platform::PaneViewDevEdge);


   //   m_pviewdata->m_pwnd->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
     // ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

   //   m_plightview = (MusicalPlayerLightView *) m_pviewdata->m_pwnd;

      layout();
   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      sp(application) papp = GetParentFrame()->get_app();
      switch(pcreatordata->m_id)
      {
      case platform::PaneViewContextMenu:
         {
//            create_context cc;
  //          cc.m_pCurrentDoc = get_document();
    //        cc.m_typeinfoNewView =  System.type_info < ::userbase::menu_list_view > ();

            sp(::userbase::view) pview = (view::create_view(System.type_info < ::userbase::menu_list_view > (), get_document(), this, 101).m_p);
            if(pview != ::null())
            {
               sp(::userbase::menu_list_view) pmenuview = (sp(::userbase::menu_list_view)) pview;
               pmenuview->LoadXmlMenu("mplite_popup_lyricview.xml");
               pcreatordata = new ::user::view_creator_data();
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }
         }
         break;

   /*         create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  System.type_info < ::userbase::menu_list_view > ();

            sp(::userbase::view) pview = (CreateView(&cc, 101, this));
            if(pview != ::null())
            {
               sp(::userbase::menu_list_view) pmenuview = (sp(::userbase::menu_list_view)) pview;
               pmenuview->m_wnd.LoadMenu(IDR_POPUP_LYRICVIEW);
               pmenuview->m_wnd.m_bAutoClose = false;
               pcreatordata = new ViewData();
               pcreatordata->m_eview = eview;
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }*/
      case platform::PaneViewDevEdge:
         {
            sp(::userbase::view) pview = create_view < platform::view > ();
            if(pview != ::null())
            {
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }
         }
         break;
      case platform::PaneViewFileManager:
         {
            sp(::filemanager::document) pdoc = papp->filemanager().std().OpenChild(false, true);
            if(pdoc != ::null())
            {
               sp(::view) pview = pdoc->get_view();
               if(pview != ::null())
               {
                  sp(::userbase::frame_window) pframe = (pview->GetParentFrame());
                  if(pframe != ::null())
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;


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

   void pane_view::install_message_handling(::ca::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , pinterface, this, &pane_view::_001OnMenuMessage);
   }



} // namespace platform
