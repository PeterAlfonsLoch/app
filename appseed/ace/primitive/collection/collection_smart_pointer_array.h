#pragma once


// Range-based for loop support
// smart_pointer_range indirect/interpreted contribution from
/**
* pugixml parser - version 1.5
* --------------------------------------------------------
* Copyright (C) 2006-2014, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
* Report bugs and download new versions at http://pugixml.org/
*
* This library is distributed under the MIT License. See notice at the end
* of this file.
*
* This work is based on the pugxml parser, which is:
* Copyright (C) 2003, by Kristen Wegner (kristen@tima.net)
*/

template < typename Iterator > class smart_pointer_range
{
public:

   Iterator m_beg;
   Iterator m_end;

   smart_pointer_range(Iterator beg,Iterator end): m_beg(beg),m_end(end)
   {
   }

   Iterator begin()  const { return m_beg; }
   Iterator end()    const { return m_end; }

private:

};


template < class T >
class smart_pointer_array :
   public array < smart_pointer < T > >
{
public:


   class ref_iterator
   {
   public:

      typedef T BASE_TYPE;
      typedef const T & BASE_ARG_TYPE;
      typedef smart_pointer_array BASE_ARRAY;

      index            m_i;
      BASE_ARRAY *     m_parray;

      ref_iterator()
      {
         m_i = 0;
         m_parray = NULL;
      }

      ref_iterator(index i,BASE_ARRAY * parray)
      {
         m_i = i;
         m_parray = parray;
      }

      ref_iterator(const ref_iterator & it)
      {
         operator = (it);
      }


      ref_iterator & operator = (const ref_iterator & it)
      {
         if(this != &it)
         {
            m_i         = it.m_i;
            m_parray    = it.m_parray;
         }
         return *this;
      }

      bool operator == (const ref_iterator & it)
      {
         if(this == &it)
            return true;
         if(m_parray != it.m_parray)
            return false;
         if(m_i >= m_parray->get_size() && it.m_i >= m_parray->get_size())
            return true;
         if(m_i <= 0 && it.m_i <= 0)
            return true;
         return m_i == it.m_i;
      }

      bool operator != (const ref_iterator & it)
      {
         return !operator==(it);
      }

      ref_iterator operator ++(int)
      {
         ref_iterator it = *this;
         operator ++();
         return it;
      }

      ref_iterator operator --(int)
      {
         ref_iterator it = *this;
         operator --();
         return it;
      }

      ref_iterator & operator ++()
      {
         m_i++;
         if(m_i >= m_parray->get_size())
            m_i = m_parray->get_size();
         return *this;
      }

      ref_iterator & operator +(index i)
      {
         m_i += i;
         if(m_i >= m_parray->get_size())
            m_i = m_parray->get_size();
         return *this;
      }

      ref_iterator & operator --()
      {
         m_i--;
         if(m_i < 0)
            m_i = 0;
         return *this;
      }

      ref_iterator mid(const ref_iterator & i) const
      {
         return ref_iterator((m_i + i.m_i + 1) / 2,m_parray);
      }

      ref_iterator & operator -(::count c)
      {
         m_i-=c;
         if(m_i < 0)
            m_i = 0;
         return *this;
      }

      bool operator < (const ref_iterator & i) const
      {

         return m_i < i.m_i;

      }

      ::count get_count() const
      {
         return m_parray->get_count();
      }


      T & operator * ()
      {
         return m_parray->at(m_i);
      }

      const T & operator * () const
      {
         return m_parray->at(m_i);
      }


   };

   typedef smart_pointer_range < ref_iterator > ref_range;


   smart_pointer_array()
   {

   }

   virtual ~smart_pointer_array()
   {

      this->remove_all();

   }

#if defined(MOVE_SEMANTICS)

   smart_pointer_array(smart_pointer_array && a)
   {

      array < smart_pointer < T > >::operator = (a);

   }

   inline smart_pointer_array & operator = (smart_pointer_array && a)
   {

      array < smart_pointer < T > >::operator = (a);

      return *this;

   }

#endif

   smart_pointer_array(const smart_pointer_array & a) :
      array < smart_pointer < T > >(a)
   {

      array < smart_pointer < T > >::operator = (a);

   }

   inline smart_pointer_array & operator = (const smart_pointer_array & a)
   {

      copy(a);

      return *this;

   }


   smart_pointer_array(::ace::application * papp) :
      object(papp),
      array < smart_pointer < T > >(papp)
   {
   }

   sp(T) & add_new()
   {

      sp(T) & sp = array < smart_pointer < T > >::add_new();

      sp.alloc(this->allocer());

      return sp;

   }


   ::count set_size(::count nNewSize, ::count nGrowBy = -1)
   {

      return array < smart_pointer < T > > :: set_size(nNewSize);

   }

   ::count set_size_create(::count nNewSize, ::count nGrowBy = -1)
   {
      index i = this->get_size();
      array < smart_pointer < T > > :: set_size(nNewSize);
      ::count ca = this->get_size();
      for(; i < ca; i++)
      {
         this->element_at(i).alloc(this->allocer());
      }
      return ca;
   }


   template < class DERIVED >
   DERIVED * get(index iStart = 0)
   {

      DERIVED * pderived = NULL;

      for(index i = iStart; i < this->get_count(); i++)
      {

         try
         {

            pderived = dynamic_cast < DERIVED * > (this->element_at(i).m_p);

         }
         catch(...)
         {

         }

         if(pderived != NULL)
            return pderived;

      }

      return NULL;

   }

   template < class DERIVED >
   DERIVED * typed_ptr_at(index iIndex)
   {

      return dynamic_cast < DERIVED * > (this->element_at(iIndex).m_p);

   }

   smart_pointer < T > & add(T * p)
   {

      return array < smart_pointer < T > >::add_new() = p;

   }


   bool add_unique(T * p)
   {

      if(contains(p))
         return false;

      this->add(p);

      return true;

   }

   ::count add_unique(const smart_pointer_array & a)
   {

      ::count c = 0;

      for (index i = 0; i < a.get_count(); i++)
      {

         if (add_unique((T *) a[i]))
            c++;

      }

      return c;

   }

   bool contains(const T * p, index iStart = 0, ::count nCount = -1) const
   {

      return find_first(p, iStart, nCount) >= 0;

   }

   ::index find_first(const T * p, index iStart = 0, ::count nCount = -1) const
   {

      index iEnd;

      if(nCount < 0)
         iEnd = this->get_upper_bound(nCount);
      else
         iEnd = iStart + nCount - 1;

      for(index i = iStart; i <= iEnd; i++)
      {

         if(this->element_at(i).m_p == p)
            return i;

      }

      return -1;

   }


   ::index find_first(const T & t, index (* lpfnCompare)(const T *, const T *), index iStart = 0, ::count nCount = -1) const
   {

      return this->find_first(&t, lpfnCompare, iStart, nCount);

   }


   ::index find_first(const T * p, index (* lpfnCompare)(const T *, const T *), index iStart = 0, ::count nCount = -1) const
   {

      index iEnd;

      if(nCount < 0)
         iEnd = this->get_upper_bound(nCount);
      else
         iEnd = iStart + nCount - 1;

      for(index i = iStart; i <= iEnd; i++)
      {

         if(lpfnCompare(this->element_at(i).m_p, p) == 0)
            return i;

      }

      return -1;

   }

   template < class DERIVED >
   smart_pointer_array & operator -= (DERIVED * p)
   {

      this->remove(dynamic_cast < T * > (p));

      return *this;

   }

   ::count remove(T * p)
   {

      ::count ca = 0;

      index iFind = 0;

      while((iFind = this->find_first(p, iFind)) >= 0)
      {

         ca++;

         this->remove_at(iFind);

      }

      return ca;

   }


   template < typename TYPE >
   ::count remove_type(TYPE *)
   {

      ::count c = 0;

      for (index i = this->get_upper_bound(); i >= 0; i--)
      {

         if (typeid(*this->element_at(i).m_p) == typeid(TYPE))
         {

            this->remove_at(i);

            c++;

         }

      }

      return c;

   }

   // overloaded operator helpers
   const smart_pointer < T > & operator[](index nIndex) const
   {

      return this->array < smart_pointer < T > >::operator[](nIndex);

   }

   smart_pointer < T > & operator[](index nIndex)
   {

      return this->array < smart_pointer < T > >::operator[](nIndex);

   }

   const smart_pointer < T > & sp_at(index nIndex) const
   {

      return this->array < smart_pointer < T > >::element_at(nIndex);

   }


   smart_pointer < T > & sp_at(index nIndex)
   {

      return this->array < smart_pointer < T > >::element_at(nIndex);

   }


   T * ptr_at(index nIndex) const
   {

      return this->sp_at(nIndex);

   }


   T * ptr_at(index nIndex)
   {

      return this->sp_at(nIndex);

   }


   T & at(index nIndex) const
   {

      return *this->ptr_at(nIndex);

   }


   T & at(index nIndex)
   {

      return *this->ptr_at(nIndex);

   }

   const smart_pointer < T > & first_sp(index n = 0) const
   {

      return this->array < smart_pointer < T > >::first(n);

   }


   smart_pointer < T > & first_sp(index n = 0)
   {

      return this->array < smart_pointer < T > >::first(n);

   }


   T * first_ptr(index n = 0) const
   {

      return this->first_sp(n);

   }


   T * first_ptr(index n = 0)
   {

      return this->first_sp(n);

   }


   T & first(index n = 0) const
   {

      return *this->first_ptr(n);

   }


   T & first(index n = 0)
   {

      return *this->first_ptr(n);

   }


   T * last_sp(index n = -1) const
   {

      return this->array < smart_pointer < T > >::last(n);

   }


   smart_pointer < T > & last_sp(index n = -1)
   {

      return this->array < smart_pointer < T > >::last(n);

   }


   T * last_ptr(index n = -1) const
   {

      return this->last_sp(n);

   }


   T * last_ptr(index n = -1)
   {

      return this->last_sp(n);

   }


   T & last(index n = -1) const
   {

      return *last_ptr(n);

   }


   T & last(index n = -1)
   {

      return *this->last_ptr(n);

   }


   const T & operator() (index nIndex) const
   {

      return *this->sp_at(nIndex);

   }


   T & operator() (index nIndex)
   {

      return *this->sp_at(nIndex);

   }



   template < typename PRED >
   T * pred_ptr_first(PRED pred)
   {

      index i = this->pred_find_first(pred);

      if(i < 0)
         return NULL;

      return this->ptr_at(i);

   }



   template < class ARRAY >
   smart_pointer_array & append(const ARRAY * pa)
   {

      ::count c = pa->get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {
         this->add(pa->element_at(i));
      }

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array & append(const sp(ARRAY) & pa)
   {

      ::count c = pa->get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {
         this->add(pa->operator[](i));
      }

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array & append(const ARRAY & a)
   {

      ::count c = a.get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {
         this->add(a.element_at(i));
      }

      return *this;

   }


   smart_pointer_array & append(const smart_pointer_array & a)
   {

      ::count c = a.get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {

         this->add(a.sp_at(i));

      }

      return *this;

   }


   template < class ARRAY >
   smart_pointer_array & append_ptra(const ARRAY * pptra)
   {

      ::count c = pptra->get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {
         this->add(*pptra->operator[](i));
      }

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array & copy(const ARRAY * pa)
   {

      if(pa == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(pa);

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array & copy(const sp(ARRAY) & pa)
   {

      if(pa == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(pa);

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array & copy(const ARRAY & a)
   {

      if(&a == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(a);

      return *this;

   }

   smart_pointer_array & copy(const smart_pointer_array & a)
   {

      if(&a == this)
         return *this;

      this->remove_all();

      this->append(a);

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array & copy_ptra(const ARRAY * pptra)
   {

      if(pptra == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(pptra);

      return *this;

   }

   ref_iterator ref_it(index iStart) { return ref_iterator(iStart,this);  }
   ref_iterator ref_it(index iStart, ::count cCount) { return ref_iterator(iStart + (cCount < 0 ? this->get_count() + cCount + 1 : cCount),this); }

   ref_range refa(index iStart = 0, ::count cCount = -1) { return smart_pointer_range < ref_iterator >(ref_it(iStart),ref_it(iStart, cCount)); }

};




// Range-based for loop support
// smart_pointer_range2 indirect/interpreted contribution from
/**
* pugixml parser - version 1.5
* --------------------------------------------------------
* Copyright (C) 2006-2014, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
* Report bugs and download new versions at http://pugixml.org/
*
* This library is distributed under the MIT License. See notice at the end
* of this file.
*
* This work is based on the pugxml parser, which is:
* Copyright (C) 2003, by Kristen Wegner (kristen@tima.net)
*/

template < typename Iterator > class smart_pointer_range2
{
public:

   Iterator m_beg;
   Iterator m_end;

   smart_pointer_range2(Iterator beg,Iterator end): m_beg(beg),m_end(end)
   {
   }

   Iterator begin()  const { return m_beg; }
   Iterator end()    const { return m_end; }

private:

};


template < class T >
class smart_pointer_array2:
   public array < smart_pointer < T > >
{
public:


   class ref_iterator
   {
   public:

      typedef T BASE_TYPE;
      typedef const T & BASE_ARG_TYPE;
      typedef smart_pointer_array2 BASE_ARRAY;

      index            m_i;
      BASE_ARRAY *     m_parray;

      ref_iterator()
      {
         m_i = 0;
         m_parray = NULL;
      }

      ref_iterator(index i,BASE_ARRAY * parray)
      {
         m_i = i;
         m_parray = parray;
      }

      ref_iterator(const ref_iterator & it)
      {
         operator = (it);
      }


      ref_iterator & operator = (const ref_iterator & it)
      {
         if(this != &it)
         {
            m_i         = it.m_i;
            m_parray    = it.m_parray;
         }
         return *this;
      }

      bool operator == (const ref_iterator & it)
      {
         if(this == &it)
            return true;
         if(m_parray != it.m_parray)
            return false;
         if(m_i >= m_parray->get_size() && it.m_i >= m_parray->get_size())
            return true;
         if(m_i <= 0 && it.m_i <= 0)
            return true;
         return m_i == it.m_i;
      }

      bool operator != (const ref_iterator & it)
      {
         return !operator==(it);
      }

      ref_iterator operator ++(int)
      {
         ref_iterator it = *this;
         operator ++();
         return it;
      }

      ref_iterator operator --(int)
      {
         ref_iterator it = *this;
         operator --();
         return it;
      }

      ref_iterator & operator ++()
      {
         m_i++;
         if(m_i >= m_parray->get_size())
            m_i = m_parray->get_size();
         return *this;
      }

      ref_iterator & operator +(index i)
      {
         m_i += i;
         if(m_i >= m_parray->get_size())
            m_i = m_parray->get_size();
         return *this;
      }

      ref_iterator & operator --()
      {
         m_i--;
         if(m_i < 0)
            m_i = 0;
         return *this;
      }

      ref_iterator mid(const ref_iterator & i) const
      {
         return ref_iterator((m_i + i.m_i + 1) / 2,m_parray);
      }

      ref_iterator & operator -(::count c)
      {
         m_i-=c;
         if(m_i < 0)
            m_i = 0;
         return *this;
      }

      bool operator < (const ref_iterator & i) const
      {

         return m_i < i.m_i;

      }

      ::count get_count() const
      {
         return m_parray->get_count();
      }


      T & operator * ()
      {
         return m_parray->at(m_i);
      }

      const T & operator * () const
      {
         return m_parray->at(m_i);
      }


   };

   typedef smart_pointer_range2 < ref_iterator > ref_range;


   smart_pointer_array2()
   {

   }

   virtual ~smart_pointer_array2()
   {

      this->remove_all();

   }

#if defined(MOVE_SEMANTICS)

   smart_pointer_array2(smart_pointer_array2 && a)
   {

      array < smart_pointer < T > >::operator = (a);

   }

   inline smart_pointer_array2 & operator = (smart_pointer_array2 && a)
   {

      array < smart_pointer < T > >::operator = (a);

      return *this;

   }

#endif

   smart_pointer_array2(const smart_pointer_array2 & a):
      array < smart_pointer < T > >(a)
   {

      array < smart_pointer < T > >::operator = (a);

   }

   inline smart_pointer_array2 & operator = (const smart_pointer_array2 & a)
   {

      copy(a);

      return *this;

   }


   smart_pointer_array2(::ace::application * papp):
      object(papp),
      array < smart_pointer < T > >(papp)
   {
   }

   sp(T) & add_new()
   {

      sp(T) & sp = array < smart_pointer < T > >::add_new();

      sp.alloc(this->allocer());

      return sp;

   }


   ::count set_size(::count nNewSize,::count nGrowBy = -1)
   {

      return array < smart_pointer < T > > :: set_size(nNewSize);

   }

   ::count set_size_create(::count nNewSize,::count nGrowBy = -1)
   {
      index i = this->get_size();
      array < smart_pointer < T > > :: set_size(nNewSize);
      ::count ca = this->get_size();
      for(; i < ca; i++)
      {
         this->element_at(i).alloc(this->allocer());
      }
      return ca;
   }


   template < class DERIVED >
   DERIVED * get(index iStart = 0)
   {

      DERIVED * pderived = NULL;

      for(index i = iStart; i < this->get_count(); i++)
      {

         try
         {

            pderived = dynamic_cast < DERIVED * > (this->element_at(i).m_p);

         }
         catch(...)
         {

         }

         if(pderived != NULL)
            return pderived;

      }

      return NULL;

   }

   template < class DERIVED >
   DERIVED * typed_ptr_at(index iIndex)
   {

      return dynamic_cast < DERIVED * > (this->element_at(iIndex).m_p);

   }

   smart_pointer < T > & add(T * p)
   {

      return array < smart_pointer < T > >::add_new() = p;

   }


   bool add_unique(T * p)
   {

      if(contains(p))
         return false;

      this->add(p);

      return true;

   }

   ::count add_unique(const smart_pointer_array2 & a)
   {

      ::count c = 0;

      for(index i = 0; i < a.get_count(); i++)
      {

         if(add_unique((T *)a[i]))
            c++;

      }

      return c;

   }

   bool contains(const T * p,index iStart = 0,::count nCount = -1) const
   {

      return find_first(p,iStart,nCount) >= 0;

   }

   ::index find_first(const T * p,index iStart = 0,::count nCount = -1) const
   {

      index iEnd;

      if(nCount < 0)
         iEnd = this->get_upper_bound(nCount);
      else
         iEnd = iStart + nCount - 1;

      for(index i = iStart; i <= iEnd; i++)
      {

         if(this->element_at(i).m_p == p)
            return i;

      }

      return -1;

   }


   ::index find_first(const T & t,index(* lpfnCompare)(const T *,const T *),index iStart = 0,::count nCount = -1) const
   {

      return this->find_first(&t,lpfnCompare,iStart,nCount);

   }


   ::index find_first(const T * p,index(* lpfnCompare)(const T *,const T *),index iStart = 0,::count nCount = -1) const
   {

      index iEnd;

      if(nCount < 0)
         iEnd = this->get_upper_bound(nCount);
      else
         iEnd = iStart + nCount - 1;

      for(index i = iStart; i <= iEnd; i++)
      {

         if(lpfnCompare(this->element_at(i).m_p,p) == 0)
            return i;

      }

      return -1;

   }

   template < class DERIVED >
   smart_pointer_array2 & operator -= (DERIVED * p)
   {

      this->remove(dynamic_cast < T * > (p));

      return *this;

   }

   ::count remove(T * p)
   {

      ::count ca = 0;

      index iFind = 0;

      while((iFind = this->find_first(p,iFind)) >= 0)
      {

         ca++;

         this->remove_at(iFind);

      }

      return ca;

   }


   template < typename TYPE >
   ::count remove_type(TYPE *)
   {

      ::count c = 0;

      for(index i = this->get_upper_bound(); i >= 0; i--)
      {

         if(typeid(*this->element_at(i).m_p) == typeid(TYPE))
         {

            this->remove_at(i);

            c++;

         }

      }

      return c;

   }

   // overloaded operator helpers
   T  & operator[](index nIndex) const
   {

      return *this->array < smart_pointer < T > >::operator[](nIndex).m_p;

   }

   T  & operator[](index nIndex)
   {

      return *this->array < smart_pointer < T > >::operator[](nIndex).m_p;

   }

   const smart_pointer < T > & sp_at(index nIndex) const
   {

      return this->array < smart_pointer < T > >::element_at(nIndex);

   }


   smart_pointer < T > & sp_at(index nIndex)
   {

      return this->array < smart_pointer < T > >::element_at(nIndex);

   }


   T * ptr_at(index nIndex) const
   {

      return this->sp_at(nIndex);

   }


   T * ptr_at(index nIndex)
   {

      return this->sp_at(nIndex);

   }


   T & at(index nIndex) const
   {

      return *this->ptr_at(nIndex);

   }


   T & at(index nIndex)
   {

      return *this->ptr_at(nIndex);

   }

   const smart_pointer < T > & first_sp(index n = 0) const
   {

      return this->array < smart_pointer < T > >::first(n);

   }


   smart_pointer < T > & first_sp(index n = 0)
   {

      return this->array < smart_pointer < T > >::first(n);

   }


   T * first_ptr(index n = 0) const
   {

      return this->first_sp(n);

   }


   T * first_ptr(index n = 0)
   {

      return this->first_sp(n);

   }


   T & first(index n = 0) const
   {

      return *this->first_ptr(n);

   }


   T & first(index n = 0)
   {

      return *this->first_ptr(n);

   }


   T * last_sp(index n = -1) const
   {

      return this->array < smart_pointer < T > >::last(n);

   }


   smart_pointer < T > & last_sp(index n = -1)
   {

      return this->array < smart_pointer < T > >::last(n);

   }


   T * last_ptr(index n = -1) const
   {

      return this->last_sp(n);

   }


   T * last_ptr(index n = -1)
   {

      return this->last_sp(n);

   }


   T & last(index n = -1) const
   {

      return *last_ptr(n);

   }


   T & last(index n = -1)
   {

      return *this->last_ptr(n);

   }


   const T & operator() (index nIndex) const
   {

      return *this->sp_at(nIndex);

   }


   T & operator() (index nIndex)
   {

      return *this->sp_at(nIndex);

   }


   template < class ARRAY >
   smart_pointer_array2 & append(const ARRAY * pa)
   {

      ::count c = pa->get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {
         this->add(pa->element_at(i));
      }

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array2 & append(const sp(ARRAY) & pa)
   {

      ::count c = pa->get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {
         this->add(pa->operator[](i));
      }

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array2 & append(const ARRAY & a)
   {

      ::count c = a.get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {
         this->add(a.element_at(i));
      }

      return *this;

   }


   smart_pointer_array2 & append(const smart_pointer_array2 & a)
   {

      ::count c = a.get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {

         this->add(a.sp_at(i));

      }

      return *this;

   }


   template < class ARRAY >
   smart_pointer_array2 & append_ptra(const ARRAY * pptra)
   {

      ::count c = pptra->get_count(); // allow to append to itself one time

      for(index i = 0; i < c; i++)
      {
         this->add(*pptra->operator[](i));
      }

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array2 & copy(const ARRAY * pa)
   {

      if(pa == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(pa);

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array2 & copy(const sp(ARRAY) & pa)
   {

      if(pa == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(pa);

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array2 & copy(const ARRAY & a)
   {

      if(&a == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(a);

      return *this;

   }

   smart_pointer_array2 & copy(const smart_pointer_array2 & a)
   {

      if(&a == this)
         return *this;

      this->remove_all();

      this->append(a);

      return *this;

   }

   template < class ARRAY >
   smart_pointer_array2 & copy_ptra(const ARRAY * pptra)
   {

      if(pptra == dynamic_cast < ARRAY * > (this))
         return *this;

      this->remove_all();

      this->append(pptra);

      return *this;

   }

   ref_iterator ref_it(index iStart) { return ref_iterator(iStart,this); }
   ref_iterator ref_it(index iStart,::count cCount) { return ref_iterator(iStart + (cCount < 0 ? this->get_count() + cCount + 1 : cCount),this); }

   ref_range refa(index iStart = 0,::count cCount = -1) { return smart_pointer_range2 < ref_iterator >(ref_it(iStart),ref_it(iStart,cCount)); }

};






#define spa(TYPE) ::smart_pointer_array < TYPE >
#define spa2(TYPE) ::smart_pointer_array2 < TYPE >
#define xmlspa(TYPE) ::smart_pointer_array < TYPE >

typedef spa(object) object_spa;
