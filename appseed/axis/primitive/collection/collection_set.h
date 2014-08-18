#pragma once




template < class TYPE,class ARG_TYPE = const TYPE &,class BASE_ARRAY_TYPE = array < TYPE,ARG_TYPE >,class COMPARE = ::comparison::less < typename TYPE,typename ARG_TYPE > >
class set:
   virtual protected BASE_ARRAY_TYPE
{
public:

   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;
   typedef BASE_ARRAY_TYPE BASE_ARRAY;



   set() { }

#if defined(MOVE_SEMANTICS)

   set(set && a):
      BASE_ARRAY_TYPE(a)
   {

   }

   inline set & operator = (set && a)
   {

      BASE_ARRAY_TYPE::operator = (a);

      return *this;

   }

#endif

   set(const set & a):
      BASE_ARRAY_TYPE(a)
   {

   }


   index add(ARG_TYPE t);

   typename BASE_ARRAY_TYPE::iterator insert(ARG_TYPE t);

   typename BASE_ARRAY_TYPE::const_iterator cend() const;
   typename BASE_ARRAY_TYPE::iterator end();
   typename BASE_ARRAY_TYPE::const_iterator end() const;

   typename BASE_ARRAY_TYPE::const_iterator cbegin() const;
   typename BASE_ARRAY_TYPE::iterator begin();
   typename BASE_ARRAY_TYPE::const_iterator begin() const;

   //::count add(const array <TYPE,ARG_TYPE> & a,index(* fCompare) (TYPE *,TYPE *) = DEFAULT_COMPARE);

   typename BASE_ARRAY_TYPE::const_iterator find(ARG_TYPE value) const;

   typename BASE_ARRAY_TYPE::iterator find(ARG_TYPE value);

   bool search(typename BASE_ARRAY_TYPE::const_iterator & it, ARG_TYPE value) const;

   bool search(typename BASE_ARRAY_TYPE::iterator & it,ARG_TYPE value);

   bool contains(ARG_TYPE t) const;

/*   bool add_unique(ARG_TYPE t,index(* fCompare) (TYPE *,TYPE *) = DEFAULT_COMPARE);

   void quick_sort(index(* fCompare) (TYPE *,TYPE *) = DEFAULT_COMPARE);

   void set_size(::count ca);

   const TYPE & element_at(::index i,index(* fCompare) (TYPE *,TYPE *) = DEFAULT_COMPARE) const;

   TYPE & element_at(::index i,index(* fCompare) (TYPE *,TYPE *) = DEFAULT_COMPARE);

   const TYPE & operator [] (::index i) const;

   TYPE & operator [] (::index i);

   bool operator == (const set & a) const;

   bool operator != (const set & a) const;

   void copy(const BASE_ARRAY & src);

   using BASE_ARRAY::remove_all;

   using BASE_ARRAY::clear;

   using BASE_ARRAY::quick_sort;

   using BASE_ARRAY::operator new;

   using BASE_ARRAY::operator delete;

   using BASE_ARRAY::set_app;

   using BASE_ARRAY::get_size;

   template<class ARRAY>
   friend index lemon::array::sort_add(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index(* fCompare) (typename ARRAY::BASE_TYPE *,typename ARRAY::BASE_TYPE *),index_array & ia);
   */

   inline ::count size() { return get_size();  }
   inline ::count get_count() { return get_size(); }
   inline ::count get_size() { return get_size(); }
   
};

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
typename BASE_ARRAY_TYPE::const_iterator set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::cend() const
{
   return BASE_ARRAY_TYPE::const_iterator(get_count(), this);
}
template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
typename BASE_ARRAY_TYPE::iterator set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::end()
{
   return BASE_ARRAY_TYPE::iterator(get_count(), this);
}
template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
typename BASE_ARRAY_TYPE::const_iterator set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::end() const
{
   return BASE_ARRAY_TYPE::const_iterator(get_count(), this);
}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
typename BASE_ARRAY_TYPE::const_iterator set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::cbegin() const
{
   return BASE_ARRAY_TYPE::const_iterator(0, this);
}
template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
typename BASE_ARRAY_TYPE::iterator set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::begin()
{
   return BASE_ARRAY_TYPE::iterator(0, this);
}
template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
typename BASE_ARRAY_TYPE::const_iterator set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::begin() const
{
   return BASE_ARRAY_TYPE::const_iterator(0, this);
}


template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
index set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
add(ARG_TYPE t)
{

   typename BASE_ARRAY_TYPE::iterator m;

   if(search(m,t))
      return m.m_i;

   insert_at(m.m_i,t);

   return m.m_i;

}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
typename BASE_ARRAY_TYPE::iterator set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >:: insert(ARG_TYPE t)
{
   return BASE_ARRAY_TYPE::iterator(add(t), this);
}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
bool set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
    search(typename BASE_ARRAY_TYPE::const_iterator & m, ARG_TYPE t) const
{

   BASE_ARRAY_TYPE::const_iterator l = cbegin();

   BASE_ARRAY_TYPE::const_iterator u = cend();

   --u;

   while(true)
   {

      m = l.mid(u);

      if(COMPARE::compare(t,*m))
      {
         
         if(m == cbegin())
            break;

         u = m;

         --u;

      }
      else if(COMPARE::compare(*m, t))
      {
         if(m == cend())
            break;

         l = m;

         ++l;

      }
      else
      {
         return m;
      }

   }

   return false;

}


template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
bool set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
search(typename BASE_ARRAY_TYPE::iterator & m, ARG_TYPE t)
{

   BASE_ARRAY_TYPE::iterator l = begin();

   BASE_ARRAY_TYPE::iterator u = end();

   --u;

   while(true)
   {

      m = l.mid(u);

      if(COMPARE::compare(t,*m))
      {

         if(m == begin())
            break;

         u = m;

         --u;

      }
      else if(COMPARE::compare(*m,t))
      {
         if(m == end())
            break;

         l = m;

         ++l;

      }
      else
      {
         return true;
      }

   }

   return false;

}


template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
typename BASE_ARRAY_TYPE::const_iterator set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
find(ARG_TYPE t) const
{
   typename BASE_ARRAY_TYPE::const_iterator m;
   if(search(m,t))
      return m;
   return cend();

}


template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
typename BASE_ARRAY_TYPE::iterator set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
find(ARG_TYPE t)
{

   typename BASE_ARRAY_TYPE::iterator m;
   if(search(m,t))
      return m;
   return end();


}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
bool set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
contains(ARG_TYPE t) const
{
   return find(t) != cend();
}

/*
template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
bool set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
add_unique(ARG_TYPE t,index(* fCompare) (TYPE *,TYPE *))
{
   if(contains(t,fCompare))
      return false;
   add(t,fCompare);
   return true;
}


template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
::index set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
add(ARG_TYPE t,index(* fCompare) (TYPE *,TYPE *))
{

   ::index i = ::lemon::array::sort_add(*this,t,fCompare,defer_update(fCompare));

   m_indexmap.mark_dirty();

   return i;

}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
::count set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
add(const array < TYPE,ARG_TYPE > & a,index(* fCompare) (TYPE *,TYPE *))
{

   ::count ca = sort_add(a,fCompare,defer_update(fCompare));

   m_indexmap.mark_dirty();

   return ca;

}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
::count set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
remove(ARG_TYPE t,index(* fCompare) (TYPE *,TYPE *))
{

   ::count ca = this->sort_remove(t,fCompare,defer_update(fCompare));

   m_indexmap.mark_dirty();

   return ca;

}


template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
void set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
quick_sort(index(* fCompare) (TYPE *,TYPE *))
{

   defer_update(fCompare);

}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
void set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
set_size(::count n)
{

   BASE_ARRAY::allocate(n);

   m_indexmap.mark_dirty();

}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
TYPE & set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
element_at(::index i,index(* fCompare) (TYPE *,TYPE *))
{

   return BASE_ARRAY::element_at(defer_update(fCompare)[i]);

}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
const TYPE & set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
element_at(::index i,index(* fCompare) (TYPE *,TYPE *)) const
{

   return ((set *) this)->element_at(i,fCompare);

}


template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
TYPE & set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
operator [](::index i)
{

   return this->element_at(i);

}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
const TYPE & set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
operator [](::index i) const
{

   return ((set *) this)->operator [](i);

}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
bool set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
operator == (const set & a) const
{

   if(&a == this)
      return true;

   if(get_size() != a.get_size())
      return false;

   index_array & ia1 = ((set *) this)->defer_update();

   index_array & ia2 = ((set *)&a)->defer_update();

   for(index i = 0; i < get_size(); i++)
   {
      if(DEFAULT_COMPARE(&((set *) this)->BASE_ARRAY::element_at(ia1[i]),&((set *)&a)->BASE_ARRAY::element_at(ia2[i])) != 0)
         return false;
   }

   return true;

}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
bool set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::
operator != (const set & a) const
{

   return !this->operator == (a);

}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY_TYPE,class COMPARE>
void set < TYPE,ARG_TYPE,BASE_ARRAY_TYPE,COMPARE >::copy(const BASE_ARRAY & src)
{

   BASE_ARRAY::copy(src);

   m_indexmap.mark_dirty();

}





// smart_pointer_sort_array
#define spsa(T) set < sp(T), const sp(T) &, spa(T) >
*/