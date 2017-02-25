#pragma once


#include "collection_sort.h"
#include "collection_point_array.h"


template < typename POINT2D >
void point2d_array_base < POINT2D >::offset(typename POINT2D::TYPE x, typename POINT2D::TYPE y)
{
   for (int32_t i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).x += x;
      this->element_at(i).y += y;
   }
}


template < typename POINT2D >
void point2d_array_base < POINT2D >::rotate(double dAngle)
{

   typename POINT2D::TYPE x;
   typename POINT2D::TYPE y;
   double dCos = cos(dAngle);
   double dSin = sin(dAngle);

   for (int32_t i = 0; i < this->get_count(); i++)
   {
      x = this->element_at(i).x;
      y = this->element_at(i).y;
      this->element_at(i).x = (LONG)(x * dCos - y * dSin);
      this->element_at(i).y = (LONG)(x * dSin + y * dCos);
   }

}




//template < typename POINT2D >
//void point2d_array_base < POINT2D >::xml_import(::xml::input_tree & xmlif)
//{
//
//   this->remove_all();
//
//   var varCount;
//
//   xmlif.import_node("count", varCount);
//
//   for (index i = 0; i < varCount.int32(); i++)
//   {
//
//      var x;
//
//      xmlif.import_node("x" + str::from(i), x);
//
//      var y;
//
//      xmlif.import_node("y" + str::from(i), y);
//
//      add(POINT2D
//
//      (x.int32(), y.int32()));
//
//   }
//
//}
//
//template < typename POINT2D >
//void point2d_array_base < POINT2D >::xml_export(::xml::output_tree & xmlof)
//{
//
//   xmlof.export_node("count", this->get_size());
//
//   for (index i = 0; i < this->get_count(); i++)
//   {
//
//      xmlof.export_node("x" + str::from(i), this->element_at(i).x);
//
//      xmlof.export_node("y" + str::from(i), this->element_at(i).y);
//
//   }
//
//}
//
//
//

template < typename POINT2D >
void point2d_array_base < POINT2D >::get_bounding_rect(typename POINT2D::LPRECT lprect) const
{

   this->get_bounding_rect(lprect, this->get_data(), this->get_count());

}

template < typename POINT2D >
void point2d_array_base < POINT2D >::get_bounding_rect(typename POINT2D::LPRECT lprect, const typename POINT2D::BASE * lppoint, ::count count)
{

   if (count <= 0)
   {

      lprect->left = 0;
      lprect->top = 0;
      lprect->right = 0;
      lprect->bottom = 0;

   }
   else
   {
      lprect->left = lppoint[0].x;
      lprect->top = lppoint[0].y;
      lprect->right = lppoint[0].x;
      lprect->bottom = lppoint[0].y;

      for (int32_t i = 1; i < count; i++)
      {
         if (lppoint[i].x < lprect->left)
            lprect->left = lppoint[i].x;
         else if (lppoint[i].x > lprect->right)
            lprect->right = lppoint[i].x;
         if (lppoint[i].y < lprect->top)
            lprect->top = lppoint[i].y;
         else if (lppoint[i].y > lprect->bottom)
            lprect->bottom = lppoint[i].y;
      }

   }

}


template < typename POINT2D >
bool point2d_array_base < POINT2D >::bounding_rect_contains_pt(typename POINT2D::BASE pt)
{
   typename POINT2D::RECT rect;
   this->get_bounding_rect(&rect);
   return rect.contains(pt);
}


template < typename POINT2D >
bool point2d_array_base < POINT2D >::polygon_contains(typename POINT2D::BASE pt)
{

   return ::polygon_contains(&pt, this->get_data(), (int)this->get_size());

}


template < typename POINT2D >
::count point2d_array_base < POINT2D >::add_unique_range(typename POINT2D::BASE ptBeg, typename POINT2D::BASE ptEnd, typename POINT2D::SIZE s)
{

   typename POINT2D::TYPE x1 = ptBeg.x;

   typename POINT2D::TYPE x2 = ptEnd.x;

   typename POINT2D::TYPE y1 = ptBeg.y;

   typename POINT2D::TYPE y2 = ptEnd.y;

   ::sort::sort(x1, x2);

   ::sort::sort(y1, y2);

   ::count c = 0;

   for (typename POINT2D::TYPE x = x1; x <= x2; x += s.cx)
   {

      for (typename POINT2D::TYPE y = y1; y <= y2; y += s.cy)
      {

         if (this->add_unique(POINT2D(x, y)))
         {

            c++;

         }

      }

   }

   return c;

}









