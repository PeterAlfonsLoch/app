#include "StdAfx.h"



void _123abc_debug_gen_array_randomize(::ca::application * papp)
{
   int_array a;
   a.add_unique(1);
   a.add_unique(2);
   App(papp).lemon_array().randomize(a);
}

namespace gen
{
   namespace lemon
   {
      array::array(::ca::application * papp) :
         ca(papp)
      {
      }
   } // namespace lemon
} // namespace gen



#ifdef _DEBUG

void ___arrayStdSortTest()
{
   base_array<int, int> ia;
   /*gen::_sort::QuickSort(
      ia,
      sort::CompareAscending < int >);*/

}

#endif // _DEBUG


