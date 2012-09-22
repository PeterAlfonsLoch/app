#pragma once


CLASS_DECL_c void ensure_file_size(HANDLE h, int64_t iSize);
CLASS_DECL_c DWORD GetFileAttributes(const char * psz);
CLASS_DECL_c DWORD GetFileSize(HANDLE h, LPDWORD lpdwHi);
CLASS_DECL_c DWORD SetFilePointer(HANDLE h, LONG lMove, PLONG plHi, DWORD dwMeth);
CLASS_DECL_c HANDLE FindFirstFile(const char * psz, WIN32_FIND_DATA * pdata);
