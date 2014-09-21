// file.cpp

// file routine overrides

// 08/20/05 (mv)

#include "framework.h"
#include "metrowin.h"

//_flag values (not the ones used by the normal CRT

_FILE __iob[3];

void _init_file()
{
	// STDIN
	//__iob[0]._base = (char *) create_file("C:\\Temp\\pid\\stdin");
   __iob[0]._base = (char *) INVALID_HANDLE_VALUE;
	__iob[0]._flag = _FILE_TEXT;

	// STDOUT
	__iob[1]._base = (char *) INVALID_HANDLE_VALUE;
	__iob[1]._flag = _FILE_TEXT;

	// STDERR
	__iob[2]._base = (char *) INVALID_HANDLE_VALUE;
	__iob[2]._flag = _FILE_TEXT;
}

_FILE *__iob_func_dup() {return (_FILE*)__iob;}


   // used directly by the stdin, stdout, and stderr macros





/*int32_t _fileno(_FILE *fp)
{
	return (int32_t)fp;			// FIXME:  This doesn't work under Win64
}

HANDLE _get_osfhandle(int32_t i)
{
	return (HANDLE)i;		// FIXME:  This doesn't work under Win64
}*/

_FILE *fopen_dup(const char *path, const char *attrs)
{



	uint32_t access, disp;
	if (strchr_dup(attrs, 'w'))
	{
		access = GENERIC_WRITE;
		disp = CREATE_ALWAYS;
	}
	else
	{
		access = GENERIC_READ;
		disp = OPEN_EXISTING;
	}

   CREATEFILE2_EXTENDED_PARAMETERS ep;

   memset(&ep, 0, sizeof(ep));
   ep.dwSize = sizeof(ep);
   ep.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;

   wstring wstr(path);

	HANDLE hFile = CreateFile2(wstr, access, 0, disp, &ep);


	if (hFile == INVALID_HANDLE_VALUE)
		return 0;

	_FILE *file = new _FILE;
	memset_dup(file, 0, sizeof(_FILE));
	file->_base = (char *) hFile;

	if (strchr_dup(attrs, 't'))
		file->_flag |= _FILE_TEXT;

	return file;


}


_FILE *_wfopen_dup(const wchar_t *path, const wchar_t *attrs)
{

	uint32_t access, disp;
	if (wcschr_dup(attrs, L'w'))
	{
		access = GENERIC_WRITE;
		disp = CREATE_ALWAYS;
	}
	else
	{
		access = GENERIC_READ;
		disp = OPEN_EXISTING;
	}

	HANDLE hFile = CreateFile2(path, access, 0, disp, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return 0;

	_FILE *file = new _FILE;
	memset_dup(file, 0, sizeof(_FILE));
	file->_base = (char *) hFile;

	if (wcschr_dup(attrs, L't'))
		file->_flag |= _FILE_TEXT;

	return file;

}


int32_t fprintf_dup(_FILE *fp, const char *s, ...)
{
	va_list args;
	va_start(args, s);

	char bfr[1024];
	int32_t len = vsprintf(bfr, s, args);

	va_end(args);

	fwrite_dup(bfr, len+1, sizeof(char), fp);
	return len;
}


int32_t fclose_dup(_FILE *fp)
{

	::CloseHandle((HANDLE)((_FILE*)fp)->_base);
	delete fp;
	return 0;


}

int32_t feof_dup(_FILE *fp)
{

	return (fp->_flag & _FILE_EOF) ? 1 : 0;

}

int32_t fflush_dup(_FILE * fp)
{

   ::FlushFileBuffers((HANDLE) fp->_base);
   return 0;

}

file_position fseek_dup(_FILE *fp, file_offset offset, int32_t origin)
{

	uint32_t meth = FILE_BEGIN;
	if (origin == SEEK_CUR)
		meth = FILE_CURRENT;
	else if (origin == SEEK_END)
		meth = FILE_END;
   LONG offsetHigh = (offset >> 32) & 0xffffffffLL;
	uint32_t dw = ::SetFilePointer((HANDLE)((_FILE*)fp)->_base, offset & 0xffffffff, &offsetHigh, meth);
	((_FILE*)fp)->_flag &= ~_FILE_EOF;
	return (uint64_t) dw | (((uint64_t) offsetHigh) << 32);

}

long ftell_dup(_FILE *fp)
{

	return SetFilePointer((HANDLE) ((_FILE*)fp)->_base, 0, 0, FILE_CURRENT);

}

size_t fread_dup(void *buffer, size_t size, size_t count, _FILE *str)
{

	if (size*count == 0)
		return 0;
	if (feof_dup(str))
		return 0;

	HANDLE hFile = (HANDLE) ((_FILE*)str)->_base;
	int32_t textMode = ((_FILE*)str)->_flag & _FILE_TEXT;

   primitive::memory buf;
   buf.allocate(size*count);
	char *src;
	if (textMode)
      src = (char*)buf.get_data();
	else
		src = (char*)buffer;

	DWORD br;
	if (!ReadFile(hFile, src, (uint32_t)(size*count), &br, 0))
		((_FILE*)str)->_flag |= _FILE_ERROR;
	else if (!br)		// nonzero return value and no bytes read = EOF
		((_FILE*)str)->_flag |= _FILE_EOF;

	if (!br)
		return 0;

	// Text-mode translation is always ANSI
	if (textMode)		// text mode: must translate CR -> LF
	{
		char *dst = (char*)buffer;
		for (uint32_t i = 0; i < br; i++)
		{
			if (src[i] != '\r')
			{
				*dst++ = src[i];
				continue;
			}

			// If next char is LF -> convert CR to LF
			if (i+1 < br)
			{
				if (src[i+1] == '\n')
				{
					*dst++ = '\n';
					i++;
				}
				else
					*dst++ = src[i];
			}
			else if (br > 1)
			{
				// This is the hard part: must peek ahead one byte
				DWORD br2 = 0;
				char peekChar = 0;
				ReadFile(hFile, &peekChar, 1, &br2, 0);
				if (!br2)
					*dst++ = src[i];
				else if (peekChar == '\n')
					*dst++ = '\n';
				else
				{
					fseek_dup(str, -1, SEEK_CUR);
					*dst++ = src[i];
				}
			}
			else
				*dst++ = src[i];
		}

		//_ca_free(src, 0);
	}

	return br/size;

}

size_t fwrite_dup(const void *buffer, size_t size, size_t count, _FILE *str)
{

	DWORD bw = 0, bw2 = 0;

	if (size*count == 0)
		return 0;

	HANDLE hFile = (HANDLE) ((_FILE*)str)->_base;
	int32_t textMode = ((_FILE*)str)->_flag & _FILE_TEXT;

   if(hFile == NULL)
      return 0;

	// Text-mode translation is always ANSI!
	if (textMode)			// text mode -> translate LF -> CRLF
	{
		const char *src = (const char*)buffer;
		size_t startpos = 0, i = 0;
		for (i = 0; i < size*count; i++)
		{
			if (src[i] != '\n')
				continue;
			if (i > 0 && src[i-1] == '\r')		// don't translate CRLF
				continue;

			if (i > startpos)
			{
            size_t dwWritten = 0;
            while(i - startpos - dwWritten > 0)
            {
				   if(!WriteFile(hFile, &src[startpos + dwWritten], (uint32_t) MIN(1024, i - startpos - dwWritten), &bw2, 0))
                  return 0;
               bw += bw2;
               dwWritten += bw2;
            }
			}

			const char *crlf = "\r\n";
			WriteFile(hFile, crlf, 2, &bw2, 0);
			bw++;		// one '\n' written

			startpos = i+1;
		}

      size_t dwWritten = 0;
      while(i - startpos - dwWritten > 0)
      {
			WriteFile(hFile, &src[startpos + dwWritten], (uint32_t) MIN(1024, i - startpos - dwWritten), &bw2, 0);
         bw += bw2;
         dwWritten += bw2;
      }
	}
	else
   {
      size_t s = size * count;
		const char *src = (const char*)buffer;
      size_t dwWritten = 0;
      while(s - dwWritten > 0)
      {
			WriteFile(hFile, &src[dwWritten], (uint32_t) MIN(1024, s - dwWritten), &bw2, 0);
         bw += bw2;
         dwWritten += bw2;
      }
   }
	return bw / size;

}

char *fgets_dup(char *str, int32_t n, _FILE *s)
{

	if (feof_dup(s))
		return 0;

	int32_t i;
	for (i = 0; i < n-1; i++)
	{
		if (!fread_dup(&str[i], 1, sizeof(char), s))
			break;
		if (str[i] == '\r')
		{
			i--;
			continue;
		}
		if (str[i] == '\n')
		{
			i++;
			break;
		}
	}

	str[i] = 0;
	return str;


}

wchar_t *fgetws_dup(wchar_t *str, int32_t n, _FILE *s)
{
	// Text-mode fgetws converts MBCS->Unicode
	if (((_FILE*)str)->_flag & _FILE_TEXT)
	{
      ::primitive::memory buf;
      buf.allocate(n);
      char *bfr = (char*)buf.get_data();
		fgets_dup(bfr, n, s);
		MultiByteToWideChar(CP_ACP, 0, bfr, -1, str, n);
		return str;
	}

	// Binary fgetws reads as Unicode

	if (feof_dup(s))
		return 0;

	int32_t i;
	for (i = 0; i < n-1; i++)
	{
		if (!fread_dup(&str[i], 1, sizeof(wchar_t), s))
			break;
		if (str[i] == L'\r')
		{
			i--;
			continue;	// does i++
		}
		if (str[i] == L'\n')
		{
			i++;
			break;
		}
	}

	str[i] = 0;
	return str;
}

int32_t fgetc_dup(_FILE *s)
{
	if (s == 0 || feof_dup(s))
		return EOF;

	uchar c;
	fread_dup(&c, 1, sizeof(uchar), s);

	return (int32_t)c;
}

int32_t ungetc_dup(int32_t c, _FILE *s)
{
	if (s == 0)
		return EOF;

	fseek_dup(s, -1, SEEK_CUR);

	return (int32_t)c;
}

wint_t fgetwc_dup(_FILE *s)
{
	if (s == 0 || feof_dup(s))
		return (wint_t)EOF;

	// text-mode fgetwc reads and converts MBCS
	if (((_FILE*)s)->_flag & _FILE_TEXT)
	{
		char ch = (char)fgetc_dup(s);
		wint_t wch;
		MultiByteToWideChar(CP_ACP, 0, &ch, 1, (LPWSTR)&wch, 1);
		return wch;
	}

	// binary fgetwc reads unicode

	wint_t c;
	fread_dup(&c, 1, sizeof(wint_t), s);

	return c;

}

wint_t ungetwc_dup(wint_t w, _FILE *s)
{
	if (s == 0)
		return EOF;

	fseek_dup(s, -2, SEEK_CUR);

	return (int32_t)w;
}


int32_t ferror_dup(_FILE *fp)
{

   return fp->_flag & _FILE_ERROR;


}

uint64_t fsize_dup(HANDLE h)
{

   DWORD dwHi;

   DWORD dwLo = ::GetFileSize(h, &dwHi);

   return dwLo | (((DWORD64) dwHi) << 32);

}




#include "framework.h"
#include <io.h>


void file_read_ex1_string_dup(HANDLE hfile,::md5::md5 * pctx,string & str);


void ensure_file_size(HANDLE h,int64_t iSize)
{

   DWORD dwHi;

   DWORD dwLo = ::GetFileSize(h,&dwHi);

   if(((uint64_t)dwLo | ((int64_t)dwHi << 32)) != iSize)
   {
      LONG l = (iSize >> 32) & 0xffffffff;
      ::SetFilePointer(h,iSize & 0xffffffff,&l,SEEK_SET);
      SetEndOfFile(h);
   }

}

DWORD SetFilePointer(HANDLE h,LONG lMove,PLONG plHi,DWORD dwMeth)
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

   if(!SetFilePointerEx(h,liMove,&liRes,dwMeth))
      throw "SetFilePointer error";

   if(plHi != NULL)
   {

      *plHi = liRes.HighPart;

   }

   return liRes.LowPart;


}

DWORD GetFileSize(HANDLE h,LPDWORD lpdwHi)
{

   FILE_STANDARD_INFO info;

   if(!GetFileInformationByHandleEx(h,FileStandardInfo,&info,sizeof(info)))
      throw "GetFileSize Error";

   if(lpdwHi != NULL)
   {
      *lpdwHi = info.EndOfFile.HighPart;
   }

   return info.EndOfFile.LowPart;

}


DWORD GetFileAttributes(const wchar_t * psz)
{

   WIN32_FILE_ATTRIBUTE_DATA data;

   zero(&data,sizeof(data));


   if(!::GetFileAttributesExW(psz,GetFileExInfoStandard,&data))
   {
      DWORD dwLastError = ::GetLastError();
      return INVALID_FILE_ATTRIBUTES;
   }

   return data.dwFileAttributes;

}


BEGIN_EXTERN_C

HANDLE FindFirstFileW(const wchar_t * pwsz,WIN32_FIND_DATAW * pdata)
{

   return FindFirstFileExW(pwsz,FindExInfoStandard,pdata,FindExSearchNameMatch,NULL,0);

}

HANDLE FindFirstFileA(const char * pwsz,WIN32_FIND_DATAA * pdata)
{

   return FindFirstFileExA(pwsz,FindExInfoStandard,pdata,FindExSearchNameMatch,NULL,0);

}

END_EXTERN_C

/*
int_bool WINAPI FileTimeToLocalFileTime(const FILETIME * lpFileTime, LPFILETIME lpLocalFileTime)
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


*/

HANDLE create_file(const char * lpcszFileName,dword dwDesiredAcces,dword dwShareMode,LPSECURITY_ATTRIBUTES lpSA,dword dwCreationDisposition,dword dwFlagsAndAttributes,HANDLE hTemplateFile)
{

   CREATEFILE2_EXTENDED_PARAMETERS ps;

   memset(&ps,0,sizeof(ps));

   ps.dwSize                  = sizeof(ps);
   ps.dwFileAttributes        = dwFlagsAndAttributes;
   ps.lpSecurityAttributes    = lpSA;
   ps.hTemplateFile           = hTemplateFile;

   wstring wstr(lpcszFileName);

   return ::CreateFile2(wstr,dwDesiredAcces,dwShareMode,dwCreationDisposition,&ps);

}


int_bool close_handle(handle h)
{

   return ::CloseHandle(h) != FALSE;

}


::Windows::Storage::StorageFolder ^ get_os_folder(const char * lpcszDirName)
{

   return wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(string(lpcszDirName)));

}


::Windows::Storage::StorageFile ^ get_os_file(const char * lpcszFileName,dword dwDesiredAcces,dword dwShareMode,LPSECURITY_ATTRIBUTES lpSA,dword dwCreationDisposition,dword dwFlagsAndAttributes,HANDLE hTemplateFile)
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

      file = wait(folder->CreateFileAsync(strFileName,optionNew));

   }
   else if(dwCreationDisposition == CREATE_NEW)
   {

      auto optionNew = ::Windows::Storage::CreationCollisionOption::FailIfExists;

      file = wait(folder->CreateFileAsync(strFileName,optionNew));

   }
   else if(dwCreationDisposition == OPEN_ALWAYS)
   {

      auto optionNew = ::Windows::Storage::CreationCollisionOption::OpenIfExists;

      file = wait(folder->CreateFileAsync(strFileName,optionNew));

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


bool get_file_time(::Windows::Storage::StorageFile ^ file,LPFILETIME lpCreationTime,LPFILETIME lpItemTime,LPFILETIME lpLastWriteTime)
{

   if(lpCreationTime != NULL)
   {

      *lpCreationTime = (FILETIME &)file->DateCreated;

   }

   if(lpItemTime != NULL || lpLastWriteTime != NULL)
   {

      ::Windows::Storage::FileProperties::BasicProperties ^ properties = wait(file->GetBasicPropertiesAsync());

      if(lpItemTime != NULL)
      {
         *lpItemTime = (FILETIME &)properties->ItemDate;
      }

      if(lpLastWriteTime != NULL)
      {
         *lpLastWriteTime = (FILETIME &)properties->DateModified;
      }

   }

   return true;

}




string get_sys_temp_path()
{

   return ::Windows::Storage::ApplicationData::Current->TemporaryFolder->Path;

}


//
//int_bool file_exists_dup(const char * path1)
//{
//
//   string str(path1);
//   str.replace("/","\\");
//   wstring wstr(L"\\\\?\\");
//   wstr = wstr + wstring(str);
//   uint32_t dwFileAttributes = ::GetFileAttributesW(wstr);
//   if(dwFileAttributes != INVALID_FILE_ATTRIBUTES && (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
//      return true;
//   else
//      return false;
//
//}
//


int_bool file_put_contents_dup(const char * path,const char * contents,::count len)
{

   dir::mk(dir::name(path));

   wstring wstr(path);



   HANDLE hfile = ::create_file(path,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
   if(hfile == INVALID_HANDLE_VALUE)
      return false;
   count dwWrite;
   if(len < 0)
      dwWrite = strlen_dup(contents);
   else
      dwWrite = len;
   DWORD dwWritten = 0;
   bool bOk = ::WriteFile(hfile,contents,(uint32_t)dwWrite,&dwWritten,NULL) != FALSE;
   ::CloseHandle(hfile);
   return dwWrite == dwWritten && bOk != FALSE;

}




string file_as_string_dup(const char * path)
{

   string str;

   HANDLE hfile = ::create_file(path,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return "";

   DWORD dwSizeHigh;

   uint32_t dwSize = ::GetFileSize(hfile,&dwSizeHigh);

   char * psz = str.GetBufferSetLength(dwSize);

   DWORD dwRead;

   ::ReadFile(hfile,psz,dwSize,&dwRead,NULL);

   psz[dwSize] = '\0';

   str.ReleaseBuffer();

   ::CloseHandle(hfile);

   return str;

}

bool file_get_memory_dup(::primitive::memory_base & memory,const char * path)
{

   memory.allocate(0);

   HANDLE hfile = ::create_file(path,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return false;

   DWORD dwSizeHigh;

   ::count  count = ::GetFileSize(hfile,&dwSizeHigh);

   memory.allocate(count);

   DWORD dwRead;

   ::ReadFile(hfile,memory.get_data(),(uint32_t)memory.get_size(),&dwRead,NULL);

   ::CloseHandle(hfile);

   return true;


}

/*

int_bool get_temp_file_name_template(char * szRet, ::count iBufferSize, const char * pszName, const char * pszExtension, const char * pszTemplate)
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
::hex::lower_from(buf, i + 1);
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

*/



uint64_t file_length_dup(const char * path)
{

   HANDLE hfile = ::create_file(path,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

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







int_bool file_ftd_dup(const char * pszDir,const char * pszFile)
{

   HANDLE hfile1 = NULL;
   HANDLE hfile2 = NULL;
   wstring wstr(pszFile);
   hfile1 = ::create_file(pszFile,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
   if(hfile1 == INVALID_HANDLE_VALUE)
      return false;

   string strVersion;


   file_read_ex1_string_dup(hfile1,NULL,strVersion);
   int32_t n;
   string strRelative;
   string strMd5;
   string strMd5New;
   int32_t iBufSize = 1024 * 1024;
   primitive::memory mem;
   mem.allocate(iBufSize);
   uchar * buf = (uchar *)mem.get_data();
   int32_t iLen;
   ::md5::md5 ctx;
   DWORD dwRead;
   DWORD dwWritten;
   if(strVersion == "fileset v1")
   {
      while(true)
      {
         file_read_n_number_dup(hfile1,NULL,n);
         if(n == 2)
            break;
         file_read_ex1_string_dup(hfile1,NULL,strMd5);
         ctx.initialize();
         file_read_ex1_string_dup(hfile1,&ctx,strRelative);
         string strPath = dir::path(pszDir,strRelative);
         dir::mk(dir::name(strPath));
         hfile2 = ::create_file(strPath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
         if(hfile2 == INVALID_HANDLE_VALUE)
            return false;
         file_read_n_number_dup(hfile1,&ctx,iLen);
         while(iLen > 0)
         {
            if(!::ReadFile(hfile1,buf,MIN(iBufSize,iLen),&dwRead,NULL))
               break;
            if(dwRead == 0)
               break;
            ::WriteFile(hfile2,buf,dwRead,&dwWritten,NULL);
            ctx.update(buf,dwRead);
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


void file_read_n_number_dup(HANDLE hfile,::md5::md5 * pctx,int32_t & iNumber)
{
   string str;
   char ch;
   DWORD dwRead;
   while(ReadFile(hfile,&ch,1,&dwRead,NULL) && dwRead == 1)
   {
      if(ch >= '0' && ch <= '9')
         str += ch;
      else
         break;
      if(pctx != NULL)
      {
         pctx->update(&ch,1);
      }
   }
   if(ch != 'n')
      return;
   if(pctx != NULL)
   {
      pctx->update(&ch,1);
   }
   iNumber = atoi_dup(str);
}

void file_read_ex1_string_dup(HANDLE hfile,::md5::md5 * pctx,string & str)
{
   int32_t iLen;
   file_read_n_number_dup(hfile,pctx,iLen);
   primitive::memory mem;
   mem.allocate(MAX(iLen,64));
   LPSTR lpsz = (LPSTR)mem.get_data();
   DWORD dwRead;
   ReadFile(hfile,lpsz,iLen,&dwRead,NULL);
   if(pctx != NULL)
   {
      pctx->update(lpsz,iLen);
   }
   lpsz[iLen] = '\0';
   str = lpsz;
}

























int_bool file_copy_dup(const char * pszNew,const char * pszSrc,int_bool bOverwrite)
{

   ::Windows::Storage::IStorageFolder ^ folderNew = wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(dir::name(pszNew)));

   auto optionNew = ::Windows::Storage::CreationCollisionOption::ReplaceExisting;

   // create target file 
   ::Windows::Storage::IStorageFile ^ fileNew = wait(folderNew->CreateFileAsync(file_title_dup(pszNew),optionNew));

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





int_bool file_is_equal_path(const char * psz1,const char * psz2)
{

   return normalize_path(psz1).CompareNoCase(normalize_path(psz2)) == 0;

}


string file_get_mozilla_firefox_plugin_container_path()
{

   throw " todo ";

   return "";

}







int ftruncate(int file,file_size len)
{
   return _chsize_s(file,len);
}



int_bool file_set_length(const char * pszName,size_t iSize)
{

   int i = open(pszName,0);

   ftruncate(i,iSize);

   ::close(i);

   return true;

}