#include "framework.h"


namespace file
{


   binary_buffer::binary_buffer()
   {
   }


   ::primitive::memory_size binary_buffer::read(void *lpBuf, ::primitive::memory_size nCount)
   {
      return ::file::reader::read(lpBuf, nCount);
   }

   void binary_buffer::write(const void * lpBuf, ::primitive::memory_size nCount)
   {
      ::file::writer::write(lpBuf, nCount);
   }


   void binary_buffer::write(output_stream & ostream)
   {
      
      seek_to_begin();

      transfer_to(*ostream.m_spbuffer);

   }


   void binary_buffer::read(input_stream & istream)
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

   bool binary_buffer::open(const char * lpszFileName, UINT nOpenFlags)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(nOpenFlags);
      return FALSE;
   }

   file_position binary_buffer::seek(file_offset lOff, ::file::e_seek nFrom)
   {
      UNREFERENCED_PARAMETER(lOff);
      UNREFERENCED_PARAMETER(nFrom);
      return 0;
   }

   file_position binary_buffer::get_position() const
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

   void binary_buffer::LockRange(file_position dwPos, file_size dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void binary_buffer::UnlockRange(file_position dwPos, file_size dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void binary_buffer::set_length(file_size dwNewLen)
   {
      UNREFERENCED_PARAMETER(dwNewLen);
   }

   file_size binary_buffer::get_length() const
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

   bool binary_buffer::GetStatus(const char * lpszFileName, file_status & rStatus)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(rStatus);
      return FALSE;
   }


   void binary_buffer::SetStatus(const char * lpszFileName, const file_status & status)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(status);
   }



   bool binary_buffer::IsOpened()
   {
      return false;
   }

   string binary_buffer::get_location() const
   {
      return GetFileName();
   }




} // namespace file



