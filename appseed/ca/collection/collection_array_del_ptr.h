#pragma once


#undef new


#include "ca/ca/gen_composite.h"


template <class TYPE, class ARG_TYPE = const TYPE &, class BASE_PTRA = comparable_array < TYPE * > >
class array_del_ptr :
   virtual public array_ptr < TYPE, ARG_TYPE, BASE_PTRA >
{
public:
   
   
   array_del_ptr();
   virtual ~array_del_ptr();

   
   void remove_at(index iIndex);
   count remove_all(bool bDelete = true);
   void remove_last(bool bDelete = true);


};

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_del_ptr < TYPE, ARG_TYPE, BASE_PTRA >::array_del_ptr()
{
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_del_ptr < TYPE, ARG_TYPE, BASE_PTRA >::~array_del_ptr()
{
   remove_all();
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_del_ptr < TYPE, ARG_TYPE, BASE_PTRA >::remove_at(
   index iIndex)
{
   ca::_sdel<TYPE>((TYPE *) this->ptra().element_at(iIndex));
   this->ptra().remove_at(iIndex);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline count array_del_ptr < TYPE, ARG_TYPE, BASE_PTRA >::remove_all(bool bDelete /*=true*/)
{
   if(bDelete)
   {
      for(int32_t iIndex = 0; iIndex < this->ptra().get_size(); iIndex++)
      {
         ca::_sdel<TYPE>((TYPE *) this->ptra().element_at(iIndex));
      }
   }
   return this->ptra().remove_all();
}


template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_del_ptr < TYPE, ARG_TYPE, BASE_PTRA >::remove_last(bool bDelete /*=true*/)
{
   if(bDelete)
   {
      ca::_sdel<TYPE>((TYPE *) this->ptra().last_element());
   }
   this->ptra().remove_last();
}


