#include "framework.h"


namespace user
{


   simple_schema::simple_schema()
   {

      m_crBackground       = ARGB(255,255,255,255);
      m_crText             = ARGB(255,0,0,0);
      m_etranslucency      = TranslucencyNone;

   }


   simple_schema::~simple_schema()
   {

   }


   COLORREF simple_schema::get_background_color()
   {

      return m_crBackground;

   }

   COLORREF simple_schema::get_color()
   {

      return m_crText;

   }

   ::draw2d::font_sp simple_schema::get_font()
   {

      return m_pfont;

   }


   ::user::ETranslucency simple_schema::_001GetTranslucency()
   {

      return m_etranslucency;

   }


} // namespace user











