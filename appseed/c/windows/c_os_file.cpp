#include "framework.h"


CLASS_DECL_c void ensure_file_size(HANDLE h, uint64_t iSize)
{

   DWORD dwHi;

   DWORD dwLo = ::GetFileSize(h, &dwHi);

   if(((uint64_t) dwLo | ((uint64_t)dwHi << 32)) != iSize)
   {

      LONG l = (iSize >> 32) & 0xffffffff;

      ::SetFilePointer(h, iSize & 0xffffffff, &l, SEEK_SET);

      SetEndOfFile(h);

   }

}



CLASS_DECL_c handle create_file(const char * lpcszFileName, dword dwDesiredAccess, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile)
{

   return CreateFileW(wstring(lpcszFileName), dwDesiredAccess, dwShareMode, lpSA, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

}


CLASS_DECL_c bool close_handle(handle h)
{

   return ::CloseHandle(h) != FALSE;

}



CLASS_DECL_c vsstring get_sys_temp_path()
{

   wchar_t  wsz[MAX_PATH * 4];

   wsz[GetTempPathW(sizeof(wsz) / sizeof(wsz[0]), wsz)] = L'\0';

   return vsstring(wsz);

}


bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinstance, UINT nID, LPCTSTR lpcszType)
{

   HRSRC hrsrc = ::FindResource(hinstance, MAKEINTRESOURCE(nID), lpcszType);

   if(hrsrc == NULL)
      return false;

   HGLOBAL hglobalResource = ::LoadResource(hinstance, hrsrc);

   if(hglobalResource == NULL)
      return false;

   uint32_t dwResourseSize = ::SizeofResource(hinstance, hrsrc);

   if(hglobalResource != NULL)
   {
      bool bOk = false;

      UINT FAR* pResource = (UINT FAR*) ::LockResource(hglobalResource);

      dir::mk(dir::name(pszFile));

      HANDLE hfile = ::create_file(pszFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

      if(hfile != INVALID_HANDLE_VALUE)
      {
         DWORD dwWritten = 0;
         ::WriteFile(hfile, pResource, dwResourseSize, &dwWritten, NULL);
         ::CloseHandle(hfile);
         bOk = dwWritten == dwResourseSize;
      }

      ::FreeResource(hglobalResource);

      return bOk;
   }

   return false;

}


bool file_exists_dup(const char * path1)
{

   vsstring str(path1);

   str.replace("/", "\\");

   wstring wstr(L"\\\\?\\");

   wstr = wstr + wstring(str);

   uint32_t dwFileAttributes = ::GetFileAttributesW(wstr);

   if(dwFileAttributes == INVALID_FILE_ATTRIBUTES || (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
      return false;
   
   return true;

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




vsstring file_as_string_dup(const char * path)
{

   vsstring str;

   HANDLE hfile = ::create_file(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return "";

   DWORD dwSizeHigh;

   DWORD dwSize = ::GetFileSize(hfile, &dwSizeHigh);

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

   uint64_t uiSize = fsize_dup(hfile);

   if(uiSize > ((::count) -1))
   {

      ::CloseHandle(hfile);

      return false;

   }

   memory.allocate((::count) uiSize);

   DWORD dwRead;

   ::ReadFile(hfile, memory.m_psz, (uint32_t) memory.m_iSize, &dwRead, NULL);

   ::CloseHandle(hfile);

   return true;

}


bool get_temp_file_name_template(char * szRet, ::count iBufferSize, const char * pszName, const char * pszExtension, const char * pszTemplate)
{

   char lpPathBuffer[MAX_PATH * 4];

   uint32_t dwRetVal = GetTempPath(sizeof(lpPathBuffer), lpPathBuffer);

   if (dwRetVal > sizeof(lpPathBuffer) || (dwRetVal == 0))
   {

      return false;

   }

   char bufTime[30];

   char bufItem[30];

   char buf[30];

   size_t iLen= strlen_dup(lpPathBuffer);

   if(!(lpPathBuffer[iLen - 1] == '/' || lpPathBuffer[iLen - 1] == '\\'))
   {

      lpPathBuffer[iLen] = '\\';

      lpPathBuffer[iLen+1] = '\0';

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
      strcpy_dup(szRet, lpPathBuffer);
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

   uint64_t ui = ::fsize_dup(hfile);

   ::CloseHandle(hfile);

   return ui;

}





vsstring file_module_path_dup()
{

   char path[MAX_PATH * 4];

   if(!GetModuleFileName(NULL, path, sizeof(path)))
      return "";

   return path;

}







bool file_ftd_dup(const char * pszDir, const char * pszFile)
{

   HANDLE hfile1 = NULL;
   
   HANDLE hfile2 = NULL;
   
   wstring wstr(pszFile);

   hfile1 = ::create_file(pszFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   
   if(hfile1 == INVALID_HANDLE_VALUE)
      return false;

   vsstring strVersion;


   file_read_gen_string_dup(hfile1, NULL, strVersion);
   
   int32_t n;
   
   vsstring strRelative;
   
   vsstring strMd5;
   
   vsstring strMd5New;
   
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
         file_read_gen_string_dup(hfile1, NULL, strMd5);
         ctx.initialize();
         file_read_gen_string_dup(hfile1, &ctx, strRelative);
         vsstring strPath = dir::path(pszDir, strRelative);
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
         vsstring strFormat;
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

   vsstring str;

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

void file_read_gen_string_dup(HANDLE hfile, ::md5::md5 * pctx, vsstring & str)
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
























bool PrintModules(vsstring & strImage, uint32_t processID, const char * pszDll )
{

   HANDLE hProcess;

   DWORD cbNeeded;

   uint32_t ui;

   hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

   if (NULL == hProcess)
      return false;

   const int32_t iMaxModuleCount = 1024;

   HMODULE * hMods = new HMODULE[iMaxModuleCount];

   const int32_t iImageSize = MAX_PATH * 8;

   char * szImage = (char *) _ca_alloc(iImageSize);

   GetModuleFileNameEx(hProcess, NULL, szImage, iImageSize);

   strImage = szImage;

   _ca_free(szImage, 0);

   bool bFound = false;

   if(EnumProcessModules(hProcess, hMods, sizeof(HMODULE) * iMaxModuleCount, &cbNeeded))
   {

      for( ui = 0; ui < (cbNeeded / sizeof(HMODULE)); ui++)
      {

         TCHAR szModName[MAX_PATH];

         // Get the full path to the module's file.

         if(GetModuleFileNameEx( hProcess, hMods[ui], szModName, sizeof(szModName) / sizeof(TCHAR)))
         {

            if(!stricmp_dup(szModName, pszDll))
            {

               bFound = true;

               break;

            }

         }

      }

   }

   delete hMods;

   CloseHandle( hProcess );

   return bFound;

}

void dll_processes(simple_uint_array & dwa, stra_dup & straProcesses, const char * pszDll)
{
   // Get the list of process identifiers.

   DWORD * aProcesses = new DWORD[1024 * 8];

   DWORD cbNeeded, cProcesses;

   uint32_t ui;

   if ( !EnumProcesses( aProcesses, 124 * 8 * sizeof(DWORD), &cbNeeded ) )
   {
      delete aProcesses;
      return;
   }

   // Calculate how many process identifiers were returned.

   cProcesses = cbNeeded / sizeof(DWORD);

   // Print the name of the modules for each process.

   vsstring strImage;

   for(ui = 0; ui < cProcesses; ui++)
   {

      if(PrintModules(strImage, aProcesses[ui], pszDll))
      {

         straProcesses.add_unique_ci(strImage);

         dwa.add(aProcesses[ui]);

      }

   }

   delete aProcesses;

}


bool file_copy_dup(const char * pszNew, const char * pszSrc, bool bOverwrite)
{

   wstring wstrNew(pszNew);

   wstring wstrSrc(pszSrc);

   return ::CopyFileW(wstrSrc, wstrNew, bOverwrite ? FALSE : TRUE) ? true : false;

}





CLASS_DECL_c bool file_is_equal_path(const char * psz1, const char * psz2)
{

   const int32_t iBufSize = MAX_PATH * 8;
   const wchar_t * pwsz1 = utf8_to_16(psz1);
   const wchar_t * pwsz2 = utf8_to_16(psz2);
   wchar_t * pwszFile1;
   wchar_t * pwszFile2;
   wchar_t * pwszPath1 = new wchar_t[iBufSize];
   wchar_t * pwszPath2 = new wchar_t[iBufSize];
   int32_t iCmp = -1;
   if(GetFullPathNameW(pwsz1, iBufSize, pwszPath1, &pwszFile1))
   {
      if(GetFullPathNameW(pwsz2, iBufSize, pwszPath2, &pwszFile2))
      {
         const char * p1 = utf16_to_8(pwszPath1);
         const char * p2 = utf16_to_8(pwszPath2);
         iCmp = stricmp_dup(p1, p2);
         _ca_free((void *) p1, 0);
         _ca_free((void *) p2, 0);
      }
   }
   _ca_free((void *) pwsz1, 0);
   _ca_free((void *) pwsz2, 0);
   delete pwszPath1;
   delete pwszPath2;
   return iCmp == 0;

}


CLASS_DECL_c vsstring file_get_mozilla_firefox_plugin_container_path()
{

   vsstring strPath;
   HKEY hkeyMozillaFirefox;

   if(::RegOpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox", &hkeyMozillaFirefox) != ERROR_SUCCESS)
      return "";
   {

      DWORD dwType;
      DWORD dwData;
      dwData = 0;
      if(::WinRegGetValueW(hkeyMozillaFirefox, NULL, L"CurrentVersion", RRF_RT_REG_SZ, &dwType, NULL, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }

      wstring wstrVersion;
      wstrVersion.alloc(dwData);
      if(::WinRegGetValueW(hkeyMozillaFirefox, NULL, L"CurrentVersion", RRF_RT_REG_SZ, &dwType, wstrVersion, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }
      wstrVersion.release_buffer();

      wstring wstrMainSubKey = wstrVersion + L"\\Main";
      dwData = 0;

      if(::WinRegGetValueW(hkeyMozillaFirefox, wstrMainSubKey, L"Install Directory", RRF_RT_REG_SZ, &dwType, NULL, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }

      wstring wstrDir;
      wstrDir.alloc(dwData);
      if(::WinRegGetValueW(hkeyMozillaFirefox, wstrMainSubKey, L"Install Directory", RRF_RT_REG_SZ, &dwType, wstrDir, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }
      wstrDir.release_buffer();

      vsstring strDir;

      strDir.attach(utf16_to_8(wstrDir));

      strPath = dir::path(strDir, "plugin-container.exe");
   }

ret1:
   ::RegCloseKey(hkeyMozillaFirefox);
   return strPath;

}




