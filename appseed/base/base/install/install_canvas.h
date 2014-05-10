#pragma once


namespace install
{

   class CLASS_DECL_BASE canvas :
      virtual public ::object
   {
   public:

      int32_t      m_iMode;
      int32_t      m_iModeCount;

      canvas(sp(::base::application) papp);
      ~canvas();

      void on_paint(::draw2d::graphics * pgraphics, LPCRECT lpcrect);


      int32_t increment_mode();


   };


} // namespace install





