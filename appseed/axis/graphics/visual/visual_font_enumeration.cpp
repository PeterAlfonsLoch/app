//#include "framework.h"


namespace visual
{


   font_enumeration::font_enumeration(::aura::application * papp) :
      object(papp)
   {

      defer_create_mutex();

   }


   font_enumeration::~font_enumeration()
   {

   }




   void font_enumeration::update()
   {

      synch_lock sl(m_pmutex);

      ::draw2d::graphics_sp g(allocer());

      g->CreateCompatibleDC(NULL);

      g->enum_fonts(m_straPath, m_stra, m_csa);

   }


} // namespace visual





