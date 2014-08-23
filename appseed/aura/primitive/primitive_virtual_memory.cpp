#include "framework.h"


namespace primitive
{


   virtual_memory::virtual_memory(sp(::aura::application) papp) :
      element(papp)
   {
      m_pbStorage = NULL;
      m_pbComputed = NULL;
   }

   virtual_memory::virtual_memory(const void * pdata, memory_size iCount)
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

   virtual_memory::virtual_memory(primitive::memory_container * pcontainer, void * pmemory, memory_size dwSize) :
      element(pcontainer->get_app())
   {
      m_pbStorage          = NULL;
      m_pbComputed = NULL;
      allocate(dwSize);
      ASSERT(__is_valid_address(pmemory, (uint_ptr) dwSize, FALSE));
      memcpy(m_pbStorage, pmemory, (size_t) dwSize);
   }


   virtual_memory::virtual_memory(primitive::memory_container * pcontainer, memory_size dwAllocationAddUp, UINT nAllocFlags)
   {
      UNREFERENCED_PARAMETER(nAllocFlags);
      m_pbStorage          = NULL;
      m_pbComputed = NULL;
      m_pcontainer         = pcontainer;
      m_dwAllocationAddUp  = dwAllocationAddUp;
   }


   virtual_memory::~virtual_memory()
   {
      free_data();
   }

   LPBYTE virtual_memory::detach()
   {

      if(m_iOffset > 0)
      {
         virtual_memory mem(m_pbComputed, m_cbStorage);

         free_data();

         return mem.detach();
      }

      LPBYTE p          = m_pbStorage;

      m_pbStorage       = NULL;
      m_cbStorage       = 0;
      m_dwAllocation    = 0;

      return p;

   }


   bool virtual_memory::allocate_internal(memory_size dwNewLength)
   {
      if(!is_enabled())
      {
         ASSERT(FALSE);
         return false;
      }

      if(dwNewLength <= 0)
      {
         return true;
      }

      remove_offset();

      if(m_pbStorage == NULL)
      {
         m_iOffset = 0;
         memory_size dwAllocation = dwNewLength + m_dwAllocationAddUp;
         m_pbStorage = (LPBYTE) ::MidAlloc((size_t) dwAllocation);
         if(m_pbStorage == NULL)
         {
            m_pbComputed = NULL;
            return false;
         }
         else
         {
            m_dwAllocation = dwAllocation;
            if(m_pcontainer != NULL)
            {
               m_pcontainer->offset_kept_pointers((int_ptr) m_pbStorage);
            }
            m_pbComputed = m_pbStorage;
            return true;
         }
      }
      else
      {
         if(m_iOffset > 0)
         {
            m_iOffset = 0;
            memory_size dwAllocation = dwNewLength + m_dwAllocationAddUp;
            LPVOID lpVoid = ::MidAlloc(dwAllocation);
            if(lpVoid == NULL)
            {
               return false;
            }
            else
            {
               memcpy(lpVoid, m_pbComputed, m_cbStorage);
               memory_size iOffset = (LPBYTE) lpVoid - m_pbStorage;
               if(m_pcontainer != NULL)
               {
                  m_pcontainer->offset_kept_pointers(iOffset);
               }

               m_dwAllocation = dwAllocation;
               MidFree(m_pbStorage);
               m_pbStorage = (LPBYTE) lpVoid;
               m_pbComputed = m_pbStorage;
               return true;
            }
         }
         else if(dwNewLength > m_dwAllocation)
         {
            memory_size dwAllocation = dwNewLength + m_dwAllocationAddUp;
            LPVOID lpVoid = ::MidRealloc(m_pbStorage, m_dwAllocation, (size_t) dwAllocation);
            if(lpVoid == NULL)
            {
               return false;
            }
            else
            {
               memory_size iOffset = (LPBYTE) lpVoid - m_pbStorage;
               if(m_pcontainer != NULL)
               {
                  m_pcontainer->offset_kept_pointers(iOffset);
               }

               m_dwAllocation = dwAllocation;
               m_pbStorage = (LPBYTE) lpVoid;
               m_pbComputed = m_pbStorage;
               return true;
            }
         }
         else
         {
            return true;
         }

      }
   }


   void virtual_memory::free_data()
   {
      if(m_pbStorage != NULL)
      {
         m_cbStorage = 0;
         m_dwAllocation =  0;
         try
         {
            ::MidFree(m_pbStorage);
         }
         catch(...)
         {
         }
         m_pbStorage = NULL;
      }
   }






















} // namespace primitive



