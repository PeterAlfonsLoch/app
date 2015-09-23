//#include "framework.h"


namespace file
{


   memory_buffer::memory_buffer(::aura::application * papp, memory_size_t iSize) :
      object(papp),
      memory_container (papp)
   {

      m_dwPosition   = 0;
      
      if(iSize > 0)
      {
         create(iSize);
      }

   }


   memory_buffer::memory_buffer(::aura::application * papp, void * pMemory, memory_size_t dwSize) :
      object(papp),
      memory_container(papp, pMemory, dwSize)
   {

      m_dwPosition = 0;

   }


   memory_buffer::memory_buffer(::aura::application * papp, const memory_buffer & memoryfile) :
      object(papp),
      memory_container (papp, ((memory_buffer &) memoryfile).get_memory())
   {

      m_dwPosition = 0;

   }


   memory_buffer::memory_buffer(::aura::application * papp, ::primitive::memory_base * pmemory) :
      object(papp),
      memory_container (papp, pmemory)
   {

      m_dwPosition = 0;

   }


   memory_buffer::~memory_buffer()
   {

   }


   memory_size_t memory_buffer::read(void *lpBuf, memory_size_t nCount)
   {
      
      single_lock sl(get_memory()->m_spmutex, TRUE);
      
      ASSERT(IsValid());

      if(m_dwPosition >= this->get_size())
         return 0;

      if(m_dwPosition + nCount > this->get_size())
         nCount = this->get_size() - m_dwPosition;

      memcpy(lpBuf, &((LPBYTE)get_data())[m_dwPosition], (size_t) nCount);

      m_dwPosition += nCount;

      return nCount;
   }


   void memory_buffer::write(const void * lpBuf, memory_size_t nCount)
   {

      if(nCount <= 0)
         return;

      single_lock sl(get_memory()->m_spmutex, TRUE);


      
      memory_size_t iEndPosition = m_dwPosition + nCount;

      if(iEndPosition > (int32_t) this->get_size())
      {

         allocate(iEndPosition);

      }

      if(iEndPosition <= 0)
      {
         m_dwPosition = 0;
         return;
      }

      LPBYTE lpb = get_data();

      ASSERT(__is_valid_address(&(lpb)[m_dwPosition], (uint_ptr) nCount, TRUE));

      memcpy(&(lpb)[m_dwPosition], lpBuf, (size_t) nCount);

      m_dwPosition = (memory_position_t) iEndPosition;
   }

   void memory_buffer::write_from_hex(const void * lpBuf,memory_size_t nCount)
   {

      single_lock sl(get_memory()->m_spmutex,TRUE);

      char ch;

      strsize iLen = nCount;

      if((iLen % 2) != 0)
      {

         iLen++;

      }

      memory_size_t iEndPosition = m_dwPosition + iLen / 2;

      if(iEndPosition > (int32_t) this->get_size())
      {

         allocate(iEndPosition);

      }

      if(iEndPosition <= 0)
      {
         
         m_dwPosition = 0;

         return;

      }

      LPBYTE lpb = get_data();

      ASSERT(__is_valid_address(&(lpb)[m_dwPosition],(uint_ptr)nCount,TRUE));

      char * pch = (char *)&(lpb)[m_dwPosition];

      const char * psz = (const char *)lpBuf;

      bool bEven = true;

      while(nCount > 0)
      {

         if(bEven)
         {

            ch = 0;

            if(*psz > '9')
               ch |= ((*psz - 'A' + 10) & 0x0f) << 4;
            else
               ch |= ((*psz - '0') & 0x0f) << 4;

            if(*psz == '\0')
               break;

         }
         else
         {
            
            if(*psz > '9')
               ch |= ((*psz - 'A' + 10) & 0x0f);
            else
               ch |= ((*psz - '0') & 0x0f);

            *pch = ch;

            pch++;

         }

         psz++;

         nCount--;

         bEven = !bEven;

      }

      if(bEven)
      {
         *(pch-1) = ch;
      }

      m_dwPosition = (memory_position_t) iEndPosition;
   }

   void memory_buffer::Truncate(file_size_t size)
   {
      
      single_lock sl(get_memory()->m_spmutex, TRUE);

      allocate((memory_size_t) size);

      if(m_dwPosition > (memory_position_t) size)
         m_dwPosition = (memory_position_t) size;


   }



   void memory_buffer::clear()
   {

      single_lock sl(get_memory()->m_spmutex, TRUE);
      
      m_dwPosition = 0;
      
      Truncate(0);

   }


   file_size_t memory_buffer::get_length() const
   {
      ASSERT(IsValid());
      return (file_size_t) this->get_size();
   }



   file_position_t memory_buffer::get_position() const
   {
      if(!IsValid())
         throw io_exception(get_app(), "memory_buffer::get_position");
      return (file_position_t) m_dwPosition;
   }


   file_position_t memory_buffer::seek(file_offset_t lOff, ::file::e_seek nFrom)
   {

      single_lock sl(get_memory()->m_spmutex, TRUE);

      ASSERT(IsValid());
      ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      //ASSERT(::file::seek_begin == FILE_BEGIN && ::file::seek_end == FILE_END && ::file::seek_current == FILE_CURRENT);

      memory_position_t dwNew = (memory_position_t) -1;

      switch(nFrom)
      {
      case ::file::seek_begin:
         dwNew = (memory_position_t) lOff;
         break;
      case ::file::seek_end:
         dwNew = (memory_position_t) (get_length() - lOff);
         break;
      case ::file::seek_current:
         if(lOff < 0)
         {
            dwNew = (memory_position_t) (m_dwPosition + lOff);
            if(dwNew > m_dwPosition)
               dwNew = 0;
         }
         else
         {
            dwNew = (memory_position_t) (m_dwPosition + lOff);
         }

         break;
      default:
         return ::numeric_info< memory_position_t >::allset();
      }

      m_dwPosition = dwNew;

      //if(dwNew > this->get_size())
         //allocate((memory_size_t) dwNew);

      return (file_position_t) dwNew;
   }


   void memory_buffer::create(memory_size_t iSize)
   {

      allocate(iSize);

   }


   void memory_buffer::load_string(string &str)
   {
      char * lpsz = str.GetBuffer((int32_t)(this->get_size() + 1));
      memcpy(lpsz, get_data(), (size_t) this->get_size());
      lpsz[this->get_size()] = 0;
      str.ReleaseBuffer();
   }


   memory_size_t memory_buffer::remove_begin(void *lpBuf, memory_size_t uiCount)
   {

      single_lock sl(get_memory()->m_spmutex, TRUE);

      ASSERT(IsValid());

      if(uiCount > get_memory()->m_cbStorage)
      {

         uiCount = get_memory()->m_cbStorage;

      }

      if(lpBuf != NULL)
      {

         memcpy(lpBuf, get_data(), (size_t) uiCount);

      }

      if(m_dwPosition <= uiCount)
      {

         m_dwPosition = 0;

      }
      else
      {

         m_dwPosition -= uiCount;

      }

      get_memory()->delete_begin(uiCount);

      return uiCount;

   }


   bool memory_buffer::IsValid() const
   {
      return memory_container::IsValid();
   }


   string memory_buffer::GetFilePath() const
   {
      return "";
   }


   uint64_t memory_buffer::GetBufferPtr(UINT nCommand, uint64_t nCount, void ** ppBufStart, void ** ppBufMax)
   {
      UNREFERENCED_PARAMETER(nCommand);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(ppBufStart);
      UNREFERENCED_PARAMETER(ppBufMax);
      return 0;
   }


   void memory_buffer::flush()
   {
   }


   void memory_buffer::set_length(file_size_t dwNewLen)
   {
      Truncate(dwNewLen);
   }


   void memory_buffer::assert_valid() const
   {
      stream_buffer::assert_valid();
   }

   void memory_buffer::dump(dump_context & dumpcontext) const
   {
      stream_buffer::dump(dumpcontext);
   }





   void memory_buffer::full_load(const char * psz)
   {

      single_lock sl(get_memory()->m_spmutex, TRUE);
      
      ASSERT(IsValid());

      memory storage;
      
      storage.allocate(1024 * 1024 * 8);
      
      ::file::buffer_sp spfile(allocer());
      
      if(spfile->open(psz, type_binary | mode_read | share_deny_none).failed())
         return;

      else
      {

         memory_size_t uiRead;

         while((uiRead = spfile->read(storage.get_data(), storage.get_size())) > 0)
         {

            write(storage.get_data(), uiRead);

         }

      }

   }


   ::primitive::memory_base * memory_buffer::create_memory()
   {
      
      return canew(memory(this));

   }


   void * memory_buffer::get_internal_data()
   {

      return get_data();

   }


   memory_size_t memory_buffer::get_internal_data_size() const
   {

      return get_size();

   }


   bool memory_buffer::set_internal_data_size(memory_size_t c)
   {

      Truncate(c);

      return c == get_internal_data_size();

   }

   void memory_buffer::transfer_to(writer & writer, memory_size_t uiSize)
   {

      if(get_internal_data() == NULL || get_internal_data_size() <= 0)
         return;

      if(uiSize > get_internal_data_size())
         uiSize = get_internal_data_size();
      
      if(writer.increase_internal_data_size(uiSize) && writer.get_internal_data() != NULL)
      {
            
         if(writer.get_internal_data() == get_internal_data())
            return;

         memmove(((byte *) writer.get_internal_data()) + writer.get_position() + uiSize, ((byte *) writer.get_internal_data()) + writer.get_position(), writer.get_internal_data_size() - uiSize);
         memcpy(((byte *) writer.get_internal_data()) + writer.get_position(), get_internal_data(), uiSize);
         writer.seek(get_internal_data_size(), seek_current);

      }
      else
      {
            
         writer.write(get_internal_data(), uiSize);

      }

   }



} // namespace file





