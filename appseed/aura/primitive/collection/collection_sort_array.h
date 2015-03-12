#pragma once



template < typename ARG_TYPE >
inline index BaseSortCompare(ARG_TYPE p1,ARG_TYPE p2)
{
   if(p1 > p2)
      return 1;
   else if(p1 < p2)
      return -1;
   else
      return 0;
}

template < typename ARG_TYPE >
inline index BaseNullCompare(ARG_TYPE p1,ARG_TYPE p2)
{
   return 0;
}



template < class TYPE,class ARG_TYPE = const TYPE &,class BASE_ARRAY_TYPE = array < TYPE,ARG_TYPE >,index(* DEFAULT_COMPARE)(ARG_TYPE,ARG_TYPE) = &BaseSortCompare < ARG_TYPE > >
class sort_array :
   virtual protected BASE_ARRAY_TYPE
{
public:

   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;
   typedef BASE_ARRAY_TYPE BASE_ARRAY;


   class sort_index :
      virtual public ::object
   {
   public:


      bool           m_bUpdated;
      index_array    m_indexa;


      sort_index(sort_index && si)
      {

         m_bUpdated = si.m_bUpdated;
         m_indexa = si.m_indexa;

      }

      sort_index()
      {
         m_bUpdated = false;
      }

      virtual ~sort_index()
      {

      }

   };

   class sort_index_map :
      virtual public mapsp(index ( * ) (ARG_TYPE, ARG_TYPE), index ( * ) (ARG_TYPE, ARG_TYPE), sort_index)
   {
   public:

      inline void mark_dirty()
      {

         typename sort_index_map::assoc * passoc = sort_index_map::PGetFirstAssoc();

         while(passoc != NULL)
         {
            passoc->m_element2->m_bUpdated = false;
            passoc = passoc->m_pnext;
         }

      }

   };


   sort_index_map    m_indexmap;

   sort_array() { }

//#if defined(MOVE_SEMANTICS)
//
//   sort_array(sort_array && a) :
//      BASE_ARRAY_TYPE(a)
//   {
//      m_indexmap.copy(a.m_indexmap);
//   }
//
//   inline sort_array & operator = (sort_array && a)
//   {
//
//      BASE_ARRAY_TYPE::operator = (a);
//
//      m_indexmap= a.m_indexmap;
//
//      return *this;
//
//   }
//
//#endif

   sort_array(const sort_array & a)
   {
      copy(a);
   }


   index_array & defer_update(index ( * fCompare ) (ARG_TYPE, ARG_TYPE) = DEFAULT_COMPARE);

   index add(ARG_TYPE t, index ( * fCompare ) (ARG_TYPE, ARG_TYPE) = DEFAULT_COMPARE);

   ::count add(const array <TYPE, ARG_TYPE> & a, index ( * fCompare ) (ARG_TYPE, ARG_TYPE) = DEFAULT_COMPARE);

   ::count remove(ARG_TYPE t, index ( * fCompare ) (ARG_TYPE, ARG_TYPE) = DEFAULT_COMPARE);

   bool find(ARG_TYPE t, index & iIndex, index ( * fCompare ) (ARG_TYPE, ARG_TYPE) = DEFAULT_COMPARE) const;

   bool contains(ARG_TYPE t, index ( * fCompare ) (ARG_TYPE, ARG_TYPE) = DEFAULT_COMPARE) const;

   bool add_unique(ARG_TYPE t, index ( * fCompare ) (ARG_TYPE, ARG_TYPE) = DEFAULT_COMPARE);

   void quick_sort(index(* fCompare) (ARG_TYPE,ARG_TYPE) = DEFAULT_COMPARE);

   void set_size(::count ca);

   const TYPE & element_at (::index i, index ( * fCompare ) (ARG_TYPE, ARG_TYPE) = DEFAULT_COMPARE) const;

   TYPE & element_at (::index i, index ( * fCompare ) (ARG_TYPE, ARG_TYPE) = DEFAULT_COMPARE);

   const TYPE & operator [] (::index i) const;

   TYPE & operator [] (::index i);

   bool operator == (const sort_array & a) const;

   bool operator != (const sort_array & a) const;

   void copy(const BASE_ARRAY & src);

   using BASE_ARRAY::remove_all;

   using BASE_ARRAY::clear;

//   using BASE_ARRAY::quick_sort;

   using BASE_ARRAY::operator new;

   using BASE_ARRAY::operator delete;

   using BASE_ARRAY::set_app;

   using BASE_ARRAY::get_size;

   template<class ARRAY>
   friend index lemon::array::sort_add(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),index_array & ia);

   template<class ARRAY>
   friend index lemon::array::sort_remove(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),index_array & ia);

   template<class ARRAY>
   friend bool lemon::array::binary_search(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index & iIndex,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),index_array & ia);

   template < class ARRAY >
   friend void ::file::array::write(::file::ostream & ostream,const ARRAY & a);

   template < class ARRAY >
   friend void ::file::array::read(::file::istream & ostream,ARRAY & a);


   sort_array & operator = (const sort_array & a)
   {
	   return copy(a);
   }

   sort_array & copy (const sort_array & a)
   {
      if(&a == this)
         return *this;
      BASE_ARRAY_TYPE::operator = ((const BASE_ARRAY_TYPE &)a);
      ::lemon::map::copy(m_indexmap, a.m_indexmap);
      return *this;
   }

   virtual void on_after_read();

};


template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
bool sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
find(ARG_TYPE t, index & iIndex, index ( * fCompare ) (ARG_TYPE, ARG_TYPE)) const
{

   if(this->get_size() == 0)
   {
      return false;
   }

   return ::lemon::array::binary_search(*this, t, iIndex, fCompare, ((sort_array *) this)->defer_update(fCompare));


}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
bool sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
contains(ARG_TYPE t, index ( * fCompare ) (ARG_TYPE, ARG_TYPE)) const
{
   index iIndex = 0;
   return find(t, iIndex, fCompare);
}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
bool sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
add_unique(ARG_TYPE t, index ( * fCompare ) (ARG_TYPE, ARG_TYPE))
{
   if(contains(t, fCompare))
      return false;
   add(t, fCompare);
   return true;
}


template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
::index sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
add(ARG_TYPE t, index ( * fCompare ) (ARG_TYPE, ARG_TYPE))
{

   ::index i = ::lemon::array::sort_add(*this, (BASE_ARG_TYPE) t, fCompare, defer_update(fCompare));

   m_indexmap.mark_dirty();

   return i;

}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
::count sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
add(const array < TYPE, ARG_TYPE > & a, index ( * fCompare ) (ARG_TYPE, ARG_TYPE))
{

   ::count ca = ::lemon::array::sort_add_array(*this,a, fCompare,defer_update(fCompare));

   m_indexmap.mark_dirty();

   return ca;

}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
::count sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
remove(ARG_TYPE t, index ( * fCompare ) (ARG_TYPE, ARG_TYPE))
{

   ::count ca = ::lemon::array::sort_remove(*this, t,fCompare,defer_update(fCompare));

   m_indexmap.mark_dirty();

   return ca;

}


template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
void sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
quick_sort(index(* fCompare) (ARG_TYPE,ARG_TYPE))
{

   defer_update(fCompare);

}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
void sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
set_size(::count n)
{

   BASE_ARRAY::allocate(n);

   m_indexmap.mark_dirty();

}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
TYPE & sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
element_at(::index i, index ( * fCompare ) (ARG_TYPE, ARG_TYPE))
{

   return BASE_ARRAY::element_at(defer_update(fCompare)[i]);

}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
const TYPE & sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
element_at(::index i, index ( * fCompare ) (ARG_TYPE, ARG_TYPE)) const
{

   return ((sort_array *) this)->element_at(i, fCompare);

}


template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
TYPE & sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
operator [](::index i)
{

   return this->element_at(i);

}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
const TYPE & sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
operator [](::index i) const
{

   return ((sort_array *) this)->operator [](i);

}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
bool sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
operator == (const sort_array & a) const
{

   if(&a == this)
      return true;

   if(get_size() != a.get_size())
      return false;

   index_array & ia1 = ((sort_array *) this)->defer_update();

   index_array & ia2 = ((sort_array *) &a)->defer_update();

   for(index i = 0; i < get_size(); i++)
   {
      if(DEFAULT_COMPARE(((sort_array *) this)->BASE_ARRAY::element_at(ia1[i]), ((sort_array *) &a)->BASE_ARRAY::element_at(ia2[i])) != 0)
         return false;
   }

   return true;

}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
bool sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::
operator != (const sort_array & a) const
{

   return !this->operator == (a);

}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY, index ( * DEFAULT_COMPARE)(ARG_TYPE, ARG_TYPE) >
void sort_array < TYPE, ARG_TYPE, BASE_ARRAY, DEFAULT_COMPARE >::copy(const BASE_ARRAY & src)
{

   BASE_ARRAY::copy(src);

   m_indexmap.mark_dirty();

}

template < class TYPE,class ARG_TYPE,class BASE_ARRAY,index(* DEFAULT_COMPARE)(ARG_TYPE,ARG_TYPE) >
void sort_array < TYPE,ARG_TYPE,BASE_ARRAY,DEFAULT_COMPARE >::on_after_read()
{
   m_indexmap.mark_dirty();
}


// smart_pointer_sort_array
#define spsa(T) sort_array < sp(T), const sp(T) &, spa(T) >


using sort_int_ptr_array = sort_array < int_ptr  > ;

