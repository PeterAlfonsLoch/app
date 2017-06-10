//#include "framework.h"


void _123abc_debug_gen_array_randomize(::aura::application * papp);
void ___arrayStdSortTest();

/*
void _123abc_debug_gen_array_randomize(::aura::application * papp)
{
   int_array a;
   a.add_unique(1);
   a.add_unique(2);
   App(papp).array().randomize(a);
}
*/


#ifdef DEBUG

void ___arrayStdSortTest()
{
   array<int32_t, int32_t> ia;
   /*::core::_sort::quick_sort(
      ia,
      sort::CompareAscending < int32_t >);*/

}

#endif // DEBUG





namespace lemon
{

    stringa x1_decode_ida(const char * psz)
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

    string x1_encode_ida(const stringa & stra)
	{
		string str;
      for(int32_t i = 0 ; i < stra.get_count(); i++)
		{
			str += "<" + stra[i] + ">";
		}
		return str;
	}


} // namespace lemon


#ifdef DEBUG

void _debug_quick_sort_iter()
{


   int_array ia;

   ia.add(3);
   ia.add(2);
   ia.add(1);

   ::sort::quick_sort_iter(ia.begin(), ia.end());


}



#endif