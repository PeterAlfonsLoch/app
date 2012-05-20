#pragma once


#include "ca/gen/gen_composite.h"


#undef new


template <class TYPE, class ARG_TYPE = const TYPE &, class BASE_PTRA = typed_ptr_array < TYPE * > >
class array_ptr_alloc :
   public array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >
{
public:
   array_ptr_alloc();
   array_ptr_alloc(const array_ptr_alloc & a);
   virtual ~array_ptr_alloc();

   virtual TYPE * add_new();


   array_ptr_alloc < TYPE, ARG_TYPE, BASE_PTRA > & operator = (const array_ptr_alloc <TYPE, ARG_TYPE, BASE_PTRA> & base_array);

   // Potentially growing the base_array
   virtual void set_at_grow(int_ptr nIndex, ARG_TYPE newElement);


   virtual void set_size(int_ptr nSize);

};

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_ptr_alloc < TYPE, ARG_TYPE, BASE_PTRA >::array_ptr_alloc()
{
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_ptr_alloc < TYPE, ARG_TYPE, BASE_PTRA >::array_ptr_alloc(const array_ptr_alloc & a)
{
   operator = (a);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_ptr_alloc < TYPE, ARG_TYPE, BASE_PTRA >::~array_ptr_alloc()
{
}


template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline TYPE * array_ptr_alloc < TYPE, ARG_TYPE, BASE_PTRA >::add_new()
{
   TYPE * p = gen::alloc<TYPE>();
   this->add(p);
   return p;
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline array_ptr_alloc < TYPE, ARG_TYPE, BASE_PTRA > & array_ptr_alloc < TYPE, ARG_TYPE, BASE_PTRA >::operator = (const array_ptr_alloc <TYPE, ARG_TYPE, BASE_PTRA > & a)
{
   if(&a == this)
      return *this;
   index i;
   for(i = 0; i < this->get_size(); i++)
   {
      this->element_at(i) = a[i];
   }
   for(; i < a.get_size(); i++)
   {
      this->ptra().add(gen::alloc<TYPE>(a[i]));
   }
   this->ptra().set_size(a.get_size());
   return *this;
}



template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_ptr_alloc < TYPE, ARG_TYPE, BASE_PTRA >::
set_size(count iSize)
{
   while(this->get_size() < iSize)
   {
      add_new();
   }
   while(this->get_size() > iSize && iSize >=0)
   {
      this->remove_at(this->get_size() - 1);
   }
}


template < class TYPE, class ARG_TYPE, class BASE_PTRA >
void array_ptr_alloc < TYPE, ARG_TYPE, BASE_PTRA >::set_at_grow(index iIndex, ARG_TYPE t)
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
         this->ptra().add(gen::alloc<TYPE>());
      }
      this->ptra().add(gen::alloc<TYPE>(t));
   }
}


///////////////////////////////////////////////////////////////////////////////
//
// Class Name: Base2DArray
//
// Two dimensional base_array
//
///////////////////////////////////////////////////////////////////////////////
template < class TYPE, class ARG_TYPE, class BASE_PTRA = comparable_array < base_array < TYPE, ARG_TYPE & > * > >
class Base2DArray:
public array_ptr_alloc < base_array < TYPE, ARG_TYPE >, base_array < TYPE, ARG_TYPE > &, BASE_PTRA >
{
public:

   void BubbleSortBySize(bool bAsc = true);
};

template < class TYPE, class ARG_TYPE, class BASE_PTRA >
void Base2DArray < TYPE, ARG_TYPE, BASE_PTRA >::
BubbleSortBySize(bool bAsc)
{
    TYPE t;
    if(bAsc)
    {
        for(index i = 0; i < this->get_size(); i++)
        {
           for(index j = i + 1; j < this->get_size(); j++)
           {
               if(this->element_at(i).get_size() > this->element_at(j).get_size())
               {
                   t = this->element_at(i);
                   set_at(i, this->element_at(j));
                   set_at(j, t);
               }

           }
        }
    }
    else
    {
        for(index i = 0; i < this->get_size(); i++)
        {
           for(index j = i + 1; j < this->get_size(); j++)
           {
               if(this->element_at(i).get_size() < this->element_at(j).get_size())
               {
                   t = this->element_at(i);
                   set_at(i, this->element_at(j));
                   set_at(j, t);
               }

           }
        }
    }
}


#define new DEBUG_NEW


