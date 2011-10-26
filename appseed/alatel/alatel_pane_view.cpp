#include "StdAfx.h"


namespace alatel
{


   pane_view::pane_view(::ca::application * papp) :
      ca(papp),
      user::tab(papp),
      ::userbase::view(papp),
      userbase::tab_view(papp),
      userex::pane_tab_view(papp),
      user::place_holder_container(papp)
   {

      m_pframePopup        = NULL;
      m_etranslucency      = TranslucencyPresent;
   
   }

   pane_view::~pane_view()
   {
   }


#ifdef _DEBUG
   void pane_view::assert_valid() const
   {
	   ::userex::pane_tab_view::assert_valid();
   }

   void pane_view::dump(dump_context& dc) const
   {
	   ::userex::pane_tab_view::dump(dc);
   }
#endif //_DEBUG

   void pane_view::_001OnCreate(gen::signal_object * pobj) 
   {
//      SCAST_PTR(user::win::message::create, pcreate, pobj)

      if(pobj->previous())
         return;

      add_tab("by weekday", pane_view_by_weekday);
      add_tab("Alarm Preview", pane_view_alarm_test);

      set_cur_tab_by_id(pane_view_by_weekday);

   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      switch(pcreatordata->m_id)
      {
      case pane_view_by_weekday:
         {
            ::alatel::document * pdoc = dynamic_cast < ::alatel::document * > (Application.m_ptemplateAlatelByWeekday->open_document_file(NULL, true, pcreatordata->m_pholder));
            if(pdoc != NULL)
            {
               ::alatel::week_view * pview = dynamic_cast < alatel::week_view * > (pdoc->get_view());
               if(pview != NULL)
               {
                  simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;
                  }
               }
               pview->create_views();
            }
         }
         break;

      case pane_view_alarm_test:
         {
            ::alatel::document * pdoc = dynamic_cast < ::alatel::document * > (Application.m_ptemplateAlatel->open_document_file(NULL, true, pcreatordata->m_pholder));
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
                  }
               }
            }

            ::ca::create_context_sp cc(&Application.creation(), NULL, true, NULL);

            cc->m_bOuterPopupAlertLike = true;

            pdoc = dynamic_cast < ::alatel::document * > (Application.m_ptemplateAlatel->open_document_file(cc));

            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  m_pframePopup = dynamic_cast < alatel::frame * > (pview->GetParentFrame());
                  if(m_pframePopup != NULL)
                  {
                     m_pframePopup->alatel_fullscreen();

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


   void pane_view::install_message_handling(user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &::alatel::pane_view::_001OnCreate);
   }

   void pane_view::on_show_view() 
   {

      ::userex::pane_tab_view::on_show_view();
      if(m_pviewdata->m_id == pane_view_alarm_test)
      {
         if(m_pframePopup != NULL)
         {
            m_pframePopup->ShowWindow(SW_SHOW);
         }
      }
      else
      {
         if(m_pframePopup != NULL)
         {
            m_pframePopup->ShowWindow(SW_HIDE);
         }
      }

   }

} // namespace alatel


