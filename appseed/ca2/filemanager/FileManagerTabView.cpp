#include "framework.h"
#include "FileManagerFrame.h"
#include "FileManagerViewUpdateHint.h"
#include "SimpleFileListView.h"
#include "SimpleFolderListView.h"
#include "SimpleFolderTreeView.h"





FileManagerTabView::FileManagerTabView(::ca::application * papp) :
   ca(papp),
   ::user::tab(papp),
   ::userbase::view(papp),
   ::userbase::tab_view(papp),
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
   ::userbase::tab_view::assert_valid();
}

void FileManagerTabView::dump(dump_context & dumpcontext) const
{
   ::userbase::tab_view::dump(dumpcontext);
}

#endif //DEBUG


void FileManagerTabView::install_message_handling(::gen::message::dispatch * pinterface)
{
   ::userbase::tab_view::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &FileManagerTabView::_001OnCreate);
}

void FileManagerTabView::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint)
{
   FileManagerViewInterface::on_update(pSender, lHint, phint);
   ::userbase::tab_view::on_update(pSender, lHint, phint);
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
            FileManagerFrame * pframe =dynamic_cast < FileManagerFrame * > ((::ca::window *) GetParentFrame());
            if(pframe != NULL)
            {
               pframe->m_dataid = str;
            }
         }
         else if(puh->is_type_of(FileManagerViewUpdateHint::TypePop))
         {
            OnActivateFrame(WA_INACTIVE, dynamic_cast < userbase::frame_window * > ( dynamic_cast < ::ca::window * > (GetParentFrame())));
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

   if(pcreatordata->m_id.is_text())
   {

      if(pcreatordata->m_id == "add_location"
         || pcreatordata->m_id == "replace_name")
      {
         ::ca::create_context_sp createcontext(get_app());
         createcontext->m_bMakeVisible = false;
         createcontext->m_puiParent = pcreatordata->m_pholder;
         file_manager_form_document * pdoc = dynamic_cast < file_manager_form_document * > (Application.m_ptemplateForm->open_document_file(createcontext));
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


         pformview->m_pfilemanagerinterface = dynamic_cast < FileManagerInterface * > (m_pviewdata->m_pdoc);
         //pformview->VmsDataInitialize(simpledb::get(get_app())->GetDataServer());
         //pcreatordata->m_pwnd = dynamic_cast < ::user::interaction * >(pformview->GetParentFrame());
         //      file_manager_form_child_frame * pframe = dynamic_cast < file_manager_form_child_frame * >(pcreatordata->m_pwnd);
         //pframe->m_iTabId = iId;
         pcreatordata->m_pdoc = pdoc;
      }

   }
   else if(pcreatordata->m_id == 200000)
   {
      ::ca::create_context_sp createcontext(get_app());
      createcontext->m_bMakeVisible = false;
      createcontext->m_puiParent = this;
      //throw not_implemented_exception();
      file_manager_operation_document * pdoc = dynamic_cast < file_manager_operation_document * > (Application.m_ptemplateOperation->open_document_file(createcontext));
      if(pdoc == NULL)
         return;
      ::view * pview = pdoc->get_view(0);
      //file_manager_form_view * poperationview = dynamic_cast < file_manager_form_view * > (pview);
      pcreatordata->m_pwnd = dynamic_cast < ::user::interaction * >(pview->GetParentFrame());
      //      file_manager_operation_child_frame * pframe = dynamic_cast < file_manager_operation_child_frame * >(pcreatordata->m_pwnd);
      //pframe->m_iTabId = iId;
      pcreatordata->m_pdoc = pdoc;
   }
   else
   {
      ::ca::create_context_sp createcontext(get_app());
      createcontext->m_bMakeVisible = true;
      createcontext->m_puiParent = pcreatordata->m_pholder;
      ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (Application.GetStdFileManagerTemplate()->m_pdoctemplateChild->open_document_file(createcontext));
      simple_frame_window * pwndTopLevel = NULL;
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
         pdoc->get_filemanager_data()->m_ptemplate = System.GetStdFileManagerTemplate();
         pdoc->get_filemanager_data()->m_iTemplate = System.GetStdFileManagerTemplate()->m_iTemplate;
         pdoc->get_filemanager_data()->m_iDocument = System.GetStdFileManagerTemplate()->m_iNextDocument++;
         pdoc->get_filemanager_data()->m_bTransparentBackground = GetFileManager()->get_filemanager_data()->m_bTransparentBackground;
         pdoc->get_filemanager_data()->m_ptemplate->m_strDISection.Format("filemanager(%d)", pdoc->get_filemanager_data()->m_iDocument);
         pdoc->get_filemanager_data()->m_bFileSize = true;




         ::view * pview = pdoc->get_view(0);

         simple_frame_window * pwnd = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());

         if(pwnd != NULL)
         {
            //pwnd->m_workset.SetAppearanceTransparency(frame::Transparent);
            pwnd->m_etranslucency = ::user::window_interface::TranslucencyTotal;
         }
         pwndTopLevel = dynamic_cast < simple_frame_window * > (pview->GetTopLevelFrame());

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
//      ::view * pview = pdoc->get_view(0);
      //pcreatordata->m_pwnd = dynamic_cast < ::user::interaction * >(pview->GetParentFrame());
      //      FileManagerChildFrame * pframe = dynamic_cast < FileManagerChildFrame * >(pcreatordata->m_pwnd);
      //pframe->m_iTabId = iId;
      pcreatordata->m_pdoc = pdoc;
      if(pwndTopLevel != NULL)
      {
         pwndTopLevel->layout();
      }
   }
}


void FileManagerTabView::_001OnCreate(gen::signal_object * pobj)
{
   //   SCAST_PTR(::gen::message::create, pcreate, pobj)

   pobj->previous();

}
