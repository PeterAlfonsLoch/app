#pragma once


namespace primitive
{


   class CLASS_DECL_ca internal_virtual_memory :
      virtual public ::primitive::base_memory
   {
   public:


      LPBYTE                  m_pbStorage;


      internal_virtual_memory();
      virtual ~internal_virtual_memory();


      void construct_memory(primitive::memory_container * pcontainer, memory_size dwAllocationAddUp = 4096, UINT nAllocFlags = 0);


      inline LPBYTE internal_get_data() const
      {
         return m_pbStorage;
      }


      virtual bool allocate_internal(memory_size dwNewLength);

      LPBYTE detach();
      void free_data();


   };

   class CLASS_DECL_ca virtual_memory :
      virtual public memory_base < internal_virtual_memory >
   {
   public:


      virtual_memory(::ca::application * papp);
      virtual_memory(const void *, int iCount);
      virtual_memory(const base_memory & memory);
      virtual_memory(const char * psz);
      virtual_memory(primitive::memory_container * pcontainer = NULL, memory_size dwAllocationAddUp = 4096, UINT nAllocFlags = 0);
      virtual_memory(primitive::memory_container * pcontainer, void * pMemory, memory_size dwSize);
      virtual ~virtual_memory();



      

   };


} // namespace primitive


