#include "StdAfx.h"

class CLASS_DECL_ca plex_heap     // warning var length structure
{
public:
   plex_heap* pNext;
   // BYTE data[maxNum*elementSize];

   void * data() { return this+1; }

   static plex_heap* PASCAL create(plex_heap*& head, UINT_PTR nMax, UINT_PTR cbElement);
         // like 'calloc' but no zero fill
         // may throw primitive::memory exceptions

   void FreeDataChain();       // free this one and links
};

class CLASS_DECL_ca plex_heap_alloc
{
public:
   plex_heap_alloc(UINT nAllocSize, UINT nBlockSize = 64);
   virtual ~plex_heap_alloc();

   UINT GetAllocSize() { return m_nAllocSize; }

   void * Alloc();               // return a chunk of primitive::memory of nAllocSize
   void Free(void * p);          // free chunk of primitive::memory returned from Alloc
   void FreeAll();               // free everything allocated from this allocator


   struct node
   {
      node* pNext;               // only valid when in free list
   };

   UINT           m_nAllocSize;  // size of each block from Alloc
   UINT           m_nBlockSize;  // number of blocks to get at a time
   plex_heap *    m_pBlocks;     // linked list of blocks (is nBlocks*nAllocSize)
   node*          m_pnodeFree;   // first free node (NULL if no free nodes)
};

plex_heap* PASCAL plex_heap::create(plex_heap*& pHead, UINT_PTR nMax, UINT_PTR cbElement)
{
   ASSERT(nMax > 0 && cbElement > 0);
   if (nMax == 0 || cbElement == 0)
   {
      AfxThrowInvalidArgException();
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

plex_heap_alloc::plex_heap_alloc(UINT nAllocSize, UINT nBlockSize)
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
}

plex_heap_alloc::~plex_heap_alloc()
{
   FreeAll();
}

void plex_heap_alloc::FreeAll()
{
   m_pBlocks->FreeDataChain();
   m_pBlocks = NULL;
   m_pnodeFree = NULL;
}

void * plex_heap_alloc::Alloc()
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

   // remove the first available node from the free list
   void * pNode = m_pnodeFree;
   m_pnodeFree = m_pnodeFree->pNext;
   memset(&((byte *)pNode)[16], 0, m_nAllocSize);
   return &((byte *)pNode)[16];
}

void plex_heap_alloc::Free(void * p)
{

   if(p == NULL)
      return;

   p = &((byte *)p)[-16];

   if(p == NULL)
      return;

   // simply return the node to the free list
   node* pNode = (node*)p;
   pNode->pNext = m_pnodeFree;
   m_pnodeFree = pNode;

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
   mutex_lock lock(&m_mutex, true);
   for(int i = 0; i < this->get_count(); i++)
   {
      delete this->element_at(i);
   }
}

void * plex_heap_alloc_array::alloc(size_t nAllocSize)
{
   mutex_lock lock(&m_mutex, true);
   plex_heap_alloc * palloc = find(nAllocSize);
   if(palloc != NULL)
   {
      return palloc->Alloc();
   }
   else
   {
      return ::system_heap_alloc(nAllocSize);
   }
}

void plex_heap_alloc_array::free(void * p, size_t nAllocSize)
{
   mutex_lock lock(&m_mutex, true);
   plex_heap_alloc * palloc = find(nAllocSize);
   if(palloc != NULL)
   {
      return palloc->Free(p);
   }
   else
   {
      return ::system_heap_free(p);
   }
}


void * plex_heap_alloc_array::realloc(void * pOld, size_t nOldAllocSize, size_t nNewAllocSize)
{
   mutex_lock lock(&m_mutex, true);
   plex_heap_alloc * pallocOld = find(nOldAllocSize);
   plex_heap_alloc * pallocNew = find(nNewAllocSize);
   if(pallocOld == NULL && pallocNew == NULL)
   {
      return ::system_heap_realloc(pOld, nNewAllocSize);
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


plex_heap_alloc * plex_heap_alloc_array::find(size_t nAllocSize)
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

