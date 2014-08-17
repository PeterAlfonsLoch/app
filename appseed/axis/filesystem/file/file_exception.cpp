#include "framework.h"

#ifdef WINDOWS
#include <Shellapi.h>
#endif


namespace file
{


   exception::exception(sp(::base::application) papp, int32_t cause , LONG lOsError, const char * lpszArchiveName) :
      element(papp),
      ::call_stack(papp),
      ::exception::base(papp),
      ::simple_exception(papp),
      ::io_exception(papp)
   {
         printf(":file(%d,%d,%s)", cause, lOsError, string(lpszArchiveName).c_str());
      Construct(cause, lOsError, lpszArchiveName);
   }


   void exception::Construct(int32_t cause, LONG lOsError, const char * pstrFileName /* = NULL */)
   {

      m_cause              = cause;
      m_lOsError           = lOsError;
      m_strFileName        = pstrFileName;

   }

   exception::~exception()
   {
   }

   int32_t exception::get_cause()
   {
      return m_cause;
   }

   LONG exception::get_os_error()
   {
      return m_lOsError;
   }

   string exception::get_file_path()
   {
      return m_strFileName;
   }


   struct PROCESS_INFO_t
   {
      string csProcess;
      uint32_t dwImageListIndex;
   };


#ifdef WINDOWSEX

   void CALLBACK exception::CallBackFunc( OF_INFO_t OpenedFileInfo, uint_ptr pUserContext )
   {
      ((exception*)pUserContext)->OnFileFound( OpenedFileInfo );
   }

   void exception::OnFileFound(OF_INFO_t OpenedFileInfo )
   {

      if(session().file_name(::str::international::unicode_to_utf8(OpenedFileInfo.lpFile)).CompareNoCase(session().file_name(m_strFileName)) == 0)
      {

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
               stInfo.dwImageListIndex = m_imgListCtrl.add( stIcon.hIcon );
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
         //m_list.set_item_text( m_nCount, 2, OpenedFileInfo.lpFile );
         //m_list.SetItemData( m_nCount, (uint_ptr)OpenedFileInfo.hFile );

      }

   }

#endif

   /*
   string exception::get_friendly_message(PUINT pnHelpContext) const
   {

   string str;

   if(!get_friendly_error_message(str, pnHelpContext))
   return "";

   return str;

   }
   */

   bool exception::get_error_message(string & str, PUINT pnHelpContext)
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

         wstr = ::str::international::utf8_to_unicode(session().dir_name(m_strFileName));

#ifdef WINDOWSEX
         GetOpenedFiles(wstr, ALL_TYPES, &exception::CallBackFunc, (uint_ptr)this);
#endif

         if(m_strAdd.has_char())
         {
            ((exception * ) this)->m_strAdd = " Process Using the file = " + m_strAdd;
         }
         else
         {
            ((exception * ) this)->m_strAdd = " Process Using the file Not Found ";
         }

      }

      string strExtra;

      strExtra = get_system_error_message(m_lOsError);

      strExtra += m_strAdd;

      strMessage.Format("file error number: %d - %s - file: %s", m_cause, strExtra.c_str(), strFileName.c_str());

      str = strMessage;

      return TRUE;
   }


   /*
   bool exception::get_error_message(string & str, PUINT pnHelpContext) const
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
   */

   /////////////////////////////////////////////////////////////////////////////
   // exception diagnostics

   void exception::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      //object::dump(dumpcontext);

      /*   dumpcontext << "m_cause = ";
      if (m_cause >= 0 && m_cause < _countof(rgszFileExceptionCause))
      dumpcontext << rgszFileExceptionCause[m_cause];
      else
      dumpcontext << szUnknown;
      dumpcontext << "\nm_lOsError = " << (void *)m_lOsError;

      dumpcontext << "\n";*/
   }



} // namespace file










/////////////////////////////////////////////////////////////////////////////
// file_exception helpers

#ifdef DEBUG
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


void throw_file_exception(::base::application * papp, int32_t cause, LONG lOsError,   const char * lpszFileName /* == NULL */ )
{

#ifdef DEBUG

   const char * lpsz;

   if (cause >= 0 && cause < _countof(rgszFileExceptionCause))
      lpsz = rgszFileExceptionCause[cause];
   else
      lpsz = szUnknown;

   string strFormat;

   strFormat.Format("file exception: %hs, file %s, App error information = %ld.\n",  lpsz, (lpszFileName == NULL) ? "Unknown" : lpszFileName, lOsError);

   ::output_debug_string(strFormat);

#endif


   throw ::file::exception(papp, cause, lOsError, lpszFileName);

}

