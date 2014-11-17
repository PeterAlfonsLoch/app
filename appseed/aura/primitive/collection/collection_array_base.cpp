#include "framework.h"


index array_base::remove_at(index nIndex,::count nCount)
{

   //ASSERT_VALID(this);

   index nUpperBound = nIndex + nCount;

   if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
      throw invalid_argument_exception(get_app());

   // just remove a range
   ::count nMoveCount = m_nSize - (nUpperBound);
   for(int32_t i = 0; i < nCount; i++)
      destruct_element((byte*)m_pData + (nIndex + i) *m_iTypeSize);

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
      void* pNewData = NULL;
      if(m_nSize != 0)
      {
         pNewData = memory_alloc(m_nSize * m_iTypeSize);
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



void array_base::construct_element(void * p) { on_construct_element(p); }
void array_base::construct_element(void * p,::count c) { on_construct_element(p,c); }
void array_base::destruct_element(void * p) { try { on_destruct_element(p); } catch(...) {} }


void array_base::on_construct_element(void *) {}
void array_base::on_construct_element(void *,::count) {}
void array_base::on_destruct_element(void *) {}


void array_base::destroy()
{
   ASSERT_VALID(this);

   if(m_pData != NULL)
   {
      for(int32_t i = 0; i < m_nSize; i++)
         destruct_element((byte *) m_pData + i * m_iTypeSize);
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
      ::aura::memmove_s(m_pData + (nIndex + nCount) * m_iTypeSize,(nOldSize - nIndex) * sizeof(TYPE),m_pData + nIndex,(nOldSize - nIndex) * sizeof(TYPE));

      DEFCONSTRUCTOR::construct(m_pData + nIndex,nCount);
   }

   // insert new value in the gap
   ASSERT(nIndex + nCount <= m_nSize);

   index nIndexParam = nIndex;

   while(nCount--)
      m_pData[nIndex++] = newElement;

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
template<class TYPE,class ARG_TYPE>
inline void array_base::_001RemoveIndexes(index_array & ia)
{

   // sort
   ia.quick_sort(true);

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
