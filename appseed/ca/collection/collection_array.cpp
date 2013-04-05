#include "framework.h"


void _123abc_debug_gen_array_randomize(::ca::applicationsp papp);
void ___arrayStdSortTest();


void _123abc_debug_gen_array_randomize(::ca::applicationsp papp)
{
   int_array a;
   a.add_unique(1);
   a.add_unique(2);
   App(papp).lemon_array().randomize(a);
}

namespace lemon
{

   array::array(::ca::applicationsp papp) :
      ca(papp)
   {
   }

} // namespace lemon



#ifdef DEBUG

void ___arrayStdSortTest()
{
   array<int32_t, int32_t> ia;
   /*::ca::_sort::quick_sort(
      ia,
      sort::CompareAscending < int32_t >);*/

}

#endif // DEBUG





namespace lemon
{

   CLASS_DECL_ca stringa x1_decode_ida(const char * psz)
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

   CLASS_DECL_ca string x1_encode_ida(const stringa & stra)
	{
		string str;
      for(int32_t i = 0 ; i < stra.get_count(); i++)
		{
			str += "<" + stra[i] + ">";
		}
		return str;
	}


} // namespace lemon

