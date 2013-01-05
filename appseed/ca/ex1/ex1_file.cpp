#include "framework.h"

namespace ex1
{

   __STATIC inline bool IsDirSep(WCHAR ch)
   {
      return (ch == '\\' || ch == '/');
   }


   file::file()
   {
   }


   ::primitive::memory_size file::read(void *lpBuf, ::primitive::memory_size nCount)
   {
      return ::ex1::reader::read(lpBuf, nCount);
   }

   void file::write(const void * lpBuf, ::primitive::memory_size nCount)
   {
      ::ex1::writer::write(lpBuf, nCount);
   }


   void file::write(byte_output_stream & ostream)
   {
      seek_to_begin();
      ex1::reader::write(ostream);
   }

   void file::read(byte_input_stream & istream)
   {
      ex1::writer::read(istream);
      seek_to_begin();
   }

   file::~file()
   {
   }

   file* file::Duplicate() const
   {
      return NULL;
   }

   bool file::open(const char * lpszFileName, UINT nOpenFlags)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(nOpenFlags);
      return FALSE;
   }

   file_position file::seek(file_offset lOff, ::ex1::e_seek nFrom)
   {
      UNREFERENCED_PARAMETER(lOff);
      UNREFERENCED_PARAMETER(nFrom);
      return 0;
   }

   file_position file::get_position() const
   {
      return 0;
   }

   void file::Flush()
   {
   }

   void file::close()
   {
   }

   void file::Abort()
   {
   }

   void file::LockRange(file_position dwPos, file_size dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void file::UnlockRange(file_position dwPos, file_size dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void file::set_length(file_size dwNewLen)
   {
      UNREFERENCED_PARAMETER(dwNewLen);
   }

   file_size file::get_length() const
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

/*   void PASCAL file::Rename(const char * lpszOldName, const char * lpszNewName)
   {
      UNREFERENCED_PARAMETER(lpszOldName);
      UNREFERENCED_PARAMETER(lpszNewName);
   }

   void PASCAL file::remove(const char * lpszFileName)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
   }*/

   void file::assert_valid() const
   {
   //   ::radix::object::assert_valid();
      // we permit the descriptor m_hFile to be any value for derived classes
   }

   void file::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
   //   ::radix::object::dump(dumpcontext);

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


   /*void vfxThrowFileException(int32_t cause, LONG lOsError,
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
#ifndef MACOS
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
   #define EDEADLOCK       EDEADLK


   /////////////////////////////////////////////////////////////////////////////
   // file name handlers

   string file::GetFileName() const
   {
      return "";
   }

   string file::GetFileTitle() const
   {
      return "";
   }

   string file::GetFilePath() const
   {
      return "";
   }






   // IMPLEMENT_DYNAMIC(file_exception, base_exception)

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

   bool PASCAL file::GetStatus(const char * lpszFileName, file_status & rStatus)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(rStatus);
      return FALSE;
   }


   void PASCAL file::SetStatus(const char * lpszFileName, const file_status & status)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(status);
   }



   bool file::IsOpened()
   {
      return false;
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
         seek(-1, ::ex1::seek_current);
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
         seek(-1, ::ex1::seek_current);
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

} // namespace ex1
