#include "framework.h"





FileManagerTabView::FileManagerTabView(sp(::ca2::application) papp) :
   ca2(papp),
   ::user::tab(papp),
   
   ::user::tab_view(papp),
   ::userex::pane_tab_view(papp),
   place_holder_container(papp)
{
}

FileManagerTabView::~FileManagerTabView()
{
}


#ifdef DEBUG
void FileManagerTabView::assert_valid() const
{
   ::user::tab_view::assert_valid();
}

void FileManagerTabView::dump(dump_context & dumpcontext) const
{
   ::user::tab_view::dump(dumpcontext);
}

#endif //DEBUG


void FileManagerTabView::install_message_handling(::ca2::message::dispatch * pinterface)
{
   ::user::tab_view::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &FileManagerTabView::_001OnCreate);
}

void FileManagerTabView::on_update(sp(::user::view) pSender, LPARAM lHint, ::ca2::object* phint)
{
   FileManagerViewInterface::on_update(pSender, lHint, phint);
   ::user::tab_view::on_update(pSender, lHint, phint);
   if(phint != NULL)
   {
      if(base < FileManagerViewUpdateHint > :: bases(phint))
      {
         FileManagerViewUpdateHint * puh = (FileManagerViewUpdateHint *) phint;
         if(puh->is_type_of(FileManagerViewUpdateHint::TypeCreateViews) && m_viewmap.get_count() == 0)
         {
            set_cur_tab_by_id(0);
         }
         if(puh->is_type_of(FileManagerViewUpdateHint::TypeInitialize))
         {
            string str;
            str.Format("FileManagerFrame(%d,%d)", GetFileManager()->get_filemanager_data()->m_iTemplate, GetFileManager()->get_filemanager_data()->m_iDocument);
            sp(FileManagerFrame) pframe = ((sp(::ca2::window)) GetParentFrame());
            if(pframe != NULL)
            {
               pframe->m_dataid = str;
            }
         }
         else if(puh->is_type_of(FileManagerViewUpdateHint::TypePop))
         {
            OnActivateFrame(WA_INACTIVE, ( (GetParentFrame())));
            if(GetTypedParent < FileManagerMainFrame > () != NULL)
            {
               GetTypedParent < FileManagerMainFrame >()->InitialUpdateFrame(NULL, TRUE);
               GetTypedParent < FileManagerMainFrame >()->ShowWindow(SW_SHOW);
               GetTypedParent < FileManagerMainFrame >()->ActivateFrame(SW_SHOW);
            }
            else
            {
               GetParentFrame()->InitialUpdateFrame(NULL, TRUE);
               GetParentFrame()->ShowWindow(SW_SHOW);
               GetParentFrame()->ActivateFrame(SW_SHOW);
            }
            OnActivateView(TRUE, this, this);
            RedrawWindow();
         }
      }
   }
   if(lHint == 89124592)
   {
      set_cur_tab_by_id("add_location");
   }
   else if(lHint == 89124593)
   {
      set_cur_tab_by_id("replace_name");
   }


}

void FileManagerTabView::on_create_view(::user::view_creator_data * pcreatordata)
{

   if(pcreatordata->m_id == "add_location"
      || pcreatordata->m_id == "replace_name")
   {
      sp(::ca2::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible = false;
      createcontext->m_puiParent = pcreatordata->m_pholder;
      sp(file_manager_form_document) pdoc = Application.filemanager().m_ptemplateForm->open_document_file(createcontext);
      if(pdoc == NULL)
         return;
      file_manager_form_view * pformview = pdoc->get_typed_view < file_manager_form_view > ();
      file_manager_form_update_hint uh;
      uh.m_etype = file_manager_form_update_hint::type_browse;
      if(pcreatordata->m_id == "replace_name")
      {
         uh.m_strForm = "filemanager\\replace_name_in_file_system.xhtml";
      }
      else if(pcreatordata->m_id == "add_location")
      {
         uh.m_strForm = "filemanager_add_location_1.xhtml";
      }
      pdoc->update_all_views(NULL, 0, &uh);

      uh.m_etype = file_manager_form_update_hint::type_get_form_view;
      pdoc->update_all_views(NULL, 0, &uh);

      uh.m_etype = file_manager_form_update_hint::type_after_browse;
      pdoc->update_all_views(NULL, 0, &uh);


      pformview->m_pfilemanagerinterface =  (m_pviewdata->m_pdoc);
      //pformview->VmsDataInitialize(simpledb::get(get_app())->GetDataServer());
      //pcreatordata->m_pwnd = (pformview->GetParentFrame());
      //      file_manager_form_child_frame * pframe = dynamic_cast < file_manager_form_child_frame * >(pcreatordata->m_pwnd);
      //pframe->m_iTabId = iId;
      pcreatordata->m_pdoc = pdoc;
   }
   else if(pcreatordata->m_id == 200000)
   {
      sp(::ca2::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible = false;
      createcontext->m_puiParent = this;
      //throw not_implemented(get_app());
      sp(file_manager_operation_document) pdoc =  (Application.filemanager().m_ptemplateOperation->open_document_file(createcontext));
      if(pdoc == NULL)
         return;
      sp(::user::view) pview = pdoc->get_view(0);
      //file_manager_form_view * poperationview = dynamic_cast < file_manager_form_view * > (pview);
      pcreatordata->m_pwnd = (pview->GetParentFrame());
      //      file_manager_operation_child_frame * pframe = dynamic_cast < file_manager_operation_child_frame * >(pcreatordata->m_pwnd);
      //pframe->m_iTabId = iId;
      pcreatordata->m_pdoc = pdoc;
   }
   else
   {
      sp(::ca2::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible = true;
      createcontext->m_puiParent = pcreatordata->m_pholder;
      sp(::filemanager::document) pdoc =  (Application.filemanager().std().m_pdoctemplateChild->open_document_file(createcontext));
      sp(simple_frame_window) pwndTopLevel = NULL;
      if(pdoc != NULL)
         //if(false)
      {
         //      pdoc->get_filemanager_data()->m_uiMenuBar = m_uiMenuBar;
         //      pdoc->get_filemanager_data()->m_uiToolBar = m_uiToolBar;



         pdoc->set().m_spafsdata = GetFileManagerDoc()->set().m_spafsdata;
         pdoc->set().m_fsdatamap = GetFileManagerDoc()->set().m_fsdatamap;

         ::filemanager::data * pfilemanagerdata = new filemanager::data(get_app());

         pdoc->set_filemanager_data(pfilemanagerdata);

         pdoc->get_filemanager_data()->m_pcallback = GetFileManager()->get_filemanager_data()->m_pcallback;
         pdoc->get_filemanager_data()->m_pmanager  = pdoc;
         pdoc->get_filemanager_data()->m_pmanagerMain  = GetFileManager();
         pdoc->get_filemanager_data()->m_ptemplate = &System.filemanager().std();
         pdoc->get_filemanager_data()->m_iTemplate = System.filemanager().std().m_iTemplate;
         pdoc->get_filemanager_data()->m_iDocument = System.filemanager().std().m_iNextDocument++;
         pdoc->get_filemanager_data()->m_bTransparentBackground = GetFileManager()->get_filemanager_data()->m_bTransparentBackground;
         pdoc->get_filemanager_data()->m_ptemplate->m_strDISection.Format("filemanager(%d)", pdoc->get_filemanager_data()->m_iDocument);
         pdoc->get_filemanager_data()->m_bFileSize = true;




         sp(::user::view) pview = pdoc->get_view(0);

         sp(simple_frame_window) pwnd =  (pview->GetParentFrame());

         if(pwnd != NULL)
         {
            //pwnd->m_workset.SetAppearanceTransparency(frame::Transparent);
            pwnd->m_etranslucency = ::user::window_interface::TranslucencyTotal;
         }
         pwndTopLevel =  (pview->GetTopLevelFrame());

         if(pwndTopLevel != NULL)
         {
            //pwndTopLevel->m_workset.SetAppearanceTransparency(frame::Transparent);
            pwndTopLevel->m_etranslucency = ::user::window_interface::TranslucencyPresent;
         }

         //pdoc->CreateViews();

         // O m_panager desse file explorer não pode ser o Manager deste
         // documento. Cada file explorer, tem que ter seu próprio
         // m_manager.
         /*FileManagerViewUpdateHint uh;

         uh.set_type(FileManagerViewUpdateHint::TypeSetManager);
         uh.m_pview = NULL;
         uh.GetFileManager() = get_document();
         */

         ///pdoc->update_all_views(NULL, 0, &uh);

         pdoc->Initialize(true);
      }
      if(pdoc == NULL)
         return;
//      sp(::user::view) pview = pdoc->get_view(0);
      //pcreatordata->m_pwnd = (pview->GetParentFrame());
      //      sp(FileManagerChildFrame) pframe = (pcreatordata->m_pwnd);
      //pframe->m_iTabId = iId;
      pcreatordata->m_pdoc = pdoc;
      if(pwndTopLevel != NULL)
      {
         pwndTopLevel->layout();
      }
   }
}


void FileManagerTabView::_001OnCreate(::ca2::signal_object * pobj)
{
   //   SCAST_PTR(::ca2::message::create, pcreate, pobj)

   pobj->previous();

}
