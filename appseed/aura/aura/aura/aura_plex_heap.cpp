#include "framework.h"


#undef new


plex_heap_alloc_array::memdleak_block * plex_heap_alloc_array::s_pmemdleakList = NULL;


plex_heap * plex_heap::create(plex_heap*& pHead, uint_ptr nMax, uint_ptr cbElement)
{
   ASSERT(nMax > 0 && cbElement > 0);
   if (nMax == 0 || cbElement == 0)
   {
      throw invalid_argument_exception(get_thread_app());
   }

   plex_heap* p = (plex_heap*) system_heap_alloc(sizeof(plex_heap) + nMax * cbElement);
   
#ifdef DEBUG
   Free_check_pointer_in_cpp(p);
#endif
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

//   m_pprotect = new critical_section();

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

//   delete m_pprotect;

}


void plex_heap_alloc_sync::FreeAll()
{

   m_protect.lock();



   try
   {
      m_pBlocks->FreeDataChain();
      m_pBlocks = NULL;
      m_pnodeFree = NULL;
   }
   catch(...)
   {
   }


   m_protect.unlock();

}


void plex_heap_alloc_sync::NewBlock()
{

   if (m_pnodeFree == NULL)
   {
      size_t nAllocSize = m_nAllocSize;

      // add another block
      plex_heap* pNewBlock = plex_heap::create(m_pBlocks, m_nBlockSize, nAllocSize);

      // chain them into free list
      node* pNode = (node*)pNewBlock->data();
      // free in reverse order to make it easier to debug
      ((BYTE*&)pNode) += (nAllocSize * m_nBlockSize) - nAllocSize;
      for (int32_t i = m_nBlockSize-1; i >= 0; i--, ((BYTE*&)pNode) -= nAllocSize)
      {
         pNode->pNext = m_pnodeFree;
         m_pnodeFree = pNode;
      }
   }
   ASSERT(m_pnodeFree != NULL);  // we must have something
#ifdef DEBUG
   Free_check_pointer_in_cpp(m_pnodeFree);
#endif

}

plex_heap_alloc::plex_heap_alloc(UINT nAllocSize, UINT nBlockSize)
{

#if !defined(METROWIN) && !defined(LINUX) && !defined(APPLEOS) && !defined(ANDROID)

   uint32_t uiShareCount = ::get_current_process_maximum_affinity() + 1;

#else

   int32_t uiShareCount = 0;

#endif

   if(uiShareCount == 0)
      uiShareCount = 4;

   allocate(uiShareCount);

   for(int32_t i = 0; i < get_count(); i++)
   {
      set_at(i, new plex_heap_alloc_sync(nAllocSize + sizeof(int32_t), nBlockSize));
   }

   m_uiShareCount = uiShareCount;
   
   m_uiAllocSize = nAllocSize;

   m_ui = 0;

}

plex_heap_alloc::~plex_heap_alloc()
{

   for(int32_t i = 0; i < get_count(); i++)
   {
      delete element_at(i);
   }

}

void plex_heap_alloc::FreeAll()
{

   for(int32_t i = 0; i < get_count(); i++)
   {

      try
      {
         element_at(i)->FreeAll();
      }
      catch(...)
      {
      }

   }

}


void plex_heap_alloc::pre_finalize()
{

   FreeAll();

   m_pData = NULL; // FreeAll freed all data alloced
   m_nSize = 0;
   m_nMaxSize = 0;

}


extern plex_heap_alloc_array * g_pheap;

plex_heap_alloc_array::plex_heap_alloc_array()
{

   if(g_pheap == NULL)
   {

      g_pheap = this;

   }

   m_iWorkingSize = 0;

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

   m_iWorkingSize = get_size();

}

plex_heap_alloc_array::~plex_heap_alloc_array()
{

   pre_finalize();

   m_iWorkingSize = 0;

   for(int32_t i = 0; i < this->get_count(); i++)
   {
      delete this->element_at(i);
   }

   remove_all();

   if(g_pheap == this)
   {

      g_pheap = NULL;

   }

}

void plex_heap_alloc_array::pre_finalize()
{

   for(int32_t i = 0; i < this->get_count(); i++)
   {
      this->element_at(i)->pre_finalize();
   }

}

mutex * g_pmutgen = NULL;

/*

#define LAST_MEM_FILE_AND_LINE 0


void * ca2_heap_alloc_dbg(size_t size, int32_t nBlockUse, const char * pszFileName, int32_t iLine)
{
#ifdef MEMDLEAK
   size_t * psize = (size_t *) g_pheap->alloc_dbg(size + sizeof(size_t), nBlockUse, pszFileName, iLine);
   psize[0] = size + sizeof(size_t);
   memset(&psize[1], 0, size);
   return &psize[1];
#else
#if LAST_MEM_FILE_AND_LINE
   string str;
   str.Format("%s(%d)", pszFileName, iLine);
   size_t * psize = (size_t *) g_pheap->alloc(size + sizeof(size_t) + 128);
   psize[0] = size + sizeof(size_t) + 128;
   strncpy((char *) &psize[1], str.Mid(MAX(0, str.get_length() - 124)), 124);
   return ((byte *) &psize[1]) + 128;
#else
   
   size_t * psize = psize = (size_t *) g_pheap->alloc(size + sizeof(size_t));
   
   psize[0] = size + sizeof(size_t);
   
   return &psize[1];
   
#endif
#endif
}

void * ca2_heap_realloc_dbg(void * pvoidOld, size_t size, int32_t nBlockUse, const char * szFileName, int32_t iLine)
{
#ifdef MEMDLEAK
   size_t * psize = (size_t *) g_pheap->realloc_dbg(&((size_t *)pvoidOld)[-1], ((size_t *)pvoidOld)[-1], size + sizeof(size_t), nBlockUse, szFileName, iLine);
   psize[0] = size + sizeof(size_t);
   return &psize[1];
#else
#if LAST_MEM_FILE_AND_LINE
   string str;
   str.Format("%s(%d)", szFileName, iLine);
   size_t * psize = (size_t *) g_pheap->realloc(&((size_t *)(((byte *)pvoidOld) - 128))[-1], ((size_t *)(((byte *)pvoidOld) - 128))[-1], size + sizeof(size_t) + 128);
   psize[0] = size + sizeof(size_t) + 128;
   strncpy((char *) &psize[1], str.Mid(MAX(0, str.get_length() - 124)), 124);
   return ((byte *) &psize[1]) + 128;
#else
   size_t * psize = (size_t *) g_pheap->realloc(&((size_t *)(((byte *)pvoidOld)))[-1], ((size_t *)(((byte *)pvoidOld)))[-1], size + sizeof(size_t));
   psize[0] = size + sizeof(size_t);
   return &psize[1];
#endif
#endif
}


void ca2_heap_free_dbg(void * pvoid)
{

}

*/



void * plex_heap_alloc_array::alloc_dbg(size_t size, int32_t nBlockUse, const char * pszFileName, int32_t iLine)
{
   
#ifdef MEMDLEAK
   
   size_t nAllocSize = size + sizeof(size_t) + sizeof(memdleak_block);
   
   plex_heap_alloc * palloc = find(nAllocSize);
   
   memdleak_block * pblock;
   
   if(palloc != NULL)
   {
      
      pblock = (memdleak_block *) palloc->Alloc();
      
   }
   else
   {
      
      pblock = (memdleak_block *) ::system_heap_alloc(nAllocSize);
      
   }
   
   pblock->m_iBlockUse     = nBlockUse;
   
   pblock->m_pszFileName   = strdup(pszFileName); // not trackable, at least think so certainly causes memory leak
   
   pblock->m_iLine         = iLine;
   
   synch_lock lock(g_pmutgen);
   
   pblock->m_pprevious                 = NULL;
   
   pblock->m_pnext                     = s_pmemdleakList;
   
   if(s_pmemdleakList != NULL)
   {
      
      s_pmemdleakList->m_pprevious     = pblock;
      
   }
   
   s_pmemdleakList                     = pblock;
   
   lock.unlock();
   
   size_t * psize = (size_t *) &pblock[1];
   
   if(palloc != NULL)
   {
   
      psize[0] = nAllocSize;
      
   }
   else
   {
   
      psize[0] = 0;
      
   }
   
   memset(&psize[1], 0, size);
   
   return &psize[1];
   
#else
#if LAST_MEM_FILE_AND_LINE
   
   string str;

   str.Format("%s(%d)", pszFileName, iLine);
   
   size_t nAllocSize = size + sizeof(size_t) + 128;
   
   plex_heap_alloc * palloc = find(nAllocSize);
   
   size_t * psize = NULL;
   
   if(palloc != NULL)
   {
      
      psize = (size_t *) palloc->Alloc();
      
      psize[0] = nAllocSize;
      
   }
   else
   {
      
      psize = (size_t *) ::system_heap_alloc(nAllocSize);
      
      psize[0] = 0;
      
   }
   
   strncpy((char *) &psize[1], str.Mid(MAX(0, str.get_length() - 124)), 124);
   
   return ((byte *) &psize[1]) + 128;
   
#else
   
   return alloc(size);
   
#endif
#endif
  


}


void plex_heap_alloc_array::free_dbg(void * p, size_t size)
{
   
#ifdef MEMDLEAK
   
   size_t * psize = &((size_t *)p)[-1];
   
   memdleak_block * pblock = &((memdleak_block *)psize)[-1];

   synch_lock lock(g_pmutgen);

   if(s_pmemdleakList == pblock)
   {
      s_pmemdleakList = pblock->m_pnext;
      s_pmemdleakList->m_pprevious = NULL;
   }
   else
   {
      pblock->m_pprevious->m_pnext = pblock->m_pnext;
      if(pblock->m_pnext != NULL)
      {
         pblock->m_pnext->m_pprevious = pblock->m_pprevious;
      }
   }

   ::free((void *) pblock->m_pszFileName);

   
   if(*psize == 0)
   {
     
      return ::system_heap_free(pblock);
      
   }
   else
   {
      
      plex_heap_alloc * palloc = find(*psize);
      
      if(palloc != NULL)
      {
      
         return palloc->Free(pblock);
      
      }
      else
      {
      
         return ::system_heap_free(pblock);
      
      }
      
   }
   
#else
   
#if LAST_MEM_FILE_AND_LINE
   
   
   size_t * psize = &((size_t *)((byte *)pvoid) - 128))[-1];
   
   if(*psize == 0)
   {
      
      return ::system_heap_free(psize);
      
   }
   
   plex_heap_alloc * palloc = find(*psize);
   
   if(palloc != NULL)
   {
      
      return palloc->Free(psize);
      
   }
   else
   {
      
      return ::system_heap_free(psize);
      
   }

#else
   
   return free(p, size);
   
#endif
#endif

}


void * plex_heap_alloc_array::realloc_dbg(void * p,  size_t size, size_t sizeOld, int align, int32_t nBlockUse, const char * pszFileName, int32_t iLine)
{
   
#ifdef MEMDLEAK
   
   
   size_t nAllocSize = size + sizeof(size_t) + sizeof(memdleak_block);
   
   size_t * psizeOld = &((size_t *)p)[-1];
   
   plex_heap_alloc * pallocOld = *psizeOld == 0 ? NULL : find(*psizeOld);

   plex_heap_alloc * pallocNew = find(nAllocSize);

   memdleak_block * pblock = &((memdleak_block *)psizeOld)[-1];

   synch_lock lock(g_pmutgen);

   if(s_pmemdleakList == pblock)
   {
      s_pmemdleakList = pblock->m_pnext;
      s_pmemdleakList->m_pprevious = NULL;
   }
   else
   {
      pblock->m_pprevious->m_pnext = pblock->m_pnext;
      if(pblock->m_pnext != NULL)
      {
         pblock->m_pnext->m_pprevious = pblock->m_pprevious;
      }
   }

   ::free((void *) pblock->m_pszFileName);

   size_t * psizeNew = NULL;

   if(pallocOld == NULL && pallocNew == NULL)
   {
   
      pblock = (memdleak_block *) ::system_heap_realloc(pblock, size + sizeof(memdleak_block));
      
      psizeNew = (size_t *) &pblock[1];
      
   }
   else if(pallocOld == pallocNew)
   {
      
      pblock = (memdleak_block *) pblock;
      
      psizeNew = (size_t *) &pblock[1];
      
   }
   else
   {
      
      memdleak_block * pblockNew = NULL;

      if(pallocNew != NULL)
      {
         
         pblockNew = (memdleak_block *) pallocNew->Alloc();
         
      }
      else
      {
         
         pblockNew = (memdleak_block *) ::system_heap_alloc(nAllocSize);
         
      }

      memcpy(pblockNew, pblock, MIN(*psizeOld, nAllocSize));

      if(pallocOld != NULL)
      {
         
         pallocOld->Free(pblock);
         
      }
      else
      {
         
         ::system_heap_free(pblock);
         
      }

      pblock = pblockNew;

      psizeNew = (size_t *) &pblock[1];
      
   }

   psizeNew[0] = nAllocSize;
   
   pblock->m_iBlockUse     = nBlockUse;
   pblock->m_pszFileName   = strdup(pszFileName);
   pblock->m_iLine         = iLine;


   pblock->m_pprevious                 = NULL;
   pblock->m_pnext                     = s_pmemdleakList;
   if(s_pmemdleakList != NULL)
   {
      s_pmemdleakList->m_pprevious        = pblock;
   }
   s_pmemdleakList                     = pblock;
   lock.unlock();


   return &psizeNew[1];
   
//   size_t * psize = (size_t *) g_pheap->realloc_dbg(&((size_t *)pvoidOld)[-1], ((size_t *)pvoidOld)[-1], size + sizeof(size_t), nBlockUse, szFileName, iLine);
  // psize[0] = size + sizeof(size_t);
   //return &psize[1];
#else
#if LAST_MEM_FILE_AND_LINE
   string str;
   str.Format("%s(%d)", szFileName, iLine);
   size_t * psize = (size_t *) realloc(&((size_t *)(((byte *)pvoidOld) - 128))[-1], ((size_t *)(((byte *)pvoidOld) - 128))[-1], size + sizeof(size_t) + 128);
   psize[0] = size + sizeof(size_t) + 128;
   strncpy((char *) &psize[1], str.Mid(MAX(0, str.get_length() - 124)), 124);
   return ((byte *) &psize[1]) + 128;
#else
   
   return realloc(p, size, sizeOld, align);
   
#endif
#endif

}


::count plex_heap_alloc_array::get_mem_info(int32_t ** ppiUse, const char *** ppszFile, int32_t ** ppiLine)
{

#ifndef MEMDLEAK

   throw simple_exception(get_thread_app(), "plex_heap_alloc_array::get_mem_info member function is available only with \"memdleak\" builds - MEMDLEAK defined");

#endif

   synch_lock lock(g_pmutgen);

   memdleak_block * pblock = s_pmemdleakList;

   ::count ca = 0;

   while(pblock != NULL)
   {

      ca++;

      pblock = pblock->m_pnext;

   }


   int32_t * piUse =(int32_t *)  malloc(sizeof(int32_t) * ca);
   const char ** pszFile = (const char **) malloc(sizeof(const char *) * ca);
   int32_t * piLine =(int32_t *)  malloc(sizeof(int32_t) * ca);

   index i = 0;

   pblock = s_pmemdleakList;

   while(pblock != NULL && i < ca)
   {
      piUse[i] = pblock->m_iBlockUse;
      pszFile[i] = strdup(pblock->m_pszFileName);
      piLine[i] = pblock->m_iLine;

      i++;

      pblock = pblock->m_pnext;



   }

   *ppiUse = piUse;
   *ppszFile = pszFile;
   *ppiLine = piLine;


   return ca;

}




void * plex_heap_alloc_array::realloc(void * p, size_t size, size_t sizeOld, int align)
{

   plex_heap_alloc * pallocOld = find(sizeOld);

   plex_heap_alloc * pallocNew = find(size);
   
   void * pNew = NULL;

   if (pallocOld == NULL && pallocNew == NULL)
   {

      pNew = (size_t *) ::system_heap_realloc(p, size);

   }
   else if (pallocOld == pallocNew)
   {

      pNew = p;

   }
   else
   {

      if (pallocNew != NULL)
      {

         pNew = (size_t *) pallocNew->Alloc();

      }
      else
      {

         pNew = (size_t *) ::system_heap_alloc(size);

      }

      if (align > 0)
      {
      
         int_ptr oldSize = (((int_ptr) p & ((int_ptr) align - 1)));
         
         if(oldSize > 0)
         {
         
            oldSize = sizeOld - (align - oldSize);
            
         }
         else
         {
         
            oldSize = sizeOld;
         
         }

         int_ptr newSize = (((int_ptr) pNew & ((int_ptr) align - 1)));
         
         if(newSize > 0)
         {
            
            newSize = size - (align - newSize);
            
         }
         else
         {
         
            newSize = size;
         
         }
         
         memcpy(
                (void *)(((int_ptr)pNew + align - 1) & ~((int_ptr)align - 1)),
                (void *)(((int_ptr)p + align - 1) & ~((int_ptr)align - 1)),
                MIN(oldSize, newSize));

      }
      else
      {

         memcpy(pNew, p, MIN(sizeOld, size));

      }

      if (pallocOld != NULL)
      {

         pallocOld->Free(p);

      }
      else
      {

         ::system_heap_free(p);

      }

   }

   return pNew;

}

void * g_pf1 = NULL;

void Free_check_pointer_in_cpp(void * p)
{

   if((unsigned long) p <  (unsigned long)  g_pf1)
   {
      printf("hit g_pf1");
   }

}
