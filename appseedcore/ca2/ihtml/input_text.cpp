#include "StdAfx.h"


namespace html
{

namespace impl
{
   input_text::input_text()
   {
      m_iFont = -1;
      m_pedit = new Ex1EditPlainTextInterface();
   }
   input_text::~input_text()
   {
      delete m_pedit;
   }

   void input_text::implement_phase1(document * pdoc, ::html::elemental * pelemental)
   {
      elemental::implement_phase1(pdoc, pelemental);
      if(m_pedit->m_pwnd == NULL)
      {
         m_pedit->Create(pdoc->m_pwnd, pdoc->m_pguie, 100);
         m_pedit->m_bPassword = pelemental->m_propertyset["type"]->GetValue().GetValueString().MakeLower() == "password";
      }
      m_pedit->m_strName = pelemental->m_pbase->tag()->get_attr_value("name");
      m_cxMax = 200;
      m_cxMin = 200;
   }

   void input_text::layout_phase3(document * pdoc)
   {
      elemental::layout_phase3(pdoc);
      point pointBound = get_bound_point();
      m_size.cx = 200;
      m_size.cy = 23;
      m_pt.y += pdoc->m_layoutstate.m_cy;
      pdoc->m_layoutstate.m_y    = get_y() + get_cy();
      pdoc->m_layoutstate.m_cy   = 0;
      pdoc->m_layoutstate.m_x    = pointBound.x;
      pdoc->m_layoutstate.m_cx   = 0;
      m_pedit->SetWindowPos(NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_SHOWWINDOW);
   }

   void input_text::_001OnDraw(document * pdoc)
   {
//      pdoc->m_pdc->OffsetViewportOrg(m_pt.x, m_pt.y);
      m_pedit->_001OnDraw(pdoc->m_pdc);
//      pdoc->m_pdc->OffsetViewportOrg(-m_pt.x, -m_pt.y);
   }

   void input_text::on_change_layout(document * pdoc)
   {
      m_pedit->SetWindowPos(NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_SHOWWINDOW);
   }

}



}