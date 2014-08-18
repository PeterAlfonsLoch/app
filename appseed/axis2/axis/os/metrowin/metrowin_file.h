#pragma once


CLASS_DECL_AXIS void ensure_file_size(HANDLE h, int64_t iSize);
CLASS_DECL_AXIS DWORD GetFileAttributesW(const wchar_t * psz);
#define GetFileAttributes GetFileAttributesW
CLASS_DECL_AXIS DWORD GetFileSize(HANDLE h, LPDWORD lpdwHi);
CLASS_DECL_AXIS DWORD SetFilePointer(HANDLE h, LONG lMove, PLONG plHi, DWORD dwMeth);
//CLASS_DECL_AXIS HANDLE FindFirstFile(const char * psz, WIN32_FIND_DATA * pdata);

BEGIN_EXTERN_C

CLASS_DECL_AXIS HANDLE FindFirstFileA(const char * pwsz, WIN32_FIND_DATAA * pdata);
CLASS_DECL_AXIS HANDLE FindFirstFileW(const wchar_t * pwsz, WIN32_FIND_DATAW * pdata);

END_EXTERN_C

int ftruncate(int file, file_size len);