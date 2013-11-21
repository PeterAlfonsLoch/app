#pragma once


namespace spa_install
{

   class CLASS_DECL_BOOT canvas :
      virtual public ::object
   {
   public:

      int32_t      m_iMode;
      int32_t      m_iModeCount;

      canvas(sp(base_application) papp);
      ~canvas();

      void on_paint(::draw2d::graphics * pgraphics, LPCRECT lpcrect);


      int32_t increment_mode();


   };


} // namespace spa_install





