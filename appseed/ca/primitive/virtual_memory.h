#pragma once


namespace primitive
{


   class CLASS_DECL_ca virtual_memory :
      virtual public ::primitive::memory_base
   {
   public:


      LPBYTE                  m_pbStorage;


      virtual_memory(::ca::application * papp);
      virtual_memory(const void *, int iCount);
      virtual_memory(const memory_base & memory);
      virtual_memory(const char * psz);
      virtual_memory(primitive::memory_container * pcontainer = NULL, memory_size dwAllocationAddUp = 4096, UINT nAllocFlags = 0);
      virtual_memory(primitive::memory_container * pcontainer, void * pMemory, memory_size dwSize);
      virtual ~virtual_memory();


      void construct_memory(primitive::memory_container * pcontainer, memory_size dwAllocationAddUp = 4096, UINT nAllocFlags = 0);


      virtual LPBYTE internal_get_data() const;


      virtual bool allocate_internal(memory_size dwNewLength);

      LPBYTE detach();
      void free_data();


   };


} // namespace primitive


