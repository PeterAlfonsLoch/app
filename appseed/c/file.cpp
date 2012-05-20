#include "framework.h"

#if defined(LINUX) || defined(MACOS)
#include <sys/types.h>
#include <sys/stat.h>

//Copy file using mmap()

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define PACKAGE "mmap"

#endif

#ifdef WINDOWS
bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinstance, UINT nID, LPCTSTR lpcszType)
{

   HRSRC hrsrc = ::FindResource(hinstance, MAKEINTRESOURCE(nID), lpcszType);

   if(hrsrc == NULL)
      return false;

   HGLOBAL hglobalResource = ::LoadResource(hinstance, hrsrc);

   if(hglobalResource == NULL)
      return false;

   DWORD dwResourseSize = ::SizeofResource(hinstance, hrsrc);

   if(hglobalResource != NULL)
   {
      bool bOk = false;

      UINT FAR* pResource = (UINT FAR*) ::LockResource(hglobalResource);

      dir::mk(dir::name(pszFile));

      HANDLE hfile = ::CreateFile(pszFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

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
#endif

bool file_exists_dup(const char * path1)
{

#ifdef WINDOWS

   DWORD dwFileAttributes = ::GetFileAttributes(path1);
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

bool file_put_contents_dup(const char * path, const char * contents, int len)
{

#ifdef WINDOWS

   HANDLE hfile = ::CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   if(hfile == INVALID_HANDLE_VALUE)
      return false;
   count dwWrite;
   if(len < 0)
      dwWrite = strlen_dup(contents);
   else
      dwWrite = len;
   DWORD dwWritten = 0;
   bool bOk = ::WriteFile(hfile, contents, (DWORD) dwWrite, &dwWritten, NULL) != FALSE;
   ::CloseHandle(hfile);
   return dwWrite == dwWritten && bOk != FALSE;

#else

   FILE * f = fopen(path, "wb");
   if(f == NULL)
      return false;
   DWORD dwWrite;
   if(len < 0)
      dwWrite = strlen_dup(contents);
   else
      dwWrite = len;
   fwrite(contents, dwWrite, 1, f);
   fclose(f);
   return true;

#endif

}




const char * file_get_contents_dup(const char * path)
{

#ifdef WINDOWS

   HANDLE hfile = ::CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   if(hfile == INVALID_HANDLE_VALUE)
      return strdup_dup("");
   DWORD dwSizeHigh;
   DWORD dwSize = ::GetFileSize(hfile, &dwSizeHigh);
   char * psz = (char *) _ca_alloc(dwSize + 1);
   DWORD dwRead;
   ::ReadFile(hfile, psz, dwSize, &dwRead, NULL);
   psz[dwSize] = '\0';
   ::CloseHandle(hfile);
   return psz;

#else

   FILE * f = fopen(path, "rb");
   if(f == NULL)
      return NULL;
   int iSize = fsize_dup(f);
   char * psz = (char *) _ca_alloc(iSize + 1);
   int iRead = fread(psz, iSize, 1, f);
   psz[iSize] = '\0';
   fclose(f);
   return psz;

#endif

}



int to_hex_char(int i);

void sprint_hex(char * sz, int iValue)
{
   int i = 8;
   sz[i] = '\0';
   i--;
   for(; i >= 0; i--)
   {
      sz[i] = to_hex_char((iValue >> (4 * (7 - i))) &  0xf);
   }
}


bool get_temp_file_name_template(char * szRet, int iBufferSize, const char * pszName, const char * pszExtension, const char * pszTemplate)
{

#ifdef WINDOWS

   char lpPathBuffer[MAX_PATH * 4];
   DWORD dwRetVal = GetTempPath(sizeof(lpPathBuffer), lpPathBuffer);
   if (dwRetVal > sizeof(lpPathBuffer) || (dwRetVal == 0))
   {
      return false;
   }
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

   for(int i = 0; i < (1024 * 1024); i++)
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

   for(int i = 0; i < (1024 * 1024); i++)
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


bool get_temp_file_name_dup(char * szRet, int iBufferSize, const char * pszName, const char * pszExtension)
{
   return get_temp_file_name_template(szRet, iBufferSize, pszName, pszExtension, NULL);
}



uint64_t file_length_dup(const char * path)
{

#ifdef WINDOWS

   HANDLE hfile = ::CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   if(hfile == INVALID_HANDLE_VALUE)
      return 0;
   DWORD dwHigh;
   unsigned int64_t ui = ::GetFileSize(hfile, &dwHigh);
   //ui |= ((unsigned int64_t) dwHigh) << 32;
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

vsstring file_module_path_dup()
{

#ifdef WINDOWS

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
   vsstring strVersion;
   hfile1 = ::CreateFile(pszFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   if(hfile1 == INVALID_HANDLE_VALUE)
      return false;
#else
   FILE * hfile1 = NULL;
   FILE * hfile2 = NULL;
   vsstring strVersion;
   hfile1 = fopen(pszFile, "rb");
   if(hfile1 == NULL)
      return false;
#endif

   file_read_ex1_string_dup(hfile1, NULL, strVersion);
   int n;
   vsstring strRelative;
   vsstring strMd5;
   vsstring strMd5New;
   int iBufSize = 1024 * 1024;
   unsigned char * buf = (unsigned char *)  _ca_alloc(iBufSize);
   int iLen;
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
         vsstring strPath = dir::path(pszDir, strRelative);
         dir::mk(dir::name(strPath));
#ifdef WINDOWS
         hfile2 = ::CreateFile(strPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
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
            ::fwrite(buf, dwRead,  1, hfile2);
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


/*   void file::write_n_number(FILE * pfile, ::md5::md5  * pctx, int iNumber)
{
vsstring str;
str.Format("%dn", iNumber);
pfile->Write((const char *) str, str.get_length());
if(pctx != NULL)
{
MD5_Update(pctx, (const char *) str, str.get_length());
}
}
*/
#ifdef WINDOWS
void file_read_n_number_dup(HANDLE hfile, ::md5::md5 * pctx, int & iNumber)
#else
void file_read_n_number_dup(FILE * hfile, ::md5::md5 * pctx, int & iNumber)
#endif
{
   DWORD dwRead;
   vsstring str;
   char ch;
#ifdef WINDOWS
   while(ReadFile(hfile, &ch, 1, &dwRead, NULL) && dwRead == 1)
#else
   while((dwRead = fread(&ch, 1, 1, (FILE *) hfile)) && dwRead == 1)
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

/* void file::write_ex1_string(ex1::file * pfile, MD5_CTX * pctx, string & str)
{
int iLen = str.get_length();
write_n_number(pfile, pctx, iLen);
pfile->Write((const char *) str, str.get_length());
if(pctx != NULL)
{
MD5_Update(pctx, (const char *) str, str.get_length());
}
}*/
#ifdef WINDOWS
void file_read_ex1_string_dup(HANDLE hfile, ::md5::md5 * pctx, vsstring & str)
#else
void file_read_ex1_string_dup(FILE * hfile, ::md5::md5 * pctx, vsstring & str)

#endif
{
   int iLen;
   file_read_n_number_dup(hfile, pctx, iLen);
   LPSTR lpsz = (LPSTR) _ca_alloc(iLen + 1);
   DWORD dwRead;
#ifdef WINDOWS
   ReadFile(hfile, lpsz, iLen, &dwRead, NULL);
#else
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






















/*   void file::dtf(const char * pszFile, const char * pszDir)
{
stringa stra_dup;
stringa straRelative;
System.dir().rls(pszDir, &stra_dup, NULL, &straRelative);
ex1::filesp spfile(get_app());
if(!spfile->Open(pszFile, ::ex1::file::modeCreate | ::ex1::file::modeWrite  | ::ex1::file::typeBinary))
throw "failed";
string strVersion;
strVersion = "fileset v1";
MD5_CTX ctx;
write_ex1_string(spfile, NULL, strVersion);
ex1::filesp file2(get_app());
int iBufSize = 1024 * 1024;
int uiRead;
unsigned char * buf = (unsigned char *)  malloc(iBufSize);
string strMd5 = "01234567012345670123456701234567";
int iPos;
for(int i = 0; i < stra_dup.get_size(); i++)
{
if(System.dir().is(stra_dup[i]))
continue;
write_n_number(spfile, NULL, 1);
iPos = spfile->get_position();
write_ex1_string(spfile, NULL, strMd5);
MD5_Init(&ctx);
write_ex1_string(spfile, &ctx, straRelative[i]);
if(!file2->Open(stra_dup[i], ::ex1::file::modeRead | ::ex1::file::typeBinary))
throw "failed";
write_n_number(spfile, &ctx, file2->get_length());
while((uiRead = file2->Read(buf, iBufSize)) > 0)
{
spfile->Write(buf, uiRead);
MD5_Update(&ctx, buf, uiRead);
}
spfile->Seek(iPos, ::ex1::file::SeekBegin);
MD5_Final(buf,&ctx);
strMd5.Empty();
string strFormat;
for(int i = 0; i < 16; i++)
{
strFormat.Format("%02x", buf[i]);
strMd5 += strFormat;
}
write_ex1_string(spfile, NULL, strMd5);
spfile->SeekToEnd();

}
write_n_number(spfile, NULL, 2);
}*/

/*bool file::ftd(const char * pszDir, const char * pszFile)
{
FILE * spfile = NULL;
FILE * file2 = NULL;
try
{
vsstring strVersion;
spfile = fopen(pszFile, "rb");
if(!spfile)
throw "failed";
read_ex1_string(spfile, NULL, strVersion);
int n;
vsstring strRelative;
vsstring strMd5;
vsstring strMd5New;
int iBufSize = 1024 * 1024;
unsigned char * buf = (unsigned char *)  malloc(iBufSize);
int iLen;
::md5::md5 ctx;
UINT_PTR uiRead;
if(strVersion == "fileset v1")
{
while(true)
{
read_n_number(spfile, NULL, n);
if(n == 2)
break;
read_ex1_string(spfile, NULL, strMd5);
ctx.initialize();
read_ex1_string(spfile, &ctx, strRelative);
vsstring strPath = dir::path(pszDir, strRelative);
dir::mk(dir::name(strPath));
file2 = fopen(strPath, "wb");
if(!file2)
throw "failed";
read_n_number(spfile, &ctx, iLen);
while(iLen > 0)
{
uiRead = fread(buf, 1, min(iBufSize, iLen ), spfile);
if(uiRead == 0)
break;
fwrite(buf, 1, uiRead, file2);
ctx.update(buf, uiRead);
iLen -= uiRead;
}
fclose(file2);
file2 = NULL;
ctx.finalize();

strMd5New.clear();
vsstring strFormat;
strMd5New = ctx.to_string();
if(_stricmp(strMd5, strMd5New) != 0)
throw "failed";
}
}
if(spfile != NULL)
fclose(spfile);
if(file2 != NULL)
fclose(file2);
return true;
}
catch(...)
{
if(spfile != NULL)
fclose(spfile);
if(file2 != NULL)
fclose(file2);
return false;
}
}


/*   void file::write_n_number(FILE * pfile, ::md5::md5  * pctx, int iNumber)
{
vsstring str;
str.Format("%dn", iNumber);
pfile->Write((const char *) str, str.get_length());
if(pctx != NULL)
{
MD5_Update(pctx, (const char *) str, str.get_length());
}
}
*/
/*   void file::read_n_number(FILE * pfile, ::md5::md5 * pctx, int & iNumber)
{
UINT_PTR uiRead;
vsstring str;
char ch;
while((uiRead = fread(&ch, 1, 1, pfile)) == 1)
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
throw "failed";
if(pctx != NULL)
{
pctx->update(&ch, 1);
}
iNumber = atoi(str);
}

/* void file::write_ex1_string(ex1::file * pfile, MD5_CTX * pctx, string & str)
{
int iLen = str.get_length();
write_n_number(pfile, pctx, iLen);
pfile->Write((const char *) str, str.get_length());
if(pctx != NULL)
{
MD5_Update(pctx, (const char *) str, str.get_length());
}
}*/

/* void file::read_ex1_string(FILE * pfile, ::md5::md5 * pctx, vsstring & str)
{
int iLen;
read_n_number(pfile, pctx, iLen);
LPSTR lpsz = (LPSTR) malloc(iLen + 1);
fread(lpsz, 1, iLen, pfile);
if(pctx != NULL)
{
pctx->update(lpsz, iLen);
}
lpsz[iLen] = '\0';
str = lpsz;
free(lpsz);
}
*/


#ifdef WINDOWS

bool PrintModules(vsstring & strImage, DWORD processID, const char * pszDll )
{
   HANDLE hProcess;
   DWORD cbNeeded;
   unsigned int i;
   hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
      PROCESS_VM_READ,
      FALSE, processID );




   if (NULL == hProcess)
      return false;

   const int iMaxModuleCount = 1024;
   HMODULE * hMods = new HMODULE[iMaxModuleCount];



   const int iImageSize = MAX_PATH * 8;
   char * szImage = (char *) _ca_alloc(iImageSize);
   GetModuleFileNameEx(hProcess, NULL, szImage, iImageSize);
   strImage = szImage;
   _ca_free(szImage, 0);

   bool bFound = false;

   if( EnumProcessModules(hProcess, hMods, sizeof(HMODULE) * iMaxModuleCount, &cbNeeded))
   {
      for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
      {
         TCHAR szModName[MAX_PATH];

         // Get the full path to the module's file.

         if ( GetModuleFileNameEx( hProcess, hMods[i], szModName,
            sizeof(szModName) / sizeof(TCHAR)))
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
   unsigned int i;

   if ( !EnumProcesses( aProcesses, 124 * 8 * sizeof(DWORD), &cbNeeded ) )
   {
      delete aProcesses;
      return;
   }

   // Calculate how many process identifiers were returned.

   cProcesses = cbNeeded / sizeof(DWORD);

   // Print the name of the modules for each process.

   vsstring strImage;
   for ( i = 0; i < cProcesses; i++ )
   {
      if(PrintModules(strImage, aProcesses[i], pszDll ))
      {
         straProcesses.add_unique_ci(strImage);
         dwa.add(aProcesses[i]);
      }
   }

   delete aProcesses;
}

#endif



bool file_copy_dup(const char * pszNew, const char * pszSrc, bool bOverwrite)
{

#ifdef WINDOWS

   return ::CopyFile(pszSrc, pszNew, bOverwrite ? FALSE : TRUE) ? true : false;

#else

   int input, output;
   size_t filesize;
   void *source, *target;


   int flags = O_RDWR|O_CREAT|O_TRUNC;
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
#ifdef WINDOWS
   const int iBufSize = MAX_PATH * 8;
   const wchar_t * pwsz1 = utf8_to_16(psz1);
   const wchar_t * pwsz2 = utf8_to_16(psz2);
   wchar_t * pwszFile1;
   wchar_t * pwszFile2;
   wchar_t * pwszPath1 = new wchar_t[iBufSize];
   wchar_t * pwszPath2 = new wchar_t[iBufSize];
   int iCmp = -1;
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

#else
   // TODO: it should follow links
#endif
}


CLASS_DECL_c vsstring file_get_mozilla_firefox_plugin_container_path()
{
#ifdef WINDOWS

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

#endif
}
