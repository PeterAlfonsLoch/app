#pragma once

class CLASS_DECL_BASE rect_array :
   public array < rect >
{
public:


   virtual ~rect_array();

   using array < rect >::add;
   void add(LPCRECT lpcrect);
   void intersect(LPCRECT lpcrect);
   
   void get_box(LPRECT lprect);
   ::rect union_rect();

   void offset(int32_t cx, int32_t cy);
   void offset(POINT pt);

   
};

inline void rect_array::offset(POINT pt)
{
   offset(pt.x, pt.y);
}
