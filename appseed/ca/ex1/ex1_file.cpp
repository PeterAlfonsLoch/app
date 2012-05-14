#include "framework.h"

namespace ex1
{

   __STATIC inline BOOL IsDirSep(WCHAR ch)
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

   BOOL file::open(const char * lpszFileName, UINT nOpenFlags,
      ex1::file_exception_sp * pException)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(nOpenFlags);
      UNREFERENCED_PARAMETER(pException);
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

   #ifdef _DEBUG
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
   #endif


   /*void vfxThrowFileException(int cause, LONG lOsError,
   //   const char * lpszFileName /* == NULL */
   /*{
   #ifdef _DEBUG
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
   #define EAGAIN          11
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




   /////////////////////////////////////////////////////////////////////////////
   // file_exception


   file_exception::file_exception(::ca::application * papp, int cause , LONG lOsError, const char * lpszArchiveName) :
      ca(papp)
   {
      Construct(cause, lOsError, lpszArchiveName);
   }


   void file_exception::Construct(int cause, LONG lOsError, const char * pstrFileName /* = NULL */)
   {

      m_cause              = cause;
      m_lOsError           = lOsError;
      m_strFileName        = pstrFileName;

   }

   file_exception::~file_exception()
   {
   }

   int file_exception::get_cause()
   {
      return m_cause;
   }

   LONG file_exception::get_os_error()
   {
      return m_lOsError;
   }

   string file_exception::get_file_path()
   {
      return m_strFileName;
   }


   struct PROCESS_INFO_t
   {
       string csProcess;
       DWORD dwImageListIndex;
   };



   void CALLBACK file_exception::CallBackFunc( OF_INFO_t OpenedFileInfo, UINT_PTR pUserContext )
   {
      ((file_exception*)pUserContext)->OnFileFound( OpenedFileInfo );
   }

   void file_exception::OnFileFound(OF_INFO_t OpenedFileInfo )
   {

	   if(System.file().name_(gen::international::unicode_to_utf8(OpenedFileInfo.lpFile)).CompareNoCase(System.file().name_(m_strFileName)) == 0)
      {

#ifdef WINDOWS
	      PROCESS_INFO_t stInfo;
	      //if( !m_stProcessInfo.Lookup( OpenedFileInfo.dwPID, stInfo))
	      {
		      TCHAR tcFileName[MAX_PATH];
		      string csModule;
		      HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, TRUE, OpenedFileInfo.dwPID );
		      stInfo.dwImageListIndex = 0;
		      if( !hProcess || !GetProcessImageFileName( hProcess, tcFileName, MAX_PATH ))
		      {
			      if( hProcess )
			      {
				      CloseHandle( hProcess );
			      }

			      if( OpenedFileInfo.dwPID == 4 )// system process
			      {
				      stInfo.csProcess = L"System";
			      }
			      else
			      {
				      stInfo.csProcess = L"Unknown Process";
			      }
		      }
		      else
		      {
			      GetDrive( tcFileName, csModule, false );
			      CloseHandle( hProcess );
			      PathStripPath( tcFileName );
			      stInfo.csProcess = tcFileName;
			      SHFILEINFO stIcon = {0};
   /*			   if( SHGetFileInfo( csModule, 0, &stIcon, sizeof( stIcon), SHGFI_ICON ))
			      {
				      stInfo.dwImageListIndex = m_imgListCtrl.Add( stIcon.hIcon );
				      DestroyIcon( stIcon.hIcon );
			      }*/
		      }
		     // m_stProcessInfo[OpenedFileInfo.dwPID] = stInfo;
	      }
	      // Insert Process name, PID and file name
	      //m_list.InsertItem( m_nCount, stInfo.csProcess, stInfo.dwImageListIndex );
	      string csPid;
	      csPid.Format( _T("%d ( 0x%x )"), OpenedFileInfo.dwPID , OpenedFileInfo.dwPID );
         m_strAdd += "PID: " + csPid + " Process Name : " + stInfo.csProcess;
	      //m_list.SetItemText( m_nCount, 2, OpenedFileInfo.lpFile );
	      //m_list.SetItemData( m_nCount, (DWORD_PTR)OpenedFileInfo.hFile );
#endif

      }

   }


   BOOL file_exception::get_friendly_error_message(string & str, PUINT pnHelpContext) const
   {

     // if (pnHelpContext != NULL)
   //      *pnHelpContext = m_cause + __IDP_FILE_NONE;

      string strMessage;

      string strFileName = m_strFileName;

      if(strFileName.is_empty())
         strFileName = "IDS_UNNAMED_FILE";

      if(m_lOsError == ERROR_ACCESS_DENIED || m_lOsError == ERROR_SHARING_VIOLATION)
      {

         wstring wstr;

         wstr = gen::international::utf8_to_unicode(System.dir().name(m_strFileName));

         GetOpenedFiles(wstr, ALL_TYPES, &file_exception::CallBackFunc, (ULONG_PTR)this);

         if(m_strAdd.has_char())
         {
            ((file_exception * ) this)->m_strAdd = " Process Using the file = " + m_strAdd;
         }
         else
         {
            ((file_exception * ) this)->m_strAdd = " Process Using the file Not Found ";
         }

      }

      string strExtra;

      strExtra = get_system_error_message(m_lOsError);

      strExtra += m_strAdd;

      strMessage.Format("file error number: %d - %s - file: %s", m_cause, strExtra, strFileName);

      str = strMessage;

      return TRUE;
   }


   BOOL file_exception::GetErrorMessage(string & str, PUINT pnHelpContext) const
   {

     // if (pnHelpContext != NULL)
   //      *pnHelpContext = m_cause + __IDP_FILE_NONE;

      string strMessage;

      string strFileName = m_strFileName;

      if(strFileName.is_empty())
         strFileName = "IDS_UNNAMED_FILE";

      string strExtra;

      strExtra = get_system_error_message(m_lOsError);

      strMessage.Format("file error number: %d - %s - file: %s", m_cause, strExtra, strFileName);

      str = strMessage;

      return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // file_exception diagnostics

   void file_exception::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      //::radix::object::dump(dumpcontext);

   /*   dumpcontext << "m_cause = ";
      if (m_cause >= 0 && m_cause < _countof(rgszFileExceptionCause))
         dumpcontext << rgszFileExceptionCause[m_cause];
      else
         dumpcontext << szUnknown;
      dumpcontext << "\nm_lOsError = " << (void *)m_lOsError;

      dumpcontext << "\n";*/
   }

   /////////////////////////////////////////////////////////////////////////////
   // file_exception helpers

   void vfxThrowFileException(::ca::application  * papp, int cause, LONG lOsError,
      const char * lpszFileName /* == NULL */)
   {
   #ifdef _DEBUG
      const char * lpsz;
      if (cause >= 0 && cause < _countof(rgszFileExceptionCause))
         lpsz = rgszFileExceptionCause[cause];
      else
         lpsz = szUnknown;
/*      TRACE3("file exception: %hs, file %s, App error information = %ld.\n",
         lpsz, (lpszFileName == NULL) ? "Unknown" : lpszFileName, lOsError);*/
   #endif
      throw new file_exception(papp, cause, lOsError, lpszFileName);
   }



   // IMPLEMENT_DYNAMIC(file_exception, base_exception)

   /////////////////////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////////////////////
   // Help and other support

   // Strings in format ".....%1 .... %2 ...." etc.


   /////////////////////////////////////////////////////////////////////////////
   // file Status implementation

   BOOL file::GetStatus(file_status & rStatus) const
   {
      UNREFERENCED_PARAMETER(rStatus);
      return FALSE;
   }

   BOOL PASCAL file::GetStatus(const char * lpszFileName, file_status & rStatus)
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

   bool file::read(unsigned char * puch)
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

   bool file::peek(unsigned char * puch)
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

   bool file::read(unsigned char & uch)
   {
      return read(&uch);
   }

   bool file::peek(char & ch)
   {
      return peek(&ch);
   }

   bool file::peek(unsigned char & uch)
   {
      return peek(&uch);
   }

} // namespace ex1
