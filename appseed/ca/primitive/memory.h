#pragma once


#include "memory_base.h"


namespace primitive
{


   class memory_container;


   class CLASS_DECL_ca internal_memory :
      virtual public base_memory
   {
   public:


      


      internal_memory();
      virtual ~internal_memory();


      LPBYTE detach();


      virtual bool allocate_internal(memory_size dwNewLength);
      void free_data();


   };


   class CLASS_DECL_ca memory :
      virtual public memory_base < internal_memory >
   {
   public:


      memory(::ca::application * papp);
      memory(const void *, memory_size iCount);
      memory(const base_memory & memorybase);
      memory(const memory & memory);
      memory(const char * psz);
      memory(primitive::memory_container * pmsc = NULL, memory_size dwAllocationAddUp = 4096, UINT nAllocFlags = 0);
      memory(primitive::memory_container * pmsc, void * pMemory, memory_size dwSize);
      virtual ~memory();


   };


} // namespace primitive


#include "virtual_memory.h"
#include "shared_memory.h"
#include "memory_container.h"
#include "memory_file.h"
#include "shared_file.h"
