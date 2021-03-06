#pragma once


namespace lemon
{


   namespace array
   {


      template < class TDST,class TSRC >
      ::count copy(TDST & dsta,const TSRC & srca)
      {

         dsta.remove_all();

         for(int i = 0; i < srca.get_size(); i++)
         {

            dsta.add((typename TDST::BASE_TYPE) srca[i]);

         }

         return dsta.get_count();

      }


   } // namespace array


   template < class TDST, class TSRC >
   ::count copy(spa(TDST) & dsta, const spa(TSRC) & srca)
   {

      ::count ca = 0;

      dsta.remove_all();

      for(int i = 0; i < srca.get_size(); i++)
      {
         dsta.add(canew(TSRC(srca(i))));
         ca++;
      }

      return ca;

   }

   namespace ptra
   {

      template < class TDST,class TSRC >
      ::count copy(ref_array < TDST > & dsta,const ref_array < TSRC > & srca)
      {

         ::count ca = 0;

         dsta.remove_all();

         for(int i = 0; i < srca.get_size(); i++)
         {
            dsta.add(new TSRC(srca(i)));
            ca++;
         }

         return ca;

      }


   }


   template < class A, class A2D >
	void array_permute(A2D & perm, const A & a)
	{
		::count count = a.get_count();
		if(count == 1)
      {
      	perm.add(a);
         return;
      }
      A elema;
      A topermut;
      A2D perm2;
      for(int32_t i = 0; i < count; i++)
		{
         elema.remove_all();
         elema.add(a[i]);
         topermut.remove_all();
         for(int32_t j = 0; j < i; j++)
         {
            topermut.add(a[j]);
         }
         for(int32_t j = i + 1; j < count; j++)
         {
            topermut.add(a[j]);
         }
         perm2.remove_all();
			array_permute(perm2, topermut);
			for(int32_t j = 0; j < perm2.get_count(); j++)
			{
            perm.add(elema + perm2[j]);
		   }
		}
	}

   template < class A >
   void array_permute(smart_pointer_array < A > & perm,const A & a)
   {
      ::count count = a.get_count();
      if(count == 1)
      {
         perm.add(canew(A(a)));
         return;
      }
      A elema;
      A topermut;
      smart_pointer_array < A > perm2;
      for(int32_t i = 0; i < count; i++)
      {
         elema.remove_all();
         elema.add(a[i]);
         topermut.remove_all();
         for(int32_t j = 0; j < i; j++)
         {
            topermut.add(a[j]);
         }
         for(int32_t j = i + 1; j < count; j++)
         {
            topermut.add(a[j]);
         }
         perm2.remove_all();
         array_permute(perm2,topermut);
         for(int32_t j = 0; j < perm2.get_count(); j++)
         {
            perm.add(canew(A(elema + perm2[j])));
         }
      }
   }

} // namespace array






namespace lemon
{

   namespace array
   {

      template <>
      inline void add(stringa & stra,const stringa & straSource) { stra.add(straSource); }
      template <>
      inline void add(::file::patha & patha,const stringa & stra) { forallref(stra) { patha.add(::file::path(item)); } }
      template <>
      inline void add(::file::patha & patha,const string & str) { patha.add(::file::path(str)); }



   } // namespace array





} // namespace lemon













