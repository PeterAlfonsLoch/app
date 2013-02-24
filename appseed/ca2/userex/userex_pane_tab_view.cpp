#include "framework.h"


namespace userex
{


   pane_tab_view::pane_tab_view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::user::tab(papp),
      place_holder_container(papp)
   {


      set_view_creator(this);


   }

   pane_tab_view::~pane_tab_view()
   {
   }

   ::user::interaction * pane_tab_view::get_view_uie()
   {
      return ::userbase::tab_view::get_view_uie();
   }

   id pane_tab_view::get_view_id()
   {
      return ::userbase::tab_view::get_view_id();
   }

   void pane_tab_view::GetTabClientRect(LPRECT lprect)
   {
      if(m_pviewdata == NULL || m_pviewdata->m_pwnd == NULL || m_pviewdata->m_iExtendOnParent == 0)
      {
         ::userbase::tab_view::GetTabClientRect(lprect);
      }
      else if(m_pviewdata->m_iExtendOnParent > 0)
      {
         int32_t i = m_pviewdata->m_iExtendOnParent;
         ::user::interaction* pguie = m_pviewdata->m_pwnd;
         ::user::interaction* pguieNext = m_pviewdata->m_pwnd;
         for(; i > 0; i--)
         {
            pguieNext = pguie->get_parent();
            if(pguieNext == NULL || !pguieNext->IsWindow())
               break;
            pguie = pguieNext;
         }
         pguie->GetWindowRect(lprect);
         ScreenToClient(lprect);
      }
      else if(m_pviewdata->m_iExtendOnParent < 0)
      {
         ::user::interaction* pguie = m_pviewdata->m_pwnd;
         ::user::interaction* pguieNext = m_pviewdata->m_pwnd;
         user::interaction_ptr_array wnda;
         while(true)
         {
            wnda.add(pguie);
            pguieNext = pguie->get_parent();
            if(pguieNext == NULL || dynamic_cast < ::ca::window * > (pguie->m_pimpl) != NULL)
               break;
            pguie = pguieNext;
         }
//         int32_t i = max(0, wnda.get_size() + m_pviewdata->m_iExtendOnParent);
         pguie = wnda[wnda.get_size() + m_pviewdata->m_iExtendOnParent];
         pguie->GetWindowRect(lprect);
         ScreenToClient(lprect);
      }
   }


   void pane_tab_view::on_show_view()
   {
      ::userbase::tab_view::on_show_view();
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

      pane * ppane = (pane *) get_data()->m_panea.ptr_at(iTab);

      if(ppane == NULL)
         return;

      ppane->m_pholder = pcreatordata->m_pholder;

      if(ppane->m_pholder == NULL)
         return;

      pcreatordata->m_pviewdata = (void *) ppane;

   }


   bool pane_tab_view::on_hold(::user::interaction * pui, ::user::place_holder * pholder)
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
      return ::userbase::tab_view::ensure(id);
   }


   void pane_tab_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      
      if(pcreatordata->m_id.is_text())
      {
         ::ca::library * plibrary = NULL;
         if(System.m_idmapCreateViewLibrary.Lookup(pcreatordata->m_id, plibrary) && plibrary != NULL)
         {
            plibrary->on_create_view(pcreatordata);
         }
         else if(pcreatordata->m_id == "file_manager"
              || pcreatordata->m_id == "left_file"
              || pcreatordata->m_id == "right_file")
         {

            ::filemanager::data * pfilemanagerdata = new ::filemanager::data(get_app());


            pfilemanagerdata->m_id = pcreatordata->m_id;

            if(oprop("file_manager_toolbar").is_set())
               pfilemanagerdata->m_strToolBar = oprop("file_manager_toolbar");
            else
               pfilemanagerdata->m_strToolBar = "file_manager_toolbar.xml";

            if(oprop("file_manager_toolbar_save").is_set())
               pfilemanagerdata->m_strToolBarSave = oprop("file_manager_toolbar_save");
            else
               pfilemanagerdata->m_strToolBarSave = "file_manager_toolbar_save.xml";

            ::filemanager::document * pdoc = Application.filemanager().std().OpenChild(true, true, pcreatordata->m_pholder, pfilemanagerdata);
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  frame_window * pframe = (frame_window *) pview->GetParentFrame();
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                  }
               }
            }
         }
         else if(pcreatordata->m_id == "tabbed_file_manager")
         {

            ::ca::create_context_sp cc(get_app());
            cc->m_bTransparentBackground     = true;
            cc->m_bMakeVisible               = true;
            cc->m_puiParent                  = pcreatordata->m_pholder;

            ::filemanager::document * pdoc = Application.filemanager().std().open(cc);

            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  frame_window * pframe = (frame_window *) pview->GetParentFrame();
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;
                  }
               }
            }
         }
      }

   }

   filemanager::document * pane_tab_view::get_filemanager_document()
   {
      return dynamic_cast < filemanager::document * > (get_view_creator()->get("file_manager")->m_pdoc);
   }

   filemanager::document * pane_tab_view::get_tabbed_filemanager_document()
   {
      return dynamic_cast < filemanager::document * > (get_view_creator()->get("tabbed_file_manager")->m_pdoc);
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



