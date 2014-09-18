#include "framework.h"


namespace primitive
{

   memory::memory(manager * pmanager)
   {

      UNREFERENCED_PARAMETER(pmanager);
      m_pprimitivememory   = this;
      m_pbStorage          = NULL;
      m_pbComputed         = NULL;
      m_pcontainer         = NULL;
      m_iOffset            = 0;
      m_dwAllocation       = 0;
      m_cbStorage          = 0;
      m_bAligned = false;

   }

   memory::memory(const memory & strSrc,manager * pmanager)
   {

      UNREFERENCED_PARAMETER(pmanager);

      m_pprimitivememory   = this;
      m_pbStorage    = NULL;
      m_pbComputed   = NULL;
      m_iOffset      = 0;
      m_dwAllocation = 0;
      m_cbStorage    = 0;
      m_bAligned = false;
      memory_base::operator = (s);

   }
   
   memory::memory(const byte * pchSrc,strsize nLength,manager * pmanager)
   {

      UNREFERENCED_PARAMETER(pmanager);

      m_pprimitivememory   = this;
      m_pbStorage    = NULL;
      m_pbComputed   = NULL;
      m_iOffset      = 0;
      m_bAligned = false;
      allocate(iCount);
      ASSERT(__is_valid_address(pdata,iCount,FALSE));
      memcpy(m_pbStorage,pdata,iCount);


   }


   memory::memory(sp(::aura::application) papp) :
      element(papp)
   {

      m_pprimitivememory   = this;
      m_pbStorage          = NULL;
      m_pbComputed         = NULL;
      m_pcontainer         = NULL;
      m_iOffset            = 0;
      m_dwAllocation       = 0;
      m_cbStorage          = 0;
      m_bAligned = false;

   }

   memory::memory(sp(::aura::application) papp, bool bAligned) :
      element(papp)
   {

      m_pprimitivememory = this;
      m_pbStorage = NULL;
      m_pbComputed = NULL;
      m_pcontainer = NULL;
      m_iOffset = 0;
      m_dwAllocation = 0;
      m_cbStorage = 0;
      m_bAligned = bAligned;

   }

   memory::memory(const void * pdata, memory_size iCount)
   {
      m_pprimitivememory   = this;
      m_pbStorage    = NULL;
      m_pbComputed   = NULL;
      m_iOffset      = 0;
      m_bAligned = false;
      allocate(iCount);
      ASSERT(__is_valid_address(pdata, iCount, FALSE));
      memcpy(m_pbStorage, pdata, iCount);
   }

   memory::memory(const memory_base & s)
   {
      m_pprimitivememory   = this;
      m_pbStorage    = NULL;
      m_pbComputed   = NULL;
      m_iOffset      = 0;
      m_dwAllocation = 0;
      m_cbStorage    = 0;
      m_bAligned = false;
      memory_base::operator = (s);
   }

   memory::memory(const memory & s)
   {
      m_pprimitivememory   = this;
      m_pbStorage    = NULL;
      m_pbComputed   = NULL;
      m_iOffset      = 0;
      m_dwAllocation = 0;
      m_cbStorage    = 0;
      m_bAligned = s.m_bAligned;
      memory_base::operator = (s);
   }

   memory::memory(const char * psz)
   {
      m_pprimitivememory   = this;
      m_pbStorage    = NULL;
      m_pbComputed   = NULL;
      m_iOffset      = 0;
      m_dwAllocation = 0;
      m_cbStorage    = 0;
      m_bAligned = false;
      from_string(psz);
   }

   memory::memory(primitive::memory_container * pcontainer, memory_size dwAllocationAddUp, UINT nAllocFlags)
   {
      UNREFERENCED_PARAMETER(nAllocFlags);
      m_pprimitivememory   = this;
      m_pbStorage          = NULL;
      m_pbComputed         = NULL;
      m_pcontainer         = pcontainer;
      m_dwAllocationAddUp  = dwAllocationAddUp;
      m_iOffset            = 0;
      m_dwAllocation       = 0;
      m_cbStorage          = 0;
      m_bAligned = false;
   }

   memory::memory(primitive::memory_container * pcontainer, void * pMemory, memory_size dwSize)
   {
      m_pprimitivememory   = this;
      m_pbStorage          = NULL;
      m_pbComputed         = NULL;
      m_pcontainer         = pcontainer;
      m_iOffset            = 0;
      m_dwAllocation       = 0;
      m_cbStorage          = 0;
      m_bAligned = false;

      allocate(dwSize);
      ASSERT(__is_valid_address(pMemory, (uint_ptr) dwSize, FALSE));
      memcpy(m_pbStorage, pMemory, (size_t) dwSize);
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
         if (m_bAligned)
         {
            m_pbStorage = (LPBYTE)aligned_memory_alloc((size_t)dwAllocation);
         }
         else
         {
            m_pbStorage = (LPBYTE)memory_alloc((size_t)dwAllocation);
         }
         
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
            LPVOID lpVoid = NULL;
            if (m_bAligned)
            {
               lpVoid = aligned_memory_alloc((size_t)dwAllocation);
            }
            else
            {
               lpVoid = memory_alloc((size_t)dwAllocation);
            }
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
               memory_free(m_pbStorage);
               m_pbStorage = (LPBYTE) lpVoid;
               m_pbComputed = m_pbStorage;
               return true;
            }
         }
         else if(dwNewLength > m_dwAllocation)
         {
            memory_size dwAllocation = dwNewLength + m_dwAllocationAddUp;
            LPVOID lpVoid = memory_realloc(m_pbStorage, (size_t) dwAllocation);
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
            memory_free(m_pbStorage);
         }
         catch(...)
         {
         }
         m_pbStorage       = NULL;
         m_pbComputed      = NULL;
         m_iOffset         = 0;
      }

   }


} // namespace primitive


