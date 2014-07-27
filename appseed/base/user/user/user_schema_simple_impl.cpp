#include "framework.h"


namespace user
{


   simple_schema::simple_schema()
   {

      m_etranslucency      = TranslucencyUndefined;

   }


   simple_schema::~simple_schema()
   {

   }


   bool simple_schema::set_color(e_color ecolor,COLORREF cr)
   {

      m_mapColor[ecolor] = cr;

      return true;

   }


   bool simple_schema::get_color(COLORREF & cr, e_color ecolor)
   {

      return m_mapColor.Lookup(ecolor,cr);

   }

   bool simple_schema::get_font(::draw2d::font_sp & font)
   {

      if(m_pfont.is_null())
         return false;

      font = m_pfont;

      return true;

   }


   bool simple_schema::get_translucency(ETranslucency & etranslucency)
   {

      if(m_etranslucency == TranslucencyUndefined)
         return false;

      etranslucency = m_etranslucency;

      return true;

   }


} // namespace user











