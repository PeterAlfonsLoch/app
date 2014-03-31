#include "framework.h"


namespace userex
{


   pane_tab_view::pane_tab_view(sp(base_application) papp) :
      element(papp),

      ::user::tab_view(papp),
      ::user::tab(papp),
      place_holder_container(papp)
   {


      set_view_creator(this);


   }

   pane_tab_view::~pane_tab_view()
   {
   }

   sp(::user::interaction) pane_tab_view::get_view_uie()
   {
      return ::user::tab_view::get_view_uie();
   }

   id pane_tab_view::get_view_id()
   {
      return ::user::tab_view::get_view_id();
   }

   void pane_tab_view::GetTabClientRect(LPRECT lprect)
   {
      if(m_pviewdata == NULL || m_pviewdata->m_pwnd == NULL || m_pviewdata->m_iExtendOnParent == 0)
      {
         ::user::tab_view::GetTabClientRect(lprect);
      }
      else if(m_pviewdata->m_iExtendOnParent > 0)
      {
         int32_t i = m_pviewdata->m_iExtendOnParent;
         sp(::user::interaction) pui = m_pviewdata->m_pwnd;
         sp(::user::interaction) puiNext = m_pviewdata->m_pwnd;
         for(; i > 0; i--)
         {
            puiNext = pui->get_parent();
            if(puiNext == NULL || !puiNext->IsWindow())
               break;
            pui = puiNext;
         }
         pui->GetWindowRect(lprect);
         ScreenToClient(lprect);
      }
      else if(m_pviewdata->m_iExtendOnParent < 0)
      {
         sp(::user::interaction) pui = m_pviewdata->m_pwnd;
         sp(::user::interaction) puiNext = m_pviewdata->m_pwnd;
         user::interaction_ptr_array wnda(get_app());
         while(true)
         {
            wnda.add(pui);
            puiNext = pui->get_parent();
            if(puiNext == NULL || (pui->m_pimpl.m_p) != NULL)
               break;
            pui = puiNext;
         }
         //         int32_t i = max(0, wnda.get_size() + m_pviewdata->m_iExtendOnParent);
         pui = wnda(wnda.get_size() + m_pviewdata->m_iExtendOnParent);
         pui->GetWindowRect(lprect);
         ScreenToClient(lprect);
      }
   }


   void pane_tab_view::on_show_view()
   {
      ::user::tab_view::on_show_view();
      ::user::view_creator::on_show_view();
      if(m_pviewdata != NULL && m_pviewdata->m_id != "file_manager" && m_pviewdataOld != NULL && m_pviewdataOld->m_id == "file_manager")
      {
         if(GetParentFrame()->ContinueModal(0))
         {
            GetParentFrame()->EndModalLoop("yes");
         }
         if(get_filemanager_document() != NULL)
         {
            get_filemanager_document()->get_filemanager_data()->m_pdocumentSave = NULL;
         }
      }

   }

   void pane_tab_view::on_new_view_creator_data(::user::view_creator_data * pcreatordata)
   {

      ::index iTab = get_tab_by_id(pcreatordata->m_id);

      pcreatordata->m_pholder = get_new_place_holder();

      if(iTab < 0)
         return;

      pane * ppane = (pane *) get_data()->m_panea.element_at(iTab);

      if(ppane == NULL)
         return;

      ppane->m_pholder = pcreatordata->m_pholder;

      if(ppane->m_pholder == NULL)
         return;

      pcreatordata->m_pviewdata = (void *) ppane;

   }


   bool pane_tab_view::on_hold(sp(::user::interaction) pui, sp(::user::place_holder) pholder)
   {
      if(!::user::place_holder_container::on_hold(pui, pholder))
         return false;
      ::user::tab::pane_array & panea = get_data()->m_panea;
      for(int32_t iTab = 0; iTab < panea.get_count(); iTab++)
      {
         if(panea[iTab].m_pholder == pholder)
         {
            ::user::view_creator_data * pcreatordata = ensure(panea[iTab].m_id);
            if(pcreatordata != NULL)
            {
               if(pcreatordata->m_pwnd == NULL)
               {
                  pcreatordata->m_pwnd = pui;
               }
            }
            break;
         }
      }
      return true;
   }

   ::user::view_creator_data * pane_tab_view::ensure(id id)
   {
      return ::user::tab_view::ensure(id);
   }


   void pane_tab_view::on_create_view(::user::view_creator_data * pcreatordata)
   {

      ::core::library * plibrary = NULL;
      if(System.m_idmapCreateViewLibrary.Lookup(pcreatordata->m_id, plibrary) && plibrary != NULL)
      {
         plibrary->on_create_view(pcreatordata);
      }
      else if(pcreatordata->m_id == "file_manager"
         || pcreatordata->m_id == "left_file"
         || pcreatordata->m_id == "right_file"
         || pcreatordata->m_id == "pick_file")
      {

         ::filemanager::data * pfilemanagerdata = oprop("file_manager_data." + *pcreatordata->m_id.m_pstr).cast < ::filemanager::data >();

         if (pfilemanagerdata == NULL)
            pfilemanagerdata = new ::filemanager::data(get_app());




         pfilemanagerdata->m_id = pcreatordata->m_id;

         if(oprop("file_manager_toolbar").is_set())
            pfilemanagerdata->m_strToolBar = oprop("file_manager_toolbar");
         else
            pfilemanagerdata->m_strToolBar = "file_manager_toolbar.xml";

         if(oprop("file_manager_toolbar_save").is_set())
            pfilemanagerdata->m_strToolBarSave = oprop("file_manager_toolbar_save");
         else
            pfilemanagerdata->m_strToolBarSave = "file_manager_toolbar_save.xml";

         sp(::filemanager::document) pdoc = Application.filemanager().std().open_child(true, pfilemanagerdata->m_bTransparentBackground, pcreatordata->m_pholder, pfilemanagerdata);
         if(pdoc != NULL)
         {
            sp(::user::impact) pview = pdoc->get_view();
            if(pview != NULL)
            {
               sp(::user::frame_window) pframe = (sp(::user::frame_window)) pview->GetParentFrame();
               if(pframe != NULL)
               {
                  pcreatordata->m_pdoc = pdoc;
               }
            }
         }
      }
      else if(pcreatordata->m_id == "tabbed_file_manager")
      {

         sp(::create_context) cc(allocer());
         cc->m_bTransparentBackground     = true;
         cc->m_bMakeVisible               = true;
         cc->m_puiParent                  = pcreatordata->m_pholder;

         sp(::filemanager::document) pdoc = Application.filemanager().std().open(cc);

         if(pdoc != NULL)
         {
            sp(::user::impact) pview = pdoc->get_view();
            if(pview != NULL)
            {
               sp(::user::frame_window) pframe = (sp(::user::frame_window)) pview->GetParentFrame();
               if(pframe != NULL)
               {
                  pcreatordata->m_pdoc = pdoc;
                  pcreatordata->m_pwnd = pframe;
               }
            }
         }
      }

   }

   sp(::filemanager::document) pane_tab_view::get_filemanager_document()
   {
      return  (get_view_creator()->get("file_manager")->m_pdoc);
   }

   sp(::filemanager::document) pane_tab_view::get_tabbed_filemanager_document()
   {
      return  (get_view_creator()->get("tabbed_file_manager")->m_pdoc);
   }

   void pane_tab_view::_001OnTabClose(int32_t iTab)
   {

      ::user::tab::_001OnTabClose(iTab);

      if(GetParentFrame()->ContinueModal(0) && get_filemanager_document() != NULL
         && get_filemanager_document()->get_filemanager_data()->m_pdocumentSave != NULL)
      {
         GetParentFrame()->EndModalLoop("yes");
      }

   }


} // namespace userex



