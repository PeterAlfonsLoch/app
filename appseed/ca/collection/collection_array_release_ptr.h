#pragma once


template <class TYPE, class ARG_TYPE = const TYPE &, class BASE_PTRA = comparable_array < TYPE * > >
class array_release_ptr :
   virtual public array_ptr < TYPE, ARG_TYPE, BASE_PTRA >
{
public:
   array_release_ptr();
   virtual ~array_release_ptr();

   void remove_at(int_ptr iIndex);
   count remove_all(bool bRelease = true);
   void remove_last(bool bRelease = true);

};

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_release_ptr < TYPE, ARG_TYPE, BASE_PTRA >::array_release_ptr()
{
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_release_ptr < TYPE, ARG_TYPE, BASE_PTRA >::~array_release_ptr()
{
   remove_all();
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_release_ptr < TYPE, ARG_TYPE, BASE_PTRA >::remove_at(
   index iIndex)
{
   ::ca::release(this->ptra().element_at(iIndex));
   this->ptra().remove_at(iIndex);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline count array_release_ptr < TYPE, ARG_TYPE, BASE_PTRA >::remove_all(bool bRelease /*=true*/)
{
   if(bRelease)
   {
      for(int32_t iIndex = 0; iIndex < this->ptra().get_size(); iIndex++)
      {
         ::ca::release(this->ptra().element_at(iIndex));
      }
   }
   return this->ptra().remove_all();
}


template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_release_ptr < TYPE, ARG_TYPE, BASE_PTRA >::remove_last(bool bRelease /*=true*/)
{
   if(bRelease)
   {
      ::ca::release(this->ptra().last_element());
   }
   this->ptra().remove_last();
}


