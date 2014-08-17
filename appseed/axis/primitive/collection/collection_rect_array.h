#pragma once

class CLASS_DECL_AXIS rect_array :
   public array < rect >
{
public:


   virtual ~rect_array();

   using array < rect >::add;
   void add(const RECT & rect);
   void add(int left,int top,int right,int bottom);
   void add(POINT pt, SIZE sz);
   void intersect(const RECT & rect);

   void add_dim(int x, int y, int cx, int cy);

   index max_normal_intersect_area(const RECT & rect, const RECT & rectModel);

   
   void get_box(LPRECT lprect);
   ::rect union_rect();

   void offset(int32_t cx, int32_t cy);
   void offset(POINT pt);

   
};

inline void rect_array::offset(POINT pt)
{
   offset(pt.x, pt.y);
}


