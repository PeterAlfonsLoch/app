#include "framework.h"

// file.cpp

// file routine overrides

// 08/20/05 (mv)

#ifdef METROWIN

//_flag values (not the ones used by the normal CRT

_FILE __iob[3];

void _init_file()
{
   // STDIN
   //__iob[0]._base = (char *) create_file("C:\\Temp\\pid\\stdin");
   __iob[0]._base = (char *)INVALID_HANDLE_VALUE;
   __iob[0]._flag = _FILE_TEXT;

   // STDOUT
   __iob[1]._base = (char *)INVALID_HANDLE_VALUE;
   __iob[1]._flag = _FILE_TEXT;

   // STDERR
   __iob[2]._base = (char *)INVALID_HANDLE_VALUE;
   __iob[2]._flag = _FILE_TEXT;
}

_FILE *__iob_func_dup() { return (_FILE*)__iob; }

#elif defined(WINDOWS)


//_flag values (not the ones used by the normal CRT

_FILE __iob[3];

void _init_file()
{
   // STDIN
   __iob[0]._base = (char *)GetStdHandle(STD_INPUT_HANDLE);
   __iob[0]._flag = _FILE_TEXT;

   // STDOUT
   __iob[1]._base = (char *)GetStdHandle(STD_OUTPUT_HANDLE);
   __iob[1]._flag = _FILE_TEXT;

   // STDERR
   __iob[2]._base = (char *)GetStdHandle(STD_ERROR_HANDLE);
   __iob[2]._flag = _FILE_TEXT;
}

_FILE *__iob_func_dup() { return (_FILE*)__iob; }
#endif

// used directly by the stdin, stdout, and stderr macros


//
//
//
///*int32_t _fileno(_FILE *fp)
//{
//return (int32_t)fp;			// FIXME:  This doesn't work under Win64
//}
//
//HANDLE _get_osfhandle(int32_t i)
//{
//return (HANDLE)i;		// FIXME:  This doesn't work under Win64
//}*/
//
//_FILE *fopen_dup(const char *path, const char *attrs)
//{
//
//#if defined(LINUX) || defined(MACOS)
//
//   return fopen(path, attrs);
//#elif defined(METROWIN)
//
//
//   uint32_t access, disp;
//   if (strchr_dup(attrs, 'w'))
//   {
//      access = GENERIC_WRITE;
//      disp = CREATE_ALWAYS;
//   }
//   else
//   {
//      access = GENERIC_READ;
//      disp = OPEN_EXISTING;
//   }
//
//   CREATEFILE2_EXTENDED_PARAMETERS ep;
//
//   memset(&ep, 0, sizeof(ep));
//   ep.dwSize = sizeof(ep);
//   ep.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
//
//   wstring wstr(path);
//
//   HANDLE hFile = CreateFile2(wstr, access, 0, disp, &ep);
//
//
//   if (hFile == INVALID_HANDLE_VALUE)
//      return 0;
//
//   _FILE *file = new _FILE;
//   memset_dup(file, 0, sizeof(_FILE));
//   file->_base = (char *)hFile;
//
//   if (strchr_dup(attrs, 't'))
//      file->_flag |= _FILE_TEXT;
//
//   return file;
//
//#else
//
//   uint32_t access, disp;
//   if (strchr_dup(attrs, 'w'))
//   {
//      access = GENERIC_WRITE;
//      disp = CREATE_ALWAYS;
//   }
//   else
//   {
//      access = GENERIC_READ;
//      disp = OPEN_EXISTING;
//   }
//
//   wstring wstr(path);
//
//   HANDLE hFile = CreateFileW(wstr, access, 0, 0, disp, 0, 0);
//
//   if (hFile == INVALID_HANDLE_VALUE)
//      return 0;
//
//   _FILE *file = new _FILE;
//   memset_dup(file, 0, sizeof(_FILE));
//   file->_base = (char *)hFile;
//
//   if (strchr_dup(attrs, 't'))
//      file->_flag |= _FILE_TEXT;
//
//   return file;
//
//#endif
//
//}
//
//#ifdef WINDOWSEX
//
//_FILE *_wfopen_dup(const wchar_t *path, const wchar_t *attrs)
//{
//
//   uint32_t access, disp;
//   if (wcschr_dup(attrs, L'w'))
//   {
//      access = GENERIC_WRITE;
//      disp = CREATE_ALWAYS;
//   }
//   else
//   {
//      access = GENERIC_READ;
//      disp = OPEN_EXISTING;
//   }
//
//   HANDLE hFile = CreateFileW(path, access, 0, 0, disp, 0, 0);
//   if (hFile == INVALID_HANDLE_VALUE)
//      return 0;
//
//   _FILE *file = new _FILE;
//   memset_dup(file, 0, sizeof(_FILE));
//   file->_base = (char *)hFile;
//
//   if (wcschr_dup(attrs, L't'))
//      file->_flag |= _FILE_TEXT;
//
//   return file;
//
//}
//
//#elif defined(METROWIN)
//
//_FILE *_wfopen_dup(const wchar_t *path, const wchar_t *attrs)
//{
//
//   uint32_t access, disp;
//   if (wcschr_dup(attrs, L'w'))
//   {
//      access = GENERIC_WRITE;
//      disp = CREATE_ALWAYS;
//   }
//   else
//   {
//      access = GENERIC_READ;
//      disp = OPEN_EXISTING;
//   }
//
//   HANDLE hFile = CreateFile2(path, access, 0, disp, NULL);
//   if (hFile == INVALID_HANDLE_VALUE)
//      return 0;
//
//   _FILE *file = new _FILE;
//   memset_dup(file, 0, sizeof(_FILE));
//   file->_base = (char *)hFile;
//
//   if (wcschr_dup(attrs, L't'))
//      file->_flag |= _FILE_TEXT;
//
//   return file;
//
//}
//
//#endif
//
//
//int32_t fprintf_dup(_FILE *fp, const char *s, ...)
//{
//   va_list args;
//   va_start(args, s);
//
//   char bfr[1024];
//#ifdef WINDOWSEX
//   int32_t len = wvsprintfA(bfr, s, args);
//#else
//   int32_t len = vsprintf(bfr, s, args);
//#endif
//
//   va_end(args);
//
//   fwrite_dup(bfr, len + 1, sizeof(char), fp);
//   return len;
//}
//
//#ifdef WINDOWSEX
//
//int32_t fwprintf_dup(_FILE *fp, const wchar_t *s, ...)
//{
//   va_list args;
//   va_start(args, s);
//
//   wchar_t bfr[1024];
//   int32_t len = wvsprintfW(bfr, s, args);
//
//   va_end(args);
//
//   char ansibfr[1024];
//   WideCharToMultiByte(CP_ACP, 0, bfr, -1, ansibfr, sizeof(ansibfr), 0, 0);
//
//   fwrite_dup(ansibfr, len + 1, sizeof(char), fp);
//   return len;
//}
//
//#endif
//
//int32_t fclose_dup(_FILE *fp)
//{
//
//#ifdef WINDOWS
//
//   ::CloseHandle((HANDLE)((_FILE*)fp)->_base);
//   delete fp;
//   return 0;
//
//#else
//
//   return fclose(fp);
//
//#endif
//
//}
//
//int32_t feof_dup(_FILE *fp)
//{
//
//#ifdef WINDOWS
//
//   return (fp->_flag & _FILE_EOF) ? 1 : 0;
//
//#else
//
//   return feof(fp);
//
//#endif
//
//}
//
//int32_t fflush_dup(_FILE * fp)
//{
//
//#ifdef WINDOWS
//
//   ::FlushFileBuffers((HANDLE)fp->_base);
//   return 0;
//
//#else
//
//   return fflush(fp);
//
//#endif
//
//}
//
//file_position fseek_dup(_FILE *fp, file_offset offset, int32_t origin)
//{
//
//#ifdef WINDOWS
//
//   uint32_t meth = FILE_BEGIN;
//   if (origin == SEEK_CUR)
//      meth = FILE_CURRENT;
//   else if (origin == SEEK_END)
//      meth = FILE_END;
//   LONG offsetHigh = (offset >> 32) & 0xffffffffLL;
//   uint32_t dw = ::SetFilePointer((HANDLE)((_FILE*)fp)->_base, offset & 0xffffffff, &offsetHigh, meth);
//   ((_FILE*)fp)->_flag &= ~_FILE_EOF;
//   return (uint64_t)dw | (((uint64_t)offsetHigh) << 32);
//
//#else
//
//   return fseek(fp, offset, origin);
//
//#endif
//
//}
//
//long ftell_dup(_FILE *fp)
//{
//
//#ifdef WINDOWS
//
//   return SetFilePointer((HANDLE)((_FILE*)fp)->_base, 0, 0, FILE_CURRENT);
//
//#else
//
//   return ftell(fp);
//
//#endif
//
//}
//
//size_t fread_dup(void *buffer, size_t size, size_t count, _FILE *str)
//{
//
//#ifdef WINDOWS
//
//   if (size*count == 0)
//      return 0;
//   if (feof_dup(str))
//      return 0;
//
//   HANDLE hFile = (HANDLE)((_FILE*)str)->_base;
//   int32_t textMode = ((_FILE*)str)->_flag & _FILE_TEXT;
//
//   char *src;
//   if (textMode)
//      src = (char*)memory_alloc(size*count);
//   else
//      src = (char*)buffer;
//
//   DWORD br;
//   if (!ReadFile(hFile, src, (uint32_t)(size*count), &br, 0))
//      ((_FILE*)str)->_flag |= _FILE_ERROR;
//   else if (!br)		// nonzero return value and no bytes read = EOF
//      ((_FILE*)str)->_flag |= _FILE_EOF;
//
//   if (!br)
//      return 0;
//
//   // Text-mode translation is always ANSI
//   if (textMode)		// text mode: must translate CR -> LF
//   {
//      char *dst = (char*)buffer;
//      for (uint32_t i = 0; i < br; i++)
//      {
//         if (src[i] != '\r')
//         {
//            *dst++ = src[i];
//            continue;
//         }
//
//         // If next char is LF -> convert CR to LF
//         if (i + 1 < br)
//         {
//            if (src[i + 1] == '\n')
//            {
//               *dst++ = '\n';
//               i++;
//            }
//            else
//               *dst++ = src[i];
//         }
//         else if (br > 1)
//         {
//            // This is the hard part: must peek ahead one byte
//            DWORD br2 = 0;
//            char peekChar = 0;
//            ReadFile(hFile, &peekChar, 1, &br2, 0);
//            if (!br2)
//               *dst++ = src[i];
//            else if (peekChar == '\n')
//               *dst++ = '\n';
//            else
//            {
//               fseek_dup(str, -1, SEEK_CUR);
//               *dst++ = src[i];
//            }
//         }
//         else
//            *dst++ = src[i];
//      }
//
//      memory_free_dbg(src, 0);
//   }
//
//   return br / size;
//
//#else
//
//   return fread(buffer, size, count, str);
//
//#endif
//
//}
//
//size_t fwrite_dup(const void *buffer, size_t size, size_t count, _FILE *str)
//{
//
//#ifdef WINDOWS
//
//   DWORD bw = 0, bw2 = 0;
//
//   if (size*count == 0)
//      return 0;
//
//   HANDLE hFile = (HANDLE)((_FILE*)str)->_base;
//   int32_t textMode = ((_FILE*)str)->_flag & _FILE_TEXT;
//
//   if (hFile == NULL)
//      return 0;
//
//   // Text-mode translation is always ANSI!
//   if (textMode)			// text mode -> translate LF -> CRLF
//   {
//      const char *src = (const char*)buffer;
//      size_t startpos = 0, i = 0;
//      for (i = 0; i < size*count; i++)
//      {
//         if (src[i] != '\n')
//            continue;
//         if (i > 0 && src[i - 1] == '\r')		// don't translate CRLF
//            continue;
//
//         if (i > startpos)
//         {
//            size_t dwWritten = 0;
//            while (i - startpos - dwWritten > 0)
//            {
//               if (!WriteFile(hFile, &src[startpos + dwWritten], (uint32_t)MIN(1024, i - startpos - dwWritten), &bw2, 0))
//                  return 0;
//               bw += bw2;
//               dwWritten += bw2;
//            }
//         }
//
//         const char *crlf = "\r\n";
//         WriteFile(hFile, crlf, 2, &bw2, 0);
//         bw++;		// one '\n' written
//
//         startpos = i + 1;
//      }
//
//      size_t dwWritten = 0;
//      while (i - startpos - dwWritten > 0)
//      {
//         WriteFile(hFile, &src[startpos + dwWritten], (uint32_t)MIN(1024, i - startpos - dwWritten), &bw2, 0);
//         bw += bw2;
//         dwWritten += bw2;
//      }
//   }
//   else
//   {
//      size_t s = size * count;
//      const char *src = (const char*)buffer;
//      size_t dwWritten = 0;
//      while (s - dwWritten > 0)
//      {
//         WriteFile(hFile, &src[dwWritten], (uint32_t)MIN(1024, s - dwWritten), &bw2, 0);
//         bw += bw2;
//         dwWritten += bw2;
//      }
//   }
//   return bw / size;
//
//#else
//
//   return fwrite(buffer, size, count, str);
//
//#endif
//
//}
//
//char *fgets_dup(char *str, int32_t n, _FILE *s)
//{
//
//#ifdef WINDOWS
//
//   if (feof_dup(s))
//      return 0;
//
//   int32_t i;
//   for (i = 0; i < n - 1; i++)
//   {
//      if (!fread_dup(&str[i], 1, sizeof(char), s))
//         break;
//      if (str[i] == '\r')
//      {
//         i--;
//         continue;
//      }
//      if (str[i] == '\n')
//      {
//         i++;
//         break;
//      }
//   }
//
//   str[i] = 0;
//   return str;
//
//#else
//
//   return fgets_dup(str, n, s);
//
//#endif
//
//}
//
//#ifdef WINDOWS
//
//wchar_t *fgetws_dup(wchar_t *str, int32_t n, _FILE *s)
//{
//   // Text-mode fgetws converts MBCS->Unicode
//   if (((_FILE*)str)->_flag & _FILE_TEXT)
//   {
//      char *bfr = (char*)memory_alloc(n);
//      fgets_dup(bfr, n, s);
//      MultiByteToWideChar(CP_ACP, 0, bfr, -1, str, n);
//      memory_free_dbg(bfr, 0);
//      return str;
//   }
//
//   // Binary fgetws reads as Unicode
//
//   if (feof_dup(s))
//      return 0;
//
//   int32_t i;
//   for (i = 0; i < n - 1; i++)
//   {
//      if (!fread_dup(&str[i], 1, sizeof(wchar_t), s))
//         break;
//      if (str[i] == L'\r')
//      {
//         i--;
//         continue;	// does i++
//      }
//      if (str[i] == L'\n')
//      {
//         i++;
//         break;
//      }
//   }
//
//   str[i] = 0;
//   return str;
//}
//
//#endif
//
//
//int32_t fgetc_dup(_FILE *s)
//{
//   if (s == 0 || feof_dup(s))
//      return EOF;
//
//   uchar c;
//   fread_dup(&c, 1, sizeof(uchar), s);
//
//   return (int32_t)c;
//}
//
//int32_t ungetc_dup(int32_t c, _FILE *s)
//{
//   if (s == 0)
//      return EOF;
//
//   fseek_dup(s, -1, SEEK_CUR);
//
//   return (int32_t)c;
//}
//
//#ifdef WINDOWS
//
//wint_t fgetwc_dup(_FILE *s)
//{
//   if (s == 0 || feof_dup(s))
//      return (wint_t)EOF;
//
//   // text-mode fgetwc reads and converts MBCS
//   if (((_FILE*)s)->_flag & _FILE_TEXT)
//   {
//      char ch = (char)fgetc_dup(s);
//      wint_t wch;
//      MultiByteToWideChar(CP_ACP, 0, &ch, 1, (LPWSTR)&wch, 1);
//      return wch;
//   }
//
//   // binary fgetwc reads unicode
//
//   wint_t c;
//   fread_dup(&c, 1, sizeof(wint_t), s);
//
//   return c;
//
//}
//
//wint_t ungetwc_dup(wint_t w, _FILE *s)
//{
//   if (s == 0)
//      return EOF;
//
//   fseek_dup(s, -2, SEEK_CUR);
//
//   return (int32_t)w;
//}
//
//#endif
//
//
//int32_t ferror_dup(_FILE *fp)
//{
//
//#ifdef WINDOWS
//
//   return fp->_flag & _FILE_ERROR;
//
//#else
//
//   return ferror(fp);
//
//#endif
//
//}
//
//#if defined(LINUX) || defined(MACOS)
//uint64_t fsize_dup(FILE * fp)
//{
//   size_t pos = ftell(fp);
//   fseek(fp, 0, SEEK_END);
//   size_t len = ftell(fp);
//   fseek(fp, pos, SEEK_SET);
//   return len;
//}
//#else
//uint64_t fsize_dup(HANDLE h)
//{
//   DWORD dwHi;
//   uint32_t dwLo = ::GetFileSize(h, &dwHi);
//   if (dwHi)
//      return 0;
//   return dwLo | (((DWORD64)dwHi) << 32);
//}
//#endif
