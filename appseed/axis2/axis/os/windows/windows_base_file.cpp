#include "framework.h"
#include <io.h>




BEGIN_EXTERN_C

int_bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinstance, UINT nID, LPCTSTR lpcszType)
{

   HRSRC hrsrc = FindResource(hinstance, MAKEINTRESOURCE(nID), lpcszType);
   HGLOBAL hglobalResource;
   uint32_t dwResourseSize;
   int_bool bOk;
   UINT FAR* pResource;
   HANDLE hfile;

   if(hrsrc == NULL)
      return FALSE;

   hglobalResource = LoadResource(hinstance, hrsrc);

   if(hglobalResource == NULL)
      return FALSE;

   dwResourseSize = SizeofResource(hinstance, hrsrc);

   if(hglobalResource != NULL)
   {

      bOk = FALSE;

      pResource = (UINT FAR*) LockResource(hglobalResource);

      ::dir_mk(dir::name(pszFile));

      hfile = create_file(pszFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

      if(hfile != INVALID_HANDLE_VALUE)
      {
         DWORD dwWritten = 0;
         WriteFile(hfile, pResource, dwResourseSize, &dwWritten, NULL);
         CloseHandle(hfile);
         bOk = dwWritten == dwResourseSize;
      }

      FreeResource(hglobalResource);

      return bOk;
   }

   return FALSE;

}


int_bool file_exists_dup(const char * path1)
{

   wstring wstr;

   wstr.alloc(strlen_dup(path1) + 256);

   wcscat(wstr, L"\\\\?\\");

   utf8_to_utf16((wchar_t *) wstr + wcslen(wstr), path1);

   wstr.set_length(wcslen(wstr));

   wchar_t * pwsz = (wchar_t *) wstr;
   while(*pwsz != L'\0')
   {
      if(*pwsz == '/')
      {
         *pwsz = '\\';
      }
      pwsz++;
   }

   uint32_t dwFileAttributes = GetFileAttributesW(wstr);

   if(dwFileAttributes == INVALID_FILE_ATTRIBUTES || (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
      return FALSE;

   return true;

}



int_bool file_put_contents_dup(const char * path, const char * contents, count len)
{

   ::dir_mk(dir::name(path));

   wstring wstr(path);

   HANDLE hfile = create_file(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return FALSE;

   count dwWrite;

   if(len < 0)
      dwWrite = strlen_dup(contents);
   else
      dwWrite = len;

   DWORD dwWritten = 0;

   int_bool bOk = WriteFile(hfile, contents, (uint32_t) dwWrite, &dwWritten, NULL) != FALSE;

   CloseHandle(hfile);

   return dwWrite == dwWritten && bOk != FALSE;


}


uint64_t file_length_dup(const char * path)
{

   HANDLE hfile = create_file(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return 0;

   uint64_t ui = fsize_dup(hfile);

   CloseHandle(hfile);

   return ui;

}











int_bool file_ftd_dup(const char * pszDir, const char * pszFile)
{

   HANDLE hfile1 = NULL;

   HANDLE hfile2 = NULL;

   wstring wstr(pszFile);

   hfile1 = create_file(pszFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(hfile1 == INVALID_HANDLE_VALUE)
      return FALSE;

   string strVersion;


   file_read_gen_string_dup(hfile1, NULL, strVersion);

   int32_t n;

   string strRelative;

   string strMd5;

   string strMd5New;

   int32_t iBufSize = 1024 * 1024;

   uchar * buf = (uchar *)  memory_alloc(iBufSize);

   int32_t iLen;
   md5::md5 ctx;
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
         string strPath = dir::path(pszDir, strRelative);
         ::dir_mk(dir::name(strPath));
         hfile2 = create_file(strPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
         if(hfile2 == INVALID_HANDLE_VALUE)
            return FALSE;
         file_read_n_number_dup(hfile1, &ctx, iLen);
         while(iLen > 0)
         {
            if(!ReadFile(hfile1, buf, min(iBufSize, iLen), &dwRead, NULL))
               break;
            if(dwRead == 0)
               break;
            WriteFile(hfile2, buf, dwRead, &dwWritten, NULL);
            ctx.update(buf, dwRead);
            iLen -= dwRead;
         }
         CloseHandle(hfile2);
         hfile2 = NULL;
         ctx.finalize();

         strMd5New.clear();
         string strFormat;
         strMd5New = ctx.to_string();
         if(strMd5.CompareNoCase(strMd5New) != 0)
            return FALSE;
      }
   }
   CloseHandle(hfile1);
   if(hfile2 != INVALID_HANDLE_VALUE)
      CloseHandle(hfile2);
   return true;
}













int_bool file_copy_dup(const char * pszNew, const char * pszSrc, int_bool bOverwrite)
{

   wstring wstrNew(pszNew);

   wstring wstrSrc(pszSrc);

   return CopyFileW(wstrSrc, wstrNew, bOverwrite ? FALSE : TRUE) ? true : FALSE;

}

handle create_file(const char * lpcszFileName, dword dwDesiredAccess, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile)
{

   return CreateFileW(wstring(lpcszFileName), dwDesiredAccess, dwShareMode, lpSA, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

}



int_bool file_is_equal_path(const char * psz1, const char * psz2)
{

   const int32_t iBufSize = MAX_PATH * 8;
   wstring pwsz1 = ::str::international::utf8_to_unicode(psz1);
   wstring pwsz2 = ::str::international::utf8_to_unicode(psz2);
   wchar_t * pwszFile1;
   wchar_t * pwszFile2;
   wchar_t * pwszPath1 = new wchar_t[iBufSize];
   wchar_t * pwszPath2 = new wchar_t[iBufSize];
   int32_t iCmp = -1;
   if(GetFullPathNameW(pwsz1, iBufSize, pwszPath1, &pwszFile1))
   {
      if(GetFullPathNameW(pwsz2, iBufSize, pwszPath2, &pwszFile2))
      {
         string p1 = ::str::international::unicode_to_utf8(pwszPath1);
         string p2 = ::str::international::unicode_to_utf8(pwszPath2);
         iCmp = stricmp_dup(p1, p2);
      }
   }
   delete pwszPath1;
   delete pwszPath2;
   return iCmp == 0;

}



END_EXTERN_C

























int_bool file_copy_dup(const char * pszNew, const char * pszSrc, bool bOverwrite)
{

   wstring wstrNew(pszNew);

   wstring wstrSrc(pszSrc);

   return ::CopyFileW(wstrSrc, wstrNew, bOverwrite ? FALSE : TRUE) ? true : false;

}






string file_get_mozilla_firefox_plugin_container_path()
{

   string strPath;
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

      string strDir;

      strDir = ::str::international::unicode_to_utf8(wstrDir);

      strPath = dir::path(strDir, "plugin-container.exe");
   }

ret1:
   ::RegCloseKey(hkeyMozillaFirefox);
   return strPath;

}






string get_sys_temp_path()
{

   wchar_t  wsz[MAX_PATH * 4];

   wsz[GetTempPathW(sizeof(wsz) / sizeof(wsz[0]), wsz)] = L'\0';

   return string(wsz);

}



string file_as_string_dup(const char * path)
{

   string str;

   HANDLE hfile = ::create_file(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return "";

   DWORD dwSizeHigh;

   DWORD dwSize = ::GetFileSize(hfile, &dwSizeHigh);

   LPSTR lpsz = str.GetBufferSetLength(dwSize);

   DWORD dwRead;

   ::ReadFile(hfile, lpsz, dwSize, &dwRead, NULL);

   lpsz[dwSize] = '\0';

   str.ReleaseBuffer(dwSize);

   ::CloseHandle(hfile);

   return str;


}


bool file_get_memory_dup(::primitive::memory_base & memory, const char * path)
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

   ::ReadFile(hfile, memory.get_data(), (uint32_t) memory.get_size(), &dwRead, NULL);

   ::CloseHandle(hfile);

   return true;

}



string file_module_path_dup()
{

   char path[MAX_PATH * 4];

   if(!GetModuleFileName(NULL, path, sizeof(path)))
      return "";

   return path;

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

void file_read_gen_string_dup(HANDLE hfile, ::md5::md5 * pctx, string & str)
{
   int32_t iLen;
   file_read_n_number_dup(hfile, pctx, iLen);
   LPSTR lpsz = (LPSTR) memory_alloc(iLen + 1);
   DWORD dwRead;
   ReadFile(hfile, lpsz, iLen, &dwRead, NULL);
   if(pctx != NULL)
   {
      pctx->update(lpsz, iLen);
   }
   lpsz[iLen] = '\0';
   str = lpsz;
   memory_free_dbg(lpsz, 0);
}


bool PrintModules(string & strImage, uint32_t processID, const char * pszDll )
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

   char * szImage = (char *) memory_alloc(iImageSize);

   GetModuleFileNameEx(hProcess, NULL, szImage, iImageSize);

   strImage = szImage;

   memory_free_dbg(szImage, 0);

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

void dll_processes(raw_uint_array & dwa, string_array & straProcesses, const char * pszDll)
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

   string strImage;

   for(ui = 0; ui < cProcesses; ui++)
   {

      if(PrintModules(strImage, aProcesses[ui], pszDll))
      {

         straProcesses.add(strImage); // there may processes with different pids but same image
         dwa.add(aProcesses[ui]);

      }

   }

   delete aProcesses;

}





#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
struct PROCESS_INFO_t
{
    string csProcess;
    uint32_t dwImageListIndex;
};


#if !defined(LINUX) && !defined(MACOS) && !defined(METROWIN) && !defined(ANDROID)

#include <Tlhelp32.h>
#include <Psapi.h>


//void EnumerateLoadedModules( string& csPath, OF_CALLBACK CallBackProc, uint_ptr pUserContext );
//void EnumerateOpenedFiles(string& csPath,OF_CALLBACK CallBackProc,uint_ptr pUserContext,HANDLE hDriver,GetFinalPathNameByHandleDef pGetFinalPathNameByHandle);

const LPCTSTR DRV_DOS_NAME = _T("\\\\.\\ListFileDrv");
const LPCTSTR DRV_NAME = _T("ListOpenedFileDrv");
const LPCTSTR DRV_FILE_NAME = _T("ListOpenedFileDrv.sys");

#define DRIVER_FILE_NAME_32 _T("\\ListOpenedFileDrv_32.sys")
#define DRIVER_FILE_NAME_64 _T("\\ListOpenedFileDrv_64.sys")


// This Function install the driver and starts it
HANDLE OnlyGetDrv()
{


        HMODULE hModule = GetModuleHandle(_T("core.dll"));
        if( !hModule )
        {
            OutputDebugStringW( L"GetModuleHandle(_T(\"core.dll\")); failed" );
            return 0;
        }
        string csFilePath;
        LPTSTR lpPath = csFilePath.GetBuffer( MAX_PATH );
        GetModuleFileName( hModule,lpPath , MAX_PATH );
        PathRemoveFileSpec( lpPath );
        csFilePath.ReleaseBuffer();
        if(IsWow64())
        {
         csFilePath += DRIVER_FILE_NAME_64;
        }
        else
        {
           csFilePath += DRIVER_FILE_NAME_32;
        }

        if( !PathFileExists( csFilePath ))
        {
           simple_message_box(NULL,"Cannot find driver " + csFilePath,"Cannot find driver " + csFilePath,MB_OK);
            return 0;
        }



	// Delete the temp file...
	//DeleteFile( csPath );
	HANDLE hFile = CreateFile( DRV_DOS_NAME, GENERIC_READ|GENERIC_WRITE,
								FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
								OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0 );
	return hFile;

}



#ifndef METROWIN

typedef struct _SYSTEM_HANDLE_INFORMATION
{
    uint32_t         dwCount;
    SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION, **PPSYSTEM_HANDLE_INFORMATION;

typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemHandleInformation = 0X10,
} SYSTEM_INFORMATION_CLASS;

#endif

typedef NTSTATUS ( WINAPI *PNtQuerySystemInformation)
				 ( IN	SYSTEM_INFORMATION_CLASS SystemInformationClass,
				   OUT	PVOID					 SystemInformation,
				   IN	ULONG					 SystemInformationLength,
				   OUT	PULONG					 ReturnLength OPTIONAL );

UINT g_CurrentIndex = 0;
struct THREAD_PARAMS
{
	PSYSTEM_HANDLE_INFORMATION pSysHandleInformation;
	GetFinalPathNameByHandleDef pGetFinalPathNameByHandle;
	LPWSTR lpPath;
	int32_t nFileType;
	HANDLE hStartEvent;
	HANDLE hFinishedEvent;
	bool bStatus;
};

uint32_t ThreadProc(void * lParam)
{
	THREAD_PARAMS* pThreadParam = (THREAD_PARAMS*)lParam;

   FILE_NAME_INFO * pinfo = (FILE_NAME_INFO *)new BYTE[MAX_PATH * 8];

	GetFinalPathNameByHandleDef pGetFinalPathNameByHandle = pThreadParam->pGetFinalPathNameByHandle;
	for( g_CurrentIndex; g_CurrentIndex < pThreadParam->pSysHandleInformation->dwCount;  )
	{

		WaitForSingleObject( pThreadParam->hStartEvent, INFINITE );
		ResetEvent( pThreadParam->hStartEvent );
		pThreadParam->bStatus = false;
		SYSTEM_HANDLE& sh = pThreadParam->pSysHandleInformation->Handles[g_CurrentIndex];
		g_CurrentIndex++;
		HANDLE hDup = (HANDLE)sh.wValue;
		HANDLE hProcess = OpenProcess( PROCESS_DUP_HANDLE , FALSE, sh.dwProcessId );
		if( hProcess )
		{
			bool b = DuplicateHandle( hProcess, (HANDLE)sh.wValue, GetCurrentProcess(), &hDup, 0, FALSE, DUPLICATE_SAME_ACCESS ) != FALSE;
			if( !b )
			{
				hDup = (HANDLE)sh.wValue;
			}
			CloseHandle( hProcess );
		}
		//uint32_t dwRet = pGetFinalPathNameByHandle( hDup, pThreadParam->lpPath, MAX_PATH, 0 );
      //uint32_t dwRet = GetFileInformationByHandleEx(hDup, FileNameInfo, pinfo, MAX_PATH * 8);
      uint32_t dwRet = GetFinalPathNameByHandleW( hDup, pThreadParam->lpPath, MAX_PATH, 0 );
      //wcsncpy(pThreadParam->lpPath, pinfo->FileName, pinfo->FileNameLength);
		if( hDup && (hDup != (HANDLE)sh.wValue))
		{
			CloseHandle( hDup );
		}
		if(dwRet)
		{
			pThreadParam->bStatus = true;
		}
		SetEvent( pThreadParam->hFinishedEvent );

	}
   delete[] (BYTE *) pinfo;
	return 0;
}




#endif // LINUX





int ftruncate(int file, int64_t len)
{
  return _chsize_s (file, len);
}





int_bool ensure_file_size(int32_t fd, size_t iSize)
{

   if(ftruncate(fd, iSize) == -1)
      return 0;

   return 1;

}

int_bool ensure_file_size(FILE * file, size_t iSize)
{

   return ensure_file_size(fileno(file), iSize);

}


int_bool ensure_file_size(HANDLE h, uint64_t iSize)
{

   DWORD dwHi;

   DWORD dwLo = GetFileSize(h, &dwHi);

   if(((uint64_t) dwLo | ((uint64_t)dwHi << 32)) != iSize)
   {

      LONG l = (iSize >> 32) & 0xffffffff;

      if(SetFilePointer(h, iSize & 0xffffffff, &l, SEEK_SET) != (DWORD) (iSize & 0xffffffff))
         return false;

      if(l != ((iSize >> 32) & 0xffffffff))
         return false;

      if(!SetEndOfFile(h))
         return false;

   }


   return 1;

}



int_bool close_handle(handle h)
{

   return CloseHandle(h) != FALSE;

}






























int_bool file_set_length(const char * pszName, size_t iSize)
{

   wstring wstr(pszName);

   HANDLE h = ::CreateFileW(wstr, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(h == INVALID_HANDLE_VALUE)
      return false;

   if(!ensure_file_size(h, iSize))
   {

      ::CloseHandle(h);

      return false;

   }

   ::CloseHandle(h);

   return true;

}
