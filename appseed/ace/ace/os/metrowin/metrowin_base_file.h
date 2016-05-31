#pragma once


//CLASS_DECL_ACE void ensure_file_size(HANDLE h, int64_t iSize);
CLASS_DECL_ACE DWORD GetFileAttributesW(const unichar * psz);
#define GetFileAttributes GetFileAttributesW
CLASS_DECL_ACE DWORD GetFileSize(HANDLE h, LPDWORD lpdwHi);
CLASS_DECL_ACE DWORD SetFilePointer(HANDLE h, LONG lMove, PLONG plHi, DWORD dwMeth);
//CLASS_DECL_ACE HANDLE FindFirstFile(const char * psz, WIN32_FIND_DATA * pdata);

BEGIN_EXTERN_C

CLASS_DECL_ACE HANDLE FindFirstFileA(const char * pwsz, WIN32_FIND_DATAA * pdata);
CLASS_DECL_ACE HANDLE FindFirstFileW(const unichar * pwsz, WIN32_FIND_DATAW * pdata);

END_EXTERN_C

int ftruncate(int file, file_size_t len);