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





namespace gen
{

   namespace lemon
   {

      CLASS_DECL_ca2 stringa x1_decode_ida(const char * psz)
	   {
         string str(psz);
         if(str.is_empty())
      	   return stringa();
		   str.replace("><", ",");
		   str = str.Mid(1, str.get_length() - 2);
		   stringa stra;
         stra.explode(",", str);;
		   return stra;
	   }

      CLASS_DECL_ca2 string x1_encode_ida(const stringa & stra)
	   {
		   string str;
         for(int i = 0 ; i < stra.get_count(); i++)
		   {
			   str += "<" + stra[i] + ">";
		   }
		   return str;
	   }


   } // namespace lemon


} // namespace gen

