#include "framework.h"


namespace nature
{


   pane_view::pane_view(sp(::base::application) papp) :
      element(papp),
      ::user::tab(papp),
      
      ::user::tab_view(papp),
      pane_tab_view(papp),
      place_holder_container(papp)
   {

      m_pdoctemplateAppearance = new ::user::single_document_template(
         get_app(),
         "nature/appearance",
         System.type_info < ::user::document > (),
         System.type_info < simple_child_frame > (),
         System.type_info < appearance_view > ());

   }

   pane_view::~pane_view()
   {
   }

#ifdef DEBUG
   void pane_view::assert_valid() const
   {
      ::userex::pane_tab_view::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::userex::pane_tab_view::dump(dumpcontext);
   }
#endif //DEBUG


   void pane_view::_001OnCreate(signal_details * pobj)
   {
      //SCAST_PTR(::message::create, pcreate, pobj)
      if(pobj->previous())
         return;

      ::user::tab::get_data()->m_iHeightAddUp = 5;


      add_tab("DevEdge", nature::PaneViewDevEdge);
      add_tab("FileManager", nature::PaneViewFileManager);
      add_tab("Appearance", nature::PaneViewAppearance);
      add_image_tab("", Application.dir().matter("image/keyboard-h21.png"), nature::PaneViewKeyboardLayout);
      add_image_tab("", Application.dir().matter("earth.png"), nature::PaneViewIdioma);


      set_cur_tab_by_id(nature::PaneViewDevEdge);





      m_pviewdata->m_pwnd->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
      ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

   //   m_plightview = (MusicalPlayerLightView *) m_pviewdata->m_pwnd;

      layout();
   }

   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      switch(pcreatordata->m_id)
      {
      case nature::PaneViewIdioma:
         {
//            create_context cc;
  //          cc.m_pCurrentDoc = get_document();
    //        cc.m_typeinfoNewView =  System.type_info < ::user::menu_list_view > ();

            sp(::user::menu_list_view) pview =  (::user::impact::create_view(System.type_info < ::user::menu_list_view > (), get_document(),NULL, pcreatordata->m_pholder, 101).m_p);
            if(pview != NULL)
            {
               sp(::user::menu_list_view) pmenuview = (sp(::user::menu_list_view)) pview;
               pmenuview->LoadXmlMenu("idioma_nature_menu.xml");
               pmenuview->m_bAutoClose = false;
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }
         }
         break;

   /*         create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  System.type_info < ::user::menu_list_view > ();

            sp(::userex::pane_tab_view) pview = (CreateView(&cc, 101, this));
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
      case nature::PaneViewDevEdge:
         {
//            create_context cc;
  //          cc.m_pCurrentDoc = get_document();
    //        cc.m_typeinfoNewView =  System.type_info < ::nature::view > ();

            sp(::user::interaction) pview =  (::user::impact::create_view(System.type_info < ::nature::view > (), get_document(), NULL, pcreatordata->m_pholder, 101).m_p);
            if(pview != NULL)
            {
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }
         }
         break;
      case PaneViewAppearance:
         {
            sp(::user::document) pdoc = (m_pdoctemplateAppearance->open_new_document());
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

      case PaneViewKeyboardLayout:
         {
            m_pkeyboardlayout = create_view < ::userex::keyboard_layout > ();
            m_pkeyboardlayout->CreateViews();
            pcreatordata->m_pdoc = m_pkeyboardlayout->m_pdoc;
            pcreatordata->m_pwnd = m_pkeyboardlayout;
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

      IGUI_WIN_MSG_LINK(WM_CREATE      , pinterface, this, &pane_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122 , pinterface, this, &pane_view::_001OnMenuMessage);

   }

   void pane_view::on_show_view()
   {
      ::userex::pane_tab_view::on_show_view();
      if(m_pviewdata->m_id == nature::PaneViewIdioma)
      {
         sp(::user::menu_list_view) pmenuview =  (m_pviewdata->m_pwnd.m_p);
         pmenuview->m_puiNotify = m_pviewdataOld == NULL ? NULL : (m_pviewdataOld->m_pwnd.m_p);
         pmenuview->m_uiMessage = WM_USER + 1122;
         pmenuview->TrackPopupMenu(pmenuview, GetParentFrame());
      }
   }

   void pane_view::on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(pHint);
   }

} // namespace nature
