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

   void input_button::implement(document * pdoc, ::html::elemental * pelemental)
   {
      //string strTag = m_propertyset[PropertyTag]->GetValue().m_str;
      //if(strTag == "html" || strTag == "body" || strTag == "head")
      if(m_pbutton->m_pwnd == NULL)
      {
         m_pbutton->Create(pdoc->m_pwnd, pdoc->m_pguie, 100);
      }
      elemental::implement(pdoc, pelemental);
      m_pbutton->_001SetButtonText(pelemental->m_pnode->GetAttrValue("value"));
      m_pbutton->m_pcontrol->m_strId = pelemental->m_pnode->GetAttrValue("name");
      
//      CDC * pdc = pdoc->m_pdc;
  //    pdc->SelectObject(&pdoc->get_font(m_pelemental)->m_font);
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
      m_pbutton->SetWindowPos(NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_SHOWWINDOW);
   }

}



}