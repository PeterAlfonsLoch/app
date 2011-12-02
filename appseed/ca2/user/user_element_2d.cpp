#include "StdAfx.h"

namespace user
{

   void element_2d::_001OnDraw(::user::elemental * pview, ::ax::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pdc);
   }

   void element_2d::_001OnLButtonDown(::user::elemental * pview, gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pobj);
   }

   void element_2d::_001OnLButtonUp(::user::elemental * pview, gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pobj);
   }

   void element_2d::_001OnMouseMove(::user::elemental * pview, gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pobj);
   }

   bool element_2d::hit_test(int x, int y)
   {
      return x >= m_pt.x && x <= m_pt.x + m_size.cx &&
      y >= m_pt.y && y <= m_pt.y + m_size.cy;
   }

   void element_2d::_001OnCalcLayout(::ax::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }

   ::ax::application * element_2d::get_app()
   {
      return NULL;
   }

} // namespace user