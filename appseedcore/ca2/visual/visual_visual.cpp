#include "StdAfx.h"

namespace visual
{

   visual::visual(::ca::graphics * pdc)
   {
      m_pdc = pdc;
   }

   visual::~visual(void)
   {
   }

   void visual::Polygon(const point_array & pointa)
   {
      m_pdc->Polygon(pointa.get_data(), pointa.get_size());
   }

} // visual