#include "StdAfx.h"


namespace paint
{

namespace impl
{
   input_text::input_text(document * pdoc)
   {
      m_iFont = -1;
      m_pedit = new ::user::edit_plain_text(pdoc->get_app());
   }
   input_text::~input_text()
   {
      delete m_pedit;
   }

   void input_text::implement(document * pdoc, ::paint::elemental * pelemental)
   {
      //string strTag = m_propertyset[PropertyTag]->get_value().m_str;
      //if(strTag == "paint" || strTag == "body" || strTag == "head")
      if(!m_pedit->IsWindow())
      {
         m_pedit->create(pdoc->m_pwnd,  100);
      }
      elemental::implement(pdoc, pelemental);
      m_pedit->m_strName = pelemental->m_pnode->attr("name");
      
//      ::ca::graphics * pdc = pdoc->m_pdc;
  //    pdc->SelectObject(pdoc->get_font(m_pelemental)->m_font);
      m_size.cx = 200;
      m_size.cy = 23;
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