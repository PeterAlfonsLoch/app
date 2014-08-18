#pragma once

namespace primitive
{


   class CLASS_DECL_AXIS virtual_memory :
      public ::primitive::memory_base
   {
   public:


      virtual_memory(sp(::axis::application) papp);
      virtual_memory(const void *, memory_size iCount);
      virtual_memory(const memory_base & memory);
      virtual_memory(const char * psz);
      virtual_memory(primitive::memory_container * pcontainer = NULL, memory_size dwAllocationAddUp = 4096, UINT nAllocFlags = 0);
      virtual_memory(primitive::memory_container * pcontainer, void * pMemory, memory_size dwSize);
      virtual ~virtual_memory();


      void construct_memory(primitive::memory_container * pcontainer, memory_size dwAllocationAddUp = 4096, UINT nAllocFlags = 0);


      virtual bool allocate_internal(memory_size dwNewLength);

      LPBYTE detach();
      void free_data();


   };


} // namespace primitive

