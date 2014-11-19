#include "framework.h"

#define construct_element(p) \
   on_construct_element(p)

#define construct_element_set(p, c) \
   on_construct_element(p,c)

#define destruct_element(p) \
   try { on_destruct_element(p); } catch(...) {}

#define copy_element(i,p) \
   on_copy_element(i, p)



array_base::array_base(int iTypeSize,bool bRaw)
{

   m_iTypeSize = iTypeSize;
   m_bRaw = bRaw;
   m_nGrowBy = 32;
   m_pData = NULL;
   m_nSize = 0;
   m_nMaxSize = 0;

}


array_base::array_base(sp(::aura::application) papp, int iTypeSize, bool bRaw):
   element(papp)
{
   
   m_iTypeSize = iTypeSize;
   m_bRaw = bRaw;
   m_nGrowBy = 32;
   m_pData = NULL;
   m_nSize = 0;
   m_nMaxSize = 0;

}

array_base::~array_base()
{

   destroy();

}


::count array_base::resize(::count nNewSize,::count nGrowBy)
{
   return allocate(nNewSize,nGrowBy);
}

::count array_base::allocate_in_bytes(::count nNewSize,::count nGrowBy)
{
   if(nGrowBy < 0)
   {
      return allocate(nNewSize / m_iTypeSize,-1);
   }
   else
   {
      return allocate(nNewSize / m_iTypeSize,nGrowBy / m_iTypeSize);
   }
}


index array_base::remove_at(index nIndex,::count nCount)
{

   //ASSERT_VALID(this);

   index nUpperBound = nIndex + nCount;

   if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
      throw invalid_argument_exception(get_app());

   // just remove a range
   ::count nMoveCount = m_nSize - (nUpperBound);
   if(!m_bRaw)
   {
      for(int32_t i = 0; i < nCount; i++)
         destruct_element((byte*)m_pData + (nIndex + i) *m_iTypeSize);
   }

   if(nMoveCount)
   {
      ::aura::memmove_s((byte*)m_pData + nIndex*m_iTypeSize,(size_t)nMoveCount * m_iTypeSize, (byte*) m_pData + nUpperBound * m_iTypeSize,(size_t)nMoveCount * m_iTypeSize);
   }
   m_nSize -= nCount;
   return nIndex;
}


void array_base::free_extra()
{
   ASSERT_VALID(this);

   if(m_nSize != m_nMaxSize)
   {
      // shrink to desired size
#ifdef SIZE_T_MAX
      ASSERT(m_nSize <= SIZE_T_MAX / m_iTypeSize); // no overflow
#endif
      byte* pNewData = NULL;
      if(m_nSize != 0)
      {
         pNewData = (byte *) memory_alloc(m_nSize * m_iTypeSize);
         // copy new data from old
         ::aura::memcpy_s(pNewData,m_nSize * m_iTypeSize,
            m_pData,m_nSize * m_iTypeSize);
      }

      // get rid of old stuff (note: no destructors called)
      memory_free(m_pData);
      m_pData = pNewData;
      m_nMaxSize = m_nSize;
   }
}



//void array_base::construct_element(void * p) { on_construct_element(p); }
//void array_base::construct_element(void * p,::count c) { on_construct_element(p,c); }
//void array_base::destruct_element(void * p) { try { on_destruct_element(p); } catch(...) {} }
//void array_base::copy_element(index i, const void * p) { on_copy_element(i, p); }


void array_base::on_construct_element(void *) {}
void array_base::on_construct_element(void *,::count) {}
void array_base::on_destruct_element(void *) {}
void array_base::on_copy_element(index i, const void * p) { ::memcpy((byte *) m_pData + i*m_iTypeSize,p,m_iTypeSize); }


void array_base::destroy()
{
   ASSERT_VALID(this);

   if(m_pData != NULL)
   {
      if(!m_bRaw)
      {
         for(int32_t i = 0; i < m_nSize; i++)
            destruct_element((byte *)m_pData + i * m_iTypeSize);
      }
      memory_free(m_pData);
      m_pData     = NULL;
      m_nSize     = 0;
      m_nMaxSize  = 0;
   }

}


index array_base::insert_at(index nIndex,const void * newElement,::count nCount /*=1*/)
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
      ::aura::memmove_s((byte *) m_pData + (nIndex + nCount) * m_iTypeSize,(nOldSize - nIndex) * m_iTypeSize,(byte *) m_pData + nIndex * m_iTypeSize,(nOldSize - nIndex) * m_iTypeSize);

      if(!m_bRaw)
      {
         construct_element_set((byte*)m_pData + nIndex*m_iTypeSize,nCount);
      }
   }

   // insert new value in the gap
   ASSERT(nIndex + nCount <= m_nSize);

   index nIndexParam = nIndex;

   while(nCount--)
      copy_element(nIndex++,newElement);

   return nIndexParam;

}


::count array_base::append(const array_base & src)
{

   ASSERT_VALID(this);

   ::count nOldSize = m_nSize;

   ::count nSrcSize = src.m_nSize;   // to enable to append to itself

   allocate(m_nSize + nSrcSize);

   memcpy((byte *) m_pData + nOldSize * m_iTypeSize,src.m_pData,nSrcSize * m_iTypeSize);

   return nOldSize;

}


void array_base::copy(const array_base & src)
{

   ASSERT_VALID(this);

   if(this == &src)
      return;

   allocate(src.m_nSize);

   memcpy(m_pData,src.m_pData,src.m_nSize * m_iTypeSize);

}



// take in ac::count that _001RemoveIndexes change
// the index raw_array by sorting it and returning
// only the indexes that could be removed
// without indexes duplicates
void array_base::_001RemoveIndexes(index_array & ia)
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



void array_base::remove_indexes(const index_array & ia)
{


   // remove indexes
   for(index i = ia.get_upper_bound(); i >= 0; i--)
   {

      remove_at(ia[i]);

   }

}



void array_base::remove_descending_indexes(const index_array & ia)
{

   for(index i = 0; i < ia.get_count(); i++)
   {

      remove_at(ia[i]);

   }

}




index array_base::insert_at(index nStartIndex,array_base * pNewArray)
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



::count array_base::set_raw_size(::count nNewSize,::count nGrowBy)
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
         delete[](BYTE*)m_pData;
         m_pData = NULL;
      }
      m_nSize = m_nMaxSize = 0;
   }
   else if(m_pData == NULL)
   {
      // create buffer big enough to hold number of requested elements or
      // m_nGrowBy elements, whichever is larger.
#ifdef SIZE_T_MAX
      if(nNewSize > SIZE_T_MAX / m_iTypeSize)
         throw memory_exception(get_app());
      ASSERT(nNewSize <= SIZE_T_MAX / m_iTypeSize);    // no overflow
#endif
      ::count nAllocSize = MAX(nNewSize,m_nGrowBy);
      m_pData = (byte *)memory_alloc(nAllocSize * m_iTypeSize);
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
      ASSERT(nNewMax <= SIZE_T_MAX / m_iTypeSize); // no overflow
#endif
      byte * pNewData = (byte *)memory_alloc(nNewMax * m_iTypeSize);
      // copy new data from old
      ::aura::memcpy_s(pNewData,(size_t)nNewMax * m_iTypeSize,
         m_pData,(size_t)m_nSize * m_iTypeSize);

      for(int32_t i = 0; i < nNewSize - m_nSize; i++)
         // get rid of old stuff (note: no destructors called)
         memory_free(m_pData);
      m_pData = pNewData;
      m_nSize = nNewSize;
      m_nMaxSize = nNewMax;
   }

   return countOld;

}
::count array_base::allocate(::count nNewSize,::count nGrowBy)
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
         if(!m_bRaw)
         {
            for(int32_t i = 0; i < m_nSize; i++)
               destruct_element((byte *)m_pData + i * m_iTypeSize);
         }
         memory_free(m_pData);
         m_pData = NULL;
      }
      m_nSize = m_nMaxSize = 0;
   }
   else if(m_pData == NULL)
   {
      // create buffer big enough to hold number of requested elements or
      // m_nGrowBy elements, whichever is larger.
#ifdef SIZE_T_MAX
      if(nNewSize > SIZE_T_MAX / m_iTypeSize)
         throw memory_exception(get_app());
      ASSERT(nNewSize <= SIZE_T_MAX / m_iTypeSize);    // no overflow
#endif
      ::count nAllocSize = MAX(nNewSize,m_nGrowBy);
      m_pData = (byte *)memory_alloc(nAllocSize * m_iTypeSize);
      if(!m_bRaw)
      {
         construct_element_set(m_pData, nNewSize);
      }
      m_nSize = nNewSize;
      m_nMaxSize = nAllocSize;
   }
   else if(nNewSize <= m_nMaxSize)
   {
      // it fits
      if(!m_bRaw)
      {
         if(nNewSize > m_nSize)
         {
            construct_element_set((byte *)m_pData + m_nSize * m_iTypeSize,nNewSize - m_nSize);
         }
         else if(m_nSize > nNewSize)
         {
            // destroy the old elements
            for(int32_t i = 0; i < m_nSize - nNewSize; i++)
               destruct_element((byte*)m_pData + (nNewSize + i) * m_iTypeSize);
         }
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
      ASSERT(nNewMax <= SIZE_T_MAX / m_iTypeSize); // no overflow
#endif
      byte* pNewData = (byte *)memory_alloc(nNewMax * m_iTypeSize);

      // copy new data from old
      ::aura::memcpy_s(pNewData,(size_t)nNewMax * m_iTypeSize,m_pData,(size_t)m_nSize * m_iTypeSize);

      // construct remaining elements
      ASSERT(nNewSize > m_nSize);
      if(!m_bRaw)
      {
         construct_element_set((byte *)pNewData + m_nSize * m_iTypeSize,nNewSize - m_nSize);
      }
      // get rid of old stuff (note: no destructors called)
      memory_free(m_pData);
      m_pData = pNewData;
      m_nSize = nNewSize;
      m_nMaxSize = nNewMax;
   }
   return countOld;
}




void array_base::on_after_read()
{


}



