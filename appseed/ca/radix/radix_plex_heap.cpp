#include "framework.h"


plex_heap * PASCAL plex_heap::create(plex_heap*& pHead, UINT_PTR nMax, UINT_PTR cbElement)
{
   ASSERT(nMax > 0 && cbElement > 0);
   if (nMax == 0 || cbElement == 0)
   {
      throw invalid_argument_exception();
   }

   plex_heap* p = (plex_heap*) system_heap_alloc(sizeof(plex) + nMax * cbElement);
         // may throw exception
   p->pNext = pHead;
   pHead = p;  // change head (adds in reverse order for simplicity)
   return p;
}


void plex_heap::FreeDataChain()     // free this one and links
{

   plex_heap* p = this;
   while (p != NULL)
   {
      BYTE* bytes = (BYTE*) p;
      plex_heap* pNext = p->pNext;
      system_heap_free(bytes);
      p = pNext;
   }

}




plex_heap_alloc_sync::plex_heap_alloc_sync(UINT nAllocSize, UINT nBlockSize)
{

   if(nBlockSize <= 1)
      nBlockSize = 4;

   ASSERT(nAllocSize >= sizeof(node));
   ASSERT(nBlockSize > 1);

   if (nAllocSize < sizeof(node))
      nAllocSize = sizeof(node);
   if (nBlockSize <= 0)
      nBlockSize = 64;

   m_nAllocSize = nAllocSize;
   m_nBlockSize = nBlockSize;
   m_pnodeFree = NULL;
   m_pBlocks = NULL;
   m_iFreeHitCount = 0;
   m_pnodeLastBlock = NULL;

}


plex_heap_alloc_sync::~plex_heap_alloc_sync()
{
   FreeAll();
}

void plex_heap_alloc_sync::FreeAll()
{
   
   m_protect.lock();

   __try
   {
      m_pBlocks->FreeDataChain();
      m_pBlocks = NULL;
      m_pnodeFree = NULL;
   }
   __finally
   {
      m_protect.unlock();
   }

}

void plex_heap_alloc_sync::NewBlock()
{

   if (m_pnodeFree == NULL)
   {
      size_t nAllocSize = m_nAllocSize + 32;

      // add another block
      plex_heap* pNewBlock = plex_heap::create(m_pBlocks, m_nBlockSize, nAllocSize);

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

}

plex_heap_alloc::plex_heap_alloc(UINT nAllocSize, UINT nBlockSize)
{
   
   int iShareCount = ::get_current_process_maximum_affinity() + 1;

   if(iShareCount <= 0)
      iShareCount = 4;

   set_size(iShareCount);

   for(int i = 0; i < get_count(); i++)
   {
      set_at(i, new plex_heap_alloc_sync(nAllocSize + sizeof(int), nBlockSize));
   }

   m_iShareCount = iShareCount;

}

plex_heap_alloc::~plex_heap_alloc()
{
   
   for(int i = 0; i < get_count(); i++)
   {
      delete element_at(i);
   }

}

void plex_heap_alloc::FreeAll()
{
   
   for(int i = 0; i < get_count(); i++)
   {
      __try
      {
         element_at(i)->FreeAll();
      }
      __finally
      {
      }
   }

}


plex_heap_alloc_array::plex_heap_alloc_array()
{

   add(new plex_heap_alloc(8, 256));
   add(new plex_heap_alloc(16, 256));
   add(new plex_heap_alloc(24, 256));
   add(new plex_heap_alloc(32, 256));
   add(new plex_heap_alloc(48, 256));

   add(new plex_heap_alloc(64, 128));
   add(new plex_heap_alloc(96, 128));
   add(new plex_heap_alloc(128, 128));
   add(new plex_heap_alloc(192, 128));
   add(new plex_heap_alloc(256, 128));

   add(new plex_heap_alloc(384));
   add(new plex_heap_alloc(512));
   add(new plex_heap_alloc(768));
   add(new plex_heap_alloc(1024));
   add(new plex_heap_alloc(1024 * 2));

   add(new plex_heap_alloc(1024 * 4, 32));
   add(new plex_heap_alloc(1024 * 8, 16));
   add(new plex_heap_alloc(1024 * 16, 8));
   add(new plex_heap_alloc(1024 * 32, 4));
   add(new plex_heap_alloc(1024 * 64, 2));

   add(new plex_heap_alloc(1024 * 128, 1));
   add(new plex_heap_alloc(1024 * 192, 1));
   add(new plex_heap_alloc(1024 * 256, 1));
   add(new plex_heap_alloc(1024 * 384, 1));
   add(new plex_heap_alloc(1024 * 512, 1));
   add(new plex_heap_alloc(1024 * 768, 1));
   add(new plex_heap_alloc(1024 * 1024, 1));
   add(new plex_heap_alloc(1024 * 1024 * 2, 1));

}

plex_heap_alloc_array::~plex_heap_alloc_array()
{
   for(int i = 0; i < this->get_count(); i++)
   {
      delete this->element_at(i);
   }
}



void * plex_heap_alloc_array::alloc_dbg(size_t nAllocSize, int nBlockUse, const char * pszFileName, int iLine)
{
   plex_heap_alloc * palloc = find(nAllocSize + sizeof(memdleak_block));
   memdleak_block * pblock;
   if(palloc != NULL)
   {
      pblock = (memdleak_block *) palloc->Alloc();
   }
   else
   {
      pblock = (memdleak_block *) ::system_heap_alloc(nAllocSize + sizeof(memdleak_block));
   }
   
   pblock->m_iBlockUse     = nBlockUse;
   pblock->m_pszFileName   = *((id) pszFileName).m_pstr;
   pblock->m_iLine         = iLine;

   return pblock + sizeof(memdleak_block);

}


void plex_heap_alloc_array::free_dbg(void * p, size_t nAllocSize)
{

   plex_heap_alloc * palloc = find(nAllocSize + sizeof(memdleak_block));

   if(palloc != NULL)
   {
      return palloc->Free(p);
   }
   else
   {
      return ::system_heap_free(p);
   }

}


void * plex_heap_alloc_array::realloc_dbg(void * pOld, size_t nOldAllocSize, size_t nNewAllocSize, int nBlockUse, const char * pszFileName, int iLine)
{
   plex_heap_alloc * pallocOld = find(nOldAllocSize + sizeof(memdleak_block));
   plex_heap_alloc * pallocNew = find(nNewAllocSize + sizeof(memdleak_block));
   memdleak_block * pblock;
   if(pallocOld == NULL && pallocNew == NULL)
   {
      pblock = (memdleak_block *) ::system_heap_realloc(pOld, nNewAllocSize + sizeof(memdleak_block));
   }
   else if(pallocOld == pallocNew)
   {
      pblock = (memdleak_block *) pOld;
   }
   else
   {

      void * pNew;
      
      if(pallocNew != NULL)
      {
         pNew = pallocNew->Alloc();
      }
      else
      {
         pNew = ::system_heap_alloc(nNewAllocSize + sizeof(memdleak_block));
      }

      memcpy(pNew, pOld, min(nOldAllocSize + sizeof(memdleak_block), nNewAllocSize + sizeof(memdleak_block)));

      if(pallocOld != NULL)
      {
         pallocOld->Free(pOld);
      }
      else
      {
         ::system_heap_free(pOld);
      }

      pblock = (memdleak_block *) pNew;

   }

   pblock->m_iBlockUse     = nBlockUse;
   pblock->m_pszFileName   = *((id) pszFileName).m_pstr;
   pblock->m_iLine         = iLine;

   return pblock + sizeof(memdleak_block);

}
