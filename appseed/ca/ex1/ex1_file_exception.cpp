#include "framework.h"


namespace ex1
{


   file_exception::file_exception(::ca::application * papp, int cause , LONG lOsError, const char * lpszArchiveName) :
      ca(papp),
      ::call_stack(papp),
      ::ex1::exception(papp)
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



   void CALLBACK file_exception::CallBackFunc( OF_INFO_t OpenedFileInfo, uint_ptr pUserContext )
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
	      //m_list.SetItemText( m_nCount, 2, OpenedFileInfo.lpFile );
	      //m_list.SetItemData( m_nCount, (dword_ptr)OpenedFileInfo.hFile );
#endif

      }

   }

/*
   string file_exception::get_friendly_message(PUINT pnHelpContext) const
   {

      string str;

      if(!get_friendly_error_message(str, pnHelpContext))
         return "";

      return str;

   }
*/

   bool file_exception::get_error_message(string & str, PUINT pnHelpContext)
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

         GetOpenedFiles(wstr, ALL_TYPES, &file_exception::CallBackFunc, (ulong_ptr)this);

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


/*
   bool file_exception::get_error_message(string & str, PUINT pnHelpContext) const
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



} // namespace ex1
