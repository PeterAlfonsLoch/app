#include "framework.h"


namespace file
{


   memory_buffer::memory_buffer(sp(base_application) papp, ::primitive::memory_size iSize) :
      element(papp),
      memory_container (papp)
   {

      m_dwPosition   = 0;
      
      if(iSize > 0)
      {
         create(iSize);
      }

   }


   memory_buffer::memory_buffer(sp(base_application) papp, void * pMemory, ::primitive::memory_size dwSize) :
      element(papp),
      memory_container(papp, pMemory, dwSize)
   {

      m_dwPosition = 0;

   }


   memory_buffer::memory_buffer(sp(base_application) papp, const memory_buffer & memoryfile) :
      element(papp),
      memory_container (papp, ((memory_buffer &) memoryfile).get_memory())
   {

      m_dwPosition = 0;

   }


   memory_buffer::memory_buffer(sp(base_application) papp, ::primitive::memory_base * pmemory) :
      element(papp),
      memory_container (papp, pmemory)
   {

      m_dwPosition = 0;

   }


   memory_buffer::~memory_buffer()
   {

   }


   ::primitive::memory_size memory_buffer::read(void *lpBuf, ::primitive::memory_size nCount)
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


   void memory_buffer::write(const void * lpBuf, ::primitive::memory_size nCount)
   {

      single_lock sl(get_memory()->m_spmutex, TRUE);
      
      ::primitive::memory_size iEndPosition = m_dwPosition + nCount;

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

      m_dwPosition = (::primitive::memory_position) iEndPosition;
   }


   void memory_buffer::Truncate(file_size size)
   {
      
      single_lock sl(get_memory()->m_spmutex, TRUE);

      allocate((::primitive::memory_size) size);

      if(m_dwPosition > (::primitive::memory_position) size)
         m_dwPosition = (::primitive::memory_position) size;


   }



   void memory_buffer::clear()
   {

      single_lock sl(get_memory()->m_spmutex, TRUE);
      
      m_dwPosition = 0;
      
      Truncate(0);

   }


   file_size memory_buffer::get_length() const
   {
      ASSERT(IsValid());
      return (file_size) this->get_size();
   }



   file_position memory_buffer::get_position() const
   {
      if(!IsValid())
         throw io_exception(get_app());
      return (file_position) m_dwPosition;
   }


   file_position memory_buffer::seek(file_offset lOff, ::file::e_seek nFrom)
   {

      single_lock sl(get_memory()->m_spmutex, TRUE);

      ASSERT(IsValid());
      ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      //ASSERT(::file::seek_begin == FILE_BEGIN && ::file::seek_end == FILE_END && ::file::seek_current == FILE_CURRENT);

      ::primitive::memory_position dwNew = (::primitive::memory_position) -1;

      switch(nFrom)
      {
      case ::file::seek_begin:
         dwNew = (::primitive::memory_position) lOff;
         break;
      case ::file::seek_end:
         dwNew = (::primitive::memory_position) (get_length() - lOff);
         break;
      case ::file::seek_current:
         if(lOff < 0)
         {
            dwNew = (::primitive::memory_position) (m_dwPosition + lOff);
            if(dwNew > m_dwPosition)
               dwNew = 0;
         }
         else
         {
            dwNew = (::primitive::memory_position) (m_dwPosition + lOff);
         }

         break;
      default:
         return ::numeric_info::get_allset_value < ::primitive::memory_position > ();
      }

      m_dwPosition = dwNew;

      //if(dwNew > this->get_size())
         //allocate((primitive::memory_size) dwNew);

      return (file_position) dwNew;
   }


   void memory_buffer::create(::primitive::memory_size iSize)
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


   ::primitive::memory_size memory_buffer::remove_begin(void *lpBuf, ::primitive::memory_size uiCount)
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
      return memory_container::IsValid() && !(m_dwPosition & 0x80000000);
   }


   string memory_buffer::GetFilePath() const
   {
      return L"";
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


   void memory_buffer::set_length(file_size dwNewLen)
   {
      Truncate(dwNewLen);
   }


   void memory_buffer::assert_valid() const
   {
      buffer::assert_valid();
   }

   void memory_buffer::dump(dump_context & dumpcontext) const
   {
      buffer::dump(dumpcontext);
   }





   void memory_buffer::full_load(const char * psz)
   {

      single_lock sl(get_memory()->m_spmutex, TRUE);
      
      ASSERT(IsValid());

      primitive::memory storage;
      storage.allocate(1024 * 1024 * 8);
      ::file::binary_buffer_sp spfile(allocer());
      if(!spfile->open(psz, type_binary | mode_read | shareDenyNone))
         return;
      else
      {
         ::primitive::memory_size uiRead;
         while((uiRead = spfile->read(storage.get_data(), storage.get_size())) > 0)
         {
            write(storage.get_data(), uiRead);
         }
      }
   }

   ::primitive::memory_base * memory_buffer::create_memory()
   {
      
      return canew(primitive::memory(this));

   }


} // namespace file
