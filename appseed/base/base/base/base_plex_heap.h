#pragma once

#undef new 
class CLASS_DECL_BASE plex_heap     // warning var length structure
{
public:
   plex_heap* pNext;
   // BYTE data[maxNum*elementSize];

   void * data() { return this+1; }

   static plex_heap* create(plex_heap*& head, uint_ptr nMax, uint_ptr cbElement);
         // like 'calloc' but no zero fill
         // may throw primitive::memory exceptions

   void FreeDataChain();       // free this one and links
};

class CLASS_DECL_BASE plex_heap_alloc_sync
{
public:


   struct node
   {
      node* pNext;               // only valid when in free list
   };


   UINT                       m_nAllocSize;  // size of each block from Alloc
   UINT                       m_nBlockSize;  // number of blocks to get at a time
   plex_heap *                m_pBlocks;     // linked list of blocks (is nBlocks*nAllocSize)
   node*                      m_pnodeFree;   // first free node (NULL if no free nodes)
   critical_section           m_protect;
   int64_t                    m_iFreeHitCount;
   node *                     m_pnodeLastBlock;


   plex_heap_alloc_sync(UINT nAllocSize, UINT nBlockSize = 64);
   virtual ~plex_heap_alloc_sync();

   UINT GetAllocSize() { return m_nAllocSize; }

   inline void * Alloc();               // return a chunk of primitive::memory of nAllocSize
   inline void Free(void * p);          // free chunk of primitive::memory returned from Alloc
   void FreeAll();               // free everything allocated from this allocator

   void NewBlock();

#ifdef WINDOWS

   void * operator new(size_t s)
   {
      return ::HeapAlloc(::GetProcessHeap(), NULL, sizeof(plex_heap_alloc_sync));
   }

   void operator delete(void * p)
   {
      ::HeapFree(::GetProcessHeap(), NULL, p);
   }

#else

   void * operator new(size_t s)
   {
      return ::malloc(sizeof(plex_heap_alloc_sync));
   }

   void operator delete(void * p)
   {
      return free(p);
   }

#endif

};



