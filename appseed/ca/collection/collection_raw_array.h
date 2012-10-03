#pragma once


//#undef new


#define new DEBUG_NEW


#ifdef DEBUG
#define TEMPLATE_TYPE_NEW new(__FILE__ + string(" - ") + typeid(TYPE).name(), __LINE__)
#else
#define TEMPLATE_TYPE_NEW new
#endif


#undef new


#define new TEMPLATE_TYPE_NEW


#ifndef __max
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif


// raw array is a special array and should be used with care
// it uses operations like memmove and memcopy to move objects and does not
// call constructors and destructors for the elements
// it is faster than the more generic arrays and is proper for use
// with strict structs and primitive data types


template<class TYPE, class ARG_TYPE = const TYPE &>
class raw_array :
   virtual public ::radix::object
{
public:


   class iterator
   {
   public:


      index            m_i;
      raw_array *     m_parray;

      iterator(index i, raw_array * parray)
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

      iterator & operator +(int i)
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



   raw_array(count nGrowBy = 32);

   inline count get_size() const;
   inline count get_size_in_bytes() const;
   inline count get_count() const;
   inline count get_byte_count() const;
   inline bool is_empty(count countMinimum = 1) const;
   inline bool has_elements(count countMinimum = 1) const;
   inline index get_upper_bound(index i = 0) const;
   count set_size(index nNewSize, count nGrowBy = -1);
   count set_size_in_bytes(index nNewSize, count nGrowBy = -1);

   void free_extra();
   count remove_all();
   void remove_last();



   // Accessing elements
   inline const TYPE& get_at(index nIndex) const;
   inline TYPE& get_at(index nIndex);
   inline void set_at(index nIndex, ARG_TYPE newElement);

   inline const TYPE & element_at(index nIndex) const;
   inline TYPE & element_at(index nIndex);

   inline const TYPE& first_element(index index = 0) const;
   inline TYPE& first_element(index index = 0);

   inline const TYPE& last_element(index index = 0) const;
   inline TYPE& last_element(index index = 0);

   // Direct Access to the element data (may return NULL)
   inline const TYPE* get_data() const;
   inline TYPE* get_data();

   // Potentially growing the raw_array
   void set_at_grow(index nIndex, ARG_TYPE newElement);
   index add(ARG_TYPE newElement);
   index add(const raw_array& src);
   index append(const raw_array& src);
   void copy(const raw_array& src);
   index push(ARG_TYPE newElement);
   void push_back(const TYPE & newElement);



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
   void insert_at(index nIndex, ARG_TYPE newElement, count nCount = 1);
   index remove_at(index nIndex, count nCount = 1);
   void insert_at(index nStartIndex, raw_array* pNewArray);
   TYPE pop(index index = 0);
   void swap(index index1, index index2);

   raw_array & operator = (const raw_array & src);


   TYPE *   m_pData;    // the actual raw_array of data
   count    m_nSize;    // # of elements (upperBound - 1)
   count    m_nMaxSize; // max allocated
   count    m_nGrowBy;  // grow amount

public:
   virtual ~raw_array();
   void dump(dump_context&) const;
   void assert_valid() const;

   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;

};

/////////////////////////////////////////////////////////////////////////////
// raw_array<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
inline count raw_array<TYPE, ARG_TYPE>::get_size() const
{
   return m_nSize;
}

template<class TYPE, class ARG_TYPE>
inline count raw_array<TYPE, ARG_TYPE>::get_size_in_bytes() const
{
   return m_nSize * sizeof(TYPE);
}

template<class TYPE, class ARG_TYPE>
inline count raw_array<TYPE, ARG_TYPE>::get_count() const
{
   return this->get_size();
}

template<class TYPE, class ARG_TYPE>
inline count raw_array<TYPE, ARG_TYPE>::get_byte_count() const
{
   return this->get_size_in_bytes();
}

template<class TYPE, class ARG_TYPE>
inline bool raw_array<TYPE, ARG_TYPE>::is_empty(count countMinimum) const
{
   return m_nSize < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool raw_array<TYPE, ARG_TYPE>::has_elements(count countMinimum) const
{
   return m_nSize >= countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline index raw_array<TYPE, ARG_TYPE>::get_upper_bound(index index) const
{
   return m_nSize - 1 - index;
}

template<class TYPE, class ARG_TYPE>
inline count raw_array<TYPE, ARG_TYPE>::remove_all()
{
   return set_size(0, -1);
}

template<class TYPE, class ARG_TYPE>
inline void raw_array<TYPE, ARG_TYPE>::remove_last()
{
   remove_at(get_upper_bound());
}

template<class TYPE, class ARG_TYPE>
inline TYPE& raw_array<TYPE, ARG_TYPE>::get_at(index nIndex)
{
//   if(nIndex >= 0 && nIndex < m_nSize)
      return m_pData[nIndex];
//   throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& raw_array<TYPE, ARG_TYPE>::get_at(index nIndex) const
{
//   if(nIndex >= 0 && nIndex < m_nSize)
      return m_pData[nIndex];
  // throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline void raw_array<TYPE, ARG_TYPE>::set_at(index nIndex, ARG_TYPE newElement)
{
//   if(nIndex >= 0 && nIndex < m_nSize)
      m_pData[nIndex] = newElement;
  // else
    //  throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& raw_array<TYPE, ARG_TYPE>::element_at(index nIndex) const
{
//   if(nIndex >= 0 && nIndex < m_nSize)
      return m_pData[nIndex];
  // throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline TYPE& raw_array<TYPE, ARG_TYPE>::element_at(index nIndex)
{
//   if(nIndex >= 0 && nIndex < m_nSize)
      return m_pData[nIndex];
  // throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& raw_array<TYPE, ARG_TYPE>::first_element(index nIndex) const
{
   return this->element_at(nIndex);
}
template<class TYPE, class ARG_TYPE>
inline TYPE& raw_array<TYPE, ARG_TYPE>::first_element(index nIndex)
{
   return this->element_at(nIndex);
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& raw_array<TYPE, ARG_TYPE>::last_element(index index) const
{
   index  = get_upper_bound(index);
//   ASSERT(index >= 0 && index < m_nSize);
  // if(index >= 0 && index < m_nSize)
      return m_pData[index];
//   throw invalid_argument_exception(get_app());
}
template<class TYPE, class ARG_TYPE>
inline TYPE& raw_array<TYPE, ARG_TYPE>::last_element(index index)
{
   index  = get_upper_bound(index);
//   ASSERT(index >= 0 && index < m_nSize);
  // if(index >= 0 && index < m_nSize)
      return m_pData[index];
//   throw invalid_argument_exception(get_app());
}

template<class TYPE, class ARG_TYPE>
inline const TYPE* raw_array<TYPE, ARG_TYPE>::get_data() const
{
   return (const TYPE*)m_pData;
}

template<class TYPE, class ARG_TYPE>
inline TYPE* raw_array<TYPE, ARG_TYPE>::get_data()
{
   return (TYPE*)m_pData;
}

template<class TYPE, class ARG_TYPE>
inline index raw_array<TYPE, ARG_TYPE>::add(ARG_TYPE newElement)
{
   index nIndex = m_nSize;
   set_at_grow(nIndex, newElement);
   return nIndex;
}

template<class TYPE, class ARG_TYPE>
inline void raw_array<TYPE, ARG_TYPE>::push_back(const TYPE & newElement)
{
   set_at_grow(m_nSize, newElement);
}

template<class TYPE, class ARG_TYPE>
inline index raw_array<TYPE, ARG_TYPE>::add(const raw_array & src)
{
   return append(src);
}

template<class TYPE, class ARG_TYPE>
inline index raw_array<TYPE, ARG_TYPE>::push(ARG_TYPE newElement)
{
   return add(newElement);
}

template<class TYPE, class ARG_TYPE>
inline const TYPE& raw_array<TYPE, ARG_TYPE>::operator[](index nIndex) const
{
   return element_at(nIndex);
}

template<class TYPE, class ARG_TYPE>
inline TYPE& raw_array<TYPE, ARG_TYPE>::operator[](index nIndex)
{
   return this->element_at(nIndex);
}

template<class TYPE, class ARG_TYPE>
inline TYPE raw_array<TYPE, ARG_TYPE>::pop(index index)
{
   
   index = get_upper_bound(index);
   
   if(index < 0 || index >= m_nSize)
      throw invalid_argument_exception(get_app());
   
   TYPE t = m_pData[index];

   remove_at(index);

   return t;

}

template<class TYPE, class ARG_TYPE>
inline void raw_array<TYPE, ARG_TYPE>::swap(index index1, index index2)
{
   TYPE t = m_pData[index2];
   m_pData[index2] = m_pData[index1];
   m_pData[index1] = t;
}

template<class TYPE, class ARG_TYPE>
inline raw_array<TYPE, ARG_TYPE> & raw_array<TYPE, ARG_TYPE>::operator = (const raw_array & src)
{
   if(&src != this)
   {
      copy(src);
   }
   return *this;
}

// out-of-line functions

template<class TYPE, class ARG_TYPE>
raw_array<TYPE, ARG_TYPE>::raw_array(count nGrowBy)
{
   m_nGrowBy = max(0, nGrowBy);
   m_pData = NULL;
   m_nSize = m_nMaxSize = 0;
}

template<class TYPE, class ARG_TYPE>
raw_array<TYPE, ARG_TYPE>::~raw_array()
{
   ASSERT_VALID(this);

   if (m_pData != NULL)
   {
      for( int i = 0; i < m_nSize; i++ )
         (m_pData + i)->~TYPE();
      delete[] (BYTE*)m_pData;
   }
}

template<class TYPE, class ARG_TYPE>
count raw_array<TYPE, ARG_TYPE>::set_size_in_bytes(count nNewSize, count nGrowBy)
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
count raw_array<TYPE, ARG_TYPE>::set_size(count nNewSize, count nGrowBy)
{
   //ASSERT_VALID(this);
   //ASSERT(nNewSize >= 0);

   if(nNewSize < 0 )
      throw invalid_argument_exception(get_app());

   if (nGrowBy >= 0)
      m_nGrowBy = nGrowBy;  // set new size

   if (nNewSize == 0)
   {
      // shrink to nothing
      if (m_pData != NULL)
      {
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
      if(nNewSize > SIZE_T_MAX/sizeof(TYPE)) // no overflow
         throw invalid_argument_exception(get_app());
#endif

      count nAllocSize = __max(nNewSize, m_nGrowBy);
      m_pData = (TYPE*) new BYTE[(size_t)nAllocSize * sizeof(TYPE)];
      memset((void *)m_pData, 0, (size_t)nAllocSize * sizeof(TYPE));
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
      }
      m_nSize = nNewSize;
   }
   else
   {
      // otherwise, grow raw_array
      nGrowBy = m_nGrowBy;
      if (nGrowBy == 0)
      {
         // heuristically determine growth when nGrowBy == 0
         //  (this avoids heap fragmentation in many situations)
         nGrowBy = m_nSize / 8;
         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
      }
      count nNewMax;
      if (nNewSize < m_nMaxSize + nGrowBy)
         nNewMax = m_nMaxSize + nGrowBy;  // granularity
      else
         nNewMax = nNewSize;  // no slush

      //ASSERT(nNewMax >= m_nMaxSize);  // no wrap around

      if(nNewMax  < m_nMaxSize) // no wrap around
         throw invalid_argument_exception(get_app());

#ifdef SIZE_T_MAX
      if(nNewSize > SIZE_T_MAX/sizeof(TYPE)) // no overflow
         throw invalid_argument_exception(get_app());
#endif

      TYPE* pNewData = (TYPE*) new BYTE[(size_t)nNewMax * sizeof(TYPE)];

      // copy new data from old
      ::gen::memcpy_s(pNewData, (size_t)nNewMax * sizeof(TYPE),
         m_pData, (size_t)m_nSize * sizeof(TYPE));

      // construct remaining elements
      //ASSERT(nNewSize > m_nSize);
      //if(nNewSize  >= m_nSize)
        // throw invalid_argument_exception(get_app());
      memset((void *)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
      delete[] (BYTE*)m_pData;
      m_pData = pNewData;
      m_nSize = nNewSize;
      m_nMaxSize = nNewMax;
   }
   return m_nSize;
}

template<class TYPE, class ARG_TYPE>
index raw_array<TYPE, ARG_TYPE>::append(const raw_array& src)
{
   ASSERT_VALID(this);
   ASSERT(this != &src);   // cannot append to itself

   if(this == &src)
      throw invalid_argument_exception(get_app());

   count nOldSize = m_nSize;
   set_size(m_nSize + src.m_nSize);
   CopyElements<TYPE>(m_pData + nOldSize, src.m_pData, src.m_nSize);
   return nOldSize;
}

template<class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::copy(const raw_array& src)
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
void raw_array<TYPE, ARG_TYPE>::free_extra()
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
         pNewData = (TYPE*) new BYTE[m_nSize * sizeof(TYPE)];
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
void raw_array<TYPE, ARG_TYPE>::set_at_grow(index nIndex, ARG_TYPE newElement)
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
void raw_array<TYPE, ARG_TYPE>::insert_at(index nIndex, ARG_TYPE newElement, count nCount /*=1*/)
{
   //ASSERT_VALID(this);
   //ASSERT(nIndex >= 0);    // will expand to meet need
   //ASSERT(nCount > 0);     // zero or negative size not allowed

   if(nIndex < 0 || nCount <= 0)
      throw invalid_argument_exception(get_app());

   if (nIndex >= m_nSize)
   {
      // adding after the end of the raw_array
      set_size(nIndex + nCount, -1);   // grow so nIndex is valid
   }
   else
   {
      // inserting in the middle of the raw_array
      count nOldSize = m_nSize;
      set_size(m_nSize + nCount, -1);  // grow it to new size
      // destroy intial data before copying over it
      // shift old data up to fill gap
      ::gen::memmove_s(m_pData + nIndex + nCount, (nOldSize-nIndex) * sizeof(TYPE),
         m_pData + nIndex, (nOldSize-nIndex) * sizeof(TYPE));

      // re-init slots we copied from
      memset((void *)(m_pData + nIndex), 0, (size_t)nCount * sizeof(TYPE));
#undef new
      for( int i = 0; i < nCount; i++ )
         ::new( (void *)( m_pData + nIndex + i ) ) TYPE;
#define new DEBUG_NEW
   }

   // insert new value in the gap
   ASSERT(nIndex + nCount <= m_nSize);
   while (nCount--)
      m_pData[nIndex++] = newElement;
}

template<class TYPE, class ARG_TYPE>
inline index raw_array<TYPE, ARG_TYPE>::remove_at(index nIndex, count nCount)
{

   //ASSERT_VALID(this);

   index nUpperBound = nIndex + nCount;

   if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
      throw invalid_argument_exception(get_app());

   // just remove a range
   count nMoveCount = m_nSize - (nUpperBound);
   if (nMoveCount)
   {
      ::gen::memmove_s(m_pData + nIndex, (size_t)nMoveCount * sizeof(TYPE),
         m_pData + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));
   }
   m_nSize -= nCount;
   return nIndex;
}

template<class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::insert_at(index nStartIndex, raw_array* pNewArray)
{
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
template<class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::dump(dump_context & dumpcontext) const
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

template<class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::assert_valid() const
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
typename raw_array<TYPE, ARG_TYPE>::iterator raw_array<TYPE, ARG_TYPE>::erase(iterator pos)
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
typename  raw_array<TYPE, ARG_TYPE>::iterator raw_array<TYPE, ARG_TYPE>::erase(iterator begin, iterator last)
{
   if(begin.m_parray == this && last.m_parray == this)
   {
      if(begin.m_i >= 0 && begin.m_i < this->get_size())
      {
         count nCount = last.m_i - begin.m_i;
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


#define new DEBUG_NEW


