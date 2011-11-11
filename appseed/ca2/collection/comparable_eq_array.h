#pragma once


template < class TYPE, class ARG_TYPE = const TYPE&, class ARRAY_TYPE = base_array < TYPE, ARG_TYPE > >
class comparable_eq_array :
   virtual public ARRAY_TYPE
{
public:
   comparable_eq_array();
   comparable_eq_array(const comparable_eq_array & base_array);

   index find_first(const TYPE &t, index find = 0, index last = -1) const;
   ::count get_count() const;
   ::count get_count(const TYPE & t, index start = 0, index last = -1, ::count countMax = -1) const;
   bool contains(const TYPE & t, index start = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;
   index remove_first(const TYPE & t, index find = 0, index last = -1);
   index remove(const TYPE & t, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);
   typename ARRAY_TYPE::iterator erase(typename ARRAY_TYPE::iterator it);
   typename ARRAY_TYPE::iterator erase(typename ARRAY_TYPE::iterator first, typename ARRAY_TYPE::iterator last);
   index erase(const TYPE & t, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);
   ::count remove(const comparable_eq_array & a);



   // add
   bool add_unique(ARG_TYPE t);


   // Set
   void merge(const comparable_eq_array & a);
   void intersect(const comparable_eq_array & a);

   // Set operators
   comparable_eq_array< TYPE, ARG_TYPE, ARRAY_TYPE > & operator -= (const TYPE & t);
   comparable_eq_array< TYPE, ARG_TYPE, ARRAY_TYPE > & operator &= (const comparable_eq_array< TYPE, ARG_TYPE, ARRAY_TYPE > & a);
   comparable_eq_array< TYPE, ARG_TYPE, ARRAY_TYPE > & operator -= (const comparable_eq_array< TYPE, ARG_TYPE, ARRAY_TYPE > & a);
   comparable_eq_array< TYPE, ARG_TYPE, ARRAY_TYPE > & operator |= (const comparable_eq_array< TYPE, ARG_TYPE, ARRAY_TYPE > & a);

   comparable_eq_array< TYPE, ARG_TYPE, ARRAY_TYPE > operator -(const comparable_eq_array< TYPE, ARG_TYPE, ARRAY_TYPE > & a) const;

   bool operator == (const comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a);
   bool operator != (const comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a);


};

template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
comparable_eq_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
comparable_eq_array()
{
}
template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
comparable_eq_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
comparable_eq_array(const comparable_eq_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE> & a) :
ARRAY_TYPE(a)
{
   operator = (a);
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
index comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
find_first(const TYPE & t, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find <= last; find++)
   {
      if(this->element_at(find) == t)
         return find;
   }
   return -1;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
inline ::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
get_count() const
{
   return ARRAY_TYPE::get_count();
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
::count comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
get_count(const TYPE & t, index find, index last, ::count countMax) const
{
   ::count count = 0;
   while((countMax >= 0 && count <= countMax)
      && (find = find_first(t, find, last)) >= 0)
      count++;
   return count;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
bool comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
contains(const TYPE & t, index find, index last, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first(t, find, last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
bool comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE>::add_unique(ARG_TYPE t)
{
   if(contains(t))
      return false;
   add(t);
   return true;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
void comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE>::
intersect(const comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE> & a)
{
   for(INT_PTR i = 0; i < this->get_size();)
   {
      if(a.contains(this->element_at(i)))
      {
         i++;
      }
      else
      {
         this->remove_at(i);
      }
   }
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
void comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE>::
merge(const comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE> & a)
{
   for(INT_PTR i = 0; i < a.get_size(); i++)
   {
      if(!contains(a.element_at(i)))
      {
         add(a.element_at(i));
      }
   }
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
inline comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE> &  comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE>::
operator &= (const comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE> & a)
{
   intersect(a);
   return *this;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
inline comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE> &  comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE>::
operator -= (const TYPE & t)
{
   remove(t);
   return *this;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
inline comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE> &  comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE>::
operator -= (const comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE> & a)
{
   remove(a);
   return *this;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
inline comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE> comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE>::
operator - (const comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE> & a) const
{
   comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE> aRet(*this);
   aRet.remove(a);
   return aRet;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
inline comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE> &  comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE>::
operator |= (const comparable_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE> & a)
{
   merge(a);
   return *this;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
index comparable_eq_array < TYPE, ARG_TYPE , ARRAY_TYPE >::
remove_first(const TYPE & t, index find, index last)
{
   if((find = find_first(t, find, last)) >= 0)
   {
      try
      {
         this->remove_at(find);
      }
      catch(...)
      {
      }
   }
   return find;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
::count comparable_eq_array < TYPE, ARG_TYPE , ARRAY_TYPE >::
remove(const TYPE & t, index find, index last, ::count countMin, ::count countMax)
{
   ::count count = 0;
   if(contains(t, find, last, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (find = remove_first(t, find, last)) >= 0)
         count++;
   return count;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
::count comparable_eq_array < TYPE, ARG_TYPE , ARRAY_TYPE >::
erase(const TYPE & t, index find, index last, ::count countMin, ::count countMax)
{
   return remove(t, find, last, countMin, countMax);
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
typename ARRAY_TYPE::iterator comparable_eq_array < TYPE, ARG_TYPE , ARRAY_TYPE >::
erase(typename  ARRAY_TYPE::iterator it)
{
   return ARRAY_TYPE::erase(it);
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
typename ARRAY_TYPE::iterator comparable_eq_array < TYPE, ARG_TYPE , ARRAY_TYPE >::
erase(typename ARRAY_TYPE::iterator first, typename ARRAY_TYPE::iterator last)
{
   return ARRAY_TYPE::erase(first, last);
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
index comparable_eq_array < TYPE, ARG_TYPE , ARRAY_TYPE >::
remove(const comparable_eq_array & a)
{
   ::count count = 0;
   for(index i = 0; i < a.get_count(); i++)
   {
      count += remove(a[i]);
   }
   return count;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
bool comparable_eq_array < TYPE, ARG_TYPE , ARRAY_TYPE >::operator == (const comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a)
{
   if(this->get_size() != a.get_size())
      return false;
   for(index i = 0; i < this->get_size(); i++)
   {
      if(!(this->element_at(i) == a.element_at(i)))
         return false;
   }
   return true;
}

template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
bool comparable_eq_array < TYPE, ARG_TYPE , ARRAY_TYPE >::operator != (const comparable_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a)
{
   return !operator==(a);
}
