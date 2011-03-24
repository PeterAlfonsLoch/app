#include "StdAfx.h"
#include "win1.h"

namespace win
{
   int win::function()
   {
      return 0;
   }

   HINSTANCE LoadLibrary(const char * lpsz)
   {
      wstring wstr;
      gen::international::utf8_to_unicode(wstr, lpsz);
      return ::LoadLibraryW(wstr);
   }
   BOOL CLASS_DECL_VMSWIN SHGetSpecialFolderPath(HWND hwnd, string &str, int csidl, BOOL fCreate)
   {
      wstring wstrPath;
      wchar_t * lpsz = wstrPath.GetBuffer(MAX_PATH);
      BOOL b = ::SHGetSpecialFolderPathW(
         hwnd,
         lpsz,
         csidl,
         fCreate);
      wstrPath.ReleaseBuffer();
      gen::international::unicode_to_utf8(str, wstrPath);
      return b;
   }

   DWORD GetFileAttributes(const char * lpFileName)
   {
      wstring wstr;
      gen::international::utf8_to_unicode(wstr, lpFileName);
      return ::GetFileAttributesW(wstr);
   }

   BOOL CreateDirectory(const char * lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
   {
      wstring wstr;
      gen::international::utf8_to_unicode(wstr, lpPathName);
      return ::CreateDirectoryW(wstr, lpSecurityAttributes);
   }
   DWORD GetCurrentDirectory(string & str)
   {
      wstring wstrPath;
      wchar_t * lpsz = wstrPath.GetBuffer(MAX_PATH);
      DWORD dw = ::GetCurrentDirectoryW(
         MAX_PATH,
         lpsz);
      wstrPath.ReleaseBuffer();
      gen::international::unicode_to_utf8(str, wstrPath);
      return dw;
   }

   DWORD GetTempPath(string & str)
   {
      wstring wstrPath;
      wchar_t * lpsz = wstrPath.GetBuffer(4096);
      DWORD dw = ::GetTempPathW(4096,   // length of the buffer
               lpsz);      // buffer for path 
      wstrPath.ReleaseBuffer();
      gen::international::unicode_to_utf8(str, wstrPath);
      return dw;
   }
   LONG RegQueryValue(HKEY hkey, const char * lpszSubKey, string & str)
   {
      DWORD dwType = 0;
      DWORD dwSize = 0;
      LONG lResult = RegQueryValueEx(hkey, lpszSubKey, NULL, &dwType, NULL, &dwSize);
      if(lResult != ERROR_SUCCESS)
         return lResult;
      ASSERT(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ);
      if(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ)
      {
         lResult = RegQueryValueEx(hkey, lpszSubKey, NULL, &dwType, (LPBYTE) str.GetBufferSetLength(dwSize), &dwSize);
         str.ReleaseBuffer(dwSize);
         return lResult;
      }
      else
      {
         return ERROR_NOT_SUPPORTED;
      }
   }

   HICON ExtractIcon(HINSTANCE hInst, const char * lpszExeFileName, UINT nIconIndex)
   {
      wstring wstr;
      gen::international::utf8_to_unicode(wstr, lpszExeFileName);
      return ::ExtractIconW(hInst, wstr, nIconIndex);
   }

   BOOL  DeleteFile(const char * lpFileName)
   {
      wstring wstr;
      gen::international::utf8_to_unicode(wstr, lpFileName);
      return ::DeleteFileW(wstr);
   }

   int GetMenuString(HMENU hmenu, UINT uIDItem, string & str, UINT flags)
   {
      wstring wstr;
      int iLen = _GetMenuString(hmenu, uIDItem, wstr, flags);
      gen::international::unicode_to_utf8(str, wstr);
      return iLen;
   }

   CLASS_DECL_VMSWIN void TimeToFileTime(::ca::application * papp, const class time& time, LPFILETIME pFileTime)
   {
         SYSTEMTIME sysTime;
         sysTime.wYear = (WORD)time.GetYear();
         sysTime.wMonth = (WORD)time.GetMonth();
         sysTime.wDay = (WORD)time.GetDay();
         sysTime.wHour = (WORD)time.GetHour();
         sysTime.wMinute = (WORD)time.GetMinute();
         sysTime.wSecond = (WORD)time.GetSecond();
         sysTime.wMilliseconds = 0;

         // convert system time to local file time
         FILETIME localTime;
         if (!SystemTimeToFileTime((LPSYSTEMTIME)&sysTime, &localTime))
               WinFileException::ThrowOsError(papp, (LONG)::GetLastError());

         // convert local file time to UTC file time
         if (!LocalFileTimeToFileTime(&localTime, pFileTime))
               WinFileException::ThrowOsError(papp, (LONG)::GetLastError());
   }


} // namespace win
