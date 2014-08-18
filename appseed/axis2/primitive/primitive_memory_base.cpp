#include "framework.h"



namespace primitive
{


   memory_base::memory_base()
   {

      m_pbStorage          = NULL;
      m_pbComputed         = NULL;
      m_cbStorage          = 0;
      m_dwAllocation       = 0;
      m_dwAllocationAddUp  = 0;
      m_iOffset            = 0;
      m_bLockMode          = false;
      m_bLock              = false;
      m_pcontainer         = NULL;
      m_pprimitivememory   = NULL;
      m_psharedmemory      = NULL;
      m_pvirtualmemory     = NULL;

   }

   memory_base::~memory_base()
   {
   }

   memory_base & memory_base::prefix_der_length()
   {
      int32_t msb = ::msb(get_size());
      if(msb < 7)
      {
         move_and_grow(1);
         get_data()[0] = (BYTE) (get_size() - 1);
      }
      else
      {
         int32_t iLen = (msb + 8) / 8;
         move_and_grow(1 + iLen);
         get_data()[0] = 0x80 | iLen;
         auto s = get_size() - 1 - iLen;
         byte * p = (byte *) &s;
         for(int32_t i = 1; i <= iLen; i++)
         {
            get_data()[i] = p[iLen - i];
         }
      }
      return *this;
   }


   memory_base & memory_base::prefix_der_uint_content()
   {
      if(get_size() > 0)
      {
         if(get_data()[0] & 0x80)
         {
            move_and_grow(1);
            get_data()[0] = 0;
         }
      }
      return *this;
   }

   memory_base & memory_base::prefix_der_type(int32_t iType)
   {

      move_and_grow(1);

      get_data()[0] = iType;

      return *this;

   }

   memory_base & memory_base::prefix_der_uint()
   {
      return prefix_der_uint_content().prefix_der_length().prefix_der_type(2); // 2 - integer
   }

   memory_base & memory_base::prefix_der_sequence()
   {
      return prefix_der_length().prefix_der_type(0x30); // 0x30 - universal sequence
   }



   inline bool memory_base::allocate(memory_size dwNewLength)
   {

      if(!is_enabled())
      {
         ASSERT(FALSE);
         return false;
      }

      if((m_iOffset + dwNewLength) <= 0)
      {
         m_iOffset = 0;
         m_cbStorage = 0;
         return true;
      }

      if((m_iOffset + dwNewLength) > m_dwAllocation)
      {
         if(!allocate_internal(m_iOffset + dwNewLength))
            return false;
      }

      if((m_iOffset + dwNewLength) > m_dwAllocation)
         return false;

      m_cbStorage    = dwNewLength;

      m_pbComputed   = m_pbStorage + m_iOffset;

      return true;
   }

   bool memory_base::allocate_internal(memory_size dwNewLength)
   {
      return false;
   }


   void memory_base::delete_begin(memory_size iSize)
   {

      iSize = max(0, min(get_size(), iSize));

      m_iOffset += iSize;

      if(m_pcontainer != NULL)
      {

         m_pcontainer->offset_kept_pointers((::primitive::memory_offset) iSize);

      }

      m_cbStorage -= iSize;

      if(m_cbStorage <= 0)
      {

         m_pbComputed = NULL;

      }
      else
      {

         m_pbComputed += iSize;

      }

      if(m_iOffset > 2 * 1024 * 1024)
      {

         remove_offset();

      }

   }




} // namespace primitive


