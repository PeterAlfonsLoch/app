#pragma once


#undef new


template <class TYPE, class ARG_TYPE = const TYPE &, class BASE_PTRA = comparable_array < TYPE * > >
class array_ptr_copy :
   public array_del_ptr < TYPE, ARG_TYPE, BASE_PTRA >
{
public:
   array_ptr_copy();
   array_ptr_copy(const array_ptr_copy & a);
   virtual ~array_ptr_copy();

   index add(const TYPE & t);
   index add(TYPE * p);
   inline void insert_at(index iIndex, ARG_TYPE t);

   count add(const array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & base_array);

   void copy(const array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & base_array);

   inline const TYPE & element_at(INT_PTR nIndex) const;
   inline TYPE & element_at(INT_PTR nIndex);

   inline const TYPE & operator[](INT_PTR nIndex) const;
   inline TYPE& operator[](INT_PTR nIndex);

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
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline index array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::add(
   const TYPE & t)
{
   return this->ptra().add(gen::alloc<TYPE>(t));
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline index array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::add(TYPE * p)
{
   return array_del_ptr < TYPE, ARG_TYPE, BASE_PTRA >::add(p);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::insert_at(
   index iIndex,
   ARG_TYPE t)
{
   this->ptra().insert_at(iIndex, gen::alloc<TYPE>(t));
}


template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::operator = (const array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & a)
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


template <class TYPE, class ARG_TYPE, class BASE_PTRA>
void array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::copy(const array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & a)
{
   this->remove_all();
   this->add(a);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
count array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::add(const array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA > & a)
{
   count countOld = this->get_count();
   for(int i = 0; i < a.get_size(); i++)
   {
      this->add(a[i]);
   }
   return countOld;
}


template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline const TYPE & array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::
element_at(INT_PTR nIndex) const
{
   return *((TYPE*) this->ptra().element_at(nIndex));
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline TYPE & array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::
element_at(INT_PTR nIndex)
{
   return *((TYPE*) this->ptra().element_at(nIndex));
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline const TYPE & array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::
operator[](INT_PTR nIndex) const
{
   return this->element_at(nIndex);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline TYPE & array_ptr_copy < TYPE, ARG_TYPE, BASE_PTRA >::
operator[](INT_PTR nIndex)
{
   return this->element_at(nIndex);
}


#define new DEBUG_NEW


