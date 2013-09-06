#include "framework.h"


namespace primitive
{

   memory::memory(sp(base_application) papp) :
      element(papp)
   {

      m_pbStorage          = NULL;
      m_pbComputed         = NULL;
      m_pcontainer         = NULL;
      m_iOffset            = 0;
      m_dwAllocation       = 0;
      m_cbStorage          = 0;

   }

   memory::~memory()
   {
      free_data();
   }

   bool memory::allocate_internal(memory_size dwNewLength)
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
         m_pbStorage = (LPBYTE) ca2_alloc((size_t) dwAllocation);
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
            LPVOID lpVoid = ca2_alloc((size_t) dwAllocation);
            if(lpVoid == NULL)
            {
               return false;
            }
            else
            {
               memcpy(lpVoid, m_pbComputed, m_cbStorage);
               primitive::memory_size iOffset = (LPBYTE) lpVoid - m_pbStorage;
               if(m_pcontainer != NULL)
               {
                  m_pcontainer->offset_kept_pointers(iOffset);
               }

               m_dwAllocation = dwAllocation;
               ca2_free(m_pbStorage);
               m_pbStorage = (LPBYTE) lpVoid;
               m_pbComputed = m_pbStorage;
               return true;
            }
         }
         else if(dwNewLength > m_dwAllocation)
         {
            memory_size dwAllocation = dwNewLength + m_dwAllocationAddUp;
            LPVOID lpVoid = ca2_realloc(m_pbStorage, (size_t) dwAllocation);
            if(lpVoid == NULL)
            {
               return false;
            }
            else
            {
               primitive::memory_size iOffset = (LPBYTE) lpVoid - m_pbStorage;
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

   LPBYTE memory::detach()
   {

      LPBYTE pbStorage = m_pbStorage;

      if(m_iOffset > 0)
      {

         primitive::memory mem(m_pbComputed, m_cbStorage);

         free_data();

         return mem.detach();

      }

      m_pbStorage       = NULL;

      m_pbComputed      = NULL;

      m_cbStorage       = 0;

      m_dwAllocation    = 0;

      m_iOffset         = 0;

      return pbStorage;

   }

   void memory::free_data()
   {

      if(m_pbStorage != NULL)
      {
         m_dwAllocation    = 0;
         m_cbStorage       = 0;
         try
         {
            ca2_free(m_pbStorage);
         }
         catch(...)
         {
         }
         m_pbStorage       = NULL;
         m_pbComputed      = NULL;
         m_iOffset         = 0;
      }

   }

   memory::memory(const void * pdata, memory_size iCount)
   {
      m_pbStorage    = NULL;
      m_pbComputed   = NULL;
      m_iOffset      = 0;
      allocate(iCount);
      ASSERT(__is_valid_address(pdata, iCount, FALSE));
      memcpy(m_pbStorage, pdata, iCount);
   }

   memory::memory(const memory_base & s)
   {
      m_pbStorage    = NULL;
      m_pbComputed   = NULL;
      m_iOffset      = 0;
      m_dwAllocation = 0;
      m_cbStorage    = 0;
      memory_base::operator = (s);
   }

   memory::memory(const memory & s)
   {
      m_pbStorage    = NULL;
      m_pbComputed   = NULL;
      m_iOffset      = 0;
      m_dwAllocation = 0;
      m_cbStorage    = 0;
      memory_base::operator = (s);
   }

   memory::memory(const char * psz)
   {
      m_pbStorage    = NULL;
      m_pbComputed   = NULL;
      m_iOffset      = 0;
      m_dwAllocation = 0;
      m_cbStorage    = 0;
      from_string(psz);
   }

   memory::memory(primitive::memory_container * pcontainer, memory_size dwAllocationAddUp, UINT nAllocFlags)
   {
      UNREFERENCED_PARAMETER(nAllocFlags);
      m_pbStorage          = NULL;
      m_pbComputed         = NULL;
      m_pcontainer         = pcontainer;
      m_dwAllocationAddUp  = dwAllocationAddUp;
      m_iOffset            = 0;
      m_dwAllocation       = 0;
      m_cbStorage          = 0;
   }

   memory::memory(primitive::memory_container * pcontainer, void * pMemory, memory_size dwSize)
   {
      m_pbStorage          = NULL;
      m_pbComputed         = NULL;
      m_pcontainer         = pcontainer;
      m_iOffset            = 0;
      m_dwAllocation       = 0;
      m_cbStorage          = 0;

      allocate(dwSize);
      ASSERT(__is_valid_address(pMemory, (uint_ptr) dwSize, FALSE));
      memcpy(m_pbStorage, pMemory, (size_t) dwSize);
   }


} // namespace primitive


