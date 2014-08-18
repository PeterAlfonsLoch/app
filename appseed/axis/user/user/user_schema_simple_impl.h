#pragma once


namespace user
{


   class CLASS_DECL_AXIS schema_simple_impl:
      virtual public ::user::schema
   {
   public:


      map < e_color,e_color,COLORREF,COLORREF >       m_mapColor;
      ::draw2d::font_sp                               m_pfont;
      ETranslucency                                   m_etranslucency;


      schema_simple_impl();
      virtual ~schema_simple_impl();


      virtual bool get_color(COLORREF & cr, e_color ecolor);
      virtual bool get_font(::draw2d::font_sp & font);
      virtual bool get_translucency(ETranslucency & etranslucency);


      virtual bool set_color(e_color ecolor, COLORREF cr);

   };


} // namespace user





