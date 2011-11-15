#pragma once


template <class TYPE, class ARG_TYPE = const TYPE &, class BASE_PTRA = comparable_array < TYPE * > >
class array_ptr :
   virtual public ::radix::object
{
public:
   array_ptr();
   virtual ~array_ptr();

   index add(TYPE * p);
   index add_unique(TYPE * p);
   void remove_at(index iIndex);
   void remove_all();
   void remove_last();
   index raw_remove_first(TYPE * pt, index find = 0, index last = -1);
   index raw_remove(TYPE * pt, index find = 0, index last = -1, count countMin = 0, count countMax = -1);
   index raw_find_first(TYPE * pt, index find = 0, index last = -1) const;
   index find_first(TYPE & t, int (* lpfnCompare)(TYPE &t1, TYPE &t2), index find = 0, index last = -1) const;
   bool contains(TYPE * pt, index find = 0, index last = -1, count countMin = 0, count countMax = -1) const;

   template < class CAST >
   index remove_first(CAST * pt, index find = 0, index last = -1)
   {
      return raw_remove_first(dynamic_cast < TYPE * > (pt), find, last);
   }

   template < class CAST >
   count remove(CAST * pt, index start = 0, index last = -1)
   {
      return raw_remove(dynamic_cast < TYPE * > (pt), start, last);
   }

   template < class CAST >
   count remove(array_ptr < CAST, const CAST & > & a)
   {
      count count = 0;
      for(index i = 0; i < a.get_count(); i++)
      {
         count += remove(a[i]);
      }
      return count;
   }

   template < class CAST >
   index find_first(CAST * pt, index find = 0, index last = -1) const
   {
      return raw_find_first(dynamic_cast < TYPE * > (pt), find, last);
   }



   void set_size(int iSize);

   template < class CAST >
   array_ptr & operator -= (CAST * pt)
   {
      remove_first(pt);
      return *this;
   }


   count get_size() const;
   count get_count() const;
   index get_upper_bound() const;
   bool is_empty() const;

   const TYPE & element_at(index nIndex) const;
   TYPE & element_at(index nIndex);

   const TYPE & last_element() const;
   TYPE& last_element();

   const TYPE & operator[](index nIndex) const;
   TYPE& operator[](index nIndex);

   const TYPE* ptr_at(index nIndex) const;
   TYPE* ptr_at(index nIndex);

   template < class T > const T * typed_ptr_at(index nIndex) const { return dynamic_cast < const T * > (m_ptra[nIndex]); }
   template < class T > T * typed_ptr_at(index nIndex) { return dynamic_cast < T * > (m_ptra[nIndex]); }

   const TYPE* last_ptr() const;
   TYPE* last_ptr();

   void swap(index iIndex1, index iIndex2);

   template < class A >
   void ptr_copy(A & a)
   {
      remove_all();
      for(index i = 0; i < a.get_count(); i++)
      {
         add(a.ptr_at(i));
      }
   }

   bool has_elements(count countMinimum = 1) const;


   BASE_PTRA m_ptra;

   inline BASE_PTRA & ptra()
   {

      return m_ptra;

   }

   inline const BASE_PTRA & ptra() const
   {

      return m_ptra;

   }

};

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::array_ptr()
{
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::~array_ptr()
{
   remove_all();
}


template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline index array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::add(TYPE * p)
{
   return m_ptra.add(p);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline index array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::add_unique(TYPE * p)
{
   return m_ptra.add_unique(p);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::remove_at(
   index iIndex)
{
   m_ptra.remove_at(iIndex);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::remove_all()
{
   m_ptra.remove_all();
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::remove_last()
{
   remove_at(get_upper_bound());
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline count array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::get_size() const
{
   return m_ptra.get_size();
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline count array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::get_count() const
{
   return m_ptra.get_count();
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline index array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::get_upper_bound() const
{
   return m_ptra.get_upper_bound();
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline bool array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::is_empty() const
{
   return m_ptra.is_empty();
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline TYPE & array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::element_at(index iIndex)
{
   return *m_ptra.element_at(iIndex);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline const TYPE & array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::element_at(index iIndex) const
{
   return *m_ptra.element_at(iIndex);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
   inline  TYPE& array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
   last_element()
{
   return *m_ptra.element_at(get_upper_bound());
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline const TYPE & array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
   last_element() const
{
   return *m_ptra.get_at(get_upper_bound());
}

   // overloaded operator helpers
template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline const TYPE & array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::operator[](index iIndex) const
{
   return this->element_at(iIndex);
}
template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline    TYPE& array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::operator[](index iIndex)
{
   return this->element_at(iIndex);
}


template <class TYPE, class ARG_TYPE, class BASE_PTRA>
index array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
find_first(TYPE & t, int (*lpfnCompare)(TYPE &t1, TYPE &t2), index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find <= last; find++)
   {
      if(lpfnCompare(*m_ptra[find], t) == 0)
         return find;
   }
   return -1;
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
index array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
raw_find_first(TYPE * pt, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find <= last; find++)
   {
      if(m_ptra[find] == pt)
         return find;
   }
   return -1;
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
index array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
raw_remove_first(TYPE * pt, index find, index last)
{
   if((find = find_first(pt, find, last)) >= 0)
      remove_at(find);
   return find;
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
index array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
raw_remove(TYPE * pt, index find, index last, count countMin, count countMax)
{
   count count = 0;
   if(contains(pt, find, last, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (find = remove_first(pt, find, last)) >= 0)
         count++;
   return count;
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
bool array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
contains(TYPE * pt, index find, index last, count countMin, count countMax) const
{
   count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first(pt, find, last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}




template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
set_size(int iSize)
{
   while(this->get_size() < iSize)
   {
      add(NULL);
   }
   while(this->get_size() > iSize)
   {
      remove_at(this->get_size() - 1);
   }
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline const TYPE* array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
ptr_at(index index) const
{
   return m_ptra[index];
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline TYPE* array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
ptr_at(index index)
{
   return m_ptra[index];
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline const TYPE* array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
last_ptr() const
{
   return m_ptra[get_upper_bound()];
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline TYPE* array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
last_ptr()
{
   return m_ptra[get_upper_bound()];
}


template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::
swap(index iIndex1, index iIndex2)
{
   TYPE * pt = m_ptra[iIndex1];
   m_ptra.set_at(iIndex1, m_ptra[iIndex2]);
   m_ptra.set_at(iIndex2, pt);
}



template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline bool array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::has_elements(count countMinimum) const
{
   return m_ptra.has_elements(countMinimum);
}
