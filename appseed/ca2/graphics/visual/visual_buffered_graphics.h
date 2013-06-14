#pragma once

namespace visual
{

   class buffered_graphics : 
      public ::ca2::graphics_sp  
   {
   public:

      
      ::ca2::bitmap_sp   m_spbitmap;
      ::ca2::bitmap_sp   m_spbitmapBlend;


      buffered_graphics();
      virtual ~buffered_graphics();


      void Prepare(LPCRECT lpcrect);


   };

} // namespace vis