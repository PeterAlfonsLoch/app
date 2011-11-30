#include "StdAfx.h"

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
         int i = m_pviewdata->m_iExtendOnParent;
         ::user::interaction* pguie = m_pviewdata->m_pwnd;
         ::user::interaction* pguieNext = m_pviewdata->m_pwnd;
         for(; i > 0; i--)
         {
            pguieNext = pguie->GetParent();
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
         user::LPWndArray wnda;
         while(true)
         {
            wnda.add(pguie);
            pguieNext = pguie->GetParent();
            if(pguieNext == NULL || dynamic_cast < ::ca::window * > (pguie->m_pimpl) != NULL)
               break;
            pguie = pguieNext;
         }
//         int i = max(0, wnda.get_size() + m_pviewdata->m_iExtendOnParent);
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
      }
   }

   void pane_tab_view::on_new_view_creator_data(::user::view_creator_data * pcreatordata)
   {

      int iTab = get_tab_by_id(pcreatordata->m_id);

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
      for(int iTab = 0; iTab < panea.get_count(); iTab++)
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
      // if id == registered_pane_from_library[i] => { alloc from library }
/*      if(pcreatordata->m_id == "pane_view_audio_control")
      {
         ::ca::create_context_sp cc(get_app());
         cc->m_puiParent = this;
         mixeruserbase::document * pdoc = dynamic_cast < mixeruserbase::document * > (Bergedge.get_mixeruserbase_central().get_document_template()->open_document_file(cc));
         if(pdoc != NULL)
         {
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;
                     pframe->m_bblur_Background = true;
                  }
               }
            }
         }
      }*/
      if(pcreatordata->m_id == "file_manager")
      {
         ::filemanager::document * pdoc = Application.GetStdFileManagerTemplate()->OpenChild(&Application, true, true, pcreatordata->m_pholder);
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

   filemanager::document * pane_tab_view::get_filemanager_document()
   {
      return get_typed_document < filemanager::document > ();
   }


   void pane_tab_view::_001OnTabClose(int iTab)
   {
      UNREFERENCED_PARAMETER(iTab);
      if(GetParentFrame()->ContinueModal(0) && get_filemanager_document() != NULL
      && get_filemanager_document()->get_filemanager_data()->m_pdocumentSave != NULL)
      {
         GetParentFrame()->EndModalLoop("yes");
      }

   }

} // namespace userex

