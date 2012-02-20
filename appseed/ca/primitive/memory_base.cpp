#include "StdAfx.h"

namespace primitive
{

   base_memory::base_memory()
   {

      m_iOffset            = 0;
      m_bLockMode          = false;
      m_bLock              = false;
      m_pcontainer         = NULL;
      m_cbStorage          = 0;
      m_dwAllocation       = 0;
      m_dwAllocationAddUp  = 0;

   }
      
   base_memory::~base_memory()
   {
   }



   inline bool base_memory::allocate(memory_size dwNewLength)
   {

      if(!is_enabled())
      {
         ASSERT(FALSE);
         return false;
      }

      if(dwNewLength <= 0)
      {
         m_iOffset = 0;
         m_cbStorage = 0;
         return true;
      }

      if(dwNewLength > m_dwAllocation)
      {
         if(!allocate_internal(dwNewLength))
            return false;
      }

      if(dwNewLength > m_dwAllocation)
         return false;

      m_cbStorage = dwNewLength;
      return true;
   }

   bool base_memory::allocate_internal(memory_size dwNewLength)
   {
      return false;
   }

   
   void base_memory::FullLoad(ex1::file & file)
   {

      if(!is_enabled())
      {
         ASSERT(false);
         return;
      }

      uint64_t dwTemp;
      memory_size cbStorage = (memory_size) file.get_length();
      file.seek_to_begin();
      allocate(cbStorage);
      try
      {
         dwTemp = file.read(base_get_data(), cbStorage);
      }
      catch(ex1::file_exception_sp * pe)
      {
         throw "smfOpenFile: read error on image!";
   #ifdef _DEBUG
         (*pe)->dump(afxdump);
   #endif
         delete pe;
      }
      if (cbStorage != dwTemp)
      {
         throw "smfOpenFile: read error on image!";
      }

   }
 

   void base_memory::read(ex1::byte_input_stream & istream)
   {

      memory_size uiRead;

      memory_size uiBufSize = 1024 + 1024;

      memory_size uiSize = 0;

      while(true)
      {

         allocate(uiSize + uiBufSize);

         uiRead = istream.read(&((byte *)base_get_data())[uiSize], uiBufSize);

         if(uiRead < uiBufSize)
         {
            allocate(uiSize + uiRead);

            break;

         }

         uiSize += uiBufSize;

      }

   }

   
   void base_memory::write(ex1::byte_output_stream & ostream)
   {

      ostream.write(base_get_data(), this->base_get_size());

   }

   
   ::primitive::memory_size base_memory::read(ex1::file & file)
   {

      file_size dwEnd = file.get_length();

      file_position dwPos = file.get_position();

      memory_size dwRemain = (memory_size)(dwEnd - dwPos);

      allocate((memory_size) dwRemain);

      memory_size dwRead = file.read(base_get_data(), dwRemain);

      allocate(dwRead);

      return dwRead;

   }

   void base_memory::base_remove_offset()
   {

      throw not_implemented_exception();

   }

   void base_memory::base_copy_from(const base_memory *pstorage)
   {
      ASSERT(pstorage != NULL);
      allocate(pstorage->base_get_size());
      memcpy(base_get_data(), pstorage->base_get_data(), (size_t) base_get_size());
   }


} // namespace primitive
