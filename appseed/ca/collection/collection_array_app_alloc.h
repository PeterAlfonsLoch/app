#pragma once


template <class TYPE, class ARG_TYPE = const TYPE &>
class array_app_alloc :
   public array_del_ptr < TYPE, ARG_TYPE >
{
public:


   array_app_alloc(::ca::application * papp);
   array_app_alloc();
   array_app_alloc(const array_app_alloc & a);
   virtual ~array_app_alloc();


   virtual TYPE * add_new();
   index add(const TYPE & t);
   index add(TYPE * p);
   inline void insert_at(index iIndex, ARG_TYPE t);

   void remove_at(index iIndex);
   count remove_all(bool bRelease = true);
   void remove_last(bool bRelease = true);

   void copy(const array_app_alloc < TYPE, ARG_TYPE > & base_array);

   // Potentially growing the base_array
   virtual void set_at_grow(int_ptr nIndex, ARG_TYPE newElement);

   void set_size(::count iSize);

   array_app_alloc < TYPE, ARG_TYPE > & operator = (const array_app_alloc <TYPE, ARG_TYPE> & base_array);

};

template <class TYPE, class ARG_TYPE>
array_app_alloc < TYPE, ARG_TYPE >::array_app_alloc(::ca::application * papp) :
 ::ca::ca(papp)
{
}

template <class TYPE, class ARG_TYPE>
array_app_alloc < TYPE, ARG_TYPE >::array_app_alloc()
{
}

template <class TYPE, class ARG_TYPE>
array_app_alloc < TYPE, ARG_TYPE >::array_app_alloc(const array_app_alloc & a)
{
   operator = (a);
}

template <class TYPE, class ARG_TYPE>
array_app_alloc < TYPE, ARG_TYPE >::~array_app_alloc()
{
   remove_all();
}


template <class TYPE, class ARG_TYPE>
inline index array_app_alloc < TYPE, ARG_TYPE >::add(
   TYPE * pt)
{
   gen::add_ref(pt);
   return array_del_ptr < TYPE, ARG_TYPE >::add(pt);
}



template <class TYPE, class ARG_TYPE>
void array_app_alloc < TYPE, ARG_TYPE >::copy(const array_app_alloc < TYPE, ARG_TYPE > & a)
{
   remove_all();
   for(int32_t i = 0; i < a.get_size(); i++)
   {
      add(a[i]);
   }
}




template <class TYPE, class ARG_TYPE>
inline void array_app_alloc < TYPE, ARG_TYPE >::remove_at(index iIndex)
{
   try
   {
      gen::release(this->ptra().element_at(iIndex));
   }
   catch(...)
   {
   }
   this->ptra().remove_at(iIndex);
}

template <class TYPE, class ARG_TYPE>
inline count array_app_alloc < TYPE, ARG_TYPE >::remove_all(bool bRelease /*=true*/)
{
   if(bRelease)
   {
      for(int32_t iIndex = 0; iIndex < this->ptra().get_size(); iIndex++)
      {
         gen::release(this->ptra().element_at(iIndex));
      }
   }
   return this->ptra().remove_all();
}

template <class TYPE, class ARG_TYPE>
inline void array_app_alloc < TYPE, ARG_TYPE >::remove_last(bool bRelease /*=true*/)
{
   if(bRelease)
   {
      gen::release(this->ptra().last_element());
   }
   this->ptra().remove_last();
}
