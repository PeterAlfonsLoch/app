#pragma once


template < typename T > class numeric_array;
typedef CLASS_DECL_AURA numeric_array < index > index_array;
typedef CLASS_DECL_AURA numeric_array < count > count_array;



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
template < class TYPE, class ALLOCATOR = allocator::nodef < TYPE > >
class array_base:
   virtual public ::object
{
public:

   typedef TYPE BASE_TYPE;


   //bool           m_bRaw;     // if raw, does not call destructors or constructors
   TYPE *         m_pData;    // the actual array of data
   ::count        m_nSize;    // # of elements (upperBound - 1)
   ::count        m_nMaxSize; // MAX allocated
   ::count        m_nGrowBy;  // grow amount

   array_base(int iTypeSize,bool bRaw);
   array_base(::aura::application * papp,int iTypeSize,bool bRaw);
   virtual ~array_base();

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


   TYPE * element_at(index i) const { return &m_pData[i]; }


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


   inline void remove_last();
   inline ::count remove_all();
   inline void clear();


   void on_construct_element(TYPE * p) { ALLOCATOR::construct(p); }
   void on_construct_element(TYPE * p,::count c) { ALLOCATOR::construct(p,c); }
   void on_destruct_element(TYPE * p) { ALLOCATOR::destruct(p); }
   void on_copy_element(index i,const TYPE * p) { ALLOCATOR::copy(&m_pData[i],p); }


   index insert_at(index nIndex,const TYPE * newElement,::count nCount = 1);
   index remove_at(index nIndex,::count nCount = 1);
   index insert_at(index nStartIndex,array_base * pNewArray);


   virtual ::count append(const array_base & src); // return old size
   virtual void copy(const array_base & src);

   virtual void on_after_read();

   template < typename PRED >
   index pred_find_first(PRED pred, index iStart = 0)
   {
      for(index i = iStart; i < get_count(); i++)
      {

         if(pred(m_pData[i]))
         {

            return i;

         }

      }

      return -1;

   }

   template < typename PRED >
   TYPE * pred_get_first(PRED pred)
   {
      for(int i = 0; i < get_count(); i++)
      {

         if(pred(m_pData[i]))
         {

            return &element_at(i);

         }

      }

      return NULL;

   }


   template < typename PRED >
   ::count pred_get_count(PRED pred)
   {

      ::count c = 0;

      for(int i = 0; i < get_count(); i++)
      {

         if(pred(m_pData[i]))
         {

            c++;

         }

      }

      return c;

   }


   template < typename PRED >
   void pred_remove(PRED pred)
   {

      for(int i = 0; i < get_count();)
      {

         if(!pred(m_pData[i]))
         {
            i++;
         }
         else
         {

            int iStart = i;

            int iCount = 1;

            i++;

            for(; i < get_count();)
            {

               if(!pred(m_pData[i]))
               {

                  break;

               }

               iCount++;

               i++;

            }

            remove_at(iStart,iCount);

            i = iStart;

         }

      }

   }

   template < typename PRED >
   bool pred_add_unique(TYPE t, PRED pred)
   {

      if(this->pred_find_first(pred) >= 0)
      {

         return false;

      }

      this->add(t);

      return true;

   }
   template < typename F >
   void each(F f)
   {

      for(index i = 0; i < get_count(); i++)
      {
         f(m_pData[i]);
      }

   }


};


template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE > >
class array :
   public ::array_base < TYPE, ALLOCATOR >
{
public:

   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;
   typedef array < TYPE, ARG_TYPE > BASE_ARRAY;


   class iterator
   {
   public:

      typedef TYPE BASE_TYPE;
      typedef ARG_TYPE BASE_ARG_TYPE;
      typedef array < TYPE,ARG_TYPE > BASE_ARRAY;

         index            m_i;
         array *     m_parray;

         iterator()
         {
            m_i = 0;
            m_parray = NULL;
         }

         iterator(index i,array * parray)
         {
            m_i = i;
            m_parray = parray;
         }

         iterator(const iterator & it)
         {
            operator = (it);
         }


         iterator & operator = (const iterator & it)
         {
            if(this != &it)
            {
               m_i         = it.m_i;
               m_parray    = it.m_parray;
            }
            return *this;
         }

         bool operator == (const iterator & it)
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

         bool operator != (const iterator & it)
         {
            return !operator==(it);
         }

         iterator operator ++(int)
         {
            iterator it = *this;
            operator ++();
            return it;
         }

         iterator operator --(int)
         {
            iterator it = *this;
            operator --();
            return it;
         }

         iterator & operator ++()
         {
            m_i++;
            if(m_i >= m_parray->get_size())
               m_i = m_parray->get_size();
            return *this;
         }

         iterator & operator +(index i)
         {
            m_i += i;
            if(m_i >= m_parray->get_size())
               m_i = m_parray->get_size();
            return *this;
         }

         iterator & operator --()
         {
            m_i--;
            if(m_i < 0)
               m_i = 0;
            return *this;
         }

         iterator mid(const iterator & i) const
         {
            return iterator((m_i + i.m_i + 1) / 2,m_parray);
         }

         iterator & operator -(::count c)
         {
            m_i-=c;
            if(m_i < 0)
               m_i = 0;
            return *this;
         }

         bool operator < (const iterator & i) const
         {

            return m_i < i.m_i;

         }

         ::count get_count() const
         {
            return m_parray->get_count();
         }


      TYPE & operator * ()
      {
         return ((TYPE*) m_parray->m_pData)[m_i];
      }

      const TYPE & operator * () const
      {
         return ((const TYPE*)m_parray->m_pData)[m_i];
      }


   };


   class const_iterator
   {
   public:


      typedef TYPE BASE_TYPE;
      typedef ARG_TYPE BASE_ARG_TYPE;
      typedef array < TYPE,ARG_TYPE > BASE_ARRAY;


         index            m_i;
         const array *     m_parray;

         const_iterator()
         {
            m_i = 0;
            m_parray = NULL;
         }

         const_iterator(index i,const array * parray)
         {
            m_i = i;
            m_parray = parray;
         }

         const_iterator(const iterator & it)
         {
            operator = (it);
         }

         const_iterator(const const_iterator & it)
         {
            operator = (it);
         }

         const_iterator & operator = (const iterator & it)
         {
            m_i         = it.m_i;
            m_parray    = it.m_parray;
            return *this;
         }

         const_iterator & operator = (const const_iterator & it)
         {
            if(this != &it)
            {
               m_i         = it.m_i;
               m_parray    = it.m_parray;
            }
            return *this;
         }

         bool operator == (const const_iterator & it)
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

         bool operator != (const const_iterator & it)
         {
            return !operator==(it);
         }

         const_iterator operator ++(int)
         {
            const_iterator it = *this;
            operator ++();
            return it;
         }

         const_iterator operator --(int)
         {
            const_iterator it = *this;
            operator --();
            return it;
         }

         const_iterator & operator ++()
         {
            m_i++;
            if(m_i >= m_parray->get_size())
               m_i = m_parray->get_size();
            return *this;
         }

         const_iterator & operator +(index i)
         {
            m_i += i;
            if(m_i >= m_parray->get_size())
               m_i = m_parray->get_size();
            return *this;
         }

         const_iterator & operator --()
         {
            m_i--;
            if(m_i < 0)
               m_i = 0;
            return *this;
         }

         const_iterator mid(const const_iterator & i) const
         {
            return const_iterator_base((m_i + i.m_i + 1) / 2,m_parray);
         }

         const_iterator & operator -(::count c)
         {
            m_i-=c;
            if(m_i < 0)
               m_i = 0;
            return *this;
         }

         bool operator < (const const_iterator & i) const
         {

            return m_i < i.m_i;

         }

         ::count get_count() const
         {
            return m_parray->get_count();
         }

      const TYPE & operator * ()
      {
         return ((const TYPE*)m_parray->m_pData)[m_i];
      }

   };




   array(::aura::application * papp = NULL, ::count nGrowBy = 0);
   array(const array & a);
   array(::std::initializer_list < TYPE > l);
   array(::count n);
   array(::count n, ARG_TYPE t);
   array(array && a);
   virtual ~array();


   inline const TYPE& get_at(index nIndex) const;
   inline TYPE& get_at(index nIndex);
   inline void set_at(index nIndex, ARG_TYPE newElement);

   inline const TYPE & element_at(index nIndex) const;
   inline TYPE & element_at(index nIndex);

   inline TYPE & first(index n = 0);
   inline const TYPE & first(index n = 0) const;

   inline TYPE & last(index n = -1);
   inline const TYPE & last(index n = -1) const;

   inline const TYPE* get_data() const;
   inline TYPE* get_data();


   inline index add(ARG_TYPE newElement);
   inline index add(const array& src);
   inline index append(const array& src);
   inline void copy(const array& src);

   inline TYPE & add_new();
   inline index add_new( ::count count);


   inline TYPE pop(index index = -1);
   inline index push(ARG_TYPE newElement,index i = 0);
   inline void pop_back(index index = -1);
   inline void push_back(ARG_TYPE newElement,index = 0);



   inline iterator erase(iterator pos);
   inline iterator erase(iterator first,iterator last);
   inline iterator begin()
   {
      return iterator(0, this);
   }

   inline iterator end()
   {
      return iterator(this->get_size(), this);
   }

   inline const_iterator begin() const
   {
      return const_iterator(0,this);
   }

   inline const_iterator end() const
   {
      return const_iterator(this->get_size(),this);
   }

   // overloaded operator helpers
   inline const TYPE& operator[](index nIndex) const;
   inline TYPE& operator[](index nIndex);

   // Operations that move elements around
   inline index insert_at(index nIndex, ARG_TYPE newElement, ::count nCount = 1);
   //void _001RemoveIndexes(index_array & ia);
   //void remove_indexes(const index_array & ia); // remove indexes from index array upper bound to index array lower bound
   //void remove_descending_indexes(const index_array & ia); // remove indexes from index array lower bound to index array upper bound
   //index insert_at(index nStartIndex, array* pNewArray);
   inline void swap(index index1, index index2);

   inline array & operator = (const array & src);
   inline array & operator = (array && a);
   inline array & move (array && a);


   //inline index find_first(ARG_TYPE t, index (* lpfnCompare)(ARG_TYPE, ARG_TYPE), index start = 0, index last = -1) const;
   //index raw_find_first(TYPE * pt, index first = 0, index last = -1) const;

   //template < class DERIVED >
   //inline index find_first(DERIVED * pt, index first = 0, index last = -1)
   //{
   //   return raw_find_first(dynamic_cast < TYPE * > (pt), first, last);
   //}

   template < class ARRAY >
   inline ::count slice(ARRAY & a, index iStart = 0, ::count nCount = -1)
   {

      ::count ca = 0;

      index iEnd;

      if(nCount < 0)
         iEnd = this->get_upper_bound(nCount);
      else
         iEnd = iStart + nCount - 1;

      for(index i = iStart; i <= iEnd; i++)
      {

         a.add(element_at(i));
         ca++;

      }

      return ca;

   }

   //void quick_sort(index (* fCompare)(TYPE *, TYPE *));
   //void quick_sort(index (* fCompare)(TYPE *, TYPE *), void (* fSwap)(TYPE *, TYPE *));
   //void quick_sort(index (* fCompare)(TYPE *, TYPE *), index_array & ia);
   //bool binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *)) const;

   //bool binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia) const;
   //index sort_add(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);
   //::count sort_add(const array < TYPE, ARG_TYPE > & a, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);
   //index sort_remove(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);

   operator TYPE *() {return this->m_pData;}
   operator const TYPE *() const {return this->m_pData;}
   operator count() const { return this->get_count(); }

   inline array & operator += (const array & a);
   inline array operator + (const array & a) const;

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


};




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


