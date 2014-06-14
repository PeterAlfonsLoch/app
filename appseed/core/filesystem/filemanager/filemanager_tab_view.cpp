#include "framework.h"


namespace filemanager
{


   tab_view::tab_view(sp(::base::application) papp) :
      element(papp),
      ::filemanager::data_interface(papp),
      ::user::tab(papp),
      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {
   }

   tab_view::~tab_view()
   {
   }


#ifdef DEBUG
   void tab_view::assert_valid() const
   {
      ::user::tab_view::assert_valid();
   }

   void tab_view::dump(dump_context & dumpcontext) const
   {
      ::user::tab_view::dump(dumpcontext);
   }

#endif //DEBUG


   void tab_view::install_message_handling(::message::dispatch * pinterface)
   {

      ::user::tab_view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &tab_view::_001OnCreate);

   }


   void tab_view::on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint)
   {

      data_interface::on_update(pSender, lHint, phint);

      ::user::tab_view::on_update(pSender, lHint, phint);

      if (phint != NULL)
      {

         if (base_class < ::user::view_update_hint > ::bases(phint))
         {

            sp(::user::view_update_hint) puh = phint;

            if (puh->is_type_of(::user::view_update_hint::hint_open_document))
            {

               if (m_viewmap.get_count() == 0)
               {

                  set_cur_tab_by_id(0);

               }
               
            }

         }
         else if (base_class < update_hint > ::bases(phint))
         {

            update_hint * puh = (update_hint *) phint;

            if (puh->is_type_of(update_hint::TypeInitialize))
            {

               string str;

               str.Format("frame(%d,%d)", GetFileManager()->get_filemanager_data()->m_iTemplate, GetFileManager()->get_filemanager_data()->m_iDocument);

               sp(frame) pframe = ((::window_sp) GetParentFrame());

               if (pframe != NULL)
               {

                  pframe->m_dataid = str;

               }

            }
            else if (puh->is_type_of(update_hint::TypePop))
            {
               OnActivateFrame(WA_INACTIVE, ((GetParentFrame())));
               if (GetTypedParent < main_frame >() != NULL)
               {
                  GetTypedParent < main_frame >()->InitialUpdateFrame(NULL, TRUE);
                  GetTypedParent < main_frame >()->ShowWindow(SW_SHOW);
                  GetTypedParent < main_frame >()->ActivateFrame(SW_SHOW);
               }
               else
               {

                  sp(::user::frame_window) spframewindow = GetParentFrame();

                  if (spframewindow.is_set())
                  {
                     spframewindow->InitialUpdateFrame(NULL, TRUE);
                     spframewindow->ShowWindow(SW_SHOW);
                     spframewindow->ActivateFrame(SW_SHOW);
                  }

               }
               OnActivateView(TRUE, this, this);
               RedrawWindow();
            }
         }
      }
      if (lHint == 89124592)
      {
         set_cur_tab_by_id("add_location");
      }
      else if (lHint == 89124593)
      {
         set_cur_tab_by_id("replace_name");
      }


   }

   void tab_view::on_create_view(::user::view_creator_data * pcreatordata)
   {

      if (pcreatordata->m_id == "add_location"
         || pcreatordata->m_id == "replace_name")
      {
         sp(::create_context) createcontext(allocer());
         createcontext->m_bMakeVisible = false;
         createcontext->m_puiParent = pcreatordata->m_pholder;
         sp(file_manager_form_document) pdoc = PlaneSession.filemanager().m_ptemplateForm->open_document_file(createcontext);
         if (pdoc == NULL)
            return;
         file_manager_form_view * pformview = pdoc->get_typed_view < file_manager_form_view >();
         file_manager_form_update_hint uh;
         uh.m_etype = file_manager_form_update_hint::type_browse;
         if (pcreatordata->m_id == "replace_name")
         {
            uh.m_strForm = "filemanager\\replace_name_in_file_system.xhtml";
         }
         else if (pcreatordata->m_id == "add_location")
         {
            uh.m_strForm = "filemanager_add_location_1.xhtml";
         }
         pdoc->update_all_views(NULL, 0, &uh);

         uh.m_etype = file_manager_form_update_hint::type_get_form_view;
         pdoc->update_all_views(NULL, 0, &uh);

         uh.m_etype = file_manager_form_update_hint::type_after_browse;
         pdoc->update_all_views(NULL, 0, &uh);


         pformview->m_pfilemanagerinterface = (m_pviewdata->m_pdoc);
         //pformview->VmsDataInitialize(simpledb::get(get_app())->GetDataServer());
         //pcreatordata->m_pwnd = (pformview->GetParentFrame());
         //      file_manager_form_child_frame * pframe = dynamic_cast < file_manager_form_child_frame * >(pcreatordata->m_pwnd);
         //pframe->m_iTabId = iId;
         pcreatordata->m_pdoc = pdoc;
      }
      else if (pcreatordata->m_id == 200000)
      {
         sp(::create_context) createcontext(allocer());
         createcontext->m_bMakeVisible = false;
         createcontext->m_puiParent = this;
         //throw not_implemented(get_app());
         sp(file_manager_operation_document) pdoc = (PlaneSession.filemanager().m_ptemplateOperation->open_document_file(createcontext));
         if (pdoc == NULL)
            return;
         sp(::user::impact) pview = pdoc->get_view(0);
         //file_manager_form_view * poperationview = dynamic_cast < file_manager_form_view * > (pview);
         pcreatordata->m_pwnd = (pview->GetParentFrame());
         //      file_manager_operation_child_frame * pframe = dynamic_cast < file_manager_operation_child_frame * >(pcreatordata->m_pwnd);
         //pframe->m_iTabId = iId;
         pcreatordata->m_pdoc = pdoc;
      }
      else
      {
         sp(::create_context) createcontext(allocer());
         createcontext->m_bMakeVisible = true;
         createcontext->m_puiParent = pcreatordata->m_pholder;
         sp(document) pdoc = (PlaneSession.filemanager().std().m_pdoctemplateChild->open_document_file(createcontext));
         sp(simple_frame_window) pwndTopLevel = NULL;
         if (pdoc != NULL)
            //if(false)
         {
            //      pdoc->get_filemanager_data()->m_uiMenuBar = m_uiMenuBar;
            //      pdoc->get_filemanager_data()->m_uiToolBar = m_uiToolBar;

            if (m_pfilemanagerinterface.is_null())
               m_pfilemanagerinterface = get_document();

            pdoc->set().m_spafsdata = GetFileManagerDoc()->set().m_spafsdata;
            pdoc->set().m_fsdatamap = GetFileManagerDoc()->set().m_fsdatamap;

            ::filemanager::data * pfilemanagerdata = new ::filemanager::data(get_app());

            pdoc->set_filemanager_data(pfilemanagerdata);

            pdoc->get_filemanager_data()->m_pmanager = pdoc;
            pdoc->get_filemanager_data()->m_pmanagerMain = GetFileManager();
            pdoc->get_filemanager_data()->m_pschema = &PlaneSession.filemanager().std();
            pdoc->get_filemanager_data()->m_iTemplate = PlaneSession.filemanager().std().m_iTemplate;
            pdoc->get_filemanager_data()->m_iDocument = PlaneSession.filemanager().std().m_iNextDocument++;
            pdoc->get_filemanager_data()->m_pschema->m_strDISection.Format("filemanager(%d)", pdoc->get_filemanager_data()->m_iDocument);
            pdoc->get_filemanager_data()->m_bFileSize = true;

            if (GetFileManager()->get_filemanager_data() != NULL)
            {

               pdoc->get_filemanager_data()->m_pcallback = GetFileManager()->get_filemanager_data()->m_pcallback;
               pdoc->get_filemanager_data()->m_bTransparentBackground = GetFileManager()->get_filemanager_data()->m_bTransparentBackground;

            }




            sp(::user::impact) pview = pdoc->get_view(0);

            sp(simple_frame_window) pwnd = (pview->GetParentFrame());

            if (pwnd != NULL)
            {
               //pwnd->m_workset.SetAppearanceTransparency(frame::Transparent);
               pwnd->m_etranslucency = ::user::window_interface::TranslucencyTotal;
            }
            pwndTopLevel = (pview->GetTopLevelFrame());

            if (pwndTopLevel != NULL)
            {
               //pwndTopLevel->m_workset.SetAppearanceTransparency(frame::Transparent);
               pwndTopLevel->m_etranslucency = ::user::window_interface::TranslucencyPresent;
            }

            //pdoc->CreateViews();

            // O m_panager desse file explorer não pode ser o Manager deste
            // documento. Cada file explorer, tem que ter seu próprio
            // m_manager.
            /*update_hint uh;

            uh.set_type(update_hint::TypeSetManager);
            uh.m_pview = NULL;
            uh.GetFileManager() = get_document();
            */

            ///pdoc->update_all_views(NULL, 0, &uh);

            pdoc->Initialize(true);
         }
         if (pdoc == NULL)
            return;
         //      sp(::user::impact) pview = pdoc->get_view(0);
         //pcreatordata->m_pwnd = (pview->GetParentFrame());
         //      sp(child_frame) pframe = (pcreatordata->m_pwnd);
         //pframe->m_iTabId = iId;
         pcreatordata->m_pdoc = pdoc;
         if (pwndTopLevel != NULL)
         {
            pwndTopLevel->layout();
         }
      }
   }


   void tab_view::_001OnCreate(signal_details * pobj)
   {
      //   SCAST_PTR(::message::create, pcreate, pobj)

      pobj->previous();

   }


} // namespace filemanager



