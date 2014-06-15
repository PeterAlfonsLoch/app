#include "framework.h"

rect_array::~rect_array()
{

}

void rect_array::offset(int32_t cx, int32_t cy)
{
   for(int32_t i = 0; i < this->get_size(); i++)
   {
      rect & rect = this->element_at(i);
      rect.left   += cx;
      rect.top    += cy;
      rect.right  += cx;
      rect.bottom += cy;

   }

}


::rect rect_array::union_rect()
{

   rect rectUnion(0,0,0,0);

   for(int32_t i = 0; i < this->get_size(); i++)
   {
      rectUnion.unite(rectUnion,this->element_at(i));
   }

   return rectUnion;

}


void rect_array::get_box(LPRECT lprect)
{

   *lprect = union_rect();

}


void rect_array::intersect(LPCRECT lpcrect)
{
   for(int32_t i = 0; i < this->get_size();)
   {
      this->element_at(i).intersect(this->element_at(i), lpcrect);
      if(this->element_at(i).is_null())
      {
         remove_at(i);
      }
      else
      {
         i++;
      }
   }

}

void rect_array::add(LPCRECT lpcrect)
{
   array < rect >::add(rect(*lpcrect));
}
