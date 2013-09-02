#pragma once

#undef new
#define new C_NEW

// raw array is a special array and should be used with care
// it uses operations like memmove and memcopy to move objects and does not
// call constructors and destructors for the elements
// it is faster than the more generic arrays and is proper for use
// with strict structs and primitive data types

template<class TYPE, class ARG_TYPE = const TYPE &>
class array :
   virtual public ::ca::ca
{
public:
   array();

   ::count get_count() const;
   ::count set_size(index nNewSize, ::count nGrowBy = -1);

   ::count remove_all();



   // Accessing elements
   const TYPE& get_at(index nIndex) const;
   TYPE& get_at(index nIndex);
   void set_at(index nIndex, ARG_TYPE newElement);

   const TYPE& element_at(index nIndex) const;
   TYPE& element_at(index nIndex);

   // Direct Access to the element data (may return NULL)
   const TYPE* get_data() const;
   TYPE* get_data();

   // Potentially growing the array
   void set_at_grow(index nIndex, ARG_TYPE newElement);
   index add(ARG_TYPE newElement);
   ::count add(const array& src);
   ::count copy(const array& src);



   // overloaded operator helpers
   const TYPE& operator[](index nIndex) const;
   TYPE& operator[](index nIndex);

   // Operations that move elements around
   void insert_at(index nIndex, ARG_TYPE newElement, ::count nCount = 1);
   index remove_at(index nIndex, ::count nCount = 1);
   void insert_at(index nStartIndex, array* pNewArray);
   void swap(index index1, index index2);

   array & operator = (const array & src);

// Implementation
protected:
   TYPE *   m_pData;    // the actual array of data
   ::count m_nSize;    // # of elements (upperBound - 1)
   ::count m_nMaxSize; // max allocated
   ::count m_nGrowBy;  // grow amount

public:
   virtual ~array();

   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;

};


template<class TYPE, class ARG_TYPE>
inline ::count array<TYPE, ARG_TYPE>::get_count() const
{
   return m_nSize;
}


template<class TYPE, class ARG_TYPE>
inline ::count array<TYPE, ARG_TYPE>::remove_all()
{
   return set_size(0, -1);
}

template<class TYPE, class ARG_TYPE>
inline TYPE& array<TYPE, ARG_TYPE>::get_at(index nIndex)
{
   return m_pData[nIndex];
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& array<TYPE, ARG_TYPE>::get_at(index nIndex) const
{
   return m_pData[nIndex];
}
template<class TYPE, class ARG_TYPE>
inline void array<TYPE, ARG_TYPE>::set_at(index nIndex, ARG_TYPE newElement)
{
   m_pData[nIndex] = newElement;
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& array<TYPE, ARG_TYPE>::element_at(index nIndex) const
{
   return m_pData[nIndex];
}
template<class TYPE, class ARG_TYPE>
inline TYPE& array<TYPE, ARG_TYPE>::element_at(index nIndex)
{
   return m_pData[nIndex];
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
inline ::count array<TYPE, ARG_TYPE>::add(const array & a)
{
   for(int32_t i = 0; i < a.get_count(); i++)
   {
      add(a[i]);
   }
   return this->get_count();
}

template<class TYPE, class ARG_TYPE>
inline ::count array<TYPE, ARG_TYPE>::copy(const array & a)
{
   remove_all();
   return add(a);
}

template<class TYPE, class ARG_TYPE>
inline const TYPE& array<TYPE, ARG_TYPE>::operator[](index nIndex) const
{
   return get_at(nIndex);
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

template<class TYPE, class ARG_TYPE>
array<TYPE, ARG_TYPE>::array()
{
   m_pData = NULL;
   m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

template<class TYPE, class ARG_TYPE>
array<TYPE, ARG_TYPE>::~array()
{
   if (m_pData != NULL)
   {
      for( int32_t i = 0; i < m_nSize; i++ )
         (m_pData + i)->~TYPE();
      delete[] (BYTE*)m_pData;
   }
}


template<class TYPE, class ARG_TYPE>
::count array<TYPE, ARG_TYPE>::set_size(::count nNewSize, ::count nGrowBy)
{

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
      ::count nAllocSize = max(nNewSize, m_nGrowBy);
      m_pData = (TYPE*) new BYTE[(size_t)nAllocSize * sizeof(TYPE)];
      memset_dup((void *)m_pData, 0, (size_t)nAllocSize * sizeof(TYPE));
      m_nSize = nNewSize;
      m_nMaxSize = nAllocSize;
   }
   else if (nNewSize <= m_nMaxSize)
   {
      // it fits
      if (nNewSize > m_nSize)
      {
         // initialize the new elements
         memset_dup((void *)(m_pData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
      }
      m_nSize = nNewSize;
   }
   else
   {
      // otherwise, grow array
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

      TYPE* pNewData = (TYPE*) new BYTE[(size_t)nNewMax * sizeof(TYPE)];

      // copy new data from old
      memcpy_dup(pNewData, m_pData, (size_t)m_nSize * sizeof(TYPE));

      // construct remaining elements
      memset_dup((void *)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
      delete[] (BYTE*)m_pData;
      m_pData = pNewData;
      m_nSize = nNewSize;
      m_nMaxSize = nNewMax;
   }
   return m_nSize;
}




template<class TYPE, class ARG_TYPE>
void array<TYPE, ARG_TYPE>::set_at_grow(index nIndex, ARG_TYPE newElement)
{

   if (nIndex >= m_nSize)
      set_size(nIndex+1, -1);
   m_pData[nIndex] = newElement;
}

template<class TYPE, class ARG_TYPE>
void array<TYPE, ARG_TYPE>::insert_at(index nIndex, ARG_TYPE newElement, ::count nCount /*=1*/)
{

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
      memmov_dup(m_pData + nIndex + nCount, m_pData + nIndex, (nOldSize-nIndex) * sizeof(TYPE));

      // re-init slots we copied from
      memset_dup((void *)(m_pData + nIndex), 0, (size_t)nCount * sizeof(TYPE));
#undef new
      for( int32_t i = 0; i < nCount; i++ )
         ::new( (void *)( m_pData + nIndex + i ) ) TYPE;
#define new C_NEW
   }

   while (nCount--)
      m_pData[nIndex++] = newElement;
}

template<class TYPE, class ARG_TYPE>
index array<TYPE, ARG_TYPE>::remove_at(index nIndex, ::count nCount)
{
   index nUpperBound = nIndex + nCount;

   // just remove a range
   ::count nMoveCount = m_nSize - (nUpperBound);
   if (nMoveCount)
   {
      memmov_dup(m_pData + nIndex, m_pData + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));
   }
   m_nSize -= nCount;
   return nIndex;
}

template<class TYPE, class ARG_TYPE>
void array<TYPE, ARG_TYPE>::insert_at(index nStartIndex, array* pNewArray)
{
   if (pNewArray->get_count() > 0)
   {
      insert_at(nStartIndex, pNewArray->get_at(0), pNewArray->get_count());
      for (index i = 0; i < pNewArray->get_count(); i++)
         set_at(nStartIndex + i, pNewArray->get_at(i));
   }
}




class CLASS_DECL_c simple_int_array :
   virtual public array < int32_t >
{
public:
};


class CLASS_DECL_c uint_array :
   virtual public array < uint32_t >
{
public:
};

class CLASS_DECL_c simple_int64_array :
   virtual public array < int64_t >
{
public:
};


class CLASS_DECL_c simple_uint64_array :
   virtual public array < uint64_t >
{
public:
};



class CLASS_DECL_c simple_double_array :
   virtual public array < double >
{
public:
   double average();
};



#undef new
#define new DEBUG_NEW


