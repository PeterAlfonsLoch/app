#include "StdAfx.h"


namespace paint
{

namespace impl
{
   text::text()
   {
      m_iFont = -1;
   }

   void text::implement(document * pdoc, ::paint::elemental * pelemental)
   {
      //string strTag = m_propertyset[PropertyTag]->get_value().m_str;
      //if(strTag == "paint" || strTag == "body" || strTag == "head")
      elemental::implement(pdoc, pelemental);
      ::ca::graphics * pdc = pdoc->m_pdc;
      pdc->SelectObject(pdoc->get_font(m_pelemental)->m_font);
      string str = m_pelemental->m_propertyset[PropertyBody];
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
      ::ca::graphics * pdc = pdoc->m_pdc;
      pdc->SelectObject(pdoc->get_font(m_pelemental)->m_font);
      int x = get_x();
      int y = get_y();
      string str = m_pelemental->m_propertyset[PropertyBody];
      pdc->TextOut(
         x,
         y,
         str);
   }
}



}