//#include "framework.h"


namespace file
{


   stdio_file::stdio_file()
   {

      m_pfile = NULL;

   }


   stdio_file::stdio_file(const char * lpszFileName,UINT nOpenFlags)
   {

      m_pfile = NULL;

      if(!open(lpszFileName,nOpenFlags))
      {

         throw_file_exception(get_app(),::file::exception::type_generic,::GetLastError(), lpszFileName);

      }

   }


   stdio_file::~stdio_file()
   {

      if(m_pfile != NULL)
      {
         
         fclose_dup(m_pfile);

      }

   }

   ::file::file_sp  stdio_file::Duplicate() const
   {
      return NULL;
   }

   
   cres stdio_file::open(const ::file::path & lpszFileName,UINT nOpenFlags)
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
         return canew(::file::exception(get_app()));
      
      return ::no_exception;

   }


   file_position_t stdio_file::seek(file_offset_t lOff,::file::e_seek eseek)
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


   file_position_t stdio_file::get_position() const
   {

      return ftell_dup(m_pfile);

   }


   void stdio_file::flush()
   {
      
      fflush_dup(m_pfile);

   }


   void stdio_file::close()
   {

      fclose_dup(m_pfile);

   }

   memory_size_t stdio_file::read(void *lpBuf,memory_size_t nCount)
   {
      
      return fread_dup(lpBuf, nCount, 1, m_pfile);

   }



   void stdio_file::write(const void * lpBuf,memory_size_t nCount)
   {
      fwrite_dup(lpBuf,nCount, 1, m_pfile);
   }


   void stdio_file::Abort()
   {
   }

   void stdio_file::LockRange(file_position_t dwPos,file_size_t dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void stdio_file::UnlockRange(file_position_t dwPos,file_size_t dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void stdio_file::set_length(file_size_t dwNewLen)
   {
      UNREFERENCED_PARAMETER(dwNewLen);
   }

   file_size_t stdio_file::get_length() const
   {

      return flen_dup(m_pfile);

   }

   // file does not support direct buffering (CMemFile does)
   uint64_t stdio_file::GetBufferPtr(UINT nCommand,uint64_t nCount,void ** ppBufStart,void ** ppBufMax)
   {
      UNREFERENCED_PARAMETER(nCommand);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(ppBufStart);
      UNREFERENCED_PARAMETER(ppBufMax);
      return 0;
   }

   /*   void stdio_file::Rename(const char * lpszOldName, const char * lpszNewName)
   {
   UNREFERENCED_PARAMETER(lpszOldName);
   UNREFERENCED_PARAMETER(lpszNewName);
   }

   void stdio_file::remove(const char * lpszFileName)
   {
   UNREFERENCED_PARAMETER(lpszFileName);
   }*/

   void stdio_file::assert_valid() const
   {
      //   object::assert_valid();
      // we permit the descriptor m_hFile to be any value for derived classes
   }

   void stdio_file::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      //   object::dump(dumpcontext);

      //   dumpcontext << "with handle " << (UINT)m_hFile;
      //   dumpcontext << " and name \"" << m_wstrFileName << "\"";
      //   dumpcontext << "\n";
   }




   string stdio_file::GetFileName() const
   {
      return "";
   }

   string stdio_file::GetFileTitle() const
   {
      return "";
   }

   string stdio_file::GetFilePath() const
   {
      return "";
   }






   bool stdio_file::GetStatus(file_status & rStatus) const
   {
      UNREFERENCED_PARAMETER(rStatus);
      return FALSE;
   }

   //bool stdio_file::GetStatus(const char * lpszFileName,file_status & rStatus)
   //{
   //   UNREFERENCED_PARAMETER(lpszFileName);
   //   UNREFERENCED_PARAMETER(rStatus);
   //   return FALSE;
   //}


   //void stdio_file::SetStatus(const char * lpszFileName,const file_status & status)
   //{
   //   UNREFERENCED_PARAMETER(lpszFileName);
   //   UNREFERENCED_PARAMETER(status);
   //}



   bool stdio_file::IsOpened()
   {
      return false;
   }


   bool stdio_file::is_open()
   {
      return IsOpened();
   }

   string stdio_file::get_location() const
   {
      return GetFileName();
   }



} // namespace file



