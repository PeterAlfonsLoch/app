#pragma once




namespace lemon
{

   namespace array
   {

      template<class ARRAY>
      bool binary_search(ARRAY & a, typename ARRAY::AXIS_ARG_TYPE t, index & iIndex, index ( * fCompare ) (typename ARRAY::AXIS_TYPE *, typename ARRAY::AXIS_TYPE *), raw_index_array & ia);

      template<class ARRAY>
      index sort_add(ARRAY & a, typename ARRAY::AXIS_ARG_TYPE t, index ( * fCompare ) (typename ARRAY::AXIS_TYPE *, typename ARRAY::AXIS_TYPE *), raw_index_array & ia);


   } // namespace array


} // namespace lemon




