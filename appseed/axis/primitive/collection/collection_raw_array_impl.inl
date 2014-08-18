#pragma once

//
// see collection_raw_array_decl.h for declaration
//
// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements

template<class TYPE, class ARG_TYPE>
inline ::count raw_array<TYPE, ARG_TYPE>::get_size() const
{
   return m_nSize;
}

template<class TYPE, class ARG_TYPE>
inline ::count raw_array<TYPE, ARG_TYPE>::get_size_in_bytes() const
{
   return m_nSize * sizeof(TYPE);
}

template<class TYPE, class ARG_TYPE>
inline ::count raw_array<TYPE, ARG_TYPE>::get_count() const
{
   return this->get_size();
}

template<class TYPE, class ARG_TYPE>
inline ::count raw_array<TYPE, ARG_TYPE>::get_byte_count() const
{
   return this->get_size_in_bytes();
}

template<class TYPE, class ARG_TYPE>
inline ::count raw_array<TYPE, ARG_TYPE>::size() const
{
   return this->get_size();
}

template<class TYPE, class ARG_TYPE>
inline ::count raw_array<TYPE, ARG_TYPE>::count() const
{
   return this->get_count();
}

template<class TYPE, class ARG_TYPE>
inline bool raw_array<TYPE, ARG_TYPE>::is_empty(::count countMinimum) const
{
   return m_nSize < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool raw_array<TYPE, ARG_TYPE>::empty(::count countMinimum) const
{
   return m_nSize < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool raw_array<TYPE, ARG_TYPE>::has_elements(::count countMinimum) const
{
   return m_nSize >= countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline index raw_array<TYPE, ARG_TYPE>::get_upper_bound(index index) const
{
   return m_nSize + index;
}

template<class TYPE, class ARG_TYPE>
inline ::count raw_array<TYPE, ARG_TYPE>::remove_all()
{
   return allocate(0, -1);
}

template <class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::
   clear()
{
   remove_all();
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
   return element_at(get_upper_bound(index));
}


template<class TYPE, class ARG_TYPE>
inline TYPE& raw_array<TYPE, ARG_TYPE>::last_element(index index)
{
   return element_at(get_upper_bound(index));
}


template<class TYPE, class ARG_TYPE>
inline TYPE & raw_array<TYPE, ARG_TYPE>::front(index n)
{
   return first_element(n);
}

template<class TYPE, class ARG_TYPE>
inline const TYPE & raw_array<TYPE, ARG_TYPE>::front(index n) const
{
   return first_element(n);
}

template<class TYPE, class ARG_TYPE>
inline TYPE & raw_array<TYPE, ARG_TYPE>::back(index n)
{
   return last_element(n);
}

template<class TYPE, class ARG_TYPE>
inline const TYPE & raw_array<TYPE, ARG_TYPE>::back(index n) const
{
   return last_element(n);
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
inline index raw_array<TYPE, ARG_TYPE>::add(const raw_array & src)
{
   return append(src);
}


template<class TYPE, class ARG_TYPE>
inline index raw_array<TYPE, ARG_TYPE>::add_new(::count count)
{
   allocate(m_nSize + count);
   return get_upper_bound();
}

template<class TYPE, class ARG_TYPE>
inline TYPE & raw_array<TYPE, ARG_TYPE>::add_new()
{
   allocate(m_nSize + 1);
   return last_element();
}


template<class TYPE, class ARG_TYPE>
inline TYPE raw_array<TYPE, ARG_TYPE>::pop(index n)
{

   index i = get_upper_bound(n);

   TYPE t = element_at(i);

   remove_at(i);

   return t;

}

template<class TYPE, class ARG_TYPE>
inline void raw_array<TYPE, ARG_TYPE>::pop_back(index n)
{

   remove_at(get_upper_bound(n));

}

template<class TYPE, class ARG_TYPE>
inline index raw_array<TYPE, ARG_TYPE>::push(ARG_TYPE newElement, index n)
{
   return insert_at(get_upper_bound(n), newElement);
}

template<class TYPE, class ARG_TYPE>
inline void raw_array<TYPE, ARG_TYPE>::push_back(ARG_TYPE newElement, index n)
{
   insert_at(get_upper_bound(n), newElement);
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
inline void raw_array<TYPE, ARG_TYPE>::swap(index index1, index index2)
{
   TYPE t = m_pData[index1];
   m_pData[index1] = m_pData[index2];
   m_pData[index2] = t;
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
raw_array<TYPE, ARG_TYPE>::raw_array(sp(::axis::application) papp, ::count nGrowBy) :
element(papp)
{
   m_nGrowBy = max(0, nGrowBy);
   m_pData = NULL;
   m_nSize = m_nMaxSize = 0;
}

template<class TYPE, class ARG_TYPE>
raw_array<TYPE, ARG_TYPE>::raw_array(const raw_array <TYPE, ARG_TYPE> & a) :
element(a.get_app())
{
   m_nGrowBy = 32;
   m_pData = NULL;
   m_nSize = m_nMaxSize = 0;
   operator = (a);
}

#ifdef MOVE_SEMANTICS
template<class TYPE,class ARG_TYPE>
raw_array<TYPE,ARG_TYPE>::raw_array(raw_array <TYPE,ARG_TYPE> && a):
element(a.get_app())
{

   m_nGrowBy = a.m_nGrowBy;
   m_pData = a.m_pData;
   m_nSize = a.m_nSize;
   m_nMaxSize = a.m_nMaxSize;

   //a.m_nGrowBy = 0;
   a.m_pData = NULL;
   //a.m_nSize = 0;
   //a.m_nMaxSize = 0;

}
#endif

template<class TYPE, class ARG_TYPE>
raw_array<TYPE, ARG_TYPE>:: raw_array(::count n)
{
   m_nGrowBy = 32;
   m_pData = NULL;
   m_nSize = m_nMaxSize = 0;
   allocate(n);
}

template<class TYPE, class ARG_TYPE>
raw_array<TYPE, ARG_TYPE>::raw_array(ARG_TYPE t, ::count n)
{
   m_nGrowBy = 32;
   m_pData = NULL;
   m_nSize = m_nMaxSize = 0;
   insert_at(0, t, n);
}


template<class TYPE, class ARG_TYPE>
raw_array<TYPE, ARG_TYPE>::raw_array(TYPE * ptypea, ::count n)
{
   m_nGrowBy = 32;
   m_pData = NULL;
   m_nSize = m_nMaxSize = 0;
   allocate(n);
   for(int i = 0; i < n; i++)
   {
      element_at(i) = ptypea[i];
   }
}



template<class TYPE, class ARG_TYPE>
raw_array<TYPE, ARG_TYPE>::~raw_array()
{

   destroy();

}

template<class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::destroy()
{
   if (m_pData != NULL)
   {
      for( int32_t i = 0; i < m_nSize; i++ )
         (m_pData + i)->~TYPE();
      delete[] (BYTE*)m_pData;
      m_pData     = NULL;
      m_nSize     = 0;
      m_nMaxSize  = 0;
   }

}


template<class TYPE, class ARG_TYPE>
::count raw_array<TYPE, ARG_TYPE>::set_size(::count nNewSize, ::count nGrowBy)
{
   return allocate(nNewSize, nGrowBy);
}


template<class TYPE, class ARG_TYPE>
::count raw_array<TYPE, ARG_TYPE>::resize(::count nNewSize, ::count nGrowBy)
{
   return allocate(nNewSize, nGrowBy);
}


template<class TYPE, class ARG_TYPE>
::count raw_array<TYPE, ARG_TYPE>::allocate_in_bytes(::count nNewSize, ::count nGrowBy)
{
   if(nGrowBy < 0)
   {
      return allocate(nNewSize / sizeof(TYPE), -1);
   }
   else
   {
      return allocate(nNewSize / sizeof(TYPE), nGrowBy / sizeof(TYPE));
   }
}

template<class TYPE, class ARG_TYPE>
::count raw_array<TYPE, ARG_TYPE>::allocate(::count nNewSize, ::count nGrowBy)
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
//         for( int32_t i = 0; i < m_nSize; i++ )
//            (m_pData + i)->~TYPE();
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
//#undef new
      m_pData = (TYPE*) new BYTE[(size_t)nAllocSize * sizeof(TYPE)];
      //memset((void *)m_pData, 0, (size_t)nAllocSize * sizeof(TYPE));
//      for( index i = 0; i < nNewSize; i++ )
  //       ::new( (void *)( m_pData + i ) ) TYPE;
//#define new AXIS_NEW
      m_nSize = nNewSize;
      m_nMaxSize = nAllocSize;
   }
   else if (nNewSize <= m_nMaxSize)
   {
      // it fits
      if (nNewSize > m_nSize)
      {
         // initialize the new elements
//         memset((void *)(m_pData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
//         for( int32_t i = 0; i < nNewSize-m_nSize; i++ )
//#undef new
//            ::new( (void *)( m_pData + m_nSize + i ) ) TYPE;
//#define new AXIS_NEW
      }
      else if (m_nSize > nNewSize)
      {
         // destroy the old elements
//         for( int32_t i = 0; i < m_nSize-nNewSize; i++ )
  //          (m_pData + nNewSize + i)->~TYPE();
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
#define new AXIS_NEW

      // copy new data from old
      ::axis::memcpy_s(pNewData, (size_t)nNewMax * sizeof(TYPE),
         m_pData, (size_t)m_nSize * sizeof(TYPE));

      // construct remaining elements
      ASSERT(nNewSize > m_nSize);
//      memset((void *)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
//      for( int32_t i = 0; i < nNewSize-m_nSize; i++ )
//#undef new
//         ::new( (void *)( pNewData + m_nSize + i ) ) TYPE;
//#define new AXIS_NEW
      // get rid of old stuff (note: no destructors called)
      delete[] (BYTE*)m_pData;
      m_pData = pNewData;
      m_nSize = nNewSize;
      m_nMaxSize = nNewMax;
   }
   return countOld;
}

template<class TYPE, class ARG_TYPE>
index raw_array<TYPE, ARG_TYPE>::append(const raw_array & src)
{

   ASSERT_VALID(this);

   ::count nOldSize = m_nSize;

   ::count nSrcSize = src.m_nSize;   // to enable to append to itself

   allocate(m_nSize + nSrcSize);

   memcpy(m_pData + nOldSize, src.m_pData, nSrcSize * sizeof(TYPE));

   return nOldSize;

}


template<class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::copy(const raw_array & src)
{

   ASSERT_VALID(this);

   if(this == &src)
      return;

   allocate(src.m_nSize);

   memcpy(m_pData, src.m_pData, src.m_nSize * sizeof(TYPE));

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
         ::axis::memcpy_s(pNewData, m_nSize * sizeof(TYPE),
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
      allocate(nIndex+1, -1);
   m_pData[nIndex] = newElement;
}

template<class TYPE, class ARG_TYPE>
TYPE raw_array<TYPE, ARG_TYPE>::get_at_grow(index nIndex)
{
   return element_at_grow(nIndex);
}


template<class TYPE, class ARG_TYPE>
TYPE & raw_array<TYPE, ARG_TYPE>::element_at_grow(index nIndex)
{
   ASSERT_VALID(this);
   ASSERT(nIndex >= 0);

   if(nIndex < 0)
      throw invalid_argument_exception(get_app());

   if (nIndex >= m_nSize)
      allocate(nIndex+1, -1);
   return m_pData[nIndex];
}


template<class TYPE, class ARG_TYPE>
index raw_array<TYPE, ARG_TYPE>::insert_at(index nIndex, ARG_TYPE newElement, ::count nCount /*=1*/)
{
   //ASSERT_VALID(this);
   //ASSERT(nIndex >= 0);    // will expand to meet need

   if(nCount <= 0)
      return -1;

   if(nIndex < 0)
      throw invalid_argument_exception(get_app());

   if (nIndex >= m_nSize)
   {
      // adding after the end of the raw_array
      allocate(nIndex + nCount, -1);   // grow so nIndex is valid
   }
   else
   {
      // inserting in the middle of the raw_array
      ::count nOldSize = m_nSize;
      allocate(m_nSize + nCount, -1);  // grow it to new size
      // destroy intial data before copying over it
      // shift old data up to fill gap
      ::axis::memmove_s(m_pData + nIndex + nCount, (nOldSize-nIndex) * sizeof(TYPE),
         m_pData + nIndex, (nOldSize-nIndex) * sizeof(TYPE));

      // re-init slots we copied from
      memset((void *)(m_pData + nIndex), 0, (size_t)nCount * sizeof(TYPE));
   }

   // insert new value in the gap
   ASSERT(nIndex + nCount <= m_nSize);

   index nIndexParam = nIndex;

   while (nCount--)
      m_pData[nIndex++] = newElement;

   return nIndexParam;

}

template<class TYPE, class ARG_TYPE>
inline index raw_array<TYPE, ARG_TYPE>::remove_at(index nIndex, ::count nCount)
{

   //ASSERT_VALID(this);

   index nUpperBound = nIndex + nCount;

   if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
      throw invalid_argument_exception(get_app());

   // just remove a range
   ::count nMoveCount = m_nSize - (nUpperBound);
   if (nMoveCount)
   {
      ::axis::memmove_s(m_pData + nIndex, (size_t)nMoveCount * sizeof(TYPE),
         m_pData + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));
   }
   m_nSize -= nCount;
   return nIndex;
}


template<class TYPE, class ARG_TYPE>
index raw_array<TYPE, ARG_TYPE>::insert_at(index nStartIndex, raw_array * pNewArray)
{
   ASSERT_VALID(this);
   ASSERT(pNewArray != NULL);
   ASSERT_VALID(pNewArray);
   ASSERT(nStartIndex >= 0);

   if(pNewArray == NULL || nStartIndex < 0)
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
index raw_array<TYPE, ARG_TYPE>::raw_find_first(TYPE *pt, index find, index last) const
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
index raw_array<TYPE, ARG_TYPE>::find_first(ARG_TYPE t, index ( * lpfnCompare )(ARG_TYPE, ARG_TYPE), index find, index last) const
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
raw_array<TYPE, ARG_TYPE> & raw_array<TYPE, ARG_TYPE>::operator += (const raw_array & a)
{

   if(&a == this)
   {
      raw_array<TYPE, ARG_TYPE> aCopy(a);
      add(aCopy);
   }
   else
   {
      add(a);
   }
   return *this;

}

template <class TYPE, class ARG_TYPE>
raw_array<TYPE, ARG_TYPE> raw_array<TYPE, ARG_TYPE>::operator + (const raw_array & a) const
{
   raw_array<TYPE, ARG_TYPE> aNew(*this);
   aNew += a;
   return a;
}








#ifdef MOVE_SEMANTICS
template <class TYPE,class ARG_TYPE>
inline raw_array<TYPE,ARG_TYPE> & raw_array<TYPE,ARG_TYPE>::operator = (raw_array && a)
{

   if(&a != this)
   {
      destroy();

      m_nGrowBy      = a.m_nGrowBy;
      m_pData        = a.m_pData;
      m_nSize        = a.m_nSize;
      m_nMaxSize     = a.m_nMaxSize;

      a.m_pData      = NULL;

   }

   return *this;
}

#endif






template<class TYPE,class ARG_TYPE>
inline void raw_array<TYPE,ARG_TYPE>::remove_indexes(const raw_index_array & ia)
{


   // remove indexes
   for(index i = ia.get_upper_bound(); i >= 0; i--)
   {

      remove_at(ia[i]);

   }

}


template<class TYPE,class ARG_TYPE>
inline void raw_array<TYPE,ARG_TYPE>::remove_descending_indexes(const raw_index_array & ia)
{

   for(index i = 0; i < ia.get_count(); i++)
   {

      remove_at(ia[i]);

   }

}





template <class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::quick_sort(index (* fCompare)(TYPE *, TYPE *), void (* fSwap)(TYPE *, TYPE *))
{
   raw_index_array stackLowerBound;
   raw_index_array stackUpperBound;
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
void raw_array<TYPE, ARG_TYPE>::quick_sort(index (* fCompare)(TYPE *, TYPE *))
{
   raw_index_array stackLowerBound;
   raw_index_array stackUpperBound;
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
void raw_array<TYPE, ARG_TYPE>::quick_sort(index (* fCompare)(TYPE *, TYPE *), raw_index_array & ia)
{

   // minimum check
   if(ia.get_size() != get_size())
      throw invalid_argument_exception(get_app());

   raw_index_array stackLowerBound;
   raw_index_array stackUpperBound;
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
bool raw_array < TYPE, ARG_TYPE > ::
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
bool raw_array < TYPE, ARG_TYPE > ::
binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *), raw_index_array & ia) const
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
index raw_array < TYPE, ARG_TYPE > ::
sort_add(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), raw_index_array & ia)
{
   index iIndex = 0;
   binary_search(t, iIndex, fCompare, ia);
   this->insert_at(iIndex, t);
   ia.add(iIndex);
   return iIndex;
}

template < class TYPE, class ARG_TYPE >
::count raw_array < TYPE, ARG_TYPE> ::
sort_add(const raw_array  < TYPE, ARG_TYPE> & a, index ( * fCompare ) (TYPE *, TYPE *), raw_index_array & ia)
{
   for(index i = 0; i < a.get_size(); i++)
   {
      sort_add((ARG_TYPE) a[i], fCompare, ia);
   }
   return a.get_size();
}

template < class TYPE, class ARG_TYPE >
::count raw_array < TYPE, ARG_TYPE > ::
sort_remove(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), raw_index_array & ia)
{
   ::count ca = 0;
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
      ca++;
   }
   return ca;
}
