#pragma once

#include "base_rect.h"

class CLASS_DECL_ca base_rect_array :
   public base_array < base_rect, base_rect & >
{
public:
   using base_array < base_rect, base_rect & >::add;
	void add(LPCRECT lpcrect);
	void intersect(LPCRECT lpcrect);
	void get_box(LPRECT lprect);
   void offset(int cx, int cy);
	void offset(POINT pt);
	virtual ~base_rect_array();

};

inline void base_rect_array::offset(POINT pt)
{
   offset(pt.x, pt.y);
}
