#include "framework.h"


namespace user
{


   schema::schema()
   {

   }

   schema::~schema()
   {

   }


   bool schema::get_background_color(COLORREF & cr)
   {

      if(m_puserschema != NULL)
      {

         return m_puserschema->get_background_color(cr);

      }

      if(get_parent_user_schema() != NULL)
      {

         return get_parent_user_schema()->get_background_color(cr);

      }

      return false;

   }

   bool schema::get_color(COLORREF & cr)
   {

      if(m_puserschema != NULL)
      {

         return m_puserschema->get_color(cr);

      }

      if(get_parent_user_schema() != NULL)
      {

         return get_parent_user_schema()->get_color(cr);

      }

      return false;

   }

   bool schema::get_font(::draw2d::font_sp & spfont)
   {

      if(m_puserschema != NULL)
      {

         return m_puserschema->get_font(spfont);

      }

      if(get_parent_user_schema() != NULL)
      {

         return get_parent_user_schema()->get_font(spfont);

      }

      return false;

   }

   bool schema::_001GetTranslucency(::user::ETranslucency & etranslucency)
   {

      if(m_puserschema != NULL)
      {

         return m_puserschema->_001GetTranslucency(etranslucency);

      }

      if(get_parent_user_schema() != NULL)
      {

         return get_parent_user_schema()->_001GetTranslucency(etranslucency);

      }

      return false;

   }


   bool schema::_001IsTranslucent()
   {

      ETranslucency etranslucency;

      if(_001GetTranslucency(etranslucency))
      {

         return etranslucency == TranslucencyPresent || etranslucency == TranslucencyTotal;

      }

      return false;

   }


   bool schema::_001IsBackgroundBypass()
   {

      ETranslucency etranslucency;

      if(_001GetTranslucency(etranslucency))
      {

         return etranslucency == TranslucencyTotal;

      }

      return false;

   }


   bool schema::_001HasTranslucency()
   {

      ETranslucency etranslucency;

      if(_001GetTranslucency(etranslucency))
      {

         return etranslucency == TranslucencyPresent || etranslucency == TranslucencyTotal;

      }

      return false;

   }


   bool schema::_001IsTransparent()
   {

      ETranslucency etranslucency;

      if(_001GetTranslucency(etranslucency))
      {

         return etranslucency == TranslucencyTotal;

      }

      return false;

   }


   ::user::schema * schema::get_user_schema()
   {

      if(m_puserschema != NULL)
      {

         return m_puserschema;

      }

      return get_parent_user_schema();

   }


   ::user::schema * schema::get_parent_user_schema()
   {

      return NULL;

   }




} // namespace user





