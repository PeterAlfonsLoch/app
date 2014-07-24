#include "framework.h"


namespace user
{


   schema::schema()
   {

   }

   schema::~schema()
   {

   }


   COLORREF schema::get_background_color()
   {

      return ARGB(255,255,255,255);

   }

   COLORREF schema::get_color()
   {

      return ARGB(255,0,0,0);

   }

   ::draw2d::font_sp schema::get_font()
   {

      return NULL;

   }

   ::user::ETranslucency schema::_001GetTranslucency()
   {

      return ::user::TranslucencyNone;

   }


} // namespace user





