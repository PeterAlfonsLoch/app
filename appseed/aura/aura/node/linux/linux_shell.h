#pragma once

#define WH_SHSTDAPI(type) type


namespace linux
{

class CLASS_DECL_AURA shell
{
public:
   shell();
   virtual ~shell();


   static shell theLinuxShell;

   static bool Initialize();
// xxx   static WINBOOL WINAPI _SHGetPathFromIDList(LPCITEMIDLIST pidl, char16_t * pszPath);
// xxx   static HANDLE WINAPI _FindFirstFile(const char16_t * lpcsz, WIN32_FIND_DATAW * lpdata);
// xxx   static WINBOOL WINAPI _FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata);
/*   static WINBOOL WINAPI _MoveFile(const char16_t * lpExistingFileName, const char16_t * lpNewFileName);
   static DWORD WINAPI _GetFullPathName(const char16_t * lpFileName, DWORD nBufferLength, char16_t * lpBuffer, char16_t ** lpFilePart);
   static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
   static WINBOOL WINAPI _GetVolumeInformation(
      const char16_t * lpRootPathName,           // root directory
      char16_t * lpVolumeNameBuffer,        // volume name buffer
      DWORD nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      char16_t * lpFileSystemNameBuffer,    // file system name buffer
      DWORD nFileSystemNameSize);         // length of file system name buffer
// xxx   static DWORD_PTR __stdcall _SHGetFileInfo(
      // xxx const char16_t * pszPath,
      // xxx DWORD dwFileAttributes,
      // xxx SHFILEINFOW *psfi,
      // xxx UINT cbFileInfo,
      // xxx UINT uFlags);
   static WINBOOL __stdcall _GetStringTypeEx(
      LCID Locale,
      DWORD dwInfoType,
      const char16_t * lpSrcStr,
      int32_t cchSrc,
      LPWORD lpCharType);
   static DWORD WINAPI  _GetTempPath(
      DWORD nBufferLength,
      char16_t * lpBuffer);
   static UINT WINAPI _GetTempFileName(
      const char16_t * lpPathName,
      const char16_t * lpPrefixString,
      UINT uUnique,
      char16_t * lpTempFileName);
   static HANDLE WINAPI _CreateFile(
      const char16_t * lpFileName,
      DWORD dwDesiredAccess,
      DWORD dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      DWORD dwCreationDisposition,
      DWORD dwFlagsAndAttributes,
      HANDLE hTemplateFile
      );
   static DWORD WINAPI _GetModuleFileName(
       HMODULE hModule,
       char16_t * lpFilename,
       DWORD nSize
       );
// xxx    static WINBOOL WINAPI _GetClassInfo(
// xxx        HINSTANCE hInstance ,
// xxx        const char16_t * lpClassName,
// xxx        LPWNDCLASSW lpWndClass);
// xxx    static ATOM WINAPI _RegisterClass(
         // xxx CONST WNDCLASSW *lpWndClass);

   static oswindow WINAPI _CreateWindowEx(
      DWORD dwExStyle,
      const char16_t * lpClassName,
      const char16_t * lpWindowName,
      DWORD dwStyle,
      int32_t x,
      int32_t y,
      int32_t nWidth,
      int32_t nHeight,
      oswindow hWndParent,
      HMENU hMenu,
      HINSTANCE hInstance,
      LPVOID lpParam);





// xxx    WINBOOL (WINAPI * m_pfnSHGetPathFromIDList)(LPCITEMIDLIST pidl, char16_t * pszPath);
// xxx    HANDLE (WINAPI * m_pfnFindFirstFile)(const char16_t * lpcsz, WIN32_FIND_DATAW * lpdata);
// xxx    WINBOOL (WINAPI * m_pfnFindNextFile)(HANDLE handle, WIN32_FIND_DATAW * lpdata);
   WINBOOL (WINAPI * m_pfnMoveFile)(const char16_t * lpExistingFileName, const char16_t * lpNewFileName);
   WCHAR * (__cdecl * m_pfn_fullpath)(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
   DWORD (WINAPI * m_pfnGetFullPathName)(const char16_t * lpFileName, DWORD nBufferLength, char16_t * lpBuffer, char16_t ** lpFilePart);
   WINBOOL (WINAPI * m_pfnGetVolumeInformation)(
      const char16_t * lpRootPathName,           // root directory
      char16_t * lpVolumeNameBuffer,        // volume name buffer
      DWORD nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      char16_t * lpFileSystemNameBuffer,    // file system name buffer
      DWORD nFileSystemNameSize);         // length of file system name buffer

// xxx    DWORD_PTR (__stdcall * m_pfnSHGetFileInfo)(
// xxx       const char16_t * pszPath,
// xxx       DWORD dwFileAttributes,
// xxx       SHFILEINFOW *psfi,
// xxx       UINT cbFileInfo,
// xxx       UINT uFlags);
   WINBOOL (__stdcall * m_pfnGetStringTypeEx)(
      LCID Locale,
      DWORD dwInfoType,
      const char16_t * lpSrcStr,
      int32_t cchSrc,
      LPWORD lpCharType);
   DWORD (WINAPI * m_pfnGetTempPath)(
      DWORD nBufferLength,
      char16_t * lpBuffer);
   UINT (WINAPI * m_pfnGetTempFileName)(
      const char16_t * lpPathName,
      const char16_t * lpPrefixString,
      UINT uUnique,
      char16_t * lpTempFileName);
   HANDLE (WINAPI * m_pfnCreateFile)(
      const char16_t * lpFileName,
      DWORD dwDesiredAccess,
      DWORD dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      DWORD dwCreationDisposition,
      DWORD dwFlagsAndAttributes,
      HANDLE hTemplateFile
      );

   DWORD (WINAPI * m_pfnGetModuleFileName)(
       HMODULE hModule,
       char16_t * lpFilename,
       DWORD nSize
       );

// xxx    WINBOOL (WINAPI * m_pfnGetClassInfo)(
       // xxx HINSTANCE hInstance ,
// xxx        const char16_t * lpClassName,
// xxx        LPWNDCLASSW lpWndClass);

   // xxx ATOM (WINAPI * m_pfnRegisterClass)(
         // xxx CONST WNDCLASSW *lpWndClass);

   oswindow (WINAPI * m_pfnCreateWindowEx)(
      DWORD dwExStyle,
      const char16_t * lpClassName,
      const char16_t * lpWindowName,
      DWORD dwStyle,
      int32_t x,
      int32_t y,
      int32_t nWidth,
      int32_t nHeight,
      oswindow hWndParent,
      HMENU hMenu,
      HINSTANCE hInstance,
      LPVOID lpParam);








// xxx    static WINBOOL SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str);
// xxx    static WINBOOL SHGetPathFromIDList(LPCITEMIDLIST pidl, char16_t * pszPath);
// xxx    static HANDLE FindFirstFile(const char16_t * lpcsz, WIN32_FIND_DATAW * lpdata);
// xxx    static WINBOOL WINAPI FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata);
   static WINBOOL MoveFile(const char16_t * lpExistingFileName, const char16_t * lpNewFileName);
   static WCHAR * __cdecl _fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
   static DWORD GetFullPathName(const char16_t * lpFileName, DWORD nBufferLength, char16_t * lpBuffer, char16_t ** lpFilePart);
   static WINBOOL GetVolumeInformation(
      const char16_t * lpRootPathName,           // root directory
      char16_t * lpVolumeNameBuffer,        // volume name buffer
      DWORD nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      char16_t * lpFileSystemNameBuffer,    // file system name buffer
      DWORD nFileSystemNameSize);         // length of file system name buffer

// xxx    static WH_SHSTDAPI(DWORD) SHGetFileInfo(
// xxx       const char16_t * pszPath,
// xxx       DWORD dwFileAttributes,
// xxx       SHFILEINFOW *psfi,
// xxx       UINT cbFileInfo,
// xxx       UINT uFlags);

   static WINBOOL  GetStringTypeEx(
      LCID Locale,
      DWORD dwInfoType,
      const char * lpSrcStr,
      int32_t cchSrc,
      LPWORD lpCharType);

   static DWORD GetTempPathW(
      DWORD nBufferLength,
      char16_t * lpBuffer);

   static UINT GetTempFileNameW(
      const char16_t * lpPathName,
      const char16_t * lpPrefixString,
      UINT uUnique,
      char16_t * lpTempFileName);

   static HANDLE CreateFile(
      const char16_t * lpFileName,
      DWORD dwDesiredAccess,
      DWORD dwShareMode,
      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      DWORD dwCreationDisposition,
      DWORD dwFlagsAndAttributes,
      HANDLE hTemplateFile);

   static DWORD WINAPI GetModuleFileName(
       HMODULE hModule,
        char16_t * lpFilename,
        DWORD nSize
       );

// xxx    static WINBOOL WINAPI GetClassInfo(
// xxx        HINSTANCE hInstance ,
// xxx        const char16_t * lpClassName,
// xxx        LPWNDCLASSW lpWndClass);

// xxx    static ATOM WINAPI RegisterClass(
// xxx          CONST WNDCLASSW *lpWndClass);

   static oswindow WINAPI CreateWindowEx(
      DWORD dwExStyle,
      const char16_t * lpClassName,
      const char16_t * lpWindowName,
      DWORD dwStyle,
      int32_t x,
      int32_t y,
      int32_t nWidth,
      int32_t nHeight,
      oswindow hWndParent,
      HMENU hMenu,
      HINSTANCE hInstance,
      LPVOID lpParam);


// xxx    static WH_SHSTDAPI(DWORD) SHGetFileInfo(
// xxx       const char * pszPath,
// xxx       DWORD dwFileAttributes,
// xxx       SHFILEINFO *psfi,
// xxx       UINT cbFileInfo,
// xxx       UINT uFlags);

   static DWORD GetTempPath(string & str);

   static UINT GetTempFileName(
      const char * lpPathName,
      const char * lpPrefixString,
      UINT uUnique,
      string & str);

   static WINBOOL MoveFile(const char * lpExistingFileName, const char * lpNewFileName);
*/
};



/*inline WINBOOL shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str)
{
   char16_t * pwszPath = (char16_t *) malloc(sizeof(char16_t) * MAX_PATH * 4);
   if(!(*theLinuxShell.m_pfnSHGetPathFromIDList)(pidl, pwszPath))
   {
      free(pwszPath);
      return FALSE;
   }
   ::str::international::unicode_to_utf8(str, pwszPath);
   free(pwszPath);
   return TRUE;
}
*/
/*

inline WINBOOL shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, char16_t * pszPath)
{
   return (*theLinuxShell.m_pfnSHGetPathFromIDList)(pidl, pszPath);
}
*/
/*
inline HANDLE shell::FindFirstFile(const char16_t * lpcsz, WIN32_FIND_DATAW * lpdata)
{
   return (*theLinuxShell.m_pfnFindFirstFile)(lpcsz, lpdata);
}

inline WINBOOL shell::FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata)
{
   return (*theLinuxShell.m_pfnFindNextFile)(handle, lpdata);
}

*/

/*
inline WCHAR * shell::_fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen)
{
   return (*theLinuxShell.m_pfn_fullpath)(UserBuf, path, maxlen);
}

inline DWORD shell::GetFullPathName(const char16_t * lpFileName, DWORD nBufferLength, char16_t * lpBuffer, char16_t ** lpFilePart)
{
   return (*theLinuxShell.m_pfnGetFullPathName)(lpFileName, nBufferLength, lpBuffer, lpFilePart);
}


inline WINBOOL shell::MoveFile(const char16_t * lpExistingFileName, const char16_t * lpNewFileName)
{
   return (*theLinuxShell.m_pfnMoveFile)(lpExistingFileName, lpNewFileName);
}

inline WINBOOL shell::GetVolumeInformation(
      const char16_t * lpRootPathName,           // root directory
      char16_t * lpVolumeNameBuffer,        // volume name buffer
      DWORD nVolumeNameSize,            // length of name buffer
      LPDWORD lpVolumeSerialNumber,     // volume serial number
      LPDWORD lpMaximumComponentLength, // maximum file name length
      LPDWORD lpFileSystemFlags,        // file system options
      char16_t * lpFileSystemNameBuffer,    // file system name buffer
      DWORD nFileSystemNameSize)         // length of file system name buffer
{
   return (*theLinuxShell.m_pfnGetVolumeInformation)(
      lpRootPathName,           // root directory
      lpVolumeNameBuffer,        // volume name buffer
      nVolumeNameSize,            // length of name buffer
      lpVolumeSerialNumber,     // volume serial number
      lpMaximumComponentLength, // maximum file name length
      lpFileSystemFlags,        // file system options
      lpFileSystemNameBuffer,    // file system name buffer
      nFileSystemNameSize);         // length of file system name buffer
}

/*
inline DWORD shell::SHGetFileInfo(
   const char16_t * pszPath,
   DWORD dwFileAttributes,
   SHFILEINFOW *psfi,
   UINT cbFileInfo,
   UINT uFlags)
{
   return (*theLinuxShell.m_pfnSHGetFileInfo)(
      pszPath,
      dwFileAttributes,
      psfi,
      cbFileInfo,
      uFlags);
}
*/
/*
inline DWORD shell::GetTempPathW(
   DWORD nBufferLength,
   char16_t * lpBuffer)
{
     return (*theLinuxShell.m_pfnGetTempPath)(
      nBufferLength,
      lpBuffer);
}

inline UINT shell::GetTempFileNameW(
   const char16_t * lpPathName,
   const char16_t * lpPrefixString,
   UINT uUnique,
   char16_t * lpTempFileName)
{
   return (*theLinuxShell.m_pfnGetTempFileName)(
      lpPathName,
      lpPrefixString,
      uUnique,
      lpTempFileName);
}

inline HANDLE shell::CreateFile(
   const char16_t * lpFileName,
   DWORD dwDesiredAccess,
   DWORD dwShareMode,
   LPSECURITY_ATTRIBUTES lpSecurityAttributes,
   DWORD dwCreationDisposition,
   DWORD dwFlagsAndAttributes,
   HANDLE hTemplateFile)
{
   return (*theLinuxShell.m_pfnCreateFile)(
      lpFileName,
      dwDesiredAccess,
      dwShareMode,
      lpSecurityAttributes,
      dwCreationDisposition,
      dwFlagsAndAttributes,
      hTemplateFile);
}

inline DWORD shell::GetModuleFileName(
    HMODULE hModule,
    char16_t * lpFilename,
    DWORD nSize
    )
{
   return (*theLinuxShell.m_pfnGetModuleFileName)(
      hModule,
      lpFilename,
      nSize);
}

/*inline WINBOOL shell::GetClassInfo(
   HINSTANCE hInstance ,
   const char16_t * lpClassName,
   LPWNDCLASSW lpWndClass)
{
   return (*theLinuxShell.m_pfnGetClassInfo)(
      hInstance ,
      lpClassName,
      lpWndClass);
}

inline ATOM shell::RegisterClass(
   CONST WNDCLASSW *lpWndClass)
{
   return (*theLinuxShell.m_pfnRegisterClass)(
      lpWndClass);
}*/
/*
inline oswindow shell::CreateWindowEx(
   DWORD dwExStyle,
   const char16_t * lpClassName,
   const char16_t * lpWindowName,
   DWORD dwStyle,
   int32_t x,
   int32_t y,
   int32_t nWidth,
   int32_t nHeight,
   oswindow hWndParent,
   HMENU hMenu,
   HINSTANCE hInstance,
   LPVOID lpParam)
{
   return (*theLinuxShell.m_pfnCreateWindowEx)(
      dwExStyle,
      lpClassName,
      lpWindowName,
      dwStyle,
      x,
      y,
      nWidth,
      nHeight,
      hWndParent,
      hMenu,
      hInstance,
      lpParam);

}

inline DWORD shell::GetTempPath(string & str)
{
   char16_t * pwsz = (char16_t *) malloc(sizeof(char16_t) * MAX_PATH * 4);
   DWORD dwResult = (*theLinuxShell.m_pfnGetTempPath)(sizeof(char16_t) * MAX_PATH * 4, pwsz);
   ::str::international::unicode_to_utf8(str, pwsz);
   free(pwsz);
   return dwResult;
}

inline UINT shell::GetTempFileName(const char * lpPathName, const char * lpPrefixString, UINT uUnique, string & str)
{
   wstring wstrPathName = ::str::international::utf8_to_unicode(lpPathName);
   wstring wstrPrefixString = ::str::international::utf8_to_unicode(lpPrefixString);
   wstring wstr;
   wstr.alloc(MAX_PATH * 4);
   UINT uiResult = (*theLinuxShell.m_pfnGetTempFileName)(
      wstrPathName,
      wstrPrefixString,
      uUnique,
      wstr);
   ::str::international::unicode_to_utf8(str, wstr);
   return uiResult;
}

inline WINBOOL shell::MoveFile(const char * lpExistingFileName, const char * lpNewFileName)
{
   return MoveFile(::str::international::utf8_to_unicode(lpExistingFileName), ::str::international::utf8_to_unicode(lpNewFileName));
}

*/


} // namespace linux

