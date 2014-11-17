#pragma once


template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)( TYPE *, TYPE *) >
index_array & sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
defer_update(index(* fCompare) (ARG_TYPE,ARG_TYPE))
{

   sp(sort_index) & sortindex = m_indexmap[fCompare];

   if(sortindex.is_null())
      sortindex = new sort_index;

   if(!sortindex->m_bUpdated)
   {
      sortindex->m_indexa.ensure_sequence(0, this->get_upper_bound());
      ::sort::array::quick_sort(*this, fCompare, sortindex->m_indexa);
      sortindex->m_bUpdated = true;
   }

   return sortindex->m_indexa;

}
