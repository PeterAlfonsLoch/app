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

   void input_text::implement(document * pdoc, ::html::elemental * pelemental)
   {
      //string strTag = m_propertyset[PropertyTag]->GetValue().m_str;
      //if(strTag == "html" || strTag == "body" || strTag == "head")
      if(m_pedit->m_pwnd == NULL)
      {
         m_pedit->Create(pdoc->m_pwnd, pdoc->m_pguie, 100);
      }
      elemental::implement(pdoc, pelemental);
      m_pedit->m_strName = pelemental->m_pnode->GetAttrValue("name");
      
//      CDC * pdc = pdoc->m_pdc;
  //    pdc->SelectObject(&pdoc->get_font(m_pelemental)->m_font);
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