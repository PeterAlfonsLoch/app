#pragma once


namespace install
{

   class CLASS_DECL_AXIS canvas :
      virtual public ::object
   {
   public:

      int32_t      m_iMode;
      int32_t      m_iModeCount;

      canvas(sp(::axis::application) papp);
      ~canvas();

      void on_paint(::draw2d::graphics * pgraphics, const RECT & rect);


      int32_t increment_mode();


   };


} // namespace install





