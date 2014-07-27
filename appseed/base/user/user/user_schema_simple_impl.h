#pragma once


namespace user
{


   class CLASS_DECL_BASE simple_schema:
      virtual public ::user::schema
   {
   public:


      map < e_color,e_color,COLORREF,COLORREF >       m_mapColor;
      ::draw2d::font_sp                               m_pfont;
      ETranslucency                                   m_etranslucency;


      simple_schema();
      virtual ~simple_schema();


      virtual bool get_color(COLORREF & cr, e_color ecolor);
      virtual bool get_font(::draw2d::font_sp & font);
      virtual bool get_translucency(ETranslucency & etranslucency);


      virtual bool set_color(e_color ecolor, COLORREF cr);

   };


} // namespace user





