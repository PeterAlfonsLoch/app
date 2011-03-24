#include "StdAfx.h"


namespace html
{

namespace impl
{
   text::text()
   {
      m_iFont = -1;
   }

   void text::implement(document * pdoc, ::html::elemental * pelemental)
   {
      //string strTag = m_propertyset[PropertyTag]->GetValue().m_str;
      //if(strTag == "html" || strTag == "body" || strTag == "head")
      elemental::implement(pdoc, pelemental);
      CDC * pdc = pdoc->m_pdc;
      pdc->SelectObject(&pdoc->get_font(m_pelemental)->m_font);
      string str = m_pelemental->m_propertyset[PropertyBody]->GetValue().m_str;
      size sizeText = pdc->GetTextExtent(str);
      m_size.cx = min(sizeText.cx, pelemental->m_pparent->m_pimpl->get_cx());
      if(pelemental->m_pparent->m_pimpl->get_cx() == 0)
      {
         m_size.cy = sizeText.cy;
      }
      else
      {
         m_size.cy = sizeText.cy * ((sizeText.cx / pelemental->m_pparent->m_pimpl->get_cx()) + 1);
      }
   }
   void text::_001OnDraw(document * pdoc)
   {
      CDC * pdc = pdoc->m_pdc;
      pdc->SelectObject(&pdoc->get_font(m_pelemental)->m_font);
      int x = get_x();
      int y = get_y();
      string str = m_pelemental->m_propertyset[PropertyBody]->GetValue().m_str;
      pdc->TextOut(
         x,
         y,
         str);
   }
}



}