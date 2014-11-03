#include "framework.h"
#include "aura/graphics/graphics.h"


namespace visual
{

   cursor::cursor(sp(::aura::application) papp) :
      element(papp),
      m_dib(allocer())
      //,m_dibWork(allocer())
   {

#ifdef WINDOWSEX

      m_hcursor = NULL;

#endif

   }


   bool cursor::to(::draw2d::graphics * pgraphics, point pt)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      return pgraphics->BitBlt(pt - m_szHotspotOffset, m_dib->m_size, m_dib->get_graphics());

   }


#ifdef WINDOWSEX

   HCURSOR cursor::get_HCURSOR()
   {

      if(m_hcursor == NULL)
      {

         m_hcursor = ::CreateAlphaCursor(m_dib,m_szHotspotOffset.cx,m_szHotspotOffset.cy);

      }

      return m_hcursor;

   }

#endif


   void cursor_alloc(::aura::application * papp, cursor * & pdib)
   {

      pdib = new cursor(papp);

   }


   ::draw2d::dib * cursor_get_dib(cursor * pcursor)
   {

      return pcursor->m_dib;

   }


} // namespace visual







