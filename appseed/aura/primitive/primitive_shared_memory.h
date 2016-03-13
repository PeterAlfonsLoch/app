#pragma once


#if !defined(METROWIN)

namespace primitive
{


   class CLASS_DECL_AURA shared_memory :
      public ::primitive::memory_base
   {
   public:


      UINT                                   m_nAllocFlags;
   HGLOBAL                                m_hGlobalMemory;
      bool                                   m_bAllowGrow;


      shared_memory(const memory_base & memory);
      shared_memory(memory_container * pmsc = NULL, double dAllocationRateUp = 4096, UINT nAllocFlags = 0);
      shared_memory(memory_container * pmsc, void * pMemory, memory_size_t dwSize);
      shared_memory(const void *, memory_size_t iCount);
      virtual ~shared_memory();


      virtual void SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow = TRUE);
      
      virtual LPBYTE impl_alloc(memory_size_t nBytes) override;
      virtual LPBYTE impl_realloc(void * pdata, memory_size_t nBytes) override;
      virtual void impl_free(LPBYTE lpMem) override;


      LPBYTE detach_shared_memory(HGLOBAL & hglobal);
      //LPBYTE detach(HGLOBAL & hglobal);
//      virtual bool allocate_internal(memory_size_t dwNewLength);



      //virtual ::object * clone() override;

   };


} // namespace primitive


#endif


