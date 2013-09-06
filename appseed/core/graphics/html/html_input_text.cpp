#include "framework.h"


namespace html
{

   namespace impl
   {

      input_text::input_text(data * pdata)
      {
         m_iFont = -1;
         m_pedit = new ::user::edit_plain_text(pdata->get_app());
         m_pedit->m_ulFlags &= ~element::flag_auto_delete;
         m_pedit->m_bMultiLine      = false;
      }

      input_text::~input_text()
      {
         try
         {
            if(m_pedit->IsWindow())
            {
               m_pedit->DestroyWindow();
            }
         }
         catch(...)
         {
         }
         try
         {
            delete m_pedit;
         }
         catch(...)
         {
         }
      }

      void input_text::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {
         elemental::implement_phase1(pdata, pelemental);
         if(!m_pedit->IsWindow())
         {
            m_pedit->oprop("parent_lock_data") = (::data *) pdata;
            m_pedit->create(pdata->m_pguie, 100);
            pdata->on_create_interaction(m_pedit);
            m_pedit->m_bPassword = pelemental->m_propertyset["type"].compare_value_ci("password") == 0;
            m_pedit->m_strName = pelemental->m_pbase->get_tag()->get_attr_value("name");
            m_pedit->m_id = pelemental->m_pbase->get_tag()->get_attr_value("id");
            m_pedit->m_pimpl->m_id = m_pedit->m_id;
            m_pedit->_001SetText(pelemental->m_pbase->get_tag()->get_attr_value("value"));
            m_pedit->SetFont(pdata->get_font(pelemental)->m_font);
         }
         pdata->m_focusptra.add_unique(m_pedit);
         m_cxMax = 200;
         m_cxMin = 200;
      }

      void input_text::layout_phase3(data * pdata)
      {
         elemental::layout_phase3(pdata);
         point pointBound = get_bound_point();
         m_box.set_cxy(200, 23);
         m_box.offset_y(pdata->m_layoutstate.m_cy);
         pdata->m_layoutstate.m_y    = get_y();
         pdata->m_layoutstate.m_cy   = get_cy();
         pdata->m_layoutstate.m_x    = pointBound.x;
         pdata->m_layoutstate.m_cx   = get_cx();
         pdata->m_layoutstate.m_bLastBlockX = true;
         pdata->m_layoutstate.m_bLastBlockY = true;
         m_pedit->SetWindowPos(0, (int32_t) m_box.left, (int32_t) m_box.top, (int32_t) m_box.get_cx(), (int32_t) m_box.get_cy(), SWP_NOREDRAW);
      }

      void input_text::_001OnDraw(data * pdata)
      {
         rect rectWindow;
         m_pedit->GetWindowRect(rectWindow);
         m_pedit->get_wnd()->ScreenToClient(rectWindow);
         ::point ptPreviousViewportOrg = pdata->m_pdc->GetViewportOrg();
         pdata->m_pdc->SetViewportOrg(rectWindow.top_left());
         m_pedit->_001OnDraw(pdata->m_pdc);
         pdata->m_pdc->SetViewportOrg(ptPreviousViewportOrg);
      }

      void input_text::on_change_layout(data * pdata)
      {
         UNREFERENCED_PARAMETER(pdata);
         m_pedit->SetWindowPos(0, (int32_t) m_box.left, (int32_t) m_box.top, (int32_t) m_box.get_cx(), (int32_t) m_box.get_cy(), SWP_NOREDRAW);
      }

   }

} // namespace html

