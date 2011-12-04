#pragma once


template <class TYPE, class ARG_TYPE = const TYPE &>
class array_parent_alloc :
   public array_del_ptr < TYPE, ARG_TYPE >
{
public:
   array_parent_alloc();
   array_parent_alloc(const array_parent_alloc & a);
   virtual ~array_parent_alloc();

   virtual TYPE * add_new();

   virtual array_parent_alloc < TYPE, ARG_TYPE > & operator = (const array_parent_alloc <TYPE, ARG_TYPE> & base_array);

   // Potentially growing the base_array
   virtual void set_at_grow(INT_PTR nIndex, ARG_TYPE newElement);

   virtual void set_size(INT_PTR nSize);

};

template <class TYPE, class ARG_TYPE>
array_parent_alloc < TYPE, ARG_TYPE >::array_parent_alloc()
{
}

template <class TYPE, class ARG_TYPE>
array_parent_alloc < TYPE, ARG_TYPE >::array_parent_alloc(const array_parent_alloc & a)
{
   operator = (a);
}

template <class TYPE, class ARG_TYPE>
array_parent_alloc < TYPE, ARG_TYPE >::~array_parent_alloc()
{
   this->remove_all();
}


template <class TYPE, class ARG_TYPE>
inline TYPE * array_parent_alloc < TYPE, ARG_TYPE >::add_new()
{
   TYPE * p = new TYPE(this);
   add(p);
   return p;
}

template <class TYPE, class ARG_TYPE>
inline array_parent_alloc <TYPE, ARG_TYPE> & array_parent_alloc < TYPE, ARG_TYPE >::operator = (
   const array_parent_alloc <TYPE, ARG_TYPE> & a)
{
   if(&a == this)
      return *this;
   int i;
   for(i = 0; i < this->ptra().get_size(); i++)
   {
      this->element_at(i) = *a.ptra()[i];
   }
   for(; i < a.ptra().get_size(); i++)
   {
      this->ptra().add(gen::alloc<TYPE>(*a.ptra()[i]));
   }
   this->ptra().set_size(a.ptra().get_size());
   return *this;
}



template <class TYPE, class ARG_TYPE>
inline void array_parent_alloc < TYPE, ARG_TYPE >::
set_size(index iSize)
{
   while(this->get_size() < iSize)
   {
      add_new();
   }
   while(this->get_size() > iSize)
   {
      remove_at(this->get_size() - 1);
   }
}


template<class TYPE, class ARG_TYPE>
void array_parent_alloc<TYPE, ARG_TYPE>::set_at_grow(index iIndex, ARG_TYPE t)
{
   ASSERT(iIndex >= 0);

   if(iIndex < this->ptra().get_size())
   {
      this->element_at(iIndex) = t;
   }
   else
   {
      INT_PTR iOldSize = this->ptra().get_size();
      this->ptra().set_size(iIndex + 1);
      INT_PTR iEmptySize = this->ptra().get_size() - 1;
      int i;
      for(i = iIndex; i < iEmptySize; i++)
      {
         this->ptra().element_at(i) = gen::alloc<TYPE>();
      }
      this->ptra().element_at(i) = gen::alloc<TYPE>(t);
   }
}
