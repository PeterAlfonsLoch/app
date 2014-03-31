#include "framework.h"


namespace html
{


   namespace impl
   {


      input_button::input_button(data * pdata)
      {
         m_iFont = -1;
         m_pbutton = new ::user::button(pdata->get_app());
         m_pbutton->m_ulFlags &= ~element::flag_auto_delete;
      }

      input_button::~input_button()
      {
         delete m_pbutton;
      }

      void input_button::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {

         m_bHasChar = true;

         if(!m_pbutton->IsWindow())
         {
            m_pbutton->create(pdata->m_pui, 100);
            pdata->on_create_interaction(m_pbutton);
         }
         elemental::implement_phase1(pdata, pelemental);
         m_pbutton->_001SetButtonText(pelemental->m_pbase->get_tag()->get_attr_value("value"));
         m_pbutton->m_id = pelemental->m_pbase->get_tag()->get_attr_value("id");
         if(m_pbutton->m_id.is_empty())
         {
            m_pbutton->m_id = pelemental->m_pbase->get_tag()->get_attr_value("name");
         }
         m_pbutton->m_pimpl->m_id = m_pbutton->m_id;
         m_cxMax = 200;
         m_cxMin = 200;
      }

      void input_button::layout_phase1(data * pdata)
      {

         m_box.set_cxy(200.f, 23.f);

      }


      void input_button::layout_phase3(data * pdata)
      {

         elemental::layout_phase3(pdata);

         m_pbutton->SetWindowPos(0, (int32_t) m_box.left, (int32_t) m_box.top, (int32_t) m_box.get_cx(), (int32_t) m_box.get_cy(), SWP_NOREDRAW);

      }


      void input_button::_001OnDraw(data * pdata)
      {
         //rect rectWindow;
         //m_pbutton->GetWindowRect(rectWindow);
         //m_pbutton->get_wnd()->ScreenToClient(rectWindow);
         ::point ptPreviousViewportOrg = pdata->m_pdc->GetViewportOrg();
         pdata->m_pdc->OffsetViewportOrg((int32_t) m_box.left, (int32_t) m_box.top);
         m_pbutton->_001OnDraw(pdata->m_pdc);
         pdata->m_pdc->SetViewportOrg(ptPreviousViewportOrg);
      }

      void input_button::on_change_layout(data * pdata)
      {
         
         UNREFERENCED_PARAMETER(pdata);

         m_pbutton->SetWindowPos(0, (int32_t) m_box.left, (int32_t) m_box.top, (int32_t) m_box.get_cx(), (int32_t) m_box.get_cy(), SWP_NOREDRAW);

      }


   } // namespace impl


} // namespace html





