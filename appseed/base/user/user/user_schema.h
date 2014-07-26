#pragma once


namespace user
{


   class CLASS_DECL_BASE schema
   {
   public:

      
      ::user::schema *        m_puserschema;


      schema();
      virtual ~schema();

      virtual ::user::schema * get_user_schema();
      virtual ::user::schema * get_parent_user_schema();

      virtual bool get_background_color(COLORREF & cr);
      virtual bool get_color(COLORREF & cr);
      virtual bool get_font(::draw2d::font_sp & spfont);
      virtual bool _001GetTranslucency(ETranslucency & etranslucency);

      virtual bool _001IsBackgroundBypass();
      virtual bool _001IsTransparent();
      virtual bool _001IsTranslucent();
      virtual bool _001HasTranslucency();


   };




} // namespace user




