#include "StdAfx.h"


namespace html
{

namespace impl
{
   input_checkbox::input_checkbox()
   {
      m_pcheckbox = new Ex1CheckBox();
   }

   input_checkbox::~input_checkbox()
   {
      delete m_pcheckbox;
   }

   void input_checkbox::implement_phase1(document * pdoc, ::html::elemental * pelemental)
   {
      if(m_pcheckbox->m_pwnd == NULL)
      {
         m_pcheckbox->Create(pdoc->m_pwnd, pdoc->m_pguie, 100);
      }
      elemental::implement_phase1(pdoc, pelemental);
      m_pcheckbox->m_pcontrol->m_strId = pelemental->m_pbase->tag()->get_attr_value("name");
   }

   void input_checkbox::layout_phase3(document * pdoc)
   {
      elemental::layout_phase3(pdoc);
      point pointBound = get_bound_point();
      m_size.cx = 200;
      m_size.cy = 23;
      m_pt.y += pdoc->m_layoutstate.m_cy;
      pdoc->m_layoutstate.m_y    = get_y();
      pdoc->m_layoutstate.m_cy   = 23;
      pdoc->m_layoutstate.m_x    += pdoc->m_layoutstate.m_cx;
      pdoc->m_layoutstate.m_cx   = 23;
      m_pcheckbox->SetWindowPos(NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_SHOWWINDOW);
   }

   void input_checkbox::_001OnDraw(document * pdoc)
   {
//      pdoc->m_pdc->OffsetViewportOrg(m_pt.x, m_pt.y);
      m_pcheckbox->_001OnDraw(pdoc->m_pdc);
//      pdoc->m_pdc->OffsetViewportOrg(-m_pt.x, -m_pt.y);
   }

   void input_checkbox::on_change_layout(document * pdoc)
   {
      m_pcheckbox->SetWindowPos(NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_SHOWWINDOW);
   }

}



}