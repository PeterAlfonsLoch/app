#pragma once

namespace core
{
   template < class t > inline void swap(t &t1, t &t2)
   {
      t t3 = t1;
      t1 = t2;
      t2 = t3;
   }

   namespace sort
   {
      template < class t > inline void sort(t &t1, t &t2)
      {
         if(t1 > t2)
            swap(t1, t2);
      }
   }
} // namespace core

