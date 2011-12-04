#include "StdAfx.h"


namespace html
{

   namespace impl
   {

      input_text::input_text(data * pdata)
      {
         m_iFont = -1;
         m_pedit = new ::user::edit_plain_text(pdata->get_app());
         m_pedit->m_ulFlags &= ~::ca::ca::flag_auto_delete;
         m_pedit->m_bMultiLine      = false;
      }

      input_text::~input_text()
      {
         delete m_pedit;
      }

      void input_text::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {
         elemental::implement_phase1(pdata, pelemental);
         if(!m_pedit->IsWindow())
         {
            m_pedit->oprop("parent_lock_data") = (::ca::data *) pdata;
            m_pedit->create(pdata->m_pguie, 100);
            pdata->on_create_interaction(m_pedit);
            m_pedit->m_bPassword = pelemental->m_propertyset["type"].compare_value_ci("password") == 0;
            m_pedit->m_strName = pelemental->m_pbase->tag()->get_attr_value("name");
            m_pedit->m_id = pelemental->m_pbase->tag()->get_attr_value("id");
            m_pedit->_001SetText(pelemental->m_pbase->tag()->get_attr_value("value"));
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
         m_size.cx = 200;
         m_size.cy = 23;
         pdata->m_layoutstate.m_cy   = get_cy();
         pdata->m_layoutstate.m_cx   = get_cx();
         m_pedit->SetWindowPos(NULL, pdata->m_layoutstate.m_x, pdata->m_layoutstate.m_y, m_size.cx, m_size.cy, SWP_NOREDRAW);
      }

      void input_text::_001OnDraw(data * pdata)
      {
         rect rectWindow;
         m_pedit->GetWindowRect(rectWindow);
         m_pedit->get_wnd()->ScreenToClient(rectWindow);
         point ptPreviousViewportOrg = pdata->m_pdc->GetViewportOrg();
         pdata->m_pdc->SetViewportOrg(rectWindow.top_left());
         m_pedit->_001OnDraw(pdata->m_pdc);
         pdata->m_pdc->SetViewportOrg(ptPreviousViewportOrg);
      }

      void input_text::on_change_layout(data * pdata)
      {
         UNREFERENCED_PARAMETER(pdata);
         m_pedit->SetWindowPos(NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_NOREDRAW);
      }

   }

} // namespace html

