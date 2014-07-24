#pragma once


namespace user
{


   class CLASS_DECL_BASE schema:
      virtual public ::object
   {
   public:


      schema();
      virtual ~schema();


      virtual COLORREF              get_background_color();
      virtual COLORREF              get_color();
      virtual ::draw2d::font_sp     get_font();
      virtual ETranslucency         _001GetTranslucency();

   };




} // namespace user




