#pragma once

#include "plex.h"

class mutex;

class CLASS_DECL_ca fixed_alloc_no_sync
{
public:
   fixed_alloc_no_sync(UINT nAllocSize, UINT nBlockSize = 64);
   ~fixed_alloc_no_sync();

   UINT GetAllocSize() { return m_nAllocSize; }

   void * Alloc();  // return a chunk of primitive::memory of nAllocSize
   void Free(void * p); // free chunk of primitive::memory returned from Alloc
   void FreeAll(); // free everything allocated from this allocator


   struct node
   {
      node* pNext;   // only valid when in free list
   };

   UINT m_nAllocSize;   // size of each block from Alloc
   UINT m_nBlockSize;   // number of blocks to get at a time
   plex* m_pBlocks;   // linked list of blocks (is nBlocks*nAllocSize)
   node* m_pnodeFree;   // first free node (NULL if no free nodes)
};

class CLASS_DECL_ca fixed_alloc : public fixed_alloc_no_sync
{
public:
   typedef class fixed_alloc_no_sync baseclass;

   fixed_alloc(UINT nAllocSize, UINT nBlockSize = 64);
   ~fixed_alloc();

   void * Alloc();   // return a chunk of primitive::memory of nAllocSize
   void Free(void * p);   // free chunk of primitive::memory returned from Alloc
   void FreeAll();   // free everything allocated from this allocator

protected:
   simple_critical_section m_protect;
};

#include "exception/base_exception.h"
#include "exception/simple_exception.h"
#include "exception/exception_assert.h"
#include "collection/base_array.h"

class CLASS_DECL_ca fixed_alloc_array :
   public base_array < fixed_alloc * >
{
public:


   fixed_alloc_array();
   virtual ~fixed_alloc_array();

   void * alloc(size_t nAllocSize);
   void free(void * p, size_t nAllocSize);
   void * realloc(void * p, size_t nOldAllocSize, size_t nNewAllocSize);

   fixed_alloc * find(size_t nAllocSize);


};


//#ifndef _DEBUG

#undef new

// DECLARE_FIXED_ALLOC -- used in class definition
/*#define DECLARE_FIXED_ALLOC(class_name) \
public: \
   void * operator new(size_t size) \
   { \
      ASSERT(size == s_alloc.GetAllocSize()); \
      UNUSED(size); \
      return s_alloc.Alloc(); \
   } \
   void * operator new(size_t, void * p) \
      { return p; } \
   void operator delete(void * p) { s_alloc.Free(p); } \
   void * operator new(size_t size, const char *, int) \
   { \
      ASSERT(size == s_alloc.GetAllocSize()); \
      UNUSED(size); \
      return s_alloc.Alloc(); \
   } \
   void operator delete(void * p, const char *, int) { s_alloc.Free(p); } \
protected: \
   static fixed_alloc s_alloc; \
public: \


// IMPLEMENT_FIXED_ALLOC -- used in class implementation file
#define IMPLEMENT_FIXED_ALLOC(class_name, block_size) \
fixed_alloc class_name::s_alloc(sizeof(class_name), block_size) \

// DECLARE_FIXED_ALLOC -- used in class definition
#define DECLARE_FIXED_ALLOC_NOSYNC(class_name) \
public: \
   void * operator new(size_t size) \
   { \
      ASSERT(size == s_alloc.GetAllocSize()); \
      UNUSED(size); \
      return s_alloc.Alloc(); \
   } \
   void * operator new(size_t, void * p) \
      { return p; } \
   void operator delete(void * p) { s_alloc.Free(p); } \
   void * operator new(size_t size, const char *, int) \
   { \
      ASSERT(size == s_alloc.GetAllocSize()); \
      UNUSED(size); \
      return s_alloc.Alloc(); \
   } \
protected: \
   static fixed_alloc_no_sync s_alloc; \
public : \


// IMPLEMENT_FIXED_ALLOC_NOSYNC -- used in class implementation file
#define IMPLEMENT_FIXED_ALLOC_NOSYNC(class_nbame, block_size) \
fixed_alloc_no_sync class_name::s_alloc(sizeof(class_name), block_size) \

#define new DEBUG_NEW

#else //!_DEBUG

#define DECLARE_FIXED_ALLOC(class_name) // nothing in debug
#define IMPLEMENT_FIXED_ALLOC(class_name, block_size) // nothing in debug
#define DECLARE_FIXED_ALLOC_NOSYNC(class_name) // nothing in debug
#define IMPLEMENT_FIXED_ALLOC_NOSYNC(class_name, block_size) // nothing in debug

#endif //!_DEBUG


*/
