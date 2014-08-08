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


void rect_array::add(int left,int top,int right,int bottom)
{
   array < rect >::add(rect(left, top, right, bottom));
}


void rect_array::add_dim(int x,int y,int cx,int cy)
{
   array < rect >::add(rect_dim(x, y, cx, cy));
}


void rect_array::add(POINT pt, SIZE sz)
{
   array < rect >::add(rect(pt, sz));
}


index rect_array::max_normal_intersect_area(LPCRECT lpcrect,LPCRECT lpcrectModel)
{

   int64_t iArea;
   int64_t iAreaMax = 0;
   index iFound = -1;
   rect rect;
   int64_t iModelArea = width(lpcrectModel) * height(lpcrectModel);

   if(iModelArea == 0)
      return -1;

   for(index i = 0; i < get_count(); i++)
   {

      if(rect.intersect(lpcrect,element_at(i)))
      {

         iArea = rect.area() * element_at(i).area() / iModelArea;

         if(iArea > iAreaMax)
         {

            iFound = i;

            iAreaMax = iArea;

         }


      }

   }

   return iFound;

}