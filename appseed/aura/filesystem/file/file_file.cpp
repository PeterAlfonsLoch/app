//#include "framework.h"
//#include <stdarg.h>

thread_int_ptr < int > g_iGenerateSyncIoError;
thread_int_ptr < int > g_iSyncIoError;

CLASS_DECL_AURA int get_sync_io_error()
{
   return g_iSyncIoError;
}


CLASS_DECL_AURA void set_sync_io_error(int iError)
{
   g_iSyncIoError = iError;
}

CLASS_DECL_AURA int get_generate_sync_io_error()
{
   return g_iGenerateSyncIoError;
}


CLASS_DECL_AURA void set_generate_sync_io_error(int iError)
{
   g_iGenerateSyncIoError = iError;
}

namespace file
{


   file::file()
   {
   }



   file::~file()
   {
   }

   ::file::file_sp  file::Duplicate() const
   {
      return NULL;
   }

   
   cres file::open(const ::file::path & lpszFileName,UINT nOpenFlags)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(nOpenFlags);
      return failure;
   }

   
   file_position_t file::seek(file_offset_t lOff, ::file::e_seek nFrom)
   {
      UNREFERENCED_PARAMETER(lOff);
      UNREFERENCED_PARAMETER(nFrom);
      return 0;
   }


   file_position_t file::seek_from_begin(file_position_t lPos)
   {

      return seek(lPos, ::file::seek_begin);

   }

   
   file_position_t file::seek_to_begin(file_position_t lPos)
   {

      return seek_from_begin(lPos);

   }


   file_position_t file::seek_begin(file_position_t lPos)
   {

      return seek_to_begin(lPos);

   }


   file_position_t file::get_position() const
   {
      return ((file *) this)->seek(0, ::file::seek_current);
   }

   file_position_t file::tell() const
   {
      return get_position();
   }

   void file::flush()
   {
   }

   void file::close()
   {
   }

   memory_size_t file::read(void *lpBuf, memory_size_t nCount)
   {
      return ::file::reader::read(lpBuf, nCount);
   }


   bool file::full_read(void * lpBuf, memory_size_t nCount)
   {

      memory_size_t uiRead;
      memory_size_t uiPos = 0;
      byte * buf = (byte *) lpBuf;

      while(nCount > 0)
      {

         uiRead = read(&buf[uiPos], nCount);

         if(uiRead <= 0)
         {
   
            return false;

         }

         nCount   -= uiRead;
         uiPos    += uiRead;

      }

      return true;

   }


   void file::write_from_hex(const void * lpBuf,memory_size_t nCount)
   {

      memory memory(get_app());

      memory.from_hex((const char *) lpBuf, nCount);

      write(memory.get_data(),memory.get_size());

   }


   void file::write(const void * lpBuf, memory_size_t nCount)
   {
      ::file::writer::write(lpBuf, nCount);
   }


   void file::write(ostream & ostream)
   {

      seek_to_begin();

      transfer_to(*ostream.m_spfile);

   }


   void file::read(istream & istream)
   {

      transfer_from(*istream.m_spfile);

      seek_to_begin();

   }


   void file::Abort()
   {
   }

   void file::LockRange(file_position_t dwPos, file_size_t dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void file::UnlockRange(file_position_t dwPos, file_size_t dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void file::set_length(file_size_t dwNewLen)
   {
      UNREFERENCED_PARAMETER(dwNewLen);
   }

   file_size_t file::get_length() const
   {
      return 0;
   }

   // file does not support direct buffering (CMemFile does)
   uint64_t file::GetBufferPtr(UINT nCommand, uint64_t nCount, void ** ppBufStart, void ** ppBufMax)
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

   void file::assert_valid() const
   {
   //   object::assert_valid();
      // we permit the descriptor m_hFile to be any value for derived classes
   }

   void file::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
   //   object::dump(dumpcontext);

   //   dumpcontext << "with handle " << (UINT)m_hFile;
   //   dumpcontext << " and name \"" << m_wstrFileName << "\"";
   //   dumpcontext << "\n";
   }



   /////////////////////////////////////////////////////////////////////////////
   // file_exception helpers

/*   #ifdef DEBUG
   static const char * rgszFileExceptionCause[] =
   {
      "none",
      "generic",
      "fileNotFound",
      "badPath",
      "tooManyOpenFiles",
      "accessDenied",
      "invalidFile",
      "removeCurrentDir",
      "directoryFull",
      "badSeek",
      "hardIO",
      "sharingViolation",
      "lockViolation",
      "diskFull",
      "endOfFile",
   };
   static const char szUnknown[] = "unknown";
   #endif*/


   /*void throw_file_exception(int32_t cause, LONG lOsError,
   //   const char * lpszFileName /* == NULL */
   /*{
   #ifdef DEBUG
      const char * lpsz;
      if (cause >= 0 && cause < _countof(rgszFileExceptionCause))
         lpsz = rgszFileExceptionCause[cause];
      else
         lpsz = szUnknown;
      TRACE3("file exception: %hs, file %W, App error information = %ld.\n",
         lpsz, (lpszFileName == NULL) ? L"Unknown" : lpszFileName, lOsError);
   #endif
      THROW(new file_exception(cause, lOsError, lpszFileName));
   }*/

   /* Error Codes */

   #define EPERM           1
   #define ENOENT          2
   #define ESRCH           3
   #define EINTR           4
   #define EIO             5
   #define ENXIO           6
   #define E2BIG           7
   #define ENOEXEC         8
   #define EBADF           9
   #define ECHILD          10
#ifndef APPLEOS
   #define EAGAIN          11
#endif
   #define ENOMEM          12
   #define EACCES          13
   #define EFAULT          14
   #define EBUSY           16
   #define EEXIST          17
   #define EXDEV           18
   #define ENODEV          19
   #define ENOTDIR         20
   #define EISDIR          21
   #define EINVAL          22
   #define ENFILE          23
   #define EMFILE          24
   #define ENOTTY          25
   #define EFBIG           27
   #define ENOSPC          28
   #define ESPIPE          29
   #define EROFS           30
   #define EMLINK          31
   #define EPIPE           32
   #define EDOM            33
   #define ERANGE          34

#if defined(WINDOWS)

   #define EDEADLK         36
   #define ENAMETOOLONG    38
   #define ENOLCK          39
   #define ENOSYS          40
   #define ENOTEMPTY       41
   #define EILSEQ          42

#endif

   /*
    * Support EDEADLOCK for compatibiity with older MS-C versions.
    */
#ifndef EDEADLOCK
   #define EDEADLOCK       EDEADLK
#endif


   /////////////////////////////////////////////////////////////////////////////
   // file name handlers

   string file::GetFileName() const
   {
      return m_strFileName.name();
   }

   string file::GetFileTitle() const
   {
      return m_strFileName.title();
   }

   string file::GetFilePath() const
   {
      return m_strFileName;
   }






   // IMPLEMENT_DYNAMIC(file_exception, ::exception::base)

   /////////////////////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////////////////////
   // Help and other support

   // Strings in format ".....%1 .... %2 ...." etc.


   /////////////////////////////////////////////////////////////////////////////
   // file Status implementation

   bool file::GetStatus(file_status & rStatus) const
   {
      UNREFERENCED_PARAMETER(rStatus);
      return FALSE;
   }

   //bool file::GetStatus(const char * lpszFileName, file_status & rStatus)
   //{
   //   UNREFERENCED_PARAMETER(lpszFileName);
   //   UNREFERENCED_PARAMETER(rStatus);
   //   return FALSE;
   //}


   //void file::SetStatus(const char * lpszFileName, const file_status & status)
   //{
   //   UNREFERENCED_PARAMETER(lpszFileName);
   //   UNREFERENCED_PARAMETER(status);
   //}



   bool file::IsOpened()
   {
      return false;
   }


   bool file::is_open()
   {
      return IsOpened();
   }

   string file::get_location() const
   {
      return GetFileName();
   }


   bool file::read(char * pch)
   {
      if(read(pch, 1) == 1)
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   bool file::read(uchar * puch)
   {
      if(read(puch, 1) == 1)
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   bool file::peek(char * pch)
   {
      if(read(pch, 1) == 1)
      {
         seek(-1, ::file::seek_current);
         return true;
      }
      else
      {
         return false;
      }
   }

   bool file::peek(uchar * puch)
   {
      if(read(puch, 1) == 1)
      {
         seek(-1, ::file::seek_current);
         return true;
      }
      else
      {
         return false;
      }
   }

   bool file::read(char & ch)
   {
      return read(&ch);
   }

   bool file::read(uchar & uch)
   {
      return read(&uch);
   }

   bool file::peek(char & ch)
   {
      return peek(&ch);
   }


   bool file::peek(uchar & uch)
   {
      return peek(&uch);
   }


   int file::sgetc()
   {

      char ch;

      if(!peek(&ch))
         return EOF;

      return ch;

   }

   int file::sbumpc()
   {

      char ch;

      if(read(&ch, 1) <= 0)
         return EOF;

      return ch;

   }

   bool file::read_string(string & str)
   {

      str.Empty();

      int i = sbumpc();

      if(i == EOF)
         return false;

      while(i != EOF)
      {

         if((char) i == '\n' || (char) i == '\r')
            break;

         str += (char) i;

         i = sbumpc();
      };

      int iNew = sbumpc();

      if(iNew == i || ((char) iNew != '\n' && (char) iNew != '\r'))
      {
         seek(-1, seek_current);
      }

      return true;

   }

   bool file::full_read_string(string & str)
   {

      str.Empty();

      int i = sbumpc();

      if (i == EOF)
         return false;

      while (i != EOF)
      {

         str += (char)i;

         i = sbumpc();
      };

      return true;

   }

   void file::SetFilePath(const char * lpszNewName)
   {
      UNREFERENCED_PARAMETER(lpszNewName);
   }


   void file::write(const string & str)
   {

      write(str,  str.get_length());

   }


   void file::writef(const char *format, ...)
   {

      string strFormat;

      va_list list;

      va_start(list, format);

      strFormat.FormatV(format, list);

      va_end(list);

      write(strFormat);

   }

   void file::copy_this(const file & file)
   {

      m_strFileName = file.m_strFileName;

   }

   
   file & file::operator = (const file & file)
   {

      if (&file == this)
      {

         return *this;

      }

      object::copy_this(file);

      file::copy_this(file);

      return *this;

   }

} // namespace file



