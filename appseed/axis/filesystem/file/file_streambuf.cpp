#include "framework.h"


namespace file
{


   streambuf::streambuf()
   {

      m_pfile = NULL;

   }



   streambuf::~streambuf()
   {

      if(m_pfile != NULL)
      {
         
         fclose_dup(m_pfile);

      }

   }

   ::file::buffer_sp  streambuf::Duplicate() const
   {
      return NULL;
   }

   bool streambuf::open(const char * lpszFileName,UINT nOpenFlags)
   {

      string str;

      if(nOpenFlags & ::file::mode_read)
      {
         str += "r";
      }

      if(nOpenFlags & ::file::mode_write)
      {
         str += "w";
      }

      if(nOpenFlags & ::file::type_binary)
      {
         str += "b";
      }
      else if(nOpenFlags & ::file::type_text)
      {
      }

      m_pfile = fopen_dup(lpszFileName,str);

      if(m_pfile == NULL)
         return false;
      
      return true;

   }


   file_position streambuf::seek(file_offset lOff,::file::e_seek eseek)
   {

      int nFrom = SEEK_SET;

      switch(eseek)
      {
      case seek_current:
         nFrom = SEEK_CUR;
         break;

      case seek_end:
         nFrom = SEEK_END;
         break;

      default:
         break;

      }

      return fseek_dup(m_pfile,lOff,nFrom);

   }


   file_position streambuf::get_position() const
   {

      return ftell_dup(m_pfile);

   }


   void streambuf::flush()
   {
      
      fflush_dup(m_pfile);

   }


   void streambuf::close()
   {

      fclose_dup(m_pfile);

   }

   ::primitive::memory_size streambuf::read(void *lpBuf,::primitive::memory_size nCount)
   {
      
      return fread_dup(lpBuf, nCount, 1, m_pfile);

   }



   void streambuf::write(const void * lpBuf,::primitive::memory_size nCount)
   {
      fwrite_dup(lpBuf,nCount, 1, m_pfile);
   }


   void streambuf::Abort()
   {
   }

   void streambuf::LockRange(file_position dwPos,file_size dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void streambuf::UnlockRange(file_position dwPos,file_size dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void streambuf::set_length(file_size dwNewLen)
   {
      UNREFERENCED_PARAMETER(dwNewLen);
   }

   file_size streambuf::get_length() const
   {

      return flen_dup(m_pfile);

   }

   // file does not support direct buffering (CMemFile does)
   uint64_t streambuf::GetBufferPtr(UINT nCommand,uint64_t nCount,void ** ppBufStart,void ** ppBufMax)
   {
      UNREFERENCED_PARAMETER(nCommand);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(ppBufStart);
      UNREFERENCED_PARAMETER(ppBufMax);
      return 0;
   }

   /*   void streambuf::Rename(const char * lpszOldName, const char * lpszNewName)
   {
   UNREFERENCED_PARAMETER(lpszOldName);
   UNREFERENCED_PARAMETER(lpszNewName);
   }

   void streambuf::remove(const char * lpszFileName)
   {
   UNREFERENCED_PARAMETER(lpszFileName);
   }*/

   void streambuf::assert_valid() const
   {
      //   object::assert_valid();
      // we permit the descriptor m_hFile to be any value for derived classes
   }

   void streambuf::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      //   object::dump(dumpcontext);

      //   dumpcontext << "with handle " << (UINT)m_hFile;
      //   dumpcontext << " and name \"" << m_wstrFileName << "\"";
      //   dumpcontext << "\n";
   }




   string streambuf::GetFileName() const
   {
      return "";
   }

   string streambuf::GetFileTitle() const
   {
      return "";
   }

   string streambuf::GetFilePath() const
   {
      return "";
   }






   bool streambuf::GetStatus(file_status & rStatus) const
   {
      UNREFERENCED_PARAMETER(rStatus);
      return FALSE;
   }

   bool streambuf::GetStatus(const char * lpszFileName,file_status & rStatus)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(rStatus);
      return FALSE;
   }


   void streambuf::SetStatus(const char * lpszFileName,const file_status & status)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(status);
   }



   bool streambuf::IsOpened()
   {
      return false;
   }


   bool streambuf::is_open()
   {
      return IsOpened();
   }

   string streambuf::get_location() const
   {
      return GetFileName();
   }



} // namespace file



