#pragma once

template <class TYPE, class ARG_TYPE = const TYPE &, class BASE_PTRA = comparable_array < TYPE * >>
class array_ptr_copy :
   public array_ptr < TYPE, ARG_TYPE, BASE_PTRA >
{
public:
   array_ptr_copy();
   array_ptr_copy(const array_ptr_copy & a);
   virtual ~array_ptr_copy();

   index add(const TYPE & t);
   index add(TYPE * p);
   inline void insert_at(int iIndex, ARG_TYPE t);

   count add(const array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & base_array);

   void copy(const array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & base_array);

   const TYPE & element_at(INT_PTR nIndex) const;
   TYPE & element_at(INT_PTR nIndex);

   const TYPE & operator[](INT_PTR nIndex) const;
   TYPE& operator[](INT_PTR nIndex);

   array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & operator = (const array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & base_array);
};

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::array_ptr_copy()
{
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::array_ptr_copy(const array_ptr_copy & a)
{
   operator = (a);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::~array_ptr_copy()
{
   remove_all();
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline index array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::add(
   const TYPE & t)
{
   return m_ptra.add(gen::alloc<TYPE>(t));
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline index array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::add(TYPE * p)
{
   return array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::add(p);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::insert_at(
   int iIndex,
   ARG_TYPE t)
{
   m_ptra.insert_at(iIndex, gen::alloc<TYPE>(t));
}


template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::operator = (const array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & a)
{
   if(&a == this)
      return *this;
   int i;
   for(i = 0; i < m_ptra.get_size(); i++)
   {
      element_at(i) = *a.m_ptra[i];
   }
   for(; i < a.m_ptra.get_size(); i++)
   {
      m_ptra.add(gen::alloc<TYPE>(*a.m_ptra[i]));
   }
   m_ptra.set_size(a.m_ptra.get_size());
   return *this;
}


template <class TYPE, class ARG_TYPE, class BASE_PTRA>
void array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::copy(const array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & a)
{
   remove_all();
   add(a);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
count array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::add(const array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & a)
{
   count countOld = get_count();
   for(int i = 0; i < a.get_size(); i++)
   {
      add(a[i]);
   }
   return countOld;
}


template <class TYPE, class ARG_TYPE, class BASE_PTRA>
const TYPE & array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::
element_at(INT_PTR nIndex) const
{
   return *m_ptra.element_at(nIndex);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
TYPE & array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::
element_at(INT_PTR nIndex)
{
   return *m_ptra.element_at(nIndex);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
const TYPE & array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::
operator[](INT_PTR nIndex) const
{
   return element_at(nIndex);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
TYPE & array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::
operator[](INT_PTR nIndex)
{
   return element_at(nIndex);
}
