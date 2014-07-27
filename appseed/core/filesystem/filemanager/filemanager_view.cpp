#include "framework.h"


namespace filemanager
{


   view::view(sp(::base::application) papp) :
      element(papp),
      ::user::split_layout(papp),
      ::user::split_view(papp),
      place_holder_container(papp)
   {
   }

   view::~view()
   {
   }

#ifdef DEBUG
   void view::assert_valid() const
   {
      ::user::split_view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::split_view::dump(dumpcontext);
   }

#endif //DEBUG


   void view::on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint)
   {
      impact::on_update(pSender, lHint, phint);
      ::user::split_view::on_update(pSender, lHint, phint);
      if (phint != NULL)
      {
         if (base_class < update_hint >::bases(phint))
         {
            update_hint * puh = (update_hint *)phint;
            if (get_filemanager_template() == puh->m_pmanager)
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

                  sp(simple_frame_window) pframe = (GetParentFrame());

                  if(pframe != NULL)
                  {

                     pframe->create_bars();

                  }

               }
               else if(puh->is_type_of(update_hint::TypeSaveAsStart))
               {
                  if (!base_class < ::filemanager::save_as_view >::bases(get_pane_window(0)))
                  {
                     //create_context cc;
                     //cc.m_usercreatecontext.m_pCurrentDoc = get_document();
                     //cc.m_usercreatecontext.m_typeinfoNewView =  System.type_info < ::filemanager::save_as_view > ();
                     //cc.m_usercreatecontext.m_pCurrentFrame = this;

                     ::filemanager::save_as_view * ptopview = create_view < ::filemanager::save_as_view >();
                     if (ptopview == NULL)
                     {
                        System.simple_message_box(NULL, "Could not create folder tree ::user::impact");
                     }
                     ptopview->m_pmanager = get_filemanager_manager();
                     InsertPaneAt(0, ptopview, true);
                     string strName =
                        System.file().title_(get_filemanager_data()->m_pdocumentSave->get_path_name())
                        + " - " + System.datetime().international().get_gmt_date_time()
                        + "." + System.file().extension(get_filemanager_data()->m_pdocumentSave->get_path_name());
                     strName.replace(":", "-");
                     strName = System.dir().path(get_filemanager_item().m_strPath, strName);
                     ptopview->_001SetText(strName, puh->m_actioncontext);
                     get_filemanager_data()->m_pmanager->m_strTopic = strName;
                     set_position(0, 49);
                     set_position(1, 49 + 49);
                     layout();
                  }
               }
               else if (puh->is_type_of(update_hint::TypeSaveAsCancel))
               {
                  if (base_class < ::filemanager::save_as_view >::bases(get_pane_window(0)))
                  {
                     RemovePaneAt(0);
                     set_position(0, 49);
                     layout();
                  }
               }
               else if (puh->is_type_of(update_hint::TypeSaveAsOK))
               {
                  ASSERT(get_filemanager_data()->m_pdocumentSave != NULL);

                  string strPath = puh->m_strPath;
                  if (strPath.is_empty())
                  {
                     string strTitle;
                     dynamic_cast <::filemanager::save_as_view *>(get_pane_window(0).m_p)->_001GetText(strTitle);
                     if (System.dir().name(strTitle).has_char() && get_filemanager_manager()->get_fs_data()->is_dir(System.dir().name(strTitle)))
                     {
                        strPath = strTitle;
                     }
                     else if (get_filemanager_manager()->get_fs_data()->is_dir(get_filemanager_item().m_strPath))
                     {
                        strPath = System.dir().path(get_filemanager_item().m_strPath, strTitle);
                     }
                     else if (strTitle.has_char())
                     {
                        strPath = System.dir().path(get_filemanager_item().m_strPath, strTitle);
                     }
                     else
                     {
                        strPath = get_filemanager_item().m_strPath;
                     }
                  }

                  bool bSave = !session().dir().is(strPath);

                  if (bSave && get_filemanager_manager()->get_fs_data()->file_exists(strPath))
                  {
                     if (System.simple_message_box(platform().get_view(), "Do you want to replace the existing file " + strPath + "?", MB_YESNO) == IDNO)
                     {
                        bSave = false;
                     }
                  }

                  update_hint uh;

                  if (bSave)
                  {
                     if (get_filemanager_data()->m_pdocumentSave->do_save(strPath))
                     {
                        uh.set_type(update_hint::TypeSaveAsSaved);
                        uh.m_strPath = strPath;
                     }
                     else
                     {
                        uh.set_type(update_hint::TypeSaveAsSaveFailed);
                     }
                  }
                  else
                  {
                     uh.set_type(update_hint::TypeSaveAsCancel);
                  }
                  get_document()->update_all_views(NULL, 0, &uh);

                  get_filemanager_data()->m_pdocumentSave = NULL;

                  if (base_class < ::filemanager::save_as_view >::bases(get_pane_window(0)))
                  {
                     RemovePaneAt(0);
                     set_position(0, 49);
                     layout();
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

      SetPaneCount(2);

      SetSplitOrientation(orientation_horizontal);

      set_position(0, 24);

      path_view * ppathview = create_view < path_view >();

      if (ppathview == NULL)
      {

         System.simple_message_box(NULL, "Could not create filemanager path view");

      }

      SetPane(0, ppathview, false);

      main_view * pmainview = create_view < main_view >();

      if (pmainview == NULL)
      {

         System.simple_message_box(NULL, "Could not create file list ::user::impact");

      }

      SetPane(1, pmainview, false);

      pmainview->create_views();

   }


} // namespace filemanager



