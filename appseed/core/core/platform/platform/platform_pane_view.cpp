#include "framework.h"


namespace platform
{


   pane_view::pane_view(sp(::axis::application) papp) :
      element(papp),
      ::user::tab(papp),
      
      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

      m_pviewdataOld = NULL;


      m_pviewdata              = NULL;
      m_pviewdataOld              = NULL;

   /*   ::user::single_document_template* pdoctemplate;
      pdoctemplate = new ::user::single_document_template(
         IDR_ALBUM,
         System.type_info < MediaLibraryDoc > (),
         System.type_info < MediaLibraryChildFrame > (),
         System.type_info < ::mplite::library::user::impact > ());
      m_pdoctemplateAlbum = pdoctemplate;

      pdoctemplate = new ::user::single_document_template(
         IDR_ALBUM,
         System.type_info < OptionsDoc > (),
         System.type_info < OptionsChildFrame > (),
         System.type_info < OptionsView > ());


      m_pdoctemplateOptions = pdoctemplate;

      pdoctemplate = new ::user::single_document_template(
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
      ::user::impact::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
   #endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // pane_view message handlers

   void pane_view::_001OnCreate(signal_details * pobj)
   {
//      SCAST_PTR(::message::create, pcreate, pobj)
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
      switch(pcreatordata->m_id)
      {
      case platform::PaneViewContextMenu:
         {
//            create_context cc;
  //          cc.m_pCurrentDoc = get_document();
    //        cc.m_typeinfoNewView =  System.type_info < ::user::menu_list_view > ();

                                           sp(::user::impact) pview = ::user::impact::create_view(System.type_info < ::user::menu_list_view >(),get_document(),null_rect(),pcreatordata->m_pholder,101);
            if(pview != NULL)
            {
               sp(::user::menu_list_view) pmenuview = (sp(::user::menu_list_view)) pview;
               pmenuview->LoadXmlMenu("mplite_popup_lyricview.xml");
               pcreatordata = new ::user::view_creator_data();
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }
         }
         break;

   /*         create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  System.type_info < ::user::menu_list_view > ();

            sp(::user::impact) pview = (CreateView(&cc, 101, this));
            if(pview != NULL)
            {
               sp(::user::menu_list_view) pmenuview = (sp(::user::menu_list_view)) pview;
               pmenuview->m_wnd.LoadMenu(IDR_POPUP_LYRICVIEW);
               pmenuview->m_wnd.m_bAutoClose = false;
               pcreatordata = new ViewData();
               pcreatordata->m_eview = eview;
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }*/
      case platform::PaneViewDevEdge:
         {
            sp(::user::impact) pview = create_view < ::platform::view > ();
            if(pview != NULL)
            {
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }
         }
         break;
      case platform::PaneViewFileManager:
         {
                                           sp(::filemanager::manager) pdoc = platform().filemanager().std().open_child(false,true);
            if(pdoc != NULL)
            {
               sp(::user::impact) pview = pdoc->get_view();
               if(pview != NULL)
               {
                  sp(::user::frame_window) pframe = (pview->GetParentFrame());
                  if(pframe != NULL)
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

   void pane_view::install_message_handling(::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , pinterface, this, &pane_view::_001OnMenuMessage);
   }



} // namespace platform
