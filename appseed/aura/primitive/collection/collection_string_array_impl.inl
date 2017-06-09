#pragma once


#include "aura/primitive/collection/collection_var_array.h"
#include "aura/primitive/primitive_property_set.h"
#include "aura/primitive/primitive_memory.h"


template < typename TYPE >
TYPE string_array < TYPE >::safe_at(index nIndex, TYPE tDefault) const
{
   if (nIndex < 0 || nIndex >= this->get_size())
      return tDefault;

   return this->element_at(nIndex);

}

template < typename TYPE >
TYPE string_array < TYPE >::safe_at(index nIndex, TYPE tDefault)
{
   if (nIndex < 0 || nIndex >= this->get_size())
      return tDefault;

   return this->element_at(nIndex);

}


//template < typename TYPE >
//TYPE string_array < TYPE >::get_at(index nIndex) const
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw index_out_of_bounds(this->get_app());
//   return get_data()[nIndex];
//}
//
//template < typename TYPE >
//void string_array < TYPE >::set_at(index nIndex, const char * newElement)
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw index_out_of_bounds(this->get_app());
//   get_data()[nIndex] = newElement;
//}


//template < typename TYPE >
//void string_array < TYPE >::set_at(index nIndex, const TYPE & newElement)
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw index_out_of_bounds(this->get_app());
//   get_data()[nIndex] = newElement;
//}
//
//
//template < typename TYPE >
//TYPE & string_array < TYPE >::element_at(index nIndex)
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw index_out_of_bounds(this->get_app());
//   return get_data()[nIndex];
//}
//
//
//template < typename TYPE >
//const TYPE & string_array < TYPE >::element_at(index nIndex) const
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw index_out_of_bounds(this->get_app());
//   return get_data()[nIndex];
//}




