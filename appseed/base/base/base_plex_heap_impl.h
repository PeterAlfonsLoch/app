#pragma once


inline void * plex_heap_alloc_sync::Alloc()
{

   m_protect.lock();
   void * pdata = NULL;
   try
   {
      if (m_pnodeFree == NULL)
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

   if(p == NULL)
      return;

   p = &((byte *)p)[-16];

   if(p == NULL)
      return;

   m_protect.lock();

   try
   {

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

               __debug_break();

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
   catch(...)
   {

   }

   m_protect.unlock();

}






class CLASS_DECL_c plex_heap_alloc :
   public array < plex_heap_alloc_sync * >
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

   void pre_finalize();

   void * operator new(size_t s)
   {
      return ::malloc(sizeof(plex_heap_alloc));
   }

   void operator delete(void * p)
   {
      ::free(p);
   }


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

   if (p == NULL)
      return;

   register int32_t i = ((int32_t *)p)[-1];

   get_data()[i]->Free(&((int32_t *)p)[-1]);

}




class CLASS_DECL_c plex_heap_alloc_array :
   public array < plex_heap_alloc * >
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


   ::count m_iWorkingSize;


   static memdleak_block * s_pmemdleakList;

   plex_heap_alloc_array();
   virtual ~plex_heap_alloc_array();


   static ::count get_mem_info(int32_t ** ppiUse, const char *** ppszFile, int32_t ** ppiLine);


   inline void * alloc(size_t nAllocSize);
   inline void * realloc(void * p, size_t nOldAllocSize, size_t nNewAllocSize);
   inline void free(void * p, size_t nAllocSize);

   void pre_finalize();

   inline plex_heap_alloc * find(size_t nAllocSize);

   void * alloc_dbg(size_t nAllocSize, int32_t nBlockUse, const char * szFileName, int32_t iLine);
   void * realloc_dbg(void * p, size_t nOldAllocSize, size_t nNewAllocSize, int32_t nBlockUse, const char * szFileName, int32_t iLine);
   void free_dbg(void * p, size_t nAllocSize);

   void * operator new(size_t s)
   {
      return ::malloc(sizeof(plex_heap_alloc_array));
   }

   void operator delete(void * p)
   {
      ::free(p);
   }

};



inline void * plex_heap_alloc_array::alloc(size_t nAllocSize)
{
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


inline void * plex_heap_alloc_array::realloc(void * pOld, size_t nOldAllocSize, size_t nNewAllocSize)
{
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

      void * pNew;

      if(pallocNew != NULL)
      {
         pNew = pallocNew->Alloc();
      }
      else
      {
         pNew = ::system_heap_alloc(nNewAllocSize);
      }

      memcpy(pNew, pOld, min(nOldAllocSize, nNewAllocSize));

      if(pallocOld != NULL)
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
   for(int32_t i = 0; i < m_iWorkingSize; i++)
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
      return NULL;
}



