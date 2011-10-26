#include "StdAfx.h"


namespace paint
{

namespace impl
{
   input_button::input_button(document * pdoc)
   {
      m_iFont = -1;
      m_pbutton = new ::user::button(pdoc->get_app());
   }

   input_button::~input_button()
   {
      delete m_pbutton;
   }

   void input_button::implement(document * pdoc, ::paint::elemental * pelemental)
   {
      //string strTag = m_propertyset[PropertyTag]->get_value().m_str;
      //if(strTag == "paint" || strTag == "body" || strTag == "head")
      if(!m_pbutton->IsWindow())
      {
         m_pbutton->create(pdoc->m_pwnd, 100);
      }
      elemental::implement(pdoc, pelemental);
      m_pbutton->_001SetButtonText(pelemental->m_pnode->attr("value"));
      m_pbutton->m_id = pelemental->m_pnode->attr("name");
      
//      ::ca::graphics * pdc = pdoc->m_pdc;
  //    pdc->SelectObject(pdoc->get_font(m_pelemental)->m_font);
      m_size.cx = 200;
      m_size.cy = 31;
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
      UNREFERENCED_PARAMETER(pdoc);
      m_pbutton->SetWindowPos(NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_SHOWWINDOW);
   }

}



}