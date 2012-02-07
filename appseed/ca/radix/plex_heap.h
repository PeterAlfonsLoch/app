#pragma once


class plex_heap_alloc;


class CLASS_DECL_ca plex_heap_alloc_array : 
   public base_array < plex_heap_alloc * >
{
public: 


   struct memdleak_block
   {
   
   
      int               m_iBlockUse;
      const char *      m_pszFileName;
      int               m_iLine;


   };

   plex_heap_alloc_array();
   virtual ~plex_heap_alloc_array();

   void * alloc(size_t nAllocSize);
   void * realloc(void * p, size_t nOldAllocSize, size_t nNewAllocSize);
   void free(void * p, size_t nAllocSize);

   plex_heap_alloc * find(size_t nAllocSize);

   void * alloc_dbg(size_t nAllocSize, int nBlockUse, const char * szFileName, int iLine);
   void * realloc_dbg(void * p, size_t nOldAllocSize, size_t nNewAllocSize, int nBlockUse, const char * szFileName, int iLine);
   void free_dbg(void * p, size_t nAllocSize);

};
