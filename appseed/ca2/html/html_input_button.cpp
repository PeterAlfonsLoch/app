#include "StdAfx.h"


namespace html
{

   namespace impl
   {

      input_button::input_button(data * pdata)
      {
         m_iFont = -1;
         m_pbutton = new ::user::button(pdata->get_app());
         m_pbutton->m_ulFlags &= ~::ca::ca::flag_auto_delete;
      }

      input_button::~input_button()
      {
         delete m_pbutton;
      }

      void input_button::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {
         if(!m_pbutton->IsWindow())
         {
            m_pbutton->create(pdata->m_pguie, 100);
            pdata->on_create_interaction(m_pbutton);
         }
         elemental::implement_phase1(pdata, pelemental);
         m_pbutton->_001SetButtonText(pelemental->m_pbase->tag()->get_attr_value("value"));
         m_pbutton->m_id = pelemental->m_pbase->tag()->get_attr_value("id");
         if(m_pbutton->m_id.is_empty())
         {
            m_pbutton->m_id = pelemental->m_pbase->tag()->get_attr_value("name");
         }
         m_pbutton->m_pimpl->m_id = m_pbutton->m_id;
         m_cxMax = 200;
         m_cxMin = 200;
      }

      void input_button::layout_phase3(data * pdata)
      {
         elemental::layout_phase3(pdata);
         point pointBound = get_bound_point();
         m_size.cx = 200;
         m_size.cy = 23;
         if(m_pelemental->m_propertyset["display"] == "block")
         {
            pdata->m_layoutstate.m_y    = get_y() + get_cy();
            pdata->m_layoutstate.m_cy   = 0;
            pdata->m_layoutstate.m_x    = pointBound.x;
            pdata->m_layoutstate.m_cx   = 0;
            pdata->m_layoutstate.m_bLastBlockX = true;
            pdata->m_layoutstate.m_bLastBlockY = true;
         }
         else
         {
            pdata->m_layoutstate.m_y    = get_y();
            pdata->m_layoutstate.m_cy   = get_cy();
            pdata->m_layoutstate.m_x    = get_x();
            pdata->m_layoutstate.m_cx   = get_cx();
            pdata->m_layoutstate.m_bLastBlockX = false;
            pdata->m_layoutstate.m_bLastBlockY = false;
         }
         m_pbutton->SetWindowPos(NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_NOREDRAW);
      }

      void input_button::_001OnDraw(data * pdata)
      {
         rect rectWindow;
         m_pbutton->GetWindowRect(rectWindow);
         m_pbutton->get_wnd()->ScreenToClient(rectWindow);
         point ptPreviousViewportOrg = pdata->m_pdc->GetViewportOrg();
         pdata->m_pdc->SetViewportOrg(rectWindow.top_left());
         m_pbutton->_001OnDraw(pdata->m_pdc);
         pdata->m_pdc->SetViewportOrg(ptPreviousViewportOrg);
      }

      void input_button::on_change_layout(data * pdata)
      {
         UNREFERENCED_PARAMETER(pdata);
         m_pbutton->SetWindowPos(NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_NOREDRAW);
      }

   }

}