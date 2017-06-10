#pragma once


#include "collection_iterator.h"

#include "collection_iterable.h"


template < typename TYPE >
class array_iterator
{
public:

   typedef TYPE BASE_TYPE;

   TYPE *      m_p;

   array_iterator()
   {
      m_p = NULL;
   }

   array_iterator(TYPE * p)
   {
      m_p = p;
   }

   array_iterator(const array_iterator & it)
   {
      operator = (it);
   }

   bool is_null() const
   {

      return m_p == NULL;

   }

   bool is_set() const
   {

      return !is_null();

   }

   array_iterator & operator = (const array_iterator & it)
   {
      m_p = it.m_p;
      return *this;
   }

   bool operator == (const array_iterator & it)
   {
      return m_p == it.m_p;
   }

   array_iterator & operator ++()
   {
      m_p++;
      return *this;
   }

   array_iterator & operator +=(index i)
   {
      m_p += i;
      return *this;
   }

   array_iterator operator +(index i)
   {
      return m_p + i;
   }


   array_iterator & operator --()
   {
      m_p--;
      return *this;
   }

   array_iterator & operator -=(index i)
   {
      m_p -= i;
      return *this;
   }

   array_iterator operator -(index i)
   {
      return m_p - i;
   }

   index operator -(array_iterator it)
   {
      return m_p - it.m_p;
   }


   array_iterator mid(const array_iterator & it) const
   {
      return m_p + ((it.m_p - m_p + 1) >> 1);
   }

   bool operator < (const array_iterator & it) const
   {

      return m_p < it.m_p;

   }


   bool operator != (const array_iterator & it)
   {

      return !operator==(it);

   }


   array_iterator operator ++(int)
   {

      array_iterator it = *this;
      operator ++();
      return it;

   }


   array_iterator operator --(int)
   {

      array_iterator it = *this;
      operator --();
      return it;

   }


   TYPE & operator * ()
   {

      return *(operator->());

   }

   TYPE & operator * () const
   {

      return *(operator->());

   }


   TYPE * operator -> ()
   {
      return m_p;
   }

   const TYPE * operator -> () const
   {
      return m_p;
   }

};


template < typename TYPE >
class const_array_iterator
{
public:

   typedef const TYPE BASE_TYPE;

   const TYPE *     m_p;

   const_array_iterator()
   {
      m_p = NULL;
   }

   const_array_iterator(const TYPE * p)
   {
      m_p = p;
   }

   const_array_iterator(const array_iterator < TYPE > & it)
   {
      operator = (it);
   }

   const_array_iterator(const const_array_iterator & it)
   {
      operator = (it);
   }


   bool is_null() const
   {

      return m_p == NULL;

   }

   bool is_set() const
   {

      return !is_null();

   }



   const_array_iterator & operator = (const array_iterator < TYPE > & it)
   {
      m_p = it.m_p;
      return *this;
   }

   const_array_iterator & operator = (const const_array_iterator & it)
   {
      m_p = it.m_p;
      return *this;
   }

   bool operator == (const const_array_iterator & it)
   {
      return m_p == it.m_p;
   }

   const_array_iterator & operator ++()
   {
      m_p++;
      return *this;
   }

   const_array_iterator & operator +=(index i)
   {
      m_p += i;
      return *this;
   }
   const_array_iterator & operator +(index i)
   {
      return m_p + i;
   }

   const_array_iterator & operator --()
   {
      m_p--;
      return *this;
   }
   const_array_iterator & operator -=(index i)
   {
      m_p -= i;
      return *this;
   }
   
   const_array_iterator operator -(index i)
   {
      return m_p - i;
   }

   index operator -(array_iterator < TYPE > it)
   {
      return m_p - it.m_p;
   }


   index operator -(const_array_iterator it)
   {
      return m_p - it.m_p;
   }


   const_array_iterator mid(const const_array_iterator & i) const
   {
      return m_p + ((i.m_p - m_p + 1) >> 1);
   }

   bool operator < (const const_array_iterator & i) const
   {
      return m_i < i.m_i;
   }


   bool operator != (const const_array_iterator & it)
   {

      return !operator==(it);

   }


   const_array_iterator operator ++(int)
   {

      const_array_iterator it = *this;
      operator ++();
      return it;

   }


   const_array_iterator operator --(int)
   {

      base_iterator it = *this;
      operator --();
      return it;

   }


   const TYPE & operator * ()
   {

      return *(operator->());

   }

   const TYPE & operator * () const
   {

      return *(operator->());

   }


   const TYPE * operator -> ()
   {
      return m_p;
   }

   const TYPE * operator -> () const
   {
      return m_p;
   }

};







#ifdef LINUX
#include <initializer_list>
#endif


namespace constructor
{


   template < class TYPE >
   class def
   {
   public:

      inline static void construct(void * p)
      {
         ::new(p) TYPE;
      }
      inline static void construct(void * p, ::count c)
      {
         while(c > 0)
         {
            ::new(p) TYPE;
            ((TYPE*&)p)++;
            c--;
         }
      }



   };


   template < class TYPE >
   class zero
   {
   public:

      inline static void construct(void * p)
      {

         ::zero(p, sizeof(TYPE));

      }

      inline static void construct(void * p, ::count c)
      {

         while (c > 0)
         {

            ::zero(p, sizeof(TYPE));

            ((byte*&)p)+=sizeof(TYPE);

            c--;

         }

      }



   };


   template < class TYPE >
   class nodef
   {
   public:

      inline static void construct(void * p)
      {
         UNREFERENCED_PARAMETER(p);
      }
      inline static void construct(void * p, :: count c)
      {
         UNREFERENCED_PARAMETER(p);
         UNREFERENCED_PARAMETER(c);
      }

   };


} // namespace constructor

namespace destructor
{


   template < class TYPE >
   class def
   {
   public:

      inline static void destruct(TYPE * p)
      {
         p->~TYPE();
      }
      inline static void destruct(TYPE * p,::count c)
      {
         while(c > 0)
         {
            p->~TYPE();
            p++;
            c--;
         }
      }



   };





   template < class TYPE >
   class nodef
   {
   public:

      inline static void destruct(TYPE * p)
      {
         UNREFERENCED_PARAMETER(p);
      }
      inline static void destruct(TYPE * p,:: count c)
      {
         UNREFERENCED_PARAMETER(p);
         UNREFERENCED_PARAMETER(c);
      }

   };


} // namespace destructor


namespace copier
{


   template < class TYPE >
   class def
   {
   public:

      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         *pdst = *psrc;

      }

      inline static void copy(TYPE *pdst,const TYPE * psrc, ::count c)
      {

         while(c > 0)
         {
            *pdst = *psrc;
            pdst++;
            psrc++;
            c--;
         }

      }


   };


} // namespace copier


namespace heap
{

   template < class TYPE,class POOL >
   class allocator
   {
   public:

#if MEMDLEAK  || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return (TYPE *)POOL::alloc(sizeof(TYPE) * c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return (TYPE *)POOL::alloc(sizeof(TYPE) * c);

      }
#endif


      inline static void _free(TYPE * p)
      {

         POOL::_free((void *)p);

      }


   };


   template < class TYPE >
   class def:
      public allocator < TYPE,default_memory_allocator>
   {

   };


   template < class TYPE >
   class processor_cache_oriented: // would it help for data-orientation-assumation ??!?!
      public allocator < TYPE,processor_cache_oriented_memory_allocator >
   {


   };


   template < class TYPE >
   class sys :
      public allocator < TYPE, system_memory_allocator>
   {

   };



} // namespace memory


namespace allocator
{


   template < class TYPE >
   class allocator
   {
   public:

      inline static void construct(TYPE * p)
      {
         constructor ::nodef< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p,:: count c)
      {
         constructor ::nodef< TYPE >::construct(p,c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor ::nodef < TYPE >::destruct(p);
      }
      inline static void destruct(TYPE * p,::count c)
      {
         destructor ::nodef < TYPE >::destruct(p,c);
      }


      inline static void copy(TYPE *pdst,const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst,psrc);

      }


      inline static void copy(TYPE *pdst,const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy(pdst,psrc,c);

      }

      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }

   };


   template < class TYPE >
   class def
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor ::def< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p,:: count c)
      {
         constructor ::def< TYPE >::construct(p,c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor ::def< TYPE>::destruct(p);
      }
      inline static void destruct(TYPE * p,::count c)
      {
         destructor ::def< TYPE>::destruct(p,c);
      }


      inline static void copy(TYPE *pdst,const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst,psrc);

      }


      inline static void copy(TYPE *pdst,const TYPE * psrc,::count c)
      {

         copier::def< TYPE >::copy(pdst,psrc,c);

      }

      #if MEMDLEAK  || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
      #else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }

      #endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };

   template < class TYPE >
   class nodef
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor ::nodef< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p,:: count c)
      {
         constructor ::nodef< TYPE >::construct(p,c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor ::nodef< TYPE>::destruct(p);
      }
      inline static void destruct(TYPE * p,::count c)
      {
         destructor ::nodef< TYPE>::destruct(p,c);
      }


      inline static void copy(TYPE *pdst,const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst,psrc);

      }


      inline static void copy(TYPE *pdst,const TYPE * psrc,::count c)
      {

         copier::def< TYPE >::copy(pdst,psrc,c);

      }

      #if MEMDLEAK || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char  * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
      #else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }
      #endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };


   template < class TYPE >
   class zero
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor ::zero< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p,:: count c)
      {
         constructor ::zero< TYPE >::construct(p,c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor ::nodef< TYPE>::destruct(p);
      }
      inline static void destruct(TYPE * p,::count c)
      {
         destructor ::nodef< TYPE>::destruct(p,c);
      }


      inline static void copy(TYPE *pdst,const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst,psrc);

      }


      inline static void copy(TYPE *pdst,const TYPE * psrc,::count c)
      {

         copier::def< TYPE >::copy(pdst,psrc,c);

      }

      #if MEMDLEAK || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
      #else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }
      #endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };

   template < class TYPE >
   class sys
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::def< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p, ::count c)
      {
         constructor::def< TYPE >::construct(p, c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor::def< TYPE>::destruct(p);
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         destructor::def< TYPE>::destruct(p, c);
      }


      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy(pdst, psrc, c);

      }

#if MEMDLEAK || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::sys < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::sys < TYPE >::alloc(c);

      }
#endif

      inline static void _free(TYPE * p)
      {

         heap::sys < TYPE >::_free(p);

      }


   };

} // namespace allocator

// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements
template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE > >
class array_data:
   virtual public ::object
{
public:


   typedef TYPE BASE_TYPE;
   typedef array_iterator < TYPE > iterator;
   typedef const_array_iterator < TYPE > const_iterator;
   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;


   TYPE *         m_pData;    // the actual array of data
   ::count        m_nSize;    // # of elements (upperBound - 1)
   ::count        m_nMaxSize; // MAX allocated
   ::count        m_nGrowBy;  // grow amount


   array_data(::aura::application * papp = NULL, ::count nGrowBy = 0);
   array_data(const array_data & a);
//   array_data(::std::initializer_list < TYPE > l);
//   array_data(::count n);
   array_data(::count n, ARG_TYPE t);
   array_data(array_data && a);
   virtual ~array_data();

   inline ::count get_size() const;
   inline ::count get_size_in_bytes() const;
   inline ::count get_count() const;
   inline ::count get_byte_count() const;
   inline ::count size() const;
   inline ::count count() const;

   inline bool is_empty(::count countMinimum = 1) const;
   inline bool empty(::count countMinimum = 1) const;
   inline bool has_elements(::count countMinimum = 1) const;
   inline index get_upper_bound(index i = -1) const;
   inline index get_lower_bound(index i = -1) const;
   inline bool bounds(index i) const;


   index index_of(const TYPE & type) const
   {

      return index_of(&type);

   }

   index index_of(const TYPE * ptype) const
   {

      return ptype - m_pData;

   }


   inline iterator lower_bound()
   {
      return iterator(&m_pData[get_lower_bound()]);
   }

   inline iterator begin()
   {
      return iterator(m_pData);
   }

   inline iterator end()
   {
      return iterator(&m_pData[get_size()]);
   }

   inline const_iterator lower_bound() const
   {
      return const_iterator(&m_pData[get_lower_bound()]);
   }

   inline iterator upper_bound()
   {
      return iterator(&m_pData[get_upper_bound()]);
   }

   inline const_iterator begin() const
   {
      return const_iterator(m_pData);
   }

   inline const_iterator end() const
   {
      return const_iterator(&m_pData[get_size()]);
   }

   inline const_iterator upper_bound() const
   {
      return const_iterator(&m_pData[get_upper_bound()]);
   }

   void iprepare_first_last(index & first, index & last) const
   {

      if (first < 0)
      {

         first = m_nSize <= 0 ? 0 : m_nSize + (first % m_nSize) + 1;

      }

      if (last < 0)
      {

         last = m_nSize <= 0 ? 0 : m_nSize + (last % m_nSize) + 1;

      }

   }

   
   void riprepare_first_last(index & first, index & last) const
   {

      if (first < 0)
      {

         first = m_nSize <= 0 ? 0 : m_nSize + (first % m_nSize);

      }

      if (last < 0)
      {

         last = m_nSize <= 0 ? 0 : m_nSize + (last % m_nSize);

      }

   }


   void iprepare_first_count(index & first, ::count & count) const
   {

      if (first < 0)
      {

         first = m_nSize <= 0 ? 0 : m_nSize + (first % m_nSize) + 1;

      }

      if (count < 0)
      {

         count = m_nSize <= 0 ? 0 : (m_nSize + (count % m_nSize) + 1);

      }
      else
      {

         count += first;

      }

   }


   void prepare_first_last(iterator & first, iterator & last) const
   {

      if (first.is_null())
      {

         first.m_p = m_pData;

      }

      if (last.is_null())
      {

         last.m_p = m_pData + m_nSize;

      }

   }

   void prepare_first_last(const_iterator & first, const_iterator & last) const
   {

      if (first.is_null())
      {

         first.m_p = m_pData;

      }

      if (last.is_null())
      {

         last.m_p = m_pData + m_nSize;

      }

   }


   void rprepare_first_last(iterator & first, iterator & last) const
   {

      if (first.is_null())
      {

         first.m_p = m_pData + m_nSize - 1;

      }

      if (last.is_null())
      {

         last.m_p = m_pData - 1;

      }

   }

   void rprepare_first_last(const_iterator & first, const_iterator & last) const
   {

      if (first.is_null())
      {

         first.m_p = m_pData + m_nSize - 1;

      }

      if (first.is_null())
      {

         last.m_p = m_pData - 1;

      }

   }

   bool valid_iter(iterator current, iterator end) const
   {

      return current.m_p < end.m_p;

   }

   bool valid_iter(const_iterator current, const_iterator end) const
   {

      return current.m_p < end.m_p;

   }

   bool rvalid_iter(iterator current, iterator end) const
   {

      return current.m_p > end.m_p;

   }

   bool rvalid_iter(const_iterator current, const_iterator end) const
   {

      return current.m_p > end.m_p;

   }


   TYPE & element_at(index i)  { return m_pData[i]; }
   const TYPE & element_at(index i) const { return m_pData[i]; }


   ::count set_size(index nNewSize,::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count allocate(index nNewSize,::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count allocate_in_bytes(index nNewSize,::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count set_raw_size(index nNewSize,::count nGrowBy = -1); // does not call constructors and destructors on items/elements
   ::count resize(index nNewSize,::count nGrowBy = -1); // does not call default constructors on new items/elements
   void free_extra();
   virtual void destroy();

   void zero(index iStart = 0, ::count c = -1);

   void _001RemoveIndexes(index_array & ia);
   void remove_indexes(const index_array & ia);
   void remove_descending_indexes(const index_array & ia);


   //inline void remove_last();
   inline ::count remove_all();
   inline void clear();


   void on_construct_element(TYPE * p) { ALLOCATOR::construct(p); }
   void on_construct_element(TYPE * p,::count c) { ALLOCATOR::construct(p,c); }
   void on_destruct_element(TYPE * p) { ALLOCATOR::destruct(p); }
   void on_copy_element(index i,const TYPE * p) { ALLOCATOR::copy(&m_pData[i],p); }




   index insert_at(index nIndex, const TYPE & newElement,::count nCount = 1);
   index remove_at(index nIndex, ::count nCount = 1);

   template < typename ITERABLE2 >
   index insert_iter_at(index nStartIndex, const ITERABLE2 & iterable, typename ITERABLE2::const_iterator first = NULL, typename ITERABLE2::const_iterator last = NULL);


   //virtual ::count append(const array_data & src); // return old size
   //virtual void copy(const array_data & src);

   virtual void on_after_read();

   template < typename PRED >
   void pred_each(PRED pred, index first = 0, ::count count = -1)
   {
      
      iprepare_first_count(first, count);

      for (; first < count; first++)
      {

         pred(m_pData[first]);

      }

   }

   template < typename PRED >
   index pred_find_first(PRED pred, index first = 0, index count = -1)
   {

      iprepare_first_count(first, count);

      for(; i < count; first++)
      {

         if(pred(m_pData[first]))
         {

            return first;

         }

      }

      return -1;

   }


   template < typename PRED >
   index pred_find_last(PRED pred, index first = -1, index last = 0)
   {

      riprepare_first_last(first, last);

      for (index i = last; i >= 0; i--)
      {

         if (pred(m_pData[i]))
         {

            return i;

         }

      }

      return -1;

   }

   template < typename PRED >
   TYPE * pred_get_first(PRED pred, index first = 0, index last = -1)
   {

      index i = pred_find_first(pred, first, count);

      if (i < 0)
      {

         return NULL;

      }

      return m_pData[i];

   }


   template < typename PRED >
   ::count pred_get_count(PRED pred, index first = 0, ::count count = -1)
   {

      ::count c = 0;

      iprepare_first_count(first, count);

      for (; first < count; first++)
      {

         if (pred(m_pData[first]))
         {

            c++;

         }

      }

      return c;

   }


   template < typename PRED >
   ::count pred_remove(PRED pred, index first = 0, ::count count = -1)
   {

      ::count c = 0;

      iprepare_first_count(first, count);

      for (; first < count; first++)
      {

         if(pred(m_pData[i]))
         {
            
            c++;

            index start = first;

            ::count remove = 1;

            first++;

            for(; i < count;)
            {

               if(!pred(m_pData[first]))
               {

                  break;

               }

               remove++;

               first++;

            }

            remove_at(start,remove);

            first = start;

         }

      }

      return c;

   }

   template < typename PRED >
   bool pred_add_unique(TYPE t, PRED pred, index first = 0, ::count count = -1)
   {

      if(pred_contains(pred, first, count))
      {

         return false;

      }

      this->add(t);

      return true;

   }


   template < typename PRED >
   bool each(PRED pred, index first = 0, ::count count = -1)
   {

      for_each(pred, first, count);

   }

   template < typename ITERABLE >
   void slice(ITERABLE & iterable, index i, ::count count = -1);

   template < typename ITERABLE2 >
   void splice(iterator i, ITERABLE2 & iterable2)
   {

      insert_iter_at(i.m_p - m_pData, iterable2);

      iterable2.remove_all();

   }

   template < typename ITERABLE2 >
   void splice(iterator i, ITERABLE2 & iterable2, typename ITERABLE2::iterator first)
   {

      insert_at(i.m_p - m_pData, *first);

      iterable2.erase(first);

   }

   template < typename ITERABLE2 >
   void splice(iterator i, ITERABLE2 & iterable2, typename ITERABLE2::iterator first, typename ITERABLE2::iterator last)
   {

      insert_iter_at(i.m_p - m_pData, iterable2, first, last);

      iterable.erase(first, last);

   }

   template < typename TYPE >
   iterator find_first_iter(const TYPE & t, iterator first = NULL, iterator last = NULL)
   {

      return ::iter::find_first(*this, t, first, last);

   }

   template < typename TYPE >
   const_iterator find_first_iter(const TYPE & t, const_iterator first = NULL, const_iterator last = NULL)
   {

      return ::iter::find_first(*this, t, first, last);

   }

   template < typename TYPE >
   index find_first(const TYPE & t, index first = 0, index count = -1) const
   {

      iprepare_first_count(first, count);

      for (; first < count; first++)
      {

         if (m_pData[first] == t)
         {

            return first;

         }

      }

      return -1;

   }

   template < typename TYPE >
   bool contains(const TYPE & t, index first = 0, index last = -1) const
   {

      return find_first(t, first, last) >= 0;

   }

   template < typename TYPE >
   ::count remove(const TYPE & t, index first = 0, index count = -1)
   {

      ::count c = 0;

      iprepare_first_count(first, count);

      for (; first < count;first++)
      {

         if (m_pData[first] == t)
         {

            c++;

            index start = first;

            ::count remove = 1;

            first++;

            for (; first < count;)
            {

               if (!(m_pData[first] == t))
               {

                  break;

               }

               remove++;

               first++;

            }

            remove_at(start, remove);

            first = start;
         }

      }

      return c;

   }

   template < typename TYPE >
   index find_first_ci(const TYPE & t, index first = 0, index count = -1) const
   {

      iprepare_first_count(first, count);

      for (; first < count; first++)
      {

         if (stricmp(m_pData[first], t) == 0)
         {

            return first;

         }

      }

      return -1;

   }

   template < typename TYPE >
   bool contains_ci(const TYPE & t, index first = 0, index last = -1) const
   {

      return find_first_ci(t, first, last) >= 0;

   }


   template < typename TYPE >
   ::count remove_ci(const TYPE & t, index first = 0, index count = -1)
   {

      ::count c = 0;

      iprepare_first_count(first, count);

      for (; first < count; first++)
      {

         if (stricmp(m_pData[first], t) == 0)
         {

            c++;

            index start = first;

            ::count remove = 1;

            first++;

            for (; first < count;)
            {

               if (stricmp(m_pData[first], t))
               {

                  break;

               }

               remove++;

               first++;

            }

            remove_at(start, remove);

            first = start;
         }

      }

      return c;

   }






   inline const TYPE& get_at(index nIndex) const;
   inline TYPE& get_at(index nIndex);
   inline void set_at(index nIndex, ARG_TYPE newElement);

   //inline const TYPE & element_at(index nIndex) const;
   //inline TYPE & element_at(index nIndex);

   inline TYPE & first(index n = 0);
   inline const TYPE & first(index n = 0) const;

   inline TYPE & last(index n = -1);
   inline const TYPE & last(index n = -1) const;

   inline const TYPE* get_data() const;
   inline TYPE* get_data();


   inline iterator add(ARG_TYPE newElement);
   inline iterator add(const array_data& src);
   inline iterator append(const array_data& src);
   inline void copy(const array_data& src);

   inline TYPE & add_new();
   inline index add_new(::count count);

   index get_random_index() const;

   TYPE & random_element();

   const TYPE & random_element() const;

   TYPE pop_random_element();

   TYPE pop(index i = -1);
   inline index push(ARG_TYPE newElement, index i = 0);
   inline void pop_back(index index = -1);
   inline void push_back(ARG_TYPE newElement, index = 0);



   inline iterator erase(iterator pos);
   inline iterator erase(iterator first, iterator last);
   inline iterator erase_count(iterator first, ::count c);


   // overloaded operator helpers
   inline const TYPE& operator[](index nIndex) const;
   inline TYPE& operator[](index nIndex);

   // Operations that move elements around
   //inline index insert_at(index nIndex, ARG_TYPE newElement, ::count nCount = 1);
   //void _001RemoveIndexes(index_array & ia);
   //void remove_indexes(const index_array & ia); // remove indexes from index array upper bound to index array lower bound
   //void remove_descending_indexes(const index_array & ia); // remove indexes from index array lower bound to index array upper bound
   //index insert_at(index nStartIndex, array* pNewArray);
   inline void iswap(index index1, index index2);
   inline void swap(iterator index1, iterator index2);

   inline array_data & operator = (const array_data & src);
   inline array_data & operator = (array_data && a);
   inline array_data & move(array_data && a);


   //inline index find_first(ARG_TYPE t, index (* lpfnCompare)(ARG_TYPE, ARG_TYPE), index start = 0, index last = -1) const;
   //index raw_find_first(TYPE * pt, index first = 0, index last = -1) const;

   //template < class DERIVED >
   //inline index find_first(DERIVED * pt, index first = 0, index last = -1)
   //{
   //   return raw_find_first(dynamic_cast < TYPE * > (pt), first, last);
   //}


   //void quick_sort(index (* fCompare)(TYPE *, TYPE *));
   //void quick_sort(index (* fCompare)(TYPE *, TYPE *), void (* fSwap)(TYPE *, TYPE *));
   //void quick_sort(index (* fCompare)(TYPE *, TYPE *), index_array & ia);
   //bool binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *)) const;

   //bool binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia) const;
   //index sort_add(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);
   //::count sort_add(const array < TYPE, ARG_TYPE > & a, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);
   //index sort_remove(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);

   operator TYPE *() { return this->m_pData; }
   operator const TYPE *() const { return this->m_pData; }
   operator count() const { return this->get_count(); }

   inline array_data & operator += (const array_data & a);
   inline array_data operator + (const array_data & a) const;

   void dump(dump_context &) const;
   void assert_valid() const;

   //inline array & move(array && a);

   inline void set_at_grow(index nIndex, ARG_TYPE newElement);

   inline TYPE & element_at_grow(index nIndex);

   template < typename... T >
   void fadd(T... a)
   {

      add(TYPE(a...));

   }

   index iterator_index(iterator it)
   {
      return index_of(it.m_p);
   }

   index iterator_index(const_iterator it) const
   {
      return index_of(it.m_p);
   }


   void provision(iterator first, iterator last)
   {

      iprovision(iterator_index(first), iterator_index(last) - iterator_index(first) + 1);

   }

   void iprovision(index first, ::count count)
   {

      set_size(get_size() + count, MAX(m_nGrowBy, count));

   }

   void remove_first()
   {

      remove_at(0);

   }


   void remove_last()
   {

      remove_at(get_upper_bound());

   }


   TYPE pop_first()
   {

      TYPE t = first();

      remove_first();

      return t;

   }


   TYPE pop_last()
   {

      TYPE t = last();

      remove_last();

      return t;

   }
};


template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE > >
class array :
   public iterable < ::array_data < TYPE, ARG_TYPE, ALLOCATOR > >
{
public:


   array(::aura::application * papp = NULL, ::count nGrowBy = 0);
   array(const array & a);
   array(::std::initializer_list < TYPE > l);
   array(::count n);
   array(::count n, ARG_TYPE t);
   array(array && a);

   array & operator = (const array & a);


};


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > & array < TYPE, ARG_TYPE, ALLOCATOR >::operator = (const array & a)
{

   if (this != &a)
   {

      ::iter::copy(*this, a);

   }

   return *this;

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::array(::aura::application * papp, ::count nGrowBy) :
   object(papp)
{
   
   m_nGrowBy = nGrowBy;

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::array(const array & a) :
   object(a)
{

   ::iter::copy(*this, a);

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::array(::std::initializer_list < TYPE > l)
{

   ::iter::add_iter(*this, l);

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::array(::count n)
{

   allocate(n);

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::array(::count n, ARG_TYPE t)
{


}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::array(array && a) :
   iterable < ::array_data < TYPE, ARG_TYPE, ALLOCATOR > >(::move(a))
{


}


template < class TYPE, class ARG_TYPE = const TYPE & >
class nodefctr_array :
   public array < TYPE, ARG_TYPE, ::constructor::nodef < TYPE > >
{
public:


   nodefctr_array(::aura::application * papp = NULL, ::count nGrowBy = 32) : array < TYPE, ARG_TYPE, ::constructor::nodef < TYPE > > (papp, nGrowBy) {}
   nodefctr_array(const array <TYPE, ARG_TYPE> & a) : array < TYPE, ARG_TYPE, ::constructor::nodef < TYPE >  > (a) {}
   nodefctr_array(::count n) : array < TYPE, ARG_TYPE, ::constructor::nodef < TYPE > > (n){}
   virtual ~nodefctr_array() {}

};






template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline index array_data < TYPE, ARG_TYPE, ALLOCATOR >::get_random_index() const
{
   
   if (this->get_size() <= 0)
      return -1;

   return (index)(rand() % get_size());

}



template < class TYPE, class ARG_TYPE, class ALLOCATOR >
TYPE & array_data < TYPE, ARG_TYPE, ALLOCATOR >::random_element()
{
   if (this->get_size() <= 0)
      throw "invalid call";
   return this->element_at(get_random_index());
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
const TYPE & array_data < TYPE, ARG_TYPE, ALLOCATOR >::random_element() const
{
   if (this->get_size() <= 0)
      throw "invalid call";
   return this->element_at(get_random_index());
}



template < class TYPE, class ARG_TYPE, class ALLOCATOR >
TYPE array_data < TYPE, ARG_TYPE, ALLOCATOR > ::pop_random_element()
{
   
   if (this->get_size() <= 0)
      throw "invalid call";
   
   index i = get_random_index();
   
   TYPE type = this->element_at(i);
   
   this->remove_at(i);

   return type;

}




template < class TYPE, class ARG_TYPE, class ALLOCATOR >
TYPE array_data < TYPE, ARG_TYPE, ALLOCATOR > ::pop(index i)
{

   i = get_upper_bound(i);

   TYPE strRet = this->element_at(i);

   this->remove_at(i);

   return strRet;

}



//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//template < typename ITERABLE >
//void array_data < TYPE, ARG_TYPE, ALLOCATOR > ::isplice(const ITERABLE & iterable, index iOffset, ::count count)
//{
//
//   remove(iOffset, count);
//
//   insert_iter_at(iOffset, iterable);
//
//}



//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//template < typename ITERABLE, typename ITERABLE2 >
//void array_data < TYPE, ARG_TYPE, ALLOCATOR > ::splice(const ITERABLE & iterable, index iOffset, ITERABLE2 & iterableRemoved, ::count count)
//{
//
//   slice(iterableRemoved, iOffset, count);
//
//   remove(iOffset, count);
//
//   insert_at(iOffset, iterable);
//
//}




template < typename TYPE >
::file::ostream & operator << (::file::ostream & ostream, const array < TYPE > & a)
{
   ostream.write_arbitrary(a.m_nSize);
   for (int32_t i = 0; i < a.get_size(); i++)
   {
      ostream << a.element_at(i);
   }
   return ostream;
}


template < typename TYPE >
::file::istream & operator >> (::file::istream & istream, array < TYPE > & a)
{

   if (istream.fail())
   {

      return istream;

   }

   ::count iSize;

   istream.read_arbitrary(iSize);

   if (istream.fail())
   {

      return istream;

   }

   ::count cOldSize = a.get_size();

   a.set_size(cOldSize + iSize);

   ::count cNewSize = a.get_size();

   for (int32_t i = cOldSize; i < cNewSize; i++)
   {

      istream >> a.element_at(i);

      if (istream.fail())
      {

         return istream;

      }

   }

   return istream;

}


