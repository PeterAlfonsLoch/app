#include "framework.h"


void file_read_ex1_string_dup(HANDLE hfile, ::md5::md5 * pctx, string & str);


CLASS_DECL_ca void ensure_file_size(HANDLE h, int64_t iSize)
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

CLASS_DECL_ca DWORD SetFilePointer(HANDLE h, LONG lMove, PLONG plHi, DWORD dwMeth)
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

CLASS_DECL_ca DWORD GetFileSize(HANDLE h, LPDWORD lpdwHi)
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


CLASS_DECL_ca DWORD GetFileAttributes(const wchar_t * psz)
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



CLASS_DECL_ca HANDLE FindFirstFile(const wchar_t * pwsz, WIN32_FIND_DATA * pdata)
{

   return FindFirstFileEx(pwsz, FindExInfoStandard, pdata, FindExSearchNameMatch, NULL, 0);

}


CLASS_DECL_ca BOOL FileTimeToLocalFileTime(const FILETIME * lpFileTime, LPFILETIME lpLocalFileTime)
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




CLASS_DECL_ca HANDLE create_file(const char * lpcszFileName, dword dwDesiredAcces, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile)
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

CLASS_DECL_ca bool close_handle(handle h)
{
   return ::CloseHandle(h) != FALSE;
}


CLASS_DECL_ca ::Windows::Storage::StorageFolder ^ get_os_folder(const char * lpcszDirName)
{

   return wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(string(lpcszDirName)));

}


CLASS_DECL_ca ::Windows::Storage::StorageFile ^ get_os_file(const char * lpcszFileName, dword dwDesiredAcces, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile)
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

   ::Platform::String ^ strFileName = file_title_dup(lpcszFileName);

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


CLASS_DECL_ca bool get_file_time(::Windows::Storage::StorageFile ^ file, LPFILETIME lpCreationTime, LPFILETIME lpItemTime, LPFILETIME lpLastWriteTime)
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




string get_sys_temp_path()
{

   return ::Windows::Storage::ApplicationData::Current->TemporaryFolder->Path;

}



bool file_exists_dup(const char * path1)
{

   string str(path1);
   str.replace("/", "\\");
   wstring wstr(L"\\\\?\\");
   wstr = wstr + wstring(str);
   uint32_t dwFileAttributes = ::GetFileAttributesW(wstr);
   if(dwFileAttributes != INVALID_FILE_ATTRIBUTES && (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
      return true;
   else
      return false;

}



bool file_put_contents_dup(const char * path, const char * contents, ::count len)
{

   dir::mk(dir::name(path));

   wstring wstr(path);

   

   HANDLE hfile = ::create_file(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   if(hfile == INVALID_HANDLE_VALUE)
      return false;
   count dwWrite;
   if(len < 0)
      dwWrite = strlen_dup(contents);
   else
      dwWrite = len;
   DWORD dwWritten = 0;
   bool bOk = ::WriteFile(hfile, contents, (uint32_t) dwWrite, &dwWritten, NULL) != FALSE;
   ::CloseHandle(hfile);
   return dwWrite == dwWritten && bOk != FALSE;

}




string file_as_string_dup(const char * path)
{
   
   string str;

   HANDLE hfile = ::create_file(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return "";

   DWORD dwSizeHigh;

   uint32_t dwSize = ::GetFileSize(hfile, &dwSizeHigh);

   str.alloc(dwSize);

   DWORD dwRead;

   ::ReadFile(hfile, str, dwSize, &dwRead, NULL);

   str.m_psz[dwSize] = '\0';

   ::CloseHandle(hfile);

   return str;

}

bool file_get_memory_dup(simple_memory & memory, const char * path)
{

   memory.allocate(0);

   HANDLE hfile = ::create_file(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return false;

   DWORD dwSizeHigh;

   ::count  count = ::GetFileSize(hfile, &dwSizeHigh);

   memory.allocate(count);

   DWORD dwRead;

   ::ReadFile(hfile, memory.m_psz, (uint32_t) memory.m_iSize, &dwRead, NULL);

   ::CloseHandle(hfile);

   return true;


}


bool get_temp_file_name_template(char * szRet, ::count iBufferSize, const char * pszName, const char * pszExtension, const char * pszTemplate)
{

   string str(::Windows::Storage::ApplicationData::Current->TemporaryFolder->Path);

   char bufTime[30];

   char bufItem[30];

   char buf[30];

   if(!str_ends_dup(str, "/") || !str_ends_dup(str, "\\"))
   {
      str += "\\";
   }

   SYSTEMTIME st;
   memset_dup(&st, 0, sizeof(st));

   GetSystemTime(&st);

   itoa_dup(bufItem, st.wYear, 10);
   zero_pad(bufItem, 4);
   strcpy_dup(bufTime, bufItem);

   itoa_dup(bufItem, st.wMonth, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, "-");
   strcat_dup(bufTime, bufItem);

   itoa_dup(bufItem, st.wDay, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, "-");
   strcat_dup(bufTime, bufItem);

   itoa_dup(bufItem, st.wHour, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, " ");
   strcat_dup(bufTime, bufItem);

   itoa_dup(bufItem, st.wMinute, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, "-");
   strcat_dup(bufTime, bufItem);

   itoa_dup(bufItem, st.wSecond, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, "-");
   strcat_dup(bufTime, bufItem);

   for(int32_t i = 0; i < (1024 * 1024); i++)
   {
      strcpy_dup(szRet, str);
      {
         strcat_dup(szRet, bufTime);
         strcat_dup(szRet, "-");
      }
      {
         sprint_hex(buf, i + 1);
         strcat_dup(szRet, buf);
         strcat_dup(szRet, "\\");
      }
      strcat_dup(szRet, pszName);
      //if(i >= 0)
      //if(i > 0)
      strcat_dup(szRet, ".");
      strcat_dup(szRet, pszExtension);
      if(pszTemplate != NULL)
      {
         if(is_file_ok(szRet, pszTemplate))
            return true;
      }
      if(file_exists_dup(szRet))
      {
         if(::DeleteFileA(szRet))
            return true;
      }
      else
      {
         return true;
      }
   }
   return false;

}





uint64_t file_length_dup(const char * path)
{

   HANDLE hfile = ::create_file(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return 0;

   uint64_t uiSize = fsize_dup(hfile);

   ::CloseHandle(hfile);

   return uiSize;

}



string file_module_path_dup()
{

   return "/ca2/stage";

}







bool file_ftd_dup(const char * pszDir, const char * pszFile)
{

   HANDLE hfile1 = NULL;
   HANDLE hfile2 = NULL;
   wstring wstr(pszFile);
   hfile1 = ::create_file(pszFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   if(hfile1 == INVALID_HANDLE_VALUE)
      return false;

   string strVersion;


   file_read_ex1_string_dup(hfile1, NULL, strVersion);
   int32_t n;
   string strRelative;
   string strMd5;
   string strMd5New;
   int32_t iBufSize = 1024 * 1024;
   uchar * buf = (uchar *)  _ca_alloc(iBufSize);
   int32_t iLen;
   ::md5::md5 ctx;
   DWORD dwRead;
   DWORD dwWritten;
   if(strVersion == "fileset v1")
   {
      while(true)
      {
         file_read_n_number_dup(hfile1, NULL, n);
         if(n == 2)
            break;
         file_read_ex1_string_dup(hfile1, NULL, strMd5);
         ctx.initialize();
         file_read_ex1_string_dup(hfile1, &ctx, strRelative);
         string strPath = dir::path(pszDir, strRelative);
         dir::mk(dir::name(strPath));
         hfile2 = ::create_file(strPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
         if(hfile2 == INVALID_HANDLE_VALUE)
            return false;
         file_read_n_number_dup(hfile1, &ctx, iLen);
         while(iLen > 0)
         {
            if(!::ReadFile(hfile1, buf, min(iBufSize, iLen), &dwRead, NULL))
               break;
            if(dwRead == 0)
               break;
            ::WriteFile(hfile2, buf, dwRead, &dwWritten, NULL);
            ctx.update(buf, dwRead);
            iLen -= dwRead;
         }
         ::CloseHandle(hfile2);
         hfile2 = NULL;
         ctx.finalize();

         strMd5New.clear();
         string strFormat;
         strMd5New = ctx.to_string();
         if(strMd5.CompareNoCase(strMd5New) != 0)
            return false;
      }
   }
   ::CloseHandle(hfile1);
   if(hfile2 != INVALID_HANDLE_VALUE)
      ::CloseHandle(hfile2);
   return true;
}


void file_read_n_number_dup(HANDLE hfile, ::md5::md5 * pctx, int32_t & iNumber)
{
   string str;
   char ch;
   DWORD dwRead;
   while(ReadFile(hfile, &ch, 1, &dwRead, NULL) && dwRead == 1)
   {
      if(ch >= '0' && ch <= '9')
         str += ch;
      else
         break;
      if(pctx != NULL)
      {
         pctx->update(&ch, 1);
      }
   }
   if(ch != 'n')
      return;
   if(pctx != NULL)
   {
      pctx->update(&ch, 1);
   }
   iNumber = atoi_dup(str);
}

void file_read_ex1_string_dup(HANDLE hfile, ::md5::md5 * pctx, string & str)
{
   int32_t iLen;
   file_read_n_number_dup(hfile, pctx, iLen);
   LPSTR lpsz = (LPSTR) _ca_alloc(iLen + 1);
   DWORD dwRead;
   ReadFile(hfile, lpsz, iLen, &dwRead, NULL);
   if(pctx != NULL)
   {
      pctx->update(lpsz, iLen);
   }
   lpsz[iLen] = '\0';
   str = lpsz;
   _ca_free(lpsz, 0);
}

























bool file_copy_dup(const char * pszNew, const char * pszSrc, bool bOverwrite)
{

    ::Windows::Storage::IStorageFolder ^ folderNew = wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(dir::name(pszNew)));

    auto optionNew = ::Windows::Storage::CreationCollisionOption::ReplaceExisting;
 
    // create target file 
    ::Windows::Storage::IStorageFile ^ fileNew = wait(folderNew->CreateFileAsync(file_title_dup(pszNew), optionNew));

    if(fileNew == nullptr)
       return false;

    ::Windows::Storage::IStorageFolder ^ folderSrc = wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(dir::name(pszSrc)));

    // create source file 
    ::Windows::Storage::IStorageFile ^ fileSrc = wait(folderSrc->GetFileAsync(file_title_dup(pszNew)));

    if(fileSrc == nullptr)
       return false;

    wait(fileSrc->CopyAndReplaceAsync(fileNew));
 
    return true;

}





CLASS_DECL_ca bool file_is_equal_path(const char * psz1, const char * psz2)
{

   return normalize_path(psz1).CompareNoCase(normalize_path(psz2)) == 0;

}


CLASS_DECL_ca string file_get_mozilla_firefox_plugin_container_path()
{

   throw " todo ";
   
   return "";
   
}






