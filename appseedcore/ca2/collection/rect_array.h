#pragma once

#include "primitive/rectangle.h"

class CLASS_DECL_ca rect_array :
   public raw_array < rect >
{
public:
   using raw_array < rect >::add;
   void add(LPCRECT lpcrect);
   void intersect(LPCRECT lpcrect);
   void get_box(LPRECT lprect);
   void offset(int cx, int cy);
   void offset(POINT pt);
   virtual ~rect_array();
};

inline void rect_array::offset(POINT pt)
{
   offset(pt.x, pt.y);
}
