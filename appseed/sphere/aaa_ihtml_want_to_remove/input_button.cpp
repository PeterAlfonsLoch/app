#include "StdAfx.h"


namespace html
{

namespace impl
{
   input_button::input_button()
   {
      m_iFont = -1;
      m_pbutton = new Ex1Button();
   }

   input_button::~input_button()
   {
      delete m_pbutton;
   }

   void input_button::implement_phase1(document * pdoc, ::html::elemental * pelemental)
   {
      if(m_pbutton->m_pwnd == NULL)
      {
         m_pbutton->Create(pdoc->m_pwnd, pdoc->m_pguie, 100);
      }
      elemental::implement_phase1(pdoc, pelemental);
      m_pbutton->_001SetButtonText(pelemental->m_pbase->tag()->get_attr_value("value"));
      m_pbutton->m_pcontrol->m_strId = pelemental->m_pbase->tag()->get_attr_value("name");
      m_cxMax = 200;
      m_cxMin = 200;
   }

   void input_button::layout_phase3(document * pdoc)
   {
      elemental::layout_phase3(pdoc);
      point pointBound = get_bound_point();
      m_size.cx = 200;
      m_size.cy = 23;
      m_pt.y += pdoc->m_layoutstate.m_cy;
      pdoc->m_layoutstate.m_y    = get_y();
      pdoc->m_layoutstate.m_cy   = 23;
      pdoc->m_layoutstate.m_x    += pdoc->m_layoutstate.m_cx;
      pdoc->m_layoutstate.m_cx   = 200;
      m_pbutton->SetWindowPos(NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_SHOWWINDOW);
   }

   void input_button::_001OnDraw(document * pdoc)
   {
//      pdoc->m_pdc->OffsetViewportOrg(m_pt.x, m_pt.y);
      m_pbutton->_001OnDraw(pdoc->m_pdc);
//      pdoc->m_pdc->OffsetViewportOrg(-m_pt.x, -m_pt.y);
   }

   void input_button::on_change_layout(document * pdoc)
   {
      m_pbutton->SetWindowPos(NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_SHOWWINDOW);
   }

}



}