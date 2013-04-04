#pragma once


class CLASS_DECL_ca plex_heap     // warning var length structure
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

class CLASS_DECL_ca plex_heap_alloc_sync
{
public:


   struct node
   {
      node* pNext;               // only valid when in free list
   };


   UINT                       m_nAllocSize;  // size of each block from Alloc
   UINT                       m_nBlockSize;  // number of blocks to get at a time
   plex_heap *                m_pBlocks;     // linked list of blocks (is nBlocks*nAllocSize)
   node*                      m_pnodeFree;   // first free node (::null() if no free nodes)
   simple_critical_section    m_protect;
   int64_t                    m_iFreeHitCount;
   node *                     m_pnodeLastBlock;


   plex_heap_alloc_sync(UINT nAllocSize, UINT nBlockSize = 64);
   virtual ~plex_heap_alloc_sync();

   UINT GetAllocSize() { return m_nAllocSize; }

   inline void * Alloc();               // return a chunk of primitive::memory of nAllocSize
   inline void Free(void * p);          // free chunk of primitive::memory returned from Alloc
   void FreeAll();               // free everything allocated from this allocator

   void NewBlock();


};


inline void * plex_heap_alloc_sync::Alloc()
{

   m_protect.lock();
   void * pdata = ::null();
   try
   {
      if (m_pnodeFree == ::null())
      {
         NewBlock();
      }
      // remove the first available node from the free list
      void * pNode = m_pnodeFree;
      m_pnodeFree = m_pnodeFree->pNext;
      pdata = &((byte *)pNode)[16];
   }
   catch(...)
   {
   }
   m_protect.unlock();
   //memset(pdata, 0, m_nAllocSize); // let constructors and algorithms initialize... "random initialization" of not initialized :-> C-:!!
   return pdata;
}

#define STORE_LAST_BLOCK 0

inline void plex_heap_alloc_sync::Free(void * p)
{

   if(p == ::null())
      return;

   p = &((byte *)p)[-16];

   if(p == ::null())
      return;

   m_protect.lock();

   try
   {

      // simply return the node to the free list
      node* pnode = (node*)p;

#ifdef MEMDFREE // Free Debug - duplicate freeing ?

      node * pnodeFree = m_pnodeFree;

      while(pnodeFree != ::null())
      {

         if(pnode == pnodeFree) // dbgsnp - debug snippet
         {

            // already in free list

            if(is_debugger_attached())
            {

               __debug_break();

            }

            return;

         }

         pnodeFree = pnodeFree->pNext;

      }

#endif

#if STORE_LAST_BLOCK

      if(m_pnodeLastBlock != ::null())
         system_heap_free(m_pnodeLastBlock);

      m_pnodeLastBlock = (node *) system_heap_alloc(m_nAllocSize + 32);

      memcpy(m_pnodeLastBlock, pnode, m_nAllocSize + 32);

#endif

      pnode->pNext = m_pnodeFree;

      m_pnodeFree = pnode;

   }
   catch(...)
   {

   }

   m_protect.unlock();

}






class CLASS_DECL_ca plex_heap_alloc :
   public simple_array < plex_heap_alloc_sync * >
{
public:


   int32_t                        m_i;
   int32_t                        m_iShareCount;


   plex_heap_alloc(UINT nAllocSize, UINT nBlockSize = 64);
   virtual ~plex_heap_alloc();

   inline UINT GetAllocSize() { return element_at(0)->GetAllocSize(); }

   inline void * Alloc();               // return a chunk of primitive::memory of nAllocSize
   inline void Free(void * p);          // free chunk of primitive::memory returned from Alloc
   void FreeAll();               // free everything allocated from this allocator

   void NewBlock();


};



inline void * plex_heap_alloc::Alloc()
{

   // veripseudo-random generator, don't need to be
   // perfectly sequential or perfectly distributed,
   // just fair well distributed
   // but very important is extremely fast
   register int32_t i = m_i;
   if(i >= m_iShareCount)
   {
      i = 0;
      m_i = 1;
   }
   else
   {
      m_i++;
   }


   register void * p  = get_data()[i]->Alloc();

   ((int32_t *) p)[0] = i;

   return &((int32_t *)p)[1];

}

inline void plex_heap_alloc::Free(void * p)
{

   if (p == ::null())
      return;

   register int32_t i = ((int32_t *)p)[-1];

   get_data()[i]->Free(&((int32_t *)p)[-1]);

}







class CLASS_DECL_ca plex_heap_alloc_array :
   public simple_array < plex_heap_alloc * >
{
public:


   struct memdleak_block
   {


      int32_t               m_iBlockUse;
      const char *      m_pszFileName;
      int32_t               m_iLine;
      memdleak_block *  m_pnext;
      memdleak_block *  m_pprevious;

   };


   static memdleak_block * s_pmemdleakList;

   plex_heap_alloc_array();
   virtual ~plex_heap_alloc_array();


   static ::count get_mem_info(int32_t ** ppiUse, const char *** ppszFile, int32_t ** ppiLine);


   inline void * alloc(size_t nAllocSize);
   inline void * realloc(void * p, size_t nOldAllocSize, size_t nNewAllocSize);
   inline void free(void * p, size_t nAllocSize);

   inline plex_heap_alloc * find(size_t nAllocSize);

   void * alloc_dbg(size_t nAllocSize, int32_t nBlockUse, const char * szFileName, int32_t iLine);
   void * realloc_dbg(void * p, size_t nOldAllocSize, size_t nNewAllocSize, int32_t nBlockUse, const char * szFileName, int32_t iLine);
   void free_dbg(void * p, size_t nAllocSize);

};


inline void * plex_heap_alloc_array::alloc(size_t nAllocSize)
{
   plex_heap_alloc * palloc = find(nAllocSize);
   if(palloc != ::null())
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

   plex_heap_alloc * palloc = find(nAllocSize);

   if(palloc != ::null())
   {
      return palloc->Free(p);
   }
   else
   {
      return ::system_heap_free(p);
   }

}


inline void * plex_heap_alloc_array::realloc(void * pOld, size_t nOldAllocSize, size_t nNewAllocSize)
{
   plex_heap_alloc * pallocOld = find(nOldAllocSize);
   plex_heap_alloc * pallocNew = find(nNewAllocSize);
   if(pallocOld == ::null() && pallocNew == ::null())
   {
      return ::system_heap_realloc(pOld, nNewAllocSize);
   }
   else if(pallocOld == pallocNew)
   {
      return pOld;
   }
   else
   {

      void * pNew;

      if(pallocNew != ::null())
      {
         pNew = pallocNew->Alloc();
      }
      else
      {
         pNew = ::system_heap_alloc(nNewAllocSize);
      }

      memcpy(pNew, pOld, min(nOldAllocSize, nNewAllocSize));

      if(pallocOld != ::null())
      {
         pallocOld->Free(pOld);
      }
      else
      {
         ::system_heap_free(pOld);
      }

      return pNew;

   }
}


inline plex_heap_alloc * plex_heap_alloc_array::find(size_t nAllocSize)
{
   size_t nFoundSize = MAX_DWORD_PTR;
   int32_t iFound = -1;
   for(int32_t i = 0; i < this->get_count(); i++)
   {
      if(this->element_at(i)->GetAllocSize() >= nAllocSize && (nFoundSize == MAX_DWORD_PTR || this->element_at(i)->GetAllocSize() < nFoundSize))
      {
         iFound = i;
         nFoundSize = this->element_at(i)->GetAllocSize();
         break;
      }
   }
   if(iFound >= 0)
      return this->element_at(iFound);
   else
      return ::null();
}
