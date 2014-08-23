#include "framework.h"
#include "InFile.h"

namespace zip
{

   InFile::InFile(sp(::axis::application) papp):
      element(papp)
   {

   }

   InFile::~InFile()
   {
      if(get_zip_file() != NULL)
         close();
   }


   ::file::buffer_sp  InFile::Duplicate() const
   {
   //   ASSERT_VALID(this);
      ASSERT(get_zip_file() != NULL);

   /*   InFile* pFile = new InFile(hFileNull);
      HANDLE hFile;
      if (!::DuplicateHandle(::GetCurrentProcess(), (HANDLE)m_hFile,
         ::GetCurrentProcess(), &hFile, 0, FALSE, DUPLICATE_SAME_ACCESS))
      {
         delete pFile;
   //xxx      Ex1WinFileException::ThrowOsError((LONG)::GetLastError());
         throw 0;
      }
      pFile->m_hFile = (UINT)hFile;
      ASSERT(pFile->m_hFile != (UINT)hFileNull);
      pFile->m_bCloseOnDelete = m_bCloseOnDelete;*/
      return NULL;
      //return new ::file::binary_buffer_sp(this);
   }


   bool InFile::zip_open(const char * lpszFileName, UINT)
   {

      m_filea.remove_all();
      m_izfilea.remove_all();
      m_straPath.remove_all();
      m_straPrefix.remove_all();

      string strFile;
      strFile = lpszFileName;

      index iFind = -1;
      index iStart = 0;
      while((iFind = ::str::find_ci(".zip:", lpszFileName, iStart)) >= 0)
      {
         m_straPath.add(string(&lpszFileName[iStart], iFind + strlen(".zip")));
         iStart = iFind + strlen(".zip:");
      }
      if(::str::ends_ci(lpszFileName, ".zip"))
      {
         m_straPath.add(string(&lpszFileName[iStart]));
      }

      if(m_straPath.get_size() == 0)
         return FALSE;

      m_filea.add(new File(get_app()));
      if(!m_filea.last_element()->zip_open(m_straPath[0]))
         return false;

      string str;
      int32_t i;
      for(i = 1; i < m_straPath.get_size(); i++)
      {
         m_izfilea.add(new InFile(get_app()));
         str = m_straPath[i];
         if(!m_izfilea.last_element()->zip_open(m_filea.last_element(), str))
         {
            m_filea.remove_all();
            m_izfilea.remove_all();
            return FALSE;
         }
         m_filea.add(new File(get_app()));
         if(!m_filea.last_element()->zip_open((::file::buffer_sp ) m_izfilea.last_element()))
         {
            m_filea.remove_all();
            m_izfilea.remove_all();
            return FALSE;
         }
         m_straPrefix.add(m_straPath[i]);
      }
      if(::str::ends(strFile, ":"))
         return TRUE;
      iFind = strFile.reverse_find(L':');
      strFile = strFile.Mid(iFind + 1);
      ::str::begins_eat(strFile, "/");
      ::str::begins_eat(strFile, "\\");
      return TRUE;
   }

   bool InFile::unzip_open(::file::buffer_sp  pfile)
   {

      m_filea.remove_all();
      m_izfilea.remove_all();
      m_straPath.remove_all();
      m_straPrefix.remove_all();

      m_filea.add(new File(get_app()));
      if(!m_filea.last_element()->unzip_open(pfile))
         return false;

      return TRUE;

   }

   bool InFile::unzip_open(const char * lpszFileName, UINT)
   {

      m_filea.remove_all();
      m_izfilea.remove_all();
      m_straPath.remove_all();
      m_straPrefix.remove_all();

      string strFile;
      strFile = lpszFileName;

      index iFind = -1;
      index iStart = 0;
      while((iFind = ::str::find_ci(".zip:", lpszFileName, iStart)) >= 0)
      {
         m_straPath.add(string(&lpszFileName[iStart], iFind + strlen(".zip")));
         iStart = iFind + strlen(".zip:");
      }
      if(::str::ends_ci(lpszFileName, ".zip"))
      {
         m_straPath.add(string(&lpszFileName[iStart]));
      }

      if(m_straPath.get_size() == 0)
         return FALSE;

      m_filea.add(new File(get_app()));
      if(!m_filea.last_element()->unzip_open(m_straPath[0]))
         return false;

      string str;
      int32_t i;
      for(i = 1; i < m_straPath.get_size(); i++)
      {
         m_izfilea.add(new InFile(get_app()));
         str = m_straPath[i];
         if(!m_izfilea.last_element()->unzip_open(m_filea.last_element(), str))
         {
            m_filea.remove_all();
            m_izfilea.remove_all();
            return FALSE;
         }
         m_filea.add(new File(get_app()));
         if(!m_filea.last_element()->unzip_open((::file::buffer_sp )m_izfilea.last_element()))
         {
            m_filea.remove_all();
            m_izfilea.remove_all();
            return FALSE;
         }
         m_straPrefix.add(m_straPath[i]);
      }
      if(::str::ends(strFile, ":"))
         return TRUE;
      iFind = strFile.reverse_find(L':');
      strFile = strFile.Mid(iFind + 1);
      ::str::begins_eat(strFile, "/");
      ::str::begins_eat(strFile, "\\");
      if(!locate(strFile))
      {
         if(!locate(strFile + "/"))
            return FALSE;
      }
      return TRUE;
   }


   bool InFile::locate(const char * pszFileName)
   {
      string strFile(pszFileName);
      index iFind = strFile.find(":");
      if(iFind >= 0)
         strFile = strFile.Left(iFind);
      strFile.replace("\\", "/");
      if(unzLocateFile(get_zip_file()->m_pfUnzip, strFile, 0) != UNZ_OK)
      {
         strFile.replace("/", "\\");
         if(unzLocateFile(get_zip_file()->m_pfUnzip, strFile, 0) != UNZ_OK)
         {
            return false;
         }
      }
      if(unzOpenCurrentFile(get_zip_file()->m_pfUnzip) != UNZ_OK)
         return false;
      if(unzGetCurrentFileInfo(get_zip_file()->m_pfUnzip,
                            &m_fi,
                            NULL,
                            0,
                            NULL,
                            0,
                            NULL,
                            0) != UNZ_OK)
         return false;

      m_iPosition = 0;
      m_strFileName = strFile;
      return true;
   }

   bool InFile::unzip_open(File * pzfile, const char * lpcszFileName)
   {
      ASSERT(__is_valid_string(lpcszFileName));
      m_filea.add(pzfile);
      if(!locate(lpcszFileName))
         return FALSE;
      return TRUE;
   }

   bool InFile::zip_open(File * pzfile, const char * lpcszFileName)
   {
      ASSERT(__is_valid_string(lpcszFileName));
      m_filea.add(pzfile);
      m_strZipFile = lpcszFileName;
      return TRUE;
   }

   bool InFile::dump(::file::buffer_sp  pfile)
   {
      if(m_strFileName.is_empty())
         return false;
      BYTE buf[1024];
      ::primitive::memory_size iRead;
      while((iRead = read(buf, sizeof(buf))) > 0)
      {
         pfile->write(buf, iRead);
      }
      return true;
   }

   ::primitive::memory_size InFile::read(void * lpBuf, ::primitive::memory_size nCount)
   {
   //   ASSERT_VALID(this);
      ASSERT(get_zip_file() != NULL);

      if (nCount == 0)
         return 0;   // avoid Win32 "NULL-read"

      ASSERT(lpBuf != NULL);
      ASSERT(__is_valid_address(lpBuf, (uint_ptr) nCount));

      uint64_t iRead;
      iRead = unzReadCurrentFile(get_zip_file()->m_pfUnzip, lpBuf, (uint32_t) nCount);
      m_iPosition += iRead;

      return (UINT)iRead;
   }

   void InFile::write(const void * lpBuf, ::primitive::memory_size nCount)
   {
      UNREFERENCED_PARAMETER(lpBuf);
      UNREFERENCED_PARAMETER(nCount);
      //ASSERT_VALID(this);
      ASSERT(get_zip_file() != NULL);

      ASSERT(FALSE);
   }

   file_position InFile::seek(file_offset lOff, ::file::e_seek nFrom)
   {
   //   ASSERT_VALID(this);
      //ASSERT(get_zip_file() != NULL);
      //ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      //ASSERT(::file::seek_begin == FILE_BEGIN && ::file::seek_end == FILE_END && ::file::seek_current == FILE_CURRENT);
   /*typedef struct unz_file_pos_s
   {
       uint_ptr pos_in_zip_directory;   /* offset in zip file directory */
     //  uint_ptr num_of_file;            /* # of file */
   //} unz_file_pos;


      uint64_t iNewPos;
      if(nFrom == ::file::seek_begin)
      {
         iNewPos = lOff;
      }
      else if(nFrom == ::file::seek_end)
      {
         iNewPos = m_fi.uncompressed_size - lOff;
      }
      else if(nFrom == ::file::seek_current)
      {
         iNewPos = m_iPosition + lOff;
      }
      else
      {
         throw invalid_argument_exception(get_app(), "zip::InFile::seek invalid seek option");
      }

      if(iNewPos < m_iPosition)
      {
         if(unzCloseCurrentFile(get_zip_file()->m_pfUnzip) != UNZ_OK)
            return ::numeric_info < file_size >::allset();
         if(unzOpenCurrentFile(get_zip_file()->m_pfUnzip) != UNZ_OK)
            return ::numeric_info < file_size >::allset();
         m_iPosition = 0;
      }

      if(iNewPos > m_iPosition)
      {
         int64_t iRemain = iNewPos - m_iPosition;
         int64_t iGet;
         int32_t iRead;
         BYTE lpbBuf[1024];
         while(iRemain > 0)
         {
            iGet = MIN(iRemain, 1024);
            iRead = unzReadCurrentFile(get_zip_file()->m_pfUnzip, lpbBuf, (uint32_t) iGet);
            iRemain -= iRead;
            if(iRead < iGet)
               break;
         }
         iNewPos -= iRemain;
      }

      m_iPosition = iNewPos;

      return iNewPos;
   }

   file_position InFile::get_position() const
   {
      return m_iPosition;
   }

   void InFile::flush()
   {
   //   ASSERT_VALID(this);

   }

   void InFile::close()
   {
   //   ASSERT_VALID(this);
      //ASSERT(get_zip_file() != NULL);

      bool bError = FALSE;
      /*if(get_zip_file() != NULL)
      {
         unzCloseCurrentFile(get_zip_file()->m_pf);
      }*/

      m_filea.remove_all();
      m_izfilea.remove_all();
      m_straPath.remove_all();
      m_straPrefix.remove_all();
      m_strFileName.Empty();

      if (bError)
         throw 0;
   }

   void InFile::Abort()
   {
   }

   void InFile::LockRange(file_position dwPos, file_size dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void InFile::UnlockRange(file_position dwPos, file_size dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void InFile::set_length(file_size dwNewLen)
   {
      UNREFERENCED_PARAMETER(dwNewLen);
   //   ASSERT_VALID(this);
      ASSERT(get_zip_file() != NULL);
      ASSERT(FALSE);
   }

   file_size InFile::get_length() const
   {
      return m_fi.uncompressed_size;
   }

   // InFile does not support direct buffering (CMemFile does)
   uint64_t InFile::GetBufferPtr(UINT UNUSED(nCommand), uint64_t /*nCount*/, void ** /*ppBufStart*/, void ** /*ppBufMax*/)
   {
      ASSERT(nCommand == bufferCheck);

      return 0;   // no support
   }



   /*/////////////////////////////////////////////////////////////////////////////
   // InFile implementation helpers

   #ifdef ::core::GetFileName
   #undef ::core::GetFileName
   #endif

   #ifndef ___NO_OLE_SUPPORT

   HRESULT __COM::CreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter,
      REFIID riid, LPVOID* ppv)
   {
      // find the object's class factory
      LPCLASSFACTORY pf = NULL;
      HRESULT hRes = GetClassObject(rclsid, IID_IClassFactory, (LPVOID*)&pf);
      if (FAILED(hRes))
         return hRes;

      // call it to create the instance
      ASSERT(pf != NULL);
      hRes = pf->CreateInstance(pUnkOuter, riid, ppv);

      // let go of the factory
      pf->Release();
      return hRes;
   }

   HRESULT __COM::GetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
   {
      *ppv = NULL;
      HINSTANCE hInst = NULL;

      // find server name for this class ID

      string strCLSID = __iding_from_clsid(rclsid);
      string strServer;
      if (!__get_in_proc_server(strCLSID, strServer))
         return REGDB_E_CLASSNOTREG;

      // try to load it
      hInst = LoadLibrary(strServer);
      if (hInst == NULL)
         return REGDB_E_CLASSNOTREG;

   #pragma warning(disable:4191)
      // get its entry point
      HRESULT (STDAPICALLTYPE* pfn)(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
      pfn = (HRESULT (STDAPICALLTYPE*)(REFCLSID rclsid, REFIID riid, LPVOID* ppv))
         GetProcAddress(hInst, "DllGetClassObject");
   #pragma warning(default:4191)

      // call it, if it worked
      if (pfn != NULL)
         return pfn(rclsid, riid, ppv);
      return CO_E_ERRORINDLL;
   }*/


   /////////////////////////////////////////////////////////////////////////////
   // InFile diagnostics

   void InFile::assert_valid() const
   {
      //object::assert_valid();
      // we permit the descriptor m_hFile to be any value for derived classes
   }

   void InFile::dump(dump_context & dumpcontext) const
   {
   //   object::dump(dumpcontext);

      dumpcontext << "with handle " << (uint_ptr)get_zip_file();
      dumpcontext << " and name \"" << m_strFileName << "\"";
      dumpcontext << "\n";
   }


   // IMPLEMENT_DYNAMIC(InFile, object)


   /////////////////////////////////////////////////////////////////////////////
   // FileException helpers

   #ifdef DEBUG
/*   static const char * rgszFileExceptionCause[] =
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
   };*/
//   static const char szUnknown[] = "unknown";
   #endif


   /*void throw_file_exception(int32_t cause, LONG lOsError,
   //   const wchar_t * lpszFileName /* == NULL */
   /*{
   #ifdef DEBUG
      const char * lpsz;
      if (cause >= 0 && cause < _countof(rgszFileExceptionCause))
         lpsz = rgszFileExceptionCause[cause];
      else
         lpsz = szUnknown;
      TRACE3("InFile exception: %hs, InFile %W, App error information = %ld.\n",
         lpsz, (lpszFileName == NULL) ? L"Unknown" : lpszFileName, lOsError);
   #endif
      THROW(new FileException(cause, lOsError, lpszFileName));
   }*/

   /* Error Codes */
   #ifndef LINUX

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


#ifdef WINDOWS

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

#endif


   bool InFile::IsOpened()
   {
      return get_zip_file() != NULL;
   }

   File * InFile::get_zip_file()
   {
      if(m_filea.get_count() <= 0)
         return NULL;
      else
         return m_filea.last_element();
   }

   const File * InFile::get_zip_file() const
   {
      if(m_filea.get_count() <= 0)
         return NULL;
      else
         return m_filea.last_element();
   }

   void InFile::add_file(const char * pszDir, const char * pszRelative)
   {

      string strPath(System.dir().path(pszDir, pszRelative));

      ::file::binary_buffer_sp file;

      file = Application.file().get_file(strPath, ::file::mode_read | ::file::type_binary);

      if(file.is_null())
         throw "failed to open file for compressing";

      ::file::file_status status;

      file->GetStatus(status);

      zip_fileinfo zipfi;

      memset(&zipfi, 0, sizeof(zipfi));

      zipfi.tmz_date.tm_hour = status.m_ctime.GetGmtHour();
      zipfi.tmz_date.tm_sec  = status.m_ctime.GetGmtSecond();
      zipfi.tmz_date.tm_min  = status.m_ctime.GetGmtMinute();
      zipfi.tmz_date.tm_year = status.m_ctime.GetGmtYear();
      zipfi.tmz_date.tm_mon  = status.m_ctime.GetGmtMonth();
      zipfi.tmz_date.tm_mday = status.m_ctime.GetGmtDay();

      zipOpenNewFileInZip(get_zip_file()->m_pfZip, pszRelative, &zipfi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);

      ::primitive::memory mem(get_app());

      mem.allocate(256 * 1024);

      primitive::memory_size uiRead;
      while((uiRead = file->read(mem, mem.get_size())) > 0)
      {
         zipWriteInFileInZip(get_zip_file()->m_pfZip, mem.get_data(), (uint32_t) uiRead);
      }

      zipCloseFileInZip(get_zip_file()->m_pfZip);


   }


} // namespace zip
