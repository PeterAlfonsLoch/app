#pragma once


#define ZEROED_ALLOC 1



BEGIN_EXTERN_C


   CLASS_DECL_AURA void * unaligned_memory_alloc(size_t size);
   CLASS_DECL_AURA void * unaligned_memory_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);

   CLASS_DECL_AURA void * aligned_memory_alloc(size_t size);
   CLASS_DECL_AURA void * aligned_memory_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);

   CLASS_DECL_AURA void * memory_alloc(size_t size);
   CLASS_DECL_AURA void * memory_calloc(size_t size, size_t bytes);
   CLASS_DECL_AURA void * memory_alloc_dbg(size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
   CLASS_DECL_AURA void * memory_realloc(void * pvoid, size_t nSize);
   CLASS_DECL_AURA void * memory_realloc_dbg(void * pvoid, size_t nSize, int32_t nBlockUse, const char * szFileName, int32_t nLine);
   CLASS_DECL_AURA void   memory_free(void * pvoid);
   CLASS_DECL_AURA void   memory_free_dbg(void * pvoid, int32_t iBlockType);
   CLASS_DECL_AURA size_t memory_size(void * p);
   CLASS_DECL_AURA size_t memory_size_dbg(void * p, int32_t iBlockType);



END_EXTERN_C




CLASS_DECL_AURA void * system_heap_alloc(size_t size);
CLASS_DECL_AURA void * system_heap_realloc(void * pvoidOld, size_t size);
CLASS_DECL_AURA void   system_heap_free(void * pvoid);







#if defined(__cplusplus)

namespace heap
{

   class CLASS_DECL_AURA default_memory_allocator
   {
   public:


      inline static void * alloc(size_t iSize)
      {

         //TODO("jai"); jas = Jonathan Blow 
         return memory_alloc(iSize);

      }


      inline static void free(void * p)
      {

         //TODO("jai"); jas = Jonathan Blow
         memory_free(p);

      }


   };


   class CLASS_DECL_AURA heap_base
   {
   public:


      void *         m_p;
      uint_ptr       m_uiSize;


      heap_base()
      {

         m_p         = NULL;
         m_uiSize    = 0;

      }

      heap_base(uint_ptr uiSize)
      {

         m_p         = NULL;
         m_uiSize    = 0;

         size(uiSize);

      }

      virtual ~heap_base()
      {

         free();

      }

      uint_ptr size()
      {

         return m_uiSize;

      }

      virtual uint_ptr size(uint_ptr uiSize)
      {

         if(m_p == NULL)
         {

            m_p = memory_alloc(uiSize);

         }
         else
         {

            m_p = memory_realloc(m_p,uiSize);

         }

         if(m_p != NULL)
         {

            m_uiSize = uiSize;

         }

         return m_uiSize;

      }


      void free()
      {

         if(m_p != NULL)
         {

            memory_free(m_p);

            m_p = NULL;

         }

      }


   };


   template < typename T >
   class heap:
      public heap_base
   {
   public:


      heap() {   }

      heap(uint_ptr iCount): heap_base(iCount * sizeof(T)) {   }

      operator T * () { return (T *)m_p; }
      operator const T * () const { return (T *)m_p; }

      uint_ptr count() { return size() / sizeof(T); }

   };

} // namespace heap



typedef ::heap::heap < char > hstring_base;

class CLASS_DECL_AURA hstring:
   public hstring_base
{
public:

   hstring() {}
   hstring(uint_ptr uiSize): hstring_base(uiSize) {}

};


typedef ::heap::heap < unichar > hwstring_base;

class CLASS_DECL_AURA hwstring:
   public hwstring_base
{
public:

   hwstring() {}
   hwstring(uint_ptr uiSize): hwstring_base(uiSize) {}

};


#endif



