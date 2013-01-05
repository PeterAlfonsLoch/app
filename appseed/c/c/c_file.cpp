#include "framework.h"


CLASS_DECL_c void sprint_hex(char * sz, int32_t iValue)
{
   int32_t i = 8;
   sz[i] = '\0';
   i--;
   for(; i >= 0; i--)
   {
      sz[i] = to_hi_hex_char((iValue >> (4 * (7 - i))) &  0xf);
   }
}

CLASS_DECL_c bool file_put_contents_dup(const char * path, const simple_memory & memory)
{

   return file_put_contents_dup(path, memory.m_psz, memory.m_iSize);

}


CLASS_DECL_c bool get_temp_file_name_dup(char * szRet, ::count iBufferSize, const char * pszName, const char * pszExtension)
{
   return get_temp_file_name_template(szRet, iBufferSize, pszName, pszExtension, NULL);
}


#if defined(LINUX) || defined(MACOS)
#include <sys/types.h>
#include <sys/stat.h>

//Copy file using mmap()

#include <fcntl.h>
#include <sys/mman.h>

#define PACKAGE "mmap"

#endif



bool file_exists_dup(const char * path1)
{

#ifdef WINDOWS

   vsstring str(path1);
   str.replace("/", "\\");
   wstring wstr(L"\\\\?\\");
   wstr = wstr + wstring(str);
   uint32_t dwFileAttributes = ::GetFileAttributesW(wstr);
   if(dwFileAttributes != INVALID_FILE_ATTRIBUTES && (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
      return true;
   else
      return false;

#else

   // dedicaverse stat -> Sir And Arthur - Cesar Serenato

   struct stat st;

   if(stat(path1, &st))
      return false;

   if((st.st_mode & S_IFDIR))
      return false;

   return true;

#endif

}



bool file_put_contents_dup(const char * path, const char * contents, ::count len)
{

#ifdef WINDOWS

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
   uint32_t dwWritten = 0;
   bool bOk = ::WriteFile(hfile, contents, (uint32_t) dwWrite, &dwWritten, NULL) != FALSE;
   ::CloseHandle(hfile);
   return dwWrite == dwWritten && bOk != FALSE;

#else

   FILE * f = fopen(path, "wb");
   if(f == NULL)
      return false;
   ::count dwWrite;
   if(len < 0)
      dwWrite = strlen_dup(contents);
   else
      dwWrite = len;
   fwrite(contents, dwWrite, 1, f);
   fclose(f);
   return true;

#endif

}




vsstring file_as_string_dup(const char * path)
{
   
   vsstring str;

#ifdef WINDOWS


   HANDLE hfile = ::create_file(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return "";

   uint32_t dwSizeHigh;

   uint32_t dwSize = ::GetFileSize(hfile, &dwSizeHigh);

   str.alloc(dwSize);

   uint32_t dwRead;

   ::ReadFile(hfile, str, dwSize, &dwRead, NULL);

   str.m_psz[dwSize] = '\0';

   ::CloseHandle(hfile);

   return str;

#else

   FILE * f = fopen(path, "rb");

   if(f == NULL)
      return "";

   ::count iSize = fsize_dup(f);

   str.alloc(iSize);

   ::count iRead = fread(str, iSize, 1, f);

   str.m_psz[iRead] = '\0';

   fclose(f);

   return str;

#endif

}

bool file_get_memory_dup(simple_memory & memory, const char * path)
{

#ifdef WINDOWS


   memory.allocate(0);

   HANDLE hfile = ::create_file(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return false;

   uint32_t dwSizeHigh;

   ::count  count = ::GetFileSize(hfile, &dwSizeHigh);

   memory.allocate(count);

   uint32_t dwRead;

   ::ReadFile(hfile, memory.m_psz, (uint32_t) memory.m_iSize, &dwRead, NULL);

   ::CloseHandle(hfile);

   return true;


#else

   FILE * f = fopen(path, "rb");
   if(f == NULL)
      return NULL;
   ::count iSize = fsize_dup(f);
   char * psz = (char *) _ca_alloc(iSize + 1);
   ::count iRead = fread(psz, iSize, 1, f);
   psz[iRead] = '\0';
   fclose(f);
   return psz;

#endif

}


bool get_temp_file_name_template(char * szRet, ::count iBufferSize, const char * pszName, const char * pszExtension, const char * pszTemplate)
{

#if defined(WINDOWS)

   char lpPathBuffer[MAX_PATH * 4];

#ifdef WINDOWSEX

   uint32_t dwRetVal = GetTempPath(sizeof(lpPathBuffer), lpPathBuffer);

   if (dwRetVal > sizeof(lpPathBuffer) || (dwRetVal == 0))
   {

      return false;

   }

#else

   vsstring str(::Windows::Storage::ApplicationData::Current->TemporaryFolder->Path->Begin());

   strcpy(lpPathBuffer, str);

#endif

   char bufTime[30];

   char bufItem[30];

   char buf[30];

   size_t iLen= strlen_dup(lpPathBuffer);
   if(!(lpPathBuffer[iLen - 1] == '/'
      || lpPathBuffer[iLen - 1] == '\\'))
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

#else

   char lpPathBuffer[256 * 4];
   strcpy_dup(lpPathBuffer, "/tmp/ca2");
   char bufTime[30];
   char bufItem[30];
   char buf[30];
   size_t iLen= strlen_dup(lpPathBuffer);
   if(!(lpPathBuffer[iLen - 1] == '/'
      || lpPathBuffer[iLen - 1] == '\\'))
   {
      lpPathBuffer[iLen] = '\\';
      lpPathBuffer[iLen+1] = '\0';
   }

   tm * ptm = gmtime(NULL);

   itoa_dup(bufItem, ptm->tm_year, 10);
   zero_pad(bufItem, 4);
   strcpy_dup(bufTime, bufItem);

   itoa_dup(bufItem, ptm->tm_mon, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, "-");
   strcat_dup(bufTime, bufItem);

   itoa_dup(bufItem, ptm->tm_mday, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, "-");
   strcat_dup(bufTime, bufItem);

   itoa_dup(bufItem, ptm->tm_hour, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, " ");
   strcat_dup(bufTime, bufItem);

   itoa_dup(bufItem, ptm->tm_min, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, "-");
   strcat_dup(bufTime, bufItem);

   itoa_dup(bufItem, ptm->tm_sec, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, "-");
   strcat_dup(bufTime, bufItem);

   for(int32_t i = 0; i < (1024 * 1024); i++)
   {
      strcpy_dup(szRet, lpPathBuffer);
      strcat_dup(szRet, pszName);
      //if(i >= 0)
      {
         strcat_dup(szRet, "-");
         strcat_dup(szRet, bufTime);
      }
      //if(i > 0)
      {
         strcat_dup(szRet, "-");
         sprint_hex(buf, i + 1);
         strcat_dup(szRet, buf);
      }
      strcat_dup(szRet, ".");
      strcat_dup(szRet, pszExtension);
      if(pszTemplate != NULL)
      {
         if(is_file_ok(szRet, pszTemplate))
            return true;
      }
      if(file_exists_dup(szRet))
      {
         if(unlink(szRet))
            return true;
      }
      else
      {
         return true;
      }
   }
   return false;

#endif
}





uint64_t file_length_dup(const char * path)
{

#ifdef WINDOWS

   HANDLE hfile = ::create_file(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return 0;

   uint32_t dwHigh;

   uint64_t ui = ::GetFileSize(hfile, &dwHigh);

   //ui |= ((uint64_t) dwHigh) << 32;

   if(dwHigh != 0)
      return 0; // currently invalid for the purposes of this API

   ::CloseHandle(hfile);

   return ui;

#else

   struct stat st;
   stat(path, &st);
   return st.st_size;

#endif

}



vsstring file_module_path_dup()
{

#ifdef WINDOWSEX

   char path[MAX_PATH * 4];
   if(!GetModuleFileName(NULL,
      path,
      sizeof(path)))
      return "";
   else
   {
      return path;
   }

#else

   return "/ca2/stage";

#endif

}







bool file_ftd_dup(const char * pszDir, const char * pszFile)
{

#ifdef WINDOWS
   HANDLE hfile1 = NULL;
   HANDLE hfile2 = NULL;
   wstring wstr(pszFile);
   hfile1 = ::create_file(pszFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   if(hfile1 == INVALID_HANDLE_VALUE)
      return false;

#else
   FILE * hfile1 = NULL;
   FILE * hfile2 = NULL;
   hfile1 = fopen(pszFile, "rb");
   if(hfile1 == NULL)
      return false;
#endif

   vsstring strVersion;


   file_read_ex1_string_dup(hfile1, NULL, strVersion);
   int32_t n;
   vsstring strRelative;
   vsstring strMd5;
   vsstring strMd5New;
   int32_t iBufSize = 1024 * 1024;
   uchar * buf = (uchar *)  _ca_alloc(iBufSize);
   int32_t iLen;
   ::md5::md5 ctx;
#ifdef WINDOWS
   uint32_t dwRead;
   uint32_t dwWritten;
#else
   ::count dwRead;
   ::count dwWritten;
#endif
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
         vsstring strPath = dir::path(pszDir, strRelative);
         dir::mk(dir::name(strPath));
#ifdef WINDOWS
         hfile2 = ::create_file(strPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
         if(hfile2 == INVALID_HANDLE_VALUE)
            return false;
#else
         hfile2 = fopen(strPath, "wb");
         if(hfile2 == NULL)
            return false;
#endif
         file_read_n_number_dup(hfile1, &ctx, iLen);
#ifdef WINDOWS
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
#else
         while(iLen > 0)
         {
            dwRead = ::fread(buf, min(iBufSize, iLen), 1, hfile1);
            break;
            if(dwRead == 0)
               break;
            dwWritten = ::fwrite(buf, dwRead,  1, hfile2);
            ctx.update(buf, dwRead);
            iLen -= dwRead;
         }
         fclose(hfile2);
#endif
         hfile2 = NULL;
         ctx.finalize();

         strMd5New.clear();
         vsstring strFormat;
         strMd5New = ctx.to_string();
         if(strMd5.CompareNoCase(strMd5New) != 0)
            return false;
      }
   }
#ifdef WINDOWS
   ::CloseHandle(hfile1);
   if(hfile2 != INVALID_HANDLE_VALUE)
      ::CloseHandle(hfile2);
#else
   fclose(hfile1);
   if(hfile2 != NULL)
      fclose(hfile2);
#endif
   return true;
}


#ifdef WINDOWS
void file_read_n_number_dup(HANDLE hfile, ::md5::md5 * pctx, int32_t & iNumber)
#else
void file_read_n_number_dup(FILE * hfile, ::md5::md5 * pctx, int32_t & iNumber)
#endif
{
   vsstring str;
   char ch;
#ifdef WINDOWS
   uint32_t dwRead;
   while(ReadFile(hfile, &ch, 1, &dwRead, NULL) && dwRead == 1)
#else
      ::count dwRead;
   while(((dwRead = fread(&ch, 1, 1, (FILE *) hfile))) && dwRead == 1)
#endif
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

#ifdef WINDOWS
void file_read_ex1_string_dup(HANDLE hfile, ::md5::md5 * pctx, vsstring & str)
#else
void file_read_ex1_string_dup(FILE * hfile, ::md5::md5 * pctx, vsstring & str)

#endif
{
   int32_t iLen;
   file_read_n_number_dup(hfile, pctx, iLen);
   LPSTR lpsz = (LPSTR) _ca_alloc(iLen + 1);
#ifdef WINDOWS
   uint32_t dwRead;
   ReadFile(hfile, lpsz, iLen, &dwRead, NULL);
#else
   ::count dwRead;
   dwRead = fread(lpsz, iLen, 1, (FILE *) hfile);
#endif
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

#ifdef WINDOWSEX

   wstring wstrNew(pszNew);
   wstring wstrSrc(pszSrc);
   return ::CopyFileW(wstrSrc, wstrNew, bOverwrite ? FALSE : TRUE) ? true : false;

#elif defined(METROWIN)

    ::Windows::Storage::IStorageFolder ^ folderNew = wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(rtstr(dir::name(pszNew))));

    auto optionNew = ::Windows::Storage::CreationCollisionOption::ReplaceExisting;
 
    // create target file 
    ::Windows::Storage::IStorageFile ^ fileNew = wait(folderNew->CreateFileAsync(rtstr(file_title_dup(pszNew)), optionNew));

    if(fileNew == nullptr)
       return false;

    ::Windows::Storage::IStorageFolder ^ folderSrc = wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(rtstr(dir::name(pszSrc))));

    // create source file 
    ::Windows::Storage::IStorageFile ^ fileSrc = wait(folderSrc->GetFileAsync(rtstr(file_title_dup(pszNew))));

    if(fileSrc == nullptr)
       return false;

    wait(fileSrc->CopyAndReplaceAsync(fileNew));
 
    return true;

#else

   int32_t input, output;
   size_t filesize;
   void *source, *target;


   int32_t flags = O_RDWR|O_CREAT|O_TRUNC;
   if(!bOverwrite)
      flags |= O_EXCL;
   if((output = open(pszNew, flags, 0666)) == -1)
   {
      fprintf(stderr, "%s: Error: opening file: %s\n", PACKAGE, pszNew);
      return false;
   }


   if((input = open(pszSrc, O_RDONLY)) == -1)
   {
      fprintf(stderr, "%s: Error: opening file: %s\n", PACKAGE, pszSrc);
      return false;
   }


   filesize = lseek(input, 0, SEEK_END);
   lseek(output, filesize - 1, SEEK_SET);
   write(output, '\0', 1);

   if((source = mmap(0, filesize, PROT_READ, MAP_SHARED, input, 0)) == (void *) -1)
   {
      fprintf(stderr, "Error mapping input file: %s\n", pszSrc);
      return false;
   }


   if((target = mmap(0, filesize, PROT_WRITE, MAP_SHARED, output, 0)) == (void *) -1)
   {
      fprintf(stderr, "Error mapping ouput file: %s\n", pszNew);
      return false;
   }

   memcpy_dup(target, source, filesize);

   munmap(source, filesize);
   munmap(target, filesize);

   close(input);
   close(output);

   return true;

 #endif

}





CLASS_DECL_c bool file_is_equal_path(const char * psz1, const char * psz2)
{
#ifdef WINDOWSEX
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

#elif defined METROWIN

   return normalize_path(psz1).CompareNoCase(normalize_path(psz2)) == 0;

#else
   
   
   if(stricmp_dup(psz1, psz2) == 0)
      return true;
   
   throw " // TODO: it should follow links ";
   
   return false;
   
#endif
}


CLASS_DECL_c vsstring file_get_mozilla_firefox_plugin_container_path()
{
#ifdef WINDOWSEX

   vsstring strPath;
   HKEY hkeyMozillaFirefox;

   if(::RegOpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox", &hkeyMozillaFirefox) != ERROR_SUCCESS)
      return "";
   {

      uint32_t dwType;
      uint32_t dwData;
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
#elif defined(METROWIN)
   
   throw " todo ";
   
   return "";
   
#else
   
   throw " todo ";
   
   return "";

#endif
   
}






vsstring file_title_dup(const char * path)
{
   vsstring str(path);
   size_t iPos;
   size_t iPos1 = str.rfind('\\');
   size_t iPos2 = str.rfind('/');
   if(iPos1 != -1 && iPos2 != -1)
   {
      if(iPos1 > iPos2)
      {
         iPos = iPos1 + 1;
      }
      else
      {
         iPos = iPos2 + 1;
      }
   }
   else if(iPos1 != -1)
   {
      iPos = iPos1 + 1;
   }
   else if(iPos2 != -1)
   {
      iPos = iPos2 + 1;
   }
   else
   {
      iPos = 0;
   }
   return str.substr(iPos);
}


vsstring file_name_dup(const char * path)
{
   vsstring str = file_title_dup(path);
   size_t iPos = str.find('.');
   if(iPos != -1)
   {
      return str.substr(0, iPos);
   }
   else
   {
      return str;
   }
}
