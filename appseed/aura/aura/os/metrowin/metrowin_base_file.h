#pragma once


//CLASS_DECL_AURA void ensure_file_size(HANDLE h, int64_t iSize);
CLASS_DECL_AURA DWORD WinGetFileAttributesW(const unichar * psz);
#define WinGetFileAttributes WinGetFileAttributesW
CLASS_DECL_AURA DWORD GetFileSize(HANDLE h, LPDWORD lpdwHi);
CLASS_DECL_AURA DWORD WinSetFilePointer(HANDLE h, LONG lMove, PLONG plHi, DWORD dwMeth);
//CLASS_DECL_AURA HANDLE FindFirstFile(const char * psz, WIN32_FIND_DATA * pdata);

BEGIN_EXTERN_C

CLASS_DECL_AURA HANDLE WinFindFirstFileA(const char * pwsz, WIN32_FIND_DATAA * pdata);
CLASS_DECL_AURA HANDLE WinFindFirstFileW(const unichar * pwsz, WIN32_FIND_DATAW * pdata);

END_EXTERN_C

int ftruncate(int file, file_size_t len);