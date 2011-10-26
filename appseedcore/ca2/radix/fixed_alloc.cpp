#include "StdAfx.h"

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

void * fixed_alloc_no_sync::Alloc()
{
   restart:
   if (m_pnodeFree == NULL)
   {
      int nAllocSize = m_nAllocSize + 32;
      // add another block
      plex* pNewBlock = plex::create(m_pBlocks, m_nBlockSize, nAllocSize);

      // chain them into free list
      node* pNode = (node*)pNewBlock->data();
      // free in reverse order to make it easier to debug
      (BYTE*&)pNode += (nAllocSize * m_nBlockSize) - nAllocSize;
      for (int i = m_nBlockSize-1; i >= 0; i--, (BYTE*&)pNode -= nAllocSize)
      {
         pNode->pNext = m_pnodeFree;
         m_pnodeFree = pNode;
      }
   }
   ASSERT(m_pnodeFree != NULL);  // we must have something

   // remove the first available node from the free list
   void * pNode = m_pnodeFree;
   try
   {
      m_pnodeFree = m_pnodeFree->pNext;
   }
   catch(...)
   {
      m_pnodeFree = NULL;
      goto restart;
   }
   return (void *) (((byte *)pNode) + 16);
}

void fixed_alloc_no_sync::Free(void * p)
{
   p = (void *) (((byte *)p) - 16);
   if(p == (void *) 0xcdcdcdcd)
   {
      if(::IsDebuggerPresent())
      {
         // Bingo!!
         ::DebugBreak();
      }
   }
   else if (p != NULL)
   {
      // simply return the node to the free list
      node* pNode = (node*)p;
      pNode->pNext = m_pnodeFree;
      m_pnodeFree = pNode;
   }
}

/////////////////////////////////////////////////////////////////////////////
// fixed_alloc

fixed_alloc::fixed_alloc(UINT nAllocSize, UINT nBlockSize)
   : baseclass(nAllocSize, nBlockSize)
{
}

fixed_alloc::~fixed_alloc()
{
}

void fixed_alloc::FreeAll()
{
   m_protect.lock();
   __try
   {
      baseclass::FreeAll();
   }
   __finally
   {
      m_protect.unlock();
   }
}

void * fixed_alloc::Alloc()
{
   m_protect.lock();
   void * p = NULL;
   try
   {
      p = baseclass::Alloc();
   }
   catch(base_exception * pe)
   {
      m_protect.unlock();
      ::ca::rethrow(pe);
   }


   m_protect.unlock();
   return p;
}

void fixed_alloc::Free(void * p)
{
   if (p != NULL)
   {
      m_protect.lock();
      __try
      {
         baseclass::Free(p);
      }
      __finally
      {
        m_protect.unlock();
      }
   }
}





fixed_alloc_array::fixed_alloc_array()
{
}



fixed_alloc_array::~fixed_alloc_array()
{
   mutex_lock lock(&m_mutex, true);
   for(int i = 0; i < this->get_count(); i++)
   {
      delete this->element_at(i);
   }
}

void * fixed_alloc_array::alloc(size_t nAllocSize)
{
   mutex_lock lock(&m_mutex, true);
   fixed_alloc * palloc = find(nAllocSize);
   if(palloc != NULL)
   {
      return palloc->Alloc();
   }
   else
   {
      single_lock sl(get_heap_mutex(), TRUE);
      return ca2_alloc(nAllocSize);
   }
}

void fixed_alloc_array::free(void * p, size_t nAllocSize)
{
   mutex_lock lock(&m_mutex, true);
   fixed_alloc * palloc = find(nAllocSize);
   if(palloc != NULL)
   {
      return palloc->Free(p);
   }
   else
   {
      single_lock sl(get_heap_mutex(), TRUE);
      return ca2_free_dbg(p, _AFX_CLIENT_BLOCK);
   }
}

void * fixed_alloc_array::realloc(void * pOld, size_t nOldAllocSize, size_t nNewAllocSize)
{
   mutex_lock lock(&m_mutex, true);
   fixed_alloc * pallocOld = find(nOldAllocSize);
   fixed_alloc * pallocNew = find(nNewAllocSize);
   if(pallocOld == NULL && pallocNew == NULL)
   {
      single_lock sl(get_heap_mutex(), TRUE);
      return ca2_realloc_dbg(pOld, nNewAllocSize, _AFX_CLIENT_BLOCK, NULL, -1);
   }
   else if(pallocOld == pallocNew)
   {
      return pOld;
   }
   else
   {
      void * pNew = alloc(nNewAllocSize);

      if(pNew == NULL)
         return NULL;

      memcpy(pNew, pOld, min(nOldAllocSize, nNewAllocSize));

      free(pOld, nOldAllocSize);

      return pNew;
   }
}

fixed_alloc * fixed_alloc_array::find(size_t nAllocSize)
{
   mutex_lock lock(&m_mutex, true);
   size_t nFoundSize = MAX_DWORD_PTR;
   int iFound = -1;
   for(int i = 0; i < this->get_count(); i++)
   {
      if(this->element_at(i)->m_nAllocSize >= nAllocSize && (nFoundSize == MAX_DWORD_PTR || this->element_at(i)->m_nAllocSize < nFoundSize))
      {
         iFound = i;
         nFoundSize = this->element_at(i)->m_nAllocSize;
         break;
      }
   }
   if(iFound >= 0)
      return this->element_at(iFound);
   else
      return NULL;
}
