#pragma once


//#undef new


#define new DEBUG_NEW


#ifdef DEBUG
#define TEMPLATE_TYPE_NEW new(__FILE__ + string(" - ") + typeid(TYPE).name(), __LINE__)
#else
#define TEMPLATE_TYPE_NEW new
#endif


class index_array;


#undef new


#define new TEMPLATE_TYPE_NEW


#ifndef __max
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#define ARRAY_MOVE_SEMANTICS(A) \
      \
   A(A && a) :  \
   ca(a.get_app()) \
   { \
    \
   m_nGrowBy      = a.m_nGrowBy; \
   m_pData        = a.m_pData; \
   m_nSize        = a.m_nSize; \
   m_nMaxSize     = a.m_nMaxSize; \
   \
   a.m_pData      = ::null(); \
   \
   } \
   \
   inline A & A::operator = (A && a)      \
   {                                      \
                                          \
      if(&a != this)                      \
      { \
         destroy(); \
         \
         m_nGrowBy      = a.m_nGrowBy; \
         m_pData        = a.m_pData; \
         m_nSize        = a.m_nSize; \
         m_nMaxSize     = a.m_nMaxSize; \
         \
         a.m_pData      = null(); \
         \
      } \
      \
   return *this; \
   \
   } 




// raw array is a special array and should be used with care
// it uses operations like memmove and memcopy to move objects and does not
// call constructors and destructors for the elements
// it is faster than the more generic arrays and is proper for use
// with strict structs and primitive data types

template < typename C >
class class_size
{
public:

   sp(C)          m_p;
   ::count        m_c;

   class_size(C * p) : m_p(p), m_c(-1) {}

   class_size(C * p, ::count c) : m_p(::null()), m_c(c) {}

   class_size(const class_size & size) : m_p(size.m_p), m_c(size.m_c) {}

   operator ::count ()
   {
      if(m_c >= 0)
      {
         return m_c;
      }
      else
      {
         return m_p->get_size();
      }

   }

   class class_size & operator ++()
   {

      m_p->set_size(m_p->get_size() + 1);

      return *this;

   }

   class class_size & operator --()
   {

      m_p->set_size(m_p->get_size() - 1);

      return *this;

   }


   class class_size operator ++(int)
   {

      class_size size(m_p, m_p->get_size());

      m_p->set_size(m_p->get_size() + 1);

      return size;

   }

   class class_size operator --(int)
   {

      class_size size(m_p, m_p->get_size());

      m_p->set_size(m_p->get_size() - 1);

      return size;

   }



   class class_size & operator +=(::count c)
   {

      m_p->set_size(m_p->get_size() + c);

      return *this;

   }

   class class_size & operator -=(::count c)
   {

      m_p->set_size(m_p->get_size() - c);

      return *this;

   }

};

template<class TYPE, class ARG_TYPE = const TYPE &>
class array :
   virtual public ::ca::object
{
public:

   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;

   /*

   class iterator
   {
   public:


   index            m_i;
   array *     m_parray;

   iterator()
   {
   m_i = 0;
   m_parray = ::null();
   }

   iterator(index i, array * parray)
   {
   m_i         = i;
   m_parray    = parray;
   }

   iterator(const iterator & it)
   {
   }

   TYPE & operator * ()
   {
   m_parray->element_at[m_i];
   }

   const TYPE & operator * () const
   {
   m_parray->element_at[m_i];
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

   iterator & operator ++()
   {
   m_i++;
   if(m_i >= m_parray->get_size())
   m_i = m_parray->get_size();
   return *this;
   }

   iterator & operator +(int32_t i)
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

   };
   */

   class iterator
   {
   public:


      index            m_i;
      array *     m_parray;

      iterator()
      {
         m_i = 0;
         m_parray = ::null();
      }

      iterator(index i, array * parray)
      {
         m_i = i;
         m_parray = parray;
      }

      iterator(const iterator & it)
      {
         operator = (it);
      }

      TYPE & operator * ()
      {
         return m_parray->element_at(m_i);
      }

      const TYPE & operator * () const
      {
         return m_parray->element_at(m_i);
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

   };


   class const_iterator
   {
   public:


      index            m_i;
      const array *     m_parray;

      const_iterator()
      {
         m_i = 0;
         m_parray = ::null();
      }

      const_iterator(index i, const array * parray)
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

      const TYPE & operator * ()
      {
         return m_parray->element_at(m_i);
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

   };

   TYPE *      m_pData;    // the actual array of data
   ::count     m_nSize;    // # of elements (upperBound - 1)
   ::count     m_nMaxSize; // max allocated
   ::count     m_nGrowBy;  // grow amount



   array(sp(::ca::application) papp = ::null(), ::count nGrowBy = 32);
   array(const array <TYPE, ARG_TYPE> & a);
   ARRAY_MOVE_SEMANTICS(array);
   array(::count n);
   array(ARG_TYPE t, ::count n = 1);
   array(TYPE * ptypea, ::count n);
   virtual ~array();

   virtual void destroy();

   inline ::count get_size() const;
   inline ::count get_size_in_bytes() const;
   inline ::count get_count() const;
   inline ::count get_byte_count() const;

   class_size < array > size();
   class_size < array > count();

   inline bool is_empty(::count countMinimum = 1) const;
   inline bool has_elements(::count countMinimum = 1) const;
   inline index get_upper_bound(index i = -1) const;
   ::count set_size(index nNewSize, ::count nGrowBy = -1);
   ::count set_size_in_bytes(index nNewSize, ::count nGrowBy = -1);

   void free_extra();

   void remove_last();

   ::count remove_all();
   void clear();




   // Accessing elements
   inline const TYPE& get_at(index nIndex) const;
   inline TYPE& get_at(index nIndex);
   inline void set_at(index nIndex, ARG_TYPE newElement);

   inline const TYPE & element_at(index nIndex) const;
   inline TYPE & element_at(index nIndex);

   inline const TYPE& first_element(index index = 0) const;
   inline TYPE& first_element(index index = 0);

   inline const TYPE& last_element(index index = -1) const;
   inline TYPE& last_element(index index = -1);

   inline TYPE & front(index n = 0);
   inline const TYPE & front(index n = 0) const;

   inline TYPE & back(index n = -1);
   inline const TYPE & back(index n = -1) const;


   // Direct Access to the element data (may return ::null())
   inline const TYPE* get_data() const;
   inline TYPE* get_data();

   // Potentially growing the array
   void set_at_grow(index nIndex, ARG_TYPE newElement);
   TYPE & element_at_grow(index nIndex);
   TYPE get_at_grow(index nIndex);
   index add(ARG_TYPE newElement);
   index add(const array& src);
   virtual index add_new(::count count);
   virtual TYPE & add_new();
   index append(const array& src);
   void copy(const array& src);


   TYPE pop(index index = -1);
   index push(ARG_TYPE newElement, index i = 0);
   void pop_back(index index = -1);
   void push_back(ARG_TYPE newElement, index = 0);



   iterator erase(iterator pos);
   iterator erase(iterator first, iterator last);
   iterator begin()
   {
      return iterator(0, this);
   }

   iterator end()
   {
      return iterator(this->get_size(), this);
   }


   // overloaded operator helpers
   inline const TYPE& operator[](index nIndex) const;
   inline TYPE& operator[](index nIndex);

   // Operations that move elements around
   index insert_at(index nIndex, ARG_TYPE newElement, ::count nCount = 1);
   index remove_at(index nIndex, ::count nCount = 1);
   void _001RemoveIndexes(index_array & ia);
   void remove_indexes(const index_array & ia); // remove indexes from index array upper bound to index array lower bound
   void remove_descending_indexes(const index_array & ia); // remove indexes from index array lower bound to index array upper bound
   index insert_at(index nStartIndex, array* pNewArray);
   void swap(index index1, index index2);

   array & operator = (const array & src);

   index find_first(ARG_TYPE t, index (* lpfnCompare)(ARG_TYPE, ARG_TYPE), index start = 0, index last = -1) const;
   index raw_find_first(TYPE * pt, index first = 0, index last = -1) const;

   template < class DERIVED >
   index find_first(DERIVED * pt, index first = 0, index last = -1)
   {
      return raw_find_first(dynamic_cast < TYPE * > (pt), first, last);
   }

   template < class ARRAY >
   ::count get_array(ARRAY & a, index iStart = 0, ::count nCount = -1)
   {

      ::count c = 0;

      index iEnd;

      if(nCount < 0)
         iEnd = get_upper_bound(nCount);
      else 
         iEnd = iStart + nCount - 1;

      for(int i = iStart; i <= iEnd; i++)
      {

         a.add(element_at(i));
         c++;

      }

      return c;

   }

   void quick_sort(index (* fCompare)(TYPE *, TYPE *));
   void quick_sort(index (* fCompare)(TYPE *, TYPE *), void (* fSwap)(TYPE *, TYPE *));
   void quick_sort(index (* fCompare)(TYPE *, TYPE *), index_array & ia);
   bool binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *)) const;

   bool binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia) const;
   index sort_add(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);
   ::count sort_add(const array < TYPE, ARG_TYPE > & a, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);
   index sort_remove(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);
   


   array & operator += (const array & a);
   array operator + (const array & a) const;

   void dump(dump_context &) const;
   void assert_valid() const;


};

/////////////////////////////////////////////////////////////////////////////
// array<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
inline ::count array<TYPE, ARG_TYPE>::get_size() const
{
   return m_nSize;
}

template<class TYPE, class ARG_TYPE>
inline ::count array<TYPE, ARG_TYPE>::get_size_in_bytes() const
{
   return m_nSize * sizeof(TYPE);
}

template<class TYPE, class ARG_TYPE>
inline ::count array<TYPE, ARG_TYPE>::get_count() const
{
   return this->get_size();
}

template<class TYPE, class ARG_TYPE>
inline ::count array<TYPE, ARG_TYPE>::get_byte_count() const
{
   return this->get_size_in_bytes();
}

template<class TYPE, class ARG_TYPE>
inline class_size < array<TYPE, ARG_TYPE > > array<TYPE, ARG_TYPE>::size()
{
   return class_size < array<TYPE, ARG_TYPE > >(this);
}

template<class TYPE, class ARG_TYPE>
inline class_size < array<TYPE, ARG_TYPE > > array<TYPE, ARG_TYPE>::count()
{
   return class_size < array<TYPE, ARG_TYPE > >(this);
}


template<class TYPE, class ARG_TYPE>
inline bool array<TYPE, ARG_TYPE>::is_empty(::count countMinimum) const
{
   return m_nSize < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool array<TYPE, ARG_TYPE>::has_elements(::count countMinimum) const
{
   return m_nSize >= countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline index array<TYPE, ARG_TYPE>::get_upper_bound(index index) const
{
   return m_nSize + index;
}

template<class TYPE, class ARG_TYPE>
inline ::count array<TYPE, ARG_TYPE>::remove_all()
{
   return set_size(0, -1);
}

template <class TYPE, class ARG_TYPE>
void array<TYPE, ARG_TYPE>::
   clear()
{
   remove_all();
}


template<class TYPE, class ARG_TYPE>
inline void array<TYPE, ARG_TYPE>::remove_last()
{
   remove_at(get_upper_bound());
}

template<class TYPE, class ARG_TYPE>
inline TYPE& array<TYPE, ARG_TYPE>::get_at(index nIndex)
{
   //   if(nIndex >= 0 && nIndex < m_nSize)
   return m_pData[nIndex];
   //   throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& array<TYPE, ARG_TYPE>::get_at(index nIndex) const
{
   //   if(nIndex >= 0 && nIndex < m_nSize)
   return m_pData[nIndex];
   // throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline void array<TYPE, ARG_TYPE>::set_at(index nIndex, ARG_TYPE newElement)
{
   //   if(nIndex >= 0 && nIndex < m_nSize)
   m_pData[nIndex] = newElement;
   // else
   //  throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& array<TYPE, ARG_TYPE>::element_at(index nIndex) const
{
   //   if(nIndex >= 0 && nIndex < m_nSize)
   return m_pData[nIndex];
   // throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline TYPE& array<TYPE, ARG_TYPE>::element_at(index nIndex)
{
   //   if(nIndex >= 0 && nIndex < m_nSize)
   return m_pData[nIndex];
   // throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& array<TYPE, ARG_TYPE>::first_element(index nIndex) const
{
   return this->element_at(nIndex);
}
template<class TYPE, class ARG_TYPE>
inline TYPE& array<TYPE, ARG_TYPE>::first_element(index nIndex)
{
   return this->element_at(nIndex);
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& array<TYPE, ARG_TYPE>::last_element(index index) const
{
   return element_at(get_upper_bound(index));
}


template<class TYPE, class ARG_TYPE>
inline TYPE& array<TYPE, ARG_TYPE>::last_element(index index)
{
   return element_at(get_upper_bound(index));
}


template<class TYPE, class ARG_TYPE>
inline TYPE & array<TYPE, ARG_TYPE>::front(index n)
{
   return first_element(n);
}

template<class TYPE, class ARG_TYPE>
inline const TYPE & array<TYPE, ARG_TYPE>::front(index n) const
{
   return first_element(n);
}

template<class TYPE, class ARG_TYPE>
inline TYPE & array<TYPE, ARG_TYPE>::back(index n)
{
   return last_element(n);
}

template<class TYPE, class ARG_TYPE>
inline const TYPE & array<TYPE, ARG_TYPE>::back(index n) const
{
   return last_element(n);
}


template<class TYPE, class ARG_TYPE>
inline const TYPE* array<TYPE, ARG_TYPE>::get_data() const
{
   return (const TYPE*)m_pData;
}

template<class TYPE, class ARG_TYPE>
inline TYPE* array<TYPE, ARG_TYPE>::get_data()
{
   return (TYPE*)m_pData;
}

template<class TYPE, class ARG_TYPE>
inline index array<TYPE, ARG_TYPE>::add(ARG_TYPE newElement)
{
   index nIndex = m_nSize;
   set_at_grow(nIndex, newElement);
   return nIndex;
}


template<class TYPE, class ARG_TYPE>
inline index array<TYPE, ARG_TYPE>::add(const array & src)
{
   return append(src);
}


template<class TYPE, class ARG_TYPE>
inline index array<TYPE, ARG_TYPE>::add_new(::count count)
{
   set_size(m_nSize + count);
   return get_upper_bound(); 
}

template<class TYPE, class ARG_TYPE>
inline TYPE & array<TYPE, ARG_TYPE>::add_new()
{
   set_size(m_nSize + 1);
   return last_element(); 
}


template<class TYPE, class ARG_TYPE>
inline TYPE array<TYPE, ARG_TYPE>::pop(index n)
{

   index i = get_upper_bound(n);

   TYPE t = element_at(i);

   remove_at(i);

   return t;

}

template<class TYPE, class ARG_TYPE>
inline void array<TYPE, ARG_TYPE>::pop_back(index n)
{

   remove_at(get_upper_bound(n));

}

template<class TYPE, class ARG_TYPE>
inline index array<TYPE, ARG_TYPE>::push(ARG_TYPE newElement, index n)
{
   return insert_at(get_upper_bound(n), newElement);
}

template<class TYPE, class ARG_TYPE>
inline void array<TYPE, ARG_TYPE>::push_back(ARG_TYPE newElement, index n)
{
   insert_at(get_upper_bound(n), newElement);
}


template<class TYPE, class ARG_TYPE>
inline const TYPE& array<TYPE, ARG_TYPE>::operator[](index nIndex) const
{
   return element_at(nIndex);
}

template<class TYPE, class ARG_TYPE>
inline TYPE& array<TYPE, ARG_TYPE>::operator[](index nIndex)
{
   return this->element_at(nIndex);
}


template<class TYPE, class ARG_TYPE>
inline void array<TYPE, ARG_TYPE>::swap(index index1, index index2)
{
   TYPE t = m_pData[index1];
   m_pData[index1] = m_pData[index2];
   m_pData[index2] = t;
}

template<class TYPE, class ARG_TYPE>
inline array<TYPE, ARG_TYPE> & array<TYPE, ARG_TYPE>::operator = (const array & src)
{
   if(&src != this)
   {
      copy(src);
   }
   return *this;
}



// out-of-line functions

template<class TYPE, class ARG_TYPE>
array<TYPE, ARG_TYPE>::array(sp(::ca::application) papp, ::count nGrowBy) :
ca(papp)
{
   m_nGrowBy = max(0, nGrowBy);
   m_pData = ::null();
   m_nSize = m_nMaxSize = 0;
}

template<class TYPE, class ARG_TYPE>
array<TYPE, ARG_TYPE>::array(const array <TYPE, ARG_TYPE> & a) :
ca(a.get_app())
{
   m_nGrowBy = 32;
   m_pData = ::null();
   m_nSize = m_nMaxSize = 0;
   operator = (a);
}



template<class TYPE, class ARG_TYPE>
array<TYPE, ARG_TYPE>:: array(::count n)
{
   m_nGrowBy = 32;
   m_pData = ::null();
   m_nSize = m_nMaxSize = 0;
   set_size(n);
}

template<class TYPE, class ARG_TYPE>
array<TYPE, ARG_TYPE>::array(ARG_TYPE t, ::count n)
{
   m_nGrowBy = 32;
   m_pData = ::null();
   m_nSize = m_nMaxSize = 0;
   insert_at(0, t, n);
}


template<class TYPE, class ARG_TYPE>
array<TYPE, ARG_TYPE>::array(TYPE * ptypea, ::count n)
{
   m_nGrowBy = 32;
   m_pData = ::null();
   m_nSize = m_nMaxSize = 0;
   set_size(n);
   for(int i = 0; i < n; i++)
   {
      element_at(i) = ptypea[i];
   }
}



template<class TYPE, class ARG_TYPE>
array<TYPE, ARG_TYPE>::~array()
{
   
   destroy();

}

template<class TYPE, class ARG_TYPE>
void array<TYPE, ARG_TYPE>::destroy()
{
   ASSERT_VALID(this);

   if (m_pData != ::null())
   {
      for( int32_t i = 0; i < m_nSize; i++ )
         (m_pData + i)->~TYPE();
      delete[] (BYTE*)m_pData;
      m_pData     = ::null();
      m_nSize     = 0;
      m_nMaxSize  = 0;
   }

}

template<class TYPE, class ARG_TYPE>
::count array<TYPE, ARG_TYPE>::set_size_in_bytes(::count nNewSize, ::count nGrowBy)
{
   if(nGrowBy < 0)
   {
      return set_size(nNewSize / sizeof(TYPE), -1);
   }
   else
   {
      return set_size(nNewSize / sizeof(TYPE), nGrowBy / sizeof(TYPE));
   }
}

template<class TYPE, class ARG_TYPE>
::count array<TYPE, ARG_TYPE>::set_size(::count nNewSize, ::count nGrowBy)
{
   ::count countOld = get_count();
   ASSERT_VALID(this);
   ASSERT(nNewSize >= 0);

   if(nNewSize < 0 )
      throw invalid_argument_exception(get_app());

   if (nGrowBy >= 0)
      m_nGrowBy = nGrowBy;  // set new size

   if (nNewSize == 0)
   {
      // shrink to nothing
      if (m_pData != ::null())
      {
         for( int32_t i = 0; i < m_nSize; i++ )
            (m_pData + i)->~TYPE();
         delete[] (BYTE*)m_pData;
         m_pData = ::null();
      }
      m_nSize = m_nMaxSize = 0;
   }
   else if (m_pData == ::null())
   {
      // create buffer big enough to hold number of requested elements or
      // m_nGrowBy elements, whichever is larger.
#ifdef SIZE_T_MAX
      if(nNewSize > SIZE_T_MAX/sizeof(TYPE))
         throw memory_exception(get_app());
      ASSERT(nNewSize <= SIZE_T_MAX/sizeof(TYPE));    // no overflow
#endif
      ::count nAllocSize = __max(nNewSize, m_nGrowBy);
#undef new
      m_pData = (TYPE*) new BYTE[(size_t)nAllocSize * sizeof(TYPE)];
      //memset((void *)m_pData, 0, (size_t)nAllocSize * sizeof(TYPE));
      for( int32_t i = 0; i < nNewSize; i++ )
         ::new( (void *)( m_pData + i ) ) TYPE;
#define new DEBUG_NEW
      m_nSize = nNewSize;
      m_nMaxSize = nAllocSize;
   }
   else if (nNewSize <= m_nMaxSize)
   {
      // it fits
      if (nNewSize > m_nSize)
      {
         // initialize the new elements
         memset((void *)(m_pData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
         for( int32_t i = 0; i < nNewSize-m_nSize; i++ )
#undef new
            ::new( (void *)( m_pData + m_nSize + i ) ) TYPE;
#define new DEBUG_NEW
      }
      else if (m_nSize > nNewSize)
      {
         // destroy the old elements
         for( int32_t i = 0; i < m_nSize-nNewSize; i++ )
            (m_pData + nNewSize + i)->~TYPE();
      }
      m_nSize = nNewSize;
   }
   else
   {
      // otherwise, grow aaa_base_array
      nGrowBy = m_nGrowBy;
      if (nGrowBy == 0)
      {
         // heuristically determine growth when nGrowBy == 0
         //  (this avoids heap fragmentation in many situations)
         nGrowBy = m_nSize / 8;
         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
      }
      ::count nNewMax;
      if (nNewSize < m_nMaxSize + nGrowBy)
         nNewMax = m_nMaxSize + nGrowBy;  // granularity
      else
         nNewMax = nNewSize;  // no slush

      ASSERT(nNewMax >= m_nMaxSize);  // no wrap around

      if(nNewMax  < m_nMaxSize)
         throw invalid_argument_exception(get_app());

#ifdef SIZE_T_MAX
      ASSERT(nNewMax <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
#endif
#undef new
      TYPE* pNewData = (TYPE*) new BYTE[(size_t)nNewMax * sizeof(TYPE)];
#define new DEBUG_NEW

      // copy new data from old
      ::ca::memcpy_s(pNewData, (size_t)nNewMax * sizeof(TYPE),
         m_pData, (size_t)m_nSize * sizeof(TYPE));

      // construct remaining elements
      ASSERT(nNewSize > m_nSize);
      memset((void *)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
      for( int32_t i = 0; i < nNewSize-m_nSize; i++ )
#undef new
         ::new( (void *)( pNewData + m_nSize + i ) ) TYPE;
#define new DEBUG_NEW
      // get rid of old stuff (note: no destructors called)
      delete[] (BYTE*)m_pData;
      m_pData = pNewData;
      m_nSize = nNewSize;
      m_nMaxSize = nNewMax;
   }
   return countOld;
}

template<class TYPE, class ARG_TYPE>
index array<TYPE, ARG_TYPE>::append(const array& src)
{
   ASSERT_VALID(this);
   ASSERT(this != &src);   // cannot append to itself

   if(this == &src)
      throw invalid_argument_exception(get_app());

   ::count nOldSize = m_nSize;
   set_size(m_nSize + src.m_nSize);
   CopyElements<TYPE>(m_pData + nOldSize, src.m_pData, src.m_nSize);
   return nOldSize;
}

template<class TYPE, class ARG_TYPE>
void array<TYPE, ARG_TYPE>::copy(const array& src)
{
   ASSERT_VALID(this);
   ASSERT(this != &src);   // cannot append to itself

   if(this != &src)
   {
      set_size(src.m_nSize);
      CopyElements<TYPE>(m_pData, src.m_pData, src.m_nSize);
   }
}

template<class TYPE, class ARG_TYPE>
void array<TYPE, ARG_TYPE>::free_extra()
{
   ASSERT_VALID(this);

   if (m_nSize != m_nMaxSize)
   {
      // shrink to desired size
#ifdef SIZE_T_MAX
      ASSERT(m_nSize <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
#endif
      TYPE* pNewData = ::null();
      if (m_nSize != 0)
      {
         pNewData = (TYPE*) new BYTE[m_nSize * sizeof(TYPE)];
         // copy new data from old
         ::ca::memcpy_s(pNewData, m_nSize * sizeof(TYPE),
            m_pData, m_nSize * sizeof(TYPE));
      }

      // get rid of old stuff (note: no destructors called)
      delete[] (BYTE*)m_pData;
      m_pData = pNewData;
      m_nMaxSize = m_nSize;
   }
}

template<class TYPE, class ARG_TYPE>
void array<TYPE, ARG_TYPE>::set_at_grow(index nIndex, ARG_TYPE newElement)
{
   //ASSERT_VALID(this);
   //ASSERT(nIndex >= 0);

   if(nIndex < 0)
      throw invalid_argument_exception(get_app());

   if (nIndex >= m_nSize)
      set_size(nIndex+1, -1);
   m_pData[nIndex] = newElement;
}

template<class TYPE, class ARG_TYPE>
TYPE array<TYPE, ARG_TYPE>::get_at_grow(index nIndex)
{
   return element_at_grow(nIndex);
}


template<class TYPE, class ARG_TYPE>
TYPE & array<TYPE, ARG_TYPE>::element_at_grow(index nIndex)
{
   ASSERT_VALID(this);
   ASSERT(nIndex >= 0);

   if(nIndex < 0)
      throw invalid_argument_exception(get_app());

   if (nIndex >= m_nSize)
      set_size(nIndex+1, -1);
   return m_pData[nIndex];
}


template<class TYPE, class ARG_TYPE>
index array<TYPE, ARG_TYPE>::insert_at(index nIndex, ARG_TYPE newElement, ::count nCount /*=1*/)
{
   //ASSERT_VALID(this);
   //ASSERT(nIndex >= 0);    // will expand to meet need

   if(nCount <= 0)
      return -1;

   if(nIndex < 0)
      throw invalid_argument_exception(get_app());

   if (nIndex >= m_nSize)
   {
      // adding after the end of the array
      set_size(nIndex + nCount, -1);   // grow so nIndex is valid
   }
   else
   {
      // inserting in the middle of the array
      ::count nOldSize = m_nSize;
      set_size(m_nSize + nCount, -1);  // grow it to new size
      // destroy intial data before copying over it
      // shift old data up to fill gap
      ::ca::memmove_s(m_pData + nIndex + nCount, (nOldSize-nIndex) * sizeof(TYPE),
         m_pData + nIndex, (nOldSize-nIndex) * sizeof(TYPE));

      // re-init slots we copied from
      memset((void *)(m_pData + nIndex), 0, (size_t)nCount * sizeof(TYPE));
#undef new
      for( int32_t i = 0; i < nCount; i++ )
         ::new( (void *)( m_pData + nIndex + i ) ) TYPE;
#define new DEBUG_NEW
   }

   // insert new value in the gap
   ASSERT(nIndex + nCount <= m_nSize);

   index nIndexParam = nIndex;

   while (nCount--)
      m_pData[nIndex++] = newElement;

   return nIndexParam;

}

template<class TYPE, class ARG_TYPE>
inline index array<TYPE, ARG_TYPE>::remove_at(index nIndex, ::count nCount)
{

   //ASSERT_VALID(this);

   index nUpperBound = nIndex + nCount;

   if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
      throw invalid_argument_exception(get_app());

   // just remove a range
   ::count nMoveCount = m_nSize - (nUpperBound);
   if (nMoveCount)
   {
      ::ca::memmove_s(m_pData + nIndex, (size_t)nMoveCount * sizeof(TYPE),
         m_pData + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));
   }
   m_nSize -= nCount;
   return nIndex;
}


template<class TYPE, class ARG_TYPE>
index array<TYPE, ARG_TYPE>::insert_at(index nStartIndex, array * pNewArray)
{
   ASSERT_VALID(this);
   ASSERT(pNewArray != ::null());
   ASSERT_VALID(pNewArray);
   ASSERT(nStartIndex >= 0);

   if(pNewArray == ::null() || nStartIndex < 0)
      throw invalid_argument_exception(get_app());

   if (pNewArray->get_size() > 0)
   {
      insert_at(nStartIndex, pNewArray->element_at(0), pNewArray->get_size());
      for (index i = 1; i < pNewArray->get_size(); i++)
         insert_at(nStartIndex + i, pNewArray->element_at(i));
   }

   return nStartIndex;

}


template<class TYPE, class ARG_TYPE>
void array<TYPE, ARG_TYPE>::dump(dump_context & dumpcontext) const
{
   ::ca::object::dump(dumpcontext);

   dumpcontext << "with " << m_nSize << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      dumpcontext << "\n";
      dump_elements<TYPE>(dumpcontext, m_pData, m_nSize);
   }

   dumpcontext << "\n";
}

template<class TYPE, class ARG_TYPE>
void array<TYPE, ARG_TYPE>::assert_valid() const
{
   ::ca::object::assert_valid();

   if (m_pData == ::null())
   {
      ASSERT(m_nSize == 0);
      ASSERT(m_nMaxSize == 0);
   }
   else
   {
      ASSERT(m_nSize >= 0);
      ASSERT(m_nMaxSize >= 0);
      ASSERT(m_nSize <= m_nMaxSize);
      ASSERT(__is_valid_address(m_pData, m_nMaxSize * sizeof(TYPE)));
   }
}

template<class TYPE, class ARG_TYPE>
typename array<TYPE, ARG_TYPE>::iterator array<TYPE, ARG_TYPE>::erase(iterator pos)
{
   if(pos.m_parray == this)
   {
      remove_at(pos.m_i);
      return iterator(pos.m_i, this);
   }
   else
   {
      return end();
   }
}

template<class TYPE, class ARG_TYPE>
typename  array<TYPE, ARG_TYPE>::iterator array<TYPE, ARG_TYPE>::erase(iterator begin, iterator last)
{
   if(begin.m_parray == this && last.m_parray == this)
   {
      if(begin.m_i >= 0 && begin.m_i < this->get_size())
      {
         ::count nCount = last.m_i - begin.m_i;
         remove_at(begin.m_i, nCount);
         return iterator(begin.m_i, this);
      }
      else
      {
         return end();
      }
   }
   else
   {
      return end();
   }
}


template <class TYPE, class ARG_TYPE>
index array<TYPE, ARG_TYPE>::raw_find_first(TYPE *pt, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find <= last; find++)
   {
      if(&this->element_at(find) == pt)
         return find;
   }
   return -1;
}
template <class TYPE, class ARG_TYPE>
index array<TYPE, ARG_TYPE>::find_first(ARG_TYPE t, index ( * lpfnCompare )(ARG_TYPE, ARG_TYPE), index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find <= last; find++)
   {
      if(lpfnCompare((ARG_TYPE)this->element_at(find), (ARG_TYPE)t) == 0)
         return find;
   }
   return -1;
}


template <class TYPE, class ARG_TYPE>
void array<TYPE, ARG_TYPE>::quick_sort(index (* fCompare)(TYPE *, TYPE *), void (* fSwap)(TYPE *, TYPE *))
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   //   uint32_t t;

   if(get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(get_upper_bound());
      while(true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
               if(fCompare(&element_at(iMPos), &element_at(iUPos)) <= 0)
                  iUPos--;
               else
               {
                  fSwap(&element_at(iMPos), &element_at(iUPos));
                  break;
               }
            }
            if(iMPos == iUPos)
               break;
            iMPos = iUPos;
            while(true)
            {
               if(iMPos == iLPos)
                  break;
               if(fCompare(&element_at(iLPos), &element_at(iMPos)) <= 0)
                  iLPos++;
               else
               {
                  fSwap(&element_at(iLPos), &element_at(iMPos));
                  break;
               }
            }
            if(iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if(iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if(iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if(stackLowerBound.get_size() == 0)
            break;
      }
   }

}

template <class TYPE, class ARG_TYPE>
void array<TYPE, ARG_TYPE>::quick_sort(index (* fCompare)(TYPE *, TYPE *))
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   //   uint32_t t;

   if(get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(get_upper_bound());
      while(true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
               if(fCompare(&element_at(iMPos), &element_at(iUPos)) <= 0)
                  iUPos--;
               else
               {
                  swap(iMPos, iUPos);
                  break;
               }
            }
            if(iMPos == iUPos)
               break;
            iMPos = iUPos;
            while(true)
            {
               if(iMPos == iLPos)
                  break;
               if(fCompare(&element_at(iLPos), &element_at(iMPos)) <= 0)
                  iLPos++;
               else
               {
                  swap(iLPos, iMPos);
                  break;
               }
            }
            if(iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if(iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if(iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if(stackLowerBound.get_size() == 0)
            break;
      }
   }

}

template <class TYPE, class ARG_TYPE>
void array<TYPE, ARG_TYPE>::quick_sort(index (* fCompare)(TYPE *, TYPE *), index_array & ia)
{

   // minimum check
   if(ia.get_size() != get_size())
      throw invalid_argument_exception(get_app());

   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   //   uint32_t t;

   if(get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(get_upper_bound());
      while(true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
               if(fCompare(&element_at(ia[iMPos]), &element_at(ia[iUPos])) <= 0)
                  iUPos--;
               else
               {
                  ia.swap(iMPos, iUPos);
                  break;
               }
            }
            if(iMPos == iUPos)
               break;
            iMPos = iUPos;
            while(true)
            {
               if(iMPos == iLPos)
                  break;
               if(fCompare(&element_at(ia[iLPos]), &element_at(ia[iMPos])) <= 0)
                  iLPos++;
               else
               {
                  ia.swap(iLPos, iMPos);
                  break;
               }
            }
            if(iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if(iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if(iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if(stackLowerBound.get_size() == 0)
            break;
      }
   }

}

template < class TYPE, class ARG_TYPE >
bool array < TYPE, ARG_TYPE >::
binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *)) const
{
   if(this->get_size() == 0)
   {
      return false;
   }
   
   index iLowerBound = 0;
   index iMaxBound   = get_upper_bound();
   index iUpperBound = iMaxBound;
   index iCompare;
   // do binary search
   iIndex = (iUpperBound + iLowerBound) / 2;
   while(iUpperBound - iLowerBound >= 8)
   {
      iCompare = fCompare((TYPE *) &this->m_pData[iIndex], (TYPE *) &t);
      if(iCompare == 0)
      {
         return true;
      }
      else if(iCompare > 0)
      {
         iUpperBound = iIndex - 1;
         if(iUpperBound < 0)
         {
            iIndex = 0;
            break;
         }
      }
      else
      {
         iLowerBound = iIndex + 1;
         if(iLowerBound > iMaxBound)
         {
            iIndex = iMaxBound + 1;
            break;
         }
      }
      iIndex = (iUpperBound + iLowerBound) / 2;
   }
   // do sequential search
   while(iIndex < this->get_count())
   {
      iCompare = fCompare((TYPE *) &this->m_pData[iIndex], (TYPE *) &t);
      if(iCompare == 0)
         return true;
      else if(iCompare < 0)
         iIndex++;
      else
         break;
   }
   if(iIndex >= this->get_count())
      return false;
   while(iIndex >= 0)
   {
      iCompare = fCompare((TYPE *) &this->m_pData[iIndex], (TYPE *)  &t);
      if(iCompare == 0)
         return true;
      else if(iCompare > 0)
         iIndex--;
      else
         break;
   }
   iIndex++;
   return false;

}


template < class TYPE, class ARG_TYPE >
bool array < TYPE, ARG_TYPE >::
binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia) const
{
   if(this->get_size() == 0)
   {
      return false;
   }
   
   index iLowerBound = 0;
   index iMaxBound   = get_upper_bound();
   index iUpperBound = iMaxBound;
   index iCompare;
   // do binary search
   iIndex = (iUpperBound + iLowerBound) / 2;
   while(iUpperBound - iLowerBound >= 8)
   {
      iCompare = fCompare((TYPE *) &this->m_pData[ia[iIndex]], (TYPE *) &t);
      if(iCompare == 0)
      {
         return true;
      }
      else if(iCompare > 0)
      {
         iUpperBound = iIndex - 1;
         if(iUpperBound < 0)
         {
            iIndex = 0;
            break;
         }
      }
      else
      {
         iLowerBound = iIndex + 1;
         if(iLowerBound > iMaxBound)
         {
            iIndex = iMaxBound + 1;
            break;
         }
      }
      iIndex = (iUpperBound + iLowerBound) / 2;
   }
   // do sequential search
   while(iIndex < this->get_count())
   {
      iCompare = fCompare((TYPE *) &this->m_pData[ia[iIndex]], (TYPE *) &t);
      if(iCompare == 0)
         return true;
      else if(iCompare < 0)
         iIndex++;
      else
         break;
   }
   if(iIndex >= this->get_count())
      return false;
   while(iIndex >= 0)
   {
      iCompare = fCompare((TYPE *) &this->m_pData[ia[iIndex]], (TYPE *)  &t);
      if(iCompare == 0)
         return true;
      else if(iCompare > 0)
         iIndex--;
      else
         break;
   }
   iIndex++;
   return false;

}

template < class TYPE, class ARG_TYPE >
index array < TYPE, ARG_TYPE >::
sort_add(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia)
{
   index iIndex = 0;
   binary_search(t, iIndex, fCompare, ia);
   this->insert_at(iIndex, t);
   ia.add(iIndex);
   return iIndex;
}

template < class TYPE, class ARG_TYPE >
::count array < TYPE, ARG_TYPE >::
sort_add(const array  < TYPE, ARG_TYPE> & a, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia)
{
   for(index i = 0; i < a.get_size(); i++)
   {
      sort_add((ARG_TYPE) a[i], fCompare, ia);
   }
   return a.get_size();
}

template < class TYPE, class ARG_TYPE >
::count array < TYPE, ARG_TYPE >::
sort_remove(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia)
{
   ::count c = 0;
   index iFind = 0;
   while(binary_search(t, iFind, fCompare, ia))
   {
      remove_at(iFind);
      index iIndex = ia[iFind];
      ia.remove_at(iFind);
      for(index i = 0; i < ia.get_size(); i++)
      {
         if(ia[i] > iIndex)
         {
            ia[i]--;
         }
      }
      iFind = 0;
      c++;
   }
   return c;
}


template <class TYPE, class ARG_TYPE>
array<TYPE, ARG_TYPE> & array<TYPE, ARG_TYPE>::operator += (const array & a)
{

   if(&a == this)
   {
      array<TYPE, ARG_TYPE> aCopy(a);
      add(aCopy);
   }
   else
   {
      add(a);
   }
   return *this;

}

template <class TYPE, class ARG_TYPE>
array<TYPE, ARG_TYPE> array<TYPE, ARG_TYPE>::operator + (const array & a) const
{
   array<TYPE, ARG_TYPE> aNew(*this);
   aNew += a;
   return a;
}


#define new DEBUG_NEW





