#pragma once


CLASS_DECL_BASE void ensure_file_size(HANDLE h, int64_t iSize);
CLASS_DECL_BASE DWORD GetFileAttributesW(const wchar_t * psz);
#define GetFileAttributes GetFileAttributesW
CLASS_DECL_BASE DWORD GetFileSize(HANDLE h, LPDWORD lpdwHi);
CLASS_DECL_BASE DWORD SetFilePointer(HANDLE h, LONG lMove, PLONG plHi, DWORD dwMeth);
//CLASS_DECL_BASE HANDLE FindFirstFile(const char * psz, WIN32_FIND_DATA * pdata);

BEGIN_EXTERN_C

CLASS_DECL_BASE HANDLE FindFirstFileA(const char * pwsz, WIN32_FIND_DATAA * pdata);
CLASS_DECL_BASE HANDLE FindFirstFileW(const wchar_t * pwsz, WIN32_FIND_DATAW * pdata);

END_EXTERN_C

int ftruncate(int file, file_size len);