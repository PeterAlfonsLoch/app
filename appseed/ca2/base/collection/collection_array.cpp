#include "framework.h"


void _123abc_debug_gen_array_randomize(sp(::ca2::application) papp);
void ___arrayStdSortTest();


void _123abc_debug_gen_array_randomize(sp(::ca2::application) papp)
{
   int_array a;
   a.add_unique(1);
   a.add_unique(2);
   App(papp).lemon_array().randomize(a);
}

namespace lemon
{

   array::array(sp(::ca2::application) papp) :
      ca2(papp)
   {
   }

} // namespace lemon



#ifdef DEBUG

void ___arrayStdSortTest()
{
   array<int32_t, int32_t> ia;
   /*::ca2::_sort::quick_sort(
      ia,
      sort::CompareAscending < int32_t >);*/

}

#endif // DEBUG





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
      for(int32_t i = 0 ; i < stra.get_count(); i++)
		{
			str += "<" + stra[i] + ">";
		}
		return str;
	}


} // namespace lemon

