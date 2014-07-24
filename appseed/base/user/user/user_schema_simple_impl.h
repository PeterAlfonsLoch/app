#pragma once


namespace user
{


   class CLASS_DECL_BASE simple_schema:
      virtual public ::user::schema
   {
   public:


      COLORREF                      m_crBackground;
      COLORREF                      m_crText;
      ::draw2d::font_sp             m_pfont;
      ETranslucency                 m_etranslucency;


      simple_schema();
      virtual ~simple_schema();


      virtual COLORREF              get_background_color();
      virtual COLORREF              get_color();
      virtual ::draw2d::font_sp     get_font();
      virtual ETranslucency         _001GetTranslucency();


   };


} // namespace user





