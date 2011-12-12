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
   virtual void set_at_grow(INT_PTR nIndex, ARG_TYPE newElement);

   virtual void set_size(INT_PTR nSize);

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
inline TYPE * array_smart_ptr < TYPE, ARG_TYPE, BASE_PTRA >::add_new()
{
   TYPE * p = System.alloc(this->get_app(), System.template type_info < TYPE > ());
   array_release_ptr < TYPE, ARG_TYPE >::add(p);
   return p;
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
void array_smart_ptr < TYPE, ARG_TYPE, BASE_PTRA >::set_at_grow(index iIndex, ARG_TYPE t)
{
   ASSERT(iIndex >= 0);

   if(iIndex < this->ptra().get_size())
   {
      this->element_at(iIndex) = t;
   }
   else
   {
      for(index i = this->get_size(); i < iIndex; i++)
      {
         this->ptra().add(System.alloc(this->get_app(), System.template type_info < TYPE > ()));
      }
      this->ptra().add(System.alloc(this->get_app(), System.template type_info < TYPE > ()));
   }
}



template < class TYPE, class ARG_TYPE, class BASE_PTRA >
inline index array_smart_ptr < TYPE, ARG_TYPE, BASE_PTRA >::add(TYPE * pt)
{
   gen::add_ref(pt);
   return array_release_ptr < TYPE, ARG_TYPE >::add(pt);
}


#define new DEBUG_NEW
