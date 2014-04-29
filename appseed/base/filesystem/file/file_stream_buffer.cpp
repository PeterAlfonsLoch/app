#include "framework.h"


namespace file
{


   stream_buffer::stream_buffer()
   {
   }



   stream_buffer::~stream_buffer()
   {
   }

   ::file::buffer_sp  stream_buffer::Duplicate() const
   {
      return NULL;
   }

   bool stream_buffer::open(const char * lpszFileName, UINT nOpenFlags)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(nOpenFlags);
      return FALSE;
   }

   file_position stream_buffer::seek(file_offset lOff, ::file::e_seek nFrom)
   {
      UNREFERENCED_PARAMETER(lOff);
      UNREFERENCED_PARAMETER(nFrom);
      return 0;
   }

   file_position stream_buffer::seek_from_begin(file_position lPos)
   {
      return seek(lPos, seek_begin);
   }

   file_position stream_buffer::get_position() const
   {
      return ((stream_buffer *) this)->seek(0, ::file::seek_current);
   }

   file_position stream_buffer::tell() const
   {
      return get_position();
   }

   void stream_buffer::flush()
   {
   }

   void stream_buffer::close()
   {
   }

   ::primitive::memory_size stream_buffer::read(void *lpBuf, ::primitive::memory_size nCount)
   {
      return ::file::reader::read(lpBuf, nCount);
   }


   void stream_buffer::full_read(void * lpBuf, ::primitive::memory_size nCount)
   {

      ::primitive::memory_size uiRead;
      ::primitive::memory_size uiPos = 0;
      byte * buf = (byte *) lpBuf;

      while(nCount > 0)
      {
         
         uiRead = read(&buf[uiPos], nCount);

         if(uiRead <= 0)
            throw io_exception(get_app());

         nCount   -= uiRead;
         uiPos    += uiRead;

      }

   }

   void stream_buffer::write(const void * lpBuf, ::primitive::memory_size nCount)
   {
      ::file::writer::write(lpBuf, nCount);
   }


   void stream_buffer::write(output_stream & ostream)
   {
      
      seek_to_begin();

      transfer_to(*ostream.m_spbuffer);

   }


   void stream_buffer::read(input_stream & istream)
   {
   
      transfer_from(*istream.m_spbuffer);

      seek_to_begin();

   }


   void stream_buffer::Abort()
   {
   }

   void stream_buffer::LockRange(file_position dwPos, file_size dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void stream_buffer::UnlockRange(file_position dwPos, file_size dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void stream_buffer::set_length(file_size dwNewLen)
   {
      UNREFERENCED_PARAMETER(dwNewLen);
   }

   file_size stream_buffer::get_length() const
   {
      return 0;
   }

   // file does not support direct buffering (CMemFile does)
   uint64_t stream_buffer::GetBufferPtr(UINT nCommand, uint64_t nCount, void ** ppBufStart, void ** ppBufMax)
   {
      UNREFERENCED_PARAMETER(nCommand);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(ppBufStart);
      UNREFERENCED_PARAMETER(ppBufMax);
      return 0;
   }

/*   void stream_buffer::Rename(const char * lpszOldName, const char * lpszNewName)
   {
      UNREFERENCED_PARAMETER(lpszOldName);
      UNREFERENCED_PARAMETER(lpszNewName);
   }

   void stream_buffer::remove(const char * lpszFileName)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
   }*/

   void stream_buffer::assert_valid() const
   {
   //   object::assert_valid();
      // we permit the descriptor m_hFile to be any value for derived classes
   }

   void stream_buffer::dump(dump_context & dumpcontext) const
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

   string stream_buffer::GetFileName() const
   {
      return "";
   }

   string stream_buffer::GetFileTitle() const
   {
      return "";
   }

   string stream_buffer::GetFilePath() const
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

   bool stream_buffer::GetStatus(file_status & rStatus) const
   {
      UNREFERENCED_PARAMETER(rStatus);
      return FALSE;
   }

   bool stream_buffer::GetStatus(const char * lpszFileName, file_status & rStatus)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(rStatus);
      return FALSE;
   }


   void stream_buffer::SetStatus(const char * lpszFileName, const file_status & status)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(status);
   }



   bool stream_buffer::IsOpened()
   {
      return false;
   }

   string stream_buffer::get_location() const
   {
      return GetFileName();
   }

   
   bool stream_buffer::read(char * pch)
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

   bool stream_buffer::read(uchar * puch)
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

   bool stream_buffer::peek(char * pch)
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

   bool stream_buffer::peek(uchar * puch)
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

   bool stream_buffer::read(char & ch)
   {
      return read(&ch);
   }

   bool stream_buffer::read(uchar & uch)
   {
      return read(&uch);
   }

   bool stream_buffer::peek(char & ch)
   {
      return peek(&ch);
   }


   bool stream_buffer::peek(uchar & uch)
   {
      return peek(&uch);
   }


   int stream_buffer::sgetc()
   {

      char ch;

      if(!peek(&ch))
         return EOF;

      return ch;
      
   }

   int stream_buffer::sbumpc()
   {

      char ch;

      if(read(&ch, 1) <= 0)
         return EOF;

      return ch;
      
   }

   bool stream_buffer::read_string(string & str)
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

   bool stream_buffer::full_read_string(string & str)
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

   void stream_buffer::SetFilePath(const char * lpszNewName)
   {
      UNREFERENCED_PARAMETER(lpszNewName);
   }


   void stream_buffer::write(const string & str)
   {

      write(str,  str.get_length());

   }


   void stream_buffer::writef(const char *format, ...)
   {

      string strFormat;

      va_list list;

      va_start(list, format);

      strFormat.FormatV(format, list);

      va_end(list);

      write(strFormat);

   }

} // namespace file



