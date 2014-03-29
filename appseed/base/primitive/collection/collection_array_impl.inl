#pragma once

//
// see collection_array_decl.h for declaration
//
// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline ::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::get_size() const
{
   return m_nSize;
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline ::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::get_size_in_bytes() const
{
   return m_nSize * sizeof(TYPE);
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline ::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::get_count() const
{
   return this->get_size();
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline ::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::get_byte_count() const
{
   return this->get_size_in_bytes();
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline ::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::size() const
{
   return this->get_size();
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline ::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::count() const
{
   return this->get_count();
}


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline bool array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::is_empty(::count countMinimum) const
{
   return m_nSize < countMinimum;
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline bool array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::empty(::count countMinimum) const
{
   return is_empty(countMinimum);
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline bool array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::has_elements(::count countMinimum) const
{
   return m_nSize >= countMinimum;
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline index array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::get_upper_bound(index index) const
{
   return m_nSize + index;
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline ::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::remove_all()
{
   return allocate(0, -1);
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline ::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::set_size(index nNewSize, ::count nGrowBy) // does not call default constructors on new items/elements
{
   return allocate(nNewSize, nGrowBy);
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::clear()
{
   remove_all();
}


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::remove_last()
{
   remove_at(get_upper_bound());
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline TYPE& array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::get_at(index nIndex)
{
   //   if(nIndex >= 0 && nIndex < m_nSize)
   return m_pData[nIndex];
   //   throw invalid_argument_exception(get_app());
}
template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline const TYPE& array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::get_at(index nIndex) const
{
   //   if(nIndex >= 0 && nIndex < m_nSize)
   return m_pData[nIndex];
   // throw invalid_argument_exception(get_app());
}
template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::set_at(index nIndex, ARG_TYPE newElement)
{
   //   if(nIndex >= 0 && nIndex < m_nSize)
   m_pData[nIndex] = newElement;
   // else
   //  throw invalid_argument_exception(get_app());
}
template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline const TYPE& array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::element_at(index nIndex) const
{
   //   if(nIndex >= 0 && nIndex < m_nSize)
   return m_pData[nIndex];
   // throw invalid_argument_exception(get_app());
}
template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline TYPE& array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::element_at(index nIndex)
{
   //   if(nIndex >= 0 && nIndex < m_nSize)
   return m_pData[nIndex];
   // throw invalid_argument_exception(get_app());
}
template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline const TYPE& array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::first_element(index nIndex) const
{
   return this->element_at(nIndex);
}
template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline TYPE& array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::first_element(index nIndex)
{
   return this->element_at(nIndex);
}
template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline const TYPE& array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::last_element(index index) const
{
   return element_at(get_upper_bound(index));
}


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline TYPE& array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::last_element(index index)
{
   return element_at(get_upper_bound(index));
}


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline TYPE & array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::front(index n)
{
   return first_element(n);
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline const TYPE & array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::front(index n) const
{
   return first_element(n);
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline TYPE & array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::back(index n)
{
   return last_element(n);
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline const TYPE & array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::back(index n) const
{
   return last_element(n);
}


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline const TYPE* array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::get_data() const
{
   return (const TYPE*)m_pData;
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline TYPE* array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::get_data()
{
   return (TYPE*)m_pData;
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::push_last()
{

   add(last_element());

}


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline index array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::push_back(ARG_TYPE newElement)
{
   return add(newElement);
}


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline index array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::add(ARG_TYPE newElement)
{
   index nIndex = m_nSize;
   allocate(nIndex + 1);
   last_element() = newElement;
   return nIndex;
}


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline index array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::add(const array & src)
{
   return append(src);
}




template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline TYPE array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::pop(index n)
{

   index i = get_upper_bound(n);

   TYPE t = element_at(i);

   remove_at(i);

   return t;

}




template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline TYPE array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::pop_to()
{

   TYPE lastelement = pop();

   last_element() = lastelement;

   return last_element();

}


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::pop_back(index n)
{

   remove_at(get_upper_bound(n));

}



template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline const TYPE& array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::operator[](index nIndex) const
{
   return element_at(nIndex);
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline TYPE& array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::operator[](index nIndex)
{
   return this->element_at(nIndex);
}


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::swap(index index1, index index2)
{
   TYPE t = m_pData[index1];
   m_pData[index1] = m_pData[index2];
   m_pData[index2] = t;
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline array < TYPE, ARG_TYPE, DEFCONSTRUCTOR >  & array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::operator = (const array & src)
{
   if(&src != this)
   {
      copy(src);
   }
   return *this;
}



// out-of-line functions

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::array(sp(base_application) papp, ::count nGrowBy) :
element(papp)
{
   m_nGrowBy = max(0, nGrowBy);
   m_pData = NULL;
   m_nSize = m_nMaxSize = 0;
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::array(const array <TYPE, ARG_TYPE> & a) :
element(a.get_app())
{
   m_nGrowBy = 32;
   m_pData = NULL;
   m_nSize = m_nMaxSize = 0;
   operator = (a);
}





template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > :: array(::count n)
{
   m_nGrowBy = 32;
   m_pData = NULL;
   m_nSize = m_nMaxSize = 0;
   allocate(n);
}





template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::~array()
{

   destroy();

}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::destroy()
{
   ASSERT_VALID(this);

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

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::resize(::count nNewSize, ::count nGrowBy)
{
   return allocate(nNewSize, nGrowBy);
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::allocate_in_bytes(::count nNewSize, ::count nGrowBy)
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

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::allocate(::count nNewSize, ::count nGrowBy)
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
      m_pData = (TYPE*) new BYTE[(size_t)nAllocSize * sizeof(TYPE)];
      DEFCONSTRUCTOR::construct( m_pData, nNewSize );
      m_nSize = nNewSize;
      m_nMaxSize = nAllocSize;
   }
   else if (nNewSize <= m_nMaxSize)
   {
      // it fits
      if (nNewSize > m_nSize)
      {
         DEFCONSTRUCTOR::construct( m_pData + m_nSize, nNewSize - m_nSize );
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
      TYPE* pNewData = (TYPE*) new BYTE[(size_t)nNewMax * sizeof(TYPE)];

      // copy new data from old
      ::core::memcpy_s(pNewData, (size_t)nNewMax * sizeof(TYPE), m_pData, (size_t)m_nSize * sizeof(TYPE));

      // construct remaining elements
      ASSERT(nNewSize > m_nSize);
      DEFCONSTRUCTOR::construct(pNewData + m_nSize, nNewSize - m_nSize);
      // get rid of old stuff (note: no destructors called)
      delete[] (BYTE*)m_pData;
      m_pData = pNewData;
      m_nSize = nNewSize;
      m_nMaxSize = nNewMax;
   }
   return countOld;
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::set_raw_size(::count nNewSize, ::count nGrowBy)
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
      m_pData = (TYPE*) new BYTE[(size_t)nAllocSize * sizeof(TYPE)];
      m_nSize = nNewSize;
      m_nMaxSize = nAllocSize;
   }
   else if (nNewSize <= m_nMaxSize)
   {
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
      TYPE* pNewData = (TYPE*) new BYTE[(size_t)nNewMax * sizeof(TYPE)];
      // copy new data from old
      ::core::memcpy_s(pNewData, (size_t)nNewMax * sizeof(TYPE),
         m_pData, (size_t)m_nSize * sizeof(TYPE));

      for( int32_t i = 0; i < nNewSize-m_nSize; i++ )
         // get rid of old stuff (note: no destructors called)
            delete[] (BYTE*)m_pData;
      m_pData = pNewData;
      m_nSize = nNewSize;
      m_nMaxSize = nNewMax;
   }

   return countOld;

}


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
index array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::append(const array& src)
{
   ASSERT_VALID(this);
   ASSERT(this != &src);   // cannot append to itself

   if(this == &src)
      throw invalid_argument_exception(get_app());

   ::count nOldSize = m_nSize;
   allocate(m_nSize + src.m_nSize);
   CopyElements<TYPE>(m_pData + nOldSize, src.m_pData, src.m_nSize);
   return nOldSize;
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::copy(const array& src)
{
   ASSERT_VALID(this);
   ASSERT(this != &src);   // cannot append to itself

   if(this != &src)
   {
      allocate(src.m_nSize);
      CopyElements<TYPE>(m_pData, src.m_pData, src.m_nSize);
   }
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::free_extra()
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
         ::core::memcpy_s(pNewData, m_nSize * sizeof(TYPE),
            m_pData, m_nSize * sizeof(TYPE));
      }

      // get rid of old stuff (note: no destructors called)
      delete[] (BYTE*)m_pData;
      m_pData = pNewData;
      m_nMaxSize = m_nSize;
   }
}



template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline index array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::remove_at(index nIndex, ::count nCount)
{

   //ASSERT_VALID(this);

   index nUpperBound = nIndex + nCount;

   if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
      throw invalid_argument_exception(get_app());

   // just remove a range
   ::count nMoveCount = m_nSize - (nUpperBound);
   for( int32_t i = 0; i < nCount; i++ )
      (m_pData + nIndex + i)->~TYPE();

   if (nMoveCount)
   {
      ::core::memmove_s(m_pData + nIndex, (size_t)nMoveCount * sizeof(TYPE),
         m_pData + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));
   }
   m_nSize -= nCount;
   return nIndex;
}




template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::dump(dump_context & dumpcontext) const
{
   object::dump(dumpcontext);

   dumpcontext << "with " << m_nSize << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      dumpcontext << "\n";
      dump_elements<TYPE>(dumpcontext, m_pData, m_nSize);
   }

   dumpcontext << "\n";
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::assert_valid() const
{
   object::assert_valid();

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

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
typename array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::iterator array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::erase(iterator pos)
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

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
typename  array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::iterator array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::erase(iterator begin, iterator last)
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


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
index array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::raw_find_first(TYPE *pt, index find, index last) const
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

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
index array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::find_first(ARG_TYPE t, index ( * lpfnCompare )(ARG_TYPE, ARG_TYPE), index find, index last) const
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



template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
bool array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *)) const
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




template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
array < TYPE, ARG_TYPE, DEFCONSTRUCTOR >  & array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::operator += (const array & a)
{

   if(&a == this)
   {
      array < TYPE, ARG_TYPE, DEFCONSTRUCTOR >  aCopy(a);
      add(aCopy);
   }
   else
   {
      add(a);
   }
   return *this;

}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
array < TYPE, ARG_TYPE, DEFCONSTRUCTOR >  array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::operator + (const array & a) const
{
   array < TYPE, ARG_TYPE, DEFCONSTRUCTOR >  aNew(*this);
   aNew += a;
   return a;
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
index array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::insert_at(index nIndex, ARG_TYPE newElement, ::count nCount /*=1*/)
{

   ASSERT_VALID(this);

   ASSERT(nIndex >= 0);    // will expand to meet need

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
      ::core::memmove_s(m_pData + nIndex + nCount, (nOldSize-nIndex) * sizeof(TYPE), m_pData + nIndex, (nOldSize-nIndex) * sizeof(TYPE));

      DEFCONSTRUCTOR::construct(m_pData + nIndex, nCount);
   }

   // insert new value in the gap
   ASSERT(nIndex + nCount <= m_nSize);

   index nIndexParam = nIndex;

   while (nCount--)
      m_pData[nIndex++] = newElement;

   return nIndexParam;

}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
index array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::insert_at(index nStartIndex, array < TYPE, ARG_TYPE, DEFCONSTRUCTOR >  * pNewArray)
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


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline TYPE & array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::add_new()
{
   set_size(m_nSize + 1);
   return last_element();
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline index array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::add_new(::count count)
{
   set_size(m_nSize + count);
   return get_upper_bound();
}



template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::set_at_grow(index nIndex, ARG_TYPE newElement)
{

   ASSERT_VALID(this);

   ASSERT(nIndex >= 0);

   if(nIndex < 0)
      throw invalid_argument_exception(get_app());

   if (nIndex >= m_nSize)
      set_size(nIndex+1, -1);

   m_pData[nIndex] = newElement;

}



template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline TYPE & array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::element_at_grow(index nIndex)
{

   ASSERT_VALID(this);

   ASSERT(nIndex >= 0);

   if(nIndex < 0)
      throw invalid_argument_exception(get_app());

   if (nIndex >= m_nSize)
      set_size(nIndex+1, -1);

   return m_pData[nIndex];

}
