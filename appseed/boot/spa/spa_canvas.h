#pragma once


namespace spa_install
{

   class CLASS_DECL_BOOT canvas
   {
   public:

      int32_t      m_iMode;
      int32_t      m_iModeCount;

      canvas();
      ~canvas();

      void on_paint(simple_graphics & g, LPCRECT lpcrect);


      int32_t increment_mode();


   };


} // namespace spa_install





