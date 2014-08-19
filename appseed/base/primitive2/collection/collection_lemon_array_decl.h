#pragma once




namespace lemon
{

   namespace array
   {

      template<class ARRAY>
      bool binary_search(ARRAY & a, typename ARRAY::BASE_ARG_TYPE t, index & iIndex, index ( * fCompare ) (typename ARRAY::BASE_TYPE *, typename ARRAY::BASE_TYPE *), index_array & ia);

      template<class ARRAY>
      index sort_add(ARRAY & a, typename ARRAY::BASE_ARG_TYPE t, index ( * fCompare ) (typename ARRAY::BASE_TYPE *, typename ARRAY::BASE_TYPE *), index_array & ia);


   } // namespace array


} // namespace lemon




