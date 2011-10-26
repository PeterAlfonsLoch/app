#pragma once

template <class TYPE, class ARG_TYPE = const TYPE &>
class array_ptr_alloc :
   public array_ptr_copy < TYPE, ARG_TYPE >
{
public:
	array_ptr_alloc();
   array_ptr_alloc(const array_ptr_alloc & a);
	virtual ~array_ptr_alloc();

   virtual TYPE * add_new();


	array_ptr_alloc < TYPE, ARG_TYPE > & operator = (const array_ptr_alloc <TYPE, ARG_TYPE> & base_array);

	// Potentially growing the base_array
	virtual void set_at_grow(INT_PTR nIndex, ARG_TYPE newElement);


   virtual void set_size(INT_PTR nSize);

};

template <class TYPE, class ARG_TYPE>
array_ptr_alloc < TYPE, ARG_TYPE >::array_ptr_alloc()
{
}

template <class TYPE, class ARG_TYPE>
array_ptr_alloc < TYPE, ARG_TYPE >::array_ptr_alloc(const array_ptr_alloc & a)
{
   operator = (a);
}

template <class TYPE, class ARG_TYPE>
array_ptr_alloc < TYPE, ARG_TYPE >::~array_ptr_alloc()
{
   remove_all();
}


template <class TYPE, class ARG_TYPE>
inline TYPE * array_ptr_alloc < TYPE, ARG_TYPE >::add_new()
{
   TYPE * p = gen::alloc<TYPE>();
   add(p);
   return p;
}

template <class TYPE, class ARG_TYPE>
inline array_ptr_alloc <TYPE, ARG_TYPE> & array_ptr_alloc < TYPE, ARG_TYPE >::operator = (
   const array_ptr_alloc <TYPE, ARG_TYPE> & a)
{
   if(&a == this)
      return *this;
	index i;
   for(i = 0; i < m_ptra.get_size(); i++)
   {
      this->element_at(i) = *a.m_ptra[i];
   }
   for(; i < a.m_ptra.get_size(); i++)
   {
      m_ptra.add(gen::alloc<TYPE>(*a.m_ptra[i]));
   }
   m_ptra.set_size(a.m_ptra.get_size());
   return *this;
}



template <class TYPE, class ARG_TYPE>
inline void array_ptr_alloc < TYPE, ARG_TYPE >::
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


template<class TYPE, class ARG_TYPE>
void array_ptr_alloc<TYPE, ARG_TYPE>::set_at_grow(index iIndex, ARG_TYPE t)
{
	ASSERT(iIndex >= 0);

   if(iIndex < m_ptra.get_size())
   {
      this->element_at(iIndex) = t;
   }
   else
   {
      INT_PTR iOldSize = m_ptra.get_size();
      m_ptra.set_size(iIndex + 1);
      INT_PTR iEmptySize = m_ptra.get_size() - 1;
      index i;
      for(i = iOldSize; i < iEmptySize; i++)
      {
         m_ptra.element_at(i) = gen::alloc<TYPE>();
      }
      m_ptra.element_at(i) = gen::alloc<TYPE>(t);
   }
}


///////////////////////////////////////////////////////////////////////////////
//
// Class Name: Base2DArray
//
// Two dimensional base_array
//
///////////////////////////////////////////////////////////////////////////////
template <class TYPE, class ARG_TYPE>
class Base2DArray:
public array_ptr_alloc <base_array <TYPE, ARG_TYPE>, base_array <TYPE, ARG_TYPE>&>
{
public:

   void BubbleSortBySize(bool bAsc = true);
};

template <class TYPE, class ARG_TYPE>
void Base2DArray<TYPE, ARG_TYPE>::
BubbleSortBySize(bool bAsc)
{
    TYPE t;
    if(bAsc)
    {
        for(index i = 0; i < this->get_size(); i++)
        for(index j = i + 1; j < this->get_size(); j++)
        {
            if(this->element_at(i);this->get_size() > this->element_at(j);this->get_size())
            {
                t = this->element_at(i);
                set_at(i, this->element_at(j));
                set_at(j, t);
            }

        }
    }
    else
    {
        for(index i = 0; i < this->get_size(); i++)
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

    return;
}







