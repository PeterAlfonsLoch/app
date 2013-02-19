#pragma once

template <class TYPE, class ARG_TYPE = const TYPE &>
class array_smart_ptr :
   virtual public base_object
{
public:
	array_smart_ptr();
	virtual ~array_smart_ptr();

   index add(TYPE * p);
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
   count remove(array_smart_ptr < CAST, const CAST & > & a)
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
   array_smart_ptr & operator -= (CAST * pt)
   {
      remove_first(pt);
      return *this;
   }


   count get_size() const;
   countget_count() const;
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

   const TYPE* last_ptr() const;
   TYPE* last_ptr();

   void swap(index iIndex1, index iIndex2);

   template < class a >
   void ptr_copy(a & a)
   {
      remove_all();
      for(index i = 0; i < a.get_count(); i++)
      {
         add(a.ptr_at(i));
      }
   }


   comparable_array < TYPE * > m_ptra;

};
template <class TYPE, class ARG_TYPE>
array_smart_ptr < TYPE, ARG_TYPE >::array_smart_ptr()
{
}

template <class TYPE, class ARG_TYPE>
array_smart_ptr < TYPE, ARG_TYPE >::~array_smart_ptr()
{
   remove_all();
}


template <class TYPE, class ARG_TYPE>
inline index array_smart_ptr < TYPE, ARG_TYPE >::add(TYPE * p)
{
   return m_ptra.add(p);
}


template <class TYPE, class ARG_TYPE>
inline void array_smart_ptr < TYPE, ARG_TYPE >::remove_at(
   index iIndex)
{
   m_ptra.remove_at(iIndex);
}

template <class TYPE, class ARG_TYPE>
inline void array_smart_ptr < TYPE, ARG_TYPE >::remove_all()
{
   m_ptra.remove_all();
}

template <class TYPE, class ARG_TYPE>
inline void array_smart_ptr < TYPE, ARG_TYPE >::remove_last()
{
   remove_at(get_upper_bound());
}

template <class TYPE, class ARG_TYPE>
inline count array_smart_ptr < TYPE, ARG_TYPE >::get_size() const
{
   return m_ptra.get_size();
}

template <class TYPE, class ARG_TYPE>
inline count array_smart_ptr < TYPE, ARG_TYPE >::get_count() const
{
   return m_ptra.get_count();
}

template <class TYPE, class ARG_TYPE>
inline index array_smart_ptr < TYPE, ARG_TYPE >::get_upper_bound() const
{
   return m_ptra.get_upper_bound();
}

template <class TYPE, class ARG_TYPE>
inline bool array_smart_ptr < TYPE, ARG_TYPE >::is_empty() const
{
   return m_ptra.is_empty();
}

template <class TYPE, class ARG_TYPE>
inline TYPE & array_smart_ptr < TYPE, ARG_TYPE >::element_at(index iIndex)
{
   return *m_ptra.element_at(iIndex);
}

template <class TYPE, class ARG_TYPE>
inline const TYPE & array_smart_ptr < TYPE, ARG_TYPE >::element_at(index iIndex) const
{
   return *m_ptra.element_at(iIndex);
}

template <class TYPE, class ARG_TYPE>
   inline  TYPE& array_smart_ptr < TYPE, ARG_TYPE >::
   last_element()
{
   return *m_ptra.element_at(get_upper_bound());
}

template <class TYPE, class ARG_TYPE>
inline const TYPE & array_smart_ptr < TYPE, ARG_TYPE >::
   last_element() const
{
   return *m_ptra.get_at(get_upper_bound());
}

	// overloaded operator helpers
template <class TYPE, class ARG_TYPE>
inline const TYPE & array_smart_ptr < TYPE, ARG_TYPE >::operator[](index iIndex) const
{
   return this->element_at(iIndex);
}
template <class TYPE, class ARG_TYPE>
inline 	TYPE& array_smart_ptr < TYPE, ARG_TYPE >::operator[](index iIndex)
{
   return this->element_at(iIndex);
}


template <class TYPE, class ARG_TYPE>
index array_smart_ptr < TYPE, ARG_TYPE >::
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

template <class TYPE, class ARG_TYPE>
index array_smart_ptr < TYPE, ARG_TYPE >::
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

template <class TYPE, class ARG_TYPE>
index array_smart_ptr < TYPE, ARG_TYPE >::
raw_remove_first(TYPE * pt, index find, index last)
{
   if((find = find_first(pt, find, last)) >= 0)
      remove_at(find);
   return find;
}

template <class TYPE, class ARG_TYPE>
index array_smart_ptr < TYPE, ARG_TYPE >::
raw_remove(TYPE * pt, index find, index last, count countMin, count countMax)
{
   count count = 0;
   if(contains(pt, find, last, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (find = remove_first(pt, find, last)) >= 0)
         count++;
   return count;
}

template <class TYPE, class ARG_TYPE>
bool array_smart_ptr < TYPE, ARG_TYPE >::
contains(TYPE * pt, index find, index last, count countMin, count countMax) const
{
   count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first(pt, find, last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}




template <class TYPE, class ARG_TYPE>
inline void array_smart_ptr < TYPE, ARG_TYPE >::
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

template <class TYPE, class ARG_TYPE>
inline const TYPE* array_smart_ptr < TYPE, ARG_TYPE >::
ptr_at(index index) const
{
   return m_ptra[index];
}

template <class TYPE, class ARG_TYPE>
inline TYPE* array_smart_ptr < TYPE, ARG_TYPE >::
ptr_at(index index)
{
   return m_ptra[index];
}

template <class TYPE, class ARG_TYPE>
inline const TYPE* array_smart_ptr < TYPE, ARG_TYPE >::
last_ptr() const
{
   return m_ptra[get_upper_bound()];
}

template <class TYPE, class ARG_TYPE>
inline TYPE* array_smart_ptr < TYPE, ARG_TYPE >::
last_ptr()
{
   return m_ptra[get_upper_bound()];
}


template <class TYPE, class ARG_TYPE>
inline void array_smart_ptr < TYPE, ARG_TYPE >::
swap(index iIndex1, index iIndex2)
{
   TYPE * pt = m_ptra[iIndex1];
   m_ptra[iIndex1] = m_ptra[iIndex2];
   m_ptra[iIndex2] = pt;
}

