#include "framework.h"


namespace primitive
{


   memory_file::memory_file(::ca::application * papp, ::primitive::memory_size iSize) :
      ca(papp),
      memory_container (papp)
   {

      m_dwPosition   = 0;
      
      if(iSize > 0)
      {
         create(iSize);
      }

   }


   memory_file::memory_file(::ca::application * papp, void * pMemory, ::primitive::memory_size dwSize) :
      ca(papp),
      memory_container(papp, pMemory, dwSize)
   {

      m_dwPosition = 0;

   }


   memory_file::memory_file(::ca::application * papp, const memory_file & memoryfile) :
      ca(papp),
      memory_container (papp, memoryfile.get_memory())
   {

      m_dwPosition = 0;

   }


   memory_file::memory_file(::ca::application * papp, memory_base * pmemory) :
      ca(papp),
      memory_container (papp, pmemory)
   {

      m_dwPosition = 0;

   }


   memory_file::~memory_file()
   {

   }


   ::primitive::memory_size memory_file::read(void *lpBuf, ::primitive::memory_size nCount)
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


   void memory_file::write(const void * lpBuf, ::primitive::memory_size nCount)
   {

      single_lock sl(get_memory()->m_spmutex, TRUE);
      
      ::primitive::memory_size iEndPosition = m_dwPosition + nCount;

      if(iEndPosition > (int) this->get_size())
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


   void memory_file::Truncate(file_size size)
   {
      
      single_lock sl(get_memory()->m_spmutex, TRUE);

      allocate((::primitive::memory_size) size);

      if(m_dwPosition > (::primitive::memory_position) size)
         m_dwPosition = (::primitive::memory_position) size;


   }



   void memory_file::clear()
   {

      single_lock sl(get_memory()->m_spmutex, TRUE);
      
      m_dwPosition = 0;
      
      Truncate(0);

   }


   file_size memory_file::get_length() const
   {
      ASSERT(IsValid());
      return (file_size) this->get_size();
   }



   file_position memory_file::get_position() const
   {
      ASSERT(IsValid());
      return (file_position) m_dwPosition;
   }


   file_position memory_file::seek(file_offset lOff, ::ex1::e_seek nFrom)
   {

      single_lock sl(get_memory()->m_spmutex, TRUE);

      ASSERT(IsValid());
      ASSERT(nFrom == ::ex1::seek_begin || nFrom == ::ex1::seek_end || nFrom == ::ex1::seek_current);
      //ASSERT(::ex1::seek_begin == FILE_BEGIN && ::ex1::seek_end == FILE_END && ::ex1::seek_current == FILE_CURRENT);

      ::primitive::memory_position dwNew = (::primitive::memory_position) -1;

      switch(nFrom)
      {
      case ::ex1::seek_begin:
         dwNew = (::primitive::memory_position) lOff;
         break;
      case ::ex1::seek_end:
         dwNew = (::primitive::memory_position) (get_length() - lOff);
         break;
      case ::ex1::seek_current:
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


   void memory_file::create(::primitive::memory_size iSize)
   {

      allocate(iSize);

   }


   void memory_file::load_string(string &str)
   {
      LPTSTR lpsz = str.GetBuffer((int)(this->get_size() + 1));
      memcpy(lpsz, get_data(), (size_t) this->get_size());
      lpsz[this->get_size()] = 0;
      str.ReleaseBuffer();
   }


   memory_size memory_file::remove_begin(void *lpBuf, ::primitive::memory_size uiCount)
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


   bool memory_file::IsValid() const
   {
      return memory_container::IsValid() && !(m_dwPosition & 0x80000000);
   }


   string memory_file::GetFilePath() const
   {
      return L"";
   }


   uint64_t memory_file::GetBufferPtr(UINT nCommand, uint64_t nCount, void ** ppBufStart, void ** ppBufMax)
   {
      UNREFERENCED_PARAMETER(nCommand);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(ppBufStart);
      UNREFERENCED_PARAMETER(ppBufMax);
      return 0;
   }


   void memory_file::Flush()
   {
   }


   void memory_file::set_length(file_size dwNewLen)
   {
      Truncate(dwNewLen);
   }


   void memory_file::assert_valid() const
   {
      file::assert_valid();
   }

   void memory_file::dump(dump_context & dumpcontext) const
   {
      file::dump(dumpcontext);
   }





   void memory_file::full_load(const char * psz)
   {

      single_lock sl(get_memory()->m_spmutex, TRUE);
      
      ASSERT(IsValid());

      primitive::memory storage;
      storage.allocate(1024 * 1024 * 8);
      ex1::filesp spfile(get_app());
      if(!spfile->open(psz, ::ex1::file::type_binary | ::ex1::file::mode_read | ::ex1::file::shareDenyNone))
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

   ::primitive::memory_base * memory_file::create_memory()
   {
      
      return new primitive::memory(this);

   }


} // namespace primitive
