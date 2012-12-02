#include "framework.h"


CLASS_DECL_c void ensure_file_size(HANDLE h, int64_t iSize)
{

   DWORD dwHi;

   DWORD dwLo = ::GetFileSize(h, &dwHi);

   if(((uint64_t) dwLo | ((int64_t)dwHi << 32)) != iSize)
   {
      LONG l = (iSize >> 32) & 0xffffffff;
      ::SetFilePointer(h, iSize & 0xffffffff, &l, SEEK_SET);
      SetEndOfFile(h);
   }

}

CLASS_DECL_c DWORD SetFilePointer(HANDLE h, LONG lMove, PLONG plHi, DWORD dwMeth)
{

   LARGE_INTEGER liMove;

   LARGE_INTEGER liRes;

   liRes.LowPart  = 0;

   liRes.HighPart = 0;

   liMove.LowPart = lMove;

   if(plHi != NULL)
   {

      liMove.HighPart = *plHi;

   }
   else
   {

      liMove.HighPart = 0;

   }

   if(!SetFilePointerEx(h, liMove, &liRes, dwMeth))
      throw "SetFilePointer error";

   if(plHi != NULL)
   {
      
      *plHi = liRes.HighPart;

   }

   return liRes.LowPart;


}

CLASS_DECL_c DWORD GetFileSize(HANDLE h, LPDWORD lpdwHi)
{

   FILE_STANDARD_INFO info;
   
   if(!GetFileInformationByHandleEx(h, FileStandardInfo, &info, sizeof(info)))
      throw "GetFileSize Error";

   if(lpdwHi != NULL)
   {
      *lpdwHi = info.EndOfFile.HighPart;
   }

   return info.EndOfFile.LowPart;

}


CLASS_DECL_c DWORD GetFileAttributes(const wchar_t * psz)
{

   WIN32_FILE_ATTRIBUTE_DATA data;

   zero(&data, sizeof(data));
   
   if(!::GetFileAttributesExW(psz, GetFileExInfoStandard, &data))
   {
      DWORD dwLastError = ::GetLastError();
      return INVALID_FILE_ATTRIBUTES;
   }

   return data.dwFileAttributes;

}



CLASS_DECL_c HANDLE FindFirstFile(const wchar_t * pwsz, WIN32_FIND_DATA * pdata)
{

   return FindFirstFileEx(pwsz, FindExInfoStandard, pdata, FindExSearchNameMatch, NULL, 0);

}


CLASS_DECL_c BOOL FileTimeToLocalFileTime(const FILETIME * lpFileTime, LPFILETIME lpLocalFileTime)
{

   SYSTEMTIME st;

   memset(&st, 0, sizeof(st));

   if(FileTimeToSystemTime(lpFileTime, &st))
      return FALSE;

   SYSTEMTIME stLocal;

   memset(&stLocal, 0, sizeof(stLocal));

   if(!SystemTimeToTzSpecificLocalTime(NULL, &st, &stLocal))
      return FALSE;

   if(!SystemTimeToFileTime(&stLocal, lpLocalFileTime))
      return FALSE;


   return TRUE;


}




CLASS_DECL_c HANDLE create_file(const char * lpcszFileName, dword dwDesiredAcces, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile)
{

   CREATEFILE2_EXTENDED_PARAMETERS ps;

   memset(&ps, 0, sizeof(ps));

   ps.dwSize                  = sizeof(ps);
   ps.dwFileAttributes        = dwFlagsAndAttributes;
   ps.lpSecurityAttributes    = lpSA;
   ps.hTemplateFile           = hTemplateFile;

   wstring wstr(lpcszFileName);

   return ::CreateFile2(wstr, dwDesiredAcces, dwShareMode, dwCreationDisposition, &ps);

}

CLASS_DECL_c bool close_handle(handle h)
{
   return ::CloseHandle(h) != FALSE;
}


CLASS_DECL_c ::Windows::Storage::StorageFolder ^ get_os_folder(const char * lpcszDirName)
{

   return wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(rtstr(lpcszDirName)));

}


CLASS_DECL_c ::Windows::Storage::StorageFile ^ get_os_file(const char * lpcszFileName, dword dwDesiredAcces, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile)
{

/*
   CREATE_ALWAYS
   2
   Creates a new file, always.
   If the specified file exists and is writable, the function overwrites the file, the function succeeds, and last-error code is set to ERROR_ALREADY_EXISTS (183).
   If the specified file does not exist and is a valid path, a new file is created, the function succeeds, and the last-error code is set to zero.
   For more information, see the Remarks section of this topic.

   CREATE_NEW
   1
   Creates a new file, only if it does not already exist.
   If the specified file exists, the function fails and the last-error code is set to ERROR_FILE_EXISTS (80).
   If the specified file does not exist and is a valid path to a writable location, a new file is created.

   OPEN_ALWAYS
   4
   Opens a file, always.
   If the specified file exists, the function succeeds and the last-error code is set to ERROR_ALREADY_EXISTS (183).
   If the specified file does not exist and is a valid path to a writable location, the function creates a file and the last-error code is set to zero.

   OPEN_EXISTING
   3
   Opens a file or device, only if it exists.
   If the specified file or device does not exist, the function fails and the last-error code is set to ERROR_FILE_NOT_FOUND (2).
   For more information about devices, see the Remarks section.
   
   TRUNCATE_EXISTING
   5
   Opens a file and truncates it so that its size is zero bytes, only if it exists.
   If the specified file does not exist, the function fails and the last-error code is set to ERROR_FILE_NOT_FOUND (2).
   The calling process must open the file with the GENERIC_WRITE bit set as part of the dwDesiredAccess parameter.

*/

   ::Windows::Storage::StorageFile ^ file = nullptr;

   ::Windows::Storage::StorageFolder ^ folder = get_os_folder(dir::name(lpcszFileName));

   if(folder == nullptr)
      return nullptr;

   ::Platform::String ^ strFileName = rtstr(file_title_dup(lpcszFileName));

   if(dwCreationDisposition == CREATE_ALWAYS)
   {

      auto optionNew = ::Windows::Storage::CreationCollisionOption::ReplaceExisting;
 
      file = wait(folder->CreateFileAsync(strFileName, optionNew));

   }
   else if(dwCreationDisposition == CREATE_NEW)
   {

      auto optionNew = ::Windows::Storage::CreationCollisionOption::FailIfExists;
 
      file = wait(folder->CreateFileAsync(strFileName, optionNew));

   }
   else if(dwCreationDisposition == OPEN_ALWAYS)
   {

      auto optionNew = ::Windows::Storage::CreationCollisionOption::OpenIfExists;
 
      file = wait(folder->CreateFileAsync(strFileName, optionNew));

   }
   else if(dwCreationDisposition == OPEN_EXISTING)
   {

      file = wait(folder->GetFileAsync(strFileName));

   }
   else if(dwCreationDisposition == TRUNCATE_EXISTING)
   {

      file = wait(folder->GetFileAsync(strFileName));
 
      ::Windows::Storage::StorageStreamTransaction ^ transaction = wait(file->OpenTransactedWriteAsync());

      transaction->Stream->Size = 0;

   }

   return file;


}


CLASS_DECL_c bool get_file_time(::Windows::Storage::StorageFile ^ file, LPFILETIME lpCreationTime, LPFILETIME lpItemTime, LPFILETIME lpLastWriteTime)
{

   if(lpCreationTime != NULL)
   {
      
      *lpCreationTime = (FILETIME &) file->DateCreated;

   }

   if(lpItemTime != NULL || lpLastWriteTime != NULL)
   {

      ::Windows::Storage::FileProperties::BasicProperties ^ properties = wait(file->GetBasicPropertiesAsync());

      if(lpItemTime != NULL)
      {
         *lpItemTime = (FILETIME &) properties->ItemDate;
      }

      if(lpLastWriteTime != NULL)
      {
         *lpLastWriteTime = (FILETIME &) properties->DateModified;
      }

   }

   return true;

}




vsstring get_sys_temp_path()
{

   return vsstring(::Windows::Storage::ApplicationData::Current->TemporaryFolder->Path->Begin());

}

