#pragma once


namespace html
{


   class CLASS_DECL_ca2 box
   {
   public:


      float    left;
      float    top;
      float    right;
      float    bottom;


      inline box();

      inline bool contains(float x, float y);
      inline bool contains(::point pt);
      inline void set_size(float x, float y);
      inline void offset_x(float x);
      inline void offset_y(float y);
      inline void offset_xy(float x, float y);
      inline void set_x(float x);
      inline void set_y(float y);
      inline void set_xy(float x, float y);
      inline void set_cx(float cx);
      inline void set_cy(float cy);
      inline void set_cxy(float cx, float cy);
      inline LPRECT get(LPRECT lprect);
      inline float get_cx();
      inline float get_cy();
      inline size get_cxy();
   };


   inline box::box()
   {

      left     = 0.0f;
      top      = 0.0f;
      right    = 0.0f;
      bottom   = 0.0f;

   }

   inline bool box::contains(float x, float y)
   {

      return x >= left && x <= right && y >= top  && y <= bottom;

   }

   inline bool box::contains(::point pt)
   {

      return contains((float) pt.x, (float) pt.y);

   }

   inline void box::set_cx(float cx)
   {
      right = left + cx;
   }

   inline void box::set_cy(float cy)
   {
      bottom = top + cy;
   }

   inline void box::set_cxy(float cx, float cy)
   {
      set_cx(cx);
      set_cy(cy);
   }

   inline void box::offset_x(float x)
   {
      left     += x;
      right    += x;
   }

   inline void box::offset_y(float y)
   {
      top      += y;
      bottom   += y;
   }

   inline void box::offset_xy(float x, float y)
   {
      offset_x(x);
      offset_y(y);
   }

   inline void box::set_x(float x)
   {
      right    = right - left + x;
      left     = x;
   }

   inline void box::set_y(float y)
   {
      bottom   = bottom - top + y;
      top      = y;
   }

   inline void box::set_xy(float x, float y)
   {
      set_x(x);
      set_y(y);
   }

   inline LPRECT box::get(LPRECT lprect)
   {
      lprect->left      = (long) left;
      lprect->right     = (long) right;
      lprect->top       = (long) top;
      lprect->bottom    = (long) bottom;
      return lprect;
   }

   inline float box::get_cx()
   {
      return right - left;
   }


   inline float box::get_cy()
   {
      return bottom - top;
   }

   inline size box::get_cxy()
   {
      return size(get_cx(), get_cy());
   }

} // namespace html




