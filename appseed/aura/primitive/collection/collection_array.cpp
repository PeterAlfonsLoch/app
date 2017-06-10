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




void __debug9876()
{



   std::set<int> called_from;


   int i = 0;
   called_from.add(i);

   called_from.contains(0);

   //called_from.remove(i);

   called_from.remove_all();


   array < int > ia;


   ia.add(1);
   ia.add(2);
   ia.add(4);
   ia.add(8);

   array < int > ia2;

   ia2.add(1);
   ia2.add(2);
   ia2.add(4);
   ia2.add(8);


   ASSERT(ia.is_equal(ia2));


   stringa stra;


   var v;

   stra.explode(";", v);

}