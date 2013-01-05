#pragma once


#undef new




template < class TYPE, class ARG_TYPE = const TYPE & >
class base_array :
   virtual public ::radix::object
{
public:

   class iterator
   {
   public:


      index            m_i;
      base_array *     m_parray;

      iterator()
      {
         m_i = 0;
         m_parray = NULL;
      }

      iterator(index i, base_array * parray)
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
      const base_array *     m_parray;

      const_iterator()
      {
         m_i = 0;
         m_parray = NULL;
      }

      const_iterator(index i, const base_array * parray)
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


   base_array();
   base_array(const base_array <TYPE, ARG_TYPE> & a);
   base_array(::count n, const TYPE & t = TYPE());
   base_array(TYPE * ptypea, ::count n)
   {
      m_pData = NULL;
      m_nSize = m_nMaxSize = m_nGrowBy = 0;
      while(n > 0)
      {
         add(*ptypea);
         ptypea++;
         n--;
      }
   }
   virtual ~base_array();

// Attributes
   ::count get_size() const;
   ::count get_count() const;
   ::count size() const;
   ::count count() const;
   bool is_empty(::count countMinimum = 1) const;
   bool has_elements(::count countMinimum = 1) const;
   index get_upper_bound() const;
   ::count set_size(::count nNewSize, ::count nGrowBy = -1);

   void free_extra();



   // Accessing elements
   const TYPE& get_at(index nIndex) const;
   TYPE& get_at(index nIndex);
   void set_at(index nIndex, ARG_TYPE newElement);
   const TYPE& element_at(index nIndex) const;
   TYPE& element_at(index nIndex);

   // Direct Access to the element data (may return NULL)
   const TYPE* get_data() const;
   TYPE* get_data();

   // Potentially growing the base_array
   void set_at_grow(index nIndex, ARG_TYPE newElement);
   TYPE & element_at_grow(index nIndex);
   TYPE get_at_grow(index nIndex);
   virtual index add_new(::count count);
   virtual index add(ARG_TYPE newElement);
   virtual TYPE & add_new();
   virtual ::count add(const base_array& src); // for disambiguation
   virtual ::count add_array(const base_array& src);
   void copy(const base_array& src);

   virtual index insert_new(::count count = 1);
   virtual index insert(ARG_TYPE newElement);

   // overloaded operator helpers
   const TYPE& operator[](index nIndex) const;
   TYPE& operator[](index nIndex);

   // Operations that move elements around
   void insert_at(index nIndex, ARG_TYPE newElement, ::count nCount = 1);
   void remove_at(index nIndex, ::count nCount = 1);
   iterator erase(iterator pos);
   iterator erase(iterator first, iterator last);
   void insert_at(index nStartIndex, base_array* pNewArray);
   void insert_array_at(index nStartIndex, base_array* pNewArray); // for disambiguation
   void remove_last();


   void increment_size(::count add_up = 1);

   iterator begin()
   {
      return iterator(0, this);
   }

   iterator end()
   {
      return iterator(this->get_size(), this);
   }

   const_iterator begin() const
   {
      return const_iterator(0, this);
   }

   const_iterator end() const
   {
      return const_iterator(this->get_size(), this);
   }

   TYPE & first_element();
   const TYPE & first_element() const;
   TYPE & front();
   const TYPE & front() const;
   TYPE & last_element();
   const TYPE & last_element() const;
   TYPE & back();
   const TYPE & back() const;
   ::count remove_all(bool bResize = false);
   void clear();

   index find_first(ARG_TYPE t, index (* lpfnCompare)(ARG_TYPE, ARG_TYPE), index start = 0, index last = -1) const;
   index raw_find_first(TYPE * pt, index first = 0, index last = -1) const;

   template < class DERIVED >
   index find_first(DERIVED * pt, index first = 0, index last = -1)
   {
      return raw_find_first(dynamic_cast < TYPE * > (pt), first, last);
   }

   void swap(index i1, index i2);

   base_array <TYPE, ARG_TYPE> & operator = (const base_array <TYPE, ARG_TYPE> & a);

   TYPE pop();
   void push(ARG_TYPE t);
   void pop_back();
   void push_back(ARG_TYPE t);


// Implementation
protected:
   TYPE *   m_pData;   // the actual base_array of data
   ::count    m_nSize;     // # of elements (upperBound - 1)
   ::count    m_nMaxSize;  // max allocated
   ::count    m_nGrowBy;   // grow amount

public:
//   void Serialize(CArchive&);
   void dump(dump_context &) const;
   void assert_valid() const;
};

template<class TYPE, class ARG_TYPE>
base_array<TYPE, ARG_TYPE>::base_array(const base_array<TYPE, ARG_TYPE> & a)
{
   m_pData = NULL;
   m_nSize = m_nMaxSize = m_nGrowBy = 0;
   operator =(a);
}

template<class TYPE, class ARG_TYPE>
base_array<TYPE, ARG_TYPE>::base_array(::count n, const TYPE & t)
{
   m_pData = NULL;
   m_nSize = m_nMaxSize = m_nGrowBy = 0;
   while(n > 0)
   {
      add((ARG_TYPE) t);
   }
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::
increment_size(::count iAddUp)
{
    set_size(this->get_size() + iAddUp);
}

template<class TYPE, class ARG_TYPE>
TYPE & base_array<TYPE, ARG_TYPE>::
last_element()
{
    ASSERT(this->get_size() > 0);
    return this->element_at(this->get_size() - 1);
}

template<class TYPE, class ARG_TYPE>
const TYPE & base_array<TYPE, ARG_TYPE>::
last_element() const
{
    ASSERT(this->get_size() > 0);
    return this->element_at(this->get_size() - 1);
}

template<class TYPE, class ARG_TYPE>
TYPE & base_array<TYPE, ARG_TYPE>::
back()
{
    ASSERT(this->get_size() > 0);
    return this->element_at(this->get_size() - 1);
}

template<class TYPE, class ARG_TYPE>
const TYPE & base_array<TYPE, ARG_TYPE>::
back() const
{
    ASSERT(this->get_size() > 0);
    return this->element_at(this->get_size() - 1);
}

template<class TYPE, class ARG_TYPE>
TYPE & base_array<TYPE, ARG_TYPE>::
first_element()
{
    ASSERT(this->get_size() > 0);
    return this->element_at(0);
}

template<class TYPE, class ARG_TYPE>
const TYPE & base_array<TYPE, ARG_TYPE>::
first_element() const
{
    ASSERT(this->get_size() > 0);
    return get_at(0);
}

template<class TYPE, class ARG_TYPE>
TYPE & base_array<TYPE, ARG_TYPE>::
front()
{
    ASSERT(this->get_size() > 0);
    return this->element_at(0);
}

template<class TYPE, class ARG_TYPE>
const TYPE & base_array<TYPE, ARG_TYPE>::
front() const
{
    ASSERT(this->get_size() > 0);
    return get_at(0);
}

template <class TYPE, class ARG_TYPE>
::count base_array<TYPE, ARG_TYPE>::
remove_all(bool bResize)
{
   ::count countOld = this->get_count();
   if(bResize)
   {
      set_size(0, -1);
   }
   else
   {
      remove_at(0, m_nSize);
   }
   return countOld;
}


template <class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::
clear()
{
   remove_all();
}

template <class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::swap(index i1, index i2)
{
    TYPE t;
    t = this->element_at(i1);
    this->element_at(i1) = this->element_at(i2);
    this->element_at(i2) = t;
}

template <class TYPE, class ARG_TYPE>
index base_array<TYPE, ARG_TYPE>::raw_find_first(TYPE *pt, index find, index last) const
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
index base_array<TYPE, ARG_TYPE>::find_first(ARG_TYPE t, index ( * lpfnCompare )(ARG_TYPE, ARG_TYPE), index find, index last) const
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
base_array <TYPE, ARG_TYPE> &
base_array<TYPE, ARG_TYPE>::
operator = (const base_array <TYPE, ARG_TYPE> & a)
{
   if(&a == this)
      return *this;
   copy(a);
   return * this;
}

template <class TYPE, class ARG_TYPE>
inline TYPE base_array <TYPE, ARG_TYPE>::pop()
{
   ASSERT(this->get_size() > 0);
   TYPE t = last_element();
   remove_at(get_upper_bound());
   return t;
}

template <class TYPE, class ARG_TYPE>
inline void base_array <TYPE, ARG_TYPE>::
push(ARG_TYPE t)
{
   add(t);
}

template <class TYPE, class ARG_TYPE>
inline void base_array <TYPE, ARG_TYPE>::pop_back()
{
   ASSERT(this->get_size() > 0);
   remove_at(get_upper_bound());
}

template <class TYPE, class ARG_TYPE>
inline void base_array <TYPE, ARG_TYPE>::
push_back(ARG_TYPE t)
{
   add(t);
}


template<class TYPE, class ARG_TYPE>
inline ::count base_array<TYPE, ARG_TYPE>::get_size() const
{
   return m_nSize;
}

template<class TYPE, class ARG_TYPE>
inline ::count base_array<TYPE, ARG_TYPE>::get_count() const
{
   return m_nSize;
}

template<class TYPE, class ARG_TYPE>
inline ::count base_array<TYPE, ARG_TYPE>::size() const
{
   return m_nSize;
}

template<class TYPE, class ARG_TYPE>
inline ::count base_array<TYPE, ARG_TYPE>::count() const
{
   return m_nSize;
}

template<class TYPE, class ARG_TYPE>
inline bool base_array<TYPE, ARG_TYPE>::is_empty(::count countMinimum) const
{
   return m_nSize < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool base_array<TYPE, ARG_TYPE>::has_elements(::count countMinimum) const
{
   return m_nSize >= countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline index base_array<TYPE, ARG_TYPE>::get_upper_bound() const
{
   return m_nSize - 1;
}

template<class TYPE, class ARG_TYPE>
inline TYPE& base_array<TYPE, ARG_TYPE>::get_at(index nIndex)
{
   ASSERT(nIndex >= 0 && nIndex < m_nSize);
   if(nIndex >= 0 && nIndex < m_nSize)
      return m_pData[nIndex];
   throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& base_array<TYPE, ARG_TYPE>::get_at(index nIndex) const
{
   ASSERT(nIndex >= 0 && nIndex < m_nSize);
   if(nIndex >= 0 && nIndex < m_nSize)
      return m_pData[nIndex];
   throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline void base_array<TYPE, ARG_TYPE>::set_at(index nIndex, ARG_TYPE newElement)
{
   ASSERT(nIndex >= 0 && nIndex < m_nSize);
   if(nIndex >= 0 && nIndex < m_nSize)
      m_pData[nIndex] = newElement;
   else
      throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& base_array<TYPE, ARG_TYPE>::element_at(index nIndex) const
{
   //ASSERT(nIndex >= 0 && nIndex < m_nSize);
   if(nIndex >= 0 && nIndex < m_nSize)
      return m_pData[nIndex];
   throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline TYPE& base_array<TYPE, ARG_TYPE>::element_at(index nIndex)
{
//   ASSERT(nIndex >= 0 && nIndex < m_nSize);
   if(nIndex >= 0 && nIndex < m_nSize)
      return m_pData[nIndex];
   throw invalid_argument_exception(get_app());
}

template<class TYPE, class ARG_TYPE>
inline const TYPE* base_array<TYPE, ARG_TYPE>::get_data() const
{
   return (const TYPE*)m_pData;
}

template<class TYPE, class ARG_TYPE>
inline void base_array<TYPE, ARG_TYPE>::remove_last()
{
   return remove_at(get_upper_bound());
}

template<class TYPE, class ARG_TYPE>
inline TYPE* base_array<TYPE, ARG_TYPE>::get_data()
   { return (TYPE*)m_pData; }
template<class TYPE, class ARG_TYPE>
inline index base_array<TYPE, ARG_TYPE>::add(ARG_TYPE newElement)
   { index nIndex = m_nSize;
      set_at_grow(nIndex, newElement);
      return nIndex; }
template<class TYPE, class ARG_TYPE>
inline index base_array<TYPE, ARG_TYPE>::insert(ARG_TYPE newElement)
{
   return add(newElement);
}
template<class TYPE, class ARG_TYPE>
inline index base_array<TYPE, ARG_TYPE>::add_new(::count count)
   { set_size(m_nSize + count);
      return get_upper_bound(); }
template<class TYPE, class ARG_TYPE>
inline TYPE & base_array<TYPE, ARG_TYPE>::add_new()
   { set_size(m_nSize + 1);
      return last_element(); }
template<class TYPE, class ARG_TYPE>
inline index base_array<TYPE, ARG_TYPE>::insert_new(::count count)
{
   return add_new(count);
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& base_array<TYPE, ARG_TYPE>::operator[](index nIndex) const
   { return get_at(nIndex); }
template<class TYPE, class ARG_TYPE>
inline TYPE& base_array<TYPE, ARG_TYPE>::operator[](index nIndex)
   { return element_at(nIndex); }

/////////////////////////////////////////////////////////////////////////////
// base_array<TYPE, ARG_TYPE> out-of-line functions

template<class TYPE, class ARG_TYPE>
base_array<TYPE, ARG_TYPE>::base_array()
{
   m_pData = NULL;
   m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

template<class TYPE, class ARG_TYPE>
base_array<TYPE, ARG_TYPE>::~base_array()
{
   ASSERT_VALID(this);

   if (m_pData != NULL)
   {
      for( int32_t i = 0; i < m_nSize; i++ )
         (m_pData + i)->~TYPE();
      delete[] (BYTE*)m_pData;
   }
}

template<class TYPE, class ARG_TYPE>
::count base_array<TYPE, ARG_TYPE>::set_size(::count nNewSize, ::count nGrowBy)
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
      if (m_pData != NULL)
      {
         for( int32_t i = 0; i < m_nSize; i++ )
            (m_pData + i)->~TYPE();
         delete[] (BYTE*)m_pData;
         m_pData = NULL;
      }
      m_nSize = m_nMaxSize = 0;
   }
   else if (m_pData == NULL)
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
      // otherwise, grow base_array
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
      ::gen::memcpy_s(pNewData, (size_t)nNewMax * sizeof(TYPE),
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
::count base_array<TYPE, ARG_TYPE>::
add(const base_array& src)
{
   return add_array(src);
}


template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::free_extra()
{
   ASSERT_VALID(this);

   if (m_nSize != m_nMaxSize)
   {
      // shrink to desired size
#ifdef SIZE_T_MAX
      ASSERT(m_nSize <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
#endif
      TYPE* pNewData = NULL;
      if (m_nSize != 0)
      {
#undef new
         pNewData = (TYPE*) new BYTE[m_nSize * sizeof(TYPE)];
#define new DEBUG_NEW
         // copy new data from old
         ::gen::memcpy_s(pNewData, m_nSize * sizeof(TYPE),
            m_pData, m_nSize * sizeof(TYPE));
      }

      // get rid of old stuff (note: no destructors called)
      delete[] (BYTE*)m_pData;
      m_pData = pNewData;
      m_nMaxSize = m_nSize;
   }
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::set_at_grow(index nIndex, ARG_TYPE newElement)
{
   ASSERT_VALID(this);
//   ASSERT(nIndex >= 0);

   if(nIndex < 0)
      throw invalid_index_exception(get_app());

   if (nIndex >= m_nSize)
      set_size(nIndex+1, -1);
   m_pData[nIndex] = newElement;
}

template<class TYPE, class ARG_TYPE>
TYPE base_array<TYPE, ARG_TYPE>::get_at_grow(index nIndex)
{
   return element_at_grow(nIndex);
}


template<class TYPE, class ARG_TYPE>
TYPE & base_array<TYPE, ARG_TYPE>::element_at_grow(index nIndex)
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
void base_array<TYPE, ARG_TYPE>::insert_at(index nIndex, ARG_TYPE newElement, ::count nCount /*=1*/)
{
   ASSERT_VALID(this);
   ASSERT(nIndex >= 0);    // will expand to meet need
   ASSERT(nCount > 0);     // zero or negative size not allowed

   if(nIndex < 0 || nCount <= 0)
      throw invalid_argument_exception(get_app());

   if (nIndex >= m_nSize)
   {
      // adding after the end of the base_array
      set_size(nIndex + nCount, -1);   // grow so nIndex is valid
   }
   else
   {
      // inserting in the middle of the base_array
      ::count nOldSize = m_nSize;
      set_size(m_nSize + nCount, -1);  // grow it to new size
      // destroy intial data before copying over it
      int32_t i;
      for(i = 0; i < nCount; i++ )
         (m_pData + nOldSize + i)->~TYPE();
      // shift old data up to fill gap
      ::gen::memmove_s(m_pData + nIndex + nCount, (nOldSize-nIndex) * sizeof(TYPE),
         m_pData + nIndex, (nOldSize-nIndex) * sizeof(TYPE));

      // re-init slots we copied from
      memset((void *)(m_pData + nIndex), 0, (size_t)nCount * sizeof(TYPE));
      for(i = 0; i < nCount; i++ )
      {
#undef new
         ::new( (void *)( m_pData + nIndex + i ) ) TYPE;
#define new DEBUG_NEW
      }
   }

   // insert new value in the gap
   ASSERT(nIndex + nCount <= m_nSize);
   while (nCount--)
      m_pData[nIndex++] = newElement;
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::remove_at(index nIndex, ::count nCount)
{
//   ASSERT_VALID(this);
//   ASSERT(nIndex >= 0);
//   ASSERT(nCount >= 0);
   index nUpperBound = nIndex + nCount;
//   ASSERT(nUpperBound <= m_nSize && nUpperBound >= nIndex && nUpperBound >= nCount);

   if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
      throw invalid_argument_exception(get_app());

   // just remove a range
   ::count nMoveCount = m_nSize - (nUpperBound);
   for( int32_t i = 0; i < nCount; i++ )
      (m_pData + nIndex + i)->~TYPE();
   if (nMoveCount)
   {
      ::gen::memmove_s(m_pData + nIndex, (size_t)nMoveCount * sizeof(TYPE),
         m_pData + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));
   }
   m_nSize -= nCount;
}


template<class TYPE, class ARG_TYPE>
typename base_array<TYPE, ARG_TYPE>::iterator base_array<TYPE, ARG_TYPE>::erase(iterator pos)
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
typename  base_array<TYPE, ARG_TYPE>::iterator base_array<TYPE, ARG_TYPE>::erase(iterator begin, iterator last)
{
   if(begin.m_parray == this && last.m_parray == this)
   {
      if(begin.m_i >= 0 && begin.m_i < get_size())
      {
         index nCount = last.m_i - begin.m_i;
         if(nCount > 0)
         {
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
   else
   {
      return end();
   }
}


template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::
insert_at(index nStartIndex, base_array* pNewArray)
{
   insert_array_at(nStartIndex, pNewArray);
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::
insert_array_at(index nStartIndex, base_array* pNewArray)
{
   if(this == pNewArray)
   {
      base_array<TYPE, ARG_TYPE> arrayCopy(*this);
      return insert_array_at(nStartIndex, &arrayCopy);
   }
   ASSERT_VALID(this);
   ASSERT(pNewArray != NULL);
   ASSERT_VALID(pNewArray);
   ASSERT(nStartIndex >= 0);

   if(pNewArray == NULL || nStartIndex < 0)
      throw invalid_argument_exception(get_app());

   if (pNewArray->get_size() > 0)
   {
      insert_at(nStartIndex, pNewArray->get_at(0), pNewArray->get_size());
      for (index i = 0; i < pNewArray->get_size(); i++)
         set_at(nStartIndex + i, pNewArray->get_at(i));
   }
}
/*
template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   ::radix::object::Serialize(ar);
   if (ar.IsStoring())
   {
      ar.WriteCount(m_nSize);
   }
   else
   {
      uint_ptr nOldSize = ar.ReadCount();
      set_size(nOldSize, -1);
   }
   SerializeElements<TYPE>(ar, m_pData, m_nSize);
}
*/

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::assert_valid() const
{
   ::radix::object::assert_valid();

   if (m_pData == NULL)
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
::count base_array<TYPE, ARG_TYPE>::
add_array(const base_array& src)
{
   if(this == &src)
   {
      base_array<TYPE, ARG_TYPE> arrayCopy(*this);
      return add_array(arrayCopy);
   }
   ASSERT_VALID(this);

   ::count nOldSize = m_nSize;
   set_size(m_nSize + src.m_nSize);
   CopyElements<TYPE>(m_pData + nOldSize, src.m_pData, src.m_nSize);
   return nOldSize;
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::copy(const base_array& src)
{
   ASSERT_VALID(this);
   if(this != &src)
   {
      set_size(src.m_nSize);
      CopyElements<TYPE>(m_pData, src.m_pData, src.m_nSize);
   }
}


template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::dump(dump_context & dumpcontext) const
{
   ::radix::object::dump(dumpcontext);

   dumpcontext << "with " << m_nSize << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      dumpcontext << "\n";
      dump_elements<TYPE>(dumpcontext, m_pData, m_nSize);
   }

   dumpcontext << "\n";
}


#define new DEBUG_NEW


typedef base_array < waitable * > sync_object_ptra;



