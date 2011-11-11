#include "StdAfx.h"

namespace html
{

namespace impl
{

   void image::_001OnDraw(document * pdoc)
   {
      if(m_pelemental->m_pbase->get_type() == html::base::type_tag)
      {
         pdoc->m_imagea[m_iImage].m_dib.Render(pdoc->m_pdc, 
            get_x(), get_y(),
            get_cx(), get_cy());
      }
   }

   void image::implement_phase1(document * pdoc, ::html::elemental * pelemental)
   {
      elemental::implement_phase1(pdoc, pelemental);
      if(pelemental->m_pbase->get_type() == html::base::type_tag)
      {
         m_iImage = pdoc->get_image_index(pelemental->m_propertyset["src"]->GetValue().GetValueString());
         m_cxMax = pdoc->m_imagea[m_iImage].m_dib.m_size.cx;
         m_cxMin = pdoc->m_imagea[m_iImage].m_dib.m_size.cx;
      }
   }

   void image::layout_phase3(document * pdoc)
   {
      if(m_pelemental->m_pbase->get_type() == html::base::type_tag)
      {
         point pointBound = get_bound_point();
         set_x(pdoc, pointBound.x);
         set_y(pdoc, pdoc->m_layoutstate.m_y + pdoc->m_layoutstate.m_cy);
         set_cxy(pdoc, pdoc->m_imagea[m_iImage].m_dib.m_size.cx,
            pdoc->m_imagea[m_iImage].m_dib.m_size.cy);
         pdoc->m_layoutstate.m_y    = get_y() + get_cy();
         pdoc->m_layoutstate.m_cy   = 0;
         pdoc->m_layoutstate.m_x    = pointBound.x;
         pdoc->m_layoutstate.m_cx   = 0;
      }
   }

} // namespace impl

} // namespace html_impl