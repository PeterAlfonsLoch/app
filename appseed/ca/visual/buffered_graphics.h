#pragma once

namespace visual
{

   class buffered_graphics : 
      public ::ca::graphics_sp  
   {
   public:

      
      ::ca::bitmap_sp   m_spbitmap;
      ::ca::bitmap_sp   m_spbitmapBlend;


      buffered_graphics();
      virtual ~buffered_graphics();


      void Prepare(LPCRECT lpcrect);


   };

} // namespace vis