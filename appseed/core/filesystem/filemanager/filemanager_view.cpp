//#include "framework.h"


namespace filemanager
{


   view::view(::aura::application * papp) :
      object(papp),
      ::user::split_layout(papp),
      ::user::split_view(papp),
      place_holder_container(papp)
   {
   }

   view::~view()
   {
   }

   void view::assert_valid() const
   {
      ::user::split_view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::split_view::dump(dumpcontext);
   }



   void view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {
      ::filemanager::impact::on_update(pSender, lHint, phint);
      ::user::split_view::on_update(pSender, lHint, phint);
      if (phint != NULL)
      {
         if (base_class < update_hint >::bases(phint))
         {
            update_hint * puh = (update_hint *)phint;
            if (get_filemanager_manager() == puh->m_pmanager)
            {
               if (puh->is_type_of(update_hint::TypeInitialize))
               {
                  string str;
                  str.Format("::frame(%d,%d)", get_filemanager_data()->m_iTemplate, get_filemanager_data()->m_iDocument);
                  sp(frame) pframe = ((::window_sp) GetParentFrame());
                  if (pframe != NULL)
                  {
                     pframe->m_dataid = str;
                  }
                  m_puserschemaSchema = get_filemanager_data();

               }
               else if (puh->is_type_of(update_hint::TypePop))
               {

                  OnActivateFrame(WA_INACTIVE, ((GetParentFrame())));

                  sp(::user::frame_window) spframewindow = GetParentFrame();

                  if (spframewindow.is_set())
                  {

                     spframewindow->ActivateFrame(SW_SHOW);

                  }

                  OnActivateView(TRUE, this, this);

                  RedrawWindow();

               }
               else if(puh->is_type_of(update_hint::TypeCreateBars))
               {

                  //sp(simple_frame_window) pframe = (GetParentFrame());

                  //if(pframe != NULL)
                  {

                    // pframe->create_bars();

                  }

               }
               else if(puh->is_type_of(update_hint::TypeTopicStart))
               {
                  
                  if (get_filemanager_manager()->m_emode != manager::mode_import && get_pane_count() == 2)
                  {

                     sp(simple_frame_window) pframe = (GetParentFrame());

                     if (pframe != NULL)
                     {

                        pframe->create_bars();

                     }

                     ::filemanager::save_as_view * ptopview = create_view < ::filemanager::save_as_view >();
                     
                     if (ptopview == NULL)
                     {

                        System.simple_message_box(NULL, "Could not create folder tree ::user::impact");

                     }
                     
                     ptopview->m_pmanager = get_filemanager_manager();

                     InsertPaneAt(0, ptopview, true);

                     ::file::path path = get_filemanager_data()->m_pdocumentTopic->get_file_path();

                     string strName = path.title() + " - " + System.datetime().international().get_gmt_date_time() + "." + path.ext();

                     strName.replace(":", "-");

                     strName =  strName;

                     ptopview->m_pedit->_001SetText(strName, puh->m_actioncontext);

                     get_filemanager_data()->m_pmanager->m_strTopic = strName;

                     set_position(0, 28);
                     
                     set_position(1, 56);

                     rect rectClient;
                     
                     GetClientRect(rectClient);
                     
                     set_need_layout();

                     pframe->set_need_layout();

                  }

               }
               else if (puh->is_type_of(update_hint::TypeTopicCancel))
               {
                  if (base_class < ::filemanager::save_as_view >::bases(get_pane_window(0)))
                  {
                     //RemovePaneAt(0);
                     //set_position(0, 49);
                     //on_layout();
                  }
               }
               else if (puh->is_type_of(update_hint::TypeTopicOK))
               {

                  if (m_pmanager->m_emode == manager::mode_import)
                  {

                     puh->m_bOk = get_filemanager_data()->m_pdocumentTopic->on_filemanager_open(m_pmanager, puh->m_filepath);

                  }

               }
            }
         }
      }

      tab_view * ptabview = GetParentFrame()->GetTypedParent < tab_view >();
      if (ptabview != NULL)
      {
         ptabview->on_update(this, lHint, phint);
      }

   }

   void view::on_create_views()
   {

      if (get_pane_count() > 0)
         return;

      bool bPathView = !Application.command_thread()->m_varTopicQuery.has_property("no_path_view");

      SetPaneCount(bPathView ? 2 : 1);

      SetSplitOrientation(orientation_horizontal);

      if (bPathView)
      {

         set_position(0, 24);

         m_panea[0]->m_bFixedSize = true;

         initialize_split_layout();

         path_view * ppathview = create_pane_view < path_view >(0);

         if (ppathview == NULL)
         {

            System.simple_message_box(NULL, "Could not create filemanager path view");

         }

      }
      else
      {

         initialize_split_layout();

      }


      main_view * pmainview = create_pane_view < main_view >(bPathView ? 1 : 0);

      if (pmainview == NULL)
      {

         System.simple_message_box(NULL, "Could not create file list ::user::impact");

      }

      //SetPane(, pmainview, false);

      //pmainview->create_views();

   }


} // namespace filemanager



