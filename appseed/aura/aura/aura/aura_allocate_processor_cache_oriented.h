#pragma once


CLASS_DECL_AURA void * processor_cache_oriented_memory_alloc(size_t s);
CLASS_DECL_AURA void processor_cache_oriented_memory_free(void * p);
CLASS_DECL_AURA void processor_cache_oriented_memory_reset();
CLASS_DECL_AURA int_bool processor_cache_oriented_set_thread_memory_pool(int iPoolIndex);
CLASS_DECL_AURA void processor_cache_oriented_destroy_all_memory_pools();

#define MAX_PROC_CACHE_ORIENTED_MEM_POOL 32


#if defined(__cplusplus)

class CLASS_DECL_AURA processor_cache_oriented_memory_allocator
{
public:

   inline static void * alloc(int iSize)
   {

      //TODO("jai"); jas = Jonathan Blow 
      return processor_cache_oriented_memory_alloc(iSize);

   }

   inline static void free(void * p)
   {

      //TODO("jai"); jas = Jonathan Blow
      processor_cache_oriented_memory_free(p);

   }

   inline static void reset()
   {

      //TODO("jai"); jas = Jonathan Blow
      processor_cache_oriented_memory_reset();

   }

};


#endif







