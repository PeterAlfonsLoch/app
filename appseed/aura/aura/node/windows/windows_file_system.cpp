#include "framework.h"
#include "windows_file_system.h"


namespace windows
{


   file_system::file_system(::aura::application * papp) :
      object(papp),
      ::file::system(papp)
   {

   }


   file_system::~file_system()
   {

   }


   bool file_system::FullPath(string &str, const char * lpszFileIn)
   {

      //if(::core::file_system::FullPath(str, lpszFileIn))
      // return true;

      if(::str::begins_ci(lpszFileIn, "http://"))
      {

         str = lpszFileIn;

         return true;

      }
      else if(::str::begins_ci(lpszFileIn, "https://"))
      {

         str = lpszFileIn;

         return true;

      }
      wstring wstrFileIn;
      wstrFileIn = ::str::international::utf8_to_unicode(lpszFileIn);
      wstring wstrFileOut;
      bool b = vfxFullPath(wstrFileOut.alloc(MAX_PATH * 8), wstrFileIn) != FALSE;
      if(b)
      {
         ::str::international::unicode_to_utf8(str, wstrFileOut);
      }
      return b;
   }

   bool file_system::FullPath(wstring & wstrFullPath, const wstring & wstrPath)
   {

      /*      if(::core::file_system::FullPath(wstrFullPath, wstrPath))
      return true;*/

      if(::str::begins_ci(wstrPath, L"http://"))
      {
         wstrFullPath = wstrPath;
         return true;
      }
      else if(::str::begins_ci(wstrPath, L"https://"))
      {
         wstrFullPath = wstrPath;
         return true;
      }

      return vfxFullPath(wstrFullPath, wstrPath) != FALSE;

   }


   UINT file_system::GetFileName(const char * lpszPathName, string & str)
   {
      int32_t nMax = MAX_PATH * 8;
      wstring wstrPathName;
      wstrPathName = ::str::international::utf8_to_unicode(lpszPathName);
      wstring wstrTitle;
      UINT user = vfxGetFileName(wstrPathName, wstrTitle.alloc(nMax), nMax);
      str = ::str::international::unicode_to_utf8(wstrTitle);
      return user;
   }

   void file_system::GetModuleShortFileName(HINSTANCE hInst, string & strShortName)
   {
      vfxGetModuleShortFileName(hInst, strShortName);
   }

   var file_system::length(const string & strPath, ::aura::application * papp)
   {
      
      var varRet;

      varRet = ::file::system::length(strPath, papp);

      if (!varRet.is_null())
         return varRet;


#ifdef WINDOWS

      WIN32_FILE_ATTRIBUTE_DATA data;

      if(!GetFileAttributesExW(::str::international::utf8_to_unicode(strPath), GetFileExInfoStandard, &data))
      {
         varRet.set_type(var::type_null);
      }
      else
      {
         varRet = (uint32_t) data.nFileSizeLow;
      }

#else

      struct stat stat;

      if(::stat(strPath, &stat)  == -1)
      {
         varRet.set_type(var::type_null);
      }
      else
      {
         varRet = stat.st_size;
      }

#endif

      return varRet;

   }


   // from win32_handmade (casey) : Thank you, Casey Muratori!! From Seattle (sitou) to Curitiba, 8 de novembro de 205


   bool file_system::get_last_write_time(FILETIME * pfiletime,const string & strFilename)
   {

      WIN32_FILE_ATTRIBUTE_DATA data;

      ZERO(data);

      if(!GetFileAttributesExW(wstring(strFilename),GetFileExInfoStandard,&data))
      {

         return false;

      }

      *pfiletime = data.ftLastWriteTime;

      return true;

   }



   bool file_system::get_status(const ::file::path & path,::file::file_status & rStatus)
   {

      // attempt to fully qualify path first
      wstring wstrFullName;
      wstring wstrFileName;
      wstrFileName = ::str::international::utf8_to_unicode(path);
      if(!vfxFullPath(wstrFullName,wstrFileName))
      {
         rStatus.m_strFullName.Empty();
         return FALSE;
      }
      ::str::international::unicode_to_utf8(rStatus.m_strFullName,wstrFullName);

      WIN32_FIND_DATAW findFileData;
      HANDLE hFind = FindFirstFileW((LPWSTR)(LPCWSTR)wstrFullName,&findFileData);
      if(hFind == INVALID_HANDLE_VALUE)
         return FALSE;
      VERIFY(FindClose(hFind));

      // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
      rStatus.m_attribute = (BYTE)(findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);

      // get just the low DWORD of the file size
      ASSERT(findFileData.nFileSizeHigh == 0);
      rStatus.m_size = (LONG)findFileData.nFileSizeLow;

      // convert times as appropriate
      rStatus.m_ctime = ::datetime::time(findFileData.ftCreationTime);
      rStatus.m_atime = ::datetime::time(findFileData.ftLastAccessTime);
      rStatus.m_mtime = ::datetime::time(findFileData.ftLastWriteTime);

      if(rStatus.m_ctime.get_time() == 0)
         rStatus.m_ctime = rStatus.m_mtime;

      if(rStatus.m_atime.get_time() == 0)
         rStatus.m_atime = rStatus.m_mtime;

      return true;

   }

   //void system::set_status(const ::file::path & path,const ::file::file_status& status)
   //{

   //   wstring lpszFileName(path);
   //   DWORD wAttr;
   //   FILETIME creationTime;
   //   FILETIME lastAccessTime;
   //   FILETIME lastWriteTime;
   //   LPFILETIME lpCreationTime = NULL;
   //   LPFILETIME lpLastAccessTime = NULL;
   //   LPFILETIME lpLastWriteTime = NULL;

   //   if((wAttr = GetFileAttributesW((LPWSTR)(LPCWSTR)lpszFileName)) == (DWORD)-1L)
   //      file_exception::ThrowOsError(get_app(),(LONG)GetLastError());

   //   if((DWORD)status.m_attribute != wAttr && (wAttr & readOnly))
   //   {
   //      // set file attribute, only if currently readonly.
   //      // This way we will be able to modify the time assuming the
   //      // caller changed the file from readonly.

   //      if(!SetFileAttributesW((LPWSTR)(LPCWSTR)lpszFileName,(DWORD)status.m_attribute))
   //         file_exception::ThrowOsError(get_app(),(LONG)GetLastError());
   //   }

   //   // last modification time
   //   if(status.m_mtime.get_time() != 0)
   //   {
   //      ::core::TimeToFileTime(status.m_mtime,&lastWriteTime);
   //      lpLastWriteTime = &lastWriteTime;

   //      // last access time
   //      if(status.m_atime.get_time() != 0)
   //      {
   //         ::core::TimeToFileTime(status.m_atime,&lastAccessTime);
   //         lpLastAccessTime = &lastAccessTime;
   //      }

   //      // create time
   //      if(status.m_ctime.get_time() != 0)
   //      {
   //         ::core::TimeToFileTime(status.m_ctime,&creationTime);
   //         lpCreationTime = &creationTime;
   //      }

   //      HANDLE hFile = ::CreateFileW((LPWSTR)(LPCWSTR)lpszFileName,GENERIC_READ | GENERIC_WRITE,
   //         FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,
   //         NULL);

   //      if(hFile == INVALID_HANDLE_VALUE)
   //         file_exception::ThrowOsError(get_app(),(LONG)::GetLastError());

   //      if(!SetFileTime((HANDLE)hFile,lpCreationTime,lpLastAccessTime,lpLastWriteTime))
   //         file_exception::ThrowOsError(get_app(),(LONG)::GetLastError());

   //      if(!::CloseHandle(hFile))
   //         file_exception::ThrowOsError(get_app(),(LONG)::GetLastError());
   //   }

   //   if((DWORD)status.m_attribute != wAttr && !(wAttr & readOnly))
   //   {
   //      if(!SetFileAttributes((LPTSTR)lpszFileName,(DWORD)status.m_attribute))
   //         file_exception::ThrowOsError(get_app(),(LONG)GetLastError());
   //   }
   //}


   //void file::SetStatus(const char * lpszFileName,const ::file::file_status& status)
   //{
   //   DWORD wAttr;
   //   FILETIME creationTime;
   //   FILETIME lastAccessTime;
   //   FILETIME lastWriteTime;
   //   LPFILETIME lpCreationTime = NULL;
   //   LPFILETIME lpLastAccessTime = NULL;
   //   LPFILETIME lpLastWriteTime = NULL;

   //   if((wAttr = GetFileAttributes((LPTSTR)lpszFileName)) == (DWORD)-1L)
   //      file_exception::ThrowOsError(get_app(),(LONG)GetLastError());

   //   if((DWORD)status.m_attribute != wAttr && (wAttr & readOnly))
   //   {
   //      // set file attribute, only if currently readonly.
   //      // This way we will be able to modify the time assuming the
   //      // caller changed the file from readonly.

   //      if(!SetFileAttributes((LPTSTR)lpszFileName,(DWORD)status.m_attribute))
   //         file_exception::ThrowOsError(get_app(),(LONG)GetLastError());
   //   }

   //   // last modification time
   //   if(status.m_mtime.get_time() != 0)
   //   {
   //      ::core::TimeToFileTime(status.m_mtime,&lastWriteTime);
   //      lpLastWriteTime = &lastWriteTime;

   //      // last access time
   //      if(status.m_atime.get_time() != 0)
   //      {
   //         ::core::TimeToFileTime(status.m_atime,&lastAccessTime);
   //         lpLastAccessTime = &lastAccessTime;
   //      }

   //      // create time
   //      if(status.m_ctime.get_time() != 0)
   //      {
   //         ::core::TimeToFileTime(status.m_ctime,&creationTime);
   //         lpCreationTime = &creationTime;
   //      }

   //      HANDLE hFile = ::CreateFile(lpszFileName,GENERIC_READ | GENERIC_WRITE,
   //         FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,
   //         NULL);

   //      if(hFile == INVALID_HANDLE_VALUE)
   //         file_exception::ThrowOsError(get_app(),(LONG)::GetLastError());

   //      if(!SetFileTime((HANDLE)hFile,lpCreationTime,lpLastAccessTime,lpLastWriteTime))
   //         file_exception::ThrowOsError(get_app(),(LONG)::GetLastError());

   //      if(!::CloseHandle(hFile))
   //         file_exception::ThrowOsError(get_app(),(LONG)::GetLastError());
   //   }

   //   if((DWORD)status.m_attribute != wAttr && !(wAttr & readOnly))
   //   {
   //      if(!SetFileAttributes((LPTSTR)lpszFileName,(DWORD)status.m_attribute))
   //         file_exception::ThrowOsError(get_app(),(LONG)GetLastError());
   //   }
   //}

   ::file::exception_sp file_system::set_status(const ::file::path & path,const ::file::file_status & status)
   {

      wstring lpszFileName(path);

      DWORD wAttr;
      FILETIME creationTime;
      FILETIME lastAccessTime;
      FILETIME lastWriteTime;
      LPFILETIME lpCreationTime = NULL;
      LPFILETIME lpLastAccessTime = NULL;
      LPFILETIME lpLastWriteTime = NULL;

      if((wAttr = GetFileAttributesW((LPWSTR)(LPCWSTR)lpszFileName)) == (DWORD)-1L)
         file_exception::ThrowOsError(get_app(),(LONG)GetLastError());

      if((DWORD)status.m_attribute != wAttr && (wAttr & FILE_ATTRIBUTE_READONLY))
      {
         // set file attribute, only if currently readonly.
         // This way we will be able to modify the time assuming the
         // caller changed the file from readonly.

         if(!SetFileAttributesW((LPWSTR)(LPCWSTR) lpszFileName,(DWORD)status.m_attribute))
            file_exception::ThrowOsError(get_app(),(LONG)GetLastError());
      }

      // last modification time
      if(status.m_mtime.get_time() != 0)
      {
         lastWriteTime = status.m_mtime.to_file_time();
         lpLastWriteTime = &lastWriteTime;

         // last access time
         if(status.m_atime.get_time() != 0)
         {
            lastAccessTime = status.m_atime.to_file_time();
            lpLastAccessTime = &lastAccessTime;
         }

         // create time
         if(status.m_ctime.get_time() != 0)
         {
            creationTime = status.m_ctime.to_file_time();
            lpCreationTime = &creationTime;
         }

         HANDLE hFile = ::CreateFileW((LPWSTR)(LPCWSTR)lpszFileName,GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,
            NULL);

         if(hFile == INVALID_HANDLE_VALUE)
         {
            return file_exception::last_os_error(get_app(),path);
         }

         if(!SetFileTime((HANDLE)hFile,lpCreationTime,lpLastAccessTime,lpLastWriteTime))
            return file_exception::last_os_error(get_app(),path);

         if(!::CloseHandle(hFile))
            return file_exception::last_os_error(get_app(),path);
      }

      if((DWORD)status.m_attribute != wAttr && !(wAttr & FILE_ATTRIBUTE_READONLY))
      {
         if(!SetFileAttributesW((LPWSTR)(LPCWSTR)lpszFileName,(DWORD)status.m_attribute))
            return file_exception::last_os_error(get_app(),path);
      }

      return ::file::no_exception();

   }



} // namespace windows


















































































