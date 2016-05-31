//#include "framework.h"


namespace file
{


   binary_buffer::binary_buffer()
   {
   }


   memory_size_t binary_buffer::read(void *lpBuf, memory_size_t nCount)
   {
      return ::file::reader::read(lpBuf, nCount);
   }

   void binary_buffer::write(const void * lpBuf, memory_size_t nCount)
   {
      ::file::writer::write(lpBuf, nCount);
   }


   void binary_buffer::write(ostream & ostream)
   {
      
      seek_to_begin();

      transfer_to(*ostream.m_spbuffer);

   }


   void binary_buffer::read(istream & istream)
   {
   
      transfer_from(*istream.m_spbuffer);

      seek_to_begin();

   }


   binary_buffer::~binary_buffer()
   {
   }

   ::file::buffer_sp  binary_buffer::Duplicate() const
   {
      return NULL;
   }

   cres binary_buffer::open(const ::file::path & lpszFileName, UINT nOpenFlags)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(nOpenFlags);
      return canew(::file::exception(get_app()));
   }

   file_position_t binary_buffer::seek(file_offset_t lOff, ::file::e_seek nFrom)
   {
      UNREFERENCED_PARAMETER(lOff);
      UNREFERENCED_PARAMETER(nFrom);
      return 0;
   }

   file_position_t binary_buffer::get_position() const
   {
      return ((binary_buffer *) this)->seek(0, ::file::seek_current);
   }

   void binary_buffer::flush()
   {
   }

   void binary_buffer::close()
   {
   }

   void binary_buffer::Abort()
   {
   }

   void binary_buffer::LockRange(file_position_t dwPos, file_size_t dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void binary_buffer::UnlockRange(file_position_t dwPos, file_size_t dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void binary_buffer::set_length(file_size_t dwNewLen)
   {
      UNREFERENCED_PARAMETER(dwNewLen);
   }

   file_size_t binary_buffer::get_length() const
   {
      return 0;
   }

   // file does not support direct buffering (CMemFile does)
   uint64_t binary_buffer::GetBufferPtr(UINT nCommand, uint64_t nCount, void ** ppBufStart, void ** ppBufMax)
   {
      UNREFERENCED_PARAMETER(nCommand);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(ppBufStart);
      UNREFERENCED_PARAMETER(ppBufMax);
      return 0;
   }

/*   void file::Rename(const char * lpszOldName, const char * lpszNewName)
   {
      UNREFERENCED_PARAMETER(lpszOldName);
      UNREFERENCED_PARAMETER(lpszNewName);
   }

   void file::remove(const char * lpszFileName)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
   }*/

   void binary_buffer::assert_valid() const
   {
   //   object::assert_valid();
      // we permit the descriptor m_hFile to be any value for derived classes
   }

   void binary_buffer::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
   //   object::dump(dumpcontext);

   //   dumpcontext << "with handle " << (UINT)m_hFile;
   //   dumpcontext << " and name \"" << m_wstrFileName << "\"";
   //   dumpcontext << "\n";
   }





   /////////////////////////////////////////////////////////////////////////////
   // file name handlers

   string binary_buffer::GetFileName() const
   {
      return "";
   }

   string binary_buffer::GetFileTitle() const
   {
      return "";
   }

   string binary_buffer::GetFilePath() const
   {
      return "";
   }






   // IMPLEMENT_DYNAMIC(file_exception, ::exception::base)

   /////////////////////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////////////////////
   // Help and other support

   // Strings in format ".....%1 .... %2 ...." etc.


   /////////////////////////////////////////////////////////////////////////////
   // file Status implementation

   bool binary_buffer::GetStatus(file_status & rStatus) const
   {
      UNREFERENCED_PARAMETER(rStatus);
      return FALSE;
   }

   //bool binary_buffer::GetStatus(const char * lpszFileName, file_status & rStatus)
   //{
   //   UNREFERENCED_PARAMETER(lpszFileName);
   //   UNREFERENCED_PARAMETER(rStatus);
   //   return FALSE;
   //}


   //void binary_buffer::SetStatus(const char * lpszFileName, const file_status & status)
   //{
   //   UNREFERENCED_PARAMETER(lpszFileName);
   //   UNREFERENCED_PARAMETER(status);
   //}



   bool binary_buffer::IsOpened()
   {
      return false;
   }

   string binary_buffer::get_location() const
   {
      return GetFileName();
   }




} // namespace file



