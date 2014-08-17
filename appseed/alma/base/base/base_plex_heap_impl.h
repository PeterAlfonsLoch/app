#pragma once


#undef new


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
      pdata = pNode;
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
   catch(...)
   {

   }

   m_protect.unlock();

}






class CLASS_DECL_BASE plex_heap_alloc :
   public array < plex_heap_alloc_sync * >
{
public:


   int32_t                        m_i;
   int32_t                        m_iShareCount;
   int32_t                        m_iAllocSize;


   plex_heap_alloc(UINT nAllocSize, UINT nBlockSize = 64);
   virtual ~plex_heap_alloc();

   inline UINT GetAllocSize() { return m_iAllocSize; }

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

   int32_t i = m_i % m_iShareCount;

   m_i++;

   int32_t * pi = (int32_t *) element_at(i)->Alloc();

   *pi = i;

   return &pi[1];

}

inline void plex_heap_alloc::Free(void * p)
{

   if (p == NULL)
      return;

   int32_t i = ((int32_t *)p)[-1];

   if(i >= 0 && i < m_iShareCount)
   {

      element_at(i)->Free(&((int32_t *)p)[-1]);

   }
   else
   {

      ::OutputDebugStringW(L"plex_heap_alloc::Free error");

   }


}




class CLASS_DECL_BASE plex_heap_alloc_array :
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
   void * realloc(void * p, size_t nAllocSize, size_t nOldAllocSize, int align);
   inline void free(void * p, size_t nAllocSize);

   void pre_finalize();

   inline plex_heap_alloc * find(size_t nAllocSize);

   void * alloc_dbg(size_t nAllocSize, int32_t nBlockUse, const char * szFileName, int32_t iLine);
   void * realloc_dbg(void * p, size_t nAllocSize, size_t nOldAllocSize, int align, int32_t nBlockUse, const char * szFileName, int32_t iLine);
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



inline void * plex_heap_alloc_array::alloc(size_t size)
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


void plex_heap_alloc_array::free(void * p, size_t size)
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




inline plex_heap_alloc * plex_heap_alloc_array::find(size_t nAllocSize)
{

   for(int32_t i = 0; i < m_iWorkingSize; i++)
   {

      if(this->element_at(i)->GetAllocSize() >= nAllocSize)
      {

         return this->element_at(i);

      }

   }

   return NULL;

}




#define new BASE_NEW
