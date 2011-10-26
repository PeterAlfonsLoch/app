#include "StdAfx.h"

point_array::~point_array(void)
{
}

void point_array::offset(int x, int y)
{
   for(int i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).x += x;
      this->element_at(i).y += y;
   }
}

void point_array::get_bounding_rect(LPRECT lprect)
{
   if(this->get_count() <= 0)
   {
      lprect->left      = 0;
      lprect->top       = 0;
      lprect->right     = 0;
      lprect->bottom    = 0;
   }
   else
   {
      lprect->left      = this->element_at(0).x;
      lprect->top       = this->element_at(0).y;
      lprect->right     = this->element_at(0).x;
      lprect->bottom    = this->element_at(0).y;

      for(int i = 1; i < this->get_count(); i++)
      {
         if(this->element_at(i).x < lprect->left)
            lprect->left = this->element_at(i).x;
         else if(this->element_at(i).x > lprect->right)
            lprect->right = this->element_at(i).x;
         if(this->element_at(i).y < lprect->top)
            lprect->top = this->element_at(i).y;
         else if(this->element_at(i).y > lprect->bottom)
            lprect->bottom = this->element_at(i).y;
      }
   }
}

bool point_array::bounding_rect_contains_pt(point pt)
{
   rect rect;
   get_bounding_rect(rect);
   return rect.contains(pt);
}


point64_array::~point64_array(void)
{
}

void point64_array::offset(__int64 x, __int64 y)
{
   for(int i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).x += x;
      this->element_at(i).y += y;
   }
}


double_point_array::~double_point_array(void)
{
}

void double_point_array::offset(double x, double y)
{
   for(int i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).x += x;
      this->element_at(i).y += y;
   }
}

