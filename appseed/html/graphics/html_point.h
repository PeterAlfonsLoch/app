#pragma once


namespace html
{

   class CLASS_DECL_CORE point
   {
   public:


      float    x;
      float    y;


      inline point();
      inline point(float x, float y);


   };

   inline point::point()
   {

      this->x  = 0.f;
      this->y  = 0.f;

   }

   inline point::point(float x, float y)
   {

      this->x  = x;
      this->y  = y;

   }


} // namespace html
