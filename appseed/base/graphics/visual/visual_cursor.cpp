#include "framework.h"

namespace visual
{

   cursor::cursor(sp(::base::application) papp) :
      element(papp),
      m_dib(allocer())
      //,m_dibWork(allocer())
   {
   }


   bool cursor::to(::draw2d::graphics * pgraphics, point pt)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      return pgraphics->BitBlt(pt - m_szHotspotOffset, m_dib->m_size, m_dib->get_graphics());

   }


} // namespace visual