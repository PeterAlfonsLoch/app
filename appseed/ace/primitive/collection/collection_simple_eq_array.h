#pragma once

template < class TYPE, class ARG_TYPE = const TYPE &, class ARRAY_TYPE = array < TYPE, ARG_TYPE > >
class simple_eq_array :
   virtual public ARRAY_TYPE
{
public:
   simple_eq_array();
   simple_eq_array(const simple_eq_array & array);

   index find_first(const TYPE &t, index find = 0, index last = -1) const;
   countget_count() const;
   bool contains(const TYPE & t, index start = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;
   index remove(const TYPE & t, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);
   ::count remove(const simple_eq_array & a);


   // add
   bool add_unique(ARG_TYPE t);



};

template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
simple_eq_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
simple_eq_array()
{
}
template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
simple_eq_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
simple_eq_array(const simple_eq_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE> & a) :
ARRAY_TYPE(a)
{
   operator = (a);
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
index simple_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
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
inline ::count simple_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
this->get_count() const
{
   return ARRAY_TYPE::get_count();
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
bool simple_eq_array < TYPE, ARG_TYPE, ARRAY_TYPE >::
contains(const TYPE & t, index find, index last, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first(t, find, last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
bool simple_eq_array<TYPE, ARG_TYPE, ARRAY_TYPE>::add_unique(ARG_TYPE t)
{
	if(contains(t))
      return false;
	add(t);
	return true;
}


template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
index simple_eq_array < TYPE, ARG_TYPE , ARRAY_TYPE >::
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
index simple_eq_array < TYPE, ARG_TYPE , ARRAY_TYPE >::
remove(const simple_eq_array & a)
{
   ::count count = 0;
   for(index i = 0; i < a.get_count(); i++)
   {
      count += remove(a[i]);
   }
   return count;
}
