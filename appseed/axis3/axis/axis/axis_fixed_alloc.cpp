#include "framework.h"

#undef new


fixed_alloc_no_sync::fixed_alloc_no_sync(UINT nAllocSize, UINT nBlockSize)
{
   if(nBlockSize <= 1)
      nBlockSize = 4;

   ASSERT(nAllocSize >= sizeof(node));
   ASSERT(nBlockSize > 1);

   if (nAllocSize < sizeof(node))
      nAllocSize = sizeof(node);
   if (nBlockSize <= 1)
      nBlockSize = 64;

   m_nAllocSize = nAllocSize;
   m_nBlockSize = nBlockSize;
   m_pnodeFree = NULL;
   m_pBlocks = NULL;
}

fixed_alloc_no_sync::~fixed_alloc_no_sync()
{
   FreeAll();
}

void fixed_alloc_no_sync::FreeAll()
{
   m_pBlocks->FreeDataChain();
   m_pBlocks = NULL;
   m_pnodeFree = NULL;
}

void fixed_alloc_no_sync::NewBlock()
{

   int32_t nAllocSize = m_nAllocSize + 32;
   // add another block
   plex* pNewBlock = plex::create(m_pBlocks, m_nBlockSize, nAllocSize);

   // chain them into free list
   node* pNode = (node*)pNewBlock->data();
   // free in reverse order to make it easier to debug
   (BYTE*&)pNode += (nAllocSize * m_nBlockSize) - nAllocSize;
   for (int32_t i = m_nBlockSize-1; i >= 0; i--, (BYTE*&)pNode -= nAllocSize)
   {
      pNode->pNext = m_pnodeFree;
      m_pnodeFree = pNode;
   }

   ASSERT(m_pnodeFree != NULL);  // we must have something

}

/////////////////////////////////////////////////////////////////////////////
// fixed_alloc_sync
//

fixed_alloc_sync::fixed_alloc_sync(UINT nAllocSize, UINT nBlockSize, int32_t iShareCount)
{

   m_i = 0;
   m_iShareCount = iShareCount;
   m_allocptra.allocate(iShareCount);
   m_protectptra.allocate(iShareCount);
   for(int32_t i = 0; i < m_allocptra.get_count(); i++)
   {
      m_allocptra[i] = new fixed_alloc_no_sync(nAllocSize + sizeof(int32_t), nBlockSize);
   }
   for(int32_t i = 0; i < m_protectptra.get_count(); i++)
   {
      m_protectptra[i] = new critical_section();
   }

   m_allocptra.allocate(iShareCount);
   m_protectptra.allocate(iShareCount);
   for(int32_t i = 0; i < m_allocptra.get_count(); i++)
   {
      m_allocptra[i] = new fixed_alloc_no_sync(nAllocSize + sizeof(int32_t), nBlockSize);
   }
   for(int32_t i = 0; i < m_protectptra.get_count(); i++)
   {
      m_protectptra[i] = new critical_section();
   }
}

fixed_alloc_sync::~fixed_alloc_sync()
{
   for(int32_t i = 0; i < m_allocptra.get_count(); i++)
   {
      delete m_allocptra[i];
   }
   for(int32_t i = 0; i < m_protectptra.get_count(); i++)
   {
      delete m_protectptra[i];
   }
}

void fixed_alloc_sync::FreeAll()
{

   for(int32_t i = 0; i < m_allocptra.get_count(); i++)
   {

      m_protectptra[i]->lock();

#ifdef WINDOWS

      __try
      {
         m_allocptra[i]->FreeAll();
      }
      __finally
      {
         m_protectptra[i]->unlock();
      }

#else

      try
      {
         m_allocptra[i]->FreeAll();
      }
      catch(...)
      {
      }

      m_protectptra[i]->unlock();
#endif

   }

}












/////////////////////////////////////////////////////////////////////////////
// fixed_alloc
//

fixed_alloc::fixed_alloc(UINT nAllocSize, UINT nBlockSize)
{

   m_i = 0;

#if defined(METROWIN) || defined(LINUX) || defined(APPLEOS) || defined(ANDROID)
   int32_t iShareCount = 0;
#else
   int32_t iShareCount = ::get_current_process_maximum_affinity() + 1;
#endif

   if(iShareCount <= 0)
      iShareCount = 4;

   m_allocptra.allocate(iShareCount);

   for(int32_t i = 0; i < m_allocptra.get_count(); i++)
   {
      m_allocptra[i] = new fixed_alloc_sync(nAllocSize + sizeof(int32_t), nBlockSize, 12);
   }

   m_iShareCount = iShareCount;

}

fixed_alloc::~fixed_alloc()
{

   for(int32_t i = 0; i < m_allocptra.get_count(); i++)
   {
      delete m_allocptra[i];
   }

}

void fixed_alloc::FreeAll()
{

   for(int32_t i = 0; i < m_allocptra.get_count(); i++)
   {
#ifdef WINDOWS
      __try
      {
         m_allocptra[i]->FreeAll();
      }
      __finally
      {
      }
#else
      try
      {
         m_allocptra[i]->FreeAll();
      }
      catch(...)
      {
      }
#endif
   }

}

















/////////////////////////////////////////////////////////////////////////////
// fixed_alloc_array
//

fixed_alloc_array::fixed_alloc_array()
{
}



fixed_alloc_array::~fixed_alloc_array()
{
   for(int32_t i = 0; i < this->get_count(); i++)
   {
      delete this->element_at(i);
   }
}

void * fixed_alloc_array::alloc(size_t nAllocSize)
{
   fixed_alloc * palloc = find(nAllocSize);
   if(palloc != NULL)
   {
      return palloc->Alloc();
   }
   else
   {
      return memory_alloc(nAllocSize);
   }
}

void fixed_alloc_array::free(void * p, size_t nAllocSize)
{
   fixed_alloc * palloc = find(nAllocSize);
   if(palloc != NULL)
   {
      return palloc->Free(p);
   }
   else
   {
      return memory_free(p);
   }
}

void * fixed_alloc_array::realloc(void * pOld, size_t nOldAllocSize, size_t nNewAllocSize)
{
   fixed_alloc * pallocOld = find(nOldAllocSize);
   fixed_alloc * pallocNew = find(nNewAllocSize);
   if(pallocOld == NULL && pallocNew == NULL)
   {
      return memory_realloc(pOld, nNewAllocSize);
   }
   else if(pallocOld == pallocNew)
   {
      return pOld;
   }
   else
   {

      void * pNew = pallocNew == NULL ? memory_alloc(nNewAllocSize) : pallocNew->Alloc();

      if(pNew == NULL)
         return NULL;

      memcpy(pNew, pOld, min(nOldAllocSize, nNewAllocSize));

      if(pallocOld != NULL)
      {
         pallocOld->Free(pOld);
      }
      else
      {
         memory_free(pOld);
      }

      return pNew;
   }
}

fixed_alloc * fixed_alloc_array::find(size_t nAllocSize)
{
   //synch_lock lock(&m_mutex, true);
   size_t nFoundSize = MAX_DWORD_PTR;
   int32_t iFound = -1;
   for(int32_t i = 0; i < this->get_count(); i++)
   {
      if(this->element_at(i)->m_allocptra[0]->m_allocptra[0]->m_nAllocSize >= nAllocSize
      && (nFoundSize == MAX_DWORD_PTR || this->element_at(i)->m_allocptra[0]->m_allocptra[0]->m_nAllocSize < nFoundSize))
      {
         iFound = i;
         nFoundSize = this->element_at(i)->m_allocptra[0]->m_allocptra[0]->m_nAllocSize;
         break;
      }
   }
   if(iFound >= 0)
      return this->element_at(iFound);
   else
      return NULL;
}
