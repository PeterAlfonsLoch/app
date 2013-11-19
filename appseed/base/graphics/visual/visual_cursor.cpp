#include "framework.h"

namespace visual
{

   cursor::cursor(sp(base_application) papp) :
      element(papp),
      m_dib(allocer())
      //,m_dibWork(allocer())
   {
   }


   bool cursor::to(::draw2d::graphics * pgraphics, int32_t x, int32_t y)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      return pgraphics->BitBlt(x - m_ptHotspot.x, y - m_ptHotspot.y, m_dib->cx, m_dib->cy, m_dib->get_graphics(), 0, 0, SRCCOPY);

   }

   bool cursor::to(::draw2d::graphics * pgraphics, point pt)
   {

      return to(pgraphics, pt.x, pt.y); 

   }


} // namespace visual