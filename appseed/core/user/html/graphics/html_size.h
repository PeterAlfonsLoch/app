#pragma once


namespace html
{


   class CLASS_DECL_HTML size
   {
   public:


      float    cx;
      float    cy;


      inline size();
      inline size(const ::size & size);
      inline size(float cx, float cy);

   };


   inline size::size()
   {
      cx = 0.0f;
      cy = 0.0f;
   }

   inline size::size(const ::size & size)
   {
      cx = (float) size.cx;
      cy = (float) size.cy;
   }

   inline size::size(float cx, float cy)
   {
      this->cx = cx;
      this->cy = cy;
   }


} // namespace html


