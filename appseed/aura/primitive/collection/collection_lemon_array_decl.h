#pragma once




namespace lemon
{

   namespace array
   {

      template < class TYPE >
      ::count ensure_sequence(numeric_array < TYPE > & a,TYPE start,TYPE end,TYPE increment = 1);

      template < class TYPE >
      ::count append_sequence(numeric_array < TYPE > & a, TYPE iterator,TYPE end,TYPE increment = 1);
      
      template < class TYPE >
      ::count set_sequence(numeric_array < TYPE > & a,TYPE start,TYPE end,TYPE increment = 1);


      template<class ARRAY>
      bool binary_search(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index & iIndex,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),index_array & ia);

      template<class ARRAY>
      index sort_add(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),index_array & ia);

      template < class TYPE >
      ::count remove_greater_than(::numeric_array < TYPE > & a,TYPE hi);

      template < class TYPE >
      ::count remove_greater_than_or_equal(::numeric_array < TYPE > & a,TYPE hi);

      template < class TYPE >
      ::count remove_lesser_than(::numeric_array < TYPE > & a,TYPE lo);

      template < class TYPE >
      ::count remove_lesser_than_or_equal(::numeric_array < TYPE > & a,TYPE lo);

      template < class TYPE >
      ::count remove_lesser_than_or_greater_than(::numeric_array < TYPE > & a,TYPE lo,TYPE hi);
      
      template < class TYPE >
      ::count remove_lesser_than_or_greater_than_or_equal(::numeric_array < TYPE > & a,TYPE lo,TYPE hi);
      
      template < class TYPE >
      ::count remove_lesser_than_or_equal_or_greater_than(::numeric_array < TYPE > & a,TYPE lo,TYPE hi);
      
      template < class TYPE >
      ::count remove_lesser_than_or_equal_or_greater_than_or_equal(::numeric_array < TYPE > & a,TYPE lo,TYPE hi);


   } // namespace array


} // namespace lemon




