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

   }
      
   memory_base::~memory_base()
   {
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

   
   void memory_base::FullLoad(ex1::file & file)
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
         dwTemp = file.read(get_data(), cbStorage);
      }
      catch(ex1::file_exception & e)
      {
         throw "smfOpenFile: read error on image!";
   #ifdef DEBUG
         e.dump(g_dumpcontext);
   #endif
      }
      if (cbStorage != dwTemp)
      {
         throw "smfOpenFile: read error on image!";
      }

   }
 

   void memory_base::read(ex1::byte_input_stream & istream)
   {

      memory_size uiRead;

      memory_size uiBufSize = 1024 + 1024;

      memory_size uiSize = 0;

      while(true)
      {

         allocate(uiSize + uiBufSize);

         uiRead = istream.read(&((byte *)get_data())[uiSize], uiBufSize);

         if(uiRead < uiBufSize)
         {
            allocate(uiSize + uiRead);

            break;

         }

         uiSize += uiBufSize;

      }

   }

   
   void memory_base::write(ex1::byte_output_stream & ostream)
   {

      ostream.write(get_data(), this->get_size());

   }

   
   ::primitive::memory_size memory_base::read(ex1::file & file)
   {

      file_size dwEnd = file.get_length();

      file_position dwPos = file.get_position();

      memory_size dwRemain = (memory_size)(dwEnd - dwPos);

      allocate((memory_size) dwRemain);

      memory_size dwRead = file.read(get_data(), dwRemain);

      allocate(dwRead);

      return dwRead;

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


