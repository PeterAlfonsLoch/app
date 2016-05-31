//#include "framework.h"



template < class TYPE, class ALLOCATOR >
array_base < TYPE, ALLOCATOR >::array_base(int iTypeSize,bool bRaw)
{

   m_nGrowBy = 0;
   m_pData = NULL;
   m_nSize = 0;
   m_nMaxSize = 0;

}


template < class TYPE,class ALLOCATOR >
array_base < TYPE, ALLOCATOR >::array_base(::ace::application * papp, int iTypeSize, bool bRaw):
   object(papp)
{

   m_nGrowBy = 0;
   m_pData = NULL;
   m_nSize = 0;
   m_nMaxSize = 0;

}


template < class TYPE,class ALLOCATOR >
array_base < TYPE, ALLOCATOR >::~array_base ()
{

   destroy();

}


template < class TYPE,class ALLOCATOR >
::count array_base < TYPE, ALLOCATOR >::resize(::count nNewSize,::count nGrowBy)
{
   return allocate(nNewSize,nGrowBy);
}


template < class TYPE,class ALLOCATOR >
::count array_base < TYPE, ALLOCATOR >::allocate_in_bytes(::count nNewSize,::count nGrowBy)
{
   if(nGrowBy < 0)
   {
      return allocate(nNewSize / sizeof(TYPE),-1);
   }
   else
   {
      return allocate(nNewSize / sizeof(TYPE),nGrowBy / sizeof(TYPE));
   }
}


template < class TYPE,class ALLOCATOR >
index array_base < TYPE, ALLOCATOR >::remove_at(index nIndex,::count nCount)
{

   //ASSERT_VALID(this);

   index nUpperBound = nIndex + nCount;

   if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
      throw invalid_argument_exception(get_app());

   // just remove a range
   ::count nMoveCount = m_nSize - (nUpperBound);

   ALLOCATOR::destruct(&m_pData[nIndex], nCount);

   if(nMoveCount)
   {
      ::ace::memmove_s(&m_pData[nIndex],(size_t)nMoveCount * sizeof(TYPE),&m_pData[nUpperBound],(size_t)nMoveCount * sizeof(TYPE));
   }

   m_nSize -= nCount;

   return nIndex;

}


template < class TYPE,class ALLOCATOR >
void array_base < TYPE, ALLOCATOR >::free_extra()
{
   ASSERT_VALID(this);

   if(m_nSize != m_nMaxSize)
   {
      // shrink to desired size
#ifdef SIZE_T_MAX
      ASSERT(m_nSize <= SIZE_T_MAX / sizeof(TYPE)); // no overflow
#endif
      TYPE* pNewData = NULL;
      if(m_nSize != 0)
      {
         TYPE * pNewData;
#if defined(__MCRTDBG) || MEMDLEAK
#ifdef __MCRTDBG
         if (::get_thread() != NULL)
         {
            if (::get_thread()->m_strFile.has_char())
            {
               pNewData = (TYPE *)ALLOCATOR::alloc(m_nSize * sizeof(TYPE), ::get_thread()->m_strFile, ::get_thread()->m_iLine);
            }
            else
            {
               pNewData = (TYPE *)ALLOCATOR::alloc(m_nSize * sizeof(TYPE), __FILE__, __LINE__);
            }
         }
         else
         {
            pNewData = (TYPE *)ALLOCATOR::alloc(m_nSize * sizeof(TYPE), __FILE__, __LINE__);
         }
#else
         if (::get_thread()->m_strDebug.has_char())
         {
            pNewData = (TYPE *)ALLOCATOR::alloc(m_nSize * sizeof(TYPE), ::get_thread()->m_strDebug, 0);
         }
         else
         {
            pNewData = (TYPE *)ALLOCATOR::alloc(m_nSize * sizeof(TYPE), __FILE__, __LINE__);
         }
#endif
#else
         pNewData = (TYPE *)ALLOCATOR::alloc(m_nSize * sizeof(TYPE));
#endif      // copy new data from old
         // copy new data from old
         ::ace::memcpy_s(pNewData,m_nSize * sizeof(TYPE),m_pData,m_nSize * sizeof(TYPE));
      }

      // get rid of old stuff (note: no destructors called)
      ALLOCATOR::_free(m_pData);
      m_pData = pNewData;
      m_nMaxSize = m_nSize;

   }

}



template < class TYPE,class ALLOCATOR >
void array_base < TYPE, ALLOCATOR >::destroy()
{

   ASSERT_VALID(this);

   if(m_pData != NULL)
   {

      ALLOCATOR::destruct(m_pData, m_nSize);

      ALLOCATOR::_free(m_pData);

      m_pData     = NULL;
      m_nSize     = 0;
      m_nMaxSize  = 0;

   }

}


template < class TYPE,class ALLOCATOR >
index array_base < TYPE, ALLOCATOR >::insert_at(index nIndex,const TYPE * newElement,::count nCount /*=1*/)
{

   ASSERT_VALID(this);

   ASSERT(nIndex >= 0);    // will expand to meet need

   if(nCount <= 0)
      return -1;

   if(nIndex < 0)
      throw invalid_argument_exception(get_app());

   if(nIndex >= m_nSize)
   {
      // adding after the end of the array
      set_size(nIndex + nCount,-1);   // grow so nIndex is valid
   }
   else
   {
      // inserting in the middle of the array
      ::count nOldSize = m_nSize;
      set_size(m_nSize + nCount,-1);  // grow it to new size
      // destroy intial data before copying over it
      // shift old data up to fill gap
      ::ace::memmove_s(m_pData + nIndex + nCount,(nOldSize - nIndex) * sizeof(TYPE),m_pData + nIndex,(nOldSize - nIndex) * sizeof(TYPE));

      ALLOCATOR::construct(&m_pData[nIndex],nCount);

   }

   // insert new value in the gap
   ASSERT(nIndex + nCount <= m_nSize);

   index nIndexParam = nIndex;

   while(nCount--)
   {

      ALLOCATOR::copy(&m_pData[nIndex++], newElement);

   }

   return nIndexParam;

}


template < class TYPE,class ALLOCATOR >
::count array_base < TYPE, ALLOCATOR >::append(const array_base < TYPE, ALLOCATOR > & src)
{

   ASSERT_VALID(this);

   ::count nOldSize = m_nSize;

   ::count nSrcSize = src.m_nSize;   // to enable to append to itself

   allocate(m_nSize + nSrcSize);

   ALLOCATOR::copy(&m_pData[nOldSize],src.m_pData,nSrcSize);

   return nOldSize;

}


template < class TYPE,class ALLOCATOR >
void array_base < TYPE, ALLOCATOR >::copy(const array_base < TYPE, ALLOCATOR > & src)
{

   ASSERT_VALID(this);

   if(this == &src)
      return;

   allocate(src.m_nSize);

   ALLOCATOR::copy(m_pData,src.m_pData,src.m_nSize);

}



// take in ac::count that _001RemoveIndexes change
// the index raw_array by sorting it and returning
// only the indexes that could be removed
// without indexes duplicates
template < class TYPE,class ALLOCATOR >
void array_base < TYPE, ALLOCATOR >::_001RemoveIndexes(index_array & ia)
{

   // sort
   ::sort::quick_sort(ia,true);

   index i = ia.get_upper_bound();

   // filter out of upper bound indexes
   while(i >= 0 && ia[i] >= get_size())
   {

      ia.remove_at(i);

      i--;

   }

   // filter out of lower bound indexes
   while(ia.get_size() > 0 && ia[0] < 0)
   {

      ia.remove_at(0);

   }

   i = ia.get_upper_bound();

   // filter out duplicates
   while(i > 0 && ia[i] >= get_size())
   {

      if(ia[i] == ia[i - 1])
         ia.remove_at(i);

      i--;

   }

   remove_indexes(ia);

}


template < class TYPE,class ALLOCATOR >
void array_base < TYPE, ALLOCATOR >::remove_indexes(const index_array & ia)
{


   // remove indexes
   for(index i = ia.get_upper_bound(); i >= 0; i--)
   {

      remove_at(ia[i]);

   }

}


template < class TYPE,class ALLOCATOR >
void array_base < TYPE, ALLOCATOR >::remove_descending_indexes(const index_array & ia)
{

   for(index i = 0; i < ia.get_count(); i++)
   {

      remove_at(ia[i]);

   }

}



template < class TYPE,class ALLOCATOR >
index array_base < TYPE, ALLOCATOR >::insert_at(index nStartIndex,array_base < TYPE, ALLOCATOR > * pNewArray)
{
   ASSERT_VALID(this);
   ASSERT(pNewArray != NULL);
   ASSERT_VALID(pNewArray);
   ASSERT(nStartIndex >= 0);

   if(pNewArray == NULL || nStartIndex < 0)
      throw invalid_argument_exception(get_app());

   if(pNewArray->get_size() > 0)
   {
      insert_at(nStartIndex,pNewArray->element_at(0),pNewArray->get_size());
      for(index i = 1; i < pNewArray->get_size(); i++)
         insert_at(nStartIndex + i,pNewArray->element_at(i));
   }

   return nStartIndex;

}


template < class TYPE,class ALLOCATOR >
::count array_base < TYPE, ALLOCATOR >::set_raw_size(::count nNewSize,::count nGrowBy)
{
   ::count countOld = get_count();
   ASSERT_VALID(this);
   ASSERT(nNewSize >= 0);

   if(nNewSize < 0)
      throw invalid_argument_exception(get_app());

   if(nGrowBy >= 0)
      m_nGrowBy = nGrowBy;  // set new size

   if(nNewSize == 0)
   {
      // shrink to nothing
      if(m_pData != NULL)
      {
         ALLOCATOR::_free(m_pData);
         m_pData = NULL;
      }
      m_nSize = m_nMaxSize = 0;
   }
   else if (m_pData == NULL)
   {
      // create buffer big enough to hold number of requested elements or
      // m_nGrowBy elements, whichever is larger.
#ifdef SIZE_T_MAX
      if (nNewSize > SIZE_T_MAX / sizeof(TYPE))
         throw memory_exception(get_app());
      ASSERT(nNewSize <= SIZE_T_MAX / sizeof(TYPE));    // no overflow
#endif
      ::count nAllocSize = MAX(nNewSize, m_nGrowBy);
#if defined(__MCRTDBG) || MEMDLEAK
      if (::get_thread() != NULL)
      {
#if defined(MEMDLEAK)
         if (::get_thread()->m_strFile.has_char())
         {
            m_pData = (TYPE *)ALLOCATOR::alloc(nAllocSize * sizeof(TYPE), ::get_thread()->m_strFile, 0);
         }
         else
         {
            m_pData = (TYPE *)ALLOCATOR::alloc(nAllocSize * sizeof(TYPE), __FILE__, __LINE__);
         }
#else
         if (::get_thread()->m_strDebug.has_char())
         {
            m_pData = (TYPE *)ALLOCATOR::alloc(nAllocSize * sizeof(TYPE), ::get_thread()->m_strDebug, ::get_thread()->m_iLine);
         }
         else
         {
            m_pData = (TYPE *)ALLOCATOR::alloc(nAllocSize * sizeof(TYPE), __FILE__, __LINE__);
         }
#endif
      }
      else
      {
         m_pData = (TYPE *)ALLOCATOR::alloc(nAllocSize * sizeof(TYPE), __FILE__, __LINE__);
      }
#else
      m_pData = (TYPE *)ALLOCATOR::alloc(nAllocSize * sizeof(TYPE));
#endif
      m_nSize = nNewSize;
      m_nMaxSize = nAllocSize;
   }
   else if(nNewSize <= m_nMaxSize)
   {
      m_nSize = nNewSize;
   }
   else
   {
      // otherwise, grow aaa_base_array
      nGrowBy = m_nGrowBy;
      if(nGrowBy == 0)
      {
         // heuristically determine growth when nGrowBy == 0
         //  (this avoids heap fragmentation in many situations)
         nGrowBy = m_nSize;
         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
      }
      ::count nNewMax;
      if(nNewSize < m_nMaxSize + nGrowBy)
         nNewMax = m_nMaxSize + nGrowBy;  // granularity
      else
         nNewMax = nNewSize;  // no slush

      ASSERT(nNewMax >= m_nMaxSize);  // no wrap around

      if(nNewMax  < m_nMaxSize)
         throw invalid_argument_exception(get_app());

#ifdef SIZE_T_MAX
      ASSERT(nNewMax <= SIZE_T_MAX / sizeof(TYPE)); // no overflow
#endif
      TYPE * pNewData;
#if defined(__MCRTDBG) || MEMDLEAK
#ifdef __MCRTDBG
      if (::get_thread() != NULL)
      {
         if (::get_thread()->m_strFile.has_char())
         {
            pNewData = (TYPE *)ALLOCATOR::alloc(nNewMax * sizeof(TYPE), ::get_thread()->m_strFile, ::get_thread()->m_iLine);
         }
         else
         {
            pNewData = (TYPE *)ALLOCATOR::alloc(nNewMax * sizeof(TYPE), __FILE__, __LINE__);
         }
      }
      else
      {
         pNewData = (TYPE *)ALLOCATOR::alloc(nNewMax * sizeof(TYPE), __FILE__, __LINE__);
      }
#else
      if (::get_thread()->m_strDebug.has_char())
      {
         pNewData = (TYPE *)ALLOCATOR::alloc(nNewMax * sizeof(TYPE), ::get_thread()->m_strDebug, ::get_thread()->m_iLine);
      }
      else
      {
         pNewData = (TYPE *)ALLOCATOR::alloc(nNewMax * sizeof(TYPE), __FILE__, __LINE__);
      }
#endif
#else
      pNewData = (TYPE *)ALLOCATOR::alloc(nNewMax * sizeof(TYPE));
#endif      // copy new data from old
      ::ace::memcpy_s(pNewData,(size_t)nNewMax * sizeof(TYPE),m_pData,(size_t)m_nSize * sizeof(TYPE));

      ///for(int32_t i = 0; i < nNewSize - m_nSize; i++)
         // get rid of old stuff (note: no destructors called)
      ALLOCATOR::_free(m_pData);
      m_pData = pNewData;
      m_nSize = nNewSize;
      m_nMaxSize = nNewMax;
   }

   return countOld;

}


template < class TYPE,class ALLOCATOR >
::count array_base < TYPE, ALLOCATOR >::allocate(::count nNewSize,::count nGrowBy)
{

   ::count countOld = get_count();
   ASSERT_VALID(this);
   ASSERT(nNewSize >= 0);

   if(nNewSize < 0)
      throw invalid_argument_exception(get_app());

   if(nGrowBy >= 0)
      m_nGrowBy = nGrowBy;  // set new size


   if(nNewSize == m_nSize)
   {

      return m_nSize;

   }

   if(nNewSize == 0)
   {
      // shrink to nothing
      if(m_pData != NULL)
      {

         ALLOCATOR::destruct(m_pData,m_nSize);

         ALLOCATOR::_free(m_pData);

         m_pData = NULL;

      }
      m_nSize = m_nMaxSize = 0;
   }
   else if(m_pData == NULL)
   {
      // create buffer big enough to hold number of requested elements or
      // m_nGrowBy elements, whichever is larger.
#ifdef SIZE_T_MAX
      if(::compare::gt(nNewSize, SIZE_T_MAX / sizeof(TYPE)))
         throw memory_exception(get_app());
      ASSERT(::compare::lt(nNewSize, SIZE_T_MAX / sizeof(TYPE)));    // no overflow
#endif

      ::count nAllocSize = MAX(nNewSize,m_nGrowBy);
      #if MEMDLEAK  || defined(__MCRTDBG)
      if(::get_thread() != NULL)
      {
#if defined(__MCRTDBG)
         if(::get_thread()->m_strFile.has_char())
         {
            m_pData = ALLOCATOR::alloc(nAllocSize, ::get_thread()->m_strFile, ::get_thread()->m_iLine);
         }
         else
         {
            m_pData = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);
         }
#else
         if (::get_thread()->m_strDebug.has_char())
         {
            m_pData = ALLOCATOR::alloc(nAllocSize, "thread://" + demangle(typeid(*::get_thread()).name()) + ", " + ::get_thread()->m_strDebug + ", " + string(__FILE__), __LINE__);
         }
         else
         {
            m_pData = ALLOCATOR::alloc(nAllocSize, "thread://" + demangle(typeid(*::get_thread()).name()) + ", " + string(__FILE__), __LINE__);
         }
#endif
      }
      else
      {
      m_pData = ALLOCATOR::alloc(nAllocSize, __FILE__, __LINE__);
      }


      #else
      m_pData = ALLOCATOR::alloc(nAllocSize);
      #endif

      ALLOCATOR::construct(m_pData,nNewSize);

      m_nSize = nNewSize;

      m_nMaxSize = nAllocSize;

   }
   else if(nNewSize <= m_nMaxSize)
   {

      if(nNewSize > m_nSize)
      {

         ALLOCATOR::construct(&m_pData[m_nSize],nNewSize - m_nSize);

      }
      else if(m_nSize > nNewSize)
      {

         ALLOCATOR::destruct(&m_pData[nNewSize],m_nSize - nNewSize);

      }

      m_nSize = nNewSize;

   }
   else
   {
      // otherwise, grow aaa_base_array
      nGrowBy = m_nGrowBy;
      if(nGrowBy == 0)
      {
         // heuristically determine growth when nGrowBy == 0
         //  (this avoids heap fragmentation in many situations)
         nGrowBy = m_nSize / 8;
         nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
      }
      ::count nNewMax;
      if(nNewSize < m_nMaxSize + nGrowBy)
         nNewMax = m_nMaxSize + nGrowBy;  // granularity
      else
         nNewMax = nNewSize;  // no slush

      ASSERT(nNewMax >= m_nMaxSize);  // no wrap around

      if(nNewMax  < m_nMaxSize)
         throw invalid_argument_exception(get_app());

#ifdef SIZE_T_MAX
      ASSERT(::compare::lt(nNewMax, SIZE_T_MAX / sizeof(TYPE))); // no overflow
#endif
      #if MEMDLEAK || defined(__MCRTDBG)
      TYPE* pNewData =  NULL;
      if(::get_thread() != NULL)
      {
         #if defined(__MCRTDBG)
         if(::get_thread()->m_strFile.has_char())
         {
            pNewData = ALLOCATOR::alloc(nNewMax * sizeof(TYPE), ::get_thread()->m_strFile,::get_thread()->m_iLine);
         }
         else
         {
            pNewData = ALLOCATOR::alloc(nNewMax * sizeof(TYPE), __FILE__, __LINE__);
         }
#else
         if (::get_thread()->m_strDebug.has_char())
         {
            pNewData = ALLOCATOR::alloc(nNewMax * sizeof(TYPE), "thread://" + demangle(typeid(*::get_thread()).name()) + ", " + ::get_thread()->m_strDebug + ", " + string(__FILE__), __LINE__);
         }
         else
         {
            pNewData = ALLOCATOR::alloc(nNewMax * sizeof(TYPE), "thread://" + demangle(typeid(*::get_thread()).name()) + ", " + string(__FILE__), __LINE__);
         }

#endif
      }
      else
      {
      pNewData = ALLOCATOR::alloc(nNewMax * sizeof(TYPE), __FILE__, __LINE__);
      }


      #else
      TYPE* pNewData = (TYPE *)ALLOCATOR::alloc(nNewMax * sizeof(TYPE));
      #endif

      // copy new data from old
      ::ace::memcpy_s(pNewData,(size_t)nNewMax * sizeof(TYPE),m_pData,(size_t)m_nSize * sizeof(TYPE));

      // construct remaining elements
      ASSERT(nNewSize > m_nSize);
      ALLOCATOR::construct(&pNewData[m_nSize],nNewSize - m_nSize);
      // get rid of old stuff (note: no destructors called)
      ALLOCATOR::_free(m_pData);
      m_pData = pNewData;
      m_nSize = nNewSize;
      m_nMaxSize = nNewMax;
   }
   return countOld;
}



template < class TYPE,class ALLOCATOR >
void array_base < TYPE, ALLOCATOR >::on_after_read()
{


}



