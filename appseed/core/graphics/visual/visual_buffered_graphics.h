#pragma once


namespace visual
{


   class buffered_graphics : 
      public ::draw2d::graphics_sp  
   {
   public:

      
      ::draw2d::bitmap_sp   m_spbitmap;
      ::draw2d::bitmap_sp   m_spbitmapBlend;


      buffered_graphics();
      virtual ~buffered_graphics();


      void Prepare(const RECT & rect);


   };


} // namespace vis





