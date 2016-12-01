#pragma once


#undef new


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

   void * Alloc();               // return a chunk of memory of nAllocSize
   void Free(void * p);          // free chunk of memory returned from Alloc
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




   void * _alloc(size_t nAllocSize);
   void * _realloc(void * p, size_t nAllocSize, size_t nOldAllocSize, int align);
   void _free(void * p, size_t nAllocSize);

   void pre_finalize();

   plex_heap_alloc * find(size_t nAllocSize);

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






#define new AURA_NEW


