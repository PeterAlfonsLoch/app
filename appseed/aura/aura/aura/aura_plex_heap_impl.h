#pragma once


#undef new

void Free_check_pointer_in_cpp(void * p);

inline void * plex_heap_alloc_sync::Alloc()
{

   cslock sl(&m_protect);

   //void * pdata = NULL;
//   try
  // {
      if (m_pnodeFree == NULL)
      {
         NewBlock();
      }
      // remove the first available node from the free list
      void * pNode = m_pnodeFree;
      m_pnodeFree = m_pnodeFree->pNext;
      //pdata = pNode;
   //}
   //catch(...)
   //{
   //}
//#ifdef DEBUG
   memset(pNode, 0, m_nAllocSize); // let constructors and algorithms initialize... "random initialization" of not initialized :-> C-:!!
//#endif
   return pNode;
}

inline void plex_heap_alloc_sync::Free(void * p)
{

   if(p == NULL)
      return;

   #ifdef DEBUG
   Free_check_pointer_in_cpp(p);
   #endif

   cslock sl(&m_protect);

#ifdef DEBUG
   memset(p, 0xCD, m_nAllocSize); // attempt to invalidate memory so it get unusable (as it should be after freed).
#endif

   // simply return the node to the free list
   node* pnode = (node*)p;

#ifdef MEMDFREE // Free Debug - duplicate freeing ?

   node * pnodeFree = m_pnodeFree;

   while(pnodeFree != NULL)
   {

      if(pnode == pnodeFree) // dbgsnp - debug snippet
      {

         // already in free list

         if(is_debugger_attached())
         {

            debug_break();

         }

         return;

      }

      pnodeFree = pnodeFree->pNext;

   }

#endif

#if STORE_LAST_BLOCK

   if(m_pnodeLastBlock != NULL)
      system_heap_free(m_pnodeLastBlock);

   m_pnodeLastBlock = (node *) system_heap_alloc(m_nAllocSize + 32);

   memcpy(m_pnodeLastBlock, pnode, m_nAllocSize + 32);

#endif

   pnode->pNext = m_pnodeFree;

   m_pnodeFree = pnode;


}






class CLASS_DECL_AURA plex_heap_alloc :
   public array < plex_heap_alloc_sync *, plex_heap_alloc_sync *, ::allocator::sys < plex_heap_alloc_sync * > >
{
public:

   // // Now alloc from any pool and release to any pool (not necessaraly the same allocated at) . save four bytes per allocation
   uint32_t                      m_uiAlloc; // Now alloc from any pool
   uint32_t                      m_uiFree; // and release to any pool
   uint32_t                      m_uiShareCount;
   uint32_t                      m_uiShareBound;
   uint32_t                      m_uiAllocSize;


   plex_heap_alloc(UINT nAllocSize, UINT nBlockSize = 64);
   virtual ~plex_heap_alloc();

   inline UINT GetAllocSize() { return m_uiAllocSize; }

   inline void * Alloc();               // return a chunk of memory of nAllocSize
   inline void Free(void * p);          // free chunk of memory returned from Alloc
   void FreeAll();               // free everything allocated from this allocator

   void NewBlock();

   void pre_finalize();

   void * operator new(size_t s)
   {
      return system_heap_alloc(sizeof(plex_heap_alloc));
   }

   void operator delete(void * p)
   {
      system_heap_free(p);
   }


};



inline void * plex_heap_alloc::Alloc()
{

   // veripseudo-random generator, don't need to be
   // perfectly sequential or perfectly distributed,
   // just fair well distributed
   // but very important is extremely fast

   return element_at((m_uiAlloc++) % m_uiShareCount)->Alloc();

}

inline void plex_heap_alloc::Free(void * p)
{

   // veripseudo-random generator, don't need to be
   // perfectly sequential or perfectly distributed,
   // just fair well distributed
   // but very important is extremely fast

   element_at((m_uiFree++) % m_uiShareCount)->Free(p);

}


//#define PLEX_HEAP_ALLOC_ARRAY_AINDEX_COUNT 3

//#ifdef OS64BIT
//#define PLEX_HEAP_ALLOC_ARRAY_BINDEX_COUNT 6
//#else
//#define PLEX_HEAP_ALLOC_ARRAY_BINDEX_COUNT 5
//#endif

class CLASS_DECL_AURA plex_heap_alloc_array :
   public array < plex_heap_alloc *, plex_heap_alloc *, ::allocator::sys < plex_heap_alloc * > >
{
public:




   //::count        m_aa[PLEX_HEAP_ALLOC_ARRAY_AINDEX_COUNT];
   //unsigned int   m_aaSize[PLEX_HEAP_ALLOC_ARRAY_AINDEX_COUNT];


   //::count        m_bb[PLEX_HEAP_ALLOC_ARRAY_BINDEX_COUNT];
   //unsigned int   m_bbSize[PLEX_HEAP_ALLOC_ARRAY_BINDEX_COUNT];

   //::count m_iWorkingSize;


//   static memdleak_block * s_pmemdleakList;

   plex_heap_alloc_array();
   virtual ~plex_heap_alloc_array();




   inline void * _alloc(size_t nAllocSize);
   void * _realloc(void * p, size_t nAllocSize, size_t nOldAllocSize, int align);
   inline void _free(void * p, size_t nAllocSize);

   void pre_finalize();

   inline plex_heap_alloc * find(size_t nAllocSize);

   void * alloc_dbg(size_t nAllocSize, int32_t nBlockUse, const char * szFileName, int32_t iLine);
   void * realloc_dbg(void * p, size_t nAllocSize, size_t nOldAllocSize, int align, int32_t nBlockUse, const char * szFileName, int32_t iLine);
   void free_dbg(void * p, size_t nAllocSize);

   void * operator new(size_t s)
   {
      return system_heap_alloc(sizeof(plex_heap_alloc_array));
   }

   void operator delete(void * p)
   {
      system_heap_free(p);
   }

};



inline void * plex_heap_alloc_array::_alloc(size_t size)
{

   plex_heap_alloc * palloc = find(size);

   if(palloc != NULL)
   {

      return palloc->Alloc();

   }
   else
   {

      return ::system_heap_alloc(size);

   }

}

#ifndef DEBUG
void plex_heap_alloc_array::_free(void * p,size_t size)
{

   plex_heap_alloc * palloc = find(size);

   if(palloc != NULL)
   {

      return palloc->Free(p);

   }
   else
   {

      return ::system_heap_free(p);

   }

}
#endif



inline plex_heap_alloc * plex_heap_alloc_array::find(size_t nAllocSize)
{

   //int32_t iA = 0;

//   for(; iA < PLEX_HEAP_ALLOC_ARRAY_AINDEX_COUNT; iA++)
//   {
//
//      if(m_aaSize[iA] >= nAllocSize)
//      {
//
//         break;
//
//      }
//
//   }
//
//   if(iA >= PLEX_HEAP_ALLOC_ARRAY_AINDEX_COUNT)
//      return NULL;
//
//
//   ::count iB = m_aa[iA];
//
//   for(; iB < PLEX_HEAP_ALLOC_ARRAY_BINDEX_COUNT; iB++)
//   {
//
//      if(m_bbSize[iB] >= nAllocSize)
//      {
//
//         break;
//
//      }
//
//   }
//
//   if(iB >= PLEX_HEAP_ALLOC_ARRAY_BINDEX_COUNT)
//      return NULL;

  // ::count i = m_bb[iB];

   for(index i = 0; i < m_nSize; i++)
   {

      if(this->m_pData[i]->m_uiAllocSize >= nAllocSize)
      {

         return this->m_pData[i];

      }

   }

   return NULL;

}




#define new AURA_NEW
