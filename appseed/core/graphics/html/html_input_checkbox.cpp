#include "framework.h"


namespace html
{

   namespace impl
   {

      input_checkbox::input_checkbox(data * pdata)
      {
         m_pcheckbox = canew( ::user::check_box(pdata->get_app()));
      }

      input_checkbox::~input_checkbox()
      {
      }

      void input_checkbox::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {
         if(!m_pcheckbox->IsWindow())
         {
            m_pcheckbox->create(pdata->m_pguie, 100);
            pdata->on_create_interaction(m_pcheckbox);
             bool bCheck = pelemental->m_pbase->get_tag()->get_attr("checked") != NULL;
             if(bCheck)
             {
                m_pcheckbox->_001SetCheck(check::checked, ::action::source::add(::action::source_data, ::action::source_load));
             }
             else
             {
                m_pcheckbox->_001SetCheck(check::unchecked, ::action::source::add(::action::source_data, ::action::source_load));
             }
         }
         elemental::implement_phase1(pdata, pelemental);

         m_pcheckbox->m_id = pelemental->m_pbase->get_tag()->get_attr_value("id");
         m_pcheckbox->m_strName = pelemental->m_pbase->get_tag()->get_attr_value("name");
         m_pcheckbox->m_id = pelemental->m_pbase->get_tag()->get_attr_value("id");
         if(pdata->m_pform != NULL && pdata->m_pform->m_pcallback != NULL)
         {
            ::user::control_event ev;
            ev.m_puie = m_pcheckbox;
            ev.m_actioncontext = ::action::source::add(::action::source_data, ::action::source_load);
            ev.m_eevent = ::user::event_initialize_control;
            ev.m_uiEvent = 0;
            pdata->m_pform->m_pcallback->BaseOnControlEvent(pdata->m_pform, &ev);
         }
      }

      void input_checkbox::layout_phase1(data * pdata)
      {

         m_box.set_cxy(23, 23);

      }


      void input_checkbox::layout_phase3(data * pdata)
      {

         elemental::layout_phase3(pdata);
         
         m_pcheckbox->SetWindowPos(0, (int32_t) m_box.left, (int32_t) m_box.top, (int32_t) m_box.get_cx(), (int32_t) m_box.get_cy(), SWP_NOREDRAW);

      }


      void input_checkbox::_001OnDraw(data * pdata)
      {
         //rect rectWindow;
         //m_pcheckbox->GetWindowRect(rectWindow);
         ::point ptPreviousViewportOrg = pdata->m_pdc->GetViewportOrg();
         pdata->m_pdc->OffsetViewportOrg((int32_t) m_box.left, (int32_t) m_box.top);
         m_pcheckbox->_001OnDraw(pdata->m_pdc);
         pdata->m_pdc->SetViewportOrg(ptPreviousViewportOrg);
      }

      void input_checkbox::on_change_layout(data * pdata)
      {
         UNREFERENCED_PARAMETER(pdata);
         m_pcheckbox->SetWindowPos(0, (int32_t) m_box.left, (int32_t) m_box.top, (int32_t) m_box.get_cx(), (int32_t) m_box.get_cy(), SWP_NOREDRAW);
      }

   }

}
