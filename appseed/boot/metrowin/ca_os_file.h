#pragma once


CLASS_DECL_ca void ensure_file_size(HANDLE h, int64_t iSize);
CLASS_DECL_ca DWORD GetFileAttributesW(const wchar_t * psz);
#define GetFileAttributes GetFileAttributesW
CLASS_DECL_ca DWORD GetFileSize(HANDLE h, LPDWORD lpdwHi);
CLASS_DECL_ca DWORD SetFilePointer(HANDLE h, LONG lMove, PLONG plHi, DWORD dwMeth);
//CLASS_DECL_ca HANDLE FindFirstFile(const char * psz, WIN32_FIND_DATA * pdata);


CLASS_DECL_ca ::Windows::Storage::StorageFolder ^ get_os_folder(const char * lpcszDirName);
CLASS_DECL_ca ::Windows::Storage::StorageFile ^ get_os_file(const char * lpcszFileName, dword dwDesiredAcces, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile);
CLASS_DECL_ca bool get_file_time(::Windows::Storage::StorageFile ^ file, LPFILETIME lpCreationTime, LPFILETIME lpItemTime, LPFILETIME lpLastWriteTime);



