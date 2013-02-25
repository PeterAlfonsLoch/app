#pragma once


#undef new


template <class TYPE, class ARG_TYPE = const TYPE &, class BASE_PTRA = comparable_array < TYPE * > >
class array_smart_ptr :
   public array_release_ptr < TYPE, ARG_TYPE, BASE_PTRA >
{
public:


   array_smart_ptr(::ca::application * papp);
   array_smart_ptr(const array_smart_ptr & a);
   virtual ~array_smart_ptr();


   virtual index add(TYPE * pt);
   virtual TYPE * add_new();


   // Potentially growing the base_array
   virtual void set_at_grow(int_ptr nIndex, ARG_TYPE newElement);

   virtual void set_size(int_ptr nSize);

};

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_smart_ptr < TYPE, ARG_TYPE, BASE_PTRA >::array_smart_ptr(::ca::application * papp) :
   ::ca::ca(papp)
{
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_smart_ptr < TYPE, ARG_TYPE, BASE_PTRA >::array_smart_ptr(const array_smart_ptr & a) :
   ::ca::ca(a.get_app())
{
   operator = (a);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_smart_ptr < TYPE, ARG_TYPE, BASE_PTRA >::~array_smart_ptr()
{
   this->remove_all();
}



template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_smart_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
set_size(count iSize)
{
   while(this->get_size() < iSize)
   {
      add_new();
   }
   while(this->get_size() > iSize && iSize >=0)
   {
      remove_at(this->get_size() - 1);
   }
}




template < class TYPE, class ARG_TYPE, class BASE_PTRA >
inline index array_smart_ptr < TYPE, ARG_TYPE, BASE_PTRA >::add(TYPE * pt)
{
   ::ca::add_ref(pt);
   return array_release_ptr < TYPE, ARG_TYPE >::add(pt);
}


#define new DEBUG_NEW
