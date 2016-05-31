#pragma once

namespace primitive
{


   class CLASS_DECL_AURA virtual_memory :
      public ::primitive::memory_base
   {
   public:


      virtual_memory(::ace::application * papp);
      virtual_memory(const void *, memory_size_t iCount);
      virtual_memory(const memory_base & memory);
      virtual_memory(const char * psz);
      virtual_memory(primitive::memory_container * pcontainer = NULL, double dAllocationRateUp = 4096, UINT nAllocFlags = 0);
      virtual_memory(primitive::memory_container * pcontainer, void * pMemory, memory_size_t dwSize);
      virtual ~virtual_memory();


      void construct_memory(primitive::memory_container * pcontainer, memory_size_t dwAllocationAddUp = 4096, UINT nAllocFlags = 0);


      virtual LPBYTE impl_alloc(memory_size_t dwAllocation) override;
      virtual LPBYTE impl_realloc(void * pdata, memory_size_t dwAllocation) override;
      virtual void impl_free(LPBYTE pdata) override;

      //virtual ::object * clone() override;


   };


} // namespace primitive

