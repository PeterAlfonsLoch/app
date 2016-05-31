//#include "framework.h"


namespace primitive
{


   virtual_memory::virtual_memory(::ace::application * papp) :
      object(papp)
   {
      m_pbStorage = NULL;
      m_pbComputed = NULL;
   }

   virtual_memory::virtual_memory(const void * pdata, memory_size_t iCount)
   {
      m_pbStorage = NULL;
      m_pbComputed = NULL;
      allocate(iCount);
      ASSERT(__is_valid_address(pdata, iCount, FALSE));
      memcpy(m_pbStorage, pdata, iCount);
   }

   virtual_memory::virtual_memory(const memory_base & s)
   {
      m_pbStorage = NULL;
      m_pbComputed = NULL;
      memory_base::operator = (s);
   }

   virtual_memory::virtual_memory(const char * psz)
   {
      from_string(psz);
   }

   virtual_memory::virtual_memory(primitive::memory_container * pcontainer, void * pmemory, memory_size_t dwSize) :
      object(pcontainer->get_app())
   {
      m_pbStorage          = NULL;
      m_pbComputed = NULL;
      allocate(dwSize);
      ASSERT(__is_valid_address(pmemory, (uint_ptr) dwSize, FALSE));
      memcpy(m_pbStorage, pmemory, (size_t) dwSize);
   }


   virtual_memory::virtual_memory(primitive::memory_container * pcontainer, double dAllocationRateUp, UINT nAllocFlags)
   {
      UNREFERENCED_PARAMETER(nAllocFlags);
      m_pbStorage          = NULL;
      m_pbComputed = NULL;
      m_pcontainer         = pcontainer;
      m_dAllocationRateUp  = dAllocationRateUp;
   }


   virtual_memory::~virtual_memory()
   {
      
      if(m_pbStorage != NULL)
      {
         
         try
         {
            
            impl_free(m_pbStorage);

         }
         catch(...)
         {

         }

      }

   }


   //LPBYTE virtual_memory::detach()
   //{

   //   LPBYTE p          = m_pbStorage;

   //   if(m_iOffset > 0)
   //   {
   //      virtual_memory mem(m_pbComputed, m_cbStorage);

   //      p = mem.detach();

   //   }
   //   else
   //   {

   //      p = m_pbStorage;

   //   }

   //   m_pbStorage       = NULL;

   //   m_cbStorage       = 0;

   //   m_dwAllocation    = 0;

   //   return p;

   //}


   LPBYTE virtual_memory::impl_alloc(memory_size_t dwAllocation)
   {

      return (LPBYTE) ::MidAlloc((size_t)dwAllocation);

   }


   LPBYTE virtual_memory::impl_realloc(void * pdata, memory_size_t dwAllocation)
   {

      return (LPBYTE) ::MidRealloc(pdata,m_dwAllocation,dwAllocation);

   }


   void virtual_memory::impl_free(LPBYTE pdata)
   {
      
      return ::MidFree(pdata);

   }



} // namespace primitive

















