#pragma once


namespace html
{


   class CLASS_DECL_CORE box
   {
   public:


      float    left;
      float    top;
      float    right;
      float    bottom;


      inline box();


      inline point & top_left();
      inline point & bottom_right();
      inline point top_left() const;
      inline point bottom_right() const;
      inline point top_right() const;
      inline point bottom_left() const;

      inline box & constrain(box & box) const;


      inline bool contains(float x, float y) const;
      inline bool contains(::point pt) const;
      inline void offset_x(float x);
      inline void offset_y(float y);
      inline void offset_xy(float x, float y);
      inline void set_x(float x);
      inline void set_y(float y);
      inline void set_xy(float x, float y);
      inline void set_xy(point point);
      inline void set_cx(float cx);
      inline void set_cy(float cy);
      inline void set_cxy(float cx, float cy);
      inline void set_cxy(::size sz);
      inline void set_cxy(size sz);
      inline void set_pos_dim(float x, float y, float cx, float cy);
      inline LPRECT get(LPRECT lprect) const;
      inline float get_cx() const;
      inline float get_cy() const;
      inline size get_cxy() const;
      inline float area() const;

      inline box & operator = (const RECT & rect);

   };


   inline box::box()
   {

      left     = 0.0f;
      top      = 0.0f;
      right    = 0.0f;
      bottom   = 0.0f;

   }

   inline bool box::contains(float x, float y) const
   {

      return x >= left && x <= right && y >= top  && y <= bottom;

   }

   inline bool box::contains(::point pt) const
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

   inline void box::set_cxy(::size sz)
   {
      set_cxy((float) sz.cx, (float) sz.cy);
   }

   inline void box::set_cxy(size sz)
   {
      set_cxy(sz.cx, sz.cy);
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

   inline void box::set_xy(point point)
   {
      set_xy(point.x, point.y);
   }

   inline LPRECT box::get(LPRECT lprect) const
   {
      lprect->left      = (int32_t) left;
      lprect->right     = (int32_t) right;
      lprect->top       = (int32_t) top;
      lprect->bottom    = (int32_t) bottom;
      return lprect;
   }

   inline float box::get_cx() const
   {
      return right - left;
   }


   inline float box::get_cy() const
   {
      return bottom - top;
   }

   inline size box::get_cxy() const
   {
      return size(get_cx(), get_cy());
   }

   inline point & box::top_left()
   {
      return *((point *) &left);
   }

   inline point & box::bottom_right()
   {
      return *((point *) &right);
   }

   inline point box::top_left() const
   {
      return point(left, top);
   }

   inline point box::bottom_right() const
   {
      return point(right, bottom);
   }

   inline point box::top_right() const
   {
      return point(right, top);
   }

   inline  point box::bottom_left() const
   {
      return point(left, bottom);
   }

   inline box & box::constrain(box & box) const
   {

      if(box.left < left)
         box.left = left;

      if(box.right < right)
         box.right = right;

      if(box.top < top)
         box.top = top;

      if(box.bottom < bottom)
         box.bottom = bottom;

      return box;

   }

   inline void box::set_pos_dim(float x, float y, float cx, float cy)
   {

      left     = x;
      top      = y;
      right    = x + cx;
      bottom   = y + cy;


   }

   inline box & box::operator = (const RECT & rect)
   {

      left     = (float) rect.left;
      top      = (float) rect.top;
      right    = (float) rect.right;
      bottom   = (float) rect.bottom;

      return *this;

   }

   inline float box::area() const
   {

      return (get_cx() < 0.f && get_cy() < 0.f ? -1.0f : 1.0f) * get_cx() * get_cy();

   }


} // namespace html




